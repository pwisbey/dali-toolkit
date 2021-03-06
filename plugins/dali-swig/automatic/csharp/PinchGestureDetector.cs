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


public class PinchGestureDetector : GestureDetector {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal PinchGestureDetector(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.PinchGestureDetector_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(PinchGestureDetector obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~PinchGestureDetector() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_PinchGestureDetector(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }


public class DetectedEventArgs : EventArgs
{
   private Actor _actor;
   private PinchGesture _pinchGesture;

   public Actor Actor
   {
      get
      {
         return _actor;
      }
      set
      {
         _actor = value;
      }
   }

   public PinchGesture PinchGesture
   {
      get
      {
         return _pinchGesture;
      }
      set
      {
         _pinchGesture = value;
      }
   }
}

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void DetectedCallbackDelegate(IntPtr actor, IntPtr pinchGesture);
  private DaliEventHandler<object,DetectedEventArgs> _pinchGestureEventHandler;
  private DetectedCallbackDelegate _pinchGestureCallbackDelegate;


  public event DaliEventHandler<object,DetectedEventArgs> Detected
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_pinchGestureEventHandler == null)
           {
              _pinchGestureEventHandler += value;

              _pinchGestureCallbackDelegate = new DetectedCallbackDelegate(OnPinchGestureDetected);
              this.DetectedSignal().Connect(_pinchGestureCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_pinchGestureEventHandler != null)
           {
              this.DetectedSignal().Disconnect(_pinchGestureCallbackDelegate);
           }

           _pinchGestureEventHandler -= value;
        }
     }
  }

 private void OnPinchGestureDetected(IntPtr actor, IntPtr pinchGesture)
  {
   DetectedEventArgs e = new DetectedEventArgs();

   // Populate all members of "e" (DetectedEventArgs) with real data
   e.Actor = Actor.GetActorFromPtr(actor);
   e.PinchGesture = Dali.PinchGesture.GetPinchGestureFromPtr(pinchGesture);

   if (_pinchGestureEventHandler != null)
   {
      //here we send all data to user event handlers
      _pinchGestureEventHandler(this, e);
   }

  }


public static PinchGestureDetector GetPinchGestureDetectorFromPtr(global::System.IntPtr cPtr) {
    PinchGestureDetector ret = new PinchGestureDetector(cPtr, false);
   if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }


  public PinchGestureDetector () : this (NDalicPINVOKE.PinchGestureDetector_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public new static PinchGestureDetector DownCast(BaseHandle handle) {
    PinchGestureDetector ret = new PinchGestureDetector(NDalicPINVOKE.PinchGestureDetector_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PinchGestureDetector(PinchGestureDetector handle) : this(NDalicPINVOKE.new_PinchGestureDetector__SWIG_1(PinchGestureDetector.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public PinchGestureDetector Assign(PinchGestureDetector rhs) {
    PinchGestureDetector ret = new PinchGestureDetector(NDalicPINVOKE.PinchGestureDetector_Assign(swigCPtr, PinchGestureDetector.getCPtr(rhs)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PinchGestureDetectedSignal DetectedSignal() {
    PinchGestureDetectedSignal ret = new PinchGestureDetectedSignal(NDalicPINVOKE.PinchGestureDetector_DetectedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
