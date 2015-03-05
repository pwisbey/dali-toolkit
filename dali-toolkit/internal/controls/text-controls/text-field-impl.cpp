/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <dali-toolkit/internal/controls/text-controls/text-field-impl.h>

// EXTERNAL INCLUDES
#include <dali/public-api/images/resource-image.h>
#include <dali/public-api/object/type-registry.h>
#include <dali/public-api/common/stage.h>
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES
#include <dali-toolkit/internal/text/layouts/layout-engine.h>
#include <dali-toolkit/internal/text/rendering/text-backend.h>

using namespace Dali::Toolkit::Text;

namespace
{

const unsigned int DEFAULT_RENDERING_BACKEND = 0;

} // namespace


namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace
{

// Type registration
BaseHandle Create()
{
  return Toolkit::TextField::New();
}

TypeRegistration mType( typeid(Toolkit::TextField), typeid(Toolkit::Control), Create );

// Setup properties, signals and actions using the type-registry.
DALI_TYPE_REGISTRATION_BEGIN( Toolkit::TextField, Toolkit::Control, Create );

DALI_PROPERTY_REGISTRATION( TextField, "rendering-backend",       INT,       RENDERING_BACKEND       )
DALI_PROPERTY_REGISTRATION( TextField, "placeholder-text",        STRING,    PLACEHOLDER_TEXT        )
DALI_PROPERTY_REGISTRATION( TextField, "text",                    STRING,    TEXT                    )
DALI_PROPERTY_REGISTRATION( TextField, "font-family",             STRING,    FONT_FAMILY             )
DALI_PROPERTY_REGISTRATION( TextField, "font-style",              STRING,    FONT_STYLE              )
DALI_PROPERTY_REGISTRATION( TextField, "point-size",              FLOAT,     POINT_SIZE              )
DALI_PROPERTY_REGISTRATION( TextField, "cursor-image",            STRING,    CURSOR_IMAGE            )
DALI_PROPERTY_REGISTRATION( TextField, "primary-cursor-color",    VECTOR4,   PRIMARY_CURSOR_COLOR    )
DALI_PROPERTY_REGISTRATION( TextField, "secondary-cursor-color",  VECTOR4,   SECONDARY_CURSOR_COLOR  )
DALI_PROPERTY_REGISTRATION( TextField, "enable-cursor-blink",     BOOLEAN,   ENABLE_CURSOR_BLINK     )
DALI_PROPERTY_REGISTRATION( TextField, "cursor-blink-interval",   FLOAT,     CURSOR_BLINK_INTERVAL   )
DALI_PROPERTY_REGISTRATION( TextField, "cursor-blink-duration",   FLOAT,     CURSOR_BLINK_DURATION   )
DALI_PROPERTY_REGISTRATION( TextField, "grab-handle-image",       STRING,    GRAB_HANDLE_IMAGE       )
DALI_PROPERTY_REGISTRATION( TextField, "decoration bounding-box", RECTANGLE, DECORATION_BOUNDING_BOX )

DALI_TYPE_REGISTRATION_END()

} // namespace

Toolkit::TextField TextField::New()
{
  // Create the implementation, temporarily owned by this handle on stack
  IntrusivePtr< TextField > impl = new TextField();

  // Pass ownership to CustomActor handle
  Toolkit::TextField handle( *impl );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  impl->Initialize();

  return handle;
}

