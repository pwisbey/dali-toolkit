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

public class LinearConstrainer : Handle {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal LinearConstrainer(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.LinearConstrainer_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(LinearConstrainer obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~LinearConstrainer() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_LinearConstrainer(swigCPtr);
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
            NDalicPINVOKE.delete_LinearConstrainer_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_LinearConstrainer_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int VALUE = NDalicPINVOKE.LinearConstrainer_Property_VALUE_get();
    public static readonly int PROGRESS = NDalicPINVOKE.LinearConstrainer_Property_PROGRESS_get();
  
  }

  public LinearConstrainer () : this (NDalicPINVOKE.LinearConstrainer_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public new static LinearConstrainer DownCast(BaseHandle handle) {
    LinearConstrainer ret = new LinearConstrainer(NDalicPINVOKE.LinearConstrainer_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public LinearConstrainer(LinearConstrainer handle) : this(NDalicPINVOKE.new_LinearConstrainer__SWIG_1(LinearConstrainer.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public LinearConstrainer Assign(LinearConstrainer rhs) {
    LinearConstrainer ret = new LinearConstrainer(NDalicPINVOKE.LinearConstrainer_Assign(swigCPtr, LinearConstrainer.getCPtr(rhs)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Apply(Property target, Property source, Vector2 range, Vector2 wrap) {
    NDalicPINVOKE.LinearConstrainer_Apply__SWIG_0(swigCPtr, Property.getCPtr(target), Property.getCPtr(source), Vector2.getCPtr(range), Vector2.getCPtr(wrap));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Apply(Property target, Property source, Vector2 range) {
    NDalicPINVOKE.LinearConstrainer_Apply__SWIG_1(swigCPtr, Property.getCPtr(target), Property.getCPtr(source), Vector2.getCPtr(range));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Remove(Handle target) {
    NDalicPINVOKE.LinearConstrainer_Remove(swigCPtr, Handle.getCPtr(target));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Dali.Property.Array Value 
  { 
    get 
    {
      Dali.Property.Array temp = new Dali.Property.Array();
      GetProperty( LinearConstrainer.Property.VALUE).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( LinearConstrainer.Property.VALUE, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Array Progress 
  { 
    get 
    {
      Dali.Property.Array temp = new Dali.Property.Array();
      GetProperty( LinearConstrainer.Property.PROGRESS).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( LinearConstrainer.Property.PROGRESS, new Dali.Property.Value( value ) );
    }
  }

}

}
