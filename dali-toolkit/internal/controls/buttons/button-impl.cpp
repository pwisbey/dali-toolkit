/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include "button-impl.h"

// EXTERNAL INCLUDES
#include <cstring> // for strcmp
#include <dali/public-api/events/touch-data.h>
#include <dali/public-api/images/resource-image.h>
#include <dali/public-api/object/type-registry.h>
#include <dali/public-api/object/type-registry-helper.h>
#include <dali/devel-api/scripting/scripting.h>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/text-controls/text-label.h>
#include <dali-toolkit/public-api/controls/image-view/image-view.h>
#include <dali-toolkit/public-api/visuals/color-visual-properties.h>
#include <dali-toolkit/devel-api/visual-factory/visual-factory.h>


/**
 * Button states and contents
 *                                         (3) mSelectedContent
 *  (2) mUnselectedContent                 (2) mSelectedBackgroundContent
 *  (1) mBackgroundContent                 (1) mBackgroundContent
 * < unselected > ----------------------- < selected >
 *       |                OnSelect()            |
 *       | OnDisabled()                         | OnDisabled()
 *       |                                      |
 * < disabled >                           < disabled-selected >
 *  (2) mDisabledContent                   (2) mDisabledSelectedContent
 *  (1) mDisabledBackgroundContent         (1) mDisabledBackgroundContent
 *
 * The drawing order of child actors is as follows.
 *
 *  Top      mLabel
 *   |       mUnselectedContent / mSelectedContent / mDisabledContent / mDisabledSelectedContent
 *   |       mSelectedBackgroundContent
 * Bottom    mBackgroundContent / mDisabledBackgroundContent
 *
 * Some of contents may be missed.
 * And 2 images - fade-in image and fade-out image - in the same layer can be shown during the transition animation. Fade-in image should be above fade-out image.
 */

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace
{

BaseHandle Create()
{
  // empty handle as we cannot create button (but type registered for clicked signal)
  return BaseHandle();
}

// Setup properties, signals and actions using the type-registry.
DALI_TYPE_REGISTRATION_BEGIN( Toolkit::Button, Toolkit::Control, Create );

DALI_PROPERTY_REGISTRATION( Toolkit, Button, "disabled",                     BOOLEAN, DISABLED                     )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "autoRepeating",                BOOLEAN, AUTO_REPEATING               )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "initialAutoRepeatingDelay",    FLOAT,   INITIAL_AUTO_REPEATING_DELAY )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "nextAutoRepeatingDelay",       FLOAT,   NEXT_AUTO_REPEATING_DELAY    )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "togglable",                    BOOLEAN, TOGGLABLE                    )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "selected",                     BOOLEAN, SELECTED                     )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "unselectedStateImage",         STRING,  UNSELECTED_STATE_IMAGE       )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "selectedStateImage",           STRING,  SELECTED_STATE_IMAGE         )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "disabledStateImage",           STRING,  DISABLED_STATE_IMAGE         )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "unselectedColor",              VECTOR4, UNSELECTED_COLOR             )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "selectedColor",                VECTOR4, SELECTED_COLOR               )
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "label",                        MAP,     LABEL                        )

// Deprecated properties:
DALI_PROPERTY_REGISTRATION( Toolkit, Button, "labelText",                    STRING,  LABEL_TEXT                   )

// Signals:
DALI_SIGNAL_REGISTRATION(   Toolkit, Button, "pressed",                               SIGNAL_PRESSED               )
DALI_SIGNAL_REGISTRATION(   Toolkit, Button, "released",                              SIGNAL_RELEASED              )
DALI_SIGNAL_REGISTRATION(   Toolkit, Button, "clicked",                               SIGNAL_CLICKED               )
DALI_SIGNAL_REGISTRATION(   Toolkit, Button, "stateChanged",                          SIGNAL_STATE_CHANGED         )

// Actions:
DALI_ACTION_REGISTRATION(   Toolkit, Button, "buttonClick",                           ACTION_BUTTON_CLICK          )

DALI_TYPE_REGISTRATION_END()

const unsigned int INITIAL_AUTOREPEATING_DELAY( 0.15f );
const unsigned int NEXT_AUTOREPEATING_DELAY( 0.05f );

} // unnamed namespace

Button::Button()
: Control( ControlBehaviour( REQUIRES_STYLE_CHANGE_SIGNALS ) ),
  mAutoRepeatingTimer(),
  mUnselectedColor( Color::WHITE ), // The natural colors of the specified images will be used by default.
  mSelectedColor( Color::WHITE ),
  mDisabled( false ),
  mAutoRepeating( false ),
  mTogglableButton( false ),
  mSelected( false ),
  mInitialAutoRepeatingDelay( INITIAL_AUTOREPEATING_DELAY ),
  mNextAutoRepeatingDelay( NEXT_AUTOREPEATING_DELAY ),
  mAnimationTime( 0.0f ),
  mClickActionPerforming( false ),
  mState( ButtonUp ),
  mPaintState( UnselectedState )
{
}

Button::~Button()
{
}

void Button::SetDisabled( bool disabled )
{
  if( disabled == mDisabled )
  {
    return;
  }

  StopTransitionAnimation();

  mDisabled = disabled;

  // Notifies the derived class the button has been disabled.
  OnDisabled();

  switch( mPaintState )
  {
    case UnselectedState:
    {
      //Layer Order
      //(3) mDisabledContent (Inserted)
      //(4) mUnselectedContent
      //(2) mDisabledBackgroundContent (Inserted)
      //(1) mBackgroundContent

      AddButtonImage( mBackgroundContent );
      TransitionButtonImage( mDisabledBackgroundContent );
      AddButtonImage( mUnselectedContent );
      TransitionButtonImage( mDisabledContent );

      AddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ SELECTED_DECORATION ] );
      TransitionOut( mUnselectedContent );
      TransitionOut( mSelectedContent );
      TransitionOut( mBackgroundContent );
      TransitionOut( mSelectedBackgroundContent );
      TransitionOut( mDisabledSelectedContent );

      mPaintState = DisabledUnselectedState;
      break;
    }
    case SelectedState:
    {
      //Layer Order
      //(5) mDisabledSelectedContent (Inserted)
      //(4) mSelectedContent
      //(3) mDisabledBackgroundContent (Inserted)
      //(2) mSelectedBackgroundContent
      //(1) mBackgroundContent

      AddButtonImage( mBackgroundContent );
      AddButtonImage( mSelectedBackgroundContent );
      TransitionButtonImage( mDisabledBackgroundContent );
      AddButtonImage( mSelectedContent );
      TransitionButtonImage( mDisabledSelectedContent );

      AddButtonImage( mDecoration[ SELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ UNSELECTED_DECORATION ] );
      TransitionOut( mUnselectedContent );
      TransitionOut( mSelectedContent );
      TransitionOut( mBackgroundContent );
      TransitionOut( mSelectedBackgroundContent );
      TransitionOut( mDisabledContent );

      mPaintState = DisabledSelectedState;
      break;
    }
    case DisabledUnselectedState:
    {
      //Layer Order
      //(3) mUnselectedContent (Inserted)
      //(4) mDisabledContent
      //(2) mBackgroundContent (Inserted)
      //(1) mDisabledBackgroundContent

      AddButtonImage( mDisabledBackgroundContent );
      TransitionButtonImage( mBackgroundContent );
      AddButtonImage( mDisabledContent );
      TransitionButtonImage( mUnselectedContent );

      AddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ SELECTED_DECORATION ] );
      TransitionOut( mSelectedContent );
      TransitionOut( mSelectedBackgroundContent );
      TransitionOut( mDisabledContent );
      TransitionOut( mDisabledSelectedContent );
      TransitionOut( mDisabledBackgroundContent );

      mPaintState = UnselectedState;
      break;
    }
    case DisabledSelectedState:
    {
      //Layer Order
      //(4) mSelectedContent (Inserted)
      //(5) mDisabledSelectedContent
      //(3) mSelectedBackgroundContent (Inserted)
      //(2) mBackgroundContent (Inserted)
      //(1) mDisabledBackgroundContent

      AddButtonImage( mDisabledBackgroundContent );
      TransitionButtonImage( mBackgroundContent );
      TransitionButtonImage( mSelectedBackgroundContent );
      AddButtonImage( mDisabledSelectedContent );
      TransitionButtonImage( mSelectedContent );

      AddButtonImage( mDecoration[ SELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ UNSELECTED_DECORATION ] );
      TransitionOut( mUnselectedContent );
      TransitionOut( mDisabledContent );
      TransitionOut( mDisabledSelectedContent );
      TransitionOut( mDisabledBackgroundContent );

      mPaintState = SelectedState;
      break;
    }
  }

  StartTransitionAnimation();
}

bool Button::IsDisabled() const
{
  return mDisabled;
}

void Button::SetAutoRepeating( bool autoRepeating )
{
  mAutoRepeating = autoRepeating;

  // An autorepeating button can't be a togglable button.
  if( autoRepeating )
  {
    mTogglableButton = false;

    if( mSelected )
    {
      // Emit a signal is not wanted, only change the appearance.
      SetSelected( false, false );
    }
  }
}

bool Button::IsAutoRepeating() const
{
  return mAutoRepeating;
}

void Button::SetInitialAutoRepeatingDelay( float initialAutoRepeatingDelay )
{
  DALI_ASSERT_ALWAYS( initialAutoRepeatingDelay > 0.f );
  mInitialAutoRepeatingDelay = initialAutoRepeatingDelay;
}

float Button::GetInitialAutoRepeatingDelay() const
{
  return mInitialAutoRepeatingDelay;
}

void Button::SetNextAutoRepeatingDelay( float nextAutoRepeatingDelay )
{
  DALI_ASSERT_ALWAYS( nextAutoRepeatingDelay > 0.f );
  mNextAutoRepeatingDelay = nextAutoRepeatingDelay;
}

float Button::GetNextAutoRepeatingDelay() const
{
  return mNextAutoRepeatingDelay;
}

void Button::SetTogglableButton( bool togglable )
{
  mTogglableButton = togglable;

  // A togglable button can't be an autorepeating button.
  if( togglable )
  {
    mAutoRepeating = false;
  }
}

bool Button::IsTogglableButton() const
{
  return mTogglableButton;
}

void Button::SetSelected( bool selected )
{
  if( !mDisabled && mTogglableButton && ( selected != mSelected ) )
  {
    SetSelected( selected, true );
  }
}

