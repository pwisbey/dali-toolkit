#ifndef __DALI_TOOLKIT_CHECK_BOX_BUTTON_H__
#define __DALI_TOOLKIT_CHECK_BOX_BUTTON_H__

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
#include <dali-toolkit/public-api/controls/buttons/button.h>

namespace Dali
{

namespace Toolkit
{

// Forward declarations

namespace Internal DALI_INTERNAL
{
class CheckBoxButton;
}

/**
 * CheckBoxButton provides a check box button which user can check or uncheck.
 *
 * By default a CheckBoxButton emits a Button::ClickedSignal() signal when the button changes its state to checked or unchecked.
 *
 * The button's appearance could be modified by setting images or actors with CheckBoxButton::SetBackgroundImage,
 * CheckBoxButton::SetCheckedImage, CheckBoxButton::SetDisabledBackgroundImage and CheckBoxButton::SetDisabledCheckedImage.
 *
 * When the button is not disabled, if it's not checked it only shows the \e background image. The \e checked image is shown over the
 * \e background image when the box is checked (\e background image is not replaced by \e checked image).
 *
 * When the button is disabled, \e background image and \e checked image are replaced by \e disabled images.
 *
 * CheckBoxButton doesn't have a text. However, a Dali::Toolkit::TableView with a Dali::TextActor or a Dali::Toolkit::TextView
 * and a CheckBoxButton could be used instead.
 */
class DALI_IMPORT_API CheckBoxButton : public Button
{
public:
  //Action Names
  static const char* const ACTION_CHECK_BOX_BUTTON_CLICK;

public:

  /**
   * Create an uninitialized CheckBoxButton; this can be initialized with CheckBoxButton::New()
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  CheckBoxButton();

  /**
   * Copy constructor.
   */
  CheckBoxButton( const CheckBoxButton& checkBox );

  /**
   * Assignment operator.
   */
  CheckBoxButton& operator=( const CheckBoxButton& checkBox );

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   */
  ~CheckBoxButton();

  /**
   * Create an initialized CheckBoxButton.
   * @return A handle to a newly allocated Dali resource.
   */
  static CheckBoxButton New();

  /**
   * Downcast an Object handle to CheckBoxButton. If handle points to a CheckBoxButton the
   * downcast produces valid handle. If not the returned handle is left uninitialized.
   * @param[in] handle Handle to an object
   * @return handle to a CheckBoxButton or an uninitialized handle
   */
  static CheckBoxButton DownCast( BaseHandle handle );

  /**
   * Sets the button as checked or unchecked.
   *
   * Emits a Button::ClickedSignal() signal if the checkbox is not disabled and the new state,
   * given in the \e checked param, is different than the previous one.
   *
   * @param[in] checked state.
   */
  void SetChecked( bool checked );

  /**
   * @return \e true if the button is checked.
   */
  bool IsChecked() const;

  /**
   * Sets the background image.
   *
   * @param[in] image The background image.
   */
  void SetBackgroundImage( Image image );

  /**
   * @copydoc SetBackgroundImage( Image image )
   */
  void SetBackgroundImage( Actor image );

  /**
   * Gets the background image.
   * @return An actor with the background image.
   */
  Actor GetBackgroundImage() const;

  /**
   * Sets the checked image.
   *
   * @param[in] image The checked image.
   */
  void SetCheckedImage( Image image );

  /**
   * @copydoc SetCheckedImage( Image image )
   */
  void SetCheckedImage( Actor image );

  /**
   * Gets the checked image.
   * @return An actor with the checked image.
   */
  Actor GetCheckedImage() const;

  /**
   * Sets the disabled background image.
   *
   * @param[in] image The disabled background image.
   */
  void SetDisabledBackgroundImage( Image image );

  /**
   * @copydoc SetDisabledBackgroundImage( Image image )
   */
  void SetDisabledBackgroundImage( Actor image );

  /**
   * Gets the disabled background image.
   * @return An actor with the disabled background image.
   */
  Actor GetDisabledBackgroundImage() const;

  /**
   * Sets the disabled checked image.
   *
   * @param[in] image The disabled checked image.
   */
  void SetDisabledCheckedImage( Image image );

  /**
   * @copydoc SetDisabledCheckedImage( Image image )
   */
  void SetDisabledCheckedImage( Actor image );

  /**
   * Gets the disabled checked image.
   * @return An actor with the disabled checked image.
   */
  Actor GetDisabledCheckedImage() const;

public: // Not intended for application developers

  /**
   * Creates a handle using the Toolkit::Internal implementation.
   * @param[in]  implementation  The Control implementation.
   */
  DALI_INTERNAL CheckBoxButton( Internal::CheckBoxButton& implementation );

  /**
   * Allows the creation of this Control from an Internal::CustomActor pointer.
   * @param[in]  internal  A pointer to the internal CustomActor.
   */
  DALI_INTERNAL CheckBoxButton( Dali::Internal::CustomActor* internal );
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_CHECK_BOX_BUTTON_H__
