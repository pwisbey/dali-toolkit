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

#include <iostream>
#include <stdlib.h>
#include <dali-toolkit-test-suite-utils.h>
#include <dali-toolkit/dali-toolkit.h>
#include <dali/integration-api/events/touch-event-integ.h>
#include <dali/integration-api/events/pan-gesture-event.h>

using namespace Dali;
using namespace Toolkit;

void scroll_view_startup(void)
{
  test_return_value = TET_UNDEF;
}

void scroll_view_cleanup(void)
{
  test_return_value = TET_PASS;
}

namespace
{
static bool gObjectCreatedCallBackCalled;

static void TestCallback(BaseHandle handle)
{
  gObjectCreatedCallBackCalled = true;
}


const int MILLISECONDS_PER_SECOND = 1000;
const int RENDER_FRAME_INTERVAL = 16;                           ///< Duration of each frame in ms. (at approx 60FPS)
const int RENDER_ANIMATION_TEST_DURATION_MS = 1000;             ///< 1000ms to test animation
const int RENDER_DELAY_SCROLL = 1000;                           ///< duration to wait for any scroll to complete.

// For Clamp Signal testing...
const float CLAMP_EXCESS_WIDTH = 200.0f;                        ///< Amount of width that can be panned outside scrollview
const float CLAMP_EXCESS_HEIGHT = 200.0f;                       ///< Amount of height that can be panned outside scrollview
const int CLAMP_STEP_0_CHECK_NOTCLAMPED = 0;                    ///< FSM: "First check that scrollview isn't clamped"
const int CLAMP_STEP_1_CHECK_CLAMPED_WEST = 1;                  ///< FSM: "Next check that scrollview clamps against left side"
const int CLAMP_STEP_2_CHECK_CLAMPED_SOUTH_WEST = 2;            ///< FSM: "Then check that scrollview clamps against bottom-left side"
const int CLAMP_STEP_3_SUCCESS = 3;                             ///< FSM: "Finished (Success)"
const Vector3 CLAMP_START_SCROLL_POSITION(30.0f, 100.0f, 0.0f); ///< Scroll start position for the Clamping tests.
const Vector2 CLAMP_TOUCH_START( 100.0f, 100.0f );              ///< Start point to touch from for the Clamping tests.
const Vector2 CLAMP_TOUCH_MOVEMENT( 5.0f, -5.0f );              ///< Amount to move touch for each frame for the Clamping tests.
const int CLAMP_GESTURE_FRAMES = 100;                           ///< Number of Frames to synthesize a gesture for the Clamping tests.
const Vector3 TEST_ACTOR_POSITION(100.0f, 100.0f, 0.0f);        ///< A Test actor position offset (arbitrary value)
const Vector3 TEST_CONSTRAINT_OFFSET(1.0f, 2.0f, 0.0f);         ///< A Test constraint offset (arbitrary value to test effects)
const float TEST_RATIO_TOLERANCE = 0.05;                        ///< +/-5% tolerance for ratio comparisons.

const int MAX_FRAMES_TO_TEST_OVERSHOOT = 600;                         ///< 10 seconds (at 60 frames per second).
const Vector3 OVERSHOOT_START_SCROLL_POSITION(100.0f, 100.0f, 0.0f);  ///< Scroll start position for the Overshoot tests.
const float TEST_CUSTOM1_SNAP_OVERSHOOT_DURATION = 0.05f;             ///< a Test duration
const float TEST_CUSTOM2_SNAP_OVERSHOOT_DURATION = 1.5f;              ///< another Test duration
const float TEST_CUSTOM3_SNAP_OVERSHOOT_DURATION = TEST_CUSTOM2_SNAP_OVERSHOOT_DURATION * 0.5f; // Same as above, but different alpha function.
const float TIME_TOLERANCE = 0.05f;                                   ///< Allow testing tolerance between a 10th of second (+/- 3 frames)


// Generate a PanGestureEvent to send to Core
Integration::PanGestureEvent GeneratePan(
    Gesture::State state,
    const Vector2& previousPosition,
    const Vector2& currentPosition,
    unsigned long timeDelta,
    unsigned int numberOfTouches = 1)
{
  Integration::PanGestureEvent pan(state);

  pan.previousPosition = previousPosition;
  pan.currentPosition = currentPosition;
  pan.timeDelta = timeDelta;
  pan.numberOfTouches = numberOfTouches;

  return pan;
}

/**
 * Helper to generate PanGestureEvent
 *
 * @param[in] application Application instance
 * @param[in] state The Gesture State
 * @param[in] pos The current position of touch.
 */
static void SendPan(ToolkitTestApplication& application, Gesture::State state, const Vector2& pos)
{
  static Vector2 last;

  if( (state == Gesture::Started) ||
      (state == Gesture::Possible) )
  {
    last.x = pos.x;
    last.y = pos.y;
  }

  application.ProcessEvent(GeneratePan(state, last, pos, RENDER_FRAME_INTERVAL));

  last.x = pos.x;
  last.y = pos.y;
}

/*
 * Simulate time passed by.
 *
 * @note this will always process at least 1 frame (1/60 sec)
 *
 * @param application Test application instance
 * @param duration Time to pass in milliseconds.
 * @return The actual time passed in milliseconds
 */
int Wait(ToolkitTestApplication& application, int duration = 0)
{
  int time = 0;

  for(int i = 0; i <= ( duration / RENDER_FRAME_INTERVAL); i++)
  {
    application.SendNotification();
    application.Render(RENDER_FRAME_INTERVAL);
    time += RENDER_FRAME_INTERVAL;
  }

  return time;
}

// Callback probes.

static bool gOnScrollStartCalled;                       ///< Whether the OnScrollStart signal was invoked.
static bool gOnScrollUpdateCalled;                      ///< Whether the OnScrollUpdate signal was invoked.
static bool gOnScrollCompleteCalled;                    ///< Whether the OnScrollComplete signal was invoked.
static bool gOnSnapStartCalled;                         ///< Whether the OnSnapStart signal was invoked.
static SnapType gLastSnapType;                          ///< Snaping information from SnapEvent.
static Vector3 gConstraintResult;                       ///< Result from constraint.

/**
 * Invoked when scrolling starts.
 *
 * @param[in] position The current scroll position.
 */
static void OnScrollStart( const Vector3& position )
{
  gOnScrollStartCalled = true;
}

/**
 * Invoked when scrolling updates (via dragging)
 *
 * @param[in] position The current scroll position.
 */
static void OnScrollUpdate( const Vector3& position )
{
  gOnScrollUpdateCalled = true;
}

/**
 * Invoked when scrolling finishes
 *
 * @param[in] position The current scroll position.
 */
static void OnScrollComplete( const Vector3& position )
{
  gOnScrollCompleteCalled = true;
}

/**
 * Invoked when a snap or flick started.
 *
 * @param[in] event The type of snap and the target position/scale/rotation.
 */
static void OnSnapStart( const ScrollView::SnapEvent& event )
{
  gOnSnapStartCalled = true;
  gLastSnapType = event.type;
}

/**
 * TestSumConstraint
 *
 * Summation of current value, property, and offset.
 *
 * current' = current + mOffset + property;
 */
struct TestSumConstraint
{
  /**
   * @param[in] offset The offset to be added to current.
   */
  TestSumConstraint(const Vector3& offset)
  :mOffset(offset)
  {
  }

