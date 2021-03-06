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

public class RectUnsignedInteger : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal RectUnsignedInteger(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(RectUnsignedInteger obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~RectUnsignedInteger() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_RectUnsignedInteger(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public RectUnsignedInteger() : this(NDalicPINVOKE.new_RectUnsignedInteger__SWIG_0(), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public RectUnsignedInteger(uint x, uint y, uint width, uint height) : this(NDalicPINVOKE.new_RectUnsignedInteger__SWIG_1(x, y, width, height), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public RectUnsignedInteger(RectUnsignedInteger rhs) : this(NDalicPINVOKE.new_RectUnsignedInteger__SWIG_2(RectUnsignedInteger.getCPtr(rhs)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public RectUnsignedInteger Assign(RectUnsignedInteger rhs) {
    RectUnsignedInteger ret = new RectUnsignedInteger(NDalicPINVOKE.RectUnsignedInteger_Assign(swigCPtr, RectUnsignedInteger.getCPtr(rhs)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Set(uint newX, uint newY, uint newWidth, uint newHeight) {
    NDalicPINVOKE.RectUnsignedInteger_Set(swigCPtr, newX, newY, newWidth, newHeight);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool IsEmpty() {
    bool ret = NDalicPINVOKE.RectUnsignedInteger_IsEmpty(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Left() {
    uint ret = NDalicPINVOKE.RectUnsignedInteger_Left(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Right() {
    uint ret = NDalicPINVOKE.RectUnsignedInteger_Right(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Top() {
    uint ret = NDalicPINVOKE.RectUnsignedInteger_Top(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Bottom() {
    uint ret = NDalicPINVOKE.RectUnsignedInteger_Bottom(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Area() {
    uint ret = NDalicPINVOKE.RectUnsignedInteger_Area(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Intersects(RectUnsignedInteger other) {
    bool ret = NDalicPINVOKE.RectUnsignedInteger_Intersects(swigCPtr, RectUnsignedInteger.getCPtr(other));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Contains(RectUnsignedInteger other) {
    bool ret = NDalicPINVOKE.RectUnsignedInteger_Contains(swigCPtr, RectUnsignedInteger.getCPtr(other));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint x {
    set {
      NDalicPINVOKE.RectUnsignedInteger_x_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_x_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint left {
    set {
      NDalicPINVOKE.RectUnsignedInteger_left_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_left_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint y {
    set {
      NDalicPINVOKE.RectUnsignedInteger_y_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_y_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint right {
    set {
      NDalicPINVOKE.RectUnsignedInteger_right_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_right_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint width {
    set {
      NDalicPINVOKE.RectUnsignedInteger_width_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_width_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint bottom {
    set {
      NDalicPINVOKE.RectUnsignedInteger_bottom_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_bottom_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint height {
    set {
      NDalicPINVOKE.RectUnsignedInteger_height_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_height_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public uint top {
    set {
      NDalicPINVOKE.RectUnsignedInteger_top_set(swigCPtr, value);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      uint ret = NDalicPINVOKE.RectUnsignedInteger_top_get(swigCPtr);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

}

}
