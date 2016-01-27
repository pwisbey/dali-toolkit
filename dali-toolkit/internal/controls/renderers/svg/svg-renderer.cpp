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
#include "svg-renderer.h"

// EXTERNAL INCLUDES
#include <dali/public-api/images/buffer-image.h>
#include <dali/public-api/common/stage.h>
#include <dali/public-api/math/vector4.h>
#include <dali/devel-api/images/atlas.h>
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES
#include "nanosvg/nanosvg.h"
#include "svg-rasterize-thread.h"
#include <dali-toolkit/internal/controls/renderers/image/image-renderer.h>
#include <dali-toolkit/internal/controls/renderers/renderer-factory-cache.h>
#include <dali-toolkit/internal/controls/renderers/control-renderer-data-impl.h>


namespace
{
const char * const RENDERER_TYPE("rendererType");
const char * const RENDERER_TYPE_VALUE("svg");
const char * const IMAGE_URL_NAME("imageUrl");
const char * const UNITS("px");

const std::string TEXTURE_UNIFORM_NAME = "sTexture";
const std::string ATLAS_RECT_UNIFORM_NAME = "uAtlasRect";

const Dali::Vector4 FULL_TEXTURE_RECT(0.f, 0.f, 1.f, 1.f);
}

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

SvgRenderer::SvgRenderer( RendererFactoryCache& factoryCache, ImageAtlasManager& atlasManager )
: ControlRenderer( factoryCache ),
  mAtlasRect( FULL_TEXTURE_RECT ),
  mAtlasManager( atlasManager ),
  mParsedImage( NULL )
{
  // the rasterized image is with pre-multiplied alpha format
  mImpl->mFlags |= Impl::IS_PREMULTIPLIED_ALPHA;
}

SvgRenderer::~SvgRenderer()
{
  if( mParsedImage )
  {
    nsvgDelete( mParsedImage );
  }
}

bool SvgRenderer::IsSvgUrl( const std::string& url )
{
  return url.substr( url.find_last_of(".") + 1 ) == "svg";
}

void SvgRenderer::DoInitialize( Actor& actor, const Property::Map& propertyMap )
{
  Property::Value* imageURLValue = propertyMap.Find( IMAGE_URL_NAME );
  if( imageURLValue )
  {
    std::string imageUrl;
    if( imageURLValue->Get( imageUrl ) )
    {
      SetImage( imageUrl );
    }
    else
    {
      DALI_LOG_ERROR( "The property '%s' is not a string\n", IMAGE_URL_NAME );
    }
  }
}

void SvgRenderer::DoSetOnStage( Actor& actor )
{
  Shader shader = ImageRenderer::GetImageShader( mFactoryCache );
  Geometry geometry = mFactoryCache.GetGeometry( RendererFactoryCache::QUAD_GEOMETRY );
  if( !geometry )
  {
    geometry =  mFactoryCache.CreateQuadGeometry();
    mFactoryCache.SaveGeometry( RendererFactoryCache::QUAD_GEOMETRY, geometry );
  }
  Material material = Material::New( shader );
  mImpl->mRenderer = Renderer::New( geometry, material );

  if( mImpl->mSize != Vector2::ZERO && mParsedImage )
  {
    AddRasterizationTask( mImpl->mSize );
  }
}

void SvgRenderer::DoSetOffStage( Actor& actor )
{
  mFactoryCache.GetSVGRasterizationThread()->RemoveTask( this );

  actor.RemoveRenderer( mImpl->mRenderer );
  mImpl->mRenderer.Reset();
}

void SvgRenderer::GetNaturalSize( Vector2& naturalSize ) const
{
  if( mParsedImage )
  {
    naturalSize.x = mParsedImage->width;
    naturalSize.y = mParsedImage->height;
  }
  else
  {
    naturalSize = Vector2::ZERO;
  }
}

