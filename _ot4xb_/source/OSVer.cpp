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
OT4XB_API void ot4xb_fill_OSVERSIONINFOEX( OSVERSIONINFOEX* p )
{
   _bcopy((LPBYTE) p , (LPBYTE) &ot4xb_global_osvi , sizeof(OSVERSIONINFOEX));
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>ot4xb_fill_OSVERSIONINFOEX</name>
      <category>runtime/os</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Copies the cached OSVERSIONINFOEX data captured during ot4xb
         initialization into the caller-provided structure.
      </description>
      <syntax>void ot4xb_fill_OSVERSIONINFOEX( OSVERSIONINFOEX* p )</syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>OSVERSIONINFOEX*</type>
            <description>Destination structure that receives the cached data.</description>
         </parameter>
      </parameters>
      <return>void</return>
      <remarks>
         The cached data comes from the legacy GetVersionEx API and should be
         treated as compatibility information, not as a modern feature-detection
         mechanism.
      </remarks>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>bIsVista</name>
      <category>runtime/os</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Legacy OS-version helper that checks whether the cached
         OSVERSIONINFOEX data reports Windows NT major version 6.
      </description>
      <syntax>BOOL bIsVista( void )</syntax>
      <parameters/>
      <return>
         <type>BOOL</type>
         <description>TRUE when major version is 6; otherwise FALSE.</description>
      </return>
      <remarks>
         Despite the name, this check is based only on the major version and is
         therefore a legacy Vista/Windows 7-era compatibility predicate. It
         returns TRUE for cached version 6.x values, including Vista and
         Windows 7. On Windows 10 it returns FALSE. These helpers have little
         practical value in current builds unless ot4xb is built for a
         specialized legacy target.
      </remarks>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
OT4XB_API BOOL bIsVista( void )
{
   return ( ot4xb_global_osvi.dwMajorVersion == 6 );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>bIsXP</name>
      <category>runtime/os</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Legacy OS-version helper that checks whether the cached
         OSVERSIONINFOEX data identifies the Windows XP family.
      </description>
      <syntax>BOOL bIsXP( void )</syntax>
      <parameters/>
      <return>
         <type>BOOL</type>
         <description>TRUE when major version is 5 and minor version is greater than 0.</description>
      </return>
      <remarks>
         This function is retained for compatibility with old code. Current
         ot4xb builds do not imply support for Windows XP; support depends on
         the toolchain, build configuration, and target runtime environment.
         For example, Visual Studio 2022 no longer supports targeting Windows
         XP. On Windows 10 this function returns FALSE. These helpers have
         little practical value in current builds unless ot4xb is built for a
         specialized legacy target.
      </remarks>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
OT4XB_API BOOL bIsXP( void )
{
   return (( ot4xb_global_osvi.dwMajorVersion == 5 ) && ( ot4xb_global_osvi.dwMinorVersion > 0));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>bIsWinXP</name>
      <category>runtime/os</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Legacy alias for bIsXP().
      </description>
      <syntax>BOOL bIsWinXP( void )</syntax>
      <parameters/>
      <return>
         <type>BOOL</type>
         <description>TRUE when bIsXP() returns TRUE.</description>
      </return>
      <remarks>
         This function has the same legacy/current-build behavior as bIsXP().
         In normal current builds it is expected to return FALSE. On Windows
         10 it returns FALSE. These helpers have little practical value in
         current builds unless ot4xb is built for a specialized legacy target.
      </remarks>
      <see-also>bIsXP</see-also>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
OT4XB_API BOOL bIsWinXP( void ){ return bIsXP(); }
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>bIsWin9x</name>
      <category>runtime/os</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Legacy OS-version helper that checks the cached OSVERSIONINFOEX data
         for Windows 9x platform values.
      </description>
      <syntax>BOOL bIsWin9x( void )</syntax>
      <parameters/>
      <return>
         <type>BOOL</type>
         <description>TRUE when major version is 4 and platform id is VER_PLATFORM_WIN32_WINDOWS.</description>
      </return>
      <remarks>
         This function is retained for compatibility with old code. In normal
         current builds it is expected to return FALSE. On Windows 10 it
         returns FALSE. These helpers have little practical value in current
         builds unless ot4xb is built for a specialized legacy target.
      </remarks>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
OT4XB_API BOOL bIsWin9x( void )
{
   return (  (( ot4xb_global_osvi.dwMajorVersion == 4 ) && ( ot4xb_global_osvi.dwPlatformId  == VER_PLATFORM_WIN32_WINDOWS )));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>lIsWin9x</name>
      <category>runtime/os</category>
      <description>
         Legacy OS-version helper that checks whether the cached Windows
         version data identifies a Windows 9x platform.
      </description>
      <syntax>lIsWin9x() -> lIsWin9x</syntax>
      <parameters/>
      <return>
         <type>logical</type>
         <description>
            .T. when the cached version data has major version 4 and the
            platform id is VER_PLATFORM_WIN32_WINDOWS; otherwise .F..
         </description>
      </return>
      <remarks>
         This function is retained for compatibility with old code. Current
         ot4xb builds do not imply support for Windows 9x; support depends on
         the toolchain, build configuration, and target runtime environment.
         On Windows 10 this function returns .F.. It has little practical value
         in current builds unless ot4xb is built for a specialized legacy
         target.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LISWIN9X( XppParamList pl){ _retl(pl,bIsWin9x());}
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>lIsXp</name>
      <category>runtime/os</category>
      <description>
         Legacy OS-version helper that checks whether the cached Windows
         version data identifies the Windows XP family.
      </description>
      <syntax>lIsXp() -> lIsXp</syntax>
      <parameters/>
      <return>
         <type>logical</type>
         <description>
            .T. when the cached version data has major version 5 and minor
            version greater than 0; otherwise .F..
         </description>
      </return>
      <remarks>
         This function is retained for compatibility with old code. Current
         ot4xb builds do not imply support for Windows XP; support depends on
         the toolchain, build configuration, and target runtime environment.
         For example, Visual Studio 2022 no longer supports targeting Windows
         XP. In normal current builds this function is expected to return .F..
         On Windows 10 this function returns .F.. It has little practical value
         in current builds unless ot4xb is built for a specialized legacy
         target.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LISXP( XppParamList pl){ _retl(pl,bIsXP());}
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>lIsVista</name>
      <category>runtime/os</category>
      <description>
         Legacy OS-version helper that checks whether the cached Windows
         version data reports Windows NT major version 6.
      </description>
      <syntax>lIsVista() -> lIsVista</syntax>
      <parameters/>
      <return>
         <type>logical</type>
         <description>
            .T. when the cached version data has major version 6; otherwise
            .F..
         </description>
      </return>
      <remarks>
         Despite the name, this check is based only on the major version and is
         therefore a legacy Vista/Windows 7-era compatibility predicate. It
         returns .T. for cached version 6.x values, including Vista and Windows
         7. On Windows 10 this function returns .F.. It has little practical
         value in current builds unless ot4xb is built for a specialized legacy
         target.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LISVISTA( XppParamList pl){ _retl(pl,bIsVista());}
//----------------------------------------------------------------------------------------------------------------------
