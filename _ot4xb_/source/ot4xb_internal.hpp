//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#ifdef _OT4XB_API_
// ---------------------------------------------------------------------------
BEGIN_EXTERN_C
OT4XB_API extern UINT g_nMsgDirtyNotify;
OT4XB_API extern UINT g_nMsgProxiRemoveSubclass;
OT4XB_API extern ULONG _xpp_REFERENCE  ;
OT4XB_API extern ULONG _xpp_MEMO       ;
OT4XB_API extern ULONG _xpp_DOUBLE     ;
OT4XB_API extern BOOL  _bXppIs19_      ;
void _API_OSVer_InitProc(void);
void _API_DrTool_InitProc(void);
void _API_DrTool_ExitProc(void);
// void _API_ping_InitProc(void);
// void _API_ping_ExitProc(void);
void _API_Memory_InitProc(void);
void _API_Memory_InitProcXBase(void);
void _API_Memory_ExitProc(void);
void _APIcpp_Tls_InitProc(void);
void _APIcpp_Tls_InitThread(void);
void _APIcpp_Tls_ExitProc(void);
void _APIcpp_Tls_ExitProc_xb(void);
void _APIcpp_Tls_ExitThread_xb(void);
void _APIcpp_Tls_ExitThread(void);
// -------------------------------------
void _hook_parclen(void);
END_EXTERN_C
// ---------------------------------------------------------------------------
CRITICAL_SECTION* _drtool_get_pcs_( void );
// ---------------------------------------------------------------------------
#include <PointerEx_internal.hpp>
#include <Tls_internal.hpp>
#include <TXbClass_internal.hpp>
#include <TXbFpParam_internal.hpp>
#include <THDict_internal.hpp>
#include <ot4xb_md5_internal.hpp>
#include <ndtg_internal.hpp>
#include <ot4xb_dirty_dlgedit_internal.hpp>
// ---------------------------------------------------------------------------
BOOL  gwst_x_mdef_scan( LPSTR pStrDef,ULONG nDefSize,LPSTR pName,ULONG nNameLen,GWST_DEF_MEMBER_ITEM * pItem);
DWORD gwst_x_name2crc( LPSTR pName,ULONG nNameLen);
//----------------------------------------------------------------------------------------------------------------------
BOOL   _conRelease_ret_BOOL( ContainerHandle con );
LONG   _conRelease_ret_LONG( ContainerHandle con );
FLOAT  _conRelease_ret_FLOAT( ContainerHandle con );
double _conRelease_ret_double( ContainerHandle con );
LPSTR  _conRelease_ret_LPSTR( ContainerHandle con );

//----------------------------------------------------------------------------------------------------------------------
// WIN95 Compat.
// #define htonl(n) ( (n >>24) | ((n&0xFF0000)>>8) |((n&0xFF00)<<8) | (n<<24) )
// #define htons(n) ( (WORD)( ((n & 0xFF)<<8) | ((n & 0xFF00)>>8)    ) )
// #define ntohl(n) ( ((n & 0xFF)<<24) | ((n & 0xFF00)<<8) | ((n & 0xFF0000)>>8) | (n >>24) )
// #define ntohs(n) ( (WORD)( ((n & 0xFF)<<8) | ((n & 0xFF00)>>8)) )
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ot4xb_iocp_ns )
   void _init_proc_(void);
END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------
#endif


