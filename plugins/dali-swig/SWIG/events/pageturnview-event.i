/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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

%define PAGETURNVIEW_EVENTHANDLER_TYPEMAP_EVENTARG(NameSpace, ClassName)
%typemap(csimports) NameSpace::ClassName %{
using System;
using System.Runtime.InteropServices;

%}
%enddef

%define PAGETURNVIEW_EVENTHANDLER_TYPEMAP_HELPER(NameSpace, ClassName)
%typemap(cscode) NameSpace::ClassName %{

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
  public delegate void PagePanStartedEventHandler(object source, PagePanStartedEventArgs e);

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  public delegate void PagePanFinishedEventHandler(object source, PagePanFinishedEventArgs e);

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  public delegate void PageTurnStartedEventHandler(object source, PageTurnStartedEventArgs e);

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  public delegate void PageTurnFinishedEventHandler(object source, PageTurnFinishedEventArgs e);

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PagePanStartedCallbackDelegate(IntPtr page);
  private PagePanStartedEventHandler _pageTurnViewPagePanStartedEventHandler;
  private PagePanStartedCallbackDelegate _pageTurnViewPagePanStartedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PagePanFinishedCallbackDelegate(IntPtr page);
  private PagePanFinishedEventHandler _pageTurnViewPagePanFinishedEventHandler;
  private PagePanFinishedCallbackDelegate _pageTurnViewPagePanFinishedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PageTurnStartedCallbackDelegate(IntPtr page, uint pageIndex, bool isTurningForward);
  private PageTurnStartedEventHandler _pageTurnViewPageTurnStartedEventHandler;
  private PageTurnStartedCallbackDelegate _pageTurnViewPageTurnStartedCallbackDelegate;

  [UnmanagedFunctionPointer(CallingConvention.StdCall)]
  private delegate void PageTurnFinishedCallbackDelegate(IntPtr page, uint pageIndex, bool isTurningForward);
  private PageTurnFinishedEventHandler _pageTurnViewPageTurnFinishedEventHandler;
  private PageTurnFinishedCallbackDelegate _pageTurnViewPageTurnFinishedCallbackDelegate;

  public event PagePanStartedEventHandler PagePanStarted
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

  public event PagePanFinishedEventHandler PagePanFinished
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


  public event PageTurnStartedEventHandler PageTurnStarted
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


  public event PageTurnFinishedEventHandler PageTurnFinished
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

  public static ClassName Get ## ClassName ## FromPtr(global::System.IntPtr cPtr) {
    ClassName ret = new ClassName(cPtr, false);
   if (NDalicPINVOKE.SWIGPendingException.Pending) throw NDalicPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

%}

%enddef


%define DALI_PAGETURNVIEW_EVENTHANDLER_PARAM( NameSpace, ClassName)

  PAGETURNVIEW_EVENTHANDLER_TYPEMAP_EVENTARG( NameSpace, ClassName);
  PAGETURNVIEW_EVENTHANDLER_TYPEMAP_HELPER( NameSpace, ClassName);

%enddef

namespace Dali
{
  DALI_PAGETURNVIEW_EVENTHANDLER_PARAM( Dali::Toolkit, PageTurnView);
}
