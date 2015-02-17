#ifndef __DALI_TOOLKIT_SHADER_EFFECT_IRIS_H__
#define __DALI_TOOLKIT_SHADER_EFFECT_IRIS_H__

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
#include <dali/public-api/shader-effects/shader-effect.h>

namespace Dali
{

namespace Toolkit
{

/**
 * @brief IrisEffect is a custom shader effect to achieve iris effects in Image actors
 */
class DALI_IMPORT_API IrisEffect : public ShaderEffect
{

public:

  /**
   * @brief Create an uninitialized IrisEffect; this can be initialized with IrisEffect::New().
   *
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  IrisEffect();

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   */
  ~IrisEffect();

  /**
   * @brief Create an initialized IrisEffect.
   *
   * @return A handle to a newly allocated Dali resource.
   */
  static IrisEffect New();

  /**
   * @brief Set the radius of the iris effect in texture coordinate distance,
   * i.e. 0.0 (no circle) to 1.0 (complete circle), to > 1.0 (extending
   * outside of texture).
   *
   * @note For Atlas Textures results may be unpredictable.
   *
   * @param [in] radius The new radius.
   */
  void SetRadius(float radius);

  /**
   * @brief Set the blend factor of the iris effect.
   *
   * The lower the value, the larger the blending portion
   * (between Opaque & Transparent)
   *
   * Blending will account for 1 / blendFactor of the radius
   * of the texture.
   *
   * @param [in] value The new blend Factor.
   */
  void SetBlendFactor(float value);

  /**
   * @brief Sets the center point of the iris (in texture coordinates).
   *
   * @param[in] center The center point.
   */
  void SetCenter( const Vector2& center );

  /**
   * @brief Get the name for the radius property which can be used in Animation APIs.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetRadiusPropertyName() const;

  /**
   * @brief Get the name for the blend factor property.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetBlendFactorPropertyName() const;

  /**
   * @brief Get the name for the center property.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetCenterPropertyName() const;


private: // Not intended for application developers
  DALI_INTERNAL IrisEffect(ShaderEffect handle);
};

}
}

#endif
