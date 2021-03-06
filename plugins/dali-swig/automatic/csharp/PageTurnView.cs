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


public class PageTurnView : View {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;

  internal PageTurnView(global::System.IntPtr cPtr, bool cMemoryOwn) : base(NDalicPINVOKE.PageTurnView_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(PageTurnView obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~PageTurnView() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          NDalicPINVOKE.delete_PageTurnView(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
      base.Dispose();
    }
  }


public class PagePanStartedEventArgs : EventArgs
{
   private PageTurnView _pageTurnView;

   public PageTurnView PageTurnView
   {
      get
      {
         return _pageTurnView;
      }
      set
      {
         _pageTurnView = value;
      }
   }
}

public class PagePanFinishedEventArgs : EventArgs
{
   private PageTurnView _pageTurnView;

   public PageTurnView PageTurnView
   {
      get
      {
         return _pageTurnView;
      }
      set
      {
         _pageTurnView = value;
      }
   }
}

public class PageTurnStartedEventArgs : EventArgs
{
   private PageTurnView _pageTurnView;
   private uint _pageIndex;
   private bool _isTurningForward;

   public PageTurnView PageTurnView
   {
      get
      {
         return _pageTurnView;
      }
      set
      {
         _pageTurnView = value;
      }
   }

   public uint PageIndex
   {
      get
      {
         return _pageIndex;
      }
      set
      {
         _pageIndex = value;
      }
   }

   public bool IsTurningForward
   {
      get
      {
         return _isTurningForward;
      }
      set
      {
         _isTurningForward = value;
      }
   }

}

public class PageTurnFinishedEventArgs : EventArgs
{
   private PageTurnView _pageTurnView;
   private uint _pageIndex;
   private bool _isTurningForward;

   public PageTurnView PageTurnView
   {
      get
      {
         return _pageTurnView;
      }
      set
      {
         _pageTurnView = value;
      }
   }

   public uint PageIndex
   {
      get
      {
         return _pageIndex;
      }
      set
      {
         _pageIndex = value;
      }
   }

   public bool IsTurningForward
   {
      get
      {
         return _isTurningForward;
      }
      set
      {
         _isTurningForward = value;
      }
   }

}

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PagePanStartedCallbackDelegate(IntPtr page);
  private DaliEventHandler<object,PagePanStartedEventArgs> _pageTurnViewPagePanStartedEventHandler;
  private PagePanStartedCallbackDelegate _pageTurnViewPagePanStartedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PagePanFinishedCallbackDelegate(IntPtr page);
  private DaliEventHandler<object,PagePanFinishedEventArgs> _pageTurnViewPagePanFinishedEventHandler;
  private PagePanFinishedCallbackDelegate _pageTurnViewPagePanFinishedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PageTurnStartedCallbackDelegate(IntPtr page, uint pageIndex, bool isTurningForward);
  private DaliEventHandler<object,PageTurnStartedEventArgs> _pageTurnViewPageTurnStartedEventHandler;
  private PageTurnStartedCallbackDelegate _pageTurnViewPageTurnStartedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PageTurnFinishedCallbackDelegate(IntPtr page, uint pageIndex, bool isTurningForward);
  private DaliEventHandler<object,PageTurnFinishedEventArgs> _pageTurnViewPageTurnFinishedEventHandler;
  private PageTurnFinishedCallbackDelegate _pageTurnViewPageTurnFinishedCallbackDelegate;

  public event DaliEventHandler<object,PagePanStartedEventArgs> PagePanStarted
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_pageTurnViewPagePanStartedEventHandler == null)
           {
              _pageTurnViewPagePanStartedEventHandler += value;

              _pageTurnViewPagePanStartedCallbackDelegate = new PagePanStartedCallbackDelegate(OnPagePanStarted);
              this.PagePanStartedSignal().Connect(_pageTurnViewPagePanStartedCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_pageTurnViewPagePanStartedEventHandler != null)
           {
              this.PagePanStartedSignal().Disconnect(_pageTurnViewPagePanStartedCallbackDelegate);
           }

           _pageTurnViewPagePanStartedEventHandler -= value;
        }
     }
  }

  // Callback for PageTurnView PagePanStarted signal
  private void OnPagePanStarted(IntPtr page)
  {
     PagePanStartedEventArgs e = new PagePanStartedEventArgs();

     // Populate all members of "e" (PagePanStartedEventArgs) with real page
     e.PageTurnView = PageTurnView.GetPageTurnViewFromPtr( page );

     if (_pageTurnViewPagePanStartedEventHandler != null)
     {
        //here we send all page to user event handlers
       _pageTurnViewPagePanStartedEventHandler(this, e);
     }
  }

  public event DaliEventHandler<object,PagePanFinishedEventArgs> PagePanFinished
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_pageTurnViewPagePanFinishedEventHandler == null)
           {
              _pageTurnViewPagePanFinishedEventHandler += value;

              _pageTurnViewPagePanFinishedCallbackDelegate = new PagePanFinishedCallbackDelegate(OnPagePanFinished);
              this.PagePanFinishedSignal().Connect(_pageTurnViewPagePanFinishedCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_pageTurnViewPagePanFinishedEventHandler != null)
           {
              this.PagePanFinishedSignal().Disconnect(_pageTurnViewPagePanFinishedCallbackDelegate);
           }

           _pageTurnViewPagePanFinishedEventHandler -= value;
        }
     }
  }

  // Callback for PageTurnView PagePanFinished signal
  private void OnPagePanFinished(IntPtr page)
  {
     PagePanFinishedEventArgs e = new PagePanFinishedEventArgs();

     // Populate all members of "e" (PagePanFinishedEventArgs) with real page
     e.PageTurnView = PageTurnView.GetPageTurnViewFromPtr( page );

     if (_pageTurnViewPagePanFinishedEventHandler != null)
     {
        //here we send all page to user event handlers
       _pageTurnViewPagePanFinishedEventHandler(this, e);
     }
  }


  public event DaliEventHandler<object,PageTurnStartedEventArgs> PageTurnStarted
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_pageTurnViewPageTurnStartedEventHandler == null)
           {
              _pageTurnViewPageTurnStartedEventHandler += value;

              _pageTurnViewPageTurnStartedCallbackDelegate = new PageTurnStartedCallbackDelegate(OnPageTurnStarted);
              this.PageTurnStartedSignal().Connect(_pageTurnViewPageTurnStartedCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_pageTurnViewPageTurnStartedEventHandler != null)
           {
              this.PageTurnStartedSignal().Disconnect(_pageTurnViewPageTurnStartedCallbackDelegate);
           }

           _pageTurnViewPageTurnStartedEventHandler -= value;
        }
     }
  }

  // Callback for PageTurnView PageTurnStarted signal
  private void OnPageTurnStarted(IntPtr page, uint pageIndex, bool isTurningForward)
  {
     PageTurnStartedEventArgs e = new PageTurnStartedEventArgs();

     // Populate all members of "e" (PageTurnStartedEventArgs) with real page
     e.PageTurnView = PageTurnView.GetPageTurnViewFromPtr( page );
     e.PageIndex = pageIndex;
     e.IsTurningForward = isTurningForward;


     if (_pageTurnViewPageTurnStartedEventHandler != null)
     {
        //here we send all page to user event handlers
       _pageTurnViewPageTurnStartedEventHandler(this, e);
     }
  }


  public event DaliEventHandler<object,PageTurnFinishedEventArgs> PageTurnFinished
  {
     add
     {
        lock(this)
        {
           // Restricted to only one listener
           if (_pageTurnViewPageTurnFinishedEventHandler == null)
           {
              _pageTurnViewPageTurnFinishedEventHandler += value;

              _pageTurnViewPageTurnFinishedCallbackDelegate = new PageTurnFinishedCallbackDelegate(OnPageTurnFinished);
              this.PageTurnFinishedSignal().Connect(_pageTurnViewPageTurnFinishedCallbackDelegate);
           }
        }
     }

     remove
     {
        lock(this)
        {
           if (_pageTurnViewPageTurnFinishedEventHandler != null)
           {
              this.PageTurnFinishedSignal().Disconnect(_pageTurnViewPageTurnFinishedCallbackDelegate);
           }

           _pageTurnViewPageTurnFinishedEventHandler -= value;
        }
     }
  }

  // Callback for PageTurnView PageTurnFinished signal
  private void OnPageTurnFinished(IntPtr page, uint pageIndex, bool isTurningForward)
  {
     PageTurnFinishedEventArgs e = new PageTurnFinishedEventArgs();

     // Populate all members of "e" (PageTurnFinishedEventArgs) with real page
     e.PageTurnView = PageTurnView.GetPageTurnViewFromPtr( page );
     e.PageIndex = pageIndex;
     e.IsTurningForward = isTurningForward;


     if (_pageTurnViewPageTurnFinishedEventHandler != null)
     {
        //here we send all page to user event handlers
       _pageTurnViewPageTurnFinishedEventHandler(this, e);
     }
  }

  public static PageTurnView GetPageTurnViewFromPtr(global::System.IntPtr cPtr) {
    PageTurnView ret = new PageTurnView(cPtr, false);
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
            NDalicPINVOKE.delete_PageTurnView_Property(swigCPtr);
          }
          swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
        }
        global::System.GC.SuppressFinalize(this);
      }
    }
  
    public Property() : this(NDalicPINVOKE.new_PageTurnView_Property(), true) {
      if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    }
  
    public static readonly int PAGE_SIZE = NDalicPINVOKE.PageTurnView_Property_PAGE_SIZE_get();
    public static readonly int CURRENT_PAGE_ID = NDalicPINVOKE.PageTurnView_Property_CURRENT_PAGE_ID_get();
    public static readonly int SPINE_SHADOW = NDalicPINVOKE.PageTurnView_Property_SPINE_SHADOW_get();
  
  }

  public PageTurnView() : this(NDalicPINVOKE.new_PageTurnView__SWIG_0(), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public PageTurnView(PageTurnView handle) : this(NDalicPINVOKE.new_PageTurnView__SWIG_1(PageTurnView.getCPtr(handle)), true) {
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
  }

  public PageTurnView Assign(PageTurnView handle) {
    PageTurnView ret = new PageTurnView(NDalicPINVOKE.PageTurnView_Assign(swigCPtr, PageTurnView.getCPtr(handle)), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static PageTurnView DownCast(BaseHandle handle) {
    PageTurnView ret = new PageTurnView(NDalicPINVOKE.PageTurnView_DownCast(BaseHandle.getCPtr(handle)), true);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PageTurnSignal PageTurnStartedSignal() {
    PageTurnSignal ret = new PageTurnSignal(NDalicPINVOKE.PageTurnView_PageTurnStartedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PageTurnSignal PageTurnFinishedSignal() {
    PageTurnSignal ret = new PageTurnSignal(NDalicPINVOKE.PageTurnView_PageTurnFinishedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PagePanSignal PagePanStartedSignal() {
    PagePanSignal ret = new PagePanSignal(NDalicPINVOKE.PageTurnView_PagePanStartedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PagePanSignal PagePanFinishedSignal() {
    PagePanSignal ret = new PagePanSignal(NDalicPINVOKE.PageTurnView_PagePanFinishedSignal(swigCPtr), false);
    if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public enum PropertyRange {
    PROPERTY_START_INDEX = PropertyRanges.PROPERTY_REGISTRATION_START_INDEX,
    PROPERTY_END_INDEX = View.PropertyRange.PROPERTY_START_INDEX+1000
  }

  public Vector2 PageSize 
  { 
    get 
    {
      Vector2 temp = new Vector2(0.0f,0.0f);
      GetProperty( PageTurnView.Property.PAGE_SIZE).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( PageTurnView.Property.PAGE_SIZE, new Dali.Property.Value( value ) );
    }
  }
  public int CurrentPageId 
  { 
    get 
    {
      int temp = 0;
      GetProperty( PageTurnView.Property.CURRENT_PAGE_ID).Get( ref temp );
      return temp;
    }
    set 
    { 
      SetProperty( PageTurnView.Property.CURRENT_PAGE_ID, new Dali.Property.Value( value ) );
    }
  }
  public Vector2 SpineShadow 
  { 
    get 
    {
      Vector2 temp = new Vector2(0.0f,0.0f);
      GetProperty( PageTurnView.Property.SPINE_SHADOW).Get(  temp );
      return temp;
    }
    set 
    { 
      SetProperty( PageTurnView.Property.SPINE_SHADOW, new Dali.Property.Value( value ) );
    }
  }

}

}