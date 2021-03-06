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
#include "toolkit-imf-manager.h"

// EXTERNAL INCLUDES
#include <dali/public-api/object/base-object.h>
#include <dali/integration-api/debug.h>

namespace Dali
{
namespace Internal
{
namespace Adaptor
{
class RenderSurface;


class ImfManager : public Dali::BaseObject
{
public:
  typedef Dali::ImfManager::ImfManagerSignalType ImfManagerSignalType;
  typedef Dali::ImfManager::ImfEventSignalType ImfEventSignalType;

public:
  static Dali::ImfManager Get();

  ImfManager( /* Ecore_X_Window ecoreXwin */ );
  void ConnectCallbacks();
  void DisconnectCallbacks();
  void Activate();
  void Deactivate();
  void Reset();

  bool RestoreAfterFocusLost() const;
  void SetRestoreAfterFocusLost( bool toggle );
  void NotifyCursorPosition();
  void SetCursorPosition( unsigned int cursorPosition );
  unsigned int GetCursorPosition() const;
  void SetSurroundingText( const std::string& text );
  const std::string& GetSurroundingText() const;

public:  // Signals
  ImfManagerSignalType& ActivatedSignal() { return mActivatedSignal; }
  ImfEventSignalType& EventReceivedSignal() { return mEventSignal; }

protected:
  virtual ~ImfManager();

private:
  void CreateContext( /*Ecore_X_Window ecoreXwin*/ );
  void DeleteContext();

private:
  // Undefined
  ImfManager( const ImfManager& );
  ImfManager& operator=( ImfManager& );

private:
  int mIMFCursorPosition;
  std::string mSurroundingText;
  bool mRestoreAfterFocusLost:1;             ///< Whether the keyboard needs to be restored (activated ) after focus regained.
  bool mIdleCallbackConnected:1;             ///< Whether the idle callback is already connected.

  ImfManagerSignalType      mActivatedSignal;
  ImfEventSignalType        mEventSignal;


  static Dali::ImfManager mToolkitImfManager;

public:

inline static Internal::Adaptor::ImfManager& GetImplementation(Dali::ImfManager& imfManager)
{
  Dali::ImfManager actualImfManager = ImfManager::Get();

  BaseObject& handle = actualImfManager.GetBaseObject();
  return static_cast<Internal::Adaptor::ImfManager&>(handle);
}

inline static const  Internal::Adaptor::ImfManager& GetImplementation(const Dali::ImfManager& imfManager)
{
  Dali::ImfManager actualImfManager = ImfManager::Get();

  const BaseObject& handle = imfManager.GetBaseObject();
  return static_cast<const Internal::Adaptor::ImfManager&>(handle);
}

};

Dali::ImfManager Dali::Internal::Adaptor::ImfManager::mToolkitImfManager;

Dali::ImfManager ImfManager::Get()
{
  Dali::ImfManager manager;

  if( ! mToolkitImfManager )
  {
    mToolkitImfManager = Dali::ImfManager( new Dali::Internal::Adaptor::ImfManager() );
  }
  return mToolkitImfManager;
}

ImfManager::ImfManager( /*Ecore_X_Window ecoreXwin*/ )
: mIMFCursorPosition( 0 ),
  mSurroundingText(),
  mRestoreAfterFocusLost( false ),
  mIdleCallbackConnected( false )
{
  CreateContext( /*ecoreXwin*/ );
  ConnectCallbacks();
}

ImfManager::~ImfManager()
{
  DisconnectCallbacks();
  DeleteContext();
}

void ImfManager::CreateContext( /*Ecore_X_Window ecoreXwin*/ )
{
}

void ImfManager::DeleteContext()
{
}

// Callbacks for predicitive text support.
void ImfManager::ConnectCallbacks()
{
}

void ImfManager::DisconnectCallbacks()
{
}

void ImfManager::Activate()
{
}

void ImfManager::Deactivate()
{
}

void ImfManager::Reset()
{
}

bool ImfManager::RestoreAfterFocusLost() const
{
  return mRestoreAfterFocusLost;
}

void ImfManager::SetRestoreAfterFocusLost( bool toggle )
{
  mRestoreAfterFocusLost = toggle;
}

void ImfManager::NotifyCursorPosition()
{
}

void ImfManager::SetCursorPosition( unsigned int cursorPosition )
{
  mIMFCursorPosition = static_cast< int >( cursorPosition );
}

unsigned int ImfManager::GetCursorPosition() const
{
  return static_cast<unsigned int>( mIMFCursorPosition );
}

void ImfManager::SetSurroundingText( const std::string& text )
{
  mSurroundingText = text;
}

const std::string& ImfManager::GetSurroundingText() const
{
  return mSurroundingText;
}

} // Adaptor

} // Internal


/********************************************************************************/
/*********************************  PUBLIC CLASS  *******************************/
/********************************************************************************/

ImfManager::ImfManager()
{
}

ImfManager::~ImfManager()
{
}

ImfManager ImfManager::Get()
{
  return Internal::Adaptor::ImfManager::Get();
}

void ImfManager::Activate()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Activate();
}

void ImfManager::Deactivate()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Deactivate();
}

bool ImfManager::RestoreAfterFocusLost() const
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).RestoreAfterFocusLost();
}

void ImfManager::SetRestoreAfterFocusLost( bool toggle )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetRestoreAfterFocusLost( toggle );
}

void ImfManager::Reset()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Reset();
}

void ImfManager::NotifyCursorPosition()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).NotifyCursorPosition();
}

void ImfManager::SetCursorPosition( unsigned int SetCursorPosition )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetCursorPosition( SetCursorPosition );
}

unsigned int ImfManager::GetCursorPosition() const
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).GetCursorPosition();
}

void ImfManager::SetSurroundingText( const std::string& text )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetSurroundingText( text );
}

const std::string& ImfManager::GetSurroundingText() const
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).GetSurroundingText();
}

void ImfManager::NotifyTextInputMultiLine( bool multiLine )
{
}

ImfManager::ImfManagerSignalType& ImfManager::ActivatedSignal()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).ActivatedSignal();
}

ImfManager::ImfEventSignalType& ImfManager::EventReceivedSignal()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).EventReceivedSignal();
}

ImfManager::ImfManager(Internal::Adaptor::ImfManager *impl)
  : BaseHandle(impl)
{
}

} // namespace Dali
