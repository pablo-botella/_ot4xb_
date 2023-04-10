//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
BEGIN_EXTERN_C

OT4XB_API void* _ot4xb_stdctxcbk_new_(DWORD dwCtx , DWORD dwFp);
OT4XB_API void  _ot4xb_stdctxcbk_delete_(void* p);
OT4XB_API void __cdecl _ot4xb_thread_pool_push_(ContainerHandle conThread);
OT4XB_API ContainerHandle __cdecl  _ot4xb_thread_pool_pop_(void);

// ---------------------------------------------------------------------------
// fpCall.cpp
// ---------------------------------------------------------------------------
OT4XB_API BOOL __cdecl  bWriteLogLine( LPSTR pFName , LPSTR pFmt , ... );
OT4XB_API BOOL __cdecl  bSendLogStr( LPSTR pFmt , ... );
OT4XB_API BOOL __cdecl  bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... );
OT4XB_API BOOL __cdecl  ot4xb_bSendLogStr( LPSTR pFmt , ... );
OT4XB_API BOOL __cdecl  ot4xb_bSendLogStrFL( LPSTR cFile , LONG nLine , LPSTR pFmt , ... );
OT4XB_API DWORD __cdecl ot4xb_GetFpLastError(void);
OT4XB_API void  __cdecl ot4xb_PutFpLastError(DWORD dw);

// ---------------------------------------------------------------------------
// ot4xb_acp.cpp
// ---------------------------------------------------------------------------
OT4XB_API ContainerHandle _ot4xb_thread_new_(void);
OT4XB_API ContainerHandle _ot4xb_thread_( LPTHREAD_START_ROUTINE fp , void* lp );
OT4XB_API HANDLE _ot4xb_ThreadObject2hThread(ContainerHandle cono);
OT4XB_API DWORD _ot4xb_hook_func_in_mod_(HMODULE hFrom,LPSTR pDllFrom,LPSTR pFName, DWORD pfNew);
OT4XB_API DWORD _ot4xb_find_sym_(LPSTR p);
OT4XB_API DWORD _ot4xb_fp_map_(DWORD fps,DWORD fpd);
OT4XB_API void _ot4xb_fp_map2_(DWORD fps,DWORD fpd);
OT4XB_API void __stdcall _ot4xb_apcproc_cb_(DWORD* pdw );
OT4XB_API void __stdcall _ot4xb_apcproc_stksync_(DWORD* pdw );
OT4XB_API DWORD __cdecl _ratx_if_(DWORD dw);
OT4XB_API DWORD*  __cdecl _ratx_prep_(DWORD np, LPSTR pStr,DWORD nFlags);
OT4XB_API void __cdecl _ratx_set_(DWORD* pdw,ULONG np,DWORD con);
OT4XB_API DWORD __cdecl _ratx_get_(DWORD* pdw,ULONG np);
OT4XB_API void __cdecl _ratx_clr_(DWORD* pdw);
OT4XB_API BOOL __cdecl kill_process_by_id(DWORD id , UINT nCode);
OT4XB_API LONG __cdecl process_wait_by_id(DWORD id , DWORD nTimeOut ); // 0 terminated , 1 running , < 0 error

OT4XB_API void __cdecl _ot4xb_setup_break_hook_(void);
OT4XB_API void __cdecl _ot4xb_redirect_xppapi_call_(XppParamList pl , ContainerHandle Self , LPSTR pMethodName );
OT4XB_API void __cdecl _ot4xb_redirect_xppapi_call_ex_(XppParamList pl , ContainerHandle Self , LPSTR pMethodName , XppFuncType pBreak );
// ---------------------------------------------------------------------------------
OT4XB_API void next_xbfpcall_use_critical_section( CRITICAL_SECTION * pcs);
OT4XB_API CRITICAL_SECTION * get_new_initialized_critical_section( void );


      
// ---------------------------------------------------------------------------
// TLXbStack.cpp
// ---------------------------------------------------------------------------
OT4XB_API ContainerHandle _WithObject_StackTop_( UINT n );

// ---------------------------------------------------------------------------
// BitWise.cpp
// ---------------------------------------------------------------------------
OT4XB_API DWORD _dw_bf_get_(DWORD dw,DWORD sh, DWORD cb);
OT4XB_API DWORD _dw_bf_set_(DWORD dw,DWORD sh, DWORD cb , DWORD v);
OT4XB_API BYTE  _b1_bf_get_(BYTE b,BYTE sh, BYTE cb);
OT4XB_API BYTE  _b1_bf_set_(BYTE b ,BYTE sh, BYTE cb , BYTE v);
OT4XB_API WORD  _w_bf_get_(WORD w,WORD sh, WORD cb);
OT4XB_API WORD  _w_bf_set_(WORD w ,WORD sh, WORD cb , WORD v);
OT4XB_API BYTE  _byteflipbits_(BYTE n);
OT4XB_API BYTE  _str_byte_xor_(LPBYTE p , UINT sh , UINT cb);
OT4XB_API BYTE  _str_byte_sum_(LPBYTE p , UINT sh , UINT cb);
OT4XB_API void _str_reverse_bytes_(LPBYTE p, UINT sh, UINT count);

