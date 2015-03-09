#ifndef __DALI_TOOLKIT_TEXT_VIEW_H__
#define __DALI_TOOLKIT_TEXT_VIEW_H__

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
#include <string>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/alignment/alignment.h>
#include <dali-toolkit/public-api/markup-processor/markup-processor.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal DALI_INTERNAL
{
class TextView;
}

/**
 * @brief The TextView class is a UI Dali::Toolkit::Control designed to extend the capabilities of the basic Dali::TextActor.
 *
 * It provides support for multi-line wrapping, multi-language font detection, text alignment, scrolling and styling.
 *
 * See the \link text-view Text View \endlink page of the Programming Guide for more details and examples.
 *
 * Signals
 * | %Signal Name      | Method                    |
 * |-------------------|---------------------------|
 * | scrolled          | @ref ScrolledSignal()     |
 */
class DALI_IMPORT_API TextView : public Control
{
public:

  /**
   * @brief The start and end property ranges for this control.
   */
  enum PropertyRange
  {
    PROPERTY_START_INDEX = Control::CONTROL_PROPERTY_END_INDEX + 1,
    PROPERTY_END_INDEX =   PROPERTY_START_INDEX + 1000              ///< Reserve property indices
  };

  /**
   * @brief An enumeration of properties belonging to the TextView class.
   */
  struct Property
  {
    enum
    {
      MARKUP_ENABLED = PROPERTY_START_INDEX, ///< name "markup-enabled",       @see SetMarkupProcessingEnabled(), type BOOLEAN
      TEXT,                                  ///< name "text",                 @see SetText(),                    type STRING
      MULTILINE_POLICY,                      ///< name "multiline-policy",     @see SetMultilinePolicy(),         type STRING
      WIDTH_EXCEED_POLICY,                   ///< name "width-exceed-policy",  @see SetWidthExceedPolicy(),       type STRING
      HEIGHT_EXCEED_POLICY,                  ///< name "height-exceed-policy", @see SetHeightExceedPolicy(),      type STRING
      LINE_JUSTIFICATION,                    ///< name "line-justification",   @see SetLineJustification(),       type STRING
      FADE_BOUNDARY,                         ///< name "fade-boundary",        @see SetFadeBoundary(),            type VECTOR4
      LINE_HEIGHT_OFFSET,                    ///< name "line-height-offset",   @see SetLineHeightOffset(),        type FLOAT
      HORIZONTAL_ALIGNMENT,                  ///< name "horizontal-alignment", @see SetTextAlignment(),           type STRING
      VERTICAL_ALIGNMENT,                    ///< name "vertical-alignment",   @see SetTextAlignment(),           type STRING
    };
  };

  /**
   * @brief Structure used to retrieve Layout info per character.
   */
  struct CharacterLayoutInfo
  {
    /**
     * @brief Default constructor.
     *
     * Initializes all members to their default values.
     */
    CharacterLayoutInfo();

    /**
     * @brief Empty destructor.
     *
     * @note Added to increase coverage.
     */
    ~CharacterLayoutInfo();

    /**
     * @brief Copy constructor.
     */
    CharacterLayoutInfo( const CharacterLayoutInfo& characterLayoutInfo );

    /**
     * @brief Assignment operator.
     */
    CharacterLayoutInfo& operator=( const CharacterLayoutInfo& character );

    /**
     * @brief Constructor.
     *
     * @param[in] size of the character.
     * @param[in] position of the character.
     * @param[in] isNewParagraphChar Whether the character is a new paragraph character.
     * @param[in] isRightToLeftCharacter Whether is a right to left character.
     * @param[in] visible Whether is visible.
     * @param[in] descender of the character (distance from the base line to the bottom of the character.)
     */
    CharacterLayoutInfo( const Size& size,
                         const Vector3& position,
                         bool isNewParagraphChar,
                         bool isRightToLeftCharacter,
                         bool visible,
                         float descender );

    Size    mSize;                     ///< Size of the character.
    Vector3 mPosition;                 ///< Position of the character within the text view.
    bool    mIsNewLineChar:1;          ///< @deprecated. Use mIsNewParagraphChar instead.
    bool    mIsNewParagraphChar:1;     ///< Whether this character represent a new paragraph.
    bool    mIsRightToLeftCharacter:1; ///< Whether it's a right-to-left character.
    bool    mIsVisible:1;              ///< Whether this character is visible or not.
    float   mDescender;                ///< The character's descender which is the distance from the baseline to the bottom of the character
  };

