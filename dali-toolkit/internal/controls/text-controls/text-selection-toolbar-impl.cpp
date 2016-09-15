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

// CLASS HEADER
#include <dali-toolkit/internal/controls/text-controls/text-selection-toolbar-impl.h>

// EXTERNAL INCLUDES
#include <cfloat>
#include <dali/public-api/images/buffer-image.h>
#include <dali/public-api/math/vector2.h>
#include <dali/public-api/math/vector4.h>
#include <dali/public-api/object/property-map.h>
#include <dali/public-api/object/type-registry-helper.h>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/image-view/image-view.h>
#include <dali-toolkit/devel-api/controls/control-depth-index-ranges.h>

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
  return Toolkit::TextSelectionToolbar::New();
}

// Setup properties, signals and actions using the type-registry.

DALI_TYPE_REGISTRATION_BEGIN( Toolkit::TextSelectionToolbar, Toolkit::Control, Create );

DALI_PROPERTY_REGISTRATION( Toolkit, TextSelectionToolbar, "maxSize",  VECTOR2, MAX_SIZE )
DALI_PROPERTY_REGISTRATION( Toolkit, TextSelectionToolbar, "enableOvershoot",  BOOLEAN, ENABLE_OVERSHOOT )
DALI_PROPERTY_REGISTRATION( Toolkit, TextSelectionToolbar, "scrollView",  MAP, SCROLL_VIEW )

DALI_TYPE_REGISTRATION_END()

} // namespace

Dali::Toolkit::TextSelectionToolbar TextSelectionToolbar::New()
{
  // Create the implementation, temporarily owned by this handle on stack
  IntrusivePtr< TextSelectionToolbar > impl = new TextSelectionToolbar();

  // Pass ownership to CustomActor handle
  Dali::Toolkit::TextSelectionToolbar handle( *impl );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  impl->Initialize();

  return handle;
}

void TextSelectionToolbar::SetProperty( BaseObject* object, Property::Index index, const Property::Value& value )
{
  Toolkit::TextSelectionToolbar selectionPopup = Toolkit::TextSelectionToolbar::DownCast( Dali::BaseHandle( object ) );

  if( selectionPopup )
  {
    TextSelectionToolbar& impl( GetImpl( selectionPopup ) );

    switch( index )
    {
      case Toolkit::TextSelectionToolbar::Property::MAX_SIZE:
      {
       impl.SetPopupMaxSize( value.Get< Vector2 >() );
       break;
      }
      case Toolkit::TextSelectionToolbar::Property::ENABLE_OVERSHOOT:
      {
        if( !impl.mScrollView )
        {
          impl.mScrollView  = Toolkit::ScrollView::New();
        }
        impl.mScrollView.SetOvershootEnabled( value.Get< bool >() );
        break;
      }
      case Toolkit::TextSelectionToolbar::Property::SCROLL_VIEW:
      {
        // Get a Property::Map from the property if possible.
        Property::Map setPropertyMap;
        if( value.Get( setPropertyMap ) )
        {
          impl.ConfigureScrollview( setPropertyMap );
        }
        break;
      }
    } // switch
  } // TextSelectionToolbar
}

Property::Value TextSelectionToolbar::GetProperty( BaseObject* object, Property::Index index )
{
  Property::Value value;

  Toolkit::TextSelectionToolbar selectionPopup = Toolkit::TextSelectionToolbar::DownCast( Dali::BaseHandle( object ) );

  if( selectionPopup )
  {
    TextSelectionToolbar& impl( GetImpl( selectionPopup ) );

    switch( index )
    {
      case Toolkit::TextSelectionToolbar::Property::MAX_SIZE:
      {
        value = impl.GetPopupMaxSize();
        break;
      }
      case Toolkit::TextSelectionToolbar::Property::ENABLE_OVERSHOOT:
      {
        value = impl.mScrollView.IsOvershootEnabled();
        break;
      }
    } // switch
  }
  return value;
}

void TextSelectionToolbar::OnInitialize()
{
  SetUp();
}

void TextSelectionToolbar::OnRelayout( const Vector2& size, RelayoutContainer& container )
{
  float width = std::max ( mTableOfButtons.GetNaturalSize().width, size.width );
  mRulerX->SetDomain( RulerDomain( 0.0, width, true ) );
  mScrollView.SetRulerX( mRulerX );
}

void TextSelectionToolbar::OnStageConnection( int depth )
{
  // Call the Control::OnStageConnection() to set the depth of the background.
  Control::OnStageConnection( depth );

  // Texts are controls, they have their own OnStageConnection() implementation.
  // Icons are inside a TableView. It has it's own OnStageConnection() implementation.
}

void TextSelectionToolbar::SetPopupMaxSize( const Size& maxSize )
{
  mMaxSize = maxSize;
  if (mScrollView && mToolbarLayer )
  {
    mScrollView.SetMaximumSize( mMaxSize );
    mToolbarLayer.SetMaximumSize( mMaxSize );
  }
}

