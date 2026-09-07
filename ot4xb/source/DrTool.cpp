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
#pragma warning( disable: 6258 ) // TerminateThread only at process shutdown; ot4xb is not meant to be loaded/unloaded dynamically, so a clean thread teardown is not needed
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
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetCommandLine
            | syntax_: `GetCommandLine()`
            | category: runtime
            | _kw_: command line, arguments, argv, process
   }}*/
/*{{|desc: Returns the raw command line of the current process.

    Returns Character - String returned by the Win32 GetCommandLine() API. }}*/
XPPRET XPPENTRY GETCOMMANDLINE( XppParamList pl ){ _retc(pl, GetCommandLine()); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cAppPath
            | syntax_: `cAppPath()`
            | category: filesystem
            | _kw_: exe path, application directory, executable folder, program path
   }}*/
/*{{|desc: Returns the directory path of the running executable, including the trailing backslash.

    Returns Character - Executable directory including the trailing path separator. }}*/
XPPRET XPPENTRY CAPPPATH( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_+1);}
/*{{end-function}}*/
// ---------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cAppDir
            | syntax_: `cAppDir()`
            | category: filesystem
            | _kw_: exe directory, application directory, executable folder, program path
   }}*/
/*{{|desc: Returns the directory path of the running executable without the trailing backslash.

    Returns Character - Executable directory without the trailing path separator. }}*/
XPPRET XPPENTRY CAPPDIR( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_);}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// like CopyFile() but using the ACLs of the destination folder
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
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lCopyFile
            | syntax_: `lCopyFile( cSource, cTarget [, lOverwrite := .T.] [, lUseTargetFolderAcl := .F.] )`
            | category: filesystem
            | _kw_: copy file, CopyFile, file copy
   }}*/
/*{{|desc: Copies a file.
    | params:
    - `cSource` Character - Source file name.
    - `cTarget` Character - Target file name.
    - `lOverwrite` Logical - When omitted, defaults to .T. Pass .F. to fail if the target exists.
    - `lUseTargetFolderAcl` Logical - When .T., uses the internal copy routine so the created target
      receives the ACLs inherited from the destination folder.

    Returns Logical - .T. when the copy succeeds; otherwise .F. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
///<xpp_function name="lMakePath">
///<short>Check and try to create all the components of a path</short>
///<proto>lMakePath( cPath ) -&gt; lOk</proto>
///<return>.T. If path exist or created and is directory, .F. if not a directory or cannot create any of the components </return>
///</xpp_function> 
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lMakePath
            | syntax_: `lMakePath( cPath )`
            | category: filesystem
            | _kw_: create directory, mkdir, make path, nested folders, MakeDir
   }}*/
/*{{|desc: Checks that a path exists and creates missing directory components when possible.
    | params:
    - `cPath` Character - Directory path to check or create.

    Returns Logical - .T. when the path exists or was created as a directory; otherwise .F. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bCheckAndMakePath
            | syntax_: `BOOL bCheckAndMakePath( LPSTR _pPath_ )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: bCheckAndMakePath
            | _kw_: create directory, mkdir, make path, nested folders
   }}*/
/*{{|desc: Checks whether a path exists and creates the missing directory levels when it does not. It walks the
      path from the first level below the root (skipping the UNC share, the drive root or the leading backslash)
      and creates every directory that is not there yet with CreateDirectory().
    | params:
    - `_pPath_` LPSTR - Path to check or create. UNC (\\server\share\...), drive (X:\...) and rooted (\...)
      paths are recognized; the root part is not created, only the levels below it.

    Returns BOOL - TRUE when the path already existed or was created successfully; FALSE when a level could
      not be created. }}*/
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cCreateTmpFile
            | syntax_: `cCreateTmpFile( [cPath] [, cPrefix] [, lCreate] )`
            | category: filesystem
            | _kw_: temp file, temporary file, GetTempFileName, unique name
   }}*/
/*{{|desc: Creates or reserves a temporary file name using the Windows temporary-file API.
    | params:
    - `cPath` Character - Optional directory. When omitted, the Windows temporary path is used.
    - `cPrefix` Character - Optional file prefix. Defaults to "tmp".
    - `lCreate` Logical - Passed as the unique number argument to GetTempFileName(); .F. lets Windows
      create a unique name.

    Returns Character/NIL - Temporary file name, or NIL if Windows cannot create one. }}*/
XPPRET XPPENTRY CCREATETMPFILE( XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cGetTmpPath
            | syntax_: `cGetTmpPath()`
            | category: filesystem
            | _kw_: temp path, temporary directory, GetTempPath, TMP
   }}*/
/*{{|desc: Returns the Windows temporary directory path.

    Returns Character - Path returned by GetTempPath(). }}*/
XPPRET XPPENTRY CGETTMPPATH( XppParamList pl)
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   GetTempPath(MAX_PATH,pPath);
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nGetDriveType
            | syntax_: `nGetDriveType( cRoot )`
            | category: filesystem
            | _kw_: drive type, GetDriveType, removable, fixed, cdrom, network drive
   }}*/
/*{{|desc: Returns the Windows drive type for a root path.
    | params:
    - `cRoot` Character - Drive root or volume path.

    Returns Numeric - Drive type returned by GetDriveType(), or DRIVE_NO_ROOT_DIR when no path is supplied. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lChDir
            | syntax_: `lChDir( cDir )`
            | category: filesystem
            | _kw_: change directory, chdir, SetCurrentDirectory, current directory
   }}*/
/*{{|desc: Changes the Win32 current directory.
    | params:
    - `cDir` Character - Directory to set as current.

    Returns Logical - .T. when SetCurrentDirectory() succeeds; otherwise .F.

    |note: The Win32 current directory belongs to the process and may affect other threads. }}*/
XPPRET XPPENTRY LCHDIR(XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cDrives
            | syntax_: `cDrives()`
            | category: filesystem
            | _kw_: drive letters, logical drives, GetLogicalDrives
   }}*/
/*{{|desc: Returns the available drive letters as a compact character string.

    Returns Character - String containing one letter per available logical drive, for example "CZ". }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: aDrives
            | syntax_: `aDrives()`
            | category: filesystem
            | _kw_: drive roots, logical drives, GetLogicalDriveStrings, drive list
   }}*/
/*{{|desc: Returns the available logical drive roots as an array.

    Returns Array/NIL - Array of drive roots such as "C:\"; NIL if Windows returns no drive strings. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cGetShortFileName
            | syntax_: `cGetShortFileName( cPath )`
            | category: filesystem
            | _kw_: short name, 8.3, GetShortPathName, dos name
   }}*/
