#include <ot4xb_api.h>
#include <ot4xb_version.h>
#include <olectl.h>
#include <ocidl.h>
#include <math.h>
// -----------------------------------------------------------------------------------------------------------------
typedef void (__stdcall * AllowSetForegroundWindow_ft )(LONG);
static AllowSetForegroundWindow_ft AllowSetForegroundWindow_fp = ( AllowSetForegroundWindow_ft )
       GetProcAddress( GetModuleHandle("user32") ,  "AllowSetForegroundWindow" );
// -----------------------------------------------------------------------------------------------------------------
static HWND  _hWndDelegate_    = 0;
static UINT  _nMsgDelegate_    = RegisterWindowMessage( "msg_2EB246C2_D7B0_4AF2_9024_A7C09B584F09" );
static UINT  _nMsgCall32_      = RegisterWindowMessage( "msg_509E9C31_BAA6_4B4C_A381_DCC57D4409CB" );
static UINT  _nMsgFollowFocus_ = RegisterWindowMessage( "msg_15DF97B6_5EFE_4F73_887A_1B02895EAB4B" );
static char  _szWndProc_[]   = "WndProc";
static HHOOK _hHook_FollowFocus_getmsg = 0;
static HHOOK _hHook_FollowFocus_wndproc = 0;
// -----------------------------------------------------------------------------------------------------------------
static DWORD _dwCrc_ot4xb_wnd_  = 0;
// -----------------------------------------------------------------------------------------------------------------
static DWORD _pApplication_UUID_crc_ = 0;
static ContainerHandle _conSingleInstance_ = 0;
//----------------------------------------------------------------------------------------------------------------------
typedef struct OT4XB_WND_CARGO_struct
{
   ContainerHandle Self;
   WNDPROC         pOldProc;
   TStdCtxCbk *    pCbk;
   UINT            nAutoReset;
   LPSTR           pXbMethod;
} OT4XB_WND_CARGO;
// -----------------------------------------------------------------------------------------------------------------
typedef struct OT4XB_HOOK_CARGO_struct
{
   ContainerHandle Self;
   TStdCtxCbk *    pCbk;
   int             iHookType;
   LPSTR           pXbMethod;
   HHOOK           hHook;
   HANDLE          hAuxThread; // not used
} OT4XB_HOOK_CARGO;
// -----------------------------------------------------------------------------------------------------------------
typedef struct OT4XB_RTF_STREAM_IN_struct
{
   LPSTR           p;
   DWORD           cb;
   DWORD           pos;
   DWORD           cargo;   
} OT4XB_RTF_STREAM_IN;
// -----------------------------------------------------------------------------------------------------------------
typedef struct OT4XB_RTF_STREAM_OUT_struct
{
   LPSTR           p;            // 0
   DWORD           cb;           // 4
   DWORD           pos;          // 8
   DWORD           cargo;        // 12
   TByteStream*   ps;            // 16
   DWORD          operation;     // 20
} OT4XB_RTF_STREAM_OUT;
      
// -----------------------------------------------------------------------------------------------------------------
static LRESULT __stdcall _ot4xbxbhookprocwithxbobj_(OT4XB_HOOK_CARGO* pc,int nCode,WPARAM wp,LPARAM lp);
//static LRESULT __stdcall _ot4xbxbhookprocwithxbobj_ex(OT4XB_HOOK_CARGO* pc,int nCode,WPARAM wp,LPARAM lp);
//----------------------------------------------------------------------------------------------------------------------
static LRESULT __stdcall _ot4xbxbwndprocwithxbobj_(OT4XB_WND_CARGO * pc,HWND hWnd,UINT nMsg,WPARAM wp, LPARAM lp)
{
   ContainerHandle pcon[7];
   LRESULT result = 0;
   BOOL    bDefault = TRUE;

   pcon[0] = _conNew(pc->Self);
   pcon[1] = _conPutNL(NULLCONTAINER,(LONG) hWnd     );
   pcon[2] = _conPutNL(NULLCONTAINER,(LONG) nMsg     );
   pcon[3] = _conPutNL(NULLCONTAINER,(LONG) wp       );
   pcon[4] = _conPutNL(NULLCONTAINER,(LONG) lp       );
   pcon[5] = _conPutNL(NULLCONTAINER,(LONG) pc->pOldProc );
   pcon[6] = _conNew(NULLCONTAINER);

   if( (nMsg == pc->nAutoReset) || ( nMsg == WM_NCDESTROY ) )
   {
      TStdCtxCbk *    pCbk     = pc->pCbk;
      WNDPROC         pOldProc = pc->pOldProc;
      SetWindowLong( hWnd,GWL_WNDPROC, (LONG) pOldProc );
      if(pCbk) delete pCbk;
      _conRelease( pc->Self );
      _conPutNL(pcon[5],0);
      _conCallMethodPa( pcon[6],(pc->pXbMethod ? pc->pXbMethod : _szWndProc_),6,pcon);
      _conReleaseM(pcon[0],pcon[1],pcon[2],pcon[3],pcon[4],pcon[5],pcon[6],0);
      if( pc->pXbMethod ){ _xfree( pc->pXbMethod ); pc->pXbMethod = 0;}
      _xfree( (void*) pc );
      return CallWindowProc( pOldProc , hWnd,nMsg,wp,lp );
   }
   _conCallMethodPa( pcon[6],(pc->pXbMethod ? pc->pXbMethod : _szWndProc_),6,pcon);
   if( _conCheckType( pcon[6] , XPP_NUMERIC) ){ _conGetLong(pcon[6],(LONG*) &result); bDefault = FALSE;}
   _conReleaseM(pcon[0],pcon[1],pcon[2],pcon[3],pcon[4],pcon[5],pcon[6],0);
   return ( bDefault ? CallWindowProc( pc->pOldProc , hWnd,nMsg,wp,lp ) : result );
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_CreateGenericWindow
            | syntax_: `ot4xb_CreateGenericWindow( oHandler, [nParentHWnd], [nAutoResetMsg], [cMethod] )`
            | category: windows/window
            | export: OT4XB_CREATEGENERICWINDOW
            | source: WndTool.cpp:OT4XB_CREATEGENERICWINDOW
            | _kw_: ot4xb_CreateGenericWindow, Function
   }}*/
/*{{|desc: Creates a non-visual OT4XB window that receives window messages in the Xbase++ UI thread and
      dispatches them to a selected Xbase++ method.
    | params:
    - `oHandler` object - Xbase++ object or class object used to process the window procedure callbacks.
    - `nParentHWnd` numeric - Parent window handle passed to CreateWindowEx(). If omitted, 0 is used. Use
      HWND_MESSAGE (-3) to create a message-only window.
    - `nAutoResetMsg` numeric - Message that restores the previous window procedure and releases the
      callback cargo. If omitted or 0, WM_NCDESTROY is used.
    - `cMethod` string - Method name invoked on oHandler for window procedure callbacks. If omitted,
      "WndProc" is used. If oHandler is an object instance, the method must be an instance method. If oHandler
      is a class object, it may be a class method.

    Returns numeric - The HWND of the created generic window, or NIL if oHandler is not an object or the
      window cannot be created.

    |note: The callback method receives hWnd, nMsg, nWParam, nLParam, and nOldWndProc.

    |note: If the callback method returns a numeric value, that value is used as the window procedure result.
      If it returns NIL or any non-numeric value, OT4XB calls the previous window procedure.

    |note: The created window uses the internal "_OT4XB_GENERIC_WINDOW_" class. After the subclass procedure is
      installed, OT4XB posts WM_NCCREATE and WM_CREATE to the new window. }}*/
XPPRET XPPENTRY OT4XB_CREATEGENERICWINDOW( XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle Self = _conTParam(pl,1,&bByRef,XPP_OBJECT);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( Self )
   {
      HWND hWnd = CreateWindowEx( 0,"_OT4XB_GENERIC_WINDOW_",0,0,
                                  0,0,0,0,
                                  (HWND) _parLong(pl,2,0),0,
                                  (HINSTANCE) GetModuleHandle(0),0);
      if( hWnd )
      {
         OT4XB_WND_CARGO * pc = (OT4XB_WND_CARGO *) _xgrab( sizeof(OT4XB_WND_CARGO) );
         pc->Self       = _conNew(Self);
         pc->pOldProc   = (WNDPROC) GetWindowLong(hWnd,GWL_WNDPROC);
         pc->nAutoReset = (UINT) _parLong(pl,3,0);
         pc->pXbMethod  = _pszParam(pl,4);
         if( pc->nAutoReset == 0 ){pc->nAutoReset = WM_NCDESTROY;}
         pc->pCbk       = new TStdCtxCbk((DWORD)pc,(DWORD) _ot4xbxbwndprocwithxbobj_ );
         SetWindowLong(hWnd,GWL_WNDPROC, (LONG) pc->pCbk);
         PostMessage( hWnd, WM_NCCREATE ,0,0);
         PostMessage( hWnd, WM_CREATE   ,0,0);
         _conPutNL( conr , (LONG) hWnd );
      }
   }
   if(!bByRef) _conRelease(Self);
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_SubclassWindow
            | syntax_: `ot4xb_SubclassWindow( nHWnd, oHandler, [nAutoResetMsg], [cMethod], [nFlags] )`
            | category: windows/window
            | export: OT4XB_SUBCLASSWINDOW
            | source: WndTool.cpp:OT4XB_SUBCLASSWINDOW
            | _kw_: ot4xb_SubclassWindow, Function
   }}*/
/*{{|desc: Subclasses an existing window and dispatches its window messages to a selected Xbase++ method.
    | params:
    - `nHWnd` numeric - Handle of the existing window to subclass.
    - `oHandler` object - Xbase++ object or class object used to process the window procedure callbacks.
    - `nAutoResetMsg` numeric - Message that restores the previous window procedure and releases the
      callback cargo. If omitted or 0, WM_NCDESTROY is used.
    - `cMethod` string - Method name invoked on oHandler for window procedure callbacks. If omitted,
      "WndProc" is used. If oHandler is an object instance, the method must be an instance method. If oHandler
      is a class object, it may be a class method.
    - `nFlags` numeric - Optional subclassing mode. Set bit 0x8000 to subclass the window through the
      Unicode window procedure slot; otherwise the ANSI slot is used.

    Returns logical - TRUE if the window was subclassed, otherwise FALSE.

    |note: The callback method receives hWnd, nMsg, nWParam, nLParam, and nOldWndProc.

    |note: If the callback method returns a numeric value, that value is used as the window procedure result.
      If it returns NIL or any non-numeric value, OT4XB calls the previous window procedure. }}*/
