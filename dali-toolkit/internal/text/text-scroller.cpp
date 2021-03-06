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
#include <dali-toolkit/internal/text/text-scroller.h>

// EXTERNAL INCLUDES
#include <dali/public-api/common/stage.h>
#include <dali/public-api/images/frame-buffer-image.h>
#include <dali/public-api/render-tasks/render-task-list.h>
#include <dali/public-api/rendering/geometry.h>
#include <dali/public-api/rendering/renderer.h>
#include <dali/public-api/rendering/sampler.h>
#include <dali/public-api/rendering/shader.h>
#include <dali/devel-api/images/texture-set-image.h>
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES
#include <dali-toolkit/internal/text/text-scroller-interface.h>
#include <dali-toolkit/internal/text/text-scroller-data.h>

namespace Dali
{

namespace Toolkit
{

namespace Text
{
extern const int MINIMUM_SCROLL_SPEED;
} // namespace

namespace
{

#if defined ( DEBUG_ENABLED )
  Debug::Filter* gLogFilter = Debug::Filter::New(Debug::NoLogging, true, "LOG_TEXT_SCROLLING");
#endif

const char* VERTEX_SHADER_SCROLL = DALI_COMPOSE_SHADER(
  attribute mediump vec2 aPosition;\n
  varying highp vec2 vTexCoord;\n
  varying highp float vRatio;\n
  uniform mediump mat4 uMvpMatrix;\n
  uniform mediump vec3 uSize;\n
  uniform mediump float uDelta;\n
  uniform mediump vec2 uTextureSize;
  uniform mediump float uGap;\n
  uniform mediump float uRtl;\n
  \n
  void main()\n
  {\n
    {\n
      mediump vec4 vertexPosition = vec4(aPosition*uSize.xy, 0.0, 1.0);\n
      float smallTextPadding = max(uSize.x - uTextureSize.x, 0. );\n
      float gap = max( uGap, smallTextPadding );\n
      vTexCoord.x = ( uDelta + ( uRtl * ( uTextureSize.x - uSize.x ) )  + ( aPosition.x * uSize.x ) )/ ( uTextureSize.x+gap );\n
      vTexCoord.y = aPosition.y;\n
      vRatio = uTextureSize.x / ( uTextureSize.x + gap );\n
      gl_Position = uMvpMatrix * vertexPosition;\n
    }\n
  }\n
);

const char* FRAGMENT_SHADER = DALI_COMPOSE_SHADER(
  varying mediump vec2 vTexCoord;\n
  varying highp float vRatio;\n
  uniform sampler2D sTexture;\n
  \n
  void main()\n
  {\n
    mediump vec2 texCoord;\n
    texCoord.y = vTexCoord.y;\n
    texCoord.x = fract( vTexCoord.x ) / vRatio;\n
    if ( texCoord.x > 1.0 )\n
      discard;\n
    \n
    gl_FragColor = texture2D( sTexture, texCoord );\n
  }\n
);

/**
 * @brief Create and set up a camera for the render task to use
 *
 * @param[in] sizeOfTarget size of the source camera to look at
 * @param[out] offscreenCamera custom camera
 */
void CreateCameraActor( const Size& sizeOfTarget, CameraActor& offscreenCamera )
{
  offscreenCamera = CameraActor::New();
  offscreenCamera.SetOrthographicProjection( sizeOfTarget );
  offscreenCamera.SetInvertYAxis( true );
}

/**
 * @brief Create a render task
 *
 * @param[in] sourceActor actor to be used as source
 * @param[in] cameraActor camera looking at source
 * @param[in] offscreenTarget resulting image from render task
 * @param[out] renderTask render task that has been setup
 */
void CreateRenderTask( Actor sourceActor, CameraActor cameraActor , FrameBufferImage offscreenTarget, RenderTask& renderTask )
{
  Stage stage = Stage::GetCurrent();
  RenderTaskList taskList = stage.GetRenderTaskList();
  renderTask = taskList.CreateTask();
  renderTask.SetSourceActor( sourceActor );
  renderTask.SetExclusive( true );
  renderTask.SetInputEnabled( false );
  renderTask.SetClearEnabled( true );
  renderTask.SetCameraActor( cameraActor );
  renderTask.SetTargetFrameBuffer( offscreenTarget );
  renderTask.SetClearColor( Color::TRANSPARENT );
  renderTask.SetCullMode( false );
}

/**
 * @brief Create quad geometry for the mesh
 *
 * @param[out] geometry quad geometry that can be used for a mesh
 */
void CreateGeometry( Geometry& geometry )
{
  struct QuadVertex { Vector2 position;  };

  QuadVertex quadVertexData[4] =
  {
      { Vector2( 0.0f, 0.0f) },
      { Vector2( 1.0f, 0.0f) },
      { Vector2( 0.0f, 1.0f) },
      { Vector2( 1.0f, 1.0f) },
  };

  const unsigned short indices[6] =
  {
     3,1,0,0,2,3
  };

  Property::Map quadVertexFormat;
  quadVertexFormat["aPosition"] = Property::VECTOR2;
  PropertyBuffer quadVertices = PropertyBuffer::New( quadVertexFormat );
  quadVertices.SetData(quadVertexData, 4 );

  geometry = Geometry::New();
  geometry.AddVertexBuffer( quadVertices );
  geometry.SetIndexBuffer( indices, sizeof(indices)/sizeof(indices[0]) );
}


/**
 * @brief Create a renderer
 *
 * @param[in] frameBufferImage texture to be used
 * @param[out] renderer mesh renderer using the supplied texture
 */
void CreateRenderer( FrameBufferImage frameBufferImage, Dali::Renderer& renderer )
{
  Shader shader = Shader::New( VERTEX_SHADER_SCROLL , FRAGMENT_SHADER, Shader::Hint::NONE );

  Sampler sampler = Sampler::New();
  sampler.SetFilterMode(FilterMode::NEAREST, FilterMode::NEAREST );

  TextureSet textureSet = TextureSet::New();
  TextureSetImage( textureSet, 0u, frameBufferImage );
  textureSet.SetSampler( 0u, sampler );

  Geometry meshGeometry;
  CreateGeometry( meshGeometry );

  renderer = Renderer::New( meshGeometry, shader );
  renderer.SetTextures( textureSet );
}

} // namespace

namespace Text
{

TextScrollerPtr TextScroller::New( ScrollerInterface& scrollerInterface )
{
  DALI_LOG_INFO( gLogFilter, Debug::Verbose, "TextScroller::New\n" );

  TextScrollerPtr textScroller( new TextScroller( scrollerInterface) );
  return textScroller;
}

Actor TextScroller::GetSourceCamera() const
{
  return mOffscreenCameraActor;
}

Actor TextScroller::GetScrollingText() const
{
  return mScrollingTextActor;
}

TextScroller::TextScroller( ScrollerInterface& scrollerInterface )
: mScrollerInterface( scrollerInterface ),
  mScrollDeltaIndex( Property::INVALID_INDEX )
{
  DALI_LOG_INFO( gLogFilter, Debug::Verbose, "TextScroller Default Constructor\n" );
}

TextScroller::~TextScroller()
{
  CleanUp();
}

void TextScroller::StartScrolling( Actor sourceActor,
                                   const ScrollerData& data )
{
  DALI_LOG_INFO( gLogFilter,
                 Debug::Verbose,
                 "TextScroller::StartScrolling controlSize[%f,%f] offscreenSize[%f,%f] direction[%d] alignmentOffset[%f]\n",
                 data.mControlSize.x, data.mControlSize.y,
                 data.mOffscreenSize.x, data.mOffscreenSize.y,
                 data.mAutoScrollDirectionRTL,
                 data.mAlignmentOffset );

  FrameBufferImage offscreenRenderTargetForText = FrameBufferImage::New( data.mOffscreenSize.width, data.mOffscreenSize.height, Pixel::RGBA8888 );
  Renderer renderer;

  CreateCameraActor( data.mOffscreenSize, mOffscreenCameraActor );
  CreateRenderer( offscreenRenderTargetForText, renderer );
  CreateRenderTask( sourceActor, mOffscreenCameraActor, offscreenRenderTargetForText, mRenderTask );

  // Reposition camera to match alignment of target, RTL text has direction=true
  if( data.mAutoScrollDirectionRTL )
  {
    mOffscreenCameraActor.SetX( data.mAlignmentOffset + data.mOffscreenSize.width * 0.5f );
  }
  else
  {
    mOffscreenCameraActor.SetX( data.mOffscreenSize.width * 0.5f );
  }

  mOffscreenCameraActor.SetY( data.mOffscreenSize.height * 0.5f );

  DALI_LOG_INFO( gLogFilter, Debug::Verbose, "TextScroller::SetParameters mWrapGap[%f]\n", data.mWrapGap )

  mScrollingTextActor = Actor::New();
  mScrollingTextActor.AddRenderer( renderer );
  mScrollingTextActor.RegisterProperty( "uTextureSize", data.mOffscreenSize );
  mScrollingTextActor.RegisterProperty( "uRtl", ( data.mAutoScrollDirectionRTL ? 1.f : 0.f ) );
  mScrollingTextActor.RegisterProperty( "uGap", data.mWrapGap );
  mScrollingTextActor.SetSize( data.mControlSize.width, std::min( data.mOffscreenSize.height, data.mControlSize.height ) );
  mScrollDeltaIndex = mScrollingTextActor.RegisterProperty( "uDelta", 0.0f );

  float scrollAmount = std::max( data.mOffscreenSize.width + data.mWrapGap, data.mControlSize.width );
  float scrollSpeed = std::max( MINIMUM_SCROLL_SPEED, data.mScrollSpeed );
  float scrollDuration =  scrollAmount / scrollSpeed;

  if( data.mAutoScrollDirectionRTL )
  {
     scrollAmount = -scrollAmount; // reverse direction of scrollung
  }

  mScrollAnimation = Animation::New( scrollDuration );
  mScrollAnimation.AnimateTo( Property( mScrollingTextActor, mScrollDeltaIndex ), scrollAmount );
  mScrollAnimation.SetEndAction( Animation::Discard );
  mScrollAnimation.SetLoopCount( data.mLoopCount );
  mScrollAnimation.FinishedSignal().Connect( this, &TextScroller::AutoScrollAnimationFinished );
  mScrollAnimation.Play();
}

void TextScroller::StopScrolling()
{
  if( mScrollAnimation &&
      ( mScrollAnimation.GetState() == Animation::PLAYING ) )
  {
    DALI_LOG_INFO( gLogFilter, Debug::Verbose, "TextScroller::SetLoopCount Single loop forced\n" );
    mScrollAnimation.SetLoopCount( 1 ); // As animation already playing this allows the current animation to finish instead of trying to stop mid-way
  }
}

void TextScroller::AutoScrollAnimationFinished( Dali::Animation& animation )
{
  DALI_LOG_INFO( gLogFilter, Debug::Verbose, "TextScroller::AutoScrollAnimationFinished\n" );
  CleanUp();
  mScrollerInterface.ScrollingFinished();
}

void TextScroller::CleanUp()
{
  if ( Stage::IsInstalled() )
  {
    Stage stage = Stage::GetCurrent();
    RenderTaskList taskList = stage.GetRenderTaskList();
    UnparentAndReset( mScrollingTextActor );
    UnparentAndReset( mOffscreenCameraActor );
    taskList.RemoveTask( mRenderTask );
  }
}

} // namespace Text

} // namespace Toolkit

} // namespace Dali
