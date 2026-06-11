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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc><function><name>GetCommandLine</name><category>runtime</category>
<description>Returns the raw command line of the current process.</description>
<syntax>GetCommandLine() -> cCommandLine</syntax>
<return><type>Character</type><description>String returned by the Win32 GetCommandLine() API.</description></return>
</function></xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY GETCOMMANDLINE( XppParamList pl ){ _retc(pl, GetCommandLine()); }
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc><function><name>cAppPath</name><category>filesystem</category>
<description>Returns the directory path of the running executable, including the trailing backslash.</description>
<syntax>cAppPath() -> cPath</syntax>
<return><type>Character</type><description>Executable directory including the trailing path separator.</description></return>
</function></xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY CAPPPATH( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_+1);}
// ---------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc><function><name>cAppDir</name><category>filesystem</category>
<description>Returns the directory path of the running executable without the trailing backslash.</description>
<syntax>cAppDir() -> cPath</syntax>
<return><type>Character</type><description>Executable directory without the trailing path separator.</description></return>
</function></xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY CAPPDIR( XppParamList pl ){ _retclen(pl,_pAppName_,(ULONG) _dwAppPath_);}
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
/*******************************************************************************************************************
<xbdoc><function><name>lCopyFile</name><category>filesystem</category>
<description>Copies a file.</description>
<syntax>lCopyFile( cSource, cTarget [, lOverwrite := .T.] [, lUseTargetFolderAcl := .F.] ) -> lOk</syntax>
<parameters>
<parameter><name>cSource</name><type>Character</type><description>Source file name.</description></parameter>
<parameter><name>cTarget</name><type>Character</type><description>Target file name.</description></parameter>
<parameter><name>lOverwrite</name><type>Logical</type><description>When omitted, defaults to .T. Pass .F. to fail if the target exists.</description></parameter>
<parameter><name>lUseTargetFolderAcl</name><type>Logical</type><description>When .T., uses the internal copy routine so the created target receives the ACLs inherited from the destination folder.</description></parameter>
</parameters>
<return><type>Logical</type><description>.T. when the copy succeeds; otherwise .F.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>lMakePath</name><category>filesystem</category>
<description>Checks that a path exists and creates missing directory components when possible.</description>
<syntax>lMakePath( cPath ) -> lOk</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Directory path to check or create.</description></parameter></parameters>
<return><type>Logical</type><description>.T. when the path exists or was created as a directory; otherwise .F.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cCreateTmpFile</name><category>filesystem</category>
<description>Creates or reserves a temporary file name using the Windows temporary-file API.</description>
<syntax>cCreateTmpFile( [cPath] [, cPrefix] [, lCreate] ) -> cFileName | NIL</syntax>
<parameters>
<parameter><name>cPath</name><type>Character</type><description>Optional directory. When omitted, the Windows temporary path is used.</description></parameter>
<parameter><name>cPrefix</name><type>Character</type><description>Optional file prefix. Defaults to "tmp".</description></parameter>
<parameter><name>lCreate</name><type>Logical</type><description>Passed as the unique number argument to GetTempFileName(); .F. lets Windows create a unique name.</description></parameter>
</parameters>
<return><type>Character | NIL</type><description>Temporary file name, or NIL if Windows cannot create one.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cGetTmpPath</name><category>filesystem</category>
<description>Returns the Windows temporary directory path.</description>
<syntax>cGetTmpPath() -> cPath</syntax>
<return><type>Character</type><description>Path returned by GetTempPath().</description></return>
</function></xbdoc>
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
<xbdoc><function><name>nGetDriveType</name><category>filesystem</category>
<description>Returns the Windows drive type for a root path.</description>
<syntax>nGetDriveType( cRoot ) -> nType</syntax>
<parameters><parameter><name>cRoot</name><type>Character</type><description>Drive root or volume path.</description></parameter></parameters>
<return><type>Numeric</type><description>Drive type returned by GetDriveType(), or DRIVE_NO_ROOT_DIR when no path is supplied.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>lChDir</name><category>filesystem</category>
<description>Changes the Win32 current directory.</description>
<syntax>lChDir( cDir ) -> lOk</syntax>
<parameters><parameter><name>cDir</name><type>Character</type><description>Directory to set as current.</description></parameter></parameters>
<return><type>Logical</type><description>.T. when SetCurrentDirectory() succeeds; otherwise .F.</description></return>
<remarks>The Win32 current directory belongs to the process and may affect other threads.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cDrives</name><category>filesystem</category>
<description>Returns the available drive letters as a compact character string.</description>
<syntax>cDrives() -> cLetters</syntax>
<return><type>Character</type><description>String containing one letter per available logical drive, for example "CZ".</description></return>
</function></xbdoc>
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
<xbdoc><function><name>aDrives</name><category>filesystem</category>
<description>Returns the available logical drive roots as an array.</description>
<syntax>aDrives() -> aRoots | NIL</syntax>
<return><type>Array | NIL</type><description>Array of drive roots such as "C:\"; NIL if Windows returns no drive strings.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cGetShortFileName</name><category>filesystem</category>
<description>Returns the short 8.3 path name for a file path when Windows can provide one.</description>
<syntax>cGetShortFileName( cPath ) -> cShortPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to convert.</description></parameter></parameters>
<return><type>Character</type><description>Short path returned by GetShortPathName(), or an empty string when no path is supplied or conversion fails.</description></return>
</function></xbdoc>
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
<xbdoc>
   <class>
      <name>_TDriveInfo_</name>
      <category>filesystem</category>
      <description>
         Data container used by GetDriveInfo() to return Windows volume information.
      </description>
      <remarks>
         The object stores the raw volume flags in ::nFlags. The read-only logical
         properties simply test ::nFlags against their corresponding Windows flag mask.
      </remarks>
      <members>
         <member><name>cRoot</name><type>Character</type><description>Root path used to query the volume.</description></member>
         <member><name>cLabel</name><type>Character</type><description>Volume label.</description></member>
         <member><name>nSerial</name><type>Numeric</type><description>Volume serial number.</description></member>
         <member><name>nMaxCompLen</name><type>Numeric</type><description>Maximum component length reported by Windows.</description></member>
         <member><name>cFileSystem</name><type>Character</type><description>File system name.</description></member>
         <member><name>nFlags</name><type>Numeric</type><description>Raw file system flags reported by Windows.</description></member>
         <member><name>nDriveType</name><type>Numeric</type><description>Drive type returned by GetDriveType().</description></member>
      </members>
      <properties>
         <property><name>lNamedStreams</name><type>Logical</type><description>.T. when ::nFlags contains 0x40000.</description></property>
         <property><name>lReadOnlyVolume</name><type>Logical</type><description>.T. when ::nFlags contains 0x80000.</description></property>
         <property><name>lObjectIds</name><type>Logical</type><description>.T. when ::nFlags contains 0x10000.</description></property>
         <property><name>lReparsePoints</name><type>Logical</type><description>.T. when ::nFlags contains 0x00080.</description></property>
         <property><name>lSupportsSparseFiles</name><type>Logical</type><description>.T. when ::nFlags contains 0x00040.</description></property>
         <property><name>lVolumeQuotas</name><type>Logical</type><description>.T. when ::nFlags contains 0x00020.</description></property>
         <property><name>lCaseIsPreserved</name><type>Logical</type><description>.T. when ::nFlags contains 0x00002.</description></property>
         <property><name>lCaseSensitive</name><type>Logical</type><description>.T. when ::nFlags contains 0x00001.</description></property>
         <property><name>lFileCompression</name><type>Logical</type><description>.T. when ::nFlags contains 0x00010.</description></property>
         <property><name>lFileEncryption</name><type>Logical</type><description>.T. when ::nFlags contains 0x20000.</description></property>
         <property><name>lPersistentAcls</name><type>Logical</type><description>.T. when ::nFlags contains 0x00008.</description></property>
         <property><name>lUnicodeStoredOnDisk</name><type>Logical</type><description>.T. when ::nFlags contains 0x00004.</description></property>
         <property><name>lVolIsCompressed</name><type>Logical</type><description>.T. when ::nFlags contains 0x08000.</description></property>
      </properties>
   </class>
</xbdoc>
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
<xbdoc>
   <function>
      <name>lDiskReady</name>
      <category>filesystem</category>
      <description>
         Checks whether a drive or volume path can return volume information.
      </description>
      <syntax>lDiskReady( cPath [, @nTimeoutSeconds] ) -> lReady</syntax>
      <parameters>
         <parameter>
            <name>cPath</name>
            <type>Character</type>
            <description>Drive root or volume path to test.</description>
         </parameter>
         <parameter>
            <name>nTimeoutSeconds</name>
            <type>Numeric by reference</type>
            <description>
               Optional timeout in seconds. This parameter changes the execution logic:
               when supplied with a value greater than zero, the check is performed in a
               helper thread instead of calling GetVolumeInformation() directly in the
               caller thread. On return the same parameter is overwritten with a logical
               value: .T. when the helper thread did not complete before the timeout,
               .F. when it completed in time.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Logical</type>
         <description>
            .T. when GetVolumeInformation() succeeds for the path; otherwise .F. A timeout
            also returns .F. and sets the second parameter to .T.
         </description>
      </return>
      <remarks>
         Without a positive timeout the function calls GetVolumeInformation() directly.
         With a positive timeout it starts a helper thread and waits for the requested
         number of seconds. If the check is still pending, the helper thread is left to
         finish later and the function returns immediately with the timeout flag set.
      </remarks>
      <remarks>
         This helper is useful for slow, removable or network drives where a direct
         volume query may block longer than the application wants to wait.
      </remarks>
   </function>
</xbdoc>
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
<xbdoc>
   <function>
      <name>GetDriveInfo</name>
      <category>filesystem</category>
      <description>
         Returns volume information for a drive or root path as a _TDriveInfo_ object.
      </description>
      <syntax>GetDriveInfo( cRoot ) -> oDriveInfo | NIL</syntax>
      <parameters>
         <parameter>
            <name>cRoot</name>
            <type>Character</type>
            <description>Drive root or path passed to the Windows volume query.</description>
         </parameter>
      </parameters>
      <return>
         <type>_TDriveInfo_ | NIL</type>
         <description>
            A _TDriveInfo_ data object when Windows returns volume information; otherwise NIL.
         </description>
      </return>
   </function>
</xbdoc>
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
<xbdoc><function><name>lIsDir</name><category>filesystem</category>
<description>Checks whether a path exists and is a directory.</description>
<syntax>lIsDir( cDir ) -> lIsDirectory</syntax>
<parameters><parameter><name>cDir</name><type>Character</type><description>Path to test.</description></parameter></parameters>
<return><type>Logical</type><description>.T. when GetFileAttributes() succeeds and FILE_ATTRIBUTE_DIRECTORY is set; otherwise .F.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>lIsFile</name><category>filesystem</category>
<description>Checks whether a path exists and is not a directory.</description>
<syntax>lIsFile( cFile ) -> lIsFile</syntax>
<parameters><parameter><name>cFile</name><type>Character</type><description>Path to test.</description></parameter></parameters>
<return><type>Logical</type><description>.T. when GetFileAttributes() succeeds and FILE_ATTRIBUTE_DIRECTORY is not set; otherwise .F.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>GetWinDir</name><category>filesystem</category>
<description>Returns the Windows directory.</description>
<syntax>GetWinDir() -> cPath</syntax>
<return><type>Character</type><description>Path returned by GetWindowsDirectory().</description></return>
</function></xbdoc>
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
<xbdoc><function><name>GetSysDir</name><category>filesystem</category>
<description>Returns the Windows system directory.</description>
<syntax>GetSysDir() -> cPath</syntax>
<return><type>Character</type><description>Path returned by GetSystemDirectory().</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathCombine</name><category>filesystem</category>
<description>Combines path components using backslash separators.</description>
<syntax>cPathCombine( cPart1 [, cPartN...] ) -> cPath</syntax>
<parameters><parameter><name>cPartN</name><type>Character</type><description>Path component. Non-character parameters are ignored.</description></parameter></parameters>
<return><type>Character</type><description>Combined path, or an empty string when no character components are supplied.</description></return>
<remarks>Forward slashes in components are converted to backslashes. Leading and trailing spaces are trimmed from each component.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cUrlCombine</name><category>filesystem</category>
<description>Combines URL or path components using slash separators.</description>
<syntax>cUrlCombine( cPart1 [, cPartN...] ) -> cUrl</syntax>
<parameters><parameter><name>cPartN</name><type>Character</type><description>URL component. Non-character parameters are ignored.</description></parameter></parameters>
<return><type>Character</type><description>Combined URL/path, or an empty string when no character components are supplied.</description></return>
<remarks>Backslashes in components are converted to slashes. Leading and trailing spaces are trimmed from each component.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cPathDefExt</name><category>filesystem</category>
<description>Adds a default extension to a path when the file name has no extension.</description>
<syntax>cPathDefExt( cPath, cDefaultExt ) -> cPath</syntax>
<parameters>
<parameter><name>cPath</name><type>Character</type><description>Path to inspect.</description></parameter>
<parameter><name>cDefaultExt</name><type>Character</type><description>Extension to add. Leading dots and spaces are ignored.</description></parameter>
</parameters>
<return><type>Character</type><description>Path with the default extension added when applicable.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathBuildRoot</name><category>filesystem</category>
<description>Builds a drive root string.</description>
<syntax>cPathBuildRoot( cDrive | nDrive ) -> cRoot</syntax>
<parameters><parameter><name>cDrive | nDrive</name><type>Character | Numeric</type><description>Drive letter, or zero-based drive number where 0 is A.</description></parameter></parameters>
<return><type>Character</type><description>Drive root such as "C:\", or an empty string for invalid input.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>aSplitPath</name><category>filesystem</category>
<description>Splits a path into root and component parts.</description>
<syntax>aSplitPath( cPath ) -> aParts</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to split.</description></parameter></parameters>
<return><type>Array</type><description>Array of path components. Root components such as drive roots or UNC roots are preserved.</description></return>
<remarks>Forward slashes are converted to backslashes before splitting.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cPathCanonicalize</name><category>filesystem</category>
<description>Canonicalizes a path by resolving "." and ".." components where possible.</description>
<syntax>cPathCanonicalize( cPath ) -> cPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to canonicalize.</description></parameter></parameters>
<return><type>Character</type><description>Canonicalized path using backslash separators.</description></return>
<remarks>This is an internal path component normalizer; it does not verify that the resulting path exists.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cPathGetExt</name><category>filesystem</category>
<description>Returns the extension of the file name part of a path.</description>
<syntax>cPathGetExt( cPath ) -> cExt</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to inspect.</description></parameter></parameters>
<return><type>Character</type><description>Extension without the dot, or an empty string when no extension is found.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathRemoveExt</name><category>filesystem</category>
<description>Removes the extension from the file name part of a path.</description>
<syntax>cPathRemoveExt( cPath ) -> cPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to modify.</description></parameter></parameters>
<return><type>Character</type><description>Path without the final file extension.</description></return>
</function></xbdoc>
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
/*******************************************************************************************************************
<xbdoc><function><name>cPathChangeExt</name><category>filesystem</category>
<description>Replaces or adds the extension of the file name part of a path.</description>
<syntax>cPathChangeExt( cPath, cNewExt ) -> cPath</syntax>
<parameters>
<parameter><name>cPath</name><type>Character</type><description>Path to modify.</description></parameter>
<parameter><name>cNewExt</name><type>Character</type><description>New extension. Leading dots and spaces are ignored.</description></parameter>
</parameters>
<return><type>Character</type><description>Path with the requested extension.</description></return>
</function></xbdoc>
*******************************************************************************************************************/
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
<xbdoc><function><name>cPathGetFileName</name><category>filesystem</category>
<description>Returns the file name part of a path.</description>
<syntax>cPathGetFileName( cPath ) -> cFileName</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to inspect.</description></parameter></parameters>
<return><type>Character</type><description>Text after the last backslash or drive separator.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathRemoveBackSlash</name><category>filesystem</category>
<description>Removes trailing backslashes from a path.</description>
<syntax>cPathRemoveBackSlash( cPath ) -> cPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to modify.</description></parameter></parameters>
<return><type>Character</type><description>Path without trailing backslashes, or an empty string when no path is supplied.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathAddBackSlash</name><category>filesystem</category>
<description>Ensures that a path ends with one backslash.</description>
<syntax>cPathAddBackSlash( cPath ) -> cPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to modify.</description></parameter></parameters>
<return><type>Character</type><description>Path with exactly one trailing backslash.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathGetPath</name><category>filesystem</category>
<description>Returns the directory part of a path.</description>
<syntax>cPathGetPath( cPath ) -> cPathPart</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to inspect.</description></parameter></parameters>
<return><type>Character</type><description>Path up to the last directory separator or drive separator.</description></return>
</function></xbdoc>
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
<xbdoc><function><name>cPathGetRoot</name><category>filesystem</category>
<description>Returns the root part of a path.</description>
<syntax>cPathGetRoot( cPath ) -> cRoot</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to inspect.</description></parameter></parameters>
<return><type>Character</type><description>UNC root, drive root, single backslash root, or an empty string when no root is present.</description></return>
<remarks>Forward slashes are converted to backslashes before parsing.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>cPathRemoveRoot</name><category>filesystem</category>
<description>Removes the root part of a path.</description>
<syntax>cPathRemoveRoot( cPath ) -> cPath</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to modify.</description></parameter></parameters>
<return><type>Character</type><description>Path without its UNC, drive or leading-backslash root.</description></return>
<remarks>Forward slashes are converted to backslashes before parsing.</remarks>
</function></xbdoc>
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
<xbdoc><function><name>lPathIsRelative</name><category>filesystem</category>
<description>Checks whether a path is relative according to the simple OT4XB path test.</description>
<syntax>lPathIsRelative( cPath ) -> lRelative</syntax>
<parameters><parameter><name>cPath</name><type>Character</type><description>Path to test.</description></parameter></parameters>
<return><type>Logical</type><description>.F. when the path starts with "\" or has ":" as the second character; otherwise .T.</description></return>
</function></xbdoc>
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
<xbdoc>
   <class>
      <name>WIN32_FIND_DATA</name>
      <category>filesystem</category>
      <description>
         OT4XB structure class that exposes the Windows WIN32_FIND_DATA structure
         and provides a small FindFirst/FindNext/FindClose search helper.
      </description>
      <syntax>WIN32_FIND_DATA():New() -> oFindData</syntax>
      <remarks>
         The documented members are the WIN32_FIND_DATA fields. They are filled by
         ::FindFirst() and ::FindNext(). The logical attribute properties map directly
         to the corresponding bits in ::dwFileAttributes. Call ::FindClose() when a
         search is no longer needed.
      </remarks>
      <remarks>
         A newly created WIN32_FIND_DATA object can be used directly with ::FindFirst()
         and ::FindNext(); it is not necessary to call ::_alloc_() or ::_link_() first.
         For normal enumeration, calling ::FindClose() at the end is enough.
      </remarks>
      <members>
         <member><name>dwFileAttributes</name><type>Numeric</type><description>Raw Windows file attribute flags.</description></member>
         <member><name>ftCreationTime</name><type>FILETIME64</type><description>Creation time.</description></member>
         <member><name>ftLastAccessTime</name><type>FILETIME64</type><description>Last access time.</description></member>
         <member><name>ftLastWriteTime</name><type>FILETIME64</type><description>Last write time.</description></member>
         <member><name>nFileSizeHigh</name><type>Numeric</type><description>High DWORD of the file size.</description></member>
         <member><name>nFileSizeLow</name><type>Numeric</type><description>Low DWORD of the file size.</description></member>
         <member><name>dwReserved0</name><type>Numeric</type><description>Windows reserved field.</description></member>
         <member><name>dwReserved1</name><type>Numeric</type><description>Windows reserved field.</description></member>
         <member><name>cFileName</name><type>Character</type><description>Primary file name.</description></member>
         <member><name>cAlternateFileName</name><type>Character</type><description>Alternate 8.3 file name, when available.</description></member>
      </members>
      <properties>
         <property><name>nFileSize</name><type>Numeric</type><description>Combined file size mapped to ::nFileSizeHigh and ::nFileSizeLow. Since Xbase++ numeric values are internally signed integers or doubles, large values are returned as double when needed.</description></property>
         <property><name>lArchive</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_ARCHIVE bit in ::dwFileAttributes.</description></property>
         <property><name>lCompressed</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_COMPRESSED bit in ::dwFileAttributes.</description></property>
         <property><name>lDevice</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_DEVICE bit in ::dwFileAttributes.</description></property>
         <property><name>lDirectory</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_DIRECTORY bit in ::dwFileAttributes.</description></property>
         <property><name>lEncrypted</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_ENCRYPTED bit in ::dwFileAttributes.</description></property>
         <property><name>lHidden</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_HIDDEN bit in ::dwFileAttributes.</description></property>
         <property><name>lNormal</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_NORMAL bit in ::dwFileAttributes.</description></property>
         <property><name>lNotContentIndexed</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_NOT_CONTENT_INDEXED bit in ::dwFileAttributes.</description></property>
         <property><name>lOffline</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_OFFLINE bit in ::dwFileAttributes.</description></property>
         <property><name>lReadonly</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_READONLY bit in ::dwFileAttributes.</description></property>
         <property><name>lReparsePoint</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_REPARSE_POINT bit in ::dwFileAttributes.</description></property>
         <property><name>lSparseFile</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_SPARSE_FILE bit in ::dwFileAttributes.</description></property>
         <property><name>lSystem</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_SYSTEM bit in ::dwFileAttributes.</description></property>
         <property><name>lTemporary</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_TEMPORARY bit in ::dwFileAttributes.</description></property>
         <property><name>lVirtual</name><type>Logical</type><description>Reads or writes the FILE_ATTRIBUTE_VIRTUAL bit in ::dwFileAttributes.</description></property>
      </properties>
      <methods>
         <method><name>FindFirst</name><syntax>::FindFirst( cMask ) -> lFound</syntax><description>Starts a search and fills the structure with the first matching entry.</description></method>
         <method><name>FindNext</name><syntax>::FindNext() -> lFound</syntax><description>Moves to the next matching entry and updates the structure.</description></method>
         <method><name>FindClose</name><syntax>::FindClose() -> NIL</syntax><description>Closes the current search handle.</description></method>
      </methods>
      <example><![CDATA[
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
      ]]></example>
   </class>
