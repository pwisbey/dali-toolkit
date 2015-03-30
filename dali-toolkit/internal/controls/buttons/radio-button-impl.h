#ifndef __DALI_TOOLKIT_INTERNAL_RADIO_BUTTON_H__
#define __DALI_TOOLKIT_INTERNAL_RADIO_BUTTON_H__

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
#include <dali/public-api/actors/image-actor.h>
#include <dali/public-api/common/dali-vector.h>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/text-view/text-view.h>
#include <dali-toolkit/public-api/controls/buttons/radio-button.h>
#include <dali-toolkit/public-api/controls/table-view/table-view.h>
#include "button-impl.h"

namespace Dali
{
namespace Toolkit
{
namespace Internal
{

/**
 * RadioButton implementation class.
 *
 * \sa Dali::Toolkit::RadioButton
 */
class RadioButton: public Button
{
public:

  /**
   * Create a new RadioButton.
   *
   * @return A smart-pointer to the newly allocated PushButton.
   */
  static Dali::Toolkit::RadioButton New();

  /**
   * Construct a new PushButton.
   */
  RadioButton();

  /**
   * Construct a new PushButton with label.
   */
  RadioButton( const std::string& label );

  /**
   * Construct a new PushButton with label.
   */
  RadioButton( Actor label );

  /**
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~RadioButton();

public: // From Button

  /**
   * @copydoc Toolkit::Internal::Button::SetButtonImage( Actor image )
   */
  virtual void SetButtonImage( Actor image );

  /**
   * @copydoc Toolkit::Internal::Button::SetSelectedImage( Actor image )
   */
  virtual void SetSelectedImage( Actor image );

private: // From Button

  /**
   * @copydoc Toolkit::Internal::Button::OnButtonInitialize()
   */
  virtual void OnButtonInitialize();

  /**
   * @copydoc Toolkit::Internal::Button::OnButtonUp()
   */
  virtual void OnButtonUp();

  /**
   * @copydoc Toolkit::Internal::Button::OnSelected()
   */
  virtual void OnSelected( bool selected );

  /**
   * @copydoc Toolkit::Internal::Button::OnLabelSet()
   */
  virtual void OnLabelSet();

private:

  /**
   * @brief Set the image to display
   *
   * @param[in] image The image to set
   */
  void SetImage( Actor image );

private:

  // Undefined
  RadioButton( const RadioButton& origin );

  // Undefined
  RadioButton& operator=( const RadioButton& origin );

private:

  Toolkit::TableView mLayoutContainer;      ///< Container to position button images and labels

};

} // namespace Internal

// Helpers for public-api forwarding methods

inline Toolkit::Internal::RadioButton& GetImplementation(Toolkit::RadioButton& button)
{
  DALI_ASSERT_ALWAYS(button);

  Dali::RefObject& handle = button.GetImplementation();

  return static_cast<Toolkit::Internal::RadioButton&> (handle);
}

inline const Toolkit::Internal::RadioButton& GetImplementation(const Toolkit::RadioButton& button)
{
  DALI_ASSERT_ALWAYS(button);

  const Dali::RefObject& handle = button.GetImplementation();

  return static_cast<const Toolkit::Internal::RadioButton&> (handle);
}

} // namespace Toolkit
} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_RADIO_BUTTON_H__
