//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Str2Md5Hex
            | syntax_: `Str2Md5Hex( cData [, nLen] )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: Str2Md5Hex, Function
   }}*/
/*{{|desc: Returns the 32-character hexadecimal MD5 digest of a string or OT4XB extended-pointer source.
    | params:
    - `cData` Character/extended pointer - Source bytes.
    - `nLen` Numeric - Optional number of bytes to hash.

    Returns Character/NIL - 32-character hexadecimal digest, or NIL when the source cannot be locked. }}*/
XPPRET XPPENTRY STR2MD5HEX( XppParamList pl )
{
   CON_PLKSTREX plk;
   LPBYTE pStr  = (LPBYTE) _conParamRLockStrEx(pl,1,&plk);
   ULONG  nLen  = ( _partype(pl,2) & XPP_NUMERIC ? _parLong(pl,2) : plk.nLen );
   LPSTR  pOut  = 0;
   if( pStr )
   {
      ot4xb_md5_internal md(pStr,nLen);
      pOut = (LPSTR) md.hex_digest();
   }
   _conUnLockStrEx_(&plk);
   if( pOut ) 
   {
      _retclen(pl,pOut,32);
      _xfree(pOut);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Str2Md5Bin
            | syntax_: `Str2Md5Bin( cData [, nLen] )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: Str2Md5Bin, Function
   }}*/
/*{{|desc: Returns the 16-byte binary MD5 digest of a string or OT4XB extended-pointer source.
    | params:
    - `cData` Character/extended pointer - Source bytes.
    - `nLen` Numeric - Optional number of bytes to hash.

    Returns Character/NIL - 16-byte binary digest, or NIL when the source cannot be locked. }}*/
XPPRET XPPENTRY STR2MD5BIN( XppParamList pl )
{
   CON_PLKSTREX plk;
   LPBYTE pStr  = (LPBYTE) _conParamRLockStrEx(pl,1,&plk);
   ULONG  nLen  = ( _partype(pl,2) & XPP_NUMERIC ? _parLong(pl,2) : plk.nLen );
   LPSTR  pOut  = 0;
   if( pStr )
   {
      ot4xb_md5_internal md(pStr,nLen);
      pOut = (LPSTR) md.raw_digest();
   }
   _conUnLockStrEx_(&plk);
   if( pOut ) 
   {
      _retclen(pl,pOut,16);
      _xfree(pOut);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: HFile2Md5Hex
            | syntax_: `HFile2Md5Hex( hFile )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: HFile2Md5Hex, Function
   }}*/
/*{{|desc: Reads from an existing Win32 file handle and returns its MD5 digest as hexadecimal text.
    | params:
    - `hFile` Numeric - Readable Win32 file handle.

    Returns Character/NIL - 32-character hexadecimal digest, or NIL on failure. }}*/
XPPRET XPPENTRY HFILE2MD5HEX( XppParamList pl )
{
   ot4xb_md5_internal md((HANDLE) _parLong(pl,1,0));
   LPSTR pOut = (LPSTR) md.hex_digest();
   if( pOut ) 
   {
      _retclen(pl,pOut,32);
      _xfree(pOut);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: HFile2Md5Bin
            | syntax_: `HFile2Md5Bin( hFile )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: HFile2Md5Bin, Function
   }}*/
/*{{|desc: Reads from an existing Win32 file handle and returns its MD5 digest as 16 raw bytes.
    | params:
    - `hFile` Numeric - Readable Win32 file handle.

    Returns Character/NIL - 16-byte binary digest, or NIL on failure. }}*/
XPPRET XPPENTRY HFILE2MD5BIN( XppParamList pl )
{
   ot4xb_md5_internal md((HANDLE) _parLong(pl,1,0));
   LPSTR pOut = (LPSTR) md.raw_digest();
   if( pOut ) 
   {
      _retclen(pl,pOut,16);
      _xfree(pOut);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: File2Md5Hex
            | syntax_: `File2Md5Hex( cFileName )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: File2Md5Hex, Function
   }}*/
/*{{|desc: Opens a file for reading and returns its MD5 digest as hexadecimal text.
    | params:
    - `cFileName` Character - File name to open with CreateFile().

    Returns Character/NIL - 32-character hexadecimal digest, or NIL when the file cannot be read. }}*/
XPPRET XPPENTRY FILE2MD5HEX( XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   LPSTR pFName         = _pszParam(pl,1);
   if( pFName )
   {
      HANDLE hFile = CreateFile(pFName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
      if( hFile && (hFile != INVALID_HANDLE_VALUE) )
      {
         ot4xb_md5_internal md(hFile);
         LPSTR pOut = (LPSTR) md.hex_digest();
         if( pOut ){ _conPutCL(conr,pOut,32);_xfree(pOut);}
         CloseHandle( hFile );
      }
      _xfree( pFName); 
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: File2Md5Bin
            | syntax_: `File2Md5Bin( cFileName )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: File2Md5Bin, Function
   }}*/
/*{{|desc: Opens a file for reading and returns its MD5 digest as 16 raw bytes.
    | params:
    - `cFileName` Character - File name to open with CreateFile().

    Returns Character/NIL - 16-byte binary digest, or NIL when the file cannot be read. }}*/
