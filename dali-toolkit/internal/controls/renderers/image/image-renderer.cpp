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
#include "image-renderer.h"

#include <dali-toolkit/internal/controls/renderers/renderer-factory-impl.h>
#include <dali-toolkit/internal/controls/renderers/renderer-factory-cache.h>
#include <dali-toolkit/internal/controls/renderers/control-renderer-impl.h>
#include <dali-toolkit/internal/controls/renderers/control-renderer-data-impl.h>
#include <dali/public-api/images/resource-image.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace
{
const char * const RENDERER_TYPE("renderer-type");
const char * const RENDERER_TYPE_VALUE("image-renderer");

// property names
const char * const IMAGE_URL_NAME("image-url");
const char * const IMAGE_FITTING_MODE("image-fitting-mode");
const char * const IMAGE_SAMPLING_MODE("image-sampling-mode");
const char * const IMAGE_DESIRED_WIDTH("image-desired-width");
const char * const IMAGE_DESIRED_HEIGHT("image-desired-height");

// fitting modes
const char * const SHRINK_TO_FIT("shrink-to-fit");
const char * const SCALE_TO_FILL("scale-to-fill");
const char * const FIT_WIDTH("fit-width");
const char * const FIT_HEIGHT("fit-height");
const char * const DEFAULT("default");

// sampling modes
const char * const BOX("box");
const char * const NEAREST("nearest");
const char * const LINEAR("linear");
const char * const BOX_THEN_NEAREST("box-then-nearest");
const char * const BOX_THEN_LINEAR("box-then-linear");
const char * const NO_FILTER("no-filter");
const char * const DONT_CARE("dont-care");

std::string TEXTURE_UNIFORM_NAME = "sTexture";

const char* VERTEX_SHADER = DALI_COMPOSE_SHADER(
  attribute mediump vec2 aPosition;\n
  varying mediump vec2 vTexCoord;\n
  uniform mediump mat4 uMvpMatrix;\n
  uniform mediump vec3 uSize;\n
  \n
  void main()\n
  {\n
    mediump vec4 vertexPosition = vec4(aPosition, 0.0, 1.0);\n
    vertexPosition.xyz *= uSize;\n
    vertexPosition = uMvpMatrix * vertexPosition;\n
    \n
    vTexCoord = aPosition + vec2(0.5);\n
    gl_Position = vertexPosition;\n
  }\n
);

const char* FRAGMENT_SHADER = DALI_COMPOSE_SHADER(
  varying mediump vec2 vTexCoord;\n
  uniform sampler2D sTexture;\n
  uniform lowp vec4 uColor;\n
  \n
  void main()\n
  {\n
    gl_FragColor = texture2D( sTexture, vTexCoord ) * uColor;\n
  }\n
);

} //unnamed namespace