void Button::SetSelected( bool selected, bool emitSignal )
{
  StopTransitionAnimation();

  mSelected = selected;

  // Notifies the derived class the button has been selected.
  OnSelected();

  switch( mPaintState )
  {
    case UnselectedState:
    {
      //Layer Order
      //(3) mSelectedContent (Inserted)
      //(4) mUnselectedContent
      //(2) mSelectedBackgroundContent (Inserted)
      //(1) mBackgroundContent

      AddButtonImage( mBackgroundContent );
      TransitionButtonImage( mSelectedBackgroundContent );
      AddButtonImage( mUnselectedContent );
      TransitionButtonImage( mSelectedContent );

      AddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      TransitionButtonImage( mDecoration[ SELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ UNSELECTED_DECORATION ] );
      TransitionOut( mUnselectedContent );
      TransitionOut( mDisabledContent );
      TransitionOut( mDisabledSelectedContent );
      TransitionOut( mDisabledBackgroundContent );

      mPaintState = SelectedState;
      break;
    }
    case SelectedState:
    {
      //Layer Order
      //(3) mUnselectedContent (Inserted)
      //(2) mSelectedContent
      //(1) mBackgroundContent

      AddButtonImage( mBackgroundContent );
      AddButtonImage( mSelectedContent );
      TransitionButtonImage( mUnselectedContent );

      AddButtonImage( mDecoration[ SELECTED_DECORATION ] );
      TransitionButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      ReAddLabel();

      TransitionOut( mDecoration[ SELECTED_DECORATION ] );
      TransitionOut( mSelectedContent );
      TransitionOut( mSelectedBackgroundContent );
      TransitionOut( mDisabledContent );
      TransitionOut( mDisabledSelectedContent );
      TransitionOut( mDisabledBackgroundContent );

      mPaintState = UnselectedState;
      break;
    }
    case DisabledUnselectedState:
    case DisabledSelectedState:
    {
      DALI_ASSERT_DEBUG( 0 && "Shouldn't be able to change paint state if the button is disabled." );
      break;
    }
  }

  StartTransitionAnimation();

  if( emitSignal )
  {
    Toolkit::Button handle( GetOwner() );

    // Emit signal.
    mStateChangedSignal.Emit( handle );
  }

  RelayoutRequest();
}

bool Button::IsSelected() const
{
  return mTogglableButton && mSelected;
}

void Button::SetAnimationTime( float animationTime )
{
  mAnimationTime = animationTime;
}

float Button::GetAnimationTime() const
{
  return mAnimationTime;
}

void Button::SetLabelText( const std::string& label )
{
  Property::Map labelProperty;
  labelProperty.Insert( "text", label );
  ModifyLabel( labelProperty );
}

std::string Button::GetLabelText() const
{
  Toolkit::TextLabel label = Dali::Toolkit::TextLabel::DownCast( mLabel );
  if( label )
  {
    return label.GetProperty<std::string>( Dali::Toolkit::TextLabel::Property::TEXT );
  }
  return std::string();
}

void Button::ModifyLabel( const Property::Map& properties )
{
  // If we don't have a label yet, create one.
  if( !mLabel )
  {
    // If we don't have a label, create one and set it up.
    // Note: The label text is set from the passed in property map after creation.
    mLabel = Toolkit::TextLabel::New();
    mLabel.SetPosition( 0.0f, 0.0f );
    // label should be the top of the button
    Self().Add( mLabel );
  }

  // Set any properties specified for the label by iterating through all property key-value pairs.
  for( unsigned int i = 0, mapCount = properties.Count(); i < mapCount; ++i )
  {
    const StringValuePair& propertyPair( properties.GetPair( i ) );

    // Convert the property string to a property index.
    Property::Index setPropertyIndex = mLabel.GetPropertyIndex( propertyPair.first );
    if( setPropertyIndex != Property::INVALID_INDEX )
    {
      // If the conversion worked, we have a valid property index,
      // Set the property to the new value.
      mLabel.SetProperty( setPropertyIndex, propertyPair.second );
    }
  }

  // Notify derived button classes of the change.
  OnLabelSet( false );

  RelayoutRequest();
}

Actor& Button::GetLabelActor()
{
  return mLabel;
}

void Button::SetDecoration( DecorationState state, Actor actor )
{
  if( mDecoration[ state ] && mDecoration[ state ].GetParent() )
  {
    mDecoration[ state ].Unparent();
  }

  mDecoration[ state ] = actor;
  mDecoration[ state ].SetColorMode( USE_OWN_COLOR );

  ResetImageLayers();
  RelayoutRequest();
}

Actor& Button::GetDecoration( DecorationState state )
{
  return mDecoration[ state ];
}

void Button::SetupContent( Actor& actorToModify, Actor newActor )
{
  if( newActor )
  {
    StopTransitionAnimation();

    if( actorToModify && actorToModify.GetParent() )
    {
      actorToModify.Unparent();
    }

    actorToModify = newActor;

    if( actorToModify )
    {
      actorToModify.SetAnchorPoint( AnchorPoint::TOP_LEFT );
      actorToModify.SetParentOrigin( ParentOrigin::TOP_LEFT );
      actorToModify.SetPosition( 0.f, 0.f );
    }

    ResetImageLayers();
  }
}

const Vector4 Button::GetUnselectedColor() const
{
  return mUnselectedColor;
}

