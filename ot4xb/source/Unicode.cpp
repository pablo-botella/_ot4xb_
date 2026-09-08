//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_cStr( TXbClsParams * px );
static void UnicodeDynStr_wStr( TXbClsParams * px );
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: mb2w
            | syntax_: `LPWSTR mb2w( LPSTR pu, int cb, int * pcc, UINT nAcp, DWORD nFlags )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: mb2w
            | _kw_: mb2w, Function
   }}*/
/*{{|desc: Converts a multibyte string to a newly allocated zero-terminated UTF-16 wide string with
      MultiByteToWideChar(), using the given code page and flags.
    | params:
    - `pu` LPSTR - Source multibyte string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcc` int * - Optional pointer to receive the converted length in WCHARs. May be NULL.
    - `nAcp` UINT - Source code page, such as CP_ACP, CP_OEMCP or CP_UTF8.
    - `nFlags` DWORD - Flags passed to MultiByteToWideChar().

    Returns LPWSTR - Newly allocated zero-terminated wide string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API  LPWSTR mb2w( LPSTR pu ,int cb ,int* pcc , UINT nAcp , DWORD nFlags)
{
   int    cc = 0;
   LPWSTR  pw = 0;
   if( !pu ) return 0;
   if( cb == -1 ) cb = lstrlenA(pu);
   cc = MultiByteToWideChar(nAcp,nFlags,pu,(int)cb,0,0);
   pw = (LPWSTR) _xgrab( (cc * 2) +2 );
   cc = MultiByteToWideChar(nAcp,nFlags,pu,(int)cb,pw,cc+1);
   if( pcc ) pcc[0] = cc;
   return pw;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pAnsi2BSTR
            | syntax_: `BSTR pAnsi2BSTR( LPSTR pAnsi, int cb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: pAnsi2BSTR
            | _kw_: pAnsi2BSTR, Function
   }}*/
/*{{|desc: Converts an ANSI string to a newly allocated BSTR, using the process ANSI code page (CP_ACP).
    | params:
    - `pAnsi` LPSTR - Source ANSI string. NULL returns NULL.
    - `cb` int - Byte length of pAnsi, or -1 when zero-terminated (the terminator is not counted).

    Returns BSTR - Newly allocated BSTR. Release it with SysFreeString() when no longer needed. }}*/
OT4XB_API BSTR pAnsi2BSTR( LPSTR pAnsi , int cb)
{
   int    cc = 0;
   LPWSTR  pw = 0;
   if( !pAnsi ) return 0;
   if( cb == -1 ) cb = lstrlenA(pAnsi);
   cc = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)cb,0,0);
   pw = (LPWSTR) SysAllocStringLen(0,cc);
   ZeroMemory(pw,(cc*2));
   cc = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)cb,pw,cc+1);
   return (BSTR) pw;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: w2mb
            | syntax_: `LPSTR w2mb( LPWSTR pw, int cc, int * pcb, UINT nAcp, DWORD nFlags )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: w2mb
            | _kw_: w2mb, Function
   }}*/
/*{{|desc: Converts a UTF-16 wide string to a newly allocated zero-terminated multibyte string with
      WideCharToMultiByte(), using the given code page and flags.
    | params:
    - `pw` LPWSTR - Source wide string. NULL returns NULL.
    - `cc` int - Length of pw in WCHARs, or -1 when pw is zero-terminated (the terminator is not
      counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.
    - `nAcp` UINT - Destination code page, such as CP_ACP, CP_OEMCP or CP_UTF8.
    - `nFlags` DWORD - Flags passed to WideCharToMultiByte().

    Returns LPSTR - Newly allocated zero-terminated multibyte string, or NULL when pw is NULL. Release
      it with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR w2mb(LPWSTR pw , int cc,int* pcb, UINT nAcp , DWORD nFlags)
{
   int   cb = 0;
   LPSTR  pu = 0;
   if( !pw ) return 0;
   if( cc == -1 ) cc = lstrlenW(pw);
   cb = WideCharToMultiByte(nAcp,nFlags,pw,cc,NULL,0,0,0);
   pu = (LPSTR) _xgrab( cb + 2);
   cb = WideCharToMultiByte(nAcp,nFlags,pw,cc,pu,cb+1,0,0);
   if( pcb ) pcb[0] = cb;
   return pu;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: mb2mb
            | syntax_: ```
                 LPSTR mb2mb( LPSTR pa, int cb, int * pcb, UINT nAcpFrom, UINT nAcpTo, DWORD nFlags1, DWORD nFlags2 )
              ```
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: mb2mb
            | _kw_: mb2mb, Function
   }}*/
