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
// return TRUE if the app is running inside a Vista system 
OT4XB_API BOOL bIsVista( void )
{
   return ( ot4xb_global_osvi.dwMajorVersion == 6 );
}
//----------------------------------------------------------------------------------------------------------------------
// return TRUE if the app is running inside a Windows XP system 
OT4XB_API BOOL bIsXP( void )
{
   return (( ot4xb_global_osvi.dwMajorVersion == 5 ) && ( ot4xb_global_osvi.dwMinorVersion > 0));
}
//----------------------------------------------------------------------------------------------------------------------
// return TRUE if the app is running inside a Windows XP system 
OT4XB_API BOOL bIsWinXP( void ){ return bIsXP(); }
//----------------------------------------------------------------------------------------------------------------------
// return TRUE if the app is running inside a Windows 9x system 
OT4XB_API BOOL bIsWin9x( void )
{
   return (  (( ot4xb_global_osvi.dwMajorVersion == 4 ) && ( ot4xb_global_osvi.dwPlatformId  == VER_PLATFORM_WIN32_WINDOWS )));
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LISWIN9X( XppParamList pl){ _retl(pl,bIsWin9x());}
XPPRET XPPENTRY LISXP( XppParamList pl){ _retl(pl,bIsXP());}
XPPRET XPPENTRY LISVISTA( XppParamList pl){ _retl(pl,bIsVista());}
//----------------------------------------------------------------------------------------------------------------------