  /**
   * @param[in] current The current base value
   * @param[in] property The property to be added to current.
   * @return The new current Vector.
   */
  Vector3 operator()(const Vector3& current)
  {
    gConstraintResult = current + mOffset;
    return gConstraintResult;
  }

  /**
   * @param[in] current The current base value
   * @param[in] property The property to be added to current.
   * @return The new current Vector.
   */
  Vector3 operator()(const Vector3&    current,
                    const PropertyInput& property)
  {
    gConstraintResult = current + property.GetVector3() + mOffset;
    return gConstraintResult;
  }

  Vector3 mOffset;

};

/**
 * @param[in] application The application instance
 * @param[in] scrollView The scrollView instance
 * @return The time taken for the overshoot to reach origin (zero)
 */
static float TestOvershootSnapDuration(ToolkitTestApplication &application, ScrollView scrollView)
{
  Property::Index overshootPropertyX = scrollView.GetPropertyIndex(ScrollView::SCROLL_OVERSHOOT_X_PROPERTY_NAME);
  Property::Index overshootPropertyY = scrollView.GetPropertyIndex(ScrollView::SCROLL_OVERSHOOT_Y_PROPERTY_NAME);

  int timeToReachOrigin = -1;
  for(int i = 0;i<MAX_FRAMES_TO_TEST_OVERSHOOT;i++)
  {
    float overshootXValue = scrollView.GetProperty<float>(overshootPropertyX);
    float overshootYValue = scrollView.GetProperty<float>(overshootPropertyY);
    if(overshootXValue == 0.0f && overshootYValue == 0.0f)
    {
      break;
    }

    timeToReachOrigin += Wait(application);
  }

  return static_cast<float>(timeToReachOrigin) * 0.001f; // return in seconds not ms.
}

/**
 * y = 2x alpha function, which is clamped between 0.0f - 1.0f
 *
 * Animations should appear to finish (reach 100% point)
 * at just half the time of a regular Linear AlphaFunction.
 *
 * @param[in] progress value (ranges from 0.0f - 1.0f)
 * @return interpolation value (ranges from 0.0f - 1.0f)
 */
float TestAlphaFunction(float progress)
{
  return std::min( progress * 2.0f, 1.0f );
}

} // unnamed namespace


int UtcDaliScrollViewNew(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewNew");

  ScrollView scrollView;

  DALI_TEST_CHECK( !scrollView );

  scrollView = ScrollView::New();

  DALI_TEST_CHECK( scrollView );

  ScrollView scrollView2(scrollView);

  DALI_TEST_CHECK( scrollView2 == scrollView );

  //Additional check to ensure object is created by checking if it's registered
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );

  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect( &TestCallback );
  {
    ScrollView scrollView = ScrollView::New();
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
  END_TEST;
}

int UtcDaliScrollViewDownCast(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewDownCast");

  ScrollView scrollView = ScrollView::New();
  BaseHandle handle(scrollView);

  ScrollView newScrollView = ScrollView::DownCast( handle );
  DALI_TEST_CHECK( scrollView );
  DALI_TEST_CHECK( newScrollView == scrollView );
  END_TEST;
}

int UtcDaliScrollViewScrollToPosition(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewScrollToPosition");

  // Create the ScrollView actor
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );

  const Vector3 target = Vector3(100.0f, 200.0f, 0.0f);
  const Vector3 target2 = Vector3(300.0f, 100.0f, 0.0f);

  scrollView.ScrollTo( target, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), target, TEST_LOCATION );
  scrollView.ScrollTo( target2 );
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), target2, TEST_LOCATION );

  Wait(application);
  END_TEST;
}

