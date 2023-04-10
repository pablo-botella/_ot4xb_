//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <Shlwapi.h>
#define OT4XB_COPYFILE_BUFFER_SIZE  0x80000  // 512kb
//typedef BOOL ( __stdcall * ft_CopyFileEx )(LPSTR,LPSTR,DWORD,void*,BOOL*,DWORD);
//----------------------------------------------------------------------------------------------------------------------
// static ft_CopyFileEx fp_CopyFileEx = 0;
static char  _pAppName_[512];
static DWORD _dwAppName_ = 0;
static DWORD _dwAppPath_ = 0;
static int _pStaticAZDrives_[27];
//----------------------------------------------------------------------------------------------------------------------
static char  _pStaticBackSlashChar_[] = "\\";
static char  _pStaticZeroChar_[] = "";

//----------------------------------------------------------------------------------------------------------------------
typedef struct DRTHREAD__struct
{
   HANDLE     ht;
   LPSTR      pPath;
   BOOL       bTimeOut;
   BOOL       bComplete;
   DWORD      dwcrc;
   void *     pNext;
   void *     pPrev;
} DRTHREAD;
static CRITICAL_SECTION _drcs_;
static DRTHREAD * _pdrt_ = 0;
//----------------------------------------------------------------------------------------------------------------------
CRITICAL_SECTION* _drtool_get_pcs_( void ){ return &_drcs_; }
//----------------------------------------------------------------------------------------------------------------------
DWORD WINAPI lDiskReady_internal(void * p );
//----------------------------------------------------------------------------------------------------------------------
//static ULONG PathNameTrans(LPSTR lpStr,LPSTR lpMax,LPSTR pTemp, PLONG pItems,LPSTR * ppRoot);
//----------------------------------------------------------------------------------------------------------------------
void _API_DrTool_InitProc(void)
{
    int n;
    char ch;

    InitializeCriticalSection( &_drcs_ );
    // fp_CopyFileEx = (ft_CopyFileEx) GetProcAddress(GetModuleHandle("kernel32"),"CopyFileExA");

    for( n=0,ch='A';ch <='Z'; ch++,n++)
    {
       LPSTR p = (LPSTR)( (void*) &_pStaticAZDrives_[n]);
       _pStaticAZDrives_[n] = 0;
       p[0] = ch; p[1] = ':';
    }

    _bset((LPBYTE)_pAppName_,0,512);
    _dwAppName_ = GetModuleFileName( NULL , _pAppName_ , 511 );
    for( n = (int) _dwAppName_; n >= 0; n--)
    {
       if( _pAppName_[n] == '\\' ){_dwAppPath_ = (DWORD) n; return;}
    }
}
//----------------------------------------------------------------------------------------------------------------------
void _API_DrTool_ExitProc(void)
{
      DRTHREAD * p;
      EnterCriticalSection( &_drcs_);
      __try
      {
         for( p =_pdrt_ ; p ; p = (DRTHREAD *) p->pNext )
         {
            TerminateThread( p->ht , 0);
            CloseHandle( p->ht );
            p->ht = 0;
         }
      }
      __finally
      {
         LeaveCriticalSection( &_drcs_);
      }
      DeleteCriticalSection( &_drcs_ );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY GETCOMMANDLINE( XppParamList pl ){ _retc(pl, GetCommandLine()); }
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CAPPPATH( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_+1);}
// ---------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CAPPDIR( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_);}
//----------------------------------------------------------------------------------------------------------------------
// like CopyFile() but using the ACLs of the destination folder
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
static BOOL ot4xb_CopyFile( LPSTR pSrc , LPSTR pDst , BOOL bFailIfExist )
{
   HANDLE hSrc = INVALID_HANDLE_VALUE;
   HANDLE hDst = INVALID_HANDLE_VALUE;
   BY_HANDLE_FILE_INFORMATION fi;
   BOOL  result = FALSE;
   LPSTR buffer = 0;
   
   if (!pSrc || !pDst){ SetLastError(ERROR_INVALID_PARAMETER); return FALSE; }
    
   buffer = (LPSTR) _xgrab(OT4XB_COPYFILE_BUFFER_SIZE);
   
   hSrc = CreateFile( pSrc , GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
   if(hSrc == INVALID_HANDLE_VALUE){ goto label_cleanup; }
   if( !GetFileInformationByHandle( hSrc, &fi ) ){ goto label_cleanup; }
   hDst = CreateFile( pDst , GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,0,
                     (bFailIfExist ? CREATE_NEW : CREATE_ALWAYS),fi.dwFileAttributes,0 );
   if(hDst == INVALID_HANDLE_VALUE){ goto label_cleanup;}

   for(;;)
   {
      DWORD n  = 0;
      DWORD nn = 0;          
      BOOL bOk = ReadFile(hSrc,buffer,OT4XB_COPYFILE_BUFFER_SIZE,&nn,0);
      if( !bOk ){ goto label_cleanup; }
      if( !nn )
      {
         result = SetFileTime( hDst ,&(fi.ftCreationTime),&(fi.ftLastAccessTime),&(fi.ftLastWriteTime));      
         goto label_cleanup;
      }
      LPSTR p = buffer;
      for(; nn ; p = _mk_ptr_(LPSTR,p,n) , nn -= n )      
      {
         bOk = WriteFile(hDst,p,nn,&n,0);
         if( !bOk ){ goto label_cleanup; }
      }
   }
   label_cleanup :
   if( buffer )
   {
      _xfree((void*) buffer);
      buffer = 0;
   }  
   if( hSrc != INVALID_HANDLE_VALUE )
   {
      CloseHandle(hSrc);
      hSrc = INVALID_HANDLE_VALUE;
   }
   if( hDst != INVALID_HANDLE_VALUE )
   {
      CloseHandle(hDst);
      hDst = INVALID_HANDLE_VALUE;
   }
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
// lCopyFile( cSrc,cDst,lOverwrite,lReplaceACLWithDestContainer)
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LCOPYFILE( XppParamList pl)
{
   BOOL bResult = FALSE;
   LPSTR pSrc = _pszParam(pl,1);
   if( pSrc )
   {
      LPSTR pDst = _pszParam(pl,2);
      if( pDst )
      {
         BOOL bOver = ( (_partype(pl,3) & XPP_LOGICAL) ? _parl(pl,3) : TRUE );
         if ( _parl(pl,4 ))
         {
            bResult = ot4xb_CopyFile( pSrc,pDst,!bOver );
         }
         else
         {
            bResult = CopyFile( pSrc,pDst,!bOver );
         }
         _xfree((void*) pDst );
      }
      _xfree((void*) pSrc );
   }
   _retl( pl , bResult);
}
//----------------------------------------------------------------------------------------------------------------------
///<xpp_function name="lMakePath">
///<short>Check and try to create all the components of a path</short>
///<proto>lMakePath( cPath ) -&gt; lOk</proto>
///<return>.T. If path exist or created and is directory, .F. if not a directory or cannot create any of the components </return>
///</xpp_function> 
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LMAKEPATH( XppParamList pl)
{
   LPSTR pStr = _pszParam(pl,1);
   BOOL bRet  = FALSE;
   if( pStr != NULL )
   {
      bRet = bCheckAndMakePath(pStr);
      _xfree((void*) pStr);
   }
   _retl(pl,bRet);
}
//----------------------------------------------------------------------------------------------------------------------
// Check the existence of a path or try to create it
// return TRUE if the path is valid and existing or succesfully created
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
OT4XB_API BOOL bCheckAndMakePath(LPSTR _pPath_ )
{
  int nLen = (int) _xstrlen(_pPath_);
  LPSTR pPath = (LPSTR) _xgrab( nLen + 10);
  int n=0;
  int nLevel = 0;
  char ch = 0;
  _xstrcpy(pPath,_pPath_ );

  if( pPath[0] == '\\' )
  {
     if( pPath[1] == '\\' ) // Network Path
     {
        if( pPath[3] != '\\' )
        {
           for(n=2; pPath[n] && pPath[n] != '\\'; n++);
           if( pPath[n] && (pPath[n+1] != '\\') )
           {
              for(n++; pPath[n] && pPath[n] != '\\'; n++);
              if( pPath[n] ){ch=pPath[n]; pPath[n]=0;}
              if( GetFileAttributes(pPath) & FILE_ATTRIBUTE_DIRECTORY ) nLevel = 1;
              if( ch != 0 ) pPath[n] = ch;
              n++;
           }
        }
     }
     else { n=1; nLevel=2; ch=0;}
  }
  else
  {
     if( pPath[1] == ':' )
     {
       if( pPath[2] == '\\' ) // drive root
       {
          if( pPath[3] != '\\' )
          {
             n=3;ch=pPath[3]; pPath[3]=0;
             if( GetFileAttributes(pPath) & FILE_ATTRIBUTE_DIRECTORY ) nLevel = 1;
             pPath[3]=ch;
          }
       }
       else{n=2; nLevel=2;}
     }
     else{n=0; nLevel=2;}
  }

  while( (nLevel > 0) && (n < nLen) )
  {
     DWORD dw;
     ch=0;
     for(; pPath[n] && pPath[n] != '\\'; n++);
     if( pPath[n] ){ch=pPath[n]; pPath[n]=0;}
     dw = GetFileAttributes(pPath);
     if( dw == ((DWORD) -1) )
     {
        if(!CreateDirectory(pPath,NULL)) nLevel = -1;
        else if( !(dw & FILE_ATTRIBUTE_DIRECTORY) )  nLevel = -1;
     }
     if( ch != 0 ) pPath[n] = ch;
     n++;
  }
  _xfree((void*) pPath);
  return (BOOL) (nLevel > 0);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CCREATETMPFILE( XppParamList pl) // cCreateTmpFile(cPath[,cPrefix][,lCreate]) -> cNewFile / NIL if fails
{
   LPSTR pPath = _pszParam(pl,1);
   LPSTR pPref = _pszParam(pl,2);
   LPSTR pOut  = (LPSTR) _xgrab(MAX_PATH + 1);
   BOOL  bOk = FALSE;
   if( !pPath  ){ pPath = (LPSTR) _xgrab(MAX_PATH + 1); GetTempPath(MAX_PATH,pPath);}
   bOk = (BOOL) (GetTempFileName(pPath,(pPref?pPref:"tmp"),(UINT) _parl(pl,3),pOut)!=0);
   if(pPath) _xfree((void*) pPath);
   if(pPref) _xfree((void*) pPref);
   if(bOk) _retc(pl,pOut); else _ret(pl);
   if(pOut) _xfree((void*) pOut);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CGETTMPPATH( XppParamList pl) // cGetTmpPath() -> cTmpPath / NIL if fails
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   GetTempPath(MAX_PATH,pPath);
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY NGETDRIVETYPE( XppParamList pl)
{
   LPSTR pPath = _pszParam(pl,1);
   UINT  nType = DRIVE_NO_ROOT_DIR;
   if( pPath )
   {
      nType = GetDriveType( pPath );
      _xfree((void*) pPath);
   }
   _retnl(pl,(LONG) nType);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LCHDIR(XppParamList pl) // lChDir( <cDir> ) -> lOk
{
   LPSTR pPath = _pszParam(pl,1);
   BOOL  bOk   = FALSE;
   if( pPath )
   {
      bOk = SetCurrentDirectory( pPath);
      _xfree((void*) pPath);
   }
   _retl(pl,bOk);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CDRIVES( XppParamList pl )
{
  DWORD      d        = GetLogicalDrives();
  char       sz[40];
  LPSTR      p        = (LPSTR) sz;
  char ch;
  _bset((LPBYTE)sz,0,40);
  for( ch = 'A' ; ch <= 'Z' ; ch++, d >>= 1 ){ if( d & 1)*p++=ch;}
  _retc(pl,sz);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY ADRIVES( XppParamList pl )
{
   LPSTR pBuffer = (LPSTR) _xgrab(1024);
   ULONG nLen    = (ULONG) GetLogicalDriveStrings(1023,pBuffer);
   ContainerHandle conr = NULLCONTAINER;
   if( nLen > 0 )
   {
      ULONG n = 0;
      TList * pList = new TList;
      while(n < nLen )
      {
         pList->Add( (void*) (pBuffer + n) );
         while(pBuffer[n]) n++;
         n++;
      }
      nLen = (ULONG)pList->Count();
      conr = _conNewArray(1,nLen);
      for( n = 0; n < nLen; n++) _conArrayPutC(conr,(LPSTR)pList->Get(n),n+1,0);
      delete pList;
   }
   _xfree( (void*) pBuffer);
   if( conr == NULLCONTAINER ) _ret(pl);
   else{ _conReturn(pl,conr); _conRelease(conr);}
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CGETSHORTFILENAME( XppParamList pl )
{
   LPSTR pPath = _pszParam(pl,1);
   LPSTR pOut  = (LPSTR) _xgrab( 1024 );
   if( pPath )
   {
      GetShortPathName(pPath,pOut,1023);
      _xfree((void*) pPath);
   }
   _retc(pl,pOut);
   _xfree((void*) pOut);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY _TDRIVEINFO_( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("_TDriveInfo_");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "_TDriveInfo_" );
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->Var("cRoot");
      pc->Var("cLabel");
      pc->Var("nSerial");
      pc->Var("nMaxCompLen");
      pc->Var("cFileSystem");
      pc->Var("nFlags");
      pc->Var("nDriveType");
      // ---------------------------------------------------------------------------------
      pc->MethodCB("init","{|s|s:cRoot := s:cLabel := s:cFileSystem := '',"
                          "s:nSerial := s:nMaxCompLen := s:nFlags := s:nDriveType := 0 }");
      // ---------------------------------------------------------------------------------
      pc->ROPropertyCB("lNamedStreams"        ,"{|s| lAnd(s:nFlags, 0x40000 ) }");
      pc->ROPropertyCB("lReadOnlyVolume"      ,"{|s| lAnd(s:nFlags, 0x80000 ) }");
      pc->ROPropertyCB("lObjectIds"           ,"{|s| lAnd(s:nFlags, 0x10000 ) }");
      pc->ROPropertyCB("lReparsePoints"       ,"{|s| lAnd(s:nFlags, 0x00080 ) }");
      pc->ROPropertyCB("lSupportsSparseFiles" ,"{|s| lAnd(s:nFlags, 0x00040 ) }");
      pc->ROPropertyCB("lVolumeQuotas"        ,"{|s| lAnd(s:nFlags, 0x00020 ) }");
      pc->ROPropertyCB("lCaseIsPreserved"     ,"{|s| lAnd(s:nFlags, 0x00002 ) }");
      pc->ROPropertyCB("lCaseSensitive"       ,"{|s| lAnd(s:nFlags, 0x00001 ) }");
      pc->ROPropertyCB("lFileCompression"     ,"{|s| lAnd(s:nFlags, 0x00010 ) }");
      pc->ROPropertyCB("lFileEncryption"      ,"{|s| lAnd(s:nFlags, 0x20000 ) }");
      pc->ROPropertyCB("lPersistentAcls"      ,"{|s| lAnd(s:nFlags, 0x00008 ) }");
      pc->ROPropertyCB("lUnicodeStoredOnDisk" ,"{|s| lAnd(s:nFlags, 0x00004 ) }");
      pc->ROPropertyCB("lVolIsCompressed"     ,"{|s| lAnd(s:nFlags, 0X08000 ) }");
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   // ---------------------------------------------------------------------------------
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------
DWORD WINAPI lDiskReady_internal(void * lp )
{
      DRTHREAD * p  = (DRTHREAD*) lp;
      char  szv[256];
      char  szf[256];
      DWORD pdw[3];
      BOOL  bRet = GetVolumeInformation((LPSTR)p->pPath,szv,256,&pdw[0],&pdw[1],&pdw[2],szf,256);
      EnterCriticalSection( &_drcs_);
      p->bComplete = TRUE;
      if( p->bTimeOut )
      {
         if( p == _pdrt_) _pdrt_ = (DRTHREAD *) p->pNext;
         if( p->pNext ) ((DRTHREAD *) p->pNext)->pPrev = p->pPrev;
         if( p->pPrev ) ((DRTHREAD *) p->pPrev)->pNext = p->pNext;
         if( p->ht ) CloseHandle(p->ht);
         _xfree( (void * ) p->pPath);
         _xfree( (void * ) p);
      }
      LeaveCriticalSection( &_drcs_);
      return (DWORD)(bRet ? 1 : 0);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LDISKREADY( XppParamList pl ) // -> lReady
{
   ULONG nLen  = _parclen( pl,1,0);
   LPSTR pPath = (LPSTR) _xgrab( nLen + 1);
   DWORD nTimeOut = (DWORD)(_parLong(pl,2) * 1000);
   _parc(pPath,nLen+1,pl,1,0);
   if( !nLen ) nTimeOut = 0;
   if( nTimeOut )
   {
      DWORD dwcrc = dwCrc32(0,(LPBYTE)pPath,nLen + 1);
      DRTHREAD * pp;
      DRTHREAD * p = 0;
      BOOL bTimeOut = FALSE;
      DWORD dwResult    = 0;
      DWORD dwThreadId  = 0;

      EnterCriticalSection( &_drcs_);
      __try
      {

         for( pp = _pdrt_; pp ; pp = (DRTHREAD * ) pp->pNext )
         {
            if( (pp->dwcrc == dwcrc) && ( pp->bTimeOut ) && ( !pp->bComplete ) )
            {
               p = pp;
               goto pp_Found_;
            }
         }
         pp_Found_: ;
      }
      __finally
      {
         LeaveCriticalSection( &_drcs_);
      }
      if( p )
      {
         p = 0;
         SleepEx(nTimeOut,FALSE);
         nTimeOut = 500;
         EnterCriticalSection( &_drcs_);
         __try
         {

            for( pp = _pdrt_; pp ; pp = (DRTHREAD * ) pp->pNext )
            {
               if( (pp->dwcrc == dwcrc) && ( pp->bTimeOut ) && ( !pp->bComplete ) )
               {
                  p = pp;
                  goto pp_Found_2_;
               }
            }
            pp_Found_2_: ;
         }
         __finally
         {
            LeaveCriticalSection( &_drcs_);
         }
         if( p ){ _xfree( (void*) pPath); _storl(TRUE,pl,2,0); _retl(pl,FALSE); return;}
      }
      p = (DRTHREAD*) _xgrab( sizeof(DRTHREAD) );
      p->pPath          = pPath;
      p->dwcrc        = dwcrc;
      p->ht             = CreateThread(0,1, lDiskReady_internal , (void*) p ,0,&dwThreadId);
      bTimeOut          = (BOOL) WaitForSingleObject(p->ht,nTimeOut);
      if( bTimeOut )
      {
         EnterCriticalSection( &_drcs_);
         if( p->bComplete ) bTimeOut = FALSE;
         else
         {
            if( _pdrt_ ){ _pdrt_->pPrev = p; p->pNext = _pdrt_;}
            _pdrt_ = p;
            p->bTimeOut = TRUE;
         }
         LeaveCriticalSection( &_drcs_);
      }
      if( !bTimeOut )
      {
         GetExitCodeThread(p->ht,&dwResult);
         CloseHandle(p->ht);
         _xfree( (void * ) p->pPath);
         _xfree( (void * ) p);
      }
      _storl(bTimeOut,pl,2,0);
      _retl(pl,(BOOL) dwResult);
   }
   else
   {
      char  szv[256];
      char  szf[256];
      DWORD pdw[3];
      BOOL  bRet = GetVolumeInformation(pPath,szv,256,&pdw[0],&pdw[1],&pdw[2],szf,256);
      _xfree((void*)pPath);
      _retl( pl,bRet);
   }
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY GETDRIVEINFO( XppParamList pl ) // -> oInfo
{
   LPSTR pPath = _pszParam(pl,1);
   ContainerHandle conr = NULLCONTAINER;

   if( pPath )
   {
      UINT  nDrType  = GetDriveType( pPath );
      LPSTR pVolName = (LPSTR) _xgrab(260);
      LPSTR pFsName  = (LPSTR) _xgrab(260);
      DWORD dwSerial = 0;
      DWORD dwMaxCl  = 0;
      DWORD dwFlags  = 0;
      BOOL  bOk;
      bOk = GetVolumeInformation(pPath,pVolName,260,&dwSerial,&dwMaxCl,&dwFlags,pFsName,260);

      if( bOk )
      {
         conr = _conNewObj("_TDriveInfo_",NULL);
         _conSetCMember(conr,"cRoot",pPath);
         _conSetCMember(conr,"cLabel",pVolName);
         _conSetNLMember(conr,"nSerial",(LONG) dwSerial);
         _conSetNLMember(conr,"nMaxCompLen",(LONG) dwMaxCl);
         _conSetCMember(conr,"cFileSystem",pFsName);
         _conSetNLMember(conr,"nFlags",(LONG) dwFlags);
         _conSetNLMember(conr,"nDriveType",(LONG) nDrType);
      }
      _xfree((void *) pFsName);
      _xfree((void *) pVolName);
      _xfree((void *) pPath );
   }
   if( conr == NULLCONTAINER ) _ret(pl);
   else{ _conReturn(pl,conr); _conRelease(conr);}
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LISDIR(XppParamList pl) // lIsDir(<cDir>)
{
   TXppParamList xpp(pl,1);
   LPSTR p = xpp[1]->LockStr();
   if( p )
   {
      DWORD dw = GetFileAttributes(p);
      if( dw != INVALID_FILE_ATTRIBUTES )
      { 
         xpp[0]->PutBool( (dw & FILE_ATTRIBUTE_DIRECTORY ) ? 1 : 0 );
         return;
      }
   }
   xpp[0]->PutBool(0);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( LISFILE ) // lIsFile( cFile) 
{
   TXppParamList xpp(pl,1);
   LPSTR p = xpp[1]->LockStr();
   if( p )
   {
      DWORD dw = GetFileAttributes(p);
      if( dw != INVALID_FILE_ATTRIBUTES )
      { 
         xpp[0]->PutBool( (dw & FILE_ATTRIBUTE_DIRECTORY ) ? 0 : 1 );
         return;
      }
   }
   xpp[0]->PutBool(0);   
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY GETWINDIR(XppParamList pl)
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   GetWindowsDirectory(pPath,MAX_PATH);
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY GETSYSDIR(XppParamList pl)
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   GetSystemDirectory(pPath,MAX_PATH);
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHCOMBINE( XppParamList pl ) // cPathCombine( cPathComponent,... ) -> cPath
{
   UINT nParams = (UINT) _partype(pl,0);
   LPSTR pOut = NULL;
   UINT nOutSize = 0;
   if( nParams != 0)
   {
      UINT n;
      TList * pList = new TList;
      for( n=1;n <= nParams; n++)
      {
         LPSTR p = _pszParam(pl,(ULONG) n);
         if(p != NULL )
         {
            pList->Add( (void*) p);
            nOutSize += (5 + _xstrlen(p)) ;
         }
      }
      if( nOutSize != 0 )
      {
         LPSTR pp = NULL;
         pOut = (LPSTR) _xgrab( nOutSize + 1 );
         nParams = pList->Count();
         pp = pOut;
         for(n=0; n < nParams; n++)
         {
            LPSTR pItem = (LPSTR) pList->Get(n);
            LPSTR p = pItem;
            while( pItem[0] == 32) pItem++;
            while( p[0] )
            {
               if( p[0] == '/')
               {
                  p[0] = '\\';
               }            
               p++;
            }
            for( p--; (p > pItem)&&(p[0]==32); p--){p[0] = 0;}
            if( pp > pOut )
            {
               if( (pp-1)[0] =='\\'){ if(pItem[0] =='\\') pItem++; }
               else { if(pItem[0] != '\\'){pp[0]='\\';pp++;} }
            }
            pp = _xxstrcpy(pp, pItem);
         }
      }
      nParams = pList->Count();
      for(n=0; n < nParams; n++){ _xfree( pList->Get(n) ); }
      delete pList;
   }
   if( pOut == NULL ) { _retc(pl,""); }
   else { _retc(pl,pOut); _xfree( (void*) pOut); }
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CURLCOMBINE( XppParamList pl ) // cUrlCombine( cPathComponent,... ) -> cPath
{
   UINT nParams = (UINT) _partype(pl,0);
   LPSTR pOut = NULL;
   UINT nOutSize = 0;
   if( nParams != 0)
   {
      UINT n;
      TList * pList = new TList;
      for( n=1;n <= nParams; n++)
      {
         LPSTR p = _pszParam(pl,(ULONG) n);
         if(p != NULL )
         {
            pList->Add( (void*) p);
            nOutSize += (5 + _xstrlen(p)) ;
         }
      }
      if( nOutSize != 0 )
      {
         LPSTR pp = NULL;
         pOut = (LPSTR) _xgrab( nOutSize + 1 );
         nParams = pList->Count();
         pp = pOut;
         
         for(n=0; n < nParams; n++)
         {
            LPSTR pItem = (LPSTR) pList->Get(n);
            LPSTR p = pItem;
            while( pItem[0] == 32) pItem++;
            while( p[0] )
            {
               if( p[0] == '\\')
               {
                  p[0] = '/';
               }
               p++;
            }
            for( p--; (p > pItem)&&(p[0]==32); p--){p[0] = 0;}
            if( pp > pOut )
            {
               if( (pp-1)[0] =='/'){ if(pItem[0] =='/') pItem++; }
               else { if(pItem[0] != '/'){pp[0]='/';pp++;} }
            }
            pp = _xxstrcpy(pp, pItem);
         }
      }
      nParams = pList->Count();
      for(n=0; n < nParams; n++){ _xfree( pList->Get(n) ); }
      delete pList;
   }
   if( pOut == NULL ) { _retc(pl,""); }
   else { _retc(pl,pOut); _xfree( (void*) pOut); }
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHDEFEXT( XppParamList pl) // cPathDefExt( cPath , cDefaultExt )
{
   ULONG nExtSize  = _parclen(pl,2,0);
   ULONG nPathSize = ( _parclen(pl,1,0) + nExtSize + 5 );
   void* pvPath    = _xgrab(nPathSize);
   LPSTR pPath    = (LPSTR) (((LPSTR) pvPath) + 1);
   LPSTR pp,pLastP,pLastB,pEnd;

   _parc(pPath,nPathSize,pl,1,0);
   for( pp = pPath ,pEnd=pLastP=pLastB=0; pp[0] ; pp++)
   {
      if( pp[0] == '.' ) pLastP = pp;
      else if( pp[0] == '\\' ) pLastB = pp;
      pEnd = pp;
   }
   if(pEnd)
   {
      if( pEnd[0] == '.')
      {
         pLastP = 0;
         while( pEnd[0] == '.' ){ pEnd[0]=0; pEnd--;}
         if( pEnd[0] == '\\' ) pLastB = pEnd;
      }
   }
   if( (pLastP <= pLastB) && (pEnd > pLastB) && nExtSize)
   {
      void * pvExt     = _xgrab(nExtSize + 5);
      LPSTR pExt      = (LPSTR) pvExt;
      _parc(pExt,nExtSize+1,pl,2,0);
      while((pExt[0] == '.')||(pExt[0] == 32)) pExt++;
      if( pExt[0] )
      {
         _xstrcat (pPath,".");
         _xstrcat (pPath,pExt);
      }
      _xfree(pvExt);
   }
   _retc(pl,pPath);
   _xfree(pvPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHBUILDROOT( XppParamList pl) // cPathBuildRoot(cnDrive)
{
   ULONG nType = _partype(pl,1);
   char sz[10];
   _bset((BYTE*)sz,0,10);
   if( nType & XPP_CHARACTER)
   {
      _parc(sz,2,pl,1);
      if( (sz[0] >= 'a') && (sz[0] <= 'z') )sz[0] -= 32;
      if( (sz[0] >= 'A') && (sz[0] <= 'Z') ) _xstrcpy( sz+1 , ":\\");
      else sz[0] = 0;

   }
   else if( nType & XPP_NUMERIC)
   {
      UINT n = (UINT) _parLong(pl,1);
      if( n < 26)
      {
         sz[0] = (char) ('A' + ((char) (n & 0xFF)));
         _xstrcpy( sz+1 , ":\\");
      }
   }
   _retc(pl,sz);
}
//----------------------------------------------------------------------------------------------------------------------
// Split a path string and return a TList filled with pointers to the path thunks
// This function not allocate memory to allocate the path thunks that will be point
// to directly to memory locations within pPath
// pPath will be modified by replacing some bytes with \0s as the stop character
// so you must provide a copy if you need to use  pPath in another places.

OT4XB_API TList * Path2TList( LPSTR pPath ) // C++ only
{
   TList* pList = new TList;
   if( pPath)
   {
      if( pPath[0] == '\\' )
      {
         if( pPath[1] == '\\' ) // Network Path
         {
            pList->Add( (void*) pPath);
            for( pPath += 2; pPath[0] && (pPath[0] != '\\') ; pPath++);
            if( pPath[0])
            {
               for( pPath++; pPath[0] && (pPath[0] != '\\'); pPath++);
            }
            if( pPath[0] ){ pPath[0] = 0; pPath++; }
            while( pPath[0] == '\\'){ pPath[0] = 0; pPath++; }
            pList->Add( (void*) _pStaticBackSlashChar_ );
         }
         else // \root
         {
            pList->Add( (void*) _pStaticBackSlashChar_ );
            pPath++;
         }
      }
      else if( ((pPath[0] >='A')&&(pPath[0] <='Z'))||((pPath[0] >='a')&&(pPath[0] <='z')) )
      {
         if( pPath[1] == ':' )
         {
            if( pPath[2] == '\\' ) // drive root
            {
               pList->Add( (void*) pPath );
               pList->Add( (void*) _pStaticBackSlashChar_ );
               pPath[2] = 0; pPath += 3;
            }
            else
            {
               int ii = (int)( (pPath[0] >= 'a') ? (pPath[0]-'a') : (pPath[0]-'A') );
               pList->Add( (void*) &_pStaticAZDrives_[ii] );
               pPath += 2;
            }
         }
      }
      while( pPath[0] )
      {
         while( pPath[0] == '\\')pPath++;
         if( pPath[0] )
         {
            pList->Add( (void*) pPath);
            for( pPath++; pPath[0] && (pPath[0] != '\\'); pPath++);
            if( pPath[0] ){ pPath[0] = 0; pPath++; }
         }
      }
   }
   return pList;
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY ASPLITPATH( XppParamList pl) // aSplitPath(cPath) -> aPathComponents
{
   UINT nPathSize = _parclen(pl,1,0);
   LPSTR pPath    = (LPSTR) _xgrab( nPathSize + 10);
   TList * pList  = NULL;
   UINT n,nItems,nItem;
   ContainerHandle conr = NULLCONTAINER;
   _parc(pPath, nPathSize +1 , pl,1,0);
   for(n=0;pPath[n];n++){ if(pPath[n] =='/'){pPath[n] ='\\';} }
   pList = Path2TList(pPath);
   nItems = pList->Count();
   n = 0; nItem = 1;
   if( nItems > 1 )
   {
      LPSTR p = (LPSTR) pList->Get(1);
      if( p[0] == '\\' )
      {
         if(p[1] == 0)
         {
            LPSTR pp = (LPSTR) pList->Get(0);
            p = (LPSTR) _xgrab( _xstrlen(pp) + 2 );
            _xstrcpy(p,pp);
            for( pp=p; pp[1] ; pp++);
            if(pp[0] != '\\')pp[1] = '\\';
            nItems--;
            conr = _conNewArray(1,nItems);
            _conArrayPutC(conr,p,1,0);
            _xfree((void*) p);
            n+=2;nItem++;
         }
      }
   }
   if( conr == NULLCONTAINER )
   {
      conr = _conNewArray(1,nItems);
   }
   for( ; nItem <= nItems; n++ , nItem++) _conArrayPutC(conr,(LPSTR)pList->Get(n),nItem,0);
   delete pList;
   _xfree( (void*) pPath );
   _conReturn(pl,conr);
   _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHCANONICALIZE( XppParamList pl) // cPathCanonicalize(cPath)
{
   UINT nPathSize = _parclen(pl,1,0);
   void * pvPath  = _xgrab( nPathSize + 11);
   LPSTR pPath    = (((LPSTR) pvPath) + 1);
   TList * pList  = NULL;
   UINT nItem,n,nItems;
   void * pvOut = _xgrab( nPathSize + 11);
   LPSTR pOut = (((LPSTR) pvOut) + 1);
   BOOL bRoot = FALSE;
   LPSTR p,pp;
   char ch;
   UINT nn;

   pp=pOut;
   _parc(pPath, nPathSize +1 , pl,1,0);
   for(n=0;pPath[n];n++){ if(pPath[n] =='/'){pPath[n] ='\\';} }
   pList = Path2TList(pPath);
   nItems = pList->Count();
   if( nItems != 0 )
   {
      for( nItem=1; nItem < nItems; nItem++) // Root not transformed
      {
         UINT  nDots  = 0;
         p = (LPSTR) pList->Get(nItem);
         for(n=0; p[n] == '.'; n++) nDots++;
         if( nDots > 0 )
         {
            pList->Replace(nItem,(void *) _pStaticZeroChar_ );
            if( nDots > 1 )
            {
               nn = nItem-1;
               while( (nn > 0) ?( ((LPSTR)pList->Get(nn))[0] == 0  ): FALSE) nn--;
               if(nn > 0)
               {
                  if( nn == 1 )
                  {
                     p = (LPSTR) pList->Get(1);
                     if( p[0] == '\\' )
                     {
                        pList->Replace(nn,(void *) _pStaticBackSlashChar_ );
                     }
                     else
                     {
                        pList->Replace(nn,(void *) _pStaticZeroChar_ );
                     }
                  }
                  else
                  {
                     pList->Replace(nn,(void *) _pStaticZeroChar_ );
                  }
               }
            }
         }
      }
      nItem = 0;
      p = (LPSTR) pList->Get(0);
      ch=0;
      for(n=0;p[n];n++){ if(p[n] =='\\'){bRoot = TRUE;} ch = p[n]; }
      pp=_xxstrcpy(pp,p);
      nItem=1;
      if( bRoot ){ if( ch != '\\' ) pp=_xxstrcpy(pp,"\\"); }
      else
      {

         if( nItems > 1 )
         {
            p = (LPSTR) pList->Get(1);
            if( p[0]  == '\\' )
            {
               if( p[1]  == 0 )
               {
                  pp=_xxstrcpy(pp,"\\");
                  nItem++;
               }
            }
         }
      }
      for(ch='\\';nItem < nItems; nItem++)
      {
         p = (LPSTR) pList->Get(nItem);
         while(p[0] =='\\') p++;
         if( p[0] )
         {
            if( ch != '\\' ) pp=_xxstrcpy(pp,"\\");
            pp=_xxstrcpy(pp,p);
            for(ch=0;p[0]; p++) ch=p[0];
         }
      }
   }
   _retc(pl,pOut);
   delete pList;
   _xfree(pvPath);
   _xfree(pvOut);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHGETEXT( XppParamList pl )
{
   LPSTR pPath    = _pszParam(pl,1);
   LPSTR pp,pLastP,pLastB,pEnd;
   if(!pPath){_retc(pl,""); return;}
   for( pp = pPath ,pEnd=pLastP=pLastB=0; pp[0] ; pp++)
   {
      if( pp[0] == '.' ) pLastP = pp;
      else if( pp[0] == '\\' ) pLastB = pp;
      pEnd = pp;
   }
   if(pEnd){if( pEnd[0] == '.') pLastP = 0; }
   if( (pLastP > pLastB) && (pEnd > pLastP) ) _retc(pl,pLastP+1);
   else _retc(pl,"");
   _xfree(pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHREMOVEEXT( XppParamList pl )
{
   LPSTR pPath    = _pszParam(pl,1);
   LPSTR pp,pLastP,pLastB,pEnd;
   if(!pPath){_retc(pl,""); return;}
   for( pp = pPath ,pEnd=pLastP=pLastB=0; pp[0] ; pp++)
   {
      if( pp[0] == '.' ) pLastP = pp;
      else if( pp[0] == '\\' ) pLastB = pp;
      pEnd = pp;
   }
   if(pEnd){if( pEnd[0] == '.') pLastP = 0; }
   if( (pLastP > pLastB) && (pEnd > pLastP) ) pLastP[0] = 0;
   _retc(pl,pPath);
   _xfree(pPath);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CPATHCHANGEEXT( XppParamList pl ) // cPathChangeExt( cPath , cNewExt )
{
   ULONG nExtSize  = _parclen(pl,2,0);
   ULONG nPathSize = ( _parclen(pl,1,0) + nExtSize + 5 );
   void* pvPath    = _xgrab(nPathSize);
   LPSTR pPath    = (LPSTR) (((LPSTR) pvPath) + 1);
   LPSTR pp,pLastP,pLastB,pEnd;


   _parc(pPath,nPathSize,pl,1,0);

   for( pp = pPath ,pEnd=pLastP=pLastB=0; pp[0] ; pp++)
   {
      if( pp[0] == '.' ) pLastP = pp;
      else if( pp[0] == '\\' ) pLastB = pp;
      pEnd = pp;
   }
   if(pEnd)
   {
      if( pEnd[0] == '.')
      {
         pLastP = 0;
         while( pEnd[0] == '.' ){ pEnd[0]=0; pEnd--;}
         if( pEnd[0] == '\\' ) pLastB = pEnd;
      }
   }

   if( pLastP > pLastB){pLastP[0] = 0; pLastP = 0;}

   if( (pLastP <= pLastB) && (pEnd > pLastB) && nExtSize)
   {
      void * pvExt     = _xgrab(nExtSize + 5);
      LPSTR pExt      = (LPSTR) pvExt;
      _parc(pExt,nExtSize+1,pl,2,0);
      while((pExt[0] == '.')||(pExt[0] == 32)) pExt++;
      if( pExt[0] )
      {
         _xstrcat (pPath,".");
         _xstrcat (pPath,pExt);
      }
      _xfree(pvExt);
   }
   _retc(pl,pPath);
   _xfree(pvPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHGETFILENAME( XppParamList pl )
{
   LPSTR pPath    = _pszParam(pl,1);
   LPSTR pp,p;
   if(!pPath){_retc(pl,""); return;}

   for( p= pp = pPath;p[0] ; p++)
   {
      if( (p[0] == ':')||(p[0] == '\\')) pp = p+1;
   }
   _retc(pl,pp);
   _xfree(pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHREMOVEBACKSLASH( XppParamList pl )
{
   LPSTR pPath    = _pszParam(pl,1);
   LPSTR p;
   if(!pPath){_retc(pl,""); return;}
   for(p=pPath;p[0];p++);
   if( p > pPath) p--;
   while( p[0]=='\\'){ p[0]=0; p--;}
   _retc(pl,pPath);
   _xfree(pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHADDBACKSLASH( XppParamList pl )
{
   int nLen = (int) _parclen(pl,1,0);
   LPSTR pPath = (LPSTR) _xgrab( nLen + 5);
   LPSTR p;
   _parc(pPath,nLen+1,pl,1,0);
   for(p=pPath;p[0];p++);
   if( p > pPath) p--;
   while( p[0]=='\\'){ p[0]=0; p--;}
   if(p[0]) p++;
   p[0]='\\';
   _retc(pl,pPath);
   _xfree(pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHGETPATH( XppParamList pl )
{
   LPSTR pPath    = _pszParam(pl,1);
   LPSTR p,pp;

   if(!pPath){_retc(pl,""); return;}
   for(p=pp=pPath;p[0];p++){if((p[0]=='\\')||(p[0]==':')){pp=p;}}
   if( p > pPath) p--;
   if(p[0] != '\\'){if((pp[0]=='\\')||(pp[0]==':')) pp[1]=0;}
   if(pPath[0] )
   {
      for(p=pPath;p[1];p++);
      p--;
      while((p[0]=='\\')&&(p[1]=='\\')){p[1]=0;p--;}
   }
   _retc(pl,pPath);
   _xfree(pPath);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHGETROOT( XppParamList pl )
{
   UINT nPathSize = _parclen(pl,1,0);
   void * pvPath  = _xgrab( nPathSize + 11);
   LPSTR pPath    = (((LPSTR) pvPath) + 1);
   TList * pList  = NULL;
   UINT n,nItems;
   void * pvOut = _xgrab( nPathSize + 11);
   LPSTR pOut = (((LPSTR) pvOut) + 1);
   LPSTR p,pp;

   pp=pOut;
   _parc(pPath, nPathSize +1 , pl,1,0);
   for(n=0;pPath[n];n++){ if(pPath[n] =='/'){pPath[n] ='\\';} }
   pList = Path2TList(pPath);
   nItems = pList->Count();
   if( nItems > 0 )
   {
      p = (LPSTR) pList->Get(0);
      if((p[0] =='\\')&&(p[1] =='\\'))
      {
         pp=_xxstrcpy(pp,p);
         p=pp-1; if( p[0] != '\\') pp=_xxstrcpy(pp,"\\");
      }
      else if((p[1] ==':')&&(((p[0] >='A')&&(p[0] <='Z'))||((p[0] >='a')&&(p[0] <='z'))))
      {
         pp=_xxstrcpy(pp,p);
         if( nItems > 1)
         {
            p = (LPSTR) pList->Get(1);
            if(p[0] =='\\') pp=_xxstrcpy(pp,"\\");
         }
      }
      else if(p[0] =='\\')
      {
         pp=_xxstrcpy(pp,"\\");
      }
   }
   _retc(pl,pOut);
   delete pList;
   _xfree(pvPath);
   _xfree(pvOut);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CPATHREMOVEROOT( XppParamList pl )
{
   UINT nPathSize = _parclen(pl,1,0);
   void * pvPath  = _xgrab( nPathSize + 11);
   LPSTR pPath    = (((LPSTR) pvPath) + 1);
   TList * pList  = NULL;
   UINT n,nItems,nItem;
   void * pvOut = _xgrab( nPathSize + 11);
   LPSTR pOut = (((LPSTR) pvOut) + 1);
   LPSTR p,pp;
   char ch;

   _parc(pPath, nPathSize +1 , pl,1,0);
   for(n=0;pPath[n];n++){ if(pPath[n] =='/'){pPath[n] ='\\';} }
   pList = Path2TList(pPath);
   nItems = pList->Count();
   if( nItems > 0 )
   {
      p = (LPSTR) pList->Get(0);
      if( p[0] )
      {
         if(((p[0] =='\\')&&(p[1] =='\\')) || (p[1] ==':') )
         {
            pList->Replace(0,(void *) _pStaticZeroChar_ );
            if( nItems > 1)
            {
               p = (LPSTR) pList->Get(1);
               if(p[0] =='\\') pList->Replace(1,(void *) _pStaticZeroChar_ );
            }
         }
         else if(p[0] =='\\'){p++; pList->Replace(0,(void *) p );}
      }
      pp=pOut;ch='\\';
      for(nItem=0;nItem < nItems; nItem++)
      {
         p = (LPSTR) pList->Get(nItem);
         while(p[0] =='\\') p++;
         if( p[0] )
         {
            if( ch != '\\' ) pp=_xxstrcpy(pp,"\\");
            pp=_xxstrcpy(pp,p);
            for(ch=0;p[0]; p++) ch=p[0];
         }
      }
   }
   _retc(pl,pOut);
   delete pList;
   _xfree(pvPath);
   _xfree(pvOut);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY LPATHISRELATIVE( XppParamList pl )
{
   char sz[4];
   _bset((BYTE*) sz,0,4);
   _parc(sz,4,pl,1,0);
   _retl( pl , !((sz[0] == '\\')||(sz[1] == ':')) );
}
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_First( TXbClsParams * px );  // ::FindFirst( cMask ) -> lFound
static void FindFiles_Next( TXbClsParams * px );   // ::FindNext() -> lFound
static void FindFiles_Close( TXbClsParams * px );  // FindClose() -> NIL
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY wapist_WIN32_FIND_DATA( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("WIN32_FIND_DATA");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("WIN32_FIND_DATA");
      pc->GwstParent();
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Member_DWord("dwFileAttributes");
      pc->Child("ftCreationTime","FILETIME64");
      pc->Child("ftLastAccessTime","FILETIME64");
      pc->Child("ftLastWriteTime","FILETIME64");
      pc->Member_DWord("nFileSizeHigh");
      pc->Member_DWord("nFileSizeLow");
      pc->Member_DWord("dwReserved0");
      pc->Member_DWord("dwReserved1");
      pc->Member_szStr("cFileName",260);
      pc->Member_szStr("cAlternateFileName",14);
      // ---------------------------
      pc->PropertyCB("nFileSize","{|s,v| iif( PCount() > 1,(s:nFileSizeHigh := hi_dword(v),"
                                 "s:nFileSizeLow  := lo_dword(v)),"
                                 "MAKE_QWORD(s:nFileSizeLow,s:nFileSizeHigh,@v)),Round(v,0)}");
      // ---------------------------
      pc->PropertyCBMask("lArchive",            0x00020 ,"dwFileAttributes");
      pc->PropertyCBMask("lCompressed",         0x00800 ,"dwFileAttributes");
      pc->PropertyCBMask("lDevice",             0x00040 ,"dwFileAttributes");
      pc->PropertyCBMask("lDirectory",          0x00010 ,"dwFileAttributes");
      pc->PropertyCBMask("lEncrypted",          0x04000 ,"dwFileAttributes");
      pc->PropertyCBMask("lHidden",             0x00002 ,"dwFileAttributes");
      pc->PropertyCBMask("lNormal",             0x00080 ,"dwFileAttributes");
      pc->PropertyCBMask("lNotContentIndexed",  0x02000 ,"dwFileAttributes");
      pc->PropertyCBMask("lOffline",            0x01000 ,"dwFileAttributes");
      pc->PropertyCBMask("lReadonly",           0x00001 ,"dwFileAttributes");
      pc->PropertyCBMask("lReparsePoint",       0x00400 ,"dwFileAttributes");
      pc->PropertyCBMask("lSparseFile",         0x00200 ,"dwFileAttributes");
      pc->PropertyCBMask("lSystem",             0x00004 ,"dwFileAttributes");
      pc->PropertyCBMask("lTemporary",          0x00100 ,"dwFileAttributes");
      pc->PropertyCBMask("lVirtual",            0x10000 ,"dwFileAttributes");
      // ---------------------------
      pc->Var( "_find_handle_" );
      // ---------------------------
      pc->Method("FindFirst",FindFiles_First,1,",@s:_find_handle_"); // ::FindFirst( cMask ) -> lFound
      pc->Method("FindNext" ,FindFiles_Next,0,",@s:_find_handle_");  // ::FindNext() -> lFound
      pc->Method("FindClose",FindFiles_Close,0,",@s:_find_handle_"); // FindClose() -> NIL
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_First( TXbClsParams * px )  // ::FindStart( cMask ) -> lFound
{
   if( px->CheckExtraType(1,XPP_NUMERIC) ) FindClose((HANDLE) px->GetExtraLong(1));
   px->PutExtra(1,NULLCONTAINER);
   if( px->CheckParamType(1,XPP_CHARACTER) )
   {
      HANDLE h = FindFirstFile(px->ParamLockStr(1),(WIN32_FIND_DATA*) px->Lock());
      px->ParamUnlockStr(1); px->Unlock();
      if( !( h == INVALID_HANDLE_VALUE ) )
      {
         px->PutExtraLong(1,(LONG) h);
         px->PutReturnBool(TRUE);
         return;
      }
   }
   px->PutReturnBool(FALSE);
}
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_Next( TXbClsParams * px )   // ::FindNext() -> lFound
{
   BOOL bOk = FALSE;
   if( px->CheckExtraType(1,XPP_NUMERIC) )
   {
      bOk = FindNextFile((HANDLE) px->GetExtraLong(1),(WIN32_FIND_DATA*) px->Lock());
      px->Unlock();
   }
   px->PutReturnBool(bOk);
}
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_Close( TXbClsParams * px )  // FindClose() -> NIL
{
   if( px->CheckExtraType(1,XPP_NUMERIC) ) FindClose((HANDLE) px->GetExtraLong(1));
   px->PutExtra(1,NULLCONTAINER);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY CCPUSERIAL( XppParamList pl )
{
   DWORD dw  = 0;
   DWORD dw1 = 0;
   DWORD dw2 = 0;
   DWORD dw3 = 0;
   char sz[32];
   ZeroMemory( sz,32);
   __asm
   {
      mov eax , 1
      cpuid
      mov dw , edx
      mov dw1 , eax
   }
   if(dw & 0x40000)
   {
      __asm
      {
         mov eax , 3
         cpuid
         mov dw2 , edx
         mov dw3 , ecx
      }
      wsprintf(sz,"%04X-%04X-%04X-%04X-%04X-%04X",
                  HIWORD(dw3),LOWORD(dw3),
                  HIWORD(dw2),LOWORD(dw2),
                  HIWORD(dw1),LOWORD(dw1));


   }
   else wsprintf(sz,"%04X",LOWORD(dw1));
   _retc(pl,sz);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( GETPROCCESSARGV )
{
   LPSTR p = ot4xb_pszz_proc_params(0);
   ContainerHandle cona = _conPszz2Array( p );
   _conReturn(pl,cona);
   if( cona ){ _conRelease(cona);}
   if( p ){ _xfree( (void*) p ); }
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR OT4XB_API ot4xb_pszz_proc_params(DWORD* pcb) // TODO:  ot4xb_pszz_proc_params(DWORD* pcb)
{
   LPSTR ps =  GetCommandLine();
   LPSTR pr =  (LPSTR) _xgrab( _xstrlen( ps ) + 64 );
   LPSTR pd =  pr;
   DWORD cb = 0;
   DWORD bc = 0;
   BOOL  q  = FALSE;
   BOOL  z  = FALSE;

   for(; (*ps) && (!(((*ps == 9)||(*ps== 32)) && (!q))) ; ps++ )
   {
      if( *ps == 92 ){ bc++; }
      else if( (*ps == 34) && ((bc & 1) == 0) ){bc = 0; q = !q; }
      else { bc = 0; }
   }
   for(; (*ps == 9) || (*ps== 32) ; ps++ );
   bc = 0; q = 0; z = 0;
   for(; *ps ; ps++ )
   {
      switch(*ps)
      {
         case  9:
         case 32:
         {
            if( q ){ *pd++ = *ps; cb++; }
            else { if(!z){ z=1; *pd++ = 0; cb++;} }
            break;
         }
         case 92:
         {
            z=0; bc++; *pd++ = *ps; cb++;
            break;
         }
         case 34:
         {
            z = 0;
            cb -= (bc >> 1); pd = _mk_ptr_(LPSTR,pr,cb);
            if( bc & 1 ){ *pd++ = 34; cb++; }
            else { q = !q; }
            bc = 0;
            break;
         }
         default: { bc= 0; z=0; *pd++ = *ps; cb++; break;}
      }
   }
   if( !z ){*pd++ = 0; cb++;}
   *pd++ = 0; cb++;
   if( pcb){ *pcb = cb; }
   return pr;
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( OT4XB_PUSHDIR ) // ot4xb_pushdir( [cNewDir] ) -> NIL | lOk if cNewDir provided and directory changed
{
   TXppParamList xpp(pl);
   TList* ls = GetTlsHeapManager()->m_pPushDir;
   DWORD  cc = 1024;
   LPWSTR cd = (LPWSTR) _xgrab( cc * 2 );
   DWORD  rr = GetCurrentDirectoryW(cc,cd);
   if( rr >= cc )
   {
      cc = rr + 1;
      _xfree( (void*) cd);
      cd = (LPWSTR) _xgrab( cc * 2 );      
      rr = GetCurrentDirectoryW(cc,cd);      
   }
   if( ((int) rr ) < 1 ){ _xfree( (void*) cd); return;}
   
   DWORD  ccf = rr + 8;
   LPWSTR cdf = (LPWSTR) _xgrab( ccf * 2 );
   DWORD  rrf = GetFullPathNameW(cd,ccf,cdf,0);
   if( rrf >= ccf )
   {
      ccf = rrf + 1;
      _xfree( (void*) cdf);
      cdf = (LPWSTR) _xgrab( ccf * 2 );      
      rrf = GetFullPathNameW(cd,ccf,cdf,0);      
   }   
   _xfree( (void*) cd); cd = 0;
   if( ((int) rrf ) < 1 ){ _xfree( (void*) cdf); return;}   
   ls->Add( (void*) cdf );
   if( xpp.PCount() > 0 )
   {
      LPSTR p = xpp[1]->StrDup();
      if( p )
      {
         PathRemoveBackslash(p);
         xpp[0]->PutBool( SetCurrentDirectory(p) );
         _xfree((void*) p );
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( OT4XB_POPDIR ) // ot4xb_popdir() // -> lOk | NIL if stack empty
{
   TXppParamList xpp(pl);
   LPWSTR pw = (LPWSTR) GetTlsHeapManager()->m_pPushDir->Pop();
   if( pw )
   {
      xpp[0]->PutBool( SetCurrentDirectoryW(pw) );
      _xfree((void*) pw );
   }
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( OT4XB_CURDIR ) // ot4xb_curdir() -> cCurDir |   ot4xb_curdir(cNewDir) -> lOk
{
   TXppParamList xpp(pl);
   if( xpp.PCount() == 0 )
   {
      DWORD  cc = 1024;
      LPWSTR cd = (LPWSTR) _xgrab( cc * 2 );
      DWORD  rr = GetCurrentDirectoryW(cc,cd);
      if( rr >= cc )
      {
         cc = rr + 1;
         _xfree( (void*) cd);
         cd = (LPWSTR) _xgrab( cc * 2 );      
         rr = GetCurrentDirectoryW(cc,cd);      
      }
      if( ((int) rr ) < 1 ){ _xfree( (void*) cd); return;}
      DWORD  ccf = rr + 8;
      LPWSTR cdf = (LPWSTR) _xgrab( ccf * 2 );
      DWORD  rrf = GetFullPathNameW(cd,ccf,cdf,0);
      if( rrf >= ccf )
      {
         ccf = rrf + 1;
         _xfree( (void*) cdf);
         cdf = (LPWSTR) _xgrab( ccf * 2 );      
         rrf = GetFullPathNameW(cd,ccf,cdf,0);      
      }   
      _xfree( (void*) cd); cd = 0;
      if( ((int) rrf ) < 1 ){ _xfree( (void*) cdf); return;}
      LPSTR pa = w2ansi(cdf);
      _xfree( (void*) cdf); cdf = 0;   
      xpp[0] ->PutStr(pa);
      _xfree( (void*) pa );
      return;
   }
   if( xpp[1]->CheckType( XPP_CHARACTER ) )
   {
      LPSTR  pa =  xpp[1]->LockStr();
      LPWSTR pw = ansi2w(pa);
      xpp[0]->PutBool( SetCurrentDirectoryW(pw) );
      _xfree( pw );
   }
}
// -----------------------------------------------------------------------------------------------------------------
// assuming _xstrlen(pOut) == MAX_PATH // Default dir to GetCurrentDirectory()
OT4XB_API int _PathCombineDefaultDir(LPSTR pOut , LPSTR pFileName , LPSTR pDefaultDir)
{
   int result = 0;
   if( !( pOut && pFileName) ){ return -1; }
   if( !bPathIsAbsolute(pFileName) )
   {
      LPSTR pCurrentFolder = 0;
      char cur_dir[MAX_PATH]; ZeroMemory(cur_dir,sizeof(cur_dir));
      if( !pDefaultDir )
      {
         pCurrentFolder = get_currrent_directory();
         pDefaultDir = pCurrentFolder;
      }
      if( (_xstrlen(pFileName) + _xstrlen(pDefaultDir)) > (MAX_PATH - 4) )
      {
         result = -2;
      }
      ot4xb_path_combine_buffer( pDefaultDir,pFileName, MAX_PATH, pOut );
   }
   else
   {
      _xstrcpy(pOut,pFileName);
   }
   return _xstrlen(pOut);   
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL bPathIsAbsolute(LPSTR pPath )
{
   if( !pPath ){return FALSE; }
   int cb = lstrlen(pPath);
   if( cb < 3 ){return FALSE; }
   if( pPath[1] == ':' )
   {
      return (BOOL) ( (pPath[2] == '\\') ? 1 : 0 );
   }
   if( pPath[1] == '\\' )   
   {   
      return (BOOL) ( (pPath[0] == '\\') ? 1 : 0 );   
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR get_currrent_directory(void)
{
   DWORD  cc = 1024;
   LPWSTR cd = (LPWSTR) _xgrab( cc * 2 );
   DWORD  rr = GetCurrentDirectoryW(cc,cd);
   if( rr >= cc )
   {
      cc = rr + 1;
      _xfree( (void*) cd);
      cd = (LPWSTR) _xgrab( cc * 2 );      
      rr = GetCurrentDirectoryW(cc,cd);      
   }
   if( ((int) rr ) < 1 ){ _xfree( (void*) cd); return 0;}
   DWORD  ccf = rr + 8;
   LPWSTR cdf = (LPWSTR) _xgrab( ccf * 2 );
   DWORD  rrf = GetFullPathNameW(cd,ccf,cdf,0);
   if( rrf >= ccf )
   {
      ccf = rrf + 1;
      _xfree( (void*) cdf);
      cdf = (LPWSTR) _xgrab( ccf * 2 );      
      rrf = GetFullPathNameW(cd,ccf,cdf,0);      
   }   
   _xfree( (void*) cd); cd = 0;
   if( ((int) rrf ) < 1 ){ _xfree( (void*) cdf); return 0;}
   LPSTR pa = w2ansi(cdf,-1,0);
   _xfree( (void*) cdf); cdf = 0;   
   return pa;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL set_currrent_directory(LPSTR pa )
{
   LPWSTR pw = ansi2w(pa,-1,0);
   BOOL result = SetCurrentDirectoryW(pw);
   _xfree( (void*) pw );
   return result;
}



// -----------------------------------------------------------------------------------------------------------------
// cargo -> { ContainerHandle codeblock , Containerhandle cargo , Containerhandle result }
OT4XB_API int  __cdecl ot4xb_recurse_dir_item_codeblock( WIN32_FIND_DATA* pfd , LPSTR pPath , DWORD cargo )
{
   ContainerHandle* pcon = (ContainerHandle*) cargo;
   ContainerHandle  conPath = _conPutC(NULLCONTAINER, pPath);
   ContainerHandle  conFd   = _conPutNL(NULLCONTAINER, (LONG) pfd);
   _conEvalB(pcon[2],pcon[0],3,pcon[1],conPath,conFd);
   _conRelease(conPath);
   _conRelease(conFd);  
   LONG result = 0;
   _conGetLong(pcon[2], &result );
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int ot4xb_recurse_dir(LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo)
{
	return ot4xb_recurse_dir_ex(folder,mask,pfn_new_item,cargo,0);
}
// -----------------------------------------------------------------------------------------------------------------
// 0 old behavior 
// 0x00001 new behavior
// 0x10001 // accept mask list separated with , or ;
// 0x00004 include system files
// 0x00002 include hidden Files 


OT4XB_API int ot4xb_recurse_dir_ex(LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo, DWORD flags )
{
   int bCancel = 0;
   DWORD nPos;
	LPSTR mask_buffer = 0;
	TList* mask_list =  0;
   TList* item_list  = new TList;
   item_list->m_nGrowBy = 1024;

	if( mask && ( flags & 1) && ( flags & 0x10000 ) )
	{
		LPSTR p =  mask_buffer = _xstrdup(mask);
		mask_list = new TList;
		mask_list->Add(p);
		for (; p[0]; p++)
		{
			if ((p[0] == ',') || (p[0] == ';'))
			{
				p[0] = 0;
				if (p[1])
				{
					mask_list->Add(p+1);
				}
			}
		}
	}
   
   
   
   if( folder && mask )
   {
      char sz[1024]; 
      char sz2[sizeof(sz)]; 
		int cb;
		ZeroMemory(sz2, sizeof(sz));
		ZeroMemory(sz, sizeof(sz));
      ot4xb_path_combine_buffer(folder,( flags & 1 ? "*.*" : mask ) ,1024,sz2);
      cb =  _PathCombineDefaultDir(sz,sz2,0);
      if( cb > 0 )
      {
         sz[cb] = 0;
         LPSTR p = (LPSTR) _xgrab(sizeof(sz));         
         PathCanonicalize(p,sz);
         item_list->Add((void*) p);          
      }
   }
   for( nPos = 0; nPos < item_list->Count(); nPos++ )
   {
      LPSTR pMask = (LPSTR) item_list->Replace(nPos,0);
      if( pMask && !bCancel )
      {
         WIN32_FIND_DATA fd;
         HANDLE hFind  =  FindFirstFile( pMask , &fd);         
         char szPath[1024]; ZeroMemory( szPath , sizeof( szPath) );
         _xstrcpy(szPath,pMask);
         PathRemoveFileSpec(szPath);
         if( hFind != INVALID_HANDLE_VALUE )
         {
				do
				{
					BOOL bMatch = TRUE;
					if (bMatch && (fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && !(flags & 0x04)) 
					{
						bMatch = FALSE; 
					}
					if (bMatch && (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !(flags & 0x02)) 
					{
						bMatch = FALSE; 
					}

					if( bMatch && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) ) 
					{ 
						bMatch = FALSE; 
						if( lstrcmp(fd.cFileName, ".") &&  lstrcmp(fd.cFileName, "..") )
						{

							char szfqfn[1024]; ZeroMemory(szfqfn, sizeof(szfqfn));
							PathCombine(szfqfn, szPath, fd.cFileName);
							ot4xb_path_combine_buffer(szPath, fd.cFileName, 1024, szfqfn);
							LPSTR p = (LPSTR)_xgrab(1024);
							ot4xb_path_combine_buffer(szfqfn, (flags & 1 ? "*.*" : mask), 1024, p);
							item_list->Add((void*)p);
						}
						bMatch = FALSE;
					}
					
					if( bMatch && (flags & 1) )
					{
						if (mask_list)
						{
							if (!bAnyStrWildCmpI(mask_list, fd.cFileName))
							{
								bMatch = FALSE;
							}
						}
						else
						{
							if (!bStrWildCmpI(mask, fd.cFileName))
							{
								bMatch = FALSE;
							}
						}

					}
               if( bMatch )
               {
                  
						bCancel = (*pfn_new_item)(&fd,szPath,cargo);


               }
            } while( bCancel ? 0 : FindNextFile( hFind , &fd) );
            FindClose( hFind );            
         }
         _xfree( (void*) pMask );
      }
   }
	if (mask_buffer)
	{
		_xfree((void*)mask_buffer);
		mask_buffer = 0;
	}
	if (mask_list)
	{
		delete mask_list;
		mask_list = 0;
	}
	if (item_list)
	{
		delete item_list;
		item_list = 0;
	}
   return bCancel;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR __cdecl ot4xb_path_combine( LPSTR pFolder , LPSTR pFile )
{
   DWORD cbo = ((_xstrlen(pFolder) + _xstrlen(pFile) + 16) | 1023);
   LPSTR pOut =  (LPSTR) _xgrab( cbo + 1);
   ot4xb_path_combine_buffer(pFolder,pFile,cbo,pOut);
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API UINT __cdecl ot4xb_path_combine_buffer( LPSTR pFolder , LPSTR pFile , DWORD cbo , LPSTR pOut )
{
   if(  cbo < (_xstrlen(pFolder) + _xstrlen(pFile) + 2) )
   {
      return 0;
   }
   LPSTR p  = pOut;
   UINT  cb = 0 ;
   char ch = 0;
   while( *pFolder == 32) pFolder++;   
   for( ; *pFolder ; pFolder++ , p++  , cb++)
   {
      ch = *pFolder;
      if( ch == '/'){ ch = '\\'; }
      *p = ( ( ch == '/') ? '\\' : ch );
   }
   if( ch != '\\' )
   {
      *p = '\\'; p++ ; cb ++;
   }
   while( (*pFile == 32) || (*pFile == '\\')) pFile++;
   for( ; *pFile ; pFile++ , p++ , cb++)
   {
      ch = *pFile;
      if( ch == '/'){ ch = '\\'; }
      *p = ( ( ch == '/') ? '\\' : ch );
   }
   pOut[cb] = 0;
   return cb;
}
// -----------------------------------------------------------------------------------------------------------------

