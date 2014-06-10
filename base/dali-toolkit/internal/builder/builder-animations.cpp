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

// EXTERNAL INCLUDES
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES
#include <dali-toolkit/internal/builder/builder-impl.h>
#include <dali-toolkit/internal/builder/builder-get-is.inl.h>
#include <dali-toolkit/internal/builder/replacement.h>

namespace // unnamed namespace
{

using namespace Dali;

TimePeriod GetTimePeriod( const TreeNode& child, const Toolkit::Internal::Replacement& constant )
{
  OptionalFloat delay      = constant.IsFloat( IsChild(child, "delay" ) );
  OptionalFloat duration   = constant.IsFloat( IsChild(child, "duration" ) );
  DALI_ASSERT_ALWAYS( duration && "Time period must have at least a duration" );

  if( delay )
  {
    return TimePeriod( *delay, *duration );
  }
  else
  {
    return TimePeriod( *duration );
  }
}

Property::Value GetPropertyValue( const Property::Type& propType, const TreeNode& child )
{
  switch ( propType )
  {
    case Property::BOOLEAN:
    {
      return Property::Value( GetBoolean( child ) );
    }

    case Property::FLOAT:
    {
      return Property::Value( GetFloat( child ) );
    }

    case Property::VECTOR2:
    {
      return Property::Value( GetVector2( child ) );
    }

    case Property::VECTOR3:
    {
      return Property::Value( GetVector3( child ) );
    }

    case Property::VECTOR4:
    {
      return Property::Value( GetVector4( child ) );
    }

    case Property::ROTATION:
    {
      if( 4 == child.Size() )
      {
        Vector4 v(GetVector4(child));
        // angle, axis as per spec
        return Property::Value( Quaternion(Radian(Degree(v[3])),
                                           Vector3(v[0],v[1],v[2])) );
      }
      else
      {
        // degrees as per spec
        Vector3 rotation = GetVector3( child );
        return Property::Value( Quaternion(Radian(Degree(rotation.x)),
                                           Radian(Degree(rotation.y)),
                                           Radian(Degree(rotation.z))) );
      }
    }

    case Property::NONE: // fall
    default:
    {
      DALI_ASSERT_ALWAYS( !"Property type incorrect" );
      return Property::Value();
    }
  }
}

AlphaFunction GetAlphaFunction( const std::string& alphaFunction )
{
  typedef std::map< const std::string, Dali::AlphaFunction > AlphaFunctionLut;
  static AlphaFunctionLut alphaFunctionLut;

  if( 0 == alphaFunctionLut.size() )
  {
    // coding convention is uppercase enums
    alphaFunctionLut["DEFAULT"]         = Dali::AlphaFunctions::Default;
    alphaFunctionLut["LINEAR"]          = Dali::AlphaFunctions::Linear;
    alphaFunctionLut["REVERSE"]         = Dali::AlphaFunctions::Reverse;
    alphaFunctionLut["EASE_IN"]         = Dali::AlphaFunctions::EaseIn;
    alphaFunctionLut["EASE_OUT"]        = Dali::AlphaFunctions::EaseOut;
    alphaFunctionLut["EASE_IN_OUT"]     = Dali::AlphaFunctions::EaseInOut;
    alphaFunctionLut["EASE_IN_SINE"]    = Dali::AlphaFunctions::EaseInSine;
    alphaFunctionLut["EASE_OUT_SINE"]   = Dali::AlphaFunctions::EaseOutSine;
    alphaFunctionLut["EASE_IN_OUT_SINE"]= Dali::AlphaFunctions::EaseInOutSine;
    alphaFunctionLut["BOUNCE"]          = Dali::AlphaFunctions::Bounce;
    alphaFunctionLut["BOUNCE_BACK"]     = Dali::AlphaFunctions::BounceBack;
    alphaFunctionLut["EASE_OUT_BACK"]   = Dali::AlphaFunctions::EaseOutBack;
    alphaFunctionLut["SIN"]             = Dali::AlphaFunctions::Sin;
    alphaFunctionLut["SIN2X"]           = Dali::AlphaFunctions::Sin;
  }

  const AlphaFunctionLut::const_iterator iter( alphaFunctionLut.find( alphaFunction ) );

  if( iter != alphaFunctionLut.end() )
  {
    return iter->second;
  }
  else
  {
    DALI_ASSERT_ALWAYS( iter != alphaFunctionLut.end() && "Unknown Anchor Constant" );
    return Dali::AlphaFunctions::Default;
  }
}

} // unnamed namespace