int UtcDaliScrollViewScrollToPage(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewScrollToPage");

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  RulerPtr rulerX = new FixedRuler( 100.0f );
  rulerX->SetDomain( RulerDomain(0.0f, 800.0f, true) );
  RulerPtr rulerY = new FixedRuler( 100.0f );
  rulerY->SetDomain( RulerDomain(0.0f, 400.0f, true) );

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );

  scrollView.ScrollTo( 1, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(100.0f, 0.0f, 0.0f), TEST_LOCATION );

  scrollView.ScrollTo( 5, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(500.0f, 0.0f, 0.0f), TEST_LOCATION );

  scrollView.ScrollTo( 10, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(200.0f, 100.0f, 0.0f), TEST_LOCATION );

  scrollView.ScrollTo( 15, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(700.0f, 100.0f, 0.0f), TEST_LOCATION );
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 15, TEST_LOCATION );

  scrollView.ScrollTo( 3 );
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(300.0f, 0.0f, 0.0f), TEST_LOCATION );
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 3, TEST_LOCATION );

  scrollView.ScrollTo( 9 );
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(100.0f, 100.0f, 0.0f), TEST_LOCATION );
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 9, TEST_LOCATION );

  // Apply DefaultRulers instead and see what happens.
  rulerX = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, 800.0f, true) );
  rulerY = new DefaultRuler();
  rulerY->SetDomain( RulerDomain(0.0f, 400.0f, true) );

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );

  // This time should always scroll to origin (0.0f, 0.0f)
  scrollView.ScrollTo( 1, 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(0.0f, 0.0f, 0.0f), TEST_LOCATION );
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 0, TEST_LOCATION );

  Wait(application);
  END_TEST;
}

int UtcDaliScrollViewScrollToActor(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewScrollToActor");

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );

  Actor actorA = Actor::New();
  const Vector3 positionA = Vector3(100.0f, 400.0f, 0.0f);
  actorA.SetPosition(positionA);
  scrollView.Add(actorA);

  Actor actorB = Actor::New();
  const Vector3 positionB = Vector3(500.0f, 200.0f, 0.0f);
  actorB.SetPosition(positionB);
  scrollView.Add(actorB);

  Wait(application);

  scrollView.ScrollTo(actorA, 0.0f);
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), positionA, TEST_LOCATION );

  Wait(application);
  scrollView.ScrollTo(actorB, 0.0f);
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), positionB, TEST_LOCATION );

  scrollView.ScrollTo(actorA);
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), positionA, TEST_LOCATION );

  scrollView.ScrollTo(actorB);
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), positionB, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewScrollToSnapPoint(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewScrollToSnapPoint");

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  RulerPtr rulerX = new FixedRuler( 100.0f );
  rulerX->SetDomain( RulerDomain(0.0f, 800.0f, true) );
  RulerPtr rulerY = new FixedRuler( 100.0f );
  rulerY->SetDomain( RulerDomain(0.0f, 400.0f, true) );

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );

  scrollView.ScrollTo( Vector3(120.0f, 190.0f, 0.0f), 0.0f );
  Wait(application);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(120.0f, 190.0f, 0.0f), TEST_LOCATION );

  scrollView.ScrollToSnapPoint();

  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), Vector3(100.0f, 200.0f, 0.0f), TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewSetScrollUpdateDistance(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewRefreshInterval");

  ScrollView scrollView = ScrollView::New();

  scrollView.SetScrollUpdateDistance(0);
  DALI_TEST_EQUALS( scrollView.GetScrollUpdateDistance(), 0, TEST_LOCATION);
  scrollView.SetScrollUpdateDistance(10);
  DALI_TEST_EQUALS( scrollView.GetScrollUpdateDistance(), 10, TEST_LOCATION);
  scrollView.SetScrollUpdateDistance(1000);
  DALI_TEST_EQUALS( scrollView.GetScrollUpdateDistance(), 1000, TEST_LOCATION);
  END_TEST;
}

