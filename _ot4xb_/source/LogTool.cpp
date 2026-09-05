//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
#include <stdio.h>
// -----------------------------------------------------------------------------------------------------------------
static HWND  ot4xb_hWndLogOut = 0;
static HWND  user_hWndLogOut  = 0;
static LPSTR user_pWndCls     = 0;
// -----------------------------------------------------------------------------------------------------------------
static BOOL bSendLogStrFL_internal( HWND * phWnd, LPSTR pWndCls, LPSTR cFile , LONG nLine , LPSTR pFmt , va_list arglist);
static BOOL bSendLogStr_internal( HWND * phWnd, LPSTR pWndCls, LPSTR pFmt , va_list arglist);
static void XbSendLogStr_internal( XppParamList pl , DWORD dwFPtr );
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Register_User_Log_Uuid
            | syntax_: `Register_User_Log_Uuid( cWndClass ) -> NIL`
            | category: log
            | _kw_: log window, register, WM_COPYDATA, user log, class name
   }}*/
/*{{|desc: Registers the window class name of the user log window targeted by lSendLogStr() and
      lSendLogStrFL(). Any previously registered class name is released and the cached window handle is
      reset, so the next send looks the target window up again by the new class name. Passing NIL, a
      non-Character value or an empty string clears the registration, and the log functions fall back to
      the default OT4XB log window.
    | params:
    - `cWndClass` Character - Window class name of the user log window. Despite the Uuid in the
      function name, no format is enforced; any window class name is accepted.

    Returns NIL

    |seealso: See also: {{ilink: <function lSendLogStr> lSendLogStr}}, {{ilink: <function lSendLogStrFL> lSendLogStrFL}} }}*/
XPPRET XPPENTRY REGISTER_USER_LOG_UUID( XppParamList pl )
{
   if( user_pWndCls ) 
   {
      LPSTR p = user_pWndCls;
      user_pWndCls     = 0;
      user_hWndLogOut  = 0;   
      _xfree( p );
   }
   user_pWndCls = _pszParam(pl,1);
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lSendLogStr
            | syntax_: `lSendLogStr( cFormat, ... ) -> lOk`
            | category: log
            | _kw_: log, send log, WM_COPYDATA, debug output, printf
   }}*/
/*{{|desc: Sends a printf-style formatted message via WM_COPYDATA to the user log window registered with
      Register_User_Log_Uuid(); when no window class is registered it falls back to the default OT4XB log
      window.
    | params:
    - `cFormat` Character - printf-style format string.
    - `...` Any - Values to format.

    Returns Logical - .T. when the message was delivered, .F. when no log window was found or formatting
      failed. }}*/
XPPRET XPPENTRY LSENDLOGSTR( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) bSendLogStr);}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lSendLogStrFL
            | syntax_: `lSendLogStrFL( cFile, nLine, cFormat, ... ) -> lOk`
            | category: log
            | _kw_: log, send log, file and line, timestamp, WM_COPYDATA
   }}*/
/*{{|desc: Sends a printf-style formatted message, preceded by a header line holding the UTC timestamp and
      the given source file and line, to the user log window registered with Register_User_Log_Uuid(); when
      no window class is registered it falls back to the default OT4XB log window.
    | params:
    - `cFile` Character - Source file name written into the header.
    - `nLine` Numeric - Source line number written into the header.
    - `cFormat` Character - printf-style format string.
    - `...` Any - Values to format.

    Returns Logical - .T. when the message was delivered, .F. when no log window was found or formatting
      failed. }}*/
XPPRET XPPENTRY LSENDLOGSTRFL( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) bSendLogStrFL);}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_lSendLogStr
            | syntax_: `ot4xb_lSendLogStr( cFormat, ... ) -> lOk`
            | category: log
            | _kw_: log, send log, ot4xb log window, WM_COPYDATA, debug output
   }}*/
/*{{|desc: Sends a printf-style formatted message via WM_COPYDATA to the default OT4XB log window, ignoring
      any window class registered with Register_User_Log_Uuid().
    | params:
    - `cFormat` Character - printf-style format string.
    - `...` Any - Values to format.

    Returns Logical - .T. when the message was delivered, .F. when no log window was found or formatting
      failed. }}*/
XPPRET XPPENTRY OT4XB_LSENDLOGSTR( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) ot4xb_bSendLogStr);}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_lSendLogStrFL
            | syntax_: `ot4xb_lSendLogStrFL( cFile, nLine, cFormat, ... ) -> lOk`
            | category: log
            | _kw_: log, send log, file and line, timestamp, ot4xb log window
   }}*/
/*{{|desc: Sends a printf-style formatted message, preceded by a header line holding the UTC timestamp and
      the given source file and line, to the default OT4XB log window, ignoring any window class registered
      with Register_User_Log_Uuid().
    | params:
    - `cFile` Character - Source file name written into the header.
    - `nLine` Numeric - Source line number written into the header.
    - `cFormat` Character - printf-style format string.
    - `...` Any - Values to format.

    Returns Logical - .T. when the message was delivered, .F. when no log window was found or formatting
      failed. }}*/