ImageRenderer::ImageRenderer()
: ControlRenderer(),
  mDesiredSize(),
  mFittingMode( FittingMode::DEFAULT ),
  mSamplingMode( SamplingMode::DEFAULT )
{
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Initialize( RendererFactoryCache& factoryCache, const Property::Map& propertyMap )
{
  Initialize(factoryCache);

  Property::Value* imageURLValue = propertyMap.Find( IMAGE_URL_NAME );
  if( imageURLValue )
  {
    imageURLValue->Get( mImageUrl );

    Property::Value* fittingValue = propertyMap.Find( IMAGE_FITTING_MODE );
    if( fittingValue )
    {
      std::string fitting;
      fittingValue->Get( fitting );

      mFittingMode = FittingMode::DEFAULT;
      if( fitting == SHRINK_TO_FIT )
      {
        mFittingMode = FittingMode::SHRINK_TO_FIT;
      }
      else if( fitting == SCALE_TO_FILL )
      {
        mFittingMode = FittingMode::SCALE_TO_FILL;
      }
      else if( fitting == FIT_WIDTH )
      {
        mFittingMode = FittingMode::FIT_WIDTH;
      }
      else if( fitting == FIT_HEIGHT )
      {
        mFittingMode = FittingMode::FIT_HEIGHT;
      }
      else if( fitting == DEFAULT )
      {
        mFittingMode = FittingMode::DEFAULT;
      }
      else
      {
        DALI_ASSERT_ALWAYS("Unknown fitting mode");
      }
    }

    Property::Value* samplingValue = propertyMap.Find( IMAGE_SAMPLING_MODE );
    if( samplingValue )
    {
      std::string sampling;
      samplingValue->Get( sampling );

      mSamplingMode = SamplingMode::DEFAULT;
      if( sampling == BOX )
      {
        mSamplingMode = SamplingMode::BOX;
      }
      else if( sampling == NEAREST )
      {
        mSamplingMode = SamplingMode::NEAREST;
      }
      else if( sampling == LINEAR )
      {
        mSamplingMode = SamplingMode::LINEAR;
      }
      else if( sampling == BOX_THEN_NEAREST )
      {
        mSamplingMode = SamplingMode::BOX_THEN_NEAREST;
      }
      else if( sampling == BOX_THEN_LINEAR )
      {
        mSamplingMode = SamplingMode::BOX_THEN_LINEAR;
      }
      else if( sampling == NO_FILTER )
      {
        mSamplingMode = SamplingMode::NO_FILTER;
      }
      else if( sampling == DONT_CARE )
      {
        mSamplingMode = SamplingMode::DONT_CARE;
      }
      else if( sampling == DEFAULT )
      {
        mSamplingMode = SamplingMode::DEFAULT;
      }
      else
      {
        DALI_ASSERT_ALWAYS("Unknown sampling mode");
      }
    }

    int desiredWidth = 0;
    Property::Value* desiredWidthValue = propertyMap.Find( IMAGE_DESIRED_WIDTH );
    if( desiredWidthValue )
    {
      desiredWidthValue->Get( desiredWidth );
    }

    int desiredHeight = 0;
    Property::Value* desiredHeightValue = propertyMap.Find( IMAGE_DESIRED_HEIGHT );
    if( desiredHeightValue )
    {
      desiredHeightValue->Get( desiredHeight );
    }

    mDesiredSize = ImageDimensions( desiredWidth, desiredHeight );
  }

  mImage.Reset();
}

void ImageRenderer::SetSize( const Vector2& size )
{
  ControlRenderer::SetSize( size );
  // ToDo: renderer responds to the size change
}

void ImageRenderer::SetClipRect( const Rect<int>& clipRect )
{
  ControlRenderer::SetClipRect( clipRect );
  //ToDo: renderer responds to the clipRect change
}

void ImageRenderer::SetOffset( const Vector2& offset )
{
  //ToDo: renderer applies the offset
}

void ImageRenderer::DoSetOnStage( Actor& actor )
{
  if( !mImageUrl.empty() && !mImage )
  {
    mImage = Dali::ResourceImage::New( mImageUrl, mDesiredSize, mFittingMode, mSamplingMode );
  }

  ApplyImageToSampler();
}

void ImageRenderer::DoSetOffStage( Actor& actor )
{
  //If we own the image then make sure we release it when we go off stage
  if( !mImageUrl.empty() )
  {
    mImage.Reset();
  }
}

void ImageRenderer::CreatePropertyMap( Property::Map& map ) const
{
  map.Clear();
  map.Insert( RENDERER_TYPE, RENDERER_TYPE_VALUE );
  if( !mImageUrl.empty() )
  {
    map.Insert( IMAGE_URL_NAME, mImageUrl );
    map.Insert( IMAGE_DESIRED_WIDTH, mDesiredSize.GetWidth() );
    map.Insert( IMAGE_DESIRED_HEIGHT, mDesiredSize.GetHeight() );
  }
  else if( mImage )
  {
    map.Insert( IMAGE_DESIRED_WIDTH, static_cast<int>(mImage.GetWidth()) );
    map.Insert( IMAGE_DESIRED_HEIGHT, static_cast<int>(mImage.GetHeight()) );

    ResourceImage resourceImage = ResourceImage::DownCast(mImage);
    if( resourceImage )
    {
      map.Insert( IMAGE_URL_NAME, resourceImage.GetUrl() );
    }
  }

  switch( mFittingMode )
  {
    case Dali::FittingMode::FIT_HEIGHT:
    {
      map.Insert( IMAGE_FITTING_MODE, FIT_HEIGHT );
      break;
    }
    case Dali::FittingMode::FIT_WIDTH:
    {
      map.Insert( IMAGE_FITTING_MODE, FIT_WIDTH );
      break;
    }
    case Dali::FittingMode::SCALE_TO_FILL:
    {
      map.Insert( IMAGE_FITTING_MODE, SCALE_TO_FILL );
      break;
    }
    case Dali::FittingMode::SHRINK_TO_FIT:
    {
      map.Insert( IMAGE_FITTING_MODE, SHRINK_TO_FIT );
      break;
    }
    default:
    {
      map.Insert( IMAGE_FITTING_MODE, DEFAULT );
      break;
    }
  }

  switch( mSamplingMode )
  {
    case Dali::SamplingMode::BOX:
    {
      map.Insert( IMAGE_SAMPLING_MODE, BOX );
      break;
    }
    case Dali::SamplingMode::NEAREST:
    {
      map.Insert( IMAGE_SAMPLING_MODE, NEAREST );
      break;
    }
    case Dali::SamplingMode::LINEAR:
    {
      map.Insert( IMAGE_SAMPLING_MODE, LINEAR );
      break;
    }
    case Dali::SamplingMode::BOX_THEN_LINEAR:
    {
      map.Insert( IMAGE_SAMPLING_MODE, BOX_THEN_LINEAR );
      break;
    }
    case Dali::SamplingMode::BOX_THEN_NEAREST:
    {
      map.Insert( IMAGE_SAMPLING_MODE, BOX_THEN_NEAREST );
      break;
    }
    case Dali::SamplingMode::NO_FILTER:
    {
      map.Insert( IMAGE_SAMPLING_MODE, NO_FILTER );
      break;
    }
    case Dali::SamplingMode::DONT_CARE:
    {
      map.Insert( IMAGE_SAMPLING_MODE, DONT_CARE );
      break;
    }
    default:
    {
      map.Insert( IMAGE_SAMPLING_MODE, DEFAULT );
      break;
    }
  }
}

void ImageRenderer::Initialize( RendererFactoryCache& factoryCache )
{
  mImpl->mGeometry = factoryCache.GetGeometry( RendererFactoryCache::QUAD_GEOMETRY );
  if( !(mImpl->mGeometry) )
  {
    mImpl->mGeometry =  factoryCache.CreateQuadGeometry();
    factoryCache.SaveGeometry( RendererFactoryCache::QUAD_GEOMETRY, mImpl->mGeometry );
  }

  mImpl->mShader = factoryCache.GetShader( RendererFactoryCache::IMAGE_SHADER );
  if( !mImpl->mShader )
  {
    mImpl->mShader = Shader::New( VERTEX_SHADER, FRAGMENT_SHADER );
    factoryCache.SaveShader( RendererFactoryCache::IMAGE_SHADER, mImpl->mShader );
  }

  mDesiredSize = ImageDimensions();
  mFittingMode = FittingMode::DEFAULT;
  mSamplingMode = SamplingMode::DEFAULT;
  mImageUrl.clear();
}

void ImageRenderer::SetImage( const std::string& imageUrl )
{
  SetImage( imageUrl, 0, 0, Dali::FittingMode::DEFAULT, Dali::SamplingMode::DEFAULT );
}

void ImageRenderer::SetImage( const std::string& imageUrl, int desiredWidth, int desiredHeight, Dali::FittingMode::Type fittingMode, Dali::SamplingMode::Type samplingMode )
{
  if( mImageUrl != imageUrl )
  {
    mImageUrl = imageUrl;
    mDesiredSize = ImageDimensions( desiredWidth, desiredHeight );
    mFittingMode = fittingMode;
    mSamplingMode = samplingMode;

    if( !mImageUrl.empty() && mImpl->mIsOnStage )
    {
      mImage = Dali::ResourceImage::New( mImageUrl, mDesiredSize, mFittingMode, mSamplingMode );
      ApplyImageToSampler();
    }
    else
    {
      mImage.Reset();
    }
  }
}

void ImageRenderer::SetImage( Image image )
{
  if( mImage != image )
  {
    mImageUrl.clear();
    mDesiredSize = ImageDimensions();
    mFittingMode = FittingMode::DEFAULT;
    mSamplingMode = SamplingMode::DEFAULT;
    mImage = image;

    if( mImage && mImpl->mIsOnStage )
    {
      ApplyImageToSampler();
    }
  }
}

Image ImageRenderer::GetImage() const
{
  return mImage;
}

void ImageRenderer::ApplyImageToSampler()
{
  if( mImage )
  {
    Material material = mImpl->mRenderer.GetMaterial();
    if( material )
    {
      for( std::size_t i = 0; i < material.GetNumberOfSamplers(); ++i )
      {
        Sampler sampler = material.GetSamplerAt( i );
        if( sampler.GetUniformName() == TEXTURE_UNIFORM_NAME )
        {
          sampler.SetImage( mImage );
          return;
        }
      }

      Sampler sampler = Sampler::New( mImage, TEXTURE_UNIFORM_NAME );
      material.AddSampler( sampler );
    }
  }
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali