//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
OSVERSIONINFOEX ot4xb_global_osvi ;
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( push )
#pragma warning( disable : 4996 )
void _API_OSVer_InitProc( void)
{
   int i;
   LPSTR p = (LPSTR) ( (void*) &ot4xb_global_osvi );
   for( i = 0; i < sizeof(OSVERSIONINFOEX); i++) p[i] = 0; // ZeroMemory
   ot4xb_global_osvi.dwOSVersionInfoSize = (DWORD) sizeof(OSVERSIONINFOEX);

   if( ! GetVersionEx((OSVERSIONINFO*) ( (void*) &ot4xb_global_osvi )) )
   {
      for( i = 0; i < sizeof(OSVERSIONINFOEX); i++) p[i] = 0; // ZeroMemory
      ot4xb_global_osvi.dwOSVersionInfoSize = (DWORD) sizeof(OSVERSIONINFO);
      GetVersionEx((OSVERSIONINFO*) ( (void*) &ot4xb_global_osvi ));
   }
}
#pragma warning( pop )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_fill_OSVERSIONINFOEX
            | syntax_: `void ot4xb_fill_OSVERSIONINFOEX( OSVERSIONINFOEX* p )`
            | category: runtime/os
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_fill_OSVERSIONINFOEX
            | _kw_: OSVERSIONINFOEX, windows version, os version, cached
   }}*/
/*{{|desc: Copies the cached OSVERSIONINFOEX data captured during ot4xb initialization into the caller-provided
      structure.
    | params:
    - `p` OSVERSIONINFOEX* - Destination structure that receives the cached data.

    Returns void

    |note: The cached data comes from the legacy GetVersionEx API and should be treated as compatibility
      information, not as a modern feature-detection mechanism. }}*/
OT4XB_API void ot4xb_fill_OSVERSIONINFOEX( OSVERSIONINFOEX* p )
{
   _bcopy((LPBYTE) p , (LPBYTE) &ot4xb_global_osvi , sizeof(OSVERSIONINFOEX));
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bIsVista
            | syntax_: `BOOL bIsVista( void )`
            | category: runtime/os
            | header: ot4xb_c_exported.h
            | mangled-name: bIsVista
            | _kw_: windows version, Vista, NT 6, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks whether the cached OSVERSIONINFOEX data reports Windows NT
      major version 6.

    Returns BOOL - TRUE when major version is 6; otherwise FALSE.

    |note: Despite the name, this check is based only on the major version and is therefore a legacy
      Vista/Windows 7-era compatibility predicate. It returns TRUE for cached version 6.x values, including
      Vista and Windows 7. On Windows 10 it returns FALSE. These helpers have little practical value in current
      builds unless ot4xb is built for a specialized legacy target. }}*/
OT4XB_API BOOL bIsVista( void )
{
   return ( ot4xb_global_osvi.dwMajorVersion == 6 );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bIsXP
            | syntax_: `BOOL bIsXP( void )`
            | category: runtime/os
            | header: ot4xb_c_exported.h
            | mangled-name: bIsXP
            | _kw_: windows version, XP, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks whether the cached OSVERSIONINFOEX data identifies the Windows
      XP family.

    Returns BOOL - TRUE when major version is 5 and minor version is greater than 0.

    |note: This function is retained for compatibility with old code. Current ot4xb builds do not imply support
      for Windows XP; support depends on the toolchain, build configuration, and target runtime environment. For
      example, Visual Studio 2022 no longer supports targeting Windows XP. On Windows 10 this function returns
      FALSE. These helpers have little practical value in current builds unless ot4xb is built for a specialized
      legacy target. }}*/
OT4XB_API BOOL bIsXP( void )
{
   return (( ot4xb_global_osvi.dwMajorVersion == 5 ) && ( ot4xb_global_osvi.dwMinorVersion > 0));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bIsWinXP
            | syntax_: `BOOL bIsWinXP( void )`
            | category: runtime/os
            | header: ot4xb_c_exported.h
            | mangled-name: bIsWinXP
            | _kw_: windows version, XP, legacy alias
   }}*/