  typedef std::vector<CharacterLayoutInfo> CharacterLayoutInfoContainer; ///< Container of layout info per character.

  /**
   * @brief Stores some info about a line.
   */
  struct LineLayoutInfo
  {
    std::size_t mCharacterGlobalIndex; ///< Global index within the whole text of the first character of current line.
    Size        mSize;                 ///< Size of the current line.
    float       mAscender;             ///< The max ascender of the current line.
  };

  typedef std::vector<LineLayoutInfo> LineLayoutInfoContainer; ///< Container of layout info per line.

  /**
   * @brief How text is laid out.
   */
  struct TextLayoutInfo
  {
    /**
     * @brief Default constructor.
     */
    TextLayoutInfo();

    /**
     * @brief Empty destructor.
     *
     * @note Added to increase coverage.
     */
    ~TextLayoutInfo();

    /**
     * @brief Copy constructor.
     */
    TextLayoutInfo( const TextLayoutInfo& textLayoutInfo );

    /**
     * @brief Assignment operator.
     */
    TextLayoutInfo& operator=( const TextLayoutInfo& textLayoutInfo );

    CharacterLayoutInfoContainer mCharacterLayoutInfoTable;    ///< The table of character's positions and sizes sorted by the character's visual index.
    LineLayoutInfoContainer      mLines;                       ///< For each line, it stores an index to the first character of the line.
    std::vector<int>             mCharacterLogicalToVisualMap; ///< The map to store the character's logical (input) index according to its visual (reordered) index.
    std::vector<int>             mCharacterVisualToLogicalMap; ///< The map to store the character's visual (reordered) index according to its logical (input) index.
    Size                         mTextSize;                    ///< Text size after relayout.
    Vector2                      mScrollOffset;                ///< Scroll's position.
  };

  /**
   * @brief This structure represents a fade boundary.
   *
   * If the Exceed policy is set to Fade all text which does not fit within the text-view fade boundary is faded out. Text which exceeds the text-view boundary becomes invisible.
   * The \e left, \e right, \e top and \e bottom values are positive, in pixels and set the distances between the text-view and fade boundaries.
   */
  struct FadeBoundary
  {
    /**
     * @brief Default constructor.
     *
     * Initializes all values to 0. It means no fade boundary.
     */
    FadeBoundary();

    /**
     * @brief Constructor.
     *
     * Initializes the fade boundary with the given values.
     *
     * @param[in] left value in pixels.
     * @param[in] right value in pixels.
     * @param[in] top value in pixels.
     * @param[in] bottom value in pixels.
     */
    FadeBoundary( PixelSize left, PixelSize right, PixelSize top, PixelSize bottom );

    PixelSize mLeft;   ///< The left fade boundary
    PixelSize mRight;  ///< The right fade boundary
    PixelSize mTop;    ///< The top fade boundary
    PixelSize mBottom; ///< The bottom fade bounday
  };

  /**
   * @brief Define how to wrap the text's paragraphs in lines.
   *
   * \e SplitByNewLineChar will wrap the text's paragraphs in lines when a '\\n' character or a \<br /\> is found.
   * \e SplitByWord has effect only when TextView size is assigned.
   * It will wrap the text's paragraphs in lines when a '\\n' character or a \<br /\> is found or if a paragraph exceeds the TextView's boundary. This option won't split a word in two.
   * \e SplitByChar has effect only when TextView size is assigned.
   * It will wrap the text's paragraphs in lines when a '\\n' character or a \<br /\> is found or if a paragraph exceeds the TextView's boundary. This option might split a word in two.
   * The default value is \e SplitByNewLineChar.
   */
  enum MultilinePolicy
  {
    SplitByNewLineChar, ///< Text's paragraphs will wrap in lines when '\\n' character is found.
    SplitByWord,        ///< Text's paragraphs will wrap in lines by word or if '\\n' character is found. It has effect only when TextView size is assigned.
    SplitByChar         ///< Text's paragraphs will wrap in lines by char or if '\\n' character is found. It has effect only when TextView size is assigned.
  };