/*{{|desc: Returns the short 8.3 path name for a file path when Windows can provide one.
    | params:
    - `cPath` Character - Path to convert.

    Returns Character - Short path returned by GetShortPathName(), or an empty string when no path is supplied
      or conversion fails. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: _TDriveInfo_
            | _slug_: tdriveinfo
            | category: filesystem
            | desc: Data container used by GetDriveInfo() to return Windows volume information.
            | note: The object stores the raw volume flags in ::nFlags. The read-only logical properties simply test
              ::nFlags against their corresponding Windows flag mask.
   | _kw_: volume info, drive info, serial number, volume label, file system
   }}*/
XPPRET XPPENTRY _TDRIVEINFO_( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("_TDriveInfo_");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "_TDriveInfo_" );
      /*{{|:**BEGIN CLASS  _TDriveInfo_** }}*/
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->Var("cRoot"); /*{{|ivar_: - VAR cRoot | type: Character | desc_: Root path used to query the volume. }}*/
      pc->Var("cLabel"); /*{{|ivar_: - VAR cLabel | type: Character | desc_: Volume label. }}*/
      pc->Var("nSerial"); /*{{|ivar_: - VAR nSerial | type: Numeric | desc_: Volume serial number. }}*/
      /*{{|ivar_: - VAR nMaxCompLen | type: Numeric | desc_: Maximum component length reported by Windows. }}*/
      pc->Var("nMaxCompLen");
      pc->Var("cFileSystem"); /*{{|ivar_: - VAR cFileSystem | type: Character | desc_: File system name. }}*/
      pc->Var("nFlags"); /*{{|ivar_: - VAR nFlags | type: Numeric | desc_: Raw file system flags reported by Windows. }}*/
      pc->Var("nDriveType"); /*{{|ivar_: - VAR nDriveType | type: Numeric | desc_: Drive type returned by GetDriveType(). }}*/
      // ---------------------------------------------------------------------------------
      /*{{|method_: - `METHOD new()`
               | return: oDriveInfo
               | desc_: Creates the object with all members reset to empty values.
      }}*/
      pc->MethodCB("init","{|s|s:cRoot := s:cLabel := s:cFileSystem := '',"
                          "s:nSerial := s:nMaxCompLen := s:nFlags := s:nDriveType := 0 }");
      // ---------------------------------------------------------------------------------
      /*{{|property_: - PROPERTY lNamedStreams | desc_: Logical  READONLY  ( ::nFlags & 0x40000  ) }}*/
      pc->ROPropertyCB("lNamedStreams"        ,"{|s| lAnd(s:nFlags, 0x40000 ) }");
      /*{{|property_: - PROPERTY lReadOnlyVolume | desc_: Logical  READONLY  ( ::nFlags & 0x80000  ) }}*/
      pc->ROPropertyCB("lReadOnlyVolume"      ,"{|s| lAnd(s:nFlags, 0x80000 ) }");
      /*{{|property_: - PROPERTY lObjectIds | desc_: Logical  READONLY  ( ::nFlags & 0x10000  ) }}*/
      pc->ROPropertyCB("lObjectIds"           ,"{|s| lAnd(s:nFlags, 0x10000 ) }");
      /*{{|property_: - PROPERTY lReparsePoints | desc_: Logical  READONLY  ( ::nFlags & 0x00080  ) }}*/
      pc->ROPropertyCB("lReparsePoints"       ,"{|s| lAnd(s:nFlags, 0x00080 ) }");
      /*{{|property_: - PROPERTY lSupportsSparseFiles | desc_: Logical  READONLY  ( ::nFlags & 0x00040  ) }}*/
      pc->ROPropertyCB("lSupportsSparseFiles" ,"{|s| lAnd(s:nFlags, 0x00040 ) }");
      /*{{|property_: - PROPERTY lVolumeQuotas | desc_: Logical  READONLY  ( ::nFlags & 0x00020  ) }}*/
      pc->ROPropertyCB("lVolumeQuotas"        ,"{|s| lAnd(s:nFlags, 0x00020 ) }");
      /*{{|property_: - PROPERTY lCaseIsPreserved | desc_: Logical  READONLY  ( ::nFlags & 0x00002  ) }}*/
      pc->ROPropertyCB("lCaseIsPreserved"     ,"{|s| lAnd(s:nFlags, 0x00002 ) }");
      /*{{|property_: - PROPERTY lCaseSensitive | desc_: Logical  READONLY  ( ::nFlags & 0x00001  ) }}*/
      pc->ROPropertyCB("lCaseSensitive"       ,"{|s| lAnd(s:nFlags, 0x00001 ) }");
      /*{{|property_: - PROPERTY lFileCompression | desc_: Logical  READONLY  ( ::nFlags & 0x00010  ) }}*/
      pc->ROPropertyCB("lFileCompression"     ,"{|s| lAnd(s:nFlags, 0x00010 ) }");
      /*{{|property_: - PROPERTY lFileEncryption | desc_: Logical  READONLY  ( ::nFlags & 0x20000  ) }}*/
      pc->ROPropertyCB("lFileEncryption"      ,"{|s| lAnd(s:nFlags, 0x20000 ) }");
      /*{{|property_: - PROPERTY lPersistentAcls | desc_: Logical  READONLY  ( ::nFlags & 0x00008  ) }}*/
      pc->ROPropertyCB("lPersistentAcls"      ,"{|s| lAnd(s:nFlags, 0x00008 ) }");
      /*{{|property_: - PROPERTY lUnicodeStoredOnDisk | desc_: Logical  READONLY  ( ::nFlags & 0x00004  ) }}*/
      pc->ROPropertyCB("lUnicodeStoredOnDisk" ,"{|s| lAnd(s:nFlags, 0x00004 ) }");
      /*{{|property_: - PROPERTY lVolIsCompressed | desc_: Logical  READONLY  ( ::nFlags & 0x08000  ) }}*/
      pc->ROPropertyCB("lVolIsCompressed"     ,"{|s| lAnd(s:nFlags, 0X08000 ) }");
      /*{{|:**END CLASS** }}*/
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   // ---------------------------------------------------------------------------------
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
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
/*{{begin-function}}*/
/*{{function_: lDiskReady
            | syntax_: `lDiskReady( cPath [, @nTimeoutSeconds] )`
            | category: filesystem
            | _kw_: drive ready, disk ready, volume, removable media
   }}*/
