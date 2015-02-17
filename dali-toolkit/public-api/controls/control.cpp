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

#include <dali-toolkit/public-api/controls/control.h>
#include <dali-toolkit/public-api/controls/control-impl.h>

namespace Dali
{

namespace Toolkit
{

const char* const Control::ACTION_CONTROL_ACTIVATED = "control-activated";

const char* const Control::SIGNAL_KEY_EVENT = "key-event";
const char* const Control::SIGNAL_TAPPED = "tapped";
const char* const Control::SIGNAL_PANNED = "panned";
const char* const Control::SIGNAL_PINCHED = "pinched";
const char* const Control::SIGNAL_LONG_PRESSED = "long-pressed";

Control Control::New()
{
  return Internal::Control::New();
}

Control::Control()
{
}

Control::Control(const Control& uiControl)
: CustomActor( uiControl ? static_cast< const Internal::Control& >( uiControl.GetImplementation() ).GetOwner() : NULL)
{
}

Control::~Control()
{
}

Control& Control::operator=( const Control& handle )
{
  if( &handle != this )
  {
    CustomActor::operator=( handle );
  }
  return *this;
}

Control Control::DownCast( BaseHandle handle )
{
  return DownCast< Control, Internal::Control >(handle);
}

Internal::Control& Control::GetImplementation()
{
  return static_cast<Internal::Control&>(CustomActor::GetImplementation());
}

const Internal::Control& Control::GetImplementation() const
{
  return static_cast<const Internal::Control&>(CustomActor::GetImplementation());
}

void Control::SetSizePolicy( SizePolicy widthPolicy, SizePolicy heightPolicy )
{
  GetImplementation().SetSizePolicy( widthPolicy, heightPolicy );
}

void Control::GetSizePolicy( SizePolicy& widthPolicy, SizePolicy& heightPolicy ) const
{
  GetImplementation().GetSizePolicy( widthPolicy, heightPolicy );
}

void Control::SetMinimumSize( const Vector3& size )
{
  GetImplementation().SetMinimumSize( size );
}

const Vector3& Control::GetMinimumSize() const
{
  return GetImplementation().GetMinimumSize();
}

void Control::SetMaximumSize( const Vector3& size )
{
  GetImplementation().SetMaximumSize( size );
}

const Vector3& Control::GetMaximumSize() const
{
  return GetImplementation().GetMaximumSize();
}

Vector3 Control::GetNaturalSize()
{
  return GetImplementation().GetNaturalSize();
}

float Control::GetHeightForWidth( float width )
{
  return GetImplementation().GetHeightForWidth( width );
}

float Control::GetWidthForHeight( float height )
{
  return GetImplementation().GetWidthForHeight( height );
}

void Control::SetKeyInputFocus()
{
  GetImplementation().SetKeyInputFocus();
}

bool Control::HasKeyInputFocus()
{
  return GetImplementation().HasKeyInputFocus();
}

void Control::ClearKeyInputFocus()
{
  GetImplementation().ClearKeyInputFocus();
}

PinchGestureDetector Control::GetPinchGestureDetector() const
{
  return GetImplementation().GetPinchGestureDetector();
}

PanGestureDetector Control::GetPanGestureDetector() const
{
  return GetImplementation().GetPanGestureDetector();
}

TapGestureDetector Control::GetTapGestureDetector() const
{
  return GetImplementation().GetTapGestureDetector();
}

LongPressGestureDetector Control::GetLongPressGestureDetector() const
{
  return GetImplementation().GetLongPressGestureDetector();
}

void Control::SetBackgroundColor( const Vector4& color )
{
  GetImplementation().SetBackgroundColor( color );
}

Vector4 Control::GetBackgroundColor() const
{
  return GetImplementation().GetBackgroundColor();
}

void Control::SetBackground( Image image )
{
  GetImplementation().SetBackground( image );
}

void Control::ClearBackground()
{
  GetImplementation().ClearBackground();
}

Actor Control::GetBackgroundActor() const
{
  return GetImplementation().GetBackgroundActor();
}

Control::KeyEventSignalType& Control::KeyEventSignal()
{
  return GetImplementation().KeyEventSignal();
}

Control::Control(Internal::Control& implementation)
: CustomActor(implementation)
{
}

Control::Control(Dali::Internal::CustomActor* internal)
: CustomActor(internal)
{
  VerifyCustomActorPointer<Internal::Control>(internal);
}

} // namespace Toolkit

} // namespace Dali