/*{{|desc: Converts a multibyte string from one Windows code page to another through an intermediate
      UTF-16 conversion.
    | params:
    - `pa` LPSTR - Source multibyte string. NULL returns NULL.
    - `cb` int - Byte length of pa, or -1 when pa is zero-terminated (the terminator is not counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.
    - `nAcpFrom` UINT - Source code page, used to expand pa to UTF-16.
    - `nAcpTo` UINT - Destination code page of the returned string.
    - `nFlags1` DWORD - Flags passed to MultiByteToWideChar() when expanding pa to UTF-16.
    - `nFlags2` DWORD - Flags passed to WideCharToMultiByte() when converting to the destination
      code page.

    Returns LPSTR - Newly allocated zero-terminated string in the destination code page, or NULL when
      pa is NULL. Release it with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR mb2mb(LPSTR pa ,int cb,int* pcb,UINT nAcpFrom , UINT nAcpTo , DWORD nFlags1, DWORD nFlags2)
{
   LPSTR  pu = 0;
   if(pa)
   {
      int    cc = 0;
      LPWSTR pw = mb2w(pa,cb,&cc,nAcpFrom,nFlags1);
      if( pw ) 
      {
         pu = w2mb(pw,cc,pcb,nAcpTo,nFlags2);         
         _xfree((void*) pw);
         pw = 0;
      }
   }
   return pu;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: w2utf8
            | syntax_: `LPSTR w2utf8( LPWSTR pw, int cc, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: w2utf8
            | _kw_: w2utf8, Function
   }}*/
/*{{|desc: Converts a UTF-16 wide string to a newly allocated zero-terminated UTF-8 string.
    | params:
    - `pw` LPWSTR - Source wide string. NULL returns NULL.
    - `cc` int - Length of pw in WCHARs, or -1 when pw is zero-terminated (the terminator is not
      counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated UTF-8 string, or NULL when pw is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR w2utf8(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_UTF8,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: w2ansi
            | syntax_: `LPSTR w2ansi( LPWSTR pw, int cc, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: w2ansi
            | _kw_: w2ansi, Function
   }}*/
/*{{|desc: Converts a UTF-16 wide string to a newly allocated zero-terminated ANSI string, using the
      process ANSI code page (CP_ACP).
    | params:
    - `pw` LPWSTR - Source wide string. NULL returns NULL.
    - `cc` int - Length of pw in WCHARs, or -1 when pw is zero-terminated (the terminator is not
      counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated ANSI string, or NULL when pw is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR w2ansi(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_ACP,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: w2oem
            | syntax_: `LPSTR w2oem( LPWSTR pw, int cc, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: w2oem
            | _kw_: w2oem, Function
   }}*/
/*{{|desc: Converts a UTF-16 wide string to a newly allocated zero-terminated OEM string, using the
      process OEM code page (CP_OEMCP).
    | params:
    - `pw` LPWSTR - Source wide string. NULL returns NULL.
    - `cc` int - Length of pw in WCHARs, or -1 when pw is zero-terminated (the terminator is not
      counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated OEM string, or NULL when pw is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR w2oem(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_OEMCP,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: utf82w
            | syntax_: `LPWSTR utf82w( LPSTR pu, int cb, int * pcc )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: utf82w
            | _kw_: utf82w, Function
   }}*/
/*{{|desc: Converts a UTF-8 string to a newly allocated zero-terminated UTF-16 wide string.
    | params:
    - `pu` LPSTR - Source UTF-8 string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcc` int * - Optional pointer to receive the converted length in WCHARs. May be NULL.

    Returns LPWSTR - Newly allocated zero-terminated wide string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API  LPWSTR utf82w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_UTF8,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ansi2w
            | syntax_: `LPWSTR ansi2w( LPSTR pu, int cb, int * pcc )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: ansi2w
            | _kw_: ansi2w, Function
   }}*/
/*{{|desc: Converts an ANSI string to a newly allocated zero-terminated UTF-16 wide string, using the
      process ANSI code page (CP_ACP).
    | params:
    - `pu` LPSTR - Source ANSI string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcc` int * - Optional pointer to receive the converted length in WCHARs. May be NULL.

    Returns LPWSTR - Newly allocated zero-terminated wide string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API  LPWSTR ansi2w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_ACP,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: oem2w
            | syntax_: `LPWSTR oem2w( LPSTR pu, int cb, int * pcc )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: oem2w
            | _kw_: oem2w, Function
   }}*/
/*{{|desc: Converts an OEM string to a newly allocated zero-terminated UTF-16 wide string, using the
      process OEM code page (CP_OEMCP).
    | params:
    - `pu` LPSTR - Source OEM string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcc` int * - Optional pointer to receive the converted length in WCHARs. May be NULL.

    Returns LPWSTR - Newly allocated zero-terminated wide string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API  LPWSTR oem2w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_OEMCP,0); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ansi2utf8
            | syntax_: `LPSTR ansi2utf8( LPSTR pa, int cb, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: ansi2utf8
            | _kw_: ansi2utf8, Function
   }}*/