/*{{|desc: Checks whether a drive or volume path can return volume information.
    | params:
    - `cPath` Character - Drive root or volume path to test.
    - `nTimeoutSeconds` Numeric by reference - Optional timeout in seconds. This parameter changes the
      execution logic: when supplied with a value greater than zero, the check is performed in a helper thread
      instead of calling GetVolumeInformation() directly in the caller thread. On return the same parameter is
      overwritten with a logical value: .T. when the helper thread did not complete before the timeout, .F. when
      it completed in time.

    Returns Logical - .T. when GetVolumeInformation() succeeds for the path; otherwise .F. A timeout also
      returns .F. and sets the second parameter to .T.

    |note: Without a positive timeout the function calls GetVolumeInformation() directly. With a positive
      timeout it starts a helper thread and waits for the requested number of seconds. If the check is still
      pending, the helper thread is left to finish later and the function returns immediately with the timeout
      flag set.

    |note: This helper is useful for slow, removable or network drives where a direct volume query may block
      longer than the application wants to wait. }}*/
XPPRET XPPENTRY LDISKREADY( XppParamList pl )
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
      if( p->ht != NULL )
      {
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
         _xfree( (void*) pPath );
         _xfree( (void*) p ); // CreateThread failed: the DRTHREAD block is orphaned
         p = 0;
         _storl(TRUE,pl,2,0);
         _retl(pl,FALSE);
      }
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetDriveInfo
            | syntax_: `GetDriveInfo( cRoot )`
            | category: filesystem
            | _kw_: volume info, drive info, serial number, volume label, GetVolumeInformation
   }}*/
/*{{|desc: Returns volume information for a drive or root path as a _TDriveInfo_ object.
    | params:
    - `cRoot` Character - Drive root or path passed to the Windows volume query.

    Returns _TDriveInfo_/NIL - A _TDriveInfo_ data object when Windows returns volume information; otherwise
      NIL. }}*/
XPPRET XPPENTRY GETDRIVEINFO( XppParamList pl )
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsDir
            | syntax_: `lIsDir( cDir )`
            | category: filesystem
            | _kw_: is directory, folder exists, directory exists, path test
   }}*/
/*{{|desc: Checks whether a path exists and is a directory.
    | params:
    - `cDir` Character - Path to test.

    Returns Logical - .T. when GetFileAttributes() succeeds and FILE_ATTRIBUTE_DIRECTORY is set; otherwise .F. }}*/
XPPRET XPPENTRY LISDIR(XppParamList pl)
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsFile
            | syntax_: `lIsFile( cFile )`
            | category: filesystem
            | _kw_: file exists, is file, path test
   }}*/
/*{{|desc: Checks whether a path exists and is not a directory.
    | params:
    - `cFile` Character - Path to test.

    Returns Logical - .T. when GetFileAttributes() succeeds and FILE_ATTRIBUTE_DIRECTORY is not set; otherwise
      .F. }}*/
_XPP_REG_FUN_( LISFILE )
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetWinDir
            | syntax_: `GetWinDir()`
            | category: filesystem
            | _kw_: windows directory, GetWindowsDirectory, system folder
   }}*/
/*{{|desc: Returns the Windows directory.

    Returns Character - Path returned by GetWindowsDirectory(). }}*/
XPPRET XPPENTRY GETWINDIR(XppParamList pl)
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   DWORD dw = GetWindowsDirectory( pPath, MAX_PATH );
   if( dw == 0 || dw > MAX_PATH ) { pPath[0] = 0; }
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetSysDir
            | syntax_: `GetSysDir()`
            | category: filesystem
            | _kw_: system32, system directory, GetSystemDirectory
   }}*/
/*{{|desc: Returns the Windows system directory.

    Returns Character - Path returned by GetSystemDirectory(). }}*/
XPPRET XPPENTRY GETSYSDIR(XppParamList pl)
{
   LPSTR pPath = (LPSTR) _xgrab(MAX_PATH + 1);
   GetSystemDirectory(pPath,MAX_PATH);
   _retc(pl,pPath);
   _xfree((void*) pPath);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathCombine
            | syntax_: `cPathCombine( cPart1 [, cPartN...] )`
            | category: filesystem
            | _kw_: path join, combine path, backslash, PathCombine
   }}*/
/*{{|desc: Combines path components using backslash separators.
    | params:
    - `cPartN` Character - Path component. Non-character parameters are ignored.

    Returns Character - Combined path, or an empty string when no character components are supplied.

    |note: Forward slashes in components are converted to backslashes. Leading and trailing spaces are trimmed
      from each component. }}*/
XPPRET XPPENTRY CPATHCOMBINE( XppParamList pl )
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cUrlCombine
            | syntax_: `cUrlCombine( cPart1 [, cPartN...] )`
            | category: filesystem
            | _kw_: url join, combine url, slash, path
   }}*/
/*{{|desc: Combines URL or path components using slash separators.
    | params:
    - `cPartN` Character - URL component. Non-character parameters are ignored.

    Returns Character - Combined URL/path, or an empty string when no character components are supplied.

    |note: Backslashes in components are converted to slashes. Leading and trailing spaces are trimmed from
      each component. }}*/
XPPRET XPPENTRY CURLCOMBINE( XppParamList pl )
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathDefExt
            | syntax_: `cPathDefExt( cPath, cDefaultExt )`
            | category: filesystem
            | _kw_: default extension, add extension, PathAddExtension
   }}*/
/*{{|desc: Adds a default extension to a path when the file name has no extension.
    | params:
    - `cPath` Character - Path to inspect.
    - `cDefaultExt` Character - Extension to add. Leading dots and spaces are ignored.

    Returns Character - Path with the default extension added when applicable. }}*/
XPPRET XPPENTRY CPATHDEFEXT( XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathBuildRoot
            | syntax_: `cPathBuildRoot( cDrive | nDrive )`
            | category: filesystem
            | _kw_: drive root, PathBuildRoot, drive letter
   }}*/
/*{{|desc: Builds a drive root string.
    | params:
    - ``cDrive | nDrive`` Character/Numeric - Drive letter, or zero-based drive number where 0 is A.

    Returns Character - Drive root such as "C:\", or an empty string for invalid input. }}*/
XPPRET XPPENTRY CPATHBUILDROOT( XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Split a path string and return a TList filled with pointers to the path thunks
// This function not allocate memory to allocate the path thunks that will be point
// to directly to memory locations within pPath
// pPath will be modified by replacing some bytes with \0s as the stop character
// so you must provide a copy if you need to use  pPath in another places.
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: Path2TList(LPSTR)
            | _tg_: Path2TList
            | syntax_: `TList * Path2TList( LPSTR pPath )`
            | category: filesystem
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?Path2TList@@YAPAVTList@@PAD@Z
            | _kw_: split path, path components, TList, UNC, drive root
   }}*/
/*{{|desc: Splits a path into its components and returns them as a new TList: the root part first (UNC
      \\server\share, drive root X:\, the drive letter, or a leading backslash) and then each folder and the
      final name, in order.
    | params:
    - `pPath` LPSTR - Path to split. The buffer is modified in place: a null terminator is written after
      each component, and the list stores pointers into this buffer, so pPath must stay alive while the list is
      used.

    Returns TList * - New list with the components; the caller owns it and must delete it. Never NIL: an empty
      or NULL path yields an empty list.

    |note: C++ only, not exported to Xbase++. }}*/
