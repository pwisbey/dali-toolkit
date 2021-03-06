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


public class VideoView : View {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal VideoView(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.VideoView_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(VideoView obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~VideoView() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_VideoView(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }


/**
  * @brief Event arguments that passed via Finished signal
  *
  */
public class FinishedEventArgs : EventArgs
{
   private VideoView _videoView;

   /**
     * @brief VideoView - VideoView is a control for video playback and display.
     *
     */
   public VideoView VideoView
   {
      get
      {
         return _videoView;
      }
      set
      {
         _videoView = value;
      }
   }
}


  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void FinishedCallbackDelegate(IntPtr data);
  private DaliEventHandler<object,FinishedEventArgs> _videoViewFinishedEventHandler;
  private FinishedCallbackDelegate _videoViewFinishedCallbackDelegate;

  /**
    * @brief Event for Finished signal which can be used to subscribe/unsubscribe the event handler
    * (in the type of FinishedEventHandler-DaliEventHandler<object,FinishedEventArgs>) provided by the user.
    * Finished signal is emitted when a video playback have finished.
    */
  public event DaliEventHandler<object,FinishedEventArgs> Finished
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_videoViewFinishedEventHandler == null)
           {
              _videoViewFinishedEventHandler += value;

              _videoViewFinishedCallbackDelegate = new FinishedCallbackDelegate(OnFinished);
              this.FinishedSignal().Connect(_videoViewFinishedCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_videoViewFinishedEventHandler != null)
           {
              this.FinishedSignal().Disconnect(_videoViewFinishedCallbackDelegate);
           }

           _videoViewFinishedEventHandler -= value;
        }
     }
  }

  // Callback for VideoView Finished signal
  private void OnFinished(IntPtr data)
  {
     FinishedEventArgs e = new FinishedEventArgs();

     // Populate all members of "e" (FinishedEventArgs) with real data
     e.VideoView = VideoView.GetVideoViewFromPtr( data );

     if (_videoViewFinishedEventHandler != null)
     {
        //here we send all data to user event handlers
        _videoViewFinishedEventHandler(this, e);
     }
  }

  public static VideoView GetVideoViewFromPtr(global::System.IntPtr cPtr) {
    VideoView ret = new VideoView(cPtr, false);
   if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
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
            NDalicPINVOKE.delete_VideoView_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_VideoView_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int VIDEO = NDalicPINVOKE.VideoView_Property_VIDEO_get();
    public static readonly int LOOPING = NDalicPINVOKE.VideoView_Property_LOOPING_get();
    public static readonly int MUTED = NDalicPINVOKE.VideoView_Property_MUTED_get();
    public static readonly int VOLUME = NDalicPINVOKE.VideoView_Property_VOLUME_get();
  
  }

  public VideoView () : this (NDalicPINVOKE.VideoView_New__SWIG_0(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public VideoView (string url) : this (NDalicPINVOKE.VideoView_New__SWIG_1(url), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public VideoView(VideoView videoView) : this(NDalicPINVOKE.new_VideoView__SWIG_1(VideoView.getCPtr(videoView)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public VideoView Assign(VideoView videoView) {
    VideoView ret = new VideoView(NDalicPINVOKE.VideoView_Assign(swigCPtr, VideoView.getCPtr(videoView)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static VideoView DownCast(BaseHandle handle) {
    VideoView ret = new VideoView(NDalicPINVOKE.VideoView_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Play() {
    NDalicPINVOKE.VideoView_Play(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Pause() {
    NDalicPINVOKE.VideoView_Pause(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Stop() {
    NDalicPINVOKE.VideoView_Stop(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Forward(int millisecond) {
    NDalicPINVOKE.VideoView_Forward(swigCPtr, millisecond);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Backward(int millisecond) {
    NDalicPINVOKE.VideoView_Backward(swigCPtr, millisecond);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public VideoViewSignal FinishedSignal() {
    VideoViewSignal ret = new VideoViewSignal(NDalicPINVOKE.VideoView_FinishedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum PropertyRange {
    PROPERTY_START_INDEX = PropertyRanges.PROPERTY_REGISTRATION_START_INDEX
  }

  public Dali.Property.Map Video 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( VideoView.Property.VIDEO).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( VideoView.Property.VIDEO, new Dali.Property.Value( value ) );
    }
  }
  public bool Looping 
  { 
    get 
    {
      bool temp = false;
      GetProperty( VideoView.Property.LOOPING).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( VideoView.Property.LOOPING, new Dali.Property.Value( value ) );
    }
  }
  public bool Muted 
  { 
    get 
    {
      bool temp = false;
      GetProperty( VideoView.Property.MUTED).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( VideoView.Property.MUTED, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map Volume 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( VideoView.Property.VOLUME).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( VideoView.Property.VOLUME, new Dali.Property.Value( value ) );
    }
  }

}

}