/*{{|desc: Converts an ANSI string to a newly allocated zero-terminated UTF-8 string, using the process
      ANSI code page (CP_ACP) as the source encoding.
    | params:
    - `pa` LPSTR - Source ANSI string. NULL returns NULL.
    - `cb` int - Byte length of pa, or -1 when pa is zero-terminated (the terminator is not counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated UTF-8 string, or NULL when pa is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR ansi2utf8( LPSTR pa ,int cb,int* pcb){ return mb2mb(pa,cb,pcb,CP_ACP,CP_UTF8,0,0);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: oem2utf8
            | syntax_: `LPSTR oem2utf8( LPSTR po, int cb, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: oem2utf8
            | _kw_: oem2utf8, Function
   }}*/
/*{{|desc: Converts an OEM string to a newly allocated zero-terminated UTF-8 string, using the process
      OEM code page (CP_OEMCP) as the source encoding.
    | params:
    - `po` LPSTR - Source OEM string. NULL returns NULL.
    - `cb` int - Byte length of po, or -1 when po is zero-terminated (the terminator is not counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated UTF-8 string, or NULL when po is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR oem2utf8(  LPSTR po ,int cb,int* pcb){ return mb2mb(po,cb,pcb,CP_OEMCP,CP_UTF8,0,0);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: utf82ansi
            | syntax_: `LPSTR utf82ansi( LPSTR pu, int cb, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: utf82ansi
            | _kw_: utf82ansi, Function
   }}*/
/*{{|desc: Converts a UTF-8 string to a newly allocated zero-terminated ANSI string, using the process
      ANSI code page (CP_ACP) as the destination encoding.
    | params:
    - `pu` LPSTR - Source UTF-8 string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated ANSI string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR utf82ansi( LPSTR pu ,int cb,int* pcb){ return mb2mb(pu,cb,pcb,CP_UTF8,CP_ACP,0,0);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: utf82oem
            | syntax_: `LPSTR utf82oem( LPSTR pu, int cb, int * pcb )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: utf82oem
            | _kw_: utf82oem, Function
   }}*/
/*{{|desc: Converts a UTF-8 string to a newly allocated zero-terminated OEM string, using the process
      OEM code page (CP_OEMCP) as the destination encoding.
    | params:
    - `pu` LPSTR - Source UTF-8 string. NULL returns NULL.
    - `cb` int - Byte length of pu, or -1 when pu is zero-terminated (the terminator is not counted).
    - `pcb` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated OEM string, or NULL when pu is NULL. Release it
      with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR utf82oem(  LPSTR pu ,int cb,int* pcb){ return mb2mb(pu,cb,pcb,CP_UTF8,CP_OEMCP,0,0);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cSzAnsi2Wide
            | syntax_: `cSzAnsi2Wide( cAnsi )`
            | category: unicode
            | _kw_: cSzAnsi2Wide, Function
   }}*/
/*{{|desc: Converts an ANSI string using the process ANSI code page to a wide-character binary string.
    | params:
    - `cAnsi` Character - ANSI string encoded with the current Windows ANSI code page.

    Returns Character - UTF-16 little-endian binary string, zero-terminated when the input was not already
      zero-terminated. }}*/
XPPRET XPPENTRY CSZANSI2WIDE(XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1 , &bByRef , XPP_CHARACTER );
   ContainerHandle conr = NULLCONTAINER;
   if( conc != NULLCONTAINER )
   {
      LPSTR pAnsi = (LPSTR) 0;
      ULONG nLen  = 0;
      if(  ot4xb_conRLockC(conc, &pAnsi , &nLen ) == 0 )
      {
         if( nLen > 0 )
         {
            ULONG nWBytes = (nLen * 2) + (pAnsi[(nLen-1)] == 0 ? 0 : 2);
            LPWSTR pWide = (LPWSTR) _xgrab( nWBytes );
            MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,nLen,pWide,nLen);
            conr = _conPutCL(conr,(LPSTR)((void *) pWide),nWBytes);
            _xfree( (void*) pWide);
         }
         ot4xb_conUnlockC( conc ); pAnsi = (LPSTR) 0;
      } 
      if( !bByRef) _conRelease( conc);
   }
   if( conr == NULLCONTAINER ) _retclen( pl , "\0\0" , 2);
   else { _conReturn( pl, conr); _conRelease( conr); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cSzWide2Ansi
            | syntax_: `cSzWide2Ansi( cWide )`
            | category: unicode
            | _kw_: cSzWide2Ansi, Function
   }}*/
/*{{|desc: Converts a wide-character binary string to an ANSI string using the process ANSI code page.
    | params:
    - `cWide` Character - UTF-16 little-endian binary string.

    Returns Character - ANSI string decoded from cWide, or an empty string when cWide is empty. }}*/