void Button::SetColor( const Vector4& color, Button::PaintState selectedState )
{
  Actor* contentActor = NULL; // Using a pointer as SetupContent assigns the new Actor to this.
  bool imageFileExists = false;
  Property::Index visualIndex = Toolkit::Button::Property::SELECTED_STATE_IMAGE;

  if ( selectedState == SelectedState || selectedState == DisabledSelectedState )
  {
    mSelectedColor = color;
    contentActor = &mSelectedContent;
    imageFileExists = !GetSelectedImageFilename().empty();
  }
  else
  {
    mUnselectedColor = color;
    contentActor = &mUnselectedContent;
    imageFileExists = !GetUnselectedImageFilename().empty();
    visualIndex = Toolkit::Button::Property::UNSELECTED_STATE_IMAGE;
  }

  if ( contentActor )
  {
    if( imageFileExists )
    {
      // If there is existing unselected content, change the color on it directly.
      contentActor->SetColor( color );
    }
    else
    {
      // If there is no existing content, create a new actor to use for flat color.
      Actor placementActor = Actor::New();
      Toolkit::VisualFactory visualFactory = Toolkit::VisualFactory::Get();
      Toolkit::Visual::Base visual;

      Property::Map map;
      map[ Toolkit::Visual::Property::TYPE ] = Toolkit::Visual::COLOR;
      map[ Toolkit::ColorVisual::Property::MIX_COLOR ] = color;

      visual = visualFactory.CreateVisual( map );

      RegisterVisual( visualIndex, placementActor, visual );

      SetupContent( *contentActor, placementActor ); //
      contentActor->SetResizePolicy( ResizePolicy::FILL_TO_PARENT, Dimension::ALL_DIMENSIONS );
    }
  }
}

const Vector4 Button::GetSelectedColor() const
{
  return mSelectedColor;
}

void Button::SetUnselectedImage( const std::string& filename )
{
  Toolkit::ImageView newContent;
  if( !filename.empty() )
  {
    newContent = Toolkit::ImageView::New( filename );
  }
  else
  {
    newContent = Toolkit::ImageView::New();
  }

  if( newContent )
  {
    SetupContent( mUnselectedContent, newContent );

    mUnselectedContent.SetColor( mUnselectedColor );

    OnUnselectedImageSet();
    RelayoutRequest();
  }
}

Actor& Button::GetUnselectedImage()
{
  return mUnselectedContent;
}

void Button::SetSelectedImage( const std::string& filename )
{
  Toolkit::ImageView newContent;
  if( !filename.empty() )
  {
   newContent = Toolkit::ImageView::New( filename );
  }
  else
  {
    newContent = Toolkit::ImageView::New();
  }

  if( newContent )
  {
    SetupContent( mSelectedContent, newContent );

    mSelectedContent.SetColor( mSelectedColor );

    OnSelectedImageSet();
    RelayoutRequest();
  }
}

Actor& Button::GetSelectedImage()
{
  return mSelectedContent;
}

void Button::SetBackgroundImage( const std::string& filename )
{
  SetupContent( mBackgroundContent, Toolkit::ImageView::New( filename ) );

  OnBackgroundImageSet();
  RelayoutRequest();
}

Actor& Button::GetBackgroundImage()
{
  return mBackgroundContent;
}

void Button::SetSelectedBackgroundImage( const std::string& filename )
{
  SetupContent( mSelectedBackgroundContent, Toolkit::ImageView::New( filename ) );

  OnSelectedBackgroundImageSet();
  RelayoutRequest();
}

Actor& Button::GetSelectedBackgroundImage()
{
  return mSelectedBackgroundContent;
}

void Button::SetDisabledImage( const std::string& filename )
{
  SetupContent( mDisabledContent, Toolkit::ImageView::New( filename ) );

  OnDisabledImageSet();
  RelayoutRequest();
}

Actor& Button::GetDisabledImage()
{
  return mDisabledContent;
}

void Button::SetDisabledSelectedImage( const std::string& filename )
{
  SetupContent( mDisabledSelectedContent, Toolkit::ImageView::New( filename ) );

  OnDisabledSelectedImageSet();
  RelayoutRequest();
}

Actor& Button::GetDisabledSelectedImage()
{
  return mDisabledSelectedContent;
}

void Button::SetDisabledBackgroundImage( const std::string& filename )
{
  SetupContent( mDisabledBackgroundContent, Toolkit::ImageView::New( filename ) );

  OnDisabledBackgroundImageSet();
  RelayoutRequest();
}

Actor& Button::GetDisabledBackgroundImage()
{
  return mDisabledBackgroundContent;
}

std::string Button::GetUnselectedImageFilename() const
{
  if( mUnselectedContent )
  {
    ResourceImage image = ResourceImage::DownCast( mUnselectedContent );
    if( image )
    {
      return image.GetUrl();
    }
  }
  return std::string();
}

std::string Button::GetSelectedImageFilename() const
{
  if( mSelectedContent )
  {
    ResourceImage image = ResourceImage::DownCast( mSelectedContent );
    if( image )
    {
      return image.GetUrl();
    }
  }
  return std::string();
}

std::string Button::GetDisabledImageFilename() const
{
  if( mDisabledContent )
  {
    ResourceImage image = ResourceImage::DownCast( mDisabledContent );
    if( image )
    {
      return image.GetUrl();
    }
  }
  return std::string();
}