// ---------------------------------------------------------------------------
// num_and_bytes.cpp
//----------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Memory Allocation
// ---------------------------------------------------------------------------
OT4XB_API UINT   __cdecl   _vpagesize(void);
OT4XB_API UINT   __cdecl   _vgetsize( void * p);
OT4XB_API void*  __cdecl  _vgrab1page(UINT * pnSize );
OT4XB_API void*  __cdecl  _vgrab( UINT n);
OT4XB_API void   __cdecl   _vfree( void * p);
OT4XB_API void*  __cdecl  _pgrab( UINT );
OT4XB_API void   __cdecl   _pfree( void * );
OT4XB_API void*  __cdecl  _xgrab( UINT );
OT4XB_API void*  __cdecl  _xgrow(void* pp  , UINT n);
OT4XB_API void*  __cdecl  _xxgrow(void* pp ,UINT nCurrent , UINT nNew);
OT4XB_API void*  __cdecl  _xxgrowa(void* pp ,UINT nCurrent , UINT nNew , UINT nItemSize);
OT4XB_API void   __cdecl   _xfree( void * );
OT4XB_API void*  __cdecl  _mgrab( UINT );
OT4XB_API void   __cdecl   _mfree( void * );
OT4XB_API void * __cdecl _mgrow(void* pp  , UINT n);
OT4XB_API UINT   __cdecl _mmsize(void* p);
OT4XB_API void * __cdecl _mcgrab(UINT nItems , UINT nItemSize );
// INTERLOCKED
OT4XB_API void*  __cdecl ot4xb_interlocked_alloc(void);
OT4XB_API DWORD  __cdecl ot4xb_interlocked_free(void*);
// -----------------
OT4XB_API void* __cdecl ot4xb_xheap_alloc( OT4XB_VHEAP*  , UINT  n);
OT4XB_API void  __cdecl ot4xb_xheap_free( OT4XB_VHEAP*  , void* p);
OT4XB_API int  __cdecl ot4xb_xheap_min(void);
OT4XB_API void* __cdecl ot4xb_vheap_alloc( OT4XB_VHEAP* vh  , UINT  n);
OT4XB_API void  __cdecl ot4xb_vheap_free( OT4XB_VHEAP*  vh , void* p);
OT4XB_API OT4XB_VHEAP* __cdecl ot4xb_vheap_create(  DWORD dwCreationFlags = HEAP_GENERATE_EXCEPTIONS, DWORD dwInitialSize = 0 , DWORD dwMaxSize = 0);
OT4XB_API void __cdecl ot4xb_vheap_destroy( OT4XB_VHEAP* vheap );
OT4XB_API OT4XB_VHEAP*  ot4xb_get_xheap(void);
OT4XB_API LONG __cdecl ot4xb_interlocked_next(void);

// ---------------------------------------------------------------------------
// gwst.cpp
// ---------------------------------------------------------------------------
OT4XB_API GWST_SORT_ITEM * __cdecl _gwst_get_member_info( ContainerHandle conoGwst , ContainerHandle conMName );
// ---------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl __sqlstr_str2money(LPSTR buffer, DWORD buffer_cb, LONGLONG & qn);
// ---------------------------------------------------------------------------
// String Pointer Manipulation
// ---------------------------------------------------------------------------
OT4XB_API LPBYTE __cdecl _bset(LPBYTE pStr, BYTE ch , UINT nBytes);
OT4XB_API LPBYTE __cdecl _bmove(LPBYTE pDest, LPBYTE pSrc , UINT nBytes);
OT4XB_API LPBYTE __cdecl _bdup(LPBYTE pSrc , UINT nBytes);
OT4XB_API LPBYTE __cdecl _bcopy(LPBYTE pDest, LPBYTE pSrc , UINT nBytes);
OT4XB_API LPBYTE __cdecl _bcopy_no_overlap(LPBYTE pDest, LPBYTE pSrc, UINT nBytes);
OT4XB_API LPBYTE __cdecl _bcopyex(LPBYTE pDest, DWORD dshift , LPBYTE pSrc , DWORD sshift , UINT nBytes);
OT4XB_API LPBYTE __cdecl _bcopywithtable(LPBYTE pDest, LPBYTE pSrc , UINT nBytes, LPBYTE pTable);
OT4XB_API void   __cdecl _bcopyf(LPBYTE pDest, LPBYTE pSrc , UINT nDstSize, UINT nSrcSize);
OT4XB_API UINT   __cdecl _bscan(LPBYTE pStr, UINT nBytes , BYTE ch);
OT4XB_API LPSTR  __cdecl _xstrcpy(LPSTR pDest, LPSTR pSrc);
OT4XB_API LPSTR  __cdecl _xxstrcpy(LPSTR pDest, LPSTR pSrc);
OT4XB_API UINT   __cdecl _xstccpy(LPSTR pDest, LPSTR pSrc, UINT nMax);
OT4XB_API LPSTR  __cdecl _xstrncpy(LPSTR pDest, LPSTR pSrc, UINT nMax);
OT4XB_API LPSTR  __cdecl _xstrcat ( LPSTR pDst, LPSTR pSrc);
OT4XB_API LPSTR  __cdecl _xstpchr( LPSTR pStr , CHAR ch );
OT4XB_API LPSTR  __cdecl _xstpblk(LPSTR pStr);
OT4XB_API UINT   __cdecl _xstrlen(LPSTR pStr);
OT4XB_API LPSTR  __cdecl _xstrdup(LPSTR pStr);
OT4XB_API LPSTR  __cdecl _xstrdupandgetlen(LPSTR pStr , UINT* pnLen);
OT4XB_API LPSTR  __cdecl _xssr_(LPSTR* pp , LPSTR p);
OT4XB_API LPSTR  __cdecl _xssr_cb_(LPSTR * ppd , UINT * pcbd , LPSTR ps , UINT cbs  );
OT4XB_API LPSTR  __cdecl _assr_cb_(LPSTR * ppd , UINT * pcbd , LPSTR ps , UINT cbs  ); // like xssr but without dupe the string
OT4XB_API int    __cdecl _xstrat(LPSTR pSep, int cbSep , LPSTR pStr, int cbStr );
// ---------------------------------------------------------------------------
OT4XB_API LPSTR __cdecl _xstr_nextline( LPSTR pStr, int* cbStr );
// ---------------------------------------------------------------------------
OT4XB_API int __cdecl _xstrcmp( LPSTR p1 , LPSTR p2 );
OT4XB_API int __cdecl _xstrcmpwithtable( LPSTR p1 , LPSTR p2 , LPBYTE pt);
OT4XB_API int __cdecl _xstrcmpi( LPSTR p1 , LPSTR p2 );
OT4XB_API int __cdecl _xsstrcmp( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2);
OT4XB_API int __cdecl _xsstrcmpwithtable( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2 , LPBYTE pt);
OT4XB_API int __cdecl _xsstrcmpi( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2);
OT4XB_API int __cdecl _xstrcmpi_09az( LPSTR p1 , LPSTR p2 );
OT4XB_API int __cdecl _bcmp(LPBYTE p1, LPBYTE p2 , UINT cb);
OT4XB_API int __cdecl _bcmpwithtable(LPBYTE p1, LPBYTE p2 , UINT cb, LPBYTE pt);

