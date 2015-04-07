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
#include "cube-transition-cross-effect-impl.h"

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

CubeTransitionCrossEffect::CubeTransitionCrossEffect( unsigned int numRows, unsigned int numColumns, Size viewAreaSize )
: CubeTransitionEffect( numRows, numColumns, viewAreaSize),
  mDisplacementRatio( 1.f )
{
}

Toolkit::CubeTransitionCrossEffect CubeTransitionCrossEffect::New(unsigned int numRows, unsigned int numColumns, Size viewAreaSize)
{
  // Create the implementation
  CubeTransitionCrossEffect* internalCubeTransEffect = new CubeTransitionCrossEffect( numRows, numColumns, viewAreaSize );

  // Pass ownership to CustomActor handle
  Toolkit::CubeTransitionCrossEffect cubeTransEffect( internalCubeTransEffect );

  //Initialization
  internalCubeTransEffect->Initialize();

  return cubeTransEffect;
}

void CubeTransitionCrossEffect::OnInitialize()
{
  float offsetX = -mTileSize.width*0.5f;
  float offsetY = -mTileSize.height*0.5f;
  unsigned int idx;
  for( unsigned int y = 0; y < mNumRows; y++ )
  {
    idx = y*mNumColumns;
    for( unsigned int x = y%2; x < mNumColumns; x=x+2)
    {
      mBoxes[idx+x].SetZ( offsetY );
      mTiles[0][idx+x].SetZ( -offsetY );
      mTiles[1][idx+x].SetY( offsetY );
    }
    for( unsigned int x = (y+1)%2; x < mNumColumns; x=x+2)
    {
      mTiles[0][idx+x].SetZ( -offsetX );
      mTiles[1][idx+x].SetX( offsetX );
    }
  }
}

void CubeTransitionCrossEffect::OnStartTransition( Vector2 panPosition, Vector2 panDisplacement )
{
  float angle = mRotateIndex * Math::PI_2 ;
  Vector3 translation0 = mTiles[mContainerIndex][ 0 ].GetCurrentPosition()*(-2.f);
  Vector3 translation1 = mTiles[mContainerIndex][ mNumColumns ].GetCurrentPosition()*(-2.f);

  unsigned int idx;
  mDisplacementRatio = 1.f + mCubeDisplacement / (mTileSize.width + mTileSize.height);

  for( unsigned int y = 0; y < mNumRows; y++ )
  {
    for( unsigned int x = y%2; x < mNumColumns; x=x+2) // rotate vertically
    {
      idx = y*mNumColumns + x;
      SetupAnimation( idx, -angle, Vector3::XAXIS, translation0 );
    }
    for( unsigned int x = (y+1)%2; x < mNumColumns; x=x+2) // rotate horizontally
    {
      idx = y*mNumColumns + x;
      SetupAnimation( idx, angle, Vector3::YAXIS, translation1 );
    }
  }

  mAnimation.Play();
  mIsAnimating = true;
}

void CubeTransitionCrossEffect::OnStopTransition()
{
  float angle = mRotateIndex * Math::PI_2 ;
  unsigned int idx;
  for( unsigned int y = 0; y < mNumRows; y++ )
  {
    for( unsigned int x = y%2; x < mNumColumns; x=x+2)
    {
      idx = y*mNumColumns + x;
      mBoxes[idx].SetOrientation( Radian(angle), Vector3::XAXIS );
    }
    for( unsigned int x = (y+1)%2; x < mNumColumns; x=x+2)
    {
      idx = y*mNumColumns + x;
      mBoxes[idx].SetOrientation( Radian(-angle), Vector3::YAXIS );
    }
  }
}

void CubeTransitionCrossEffect::SetupAnimation(unsigned int actorIndex, float angle,
                                               const Vector3 axis, Vector3 resetTranslation)
{
  if ( mFirstTransition && (!mIsToNextImage) ) // for the first transition and it is going to previous image
  {
    mTiles[mContainerIndex][actorIndex].SetOrientation( Radian( angle),  axis );
  }
  else if( !mChangeTurningDirection )   // reset rotation, translation and color
  {
    mTiles[mContainerIndex][actorIndex].TranslateBy( resetTranslation );
    mTiles[mContainerIndex][actorIndex].SetOrientation( Radian( angle),  axis );
  }
  mAnimation.AnimateTo( Property( mBoxes[actorIndex], Actor::Property::ORIENTATION ), Quaternion( Radian( -angle ), axis ), AlphaFunctions::EaseInOutSine );
  Vector3 position(mBoxes[actorIndex].GetCurrentPosition());
  mAnimation.AnimateTo( Property( mBoxes[actorIndex], Actor::Property::POSITION ), position * mDisplacementRatio + Vector3( 0.f, 0.f, mCubeDisplacement ), AlphaFunctions::Bounce );
  mAnimation.AnimateTo( Property( mTiles[mContainerIndex^1][actorIndex], Actor::Property::COLOR ), HALF_BRIGHTNESS, AlphaFunctions::EaseOut );
  mAnimation.AnimateTo( Property( mTiles[mContainerIndex][actorIndex], Actor::Property::COLOR ), FULL_BRIGHTNESS, AlphaFunctions::EaseIn );
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
