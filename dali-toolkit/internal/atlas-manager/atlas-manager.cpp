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

// CLASS HEADER
#include <dali-toolkit/internal/atlas-manager/atlas-manager.h>

 // INTERNAL INCLUDES
#include <dali-toolkit/internal/atlas-manager/atlas-manager-impl.h>

namespace Dali
{

namespace Toolkit
{

AtlasManager::AtlasManager()
{
}

AtlasManager::~AtlasManager()
{
}

AtlasManager AtlasManager::New()
{
  Internal::AtlasManagerPtr internal = Internal::AtlasManager::New();
  return AtlasManager(internal.Get());
}

AtlasManager::AtlasManager(Internal::AtlasManager *impl)
  : BaseHandle(impl)
{
}

AtlasManager::AtlasId AtlasManager::CreateAtlas( SizeType width,
                                                 SizeType height,
                                                 SizeType blockWidth,
                                                 SizeType blockHeight,
                                                 Pixel::Format pixelformat )
{
  return GetImplementation(*this).CreateAtlas( width, height, blockWidth, blockHeight, pixelformat );
}

void AtlasManager::SetAddPolicy( AddFailPolicy policy )
{
  GetImplementation(*this).SetAddPolicy( policy );
}

void AtlasManager::Add( const BufferImage& image,
                        AtlasManager::AtlasSlot& slot,
                        AtlasManager::AtlasId atlas )
{
  GetImplementation(*this).Add( image, slot, atlas );
}

bool AtlasManager::Remove( ImageId id )
{
  return GetImplementation(*this).Remove( id );
}

void AtlasManager::GenerateMeshData( ImageId id,
                                     const Vector2& position,
                                     MeshData& meshData)
{
  GetImplementation(*this).GenerateMeshData( id,
                                             position,
                                             meshData );
}

void AtlasManager::StitchMesh( MeshData& first,
                               const MeshData& second,
                               bool optimize )
{
  GetImplementation(*this).StitchMesh( first, second, optimize );
}

void AtlasManager::StitchMesh( const MeshData& first,
                               const MeshData& second,
                               MeshData& out,
                               bool optimize )
{
  GetImplementation(*this).StitchMesh( first, second, out, optimize );
}

Dali::Atlas AtlasManager::GetAtlasContainer( AtlasId atlas ) const
{
  return GetImplementation(*this).GetAtlasContainer( atlas );
}

AtlasManager::AtlasId AtlasManager::GetAtlas( ImageId id )
{
  return GetImplementation(*this).GetAtlas( id );
}

Vector2 AtlasManager::GetBlockSize( AtlasId atlas )
{
  return GetImplementation(*this).GetBlockSize( atlas );
}

Vector2 AtlasManager::GetAtlasSize( AtlasId atlas )
{
  return GetImplementation(*this).GetAtlasSize( atlas );
}

AtlasManager::SizeType AtlasManager::GetFreeBlocks( AtlasId atlas )
{
  return GetImplementation(*this).GetFreeBlocks( atlas );
}

void AtlasManager::SetNewAtlasSize( const Vector2& size,
                                    const Vector2& blockSize )
{
  GetImplementation(*this).SetNewAtlasSize( size, blockSize );
}

AtlasManager::SizeType AtlasManager::GetAtlasCount() const
{
  return GetImplementation(*this).GetAtlasCount();
}

Pixel::Format AtlasManager::GetPixelFormat( AtlasId atlas )
{
  return GetImplementation(*this).GetPixelFormat( atlas );
}

void AtlasManager::GetMetrics( Metrics& metrics )
{
  return GetImplementation(*this).GetMetrics( metrics );
}

} // namespace Toolkit

} // namespace Dali