int UtcDaliScrollViewWrapMode(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewWrapMode");

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );

  // Position rulers. 4x4 grid.
  RulerPtr rulerX = new FixedRuler(50.0f);
  RulerPtr rulerY = new FixedRuler(50.0f);
  rulerX->SetDomain( RulerDomain(0.0f, 200.0f, false) );
  rulerY->SetDomain( RulerDomain(0.0f, 200.0f, false) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);

  scrollView.SetWrapMode(false);
  scrollView.ScrollTo(Vector3(225.0f, 125.0f, 0.0f), 0.0f); // 5th (1st) page across, and 3rd (3rd) page down. (wrapped)
  Wait(application);
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 17, TEST_LOCATION );
  scrollView.SetWrapMode(true);
  DALI_TEST_EQUALS( static_cast<int>(scrollView.GetCurrentPage()), 13, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewActorAutoSnap(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewActorAutoSnap");

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  rulerY->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);

  const Vector3 aPosition = Vector3(200.0f, 50.0f, 0.0f);
  Actor a = Actor::New();
  scrollView.Add(a);
  a.SetPosition(aPosition);

  const Vector3 bPosition = Vector3(600.0f, 600.0f, 0.0f);
  Actor b = Actor::New();
  scrollView.Add(b);
  b.SetPosition(bPosition);

  // Goto a random position, and execute snap (should not move)
  Vector3 targetScroll = Vector3(500.0f, 500.0f, 0.0f);
  scrollView.ScrollTo(targetScroll, 0.0f);
  Wait(application);
  scrollView.ScrollToSnapPoint();
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), targetScroll, TEST_LOCATION );

  // Enable ActorAutoSnap, and now try snapping.
  scrollView.SetActorAutoSnap(true);
  scrollView.ScrollToSnapPoint();
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), bPosition, TEST_LOCATION );

  scrollView.ScrollTo(Vector3(0.0f, 0.0f, 0.0f), 0.0f);
  Wait(application);
  scrollView.ScrollToSnapPoint();
  Wait(application, RENDER_DELAY_SCROLL);
  DALI_TEST_EQUALS( scrollView.GetCurrentScrollPosition(), aPosition, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewSignalsStartComplete(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSignalsStartComplete");

  gOnScrollStartCalled = false;
  gOnScrollCompleteCalled = false;

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  rulerY->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );
  scrollView.ScrollTo( Vector3(100.0f, 100.0f, 0.0f) );
  Wait(application, RENDER_DELAY_SCROLL);

  DALI_TEST_CHECK(gOnScrollStartCalled);
  DALI_TEST_CHECK(gOnScrollCompleteCalled);
  END_TEST;
}

int UtcDaliScrollViewSignalsUpdate(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSignalsUpdate");

  gOnScrollStartCalled = false;
  gOnScrollUpdateCalled = false;
  gOnScrollCompleteCalled = false;

  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  rulerY->SetDomain( RulerDomain(0.0f, 1000.0f, false) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );

  ImageActor image = CreateSolidColorActor( Color::RED );
  image.SetSize(stageSize);
  image.SetParentOrigin(ParentOrigin::TOP_LEFT);
  image.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  scrollView.Add(image);

  Wait(application);

  // Do a pan starting from 100,100 and moving down diagonally.
  Vector2 pos(100.0f, 100.0f);
  SendPan(application, Gesture::Possible, pos);
  SendPan(application, Gesture::Started, pos);
  pos.x += 5.0f;
  pos.y += 5.0f;
  Wait(application, 100);

  for(int i = 0;i<20;i++)
  {
    SendPan(application, Gesture::Continuing, pos);
    pos.x += 5.0f;
    pos.y += 5.0f;
    Wait(application);
  }

  SendPan(application, Gesture::Finished, pos);
  Wait(application, RENDER_DELAY_SCROLL);

  DALI_TEST_CHECK(gOnScrollStartCalled);
  DALI_TEST_CHECK(gOnScrollUpdateCalled);
  DALI_TEST_CHECK(gOnScrollCompleteCalled);
  END_TEST;
}

static Vector2 PerformGestureDiagonalSwipe(ToolkitTestApplication& application, Vector2 start, Vector2 direction, int frames, bool finish = true)
{
  gOnScrollStartCalled = false;
  gOnScrollUpdateCalled = false;
  gOnScrollCompleteCalled = false;
  gOnSnapStartCalled = false;

  // Now do a pan starting from (start) and heading (direction)
  Vector2 pos(start);
  SendPan(application, Gesture::Possible, pos);
  SendPan(application, Gesture::Started, pos);
  Wait(application);

  for(int i = 0;i<frames;i++)
  {
    pos += direction; // Move in this direction
    SendPan(application, Gesture::Continuing, pos);
    Wait(application);
  }

  if(finish)
  {
    pos += direction; // Move in this direction.
    SendPan(application, Gesture::Finished, pos);
    Wait(application, RENDER_DELAY_SCROLL);
  }

  return pos;
}

int UtcDaliScrollViewScrollSensitive(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewScrollSensitive");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );
  scrollView.SnapStartedSignal().Connect( &OnSnapStart );

  scrollView.ScrollTo(CLAMP_START_SCROLL_POSITION, 0.0f); // move in a little.
  Wait(application);

  // First try insensitive swipe.
  scrollView.SetScrollSensitive(false);
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, CLAMP_TOUCH_MOVEMENT, CLAMP_GESTURE_FRAMES, true);

  DALI_TEST_CHECK( !gOnScrollStartCalled );
  DALI_TEST_CHECK( !gOnScrollCompleteCalled );
  DALI_TEST_CHECK( !gOnSnapStartCalled );

  // Second try sensitive swipe.
  scrollView.SetScrollSensitive(true);
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, CLAMP_TOUCH_MOVEMENT, CLAMP_GESTURE_FRAMES, true);

  DALI_TEST_CHECK( gOnScrollStartCalled );
  DALI_TEST_CHECK( gOnScrollCompleteCalled );
  DALI_TEST_CHECK( gOnSnapStartCalled );
  END_TEST;
}

