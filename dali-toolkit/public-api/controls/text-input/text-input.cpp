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

// CLASS HEADER
#include <dali-toolkit/public-api/controls/text-input/text-input.h>

// EXTERNAL INCLUDES
#include <dali/public-api/actors/mesh-actor.h>
#include <dali/public-api/adaptor-framework/clipboard.h>
#include <dali/public-api/adaptor-framework/clipboard-event-notifier.h>
#include <dali/public-api/adaptor-framework/imf-manager.h>
#include <dali/public-api/adaptor-framework/timer.h>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/text-input/text-input.h>
#include <dali-toolkit/internal/controls/text-input/text-input-impl.h>

namespace Dali
{

namespace Toolkit
{

TextInput::TextInput()
{
}

TextInput::TextInput(Internal::TextInput& implementation)
: Control(implementation)
{
}

TextInput::TextInput( const TextInput& textInput )
: Control( textInput )
{
}

TextInput& TextInput::operator=( const TextInput& textInput )
{
  if( &textInput != this )
  {
    Control::operator=( textInput );
  }

  return *this;
}

TextInput TextInput::New()
{
  return Internal::TextInput::New();
}

TextInput TextInput::DownCast( BaseHandle actor )
{
  return Control::DownCast<TextInput, Internal::TextInput>(actor);
}

TextInput::~TextInput()
{
}

std::string TextInput::GetText() const
{
  return GetImpl(*this).GetText();
}

std::string TextInput::GetMarkupText() const
{
  return GetImpl(*this).GetMarkupText();
}

void TextInput::SetMaxCharacterLength(std::size_t maxChars)
{
  GetImpl(*this).SetMaxCharacterLength(maxChars);
}

void TextInput::SetNumberOfLinesLimit(std::size_t maxLines)
{
  GetImpl(*this).SetNumberOfLinesLimit( maxLines );
}

std::size_t TextInput::GetNumberOfLinesLimit() const
{
  return GetImpl(*this).GetNumberOfLinesLimit();
}

std::size_t TextInput::GetNumberOfCharacters() const
{
  return GetImpl(*this).GetNumberOfCharacters();
}

void TextInput::SetPlaceholderText( const std::string& placeHolderText )
{
  GetImpl(*this).SetPlaceholderText( placeHolderText );
}

std::string TextInput::GetPlaceholderText()
{
  return GetImpl(*this).GetPlaceholderText();
}

void TextInput::SetInitialText(const std::string& initialText)
{
  GetImpl(*this).SetInitialText(initialText);
}

void TextInput::SetEditable(bool editMode)
{
  GetImpl(*this).SetEditable(editMode, false);
}

void TextInput::SetEditable(bool editMode, const Vector2& touchPoint)
{
  GetImpl(*this).SetEditable(editMode, true, touchPoint);
}

bool TextInput::IsEditable() const
{
  return GetImpl(*this).IsEditable();
}

void TextInput::SetEditOnTouch( bool editOnTouch )
{
  GetImpl(*this).SetEditOnTouch( editOnTouch );
}

bool TextInput::IsEditOnTouch() const
{
  return GetImpl(*this).IsEditOnTouch();
}

void TextInput::SetTextSelectable( bool textSelectable )
{
  GetImpl(*this).SetTextSelectable( textSelectable );
}

bool TextInput::IsTextSelectable() const
{
  return GetImpl(*this).IsTextSelectable();
}

bool TextInput::IsTextSelected() const
{
  return GetImpl(*this).IsTextSelected();
}

void TextInput::SelectText(std::size_t start, std::size_t end)
{
  GetImpl(*this).SelectText( start, end );
}

void TextInput::DeSelectText()
{
  GetImpl(*this).DeSelectText();
}

void TextInput::SetGrabHandleImage( Image image )
{
  GetImpl(*this).SetGrabHandleImage(image);
}

void TextInput::SetCursorImage(Dali::Image image, const Vector4& border )
{
  GetImpl(*this).SetCursorImage(image, border );
}

Vector3 TextInput::GetSelectionHandleSize()
{
  return GetImpl(*this).GetSelectionHandleSize();
}

void TextInput::SetRTLCursorImage(Dali::Image image, const Vector4& border )
{
  GetImpl(*this).SetRTLCursorImage(image, border );
}

void TextInput::EnableGrabHandle(bool toggle)
{
  GetImpl(*this).EnableGrabHandle( toggle );
}

bool TextInput::IsGrabHandleEnabled()
{
  return GetImpl(*this).IsGrabHandleEnabled();
}

void TextInput::SetBoundingRectangle( const Rect<float>& boundingOriginAndSize )
{
  GetImpl(*this).SetBoundingRectangle( boundingOriginAndSize );
}

const Rect<float> TextInput::GetBoundingRectangle() const
{
  return GetImpl(*this).GetBoundingRectangle();
}

void TextInput::SetActiveStyle( const TextStyle& style, const TextStyle::Mask mask )
{
  GetImpl(*this).SetActiveStyle(style,mask);
}

void TextInput::ApplyStyle( const TextStyle& style, const TextStyle::Mask mask )
{
  GetImpl(*this).ApplyStyle( style, mask );
}

void TextInput::ApplyStyleToAll( const TextStyle& style, const TextStyle::Mask mask )
{
  GetImpl(*this).ApplyStyleToAll( style, mask );
}

TextStyle TextInput::GetStyleAtCursor() const
{
  return GetImpl(*this).GetStyleAtCursor();
}

void TextInput::SetTextAlignment( Toolkit::Alignment::Type align )
{
  GetImpl(*this).SetTextAlignment(align);
}

void TextInput::SetTextLineJustification( Toolkit::TextView::LineJustification justification )
{
  GetImpl(*this).SetTextLineJustification(justification);
}

void TextInput::SetFadeBoundary( const Toolkit::TextView::FadeBoundary& fadeBoundary )
{
  GetImpl(*this).SetFadeBoundary( fadeBoundary );
}

const Toolkit::TextView::FadeBoundary& TextInput::GetFadeBoundary() const
{
  return GetImpl(*this).GetFadeBoundary();
}

Alignment::Type TextInput::GetTextAlignment() const
{
  return GetImpl(*this).GetTextAlignment();
}

void TextInput::SetMultilinePolicy( TextView::MultilinePolicy policy )
{
  GetImpl(*this).SetMultilinePolicy(policy);
}

TextView::MultilinePolicy TextInput::GetMultilinePolicy() const
{
  return GetImpl(*this).GetMultilinePolicy();
}

void TextInput::SetWidthExceedPolicy( TextView::ExceedPolicy policy )
{
  GetImpl(*this).SetWidthExceedPolicy(policy);
}

TextView::ExceedPolicy TextInput::GetWidthExceedPolicy() const
{
  return GetImpl(*this).GetWidthExceedPolicy();
}

void TextInput::SetHeightExceedPolicy( TextView::ExceedPolicy policy )
{
  GetImpl(*this).SetHeightExceedPolicy(policy);
}

TextView::ExceedPolicy TextInput::GetHeightExceedPolicy() const
{
  return GetImpl(*this).GetHeightExceedPolicy();
}

void TextInput::SetExceedEnabled( bool enable )
{
  GetImpl(*this).SetExceedEnabled( enable );
}

bool TextInput::GetExceedEnabled() const
{
  return GetImpl(*this).GetExceedEnabled();
}

void TextInput::SetSortModifier( float depthOffset )
{
  GetImpl( *this ).SetSortModifier( depthOffset );
}

void TextInput::SetSnapshotModeEnabled( bool enable )
{
  GetImpl( *this ).SetSnapshotModeEnabled( enable );
}

bool TextInput::IsSnapshotModeEnabled() const
{
  return GetImpl( *this ).IsSnapshotModeEnabled();
}

void TextInput::SetScrollEnabled( bool enable )
{
  GetImpl( *this ).SetScrollEnabled( enable );
}

bool TextInput::IsScrollEnabled() const
{
  return GetImpl( *this ).IsScrollEnabled();
}

void TextInput::SetScrollPosition( const Vector2& position )
{
  GetImpl( *this ).SetScrollPosition( position );
}

Vector2 TextInput::GetScrollPosition() const
{
  return GetImpl( *this ).GetScrollPosition();
}

TextInput::InputSignalType& TextInput::InputStartedSignal()
{
  return GetImpl(*this).InputStartedSignal();
}

TextInput::InputSignalType& TextInput::InputFinishedSignal()
{
  return GetImpl(*this).InputFinishedSignal();
}

TextInput::InputSignalType& TextInput::CutAndPasteToolBarDisplayedSignal()
{
  return GetImpl(*this).CutAndPasteToolBarDisplayedSignal();
}

TextInput::StyleChangedSignalType& TextInput::StyleChangedSignal()
{
  return GetImpl(*this).StyleChangedSignal();
}

TextInput::TextModifiedSignalType& TextInput::TextModifiedSignal()
{
  return GetImpl(*this).TextModifiedSignal();
}

TextInput::MaxInputCharactersReachedSignalType& TextInput::MaxInputCharactersReachedSignal()
{
  return GetImpl(*this).MaxInputCharactersReachedSignal();
}

TextInput::InputTextExceedBoundariesSignalType& TextInput::InputTextExceedBoundariesSignal()
{
  return GetImpl(*this).InputTextExceedBoundariesSignal();
}

void TextInput::SetMarkupProcessingEnabled( bool enable )
{
  return GetImpl( *this ).SetMarkupProcessingEnabled( enable );
}

bool TextInput::IsMarkupProcessingEnabled() const
{
  return GetImpl( *this ).IsMarkupProcessingEnabled();
}


TextInput::TextInput( Dali::Internal::CustomActor* internal )
: Control( internal )
{
  VerifyCustomActorPointer<Internal::TextInput>(internal);
}

} // namespace Toolkit

} // namespace Dali