OT4XB_API LPWSTR _xstrcpyW(LPWSTR pDest, LPWSTR pSrc);
OT4XB_API UINT _xstrlenW(LPWSTR pStr);
OT4XB_API LPWSTR _xstrdupW(LPWSTR pStr );
// ---------------------------------------------------------------------------
OT4XB_API DWORD _xstrhash(LPSTR pKey, DWORD cb);
OT4XB_API DWORD _xstrhtcs(LPSTR pKey, DWORD cb);
OT4XB_API DWORD dwCrc32Lower(DWORD dwCRC,LPBYTE pStr,ULONG nLen);
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int _dwscan(LPDWORD pdw, int item_count , DWORD dwValue );
OT4XB_API int _dwscan_lwstrcrc32(LPDWORD pdw, int item_count , LPSTR k , int cb = -1 , DWORD* pdwcrc = 0);
OT4XB_API int _dwscan_lwstrcrc32_ex( LPDWORD pdw, int item_count, LPSTR k, int cb, DWORD* pdwcrc = 0, int item_start = 0 );
OT4XB_API int _qwscan(ULONGLONG * pqw, int item_count, ULONGLONG * pvalue );
OT4XB_API int _qwscan_atoqw(ULONGLONG * pqw, int item_count, LPSTR int_string , ULONGLONG * pqvalue = 0);
// ---------------------------------------------------------------------------
// Windows Version
// ---------------------------------------------------------------------------
OT4XB_API void ot4xb_fill_OSVERSIONINFOEX( OSVERSIONINFOEX* p );
OT4XB_API BOOL __cdecl bIsVista( void );
OT4XB_API BOOL __cdecl bIsXP( void );
OT4XB_API BOOL __cdecl bIsWinXP( void );
OT4XB_API BOOL __cdecl bIsWin9x( void );

// ---------------------------------------------------------------------------
// Xbase Parameters
// ---------------------------------------------------------------------------

OT4XB_API void __cdecl _retcFmt(XppParamList , LPSTR , ... );
OT4XB_API ContainerHandle __cdecl _conParamSelfByRef(XppParamList , ULONG );
OT4XB_API ContainerHandle __cdecl _conParamByRef(XppParamList , ULONG );
OT4XB_API ContainerHandle __cdecl _conTParamByRef(XppParamList , ULONG , ULONG );
OT4XB_API ContainerHandle __cdecl _conTpParamByRef(XppParamList , ULONG , ULONG * );
OT4XB_API LPSTR __cdecl _pszzACParam( XppParamList pl, ULONG nParam);
OT4XB_API LPSTR __cdecl _pszParam( XppParamList pl, ULONG n);
OT4XB_API LPSTR _pszParam_cb( XppParamList pl, ULONG n, DWORD* pcb = 0);
OT4XB_API ContainerHandle _conCopyParam( XppParamList pl, ULONG n);
OT4XB_API ContainerHandle __cdecl _conTParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG nType );
OT4XB_API ContainerHandle __cdecl _conTpParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG * pType );
OT4XB_API DWORD __cdecl _dwANFlagsParam( XppParamList pl, ULONG nParam);

// ---------------------------------------------------------------------------
// Xbase eXtended pointer Parameters
// ---------------------------------------------------------------------------
OT4XB_API LPSTR _conLockStrEx_( ContainerHandle con , ULONG nType , BOOL bByRef , CON_PLKSTREX * pInfo, BOOL bWrite);
OT4XB_API void _conUnLockStrEx_(CON_PLKSTREX * pInfo);
OT4XB_API LPSTR _conParamRLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo);
OT4XB_API LPSTR _conParamWLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo);
OT4XB_API void _conParamUnLockStrEx(CON_PLKSTREX * pInfo);
OT4XB_API LPSTR _conParamRLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo);
OT4XB_API LPSTR _conParamWLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo);
OT4XB_API void _conParamUnLockStrExFloat(CON_PLKSTREX * pInfo);


