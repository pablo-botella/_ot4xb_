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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY OT4XB_SUBCLASSWINDOW( XppParamList pl) // ot4xb_subclasswindow( hWnd,oHandler, nMsgReset,cMethod,nFlags)
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
HWND OT4XB_API __cdecl _ot4xb_get_hwnd_delegate_(void){return _hWndDelegate_;}
void OT4XB_API __cdecl _ot4xb_set_hwnd_delegate_(HWND hWnd){_hWndDelegate_ = hWnd;}
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
XPPRET XPPENTRY DELEGATED_XBASE_CALL( XppParamList pl) // DELEGATED_XBASE_CALL( hWnd , fn,... )
{
   char fn[256]; ZeroMemory(fn,sizeof(fn));
   if( ! _parc(fn,sizeof(fn),pl,2,0) ){ _ret(pl); return; }
   ContainerHandle   conr = _delegated_xbase_call_(pl,fn,2,(HWND) _parLong(pl,1,0) );
   _conReturn(pl,conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DELEGATED_FPQCALL( XppParamList pl)
{
   ContainerHandle   conr = _delegated_xbase_call_(pl,"FPQCALL");
   _conReturn(pl,conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DELEGATED_EVAL( XppParamList pl)
{
   ContainerHandle   conr = _delegated_xbase_call_(pl,"EVAL");
   _conReturn(pl,conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY OT4XB_SINGLE_INSTANCE( XppParamList pl ) //  s:_cAppUUID_ , oApp , aParams ,[@dwOldProcessId] )
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
// -----------------------------------------------------------------------------------------------------------------
extern "C" DWORD OT4XB_API str2ipicture(void* p , ULONG cb)
{
   IPicture* pPicture = NULL;
   if( p && cb )
   {
      HGLOBAL   hGlb     = GlobalAlloc(GMEM_MOVEABLE,cb);
      void*     pData    = GlobalLock( hGlb );
      _bcopy((LPBYTE) pData,(LPBYTE) p,cb);
      IStream * pStream  = NULL;
      GlobalUnlock(hGlb);
      CreateStreamOnHGlobal(hGlb,TRUE,&pStream);
      if( pStream )
      {
         OleLoadPicture(pStream,0,FALSE,IID_IPicture,(void**)&pPicture);
         pStream->Release();
      }
      else GlobalFree(hGlb);
   }
   return (DWORD) pPicture;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" DWORD OT4XB_API ipicture2file(DWORD dwpic,  LPSTR fn )
{
   IPicture* pi = (IPicture*) dwpic;
   BSTR bsfn = 0;
   HRESULT result = -1;
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
         if (SUCCEEDED(CreateStreamOnHGlobal(hGlb, TRUE, &pStream) && pStream) )
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
// -----------------------------------------------------------------------------------------------------------------
static BOOL ot4xb_hooktype_from_string( LPSTR pStr , int* pht , LPSTR* ppxm )
{
   if( !pStr ){ return FALSE; }
   switch( dwCrc32Lower(0,(LPBYTE) pStr, _xstrlen(pStr)) )
   {
      case 0xF2D74027:{static char sz[] = "journalrecord_hookproc";pht[0]= WH_JOURNALRECORD;
                       ppxm[0] = sz;return TRUE;}
      case 0x5A77879A:{static char sz[] = "journalplayback_hookproc";pht[0]= WH_JOURNALPLAYBACK;
                       ppxm[0] = sz;return TRUE;}
      case 0x83748095:{static char sz[] = "keyboard_hookproc";pht[0]= WH_KEYBOARD;
                       ppxm[0] = sz;return TRUE;}
      case 0xC58EC3FF:{static char sz[] = "getmessage_hookproc";pht[0]= WH_GETMESSAGE;
                       ppxm[0] = sz;return TRUE;}
      case 0xDC90E3F5:{static char sz[] = "callwndproc_hookproc";pht[0]= WH_CALLWNDPROC;
                       ppxm[0] = sz;return TRUE;}
      case 0xB573106B:{static char sz[] = "cbt_hookproc";pht[0]= WH_CBT;
                       ppxm[0] = sz;return TRUE;}
      case 0xBFF4BBD3:{static char sz[] = "sysmsgfilter_hookproc";pht[0]= WH_SYSMSGFILTER;
                       ppxm[0] = sz;return TRUE;}
      case 0xAF35B6ED:{static char sz[] = "mouse_hookproc";pht[0]= WH_MOUSE;
                       ppxm[0] = sz;return TRUE;}
      case 0x6CA547A7:{static char sz[] = "debug_hookproc";pht[0]= WH_DEBUG;
                       ppxm[0] = sz;return TRUE;}
      case 0x4592B2FD:{static char sz[] = "shell_hookproc";pht[0]= WH_SHELL;
                       ppxm[0] = sz;return TRUE;}
      case 0x9C0CFB4D:{static char sz[] = "foregroundidle_hookproc";pht[0]= WH_FOREGROUNDIDLE;
                       ppxm[0] = sz;return TRUE;}
      case 0xD185CD67:{static char sz[] = "callwndprocret_hookproc";pht[0]= WH_CALLWNDPROCRET;
                       ppxm[0] = sz;return TRUE;}
      case 0x82DEEEB1:{static char sz[] = "keyboard_ll_hookproc";pht[0]= WH_KEYBOARD_LL;
                       ppxm[0] = sz;return TRUE;}
      case 0x50FB3706:{static char sz[] = "mouse_ll_hookproc";pht[0]= WH_MOUSE_LL;
                       ppxm[0] = sz;return TRUE;}
   }
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_HOOKTHREAD ) //  ot4xb_hookthread(cHType,Self,dwThreadId)
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_UNHOOKTHREAD ) // ot4xb_unhookthread(pc)
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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
void OT4XB_API ForceForegroundWindow(HWND hWnd)
{
   _ot4xb_gen_hwnd_delegate_(hWnd);
   ot4xb_call_in_gui_thread_(  1 , (DWORD) ot4xb_ForceForegroundWindow , hWnd );
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
      SetWindowPos(m_hPanel,0,0,0,rc.right,m_height,SWP_NOOWNERZORDER|SWP_NOZORDER);            
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
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_dlgproc , ot4xb_automatic_scroll_focus_t , dlg_proc );      
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
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_panelproc , ot4xb_automatic_scroll_focus_t , panel_proc );         
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
_XPP_REG_FUN_( OT4XB_PAINTTHEMSGBAR ) //ot4xb_PaintTheMsgBar( hWnd , nMeter , cMeter,cCaption)
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
  DeleteObject(hDCMem);
  ReleaseDC(hWnd,hDC);
  _ret(pl); return;
}
// ------------------------------------------------------------------------------------------------------------------------
// _ot4xb_rtf_stream_in@16
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