XPPRET XPPENTRY OT4XB_LSENDLOGSTRFL( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) ot4xb_bSendLogStrFL);}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
static void XbSendLogStr_internal( XppParamList pl , DWORD dwFPtr )
{
   LONG nParams,n;
   TXbFpParam * pParams = TXbFpParam::InitList(pl,1,&nParams);
   LONG sp1;
   DWORD dw;

   TXbFpParam::PrepareStackValues(pParams);

   _asm mov sp1 ,esp; // Save the stack before

   _asm mov eax , 0 ; // Put some zeros at the end
   _asm push eax;   // 1
   _asm push eax;   // 2
   _asm push eax;   // 3

   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   _asm mov eax , dwFPtr;
   _asm call eax;

   _asm mov dw ,eax;
   _asm mov eax ,sp1;
   _asm mov esp ,eax;

   GetTlsHeapManager()->PutLastError(GetLastError());
   TXbFpParam::ReleaseAll(pParams);
   _retl(pl,(BOOL) dw);
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bSendLogStrFL
            | syntax_: `BOOL bSendLogStrFL( LPSTR cFile, LONG nLine, LPSTR pFmt, ... )`
            | category: log
            | header: ot4xb_c_exported.h
            | mangled-name: bSendLogStrFL
            | _kw_: log, send log, file and line, timestamp, WM_COPYDATA
   }}*/
/*{{|desc: Sends a printf-style formatted message, preceded by a "YYYYMMDD-HH:MM:SS.mmm {File:...,Line:...}"
      UTC header line, via WM_COPYDATA to the user log window registered with Register_User_Log_Uuid()
      (default OT4XB log window when no class is registered). C primitive behind lSendLogStrFL(). The
      expanded text is capped at 1MB; a failing format returns FALSE instead of crashing.
    | params:
    - `cFile` LPSTR - Source file name written into the header (typically __FILE__).
    - `nLine` LONG - Source line number written into the header (typically __LINE__).
    - `pFmt` LPSTR - printf-style format string; the variadic arguments follow.
    - `...` Values formatted into pFmt.

    Returns BOOL - TRUE when the message was delivered, FALSE when no log window was found or formatting
      failed. }}*/
BOOL OT4XB_API bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStrFL_internal( &user_hWndLogOut,user_pWndCls,cFile,nLine,pFmt,arglist);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_bSendLogStrFL
            | syntax_: `BOOL ot4xb_bSendLogStrFL( LPSTR cFile, LONG nLine, LPSTR pFmt, ... )`
            | category: log
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_bSendLogStrFL
            | _kw_: log, send log, file and line, timestamp, ot4xb log window
   }}*/
/*{{|desc: Sends a printf-style formatted message, preceded by a "YYYYMMDD-HH:MM:SS.mmm {File:...,Line:...}"
      UTC header line, via WM_COPYDATA to the default OT4XB log window. C primitive behind
      ot4xb_lSendLogStrFL(). The expanded text is capped at 1MB; a failing format returns FALSE instead of
      crashing.
    | params:
    - `cFile` LPSTR - Source file name written into the header (typically __FILE__).
    - `nLine` LONG - Source line number written into the header (typically __LINE__).
    - `pFmt` LPSTR - printf-style format string; the variadic arguments follow.
    - `...` Values formatted into pFmt.

    Returns BOOL - TRUE when the message was delivered, FALSE when no log window was found or formatting
      failed. }}*/