// ---------------------------------------------------------------------------
// Xbase Objects
// ---------------------------------------------------------------------------
OT4XB_API BOOL _conClassDestroyCon(ContainerHandle conco);
OT4XB_API LPSTR _pszGetClassName( ContainerHandle conClassObject );
OT4XB_API ContainerHandle _conClsObj(LPSTR);
OT4XB_API ContainerHandle _conClsObjNew(LPSTR);
OT4XB_API ContainerHandle _conNewObj(LPSTR,ContainerHandle, ... );
OT4XB_API ContainerHandle _conPutNewObj(ContainerHandle conr , LPSTR pClassName, ContainerHandle p1 , ... );
OT4XB_API ContainerHandle _conNewObjR(LPSTR pClassName, ContainerHandle p1 , ... );
OT4XB_API ContainerHandle _conGetSuperClass( ContainerHandle conClassObject );
OT4XB_API ContainerHandle _conTMember( ContainerHandle Self,LPSTR pszMemberName , ULONG nType);
OT4XB_API void  _conSetNILMember( ContainerHandle conObj, LPSTR pMName );
OT4XB_API LONG  _conGetNLMember( ContainerHandle conObj, LPSTR pMName);
OT4XB_API void  _conSetNLMember( ContainerHandle conObj, LPSTR pMName , LONG n);
OT4XB_API BOOL  _conGetLMember( ContainerHandle conObj, LPSTR pMName);
OT4XB_API void  _conSetLMember( ContainerHandle conObj, LPSTR pMName , BOOL n);
//OT4XB_API void  _conSetMemberStr( ContainerHandle conObj, LPSTR pMName , LPSTR pValue);
OT4XB_API LPSTR _pszMember( ContainerHandle cono, LPSTR pMName, PULONG pnLen);
OT4XB_API LPWSTR _pszMember2W( ContainerHandle cono, LPSTR pMName, PULONG pcc );
OT4XB_API void  _conSetCLMember( ContainerHandle conObj, LPSTR pMName , LPSTR pValue , ULONG nLen);
OT4XB_API void  _conSetCMember( ContainerHandle conObj, LPSTR pMName , LPSTR pValue);
OT4XB_API void  _conGetCLMember( ContainerHandle conObj, LPSTR pMName , LPSTR pValue , ULONG nLen);

// ---------------------------------------------------------------------------
//  Xbase Container Miscelaneous
// ---------------------------------------------------------------------------
OT4XB_API DWORD _conArrayGetLen(ContainerHandle cona , ...);
OT4XB_API DWORD _conArrayGetType(ContainerHandle cona , ...);
OT4XB_API BOOL _conArrayCheckType(ContainerHandle cona , ULONG nType,...);
OT4XB_API BOOL _conCheckType(ContainerHandle con , ULONG nType);
//-----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conPutZeroString(ContainerHandle con , ULONG nLen);
// ---------------------------------------------------------------------------
OT4XB_API void _conReleaseM(ContainerHandle con , ... );
OT4XB_API void _conReleasePa(ContainerHandle * pcon ,ULONG np);
OT4XB_API void _conNil2NullContainer(ContainerHandle * pcon );
OT4XB_API LPSTR _conXStrDup(ContainerHandle con, ULONG* pnLen = 0);
// ---------------------------------------------------------------------------
OT4XB_API DWORD _conGetFloat(ContainerHandle con , FLOAT * nfValue);
OT4XB_API ContainerHandle _conPutFloat(ContainerHandle con , FLOAT nf );
OT4XB_API DWORD _conGetQWord(ContainerHandle con , ULONGLONG * pqw);
OT4XB_API ContainerHandle _conPutQWord(ContainerHandle con , ULONGLONG qw);
// ---------------------------------------------------------------------------
OT4XB_API XPPAPIRET _conGetLong(ContainerHandle con,LONG * pnVal);
OT4XB_API XPPAPIRET _conGetLongOrBool(ContainerHandle con,LONG * pnVal);
OT4XB_API XPPAPIRET _conGetLong64(ContainerHandle con,LONGLONG * pnVal);
OT4XB_API XPPAPIRET _conGetLongEx(ContainerHandle con,LONG * pnVal);
OT4XB_API LONG _parLong(XppParamList pl , ULONG nIndex , ... );
OT4XB_API LONG _parLongOrBool(XppParamList pl , ULONG nIndex , ... );
OT4XB_API LONG _parLongEx(XppParamList pl , ULONG nIndex , ... );
OT4XB_API LONGLONG _parLong64(XppParamList pl , ULONG nIndex , ... );
OT4XB_API HWND _parHWND(XppParamList pl , ULONG nIndex , ... );
OT4XB_API HWND _conGetHWND(ContainerHandle con  );
OT4XB_API BSTR _conGetBSTR(ContainerHandle con);
OT4XB_API BSTR _conArrayGetBSTR(ContainerHandle cona , ULONG nLen ,  ... );
OT4XB_API BSTR _conGetBSTRMember( ContainerHandle conObj, LPSTR pMName);
OT4XB_API BSTR _BSTRParam(XppParamList pl , ULONG n);
OT4XB_API XPPAPIRET _conGetDateAsFileTime(ContainerHandle con,FILETIME * pft );
OT4XB_API XPPAPIRET _conGetDateAsSystemTime(ContainerHandle con,SYSTEMTIME * pst );
OT4XB_API XPPAPIRET _conGetDateTimeAsSystemTime(ContainerHandle cond,ContainerHandle cont,SYSTEMTIME * pst );
OT4XB_API XPPAPIRET _conPutDateFromFileTime(ContainerHandle con,FILETIME * pft );
OT4XB_API XPPAPIRET _conPutDateFromSystemTime(ContainerHandle con,SYSTEMTIME * pst);
OT4XB_API LONGLONG * _cona2i64a(ContainerHandle cona,ULONG* pnItems);
LPSTR OT4XB_API _pszCaptionParam( XppParamList pl, ULONG n);
OT4XB_API ContainerHandle _conaadd( ContainerHandle cona , ContainerHandle con );
OT4XB_API ContainerHandle _conNewCodeblock( LPSTR pStr );
OT4XB_API ContainerHandle _conGenericBreakCB( BOOL bCopy = 1 );
// ---------------------------------------------------------------------------
OT4XB_API ULONG ot4xb_conRLockC(ContainerHandle con, LPSTR* pp, ULONG *pcb);
OT4XB_API ULONG ot4xb_conWLockC(ContainerHandle con, LPSTR* pp, ULONG *pcb);
OT4XB_API ULONG ot4xb_conUnlockC(ContainerHandle con);
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// Xbase Arrays
// ---------------------------------------------------------------------------
OT4XB_API ULONG _conaGetLen(ContainerHandle cona , ULONG * pIndex = 0 , ULONG nDepth = 0);
OT4XB_API ULONG _conaGetType(ContainerHandle cona , ULONG * pIndex = 0 , ULONG nDepth = 0);
OT4XB_API ULONG _conGetArrayLen(ContainerHandle cona );
OT4XB_API XPPAPIRET _conArrayPutC(ContainerHandle , LPSTR , ... );
OT4XB_API XPPAPIRET _conArrayPutEmptyData(ContainerHandle , ULONG , LONG , LONG , ... );
OT4XB_API XPPAPIRET _conArrayPutNL(ContainerHandle  , LONG , ... );
OT4XB_API XPPAPIRET _conArrayPutNDF(ContainerHandle , double , LONG , LONG , ULONG , ... );
OT4XB_API XPPAPIRET _conArrayPutND(ContainerHandle  , double , ULONG , ... );
OT4XB_API XPPAPIRET _conArrayPutL(ContainerHandle   , BOOL , ... );
OT4XB_API XPPAPIRET _conArrayPutDS(ContainerHandle  , LPSTR , ... );
OT4XB_API XPPAPIRET _conArrayPutCL(ContainerHandle  , LPSTR , ULONG , ... );
OT4XB_API XPPAPIRET _conArrayPutBSTR2a(ContainerHandle cona , BSTR bs ,  ... );
OT4XB_API XPPAPIRET _conArrayPutC_MacroStr(ContainerHandle , LPSTR , ... );
OT4XB_API LONG _conArrayGetNL(ContainerHandle , ... );
OT4XB_API BOOL _conArrayGetL(ContainerHandle cona , ... );
OT4XB_API LONG _conArrayGetNLEx(ContainerHandle , ... );
OT4XB_API double _conArrayGetND(ContainerHandle cona , ... );
OT4XB_API LPSTR _conArrayGetXStrDup(ContainerHandle cona , ... );
OT4XB_API LONG _conArrayGetCL(ContainerHandle cona , LPSTR pStr , ULONG nLen ,  ... );
OT4XB_API LONG _conArrayGetSizeC(ContainerHandle , ... );
OT4XB_API LPSTR _conArray2Pszz(ContainerHandle cona , DWORD* pcb = 0);
OT4XB_API ContainerHandle _conPszz2Array( LPSTR p );