  /**
   * @brief Define how to display the lines when they doesn't fit inside the TextView after the text's paragraphs are wrapped in lines.
   *
   * The default value is \e Original.
   */
  enum ExceedPolicy
  {
    Original,         ///< Will display the lines in their original size. If a line, a word or a character is bigger than the TextView size it may exceed its boundary.
    Fade,             ///< Will display the lines in their original size. It won't display the part of the line which exceeds the TextView boundary. It fades the text out.
    Split,            ///< Will split the lines in a new line(s).
    ShrinkToFit,      ///< Will shrink the lines to fit the TextView boundary.
    EllipsizeEnd      ///< Will ellipsize the lines by the end.
  };

  /**
   * @brief Define how to justify lines inside the text's boundary.
   *
   * The default value is \e Left.
   */
  enum LineJustification
  {
    Left,     ///< Justify to the left.
    Center,   ///< Centered.
    Right,    ///< Justify to the right.
    Justified ///< Line justified.
  };

public:
  /**
   * @brief Create a TextView handle; this can be initialised with TextView::New().
   *
   * Calling member functions with an uninitialised Dali::Object handle is not allowed.
   */
  TextView();

  /**
   * @brief Copy constructor.
   *
   * Creates another handle that points to the same real object
   * @param[in] handle The handle to copy from
   */
  TextView( const TextView& handle );

  /**
   * @brief Assignment operator.
   *
   * Changes this handle to point to another real object
   * @param[in] handle The handle to copy from
   * @return a reference to this
   */
  TextView& operator=( const TextView& handle );

  /**
   * @brief Create a TextView control with no text.
   *
   * @return A handle the TextView control.
   */
  static TextView New();

  /**
   * @brief Create a TextView control.
   *
   * @param[in] text to display.
   * @return A handle the TextView control.
   */
  static TextView New( const std::string& text );

  /**
   * @brief Create a TextView control with styled text.
   *
   * @param[in] text The text with style to display.
   * @return A handle the TextView control.
   */
  static TextView New( const MarkupProcessor::StyledTextArray& text );

  /**
   * @brief Downcast an Object handle to TextView.
   *
   * If handle points to a TextView the
   * downcast produces valid handle. If not the returned handle is left uninitialized.
   * @param[in] handle Handle to an object
   * @return handle to a TextView or an uninitialized handle
   */
  static TextView DownCast( BaseHandle handle );

  /**
   * @brief Destructor
   *
   * This is non-virtual since derived Handle types must not contain data or virtual methods.
   */
  ~TextView();

  /**
   * @brief Replace the current text with a new text string.
   *
   * @param[in] text to display. The string may contain style tags.
   */
  void SetText( const std::string& text );

  /**
   * @brief Replace the current text with a new text string with style.
   *
   * @param[in] text The text with style to display.
   */
  void SetText( const MarkupProcessor::StyledTextArray& text );

  /**
   * @brief Inserts the given text in the specified position.
   *
   * @param[in] position Where the given text is going to be added.
   * @param[in] text The text to be added.
   */
  void InsertTextAt( std::size_t position, const std::string& text );

  /**
   * @brief Inserts the given text with style in the specified position.
   *
   * @param[in] position Where the given text is going to be added.
   * @param[in] text The text with style to be added.
   */
  void InsertTextAt( std::size_t position, const MarkupProcessor::StyledTextArray& text );

  /**
   * @brief Replaces part of the text.
   *
   * It removes the specified number of characters from the given position and inserts the given text in the same specified position.
   *
   * @param[in] position of the first character to be removed and Where the given text is going to be added.
   * @param[in] numberOfCharacters number of characters to be removed.
   * @param[in] text The text to be added.
   */
  void ReplaceTextFromTo( std::size_t position, std::size_t numberOfCharacters, const std::string& text );

  /**
   * @brief Replaces part of the text.
   *
   * It removes the specified number of characters from the given position and inserts the given text with style in the same specified position.
   *
   * @param[in] position of the first character to be removed and Where the given text is going to be added.
   * @param[in] numberOfCharacters number of characters to be removed.
   * @param[in] text The text with style to be added.
   */
  void ReplaceTextFromTo( std::size_t position, std::size_t numberOfCharacters, const MarkupProcessor::StyledTextArray& text );

