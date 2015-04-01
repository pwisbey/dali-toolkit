/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// CLASS HEADER
#include <dali-toolkit/internal/controls/magnifier/magnifier-impl.h>

// EXTERNAL INCLUDES
#include <dali/public-api/animation/constraint.h>
#include <dali/public-api/animation/constraints.h>
#include <dali/public-api/common/stage.h>
#include <dali/public-api/render-tasks/render-task-list.h>
#include <dali/public-api/images/resource-image.h>

using namespace Dali;

namespace // unnamed namespace
{

const char* DEFAULT_FRAME_IMAGE_PATH = DALI_IMAGE_DIR "magnifier-image-frame.png";

const float IMAGE_BORDER_INDENT = 14.0f;            ///< Indent of border in pixels.

struct CameraActorPositionConstraint
{
  CameraActorPositionConstraint(const Vector2& stageSize, float defaultCameraDistance = 0.0f)
  : mStageSize(stageSize),
    mDefaultCameraDistance(defaultCameraDistance)
  {
  }

  void operator()( Vector3& current, const PropertyInputContainer& inputs )
  {
    const Vector3& sourcePosition = inputs[0]->GetVector3();

    current.x = sourcePosition.x + mStageSize.x * 0.5f;
    current.y = sourcePosition.y + mStageSize.y * 0.5f;
    current.z = sourcePosition.z + mDefaultCameraDistance;
  }

  Vector2 mStageSize;
  float mDefaultCameraDistance;

};

struct RenderTaskViewportPositionConstraint
{
  RenderTaskViewportPositionConstraint(const Vector2& stageSize)
  : mStageSize(stageSize)
  {
  }

  void operator()( Vector2& current, const PropertyInputContainer& inputs )
  {
    current = inputs[0]->GetVector3(); // World position?

    // should be updated when:
    // Magnifier's world position/size/scale/parentorigin/anchorpoint changes.
    // or Magnifier camera's world position changes.
    Vector3 size = inputs[1]->GetVector3() * inputs[2]->GetVector3(); /* magnifier-size * magnifier-scale */

    // Reposition, and resize viewport to reflect the world bounds of this Magnifier actor.
    current.x += ( mStageSize.width - size.width ) * 0.5f;
    current.y += ( mStageSize.height - size.height ) * 0.5f;
  }

  Vector2 mStageSize;
};

struct RenderTaskViewportSizeConstraint
{
  RenderTaskViewportSizeConstraint()
  {
  }

  void operator()( Vector2& current, const PropertyInputContainer& inputs )
  {
    current = inputs[0]->GetVector3() * inputs[1]->GetVector3(); /* magnifier-size * magnifier-scale */
  }
};

}

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

///////////////////////////////////////////////////////////////////////////////////////////////////
// Magnifier
///////////////////////////////////////////////////////////////////////////////////////////////////

Dali::Toolkit::Magnifier Magnifier::New()
{
  // Create the implementation
  MagnifierPtr magnifier(new Magnifier());

  // Pass ownership to CustomActor via derived handle
  Dali::Toolkit::Magnifier handle(*magnifier);

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  magnifier->Initialize();

  return handle;
}

Magnifier::Magnifier()
: Control( REQUIRES_TOUCH_EVENTS ),
  mPropertySourcePosition(Property::INVALID_INDEX),
  mDefaultCameraDistance(1000.f),
  mActorSize(Vector3::ZERO),
  mMagnificationFactor(1.0f)
{
}

void Magnifier::SetSourceActor(Actor actor)
{
  mTask.SetSourceActor( actor );
}

void Magnifier::SetSourcePosition(const Vector3& position)
{
  Self().SetProperty(mPropertySourcePosition, position);
}

void Magnifier::Initialize()
{
  Actor self = Self();
  mPropertySourcePosition = self.RegisterProperty( Toolkit::Magnifier::SOURCE_POSITION_PROPERTY_NAME, Vector3::ZERO );
  Vector2 stageSize(Stage::GetCurrent().GetSize());

  // NOTE:
  // sourceActor is a dummy delegate actor that takes the source property position,
  // and generates a WORLD_POSITION, which is 1 frame behind the source property.
  // This way the constraints for determining the camera position (source) and those
  // for determining viewport position use the same 1 frame old values.
  // A simple i) CameraPos = f(B), ii) B = f(A) set of constraints wont suffice as
  // although CameraPos will use B, which is A's previous value. The constraint will
  // not realise that B is still dirty as far as constraint (i) is concerned.
  // Perhaps this is a bug in the way the constraint system factors into what is dirty
  // and what is not.
  mSourceActor = Actor::New();
  Stage().GetCurrent().Add(mSourceActor);
  mSourceActor.SetParentOrigin(ParentOrigin::CENTER);
  Constraint constraint = Constraint::New<Vector3>( Actor::Property::POSITION, EqualToConstraint() );
  constraint.AddSource( Source( self, mPropertySourcePosition ) );
  mSourceActor.ApplyConstraint(constraint);

  // create the render task this will render content on top of everything
  // based on camera source position.
  InitializeRenderTask();

  // set up some constraints to:
  // i) reposition (dest) frame actor based on magnifier actor's world position (this is 1 frame delayed)
  // ii) reposition and resize (dest) the render task's viewport based on magnifier actor's world position (1 frame delayed) & size.
  // iii) reposition (source) camera actor based on magnifier source actor's world position (this is 1 frame delayed)

  // Apply constraint to camera's position
  // Position our camera at the same distance from its target as the default camera is.
  // The camera position doesn't affect how we render, just what we render (due to near and far clip planes)
  // NOTE: We can't interrogate the default camera's position as it is not known initially (takes 1 frame
  // for value to update).
  // But we can determine the initial position using the same formula:
  // distance = stage.height * 0.5 / tan(FOV * 0.5)

  RenderTaskList taskList = Stage::GetCurrent().GetRenderTaskList();
  RenderTask renderTask = taskList.GetTask(0u);
  float fov = renderTask.GetCameraActor().GetFieldOfView();
  mDefaultCameraDistance = (stageSize.height * 0.5f) / tanf(fov * 0.5f);

  // Use a 1 frame delayed source position to determine the camera actor's position.
  // This is necessary as the viewport is determined by the Magnifier's Actor's World position (which is computed
  // at the end of the update cycle i.e. after constraints have been applied.)
  //Property::Index propertySourcePositionDelayed = mCameraActor.RegisterProperty("delayed-source-position", Vector3::ZERO);

  constraint = Constraint::New<Vector3>( Actor::Property::POSITION, CameraActorPositionConstraint(stageSize, mDefaultCameraDistance) );
  constraint.AddSource( Source( mSourceActor, Actor::Property::WORLD_POSITION ) );
  mCameraActor.ApplyConstraint(constraint);

  // Apply constraint to render-task viewport position
  constraint = Constraint::New<Vector2>( RenderTask::Property::VIEWPORT_POSITION, RenderTaskViewportPositionConstraint(stageSize) );
  constraint.AddSource( Source( self, Actor::Property::WORLD_POSITION ) );
  constraint.AddSource( Source( self, Actor::Property::SIZE ) );
  constraint.AddSource( Source( self, Actor::Property::WORLD_SCALE ) );
  mTask.ApplyConstraint(constraint);

  // Apply constraint to render-task viewport position
  constraint = Constraint::New<Vector2>( RenderTask::Property::VIEWPORT_SIZE, RenderTaskViewportSizeConstraint() );
  constraint.AddSource( Source( self, Actor::Property::SIZE ) );
  constraint.AddSource( Source( self, Actor::Property::WORLD_SCALE ) );
  mTask.ApplyConstraint(constraint);
}

