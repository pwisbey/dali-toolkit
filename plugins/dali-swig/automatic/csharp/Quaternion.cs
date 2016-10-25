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

public class Quaternion : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Quaternion(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Quaternion obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Quaternion() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_Quaternion(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public static Quaternion operator+(Quaternion arg1, Quaternion arg2) {
    return arg1.Add(arg2);
  }

  public static Quaternion operator-(Quaternion arg1, Quaternion arg2) {
    return arg1.Subtract(arg2);
  }

  public static Quaternion operator-(Quaternion arg1) {
    return arg1.Subtract();
  }

  public static Quaternion operator*(Quaternion arg1, Quaternion arg2) {
    return arg1.Multiply(arg2);
  }

  public static Vector3 operator*(Quaternion arg1, Vector3 arg2) {
    return arg1.Multiply(arg2);
  }

  public static Quaternion operator*(Quaternion arg1, float arg2) {
    return arg1.Multiply(arg2);
  }

  public static Quaternion operator/(Quaternion arg1, Quaternion arg2) {
    return arg1.Divide(arg2);
  }

  public static Quaternion operator/(Quaternion arg1, float arg2) {
    return arg1.Divide(arg2);
  }

  public Quaternion() : this(NDalicPINVOKE.new_Quaternion__SWIG_0(), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(float cosThetaBy2, float iBySineTheta, float jBySineTheta, float kBySineTheta) : this(NDalicPINVOKE.new_Quaternion__SWIG_1(cosThetaBy2, iBySineTheta, jBySineTheta, kBySineTheta), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Vector4 vector) : this(NDalicPINVOKE.new_Quaternion__SWIG_2(Vector4.getCPtr(vector)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Radian angle, Vector3 axis) : this(NDalicPINVOKE.new_Quaternion__SWIG_3(Radian.getCPtr(angle), Vector3.getCPtr(axis)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Radian pitch, Radian yaw, Radian roll) : this(NDalicPINVOKE.new_Quaternion__SWIG_4(Radian.getCPtr(pitch), Radian.getCPtr(yaw), Radian.getCPtr(roll)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Matrix matrix) : this(NDalicPINVOKE.new_Quaternion__SWIG_5(Matrix.getCPtr(matrix)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Vector3 xAxis, Vector3 yAxis, Vector3 zAxis) : this(NDalicPINVOKE.new_Quaternion__SWIG_6(Vector3.getCPtr(xAxis), Vector3.getCPtr(yAxis), Vector3.getCPtr(zAxis)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion(Vector3 v0, Vector3 v1) : this(NDalicPINVOKE.new_Quaternion__SWIG_7(Vector3.getCPtr(v0), Vector3.getCPtr(v1)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public static Quaternion IDENTITY {
    get {
      global::System.IntPtr cPtr = NDalicPINVOKE.Quaternion_IDENTITY_get();
      Quaternion ret = (cPtr == global::System.IntPtr.Zero) ? null : new Quaternion(cPtr, false);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public bool IsIdentity() {
    bool ret = NDalicPINVOKE.Quaternion_IsIdentity(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool ToAxisAngle(Vector3 axis, Radian angle) {
    bool ret = NDalicPINVOKE.Quaternion_ToAxisAngle(swigCPtr, Vector3.getCPtr(axis), Radian.getCPtr(angle));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector4 AsVector() {
    Vector4 ret = new Vector4(NDalicPINVOKE.Quaternion_AsVector(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void SetEuler(Radian pitch, Radian yaw, Radian roll) {
    NDalicPINVOKE.Quaternion_SetEuler(swigCPtr, Radian.getCPtr(pitch), Radian.getCPtr(yaw), Radian.getCPtr(roll));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Vector4 EulerAngles() {
    Vector4 ret = new Vector4(NDalicPINVOKE.Quaternion_EulerAngles(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Add(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Add(swigCPtr, Quaternion.getCPtr(other)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Subtract(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Subtract__SWIG_0(swigCPtr, Quaternion.getCPtr(other)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Multiply(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Multiply__SWIG_0(swigCPtr, Quaternion.getCPtr(other)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector3 Multiply(Vector3 other) {
    Vector3 ret = new Vector3(NDalicPINVOKE.Quaternion_Multiply__SWIG_1(swigCPtr, Vector3.getCPtr(other)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Divide(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Divide__SWIG_0(swigCPtr, Quaternion.getCPtr(other)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Multiply(float scale) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Multiply__SWIG_2(swigCPtr, scale), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Divide(float scale) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Divide__SWIG_1(swigCPtr, scale), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Subtract() {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Subtract__SWIG_1(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion AddAssign(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_AddAssign(swigCPtr, Quaternion.getCPtr(other)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion SubtractAssign(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_SubtractAssign(swigCPtr, Quaternion.getCPtr(other)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion MultiplyAssign(Quaternion other) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_MultiplyAssign__SWIG_0(swigCPtr, Quaternion.getCPtr(other)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion MultiplyAssign(float scale) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_MultiplyAssign__SWIG_1(swigCPtr, scale), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion DivideAssign(float scale) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_DivideAssign(swigCPtr, scale), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool EqualTo(Quaternion rhs) {
    bool ret = NDalicPINVOKE.Quaternion_EqualTo(swigCPtr, Quaternion.getCPtr(rhs));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool NotEqualTo(Quaternion rhs) {
    bool ret = NDalicPINVOKE.Quaternion_NotEqualTo(swigCPtr, Quaternion.getCPtr(rhs));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float Length() {
    float ret = NDalicPINVOKE.Quaternion_Length(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public float LengthSquared() {
    float ret = NDalicPINVOKE.Quaternion_LengthSquared(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Normalize() {
    NDalicPINVOKE.Quaternion_Normalize(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion Normalized() {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Normalized(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void Conjugate() {
    NDalicPINVOKE.Quaternion_Conjugate(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Invert() {
    NDalicPINVOKE.Quaternion_Invert(swigCPtr);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public Quaternion Log() {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Log(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Quaternion Exp() {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Exp(swigCPtr), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static float Dot(Quaternion q1, Quaternion q2) {
    float ret = NDalicPINVOKE.Quaternion_Dot(Quaternion.getCPtr(q1), Quaternion.getCPtr(q2));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Quaternion Lerp(Quaternion q1, Quaternion q2, float t) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Lerp(Quaternion.getCPtr(q1), Quaternion.getCPtr(q2), t), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Quaternion Slerp(Quaternion q1, Quaternion q2, float progress) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Slerp(Quaternion.getCPtr(q1), Quaternion.getCPtr(q2), progress), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Quaternion SlerpNoInvert(Quaternion q1, Quaternion q2, float t) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_SlerpNoInvert(Quaternion.getCPtr(q1), Quaternion.getCPtr(q2), t), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static Quaternion Squad(Quaternion start, Quaternion end, Quaternion ctrl1, Quaternion ctrl2, float t) {
    Quaternion ret = new Quaternion(NDalicPINVOKE.Quaternion_Squad(Quaternion.getCPtr(start), Quaternion.getCPtr(end), Quaternion.getCPtr(ctrl1), Quaternion.getCPtr(ctrl2), t), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static float AngleBetween(Quaternion q1, Quaternion q2) {
    float ret = NDalicPINVOKE.Quaternion_AngleBetween(Quaternion.getCPtr(q1), Quaternion.getCPtr(q2));
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector4 Rotate(Vector4 vector) {
    Vector4 ret = new Vector4(NDalicPINVOKE.Quaternion_Rotate__SWIG_0(swigCPtr, Vector4.getCPtr(vector)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector3 Rotate(Vector3 vector) {
    Vector3 ret = new Vector3(NDalicPINVOKE.Quaternion_Rotate__SWIG_1(swigCPtr, Vector3.getCPtr(vector)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public Vector4 mVector {
    set {
      NDalicPINVOKE.Quaternion_mVector_set(swigCPtr, Vector4.getCPtr(value));
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      global::System.IntPtr cPtr = NDalicPINVOKE.Quaternion_mVector_get(swigCPtr);
      Vector4 ret = (cPtr == global::System.IntPtr.Zero) ? null : new Vector4(cPtr, false);
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

}

}