  /**
   * @brief Removes the specified number of characters from the given position.
   *
   * @param[in] position of the first character to be removed.
   * @param[in] numberOfCharacters number of characters to be removed.
   */
  void RemoveTextFrom( std::size_t position, std::size_t numberOfCharacters );

  /**
   * @brief Get the currently displayed text.
   *
   * @return The currently displayed text.
   */
  std::string GetText() const;

  /**
   * @brief Sets a line height offset.
   *
   * The line height offset will be added to the font line height.
   * @param [in] offset The height offset in PointSize units.
   */
  void SetLineHeightOffset( PointSize offset );

  /**
   * @brief Retrieves the line height offset.
   *
   * @return The line height offset in PointSize units.
   */
  PointSize GetLineHeightOffset() const;

  /**
   * @brief Sets the given style to the current text.
   *
   * By default all style settings are applied but a bit mask could be used to modify only certain style settings.
   * @note TextView doesn't store a copy of the given style, it applies the given style to the current text only.
   * Subsequent calls to SetText() will override any style set by this method.
   * @param[in] style The given style
   * @param[in] mask The bit mask.
   */
  void SetStyleToCurrentText( const TextStyle& style, TextStyle::Mask mask = TextStyle::ALL );

  /**
   * @brief Set the current text alignment.
   *
   * Default alignment is (HorizontalCenter | VerticalCenter)
   * @param[in] align The new alignment option.
   */
  void SetTextAlignment( Alignment::Type align );

  /**
   * @brief Get the current text alignment combined into a single value.
   *
   * The values can be tested by using the & operator
   * and the desired flag. e.g. if (GetTextAlignment() & HorizontalCentre) ...
   * @return the combined alignment
   */
  Alignment::Type GetTextAlignment() const;

  /**
   * @brief Sets how to split the paragraphs into lines.
   *
   * @param policy The multi-line policy. \e SplitByNewLineChar is set by default.
   */
  void SetMultilinePolicy( MultilinePolicy policy );

  /**
   * @brief Gets the wrap in lines policy.
   *
   * @return The multi-line policy.
   */
  MultilinePolicy GetMultilinePolicy() const;

  /**
   * @brief Sets how to display the text inside the TextView when it exceeds the text-view's width.
   *
   * @param policy The exceed policy. Original is set by default.
   */
  void SetWidthExceedPolicy( ExceedPolicy policy );

  /**
   * @brief Gets the width exceed policy.
   *
   * @return The exceed policy.
   */
  ExceedPolicy GetWidthExceedPolicy() const;

  /**
   * @brief Sets how to display the text inside the TextView when it exceeds the text-view's height.
   *
   * @param policy The exceed policy. Original is set by default.
   */
  void SetHeightExceedPolicy( ExceedPolicy policy );

  /**
   * @brief Gets the height exceed policy.
   *
   * @return The exceed policy.
   */
  ExceedPolicy GetHeightExceedPolicy() const;

  /**
   * @brief Sets how to justify lines inside the text's boundary.
   *
   * @param justification The line justification. Left is set by default.
   */
  void SetLineJustification( LineJustification justification );

  /**
   * @brief Gets the line justification.
   *
   * @return The line justification.
   */
  LineJustification GetLineJustification() const;

  /**
   * @brief Sets a fade boundary.
   *
   * @see FadeBoundary.
   *
   * @param[in] fadeBoundary The given fade boundary.
   */
  void SetFadeBoundary( const FadeBoundary& fadeBoundary );

  /**
   * @brief Retrieves the fade boundary.
   *
   * @see FadeBoundary.
   *
   * @return The fade boundary.
   */
  const FadeBoundary& GetFadeBoundary() const;

  /**
   * @brief Sets the ellipsize text.
   *
   * @param[in] ellipsizeText The new text. The string may contain style tags. By default the ellipsize text is '...'
   */
  void SetEllipsizeText( const std::string& ellipsizeText );

  /**
   * @brief Sets the ellipsize text with style.
   *
   * @param[in] ellipsizeText The new text with its style.
   */
  void SetEllipsizeText( const MarkupProcessor::StyledTextArray& ellipsizeText );

  /**
   * @brief Retrieves the ellipsize text.
   *
   * @return The ellipsize text.
   */
  std::string GetEllipsizeText() const;