bool Button::DoAction( BaseObject* object, const std::string& actionName, const Property::Map& attributes )
{
  bool ret = false;

  Dali::BaseHandle handle( object );

  Toolkit::Button button = Toolkit::Button::DownCast( handle );

  DALI_ASSERT_ALWAYS( button );

  if( 0 == strcmp( actionName.c_str(), ACTION_BUTTON_CLICK ) )
  {
    ret = GetImplementation( button ).DoClickAction( attributes );
  }

  return ret;
}

bool Button::DoClickAction( const Property::Map& attributes )
{
  // Prevents the button signals from doing a recursive loop by sending an action
  // and re-emitting the signals.
  if( !mClickActionPerforming )
  {
    mClickActionPerforming = true;
    OnButtonDown();
    mState = ButtonDown;
    OnButtonUp();
    mClickActionPerforming = false;

    return true;
  }

  return false;
}

void Button::OnButtonDown()
{
  if( !mTogglableButton )
  {
    Pressed();

    if( mAutoRepeating )
    {
      SetUpTimer( mInitialAutoRepeatingDelay );
    }
  }

  // The pressed signal should be emitted regardless of toggle mode.
  Toolkit::Button handle( GetOwner() );
  mPressedSignal.Emit( handle );
}

void Button::OnButtonUp()
{
  if( ButtonDown == mState )
  {
    if( mTogglableButton )
    {
      SetSelected( !mSelected );
    }
    else
    {
      Released();

      if( mAutoRepeating )
      {
        mAutoRepeatingTimer.Reset();
      }
    }

    // The clicked and released signals should be emitted regardless of toggle mode.
    Toolkit::Button handle( GetOwner() );
    mReleasedSignal.Emit( handle );
    mClickedSignal.Emit( handle );
  }
}

void Button::OnTouchPointLeave()
{
  if( ButtonDown == mState )
  {
    if( !mTogglableButton )
    {
      Released();

      if( mAutoRepeating )
      {
        mAutoRepeatingTimer.Reset();
      }
    }

    // The released signal should be emitted regardless of toggle mode.
    Toolkit::Button handle( GetOwner() );
    mReleasedSignal.Emit( handle );
  }
}

void Button::OnTouchPointInterrupted()
{
  OnTouchPointLeave();
}

Toolkit::Button::ButtonSignalType& Button::PressedSignal()
{
  return mPressedSignal;
}

Toolkit::Button::ButtonSignalType& Button::ReleasedSignal()
{
  return mReleasedSignal;
}

Toolkit::Button::ButtonSignalType& Button::ClickedSignal()
{
  return mClickedSignal;
}

Toolkit::Button::ButtonSignalType& Button::StateChangedSignal()
{
  return mStateChangedSignal;
}

bool Button::DoConnectSignal( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor )
{
  Dali::BaseHandle handle( object );

  bool connected( true );
  Toolkit::Button button = Toolkit::Button::DownCast( handle );

  if( 0 == strcmp( signalName.c_str(), SIGNAL_PRESSED ) )
  {
    button.PressedSignal().Connect( tracker, functor );
  }
  else if( 0 == strcmp( signalName.c_str(), SIGNAL_RELEASED ) )
  {
    button.ReleasedSignal().Connect( tracker, functor );
  }
  else if( 0 == strcmp( signalName.c_str(), SIGNAL_CLICKED ) )
  {
    button.ClickedSignal().Connect( tracker, functor );
  }
  else if( 0 == strcmp( signalName.c_str(), SIGNAL_STATE_CHANGED ) )
  {
    button.StateChangedSignal().Connect( tracker, functor );
  }
  else
  {
    // signalName does not match any signal
    connected = false;
  }

  return connected;
}

void Button::OnInitialize()
{
  Actor self = Self();

  mTapDetector = TapGestureDetector::New();
  mTapDetector.Attach( self );
  mTapDetector.DetectedSignal().Connect(this, &Button::OnTap);

  self.SetKeyboardFocusable( true );

  self.TouchSignal().Connect( this, &Button::OnTouch );
}

bool Button::OnAccessibilityActivated()
{
  return OnKeyboardEnter();
}

bool Button::OnKeyboardEnter()
{
  // When the enter key is pressed, or button is activated, the click action is performed.
  Property::Map attributes;
  bool ret = DoClickAction( attributes );

  return ret;
}

void Button::OnStageDisconnection()
{
  if( ButtonDown == mState )
  {
    if( !mTogglableButton )
    {
      Released();

      if( mAutoRepeating )
      {
        mAutoRepeatingTimer.Reset();
      }
    }
  }

  mState = ButtonUp;

  Control::OnStageDisconnection();
}

bool Button::OnTouch( Actor actor, const TouchData& touch )
{
  // Only events are processed when the button is not disabled and the touch event has only
  // one touch point.
  if( ( !mDisabled ) && ( 1 == touch.GetPointCount() ) )
  {
    switch( touch.GetState( 0 ) )
    {
      case PointState::DOWN:
      {
        OnButtonDown(); // Notification for derived classes.

        // Sets the button state to ButtonDown.
        mState = ButtonDown;
        break;
      }
      case PointState::UP:
      {
        OnButtonUp(); // Notification for derived classes.

        // Sets the button state to ButtonUp.
        mState = ButtonUp;
        break;
      }
      case PointState::INTERRUPTED:
      {
        OnTouchPointInterrupted(); // Notification for derived classes.

        // Sets the button state to the default (ButtonUp).
        mState = ButtonUp;
        break;
      }
      case PointState::LEAVE:
      {
        OnTouchPointLeave(); // Notification for derived classes.

        // Sets the button state to the default (ButtonUp).
        mState = ButtonUp;
        break;
      }
      case PointState::MOTION:
      case PointState::STATIONARY: // FALLTHROUGH
      {
        // Nothing to do
        break;
      }
    }
  }
  else if( 1 < touch.GetPointCount() )
  {
    OnTouchPointLeave(); // Notification for derived classes.

    // Sets the button state to the default (ButtonUp).
    mState = ButtonUp;
  }

  return false;
}