/*{{|desc: Legacy alias for bIsXP().

    Returns BOOL - TRUE when bIsXP() returns TRUE.

    |note: This function has the same legacy/current-build behavior as bIsXP(). In normal current builds it is
      expected to return FALSE. On Windows 10 it returns FALSE. These helpers have little practical value in
      current builds unless ot4xb is built for a specialized legacy target.

    |seealso: See also: {{ilink: <c-function bIsXP> bIsXP}} }}*/
OT4XB_API BOOL bIsWinXP( void ){ return bIsXP(); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bIsWin9x
            | syntax_: `BOOL bIsWin9x( void )`
            | category: runtime/os
            | header: ot4xb_c_exported.h
            | mangled-name: bIsWin9x
            | _kw_: windows version, Windows 95 98 ME, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks the cached OSVERSIONINFOEX data for Windows 9x platform values.

    Returns BOOL - TRUE when major version is 4 and platform id is VER_PLATFORM_WIN32_WINDOWS.

    |note: This function is retained for compatibility with old code. In normal current builds it is expected
      to return FALSE. On Windows 10 it returns FALSE. These helpers have little practical value in current
      builds unless ot4xb is built for a specialized legacy target. }}*/
OT4XB_API BOOL bIsWin9x( void )
{
   return (  (( ot4xb_global_osvi.dwMajorVersion == 4 ) && ( ot4xb_global_osvi.dwPlatformId  == VER_PLATFORM_WIN32_WINDOWS )));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsWin9x
            | syntax_: `lIsWin9x()`
            | category: runtime/os
            | _kw_: windows version, Windows 95 98 ME, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks whether the cached Windows version data identifies a Windows 9x
      platform.

    Returns logical - .T. when the cached version data has major version 4 and the platform id is
      VER_PLATFORM_WIN32_WINDOWS; otherwise .F..

    |note: This function is retained for compatibility with old code. Current ot4xb builds do not imply support
      for Windows 9x; support depends on the toolchain, build configuration, and target runtime environment. On
      Windows 10 this function returns .F.. It has little practical value in current builds unless ot4xb is
      built for a specialized legacy target. }}*/
XPPRET XPPENTRY LISWIN9X( XppParamList pl){ _retl(pl,bIsWin9x());}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsXp
            | syntax_: `lIsXp()`
            | category: runtime/os
            | _kw_: windows version, XP, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks whether the cached Windows version data identifies the Windows
      XP family.

    Returns logical - .T. when the cached version data has major version 5 and minor version greater than 0;
      otherwise .F..

    |note: This function is retained for compatibility with old code. Current ot4xb builds do not imply support
      for Windows XP; support depends on the toolchain, build configuration, and target runtime environment. For
      example, Visual Studio 2022 no longer supports targeting Windows XP. In normal current builds this
      function is expected to return .F.. On Windows 10 this function returns .F.. It has little practical value
      in current builds unless ot4xb is built for a specialized legacy target. }}*/
XPPRET XPPENTRY LISXP( XppParamList pl){ _retl(pl,bIsXP());}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsVista
            | syntax_: `lIsVista()`
            | category: runtime/os
            | _kw_: windows version, Vista, NT 6, legacy
   }}*/
/*{{|desc: Legacy OS-version helper that checks whether the cached Windows version data reports Windows NT
      major version 6.

    Returns logical - .T. when the cached version data has major version 6; otherwise .F..

    |note: Despite the name, this check is based only on the major version and is therefore a legacy
      Vista/Windows 7-era compatibility predicate. It returns .T. for cached version 6.x values, including Vista
      and Windows 7. On Windows 10 this function returns .F.. It has little practical value in current builds
      unless ot4xb is built for a specialized legacy target. }}*/
XPPRET XPPENTRY LISVISTA( XppParamList pl){ _retl(pl,bIsVista());}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
