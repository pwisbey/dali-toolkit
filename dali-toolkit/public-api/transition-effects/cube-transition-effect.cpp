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
#include "cube-transition-effect.h"

//INTERNAL INCLUDES
#include <dali-toolkit/internal/transition-effects/cube-transition-effect-impl.h>

namespace Dali
{

namespace Toolkit
{

CubeTransitionEffect::CubeTransitionEffect()
{
}

CubeTransitionEffect::~CubeTransitionEffect()
{
}

CubeTransitionEffect::CubeTransitionEffect(Internal::CubeTransitionEffect* impl)
: BaseHandle(impl)
{
}

CubeTransitionEffect CubeTransitionEffect::DownCast( BaseHandle handle )
{
  return CubeTransitionEffect( dynamic_cast< Dali::Toolkit::Internal::CubeTransitionEffect* >( handle.GetObjectPtr() ) );
}

void CubeTransitionEffect::SetTransitionDuration( float duration )
{
  GetImpl(*this).SetTransitionDuration( duration );
}

float CubeTransitionEffect::GetTransitionDuration() const
{
  return GetImpl(*this).GetTransitionDuration();
}

void CubeTransitionEffect::SetCubeDisplacement( float displacement )
{
  GetImpl(*this).SetCubeDisplacement( displacement );
}

float CubeTransitionEffect::GetCubeDisplacement() const
{
  return GetImpl(*this).GetCubeDisplacement();
}

Actor CubeTransitionEffect::GetRoot()
{
  return GetImpl(*this).GetRoot();
}

bool CubeTransitionEffect::IsTransiting()
{
  return GetImpl(*this).IsTransiting();
}

void CubeTransitionEffect::SetCurrentImage(ImageActor imageActor)
{
  GetImpl(*this).SetCurrentImage( imageActor );
}

void CubeTransitionEffect::SetTargetImage(ImageActor imageActor)
{
  GetImpl(*this).SetTargetImage( imageActor );
}

void CubeTransitionEffect::StartTransition( bool toNextImage )
{
  GetImpl(*this).StartTransition( toNextImage );
}

void CubeTransitionEffect::StartTransition( Vector2 panPosition, Vector2 panDisplacement )
{
  GetImpl(*this).StartTransition( panPosition, panDisplacement );
}

void CubeTransitionEffect::PauseTransition()
{
  GetImpl(*this).PauseTransition();
}

void CubeTransitionEffect::ResumeTransition()
{
  GetImpl(*this).ResumeTransition();
}

void CubeTransitionEffect::StopTransition()
{
  GetImpl(*this).StopTransition();
}

CubeTransitionEffect::TransitionCompletedSignalType& CubeTransitionEffect::TransitionCompletedSignal()
{
  return GetImpl( *this ).TransitionCompletedSignal();
}

} // namespace Toolkit

} // namespace Dali