XPPRET XPPENTRY OT4XB_SUBCLASSWINDOW( XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle Self = _conTParam(pl,2,&bByRef,XPP_OBJECT);
   ContainerHandle conr = _conPutL(NULLCONTAINER,FALSE);
   if( Self )
   {
      HWND hWnd = (HWND) _parLong(pl,1,0);
      BOOL bUnicode = _parLong(pl,5,0) & 0x8000;
      if( hWnd )
      {
         OT4XB_WND_CARGO * pc = (OT4XB_WND_CARGO *) _xgrab( sizeof(OT4XB_WND_CARGO) );
         pc->Self       = _conNew(Self);
         if( bUnicode )
         {
            pc->pOldProc   = (WNDPROC) GetWindowLongW(hWnd,GWL_WNDPROC);
         }
         else
         {
            pc->pOldProc   = (WNDPROC) GetWindowLongA(hWnd,GWL_WNDPROC);
         }
            
         pc->nAutoReset = (UINT) _parLong(pl,3,0);
         pc->pXbMethod  = _pszParam(pl,4);
         if( !pc->nAutoReset ) pc->nAutoReset = WM_NCDESTROY;
         pc->pCbk       = new TStdCtxCbk((DWORD)pc,(DWORD) _ot4xbxbwndprocwithxbobj_ );
         if( bUnicode )
         {
            SetWindowLongW(hWnd,GWL_WNDPROC, (LONG) pc->pCbk);            
         }
         else
         {
            SetWindowLongA(hWnd,GWL_WNDPROC, (LONG) pc->pCbk);                        
         }         
         _conPutL( conr , TRUE);
      }
   }
   if(!bByRef) _conRelease(Self);
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void _ot4xb_xbcall_onnewinstance_( ContainerHandle cona )
{
   _conMCallVoid( _conSingleInstance_ ,"OnNewInstance",cona );
   _conRelease(cona);
}
// -----------------------------------------------------------------------------------------------------------------
static LRESULT __stdcall _ot4xbDelegateProc_(HWND hWnd,UINT nMsg,WPARAM wp, LPARAM lp)
{
   if( nMsg == _nMsgDelegate_ )
   {
      DWORD* pdw = (DWORD*)((void*) lp);
      return _conCallPa((ContainerHandle) pdw[0],(LPSTR) pdw[1], pdw[2] ,(ContainerHandle*) pdw[3]);
   }
   if( nMsg == _nMsgCall32_ )
   {
      LONG   sp1;
      LONG   np;
      DWORD dw;
      _asm mov sp1 ,esp;
      for( np = 0; np < (LONG) wp; np++ )
      {
         dw = reinterpret_cast<DWORD*>(lp)[np];
         _asm mov eax , dw;
         _asm push eax;
      }
      dw = reinterpret_cast<DWORD*>(lp)[wp];
      _asm mov eax , dw;
      _asm call eax;
      _asm mov dw ,eax;
      _asm mov eax ,sp1;
      _asm mov esp ,eax;
      _xfree((void*) lp);
      return (LRESULT) dw;
   }
   if( nMsg == WM_COPYDATA )
   {
      if( wp && lp && _conSingleInstance_ && _pApplication_UUID_crc_ )
      {
         COPYDATASTRUCT* pCds =  reinterpret_cast<COPYDATASTRUCT*>(lp);
         LPSTR pcls = (LPSTR) _xgrab(128);
         DWORD dw   = (DWORD) GetClassName( (HWND) wp , pcls , 127 );
         DWORD ncrc = ( dw ? dwCrc32Lower(0,(BYTE*) pcls, dw) : 0 );
         _xfree((void*) pcls);
         if( !(ncrc == _dwCrc_ot4xb_wnd_) ) return 0;
         if( pCds->dwData == _pApplication_UUID_crc_ )
         {
            LPSTR pData = (LPSTR) _xgrab(pCds->cbData + 4 );
            ContainerHandle cona;
            _bcopy( (LPBYTE) pData , (LPBYTE) pCds->lpData , pCds->cbData );
            ReplyMessage(1);
            cona = _conCallCon("PSzz2Array",(LONG) pData );
            _xfree((void*) pData );
            ot4xb_delay_call_in_gui_thread_(1,(DWORD)_ot4xb_xbcall_onnewinstance_ , cona);
            return 1;
         }
      }
      return 0;
   }
   if( nMsg == WM_DESTROY  )
   {
      if ( hWnd == _hWndDelegate_ ) _hWndDelegate_ = 0;
      SetWindowLong( hWnd,GWL_WNDPROC, (LONG) DefWindowProc );
      return CallWindowProc(DefWindowProc,hWnd,nMsg,wp,lp);
   }
   if( nMsg == WM_COMMAND && lp && (LOWORD(wp) == 0xFFFF) )
   {
      switch( HIWORD(wp) )
      {
         case 1:{  EnableWindow((HWND) lp , 1); return 0;}
         case 2:{  EnableWindow((HWND) lp , 0); return 0;}
         case 3:{  SetForegroundWindow((HWND) lp ); BringWindowToTop((HWND) lp ); return 0;}
      }
   }
   return CallWindowProc(DefWindowProc,hWnd,nMsg,wp,lp);
}
// -----------------------------------------------------------------------------------------------------------------
static LRESULT __stdcall _ot4xbDelegateGen_(WNDPROC pOldProc ,HWND hWnd,UINT nMsg,WPARAM wp, LPARAM lp)
{
   if( ! _dwCrc_ot4xb_wnd_ )
   {
      _dwCrc_ot4xb_wnd_  = dwCrc32Lower(0,(BYTE*)"_OT4XB_GENERIC_WINDOW_",_xstrlen("_OT4XB_GENERIC_WINDOW_"));
   }
   if( nMsg == _nMsgDelegate_ )
   {
      HINSTANCE hm = (HINSTANCE) GetModuleHandle(0);
      HWND      hw = CreateWindowEx( 0,"_OT4XB_GENERIC_WINDOW_",0,0,0,0,0,0,0,0,hm,0);
      if( hw )
      {
         SetWindowLong(hw,GWL_WNDPROC, (LONG) _ot4xbDelegateProc_ );
         _hWndDelegate_ = hw;
      }
      return 0;
   }
   return CallWindowProc(pOldProc,hWnd,nMsg,wp,lp);
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_gen_hwnd_delegate_
            | syntax_: `HWND _ot4xb_gen_hwnd_delegate_( HWND hWnd )`
            | category: windows/delegation
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_gen_hwnd_delegate_
            | _kw_: _ot4xb_gen_hwnd_delegate_, Function
   }}*/
/*{{|desc: Ensures that the internal OT4XB delegate window exists. When it does not exist yet and hWnd is a
      valid window, hWnd is subclassed for the time of one message, so the delegate window is created by the
      thread that owns hWnd; the original window procedure of hWnd is restored before returning. C-level
      counterpart of ot4xb_register_delegate_hwnd().
    | params:
    - `hWnd` HWND - Existing window used to create the delegate window in the thread that owns it.
      Ignored when the delegate window already exists.

    Returns HWND - Handle of the delegate window, or NULL when it does not exist and could not be created. }}*/
HWND OT4XB_API __cdecl _ot4xb_gen_hwnd_delegate_(HWND hWnd)
{
   if( (!_hWndDelegate_) &&  IsWindow(hWnd) )
   {
      LONG nOldProc        = GetWindowLong(hWnd,GWL_WNDPROC);
      TStdCtxCbk* pCbk     = new TStdCtxCbk((DWORD) nOldProc,(DWORD) _ot4xbDelegateGen_ );
      SetWindowLong(hWnd,GWL_WNDPROC, (LONG) pCbk);
      SendMessage( hWnd , _nMsgDelegate_ ,0,0);
      SetWindowLong(hWnd,GWL_WNDPROC,nOldProc);
      delete pCbk;
   }
   return _hWndDelegate_;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_register_delegate_hwnd
            | syntax_: `ot4xb_register_delegate_hwnd( [hWnd | oXbp] )`
            | category: windows/delegation
            | export: OT4XB_REGISTER_DELEGATE_HWND
            | source: WndTool.cpp:OT4XB_REGISTER_DELEGATE_HWND
            | _kw_: ot4xb_register_delegate_hwnd, Function
   }}*/
/*{{|desc: Ensures that the internal OT4XB delegate window exists and returns its window handle.
    | params:
    - `hWnd` numeric - Optional existing window handle used to create the delegate window in the UI thread.
    - `oXbp` object - Optional Xbase++ presentation object whose ::GetHWND() value is used as the window
      handle.

    Returns numeric - Window handle of the internal OT4XB delegate window, or 0 if it could not be created.

    |note: This function is normally called automatically when OT4XB needs to delegate messages or execute code
      in the UI thread of the Xbase++ application. The delegate window is a shared OT4XB infrastructure window.
      Many OT4XB functions reuse this same window to marshal calls or messages to the UI thread. Applications
      may call it explicitly during startup to guarantee that the delegate window already exists before the
      first delegated operation. Calling it more than once is safe: the second and subsequent calls only return
      the already registered delegate window handle. When no window is supplied, OT4XB creates a temporary
      XbpStatic object, uses its HWND to create the delegate window in the UI thread, and destroys the temporary
      object afterwards. }}*/
XPPRET XPPENTRY OT4XB_REGISTER_DELEGATE_HWND( XppParamList pl)
{
   if( !_hWndDelegate_ )
   {
      ContainerHandle  conXbp = NULLCONTAINER;
      HWND             hWnd = ( _partype(pl,0) > 0 ? _parHWND(pl,1,0) : (HWND) 0);
      if( !hWnd )
      {
         conXbp = _conNew(NULLCONTAINER);
         _conEvalMacroStr( conXbp , "XbpStatic():New():Create()" );
         hWnd = (HWND) _conMCallLong(conXbp,"GetHWnd");
      }
      if( IsWindow(hWnd) )
      {
         LONG nOldProc        = GetWindowLong(hWnd,GWL_WNDPROC);
         TStdCtxCbk* pCbk     = new TStdCtxCbk((DWORD) nOldProc,(DWORD) _ot4xbDelegateGen_ );
         SetWindowLong(hWnd,GWL_WNDPROC, (LONG) pCbk);
         SendMessage( hWnd , _nMsgDelegate_ ,0,0);
         SetWindowLong(hWnd,GWL_WNDPROC,nOldProc);
         delete pCbk;
      }
      if( conXbp )
      {
         _conMCallVoid(conXbp, "Destroy");
         _conRelease( conXbp);
         conXbp = NULLCONTAINER;
      }
   }
   _retnl(pl,(LONG) _hWndDelegate_) ;
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_get_hwnd_delegate_
            | syntax_: `HWND _ot4xb_get_hwnd_delegate_( void )`
            | category: windows/delegation
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_get_hwnd_delegate_
            | _kw_: _ot4xb_get_hwnd_delegate_, Function
   }}*/
/*{{|desc: Returns the handle of the internal OT4XB delegate window without trying to create it.

    Returns HWND - Handle of the delegate window, or NULL when it has not been created yet. }}*/
HWND OT4XB_API __cdecl _ot4xb_get_hwnd_delegate_(void){return _hWndDelegate_;}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_set_hwnd_delegate_
            | syntax_: `void _ot4xb_set_hwnd_delegate_( HWND hWnd )`
            | category: windows/delegation
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_set_hwnd_delegate_
            | _kw_: _ot4xb_set_hwnd_delegate_, Function
   }}*/
/*{{|desc: Replaces the stored handle of the internal OT4XB delegate window. The handle is stored as it is,
      without any check; passing NULL makes OT4XB forget the current delegate window.
    | params:
    - `hWnd` HWND - Window handle to store as the delegate window, or NULL to clear it.

    Returns void }}*/
void OT4XB_API __cdecl _ot4xb_set_hwnd_delegate_(HWND hWnd){_hWndDelegate_ = hWnd;}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static ContainerHandle _delegated_xbase_call_( XppParamList pl , LPSTR pFName , ULONG nParamShift = 0, HWND hwnd_target = 0)
{
   ContainerHandle   conr = _conNew(NULLCONTAINER);
   if( hwnd_target == 0 )
   {
      if( _hWndDelegate_ == 0 )
      {
         _conEvalMacroStr( conr , "OT4XB_REGISTER_DELEGATE_HWND()" );
         _conPut(conr,NULLCONTAINER);
      }
      hwnd_target = _hWndDelegate_; 
   }
   if( hwnd_target == 0 )
   {
      TXbGenError e;
      e.subsystem( "OT4XB" );
      e.description("OT4XB Delegate Wnd is not defined");
      e.operation( __FUNCTION__ );
      e.Launch();
   }
   else
   {
      ULONG             np     = _partype(pl,0);
      ContainerHandle*  pcon;
      BOOL *            pbref;
      ULONG n;
      DWORD pdw[4];
      if( np <  nParamShift){np = 0;}
      else { np -= nParamShift; }
      pcon   = (ContainerHandle*) _xgrab( (np +1 ) * sizeof(ContainerHandle));
      pbref  = (BOOL*) _xgrab( (np+1) * sizeof(BOOL));
      for(n=0;n < np; n++) pcon[n] = _conParam(pl,n+1+nParamShift,pbref+n);
      pdw[0] = (DWORD) (void*) conr;
      pdw[1] = (DWORD) (void*) pFName;
      pdw[2] = np;
      pdw[3] = (DWORD) (void*) pcon;
      SendMessage( hwnd_target , _nMsgDelegate_ , 0 , (LPARAM) (void*) pdw );
      for(n=0;n < np; n++){if(!(pbref[n])) _conRelease(pcon[n]);}
      _xfree( (void*) pcon); _xfree( (void*) pbref);
   }
   return conr;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: delegated_xbase_call
            | syntax_: `delegated_xbase_call( nHWnd, cFunctionName, ... )`
            | category: windows/delegation
            | export: DELEGATED_XBASE_CALL
            | source: WndTool.cpp:DELEGATED_XBASE_CALL
            | _kw_: delegated_xbase_call, Function
   }}*/
