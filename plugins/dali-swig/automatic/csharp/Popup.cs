/** Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
// This File has been auto-generated by SWIG and then modified using DALi Ruby Scripts
//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.9
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Dali {

using System;
using System.Runtime.InteropServices;


public class Popup : View {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal Popup(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.Popup_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Popup obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Popup() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_Popup(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }


  public class OutsideTouchedEventArgs : EventArgs
  {
  }

  public class ShowingEventArgs : EventArgs
  {
  }

  public class ShownEventArgs : EventArgs
  {
  }

  public class HidingEventArgs : EventArgs
  {
  }

  public class HiddenEventArgs : EventArgs
  {
  }

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void OutsideTouchedEventCallbackDelegate();
  private DaliEventHandler<object,OutsideTouchedEventArgs> _popUpOutsideTouchedEventHandler;
  private OutsideTouchedEventCallbackDelegate _popUpOutsideTouchedEventCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void ShowingEventCallbackDelegate();
  private DaliEventHandler<object,ShowingEventArgs> _popUpShowingEventHandler;
  private ShowingEventCallbackDelegate _popUpShowingEventCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void ShownEventCallbackDelegate();
  private DaliEventHandler<object,ShownEventArgs> _popUpShownEventHandler;
  private ShownEventCallbackDelegate _popUpShownEventCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void HidingEventCallbackDelegate();
  private DaliEventHandler<object,HidingEventArgs> _popUpHidingEventHandler;
  private HidingEventCallbackDelegate _popUpHidingEventCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void HiddenEventCallbackDelegate();
  private DaliEventHandler<object,HiddenEventArgs> _popUpHiddenEventHandler;
  private HiddenEventCallbackDelegate _popUpHiddenEventCallbackDelegate;

  public event DaliEventHandler<object,OutsideTouchedEventArgs> OutsideTouched
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_popUpOutsideTouchedEventHandler == null)
           {
              _popUpOutsideTouchedEventHandler += value;

              _popUpOutsideTouchedEventCallbackDelegate = new OutsideTouchedEventCallbackDelegate(OnOutsideTouched);
              this.OutsideTouchedSignal().Connect(_popUpOutsideTouchedEventCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_popUpOutsideTouchedEventHandler != null)
           {
              this.OutsideTouchedSignal().Disconnect(_popUpOutsideTouchedEventCallbackDelegate);
           }

           _popUpOutsideTouchedEventHandler -= value;
        }
     }
  }

  // Callback for Popup OutsideTouchedSignal
  private void OnOutsideTouched()
  {
     OutsideTouchedEventArgs e = new OutsideTouchedEventArgs();

     if (_popUpOutsideTouchedEventHandler != null)
     {
        //here we send all data to user event handlers
        _popUpOutsideTouchedEventHandler(this, e);
     }
  }

  public event DaliEventHandler<object,ShowingEventArgs> Showing
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_popUpShowingEventHandler == null)
           {
              _popUpShowingEventHandler += value;

              _popUpShowingEventCallbackDelegate = new ShowingEventCallbackDelegate(OnShowing);
              this.ShowingSignal().Connect(_popUpShowingEventCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_popUpShowingEventHandler != null)
           {
              this.ShowingSignal().Disconnect(_popUpShowingEventCallbackDelegate);
           }

           _popUpShowingEventHandler -= value;
        }
     }
  }

  // Callback for ShowingSignal
  private void OnShowing()
  {
     ShowingEventArgs e = new ShowingEventArgs();

     if (_popUpShowingEventHandler != null)
     {
        //here we send all data to user event handlers
        _popUpShowingEventHandler(this, e);
     }
  }


  public event DaliEventHandler<object,ShownEventArgs> Shown
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_popUpShownEventHandler == null)
           {
              _popUpShownEventHandler += value;

              _popUpShownEventCallbackDelegate = new ShownEventCallbackDelegate(OnShown);
              this.ShownSignal().Connect(_popUpShownEventCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_popUpShownEventHandler != null)
           {
              this.ShownSignal().Disconnect(_popUpShownEventCallbackDelegate);
           }

           _popUpShownEventHandler -= value;
        }
     }
  }

  // Callback for ShownSignal
  private void OnShown()
  {
     ShownEventArgs e = new ShownEventArgs();

     if (_popUpShownEventHandler != null)
     {
        //here we send all data to user event handlers
        _popUpShownEventHandler(this, e);
     }
  }

  public event DaliEventHandler<object,HidingEventArgs> Hiding
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_popUpHidingEventHandler == null)
           {
              _popUpHidingEventHandler += value;

              _popUpHidingEventCallbackDelegate = new HidingEventCallbackDelegate(OnHiding);
              this.HidingSignal().Connect(_popUpHidingEventCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_popUpHidingEventHandler != null)
           {
              this.HidingSignal().Disconnect(_popUpHidingEventCallbackDelegate);
           }

           _popUpHidingEventHandler -= value;
        }
     }
  }

  // Callback for HidingSignal
  private void OnHiding()
  {
     HidingEventArgs e = new HidingEventArgs();

     if (_popUpHidingEventHandler != null)
     {
        //here we send all data to user event handlers
        _popUpHidingEventHandler(this, e);
     }
  }

  public event DaliEventHandler<object,HiddenEventArgs> Hidden
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_popUpHiddenEventHandler == null)
           {
              _popUpHiddenEventHandler += value;

              _popUpHiddenEventCallbackDelegate = new HiddenEventCallbackDelegate(OnHidden);
              this.HiddenSignal().Connect(_popUpHiddenEventCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_popUpHiddenEventHandler != null)
           {
              this.HiddenSignal().Disconnect(_popUpHiddenEventCallbackDelegate);
           }

           _popUpHiddenEventHandler -= value;
        }
     }
  }

  // Callback for HiddenSignal
  private void OnHidden()
  {
     HiddenEventArgs e = new HiddenEventArgs();

     if (_popUpHiddenEventHandler != null)
     {
        //here we send all data to user event handlers
        _popUpHiddenEventHandler(this, e);
     }
  }

  public class Property : global::System.IDisposable {
    private global::System.Runtime.InteropServices.HandleRef swigCPtr;
    protected bool swigCMemOwn;
  
    internal Property(global::System.IntPtr cPtr, bool cMemoryOwn) {
      swigCMemOwn = cMemoryOwn;
      swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
    }
  
    internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Property obj) {
      return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
    }
  
    ~Property() {
      Dispose();
    }
  
    public virtual void Dispose() {
      lock(this) {
        if (swigCPtr.Handle != global::System.IntPtr.Zero) {
          if (swigCMemOwn) {
            swigCMemOwn = false;
            NDalicPINVOKE.delete_Popup_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_Popup_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int TITLE = NDalicPINVOKE.Popup_Property_TITLE_get();
    public static readonly int CONTENT = NDalicPINVOKE.Popup_Property_CONTENT_get();
    public static readonly int FOOTER = NDalicPINVOKE.Popup_Property_FOOTER_get();
    public static readonly int DISPLAY_STATE = NDalicPINVOKE.Popup_Property_DISPLAY_STATE_get();
    public static readonly int TOUCH_TRANSPARENT = NDalicPINVOKE.Popup_Property_TOUCH_TRANSPARENT_get();
    public static readonly int TAIL_VISIBILITY = NDalicPINVOKE.Popup_Property_TAIL_VISIBILITY_get();
    public static readonly int TAIL_POSITION = NDalicPINVOKE.Popup_Property_TAIL_POSITION_get();
    public static readonly int CONTEXTUAL_MODE = NDalicPINVOKE.Popup_Property_CONTEXTUAL_MODE_get();
    public static readonly int ANIMATION_DURATION = NDalicPINVOKE.Popup_Property_ANIMATION_DURATION_get();
    public static readonly int ANIMATION_MODE = NDalicPINVOKE.Popup_Property_ANIMATION_MODE_get();
    public static readonly int ENTRY_ANIMATION = NDalicPINVOKE.Popup_Property_ENTRY_ANIMATION_get();
    public static readonly int EXIT_ANIMATION = NDalicPINVOKE.Popup_Property_EXIT_ANIMATION_get();
    public static readonly int AUTO_HIDE_DELAY = NDalicPINVOKE.Popup_Property_AUTO_HIDE_DELAY_get();
    public static readonly int BACKING_ENABLED = NDalicPINVOKE.Popup_Property_BACKING_ENABLED_get();
    public static readonly int BACKING_COLOR = NDalicPINVOKE.Popup_Property_BACKING_COLOR_get();
    public static readonly int POPUP_BACKGROUND_IMAGE = NDalicPINVOKE.Popup_Property_POPUP_BACKGROUND_IMAGE_get();
    public static readonly int TAIL_UP_IMAGE = NDalicPINVOKE.Popup_Property_TAIL_UP_IMAGE_get();
    public static readonly int TAIL_DOWN_IMAGE = NDalicPINVOKE.Popup_Property_TAIL_DOWN_IMAGE_get();
    public static readonly int TAIL_LEFT_IMAGE = NDalicPINVOKE.Popup_Property_TAIL_LEFT_IMAGE_get();
    public static readonly int TAIL_RIGHT_IMAGE = NDalicPINVOKE.Popup_Property_TAIL_RIGHT_IMAGE_get();
  
  }

  public Popup () : this (NDalicPINVOKE.Popup_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public Popup(Popup handle) : this(NDalicPINVOKE.new_Popup__SWIG_1(Popup.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Popup Assign(Popup handle) {
    Popup ret = new Popup(NDalicPINVOKE.Popup_Assign(swigCPtr, Popup.getCPtr(handle)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static Popup DownCast(BaseHandle handle) {
    Popup ret = new Popup(NDalicPINVOKE.Popup_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetTitle(Actor titleActor) {
    NDalicPINVOKE.Popup_SetTitle(swigCPtr, Actor.getCPtr(titleActor));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Actor GetTitle() {
    Actor ret = new Actor(NDalicPINVOKE.Popup_GetTitle(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetContent(Actor content) {
    NDalicPINVOKE.Popup_SetContent(swigCPtr, Actor.getCPtr(content));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Actor GetContent() {
    Actor ret = new Actor(NDalicPINVOKE.Popup_GetContent(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetFooter(Actor footer) {
    NDalicPINVOKE.Popup_SetFooter(swigCPtr, Actor.getCPtr(footer));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Actor GetFooter() {
    Actor ret = new Actor(NDalicPINVOKE.Popup_GetFooter(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetDisplayState(Popup.DisplayStateType displayState) {
    NDalicPINVOKE.Popup_SetDisplayState(swigCPtr, (int)displayState);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Popup.DisplayStateType GetDisplayState() {
    Popup.DisplayStateType ret = (Popup.DisplayStateType)NDalicPINVOKE.Popup_GetDisplayState(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public VoidSignal OutsideTouchedSignal() {
    VoidSignal ret = new VoidSignal(NDalicPINVOKE.Popup_OutsideTouchedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public VoidSignal ShowingSignal() {
    VoidSignal ret = new VoidSignal(NDalicPINVOKE.Popup_ShowingSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public VoidSignal ShownSignal() {
    VoidSignal ret = new VoidSignal(NDalicPINVOKE.Popup_ShownSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public VoidSignal HidingSignal() {
    VoidSignal ret = new VoidSignal(NDalicPINVOKE.Popup_HidingSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public VoidSignal HiddenSignal() {
    VoidSignal ret = new VoidSignal(NDalicPINVOKE.Popup_HiddenSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum PropertyRange {
    PROPERTY_START_INDEX = PropertyRanges.PROPERTY_REGISTRATION_START_INDEX,
    PROPERTY_END_INDEX = View.PropertyRange.PROPERTY_START_INDEX+1000
  }

  public enum DisplayStateType {
    SHOWING,
    SHOWN,
    HIDING,
    HIDDEN
  }

  public enum AnimationModeType {
    NONE,
    ZOOM,
    FADE,
    CUSTOM
  }

  public enum ContextualModeType {
    NON_CONTEXTUAL,
    ABOVE,
    RIGHT,
    BELOW,
    LEFT
  }

  public Dali.Property.Map Title 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( Popup.Property.TITLE).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TITLE, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map Content 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( Popup.Property.CONTENT).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.CONTENT, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map Footer 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( Popup.Property.FOOTER).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.FOOTER, new Dali.Property.Value( value ) );
    }
  }
  public string DisplayState 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.DISPLAY_STATE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.DISPLAY_STATE, new Dali.Property.Value( value ) );
    }
  }
  public bool TouchTransparent 
  { 
    get 
    {
      bool temp = false;
      GetProperty( Popup.Property.TOUCH_TRANSPARENT).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TOUCH_TRANSPARENT, new Dali.Property.Value( value ) );
    }
  }
  public bool TailVisibility 
  { 
    get 
    {
      bool temp = false;
      GetProperty( Popup.Property.TAIL_VISIBILITY).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_VISIBILITY, new Dali.Property.Value( value ) );
    }
  }
  public Vector3 TailPosition 
  { 
    get 
    {
      Vector3 temp = new Vector3(0.0f,0.0f,0.0f);
      GetProperty( Popup.Property.TAIL_POSITION).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_POSITION, new Dali.Property.Value( value ) );
    }
  }
  public string ContextualMode 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.CONTEXTUAL_MODE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.CONTEXTUAL_MODE, new Dali.Property.Value( value ) );
    }
  }
  public float AnimationDuration 
  { 
    get 
    {
      float temp = 0.0f;
      GetProperty( Popup.Property.ANIMATION_DURATION).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.ANIMATION_DURATION, new Dali.Property.Value( value ) );
    }
  }
  public string AnimationMode 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.ANIMATION_MODE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.ANIMATION_MODE, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map EntryAnimation 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( Popup.Property.ENTRY_ANIMATION).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.ENTRY_ANIMATION, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map ExitAnimation 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( Popup.Property.EXIT_ANIMATION).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.EXIT_ANIMATION, new Dali.Property.Value( value ) );
    }
  }
  public int AutoHideDelay 
  { 
    get 
    {
      int temp = 0;
      GetProperty( Popup.Property.AUTO_HIDE_DELAY).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.AUTO_HIDE_DELAY, new Dali.Property.Value( value ) );
    }
  }
  public bool BackingEnabled 
  { 
    get 
    {
      bool temp = false;
      GetProperty( Popup.Property.BACKING_ENABLED).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.BACKING_ENABLED, new Dali.Property.Value( value ) );
    }
  }
  public Vector4 BackingColor 
  { 
    get 
    {
      Vector4 temp = new Vector4(0.0f,0.0f,0.0f,0.0f);
      GetProperty( Popup.Property.BACKING_COLOR).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.BACKING_COLOR, new Dali.Property.Value( value ) );
    }
  }
  public string PopupBackgroundImage 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.POPUP_BACKGROUND_IMAGE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.POPUP_BACKGROUND_IMAGE, new Dali.Property.Value( value ) );
    }
  }
  public string TailUpImage 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.TAIL_UP_IMAGE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_UP_IMAGE, new Dali.Property.Value( value ) );
    }
  }
  public string TailDownImage 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.TAIL_DOWN_IMAGE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_DOWN_IMAGE, new Dali.Property.Value( value ) );
    }
  }
  public string TailLeftImage 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.TAIL_LEFT_IMAGE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_LEFT_IMAGE, new Dali.Property.Value( value ) );
    }
  }
  public string TailRightImage 
  { 
    get 
    {
      string temp;
      GetProperty( Popup.Property.TAIL_RIGHT_IMAGE).Get( out temp );
      return temp;
    }
    set 
    { 
      SetProperty( Popup.Property.TAIL_RIGHT_IMAGE, new Dali.Property.Value( value ) );
    }
  }

}

}
