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

#include <iostream>

#include <stdlib.h>
#include <limits>

#include <dali-toolkit-test-suite-utils.h>
#include <dali-toolkit/dali-toolkit.h>
#include <dali-toolkit/internal/text/text-controller.h>

using namespace Dali;
using namespace Toolkit;
using namespace Text;

namespace
{

const char* const OPTION_SELECT_WORD("option-select_word"); // "Select Word" popup option.
const char* const OPTION_SELECT_ALL("option-select_all");   // "Select All" popup option.
const char* const OPTION_CUT("optionCut");                  // "Cut" popup option.
const char* const OPTION_COPY("optionCopy");                // "Copy" popup option.
const char* const OPTION_PASTE("optionPaste");              // "Paste" popup option.
const char* const OPTION_CLIPBOARD("optionClipboard");      // "Clipboard" popup option.

const Size CONTROL_SIZE( 300.f, 60.f );

class ControlImpl : public ControlInterface
{
public:
  ControlImpl()
  : ControlInterface()
  {}

  virtual ~ControlImpl()
  {}

  virtual void AddDecoration( Actor& actor, bool needsClipping )
  {}

  virtual void RequestTextRelayout()
  {}

  virtual void TextChanged()
  {}

  virtual void MaxLengthReached()
  {}

  virtual void InputStyleChanged( InputStyle::Mask inputStyleMask )
  {}
};

std::string gClipboardText;
void ContentSelectedCallback( ClipboardEventNotifier& notifier )
{
  gClipboardText = notifier.GetContent();
}

} // namespace

int UtcDaliTextController(void)
{
  tet_infoline(" UtcDaliTextController");
  ToolkitTestApplication application;

  // Creates a text controller.
  ControlImpl controlImpl;
  ControllerPtr controller = Controller::New( controlImpl );

  DALI_TEST_CHECK( controller );

  tet_result(TET_PASS);
  END_TEST;
}

int UtcDaliTextControllerEnableCursorBlinking(void)
{
  tet_infoline(" UtcDaliTextControllerEnableCursorBlinking");
  ToolkitTestApplication application;

  // Creates a text controller.
  ControlImpl controlImpl;
  ControllerPtr controller = Controller::New( controlImpl );

  DALI_TEST_CHECK( controller );

  // There is no text input enabled.
  DALI_TEST_CHECK( !controller->GetEnableCursorBlink() );

  // Enable the text input.
  // Creates a decorator.
  Text::DecoratorPtr decorator = Text::Decorator::New( *controller,
                                                       *controller );

  // Enables the text input.
  controller->EnableTextInput( decorator );

  // Enables the cursor blink.
  controller->SetEnableCursorBlink( true );

  DALI_TEST_CHECK( controller->GetEnableCursorBlink() );

  // Disables the cursor blink.
  controller->SetEnableCursorBlink( false );

  DALI_TEST_CHECK( !controller->GetEnableCursorBlink() );

  tet_result(TET_PASS);
  END_TEST;
}

int UtcDaliTextControllerImfEvent(void)
{
  tet_infoline(" UtcDaliTextController");
  ToolkitTestApplication application;

  // Creates a text controller.
  ControlImpl controlImpl;
  ControllerPtr controller = Controller::New( controlImpl );

  std::string text;
  ImfManager::ImfEventData imfEvent;

  DALI_TEST_CHECK( controller );

  // Enable the text input.
  // Creates a decorator.
  Text::DecoratorPtr decorator = Text::Decorator::New( *controller,
                                                       *controller );

  // Enables the text input.
  controller->EnableTextInput( decorator );

  // Creates an ImfManager.
  ImfManager imfManager = ImfManager::Get();

  // Send VOID event.
  imfEvent = ImfManager::ImfEventData( ImfManager::VOID, "", 0, 0 );
  controller->OnImfEvent( imfManager, imfEvent );

  controller->GetText( text );
  DALI_TEST_CHECK( text.empty() );

  // Send COMMIT event.
  imfEvent = ImfManager::ImfEventData( ImfManager::COMMIT, "Hello ", 0, 6 );
  controller->OnImfEvent( imfManager, imfEvent );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_EQUALS( "Hello ", text, TEST_LOCATION );

  // Send PREEDIT event
  imfEvent = ImfManager::ImfEventData( ImfManager::PREEDIT, "w", 6, 1 );
  controller->OnImfEvent( imfManager, imfEvent );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_EQUALS( "Hello w", text, TEST_LOCATION );

  // Send DELETESURROUNDING event
  imfEvent = ImfManager::ImfEventData( ImfManager::DELETESURROUNDING, "", -1, 1 );
  controller->OnImfEvent( imfManager, imfEvent );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_EQUALS( "Hello ", text, TEST_LOCATION );

  // Send PREEDIT event
  imfEvent = ImfManager::ImfEventData( ImfManager::PREEDIT, "wo", 6, 2 );
  controller->OnImfEvent( imfManager, imfEvent );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_EQUALS( "Hello wo", text, TEST_LOCATION );

  // Send GETSURROUNDING event
  imfEvent = ImfManager::ImfEventData( ImfManager::GETSURROUNDING, "", 0, 0 );
  controller->OnImfEvent( imfManager, imfEvent );

  controller->GetText( text );
  DALI_TEST_EQUALS( "Hello wo", text, TEST_LOCATION );

  tet_result(TET_PASS);
  END_TEST;
}

