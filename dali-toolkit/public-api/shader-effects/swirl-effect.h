#ifndef __DALI_TOOLKIT_SHADER_EFFECT_SWIRL_H__
#define __DALI_TOOLKIT_SHADER_EFFECT_SWIRL_H__

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
 * @brief SwirlEffect is a custom shader effect to achieve swirl effects in Image actors.
 */
class DALI_IMPORT_API SwirlEffect : public ShaderEffect
{
public:

  /**
   * @brief Create an uninitialized SwirlEffect; this can be initialized with SwirlEffect::New().
   *
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  SwirlEffect();

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   */
  ~SwirlEffect();

  /**
   * @brief Create an initialized SwirlEffect.
   *
   * @param[in] warp True if the effect should warp.
   * @return A handle to a newly allocated Dali resource.
   */
  static SwirlEffect New(bool warp);

  /**
   * @brief Set the angle of the swirl.
   *
   * @param[in] angle The angle in float.
   */
  void SetAngle(float angle);

  /**
   * @brief Set the center of the swirl.
   *
   * @param[in] center The center in Vector2.
   */
  void SetCenter(const Vector2& center);

  /**
   * @brief Set the radius of the swirl.
   *
   * @param[in] radius The radius in float.
   */
  void SetRadius(float radius);

  /**
   * @brief Get the name for the angle property.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetAnglePropertyName() const;

  /**
   * @brief Get the name for the center property.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetCenterPropertyName() const;

  /**
   * @brief Get the name for the radius property.
   *
   * @return A std::string containing the property name
   */
  const std::string& GetRadiusPropertyName() const;

private: // Not intended for application developers
  DALI_INTERNAL SwirlEffect(ShaderEffect handle);
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_SHADER_EFFECT_SWIRL_H__