// ---------------------------------------------------------------------------
// string
// ---------------------------------------------------------------------------
OT4XB_API DWORD __cdecl dwCrc32(DWORD dwCRC,LPBYTE pStr,ULONG nLen);
OT4XB_API DWORD __cdecl dwCrc8(DWORD dwCrc, char* data, int length);
OT4XB_API DWORD dwCrc32WithTable(DWORD dwCRC,LPBYTE pStr,ULONG nLen,LPBYTE pTable);
OT4XB_API BOOL bStrWildCmp(LPSTR pWild, LPSTR pStr);
OT4XB_API BOOL bStrWildCmpEx(LPSTR pWild, LPSTR pStr , DWORD flags, DWORD m1 = 0, DWORD m2 = 0);
OT4XB_API BOOL bAnyStrWildCmpI(TList* wild_list, LPSTR pStr);
OT4XB_API BOOL bStrWildCmpI(LPSTR pWild, LPSTR pStr);
OT4XB_API BOOL bStrWildCmpWithTable(LPSTR pWild, LPSTR pStr, LPBYTE tb);
OT4XB_API BOOL bStrWildCmpWithTableEx(LPSTR pWild, LPSTR pStr, LPBYTE tb , DWORD flags , DWORD m1 = 0 , DWORD m2 = 0 );

