//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY HFILE2MD5BIN( XppParamList pl )
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
XPPRET XPPENTRY _MD5_NEW( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   psc = new ot4xb_md5_internal;
   _stornl((LONG)psc, pl,1,0);
   _retnl( pl , (LONG) psc );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _MD5_STR( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc )
   { 
      CON_PLKSTREX plk;
      LPSTR pStr = _conParamRLockStrEx(pl,1,&plk);
      ULONG nLen = ( _partype(pl,2) & XPP_NUMERIC ? _parLong(pl,2) : plk.nLen );
      if( pStr ) bOk = psc->Update((LPBYTE) pStr,nLen);
      _conUnLockStrEx_(&plk);
   }
   _retl(pl,bOk);
}
// -----------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY _MD5_FINALIZE( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   BOOL bOk = FALSE;
   if( psc ) bOk = psc->Finalize();
   _retl(pl,bOk);
}
// -----------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY _MD5_DESTROY( XppParamList pl )
{
   ot4xb_md5_internal* psc = reinterpret_cast<ot4xb_md5_internal*>(_parLong(pl,1));
   if( psc ) delete psc;
   _stornl(0,pl,1,0);
   _retnl(pl,0);
}
// -----------------------------------------------------------------------------------------------------------------