BOOL OT4XB_API ot4xb_bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStrFL_internal( &ot4xb_hWndLogOut,0,cFile,nLine,pFmt,arglist);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// Composes a log line into a size-guarded heap buffer (caller _xfree's it) and returns it, setting *pcb to its
// length; returns 0 on failure. cFile != 0 prepends the "YYYYMMDD-HH:MM:SS.mmm {File:...,Line:...}" header. The
// caller's format+args are expanded with vsnprintf under __try/__except and capped at 1MB, so neither an oversized
// output nor a bad format/args can overflow or crash the process.
static LPSTR compose_log_line( LPSTR cFile, LONG nLine, LPSTR pFmt, va_list arglist, DWORD* pcb )
{
   char       sz[1024];
   SYSTEMTIME st;
   LPSTR      p;
   LPSTR      pUse;
   int        n = -1;

   if( cFile )
   {
      GetSystemTime( &st );
      snprintf( sz, sizeof(sz), "%04.4u%02.2u%02.2u-%02.2u:%02.2u:%02.2u.%03.3u {File:%s,Line:%u}\r\n%s\r\n",
                st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
                cFile, nLine, pFmt );
      pUse = sz;      // header + caller's format ( format text capped at sizeof(sz) )
   }
   else
   {
      pUse = pFmt;    // no header -> caller's format used directly, uncapped
   }
   p = (LPSTR) _xgrab( 0x100000 );   // 1MB size guard
   __try
   {
      n = vsnprintf( p, 0x100000, pUse, arglist );
   }
   __except( EXCEPTION_EXECUTE_HANDLER )
   {
      n = -1;   // bad caller format / args -> fail safely instead of crashing
   }
   if( n < 0 )
   {
      _xfree( p );
      if( pcb ) { *pcb = 0; }
      return 0;
   }
   if( n >= 0x100000 ) { n = 0x100000 - 1; }   // truncated
   if( pcb ) { *pcb = (DWORD) n; }
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
static BOOL bSendLogStrFL_internal( HWND * phWnd, LPSTR pWndCls, LPSTR cFile , LONG nLine , LPSTR pFmt , va_list arglist)
{
   BOOL bOk  = FALSE;
   if( !pWndCls ) phWnd   = &ot4xb_hWndLogOut;
   if( !phWnd   ) { phWnd   = &ot4xb_hWndLogOut; pWndCls = 0; }
   if( phWnd[0] ){ if( !IsWindow(phWnd[0]) ) phWnd[0] = 0; }
   if( !phWnd[0] )
   {
      if( pWndCls )  phWnd[0] = FindWindow(pWndCls,0);
      else           phWnd[0] = FindWindow(OT4XB_LOG_WND_CLASS,0);
   }
   if( phWnd[0] )
   {
      COPYDATASTRUCT cds;
      cds.dwData = 0;
      cds.lpData = compose_log_line( cFile, nLine, pFmt, arglist, &cds.cbData );
      if( cds.lpData )
      {
         SendMessage( phWnd[0] , WM_COPYDATA, 0 , (LPARAM) ((void*) &cds) );
         _xfree( cds.lpData );
         bOk = TRUE;
      }
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
// static HWND  ot4xb_hWndLogOut = 0;
// static HWND  user_hWndLogOut  = 0;
// static LPSTR user_pWndCls     = 0;
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bSendLogStr
            | syntax_: `BOOL bSendLogStr( LPSTR pFmt, ... )`
            | category: log
            | header: ot4xb_c_exported.h
            | mangled-name: bSendLogStr
            | _kw_: log, send log, WM_COPYDATA, debug output, printf
   }}*/
/*{{|desc: Sends a printf-style formatted message via WM_COPYDATA to the user log window registered with
      Register_User_Log_Uuid() (default OT4XB log window when no class is registered). C primitive behind
      lSendLogStr(). The expanded text is capped at 1MB; a failing format returns FALSE instead of crashing.
    | params:
    - `pFmt` LPSTR - printf-style format string; the variadic arguments follow.
    - `...` Values formatted into pFmt.

    Returns BOOL - TRUE when the message was delivered, FALSE when no log window was found or formatting
      failed. }}*/
BOOL OT4XB_API bSendLogStr( LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStr_internal(&user_hWndLogOut,user_pWndCls,pFmt,arglist);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_bSendLogStr
            | syntax_: `BOOL ot4xb_bSendLogStr( LPSTR pFmt, ... )`
            | category: log
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_bSendLogStr
            | _kw_: log, send log, ot4xb log window, WM_COPYDATA, debug output
   }}*/
/*{{|desc: Sends a printf-style formatted message via WM_COPYDATA to the default OT4XB log window, ignoring
      any window class registered with Register_User_Log_Uuid(). C primitive behind ot4xb_lSendLogStr(). The
      expanded text is capped at 1MB; a failing format returns FALSE instead of crashing.
    | params:
    - `pFmt` LPSTR - printf-style format string; the variadic arguments follow.
    - `...` Values formatted into pFmt.

    Returns BOOL - TRUE when the message was delivered, FALSE when no log window was found or formatting
      failed. }}*/
BOOL OT4XB_API ot4xb_bSendLogStr( LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStr_internal( &ot4xb_hWndLogOut,0,pFmt,arglist);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static BOOL bSendLogStr_internal( HWND * phWnd, LPSTR pWndCls, LPSTR pFmt , va_list arglist)
{
   BOOL bOk  = FALSE;
   if( !pWndCls ) phWnd   = &ot4xb_hWndLogOut;
   if( !phWnd   ) { phWnd   = &ot4xb_hWndLogOut; pWndCls = 0; }
   if( phWnd[0] ){ if( !IsWindow(phWnd[0]) ) phWnd[0] = 0; }
   if( !phWnd[0] )
   {
      if( pWndCls )  phWnd[0] = FindWindow(pWndCls,0);
      else           phWnd[0] = FindWindow(OT4XB_LOG_WND_CLASS,OT4XB_LOG_WND_CLASS);
   }
   if( phWnd[0] )
   {
      COPYDATASTRUCT cds;
      cds.dwData = 0;
      cds.lpData = compose_log_line( 0, 0, pFmt, arglist, &cds.cbData );   // cFile == 0 -> no header
      if( cds.lpData )
      {
         SendMessage( phWnd[0] , WM_COPYDATA, 0 , (LPARAM) ((void*) &cds) );
         _xfree( cds.lpData );
         bOk = TRUE;
      }
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------