  /**
   * @brief A mechanism to retrieve layout information from the TextView.
   *
   * It produces a vector of CharcterLayoutInfo structures which describe the size and position of each character,
   * two vectors which maps the logical and visual positions of the characters in a bidirectional text, the size
   * of the whole laid-out text and the scroll offset value.
   *
   * @see TextLayoutInfo.
   *
   * @param[out] textLayoutInfo A structure with text layout information.
   */
  void GetTextLayoutInfo( TextLayoutInfo& textLayoutInfo );

  /**
   * @brief Allows modification of text-actor's position in the depth sort algorithm.
   *
   * @see Dali::RenderableActor::SetSortModifier()
   * @param [in] depthOffset the offset to be given to the internal text-actors. Positive values pushing it further back.
   */
  void SetSortModifier( float depthOffset );

  /**
   * @brief Sets whether text-view renders text using a previously generated snapshot.
   *
   * Rendering long text using a snapshot may increase performance. The default value is \e false (render without using a snapshot).
   *
   * @param[in] enable Whether text-view is using a snapshot to render text.
   */
  void SetSnapshotModeEnabled( bool enable );

  /**
   * @brief Retrieves whether text-view is using a snapshot to render text.
   *
   * @return \e true if text-view is using a snapshot to render text, otherwhise it returns \e false.
   */
  bool IsSnapshotModeEnabled() const;

  /**
   * @brief Sets whether markup processing should be carried out.
   *
   * To use markup, applications need to SetMarkupProcessingEnabled first, then SetText().
   *
   * @see SetText()
   * @param[in] enable whether markup processing is carried out or not.
   */
  void SetMarkupProcessingEnabled( bool enable );

  /**
   * @brief Retrieves whether text-view is processing markup text
   *
   * @return \e true if text-view markup processing is enabled, otherwhise it returns \e false.
   */
  bool IsMarkupProcessingEnabled() const;

  /**
   * @brief Enables or disables the text scroll.
   *
   * When scroll is enabled, snapshot mode will be enabled automatically. Equally, if scroll is disabled
   * the snapshot mode is restored to the previous value.
   *
   * @param[in] enable Whether to enable the text scroll.
   */
  void SetScrollEnabled( bool enable );

  /**
   * @brief Retrieves whether the text scroll is enabled.
   *
   * @return \e true if the scroll is enabled.
   */
  bool IsScrollEnabled() const;

  /**
   * @brief Sets a new scroll position.
   *
   * The new scroll position set could be trimmed if the text doesn't cover the whole text-view.
   * i.e. If a text-view is 100x100 and a text is 200x100 a scroll position beyond 50x0 will be trimmed to 50x0.
   *
   * Call IsScrollPositionTrimmed() to know if the last scroll position set has been trimmed.
   *
   * A signal is emitted. @see ScrolledSignal().
   *
   * @param[in] position The new scroll position.
   */
  void SetScrollPosition( const Vector2& position );

  /**
   * @brief Recrieves current scroll position.
   *
   * @return The scroll position.
   */
  const Vector2& GetScrollPosition() const;

  /**
   * @brief Whether the last scroll position set was trimmed.
   *
   * @return \e true if the last scroll position set was trimmed, otherwise \e false.
   */
  bool IsScrollPositionTrimmed() const;

public:
  /// @brief Signal types
  typedef Signal< void ( TextView textView, Vector2 scrollDelta ) > ScrolledSignalType;

  /**
   * @brief Signal emitted when the text is scrolled inside the text-view.
   *
   * A callback with the following prototype can be connected to this signal.
   *
   * Callback(TextView textView, Vector2 scrollDelta)
   *
   * \e textView is the handle of the text-view emitting the signal.
   * \e scrollDelta is the differente of the current scroll position with the previous one.
   * @return The signal to connect to
   */
  ScrolledSignalType& ScrolledSignal();

public: // Not intended for application developers

  /**
   * @brief Creates a handle using the Toolkit::Internal implementation.
   * @note Not intended for application developers
   *
   * @param[in]  implementation  The Control implementation.
   */
  DALI_INTERNAL TextView( Internal::TextView& implementation );

  /**
   * @brief Allows the creation of this Control from an Internal::CustomActor pointer.
   * @note Not intended for application developers
   *
   * @param[in]  internal  A pointer to the internal CustomActor.
   */
  explicit DALI_INTERNAL TextView( Dali::Internal::CustomActor* internal );
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_ITEM_VIEW_H__
