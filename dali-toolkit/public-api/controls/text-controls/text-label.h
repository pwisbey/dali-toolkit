#ifndef __DALI_TOOLKIT_TEXT_LABEL_H__
#define __DALI_TOOLKIT_TEXT_LABEL_H__

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

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/control.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal DALI_INTERNAL
{
class TextLabel;
}
/**
 * @addtogroup dali_toolkit_controls_text_controls
 * @{
 */

/**
 * @brief A control which renders a short text string.
 *
 * Text labels are lightweight, non-editable and do not respond to user input.
 *
 * @section TextLabelProperties Properties
 * |%Property enum                    |String name          |Type          |Writable|Animatable|
 * |----------------------------------|---------------------|--------------|--------|----------|
 * | Property::RENDERING_BACKEND      | renderingBackend    |  INTEGER     | O      | X        |
 * | Property::TEXT                   | text                |  STRING      | O      | X        |
 * | Property::FONT_FAMILY            | fontFamily          |  STRING      | O      | X        |
 * | Property::FONT_STYLE             | fontStyle           |  STRING      | O      | X        |
 * | Property::POINT_SIZE             | pointSize           |  FLOAT       | O      | X        |
 * | Property::MULTI_LINE             | multiLine           |  BOOLEAN     | O      | X        |
 * | Property::HORIZONTAL_ALIGNMENT   | horizontalAlignment |  STRING      | O      | X        |
 * | Property::VERTICAL_ALIGNMENT     | verticalAlignment   |  STRING      | O      | X        |
 * | Property::TEXT_COLOR             | textColor           |  VECTOR4     | O      | X        |
 * | Property::ENABLE_MARKUP          | enableMarkup        |  BOOLEAN     | O      | X        |
 * | Property::ENABLE_AUTO_SCROLL     | enableAutoScroll    |  BOOLEAN     | O      | X        |
 * | Property::AUTO_SCROLL_SPEED      | autoScrollSpeed     |  INTEGER     | O      | X        |
 * | Property::AUTO_SCROLL_LOOP_COUNT | autoScrollLoopCount |  INTEGER     | O      | X        |
 * | Property::AUTO_SCROLL_GAP        | autoScrollGap       |  INTEGER     | O      | X        |
 * | Property::SHADOW                 | shadow              |  STRING      | O      | X        |
 * | Property::UNDERLINE              | underline           |  STRING      | O      | X        |
 *
 * @SINCE_1_0.0
 */
class DALI_IMPORT_API TextLabel : public Control
{
public:

  /**
   * @brief The start and end property ranges for this control.
   * @SINCE_1_0.0
   */
  enum PropertyRange
  {
    PROPERTY_START_INDEX = Control::CONTROL_PROPERTY_END_INDEX + 1, ///< @SINCE_1_0.0
    PROPERTY_END_INDEX =   PROPERTY_START_INDEX + 1000              ///< Reserve property indices @SINCE_1_0.0
  };

  /**
   * @brief An enumeration of properties belonging to the TextLabel class.
   * @SINCE_1_0.0
   */
  struct Property
  {
    enum
    {
      /**
       * @brief The type of rendering e.g. bitmap-based
       * @details name "renderingBackend", type INT, default RENDERING_SHARED_ATLAS
       * @SINCE_1_0.0
       */
      RENDERING_BACKEND = PROPERTY_START_INDEX,

      /**
       * @brief The text to display in UTF-8 format,
       * @details name "text", type STRING
       * @SINCE_1_0.0
       */
      TEXT,

      /**
       * @brief The requested font family to use,
       * @details name "fontFamily", type STRING
       * @SINCE_1_0.0
       */
      FONT_FAMILY,

      /**
       * @brief The requested font style to use,
       * @details name "fontStyle", type STRING
       * @SINCE_1_0.0
       */
      FONT_STYLE,

      /**
       * @brief The size of font in points
       * @details name "pointSize", type FLOAT
       * @SINCE_1_0.0
       */
      POINT_SIZE,

      /**
       * @brief The single-line or multi-line layout option
       * @details name "multiLine", type FLOAT, default SINGLE_LINE_BOX
       * @SINCE_1_0.0
       */
      MULTI_LINE,

      /**
       * @brief The line horizontal alignment
       * @details name "horizontalAlignment", type STRING,  values "BEGIN", "CENTER", "END", default BEGIN
       * @SINCE_1_0.0
       */
      HORIZONTAL_ALIGNMENT,

      /**
       * @brief The line vertical alignment
       * @details name "verticalAlignment", type STRING,  values "TOP",   "CENTER", "BOTTOM" @SINCE_1_0.0, default TOP
       * @SINCE_1_0.0
       */
      VERTICAL_ALIGNMENT,

      /**
       * @brief The color of the text
       * @details name "textColor", type VECTOR4
       * @SINCE_1_0.0
       */
      TEXT_COLOR,