OT4XB_API void ansi_capitalize(LPSTR p , int cb );
OT4XB_API BYTE chHex2Nibble( BYTE chHex );
OT4XB_API LPSTR ot4xb_urldecode(LPSTR pIn , DWORD cbIn, DWORD* pcbOut);
OT4XB_API LPSTR ot4xb_urlencode(LPSTR pIn , DWORD cbIn, DWORD* pcbOut);
OT4XB_API DWORD ot4xb_urlencode_cb(LPBYTE pIn , DWORD cbIn);
OT4XB_API DWORD ot4xb_urlencode_buffer(LPBYTE pIn , DWORD cbIn, LPBYTE pOut , DWORD cbOut);
OT4XB_API LONG ot4xb_CHEX2BIN_defmode_(LONG n );
OT4XB_API LPBYTE pHex2Bin(LPSTR ph, DWORD* pcb);
OT4XB_API LPSTR pBin2Hex(LPBYTE pb , UINT cb);
OT4XB_API int Bin2Hex_buffer(LPBYTE pb, UINT cb , LPSTR buffer , UINT buffer_cb);
OT4XB_API LONGLONG pHex2i64(LPBYTE ph, DWORD cb = 0xFFFFFFFF);
OT4XB_API DWORD pHex2i32(LPBYTE ph, DWORD cb = 0xFFFFFFFF);
OT4XB_API TList* TxtSplitLinesToTList( LPSTR pStr , DWORD dwFlags = 0 );
OT4XB_API TList* TxtSplitLinesToTListEx( LPSTR pStr , DWORD dwFlags = 0 , DWORD* pdwSkip = 0);
// ----- 
OT4XB_API void  ByteMapTable_Add(LPBYTE pTable , LPBYTE pPos , LPBYTE pMap ,DWORD cb);
OT4XB_API BOOL  ByteMapTable_IsSafeStr(LPBYTE pTable , LPBYTE p , int cb);
OT4XB_API void  ByteMapTable_FillSeq(LPBYTE pTable , LPWORD pSeq , DWORD sc);
OT4XB_API DWORD ByteMapTable_StrFindFlag(LPBYTE pSrc , int cb, int nStart , LPBYTE pTable , DWORD dwFlags);
OT4XB_API DWORD ByteMapTable_LTrimEx(LPBYTE pTable , LPBYTE pIn , DWORD cbIn = (DWORD) -1 );
OT4XB_API DWORD ByteMapTable_RTrimEx(LPBYTE pTable , LPBYTE pIn , DWORD cbIn = (DWORD) -1 );
// ----
OT4XB_API int  ByteMapTable_RemoveUnsafe(LPBYTE pTable , LPBYTE p , int cb);
OT4XB_API int  ByteMapTable_CondenseString(LPBYTE pTable , LPBYTE p , int cb , BYTE chFill = 0x20 );
// ----
OT4XB_API LPSTR cp850_to_html(LPSTR pIn , UINT* pcbOut, DWORD dwFlags);
OT4XB_API LPSTR cp437_to_html(LPSTR pIn , UINT* pcbOut, DWORD dwFlags);
OT4XB_API LPSTR cp1252_to_html(LPSTR pIn , UINT* pcbOut, DWORD dwFlags);
OT4XB_API LPSTR bin2ot4xbenc_ta(LPSTR pIn, UINT cb, UINT* pcbOut, UINT * lt, UINT * rt);
OT4XB_API LPSTR bin2ot4xbenc(LPSTR pIn , UINT cb, UINT* pcbOut);
OT4XB_API LPSTR ot4xbenc2bin(LPSTR pIn , UINT cb, UINT* pcbOut);
OT4XB_API LPSTR escape_to_xml(LPSTR pIn , UINT* pcbOut);
OT4XB_API LPSTR escape_to_sql(LPSTR pIn, UINT* pcbOut);
OT4XB_API LPSTR escape_to_json(LPSTR pIn , int cb , UINT* pcbOut);
OT4XB_API LPSTR unescape_from_json(LPSTR pIn , UINT* pcbOut);
OT4XB_API LPSTR x_www_form_urlencoded_to_cp1252(LPSTR pIn , UINT cb, void** ppInfo);
OT4XB_API LPSTR x_www_form_urlencoded_ncp(LPSTR pIn , UINT cb, void** ppInfo);
// ---------------------------------------------------------------------------------
OT4XB_API BOOL bIsNibble( char ch , DWORD *pNibble = 0, int nNibble = 0 );
OT4XB_API int ansi_byte_to_utf8_urlenc( BYTE ch , LPBYTE buffer , int nLevel ); // default 4// note : buffer must be able to alloc at least 12 characters
OT4XB_API int ot4xb_qp_decode_required_length( int nSrcLen);
OT4XB_API BOOL ot4xb_qp_decode(LPBYTE p,int cb,LPSTR p_out,int* pcb_out,DWORD dwFlags = 0);
OT4XB_API int ot4xb_base64_decode_required_length( int nSrcLen);
OT4XB_API BOOL ot4xb_base64_decode(LPSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen);
OT4XB_API int ot4xb_base64_encode_required_length( int nSrcLen);
OT4XB_API BOOL ot4xb_base64_encode(LPBYTE pSrc, int nSrcLen, LPSTR szDest, int *pnDestLen, DWORD dwFlags = 0);
OT4XB_API int ot4xb_uu_decode_required_length( int nSrcLen);
OT4XB_API BOOL ot4xb_uu_decode(BYTE* pbSrcData,int nSrcLen,BYTE* pbDest,int* pnDestLen);
OT4XB_API int ot4xb_base32_encode_required_length(int nSrcLen);
OT4XB_API BOOL ot4xb_base32_encode_with_table(LPSTR pTable , LPBYTE pSrc, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD dwFlags = 0);
// ---------------------------------------------------------------------------
// DrTool.cpp
// ---------------------------------------------------------------------------
OT4XB_API BOOL bCheckAndMakePath(LPSTR pPath);
OT4XB_API LPSTR get_currrent_directory(void);
OT4XB_API BOOL  set_currrent_directory(LPSTR pa );
OT4XB_API BOOL bPathIsAbsolute(LPSTR pPath );
OT4XB_API int  _PathCombineDefaultDir(LPSTR pOut , LPSTR pFileName , LPSTR pDefaultDir = 0 );
OT4XB_API int __cdecl ot4xb_recurse_dir_item_codeblock( WIN32_FIND_DATA* pfd , LPSTR pPath , DWORD cargo );
OT4XB_API int ot4xb_recurse_dir( LPSTR folder , LPSTR mask , _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item , DWORD cargo);
OT4XB_API int ot4xb_recurse_dir_ex(LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo, DWORD flags);

