#ifndef DALI_TOOLKIT_IMAGE_VISUAL_PROPERTIES_H
#define DALI_TOOLKIT_IMAGE_VISUAL_PROPERTIES_H

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

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/visuals/visual-properties.h>

namespace Dali
{

namespace Toolkit
{

namespace ImageVisual
{

namespace Property
{

enum
{
  /**
   * @brief The URL of the image.
   * @details Name "url", type Property::STRING.
   * @SINCE_1_1.45
   * @note Mandatory.
   */
  URL = VISUAL_PROPERTY_START_INDEX,

  /**
   * @brief Fitting options, used when resizing images to fit desired dimensions.
   * @details Name "fittingMode", type Dali::FittingMode (Property::INTEGER) or Property::STRING.
   * @SINCE_1_1.45
   * @note Optional. If not supplied, default is FittingMode::SHRINK_TO_FIT.
   * @note For Normal Quad images only.
   * @see Dali::FittingMode
   */
  FITTING_MODE,

  /**
   * @brief Filtering options, used when resizing images to sample original pixels.
   * @details Name "samplingMode", type Dali::SamplingMode (Property::INTEGER) or Property::STRING.
   * @SINCE_1_1.45
   * @note Optional. If not supplied, default is SamplingMode::BOX.
   * @note For Normal Quad images only.
   * @see Dali::SamplingMode
   */
  SAMPLING_MODE,

  /**
   * @brief The desired image width.
   * @details Name "desiredWidth", type Property::INTEGER.
   * @SINCE_1_1.45
   * @note Optional. If not specified, the actual image width is used.
   * @note For Normal Quad images only.
   */
  DESIRED_WIDTH,

  /**
   * @brief The desired image height.
   * @details Name "desiredHeight", type Property::INTEGER.
   * @SINCE_1_1.45
   * @note Optional. If not specified, the actual image height is used.
   * @note For Normal Quad images only.
   */
  DESIRED_HEIGHT,

  /**
   * @brief Whether to load the image synchronously.
   * @details Name "synchronousLoading", type Property::BOOLEAN.
   * @SINCE_1_1.45
   * @note Optional. If not specified, the default is false, i.e. the image is loaded asynchronously.
   * @note For Normal Quad images only.
   */
  SYNCHRONOUS_LOADING,

  /**
   * @brief If true, only draws the borders.
   * @details Name "borderOnly", type Property::BOOLEAN.
   * @SINCE_1_1.45
   * @note Optional. If not specified, the default is false.
   * @note For N-Patch images only.
   */
  BORDER_ONLY,

  /**
   * @brief This enables Image visuals to automatically be converted to Batch-Image visuals.
   * @details Name "batchingEnabled", type Property::BOOLEAN.
   * @SINCE_1_2.0
   * @note Optional. If not specified, the default is false.
   * @note For Image visuals only. Not to be used with NPatch or SVG images.
   */
  BATCHING_ENABLED,

  /**
   * @brief The image area to be displayed.
   * @details Name "pixelArea", type Property::VECTOR4.
   *          It is a rectangular area.
   *          The first two elements indicate the top-left position of the area, and the last two elements are the area width and height respectively.
   * @SINCE_1_2.1
   * @note Optional. If not specified, the default value is [0.0, 0.0, 1.0, 1.0], i.e. the entire area of the image.
   * @note For Normal Quad images only.
   */
  PIXEL_AREA,

  /**
   * @brief The wrap mode for u coordinate.
   * @details Name "wrapModeU", type Dali::WrapMode::Type (Property::INTEGER) or Property::STRING
   *          It decides how the texture should be sampled when the u coordinate exceeds the range of 0.0 to 1.0.
   * @SINCE_1_2.1
   * @note Optional. If not specified, the default is CLAMP.
   * @note For Normal QUAD image only.
   */
  WRAP_MODE_U,

  /**
   * @brief The wrap mode for v coordinate.
   * @details Name "wrapModeV", type Dali::WrapMode::Type (Property::INTEGER) or Property::STRING
   *          it decides how the texture should be sampled when the v coordinate exceeds the range of 0.0 to 1.0.
   * @SINCE_1_2.1
   * @note Optional. If not specified, the default is CLAMP.
   * @note For Normal QUAD image only.
   */
  WRAP_MODE_V,
};

} // namespace Property

} // namespace ImageVisual

} // namespace Toolkit

} // namespace Dali

#endif // DALI_TOOLKIT_IMAGE_VISUAL_PROPERTIES_H