      /**
       * @brief The drop shadow offset 0 indicates no shadow
       * @details name "shadowOffset", type VECTOR4
       * @DEPRECATED_1_1.37 Use SHADOW instead
       */
      SHADOW_OFFSET,

      /**
       * @brief The color of a drop shadow
       * @details name "shadowColor", type VECTOR4
       * @DEPRECATED_1_1.37 Use SHADOW instead
       */
      SHADOW_COLOR,

      /**
       * @brief The underline enabled flag
       * @details name "underlineEnabled", type BOOLEAN
       * @DEPRECATED_1_1.37 Use UNDERLINE instead
       */
      UNDERLINE_ENABLED,

      /**
       * @brief The color of the underline
       * @details name "underlineColor", type VECTOR4
       * @DEPRECATED_1_1.37 Use UNDERLINE instead
       */
      UNDERLINE_COLOR,

      /**
       * @brief Overrides the underline height from font metrics
       * @details name "underlineHeight", type FLOAT
       * @DEPRECATED_1_1.37 Use UNDERLINE instead
       */
      UNDERLINE_HEIGHT,

      /**
       * @brief  Whether the mark-up processing is enabled
       * @details name "enableMarkup", type BOOLEAN
       * @SINCE_1_0.0
       */
      ENABLE_MARKUP,

      /**
       * @brief  Start or stop auto scrolling,
       * @details name "enableMarkup", type BOOLEAN, default is false
       * @SINCE_1_1.35
       */
      ENABLE_AUTO_SCROLL,

      /**
       * @brief  Start or stop auto scrolling,
       * @details name "autoScrollSpeed", type INT, default in style sheet
       * @SINCE_1_1.35
       */
      AUTO_SCROLL_SPEED,

      /**
       * @brief  Number of complete loops when scrolling enabled
       * @details name "autoScrollLoopCount", type INT, default in style sheet
       * @SINCE_1_1.35
       */
      AUTO_SCROLL_LOOP_COUNT,

      /**
       * @brief  Gap before before scrolling wraps
       * @details name "autoScrollGap", type INT, default in style sheet but can be overridden to prevent same text being show at start and end.
       * @SINCE_1_1.35
       */
      AUTO_SCROLL_GAP,

      /**
       * @brief The default extra space between lines in points.
       * @details name "lineSpacing", type FLOAT.
       * @SINCE_1_1.37
       */
      LINE_SPACING,

      /**
       * @brief The default underline parameters.
       * @details name "underline", type STRING.
       * @SINCE_1_1.37
       */
      UNDERLINE,

      /**
       * @brief The default shadow parameters.
       * @details name "shadow", type STRING.
       * @SINCE_1_1.37
       */
      SHADOW,

      /**
       * @brief The default emboss parameters.
       * @details name "emboss", type STRING.
       * @SINCE_1_1.37
       */
      EMBOSS,

      /**
       * @brief The default outline parameters.
       * @details name "outline", type STRING.
       * @SINCE_1_1.37
       */
      OUTLINE,
    };
  };

  /**
   * @brief Create the TextLabel control.
   *
   * @SINCE_1_0.0
   * @return A handle to the TextLabel control.
   */
  static TextLabel New();

  /**
   * @brief Create the TextLabel control.
   *
   * @SINCE_1_0.0
   * @param[in] text The text to display.
   * @return A handle to the TextLabel control.
   */
  static TextLabel New( const std::string& text );

  /**
   * @brief Creates an empty handle.
   * @SINCE_1_0.0
   */
  TextLabel();

  /**
   * @brief Copy constructor.
   *
   * @SINCE_1_0.0
   * @param[in] handle The handle to copy from.
   */
  TextLabel( const TextLabel& handle );

  /**
   * @brief Assignment operator.
   *
   * @SINCE_1_0.0
   * @param[in] handle The handle to copy from.
   * @return A reference to this.
   */
  TextLabel& operator=( const TextLabel& handle );

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   * @SINCE_1_0.0
   */
  ~TextLabel();

  /**
   * @brief Downcast a handle to TextLabel.
   *
   * If the BaseHandle points is a TextLabel the downcast returns a valid handle.
   * If not the returned handle is left empty.
   *
   * @SINCE_1_0.0
   * @param[in] handle Handle to an object
   * @return handle to a TextLabel or an empty handle
   */
  static TextLabel DownCast( BaseHandle handle );

public: // Not intended for application developers

  /// @cond internal
  /**
   * @brief Creates a handle using the Toolkit::Internal implementation.
   *
   * @SINCE_1_0.0
   * @param[in] implementation The Control implementation.
   */
  DALI_INTERNAL TextLabel( Internal::TextLabel& implementation );

  /**
   * @brief Allows the creation of this Control from an Internal::CustomActor pointer.
   *
   * @SINCE_1_0.0
   * @param[in]  internal  A pointer to the internal CustomActor.
   */
  explicit DALI_INTERNAL TextLabel( Dali::Internal::CustomActor* internal );
  /// @endcond
};

/**
 * @}
 */
} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_TEXT_LABEL_H__