void SvgRenderer::SetSize( const Vector2& size )
{
  if(mImpl->mSize != size && mParsedImage && GetIsOnStage() )
  {
    AddRasterizationTask( size );
  }
  mImpl->mSize = size;
}

void SvgRenderer::DoCreatePropertyMap( Property::Map& map ) const
{
  map.Clear();
  map.Insert( RENDERER_TYPE, RENDERER_TYPE_VALUE );
  if( !mImageUrl.empty() )
  {
    map.Insert( IMAGE_URL_NAME, mImageUrl );
  }
}

void SvgRenderer::SetImage( const std::string& imageUrl, ImageDimensions size )
{
  if( mImageUrl != imageUrl )
  {
    mImageUrl = imageUrl;

    NSVGimage* parsedImageOld = mParsedImage;

    Vector2 dpi = Stage::GetCurrent().GetDpi();
    float meanDpi = (dpi.height + dpi.width) * 0.5f;
    mParsedImage = nsvgParseFromFile(mImageUrl.c_str(), UNITS, meanDpi);

    if( size.GetWidth() != 0u && size.GetHeight() != 0u)
    {
      mImpl->mSize.x = size.GetWidth();
      mImpl->mSize.y = size.GetHeight();
    }

    if( mImpl->mSize != Vector2::ZERO && GetIsOnStage() )
    {
      AddRasterizationTask( mImpl->mSize );
    }

    mFactoryCache.GetSVGRasterizationThread()->DeleteImage( parsedImageOld );
  }
}

void SvgRenderer::AddRasterizationTask( const Vector2& size )
{
  if( mImpl->mRenderer && mParsedImage )
  {
    unsigned int width = static_cast<unsigned int>(size.width);
    unsigned int height = static_cast<unsigned int>( size.height );
    BufferImage image = BufferImage::New( width, height, Pixel::RGBA8888);

    RasterizingTaskPtr newTask = new RasterizingTask( this, mParsedImage, width, height );
    mFactoryCache.GetSVGRasterizationThread()->AddTask( newTask );
  }
}

void SvgRenderer::ApplyRasterizedImage( PixelDataPtr rasterizedPixelData )
{
  if( GetIsOnStage()  )
  {
    Material currentMaterial = mImpl->mRenderer.GetMaterial();
    if( mAtlasRect != FULL_TEXTURE_RECT )
    {
      mAtlasManager.Remove( currentMaterial, mAtlasRect );
    }

    Vector4 atlasRect;
    Material material = mAtlasManager.Add(atlasRect, rasterizedPixelData );
    if( material ) // atlasing
    {
      if( material != currentMaterial )
      {
        mImpl->mRenderer.SetMaterial( material );
      }
      mImpl->mRenderer.RegisterProperty( ATLAS_RECT_UNIFORM_NAME, atlasRect );
      mAtlasRect = atlasRect;
    }
    else // no atlasing
    {
      Atlas texture = Atlas::New( rasterizedPixelData->GetWidth(), rasterizedPixelData->GetHeight() );
      texture.Upload( rasterizedPixelData, 0, 0 );

      if( mAtlasRect == FULL_TEXTURE_RECT )
      {
        material = currentMaterial;
      }
      else
      {
        material = Material::New( ImageRenderer::GetImageShader( mFactoryCache ) );
        mImpl->mRenderer.SetMaterial( material );

        mImpl->mRenderer.RegisterProperty( ATLAS_RECT_UNIFORM_NAME, FULL_TEXTURE_RECT );
        mAtlasRect = FULL_TEXTURE_RECT;
      }

      if( material )
      {
        int index = material.GetTextureIndex( TEXTURE_UNIFORM_NAME );
        if( index != -1 )
        {
          material.SetTextureImage( index, texture );
          return;
        }

        material.AddTexture( texture, TEXTURE_UNIFORM_NAME );
      }
    }
  }
}



} // namespace Internal

} // namespace Toolkit

} // namespace Dali