</xbdoc>
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
      pc->Var( "_find_handle_" ); // Xbase++ instance state, not part of the WIN32_FIND_DATA structure.
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
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>cCpuSerial</name>
      <category>system</category>
      <description>
         Returns a legacy CPU identification string obtained with the x86 CPUID instruction.
      </description>
      <syntax>cCpuSerial() -> cSerial</syntax>
      <remarks>
         The function calls CPUID with EAX=1 and checks the Processor Serial Number
         feature bit in EDX. When that bit is present, it calls CPUID with EAX=3 and
         formats the reported serial data together with the EAX=1 value. Otherwise it
         returns a short hexadecimal string built from the low word of EAX=1.
      </remarks>
      <remarks>
         This is a legacy helper. It was useful only for the Intel Pentium III
         Processor Serial Number feature. That feature stopped being useful as a CPU
         serial source when Pentium 4 and later processors no longer supported it.
         On current CPUs the returned value is not a real processor serial number and
         should not be treated as a stable hardware identity.
      </remarks>
      <return>
         <type>Character</type>
         <description>Formatted hexadecimal CPU identification string.</description>
      </return>
   </function>
</xbdoc>
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
<xbdoc>
   <function>
      <name>GetProcessArgv</name>
      <category>runtime</category>
      <description>
         Returns the current process command-line arguments as an array.
      </description>
      <syntax>GetProcessArgv() -> aArgs</syntax>
      <remarks>
         The function reads the process command line, skips the executable name and
         parses the remaining text into separate arguments. Quoted arguments are kept
         together and backslash-escaped quotes are handled by the internal parser.
      </remarks>
      <remarks>
         GetProccessArgv() is kept as a backward-compatible alias for the historical
         misspelling and delegates to GetProcessArgv().
      </remarks>
      <remarks>
         When the program is launched through xppdbg, the first array element may be the
         program name and the user arguments may therefore appear shifted by one position.
      </remarks>
      <example><![CDATA[
      // Compensate the xppdbg argument shift when wrapping argv-style access.
      INLINE METHOD argv(n)
         RETURN __aPeek( GetProccessArgv(), n + iif( IsDebug(), 1, 0 ) )
      ]]></example>
      <remarks>
         The corrected GetProcessArgv() name is available in ot4xb.dll
         Version:{1,7,14,0}.
      </remarks>
      <return>
         <type>Array</type>
         <description>Array with the arguments passed after the executable name.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( GETPROCCESSARGV ) { GETPROCESSARGV( pl ); }