void Button::OnTap(Actor actor, const TapGesture& tap)
{
  // Do nothing.
}

void Button::SetUpTimer( float delay )
{
  mAutoRepeatingTimer = Dali::Timer::New( static_cast<unsigned int>( 1000.f * delay ) );
  mAutoRepeatingTimer.TickSignal().Connect( this, &Button::AutoRepeatingSlot );
  mAutoRepeatingTimer.Start();
}

bool Button::AutoRepeatingSlot()
{
  bool consumed = false;
  if( !mDisabled )
  {
    // Restart the autorepeat timer.
    SetUpTimer( mNextAutoRepeatingDelay );

    Pressed();

    Toolkit::Button handle( GetOwner() );

    //Emit signal.
    consumed = mReleasedSignal.Emit( handle );
    consumed |= mClickedSignal.Emit( handle );
    consumed |= mPressedSignal.Emit( handle );
 }

  return consumed;
}

void Button::Pressed()
{
  if( mPaintState == UnselectedState )
  {
    StopTransitionAnimation();

    // Notifies the derived class the button has been pressed.
    OnPressed();

    //Layer Order
    //(4) mSelectedContent (Inserted)
    //(3) mUnselectedContent
    //(2) mSelectedBackgroundContent (Inserted)
    //(1) mBackgroundContent

    AddButtonImage( mBackgroundContent );
    TransitionButtonImage( mSelectedBackgroundContent );
    AddButtonImage( mUnselectedContent );
    TransitionButtonImage( mSelectedContent );

    AddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
    TransitionButtonImage( mDecoration[ SELECTED_DECORATION ] );
    ReAddLabel();

    TransitionOut( mDecoration[ UNSELECTED_DECORATION ] );
    TransitionOut( mUnselectedContent );
    TransitionOut( mDisabledContent );
    TransitionOut( mDisabledSelectedContent );
    TransitionOut( mDisabledBackgroundContent );

    mPaintState = SelectedState;

    StartTransitionAnimation();
  }
}

void Button::Released()
{
  if( mPaintState == SelectedState )
  {
    StopTransitionAnimation();

    // Notifies the derived class the button has been released.
    OnReleased();

    //Layer Order
    //(3) mUnselectedContent (Inserted)
    //(2) mSelectedContent
    //(1) mBackgroundContent

    AddButtonImage( mBackgroundContent );
    AddButtonImage( mSelectedContent );
    TransitionButtonImage( mUnselectedContent );

    AddButtonImage( mDecoration[ SELECTED_DECORATION ] );
    TransitionButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
    ReAddLabel();

    TransitionOut( mDecoration[ SELECTED_DECORATION ] );
    TransitionOut( mSelectedContent );
    TransitionOut( mSelectedBackgroundContent );
    TransitionOut( mDisabledContent );
    TransitionOut( mDisabledSelectedContent );
    TransitionOut( mDisabledBackgroundContent );

    mPaintState = UnselectedState;

    StartTransitionAnimation();
  }
}

Button::ButtonState Button::GetState()
{
  return mState;
}

Button::PaintState Button::GetPaintState()
{
  return mPaintState;
}

void Button::PrepareAddButtonImage( Actor& actor )
{
  if( actor )
  {
    Self().Add( actor );
    PrepareForTranstionOut( actor );
  }
}

void Button::TransitionButtonImage( Actor& actor )
{
  if( actor )
  {
    if( !actor.GetParent() )
    {
      Self().Add( actor );
    }

    OnTransitionIn( actor );
  }
}

void Button::AddButtonImage( Actor& actor )
{
  if( actor )
  {
    Self().Add( actor );
  }
}

void Button::ReAddLabel()
{
  if( mLabel )
  {
    mLabel.Unparent();
    Self().Add( mLabel );
  }
}

void Button::RemoveButtonImage( Actor& actor )
{
  if( actor )
  {
    if( actor.GetParent() )
    {
      Self().Remove( actor );
    }
    PrepareForTranstionIn( actor );
  }
}

unsigned int Button::FindChildIndex( Actor& actor )
{
  Actor self = Self();
  unsigned int childrenNum = self.GetChildCount();

  for( unsigned int i = 0; i < childrenNum; i++ )
  {
    Actor child = self.GetChildAt( i );
    if( child == actor )
    {
      return i;
    }
  }

  return childrenNum;
}

void Button::TransitionOut( Actor actor )
{
  OnTransitionOut( actor );
}