XPPRET XPPENTRY FILE2MD5BIN( XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   LPSTR pFName         = _pszParam(pl,1);
   if( pFName )
   {
      HANDLE hFile = CreateFile(pFName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
      if( hFile && (hFile != INVALID_HANDLE_VALUE) )
      {
         ot4xb_md5_internal md(hFile);
         LPSTR pOut = (LPSTR) md.raw_digest();
         if( pOut ){ _conPutCL(conr,pOut,16);_xfree(pOut);}
         CloseHandle( hFile );
      }
      _xfree( pFName); 
   }
   _conReturn(pl,conr); _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_new
            | syntax_: `_md5_new( [@pMd5] )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_new, Function
   }}*/
/*{{|desc: Allocates a low-level incremental MD5 context.
    | params:
    - `@pMd5` Numeric by reference - Optional existing context pointer to destroy and replace.

    Returns Numeric - Pointer to the new MD5 context. }}*/
XPPRET XPPENTRY _MD5_NEW( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   psc = new ot4xb_md5_internal;
   _stornl((LONG)psc, pl,1,0);
   _retnl( pl , (LONG) psc );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_str
            | syntax_: `_md5_str( pMd5, cData [, nLen] )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_str, Function
   }}*/
/*{{|desc: Adds a string or OT4XB extended-pointer source to a low-level incremental MD5 context.
    | params:
    - `pMd5` Numeric - Context pointer returned by _md5_new().
    - `cData` Character/extended pointer - Source bytes to add to the digest.
    - `nLen` Numeric - Optional number of bytes to add.

    Returns Logical - .T. when the chunk was added. }}*/
XPPRET XPPENTRY _MD5_STR( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc )
   { 
      CON_PLKSTREX plk;
      LPSTR pStr = _conParamRLockStrEx(pl,2,&plk);
      ULONG nLen = ( _partype(pl,3) & XPP_NUMERIC ? _parLong(pl,3) : plk.nLen );
      if( pStr ) bOk = psc->Update((LPBYTE) pStr,nLen);
      _conUnLockStrEx_(&plk);
   }
   _retl(pl,bOk);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_hfile
            | syntax_: `_md5_hfile( pMd5, hFile )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_hfile, Function
   }}*/
/*{{|desc: Adds file contents to a low-level incremental MD5 context.
    | params:
    - `pMd5` Numeric - Context pointer returned by _md5_new().
    - `hFile` Numeric - Readable Win32 file handle.

    Returns Logical - .T. when the file contents were added.

    |note: Low-level entry point. }}*/
XPPRET XPPENTRY _MD5_HFILE( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc )
   {  
      HANDLE hFile = (HANDLE) _parLong(pl,2,0);
      if( hFile && ( hFile != INVALID_HANDLE_VALUE ) ) bOk = psc->Update(hFile);
   }
   _retl(pl,bOk);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_finalize
            | syntax_: `_md5_finalize( pMd5 )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_finalize, Function
   }}*/
/*{{|desc: Finalizes a low-level incremental MD5 context.
    | params:
    - `pMd5` Numeric - Context pointer returned by _md5_new().

    Returns Logical - .T. when the context was finalized. }}*/
XPPRET XPPENTRY _MD5_FINALIZE( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc ) bOk = psc->Finalize();
   _retl(pl,bOk);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_gethex
            | syntax_: `_md5_gethex( pMd5 )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_gethex, Function
   }}*/
/*{{|desc: Returns the hexadecimal digest from a low-level MD5 context.
    | params:
    - `pMd5` Numeric - Context pointer returned by _md5_new().

    Returns Character/NIL - 32-character hexadecimal digest, or NIL when unavailable. }}*/
XPPRET XPPENTRY _MD5_GETHEX( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc )
   {
      LPSTR pStr = (LPSTR) psc->hex_digest();
      if( pStr )
      {
         _retclen(pl,pStr,32);
         _xfree(pStr);
         return;
      }
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_getbin
            | syntax_: `_md5_getbin( pMd5 )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_getbin, Function
   }}*/
/*{{|desc: Returns the binary digest from a low-level MD5 context.
    | params:
    - `pMd5` Numeric - Context pointer returned by _md5_new().

    Returns Character/NIL - 16-byte binary digest, or NIL when unavailable. }}*/
XPPRET XPPENTRY _MD5_GETBIN( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc )
   {
      LPSTR pStr = (LPSTR) psc->raw_digest();
      if( pStr )
      {
         _retclen(pl,pStr,16);
         _xfree(pStr);
         return;
      }
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _md5_destroy
            | syntax_: `_md5_destroy( @pMd5 )`
            | category: hash/md5
            | source: ot4xb_md5.cpp
            | _kw_: _md5_destroy, Function
   }}*/
/*{{|desc: Destroys a low-level MD5 context and clears the caller's pointer slot.
    | params:
    - `@pMd5` Numeric by reference - Context pointer returned by _md5_new().

    Returns Numeric - Always 0. }}*/
XPPRET XPPENTRY _MD5_DESTROY( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