XPPRET XPPENTRY CSZWIDE2ANSI(XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1 , &bByRef , XPP_CHARACTER );
   ContainerHandle conr = NULLCONTAINER;
   if( conc != NULLCONTAINER )
   {
      LPWSTR pWide = (LPWSTR) 0;
      ULONG nWBytes  = 0;
      if(  ot4xb_conRLockC(conc,(LPSTR *)((void*) &pWide) , &nWBytes ) == 0 )
      {
         if( nWBytes > 1 )
         {
            ULONG nLen  = ( nWBytes >> 1 );
            LPSTR pAnsi = (LPSTR) _xgrab( nLen + 1);
            WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pWide,nLen,pAnsi,nLen,0,0);
            conr = _conPutC(conr,pAnsi);
            _xfree( (void*) pAnsi);
         }
         ot4xb_conUnlockC( conc ); pWide = (LPWSTR) 0;
      }
      if( !bByRef) _conRelease( conc);
   }
   if( conr == NULLCONTAINER ) _retc(pl,"");
   else { _conReturn( pl, conr); _conRelease( conr); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>UNICODEDYNSTR</name>
      <parent>GWST</parent>
      <source>Unicode.cpp:UNICODEDYNSTR</source>
      <category>unicode</category>
      <description>
         Structure-style helper class that encapsulates a pointer to a Windows Unicode string.
         It is useful when a Win32/OT4XB call needs a writable pointer to a wide string, especially through
         the OT4XB extended pointer mechanism.
      </description>
      <syntax>UNICODEDYNSTR():New() -> oUnicodeString</syntax>
      <members>
         <member type="LPWSTR" name="p" offset="0">
            Pointer to the current wide string buffer.
         </member>
      </members>
      <instance-variables>
         <variable>
            <name>_pp_</name>
            <description>Internal pointer owned by this object when the buffer was assigned through ::cStr or ::wStr.</description>
         </variable>
         <variable>
            <name>_nBytes_</name>
            <description>Internal byte length of the assigned wide string, not including the terminating WCHAR.</description>
         </variable>
      </instance-variables>
      <properties>
         <property>
            <name>UNICODEDYNSTR::cStr</name>
            <syntax>::cStr := cAnsi</syntax>
            <syntax>::cStr -> cAnsi</syntax>
            <description>
               Assigning an ANSI Xbase++ string converts it from CP_ACP to a zero-terminated WCHAR buffer,
               stores the buffer pointer in ::p, and keeps ownership in the object. Reading converts the
               pointed wide string back to ANSI.
            </description>
         </property>
         <property>
            <name>UNICODEDYNSTR::wStr</name>
            <syntax>::wStr := cWideBytes</syntax>
            <syntax>::wStr -> cWideBytes</syntax>
            <description>
               Assigning a binary WCHAR string stores a copy as a zero-terminated wide buffer and updates ::p.
               Reading returns the wide string bytes.
            </description>
         </property>
      </properties>
      <remarks>
         If ::p is changed to point to external memory, the object does not own that external memory.
         When ::p differs from the internally owned pointer, ::cStr and ::wStr assume that ::p points to a
         zero-terminated WCHAR string.
      </remarks>
      <remarks>
         Assigning a new value to ::cStr or ::wStr releases the previous internally owned buffer. Assigning
         NIL or any non-character value clears ::p and releases the owned buffer.
      </remarks>
      <example><![CDATA[
local ws := UNICODEDYNSTR():New()

ws:cStr := "caption"
SomeApiThatExpectsWidePointer( ws )

? ws:cStr
ws:cStr := NIL
      ]]></example>
   </class>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY UNICODEDYNSTR( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("UNICODEDYNSTR");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("UNICODEDYNSTR");
      pc->GwstParent();
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Var("_pp_");
      pc->Var("_nBytes_");
      pc->Member_Pointer32("p");
      pc->Property("cStr", UnicodeDynStr_cStr , 1 );
      pc->Property("wStr", UnicodeDynStr_wStr , 1 );
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_cStr( TXbClsParams * px )
{
   ContainerHandle Self = px->GetSelf();
   void * p  = (void*) _conGetNLMember(Self,"p");
   void * pp = (void*) _conGetNLMember(Self,"_pp_");

   if( px->PCount() > 0 )
   {
      if( pp != NULL ){ _xfree( pp ); pp = NULL; }
      if( px->CheckParamType(1, XPP_CHARACTER ) )
      {
         ULONG   nLen   = 0;
         LPSTR   pStr   = px->ParamLockStr(1,&nLen);
         ULONG   nBytes = ((nLen * 2) + 2);
         LPWSTR  pWide  = ( LPWSTR ) _xgrab( nBytes );
         MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pStr,nLen,pWide,nLen);
         px->ParamUnlockStr(1); pStr = NULL;
         _conSetNLMember(Self,"p",(LONG) pWide);
         _conSetNLMember(Self,"_pp_",(LONG) pWide);
         _conSetNLMember(Self,"_nBytes_",(LONG) (nLen * 2) );
         px->PutReturn( px->GetParam(1) );
         return;
      }
      else
      {
         _conSetNLMember(Self,"p",0);
         _conSetNLMember(Self,"_pp_",0);
         _conSetNLMember(Self,"_nBytes_",0);
      }
   }
   else
   {
      if( p == pp ) // String was stored trought ::cStr or ::wStr methods
      {
         ULONG nBytes = (ULONG ) _conGetNLMember(Self,"_nBytes_");
         ULONG nLen   = (nBytes >> 1);
         LPSTR pStr   = (LPSTR) _xgrab(nLen);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,( LPWSTR )p,nLen,pStr,nLen,0,0);
         px->PutReturnStrLen(pStr,nLen);
         _xfree((void*) pStr);
      }
      else  // assuming string is Zero terminated
      {
         LPWSTR  pWide  = ( LPWSTR ) p;
         ULONG nLen     = 0;
         ULONG n;
         LPSTR pStr;
         for( n = 0; (pWide[n] != (WCHAR) 0); n++) nLen++;
         pStr   = (LPSTR) _xgrab(nLen);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pWide,nLen,pStr,nLen,0,0);
         px->PutReturnStrLen(pStr,nLen);
         _xfree((void*) pStr);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_wStr( TXbClsParams * px )
{
   ContainerHandle Self = px->GetSelf();
   void * p  = (void*) _conGetNLMember(Self,"p");
   void * pp = (void*) _conGetNLMember(Self,"_pp_");
   if( px->PCount() > 0 )
   {
      if( pp != NULL ){ _xfree( pp ); pp = NULL; }
      if( px->CheckParamType(1, XPP_CHARACTER ) )
      {
         ULONG    nBytes = 0;
         LPWSTR   pWStr   = (LPWSTR) px->ParamLockStr(1,&nBytes);
         ULONG    nLen   = (nBytes >> 1);
         LPWSTR   pWide;
         ULONG    n;

         if( nLen > 0 )
         {
            if( pWStr[nLen-1] != (WCHAR) 0 ) nBytes += 2;
         }
         else nBytes = 2;
         pWide = (LPWSTR) _xgrab( nBytes );
         for( n = 0; n < nLen; n++ )  pWide[n] = pWStr[n];
         px->ParamUnlockStr(1); pWStr = NULL;
         _conSetNLMember(Self,"p",(LONG) pWide);
         _conSetNLMember(Self,"_pp_",(LONG) pWide);
         _conSetNLMember(Self,"_nBytes_",(LONG) (nLen * 2));
         px->PutReturn( px->GetParam(1) );
      }
      else
      {
         _conSetNLMember(Self,"p",0);
         _conSetNLMember(Self,"_pp_",0);
         _conSetNLMember(Self,"_nBytes_",0);
      }
   }
   else
   {
      if( p == pp ) // String was stored trought ::cStr or ::wStr methods
      {
         ULONG nBytes = (ULONG ) _conGetNLMember(Self,"_nBytes_");
         px->PutReturnStrLen((LPSTR)p,nBytes);
      }
      else  // assuming string is Zero terminated
      {
         LPWSTR  pWide  = ( LPWSTR ) p;
         ULONG nLen = 0;
         ULONG n;
         for( n = 0; (pWide[n] != (WCHAR) 0); n++) nLen++;
         px->PutReturnStrLen((LPSTR) p,(nLen* 2));
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUtf8ToAnsi
            | syntax_: `cUtf8ToAnsi( cUtf8 )`
            | category: unicode
            | _kw_: cUtf8ToAnsi, Function
   }}*/
/*{{|desc: Converts UTF-8 text to ANSI using the process ANSI code page.
    | params:
    - `cUtf8` Character - UTF-8 encoded text.

    Returns Character - Text converted to the current Windows ANSI code page. }}*/
XPPRET XPPENTRY CUTF8TOANSI(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nUtf8Len * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_UTF8,0,pUtf8,(int)nUtf8Len,pWide,(int)(nUtf8Len+1));
         int    nAnsiLen = WideCharToMultiByte(CP_ACP,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pAnsi    = (LPSTR) _xgrab((UINT) (nAnsiLen + 1));
         nAnsiLen = WideCharToMultiByte(CP_ACP,0,pWide,nWideLen,pAnsi,nAnsiLen+1,0,0);
         _conPutCL(conr,pAnsi,(ULONG)nAnsiLen);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pAnsi );         
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cAnsiToUtf8
            | syntax_: `cAnsiToUtf8( cAnsi )`
            | category: unicode
            | _kw_: cAnsiToUtf8, Function
   }}*/
/*{{|desc: Converts ANSI text from the process ANSI code page to UTF-8.
    | params:
    - `cAnsi` Character - ANSI text encoded with the current Windows ANSI code page.

    Returns Character - UTF-8 encoded text. }}*/
XPPRET XPPENTRY CANSITOUTF8(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nAnsiLen = 0;
      LPSTR pAnsi    = 0;
      if( ot4xb_conRLockC(conc,&pAnsi,&nAnsiLen) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nAnsiLen * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)nAnsiLen,pWide,(int)(nAnsiLen+1));
         int    nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pUtf8    = (LPSTR) _xgrab((UINT) (nUtf8Len + 1));
         nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,pUtf8,nUtf8Len+1,0,0);
         _conPutCL(conr,pUtf8,(ULONG)nUtf8Len);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pUtf8 );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUtf8ToOem
            | syntax_: `cUtf8ToOem( cUtf8 )`
            | category: unicode
            | _kw_: cUtf8ToOem, Function
   }}*/