OT4XB_API LPSTR __cdecl ot4xb_path_combine( LPSTR pFolder , LPSTR pFile );
OT4XB_API UINT  __cdecl ot4xb_path_combine_buffer( LPSTR pFolder , LPSTR pFile , DWORD cbo , LPSTR pOut );

// ---------------------------------------------------------------------------
// TBinFile.cpp
// ---------------------------------------------------------------------------
OT4XB_API BOOL lMemoWrite(LPSTR pFileName,LPBYTE pBuffer, DWORD cb , BOOL bAppend);
OT4XB_API LPBYTE pMemoRead(LPSTR pFileName, DWORD* pcb );
OT4XB_API LPBYTE pMemoReadEx(LPSTR pFileName, DWORD* pcb , LPBYTE pBuffer , DWORD dwOffset , DWORD dwMaxBytes );
OT4XB_API LPBYTE pMemoReadEx2(LPSTR pFileName, DWORD* pcb , LPBYTE pBuffer , DWORD dwOffset , DWORD dwMaxBytes , DWORD & dwFlags);
OT4XB_API DWORD dwWriteLogData(LPSTR pFName, void* data , DWORD cb , LONGLONG* pLocator64 );

// ---------------------------------------------------------------------------
// Unicode.cpp
// ---------------------------------------------------------------------------
OT4XB_API BSTR    pAnsi2BSTR( LPSTR pAnsi , int cb = -1);
OT4XB_API WCHAR * pAnsi2WStr( LPSTR pAnsi , int cb = -1, int* pcc = 0);
OT4XB_API LPSTR   pWStr2Ansi( WCHAR* pWide  , int cc = -1, int* pcc = 0);
OT4XB_API LPSTR   w2utf8(LPWSTR pw , int cc = -1,int* pcb = 0);
OT4XB_API LPSTR   w2ansi(LPWSTR pw , int cc = -1,int* pcb = 0);
OT4XB_API LPSTR   w2oem(LPWSTR pw , int cc = -1,int* pcb = 0);
OT4XB_API LPWSTR  utf82w( LPSTR pu ,int cb = -1 ,int* pcc = 0 );
OT4XB_API LPWSTR  ansi2w( LPSTR pu ,int cb = -1 ,int* pcc = 0 );
OT4XB_API LPWSTR  oem2w( LPSTR pu ,int cb = -1 ,int* pcc = 0 );
OT4XB_API LPSTR   ansi2utf8( LPSTR pa ,int cb = -1,int* pcb = 0 );
OT4XB_API LPSTR   oem2utf8( LPSTR po ,int cb = -1,int* pcb = 0 );
OT4XB_API LPSTR   utf82ansi( LPSTR pu ,int cb = -1,int* pcb = 0);
OT4XB_API LPSTR   utf82oem( LPSTR pu ,int cb = -1,int* pcb = 0);
OT4XB_API  LPWSTR mb2w( LPSTR pu ,int cb ,int* pcc , UINT nAcp , DWORD nFlags = 0);
OT4XB_API LPSTR w2mb(LPWSTR pw , int cc,int* pcb, UINT nAcp , DWORD nFlags = 0);
OT4XB_API LPSTR mb2mb(LPSTR pa ,int cb,int* pcb,UINT nAcpFrom , UINT nAcpTo , DWORD nFlags1 = 0 , DWORD nFlags2 = 0  );


// ---------------------------------------------------------------------------
// wndTool.cpp
// ---------------------------------------------------------------------------
DWORD OT4XB_API ot4xb_call_in_gui_thread_(ULONG np, DWORD dwfp , ... );
DWORD OT4XB_API ot4xb_delay_call_in_gui_thread_(ULONG np, DWORD dwfp , ... );
LPSTR OT4XB_API ot4xb_pszz_proc_params(DWORD* pcb);
void OT4XB_API  ot4xb_ForceForegroundWindow(HWND hWnd);
void OT4XB_API  ForceForegroundWindow(HWND hWnd);
HWND OT4XB_API __cdecl _ot4xb_gen_hwnd_delegate_(HWND hWnd);
HWND OT4XB_API __cdecl _ot4xb_get_hwnd_delegate_(void);
void OT4XB_API __cdecl _ot4xb_set_hwnd_delegate_(HWND hWnd);
WORD OT4XB_API _best_font_size_from_list_( WORD wav , WORD* lst , UINT wc );
void OT4XB_API ot4xb_generic_message_loop_no_translate(void);  
void OT4XB_API ot4xb_generic_message_loop(void);  
DWORD OT4XB_API __stdcall ot4xb_rtf_stream_in(DWORD dwctx, LPBYTE pOut , LONG cbOut , LONG* pcb );
DWORD OT4XB_API __stdcall ot4xb_rtf_stream_out(DWORD dwctx, LPBYTE pOut , LONG cbOut , LONG* pcb );
DWORD OT4XB_API str2istream(void* p , ULONG cb);
OT4XB_API DWORD _ot4xb_hook_createwindowex_(HANDLE con);