int UtcDaliScrollViewTouchesRequired(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewTouchesRequired");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );
  scrollView.SnapStartedSignal().Connect( &OnSnapStart );

  scrollView.ScrollTo(CLAMP_START_SCROLL_POSITION, 0.0f); // move in a little.
  Wait(application);

  // First try touches required being a minimum and maximum of 2.
  scrollView.SetTouchesRequiredForPanning(2, 2, true);
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, CLAMP_TOUCH_MOVEMENT, CLAMP_GESTURE_FRAMES, true);

  DALI_TEST_CHECK( !gOnScrollStartCalled );
  DALI_TEST_CHECK( !gOnScrollUpdateCalled );
  DALI_TEST_CHECK( !gOnScrollCompleteCalled );
  DALI_TEST_CHECK( !gOnSnapStartCalled );

  scrollView.ScrollTo(CLAMP_START_SCROLL_POSITION, 0.0f); // move in a little.
  Wait(application);

  // Second try touches required being a minimum and maximum of 1.
  scrollView.SetTouchesRequiredForPanning(1, 1, true);
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, CLAMP_TOUCH_MOVEMENT * 0.1f, CLAMP_GESTURE_FRAMES * 0.1f, true);

  DALI_TEST_CHECK( gOnScrollStartCalled );
  DALI_TEST_CHECK( gOnScrollUpdateCalled );
  DALI_TEST_CHECK( gOnScrollCompleteCalled );
  DALI_TEST_CHECK( gOnSnapStartCalled );
  END_TEST;
}

int UtcDaliScrollViewAxisAutoLock(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewAxisAutoLock");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );

  // Normal
  scrollView.ScrollTo(Vector3(100.0f, 100.0f, 0.0f), 0.0f); // move in a little.
  Wait(application);
  Vector3 startPosition = scrollView.GetCurrentScrollPosition();
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, Vector2(5.0f, 1.0f), 50, true); // mostly horizontal
  const Vector3 positionAfterNormal = scrollView.GetCurrentScrollPosition();

  // Autolock
  scrollView.SetAxisAutoLock(true);
  DALI_TEST_CHECK(scrollView.GetAxisAutoLock());

  scrollView.ScrollTo(Vector3(100.0f, 100.0f, 0.0f), 0.0f); // move in a little.
  Wait(application);
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, Vector2(5.0f, 1.0f), 50, true); // mostly horizontal
  const Vector3 positionAfterAutoLock = scrollView.GetCurrentScrollPosition();

  // compare how much the Y position has deviated for normal and autolock.
  const float devianceNormal = fabsf(startPosition.y - positionAfterNormal.y);
  const float devianceAutoLock = fabsf(startPosition.y - positionAfterAutoLock.y);

  // in auto-lock it should be a mostly horizontal pan (thus deviance should be much lower)
  DALI_TEST_CHECK(devianceAutoLock < devianceNormal);

  scrollView.SetAxisAutoLock(false);
  DALI_TEST_CHECK(!scrollView.GetAxisAutoLock());
  END_TEST;
}

int UtcDaliScrollViewAxisAutoLockGradient(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewAxisAutoLockGradient");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  scrollView.SetAxisAutoLockGradient(0.5f);
  DALI_TEST_EQUALS(scrollView.GetAxisAutoLockGradient(), 0.5f, TEST_LOCATION);
  scrollView.SetAxisAutoLockGradient(1.0f);
  DALI_TEST_EQUALS(scrollView.GetAxisAutoLockGradient(), 1.0f, TEST_LOCATION);
  END_TEST;
}

