#ifndef __DALI_TOOLKIT_SCROLLABLE_H__
#define __DALI_TOOLKIT_SCROLLABLE_H__

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

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/control.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal DALI_INTERNAL
{
class Scrollable;
}

/**
 * @brief How axes/rotation or scale are clamped
 */
enum ClampState
{
  NotClamped,   ///< The quantity isn't clamped
  ClampedToMin, ///< The quantity is clamped to the min value
  ClampedToMax  ///< The quantity is clamped to the max value
};

/**
 * @brief A 2 dimensional clamp
 */
struct ClampState2
{
  ClampState x; ///< The clamp state of the x axis
  ClampState y; ///< The clamp state of the y axis
};

/**
 * @brief A 3 dimensional clamp
 */
struct ClampState3
{
  ClampState x; ///< The clamp state of the x axis
  ClampState y; ///< The clamp state of the y axis
  ClampState z; ///< The clamp state of the z axis
};

/**
 * @brief Base class for derived Scrollables that contains actors that can be scrolled manually
 * (via touch) or automatically.
 *
 * Scrollables such as ScrollView and ItemView can be derived from this class.
 */
class DALI_IMPORT_API Scrollable : public Control
{
public:

  /**
   * @brief Clamp signal event's data
   */
  struct ClampEvent
  {
    ClampState3 scale;       ///< Clamp information for scale axes
    ClampState3 position;    ///< Clamp information for position axes
    ClampState rotation;     ///< Clamp information for rotation
  };

  /**
   * @brief Scroll component types
   */
  enum ScrollComponentType
  {
    HorizontalScrollBar,
    VerticalScrollBar,
    OvershootIndicator,
  };

  // Custom properties

  static const std::string SCROLL_RELATIVE_POSITION_PROPERTY_NAME;      ///< Property, name "scroll-relative-position", type VECTOR3
  static const std::string SCROLL_POSITION_MIN_PROPERTY_NAME;           ///< Property, name "scroll-position-min",      type VECTOR3
  static const std::string SCROLL_POSITION_MAX_PROPERTY_NAME;           ///< Property, name "scroll-position-max",      type VECTOR3
  static const std::string SCROLL_DIRECTION_PROPERTY_NAME;              ///< Property, name "scroll-direction",         type VECTOR2

  /// @name Properties
  /** @{ */
  static const Property::Index PROPERTY_OVERSHOOT_EFFECT_COLOR;         ///< Property, name "overshoot-effect-color",  @see SetOvershootEffectColor(),  type VECTOR4
  static const Property::Index PROPERTY_OVERSHOOT_ANIMATION_SPEED;      ///< Property, name "overshoot-animation-speed",  @see SetOvershootAnimationSpeed(),  type FLOAT
  /** @} */

  /// @name Signals
  /** @{ */
  static const char* const SIGNAL_SCROLL_STARTED;   ///< "scroll-started";
  static const char* const SIGNAL_SCROLL_COMPLETED; ///< "scroll-completed";
  static const char* const SIGNAL_SCROLL_UPDATED;   ///< "scroll-updated";
  static const char* const SIGNAL_SCROLL_CLAMPED;   ///< "scroll-clamped";
  /** @} */

public:

  typedef Signal< void ( const Vector3& ) > ScrollStartedSignalType;   ///< ScrollStarted signal type
  typedef Signal< void ( const Vector3& ) > ScrollCompletedSignalType; ///< ScrollCompleted signal type
  typedef Signal< void ( const Vector3& ) > ScrollUpdatedSignalType;   ///< Scroll updated signal type
  typedef Signal< void ( const ClampEvent& ) > ScrollClampedSignalType; ///< Scroll clamped signal type

  /**
   * @brief Signal emitted when the Scrollable has moved (whether by touch or animation).
   */
  ScrollStartedSignalType& ScrollStartedSignal();

  /**
   * @brief Signal emitted when the Scrollable has moved (whether by touch or animation).
   */
  ScrollUpdatedSignalType& ScrollUpdatedSignal();

  /**
   * @brief Signal emitted when the Scrollable has completed movement (whether by touch or animation).
   */
  ScrollCompletedSignalType& ScrollCompletedSignal();

  /**
   * @brief Signal emitted when the Scrollable is pushing against a domain boundary
   * (in either position, scale, or rotation).
   *
   * @return The signal to connect to
   */
  ScrollClampedSignalType& ScrollClampedSignal();

public:

  /**
   * @brief Creates an uninitialized Scrollable handle.
   */
  Scrollable();

  /**
   * @brief Copy constructor.
   *
   * Creates another handle that points to the same real object
   *
   * @param handle to copy from
   */
  Scrollable( const Scrollable& handle );

  /**
   * @brief Assignment operator.
   *
   * Changes this handle to point to another real object
   * @param[in] handle to copy from
   * @return A reference to this
   */
  Scrollable& operator=( const Scrollable& handle );

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   */
  ~Scrollable();

  /**
   * @brief Downcast an Object handle to Scrollable.
   *
   * If handle points to a Scrollable the downcast produces valid
   * handle. If not the returned handle is left uninitialized.
   *
   * @param[in] handle Handle to an object
   * @return handle to a Scrollable or an uninitialized handle
   */
  static Scrollable DownCast( BaseHandle handle );

  /**
   * @brief Checks if a ScrollComponent has been enabled or not.
   *
   * @param[in] type The Scroll Component Type to check
   * @return True (if Enabled)
   */
  bool IsScrollComponentEnabled(Scrollable::ScrollComponentType type) const;

  /**
   * @brief Enables a ScrollComponent.
   *
   * @param[in] type The Scroll Component Type to enable
   */
  void EnableScrollComponent(Scrollable::ScrollComponentType type);

  /**
   * @brief Disables a ScrollComponent.
   *
   * @param[in] type The Scroll Component Type to disable
   */
  void DisableScrollComponent(Scrollable::ScrollComponentType type);

  /**
   * @brief Set the color of the overshoot effect.
   *
   * @param[in] color The color of the overshoot effect.
   */
  void SetOvershootEffectColor( const Vector4& color );

  /**
   * @brief Get the color of the overshoot effect.
   * @return The color of the overshoot effect.
   */
  Vector4 GetOvershootEffectColor() const;

  /**
   * @brief Set the speed of overshoot animation in pixels per second.
   * When the speed is not greater than 0, the overshoot is set instantly with no animation.
   * @param[in] pixelsPerSecond The speed of the overshoot animation.
   */
  void SetOvershootAnimationSpeed( float pixelsPerSecond );

  /**
   * @brief Get the speed of overshoot animation in pixels per second.
   * @return The speed of the overshoot animation.
   */
  float GetOvershootAnimationSpeed() const;

public: // Not intended for application developers

  /**
   * @brief Creates a handle using the Toolkit::Internal implementation.
   *
   * @param[in]  implementation  The Control implementation.
   */
  DALI_INTERNAL Scrollable(Internal::Scrollable& implementation);

  /**
   * @brief Allows the creation of this Control from an Internal::CustomActor pointer.
   *
   * @param[in]  internal  A pointer to the internal CustomActor.
   */
  explicit DALI_INTERNAL Scrollable( Dali::Internal::CustomActor* internal );
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_SCROLLABLE_H__
