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

public class FlexContainer : View {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal FlexContainer(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.FlexContainer_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(FlexContainer obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~FlexContainer() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_FlexContainer(swigCPtr);
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
            NDalicPINVOKE.delete_FlexContainer_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_FlexContainer_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int CONTENT_DIRECTION = NDalicPINVOKE.FlexContainer_Property_CONTENT_DIRECTION_get();
    public static readonly int FLEX_DIRECTION = NDalicPINVOKE.FlexContainer_Property_FLEX_DIRECTION_get();
    public static readonly int FLEX_WRAP = NDalicPINVOKE.FlexContainer_Property_FLEX_WRAP_get();
    public static readonly int JUSTIFY_CONTENT = NDalicPINVOKE.FlexContainer_Property_JUSTIFY_CONTENT_get();
    public static readonly int ALIGN_ITEMS = NDalicPINVOKE.FlexContainer_Property_ALIGN_ITEMS_get();
    public static readonly int ALIGN_CONTENT = NDalicPINVOKE.FlexContainer_Property_ALIGN_CONTENT_get();
  
  }

  public class ChildProperty : global::System.IDisposable {
    private global::System.Runtime.InteropServices.HandleRef swigCPtr;
    protected bool swigCMemOwn;
  
    internal ChildProperty(global::System.IntPtr cPtr, bool cMemoryOwn) {
      swigCMemOwn = cMemoryOwn;
      swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
    }
  
    internal static global::System.Runtime.InteropServices.HandleRef getCPtr(ChildProperty obj) {
      return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
    }
  
    ~ChildProperty() {
      Dispose();
    }
  
    public virtual void Dispose() {
      lock(this) {
        if (swigCPtr.Handle != global::System.IntPtr.Zero) {
          if (swigCMemOwn) {
            swigCMemOwn = false;
            NDalicPINVOKE.delete_FlexContainer_ChildProperty(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public ChildProperty() : this(NDalicPINVOKE.new_FlexContainer_ChildProperty(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int FLEX = NDalicPINVOKE.FlexContainer_ChildProperty_FLEX_get();
    public static readonly int ALIGN_SELF = NDalicPINVOKE.FlexContainer_ChildProperty_ALIGN_SELF_get();
    public static readonly int FLEX_MARGIN = NDalicPINVOKE.FlexContainer_ChildProperty_FLEX_MARGIN_get();
  
  }

  public FlexContainer () : this (NDalicPINVOKE.FlexContainer_New(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();

  }
  public FlexContainer(FlexContainer handle) : this(NDalicPINVOKE.new_FlexContainer__SWIG_1(FlexContainer.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public FlexContainer Assign(FlexContainer handle) {
    FlexContainer ret = new FlexContainer(NDalicPINVOKE.FlexContainer_Assign(swigCPtr, FlexContainer.getCPtr(handle)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static FlexContainer DownCast(BaseHandle handle) {
    FlexContainer ret = new FlexContainer(NDalicPINVOKE.FlexContainer_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum FlexDirectionType {
    COLUMN,
    COLUMN_REVERSE,
    ROW,
    ROW_REVERSE
  }

  public enum ContentDirectionType {
    INHERIT,
    LTR,
    RTL
  }

  public enum Justification {
    JUSTIFY_FLEX_START,
    JUSTIFY_CENTER,
    JUSTIFY_FLEX_END,
    JUSTIFY_SPACE_BETWEEN,
    JUSTIFY_SPACE_AROUND
  }

  public enum Alignment {
    ALIGN_AUTO,
    ALIGN_FLEX_START,
    ALIGN_CENTER,
    ALIGN_FLEX_END,
    ALIGN_STRETCH
  }

  public enum WrapType {
    NO_WRAP,
    WRAP
  }

  public enum PropertyRange {
    PROPERTY_START_INDEX = PropertyRanges.PROPERTY_REGISTRATION_START_INDEX,
    PROPERTY_END_INDEX = View.PropertyRange.PROPERTY_START_INDEX+1000,
    CHILD_PROPERTY_START_INDEX = PropertyRanges.CHILD_PROPERTY_REGISTRATION_START_INDEX,
    CHILD_PROPERTY_END_INDEX = PropertyRanges.CHILD_PROPERTY_REGISTRATION_START_INDEX+1000
  }

  public int ContentDirection 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.CONTENT_DIRECTION).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.CONTENT_DIRECTION, new Dali.Property.Value( value ) );
    }
  }
  public int FlexDirection 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.FLEX_DIRECTION).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.FLEX_DIRECTION, new Dali.Property.Value( value ) );
    }
  }
  public int FlexWrap 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.FLEX_WRAP).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.FLEX_WRAP, new Dali.Property.Value( value ) );
    }
  }
  public int JustifyContent 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.JUSTIFY_CONTENT).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.JUSTIFY_CONTENT, new Dali.Property.Value( value ) );
    }
  }
  public int AlignItems 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.ALIGN_ITEMS).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.ALIGN_ITEMS, new Dali.Property.Value( value ) );
    }
  }
  public int AlignContent 
  { 
    get 
    {
      int temp = 0;
      GetProperty( FlexContainer.Property.ALIGN_CONTENT).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( FlexContainer.Property.ALIGN_CONTENT, new Dali.Property.Value( value ) );
    }
  }

}

}