/*{{|desc: Executes an Xbase++ function in the thread that runs the target window procedure.
    | params:
    - `nHWnd` numeric - Handle of the window whose procedure will receive the delegated call message. If
      NIL, empty, or 0, OT4XB uses its internal delegate window, which runs in the Xbase++ UI thread.
    - `cFunctionName` string - Name of the Xbase++ function to call.
    - `...` any - Parameters passed to the target Xbase++ function.

    Returns any - The value returned by the delegated Xbase++ function.

    |note: The call is sent synchronously with SendMessage(), so the caller waits until the target window
      procedure dispatches the function and returns the result. }}*/
XPPRET XPPENTRY DELEGATED_XBASE_CALL( XppParamList pl)
{
   char fn[256]; ZeroMemory(fn,sizeof(fn));
   if( ! _parc(fn,sizeof(fn),pl,2,0) ){ _ret(pl); return; }
   ContainerHandle   conr = _delegated_xbase_call_(pl,fn,2,(HWND) _parLong(pl,1,0) );
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: delegated_FPQCall
            | syntax_: `delegated_FPQCall( uFunction, cCallTemplate, ... )`
            | category: windows/delegation
            | export: DELEGATED_FPQCALL
            | source: WndTool.cpp:DELEGATED_FPQCALL
            | _kw_: delegated_FPQCall, Function
   }}*/
/*{{|desc: Executes FPQCall in the Xbase++ UI thread through the internal OT4XB delegate window.
    | params:
    - `uFunction` numeric/array - Target function. A numeric value must be a pointer to a cdecl or stdcall
      function. An array value must have the form { hDllOrDllName, cProcName }, where the first element is a DLL
      handle or DLL name and the second element is the exported procedure name.
    - `cCallTemplate` string - FPQCall qualification string. Each four-character group describes one item:
      the first group describes the return value and each following group describes one parameter.
    - `...` any - Parameters passed to the target function according to cCallTemplate.

    Returns any - The value returned by FPQCall after the target function completes.

    |note: The delegated call uses FPQCall and therefore supports cdecl and stdcall functions. It does not
      support fastcall or other calling conventions that pass arguments through registers or use a different
      stack discipline. }}*/
XPPRET XPPENTRY DELEGATED_FPQCALL( XppParamList pl)
{
   ContainerHandle   conr = _delegated_xbase_call_(pl,"FPQCALL");
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: delegated_eval
            | syntax_: `delegated_eval( bBlock, ... )`
            | category: windows/delegation
            | export: DELEGATED_EVAL
            | source: WndTool.cpp:DELEGATED_EVAL
            | _kw_: delegated_eval, Function
   }}*/
/*{{|desc: Evaluates a code block in the Xbase++ UI thread through the internal OT4XB delegate window.
    | params:
    - `bBlock` codeblock - Code block to evaluate.
    - `...` any - Parameters passed to the code block.

    Returns any - The value returned by the evaluated code block.

    |note: The call is delegated synchronously, so the caller waits until the code block is evaluated and the
      result is returned. }}*/
XPPRET XPPENTRY DELEGATED_EVAL( XppParamList pl)
{
   ContainerHandle   conr = _delegated_xbase_call_(pl,"EVAL");
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_call_in_gui_thread_
            | syntax_: `DWORD ot4xb_call_in_gui_thread_( ULONG np, DWORD dwfp, ... )`
            | category: windows/delegation
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_call_in_gui_thread_
            | _kw_: ot4xb_call_in_gui_thread_, Function
   }}*/
/*{{|desc: Calls a function in the thread that owns the OT4XB delegate window, normally the main GUI thread
      of the Xbase++ application. The arguments are packed and sent with SendMessage() to the delegate
      window, whose window procedure pushes them on the stack and calls the function, so the caller waits
      until the call completes. Both __cdecl and __stdcall functions are supported. When the delegate window
      does not exist the function is not called.
    | params:
    - `np` ULONG - Number of variadic arguments that follow dwfp.
    - `dwfp` DWORD - Address of the function to call.
    - `...` DWORD - The np arguments, 32 bits each, passed to the target function in order.

    Returns DWORD - The value returned by the called function, or 0 when the delegate window does not
      exist. }}*/
DWORD OT4XB_API ot4xb_call_in_gui_thread_(ULONG np, DWORD dwfp , ... )
{
   DWORD dwResult = 0;
   if( _hWndDelegate_ )
   {
      DWORD * pStack = (DWORD*) _xgrab( (np + 2) * sizeof(DWORD) );
      ULONG n = np;
      va_list pva;
      pStack[n] = dwfp;
      va_start(pva,dwfp);
      while(n){n--;pStack[n] = va_arg(pva,DWORD);}
      dwResult = (DWORD) SendMessage(_hWndDelegate_,_nMsgCall32_,(WPARAM)np,(LPARAM)pStack);
   }
   return dwResult;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_delay_call_in_gui_thread_
            | syntax_: `DWORD ot4xb_delay_call_in_gui_thread_( ULONG np, DWORD dwfp, ... )`
            | category: windows/delegation
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_delay_call_in_gui_thread_
            | _kw_: ot4xb_delay_call_in_gui_thread_, Function
   }}*/
/*{{|desc: Queues a function call in the thread that owns the OT4XB delegate window, normally the main GUI
      thread of the Xbase++ application. The arguments are packed and posted with PostMessage() to the
      delegate window, whose window procedure pushes them on the stack and calls the function when the
      message is dispatched. The caller does not wait and the value returned by the called function is
      lost. Both __cdecl and __stdcall functions are supported. When the delegate window does not exist
      nothing is queued.
    | params:
    - `np` ULONG - Number of variadic arguments that follow dwfp.
    - `dwfp` DWORD - Address of the function to call.
    - `...` DWORD - The np arguments, 32 bits each, passed to the target function in order.

    Returns DWORD - Nonzero when the call was queued; 0 when posting failed or the delegate window does
      not exist. }}*/
DWORD OT4XB_API ot4xb_delay_call_in_gui_thread_(ULONG np, DWORD dwfp , ... )
{
   DWORD dwResult = 0;
   if( _hWndDelegate_ )
   {
      DWORD * pStack = (DWORD*) _xgrab( (np + 2) * sizeof(DWORD) );
      ULONG n = np;
      va_list pva;
      pStack[n] = dwfp;
      va_start(pva,dwfp);
      while(n){n--;pStack[n] = va_arg(pva,DWORD);}
      dwResult = (DWORD) PostMessage(_hWndDelegate_,_nMsgCall32_,(WPARAM)np,(LPARAM)pStack);
   }
   return dwResult;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static DWORD ot4xb_single_instance_internal(LPSTR pUuid, ContainerHandle cono , ContainerHandle cona )
{
   BOOL  bMustQuit  = FALSE;
   DWORD dwOldProc  = 0;
   DWORD dwCrc      = dwCrc32Lower(0,(BYTE*) pUuid,_xstrlen(pUuid));
   HWND hWndTarget;
   if( _conSingleInstance_){ _conRelease(_conSingleInstance_); _conSingleInstance_ = 0; }
   SetWindowText( _hWndDelegate_ , 0 );
   _pApplication_UUID_crc_ = 0;
   hWndTarget = FindWindowEx(0,0,"_OT4XB_GENERIC_WINDOW_",pUuid);
   if( hWndTarget )
   {
      GetWindowThreadProcessId( hWndTarget ,&dwOldProc);
      COPYDATASTRUCT cds;
      DWORD cb = 0;
      if( cona )
      {
         cds.lpData  = (void*) _conArray2Pszz(cona,&cb);
      }
      else
      {
         cds.lpData  = (void*) ot4xb_pszz_proc_params(&cb);
      }
      cds.cbData  = cb;
      cds.dwData  = dwCrc;
      bMustQuit = SendMessage( hWndTarget , WM_COPYDATA , (WPARAM) _hWndDelegate_ , (LPARAM) &cds );
      _xfree(cds.lpData);
   }
   if( cona){ _conRelease(cona); }
   if( bMustQuit ) { _conRelease(cono); _xfree(pUuid); }
   else
   {
      SetWindowText( _hWndDelegate_ , pUuid );
      _xfree( (void*) pUuid );
      _conSingleInstance_ = cono;
      _pApplication_UUID_crc_ = dwCrc;
   }
   return ( bMustQuit ? dwOldProc : 0 ) ;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_single_instance
            | syntax_: `ot4xb_single_instance( cUniqueId, oController, [aParams], [@nOldProcessId] )`
            | category: windows/application
            | export: OT4XB_SINGLE_INSTANCE
            | source: WndTool.cpp:OT4XB_SINGLE_INSTANCE
            | _kw_: ot4xb_single_instance, Function
   }}*/
/*{{|desc: Registers the current process as the single running instance for an application identifier, or
      notifies the already running instance when one is found.
    | params:
    - `cUniqueId` string - Unique application identifier. A GUID string is commonly used.
    - `oController` object - Controller object for the current application instance. If this process
      becomes the registered instance, the object is stored and later used by this same instance to handle
      ::OnNewInstance() calls.
    - `aParams` array - Parameters sent to the already running instance. If omitted, OT4XB sends the new
      process command line parameters.
    - `nOldProcessId` numeric - Receives the process id of the already running instance when one is found.

    Returns logical - TRUE when another running instance was found and notified; otherwise FALSE.

    |note: Each process calls ot4xb_single_instance() with its own controller object. If no previous instance
      is found, the current process stores that object as the controller for its single-instance delegate
      window.

    |note: If a previous instance is found, the new process sends aParams to that instance and returns TRUE.
      The previous instance then calls ::OnNewInstance( aParams ) on its own stored controller object.

    |note: A typical ::OnNewInstance() handler brings the existing application window to the foreground and
      lets the new process exit. }}*/
XPPRET XPPENTRY OT4XB_SINGLE_INSTANCE( XppParamList pl )
{

   if( _partype(pl,0) < 2 ){ _ret(pl); return;}
   if(!(_partype(pl,1) & XPP_CHARACTER)){ _ret(pl); return;}
   if(!(_partype(pl,2) & XPP_OBJECT)){ _ret(pl); return;}
   if( _hWndDelegate_ == 0 ){ _conCallVoid( "OT4XB_REGISTER_DELEGATE_HWND" ); }
   if( _hWndDelegate_ == 0 )
   {
      TXbGenError e;
      e.subsystem( "OT4XB" );
      e.description("OT4XB Delegate Wnd is not defined");
      e.operation( __FUNCTION__ );
      e.Launch();
   }
   else
   {
      DWORD dwOldProc = ot4xb_call_in_gui_thread_(  3 ,
                                                   (DWORD) ot4xb_single_instance_internal ,
                                                   _pszParam(pl,1),
                                                   _conCopyParam(pl,2),
                                                  (( _partype(pl,3) & XPP_ARRAY) ? _conCopyParam(pl,3) : 0)
                                                );
      _stornl((LONG) dwOldProc,pl,4,0);
      _retl(pl, (BOOL) ( dwOldProc ? 1 : 0 ) );
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: str2ipicture
            | syntax_: `DWORD str2ipicture( void * p, ULONG cb )`
            | header: ot4xb_c_exported.h
            | category: windows/picture
            | mangled-name: str2ipicture
            | _kw_: str2ipicture, Function
   }}*/