void TextField::SetProperty( BaseObject* object, Property::Index index, const Property::Value& value )
{
  Toolkit::TextField textField = Toolkit::TextField::DownCast( Dali::BaseHandle( object ) );

  if( textField )
  {
    TextField& impl( GetImpl( textField ) );

    switch( index )
    {
      case Toolkit::TextField::PROPERTY_RENDERING_BACKEND:
      {
        unsigned int backend = value.Get< unsigned int >();

        if( impl.mRenderingBackend != backend )
        {
          impl.mRenderingBackend = backend;
          impl.mRenderer.Reset();
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_PLACEHOLDER_TEXT:
      {
        if( impl.mController )
        {
          //impl.mController->SetPlaceholderText( value.Get< std::string >() ); TODO
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_TEXT:
      {
        if( impl.mController )
        {
          impl.mController->SetText( value.Get< std::string >() );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_IMAGE:
      {
        ResourceImage image = ResourceImage::New( value.Get< std::string >() );

        if( impl.mDecorator )
        {
          impl.mDecorator->SetCursorImage( image );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_PRIMARY_CURSOR_COLOR:
      {
        if( impl.mDecorator )
        {
          impl.mDecorator->SetColor( PRIMARY_CURSOR, value.Get< Vector4 >() );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_SECONDARY_CURSOR_COLOR:
      {
        if( impl.mDecorator )
        {
          impl.mDecorator->SetColor( SECONDARY_CURSOR, value.Get< Vector4 >() );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_ENABLE_CURSOR_BLINK:
      {
        if( impl.mController )
        {
          //impl.mController->SetEnableCursorBlink( value.Get< bool >() ); TODO
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_BLINK_INTERVAL:
      {
        if( impl.mDecorator )
        {
          impl.mDecorator->SetCursorBlinkInterval( value.Get< float >() );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_BLINK_DURATION:
      {
        if( impl.mDecorator )
        {
          impl.mDecorator->SetCursorBlinkDuration( value.Get< float >() );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_GRAB_HANDLE_IMAGE:
      {
        ResourceImage image = ResourceImage::New( value.Get< std::string >() );

        if( impl.mDecorator )
        {
          impl.mDecorator->SetGrabHandleImage( image );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_DECORATION_BOUNDING_BOX:
      {
        if( impl.mDecorator )
        {
          impl.mDecorator->SetBoundingBox( value.Get< Rect<int> >() );
        }
        break;
      }
    }
  }
}

Property::Value TextField::GetProperty( BaseObject* object, Property::Index index )
{
  Property::Value value;

  Toolkit::TextField textField = Toolkit::TextField::DownCast( Dali::BaseHandle( object ) );

  if( textField )
  {
    TextField& impl( GetImpl( textField ) );

    switch( index )
    {
      case Toolkit::TextField::PROPERTY_RENDERING_BACKEND:
      {
        value = impl.mRenderingBackend;
        break;
      }
      case Toolkit::TextField::PROPERTY_PLACEHOLDER_TEXT:
      {
        DALI_LOG_WARNING( "UTF-8 text representation was discarded\n" );
        break;
      }
      case Toolkit::TextField::PROPERTY_TEXT:
      {
        DALI_LOG_WARNING( "UTF-8 text representation was discarded\n" );
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_IMAGE:
      {
        if( impl.mDecorator )
        {
          ResourceImage image = ResourceImage::DownCast( impl.mDecorator->GetCursorImage() );
          if( image )
          {
            value = image.GetUrl();
          }
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_PRIMARY_CURSOR_COLOR:
      {
        if( impl.mDecorator )
        {
          value = impl.mDecorator->GetColor( PRIMARY_CURSOR );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_SECONDARY_CURSOR_COLOR:
      {
        if( impl.mDecorator )
        {
          value = impl.mDecorator->GetColor( SECONDARY_CURSOR );
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_ENABLE_CURSOR_BLINK:
      {
        //value = impl.mController->GetEnableCursorBlink(); TODO
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_BLINK_INTERVAL:
      {
        if( impl.mDecorator )
        {
          value = impl.mDecorator->GetCursorBlinkInterval();
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_CURSOR_BLINK_DURATION:
      {
        if( impl.mDecorator )
        {
          value = impl.mDecorator->GetCursorBlinkDuration();
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_GRAB_HANDLE_IMAGE:
      {
        if( impl.mDecorator )
        {
          ResourceImage image = ResourceImage::DownCast( impl.mDecorator->GetCursorImage() );
          if( image )
          {
            value = image.GetUrl();
          }
        }
        break;
      }
      case Toolkit::TextField::PROPERTY_DECORATION_BOUNDING_BOX:
      {
        if( impl.mDecorator )
        {
          value = impl.mDecorator->GetBoundingBox();
        }
        break;
      }
    }
  }

  return value;
}

void TextField::OnInitialize()
{
  mController = Text::Controller::New( *this );

  mDecorator = Text::Decorator::New( *this, *mController );

  mController->GetLayoutEngine().SetLayout( LayoutEngine::SINGLE_LINE_BOX );

  mController->EnableTextInput( mDecorator );

  // Forward input events to controller
  mDoubleTapDetector = TapGestureDetector::New();
  mDoubleTapDetector.SetMaximumTapsRequired( 2 );
  mDoubleTapDetector.DetectedSignal().Connect( this, &TextField::OnTap );
  mDoubleTapDetector.Attach(Self());

  // Set BoundingBox to stage size if not already set.
  if ( mDecorator->GetBoundingBox().IsEmpty() )
  {
    Vector2 stageSize = Dali::Stage::GetCurrent().GetSize();
    mDecorator->SetBoundingBox( Rect<int>( 0.0f, 0.0f, stageSize.width, stageSize.height ) );
  }
}

Vector3 TextField::GetNaturalSize()
{
  return mController->GetNaturalSize();
}

float TextField::GetHeightForWidth( float width )
{
  return mController->GetHeightForWidth( width );
}

void TextField::OnRelayout( const Vector2& size, ActorSizeContainer& container )
{
  if( mController->Relayout( size ) )
  {
    if( mDecorator )
    {
      mDecorator->Relayout( size );
    }

    if( !mRenderer )
    {
      mRenderer = Backend::Get().NewRenderer( mRenderingBackend );
    }

    if( mRenderer )
    {
      Actor renderableActor = mRenderer->Render( mController->GetView() );

      if( renderableActor )
      {
        Self().Add( renderableActor );
      }
    }
  }
}

void TextField::OnTap( Actor actor, const TapGesture& gesture )
{
  mController->TapEvent( gesture.numberOfTaps, gesture.localPoint.x, gesture.localPoint.y );
}

void TextField::RequestTextRelayout()
{
  RelayoutRequest();
}

TextField::TextField()
: Control( ControlBehaviour( CONTROL_BEHAVIOUR_NONE ) ),
  mRenderingBackend( DEFAULT_RENDERING_BACKEND )
{
}

TextField::~TextField()
{
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
