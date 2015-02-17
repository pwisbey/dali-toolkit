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

// FILE HEADER
#include <dali-toolkit/internal/controls/text-view/split-by-new-line-char-policies.h>

// INTERNAL INCLUDES
#include <dali/integration-api/debug.h>
#include <dali-toolkit/internal/controls/text-view/relayout-utilities.h>
#include <dali-toolkit/internal/controls/text-view/text-view-processor.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace SplitByNewLineChar
{

namespace
{

Vector3 SplitPosition( const TextViewRelayout::RelayoutParameters& relayoutParameters,
                       const TextView::LayoutParameters& layoutParameters,
                       TextView::RelayoutData& relayoutData )
{
  const float wordOffset = ( relayoutParameters.mIsFirstCharacter ? 0.f : relayoutParameters.mPositionOffset.x );
  const float previousPositionY = ( relayoutParameters.mIsFirstCharacter ? 0.f : relayoutParameters.mPositionOffset.y );

  if( relayoutParameters.mIsNewLine ||
      relayoutParameters.mIsFirstCharacter ||
      ( wordOffset + relayoutParameters.mCharacterSize.width > relayoutData.mTextViewSize.width ) )
  {
    if( !relayoutParameters.mIsNewLine &&
        ( relayoutParameters.mIsWhiteSpace || relayoutParameters.mIsNewParagraphCharacter ) )
    {
      // Current character is a white space. Don't want to move a white space to the next line.
      // These white spaces are placed just in the edge.
      return Vector3( relayoutData.mTextViewSize.width - relayoutParameters.mWordSize.width, relayoutParameters.mPositionOffset.y, 0.f );
    }
    else
    {
      const TextViewProcessor::ParagraphLayoutInfo& paragraphLayoutInfo( *( relayoutData.mTextLayoutInfo.mParagraphsLayoutInfo.begin() + relayoutParameters.mIndices.mParagraphIndex ) );

      TextViewRelayout::LineLayoutInfo subLineInfo;
      subLineInfo.mLineLength = 0.f;
      subLineInfo.mMaxCharHeight = 0.f;
      subLineInfo.mMaxAscender = 0.f;
      TextViewRelayout::CalculateLineLayout( relayoutData.mTextViewSize.width,
                                             relayoutParameters.mIndices,
                                             paragraphLayoutInfo,
                                             TextViewRelayout::WrapByParagraphCharacterAndSplit,
                                             1.f, // Shrink factor
                                             subLineInfo );

      Toolkit::TextView::LineLayoutInfo lineInfo;
      lineInfo.mCharacterGlobalIndex = relayoutParameters.mCharacterGlobalIndex;    // Index to the first character of the next line.
      lineInfo.mSize = Size( subLineInfo.mLineLength, subLineInfo.mMaxCharHeight ); // Size of this piece of paragraph.
      lineInfo.mAscender = subLineInfo.mMaxAscender;                                // Ascender of this piece of paragraph.
      relayoutData.mLines.push_back( lineInfo );

      return Vector3( 0.f, previousPositionY + subLineInfo.mMaxCharHeight + layoutParameters.mLineHeightOffset, 0.f );
    }
  }
  else
  {
    return Vector3( wordOffset, previousPositionY, 0.f );
  }
}

void CalculateSizeAndPosition( const TextView::LayoutParameters& layoutParameters,
                               TextView::RelayoutData& relayoutData )
{
  // clear
  relayoutData.mCharacterLayoutInfoTable.clear();
  relayoutData.mLines.clear();
  relayoutData.mTextSizeForRelayoutOption = Size();
  relayoutData.mShrinkFactor = 1.f;

  // Calculates the text size for split by char.
  Vector4 minMaxXY( std::numeric_limits<float>::max(),
                    std::numeric_limits<float>::max(),
                    std::numeric_limits<float>::min(),
                    std::numeric_limits<float>::min() );

  TextViewRelayout::RelayoutParameters relayoutParameters;

  if( TextView::ShrinkOriginal == layoutParameters.mExceedPolicy )
  {
    if( relayoutData.mTextLayoutInfo.mWholeTextSize.width > relayoutData.mTextViewSize.width )
    {
      relayoutData.mShrinkFactor = relayoutData.mTextViewSize.width / relayoutData.mTextLayoutInfo.mWholeTextSize.width;
    }
  }
  else if( TextView::Shrink == layoutParameters.mExceedPolicy )
  {
    if( ( relayoutData.mTextLayoutInfo.mWholeTextSize.width > relayoutData.mTextViewSize.width ) ||
        ( relayoutData.mTextLayoutInfo.mWholeTextSize.height > relayoutData.mTextViewSize.height ) )
    {
      relayoutData.mShrinkFactor = std::min( relayoutData.mTextViewSize.width / relayoutData.mTextLayoutInfo.mWholeTextSize.width,
                                             relayoutData.mTextViewSize.height / relayoutData.mTextLayoutInfo.mWholeTextSize.height );
    }
  }

  relayoutParameters.mIsFirstCharacter = true;
  relayoutParameters.mIndices.mParagraphIndex = 0u;
  relayoutParameters.mPositionOffset = Vector3::ZERO;
  relayoutParameters.mCharacterGlobalIndex = 0u;

  for( TextViewProcessor::ParagraphLayoutInfoContainer::iterator paragraphLayoutIt = relayoutData.mTextLayoutInfo.mParagraphsLayoutInfo.begin(),
       endParagraphLayoutIt = relayoutData.mTextLayoutInfo.mParagraphsLayoutInfo.end();
       paragraphLayoutIt != endParagraphLayoutIt;
       ++paragraphLayoutIt, ++relayoutParameters.mIndices.mParagraphIndex )
  {
    TextViewProcessor::ParagraphLayoutInfo& paragraphLayoutInfo( *paragraphLayoutIt );

    relayoutParameters.mParagraphSize = paragraphLayoutInfo.mSize * relayoutData.mShrinkFactor;

    relayoutParameters.mIsNewLine = true;
    relayoutParameters.mIndices.mWordIndex = 0u;

    for( TextViewProcessor::WordLayoutInfoContainer::iterator wordLayoutIt = paragraphLayoutInfo.mWordsLayoutInfo.begin(),
           endWordLayoutIt = paragraphLayoutInfo.mWordsLayoutInfo.end();
         wordLayoutIt != endWordLayoutIt;
         ++wordLayoutIt, ++relayoutParameters.mIndices.mWordIndex )
    {
      TextViewProcessor::WordLayoutInfo& wordLayoutInfo( *wordLayoutIt );
      relayoutParameters.mIsWhiteSpace = TextViewProcessor::WordSeparator == wordLayoutInfo.mType;
      relayoutParameters.mIsNewParagraphCharacter = TextViewProcessor::ParagraphSeparator == wordLayoutInfo.mType;

      relayoutParameters.mIsFirstCharacterOfWord = true;
      relayoutParameters.mWordSize = wordLayoutInfo.mSize;
      relayoutParameters.mIndices.mCharacterIndex = 0u;

      for( TextViewProcessor::CharacterLayoutInfoContainer::iterator characterLayoutIt = wordLayoutInfo.mCharactersLayoutInfo.begin(),
             endCharacterLayoutIt = wordLayoutInfo.mCharactersLayoutInfo.end();
           characterLayoutIt != endCharacterLayoutIt;
           ++characterLayoutIt, ++relayoutParameters.mIndices.mCharacterIndex )
      {
        TextViewProcessor::CharacterLayoutInfo& characterLayoutInfo( *characterLayoutIt );
        relayoutParameters.mCharacterSize = characterLayoutInfo.mSize;

        relayoutParameters.mCharacterSize = characterLayoutInfo.mSize;

        switch( layoutParameters.mExceedPolicy )
        {
          case TextView::OriginalShrink:
          case TextView::SplitShrink:
          case TextView::ShrinkFade: // Fall Through
          {
            DALI_LOG_WARNING( "SplitByNewLineChar::CalculateSizeAndPosition() policy not implemented.\n" );
            break;
          }
          case TextView::Original: // Fall Through
          case TextView::ShrinkOriginal: // Fall Through
          case TextView::Shrink: // Fall Through
          case TextView::OriginalFade: // Fall Through
          case TextView::FadeOriginal: // Fall Through
          case TextView::Fade: // Fall Through
          case TextView::EllipsizeEndOriginal: // Fall Through
          case TextView::EllipsizeEnd: // Fall Through
          {
            if( relayoutParameters.mIsNewLine )
            {
              relayoutParameters.mPositionOffset.x = 0.f;
              relayoutParameters.mPositionOffset.y += paragraphLayoutInfo.mSize.height * relayoutData.mShrinkFactor;
            }

            characterLayoutInfo.mPosition = relayoutParameters.mPositionOffset;

            relayoutParameters.mPositionOffset.x += characterLayoutInfo.mSize.width * relayoutData.mShrinkFactor;

            if( relayoutParameters.mIsNewLine ||
                relayoutParameters.mIsFirstCharacter )
            {
              Toolkit::TextView::LineLayoutInfo lineInfo;
              lineInfo.mCharacterGlobalIndex = relayoutParameters.mCharacterGlobalIndex;       // Index to the first character of the next line.
              lineInfo.mSize = relayoutParameters.mParagraphSize;                              // Size of this piece of paragraph.
              lineInfo.mAscender = paragraphLayoutInfo.mAscender * relayoutData.mShrinkFactor; // Ascender of this piece of paragraph.
              relayoutData.mLines.push_back( lineInfo );
            }
            break;
          }
          case TextView::SplitOriginal:
          case TextView::SplitFade:
          case TextView::SplitEllipsizeEnd: // Fall Through
          {
            characterLayoutInfo.mPosition = SplitPosition( relayoutParameters,
                                                           layoutParameters,
                                                           relayoutData );

            relayoutParameters.mPositionOffset = characterLayoutInfo.mPosition + Vector3( characterLayoutInfo.mSize.width, 0.f, 0.f );
            break;
          }
          default:
          {
            DALI_LOG_WARNING( "SplitByNewLineChar::CalculateSizeAndPosition() Layout configuration not possible.\n" );
            break;
          }
        }

        // Get last line info and calculate the bearing (used to align glyphs with the baseline).
        TextViewRelayout::CalculateBearing( characterLayoutInfo, relayoutData );

        // updates min and max position to calculate the text size for split by new line char.
        TextViewRelayout::UpdateLayoutInfoTable( minMaxXY,
                                                 wordLayoutInfo,
                                                 characterLayoutInfo,
                                                 relayoutParameters,
                                                 relayoutData );

        ++relayoutParameters.mCharacterGlobalIndex;
        relayoutParameters.mIsFirstCharacter = false;
        relayoutParameters.mIsNewLine = false;
      } // end characters
    } // end words
  } // end paragraphs

  if( relayoutData.mCharacterLayoutInfoTable.empty() )
  {
    relayoutData.mTextSizeForRelayoutOption = Size();
  }
  else
  {
    relayoutData.mTextSizeForRelayoutOption.width = minMaxXY.z - minMaxXY.x;
    relayoutData.mTextSizeForRelayoutOption.height = minMaxXY.w - minMaxXY.y;
  }

  // Check if the last character is a new paragraph character. In that case the height should be added.
  if( !relayoutData.mTextLayoutInfo.mParagraphsLayoutInfo.empty() )
  {
    const TextViewProcessor::ParagraphLayoutInfo& paragraphLayoutInfo( *( relayoutData.mTextLayoutInfo.mParagraphsLayoutInfo.end() - 1u ) );

    if( paragraphLayoutInfo.mWordsLayoutInfo.empty() ) // if it's empty, it means the last character is a new paragraph character.
    {
      relayoutData.mTextSizeForRelayoutOption.height += paragraphLayoutInfo.mSize.height * relayoutData.mShrinkFactor;
    }
  }
}

} // namespace

void Relayout( Actor textView,
               TextView::RelayoutOperationMask relayoutOperationMask,
               const TextView::LayoutParameters& layoutParameters,
               const TextView::VisualParameters& visualParameters,
               TextView::RelayoutData& relayoutData )
{
  if( relayoutOperationMask & TextView::RELAYOUT_SIZE_POSITION )
  {
    CalculateSizeAndPosition( layoutParameters,
                              relayoutData );

    TextViewRelayout::ReorderRightToLeftLayout( relayoutData );

    TextViewRelayout::SetUnderlineInfo( relayoutData );
  }

  if( relayoutOperationMask & TextView::RELAYOUT_ALIGNMENT )
  {
    TextViewRelayout::UpdateAlignment( layoutParameters,
                                       relayoutData );
  }

  if( relayoutOperationMask & TextView::RELAYOUT_VISIBILITY )
  {
    TextViewRelayout::UpdateVisibility( layoutParameters,
                                        visualParameters,
                                        relayoutData );
  }

  const bool initializeTextActors = relayoutOperationMask & TextView::RELAYOUT_INITIALIZE_TEXT_ACTORS;
  const bool updateTextActors = relayoutOperationMask & TextView::RELAYOUT_TEXT_ACTOR_UPDATE;
  if( initializeTextActors || updateTextActors )
  {
    TextViewRelayout::UpdateTextActorInfo( visualParameters,
                                           relayoutData,
                                           initializeTextActors );
  }

  if( relayoutOperationMask & TextView::RELAYOUT_INSERT_TO_TEXT_VIEW )
  {
    TextViewRelayout::InsertToTextView( textView,
                                        relayoutData );
  }
}

} // namespace SplitByNewLineChar

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