/*{{|desc: Creates an OLE picture object from an image held in a memory buffer. The buffer is copied to a
      global memory block, wrapped in a COM stream and loaded with OleLoadPicture(), so any image format
      supported by that function can be used.
    | params:
    - `p` void * - Buffer holding the image data.
    - `cb` ULONG - Size of the image data in bytes.

    Returns DWORD - IPicture interface pointer, or 0 when p or cb is 0 or the image cannot be loaded. The
      caller releases the object through its Release() method. }}*/
extern "C" DWORD OT4XB_API str2ipicture(void* p , ULONG cb)
{
   IPicture* pPicture = NULL;
   if( p && cb )
   {
      HGLOBAL   hGlb     = GlobalAlloc(GMEM_MOVEABLE,cb);
      if( !hGlb ) {return 0; }
      void*     pData    = GlobalLock( hGlb );
      _bcopy((LPBYTE) pData,(LPBYTE) p,cb);
      IStream * pStream  = NULL;
      GlobalUnlock(hGlb);
      HRESULT hr = CreateStreamOnHGlobal(hGlb,TRUE,&pStream);
      if( SUCCEEDED(hr) && pStream )
      {
         hr = OleLoadPicture(pStream,0,FALSE,IID_IPicture,(void**)&pPicture);
         pStream->Release();
         if (FAILED(hr) || pPicture == NULL)
         {
            GlobalFree(hGlb);
         }
      }
      else GlobalFree(hGlb);
   }
   return (DWORD) pPicture;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ipicture2file
            | syntax_: `DWORD ipicture2file( DWORD dwpic, LPSTR fn )`
            | header: ot4xb_c_exported.h
            | category: windows/picture
            | mangled-name: ipicture2file
            | _kw_: ipicture2file, Function
   }}*/
/*{{|desc: Saves an OLE picture object to a picture file with OleSavePictureFile().
    | params:
    - `dwpic` DWORD - IPicture interface pointer, for instance one returned by str2ipicture().
    - `fn` LPSTR - Name of the destination file; the ANSI string is converted to a BSTR for OLE.

    Returns DWORD - The HRESULT of the save operation: 0 when the picture was saved, an error code
      otherwise, or (DWORD) -1 when dwpic is NULL or fn is NULL or empty. }}*/
extern "C" DWORD OT4XB_API ipicture2file(DWORD dwpic,  LPSTR fn )
{
   IPicture* pi = (IPicture*) dwpic;
   BSTR bsfn = 0;
   HRESULT result = (HRESULT)  - 1;
   if (pi && fn)
   {
      UINT cb = _xstrlen(fn);
      if (cb)
      {
         bsfn = SysAllocStringByteLen(0, (cb * 2));
         MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fn, cb, (LPWSTR)bsfn, cb);
      }
      if (bsfn)
      {
         IPictureDisp* pd = NULL;
         if (SUCCEEDED(pi->QueryInterface(IID_IPictureDisp, (void**)&pd)))
         {
            result = OleSavePictureFile(pd, bsfn);
            pd->Release();
            pd = 0;
         }
         SysFreeString(bsfn);
         bsfn = 0;
      }
   }
   return result;


}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: str2hbmp
            | syntax_: `DWORD str2hbmp( void * p, ULONG cb, DWORD nFlags )`
            | header: ot4xb_c_exported.h
            | category: windows/picture
            | mangled-name: str2hbmp
            | _kw_: str2hbmp, Function
   }}*/
/*{{|desc: Creates a GDI bitmap from an image held in a memory buffer. The image is loaded into an OLE
      picture object with str2ipicture(), the bitmap handle of the picture is copied with CopyImage() and
      the picture object is released.
    | params:
    - `p` void * - Buffer holding the image data.
    - `cb` ULONG - Size of the image data in bytes.
    - `nFlags` DWORD - Extra LR_* flags for CopyImage(), combined with LR_COPYRETURNORG.

    Returns DWORD - HBITMAP of the bitmap, or 0 when the image cannot be loaded. The caller destroys it
      with DeleteObject(). }}*/
extern "C" DWORD OT4XB_API str2hbmp(void* p , ULONG cb, DWORD nFlags)
{
   IPicture* pPic = (IPicture*) str2ipicture(p,cb);
   HBITMAP hBmp = 0;
   if(pPic)
   {
      HBITMAP hBmpTmp = 0;
      pPic->get_Handle((UINT*)&hBmpTmp);
      hBmp = (HBITMAP) CopyImage((HANDLE)hBmpTmp,IMAGE_BITMAP,0,0,LR_COPYRETURNORG | nFlags);
      pPic->Release();
   }
   return (DWORD) hBmp;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: istream2xgrab_mem
            | syntax_: `LPVOID istream2xgrab_mem( IStream * pStream, ULONG * pcb )`
            | header: ot4xb_c_exported.h
            | category: windows/stream
            | mangled-name: istream2xgrab_mem
            | _kw_: istream2xgrab_mem, Function
   }}*/
/*{{|desc: Reads the whole content of a COM stream into a new memory block allocated with _xgrab(). The
      stream is measured by seeking to its end and then read from position 0, whatever its current position
      was. The block is allocated one byte larger than the content and zero filled, so text content comes
      back NUL terminated. Empty streams and streams of 4 GB or more are rejected.
    | params:
    - `pStream` IStream * - Stream to read. It is not released by this function.
    - `pcb` ULONG * - Receives the number of bytes read from the stream.

    Returns LPVOID - New block holding the stream content, released by the caller with _xfree(), or NULL
      when pStream or pcb is NULL or the stream is empty or too large. }}*/
extern "C" LPVOID OT4XB_API istream2xgrab_mem(IStream * pStream, ULONG * pcb)
{
   if (pStream && pcb)
   {
      LARGE_INTEGER li;
      li.QuadPart = 0;
      ULARGE_INTEGER licb;
      licb.QuadPart = 0;
      *pcb = 0;
      pStream->Seek(li, STREAM_SEEK_END, &licb);
      if ((licb.HighPart > 0) || (licb.LowPart == 0))
      {
         // discard empty and huge streams
         return 0;
      }
      pStream->Seek(li, STREAM_SEEK_SET, 0);
      void* buffer = _xgrab(licb.LowPart + 1);
      pStream->Read(buffer, licb.LowPart, pcb);
      return buffer;
   }
   return NULL;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: istream_release_and_get_content_as_base64
            | syntax_: `LPSTR istream_release_and_get_content_as_base64( IStream * pStream, DWORD base64_flags )`
            | header: ot4xb_c_exported.h
            | category: windows/stream
            | mangled-name: istream_release_and_get_content_as_base64
            | _kw_: istream_release_and_get_content_as_base64, Function
   }}*/
/*{{|desc: Reads the whole content of a COM stream, releases the stream and returns the content encoded as
      Base64 text in a new NUL terminated string allocated with _xgrab(). The stream is released even when
      its content cannot be read.
    | params:
    - `pStream` IStream * - Stream to read and release.
    - `base64_flags` DWORD - ATL Base64 flags passed to ot4xb_base64_encode(); 2 requests output
      without CRLF line breaks.

    Returns LPSTR - New Base64 string, released by the caller with _xfree(), or NULL when pStream is NULL
      or the stream content cannot be read. }}*/
extern "C" LPSTR OT4XB_API istream_release_and_get_content_as_base64(IStream * pStream , DWORD base64_flags)
{
   if (pStream)
   {
      ULONG bin_buffer_cb = 0;
      void* bin_buffer = istream2xgrab_mem(pStream, &bin_buffer_cb);
      pStream->Release();
      if (bin_buffer)
      {
         int cb = ot4xb_base64_encode_required_length((int)bin_buffer_cb);
         void* buffer = _xgrab(((UINT)cb) + 1);
         ot4xb_base64_encode((LPBYTE)bin_buffer, (int)bin_buffer_cb, (LPSTR)buffer, &cb, base64_flags);
         _xfree(bin_buffer);
         bin_buffer = NULL;
         return (LPSTR) buffer;
      }
   }
   return NULL;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: str2istream
            | syntax_: `DWORD str2istream( void * p, ULONG cb )`
            | category: windows/stream
            | header: ot4xb_c_exported.h
            | mangled-name: str2istream
            | _kw_: str2istream, Function
   }}*/
/*{{|desc: Creates a COM stream holding a copy of a memory buffer. The buffer is copied to a global memory
      block wrapped with CreateStreamOnHGlobal(); the block is released together with the stream. The
      initial stream position is 0.
    | params:
    - `p` void * - Buffer to copy into the stream.
    - `cb` ULONG - Number of bytes to copy; (ULONG) -1 treats p as a NUL terminated string and uses
      its length.

    Returns DWORD - IStream interface pointer, or 0 when p or cb is 0 or the stream cannot be created.
      The caller releases the stream through its Release() method. }}*/