OT4XB_API TList * Path2TList( LPSTR pPath )
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
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: aSplitPath
            | syntax_: `aSplitPath( cPath )`
            | category: filesystem
            | _kw_: split path, path components, directories, array
   }}*/
/*{{|desc: Splits a path into root and component parts.
    | params:
    - `cPath` Character - Path to split.

    Returns Array - Array of path components. Root components such as drive roots or UNC roots are preserved.

    |note: Forward slashes are converted to backslashes before splitting. }}*/
XPPRET XPPENTRY ASPLITPATH( XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathCanonicalize
            | syntax_: `cPathCanonicalize( cPath )`
            | category: filesystem
            | _kw_: canonical path, normalize path, dot dot, PathCanonicalize
   }}*/
/*{{|desc: Canonicalizes a path by resolving "." and ".." components where possible.
    | params:
    - `cPath` Character - Path to canonicalize.

    Returns Character - Canonicalized path using backslash separators.

    |note: This is an internal path component normalizer; it does not verify that the resulting path exists. }}*/
XPPRET XPPENTRY CPATHCANONICALIZE( XppParamList pl)
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathGetExt
            | syntax_: `cPathGetExt( cPath )`
            | category: filesystem
            | _kw_: file extension, extension, PathFindExtension
   }}*/
/*{{|desc: Returns the extension of the file name part of a path.
    | params:
    - `cPath` Character - Path to inspect.

    Returns Character - Extension without the dot, or an empty string when no extension is found. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathRemoveExt
            | syntax_: `cPathRemoveExt( cPath )`
            | category: filesystem
            | _kw_: remove extension, strip extension, PathRemoveExtension
   }}*/
/*{{|desc: Removes the extension from the file name part of a path.
    | params:
    - `cPath` Character - Path to modify.

    Returns Character - Path without the final file extension. }}*/
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
   if( (pLastP != NULL) && (pLastP > pLastB) && (pEnd > pLastP) ) pLastP[0] = 0;
   _retc(pl,pPath);
   _xfree(pPath);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathChangeExt
            | syntax_: `cPathChangeExt( cPath, cNewExt )`
            | category: filesystem
            | _kw_: change extension, rename extension, PathRenameExtension
   }}*/
/*{{|desc: Replaces or adds the extension of the file name part of a path.
    | params:
    - `cPath` Character - Path to modify.
    - `cNewExt` Character - New extension. Leading dots and spaces are ignored.

    Returns Character - Path with the requested extension. }}*/
XPPRET XPPENTRY CPATHCHANGEEXT( XppParamList pl )
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

   if( (pLastP != NULL) && (pLastP > pLastB)){pLastP[0] = 0; pLastP = 0;}

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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathGetFileName
            | syntax_: `cPathGetFileName( cPath )`
            | category: filesystem
            | _kw_: file name, base name, PathFindFileName, strip directory
   }}*/
/*{{|desc: Returns the file name part of a path.
    | params:
    - `cPath` Character - Path to inspect.

    Returns Character - Text after the last backslash or drive separator. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathRemoveBackSlash
            | syntax_: `cPathRemoveBackSlash( cPath )`
            | category: filesystem
            | _kw_: trailing backslash, remove backslash, PathRemoveBackslash
   }}*/
/*{{|desc: Removes trailing backslashes from a path.
    | params:
    - `cPath` Character - Path to modify.

    Returns Character - Path without trailing backslashes, or an empty string when no path is supplied. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathAddBackSlash
            | syntax_: `cPathAddBackSlash( cPath )`
            | category: filesystem
            | _kw_: trailing backslash, add backslash, PathAddBackslash
   }}*/
/*{{|desc: Ensures that a path ends with one backslash.
    | params:
    - `cPath` Character - Path to modify.

    Returns Character - Path with exactly one trailing backslash. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathGetPath
            | syntax_: `cPathGetPath( cPath )`
            | category: filesystem
            | _kw_: directory part, dirname, PathRemoveFileSpec, folder of file
   }}*/
/*{{|desc: Returns the directory part of a path.
    | params:
    - `cPath` Character - Path to inspect.

    Returns Character - Path up to the last directory separator or drive separator. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathGetRoot
            | syntax_: `cPathGetRoot( cPath )`
            | category: filesystem
            | _kw_: path root, drive, UNC root, PathStripToRoot
   }}*/
/*{{|desc: Returns the root part of a path.
    | params:
    - `cPath` Character - Path to inspect.

    Returns Character - UNC root, drive root, single backslash root, or an empty string when no root is
      present.

    |note: Forward slashes are converted to backslashes before parsing. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPathRemoveRoot
            | syntax_: `cPathRemoveRoot( cPath )`
            | category: filesystem
            | _kw_: remove root, strip drive, relative part
   }}*/
/*{{|desc: Removes the root part of a path.
    | params:
    - `cPath` Character - Path to modify.

    Returns Character - Path without its UNC, drive or leading-backslash root.

    |note: Forward slashes are converted to backslashes before parsing. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lPathIsRelative
            | syntax_: `lPathIsRelative( cPath )`
            | category: filesystem
            | _kw_: relative path, absolute path, PathIsRelative
   }}*/
/*{{|desc: Checks whether a path is relative according to the simple OT4XB path test.
    | params:
    - `cPath` Character - Path to test.

    Returns Logical - .F. when the path starts with "\" or has ":" as the second character; otherwise .T. }}*/
