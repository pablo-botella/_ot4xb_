//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------

#ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#endif
// -----------------------------------------------------------------------------------------------------------------
//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#ifdef _OT4XB_API_
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#include <atlbase.h>
#include <atlstr.h>
#endif
// -----------------------------------------------------------------------------------------------------------------
#include <uxtheme.h>
#ifdef _OT4XB_API_
#pragma warning( push , 3 )
#include <gdiplus.h>
#pragma warning( pop)
#endif
#include <xpppar.h>
#include <xppcon.h>
#define _mk_ptr_( cast, ptr, addValue ) ((cast)((void*)( (DWORD)(ptr)+(DWORD)(addValue))))
#define _mk_ptr_minus( cast, ptr, minusValue ) ((cast)((void*)( (DWORD)(ptr)-(DWORD)(minusValue))))
#define _align_dword_ptr_( cast , ptr )  _mk_ptr_(cast,ptr,( (((DWORD) ptr) & 3) ? (4 - (((DWORD) ptr) & 3)) : 0 ))
#define xpp_assert( b , n , c )  if( !b ){TXbGenError _e_(n,__FUNCTION__,c);_e_.Launch();return;}
//----------------------------------------------------------------------------
#ifdef OT4XB_DEBUG
#define ot4xb_SendFLog(...)                             ot4xb_bSendLogStrFL( __FILE__ , __LINE__ ,__VA_ARGS__)
#else
#define ot4xb_SendFLog(...)
#endif
//----------------------------------------------------------------------------------------------------------------------
#define CBSZ1(sz,str,p1)                         ((wsprintf(sz,str,p1                        ),sz))
#define CBSZ2(sz,str,p1,p2)                      ((wsprintf(sz,str,p1,p2                     ),sz))
#define CBSZ3(sz,str,p1,p2,p3)                   ((wsprintf(sz,str,p1,p2,p3                  ),sz))
#define CBSZ4(sz,str,p1,p2,p3,p4)                ((wsprintf(sz,str,p1,p2,p3,p4               ),sz))
#define CBSZ5(sz,str,p1,p2,p3,p4,p5)             ((wsprintf(sz,str,p1,p2,p3,p4,p5            ),sz))
#define CBSZ6(sz,str,p1,p2,p3,p4,p5,p6)          ((wsprintf(sz,str,p1,p2,p3,p4,p5,p6         ),sz))
#define CBSZ7(sz,str,p1,p2,p3,p4,p5,p6,p7)       ((wsprintf(sz,str,p1,p2,p3,p4,p5,p6,p7      ),sz))
#define CBSZ8(sz,str,p1,p2,p3,p4,p5,p6,p7,p8)    ((wsprintf(sz,str,p1,p2,p3,p4,p5,p6,p7,p8   ),sz))
#define CBSZ9(sz,str,p1,p2,p3,p4,p5,p6,p7,p8,p9) ((wsprintf(sz,str,p1,p2,p3,p4,p5,p6,p7,p8,p9),sz))
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifdef __cplusplus
#define BEGIN_EXTERN_C  extern "C" {
#define BEGIN_NAMESPACE( n ) namespace n {
#define END_NAMESPACE()  }
#else
#define BEGIN_EXTERN_C
#define BEGIN_NAMESPACE( n )
#define END_NAMESPACE()
#endif
#ifdef __cplusplus
#define END_EXTERN_C  }
#else
#define END_EXTERN_C
#endif
// ---------------------------------------------------------------------------
#ifdef _OT4XB_STATIC_LIB_
#define OT4XB_API
#else// ---------------
#ifdef _OT4XB_API_
#define OT4XB_API __declspec(dllexport)
#include <ot4xb_xbexports.hpp>
#else
#ifdef ALINK_COMPAT
#define OT4XB_API __declspec(dllimport)
#else
#define OT4XB_API __declspec(dllimport)
#endif
#endif
#endif // ---------------
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API ULONG __cdecl ot4xb_parclen(XppParamList pl , ULONG n , ... );
#define _parclen ot4xb_parclen
//----------------------------------------------------------------------------------------------------------------------
#ifndef OT4XB_SKIP_XB_REGISTRATION
#define BEGIN_REGISTER_XBASE_TABLE() static XppRegisterTable _functions_table_; \
static XppRegisterFunction _functions_[] = {
#endif
//----------------------------------------------------------------------------------------------------------------------
#ifndef OT4XB_SKIP_XB_REGISTRATION
#define END_REGISTER_XBASE_TABLE() };\
static ULONG XPPAPIENTRY _xbase_InitProcedure(void * );\
static ULONG XPPAPIENTRY _xbase_ExitProcedure(void * );\
static XppDllRegistration __dllreg__ = { \
_functions_,sizeof(_functions_) / sizeof(XppRegisterFunction), \
0, _xbase_InitProcedure,_xbase_ExitProcedure,NULL};
#endif
// -----------------------------------------------------------------------------------------------------------------
#ifndef OT4XB_SKIP_XB_REGISTRATION
#define XBASE_TABLE_START( e )     { #e , e }
#define XBASE_TABLE_ENTRY( e )    ,{ #e , e }
#endif
//----------------------------------------------------------------------------------------------------------------------
#ifndef OT4XB_SKIP_XB_REGISTRATION
#define XBASE_INIT_PROC()  static ULONG XPPAPIENTRY _xbase_InitProcedure(void*  )
#define XBASE_EXIT_PROC()  static ULONG XPPAPIENTRY _xbase_ExitProcedure(void*  )
#endif
//----------------------------------------------------------------------------------------------------------------------
#define BEGIN_XBASE_CLASS( clsname )  extern "C" XPPRET XPPENTRY clsname( XppParamList pl){\
ContainerHandle conco = _conClsObj(#clsname);if( conco == NULLCONTAINER ){\
TXbClass * pc = new TXbClass;pc->ClassName(#clsname);pc->EXPORTED();
// ---------------------------------------------------------------------------
#define END_XBASE_CLASS \
conco = pc->Create(); delete pc;if( conco == NULLCONTAINER ){_ret(pl); return;}}\
_conReturn(pl,conco);_conRelease(conco);}
//----------------------------------------------------------------------------------------------------------------------
#define _XPP_REG_FUN_( fn ) extern "C" XPPRET XPPENTRY fn( XppParamList pl )
//----------------------------------------------------------------------------------------------------------------------
extern BYTE _lower_ansi_char_table_[256];
extern OSVERSIONINFOEX ot4xb_global_osvi ;
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_constants.h>
#include <ot4xb_classes.h>
#include <ot4xb_types.h>
#include <ot4xb_c_exported.h>
#include <ot4xb_cpp_exported.h>
//------------------------------------------------------------------------------------------------------------
#ifdef _OT4XB_API_
#if WINVER >= 0x0600
#include <vhti.h>
#endif

#include <ot4xb_internal.hpp>
#pragma optimize( "t", on )
#endif
//------------------------------------------------------------------------------------------------------------
#include <ot4xb_TGStack.h>
#include <ot4xb_XbSet.h>
#include <ot4xb_XbClass.h>
#include <ot4xb_TXppParamList.h>
#include <ot4xb_TLists.h>
#include <ot4xb_TZString.h>
#include <ot4xb_TBinFile.h>
#include <ot4xb_THashTable.h>
#include <ot4xb_THtcs.h>
#include <ot4xb_TldList.h>
#include <ot4xb_TokenizeEx.h>
#include <ot4xb_resource_tool.h>
#include <ot4xb_statistics.h>
#include <ot4xb_sqlstr.h>
//-----------------------------------------------------------------------------------------------------------------------
#define _TSTDCTXCBK_PROXI_WNDPROC_( function , cls , method )                         \
LRESULT __stdcall function( DWORD* ctx, HWND hWnd ,UINT nMsg,WPARAM wp , LPARAM lp )  \
{                                                                                     \
   WNDPROC old_proc = (WNDPROC) ctx[1];                                               \
   if( (nMsg == g_nMsgProxiRemoveSubclass) || ( nMsg == WM_NCDESTROY ) )              \
   {                                                                                  \
      WNDPROC oldproc = reinterpret_cast<WNDPROC>(ctx[1]);                            \
      reinterpret_cast< cls * >(ctx[0])->method(hWnd,nMsg,wp,lp,old_proc);            \
      SetWindowLong(hWnd,GWL_WNDPROC,ctx[1]);                                         \
      delete reinterpret_cast<TStdCtxCbk*>(ctx[2]);                                   \
      _xfree((void*) ctx);                                                            \
      if(nMsg == g_nMsgProxiRemoveSubclass){ return 0; }                              \
      return CallWindowProc(oldproc,hWnd,nMsg,wp,lp);                                 \
   }                                                                                  \
   return reinterpret_cast< cls * >(ctx[0])->method(hWnd,nMsg,wp,lp,old_proc);        \
}
// -----------------------------------------------------------------------------------------------------------------
#define _TSTDCTXCBK_SUBCLASS_( __h__wnd__  , __ptr__function__ , __ptr__this__ )                      \
if( __h__wnd__ )                                                                                      \
{                                                                                                     \
   DWORD* __pdw__ctx__ = (DWORD*) _xgrab( 4 * sizeof(DWORD) );                                        \
   __pdw__ctx__[0] = (DWORD) __ptr__this__;                                                           \
   __pdw__ctx__[1] = (DWORD) GetWindowLong( __h__wnd__ ,GWL_WNDPROC );                                \
   __pdw__ctx__[2] = (DWORD) new TStdCtxCbk( (DWORD) __pdw__ctx__ , (DWORD) __ptr__function__ );      \
   __pdw__ctx__[3] = 0;                                                                               \
   SetWindowLong(__h__wnd__,GWL_WNDPROC, (DWORD) __pdw__ctx__[2] );                                   \
}
//----------------------------------------------------------------------------------------------------------------------