extern "C" DWORD OT4XB_API str2istream(void* p , ULONG cb)
{
   if( cb ==  ((DWORD) -1) )
   {
      cb = 0;
      if( p ){ cb = _xstrlen((LPSTR) p ); }
   }
   if( p && cb )
   {
      HGLOBAL   hGlb     = GlobalAlloc(GMEM_MOVEABLE,cb);
      if (hGlb)
      {
         void* pData = GlobalLock(hGlb);
         _bcopy((LPBYTE)pData, (LPBYTE)p, cb);
         IStream* pStream = NULL;
         GlobalUnlock(hGlb);
         HRESULT hr = CreateStreamOnHGlobal(hGlb, TRUE, &pStream);
         if (SUCCEEDED(hr) && pStream)
         {
            return (DWORD)pStream;
         }
         else
         {
            GlobalFree(hGlb);
         }
      }
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static BOOL ot4xb_hooktype_from_string( LPSTR pStr , int* pht , LPSTR* ppxm )
{
   if( !pStr ){ return FALSE; }
   switch( dwCrc32Lower(0,(LPBYTE) pStr, _xstrlen(pStr)) )
   {
      case 0xF2D74027: /* "journalrecord" */ {static char sz[] = "journalrecord_hookproc";pht[0]= WH_JOURNALRECORD;
                       ppxm[0] = sz;return TRUE;}
      case 0x5A77879A: /* "journalplayback" */ {static char sz[] = "journalplayback_hookproc";pht[0]= WH_JOURNALPLAYBACK;
                       ppxm[0] = sz;return TRUE;}
      case 0x83748095: /* "keyboard" */ {static char sz[] = "keyboard_hookproc";pht[0]= WH_KEYBOARD;
                       ppxm[0] = sz;return TRUE;}
      case 0xC58EC3FF: /* "getmessage" */ {static char sz[] = "getmessage_hookproc";pht[0]= WH_GETMESSAGE;
                       ppxm[0] = sz;return TRUE;}
      case 0xDC90E3F5: /* "callwndproc" */ {static char sz[] = "callwndproc_hookproc";pht[0]= WH_CALLWNDPROC;
                       ppxm[0] = sz;return TRUE;}
      case 0xB573106B: /* "cbt" */ {static char sz[] = "cbt_hookproc";pht[0]= WH_CBT;
                       ppxm[0] = sz;return TRUE;}
      case 0xBFF4BBD3: /* "sysmsgfilter" */ {static char sz[] = "sysmsgfilter_hookproc";pht[0]= WH_SYSMSGFILTER;
                       ppxm[0] = sz;return TRUE;}
      case 0xAF35B6ED: /* "mouse" */ {static char sz[] = "mouse_hookproc";pht[0]= WH_MOUSE;
                       ppxm[0] = sz;return TRUE;}
      case 0x6CA547A7: /* "debug" */ {static char sz[] = "debug_hookproc";pht[0]= WH_DEBUG;
                       ppxm[0] = sz;return TRUE;}
      case 0x4592B2FD: /* "shell" */ {static char sz[] = "shell_hookproc";pht[0]= WH_SHELL;
                       ppxm[0] = sz;return TRUE;}
      case 0x9C0CFB4D: /* "foregroundidle" */ {static char sz[] = "foregroundidle_hookproc";pht[0]= WH_FOREGROUNDIDLE;
                       ppxm[0] = sz;return TRUE;}
      case 0xD185CD67: /* "callwndprocret" */ {static char sz[] = "callwndprocret_hookproc";pht[0]= WH_CALLWNDPROCRET;
                       ppxm[0] = sz;return TRUE;}
      case 0x82DEEEB1: /* "keyboard_ll" */ {static char sz[] = "keyboard_ll_hookproc";pht[0]= WH_KEYBOARD_LL;
                       ppxm[0] = sz;return TRUE;}
      case 0x50FB3706: /* "mouse_ll" */ {static char sz[] = "mouse_ll_hookproc";pht[0]= WH_MOUSE_LL;
                       ppxm[0] = sz;return TRUE;}
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_HookThread
            | syntax_: `ot4xb_HookThread( cHookType, oHandler, [nThreadId] )`
            | category: windows/hooks
            | export: OT4XB_HOOKTHREAD
            | source: WndTool.cpp:OT4XB_HOOKTHREAD
            | _kw_: ot4xb_HookThread, Function
   }}*/
/*{{|desc: Installs a Windows hook inside the current process and dispatches hook callbacks to a method of an
      Xbase++ handler object.
    | params:
    - `cHookType` string - Hook type name recognized by OT4XB. Valid values are "journalrecord",
      "journalplayback", "keyboard", "getmessage", "callwndproc", "cbt", "sysmsgfilter", "mouse", "debug",
      "shell", "foregroundidle", "callwndprocret", "keyboard_ll", and "mouse_ll".
    - `oHandler` object - Xbase++ object that implements the hook callback method selected by cHookType.
    - `nThreadId` numeric - Target thread id. If omitted, the current thread id is used. The target thread
      must belong to the current process context.

    Returns numeric - Internal hook cargo pointer used later by ot4xb_UnhookThread(), or 0 if the hook cannot
      be installed.

    |note: When the hook is no longer needed, pass the returned nHookCargo value to ot4xb_UnhookThread() to
      remove the hook and release its internal callback resources.

    |note: The selected handler method receives nCode, nWParam, nLParam, and nHookCargo.

    |note: If the handler method returns a numeric value, that value is returned from the hook procedure and
      OT4XB does not call CallNextHookEx(). If it returns NIL or any non-numeric value, OT4XB calls
      CallNextHookEx().

    |note: This function is for hooks that run inside the current process. OT4XB passes NULL as the module
      handle to SetWindowsHookEx(), so the hook procedure is not supplied from a DLL that Windows can inject
      into other processes.

    |note: Global hooks for external processes are not supported. A global hook would require a native DLL that
      Windows can load into arbitrary target processes, but an Xbase++ extension DLL requires an already
      initialized Xbase++ process.

    |note: The hook type selects one of these handler methods: ::journalrecord_hookproc(),
      ::journalplayback_hookproc(), ::keyboard_hookproc(), ::getmessage_hookproc(), ::callwndproc_hookproc(),
      ::cbt_hookproc(), ::sysmsgfilter_hookproc(), ::mouse_hookproc(), ::debug_hookproc(), ::shell_hookproc(),
      ::foregroundidle_hookproc(), ::callwndprocret_hookproc(), ::keyboard_ll_hookproc(), and
      ::mouse_ll_hookproc(). }}*/
_XPP_REG_FUN_( OT4XB_HOOKTHREAD )
{
   TXppParamList xpp(pl,4);
   int   iht    = 0;
   LPSTR pxm    = 0;
   xpp[0]->PutLong(0);
   if( ot4xb_hooktype_from_string(xpp[1]->LockStr(),&iht,&pxm) && xpp[2]->CheckType(XPP_OBJECT) )
   {
      OT4XB_HOOK_CARGO * pc = (OT4XB_HOOK_CARGO *) _xgrab( sizeof(OT4XB_HOOK_CARGO) );
      pc->Self       = _conNew(xpp[2]->Get());
      pc->iHookType  = iht;
      pc->pXbMethod  = pxm;
      pc->pCbk       = new TStdCtxCbk((DWORD)pc,(DWORD) _ot4xbxbhookprocwithxbobj_ );
      if( xpp[3]->CheckType(XPP_NUMERIC) )
      {
         pc->hHook = SetWindowsHookEx( iht, (HOOKPROC) pc->pCbk ,0, xpp[3]->GetDWord());
      }
      else
      {
         pc->hHook = SetWindowsHookEx( iht, (HOOKPROC) pc->pCbk ,0, GetCurrentThreadId());
      }
      if(pc->hHook)
      {
         xpp[0]->PutLong( (LONG) pc );
      }
      else
      {
         delete pc->pCbk;
         _conRelease( pc->Self );
         _xfree((void*) pc);
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_UnhookThread
            | syntax_: `ot4xb_UnhookThread( nHookCargo )`
            | category: windows/hooks
            | export: OT4XB_UNHOOKTHREAD
            | source: WndTool.cpp:OT4XB_UNHOOKTHREAD
            | _kw_: ot4xb_UnhookThread, Function
   }}*/
/*{{|desc: Removes a thread hook installed by ot4xb_HookThread() and releases the internal hook callback
      resources.
    | params:
    - `nHookCargo` numeric - Internal hook cargo pointer returned by ot4xb_HookThread().

    Returns nil - Always returns NIL.

    |note: If nHookCargo is not 0, OT4XB calls UnhookWindowsHookEx(), releases the stored Xbase++ handler
      object, deletes the callback wrapper, and frees the hook cargo block.

    |note: The nHookCargo value must not be reused after this function returns. }}*/
_XPP_REG_FUN_( OT4XB_UNHOOKTHREAD )
{
   OT4XB_HOOK_CARGO * pc = (OT4XB_HOOK_CARGO *) _parLong(pl,1,0);
   if( pc )
   {
      UnhookWindowsHookEx(pc->hHook );
      _conRelease( pc->Self );
      delete pc->pCbk;
      _xfree((void*) pc);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static LRESULT __stdcall _ot4xbxbhookprocwithxbobj_(OT4XB_HOOK_CARGO* pc,int nCode,WPARAM wp,LPARAM lp)
{
   ContainerHandle pcon[6];
   LRESULT result = 0;
   BOOL    bCallNextHook = TRUE;
   pcon[0] = _conNew(pc->Self);
   pcon[1] = _conPutNL(NULLCONTAINER,(LONG) nCode    );
   pcon[2] = _conPutNL(NULLCONTAINER,(LONG) wp       );
   pcon[3] = _conPutNL(NULLCONTAINER,(LONG) lp       );
   pcon[4] = _conPutNL(NULLCONTAINER,(LONG) pc->hHook);
   pcon[5] = _conNew(NULLCONTAINER);
   _conCallMethodPa( pcon[5],pc->pXbMethod,5,pcon);
   if( _conCheckType( pcon[5] , XPP_NUMERIC ) )
   {
      bCallNextHook = FALSE;
      _conGetLong(pcon[5],(LONG*) &result);
   }
   _conReleasePa(pcon,6);
   if( bCallNextHook ) result = CallNextHookEx(pc->hHook,nCode,wp,lp);
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _create_font_
            | syntax_: ```
            | header: ot4xb_c_exported.h
                 HFONT _create_font_( HDC hDC, LPSTR szFaceName, int iDeciPtHeight, int iDeciPtWidth, int iAttributes, BOOL fLogRes)
              ```
            | category: windows/font
            | mangled-name: _create_font_
            | _kw_: _create_font_, Function
   }}*/
/*{{|desc: Creates a GDI font from a face name and a character height given in tenths of a point. The
      device context is used to convert the point size to device units; its state is saved and restored
      around the computation. When iDeciPtWidth is not 0 the font is created twice, so that the average
      character width matches the requested width.
    | params:
    - `hDC` HDC - Device context used to compute the font size in device units.
    - `szFaceName` LPSTR - Face name of the font.
    - `iDeciPtHeight` int - Character height in tenths of a point.
    - `iDeciPtWidth` int - Average character width in tenths of a point, or 0 to keep the default
      width of the face.
    - `iAttributes` int - Attribute bits: 1 bold, 2 italic, 4 underline, 8 strike out.
    - `fLogRes` BOOL - TRUE sizes the font with the logical resolution of the device; FALSE uses the
      physical resolution computed from the device size in millimeters.

    Returns HFONT - The new font, destroyed by the caller with DeleteObject(). }}*/
extern "C" HFONT OT4XB_API _create_font_(HDC hDC, LPSTR szFaceName, int iDeciPtHeight,int iDeciPtWidth, int iAttributes, BOOL fLogRes)
{
   FLOAT      cxDpi, cyDpi;
   HFONT      hFont;
   LOGFONT    lf;
   POINT      pt;
   TEXTMETRIC tm;

   SaveDC (hDC) ;
   SetGraphicsMode (hDC, GM_ADVANCED) ;
   ModifyWorldTransform (hDC, NULL, MWT_IDENTITY) ;
   SetViewportOrgEx (hDC, 0, 0, NULL) ;
   SetWindowOrgEx   (hDC, 0, 0, NULL) ;
   if (fLogRes)
   {
      cxDpi = (FLOAT) GetDeviceCaps (hDC, LOGPIXELSX) ;
      cyDpi = (FLOAT) GetDeviceCaps (hDC, LOGPIXELSY) ;
   }
   else
   {
      cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hDC, HORZRES) / GetDeviceCaps(hDC, HORZSIZE)) ;
      cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hDC, VERTRES) / GetDeviceCaps(hDC, VERTSIZE)) ;
   }
   pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
   pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
   DPtoLP (hDC, &pt, 1) ;
   lf.lfHeight         = - (int) (fabs((FLOAT)pt.y) / 10.0 + 0.5) ;
   lf.lfWidth          = 0 ;
   lf.lfEscapement     = 0 ;
   lf.lfOrientation    = 0 ;
   lf.lfWeight         = (LONG) (iAttributes & 1 ? 700 : 0 ); // Bold
   lf.lfItalic         = (BYTE) (iAttributes & 2 ?   1 : 0 );
   lf.lfUnderline      = (BYTE) (iAttributes & 4 ?   1 : 0 );
   lf.lfStrikeOut      = (BYTE) (iAttributes & 8 ?   1 : 0 );
   lf.lfCharSet        = 0 ;
   lf.lfOutPrecision   = 0 ;
   lf.lfClipPrecision  = 0 ;
   lf.lfQuality        = 0 ;
   lf.lfPitchAndFamily = 0 ;

   _xstrcpy (lf.lfFaceName, szFaceName) ;

   hFont = CreateFontIndirect (&lf) ;

   if (iDeciPtWidth != 0)
   {
      hFont = (HFONT) SelectObject (hDC, hFont) ;
      GetTextMetrics (hDC, &tm) ;
      DeleteObject (SelectObject (hDC, hFont)) ;
      lf.lfWidth = (int) (tm.tmAveCharWidth * fabs((FLOAT)pt.x) / fabs((FLOAT)pt.y) + 0.5) ;
      hFont = CreateFontIndirect (&lf) ;
   }
   RestoreDC (hDC, -1) ;
   return hFont ;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_ForceForegroundWindow
            | syntax_: `void ot4xb_ForceForegroundWindow( HWND hWnd )`
            | category: windows/window
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_ForceForegroundWindow
            | _kw_: ot4xb_ForceForegroundWindow, Function
   }}*/