XPPRET XPPENTRY LPATHISRELATIVE( XppParamList pl )
{
   char sz[4];
   _bset((BYTE*) sz,0,4);
   _parc(sz,4,pl,1,0);
   _retl( pl , !((sz[0] == '\\')||(sz[1] == ':')) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_First( TXbClsParams * px );  // ::FindFirst( cMask ) -> lFound
static void FindFiles_Next( TXbClsParams * px );   // ::FindNext() -> lFound
static void FindFiles_Close( TXbClsParams * px );  // FindClose() -> NIL
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WIN32_FIND_DATA
            | _slug_: win32_find_data
            | class-function: WIN32_FIND_DATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: filesystem
            | desc: OT4XB structure class that exposes the Windows WIN32_FIND_DATA structure and provides a small
            | _kw_: FindFirstFile, FindNextFile, directory listing, file search, file attributes, wildcard
              FindFirst/FindNext/FindClose search helper. }}*/
           
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
      /*{{|:**BEGIN STRUCTURE  WIN32_FIND_DATA** }}*/
      /*{{|member_: - MEMBER DWORD dwFileAttributes | desc_: Raw Windows file attribute flags. }}*/
      pc->Member_DWord("dwFileAttributes");
      /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftCreationTime | desc_: Creation time. }}*/
      pc->Child("ftCreationTime","FILETIME64");
      /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftLastAccessTime
               | desc_: Last access time.
      }}*/
      pc->Child("ftLastAccessTime","FILETIME64");
      /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftLastWriteTime | desc_: Last write time. }}*/
      pc->Child("ftLastWriteTime","FILETIME64");
      /*{{|member_: - MEMBER DWORD nFileSizeHigh | desc_: High DWORD of the file size. }}*/
      pc->Member_DWord("nFileSizeHigh");
      /*{{|member_: - MEMBER DWORD nFileSizeLow | desc_: Low DWORD of the file size. }}*/
      pc->Member_DWord("nFileSizeLow");
      /*{{|member_: - MEMBER DWORD dwReserved0 | desc_: Windows reserved field. }}*/
      pc->Member_DWord("dwReserved0");
      /*{{|member_: - MEMBER DWORD dwReserved1 | desc_: Windows reserved field. }}*/
      pc->Member_DWord("dwReserved1");
      /*{{|member_: - MEMBER CHAR[260] cFileName | desc_: Primary file name. }}*/
      pc->Member_szStr("cFileName",260);
      /*{{|member_: - MEMBER CHAR[14] cAlternateFileName | desc_: Alternate 8.3 file name, when available. }}*/
      pc->Member_szStr("cAlternateFileName",14);
      // ---------------------------
      
      /*{{|property_: - PROPERTY nFileSize
               | type: Numeric
               | desc_: Combined file size mapped to ::nFileSizeHigh and ::nFileSizeLow. Since Xbase++ numeric values are
                 internally signed integers or doubles, large values are returned as double when needed.
               | note: Assigning a value splits it into ::nFileSizeHigh and ::nFileSizeLow; reading composes them with
                 MAKE_QWORD(), which keeps large values from showing up negative and represents bigger sizes as far as a
                 double allows, and Round() strips the decimal residue so the value prints without decimals.
      }}*/
      pc->PropertyCB("nFileSize","{|s,v| iif( PCount() > 1,(s:nFileSizeHigh := hi_dword(v),"
                                 "s:nFileSizeLow  := lo_dword(v)),"
                                 "MAKE_QWORD(s:nFileSizeLow,s:nFileSizeHigh,@v)),Round(v,0)}");
      // ---------------------------
      /*{{|property_: - PROPERTY lArchive | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE ) }}*/
      pc->PropertyCBMask("lArchive",            0x00020 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lCompressed | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED ) }}*/
      pc->PropertyCBMask("lCompressed",         0x00800 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lDevice | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_DEVICE ) }}*/
      pc->PropertyCBMask("lDevice",             0x00040 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lDirectory | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) }}*/
      pc->PropertyCBMask("lDirectory",          0x00010 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lEncrypted | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED ) }}*/
      pc->PropertyCBMask("lEncrypted",          0x04000 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lHidden | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ) }}*/
      pc->PropertyCBMask("lHidden",             0x00002 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lNormal | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_NORMAL ) }}*/
      pc->PropertyCBMask("lNormal",             0x00080 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lNotContentIndexed | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED ) }}*/
      pc->PropertyCBMask("lNotContentIndexed",  0x02000 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lOffline | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_OFFLINE ) }}*/
      pc->PropertyCBMask("lOffline",            0x01000 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lReadonly | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_READONLY ) }}*/
      pc->PropertyCBMask("lReadonly",           0x00001 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lReparsePoint | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT ) }}*/
      pc->PropertyCBMask("lReparsePoint",       0x00400 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lSparseFile | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE ) }}*/
      pc->PropertyCBMask("lSparseFile",         0x00200 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lSystem | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_SYSTEM ) }}*/
      pc->PropertyCBMask("lSystem",             0x00004 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lTemporary | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY ) }}*/
      pc->PropertyCBMask("lTemporary",          0x00100 ,"dwFileAttributes");
      /*{{|property_: - PROPERTY lVirtual | desc_: Logical  READ-WRITE  ( ::dwFileAttributes & FILE_ATTRIBUTE_VIRTUAL ) }}*/
      pc->PropertyCBMask("lVirtual",            0x10000 ,"dwFileAttributes");
      // ---------------------------
      /*{{|ivar_: - VAR _find_handle_
               | desc_: Search handle returned by ::FindFirst() and kept until ::FindClose(), stored as an Xbase++
                 instance variable outside the WIN32_FIND_DATA structure.
      }}*/
      pc->Var( "_find_handle_" );
      // ---------------------------
      /*{{|method_: - `METHOD FindFirst( cMask )`
               | return: lFound
               | desc_: Starts a search and fills the structure with the first matching entry.
      }}*/
      pc->Method("FindFirst",FindFiles_First,1,",@s:_find_handle_");
      /*{{|method_: - `METHOD FindNext()`
               | return: lFound
               | desc_: Moves to the next matching entry and updates the structure.
      }}*/
      pc->Method("FindNext" ,FindFiles_Next,0,",@s:_find_handle_");
      /*{{|method_: - `METHOD FindClose()` | return: NIL | desc_: Closes the current search handle. }}*/
      pc->Method("FindClose",FindFiles_Close,0,",@s:_find_handle_");
      // ---------------------------
      /*{{|:**END STRUCTURE** }}*/

      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}



/*{{| note: The documented members are the WIN32_FIND_DATA fields. They are filled by ::FindFirst() and
              ::FindNext(). The logical attribute properties map directly to the corresponding bits in
              ::dwFileAttributes. Call ::FindClose() when a search is no longer needed.
            | note: A newly created WIN32_FIND_DATA object can be used directly with ::FindFirst() and ::FindNext(); it
              is not necessary to call ::_alloc_() or ::_link_() first. For normal enumeration, calling ::FindClose() at
              the end is enough.
            | note: Besides implementing the structure, the class adds auxiliary extras: the _find_handle_ instance
              variable that keeps the search handle, the FindFirst/FindNext/FindClose methods, the nFileSize property,
              and the lXxx properties, which read or set single bits of ::dwFileAttributes without lAnd() or nOr().
            | see-also: class GWST
            | example: ```
              PROC Main()
                 LOCAL fd := WIN32_FIND_DATA():New()
                 LOCAL lFound

                 lFound := fd:FindFirst( cPathCombine( cAppPath(), "*.bat" ) )
                 WHILE lFound
                    ? fd:cFileName, " - "
                    ?? fd:ftLastAccessTime:ElapSeconds()
                    lFound := fd:FindNext()
                 ENDDO
                 fd:FindClose()
                 fd := NIL
                 Inkey(0)
              RETURN
              ```
   }}*/