const Dali::Vector2& TextSelectionToolbar::GetPopupMaxSize() const
{
  return mMaxSize;
}

void TextSelectionToolbar::SetUpScrollView()
{
  mScrollView.SetResizePolicy( ResizePolicy::FIT_TO_CHILDREN, Dimension::ALL_DIMENSIONS );
  mScrollView.SetParentOrigin( ParentOrigin::CENTER_LEFT );
  mScrollView.SetAnchorPoint( AnchorPoint::CENTER_LEFT );

  mScrollView.SetScrollingDirection( PanGestureDetector::DIRECTION_HORIZONTAL, Degree( 40.0f ) );
  mScrollView.SetAxisAutoLock( true );
  mScrollView.ScrollStartedSignal().Connect( this, &TextSelectionToolbar::OnScrollStarted );
  mScrollView.ScrollCompletedSignal().Connect( this, &TextSelectionToolbar::OnScrollCompleted );

  mRulerX = new DefaultRuler();  // IntrusivePtr which is unreferenced when ScrollView is destroyed.

  RulerPtr rulerY = new DefaultRuler();  // IntrusivePtr which is unreferenced when ScrollView is destroyed.
  rulerY->Disable();
  mScrollView.SetRulerY( rulerY );

  mScrollView.SetOvershootEnabled( true );
}

void TextSelectionToolbar::SetUp()
{
  Actor self = Self();

  self.SetResizePolicy( ResizePolicy::FIT_TO_CHILDREN, Dimension::ALL_DIMENSIONS );

  // Create Layer to house the toolbar.
  mToolbarLayer = Layer::New();
  mToolbarLayer.SetResizePolicy( ResizePolicy::FIT_TO_CHILDREN, Dimension::ALL_DIMENSIONS );
  mToolbarLayer.SetAnchorPoint( AnchorPoint::CENTER );
  mToolbarLayer.SetParentOrigin( ParentOrigin::CENTER );

  if( !mScrollView )
  {
    mScrollView = Toolkit::ScrollView::New();
  }
  SetUpScrollView();

  // Toolbar must start with at least one option, adding further options with increase it's size
  mTableOfButtons = Dali::Toolkit::TableView::New( 1, 1 );
  mTableOfButtons.SetFitHeight( 0 );
  mTableOfButtons.SetParentOrigin( ParentOrigin::CENTER_LEFT );
  mTableOfButtons.SetAnchorPoint( AnchorPoint::CENTER_LEFT );

  mScrollView.Add( mTableOfButtons );
  mToolbarLayer.Add( mScrollView );

  self.Add( mToolbarLayer );
}

void TextSelectionToolbar::OnScrollStarted( const Vector2& position )
{
  mTableOfButtons.SetSensitive( false );
}

void TextSelectionToolbar::OnScrollCompleted( const Vector2& position )
{
  mTableOfButtons.SetSensitive( true );
}

void TextSelectionToolbar::AddOption( Actor& option )
{
  mTableOfButtons.AddChild( option, Toolkit::TableView::CellPosition( 0, mIndexInTable )  );
  mTableOfButtons.SetFitWidth( mIndexInTable );
  mIndexInTable++;
}

void TextSelectionToolbar::AddDivider( Actor& divider )
{
  AddOption( divider );
  mDividerIndexes.PushBack( mIndexInTable - 1u );
}

void TextSelectionToolbar::ResizeDividers( Size& size )
{
  for( unsigned int i = 0; i < mDividerIndexes.Count(); ++i )
  {
    Actor divider = mTableOfButtons.GetChildAt( Toolkit::TableView::CellPosition( 0, mDividerIndexes[ i ] ) );
    divider.SetSize( size );
  }
  RelayoutRequest();
}

void TextSelectionToolbar::RaiseAbove( Layer target )
{
  mToolbarLayer.RaiseAbove( target );
}

void TextSelectionToolbar::ConfigureScrollview( const Property::Map& properties )
{
  // Set any properties specified for the label by iterating through all property key-value pairs.
  for( unsigned int i = 0, mapCount = properties.Count(); i < mapCount; ++i )
  {
    const StringValuePair& propertyPair( properties.GetPair( i ) );

    // Convert the property string to a property index.
    Property::Index setPropertyIndex = mScrollView.GetPropertyIndex( propertyPair.first );
    if( setPropertyIndex != Property::INVALID_INDEX )
    {
      // If the conversion worked, we have a valid property index,
      // Set the property to the new value.
      mScrollView.SetProperty( setPropertyIndex, propertyPair.second );
    }
  }

  RelayoutRequest();
}


TextSelectionToolbar::TextSelectionToolbar()
: Control( ControlBehaviour( ControlBehaviour( REQUIRES_STYLE_CHANGE_SIGNALS ) ) ),
  mMaxSize (),
  mIndexInTable( 0 ),
  mDividerIndexes()
{
}

TextSelectionToolbar::~TextSelectionToolbar()
{
  mRulerX.Reset();
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
