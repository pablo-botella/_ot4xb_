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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LSENDLOGSTR( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) bSendLogStr);}
XPPRET XPPENTRY LSENDLOGSTRFL( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) bSendLogStrFL);}
XPPRET XPPENTRY OT4XB_LSENDLOGSTR( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) ot4xb_bSendLogStr);}
XPPRET XPPENTRY OT4XB_LSENDLOGSTRFL( XppParamList pl ){XbSendLogStr_internal(pl,(DWORD) ot4xb_bSendLogStrFL);}
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
BOOL OT4XB_API bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStrFL_internal( &user_hWndLogOut,user_pWndCls,cFile,nLine,pFmt,arglist);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL OT4XB_API ot4xb_bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStrFL_internal( &ot4xb_hWndLogOut,0,cFile,nLine,pFmt,arglist);
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
      SYSTEMTIME     st;
      LPSTR          pStr = (LPSTR) _xgrab(1024);
      GetSystemTime(&st);
      sprintf( pStr , "%04.4u%02.2u%02.2u-%02.2u:%02.2u:%02.2u.%03.3u {File:%s,Line:%u}\r\n%s\r\n",
               st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,
               cFile , nLine , pFmt );
      cds.dwData = 0;
      cds.lpData = _xgrab(0x040000);
      cds.cbData = (DWORD) vsprintf( (LPSTR) cds.lpData, pStr, arglist );
      SendMessage( phWnd[0] , WM_COPYDATA, 0 , (LPARAM) ((void*) &cds) );
      _xfree(cds.lpData);
      _xfree((void*) pStr);
      bOk = TRUE;
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
// static HWND  ot4xb_hWndLogOut = 0;
// static HWND  user_hWndLogOut  = 0;
// static LPSTR user_pWndCls     = 0;
// -----------------------------------------------------------------------------------------------------------------
BOOL OT4XB_API bSendLogStr( LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStr_internal(&user_hWndLogOut,user_pWndCls,pFmt,arglist);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL OT4XB_API ot4xb_bSendLogStr( LPSTR pFmt , ... )
{
   va_list(arglist);
   va_start(arglist, pFmt);
   return bSendLogStr_internal( &ot4xb_hWndLogOut,0,pFmt,arglist);
}
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

      va_start(arglist, pFmt);
      cds.dwData = 0;
      cds.lpData = _xgrab(0x40000);
      cds.cbData = (DWORD) vsprintf( (LPSTR) cds.lpData, pFmt, arglist );
      SendMessage( phWnd[0] , WM_COPYDATA, 0 , (LPARAM) ((void*) &cds) );
      _xfree(cds.lpData);
      bOk = TRUE;
   }
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------