int UtcDaliScrollViewConstraints(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewConstraints");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);

  // Add an Actor to ScrollView,
  // Apply TestSumConstraint to ScrollView's children (includes this Actor)
  gConstraintResult = Vector3::ZERO;
  Actor a = Actor::New();
  scrollView.Add(a);
  a.SetPosition( TEST_ACTOR_POSITION );
  Wait(application);

  Property::Index scrollPositionProperty = scrollView.GetPropertyIndex(ScrollView::SCROLL_POSITION_PROPERTY_NAME);
  Constraint constraint = Constraint::New<Vector3>( Actor::POSITION,
                                                       Source(scrollView, scrollPositionProperty),
                                                       TestSumConstraint( TEST_CONSTRAINT_OFFSET ) );
  constraint.SetRemoveAction(Constraint::Discard);
  scrollView.ApplyConstraintToChildren(constraint);
  Wait(application);

  DALI_TEST_EQUALS( gConstraintResult, TEST_ACTOR_POSITION + TEST_CONSTRAINT_OFFSET, TEST_LOCATION );

  gConstraintResult = Vector3::ZERO;
  scrollView.RemoveConstraintsFromChildren();
  Wait(application);

  DALI_TEST_EQUALS( gConstraintResult, Vector3::ZERO, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewBind(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewBind");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);

  // Add an Actor to ScrollView,
  // Apply TestSumConstraint to ScrollView's children (includes this Actor)

  gConstraintResult = Vector3::ZERO;
  Actor a = Actor::New();
  scrollView.Add(a);
  a.SetPosition( TEST_ACTOR_POSITION );
  Wait(application);

  Property::Index scrollPositionProperty = scrollView.GetPropertyIndex(ScrollView::SCROLL_POSITION_PROPERTY_NAME);
  // apply this constraint to scrollview
  Constraint constraint = Constraint::New<Vector3>( Actor::POSITION,
                                                       Source(scrollView, scrollPositionProperty),
                                                       TestSumConstraint( TEST_CONSTRAINT_OFFSET ) );

  constraint.SetRemoveAction(Constraint::Discard);
  scrollView.ApplyConstraintToChildren(constraint);

  Wait(application);
  // Defaulty Bound.
  DALI_TEST_EQUALS( gConstraintResult, TEST_ACTOR_POSITION + TEST_CONSTRAINT_OFFSET, TEST_LOCATION );

  // UnBind
  gConstraintResult = Vector3::ZERO;
  scrollView.UnbindActor( a );
  Wait(application);
  DALI_TEST_EQUALS( gConstraintResult, Vector3::ZERO, TEST_LOCATION );

  // Bind
  gConstraintResult = Vector3::ZERO;
  scrollView.BindActor( a );
  Wait(application);
  DALI_TEST_EQUALS( gConstraintResult, TEST_ACTOR_POSITION + TEST_CONSTRAINT_OFFSET, TEST_LOCATION );
  END_TEST;
}

int UtcDaliRulerEnableDisable(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliRulerEnableDisable");

  RulerPtr ruler = new DefaultRuler();

  DALI_TEST_CHECK( ruler->IsEnabled() );
  ruler->Disable();
  DALI_TEST_CHECK( !ruler->IsEnabled() );
  ruler->Enable();
  DALI_TEST_CHECK( ruler->IsEnabled() );
  END_TEST;
}

int UtcDaliRulerDomainEnableDisable(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliRulerDomainEnableDisable");

  RulerPtr ruler = new DefaultRuler();
  DALI_TEST_EQUALS( ruler->GetDomain().GetSize(), 1.0f, TEST_LOCATION );


  ruler->SetDomain( RulerDomain(0.0f, 100.0f, true) );
  DALI_TEST_EQUALS( ruler->GetDomain().GetSize(), 100.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->Clamp(-200.0f), 0.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->Clamp(200.0f), 100.0f, TEST_LOCATION );

  ruler->DisableDomain();
  DALI_TEST_EQUALS( ruler->GetDomain().GetSize(), 1.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->Clamp(-200.0f), -200.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->Clamp(200.0f), 200.0f, TEST_LOCATION );
  END_TEST;
}

int UtcDaliRulerSnapAndClamp(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliRulerSnapAndClamp");

  RulerPtr ruler = new FixedRuler( 50.0f );
  ruler->SetDomain( RulerDomain(0.0f, 400.0f, true) );

  // default testing. (snap and clamp)
  DALI_TEST_EQUALS( ruler->SnapAndClamp(50.0f), 50.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(30.0f), 50.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(10.0f), 0.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(-40.0f), 0.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(390.0f), 400.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(430.0f), 400.0f, TEST_LOCATION);

  // bias testing.
  DALI_TEST_EQUALS( ruler->SnapAndClamp(40.0f, 0.0f), 0.0f, TEST_LOCATION); // Flick Left
  DALI_TEST_EQUALS( ruler->SnapAndClamp(40.0f, 0.5f), 50.0f, TEST_LOCATION); // No Flick
  DALI_TEST_EQUALS( ruler->SnapAndClamp(40.0f, 1.0f), 50.0f, TEST_LOCATION); // Flick Right

  DALI_TEST_EQUALS( ruler->SnapAndClamp(20.0f, 0.0f), 0.0f, TEST_LOCATION); // Flick Left
  DALI_TEST_EQUALS( ruler->SnapAndClamp(20.0f, 0.5f), 0.0f, TEST_LOCATION); // No Flick
  DALI_TEST_EQUALS( ruler->SnapAndClamp(20.0f, 1.0f), 50.0f, TEST_LOCATION); // Flick Right

  // length testing.
  DALI_TEST_EQUALS( ruler->SnapAndClamp(-10.0f, 0.5f, 10.0f), 0.0f, TEST_LOCATION); // 10 units long (over left boundary)
  DALI_TEST_EQUALS( ruler->SnapAndClamp(-5.0f, 0.5f, 10.0f), 0.0f, TEST_LOCATION); // 10 units long (slightly ovr left boundary)
  DALI_TEST_EQUALS( ruler->SnapAndClamp(300.0f, 0.5f, 10.0f), 300.0f, TEST_LOCATION); // 10 units long (not over a boundary)
  DALI_TEST_EQUALS( ruler->SnapAndClamp(395.0f, 0.5f, 10.0f), 390.0f, TEST_LOCATION); // 10 units long (slightly over right boundary)
  DALI_TEST_EQUALS( ruler->SnapAndClamp(500.0f, 0.5f, 10.0f), 390.0f, TEST_LOCATION); // 10 units long (over right boundary)

  // scale testing.
  DALI_TEST_EQUALS( ruler->SnapAndClamp(-100.0f, 0.5f, 0.0f, 2.0f), 0.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(50.0f, 0.5f, 0.0f, 2.0f), 50.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(700.0f, 0.5f, 0.0f, 2.0f), 700.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( ruler->SnapAndClamp(850.0f, 0.5f, 0.0f, 2.0f), 800.0f, TEST_LOCATION);

  // clamp state testing.
  ClampState clamped;
  DALI_TEST_EQUALS( ruler->SnapAndClamp(50.0f, 0.5f, 0.0f, 1.0f, clamped), 50.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, NotClamped, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->SnapAndClamp(30.0f, 0.5f, 0.0f, 1.0f, clamped), 50.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, NotClamped, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->SnapAndClamp(10.0f, 0.5f, 0.0f, 1.0f, clamped), 0.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, NotClamped, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->SnapAndClamp(-40.0f, 0.5f, 0.0f, 1.0f, clamped), 0.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, ClampedToMin, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->SnapAndClamp(390.0f, 0.5f, 0.0f, 1.0f, clamped), 400.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, NotClamped, TEST_LOCATION );
  DALI_TEST_EQUALS( ruler->SnapAndClamp(430.0f, 0.5f, 0.0f, 1.0f, clamped), 400.0f, TEST_LOCATION);
  DALI_TEST_EQUALS( clamped, ClampedToMax, TEST_LOCATION );
  END_TEST;
}

int UtcDaliRulerFixedRulerSpacing(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliRulerFixedRulerSpacing");

  RulerPtr rulerNormal = new FixedRuler( 25.0f );
  rulerNormal->SetDomain( RulerDomain(10.0f, 90.0f, true) );

  unsigned int volume;
  float position;

  position = rulerNormal->GetPositionFromPage(1, volume, true);
  DALI_TEST_EQUALS( position, 35.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( volume, 0u, TEST_LOCATION );

  position = rulerNormal->GetPositionFromPage(2, volume, true);
  DALI_TEST_EQUALS( position, 60.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( volume, 0u, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewOvershoot(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewOvershoot");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.ScrollStartedSignal().Connect( &OnScrollStart );
  scrollView.ScrollUpdatedSignal().Connect( &OnScrollUpdate );
  scrollView.ScrollCompletedSignal().Connect( &OnScrollComplete );

  scrollView.ScrollTo(OVERSHOOT_START_SCROLL_POSITION, 0.0f); // move in a little.
  Wait(application);

  // 1. Scroll page in NW (-500,-500 pixels), then inspect overshoot. (don't release touch)
  Vector2 currentPos = Vector2(100.0f, 100.0f);
  currentPos = PerformGestureDiagonalSwipe(application, currentPos, Vector2(5.0f, 5.0f), 100, false);
  Property::Index overshootXProperty = scrollView.GetPropertyIndex(ScrollView::SCROLL_OVERSHOOT_X_PROPERTY_NAME);
  Property::Index overshootYProperty = scrollView.GetPropertyIndex(ScrollView::SCROLL_OVERSHOOT_Y_PROPERTY_NAME);
  Property::Index scrollPositionProperty = scrollView.GetPropertyIndex(ScrollView::SCROLL_POSITION_PROPERTY_NAME);
  float overshootXValue = scrollView.GetProperty<float>(overshootXProperty);
  float overshootYValue = scrollView.GetProperty<float>(overshootYProperty);
  Vector3 positionValue = scrollView.GetProperty<Vector3>(scrollPositionProperty);
  DALI_TEST_EQUALS(overshootXValue, 1.0f, TEST_LOCATION);
  DALI_TEST_EQUALS(overshootYValue, 1.0f, TEST_LOCATION);
  DALI_TEST_EQUALS(positionValue, Vector3::ZERO, TEST_LOCATION);

  float timeToReachOrigin;

  // Now release touch. Overshoot should snap back to zero.
  SendPan(application, Gesture::Finished, currentPos);
  timeToReachOrigin = TestOvershootSnapDuration(application, scrollView);

  DALI_TEST_CHECK( (timeToReachOrigin > Toolkit::ScrollView::DEFAULT_SNAP_OVERSHOOT_DURATION - TIME_TOLERANCE) &&
                   (timeToReachOrigin < Toolkit::ScrollView::DEFAULT_SNAP_OVERSHOOT_DURATION + TIME_TOLERANCE) );

  // 2. Repeat Scroll, but this time change overshoot snap duration to shorter time
  scrollView.SetSnapOvershootDuration(TEST_CUSTOM1_SNAP_OVERSHOOT_DURATION);

  currentPos = PerformGestureDiagonalSwipe(application, Vector2(100.0f, 100.0f), Vector2(5.0f, 5.0f), 100, false);
  // Now release touch. Overshoot should snap back to zero.
  SendPan(application, Gesture::Finished, currentPos);
  timeToReachOrigin = TestOvershootSnapDuration(application, scrollView);

  DALI_TEST_CHECK( (timeToReachOrigin > TEST_CUSTOM1_SNAP_OVERSHOOT_DURATION - TIME_TOLERANCE) &&
                   (timeToReachOrigin < TEST_CUSTOM1_SNAP_OVERSHOOT_DURATION + TIME_TOLERANCE) );

  // 3. Repeat Scroll, but this time change overshoot snap duration to longer time.
  scrollView.SetSnapOvershootDuration(TEST_CUSTOM2_SNAP_OVERSHOOT_DURATION);

  currentPos = PerformGestureDiagonalSwipe(application, Vector2(100.0f, 100.0f), Vector2(5.0f, 5.0f), 100, false);
  // Now release touch. Overshoot should snap back to zero.
  SendPan(application, Gesture::Finished, currentPos);
  timeToReachOrigin = TestOvershootSnapDuration(application, scrollView);

  DALI_TEST_CHECK( (timeToReachOrigin > TEST_CUSTOM2_SNAP_OVERSHOOT_DURATION - TIME_TOLERANCE) &&
                   (timeToReachOrigin < TEST_CUSTOM2_SNAP_OVERSHOOT_DURATION + TIME_TOLERANCE) );

  // 4. Repeat Scroll, but this time change overshoot function.
  scrollView.SetSnapOvershootDuration(TEST_CUSTOM3_SNAP_OVERSHOOT_DURATION);
  scrollView.SetSnapOvershootAlphaFunction(TestAlphaFunction);

  currentPos = PerformGestureDiagonalSwipe(application, Vector2(100.0f, 100.0f), Vector2(5.0f, 5.0f), 100, false);
  // Now release touch. Overshoot should snap back to zero.
  SendPan(application, Gesture::Finished, currentPos);
  timeToReachOrigin = TestOvershootSnapDuration(application, scrollView);

  DALI_TEST_CHECK( (timeToReachOrigin > TEST_CUSTOM3_SNAP_OVERSHOOT_DURATION - TIME_TOLERANCE) &&
                   (timeToReachOrigin < TEST_CUSTOM3_SNAP_OVERSHOOT_DURATION + TIME_TOLERANCE) );
  END_TEST;
}

int UtcDaliScrollViewSnapAlphaFunction(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSnapAlphaFunction");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  scrollView.SetScrollSnapAlphaFunction( AlphaFunctions::EaseIn );
  DALI_TEST_CHECK( scrollView.GetScrollSnapAlphaFunction() == AlphaFunctions::EaseIn );
  scrollView.SetScrollSnapAlphaFunction( AlphaFunctions::EaseOut );
  DALI_TEST_CHECK( scrollView.GetScrollSnapAlphaFunction() == AlphaFunctions::EaseOut );

  scrollView.SetScrollFlickAlphaFunction( AlphaFunctions::Bounce );
  DALI_TEST_CHECK( scrollView.GetScrollFlickAlphaFunction() == AlphaFunctions::Bounce );
  scrollView.SetScrollFlickAlphaFunction( AlphaFunctions::BounceBack );
  DALI_TEST_CHECK( scrollView.GetScrollFlickAlphaFunction() == AlphaFunctions::BounceBack );
  END_TEST;
}

int UtcDaliScrollViewSnapDuration(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSnapDuration");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  scrollView.SetScrollSnapDuration( 1.0f );
  DALI_TEST_EQUALS( scrollView.GetScrollSnapDuration(), 1.0f, TEST_LOCATION );
  scrollView.SetScrollSnapDuration( 0.5f );
  DALI_TEST_EQUALS( scrollView.GetScrollSnapDuration(), 0.5f, TEST_LOCATION );

  scrollView.SetScrollFlickDuration( 2.0f );
  DALI_TEST_EQUALS( scrollView.GetScrollFlickDuration(), 2.0f, TEST_LOCATION );
  scrollView.SetScrollFlickDuration( 1.5f );
  DALI_TEST_EQUALS( scrollView.GetScrollFlickDuration(), 1.5f, TEST_LOCATION );
  END_TEST;
}

int UtcDaliScrollViewSignalsSnapStart(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSignalsSnapStart");

  // Set up a scrollView...
  ScrollView scrollView = ScrollView::New();
  Stage::GetCurrent().Add( scrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  scrollView.SetSize(stageSize);
  scrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  scrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + CLAMP_EXCESS_HEIGHT, true) );
  scrollView.SetRulerX(rulerX);
  scrollView.SetRulerY(rulerY);
  scrollView.SnapStartedSignal().Connect( &OnSnapStart );

  scrollView.ScrollTo(CLAMP_START_SCROLL_POSITION, 0.0f); // move in a little.
  Wait(application);

  // First try a snap.
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, Vector2(0.5f, 0.0f), 60, true);

  DALI_TEST_CHECK( gOnSnapStartCalled );
  DALI_TEST_CHECK( gLastSnapType == Toolkit::Snap );

  // Second try a swipe.
  PerformGestureDiagonalSwipe(application, CLAMP_TOUCH_START, Vector2(20.0f, 0.0f), 60, true);

  DALI_TEST_CHECK( gOnSnapStartCalled );
  DALI_TEST_CHECK( gLastSnapType == Toolkit::Flick );
  END_TEST;
}


int UtcDaliScrollViewSetMouseWheelScrollDistanceStep(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewSetMouseWheelScrollDistanceStep");

  ScrollView scrollView = ScrollView::New();
  // Disable Refresh signal (TET environment cannot use adaptor's Timer)
  scrollView.SetMouseWheelScrollDistanceStep(Vector2(30.0f, 15.0f));
  DALI_TEST_EQUALS( scrollView.GetMouseWheelScrollDistanceStep(), Vector2(30.0f, 15.0f), TEST_LOCATION );
  scrollView.SetMouseWheelScrollDistanceStep(Vector2(60.0f, 30.0f));
  DALI_TEST_EQUALS( scrollView.GetMouseWheelScrollDistanceStep(), Vector2(60.0f, 30.0f), TEST_LOCATION);
  END_TEST;
}

int UtcDaliScrollViewGetSet(void)
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliScrollViewGetSet");
  ScrollView scrollView = ScrollView::New();
  scrollView.SetMaxOvershoot(50.0f, 50.0f);
  scrollView.SetMaxFlickSpeed(0.5f);
  DALI_TEST_EQUALS(scrollView.GetMaxFlickSpeed(), 0.5f, Math::MACHINE_EPSILON_0, TEST_LOCATION);
  scrollView.SetFrictionCoefficient(0.6f);
  DALI_TEST_EQUALS(scrollView.GetFrictionCoefficient(), 0.6f, Math::MACHINE_EPSILON_0, TEST_LOCATION);
  scrollView.SetFlickSpeedCoefficient(0.7f);
  DALI_TEST_EQUALS(scrollView.GetFlickSpeedCoefficient(), 0.7f, Math::MACHINE_EPSILON_0, TEST_LOCATION);
  END_TEST;
}
