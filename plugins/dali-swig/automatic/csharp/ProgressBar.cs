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

public class ProgressBar : View {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal ProgressBar(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.ProgressBar_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ProgressBar obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~ProgressBar() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_ProgressBar(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
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
            NDalicPINVOKE.delete_ProgressBar_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_ProgressBar_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int PROGRESS_VALUE = NDalicPINVOKE.ProgressBar_Property_PROGRESS_VALUE_get();
    public static readonly int TRACK_VISUAL = NDalicPINVOKE.ProgressBar_Property_TRACK_VISUAL_get();
    public static readonly int PROGRESS_VISUAL = NDalicPINVOKE.ProgressBar_Property_PROGRESS_VISUAL_get();
  
  }

  public ProgressBar () : this (NDalicPINVOKE.ProgressBar_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public ProgressBar(ProgressBar handle) : this(NDalicPINVOKE.new_ProgressBar__SWIG_1(ProgressBar.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public ProgressBar Assign(ProgressBar handle) {
    ProgressBar ret = new ProgressBar(NDalicPINVOKE.ProgressBar_Assign(swigCPtr, ProgressBar.getCPtr(handle)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static ProgressBar DownCast(BaseHandle handle) {
    ProgressBar ret = new ProgressBar(NDalicPINVOKE.ProgressBar_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public SWIGTYPE_p_Dali__SignalT_void_fDali__Toolkit__ProgressBar_floatF_t ValueChangedSignal() {
    SWIGTYPE_p_Dali__SignalT_void_fDali__Toolkit__ProgressBar_floatF_t ret = new SWIGTYPE_p_Dali__SignalT_void_fDali__Toolkit__ProgressBar_floatF_t(NDalicPINVOKE.ProgressBar_ValueChangedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum PropertyRange {
    PROPERTY_START_INDEX = PropertyRanges.PROPERTY_REGISTRATION_START_INDEX,
    PROPERTY_END_INDEX = View.PropertyRange.PROPERTY_START_INDEX+1000
  }

  public float ProgressValue 
  { 
    get 
    {
      float temp = 0.0f;
      GetProperty( ProgressBar.Property.PROGRESS_VALUE).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( ProgressBar.Property.PROGRESS_VALUE, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map TrackVisual 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( ProgressBar.Property.TRACK_VISUAL).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( ProgressBar.Property.TRACK_VISUAL, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Map ProgressVisual 
  { 
    get 
    {
      Dali.Property.Map temp = new Dali.Property.Map();
      GetProperty( ProgressBar.Property.PROGRESS_VISUAL).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( ProgressBar.Property.PROGRESS_VISUAL, new Dali.Property.Value( value ) );
    }
  }

}

}