/*{{|desc: Forces a window to become the foreground window, working around the foreground lock that keeps a
      background process from stealing the focus. When the foreground window belongs to another thread, the
      input queues of both threads are attached, the foreground lock timeout is temporarily removed and
      AllowSetForegroundWindow() is called before SetForegroundWindow(). Nothing is done when hWnd is not a
      valid window.
    | params:
    - `hWnd` HWND - Window to bring to the foreground.

    Returns void }}*/
void OT4XB_API  ot4xb_ForceForegroundWindow(HWND hWnd)
{
   if(!IsWindow(hWnd)) return;
   DWORD nTimeOut       = 0;
   HWND  hPrevFWnd      = GetForegroundWindow();
   DWORD nNewThreadId   = GetCurrentThreadId();
   DWORD nOldThreadId   = GetWindowThreadProcessId(hPrevFWnd,0);
   if(nNewThreadId != nOldThreadId)
   {
      AttachThreadInput(nNewThreadId, nOldThreadId, TRUE);
      SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT,0,&nTimeOut,0);
      SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT,0,0,SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
      if(AllowSetForegroundWindow_fp){ (*AllowSetForegroundWindow_fp)(-1);}
      SetForegroundWindow(hWnd);
      SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT,0,(void*)nTimeOut,SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
      AttachThreadInput(nNewThreadId, nOldThreadId, FALSE);
      return;
   }
   SetForegroundWindow(hWnd);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ForceForegroundWindow
            | syntax_: `void ForceForegroundWindow( HWND hWnd )`
            | category: windows/window
            | header: ot4xb_c_exported.h
            | mangled-name: ForceForegroundWindow
            | _kw_: ForceForegroundWindow, Function
   }}*/
/*{{|desc: Forces a window to become the foreground window from the thread that owns the OT4XB delegate
      window. The delegate window is created through hWnd when it does not exist yet, and
      ot4xb_ForceForegroundWindow() is then executed in the delegate thread. Nothing is done when the
      delegate window cannot be created.
    | params:
    - `hWnd` HWND - Window to bring to the foreground.

    Returns void }}*/
void OT4XB_API ForceForegroundWindow(HWND hWnd)
{
   _ot4xb_gen_hwnd_delegate_(hWnd);
   ot4xb_call_in_gui_thread_(  1 , (DWORD) ot4xb_ForceForegroundWindow , hWnd );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _best_font_size_from_list_
            | syntax_: `WORD _best_font_size_from_list_( WORD wav, WORD * lst, UINT wc )`
            | category: windows/font
            | header: ot4xb_c_exported.h
            | mangled-name: _best_font_size_from_list_
            | _kw_: _best_font_size_from_list_, Function
   }}*/
/*{{|desc: Selects a font size from a list of candidates, where every size packs two byte values in a WORD
      (LOBYTE and HIBYTE). The list is walked from the last entry towards the first and the first entry
      whose two bytes are both less than or equal to the corresponding bytes of wav is returned, so with a
      list sorted in ascending order the biggest size that fits is selected.
    | params:
    - `wav` WORD - Available size; its two packed byte values act as upper limits.
    - `lst` WORD * - List of packed candidate sizes.
    - `wc` UINT - Number of entries in lst.

    Returns WORD - The selected entry of lst, or 0 when no entry fits. }}*/
WORD OT4XB_API _best_font_size_from_list_( WORD wav , WORD* lst , UINT wc )
{
   BYTE l = LOBYTE(wav);
   BYTE h = HIBYTE(wav);
   while( wc )
   {
      WORD s = lst[(--wc)];
      if( (LOBYTE(s) <= l) && (HIBYTE(s) <= h) ) return s;
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_generic_message_loop_no_translate
            | syntax_: `void ot4xb_generic_message_loop_no_translate( void )`
            | category: windows/message-loop
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_generic_message_loop_no_translate
            | _kw_: ot4xb_generic_message_loop_no_translate, Function
   }}*/
/*{{|desc: Runs a message loop for the calling thread, dispatching every message with DispatchMessage()
      until GetMessage() reports WM_QUIT or fails. TranslateMessage() is not called, so keyboard messages
      are not translated into character messages.

    Returns void }}*/
extern "C" void OT4XB_API ot4xb_generic_message_loop_no_translate(void)
{
   for(;;)
   {
      MSG msg;   
      int n = (int) GetMessage(&msg,0,0,0);
      if( (n == 0)|| (n == -1)){ return; }
      DispatchMessage(&msg);
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_generic_message_loop
            | syntax_: `void ot4xb_generic_message_loop( void )`
            | category: windows/message-loop
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_generic_message_loop
            | _kw_: ot4xb_generic_message_loop, Function
   }}*/
/*{{|desc: Runs a standard message loop for the calling thread, translating keyboard messages with
      TranslateMessage() and dispatching every message with DispatchMessage(), until GetMessage() reports
      WM_QUIT or fails.

    Returns void }}*/
extern "C" void OT4XB_API ot4xb_generic_message_loop(void)
{
   for(;;)
   {
      MSG msg;   
      int n = (int) GetMessage(&msg,0,0,0);
      if( (n == 0)|| (n == -1)){ return; }
      TranslateMessage(&msg);
      DispatchMessage(&msg);      
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
class ot4xb_automatic_scroll_focus_t : public T_ot4xb_base
{
   public:
   // ---------------------------------------------------------------------------------   
   HWND m_hDlg;
   HWND m_hPanel;
   LONG m_height;
   LONG m_max_scroll;   
   LONG m_scroll_pos;
   BOOL m_disable_wheel;
   LONG m_vrow_size;
   
   // ---------------------------------------------------------------------------------      
   static void set( HWND hDlg , HWND hPanel , LONG height , LONG vr , BOOL mw )
   {
      new ot4xb_automatic_scroll_focus_t(hDlg,hPanel,height,vr,mw);   
   }
   // ---------------------------------------------------------------------------------
   static LRESULT __stdcall hook_proc_getmsg( int code , WPARAM _wp , LPARAM _lp )
   {
      if( (code == HC_ACTION) && ( _wp == PM_REMOVE) && _lp && (reinterpret_cast<MSG*>(_lp)->message == WM_MOUSEWHEEL))
      {
         HWND hWnd = reinterpret_cast<MSG*>(_lp)->hwnd;
         if( hWnd )
         {
            HWND hParent = GetAncestor(hWnd,GA_PARENT );
            if( hParent )
            {
               PostMessage(hParent,_nMsgFollowFocus_,WM_MOUSEWHEEL,reinterpret_cast<MSG*>(_lp)->wParam); 
            }
         }
      }
      return CallNextHookEx( _hHook_FollowFocus_getmsg , code , _wp , _lp );
   };
   // ---------------------------------------------------------------------------------
   static LRESULT __stdcall hook_proc_wndproc( int code , WPARAM _wp , LPARAM _lp )
   {
      if( (code == HC_ACTION) && _lp && (reinterpret_cast<CWPSTRUCT*>(_lp)->message == WM_SETFOCUS) )
      {
         HWND hWnd = reinterpret_cast<CWPSTRUCT*>(_lp)->hwnd;
         if( hWnd )
         {
            HWND hParent = GetAncestor(hWnd,GA_PARENT );
            if( hParent )
            {
               PostMessage(hParent,_nMsgFollowFocus_,WM_SETFOCUS,(LPARAM) hWnd); 
            }
         }
      }
      return CallNextHookEx( _hHook_FollowFocus_wndproc , code , _wp , _lp );
   };   
   
   // ---------------------------------------------------------------------------------
   ot4xb_automatic_scroll_focus_t( HWND hDlg , HWND hPanel , LONG height , LONG v_row_size , BOOL disable_wheel)   
   {
      m_disable_wheel = disable_wheel;
      m_vrow_size = v_row_size;
      if( !_hHook_FollowFocus_getmsg )
      {
         _hHook_FollowFocus_getmsg  = SetWindowsHookEx( WH_GETMESSAGE,hook_proc_getmsg,0,GetCurrentThreadId());
      }         
      if( !_hHook_FollowFocus_wndproc)
      {
         _hHook_FollowFocus_wndproc = SetWindowsHookEx( WH_CALLWNDPROC,hook_proc_wndproc,0,GetCurrentThreadId());      
      }   
      SetWindowLong(hDlg,GWL_STYLE,GetWindowLong(hDlg,GWL_STYLE) | WS_VSCROLL);
      SetWindowPos(hDlg,0,0,0,0,0,SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_NOSIZE|SWP_FRAMECHANGED);
      m_hDlg    = hDlg;
      m_hPanel  = hPanel;
      m_height  = height;      
      on_dlg_resize();
      _TSTDCTXCBK_SUBCLASS_( hDlg  ,proxi_dlgproc  ,this);
      _TSTDCTXCBK_SUBCLASS_( hPanel,proxi_panelproc,this); 
           
   };
   // ---------------------------------------------------------------------------------
   ~ot4xb_automatic_scroll_focus_t()
   {
      ;
   }   
   // ---------------------------------------------------------------------------------
   void on_dlg_resize()
   {

      RECT rc;   
      GetClientRect(m_hDlg, &rc);
      if( m_height < 1 ){ m_height = rc.bottom; }      
      m_max_scroll = m_height - rc.bottom;   
      SetWindowPos(m_hPanel,(HWND) 0,0,0,rc.right,m_height,SWP_NOOWNERZORDER|SWP_NOZORDER);
      m_scroll_pos = 0;
      if( m_max_scroll < 0 ){ m_max_scroll = 0; }
      SCROLLINFO si; ZeroMemory( &si , sizeof(si)); si.cbSize = sizeof(si);
      if( m_max_scroll > 0 )
      {
         si.nMin = 0;
         si.nMax = m_max_scroll;
         si.nPage = m_vrow_size;
         si.nPos  = m_scroll_pos;
         si.fMask = SIF_ALL;
         SetScrollInfo(m_hDlg,SB_VERT,&si,1);
      }      
   }
   // ---------------------------------------------------------------------------------
   void HandleVScroll( WORD wScroll , WORD wAction )
   {
      SCROLLINFO si;
      if( m_max_scroll )
      {
         switch( wAction)
         {
            case SB_TOP:           { m_scroll_pos = 0; break;  }
            case SB_BOTTOM :       { m_scroll_pos = m_max_scroll; break; }
            case SB_THUMBTRACK:
            case SB_THUMBPOSITION: { m_scroll_pos = (LONG) ((__int16) wScroll ); break; }
            case SB_LINEDOWN:
            case SB_PAGEDOWN:      { m_scroll_pos += m_vrow_size; break;  }
            case SB_LINEUP:
            case SB_PAGEUP:        { m_scroll_pos -= m_vrow_size; break;  }
            default: { return; }
         }
         if( m_scroll_pos < (m_vrow_size >> 1) ){ m_scroll_pos = 0; }
         if( m_scroll_pos > m_max_scroll ){ m_scroll_pos = m_max_scroll; }
         if( (m_max_scroll - m_scroll_pos) < m_vrow_size ){ m_scroll_pos = m_max_scroll; }
         ZeroMemory( &si , sizeof(si));
         si.cbSize = sizeof(si);
         si.fMask  = SIF_POS;
         si.nPos   = m_scroll_pos;
         SetScrollInfo(m_hDlg,SB_VERT,&si,TRUE);
         SetWindowPos(m_hPanel,0,0,(0 - m_scroll_pos),0,0,SWP_NOZORDER|SWP_NOSIZE);
      }
   }
   // ---------------------------------------------------------------------------------
   void HandleWheel( LONG nDelta)
   {
      if( m_max_scroll )      
      {
         SCROLLINFO si;      
         m_scroll_pos -= (LONG) (nDelta/2);
         if( m_scroll_pos < 0 ){ m_scroll_pos = 0; }
         if( m_scroll_pos > m_max_scroll ){ m_scroll_pos = m_max_scroll; }
         ZeroMemory( &si , sizeof(si));
         si.cbSize = sizeof(si);
         si.fMask  = SIF_POS;
         si.nPos   = m_scroll_pos;
         SetScrollInfo(m_hDlg,SB_VERT,&si,TRUE);
         SetWindowPos( m_hPanel,0,0,(0 - m_scroll_pos),0,0,SWP_NOZORDER|SWP_NOSIZE);
      }
   }   
   // ---------------------------------------------------------------------------------
   void on_edit_focus(HWND hEdit)
   {
      if( m_max_scroll < 1 ) return;
      RECT rce;
      RECT rcc;
      GetWindowRect(hEdit,&rce);      
      ScreenToClient(m_hPanel,_mk_ptr_( LPPOINT , &rce , 0 ));
      ScreenToClient(m_hPanel,_mk_ptr_( LPPOINT , &rce , sizeof(LONG) * 2 ));
      GetClientRect(m_hDlg,&rcc);      
            
      if( (rce.top - m_scroll_pos) < 0 )
      {
         HandleVScroll( LOWORD( rce.top - m_vrow_size ), SB_THUMBPOSITION);
         return; 
      }
      
      if( ( (rce.bottom +m_vrow_size) - m_scroll_pos) > rcc.bottom )
      {
         HandleVScroll( LOWORD( (rce.bottom - rcc.bottom) + m_vrow_size ), SB_THUMBPOSITION);      
      }
   }
   // ---------------------------------------------------------------------------------   
   static LRESULT __stdcall proxi_dlgproc( DWORD* ctx, HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp )
   {
      WNDPROC old_proc = (WNDPROC) ctx[ 1 ]; if( ( nMsg == g_nMsgProxiRemoveSubclass ) || ( nMsg == 0x0082 ) )
      {
         WNDPROC oldproc = reinterpret_cast<WNDPROC>( ctx[ 1 ] );
         reinterpret_cast<ot4xb_automatic_scroll_focus_t*>( ctx[ 0 ] )->dlg_proc( hWnd, nMsg, wp, lp, old_proc );
         SetWindowLongA( hWnd, ( -4 ), ctx[ 1 ] );
         delete reinterpret_cast<TStdCtxCbk*>( ctx[ 2 ] );
         _xfree( (void*) ctx );
         if( nMsg == g_nMsgProxiRemoveSubclass )
         {
            return 0;
         } return CallWindowProcA( oldproc, hWnd, nMsg, wp, lp );
      } return reinterpret_cast<ot4xb_automatic_scroll_focus_t*>( ctx[ 0 ] )->dlg_proc( hWnd, nMsg, wp, lp, old_proc );
   };
   LRESULT dlg_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)   
   {
      switch( nMsg)
      {
         case WM_SIZE:
         {
            if( wp != SIZE_MINIMIZED )
            {
               on_dlg_resize(); 
            }
            return DefWindowProc( hWnd,nMsg,wp,lp );            
         }
         case WM_NCDESTROY:         
         {
            delete this;
            return 0; // the proxi will call the oldproc anyway
         }
         case WM_VSCROLL:
         {
            HandleVScroll( HIWORD( wp) , LOWORD(wp));
            return 0;
         }         
      }
      return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);      
   }
   // ---------------------------------------------------------------------------------
   static LRESULT __stdcall proxi_panelproc( DWORD* ctx, HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp )
   {
      WNDPROC old_proc = (WNDPROC) ctx[ 1 ]; if( ( nMsg == g_nMsgProxiRemoveSubclass ) || ( nMsg == 0x0082 ) )
      {
         WNDPROC oldproc = reinterpret_cast<WNDPROC>( ctx[ 1 ] ); reinterpret_cast< ot4xb_automatic_scroll_focus_t* >( ctx[ 0 ] )->panel_proc( hWnd, nMsg, wp, lp, old_proc ); SetWindowLongA( hWnd, ( -4 ), ctx[ 1 ] ); delete reinterpret_cast<TStdCtxCbk*>( ctx[ 2 ] ); _xfree( (void*) ctx ); if( nMsg == g_nMsgProxiRemoveSubclass )
         {
            return 0;
         } return CallWindowProcA( oldproc, hWnd, nMsg, wp, lp );
      } return reinterpret_cast< ot4xb_automatic_scroll_focus_t* >( ctx[ 0 ] )->panel_proc( hWnd, nMsg, wp, lp, old_proc );
   };
   LRESULT panel_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)   
   {
      if( nMsg == _nMsgFollowFocus_ )
      {
         switch( wp )
         {
            case WM_MOUSEWHEEL:
            {
               if( m_disable_wheel ){ return 0;}
               HWND hFocus = GetFocus();
               if( (hFocus) && (hFocus != m_hDlg) && (hFocus != m_hPanel) && GetProp(hFocus,"WantTheWheel") )
               {
                  return 0;
               }
               HandleWheel( (LONG) ((short) HIWORD(lp)));
               return 0;                        
            }
            case WM_SETFOCUS:
            {
               if( IsWindow((HWND) lp) ){ on_edit_focus((HWND) lp); }
               return 0;                        
            }            
         }
      }
      return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);         
   }   
   // ---------------------------------------------------------------------------------   
        
};
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_automatic_scroll_focus
            | syntax_: `ot4xb_automatic_scroll_focus( hDlg, hPanel, nContentHeight, [nStep], [lDisableWheel] )`
            | category: windows/scrolling
            | export: OT4XB_AUTOMATIC_SCROLL_FOCUS
            | source: WndTool.cpp:OT4XB_AUTOMATIC_SCROLL_FOCUS
            | _kw_: ot4xb_automatic_scroll_focus, Function
   }}*/
