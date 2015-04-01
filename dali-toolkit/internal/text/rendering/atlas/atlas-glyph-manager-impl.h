
#ifndef __DALI_TOOLKIT_ATLAS_GLYPH_MANAGER_IMPL_H__
#define __DALI_TOOLKIT_ATLAS_GLYPH_MANAGER_IMPL_H__

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
 */


// EXTERNAL INCLUDES
#include <dali/public-api/common/vector-wrapper.h>
#include <dali/public-api/object/base-object.h>

// INTERNAL INCLUDES
#include <dali-toolkit/internal/text/rendering/atlas/atlas-glyph-manager.h>

namespace Dali
{

namespace Toolkit
{

class AtlasGlyphManager;

} // namespace Toolkit

namespace Toolkit
{

namespace Internal
{

class AtlasGlyphManager;
typedef IntrusivePtr<AtlasGlyphManager> AtlasGlyphManagerPtr;

class AtlasGlyphManager : public Dali::BaseObject
{
public:

  struct GlyphRecord
  {
    Text::FontId mFontId;
    Text::GlyphIndex mIndex;
    uint32_t mImageId;
  };

  AtlasGlyphManager();

  virtual ~AtlasGlyphManager();

/**
   * Create a new AtlasGlyphManager
   */
  static AtlasGlyphManagerPtr New();

  /**
   * @copydoc Toolkit::AtlasGlyphManager::Add
   */
  void Add( const Text::GlyphInfo& glyph,
            const BufferImage& bitmap,
            Dali::Toolkit::AtlasManager::AtlasSlot& slot );

  /**
   * @copydoc Toolkit::AtlasGlyphManager::GenerateMeshData
   */
  void GenerateMeshData( uint32_t imageId,
                         const Vector2& position,
                         MeshData& meshData );

  /**
   * @copydoc Toolkit::AtlasGlyphManager::StitchMesh
   */
  void StitchMesh( MeshData& first,
                   const MeshData& second );

  /**
   * @copydoc Toolkit::AtlasGlyphManager::Cached
   */
  void Cached( Text::FontId fontId,
               Text::GlyphIndex index,
               Dali::Toolkit::AtlasManager::AtlasSlot& slot );

  /**
   * @copydoc Toolkit::AtlasGlyphManager::SetNewAtlasSize
   */
  void SetNewAtlasSize( const Vector2& size,
                        const Vector2& blockSize );

  /**
   * @copydoc Toolkit::AtlasGlyphManager::Remove
   */
  void Remove( uint32_t imageId );

  /**
   * @copydoc toolkit::AtlasGlyphManager::GetPixelFormat
   */
  Pixel::Format GetPixelFormat( uint32_t atlasId );

  /**
   * @copydoc toolkit::AtlasGlyphManager::GetMetrics
   */
  const Toolkit::AtlasGlyphManager::Metrics& GetMetrics();

private:

  Dali::Toolkit::AtlasManager mAtlasManager;
  Vector< GlyphRecord > mGlyphRecords;
  uint32_t mCount;
  Toolkit::AtlasGlyphManager::Metrics mMetrics;
};

} // namespace Internal

inline const Internal::AtlasGlyphManager& GetImplementation(const Toolkit::AtlasGlyphManager& manager)
{
  DALI_ASSERT_ALWAYS( manager && "AtlasGlyphManager handle is empty" );

  const BaseObject& handle = manager.GetBaseObject();

  return static_cast<const Internal::AtlasGlyphManager&>(handle);
}

inline Internal::AtlasGlyphManager& GetImplementation(Toolkit::AtlasGlyphManager& manager)
{
  DALI_ASSERT_ALWAYS( manager && "AtlasGlyphManager handle is empty" );

  BaseObject& handle = manager.GetBaseObject();

  return static_cast<Internal::AtlasGlyphManager&>(handle);
}

} // namespace Toolkit

} // namespace Dali


 #endif // __DALI_TOOLKIT_ATLAS_GLYPH_MANAGER_IMPL_H__