/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
static void FindFiles_First( TXbClsParams * px )  // ::FindFirst( cMask ) -> lFound
{
   if( px->CheckExtraType(1,XPP_NUMERIC) ) FindClose((HANDLE) px->GetExtraLong(1));
   px->PutExtra(1,NULLCONTAINER);
   if( px->CheckParamType(1,XPP_CHARACTER) )
   {
      // GWST Lock() exposes the structure buffer: allocated/attached memory when present,
      // otherwise the locked Xbase++ string backing store.
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
/*{{begin-function}}*/
/*{{function_: cCpuSerial
            | syntax_: `cCpuSerial()`
            | category: system
            | _kw_: cpuid, cpu id, processor id, hardware id, serial
   }}*/
/*{{|desc: Returns a legacy CPU identification string obtained with the x86 CPUID instruction.

    Returns Character - Formatted hexadecimal CPU identification string.

    |note: The function calls CPUID with EAX=1 and checks the Processor Serial Number feature bit in EDX. When
      that bit is present, it calls CPUID with EAX=3 and formats the reported serial data together with the
      EAX=1 value. Otherwise it returns a short hexadecimal string built from the low word of EAX=1.

    |note: This is a legacy helper. It was useful only for the Intel Pentium III Processor Serial Number
      feature. That feature stopped being useful as a CPU serial source when Pentium 4 and later processors no
      longer supported it. On current CPUs the returned value is not a real processor serial number and should
      not be treated as a stable hardware identity. }}*/
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetProccessArgv
            | syntax_: `GetProccessArgv()`
            | category: runtime
            | _kw_: command line, arguments, argv, misspelled alias
   }}*/
/*{{|desc: Historical misspelled name of GetProcessArgv(), kept exported as a duplicate so existing code keeps
      working.

    Returns Array - Same as GetProcessArgv().

    |note: Do not use in new code; use GetProcessArgv(). It is left in place only to avoid breaking existing
      programs. }}*/
_XPP_REG_FUN_( GETPROCCESSARGV ) { GETPROCESSARGV( pl ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetProcessArgv
            | syntax_: `GetProcessArgv()`
            | category: runtime
            | _kw_: command line, arguments, argv, parameters, process
   }}*/
/*{{|desc: Returns the current process command-line arguments as an array.

    Returns Array - Array with the arguments passed after the executable name.

    |note: The function reads the process command line, skips the executable name and parses the remaining text
      into separate arguments. Quoted arguments are kept together and backslash-escaped quotes are handled by
      the internal parser.

    |note: When the program is launched through xppdbg, the first array element may be the program name and the
      user arguments may therefore appear shifted by one position.

    |note: The corrected GetProcessArgv() name is available in ot4xb.dll Version:{1,7,14,0}.

    |example: // Compensate the xppdbg argument shift when wrapping argv-style access. INLINE METHOD argv(n)
      RETURN __aPeek( GetProcessArgv(), n + iif( IsDebug(), 1, 0 ) ) }}*/
_XPP_REG_FUN_( GETPROCESSARGV )
{
   LPSTR p = ot4xb_pszz_proc_params(0);
   ContainerHandle cona = _conPszz2Array( p );
   _conReturn(pl,cona);
   if( cona ){ _conRelease(cona);}
   if( p ){ _xfree( (void*) p ); }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_pszz_proc_params
            | syntax_: `LPSTR ot4xb_pszz_proc_params( DWORD * pcb )`
            | category: runtime
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_pszz_proc_params
            | _kw_: command line, arguments, argv, double zero list, pszz
   }}*/
/*{{|desc: Reads the process command line with GetCommandLine(), skips the executable name (honoring quotes and
      backslash escaping) and returns the remaining arguments as a pszz buffer: each argument as a
      NUL-terminated string, the whole ended by a double NUL.
    | params:
    - `pcb` DWORD * - Optional (may be NULL). When not NULL, receives the number of bytes written to the
      returned buffer, including the terminators.

    Returns LPSTR - New pszz buffer allocated with _xgrab(); the caller frees it with _xfree(). Used by
      GetProcessArgv() together with _conPszz2Array(). }}*/
LPSTR OT4XB_API ot4xb_pszz_proc_params(DWORD* pcb)
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_pushdir
            | syntax_: `ot4xb_pushdir( [cNewDir] )`
            | category: filesystem
            | _kw_: push directory, directory stack, save current directory, pushd
   }}*/
/*{{|desc: Pushes the current directory onto the current thread's directory stack.
    | params:
    - `cNewDir` Character - Optional directory to set after the current directory has been pushed.

    Returns NIL/Logical - NIL when only the current directory is pushed. When cNewDir is supplied, returns .T.
      if the directory change succeeds, otherwise .F.

    |note: The saved directories are stored in a thread-local stack. Each thread has its own push/pop directory
      stack, so a thread only pops entries it pushed itself.

    |note: The stack is thread-local, but the actual directory change uses the Win32 current directory through
      SetCurrentDirectory(). That current directory belongs to the process, so changing it can affect other
      threads. }}*/
_XPP_REG_FUN_( OT4XB_PUSHDIR )
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_popdir
            | syntax_: `ot4xb_popdir()`
            | category: filesystem
            | _kw_: pop directory, directory stack, restore current directory, popd
   }}*/
/*{{|desc: Restores the last directory saved with ot4xb_pushdir() in the current thread.

    Returns Logical/NIL - .T. when the saved directory is restored, .F. when the restore fails, or NIL when
      the current thread's directory stack is empty.

    |note: The stack is thread-local, so ot4xb_popdir() can only restore directories pushed by the same thread.

    |note: The restore operation uses SetCurrentDirectoryW(). The saved stack entry is thread-local, but the
      Win32 current directory being restored belongs to the process and can affect other threads. }}*/
_XPP_REG_FUN_( OT4XB_POPDIR )
{
   TXppParamList xpp(pl);
   LPWSTR pw = (LPWSTR) GetTlsHeapManager()->m_pPushDir->Pop();
   if( pw )
   {
      xpp[0]->PutBool( SetCurrentDirectoryW(pw) );
      _xfree((void*) pw );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_curdir
            | syntax_: `ot4xb_curdir()`
            | category: filesystem
            | _kw_: current directory, GetCurrentDirectory, SetCurrentDirectory, curdir, cwd
   }}*/