/*{{|desc: Enables automatic vertical scrolling for a dialog/container and its child panel, keeping the focused
      child control visible.
    | params:
    - `hDlg` numeric/object - HWND or Xbase Part object for the dialog or container that receives the
      vertical scrollbar.
    - `hPanel` numeric/object - HWND or Xbase Part object for the child panel that contains the controls
      and is moved vertically inside hDlg.
    - `nContentHeight` numeric - Total virtual height of the panel content. If less than 1, the current
      client height of hDlg is used.
    - `nStep` numeric - Scroll step and focus margin size. If omitted, 20 is used.
    - `lDisableWheel` logical - If TRUE, mouse wheel messages forwarded by the follow-focus hook are
      ignored by this automatic scroll handler.

    Returns numeric - Registered internal follow-focus message id used by the installed hooks and subclass
      procedures.

    |note: hDlg is subclassed to handle WM_SIZE and WM_VSCROLL. hPanel is subclassed to receive the internal
      follow-focus message used for focus and mouse wheel forwarding.

    |note: When a child control receives focus, OT4XB calculates its position inside hPanel. If the control is
      outside the visible client area of hDlg, hPanel is moved vertically so the control becomes visible.

    |note: OT4XB installs thread-local WH_GETMESSAGE and WH_CALLWNDPROC hooks the first time this feature is
      enabled. These hooks observe WM_MOUSEWHEEL and WM_SETFOCUS in the current thread and post the internal
      follow-focus message to the parent window.

    |note: Mouse wheel scrolling is skipped when lDisableWheel is TRUE. It is also skipped when the focused
      child window has the "WantTheWheel" property, allowing that control to keep the wheel message for its own
      use. }}*/
_XPP_REG_FUN_( OT4XB_AUTOMATIC_SCROLL_FOCUS )
{
   TXppParamList xpp(pl,5);
   if( _hWndDelegate_ == 0 ){ _conCallVoid( "OT4XB_REGISTER_DELEGATE_HWND" ); }
   if( _hWndDelegate_ == 0 )
   {
      TXbGenError e;
      e.subsystem( "OT4XB" );
      e.description("OT4XB Delegate Wnd is not defined");
      e.operation( __FUNCTION__ );
      e.Launch();
      return;
   }   
   HWND hDlg = xpp[1]->GetHWND(); if( !hDlg ){ return ;} if( !IsWindow(hDlg)  ){ return ;}
   HWND hPan = xpp[2]->GetHWND(); if( !hPan ){ return ;} if( !IsWindow(hPan)  ){ return ;} 
   LONG cy   = xpp[3]->GetLong();  
   LONG vrs  = ( xpp[4]->CheckType(XPP_NUMERIC) ?  xpp[4]->GetLong() : 20 );
   BOOL mw  = xpp[5]->GetBool();
   ot4xb_call_in_gui_thread_(  5 ,(DWORD) ot4xb_automatic_scroll_focus_t::set , hDlg, hPan ,cy,vrs,mw);
   xpp[0]->PutDWord(_nMsgFollowFocus_);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// the old ODBD MsgBar dll
// -----------------------------------------------------------------------------------------------------------------

static void PaintTheMsgRect( HDC hDC , RECT * prct , COLORREF * pclr , LPSTR pText , int nTxtLen,int iAlign ) 
{

  HPEN    hPen     = (HPEN) SelectObject(hDC,GetStockObject(WHITE_PEN));
  
  if ( pclr ) 
  {                  
    HBRUSH  hbr  = CreateSolidBrush( (COLORREF) * pclr );
    FillRect(hDC,prct,hbr);
    DeleteObject(hbr);
  }   
  MoveToEx(hDC,prct->left,prct->bottom,0); LineTo(hDC,prct->right,prct->bottom);
  MoveToEx(hDC,prct->right,prct->top,0); LineTo(hDC,prct->right,prct->bottom);
  SelectObject( hDC,CreatePen(PS_SOLID,1,RGB(128,128,128)) );
  MoveToEx(hDC,prct->left,prct->bottom + 1,0); LineTo(hDC,prct->left,prct->top);
  LineTo(hDC,prct->right,prct->top);
  DeleteObject(SelectObject(hDC,hPen)); 
  InflateRect(prct,-2,-1);
  if ( pText ) 
  {
     int ibk = SetBkMode(hDC,TRANSPARENT);
     DrawText(hDC,pText,nTxtLen,prct,DT_SINGLELINE | DT_VCENTER | iAlign);
     SetBkMode(hDC,ibk);
  }
  InflateRect(prct,2,1);
  return;
} 
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_PaintTheMsgBar
            | syntax_: `ot4xb_PaintTheMsgBar( hWnd, nMeter, cMeter, cCaption, [nTextFlags] )`
            | category: windows/painting
            | export: OT4XB_PAINTTHEMSGBAR
            | source: WndTool.cpp:OT4XB_PAINTTHEMSGBAR
            | _kw_: ot4xb_PaintTheMsgBar, Function
   }}*/
/*{{|desc: Paints a message bar with text and an optional progress/meter area using the client area of a window
      or control.
    | params:
    - `hWnd` numeric - Window or control handle whose client area is painted.
    - `nMeter` numeric - Meter value. If less than 0, the meter area is not painted.
    - `cMeter` string - Text drawn inside the meter area when nMeter is enabled.
    - `cCaption` string - Text drawn in the main caption area.
    - `nTextFlags` numeric - Additional DrawText() flags ORed with DT_LEFT for the caption area.

    Returns nil - Always returns NIL.

    |note: This is a legacy quick-and-dirty GDI painting helper. It paints directly over the client area of the
      target window or control and does not implement a full status bar control.

    |note: The optional meter area uses a fixed 161-pixel width and an old custom scale for nMeter. }}*/
