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
#include "actor-wrapper.h"

// EXTERNAL INCLUDES
#include <dali/public-api/object/type-registry.h>

// INTERNAL INCLUDES
#include <actors/layer-api.h>
#include <actors/actor-api.h>
#include <actors/image-actor-api.h>
#include <actors/text-actor-api.h>
#include <actors/mesh-actor-api.h>
#include <actors/camera-actor-api.h>
#include <actors/renderable-actor-api.h>
#include <v8-utils.h>
#include <dali-wrapper.h>

namespace Dali
{

namespace V8Plugin
{

v8::Persistent<v8::ObjectTemplate> ActorWrapper::mActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mImageActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mTextActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mMeshActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mCameraActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mLayerActorTemplate;
v8::Persistent<v8::ObjectTemplate> ActorWrapper::mTextViewTemplate;

namespace
{


/**
 * pointer to a persistent template handle
 */
struct ActorTemplate
{
  v8::Persistent<v8::ObjectTemplate>* actorTemplate;
};

/**
 * array of templates for each type of actor
 */
const ActorTemplate ActorTemplateLookup[]=
{
    { &ActorWrapper::mActorTemplate },        // ACTOR
    { &ActorWrapper::mImageActorTemplate },   // IMAGE_ACTOR
    { &ActorWrapper::mTextActorTemplate  },   // TEXT_ACTOR
    { &ActorWrapper::mMeshActorTemplate  },   // MESH_ACTOR
    { &ActorWrapper::mLayerActorTemplate },   // LAYER_ACTOR
    { &ActorWrapper::mCameraActorTemplate},   // CAMERA_ACTOR
    { &ActorWrapper::mTextViewTemplate }
};

/**
 * Bitmask of API's that an actor can support
 */
enum ActorApiBitMask
{
  ACTOR_API              = 1 << 0,
  RENDERABLE_ACTOR_API   = 1 << 1,
  IMAGE_ACTOR_API        = 1 << 2,
  TEXT_ACTOR_API         = 1 << 3,
  MESH_ACTOR_API         = 1 << 4,
  LAYER_API              = 1 << 5,
  CAMERA_ACTOR_API       = 1 << 6,
};

/**
 * structure used for the ActorApiLookup.
 */
struct ActorApiStruct
{
  const char* actorName;
  ActorWrapper::ActorType actorType;
  Actor (*constructor)( const v8::FunctionCallbackInfo< v8::Value >& args);
  int supportApis;
};

/**
 * Lookup table to match a actor type with a constructor and supported API's.
 */
const ActorApiStruct ActorApiLookup[]=
{
  {"Actor",      ActorWrapper::ACTOR,        ActorApi::New,       ACTOR_API },
  {"ImageActor", ActorWrapper::IMAGE_ACTOR,  ImageActorApi::New,  ACTOR_API | RENDERABLE_ACTOR_API | IMAGE_ACTOR_API   },
  {"TextActor",  ActorWrapper::TEXT_ACTOR,   TextActorApi::New,   ACTOR_API | RENDERABLE_ACTOR_API | TEXT_ACTOR_API    },
  {"MeshActor",  ActorWrapper::MESH_ACTOR,   MeshActorApi::New,   ACTOR_API | RENDERABLE_ACTOR_API | MESH_ACTOR_API    },
  {"Layer",      ActorWrapper::LAYER_ACTOR,  LayerApi::New,       ACTOR_API | LAYER_API                                },
  {"CameraActor",ActorWrapper::CAMERA_ACTOR, CameraActorApi::New, ACTOR_API | CAMERA_ACTOR_API                         },
  {"TextView",   ActorWrapper::TEXT_VIEW,    TextViewApi::New,    ACTOR_API },

};

const unsigned int ActorApiLookupCount = sizeof(ActorApiLookup)/sizeof(ActorApiLookup[0]);



/**
 * Creates an actor given a type name
 * Uses the type registry to create an actor of the correct type
 */
Actor CreateActor( const v8::FunctionCallbackInfo< v8::Value >& args,
                        const std::string& typeName )
{
  Actor actor;

  ActorWrapper::ActorType actorType = ActorWrapper::GetActorType( typeName );

  // if we don't currently support the actor type, then use type registry to create it
  if( actorType == ActorWrapper::UNKNOWN_ACTOR )
  {
    Dali::TypeInfo typeInfo = Dali::TypeRegistry::Get().GetTypeInfo( typeName );
    if( typeInfo ) // handle, check if it has a value
    {
      Dali::BaseHandle handle = typeInfo.CreateInstance();
      if( handle )
      {
        actor = Actor::DownCast( handle );
      }
    }
    else
    {
      DALI_SCRIPT_EXCEPTION(args.GetIsolate(),"Unknown actor type");
      return Actor();
    }
  }
  else
  {
    // run the constructor for this type of actor so it can pull out
    // custom parameters, e.g. new TextActor("hello world"); or ImageActor( MyImage );
    actor = (ActorApiLookup[actorType].constructor)( args );
  }
  return actor;
}



/**
 * given an actor type return what api's it supports
 */
int GetActorSupportedApis( ActorWrapper::ActorType type )
{
  return ActorApiLookup[ type].supportApis;
}

/**
 * Used for the ActorFunctionTable to map function names to functions
 * with for a specific API
 */
struct ActorFunctions
{
  const char* name;               ///< function name
  void (*function)( const v8::FunctionCallbackInfo< v8::Value >& args);
  ActorApiBitMask api;
};

/**
 * Contains a list of all functions that can be called an
 * actor / image-actor / mesh-actor/ layer / camera-actor
 */
const ActorFunctions ActorFunctionTable[]=
{
    /**************************************
    * Actor API (in order of actor.h)
    * Any properties that have accessor functions are ignored to avoid duplication
    **************************************/
    // ignore. GetName()  use Actor.name
    // ignore. SetName()  use Actor.name
    { "GetId",             ActorApi::GetId,            ACTOR_API },
    { "IsRoot",            ActorApi::IsRoot,           ACTOR_API },
    { "OnStage",           ActorApi::OnStage,          ACTOR_API },
    { "IsLayer",           ActorApi::IsLayer,          ACTOR_API },
    { "GetLayer",          ActorApi::GetLayer,         ACTOR_API },
    { "Add",               ActorApi::AddActor,         ACTOR_API },
    { "Remove",            ActorApi::RemoveActor,      ACTOR_API },
    { "IsEqualTo" ,        ActorApi::IsEqualTo,        ACTOR_API },
    { "Unparent",          ActorApi::Unparent,         ACTOR_API },
    { "GetChildCount",     ActorApi::GetChildCount,    ACTOR_API },
    { "GetChildAt"   ,     ActorApi::GetChildAt,       ACTOR_API },
    { "FindChildByName",   ActorApi::FindChildByName,  ACTOR_API },
    { "FindChildById",     ActorApi::FindChildById,    ACTOR_API },
    { "GetParent" ,        ActorApi::GetParent,        ACTOR_API },
    { "GetActorType" ,     ActorApi::GetActorType,     ACTOR_API }, // custom for javascript

    // ignore. SetParentOrigin() use Actor.parentOrigin
    // ignore. GetCurrentParentOrigin()  use Actor.parentOrigin
    // ignore. SetAnchorPoint()  use Actor.anchorPoint
    // ignore. GetCurrentAnchorPoint()  use Actor.anchorPoint
    // ignore. SetSize() use Actor.size
    // ignore. GetCurrentSize() use Actor.size
    // ignore. SetPosition(....) use Actor.position
    // ignore. SetX, SetY, SetZ,  use Actor.position.x, Actor.position.y, Actor.position.z
    { "MoveBy",         ActorApi::MoveBy,              ACTOR_API },
    // ignore GetCurrentPosition(). use Actor.position
    // ignore GetCurrentWorldPosition() use Actor.worldPosition
    // ignore SetPositionInheritanceMode() use Actor.positionInheritance
    // ignore GetPositionInheritanceMode()  use Actor.positionInheritance
    // ignore SetRotation() use Actor.rotation
    { "RotateBy",         ActorApi::RotateBy,          ACTOR_API },
    // ignore GetCurrentRotation() use Actor.rotation
    // ignore SetInheritRotation() use Actor.inheritRotation
    // ignore IsRotationInherited() use Actor.inheritRotation
    // ignore GetCurrentWorldRotation() use Actor.worldRotation
    // ignore SetScale() use Actor.scale
    { "ScaleBy",         ActorApi::ScaleBy,            ACTOR_API },
    // ignore GetCurrentScale() use Actor.scale
    // ignore GetCurrentWorldScale() use Actor.worldScale
    // ignore SetInheritScale() use Actor.inheritScale
    // ignore IsScaleInherited() use Actor.inheritScale
    // ignore GetCurrentWorldMatrix() use Actor.worldMatrix
    // ignore SetVisible() use Actor.visible
    // ignore IsVisible() use Actor.visible
    // ignore SetOpacity() use Actor.opacity
    { "OpactiyBy",         ActorApi::OpacityBy,        ACTOR_API },
    // ignore GetCurrentOpacity() use Actor.opacity
    // ignore SetColor() use Actor.color
    { "ColorBy",         ActorApi::ColorBy,            ACTOR_API },
    // ignore GetCurrentColor() use Actor.color
    // ignore SetColorMode() use Actor.colorMode
    // ignore GetColorMode() use Actor.colorMode
    // ignore GetCurrentWorldColor() use Actor.worldColor
    // ignore SetInheritShaderEffect() use Actor.inheritShaderEffect
    // ignore GetInheritShaderEffect() use Actor.inheritShaderEffect
    // ignore SetDrawMode() use Actor.drawMode
    // ignore GetDrawMode() use Actor.drawMode
    // ignore SetSensitive() use Actor.sensitve
    // ignore IsSensitive() use Actor.sensitive
    { "ScreenToLocal"       , ActorApi::ScreenToLocal,         ACTOR_API},
    // ignore SetLeaveRequired() use Actor.leaveRequired
    // ignore GetLeaveRequired() use Actor.leaveRequired
    { "SetKeyboardFocusable", ActorApi::SetKeyboardFocusable,  ACTOR_API }, //-- should this be a property???
    { "IsKeyboardFocusable" , ActorApi::IsKeyboardFocusable,   ACTOR_API }, //-- should this be a property???

    /**************************************
     * Renderable Actor API (in order of renderable-actor.h)
     **************************************/
    { "SetSortModifier",    RenderableActorApi::SetSortModifier,   RENDERABLE_ACTOR_API  },
    { "GetSortModifier",    RenderableActorApi::GetSortModifier,   RENDERABLE_ACTOR_API  },
    { "SetCullFace",        RenderableActorApi::SetCullFace,       RENDERABLE_ACTOR_API  },
    { "GetCullFace",        RenderableActorApi::GetCullFace,       RENDERABLE_ACTOR_API  },
    { "SetBlendMode",       RenderableActorApi::SetBlendMode,      RENDERABLE_ACTOR_API  },
    { "GetBlendMode",       RenderableActorApi::GetBlendMode,      RENDERABLE_ACTOR_API  },
    { "SetBlendFunc",       RenderableActorApi::SetBlendFunc,      RENDERABLE_ACTOR_API  },
    { "GetBlendFunc",       RenderableActorApi::GetBlendFunc,      RENDERABLE_ACTOR_API  },
    { "SetBlendEquation",   RenderableActorApi::SetBlendEquation,  RENDERABLE_ACTOR_API  },
    { "GetBlendEquation",   RenderableActorApi::GetBlendEquation,  RENDERABLE_ACTOR_API  },
    { "SetBlendColor",      RenderableActorApi::SetBlendColor,     RENDERABLE_ACTOR_API  },
    { "GetBlendColor",      RenderableActorApi::GetBlendColor,     RENDERABLE_ACTOR_API  },
    { "SetShaderEffect",    RenderableActorApi::SetShaderEffect,   RENDERABLE_ACTOR_API  },
    { "GetShaderEffect",    RenderableActorApi::GetShaderEffect,   RENDERABLE_ACTOR_API  },
    { "RemoveShaderEffect", RenderableActorApi::RemoveShaderEffect,RENDERABLE_ACTOR_API  },




    /**************************************
     * Layer  API (in order of layer.h)
     **************************************/
    { "GetDepth",           LayerApi::GetDepth,                 LAYER_API  },
    { "Raise",              LayerApi::Raise,                    LAYER_API  },
    { "Lower",              LayerApi::Lower,                    LAYER_API  },
    { "RaiseAbove",         LayerApi::RaiseAbove,               LAYER_API  },
    { "RaiseBelow",         LayerApi::LowerBelow,               LAYER_API  },
    { "RaiseToTop",         LayerApi::RaiseToTop,               LAYER_API  },
    { "LowerToBottom",      LayerApi::ToBottom,                 LAYER_API  },
    { "MoveAbove",          LayerApi::MoveAbove,                LAYER_API  },
    { "MoveBelow",          LayerApi::MoveBelow,                LAYER_API  },
    // ignore SetClipping, use layer.clippingEnable
    // ignore IsClipping, use layer.clippingEnable
    // ignore SetClippingBox, use layer.clippingBox
    { "SetDepthTestDisabled", LayerApi::SetDepthTestDisabled,   LAYER_API },
    { "IsDepthTestDisabled",  LayerApi::IsDepthTestDisabled,    LAYER_API },
    // @todo SetSortFunction

    /**************************************
     * Image Actor API (in order of image-actor.h)
     **************************************/

    { "SetImage",           ImageActorApi::SetImage,              IMAGE_ACTOR_API },
    { "GetImage",           ImageActorApi::GetImage,              IMAGE_ACTOR_API },
    { "SetToNaturalSize",   ImageActorApi::SetToNaturalSize,      IMAGE_ACTOR_API },
    // ignore SetPixelArea, use imageActor.pixelArea
    // ignore GetPixelArea, use imageActor.pixelArea
    { "IsPixelAreaSet",     ImageActorApi::IsPixelAreaSet,        IMAGE_ACTOR_API },
    { "ClearPixelArea",     ImageActorApi::ClearPixelArea,        IMAGE_ACTOR_API },
    // ignore SetStyle, use imageActor.style
    // ignore GetStyle, use imageActor.style
    // ignore SetNinePatchBorder use imageActor.border
    // ignore GetNinePatchBorder use imageActor.border
    // ignore SetFadeIn use imageActor.fadeIn
    // ignore GetFadeIn use imageActor.fadeIn
    // ignore SetFadeInDuration use imageActor.fadeInDuration
    // ignore GetFadeInDuration use imageActor.fadeInDuration
    //{ "GetCurrentImageSize", ImageActorApi::GetCurrentImageSize,  IMAGE_ACTOR_API },


    /**************************************
     * Text Actor API (in order of text-actor.h)
     **************************************/
    //ignore SetText use textActor.text
    { "SetToNaturalSize",   TextActorApi::SetToNaturalSize,      TEXT_ACTOR_API },
    // ignore GetFont use textActor.font
    // ignore SetFont use textActor.font
    // ignore SetGradient use textActor.gradientColor
    // ignore GetGradient textActor.gradientColor
    // ignore SetGradientStartPoint use textActor.gradientStartPoint
    // ignore GetGradientStartPoint textActor.gradientStartPoint
    // ignore SetGradientEndPoint use textActor.gradientEndPoint
    // ignore GetGradientEndPoint textActor.gradientEndPoint
    // @todo? SetTextStyle ( can use individual properties as a work around )
    // @todo? GetTextStyle ( can use individual properties as a work around )
    // ignore SetTextColor use textActor.textColor
    // ignore GetTextColor use textActor.textColor
    // ignore SetSmoothEdge use textActor.smoothEdge
    // ignore SetOutline use textActor.outLineEnable, outlineColor, thicknessWidth
    // ignore SetGlow use textActor.glowEnable, glowColor, glowIntensity
    // ignore SetShadow use textActor.shadowEnable, shadowColor, shadowOffset, shadowSize
    // ignore SetItalics use textActor.italicsAngle ?
    // ignore GetItalics  @todo add italics flag? or just stick with angle
    // ignore GetItalicsAngle  use textActor.italicsAngle
    // ignore SetUnderline use textActor.underline
    // ignore GetUnderline use textActor.underline
    // ignore SetWeight use textActor.weight
    // ignore GetWeight use textActor.weight
    // ignore SetFontDetectionAutomatic use textActor.fontDetectionAutomatic
    // ignore IsFontDetectionAutomatic use textActor.fontDetectionAutomatic
    // ignore GetLoadingState text is loaded synchronously
    // ignore TextAvailableSignal text is loaded synchronously

    /**************************************
     * Mesh Actor API (in order of mesh-actor.h)
     **************************************/
    // @todo a version of MeshActor::New( mesh )
    // @todo a version of MeshActor::New( AnimatableMesh )
    // @todo SetMaterial
    // @todo GetMaterial
    // @todo BindBonesToMesh

    /**************************************
     * Camera Actor API (in order of camera.h)
     **************************************/
    // ignore SetType use camera.type
    // ignore GetType use camera.type
    // ignore SetProjectionMode use camera.projectionMode
    // ignore GetProjectionMode use camera.projectionMode
    // ignore SetFieldOfView use camera.fieldOfView
    // ignore GetFieldOfView use camera.fieldOfView
    // ignore SetAspectRatio use camera.aspectRatio
    // ignore GetAspectRatio use camera.aspectRatio
    // ignore SetNearClippingPlane use camera.nearPlaneDistance
    // ignore GetNearClippingPlane use camera.nearPlaneDistance
    // ignore SetFarClippingPlane use camera.farPlaneDistance
    // ignore GetFarClippingPlane use camera.farPlaneDistance
    // ignore GetTargetPosition use camera.targetPosition
    // ignore SetInvertYAxis use camera.invertYAxis
    // ignore GetInvertYAxis use camera.invertYAxis
    { "SetPerspectiveProjection",   CameraActorApi::SetPerspectiveProjection,   CAMERA_ACTOR_API },
    { "SetOrthographicProjection",  CameraActorApi::SetOrthographicProjection,  CAMERA_ACTOR_API },

};

const unsigned int ActorFunctionTableCount = sizeof(ActorFunctionTable)/sizeof(ActorFunctionTable[0]);
} //un-named space


ActorWrapper::ActorWrapper( Actor actor,
              GarbageCollectorInterface& gc )
: HandleWrapper( BaseWrappedObject::ACTOR , actor, gc ),
  mActor( actor )

{
}

v8::Handle<v8::Object> ActorWrapper::WrapActor(v8::Isolate* isolate, Actor actor )
{
  v8::EscapableHandleScope handleScope( isolate );
  v8::Local<v8::Object> object = WrapActor( isolate, actor, GetActorType( actor.GetTypeName() ) );

  return handleScope.Escape( object );
}

Actor ActorWrapper::GetActor()
{
  return mActor;
}

v8::Handle<v8::Object> ActorWrapper::WrapActor( v8::Isolate* isolate, Actor actor, ActorType actorType )
{
  v8::EscapableHandleScope handleScope( isolate );
  v8::Local<v8::ObjectTemplate> objectTemplate;

  objectTemplate = GetActorTemplate( isolate, actorType );

  // create an instance of the template
  v8::Local<v8::Object> localObject = objectTemplate->NewInstance();

  // create teh actor object
  ActorWrapper* pointer = new ActorWrapper( actor, Dali::V8Plugin::DaliWrapper::Get().GetDaliGarbageCollector() );

  // assign the JavaScript object to the wrapper.
  // This also stores Dali object, in an internal field inside the JavaScript object.
  pointer->SetJavascriptObject( isolate, localObject );

  return handleScope.Escape( localObject );
}

v8::Local<v8::ObjectTemplate> ActorWrapper::GetActorTemplate( v8::Isolate* isolate, ActorWrapper::ActorType type )
{
  v8::EscapableHandleScope handleScope( isolate );
  v8::Local<v8::ObjectTemplate> objectTemplate;

  if( ActorTemplateLookup[type].actorTemplate->IsEmpty() )
  {
    objectTemplate = MakeDaliActorTemplate( isolate, type );
    ActorTemplateLookup[type].actorTemplate->Reset( isolate, objectTemplate );
  }
  else
  {
    // get the object template
    objectTemplate = v8::Local<v8::ObjectTemplate>::New( isolate, *ActorTemplateLookup[type].actorTemplate );
  }

  return handleScope.Escape( objectTemplate );
}

v8::Handle<v8::ObjectTemplate> ActorWrapper::MakeDaliActorTemplate( v8::Isolate* isolate, ActorType actorType )
{
  v8::EscapableHandleScope handleScope( isolate );

  v8::Local<v8::ObjectTemplate> objTemplate = v8::ObjectTemplate::New();

  objTemplate->SetInternalFieldCount( BaseWrappedObject::FIELD_COUNT );

  // find out what API's this actor supports
  int supportApis = GetActorSupportedApis( actorType );

  // add our function properties
  for( unsigned int i = 0; i < ActorFunctionTableCount; ++i )
  {
    const ActorFunctions property =  ActorFunctionTable[i];

    // check to see if the actor supports a certain type of API
    // e.g. ImageActor will support ACTOR_API, RENDERABLE_API and IMAGE_ACTOR_API
    if( supportApis &  property.api )
    {
      std::string funcName = V8Utils::GetJavaScriptFunctionName( property.name);

      objTemplate->Set( v8::String::NewFromUtf8(   isolate, funcName.c_str() ),
                      v8::FunctionTemplate::New( isolate, property.function ) );
    }
  }

  // property handle intercepts property getters and setters and signals
  HandleWrapper::AddInterceptsToTemplate( isolate, objTemplate );


  return handleScope.Escape( objTemplate );
}

void ActorWrapper::NewActor( const v8::FunctionCallbackInfo< v8::Value >& args)
{
  v8::Isolate* isolate = args.GetIsolate();
  v8::HandleScope handleScope( isolate );

  if( !args.IsConstructCall() )
  {
    DALI_SCRIPT_EXCEPTION( isolate, "constructor called without 'new" );
    return;
  }

  // find out the callee function name...e.g. TextActor, ImageActor, MeshActor
  v8::Local<v8::Function> callee = args.Callee();
  v8::Local<v8::Value> v8String = callee->GetName();
  std::string typeName = V8Utils::v8StringToStdString( v8String );

  // create a new actor based on type, using the type registry.
  Actor actor = CreateActor( args, typeName );

  v8::Local<v8::Object> localObject = WrapActor( isolate, actor );

  args.GetReturnValue().Set( localObject );
}

/**
 * given an actor type name, e.g. ImageActor returns the type, e.g. ActorWrapper::IMAGE_ACTOR
 */
ActorWrapper::ActorType ActorWrapper::GetActorType( const std::string& name )
{
  for( unsigned int i = 0 ; i < ActorApiLookupCount ; i++ )
  {
    if( ActorApiLookup[i].actorName == name )
    {
      return ActorApiLookup[i].actorType;
    }
  }
  return ActorWrapper::UNKNOWN_ACTOR;
}



} // namespace V8Plugin

} // namespace Dali