/*{{|desc: Gets or sets the current directory.
    | params:
    - `cNewDir` Character - Optional directory to set as the current directory.

    Returns Character/Logical/NIL - Without parameters, returns the current directory as a full path. With
      cNewDir, returns .T. if the directory change succeeds, otherwise .F. Returns NIL when the current
      directory cannot be obtained or the parameter is not character.

    |note: Also ot4xb_curdir( cNewDir ) -> lOk

    |note: This function reads or changes the Win32 current directory directly. It does not push or pop the
      thread-local directory stack used by ot4xb_pushdir() and ot4xb_popdir().

    |note: Unlike the push/pop stack, the current directory changed by SetCurrentDirectoryW() belongs to the
      process, so changing it can affect other threads. }}*/
_XPP_REG_FUN_( OT4XB_CURDIR )
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _PathCombineDefaultDir
            | syntax_: `int _PathCombineDefaultDir( LPSTR pOut, LPSTR pFileName, LPSTR pDefaultDir )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: _PathCombineDefaultDir
            | _kw_: combine path, default directory, absolute, relative path
   }}*/
/*{{|desc: Combines pFileName with a base directory into pOut. When pFileName is absolute it is copied as it
      is; when it is relative it is combined with pDefaultDir, or with the current directory when pDefaultDir is
      NULL.
    | params:
    - `pOut` LPSTR - Output buffer that receives the combined path; it must hold at least MAX_PATH
      characters.
    - `pFileName` LPSTR - File name or path to place under the base directory. If it is absolute it is used
      as it is.
    - `pDefaultDir` LPSTR - Base directory for a relative pFileName; when NULL the current directory
      (get_current_directory()) is used.

    Returns int - -1 when pOut or pFileName is NULL; -2 when the combined path would exceed MAX_PATH;
      otherwise the length of the string written to pOut. }}*/
OT4XB_API int _PathCombineDefaultDir(LPSTR pOut , LPSTR pFileName , LPSTR pDefaultDir)
{
   
   if( !( pOut && pFileName) ){ return -1; }
   if( !bPathIsAbsolute(pFileName) )
   {
      LPSTR pCurrentFolder = 0;
      char cur_dir[MAX_PATH]; ZeroMemory(cur_dir,sizeof(cur_dir));
      if( !pDefaultDir )
      {
         pCurrentFolder = get_current_directory();
         pDefaultDir = pCurrentFolder;
      }
      if( (_xstrlen(pFileName) + _xstrlen(pDefaultDir)) > (MAX_PATH - 4) )
      {
         return  -2;
      }
      ot4xb_path_combine_buffer( pDefaultDir,pFileName, MAX_PATH, pOut );
   }
   else
   {
      _xstrcpy(pOut,pFileName);
   }
   return _xstrlen(pOut);   
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bPathIsAbsolute
            | syntax_: `BOOL bPathIsAbsolute( LPSTR pPath )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: bPathIsAbsolute
            | _kw_: absolute path, UNC, drive path, PathIsRelative
   }}*/
/*{{|desc: Tells whether pPath is an absolute path: a drive path (X:\...) or a UNC path (\\server\...). A
      rooted path without a drive (\folder) or any relative path is not considered absolute.
    | params:
    - `pPath` LPSTR - Path to test. NULL or shorter than 3 characters returns FALSE.

    Returns BOOL - TRUE when pPath is a drive-rooted (X:\) or UNC (\\) absolute path; otherwise FALSE. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: get_current_directory
            | syntax_: `LPSTR get_current_directory( void )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: get_current_directory
            | _kw_: current directory, GetCurrentDirectory, cwd, full path
   }}*/
/*{{|desc: Returns the current directory as a new ANSI string. It reads the directory with
      GetCurrentDirectoryW(), normalizes it to a full path with GetFullPathNameW() and converts the result to
      ANSI.

    Returns LPSTR - New ANSI string allocated internally; the caller frees it with _xfree(). NULL when the
      current directory cannot be obtained. }}*/
OT4XB_API LPSTR get_current_directory( void )
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: get_currrent_directory
            | syntax_: `LPSTR get_currrent_directory( void )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: get_currrent_directory
            | _kw_: current directory, misspelled alias
   }}*/
/*{{|desc: Historical misspelled name (triple r) of get_current_directory(), kept exported as an alias so
      existing external code keeps working.

    Returns LPSTR - Same as get_current_directory(): a new ANSI string the caller frees with _xfree(), or NULL
      on failure.

    |note: Do not use in new code; use get_current_directory(). It only delegates to it and is kept to avoid
      breaking existing programs. }}*/
OT4XB_API LPSTR get_currrent_directory( void )
{
   return get_current_directory();
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: set_current_directory
            | syntax_: `BOOL set_current_directory( LPSTR pa )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: set_current_directory
            | _kw_: change directory, SetCurrentDirectory, chdir, cwd
   }}*/
/*{{|desc: Sets the process current directory from an ANSI path. Converts pa to wide with ansi2w() and calls
      SetCurrentDirectoryW().
    | params:
    - `pa` LPSTR - New current directory (ANSI).

    Returns BOOL - TRUE when SetCurrentDirectoryW() succeeds; otherwise FALSE. }}*/
OT4XB_API BOOL set_current_directory( LPSTR pa )
{
   LPWSTR pw = ansi2w(pa,-1,0);
   BOOL result = SetCurrentDirectoryW(pw);
   _xfree( (void*) pw );
   return result;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: set_currrent_directory
            | syntax_: `BOOL set_currrent_directory( LPSTR pa )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: set_currrent_directory
            | _kw_: change directory, misspelled alias
   }}*/
/*{{|desc: Historical misspelled name (triple r) of set_current_directory(), kept exported as an alias so
      existing external code keeps working.
    | params:
    - `pa` LPSTR - New current directory (ANSI).

    Returns BOOL - Same as set_current_directory().

    |note: Do not use in new code; use set_current_directory(). It only delegates to it and is kept to avoid
      breaking existing programs. }}*/
OT4XB_API BOOL set_currrent_directory( LPSTR pa )
{
   return set_current_directory(pa);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// typedef int ( __cdecl   * _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_)( WIN32_FIND_DATA* , LPSTR , DWORD );
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_recurse_dir_item_codeblock
            | syntax_: `int ot4xb_recurse_dir_item_codeblock( WIN32_FIND_DATA * pfd, LPSTR pPath, DWORD cargo )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_recurse_dir_item_codeblock
            | _kw_: recurse directory, callback, code block, directory walk
   }}*/
