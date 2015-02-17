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

#include <dali-toolkit/public-api/controls/scroll-bar/scroll-bar.h>
#include <dali-toolkit/internal/controls/scroll-bar/scroll-bar-impl.h>

namespace Dali
{

namespace Toolkit
{

const char* const ScrollBar::SCROLL_POSITION_NOTIFIED_SIGNAL_NAME = "scroll-position-notified";

ScrollBar::ScrollBar()
{
}

ScrollBar::ScrollBar(Internal::ScrollBar& implementation)
: ScrollComponent( implementation )
{
}

ScrollBar::ScrollBar( Dali::Internal::CustomActor* internal )
: ScrollComponent( internal )
{
  VerifyCustomActorPointer<Internal::ScrollBar>(internal);
}

ScrollBar::ScrollBar( const ScrollBar& scrollBar )
: ScrollComponent( scrollBar )
{
}

ScrollBar& ScrollBar::operator=( const ScrollBar& scrollBar )
{
  if( &scrollBar != this )
  {
    Control::operator=( scrollBar );
  }
  return *this;
}

ScrollBar ScrollBar::New()
{
  return Internal::ScrollBar::New();
}

ScrollBar ScrollBar::DownCast( BaseHandle handle )
{
  return Control::DownCast<ScrollBar, Internal::ScrollBar>(handle);
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::SetIndicatorImage( Image image )
{
  GetImpl(*this).SetIndicatorImage(image);
}

Actor ScrollBar::GetScrollIndicator()
{
  return GetImpl(*this).GetScrollIndicator();
}

void ScrollBar::SetPositionNotifications( const std::vector<float>& positions )
{
  GetImpl(*this).SetPositionNotifications(positions);
}

void ScrollBar::SetIndicatorHeightPolicy( ScrollBar::IndicatorHeightPolicy policy )
{
  GetImpl(*this).SetIndicatorHeightPolicy(policy);
}

ScrollBar::IndicatorHeightPolicy ScrollBar::GetIndicatorHeightPolicy()
{
  return GetImpl(*this).GetIndicatorHeightPolicy();
}

void ScrollBar::SetIndicatorFixedHeight( float height )
{
  GetImpl(*this).SetIndicatorFixedHeight(height);
}

float ScrollBar::GetIndicatorFixedHeight()
{
  return GetImpl(*this).GetIndicatorFixedHeight();
}

void ScrollBar::SetIndicatorShowDuration( float durationSeconds )
{
  GetImpl(*this).SetIndicatorShowDuration(durationSeconds);
}

float ScrollBar::GetIndicatorShowDuration()
{
  return GetImpl(*this).GetIndicatorShowDuration();
}

void ScrollBar::SetIndicatorHideDuration( float durationSeconds )
{
  GetImpl(*this).SetIndicatorHideDuration(durationSeconds);
}

float ScrollBar::GetIndicatorHideDuration()
{
  return GetImpl(*this).GetIndicatorHideDuration();
}

void ScrollBar::Show()
{
  GetImpl(*this).Show();
}

void ScrollBar::Hide()
{
  GetImpl(*this).Hide();
}

ScrollBar::ScrollPositionNotifiedSignalType& ScrollBar::ScrollPositionNotifiedSignal()
{
  return GetImpl(*this).ScrollPositionNotifiedSignal();
}

} // namespace Toolkit

} // namespace Dali
