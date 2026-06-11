//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>Str2Md5Hex</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>
         Returns the 32-character hexadecimal MD5 digest of a string or OT4XB extended-pointer source.
      </description>
      <syntax>Str2Md5Hex( cData [, nLen] ) -> cHex32 | NIL</syntax>
      <parameters>
         <parameter><name>cData</name><type>Character | extended pointer</type><description>Source bytes.</description></parameter>
         <parameter><name>nLen</name><type>Numeric</type><description>Optional number of bytes to hash.</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>32-character hexadecimal digest, or NIL when the source cannot be locked.</description></return>
      <remarks>
         MD5 is retained for compatibility and checksums. It should not be used for new security-sensitive password or signature designs.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>Str2Md5Bin</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Returns the 16-byte binary MD5 digest of a string or OT4XB extended-pointer source.</description>
      <syntax>Str2Md5Bin( cData [, nLen] ) -> cBin16 | NIL</syntax>
      <parameters>
         <parameter><name>cData</name><type>Character | extended pointer</type><description>Source bytes.</description></parameter>
         <parameter><name>nLen</name><type>Numeric</type><description>Optional number of bytes to hash.</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>16-byte binary digest, or NIL when the source cannot be locked.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>HFile2Md5Hex</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Reads from an existing Win32 file handle and returns its MD5 digest as hexadecimal text.</description>
      <syntax>HFile2Md5Hex( hFile ) -> cHex32 | NIL</syntax>
      <parameters>
         <parameter><name>hFile</name><type>Numeric</type><description>Readable Win32 file handle.</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>32-character hexadecimal digest, or NIL on failure.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>HFile2Md5Bin</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Reads from an existing Win32 file handle and returns its MD5 digest as 16 raw bytes.</description>
      <syntax>HFile2Md5Bin( hFile ) -> cBin16 | NIL</syntax>
      <parameters>
         <parameter><name>hFile</name><type>Numeric</type><description>Readable Win32 file handle.</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>16-byte binary digest, or NIL on failure.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>File2Md5Hex</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Opens a file for reading and returns its MD5 digest as hexadecimal text.</description>
      <syntax>File2Md5Hex( cFileName ) -> cHex32 | NIL</syntax>
      <parameters>
         <parameter><name>cFileName</name><type>Character</type><description>File name to open with CreateFile().</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>32-character hexadecimal digest, or NIL when the file cannot be read.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>File2Md5Bin</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Opens a file for reading and returns its MD5 digest as 16 raw bytes.</description>
      <syntax>File2Md5Bin( cFileName ) -> cBin16 | NIL</syntax>
      <parameters>
         <parameter><name>cFileName</name><type>Character</type><description>File name to open with CreateFile().</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>16-byte binary digest, or NIL when the file cannot be read.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_new</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Allocates a low-level incremental MD5 context.</description>
      <syntax>_md5_new( [@pMd5] ) -> pMd5</syntax>
      <parameters>
         <parameter><name>@pMd5</name><type>Numeric by reference</type><description>Optional existing context pointer to destroy and replace.</description></parameter>
      </parameters>
      <return><type>Numeric</type><description>Pointer to the new MD5 context.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY _MD5_NEW( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   psc = new ot4xb_md5_internal;
   _stornl((LONG)psc, pl,1,0);
   _retnl( pl , (LONG) psc );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_str</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Adds a string or OT4XB extended-pointer source to a low-level incremental MD5 context.</description>
      <syntax>_md5_str( pMd5, cData [, nLen] ) -> lOk</syntax>
      <parameters>
         <parameter><name>pMd5</name><type>Numeric</type><description>Context pointer returned by _md5_new().</description></parameter>
         <parameter><name>cData</name><type>Character | extended pointer</type><description>Source bytes to add to the digest.</description></parameter>
         <parameter><name>nLen</name><type>Numeric</type><description>Optional number of bytes to add.</description></parameter>
      </parameters>
      <return><type>Logical</type><description>.T. when the chunk was added.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_hfile</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Adds file contents to a low-level incremental MD5 context.</description>
      <syntax>_md5_hfile( pMd5, hFile ) -> lOk</syntax>
      <parameters>
         <parameter><name>pMd5</name><type>Numeric</type><description>Context pointer returned by _md5_new().</description></parameter>
         <parameter><name>hFile</name><type>Numeric</type><description>Readable Win32 file handle.</description></parameter>
      </parameters>
      <return><type>Logical</type><description>.T. when the file contents were added.</description></return>
      <remarks>
         Low-level entry point. Verify the current implementation before using this function directly.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY _MD5_HFILE( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc )
   {  
      HANDLE hFile = (HANDLE) _parLong(pl,1,0);
      if( hFile && ( hFile != INVALID_HANDLE_VALUE ) ) bOk = psc->Update(hFile);
   }
   _retl(pl,bOk);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_finalize</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Finalizes a low-level incremental MD5 context.</description>
      <syntax>_md5_finalize( pMd5 ) -> lOk</syntax>
      <parameters>
         <parameter><name>pMd5</name><type>Numeric</type><description>Context pointer returned by _md5_new().</description></parameter>
      </parameters>
      <return><type>Logical</type><description>.T. when the context was finalized.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY _MD5_FINALIZE( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc ) bOk = psc->Finalize();
   _retl(pl,bOk);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_gethex</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Returns the hexadecimal digest from a low-level MD5 context.</description>
      <syntax>_md5_gethex( pMd5 ) -> cHex32 | NIL</syntax>
      <parameters>
         <parameter><name>pMd5</name><type>Numeric</type><description>Context pointer returned by _md5_new().</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>32-character hexadecimal digest, or NIL when unavailable.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_getbin</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Returns the binary digest from a low-level MD5 context.</description>
      <syntax>_md5_getbin( pMd5 ) -> cBin16 | NIL</syntax>
      <parameters>
         <parameter><name>pMd5</name><type>Numeric</type><description>Context pointer returned by _md5_new().</description></parameter>
      </parameters>
      <return><type>Character | NIL</type><description>16-byte binary digest, or NIL when unavailable.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>_md5_destroy</name>
      <source>ot4xb_md5.cpp</source>
      <category>hash/md5</category>
      <description>Destroys a low-level MD5 context and clears the caller's pointer slot.</description>
      <syntax>_md5_destroy( @pMd5 ) -> 0</syntax>
      <parameters>
         <parameter><name>@pMd5</name><type>Numeric by reference</type><description>Context pointer returned by _md5_new().</description></parameter>
      </parameters>
      <return><type>Numeric</type><description>Always 0.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY _MD5_DESTROY( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
}
// -----------------------------------------------------------------------------------------------------------------