/*{{|desc: A ready-made _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ callback that you pass to
      ot4xb_recurse_dir()/ot4xb_recurse_dir_ex() to run an Xbase++ code block for each matching entry. Per entry
      it evaluates the block as `{ |cargo, cPath, pW32FindData| ... }`, which returns 0 = ok (continue) or 1 =
      cancel (stop the walk).
    | params:
    - `pfd` WIN32_FIND_DATA * - Find data of the current entry; passed to the block as pW32FindData, a
      numeric pointer.
    - `pPath` LPSTR - Full path of the current entry; passed to the block as cPath (character).
    - `cargo` DWORD - Pointer to a raw three-int32 array (an __i32 churro) of ContainerHandle pointers:
      offset 0 the code block, offset 4 the cargo (any Xbase++ value), offset 8 the result (starts as NIL).

    Returns int - What the block returned (read from the result container with _conGetLong()): 0 = ok, 1 =
      cancel.

    |example: ```
      // bBlock := { |cargo, cPath, pW32FindData|  ...  0 }        // return 0 = ok, 1 = cancel
      // __i32 builds a plain 3-int32 array, so order the args as [0] code block, [4] cargo, [8] result:
      bin_cargo := __i32( _var2con( codeblock ), _var2con( cargo ), _var2con( result ) )
      // ... run ot4xb_recurse_dir() / ot4xb_recurse_dir_ex() with the callback and bin_cargo ...
      result := _conRelease( PeekDWord( bin_cargo, 8 ) )          // result is at offset 8
      _conRelease( PeekDWord( bin_cargo, 0 ) )                    // free the code block
      _conRelease( PeekDWord( bin_cargo, 4 ) )                    // free the cargo
      ``` }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_recurse_dir
            | syntax_: ```
                 int ot4xb_recurse_dir( LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo )
              ```
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_recurse_dir
            | _kw_: recurse directory, directory walk, find files, mask, tree
   }}*/
/*{{|desc: Walks a directory from folder and calls pfn_new_item for every entry that matches mask. Shorthand
      for ot4xb_recurse_dir_ex() with flags = 0.
    | params:
    - `folder` LPSTR - Root folder to walk.
    - `mask` LPSTR - File mask applied to each entry (for example "*.txt").
    - `pfn_new_item` _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ - Callback invoked for each matching entry as
      pfn_new_item( &WIN32_FIND_DATA, szPath, cargo ); returning 0 continues and non-zero cancels the walk.
    - `cargo` DWORD - Opaque value passed to the callback unchanged.

    Returns int - Same as ot4xb_recurse_dir_ex().

    |seealso: See also: {{ilink: <c-function ot4xb_recurse_dir_ex> ot4xb_recurse_dir_ex}} }}*/
OT4XB_API int ot4xb_recurse_dir(LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo)
{
	return ot4xb_recurse_dir_ex(folder,mask,pfn_new_item,cargo,0);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// 0 old behavior 
// 0x00001 new behavior
// 0x10001 // accept mask list separated with , or ;
// 0x00004 include system files
// 0x00002 include hidden Files 
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_recurse_dir_ex
            | syntax_: ```
                 int ot4xb_recurse_dir_ex( LPSTR folder, LPSTR mask, _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ pfn_new_item, DWORD cargo, DWORD flags )
              ```
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_recurse_dir_ex
            | _kw_: recurse directory, directory walk, find files, mask, tree, flags, subdirectories
   }}*/
/*{{|desc: Recursively walks the directory tree under folder and calls pfn_new_item( &WIN32_FIND_DATA, szPath,
      cargo ) for every file that matches mask. Subdirectories are entered automatically ("." and ".." are
      skipped) and, by default, hidden and system files are skipped. The callback returns 0 to continue or
      non-zero to cancel; the walk stops as soon as it cancels.
    | params:
    - `folder` LPSTR - Root folder to walk.
    - `mask` LPSTR - File mask (for example "*.txt"); see the flags for wildcard and multi-mask handling.
    - `pfn_new_item` _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_ - Callback invoked per matching file; returning
      non-zero cancels the walk.
    - `cargo` DWORD - Opaque value passed to the callback unchanged.
    - `flags` DWORD - Bit flags controlling the walk.
    | flags:
    - `0x01` Wildcard mode - search with "*.*" and match each name against mask with case-insensitive
      wildcards, instead of passing mask straight to FindFirstFile.
    - `0x02` Include hidden files (FILE_ATTRIBUTE_HIDDEN); off by default.
    - `0x04` Include system files (FILE_ATTRIBUTE_SYSTEM); off by default.
    - `0x10000` With 0x01, treat mask as a list of masks separated by "," or ";".

    Returns int - The last callback result: 0 when the walk finished, non-zero when a callback cancelled it.

    |seealso: See also: {{ilink: <c-function ot4xb_recurse_dir> ot4xb_recurse_dir}} }}*/
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
         pMask = 0;
      }
      else if( pMask ) // walk cancelled: the extracted item must still be freed
      {
         _xfree( (void*) pMask );
         pMask = 0;
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_path_combine
            | syntax_: `LPSTR ot4xb_path_combine( LPSTR pFolder, LPSTR pFile )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_path_combine
            | _kw_: path join, combine path, backslash, normalize slashes
   }}*/
/*{{|desc: Combines a folder and a file or relative path into a new path string, inserting the separating
      backslash and normalizing forward slashes to backslashes. Allocates the output buffer; wrapper over
      ot4xb_path_combine_buffer().
    | params:
    - `pFolder` LPSTR - Base folder.
    - `pFile` LPSTR - File name or relative path to append.

    Returns LPSTR - New combined path allocated with _xgrab(); the caller frees it with _xfree().

    |seealso: See also: {{ilink: <c-function ot4xb_path_combine_buffer> ot4xb_path_combine_buffer}} }}*/
OT4XB_API LPSTR __cdecl ot4xb_path_combine( LPSTR pFolder , LPSTR pFile )
{
   DWORD cbo = ((_xstrlen(pFolder) + _xstrlen(pFile) + 16) | 1023);
   LPSTR pOut =  (LPSTR) _xgrab( cbo + 1);
   ot4xb_path_combine_buffer(pFolder,pFile,cbo,pOut);
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_path_combine_buffer
            | syntax_: `UINT ot4xb_path_combine_buffer( LPSTR pFolder, LPSTR pFile, DWORD cbo, LPSTR pOut )`
            | category: filesystem
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_path_combine_buffer
            | _kw_: path join, combine path, buffer, backslash, normalize slashes
   }}*/
/*{{|desc: Combines pFolder and pFile into the caller-provided buffer pOut, inserting a single backslash
      between them and normalizing forward slashes to backslashes. Leading spaces of pFolder, and leading spaces
      and backslashes of pFile, are skipped.
    | params:
    - `pFolder` LPSTR - Base folder; leading spaces are skipped.
    - `pFile` LPSTR - File name or relative path to append; leading spaces and backslashes are skipped.
    - `cbo` DWORD - Size of pOut in bytes. If it is smaller than the combined length plus terminator,
      nothing is written and the function returns 0.
    - `pOut` LPSTR - Output buffer that receives the combined, NUL-terminated path.

    Returns UINT - Length of the resulting path, or 0 when pOut is too small. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