_XPP_REG_FUN_( GETPROCESSARGV )
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
<xbdoc>
   <function>
      <name>ot4xb_pushdir</name>
      <category>filesystem</category>
      <description>
         Pushes the current directory onto the current thread's directory stack.
      </description>
      <syntax>ot4xb_pushdir( [cNewDir] ) -> NIL | lOk</syntax>
      <parameters>
         <parameter>
            <name>cNewDir</name>
            <type>Character</type>
            <description>Optional directory to set after the current directory has been pushed.</description>
         </parameter>
      </parameters>
      <return>
         <type>NIL | Logical</type>
         <description>
            NIL when only the current directory is pushed. When cNewDir is supplied,
            returns .T. if the directory change succeeds, otherwise .F.
         </description>
      </return>
      <remarks>
         The saved directories are stored in a thread-local stack. Each thread has its
         own push/pop directory stack, so a thread only pops entries it pushed itself.
      </remarks>
      <remarks>
         The stack is thread-local, but the actual directory change uses the Win32
         current directory through SetCurrentDirectory(). That current directory belongs
         to the process, so changing it can affect other threads.
      </remarks>
   </function>
</xbdoc>
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
<xbdoc>
   <function>
      <name>ot4xb_popdir</name>
      <category>filesystem</category>
      <description>
         Restores the last directory saved with ot4xb_pushdir() in the current thread.
      </description>
      <syntax>ot4xb_popdir() -> lOk | NIL</syntax>
      <return>
         <type>Logical | NIL</type>
         <description>
            .T. when the saved directory is restored, .F. when the restore fails, or NIL
            when the current thread's directory stack is empty.
         </description>
      </return>
      <remarks>
         The stack is thread-local, so ot4xb_popdir() can only restore directories pushed
         by the same thread.
      </remarks>
      <remarks>
         The restore operation uses SetCurrentDirectoryW(). The saved stack entry is
         thread-local, but the Win32 current directory being restored belongs to the
         process and can affect other threads.
      </remarks>
   </function>
</xbdoc>
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
<xbdoc>
   <function>
      <name>ot4xb_curdir</name>
      <category>filesystem</category>
      <description>
         Gets or sets the current directory.
      </description>
      <syntax>ot4xb_curdir() -> cCurDir</syntax>
      <syntax>ot4xb_curdir( cNewDir ) -> lOk</syntax>
      <parameters>
         <parameter>
            <name>cNewDir</name>
            <type>Character</type>
            <description>Optional directory to set as the current directory.</description>
         </parameter>
      </parameters>
      <return>
         <type>Character | Logical | NIL</type>
         <description>
            Without parameters, returns the current directory as a full path. With cNewDir,
            returns .T. if the directory change succeeds, otherwise .F. Returns NIL when
            the current directory cannot be obtained or the parameter is not character.
         </description>
      </return>
      <remarks>
         This function reads or changes the Win32 current directory directly. It does not
         push or pop the thread-local directory stack used by ot4xb_pushdir() and
         ot4xb_popdir().
      </remarks>
      <remarks>
         Unlike the push/pop stack, the current directory changed by SetCurrentDirectoryW()
         belongs to the process, so changing it can affect other threads.
      </remarks>
   </function>
</xbdoc>
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

