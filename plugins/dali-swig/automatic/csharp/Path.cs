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

public class Path : Handle {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal Path(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.Path_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Path obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Path() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_Path(swigCPtr);
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
            NDalicPINVOKE.delete_Path_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_Path_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int POINTS = NDalicPINVOKE.Path_Property_POINTS_get();
    public static readonly int CONTROL_POINTS = NDalicPINVOKE.Path_Property_CONTROL_POINTS_get();
  
  }

  public Path () : this (NDalicPINVOKE.Path_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public new static Path DownCast(BaseHandle handle) {
    Path ret = new Path(NDalicPINVOKE.Path_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Path(Path handle) : this(NDalicPINVOKE.new_Path__SWIG_1(Path.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Path Assign(Path rhs) {
    Path ret = new Path(NDalicPINVOKE.Path_Assign(swigCPtr, Path.getCPtr(rhs)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void AddPoint(Vector3 point) {
    NDalicPINVOKE.Path_AddPoint(swigCPtr, Vector3.getCPtr(point));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void AddControlPoint(Vector3 point) {
    NDalicPINVOKE.Path_AddControlPoint(swigCPtr, Vector3.getCPtr(point));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void GenerateControlPoints(float curvature) {
    NDalicPINVOKE.Path_GenerateControlPoints(swigCPtr, curvature);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Sample(float progress, Vector3 position, Vector3 tangent) {
    NDalicPINVOKE.Path_Sample(swigCPtr, progress, Vector3.getCPtr(position), Vector3.getCPtr(tangent));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Vector3 GetPoint(uint index) {
    Vector3 ret = new Vector3(NDalicPINVOKE.Path_GetPoint(swigCPtr, index), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector3 GetControlPoint(uint index) {
    Vector3 ret = new Vector3(NDalicPINVOKE.Path_GetControlPoint(swigCPtr, index), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint GetPointCount() {
    uint ret = NDalicPINVOKE.Path_GetPointCount(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Dali.Property.Array Points 
  { 
    get 
    {
      Dali.Property.Array temp = new Dali.Property.Array();
      GetProperty( Path.Property.POINTS).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Path.Property.POINTS, new Dali.Property.Value( value ) );
    }
  }
  public Dali.Property.Array ControlPoints 
  { 
    get 
    {
      Dali.Property.Array temp = new Dali.Property.Array();
      GetProperty( Path.Property.CONTROL_POINTS).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( Path.Property.CONTROL_POINTS, new Dali.Property.Value( value ) );
    }
  }

}

}