namespace Dali
{

namespace Toolkit
{

namespace Internal
{

Animation CreateAnimation( const TreeNode& child, const Replacement& constant, Dali::Actor searchRoot )
{
  float durationSum = 0.f;

  Dali::Actor searchActor = searchRoot ? searchRoot : Dali::Stage::GetCurrent().GetRootLayer();

  Animation animation( Animation::New( 0.f ) );

  // duration needs to be set before AnimateTo calls for correct operation when AnimateTo has no "time-period".
  OptionalFloat duration = constant.IsFloat( IsChild(child, "duration" ) );

  if( duration )
  {
    animation.SetDuration( *duration );
  }

  if( OptionalBoolean looping = constant.IsBoolean(  IsChild(child, "loop" ) ) )
  {
    animation.SetLooping( *looping );
  }

  if( OptionalString endAction = constant.IsString(  IsChild(child, "end-action" ) ) )
  {
    if("BAKE" == *endAction)
    {
      animation.SetEndAction( Animation::Bake );
    }
    else if("DISCARD" == *endAction)
    {
      animation.SetEndAction( Animation::Discard );
    }
    else if("BAKE_FINAL" == *endAction)
    {
      animation.SetEndAction( Animation::BakeFinal );
    }
  }

  if( OptionalString endAction = constant.IsString(  IsChild(child, "destroy-action" ) ) )
  {
    if("BAKE" == *endAction)
    {
      animation.SetDestroyAction( Animation::Bake );
    }
    else if("DISCARD" == *endAction)
    {
      animation.SetDestroyAction( Animation::Discard );
    }
    else if("BAKE_FINAL" == *endAction)
    {
      animation.SetDestroyAction( Animation::BakeFinal );
    }
  }

  OptionalChild propertiesNode = IsChild(child, "properties" );
  if(propertiesNode)
  {
    const TreeNode::ConstIterator endIter = (*propertiesNode).CEnd();
    for( TreeNode::ConstIterator iter = (*propertiesNode).CBegin(); endIter != iter; ++iter )
    {
      const TreeNode::KeyNodePair& pKeyChild = *iter;

      OptionalString actorName( constant.IsString( IsChild(pKeyChild.second, "actor" ) ) );
      OptionalString property(  constant.IsString( IsChild(pKeyChild.second, "property" ) ) );
      DALI_ASSERT_ALWAYS( actorName && "Animation must specify actor name" );
      DALI_ASSERT_ALWAYS( property  && "Animation must specify a property name" );

      Actor targetActor = searchActor.FindChildByName( *actorName );
      DALI_ASSERT_ALWAYS( targetActor && "Actor must exist for property" );

      Property::Index idx( targetActor.GetPropertyIndex( *property ) );

      // A limitation here is that its possible that between binding to the signal and
      // the signal call that the ShaderEffect of the targetActor has been changed.
      // However this is a unlikely use case especially when using scripts.
      if( idx == Property::INVALID_INDEX )
      {
        if( ShaderEffect effect = targetActor.GetShaderEffect() )
        {
          idx = effect.GetPropertyIndex( *property );
          if(idx != Property::INVALID_INDEX)
          {
            targetActor = effect;
          }
          else
          {
            DALI_SCRIPT_WARNING( "Cannot find property on object or ShaderEffect\n" );
            continue;
          }
        }
        else
        {
          DALI_SCRIPT_WARNING( "Cannot find property on object or ShaderEffect\n" );
          continue;
        }
      }

      if( idx == Property::INVALID_INDEX)
      {
        DALI_ASSERT_ALWAYS( idx != Property::INVALID_INDEX && "Animation must specify a valid property" );
        continue;
      }

      Property prop( Property( targetActor, idx ) );
      Property::Value propValue;

      // these are the defaults
      AlphaFunction alphaFunction( AlphaFunctions::Default );
      TimePeriod timePeriod( 0.f );

      OptionalChild timeChild = IsChild( pKeyChild.second, "time-period" );

      if( timeChild )
      {
        timePeriod = GetTimePeriod( *timeChild, constant );
      }

      durationSum = std::max( durationSum, timePeriod.delaySeconds + timePeriod.durationSeconds );

      if( OptionalString alphaChild = constant.IsString( IsChild(pKeyChild.second, "alpha-function" ) ) )
      {
        alphaFunction = GetAlphaFunction( *alphaChild );
      }

      if( OptionalChild keyFrameChild = IsChild(pKeyChild.second, "key-frames") )
      {
        KeyFrames keyframes = KeyFrames::New();

        const TreeNode::ConstIterator endIter = (*keyFrameChild).CEnd();
        for( TreeNode::ConstIterator iter = (*keyFrameChild).CBegin(); endIter != iter; ++iter )
        {
          const TreeNode::KeyNodePair& kfKeyChild = *iter;

          OptionalFloat kfProgress = constant.IsFloat( IsChild(kfKeyChild.second, "progress" ) );
          DALI_ASSERT_ALWAYS( kfProgress && "Key frame entry must have 'progress'" );

          OptionalChild kfValue = IsChild( kfKeyChild.second, "value" );
          DALI_ASSERT_ALWAYS( kfValue && "Key frame entry must have 'value'" );

          try
          {
            propValue = GetPropertyValue( prop.object.GetPropertyType(prop.propertyIndex), *kfValue );
          }
          catch(...)
          {
            DALI_LOG_WARNING( "Property:'%s' type does not match value type '%s'\n",
                              (*property).c_str(),
                              PropertyTypes::GetName(prop.object.GetPropertyType(prop.propertyIndex)) );

            throw;
          }

          AlphaFunction kfAlphaFunction( AlphaFunctions::Default );
          if( OptionalString alphaFuncStr = constant.IsString( IsChild(pKeyChild.second, "alpha-function") ) )
          {
            kfAlphaFunction = GetAlphaFunction( *alphaFuncStr );
          }

          keyframes.Add( *kfProgress, propValue, kfAlphaFunction );
        }

        if( timeChild )
        {
          animation.AnimateBetween( prop, keyframes, alphaFunction, timePeriod );
        }
        else
        {
          animation.AnimateBetween( prop, keyframes, alphaFunction );
        }
      }
      else
      {
        try
        {
          propValue = GetPropertyValue( prop.object.GetPropertyType(prop.propertyIndex), *IsChild(pKeyChild.second, "value") );
        }
        catch(...)
        {
          DALI_LOG_WARNING( "Property:'%s' type does not match value type '%s'\n", (*property).c_str(),
                            PropertyTypes::GetName( prop.object.GetPropertyType(prop.propertyIndex) ) );

          throw;
        }

        if( OptionalBoolean relative = constant.IsBoolean( IsChild(pKeyChild.second, "relative") ) )
        {
          if( timeChild )
          {
            animation.AnimateBy( prop, propValue, alphaFunction, timePeriod );
          }
          else
          {
            animation.AnimateBy( prop, propValue, alphaFunction );
          }
        }
        else
        {
          if( timeChild )
          {
            animation.AnimateTo( prop, propValue, alphaFunction, timePeriod );
          }
          else
          {
            animation.AnimateTo( prop, propValue, alphaFunction );
          }
        }
      }
    }
  }

  if( !duration )
  {
    animation.SetDuration( durationSum );
  }

  return animation;
}

Animation CreateAnimation( const TreeNode& child )
{
  Replacement replacement;
  return CreateAnimation( child, replacement, Stage::GetCurrent().GetRootLayer() );
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