void Button::ResetImageLayers()
{
  // Ensure that all layers are in the correct order and state according to the paint state

  switch( mPaintState )
  {
    case UnselectedState:
    {
      //Layer Order
      //(2) mUnselectedContent
      //(1) mBackgroundContent

      RemoveButtonImage( mDecoration[ SELECTED_DECORATION ] );
      RemoveButtonImage( mSelectedContent );
      RemoveButtonImage( mSelectedBackgroundContent );
      RemoveButtonImage( mDisabledContent );
      RemoveButtonImage( mDisabledSelectedContent );
      RemoveButtonImage( mDisabledBackgroundContent );

      PrepareAddButtonImage( mBackgroundContent );
      PrepareAddButtonImage( mUnselectedContent );

      PrepareAddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      ReAddLabel();
      break;
    }
    case SelectedState:
    {
      //Layer Order
      //(3) mSelectedContent
      //(2) mSelectedBackgroundContent
      //(1) mBackgroundContent

      RemoveButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      RemoveButtonImage( mUnselectedContent );
      RemoveButtonImage( mDisabledContent );
      RemoveButtonImage( mDisabledSelectedContent );
      RemoveButtonImage( mDisabledBackgroundContent );

      PrepareAddButtonImage( mBackgroundContent );
      PrepareAddButtonImage( mSelectedBackgroundContent );
      PrepareAddButtonImage( mSelectedContent );

      PrepareAddButtonImage( mDecoration[ SELECTED_DECORATION ] );
      ReAddLabel();
      break;
    }
    case DisabledUnselectedState:
    {
      //Layer Order
      //(2) mDisabledContent
      //(1) mDisabledBackgroundContent

      RemoveButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      RemoveButtonImage( mUnselectedContent );
      RemoveButtonImage( mBackgroundContent );
      RemoveButtonImage( mDecoration[ SELECTED_DECORATION ] );
      RemoveButtonImage( mSelectedContent );
      RemoveButtonImage( mDisabledSelectedContent );
      RemoveButtonImage( mSelectedBackgroundContent );

      PrepareAddButtonImage( mDisabledBackgroundContent ? mDisabledBackgroundContent : mBackgroundContent );
      PrepareAddButtonImage( mDisabledContent ? mDisabledContent : mUnselectedContent );

      PrepareAddButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      ReAddLabel();
      break;
    }
    case DisabledSelectedState:
    {
      //Layer Order
      // (2) mDisabledSelectedContent
      // (1) mDisabledBackgroundContent

      RemoveButtonImage( mDecoration[ UNSELECTED_DECORATION ] );
      RemoveButtonImage( mUnselectedContent );
      RemoveButtonImage( mDecoration[ SELECTED_DECORATION ] );
      RemoveButtonImage( mSelectedContent );
      RemoveButtonImage( mBackgroundContent );
      RemoveButtonImage( mSelectedBackgroundContent );
      RemoveButtonImage( mDisabledContent );

      if( mDisabledBackgroundContent )
      {
        PrepareAddButtonImage( mDisabledBackgroundContent );
      }
      else
      {
        PrepareAddButtonImage( mBackgroundContent );
        PrepareAddButtonImage( mSelectedBackgroundContent );
      }

      PrepareAddButtonImage( mDisabledSelectedContent ? mDisabledSelectedContent : mSelectedContent );

      PrepareAddButtonImage( mDecoration[ SELECTED_DECORATION ] );
      ReAddLabel();
      break;
    }
  }
}

void Button::StartTransitionAnimation()
{
  if( mTransitionAnimation )
  {
    mTransitionAnimation.Play();
  }
  else
  {
    ResetImageLayers();
  }
}

void Button::StopTransitionAnimation()
{
  if( mTransitionAnimation )
  {
    mTransitionAnimation.Clear();
    mTransitionAnimation.Reset();
  }
}

Dali::Animation Button::GetTransitionAnimation()
{
  if( !mTransitionAnimation )
  {
    mTransitionAnimation = Dali::Animation::New( GetAnimationTime() );
    mTransitionAnimation.FinishedSignal().Connect( this, &Button::TransitionAnimationFinished );
  }

  return mTransitionAnimation;
}

void Button::TransitionAnimationFinished( Dali::Animation& source )
{
  StopTransitionAnimation();
  ResetImageLayers();
}

void Button::SetProperty( BaseObject* object, Property::Index index, const Property::Value& value )
{
  Toolkit::Button button = Toolkit::Button::DownCast( Dali::BaseHandle( object ) );

  if ( button )
  {
    switch ( index )
    {
      case Toolkit::Button::Property::DISABLED:
      {
        GetImplementation( button ).SetDisabled( value.Get< bool >() );
        break;
      }

      case Toolkit::Button::Property::AUTO_REPEATING:
      {
        GetImplementation( button ).SetAutoRepeating( value.Get< bool >() );
        break;
      }

      case Toolkit::Button::Property::INITIAL_AUTO_REPEATING_DELAY:
      {
        GetImplementation( button ).SetInitialAutoRepeatingDelay( value.Get< float >() );
        break;
      }

      case Toolkit::Button::Property::NEXT_AUTO_REPEATING_DELAY:
      {
        GetImplementation( button ).SetNextAutoRepeatingDelay( value.Get< float >() );
        break;
      }

      case Toolkit::Button::Property::TOGGLABLE:
      {
        GetImplementation( button ).SetTogglableButton( value.Get< bool >() );
        break;
      }

      case Toolkit::Button::Property::SELECTED:
      {
        GetImplementation( button ).SetSelected( value.Get< bool >() );
        break;
      }

      case Toolkit::Button::Property::UNSELECTED_STATE_IMAGE:
      {
        GetImplementation( button ).SetUnselectedImage( value.Get< std::string >() );
        break;
      }

      case Toolkit::Button::Property::SELECTED_STATE_IMAGE:
      {
        GetImplementation( button ).SetSelectedImage( value.Get< std::string >() );
        break;
      }

      case Toolkit::Button::Property::DISABLED_STATE_IMAGE:
      {
        GetImplementation( button ).SetDisabledImage( value.Get< std::string >() );
        break;
      }

      case Toolkit::Button::Property::UNSELECTED_COLOR:
      {
        GetImplementation( button ).SetColor( value.Get< Vector4 >(), UnselectedState );
        break;
      }

      case Toolkit::Button::Property::SELECTED_COLOR:
      {
        GetImplementation( button ).SetColor( value.Get< Vector4 >(), SelectedState );
        break;
      }

      case Toolkit::Button::Property::LABEL_TEXT:
      {
        GetImplementation( button ).SetLabelText( value.Get< std::string >() );
        break;
      }

      case Toolkit::Button::Property::LABEL:
      {
        // Get a Property::Map from the property if possible.
        Property::Map setPropertyMap;
        if( value.Get( setPropertyMap ) )
        {
          GetImplementation( button ).ModifyLabel( setPropertyMap );
        }
      }
      break;
    }
  }
}