// ---------------------------------------------------------------------------
// ot4xb_ndtk.cpp
// ---------------------------------------------------------------------------
extern "C" LPVOID OT4XB_API ndtk_new(void);
extern "C" void  OT4XB_API ndtk_delete(void* p);
extern "C" LONG OT4XB_API ndtk_get_depth(LPSTR pRoot);
extern "C" BOOL OT4XB_API ndtk_set_depth(LPSTR pRoot , LONG nLevel);
extern "C" void OT4XB_API ndtk_dec_depth(LPSTR pRoot);
extern "C" void OT4XB_API ndtk_add(LPSTR pRoot , LPSTR pNode);
extern "C" BOOL OT4XB_API ndtk_ischild(LPSTR pParent , LPSTR pChild , BOOL* pbIdentical );
// ---------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ot4xb_variant.cpp
// ---------------------------------------------------------------------------
class _variant_t;

LPVOID OT4XB_API _variant_t_GetIUnknow(_variant_t* pv);
LPBYTE OT4XB_API _variant_t_VT_UI1Array2Str(_variant_t* pv , UINT* pcb);
void OT4XB_API _variant_t_SetStrAsUI1Array( _variant_t* pv , LPSTR pStr , int cb );
BSTR OT4XB_API str2bstr(LPSTR p , int cb);
LONG OT4XB_API _variant_t_Get_Type(_variant_t* pv);
void OT4XB_API _variant_t_SetString(_variant_t* pv , LPSTR p);
LPSTR OT4XB_API _variant_t_GetString(_variant_t* pv , UINT* pcb );
void OT4XB_API _variant_t_Clear(_variant_t* pv);
void OT4XB_API _variant_t_Set_Missing(_variant_t* pv);
void OT4XB_API _variant_t_Set_I2(_variant_t* pv, short n);
void OT4XB_API _variant_t_Set_UI2(_variant_t* pv, WORD n);
void OT4XB_API _variant_t_Set_BOOL(_variant_t* pv, BOOL b);
BOOL OT4XB_API _variant_t_Get_BOOL(_variant_t* pv, BOOL* pVal );
void OT4XB_API _variant_t_Set_I4(_variant_t* pv, LONG n);
BOOL OT4XB_API _variant_t_Get_I4(_variant_t* pv, LONG* pn);
void OT4XB_API _variant_t_Set_UI4(_variant_t* pv, DWORD n);
BOOL OT4XB_API _variant_t_Get_UI4(_variant_t* pv, DWORD* pn);
void OT4XB_API _variant_t_Set_INT(_variant_t* pv, int n);
void OT4XB_API _variant_t_Set_UINT(_variant_t* pv, UINT n);
BOOL OT4XB_API _variant_t_Get_Int32(_variant_t* pv, LONG* pn);
void OT4XB_API _variant_t_Set_R4(_variant_t* pv, double n);
void OT4XB_API _variant_t_Set_R8(_variant_t* pv, double n);
void OT4XB_API _variant_t_Set_DATE(_variant_t* pv, double n);
void OT4XB_API _variant_t_Set_IUnknow(_variant_t* pv,IUnknown* p, BOOL bAddRef);
void OT4XB_API _variant_t_Set_UI1(_variant_t* pv, BYTE n);
void OT4XB_API _variant_t_Set_I1(_variant_t* pv, char n);
void OT4XB_API _variant_t_Set_I8(_variant_t* pv, LONGLONG n);
void OT4XB_API _variant_t_Set_UI8(_variant_t* pv, ULONGLONG n);
// void OT4XB_API _variant_t_Set_LPITEMIDLIST(_variant_t* pv,LPITEMIDLIST  p );
ContainerHandle OT4XB_API simple_variant_t_2_con(_variant_t* pv);
ContainerHandle OT4XB_API _variant_t_VT_ARRAY_2d2con(_variant_t* pv);
extern "C" HRESULT OT4XB_API _ot4xb_VariantChangeType(__out VARIANTARG * pvargDest, __in const VARIANTARG * pvarSrc, __in USHORT wFlags, __in VARTYPE vt);
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API __cdecl ft64_SetTs( FILETIME* pft, LPSTR ps , LONG* pnShift );
LPSTR OT4XB_API __cdecl ft64_GetTs( FILETIME* pft, LPSTR pFmt);
LPSTR OT4XB_API __cdecl ft64_ToHttp( FILETIME* pft);
void OT4XB_API __cdecl ft64_AddYears( FILETIME* pft, LONG y );
void OT4XB_API __cdecl ft64_AddMonths( FILETIME* pft, LONG m );
void OT4XB_API __cdecl ft64_SetUnixTime( FILETIME* pft, DWORD ut );
DWORD OT4XB_API __cdecl ft64_GetUnixTime( FILETIME* pft);
void OT4XB_API __cdecl ft64_SetUnixTime64( FILETIME* pft, LONGLONG ut );
LONGLONG OT4XB_API __cdecl ft64_GetUnixTime64( FILETIME* pft);
void OT4XB_API __cdecl ft64_SetRfc822Date( FILETIME* pft, LPSTR ps , LONG* pnShift );
void OT4XB_API __cdecl ft64_ToLocalTime( FILETIME* pft);
// -----------------------------------------------------------------------------------------------------------------
LPSTR OT4XB_API __cdecl ft64_strf( FILETIME* pft, LPSTR pFormat );
LPSTR OT4XB_API __cdecl ft64_strf_l( FILETIME* pft, LPSTR pFormat , LPSTR locale_string , int locale_category );
BOOL  OT4XB_API __cdecl ft64_now( FILETIME* pft );
// -----------------------------------------------------------------------------------------------------------------
BOOL  OT4XB_API __cdecl ot4xb_regex_match(LPSTR pattern, LPSTR string_to_test, int flags = 0, int match_flags = 0);


// -----------------------------------------------------------------------------------------------------------------

END_EXTERN_C