/*{{|desc: Converts UTF-8 text to the process OEM code page.
    | params:
    - `cUtf8` Character - UTF-8 encoded text.

    Returns Character - Text converted to the current Windows OEM code page. }}*/
XPPRET XPPENTRY CUTF8TOOEM(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nUtf8Len * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_UTF8,0,pUtf8,(int)nUtf8Len,pWide,(int)(nUtf8Len+1));
         int    nOemLen = WideCharToMultiByte(CP_OEMCP,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pOem    = (LPSTR) _xgrab((UINT) (nOemLen + 1));
         nOemLen = WideCharToMultiByte(CP_OEMCP,0,pWide,nWideLen,pOem,nOemLen+1,0,0);
         _conPutCL(conr,pOem,(ULONG)nOemLen);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pOem );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cOemToUtf8
            | syntax_: `cOemToUtf8( cOem )`
            | category: unicode
            | _kw_: cOemToUtf8, Function
   }}*/
/*{{|desc: Converts OEM text from the process OEM code page to UTF-8.
    | params:
    - `cOem` Character - OEM text encoded with the current Windows OEM code page.

    Returns Character - UTF-8 encoded text. }}*/
XPPRET XPPENTRY COEMTOUTF8(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nOemLen = 0;
      LPSTR pOem    = 0;
      if( ot4xb_conRLockC(conc,&pOem,&nOemLen) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nOemLen * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_OEMCP,0,pOem,(int)nOemLen,pWide,(int)(nOemLen+1));
         int    nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pUtf8    = (LPSTR) _xgrab((UINT) (nUtf8Len + 1));
         nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,pUtf8,nUtf8Len+1,0,0);
         _conPutCL(conr,pUtf8,(ULONG)nUtf8Len);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pUtf8 );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pAnsi2WStr
            | syntax_: `WCHAR * pAnsi2WStr( LPSTR pAnsi, int cb, int * pcc )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: pAnsi2WStr
            | _kw_: pAnsi2WStr, Function
   }}*/
/*{{|desc: Converts an ANSI string to a newly allocated zero-terminated UTF-16 wide string, using the
      process ANSI code page (CP_ACP) with the MB_PRECOMPOSED flag.
    | params:
    - `pAnsi` LPSTR - Source ANSI string.
    - `cb` int - Byte length of pAnsi, or -1 when zero-terminated (the terminator is not counted).
    - `pcc` int * - Optional pointer to receive the converted length in WCHARs. May be NULL.

    Returns WCHAR * - Newly allocated zero-terminated wide string, or NULL when pAnsi is NULL or empty.
      Release it with _xfree() when no longer needed. }}*/
OT4XB_API WCHAR * pAnsi2WStr( LPSTR pAnsi , int cb , int* pcc )
{
   if( pAnsi )
   {
      if( (cb == -1 ) && pAnsi ) cb = (int) _xstrlen(pAnsi);
      if( pAnsi && cb )
      {
         LPWSTR pWide = (LPWSTR) _xgrab( (ULONG) ((cb + 1) * 2) );
         int    cc    = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,cb,pWide,cb);
         if( pcc ) pcc[0] = cc;
         return pWide;
      }
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pWStr2Ansi
            | syntax_: `LPSTR pWStr2Ansi( WCHAR * pWide, int cc, int * pcc )`
            | category: unicode
            | header: ot4xb_c_exported.h
            | mangled-name: pWStr2Ansi
            | _kw_: pWStr2Ansi, Function
   }}*/
/*{{|desc: Converts a UTF-16 wide string to a newly allocated zero-terminated ANSI string, using the
      process ANSI code page (CP_ACP) with the WC_COMPOSITECHECK flag.
    | params:
    - `pWide` WCHAR * - Source wide string. NULL returns NULL.
    - `cc` int - Length of pWide in WCHARs, or -1 when zero-terminated (the terminator is not
      counted).
    - `pcc` int * - Optional pointer to receive the converted length in bytes. May be NULL.

    Returns LPSTR - Newly allocated zero-terminated ANSI string, or NULL when pWide is NULL. Release
      it with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR pWStr2Ansi( WCHAR* pWide  , int cc, int* pcc)
{
   return w2mb( pWide, cc, pcc, CP_ACP, WC_COMPOSITECHECK );   // w2mb sizes by byte count -> DBCS-safe
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// Added behavior: PeekWStr(pMem,[@]nShift,-1) Assuming Zero terminated string
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekWStr
            | syntax_: `PeekWStr( pMem, @nShift, nChars )`
            | category: unicode/memory
            | _kw_: PeekWStr, Function
   }}*/
/*{{|desc: Reads UTF-16 little-endian data from a memory buffer or pointer.
    | params:
    - `pMem` Pointer/Character - Source memory or binary string.
    - `nShift` Numeric by reference - Byte offset in the source. It is updated after the read.
    - ``nChars | cWide | aItems`` Numeric/Character by reference/Array - Numeric values read that many
      UTF-16 characters. -1 reads a zero-terminated UTF-16 string. A character by reference receives as many
      bytes as its current length. An array reads several fields in sequence; character items use their
      current byte length and numeric items are interpreted as character counts.

    Returns Returns the UTF-16 binary string, the number of bytes written to the by-reference string, the
      updated array, or NIL when the source cannot be locked.

    |note: Also PeekWStr( pMem, @nShift, @cWide ) -> nBytes

    |note: Also PeekWStr( pMem, @nShift, aItems ) -> aItems }}*/
XPPRET XPPENTRY PEEKWSTR(XppParamList pl)
{
    CON_PLKSTREX plk;
    LPSTR p      = (LPSTR) _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);

    if( p == 0){_conUnLockStrEx_(&plk); _ret(pl); return;}

    if( ulType & XPP_CHARACTER )
    {
       BOOL bByRef = FALSE;
       ContainerHandle con = _conParam(pl,3,&bByRef);
       ULONG nSize = 0;
       p += nShift;
       if( con == NULLCONTAINER ){_conUnLockStrEx_(&plk); _ret(pl); return;}
       _conSizeC(con,&nSize);
       _conPutCL(con,p,nSize);
       if(!bByRef) _conRelease(con);
       _stornl(nShift+nSize,pl,2);
       _conUnLockStrEx_(&plk);
       _retnl(pl,nSize);
       return;
    }
    else if( ulType & XPP_NUMERIC)
    {
       ContainerHandle conr = NULLCONTAINER;
       LONG nSize = (_parLong(pl,3) * 2);
       p += nShift;
       if( nSize < 0 )
       {
          nSize = (lstrlenW( (LPWSTR) p ) * 2);
          _stornl(nShift+nSize+2,pl,2);
       }
       else
       {
          _stornl(nShift+nSize,pl,2);
       }
       conr = _conPutCL( conr , p,(ULONG) nSize);
       _conUnLockStrEx_(&plk);
       _conReturn( pl , conr );
       _conRelease(conr );
       return;
    }
    else if( ulType & XPP_ARRAY )
    {
       ContainerHandle cona = _conParam(pl,3,0);
       ULONG nItems = 0;
       ULONG nn;
       //LONG  nRead = 0;
       _conSizeA( cona, &nItems , 0 );
       for( nn = 1; nn <= nItems; nn++)
       {
          LONG nSize;
          ulType = 0;
          _conTypeA(cona,&ulType,nn,0);
          if( ulType & XPP_CHARACTER )
          {
             nSize = _conArrayGetSizeC(cona,nn,0);
             _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
             nShift += nSize;
          }
          else
          {
             nSize = ( _conArrayGetNL(cona,nn,0) * 2);
             if( nSize < 0 )
             {
                 nSize = (lstrlenW( reinterpret_cast<LPWSTR>(p + nShift) ) * 2);
                 _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
                 nShift += (nSize + 2);
             }
             else
             {
                _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
                nShift += nSize;
             }
          }
          //nRead  += nSize;
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
       return;
    }
    _conUnLockStrEx_(&plk);
    _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUtf8ToWide
            | syntax_: `cUtf8ToWide( cUtf8 )`
            | category: unicode
            | _kw_: cUtf8ToWide, Function
   }}*/
/*{{|desc: Converts UTF-8 text to a UTF-16 little-endian binary string.
    | params:
    - `cUtf8` Character - UTF-8 encoded text.

    Returns Character - UTF-16 little-endian binary string. }}*/
XPPRET XPPENTRY CUTF8TOWIDE(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         int    nWideLen = 0;
         LPWSTR pWide    = utf82w(pUtf8,nUtf8Len,&nWideLen);
         ot4xb_conUnlockC(conc);
         _conPutCL(conr,(LPSTR) pWide,nWideLen * 2);
         _xfree( (void*) pWide );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _mb2w
            | syntax_: `_mb2w( cText, nCodePage [, nFlags] [, lNoAddZero] )`
            | category: unicode
            | _kw_: _mb2w, Function
   }}*/
/*{{|desc: Converts a multibyte string from a selected Windows code page to UTF-16.
    | params:
    - `cText` Character - Source multibyte text.
    - `nCodePage` Numeric - Windows code page, such as 0 for CP_ACP, 1 for CP_OEMCP, or 65001 for CP_UTF8.
    - `nFlags` Numeric - Flags passed to MultiByteToWideChar().
    - `lNoAddZero` Logical - When .T., do not include an extra terminating zero byte in the source length.

    Returns Character - UTF-16 little-endian binary string. }}*/
_XPP_REG_FUN_( _MB2W )
{
   TXppParamList xpp(pl,4);
   int   cb = 0;
   LPSTR pu = xpp[1]->LockStr((ULONG*) &cb); if( !pu ){ return; }      
   int cc = 0;
   LPWSTR pw = mb2w(pu,cb+(xpp[4]->GetBool() ? 0 : 1 ),&cc,xpp[2]->GetDWord(),xpp[3]->GetDWord());
   if( !pw ){ return; }
   xpp[0]->PutStrLen( (LPSTR) pw , (ULONG) cc * 2 );
   _xfree((void*) pw);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _w2mb
            | syntax_: `_w2mb( cWide, nCodePage [, nFlags] [, lRemoveZero] )`
            | category: unicode
            | _kw_: _w2mb, Function
   }}*/
/*{{|desc: Converts a UTF-16 little-endian binary string to a selected Windows multibyte code page.
    | params:
    - `cWide` Character - UTF-16 little-endian binary string.
    - `nCodePage` Numeric - Windows code page, such as 0 for CP_ACP, 1 for CP_OEMCP, or 65001 for CP_UTF8.
    - `nFlags` Numeric - Flags passed to WideCharToMultiByte().
    - `lRemoveZero` Logical - When .T., remove one trailing zero byte from the converted result when
      present.

    Returns Character - Converted multibyte string. }}*/
_XPP_REG_FUN_( _W2MB )
{
   TXppParamList xpp(pl,4);
   int cc = 0;
   LPWSTR pw = (LPWSTR ) xpp[1]->LockStr((ULONG*) &cc); if( !pw ){ return; }
   cc = cc >> 1;
   int   cb = 0;  
   LPSTR pu = w2mb(pw,cc,&cb,xpp[2]->GetDWord(),xpp[3]->GetDWord());
   if(!pu){ return; }   
   if(xpp[4]->GetBool()){if( cb > 0 ){ if( pu[(cb-1)] == 0 ){ cb--; }}}
   xpp[0]->PutStrLen(pu,(ULONG)cb);
   _xfree((void*) pu);   
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
//#define CP_ACP                    0           // default to ANSI code page
//#define CP_OEMCP                  1           // default to OEM  code page
//#define CP_THREAD_ACP             3           // current thread's ANSI code page
//#define CP_UTF8                   65001       // UTF-8 translation
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _mb2mb
            | syntax_: `_mb2mb( cText, nCodePageFrom, nCodePageTo [, nFlagsFrom] [, nFlagsTo] )`
            | category: unicode
            | _kw_: _mb2mb, Function
   }}*/
/*{{|desc: Converts a multibyte string from one Windows code page to another.
    | params:
    - `cText` Character - Source multibyte text.
    - `nCodePageFrom` Numeric - Source Windows code page.
    - `nCodePageTo` Numeric - Destination Windows code page.
    - `nFlagsFrom` Numeric - Flags passed to MultiByteToWideChar() for the source conversion.
    - `nFlagsTo` Numeric - Flags passed to WideCharToMultiByte() for the destination conversion.

    Returns Character - Converted multibyte string. }}*/
_XPP_REG_FUN_( _MB2MB)
{
   TXppParamList xpp(pl,5);
   int   cb1 = 0;
   LPSTR p1  = xpp[1]->LockStr((ULONG*) &cb1); if( !p1 ){ return; }
   int   cb2 = 0;  
   LPSTR p2  = mb2mb(p1,cb1,&cb2,xpp[2]->GetDWord(),xpp[3]->GetDWord(),xpp[4]->GetDWord(),xpp[5]->GetDWord());
   if( !p2 ){ return; }   
   xpp[0]->PutStrLen(p2,(ULONG)cb2);
   _xfree((void*) p2);   
}
/*{{end-function}}*/