Magnifier::~Magnifier()
{

}

void Magnifier::InitializeRenderTask()
{
  Stage stage = Stage::GetCurrent();

  RenderTaskList taskList = stage.GetRenderTaskList();

  mTask = taskList.CreateTask();
  mTask.SetInputEnabled(false);
  mTask.SetClearColor(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
  mTask.SetClearEnabled(true);

  mCameraActor = CameraActor::New();
  mCameraActor.SetType(Camera::FREE_LOOK);

  stage.Add(mCameraActor);
  mTask.SetCameraActor( mCameraActor );

  SetFrameVisibility(true);
}

bool Magnifier::GetFrameVisibility() const
{
  return mFrame;
}

void Magnifier::SetFrameVisibility(bool visible)
{
  if(visible && !mFrame)
  {
    Actor self(Self());

    Image image = ResourceImage::New( DEFAULT_FRAME_IMAGE_PATH );
    mFrame = ImageActor::New( image );
    mFrame.SetRelayoutEnabled( false );
    mFrame.SetDrawMode(DrawMode::OVERLAY);
    mFrame.SetStyle( ImageActor::STYLE_NINE_PATCH );
    mFrame.SetPositionInheritanceMode(DONT_INHERIT_POSITION);
    mFrame.SetInheritScale(true);

    Constraint constraint = Constraint::New<Vector3>( Actor::Property::POSITION, EqualToConstraint() );
    constraint.AddSource( ParentSource( Actor::Property::WORLD_POSITION ) );
    mFrame.ApplyConstraint( constraint );

    mFrame.SetNinePatchBorder( Vector4::ONE * IMAGE_BORDER_INDENT );
    self.Add(mFrame);

    Vector3 sizeOffset(IMAGE_BORDER_INDENT*2.f - 2.f, IMAGE_BORDER_INDENT*2.f - 2.f, 0.0f);
    mFrame.SetSize(mActorSize + sizeOffset);
  }
  else if(!visible && mFrame)
  {
    UnparentAndReset(mFrame);
  }
}

void Magnifier::OnControlSizeSet(const Vector3& targetSize)
{
  if( mFrame )
  {
    Vector3 sizeOffset(IMAGE_BORDER_INDENT*2.f - 2.f, IMAGE_BORDER_INDENT*2.f - 2.f, 0.0f);
    mFrame.SetSize(targetSize + sizeOffset);
  }

  // TODO: Once Camera/CameraActor properties function as proper animatable properties
  // this code can disappear.
  // whenever the size of the magnifier changes, the field of view needs to change
  // to compensate for the new size of the viewport. this cannot be done within
  // a constraint yet as Camera/CameraActor properties are not animatable/constrainable.
  mActorSize = targetSize;
  Update();
}

float Magnifier::GetMagnificationFactor() const
{
  return mMagnificationFactor;
}

void Magnifier::SetMagnificationFactor(float value)
{
  mMagnificationFactor = value;
  Update();
}

void Magnifier::Update()
{
  // TODO: Make Camera settings (fieldofview/aspectratio) as animatable constraints.

  // should be updated when:
  // Magnifier's world size/scale changes.
  Actor self(Self());
  Vector3 worldSize = mActorSize * self.GetCurrentWorldScale();

  // Adjust field of view to scale content

  // size.height / 2
  // |------/
  // |d    /
  // |i   /
  // |s  /
  // |t /
  // |./
  // |/ <--- fov/2 radians.
  //
  const float fov = atanf( 0.5f * worldSize.height / mDefaultCameraDistance / mMagnificationFactor) * 2.0f;
  mCameraActor.SetFieldOfView( fov );

  // Adjust aspect ratio to compensate for rectangular viewports.
  mCameraActor.SetAspectRatio( worldSize.width / worldSize.height );
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