_XPP_REG_FUN_( OT4XB_PAINTTHEMSGBAR )
{
  HWND    hWnd      = ( HWND ) _parnl(pl,1);
  int     iMeter    = ( int ) _parnl(pl,2);
  int     iLen;
  HDC     hDC       = GetDC(hWnd);
  HDC     hDCMem    = CreateCompatibleDC(hDC);
  HBITMAP hBmMem;
  char   lpCaption[512];
  RECT    rct;
  HBRUSH  oldBrush;
  HPEN    oldPen  ;
  
  ZeroMemory(lpCaption,sizeof(lpCaption));
  iLen = (int) _parc(lpCaption,511,pl,4);
  GetClientRect( hWnd , &rct);
  hBmMem = CreateCompatibleBitmap( hDC,rct.right,rct.bottom);
  hBmMem = (HBITMAP) SelectObject(hDCMem,hBmMem);
  
  oldBrush = (HBRUSH) SelectObject(hDCMem,GetStockObject(LTGRAY_BRUSH));
  oldPen   = (HPEN) SelectObject(hDCMem,GetStockObject(BLACK_PEN));
  FillRect(hDCMem,&rct,(HBRUSH) GetStockObject(LTGRAY_BRUSH));
  MoveToEx(hDCMem,0,0,0); LineTo(hDCMem,rct.right,0);
  SelectObject(hDCMem,GetStockObject(WHITE_PEN));
  MoveToEx(hDCMem,0,1,0); LineTo(hDCMem,rct.right,1);
  rct.left += 2 ; rct.top += 2; rct.right -= 1 ; rct.bottom -= 1;
  if (iMeter > -1 )
  {
     char  pMeter[256];
     int  nLen        = _parc(pMeter,255,pl,3);
     RECT  rctMeter;
     COLORREF clr = RGB(0,0,128);
     COLORREF oldClrText = SetTextColor(hDCMem,RGB(255,255,255));
     CopyRect(&rctMeter,&rct); 
     rctMeter.right = rctMeter.left + 161; rct.left = rctMeter.right +6;
     PaintTheMsgRect(hDCMem ,&rctMeter,&clr,pMeter ,nLen, DT_CENTER); 
     SetTextColor(hDCMem,oldClrText);
     rctMeter.left += (int) ( (iMeter * 16)/10 );
     if (rctMeter.left < rctMeter.right) InvertRect(hDCMem,&rctMeter);
  }
  PaintTheMsgRect(hDCMem ,&rct,0,lpCaption ,iLen, DT_LEFT | (int) (_parnl(pl,5)) );
  SelectObject( hDCMem,oldBrush); SelectObject( hDCMem, oldPen);
  GetClientRect(hWnd,&rct);
  BitBlt(hDC,0,0,rct.right,rct.bottom,hDCMem,0,0,SRCCOPY);  
  DeleteObject(SelectObject(hDCMem,hBmMem));
  DeleteDC(hDCMem);
  ReleaseDC(hWnd,hDC);
  _ret(pl); return;
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_rtf_stream_in
            | syntax_: `DWORD ot4xb_rtf_stream_in( DWORD dwctx, LPBYTE pOut, LONG cbOut, LONG * pcb )`
            | category: windows/rich-edit
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_rtf_stream_in@16
            | _kw_: ot4xb_rtf_stream_in, Function
   }}*/
/*{{|desc: Stream callback used to feed buffered text into a rich edit control. It has the shape the
      EM_STREAMIN message expects from an EDITSTREAMCALLBACK: every call copies the next chunk of the
      source buffer into the buffer supplied by the control, until the source is exhausted.
    | params:
    - `dwctx` DWORD - Context pointer passed by the control as the EDITSTREAM cookie. It points to a
      structure holding the source buffer address (offset 0), its total size (offset 4) and the read
      position (offset 8), which is advanced on every call.
    - `pOut` LPBYTE - Buffer of the control that receives the next chunk.
    - `cbOut` LONG - Capacity of pOut in bytes.
    - `pcb` LONG * - Receives the number of bytes copied; 0 signals the end of the data.

    Returns DWORD - Always 0, which tells the control to continue. }}*/
DWORD OT4XB_API __stdcall ot4xb_rtf_stream_in(DWORD dwctx, LPBYTE pOut , LONG cbOut , LONG* pcb )
{
   OT4XB_RTF_STREAM_IN* ctx = (OT4XB_RTF_STREAM_IN*) dwctx;
   DWORD dwMax   = ( (ctx->cb > ctx->pos) ? (ctx->cb - ctx->pos) : 0 );
   DWORD dw      = (DWORD) cbOut;
   if( dw > dwMax )
   { 
      dw = dwMax;
   }
   if( dw )
   {
      _bcopy(pOut,_mk_ptr_(LPBYTE , ctx->p, ctx->pos),dw);
      ctx->pos += dw;
   }
   pcb[0] = (LONG) dw;
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_rtf_stream_out
            | syntax_: `DWORD ot4xb_rtf_stream_out( DWORD dwctx, LPBYTE pOut, LONG cbOut, LONG * pcb )`
            | category: windows/rich-edit
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_rtf_stream_out@16
            | _kw_: ot4xb_rtf_stream_out, Function
   }}*/
/*{{|desc: Stream callback and context manager used to collect the text streamed out of a rich edit
      control with the EM_STREAMOUT message. The context holds a result buffer address at offset 0, its
      size at offset 4 and an operation code at offset 20 that selects what each call does: with dwctx 0 a
      new context is allocated, an internal byte stream is prepared, the operation is set to 1 and the
      context is returned; operation 1 is the EDITSTREAMCALLBACK role, appending every chunk received from
      the control to the byte stream; operation 2, set by the caller after the streaming, moves the
      collected bytes to a plain buffer published at offsets 0 and 4 and sets the operation to 3;
      operation 3 releases the buffer and the context.
    | params:
    - `dwctx` DWORD - Context pointer, used as the EDITSTREAM cookie; 0 allocates and initializes a
      new context.
    - `pOut` LPBYTE - Buffer with the chunk sent by the control; used only by operation 1.
    - `cbOut` LONG - Size of the chunk in bytes; used only by operation 1.
    - `pcb` LONG * - Receives the number of bytes accepted; used only by operation 1.

    Returns DWORD - The new context pointer on the initial call, (DWORD) -1 for an unknown operation
      code, 0 otherwise. }}*/
DWORD OT4XB_API __stdcall ot4xb_rtf_stream_out(DWORD dwctx, LPBYTE pOut , LONG cbOut , LONG* pcb )
{
   if( dwctx == 0 )
   {
      dwctx = (DWORD) _xgrab( sizeof( OT4XB_RTF_STREAM_OUT ) );
   }
   
   OT4XB_RTF_STREAM_OUT* ctx = (OT4XB_RTF_STREAM_OUT*) dwctx;
   switch( ctx->operation )
   {
      case 0: // init
      {
         ctx->ps =  new TByteStream(65536,65536);
         ctx->operation = 1;
         return dwctx;
      }
      case 1: // work
      {
         ctx->ps->Add(pOut,cbOut);
         pcb[0] = cbOut;
         return 0;
      }
      case 2: // finalize
      {
         ctx->p = (LPSTR) ctx->ps->Detach((UINT*) &ctx->cb,0);
         ctx->ps = 0;
         ctx->operation = 3;         
         return 0;
      }
      case 3: // release
      {
         if( ctx->p) _xfree( ctx->p );
         _xfree( (void*) ctx );
         return 0;
      }      
   }
   return (DWORD) -1;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
HWND __stdcall ot4xb_fake_CreateWindowEx_xbasecontainer(  DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,
                                                   int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,
                                                   HINSTANCE hInstance,LPVOID lpParam)
{
   ContainerHandle Self = (ContainerHandle) _ot4xb_hook_createwindowex_(0);
   if( Self )
   {
      ContainerHandle pcon[14];
      HWND hWnd = 0;
               
      pcon[0]  = _conNew(Self);
      pcon[1]  = _conPutNL(NULLCONTAINER, (LONG)  dwExStyle     );
      pcon[2]  = _conPutNL(NULLCONTAINER, (LONG)  lpClassName   );
      pcon[3]  = _conPutNL(NULLCONTAINER, (LONG)  lpWindowName  );
      pcon[4]  = _conPutNL(NULLCONTAINER, (LONG)  dwStyle       );
      pcon[5]  = _conPutNL(NULLCONTAINER, (LONG)  X             );
      pcon[6]  = _conPutNL(NULLCONTAINER, (LONG)  Y             );
      pcon[7]  = _conPutNL(NULLCONTAINER, (LONG)  nWidth        );
      pcon[8]  = _conPutNL(NULLCONTAINER, (LONG)  nHeight       );
      pcon[9]  = _conPutNL(NULLCONTAINER, (LONG)  hWndParent    );
      pcon[10] = _conPutNL(NULLCONTAINER, (LONG)  hMenu         );
      pcon[11] = _conPutNL(NULLCONTAINER, (LONG)  hInstance     );
      pcon[12] = _conPutNL(NULLCONTAINER, (LONG)  lpParam       );
      pcon[13] = _conNew(NULLCONTAINER);
       
      _conCallMethodPa( pcon[13],"createwindowex_hook",13,pcon);
      hWnd = _conGetHWND( pcon[13] );
      _conReleasePa(pcon,14);
      return hWnd;
   }
   return CreateWindowExA(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam);
}
// -----------------------------------------------------------------------------------------------------------------
#define OT4XB_FAKE_CREATEWINDOWSEXA_PROP_ID_ "031938d9-83d9-44a6-8e6d-7c5e878fd8fa"
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_hook_createwindowex_
            | syntax_: `DWORD _ot4xb_hook_createwindowex_( HANDLE con )`
            | category: windows/window
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_hook_createwindowex_
            | _kw_: _ot4xb_hook_createwindowex_, Function
   }}*/
/*{{|desc: Support function for routing a CreateWindowExA() call to an Xbase++ object. Called with
      (HANDLE) -1 it returns the address of the OT4XB replacement for CreateWindowExA(): when a handler is
      registered, the replacement calls its ::createwindowex_hook() method with the twelve
      CreateWindowExA() arguments and returns the window handle produced by the method; without a
      registered handler it calls the original CreateWindowExA(). Called with a container handle from the
      thread that owns the OT4XB delegate window, it registers that handler for the next hooked call;
      called with NULL it returns the registered handler and clears the registration.
    | params:
    - `con` HANDLE - (HANDLE) -1 to obtain the replacement function address; a container handle to
      register the handler object; NULL to fetch and clear the registered handler.

    Returns DWORD - The replacement function address, the previously registered container handle, or 0
      after registering a handler and on any call outside the delegate window thread. }}*/
OT4XB_API DWORD _ot4xb_hook_createwindowex_(HANDLE con)
{
   if( con == (HANDLE) -1 )
   {
      return (DWORD) ot4xb_fake_CreateWindowEx_xbasecontainer;
   }
   
   if( _hWndDelegate_ )
   {
      if( GetCurrentThreadId() == GetWindowThreadProcessId(_hWndDelegate_,0) )
      {
         if( con ) 
         {
            SetProp(_hWndDelegate_, OT4XB_FAKE_CREATEWINDOWSEXA_PROP_ID_ , con ); 
            return 0;
         }
         else
         {
            con = GetProp(_hWndDelegate_, OT4XB_FAKE_CREATEWINDOWSEXA_PROP_ID_ );
            RemoveProp(_hWndDelegate_, OT4XB_FAKE_CREATEWINDOWSEXA_PROP_ID_ );
            return (DWORD) con;
         }
      }
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
