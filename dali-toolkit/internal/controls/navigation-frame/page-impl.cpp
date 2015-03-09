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
#include "page-impl.h"

// EXTERNAL INCLUDES
#include <dali/public-api/object/type-registry.h>
#include <dali/public-api/object/type-registry-helper.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace
{

BaseHandle Create()
{
  return Toolkit::Page::New();
}

DALI_TYPE_REGISTRATION_BEGIN( Toolkit::Page, Toolkit::Control, Create )
DALI_TYPE_REGISTRATION_END()

} // unnamed namespace

Page::Page()
: Control( CONTROL_BEHAVIOUR_NONE ),
  mTitle(""),
  mSubTitle(""),
  mPropertyTitle(Property::INVALID_INDEX),
  mPropertySubTitle(Property::INVALID_INDEX)
{
}

Page::~Page()
{
  Toolkit::Page::ControlOnBarContainer::const_iterator iter;

  if( !mToolBarControls.empty() )
  {
    for( iter = mToolBarControls.begin(); iter != mToolBarControls.end(); iter++ )
    {
      delete( *iter );
    }
  }

}

Toolkit::Page Page::New()
{
  // Create the implementation, temporarily owned by this handle on stack
  IntrusivePtr< Page > internalpage = new Page();

  // Pass ownership to CustomActor handle
  Toolkit::Page page( *internalpage );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  internalpage->Initialize();

  return page;

}

void Page::SetTitle(const std::string& title)
{
  mTitle = title;
}

const std::string& Page::GetTitle() const
{
  return mTitle;
}

void Page::SetSubTitle(const std::string& subtitle)
{
  mSubTitle = subtitle;
}

const std::string& Page::GetSubTitle() const
{
  return mSubTitle;
}

void Page::SetTitleIcon( Actor titleIcon)
{
  mTitleIcon = titleIcon;
}

Actor Page::GetTitleIcon() const
{
  return mTitleIcon;
}

bool Page::AddControlToToolBar(Actor control, Toolkit::Alignment::Type alignment)
{
  if( !control || ( alignment!=Toolkit::Alignment::HorizontalLeft
                 && alignment!=Toolkit::Alignment::HorizontalCenter
                 && alignment!=Toolkit::Alignment::HorizontalRight ) )
  {
    return false;
  }
  else
  {
    mToolBarControls.push_back(new Toolkit::Page::ControlOnBar(control, alignment));
    return true;
  }
}

const Toolkit::Page::ControlOnBarContainer& Page::GetControlsOnToolBar() const
{
  return mToolBarControls;
}

bool Page::AddControlToTitleBar(Actor control)
{
  if( !control )
  {
    return false;
  }
  else
  {
    mTitleBarControls.push_back(control);
    return true;
  }
}

const ActorContainer& Page::GetControlsOnTitleBar() const
{
  return mTitleBarControls;
}

void Page::SetPopupMenu( Toolkit::Popup popupMenu )
{
  mPopupMenu = popupMenu;
}

Toolkit::Popup Page::GetPopupMenu() const
{
  return mPopupMenu;
}

void Page::OnInitialize()
{
  Actor self = Self();

  mPropertyTitle = self.RegisterProperty( Dali::Toolkit::Page::PROPERTY_TITLE, "", Property::READ_WRITE );
  mPropertySubTitle = self.RegisterProperty( Dali::Toolkit::Page::PROPERTY_SUB_TITLE, "", Property::READ_WRITE );
}

void Page::OnPropertySet( Property::Index index, Property::Value propertyValue )
{
  if( index == mPropertyTitle )
  {
    std::string title( propertyValue.Get<std::string>() );
    SetTitle(title);
  }
  else if( index == mPropertySubTitle )
  {
    std::string subTitle( propertyValue.Get<std::string>() );
    SetSubTitle(subTitle);
  }
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