int UtcDaliTextControllerTextPopupButtonTouched(void)
{
  tet_infoline(" UtcDaliTextControllerTextPopupButtonTouched");
  ToolkitTestApplication application;

  // Creates a text controller.
  ControlImpl controlImpl;
  ControllerPtr controller = Controller::New( controlImpl );

  DALI_TEST_CHECK( controller );

  std::string text;
  PushButton button;
  Property::Map attributes;

  // Enable the text input.
  // Creates a decorator.
  Text::DecoratorPtr decorator = Text::Decorator::New( *controller,
                                                       *controller );

  // Enables the text input.
  controller->EnableTextInput( decorator );

  // Creates the text's popup.
  TextSelectionPopupCallbackInterface& callbackInterface = *controller;
  TextSelectionPopup textPopup = TextSelectionPopup::New( &callbackInterface );

  Toolkit::TextSelectionPopup::Buttons buttonsToEnable = static_cast<Toolkit::TextSelectionPopup::Buttons>( TextSelectionPopup::CUT        |
                                                                                                            TextSelectionPopup::COPY       |
                                                                                                            TextSelectionPopup::PASTE      |
                                                                                                            TextSelectionPopup::SELECT     |
                                                                                                            TextSelectionPopup::SELECT_ALL |
                                                                                                            TextSelectionPopup::CLIPBOARD );

  textPopup.EnableButtons( buttonsToEnable );
  Stage::GetCurrent().Add( textPopup );
  textPopup.ShowPopup();

  // Render and notify
  application.SendNotification();
  application.Render();

  // Sets some text.
  controller->SetText( "Hello world" );

  // Select the whole text.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_SELECT_ALL ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Call relayout to process the input events.
  controller->Relayout( CONTROL_SIZE );

  // Cut the text.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_CUT ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_CHECK( text.empty() );

  // Set text again.
  controller->SetText( "Hello world" );

  // Select the whole text.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_SELECT_ALL ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Call relayout to process the input events.
  controller->Relayout( CONTROL_SIZE );

  // Copy to the clipboard.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_COPY ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Call relayout to process the input events.
  controller->Relayout( CONTROL_SIZE );

  // Cut the text.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_CUT ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Force to update the model.
  controller->GetNaturalSize();

  controller->GetText( text );
  DALI_TEST_CHECK( text.empty() );

  ClipboardEventNotifier clipboardEventNotifier = ClipboardEventNotifier::Get();
  clipboardEventNotifier.ContentSelectedSignal().Connect( &ContentSelectedCallback );

  // Paste the text.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_PASTE ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  // Call relayout to process the input events.
  controller->Relayout( CONTROL_SIZE );

  DALI_TEST_EQUALS( "Hello world", gClipboardText, TEST_LOCATION );

  // Show the clipboard.
  button = PushButton::DownCast( textPopup.FindChildByName( OPTION_CLIPBOARD ) );
  DALI_TEST_CHECK( button );

  button.DoAction( "buttonClick", attributes );

  tet_result(TET_PASS);
  END_TEST;
}