Property::Value Button::GetProperty( BaseObject* object, Property::Index propertyIndex )
{
  Property::Value value;

  Toolkit::Button button = Toolkit::Button::DownCast( Dali::BaseHandle( object ) );

  if ( button )
  {
    switch ( propertyIndex )
    {
      case Toolkit::Button::Property::DISABLED:
      {
        value = GetImplementation( button ).mDisabled;
        break;
      }

      case Toolkit::Button::Property::AUTO_REPEATING:
      {
        value = GetImplementation( button ).mAutoRepeating;
        break;
      }

      case Toolkit::Button::Property::INITIAL_AUTO_REPEATING_DELAY:
      {
        value = GetImplementation( button ).mInitialAutoRepeatingDelay;
        break;
      }

      case Toolkit::Button::Property::NEXT_AUTO_REPEATING_DELAY:
      {
        value = GetImplementation( button ).mNextAutoRepeatingDelay;
        break;
      }

      case Toolkit::Button::Property::TOGGLABLE:
      {
        value = GetImplementation( button ).mTogglableButton;
        break;
      }

      case Toolkit::Button::Property::SELECTED:
      {
        value = GetImplementation( button ).mSelected;
        break;
      }

      case Toolkit::Button::Property::UNSELECTED_STATE_IMAGE:
      {
        value = GetImplementation( button ).GetUnselectedImageFilename();
        break;
      }

      case Toolkit::Button::Property::SELECTED_STATE_IMAGE:
      {
        value = GetImplementation( button ).GetSelectedImageFilename();
        break;
      }

      case Toolkit::Button::Property::DISABLED_STATE_IMAGE:
      {
        value = GetImplementation( button ).GetDisabledImageFilename();
        break;
      }

      case Toolkit::Button::Property::UNSELECTED_COLOR:
      {
        value = GetImplementation( button ).GetUnselectedColor();
        break;
      }

      case Toolkit::Button::Property::SELECTED_COLOR:
      {
        value = GetImplementation( button ).GetSelectedColor();
        break;
      }

      case Toolkit::Button::Property::LABEL_TEXT:
      {
        value = GetImplementation( button ).GetLabelText();
        break;
      }

      case Toolkit::Button::Property::LABEL:
      {
        Property::Map emptyMap;
        value = emptyMap;
        break;
      }
    }
  }

  return value;
}

// Deprecated API

void Button::SetLabel( Actor label )
{
  if( mLabel != label )
  {
    if( mLabel && mLabel.GetParent() )
    {
      mLabel.GetParent().Remove( mLabel );
    }

    mLabel = label;
    mLabel.SetPosition( 0.0f, 0.0f );

    // label should be the top of the button
    Self().Add( mLabel );

    ResetImageLayers();
    OnLabelSet( true );

    RelayoutRequest();
  }
}

void Button::SetButtonImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mUnselectedContent, image );

    OnUnselectedImageSet();
    RelayoutRequest();
  }
}

void Button::SetSelectedImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mSelectedContent, image );

    OnSelectedImageSet();
    RelayoutRequest();
  }
}

void Button::SetBackgroundImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mBackgroundContent, image );

    OnBackgroundImageSet();
    RelayoutRequest();
  }
}

void Button::SetSelectedBackgroundImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mSelectedBackgroundContent, image );

    OnSelectedBackgroundImageSet();
    RelayoutRequest();
  }
}

void Button::SetDisabledImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mDisabledContent, image );

    OnDisabledImageSet();
    RelayoutRequest();
  }
}

void Button::SetDisabledSelectedImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mDisabledSelectedContent, image );

    OnDisabledSelectedImageSet();
    RelayoutRequest();
  }
}

void Button::SetDisabledBackgroundImage( Actor image )
{
  if( image )
  {
    StopTransitionAnimation();

    SetupContent( mDisabledBackgroundContent, image );

    OnDisabledBackgroundImageSet();
    RelayoutRequest();
  }
}

Actor Button::GetButtonImage() const
{
  return mUnselectedContent;
}

Actor Button::GetSelectedImage() const
{
  return mSelectedContent;
}


} // namespace Internal

} // namespace Toolkit

} // namespace Dali
