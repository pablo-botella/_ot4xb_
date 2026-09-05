//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <locale.h>
#include <time.h>
#include <stdio.h>
// -----------------------------------------------------------------------------------------------------------------
static const char s_dt[7][4]  = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
static const char s_mt[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
//----------------------------------------------------------------------------------------------------------------------
static void elaptime_to_str( TZString & z, LONGLONG t1, LONGLONG t2 );
//----------------------------------------------------------------------------------------------------------------------

class lpstr_cb_t
{
   public:
      // ---------------------------------------------------------------------------------
      LPSTR* m_ppb;
      LONG*  m_pcb;
      // ---------------------------------------------------------------------------------
      lpstr_cb_t( LPSTR & p, LONG & cb ){ m_ppb = &p; m_pcb = &cb;};
      // ---------------------------------------------------------------------------------
      WORD d2n( LPSTR _ps_, DWORD sh , DWORD cb )
      {
         DWORD   dwNum = 0;
         LPBYTE p    = _mk_ptr_( LPBYTE , _ps_ , sh );
         while( cb )
         {
            BYTE ch = *p++;
            dwNum += (ch - 48);
            cb--;
            if(cb) dwNum = ( dwNum * 10 );
         }
         return LOWORD(dwNum);
      };
      // ---------------------------------------------------------------------------------
      BOOL skip(LONG n = 1)
      {
         if( (n < 1 ) || (m_pcb[0] < n) ){return FALSE;}
         m_ppb[0] = _mk_ptr_(LPSTR,m_ppb[0],n);
         m_pcb[0] -= n;
         return TRUE;
      };
      // ---------------------------------------------------------------------------------
      BOOL chk(LONG n){return (BOOL)(*m_pcb >= n);};
      // ---------------------------------------------------------------------------------
      BOOL d(LONG n = 1)
      {
         char _ch;
         if( (n < 1 ) || (m_pcb[0] < n) ){return FALSE;}
         while( n ){ --n; _ch = (*m_ppb)[n]; if((_ch < '0') || (_ch > '9')){return FALSE; }}
         return TRUE;
      };
      // ---------------------------------------------------------------------------------
      BOOL sg(void)
      {
         if( (*m_pcb) < 1 ){return FALSE;}
         return (BOOL) ( (((*m_ppb)[0]) == '+') || (((*m_ppb)[0]) == '-') );
      };
      // ---------------------------------------------------------------------------------
      BOOL sp(void)
      {
         if( (*m_pcb) < 1 ){return FALSE;}
         return (BOOL) ((*m_ppb)[0] == 32);
      };
      // ---------------------------------------------------------------------------------
      WORD w(LONG nDigits)
      {
         WORD w = d2n(*m_ppb,0,nDigits);
         skip(nDigits);
         return w;
      };
      // ---------------------------------------------------------------------------------
      char ch(void){char _ch = (*m_ppb)[0];skip(1);return _ch;};
      // ---------------------------------------------------------------------------------
      BOOL cc( char _ch ){ return (BOOL) ((*m_pcb >= 1) && (((*m_ppb)[0]) == _ch));};
      BOOL chc( char _ch ){ return (BOOL) ((*m_pcb >= 1) && (ch() == _ch));};
      // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
#define _ensure_(b) {if(!(b)){ goto End_Parsing;}}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_SetTs
            | syntax_: `void __cdecl ft64_SetTs( FILETIME* pft, LPSTR ps, LONG* pnShift )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_SetTs
            | _kw_: timestamp, parse date, FILETIME, ISO 8601, timezone
   }}*/
/*{{|desc: Parses the timestamp string ps and stores the result into the FILETIME pft. When the string carries a timezone
      component, the shift in minutes is written to pnShift. This is the C primitive behind the Xbase++ function
      ft64_SetTs().
    | params:
    - `pft` FILETIME* - Destination FILETIME; both DWORDs are zeroed first, and left at zero when ps is empty or
      cannot be parsed.
    - `ps` LPSTR - Timestamp string to parse.
    - `pnShift` LONG* - Receives the timezone shift in minutes; ignored when NULL.

    Returns void.

    |seealso: See also: {{ilink: <function ft64_SetTs> ft64_SetTs}}, {{ilink: <class FILETIME64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_SetTs( FILETIME* pft, LPSTR ps , LONG* pnShift )
{
   LONG cb;
   if( pft ){ pft->dwHighDateTime = 0; pft->dwLowDateTime = 0; }
   if( !( pft && ps ) ) return;
   cb = (LONG) _xstrlen(ps);
   if( cb > 0 )
   {
      lpstr_cb_t p( ps , cb);
      char ch = 0;
      SYSTEMTIME st;
      LONG  nShift = 0;

      _bset( (LPBYTE) &st , 0 , sizeof(SYSTEMTIME) );
      _ensure_(p.chk(4));
      st.wYear = p.w(4);
      _ensure_(p.chk(1)); if( !p.d() ){ ch = p.ch();}
      _ensure_(p.chk(2)); st.wMonth = p.w(2);
      if(ch){ _ensure_(p.chc(ch)); }
      _ensure_(p.chk(2)); st.wDay = p.w(2);
      while(!p.d()){ _ensure_( p.skip() ); }
      _ensure_(p.chk(2)); st.wHour   = p.w(2);
      if(p.d()){ch=0;} else { ch = p.ch();}
      _ensure_(p.chk(2)); st.wMinute = p.w(2);
      if(ch && p.cc(ch)){ p.skip();}
      _ensure_(p.chk(2));
      if( p.d(2) ) st.wSecond = p.w(2);
      if( p.cc('.') || p.cc(',') || p.cc(':') )
      {
         p.skip();
         if( ! p.d() ) goto Parse_Zone;
         st.wMilliseconds = (p.w(1) * 100 );
         if( ! p.d() ) goto Parse_Zone;
         st.wMilliseconds += (p.w(1) * 10 );
         if( ! p.d() ) goto Parse_Zone;
         st.wMilliseconds +=  (p.w(1) & 0xFFFF);
      }
      Parse_Zone: ;
      _ensure_(p.chk(1));
      while(p.sp()){ p.skip();}
      _ensure_(p.chk(1));
      if( p.sg() )
      {
         WORD z = 0;
         ch = p.ch();
         if( p.d(2) ) z = ( p.w(2) * 60 );
         else if( p.d(1) ) z = ( p.w(1) * 60 );
         else {  goto End_Parsing; }
         if( ch == '-' )  nShift -= (LONG) MAKELONG(z,0);
         else nShift += (LONG) MAKELONG(z,0);
         _ensure_( p.skip() );
         if( p.d(2) )
         {
            z = (p.w(2) & 0xFFFF);
            if( ch == '-' )  nShift -= (LONG) MAKELONG(z,0);
            else nShift += (LONG) MAKELONG(z,0);
         }
      }
      End_Parsing: ;
      SystemTimeToFileTime( &st , pft);
      if( pnShift ) pnShift[0] = nShift;
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_SetTs
            | syntax_: `ft64_SetTs( pft, cTimeStamp, @nShift [, nFlags] )`
            | category: date-time/filetime
            | _kw_: timestamp, parse date, FILETIME64, ISO 8601, timezone
   }}*/
/*{{|desc: Stores a timestamp string into a FILETIME64 value.
    | params: 

    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `cTimeStamp` Character/FILETIME64 object/NIL - Timestamp string to parse. With flag 0x01 it may also be a
      FILETIME64-compatible object to copy from. With flag 0x10, NIL stores the current time.
    - `nShift` Numeric by reference - Receives the timezone shift in minutes when the string contains a timezone
      component.
    - `nFlags` Numeric - Behaviour flags, see below.

    Flags:
    - `0x01` cTimeStamp may be a FILETIME64-compatible object to copy from
    - `0x10` cTimeStamp == NIL stores the current UTC time
    - `0x30` cTimeStamp == NIL stores the current local time

    Returns NIL.

    |note: The pft parameter uses OT4XB extended pointer handling. It can be a FILETIME64 object, an 8-byte character buffer
      passed by reference when it must be modified, a numeric memory pointer, or an array holding the low and high DWORD
      values.

    |seealso: See also: {{ilink: <class FILETIME64> FILETIME64}} }}*/
_XPP_REG_FUN_( FT64_SETTS )
{
   TXppParamList xpp(pl,4);
   DWORD flags = xpp[4]->GetDWord();  
   FILETIME* pft = (FILETIME*) xpp[1]->WLockStrEx();
   if( pft && ( xpp[1]->ExLen() >= sizeof( FILETIME ) ) )
   {
      if( xpp[2]->CheckType( XPP_CHARACTER )  )
      {
         LPSTR ps = xpp[2]->LockStr();
         if( ps )
         {
            LONG ns = 0;
            ft64_SetTs(pft,ps ,&ns);
            xpp[3]->PutLong(ns);
         }
      }
      else if( xpp[2]->CheckType( XPP_UNDEF) && ( flags & 0x10 ) )
      {
         if(flags & 0x20) 
         {
            SYSTEMTIME st;
            GetLocalTime( &st );
            SystemTimeToFileTime( &st , pft );
         }
         else
         {
            ft64_now(pft);
         }
      }
      else if( xpp[2]->CheckType( XPP_OBJECT ) && ( flags & 0x01 ) )
      {
         FILETIME* pft2 = (FILETIME*) xpp[2]->LockStrEx();
         if( pft2 )
         {
            if( xpp[2]->ExLen() >= sizeof( FILETIME ) )
            {
               _bcopy( _mk_ptr_(LPBYTE,pft,0) ,  _mk_ptr_(LPBYTE,pft2,0) , sizeof( FILETIME ) );
            } 
         }
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_GetTs
            | syntax_: `LPSTR __cdecl ft64_GetTs( FILETIME* pft, LPSTR pFmt )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_GetTs
            | _kw_: timestamp, format date, FILETIME, ISO 8601
   }}*/
/*{{|desc: Formats the FILETIME pft as a timestamp string and returns it. When pFmt is NULL the default
      format "%04.4hu-%02.2hu-%02.2hu %02.2hu:%02.2hu:%02.2hu" (YYYY-MM-DD HH:MM:SS) is used. Formatting is
      done with _sprintf_p, whose positional arguments are, in order, year, month, day, hour, minute,
      second and milliseconds. This is the C primitive behind the Xbase++ function ft64_GetTs().
    | params:
    - `pft` FILETIME* - Source FILETIME to format; the function returns NULL when it is NULL.
    - `pFmt` LPSTR - printf-style positional format string; NULL selects the default format above.

    Returns LPSTR - Pointer to a 256-byte buffer allocated with _xgrab holding the formatted timestamp,
      or NULL when pft is NULL.

    |seealso: See also: {{ilink: <c-function ft64_GetTs> ft64_GetTs}}, {{ilink: <c-function ft64_strf> ft64_strf}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
LPSTR OT4XB_API __cdecl ft64_GetTs( FILETIME* pft, LPSTR pFmt)
{
   static char _pFmt_[] = "%04.4hu-%02.2hu-%02.2hu %02.2hu:%02.2hu:%02.2hu";
   LPSTR pTs = 0;
   if( !pft ) return 0;
   if( !pFmt ) pFmt = _pFmt_;
   SYSTEMTIME st;
   ZeroMemory(&st,sizeof( SYSTEMTIME ) );
   if( (pft->dwLowDateTime + pft->dwHighDateTime) != 0) FileTimeToSystemTime(pft,&st);
   pTs = (LPSTR) _xgrab(256);
   _sprintf_p(pTs,256,pFmt,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,0,0,0,0,0,0);
   return pTs;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_GetTs
            | syntax_: `ft64_GetTs( pft [, cFormat [, nFlags]] )`
            | category: date-time/filetime
            | _kw_: timestamp, format date, FILETIME64, ISO 8601
   }}*/
/*{{|desc: Formats a FILETIME64 value as a timestamp string.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.
    - `cFormat` Character - Optional printf-style format. Arguments supplied internally are year, month,
      day, hour, minute, second and millisecond.
    - `nFlags` Numeric - Source and built-in format flags, see below.
    | flags:
    - `1` low nibble - uses the current local time when pft is NIL
    - `2` low nibble - uses the current UTC time when pft is NIL
    - `0x0C00` built-in format YYYYMMDDhhmm (when cFormat is omitted)
    - `0x0E00` built-in format YYYYMMDDhhmmss
    - `0x0F00` the current 15-character compact format
    - `0x1700` built-in format YYYY-MM-DDThh:mm:ss.mmm

    Returns Character/NIL - Formatted timestamp, or NIL when no FILETIME source can be resolved.

    |note: Default format is YYYY-MM-DD hh:mm:ss. }}*/
_XPP_REG_FUN_( FT64_GETTS )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   LPSTR p = 0;
	FILETIME ft_current_local_time;
	DWORD dwFlags = _parLong(pl, 3);
	if (!pft) 
	{ 
		
		switch(dwFlags & 0x0F )
		{
			case 1:
			{
				SYSTEMTIME st;
				GetLocalTime(&st);
				SystemTimeToFileTime(&st, &ft_current_local_time);
				pft = &ft_current_local_time;
				break;
			}
			case 2:
			{
				GetSystemTimeAsFileTime(&ft_current_local_time);
				pft = &ft_current_local_time;
				break;
			}
		}
	}

   if( pft )
   {
      LPSTR pFmt = _pszParam(pl,2);
		LPSTR ppff = pFmt;
		if (!ppff)
		{
			switch (dwFlags & 0xFFFF00)
			{
				case 0x0C00: // 12
				{
					static char _pFmt_[] = "%04.4hu%02.2hu%02.2hu%02.2hu%02.2hu";
					ppff = _pFmt_;
					break;
				}
				case 0x0E00: // 14
				{
					static char _pFmt_[] = "%04.4hu%02.2hu%02.2hu%02.2hu%02.2hu%02.2hu";
					ppff = _pFmt_;
					break;
				}
				case 0x0F00: // 15				
				{
					static char _pFmt_[] = "%04.4hu%02.2hu%02.2hu%02.2hu%02.2hu%03.3hu";
					ppff = _pFmt_;
					break;
				}
				case 0x1700: // 23
				{
					static char _pFmt_[] = "%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu.%03.3hu";
					ppff = _pFmt_;          
					break;
				}
			}
		}

      p = ft64_GetTs(pft,ppff);
      if( pFmt) _xfree( (void*) pFmt);
      _conParamUnLockStrEx(&plk);
   }
   if( p ){ _retc(pl,p); _xfree((void*) p); }
   else { _ret(pl); };
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_ToHttp
            | syntax_: `LPSTR __cdecl ft64_ToHttp( FILETIME* pft )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_ToHttp
            | _kw_: http date, RFC 1123, GMT, Last-Modified, FILETIME
   }}*/
/*{{|desc: Formats the FILETIME pft as an HTTP-style date string of the form "Ddd, DD Mmm YYYY HH:MM:SS"
      (RFC 1123 layout with English day and month abbreviations). This is the C primitive behind the
      Xbase++ function ft64_ToHttp().
    | params:
    - `pft` FILETIME* - Source FILETIME to format; the function returns NULL when it is NULL.

    Returns LPSTR - Newly allocated copy of the formatted string, duplicated with _xstrdup (which uses
      _xgrab), or NULL when pft is NULL.

    |seealso: See also: {{ilink: <c-function ft64_ToHttp> ft64_ToHttp}}, {{ilink: <c-function ft64_GetTs> ft64_GetTs}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
LPSTR OT4XB_API __cdecl ft64_ToHttp( FILETIME* pft)
{
   char buffer[256]; ZeroMemory(buffer,sizeof(buffer));
   if( !pft ) return 0;
   SYSTEMTIME st;
   ZeroMemory(&st,sizeof( SYSTEMTIME ) );
   if( (pft->dwLowDateTime + pft->dwHighDateTime) != 0) FileTimeToSystemTime(pft,&st);
   _sprintf_p( buffer,256,"%s, %02hu %s %4hu %02hu:%02hu:%02hu",s_dt[st.wDayOfWeek],st.wDay,s_mt[(st.wMonth - 1)],
               st.wYear,st.wHour,st.wMinute,st.wSecond );
   return _xstrdup(buffer);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_ToHttp
            | syntax_: `ft64_ToHttp( pft [, nFlags] )`
            | category: date-time/filetime
            | _kw_: http date, RFC 1123, GMT, Last-Modified, FILETIME64
   }}*/
/*{{|desc: Formats a FILETIME64 value as an HTTP date string.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.
    - `nFlags` Numeric - Source flags, see below.
    | flags:
    - `1` low nibble - uses the current local time when pft is NIL
    - `2` low nibble - uses the current UTC time when pft is NIL

    Returns Character/NIL - HTTP-style timestamp, or NIL when no FILETIME source can be resolved. }}*/
_XPP_REG_FUN_( FT64_TOHTTP)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   LPSTR p = 0;
	FILETIME ft_current_local_time;
	if (!pft)
	{
		DWORD dw = _parLong(pl, 2);
		switch (dw & 0x0F)
		{
			case 1:
			{
				SYSTEMTIME st;
				GetLocalTime(&st);
				SystemTimeToFileTime(&st, &ft_current_local_time);
				pft = &ft_current_local_time;
				break;
			}
			case 2:
			{
				GetSystemTimeAsFileTime(&ft_current_local_time);
				pft = &ft_current_local_time;
				break;
			}
		}
	}
   if( pft )
   {
      p = ft64_ToHttp(pft);
      _conParamUnLockStrEx(&plk);
   }
   if( p ){ _retc(pl,p); _xfree((void*) p); }
   else { _ret(pl); };
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_SetDateTime
            | syntax_: `ft64_SetDateTime( pft, dDate, uTime )`
            | category: date-time/filetime
            | _kw_: date and time, FILETIME64, from Xbase++ date
   }}*/
/*{{|desc: Stores an Xbase++ date/time pair into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `dDate` Date/Character/FILETIME64 object - Date value to store, or another FILETIME64-compatible
      value to copy from.
    - `uTime` Character/Numeric - Time as HH:MM:SS.mmm or as seconds after midnight.

    Returns NIL

    |note: The form ft64_SetDateTime( pft, oFileTime ) copies from another FILETIME64-compatible value. }}*/
_XPP_REG_FUN_( FT64_SETDATETIME )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      ULONG nType = _partype(pl,2);
      SYSTEMTIME st;
      ZeroMemory(&st,sizeof( SYSTEMTIME));
      switch( nType & 0xFF )
      {
         case XPP_OBJECT:
         {
            CON_PLKSTREX plk2;
            FILETIME* pft2 = (FILETIME*) _conParamRLockStrEx(pl,2,&plk2);
            if( pft2 )
            {
               FileTimeToSystemTime(pft2,&st);
               _conParamUnLockStrEx(&plk2);
            }
            break;
         }
         case XPP_DATE:
         case XPP_CHARACTER:
         {
            ULONG nt3 = _partype(pl,3);
            BOOL bDateByRef = FALSE;
            ContainerHandle conDate   = _conParam(pl,2,&bDateByRef);
            _conGetDateAsSystemTime(conDate,&st);
            if( !bDateByRef ) _conRelease(conDate);
            if( st.wDay > 0 )
            {
               if( (st.wDay > 0 ) && (nt3 & XPP_CHARACTER ) )
               {
                  char sz[32];
                  ZeroMemory( sz , 32 );
                  _parc(sz,31,pl,3,0);
                  // HH:MM:SS.DDD
                  // 012345678901
                  sz[2] = sz[5] = sz[8] = sz[12] = 0;
                  sz[11] = (sz[11] ? sz[11] : '0'); sz[10] = (sz[10] ? sz[10] : '0'); sz[9] = (sz[9] ? sz[9] : '0');
                  st.wHour         = (WORD) (atoi(sz) & 0x00FF);
                  st.wMinute       = (WORD) (atoi(sz+3) & 0x00FF);
                  st.wSecond       = (WORD) (atoi(sz+6) & 0x00FF);
                  st.wMilliseconds = (WORD) (atoi(sz+9) & 0x0FFF);
               }
               else if( nt3 & XPP_NUMERIC )
               {
                  LONG nl = (LONG) (_parnd(pl,3,0) * 1000.00F);
                  st.wHour   = (WORD) (nl / 3600000 ); nl = (nl % 3600000);
                  st.wMinute = (WORD) (nl / 60000 ); nl = (nl % 60000);
                  st.wSecond = (WORD) (nl / 1000 ); nl = (nl % 1000);
                  st.wMilliseconds = (WORD) nl;
               }
            }
            break;
         }
      }
      SystemTimeToFileTime( &st , pft);
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_GetDateTime
            | syntax_: `ft64_GetDateTime( pft, @dDate, @cTime )`
            | category: date-time/filetime
            | _kw_: date and time, FILETIME64, to Xbase++ date, time string
   }}*/
/*{{|desc: Extracts the date and a time string from a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.
    - `dDate` Date by reference - Receives the Xbase++ date.
    - `cTime` Character by reference - Receives HH:MM:SS.mmm.

    Returns NIL }}*/
_XPP_REG_FUN_( FT64_GETDATETIME )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   SYSTEMTIME st;
   char sz[64];
   ZeroMemory( sz,64);
   ZeroMemory( &st,sizeof(SYSTEMTIME) );
   if( pft )
   {
      if( (pft->dwLowDateTime + pft->dwHighDateTime) != 0){ FileTimeToSystemTime(pft,&st); }
      _conParamUnLockStrEx(&plk);
   }
   wsprintf(sz,"%04.4hu%02.2hu%02.2hu",st.wYear,st.wMonth,st.wDay);
   _stords(sz,pl,2,0);
   wsprintf(sz,"%02.2hu:%02.2hu:%02.2hu.%03.3hu",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
   _storc(sz,pl,3,0);
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_GetDateTimeSec
            | syntax_: `ft64_GetDateTimeSec( pft, @dDate, @nSeconds )`
            | category: date-time/filetime
            | _kw_: date and time, seconds since midnight, FILETIME64
   }}*/
/*{{|desc: Extracts the date and the time as seconds after midnight from a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.
    - `dDate` Date by reference - Receives the Xbase++ date.
    - `nSeconds` Numeric by reference - Receives seconds after midnight, including milliseconds as
      decimals.

    Returns NIL }}*/
_XPP_REG_FUN_( FT64_GETDATETIMESEC )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   SYSTEMTIME st;
   double nds = 0.00F;
   char sz[64];
   ZeroMemory( sz,64);
   ZeroMemory( &st,sizeof(SYSTEMTIME) );
   if( pft )
   {
      double nd;
      if( (pft->dwLowDateTime + pft->dwHighDateTime) != 0)
      {
         FileTimeToSystemTime(pft,&st);
         nd = (double) st.wHour        ; nds  = ( nd * 3600000.00F );
         nd = (double) st.wMinute      ; nds += ( nd *   60000.00F );
         nd = (double) st.wSecond      ; nds += ( nd *    1000.00F );
         nd = (double) st.wMilliseconds; nds += nd;
      }
      _conParamUnLockStrEx(&plk);
   }
   wsprintf(sz,"%04.4hu%02.2hu%02.2hu",st.wYear,st.wMonth,st.wDay);
   _stords(sz,pl,2,0);
   _stornd(nds/1000.00F,pl,3,0);
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Now
            | syntax_: `ft64_Now( pft [, lLocal] )`
            | category: date-time/filetime
            | _kw_: now, current time, UTC, FILETIME64, system time
   }}*/
/*{{|desc: Stores the current time into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `lLocal` Logical - When .T., stores local time. Otherwise stores UTC system time.

    Returns NIL }}*/
_XPP_REG_FUN_( FT64_NOW )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      if( _parl(pl,2,0) ){ SYSTEMTIME st; GetLocalTime( &st ); SystemTimeToFileTime( &st , pft ); }
      else { GetSystemTimeAsFileTime(pft); }
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void elaptime_to_str( TZString & z, LONGLONG t1, LONGLONG t2 )
{
   BOOL minus = ( t1 > t2 ? 1 : 0 );
   LONGLONG td = ( minus ? t1 - t2 : t2 - t1 );
   LONGLONG nn, dw;
   BOOL have_days = FALSE;

   if( td >= 315576000000000LL ) // 10000 * 1000 * 60 * 60 * 24 * 365.25
   {
      nn = ( td - ( td % 315576000000000LL ) ) / 315576000000000LL;
      td = td % 315576000000000LL;
      dw = (DWORD) ( nn & 0xFFFFFFFFLL );
      z.printf( ( minus ? "-%iY/" : "%iY/" ), dw );
      have_days = TRUE;
   }
   if( td >= 864000000000LL || have_days ) // 10000 * 1000 * 60 * 60 * 24
   {
      nn = ( td - ( td % 864000000000LL ) ) / 864000000000LL;
      td = td % 864000000000LL;
      dw = (DWORD) ( nn & 0xFFFFFFFFLL );
      z.printf( ( minus ? "-%iD  " : "%iD  " ), dw );
   }

   dw = 0;
   if( td >= 36000000000LL ) // 10000 * 1000 * 60 * 60 // hours
   {
      nn = ( td - ( td % 36000000000LL ) ) / 36000000000LL;
      td = td % 36000000000LL;
      dw = (DWORD) ( nn & 0xFFFFFFFFLL );
   }
   z.printf( ( minus ? "- %02.2i:" : "%02.2i:" ), dw );

   dw = 0;
   if( td >= 600000000LL ) // 10000 * 1000 * 60 // minutes
   {
      nn = ( td - ( td % 600000000LL ) ) / 600000000LL;
      td = td % 600000000LL;
      dw = (DWORD) ( nn & 0xFFFFFFFFLL );
   }
   z.printf( "%02.2i:", dw );


   dw = 0;
   if( td >= 10000000LL ) // 10000 * 1000  // seconds
   {
      nn = ( td - ( td % 10000000LL ) ) / 10000000LL;
      td = td % 10000000LL;
      dw = (DWORD) ( nn & 0xFFFFFFFFLL );
   }
   z.printf( "%02.2i", dw );
   if( td > 0 )
   {
      dw = 0;
      if( td >= 10000LL ) // 10000  // milliseconds
      {
         nn = ( td - ( td % 10000LL ) ) / 10000LL;
         td = td % 10000LL;
         dw = (DWORD) ( nn & 0xFFFFFFFFLL );
      }
      z.printf( ".%03.3i", dw );
   }
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_ElapMilliSeconds
            | syntax_: `ft64_ElapMilliSeconds( pft [, pft2 [, lLocal [, @cElapsed]]] )`
            | category: date-time/filetime
            | _kw_: elapsed, milliseconds, difference, FILETIME64, timer
   }}*/
/*{{|desc: Returns elapsed milliseconds between two FILETIME64 values.
    | params:
    - `pft` FILETIME64 extended pointer - Start FILETIME storage.
    - `pft2` FILETIME64 extended pointer - End FILETIME storage. When omitted, current UTC or local time is
      used.
    - `lLocal` Logical - When pft2 is omitted, .T. compares against current local time; otherwise UTC is
      used.
    - `cElapsed` Character by reference - Optional elapsed text. When this fourth parameter is supplied,
      the function stores the text and does not return the numeric value.

    Returns Numeric/NIL - Elapsed milliseconds, unless cElapsed is supplied. }}*/
_XPP_REG_FUN_( FT64_ELAPMILLISECONDS)
{
   CON_PLKSTREX plk;
   LONGLONG t1 = 0;
   LONGLONG t2 = 0;
   double nd = 0.00F;
   LONGLONG* pft = (LONGLONG*) _conParamRLockStrEx(pl,1,&plk);
   if( pft ){ t1 = *pft; _conParamUnLockStrEx(&plk);}
   ZeroMemory( &plk, sizeof( CON_PLKSTREX ));
   pft = (LONGLONG*) _conParamRLockStrEx(pl,2,&plk);
   if( pft )
   {
      t2 = *pft; _conParamUnLockStrEx(&plk);
   }
   else
   {
      if( _parl(pl,3,0) )
      {
         SYSTEMTIME st;
         GetLocalTime( &st );
         SystemTimeToFileTime( &st , _mk_ptr_(LPFILETIME,(&t2),0) );
      }
      else
      {
         GetSystemTimeAsFileTime(_mk_ptr_(LPFILETIME,(&t2),0));
      }
   }
   if( _partype( pl,0 ) > 3 )   
   {
      TZString z;
      elaptime_to_str(z, t1, t2 );
      _storclen( z.GetBuffer(), z.len() , pl , 4 , 0);
      return;
   }

   nd = (double) ( (t2 - t1) /10000LL );
   _retnd(pl,nd);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_ElapSeconds
            | syntax_: `ft64_ElapSeconds( pft [, pft2 [, lLocal [, @cElapsed]]] )`
            | category: date-time/filetime
            | _kw_: elapsed, seconds, difference, FILETIME64, timer
   }}*/
/*{{|desc: Returns elapsed seconds between two FILETIME64 values.
    | params:
    - `pft` FILETIME64 extended pointer - Start FILETIME storage.
    - `pft2` FILETIME64 extended pointer - End FILETIME storage. When omitted, current UTC or local time is
      used.
    - `lLocal` Logical - When pft2 is omitted, .T. compares against current local time; otherwise UTC is
      used.
    - `cElapsed` Character by reference - Optional elapsed text. When this fourth parameter is supplied,
      the function stores the text and does not return the numeric value.

    Returns Numeric/NIL - Elapsed seconds, unless cElapsed is supplied. }}*/
_XPP_REG_FUN_( FT64_ELAPSECONDS)
{
   CON_PLKSTREX plk;
   LONGLONG t1 = 0;
   LONGLONG t2 = 0;
   double nd = 0.00F;
   LONGLONG* pft = (LONGLONG*) _conParamRLockStrEx(pl,1,&plk);
   if( pft ){ t1 = *pft; _conParamUnLockStrEx(&plk);}
   ZeroMemory( &plk, sizeof( CON_PLKSTREX ));
   pft = (LONGLONG*) _conParamRLockStrEx(pl,2,&plk);
   if( pft )
   {
      t2 = *pft; _conParamUnLockStrEx(&plk);
   }
   else
   {
      if( _parl(pl,3,0) )
      {
         SYSTEMTIME st;
         GetLocalTime( &st );
         SystemTimeToFileTime( &st , _mk_ptr_(LPFILETIME,(&t2),0) );
      }
      else
      {
         GetSystemTimeAsFileTime(_mk_ptr_(LPFILETIME,(&t2),0));
      }
   }
   if( _partype( pl, 0 ) > 3 )
   {
      TZString z;
      elaptime_to_str( z, t1, t2 );
      _storclen( z.GetBuffer(), z.len(), pl, 4, 0 );
      return;
   }
   nd = (double) ( (t2 - t1) /10000000LL );
   _retnd(pl,nd);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Compare
            | syntax_: `ft64_Compare( pft, pft2 [, nFlags] )`
            | category: date-time/filetime
            | _kw_: compare, FILETIME64, before after, sort dates
   }}*/
/*{{|desc: Compares two FILETIME64 values.
    | params:
    - `pft` FILETIME64 extended pointer - First FILETIME storage.
    - `pft2` FILETIME64 extended pointer - Second FILETIME storage.
    - `nFlags` Numeric - With pft2 omitted, selects the comparison against now, see below.
    | flags:
    - `1` with pft2 omitted, compares pft with the current UTC time and returns a logical value
    - `2` with pft2 omitted, compares pft with the current local time and returns a logical value

    Returns Numeric/Logical/NIL - With two FILETIME values, 0 when equal, 1 when pft is earlier than pft2, and
      -1 when pft is later than pft2. With flags 1 or 2 and no pft2, whether pft is before or equal to now. }}*/
_XPP_REG_FUN_( FT64_COMPARE)
{
   CON_PLKSTREX plk;
   LONGLONG t1 = 0;
   LONGLONG t2 = 0;
   ContainerHandle conr = _conNew(NULLCONTAINER);
   LONGLONG* pft = (LONGLONG*) _conParamRLockStrEx(pl,1,&plk);
   if( pft ){ t1 = *pft; _conParamUnLockStrEx(&plk);}
   ZeroMemory( &plk, sizeof( CON_PLKSTREX ));
   pft = (LONGLONG*) _conParamRLockStrEx(pl,2,&plk);
   if( pft )
   {
      t2 = *pft; _conParamUnLockStrEx(&plk);
      _conPutNL(conr, ( t1 == t2 ? 0 : ( t1 > t2 ? -1 : 1) ) );

   }
   else
   {
      switch( _parLong(pl,3,0) & 3 )
      {
         case 1:
         {
            GetSystemTimeAsFileTime((FILETIME*) &t2);
            _conPutL(conr,  ( (t1 <= t2) ? 1 : 0 ) );
            break;
         }
         case 2:
         {
            SYSTEMTIME st; 
            GetLocalTime( &st ); 
            SystemTimeToFileTime( &st , (FILETIME*) &t2 );
            _conPutL(conr,  ( (t1 <= t2) ? 1 : 0 ) );
            break;
         }         
      }
   }
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Add
            | syntax_: `ft64_Add( pft, nMilliseconds [, nMultiplier] )`
            | category: date-time/filetime
            | _kw_: add milliseconds, offset, FILETIME64, date arithmetic
   }}*/
/*{{|desc: Adds a millisecond-based offset to a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - FILETIME storage to modify.
    - `nMilliseconds` Numeric - Base offset in milliseconds.
    - `nMultiplier` Numeric - Optional multiplier. Default is 1.

    Returns NIL

    |note: FILETIME stores 100-nanosecond ticks. This function converts nMilliseconds to FILETIME ticks and
      then applies the optional multiplier. }}*/
_XPP_REG_FUN_( FT64_ADD )
{
   CON_PLKSTREX plk;
   LONGLONG* pft = (LONGLONG*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      LONGLONG  n   = _parLong64(pl,2,0) * 10000LL;
      LONGLONG  m   = ( (_partype(pl,3) & XPP_NUMERIC) ? _parLong64(pl,3,0) : 1LL );
      *pft = (*pft) + ( n * m );
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_now
            | syntax_: `BOOL __cdecl ft64_now( FILETIME* pft )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_now
            | _kw_: now, current time, UTC, FILETIME, GetSystemTimePreciseAsFileTime
   }}*/
/*{{|desc: Stores the current UTC time into the FILETIME pft. On the first call it resolves
      GetSystemTimePreciseAsFileTime from kernel32 and uses it when available, falling back to
      GetSystemTimeAsFileTime otherwise. This is the C primitive behind the Xbase++ function ft64_Now().
    | params:
    - `pft` FILETIME* - Destination FILETIME that receives the current UTC time.

    Returns BOOL - TRUE when the high-resolution GetSystemTimePreciseAsFileTime was used, FALSE when the
      standard GetSystemTimeAsFileTime was used instead.

    |seealso: See also: {{ilink: <function ft64_Now> ft64_Now}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
BOOL  OT4XB_API __cdecl ft64_now(FILETIME* pft)
{
	static _PFN_GetSystemTimeAsFileTime fp = 0;
	static BOOL bPrecise = FALSE;
	if (!fp)
	{
      HMODULE hKernel32 = GetModuleHandleA( "kernel32" );
      if(! hKernel32 )  // no way hKernel32 == NULL GetModuleHandleA is inside kernel32 :-) but just to avoid the warning 
      {
         return FALSE;
      }
      fp = (_PFN_GetSystemTimeAsFileTime) GetProcAddress( hKernel32, "GetSystemTimePreciseAsFileTime" );
      
      if( fp )
      {
			bPrecise = TRUE;
		}
		else
		{
         fp = (_PFN_GetSystemTimeAsFileTime) GetSystemTimeAsFileTime;
		}
	}
	(*fp)(pft);
	return bPrecise;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_AddYears
            | syntax_: `void __cdecl ft64_AddYears( FILETIME* pft, LONG y )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_AddYears
            | _kw_: add years, FILETIME, date arithmetic, leap year
   }}*/
/*{{|desc: Adds y years to the FILETIME pft in place. If the source date is February 29 and the target
      year is not a leap year, the day is clamped to February 28. This is the C primitive behind the
      Xbase++ function ft64_Add_Y().
    | params:
    - `pft` FILETIME* - FILETIME to modify in place; y may be negative to subtract years.
    - `y` LONG - Number of years to add (or subtract when negative).

    Returns void

    |seealso: See also: {{ilink: <function ft64_Add_Y> ft64_Add_Y}}, {{ilink: <c-function ft64_AddMonths> ft64_AddMonths}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_AddYears( FILETIME* pft, LONG y )
{
   SYSTEMTIME st;
   ZeroMemory(&st,sizeof(SYSTEMTIME));
   FileTimeToSystemTime(pft,&st);
   y += ((LONG) st.wYear);
   st.wYear = LOWORD(y);
   if( (st.wMonth == 2) && (st.wDay == 29 ) && ( st.wYear & 3 ) ){ st.wDay = 28; } // Leap Adjust
   SystemTimeToFileTime(&st,pft);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_AddMonths
            | syntax_: `void __cdecl ft64_AddMonths( FILETIME* pft, LONG m )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_AddMonths
            | _kw_: add months, FILETIME, date arithmetic
   }}*/
/*{{|desc: Adds m months to the FILETIME pft in place, carrying whole years and normalizing the month to
      the 1..12 range. When the resulting month has fewer days than the original day, the day is clamped to
      the last valid day (28/29 for February, 30 for 30-day months). This is the C primitive behind the
      Xbase++ function ft64_Add_M().
    | params:
    - `pft` FILETIME* - FILETIME to modify in place; m may be negative to subtract months.
    - `m` LONG - Number of months to add (or subtract when negative).

    Returns void

    |seealso: See also: {{ilink: <function ft64_Add_M> ft64_Add_M}}, {{ilink: <c-function ft64_AddYears> ft64_AddYears}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_AddMonths( FILETIME* pft, LONG m )
{
   SYSTEMTIME st;
   LONG y = (m / 12 );
   m -= ( y * 12 );
   ZeroMemory(&st,sizeof(SYSTEMTIME));
   FileTimeToSystemTime(pft,&st);
   m += ((LONG) st.wMonth);
   y += ((LONG) st.wYear );
   if( m > 12 ){ y = (y+1); m = (m-12);}
   if( m < 1  ){ y = (y-1); m = (m+12);}
   st.wMonth = LOWORD(m);
   st.wYear  = LOWORD(y);
   if( (st.wMonth == 2) && (st.wDay > 28 ) )
   {
      // Leap Adjust
      st.wDay = ((st.wYear & 3) ? 28 : 29 );
   }
   else if( (st.wDay == 31 ) && ((st.wMonth == 4) ||(st.wMonth == 6) ||(st.wMonth == 9) ||(st.wMonth == 11)) )
   {
      st.wDay = 30;
   }
   SystemTimeToFileTime(&st,pft);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Add_Y
            | syntax_: `ft64_Add_Y( pft, nYears )`
            | category: date-time/filetime
            | _kw_: add years, FILETIME64, date arithmetic
   }}*/
/*{{|desc: Adds years to a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - FILETIME storage to modify.
    - `nYears` Numeric - Number of years to add. Negative values move backwards.

    Returns NIL

    |note: February 29 is adjusted to February 28 when the target year is not leap. }}*/
_XPP_REG_FUN_( FT64_ADD_Y )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      ft64_AddYears(pft, _parLong(pl,2,0));
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Add_M
            | syntax_: `ft64_Add_M( pft, nMonths )`
            | category: date-time/filetime
            | _kw_: add months, FILETIME64, date arithmetic
   }}*/
/*{{|desc: Adds months to a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - FILETIME storage to modify.
    - `nMonths` Numeric - Number of months to add. Negative values move backwards.

    Returns NIL

    |note: End-of-month dates are adjusted when the target month has fewer days. }}*/
_XPP_REG_FUN_( FT64_ADD_M )
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      ft64_AddMonths(pft, _parLong(pl,2,0));
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_To_DosDateTime
            | syntax_: `ft64_To_DosDateTime( pft )`
            | category: date-time/filetime
            | _kw_: DOS date, FAT time, zip timestamp, FileTimeToDosDateTime
   }}*/
/*{{|desc: Converts a FILETIME64 value to a DOS FAT date/time DWORD.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.

    Returns Numeric/NIL - DOS date/time value, or NIL if conversion fails. }}*/
_XPP_REG_FUN_( FT64_TO_DOSDATETIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pft )
   {
      WORD wd = 0;
      WORD wt = 0;
      if( FileTimeToDosDateTime(pft,&wd,&wt) ){ _conPutNL(conr,MAKELONG(wt,wd)); }
      _conParamUnLockStrEx(&plk);
   }
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_From_DosDateTime
            | syntax_: `ft64_From_DosDateTime( pft, nDosDateTime )`
            | category: date-time/filetime
            | _kw_: DOS date, FAT time, zip timestamp, DosDateTimeToFileTime
   }}*/
/*{{|desc: Stores a DOS FAT date/time DWORD into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `nDosDateTime` Numeric - DOS FAT date/time value.

    Returns Logical - .T. when the value was converted; otherwise .F. }}*/
_XPP_REG_FUN_( FT64_FROM_DOSDATETIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   BOOL bOk = FALSE;
   if( pft )
   {
      LONG ddt = _parLong(pl,2,0);
      bOk = DosDateTimeToFileTime( HIWORD(ddt),LOWORD(ddt),pft );
      _conParamUnLockStrEx(&plk);
   }
   _retl(pl,bOk);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_SetUnixTime
            | syntax_: `void __cdecl ft64_SetUnixTime( FILETIME* pft, DWORD ut )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_SetUnixTime
            | _kw_: unix time, epoch, time_t, 1970, FILETIME
   }}*/
/*{{|desc: Stores the Unix time ut (seconds elapsed since 1970-01-01 UTC) into the FILETIME pft,
      converting to the FILETIME scale (100-nanosecond ticks since 1601-01-01) with the standard
      116444736000000000 epoch offset. This is the C primitive behind the Xbase++ function
      ft64_From_UnixTime().
    | params:
    - `pft` FILETIME* - Destination FILETIME; must be a valid non-NULL pointer.
    - `ut` DWORD - Unix time in seconds (32-bit).

    Returns void

    |seealso: See also: {{ilink: <function ft64_From_UnixTime> ft64_From_UnixTime}}, {{ilink: <c-function ft64_GetUnixTime> ft64_GetUnixTime}}, {{ilink: <c-function ft64_SetUnixTime64> ft64_SetUnixTime64}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_SetUnixTime( FILETIME* pft, DWORD ut )
{
   reinterpret_cast<LONGLONG*>(pft)[0] = Int32x32To64(ut,10000000L) + 116444736000000000LL;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_GetUnixTime
            | syntax_: `DWORD __cdecl ft64_GetUnixTime( FILETIME* pft )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_GetUnixTime
            | _kw_: unix time, epoch, time_t, 1970, FILETIME
   }}*/
/*{{|desc: Returns the Unix time (seconds since 1970-01-01 UTC) held in the FILETIME pft, converting from
      the FILETIME scale by removing the 116444736000000000 epoch offset and dividing by 10000000. The
      result is truncated to 32 bits. This is the C primitive behind the Xbase++ function ft64_To_UnixTime().
    | params:
    - `pft` FILETIME* - Source FILETIME; must be a valid non-NULL pointer.

    Returns DWORD - Unix time in seconds, truncated to 32 bits.

    |seealso: See also: {{ilink: <function ft64_To_UnixTime> ft64_To_UnixTime}}, {{ilink: <c-function ft64_SetUnixTime> ft64_SetUnixTime}}, {{ilink: <c-function ft64_GetUnixTime64> ft64_GetUnixTime64}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
DWORD OT4XB_API __cdecl ft64_GetUnixTime( FILETIME* pft)
{
   LONGLONG ll = reinterpret_cast<LONGLONG*>(pft)[0];
   return (DWORD) (((LONGLONG) ((ll - 116444736000000000LL) / 10000000LL)) & 0xFFFFFFFFLL);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_To_UnixTime
            | syntax_: `ft64_To_UnixTime( pft )`
            | category: date-time/filetime
            | _kw_: unix time, epoch, time_t, 1970, FILETIME64
   }}*/
/*{{|desc: Converts a FILETIME64 value to a 32-bit Unix timestamp.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.

    Returns Numeric/NIL - Unix time in seconds. Values are returned using the 32-bit numeric representation
      available to Xbase++. }}*/
_XPP_REG_FUN_( FT64_TO_UNIXTIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pft )
   {
      _conPutNL(conr,(LONG) ft64_GetUnixTime(pft) );
      _conParamUnLockStrEx(&plk);
   }
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_From_UnixTime
            | syntax_: `ft64_From_UnixTime( pft, nUnixTime )`
            | category: date-time/filetime
            | _kw_: unix time, epoch, time_t, 1970, FILETIME64
   }}*/
/*{{|desc: Stores a 32-bit Unix timestamp into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `nUnixTime` Numeric - Unix time in seconds.

    Returns NIL }}*/
_XPP_REG_FUN_( FT64_FROM_UNIXTIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      ft64_SetUnixTime(pft,(DWORD)_parLong(pl,2,0));
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_SetUnixTime64
            | syntax_: `void __cdecl ft64_SetUnixTime64( FILETIME* pft, LONGLONG ut )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_SetUnixTime64
            | _kw_: unix time, epoch, 64-bit, time_t, FILETIME
   }}*/
/*{{|desc: Stores the 64-bit Unix time ut (seconds since 1970-01-01 UTC) into the FILETIME pft, converting
      to the FILETIME scale (100-nanosecond ticks since 1601-01-01) with the 116444736000000000 epoch
      offset. Same as ft64_SetUnixTime but accepts a 64-bit seconds value, so it is not limited to the
      year 2106. C-only; there is no Xbase++ wrapper.
    | params:
    - `pft` FILETIME* - Destination FILETIME; must be a valid non-NULL pointer.
    - `ut` LONGLONG - Unix time in seconds (64-bit).

    Returns void

    |seealso: See also: {{ilink: <c-function ft64_SetUnixTime> ft64_SetUnixTime}}, {{ilink: <c-function ft64_GetUnixTime64> ft64_GetUnixTime64}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_SetUnixTime64( FILETIME* pft, LONGLONG ut )
{
   reinterpret_cast<LONGLONG*>(pft)[0] = (ut * 10000000LL) + 116444736000000000LL;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_GetUnixTime64
            | syntax_: `LONGLONG __cdecl ft64_GetUnixTime64( FILETIME* pft )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_GetUnixTime64
            | _kw_: unix time, epoch, 64-bit, time_t, FILETIME
   }}*/
/*{{|desc: Returns the 64-bit Unix time (seconds since 1970-01-01 UTC) held in the FILETIME pft, converting
      from the FILETIME scale by removing the 116444736000000000 epoch offset and dividing by 10000000.
      Same as ft64_GetUnixTime but returns a full 64-bit result. C-only; there is no Xbase++ wrapper.
    | params:
    - `pft` FILETIME* - Source FILETIME; must be a valid non-NULL pointer.

    Returns LONGLONG - Unix time in seconds (64-bit).

    |seealso: See also: {{ilink: <c-function ft64_GetUnixTime> ft64_GetUnixTime}}, {{ilink: <c-function ft64_SetUnixTime64> ft64_SetUnixTime64}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
LONGLONG OT4XB_API __cdecl ft64_GetUnixTime64( FILETIME* pft)
{
   LONGLONG ll = reinterpret_cast<LONGLONG*>(pft)[0];
   return ( (ll - 116444736000000000LL) / 10000000LL );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_To_ExcelTime
            | syntax_: `ft64_To_ExcelTime( pft )`
            | category: date-time/filetime
            | _kw_: excel date, serial date, OLE date, FILETIME64
   }}*/
/*{{|desc: Converts a FILETIME64 value to an Excel serial date/time number.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.

    Returns Numeric/NIL - Excel serial date/time value. }}*/
_XPP_REG_FUN_( FT64_TO_EXCELTIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamRLockStrEx(pl,1,&plk);
   ContainerHandle conr = _conNew(NULLCONTAINER);
   if( pft )
   {
      LONGLONG ll = ft64_GetUnixTime64(pft);
      if( ll == 0LL ){ _conPutNL(conr,25569); }
      else  { _conPutND(conr,  ((((double) ll )/86400.00) +25569.00) ); }
      _conParamUnLockStrEx(&plk);
   }
   _conReturn(pl,conr);
   _conRelease(conr);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_From_ExcelTime
            | syntax_: `ft64_From_ExcelTime( pft, nExcelTime )`
            | category: date-time/filetime
            | _kw_: excel date, serial date, OLE date, FILETIME64
   }}*/
/*{{|desc: Stores an Excel serial date/time number into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `nExcelTime` Numeric - Excel serial date/time value.

    Returns NIL }}*/
_XPP_REG_FUN_( FT64_FROM_EXCELTIME)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      double nd = ((_parnd(pl,2,0) - 25569.00 ) * 86400.00 );
      ft64_SetUnixTime64(pft,(LONGLONG) nd );
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: FILETIME64
            | _slug_: filetime64
            | class-function: FILETIME64
            | parent: {{ilink: <class gwst> gwst}}
            | category: date-time/filetime
            | desc: GWST wrapper over the WinAPI FILETIME structure, with helper properties and methods for timestamp
              parsing, formatting, arithmetic and common time representations.
            | note: FILETIME64 uses the normal GWST storage model. Mutating helper methods generally return Self so
              calls can be chained; methods that only read the value return the requested value.
            | note: The class is named FILETIME64 instead of FileTime to avoid a name conflict with the FileTime
              function/class name used by Alaska XbTools.
   | _kw_: FILETIME, timestamp, date time, UTC, 64-bit time, structure
   }}*/
XPPRET XPPENTRY wapist_FILETIME64( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("FILETIME64");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("FILETIME64");
      pc->GwstParent();
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      /*{{|:**BEGIN STRUCTURE  FILETIME64** }}*/
      /*{{|member_: - MEMBER DWORD dwLowDateTime | desc_: The low-order part of the file time. }}*/
      pc->Member_DWord( "dwLowDateTime" );
      /*{{|member_: - MEMBER DWORD dwHighDateTime | desc_: The high-order part of the file time. }}*/
      pc->Member_DWord("dwHighDateTime");
      // ---------------------------
      pc->GwstSetOffset(0);
      /*{{|member_: - MEMBER uint64 qft  
               | desc_: int64 representing the same file time, for high values Xbase++ represent as a double. This is an inline union  with offset 0
      }}*/
      pc->Member_DWord64("qft");
      // ---------------------------
      /*{{|:**More Methods and Properties** }}*/
      
      /*{{|method_: - METHOD SetTimeStamp( cTimeStamp , [@nShift] , [nFlags] )
               | return: Self
               | desc_: Stores a timestamp string, a FILETIME64 object or now, by flags.
      }}*/
      pc->MethodCB("SetTimeStamp","{|s,c,sh,flags| ft64_SetTs(s,c,@sh,flags),s}");
      /*{{|method_: - METHOD _GetTimeStamp_( [cFormat] )
               | return: Character
               | desc_: Formats the value with a printf-style format.
      }}*/
      pc->MethodCB("_GetTimeStamp_","{|s,f| ft64_GetTs(s,f)}");
      /*{{|method_: - METHOD GetTimeStamp()
               | return: Character
               | desc_: Returns YYYY-MM-DD hh:mm:ss (the default format).
      }}*/
      pc->MethodCB("GetTimeStamp","{|s| ft64_GetTs(s)}");
      /*{{|method_: - METHOD strf( cFormat , [cLocale] )
               | return: Character
               | desc_: Formats the value with the C runtime strftime() formatter.
      }}*/
      pc->MethodCB("strf","{|s,fmt,locale| FT64_STRF(s,fmt,locale)}");
      
      /*{{|method_: - METHOD GetTimeStamp19()
               | return: Character
               | desc_: Returns YYYY-MM-DD hh:mm:ss, 19 characters (same as GetTimeStamp).
      }}*/
      pc->MethodCB("GetTimeStamp19","{|s| ft64_GetTs(s)}");
      /*{{|method_: - METHOD GetTimeStamp14()
               | return: Character
               | desc_: Returns YYYYMMDDhhmmss, 14 characters (fixed format).
      }}*/
      pc->MethodCB("GetTimeStamp14","{|s| ft64_GetTs(s,'%04.4hu%02.2hu%02.2hu%02.2hu%02.2hu%02.2hu')}");
      /*{{|method_: - METHOD GetIso8601()
               | return: Character
               | desc_: Returns YYYY-MM-DDThh:mm:ss (fixed format).
      }}*/
      pc->MethodCB("GetIso8601","{|s| ft64_GetTs(s,'%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu')}");
      /*{{|method_: - METHOD json_escape_self()
               | return: Character
               | desc_: Returns the value as a double-quoted JSON string, YYYY-MM-DDThh:mm:ss.mmm followed by
                 tls():json_timezone when present.
      }}*/
      pc->MethodCB("json_escape_self","{|s| '\"' + ft64_GetTs(s,'%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu.%03.3hu') + __vstr(tls():json_timezone,'') +  '\"' }");

      /*{{|property_: - PROPERTY cTimeStamp
               | type: Character
               | desc_: Read/write. The value as YYYY-MM-DD hh:mm:ss (ft64_GetTs); assigning a timestamp string parses it
                 (ft64_SetTs).
      }}*/
      pc->PropertyCB("cTimeStamp","{|s,v| iif(PCount() > 1,ft64_SetTs(s,v),ft64_GetTs(s))}");
      
      /*{{|method_: - METHOD SetDateTime( dDate , [uTime] )
               | return: Self
               | desc_: Stores an Xbase++ date/time pair.
      }}*/
      pc->MethodCB("SetDateTime","{|s,d,t| ft64_SetDateTime(s,d,t),s}");
      /*{{|method_: - METHOD GetDateTime( @dDate , @cTime )
               | return: Self
               | desc_: Extracts the date and a time string.
      }}*/
      pc->MethodCB("GetDateTime","{|s,d,t| ft64_GetDateTime(s,@d,@t),s}");
      /*{{|method_: - METHOD GetDateTimeSec( @dDate , @nSeconds )
               | return: Self
               | desc_: Extracts the date and the time as seconds after midnight.
      }}*/
      pc->MethodCB("GetDateTimeSec","{|s,d,t| ft64_GetDateTimeSec(s,@d,@t),s}");
      /*{{|method_: - METHOD Now( [lLocal] )
               | return: Self
               | desc_: Stores the current time, UTC or local.
      }}*/
      pc->MethodCB("Now","{|s,lLocal| ft64_Now(s,lLocal),s}");
      /*{{|method_: - METHOD NowL()
               | return: Self
               | desc_: Stores the current local time (lLocal = .T.).
      }}*/
      pc->MethodCB("NowL","{|s| ft64_Now(s,.T.),s}");
      /*{{|method_: - METHOD ElapMilliSeconds( [pft2] , [lLocal] )
               | return: Numeric
               | desc_: Elapsed milliseconds from this value to pft2, or to now.
      }}*/
      pc->MethodCB("ElapMilliSeconds","{|s,t2,lLocal| ft64_ElapMilliSeconds(s,t2,lLocal)}");
      /*{{|method_: - METHOD ElapMilliSecondsL( [pft2] )
               | return: Numeric
               | desc_: Elapsed milliseconds against local time when pft2 is omitted (lLocal = .T.).
      }}*/
      pc->MethodCB("ElapMilliSecondsL","{|s,t2| ft64_ElapMilliSeconds(s,t2,.T.)}");
      /*{{|method_: - METHOD ElapTimeStr( [pft2] , [lLocal] )
               | return: Character
               | desc_: Elapsed time as text (the cElapsed output).
      }}*/
      pc->MethodCB( "ElapTimeStr", "{|s,t2,lLocal,ts| ft64_ElapMilliSeconds(s,t2,lLocal,@ts) , ts}" );
      /*{{|method_: - METHOD ElapSeconds( [pft2] , [lLocal] )
               | return: Numeric
               | desc_: Elapsed seconds from this value to pft2, or to now.
      }}*/
      pc->MethodCB("ElapSeconds","{|s,t2,lLocal| ft64_ElapSeconds(s,t2,lLocal)}");
      /*{{|method_: - METHOD ElapSecondsL( [pft2] )
               | return: Numeric
               | desc_: Elapsed seconds against local time when pft2 is omitted (lLocal = .T.).
      }}*/
      pc->MethodCB("ElapSecondsL","{|s,t2| ft64_ElapSeconds(s,t2,.T.)}");
      /*{{|method_: - METHOD Compare( pft2 )
               | return: Numeric
               | desc_: 0 when equal, 1 when this value is earlier than pft2, -1 when it is later.
      }}*/
      pc->MethodCB("Compare","{|s,t2| ft64_Compare(s,t2)}");
      // ---------------------------
      /*{{|method_: - METHOD SETRFC822( cRfc822 , [@nShift] )
               | return: Self
               | desc_: Stores an RFC822 timestamp string.
      }}*/
      pc->MethodCB("SETRFC822","{|s,c,sh| ft64_SetRfc822Date(s,c,@sh),s}");
      // ---------------------------
      /*{{|method_: - METHOD Day() | return: Numeric | desc_: Day of month of the stored date (Day() over dDate). }}*/
      pc->MethodCB("Day","{|s| Day(s:dDate)}");
      /*{{|method_: - METHOD Month()
               | return: Numeric
               | desc_: Month number of the stored date (Month() over dDate).
      }}*/
      pc->MethodCB("Month","{|s| Month(s:dDate)}");
      /*{{|method_: - METHOD Year() | return: Numeric | desc_: Year of the stored date (Year() over dDate). }}*/
      pc->MethodCB("Year","{|s| Year(s:dDate)}");
      /*{{|property_: - PROPERTY dDate
               | type: Date
               | desc_: Read/write. The date component as an Xbase++ date (GetDateTime); assigning stores the date
                 (SetDateTime with no time).
      }}*/
      pc->PropertyCB("dDate","{|s,v| iif(PCount() > 1, s:SetDateTime(v) ,s:GetDateTime(@v)),v}");
      /*{{|property_: - PROPERTY cTime
               | type: Character
               | desc_: Read/write. The time component as HH:MM:SS.mmm (GetDateTime); assigning stores the time
                 (SetDateTime with no date).
      }}*/
      pc->PropertyCB("cTime","{|s,v| iif(PCount() > 1, s:SetDateTime(,v) ,s:GetDateTime(,@v)),v}");
      /*{{|property_: - PROPERTY nTime
               | type: Numeric
               | desc_: Read/write. The time component as seconds after midnight, milliseconds as decimals
                 (GetDateTimeSec); assigning stores the time (SetDateTime with no date).
      }}*/
      pc->PropertyCB("nTime","{|s,v| iif(PCount() > 1, s:SetDateTime(,v) ,s:GetDateTimeSec(,@v)),v}");
      // ---------------------------
      /*{{|method_: - METHOD AddMilliSeconds( nMilliseconds )
               | return: Self
               | desc_: Adds milliseconds (multiplier 1).
      }}*/
      pc->MethodCB("AddMilliSeconds","{|s,n| ft64_Add(s,n,1),s}");
      /*{{|method_: - METHOD AddSeconds( nSeconds )
               | return: Self
               | desc_: Adds seconds (multiplier 1000).
               | param nSeconds: Numeric - Offset in seconds.
      }}*/
      pc->MethodCB("AddSeconds","{|s,n| ft64_Add(s,n,1000),s}");
      /*{{|method_: - METHOD AddMinutes( nMinutes )
               | return: Self
               | desc_: Adds minutes (multiplier 60000).
               | param nMinutes: Numeric - Offset in minutes.
      }}*/
      pc->MethodCB("AddMinutes","{|s,n| ft64_Add(s,n,60000),s}");
      /*{{|method_: - METHOD AddHours( nHours )
               | return: Self
               | desc_: Adds hours (multiplier 3600000).
               | param nHours: Numeric - Offset in hours.
      }}*/
      pc->MethodCB("AddHours","{|s,n| ft64_Add(s,n,3600000),s}");
      /*{{|method_: - METHOD AddDays( nDays )
               | return: Self
               | desc_: Adds days (multiplier 86400000).
               | param nDays: Numeric - Offset in days.
      }}*/
      pc->MethodCB("AddDays","{|s,n| ft64_Add(s,n,86400000),s}");
      // ---------------------------
      /*{{|method_: - METHOD AddMonths( nMonths ) | return: Self | desc_: Adds months. }}*/
      pc->MethodCB("AddMonths","{|s,n| Ft64_Add_M(s,n),s}");
      /*{{|method_: - METHOD AddYears( nYears ) | return: Self | desc_: Adds years. }}*/
      pc->MethodCB("AddYears","{|s,n| Ft64_Add_Y(s,n),s}");
      // ---------------------------
      /*{{|property_: - PROPERTY cHexTs
               | type: Character
               | desc_: Read/write. The 64-bit FILETIME value as a hexadecimal string (GetHexTs); assigning stores it
                 (SetHexTs).
      }}*/
      pc->PropertyCB("cHexTs","{|s,v| iif(PCount() > 1, s:SetHexTs(v) ,s:GetHexTs())}");
      /*{{|method_: - METHOD SetHexTs( cHex )
               | return: NIL
               | desc_: Stores a 64-bit FILETIME value given as a hexadecimal string (nHex2Qw + PokeStr); non-character
                 values are ignored.
               | param cHex: Character - Hexadecimal representation of the 64-bit value.
      }}*/
      pc->MethodCB("SetHexTs" , "{|s,v| iif( ValType(v) =='C',PokeStr(s,0,nHex2Qw(v)),),NIL }");
      /*{{|method_: - METHOD GetHexTs()
               | return: Character
               | desc_: Returns the 64-bit FILETIME value as a hexadecimal string (cQw2Hex over qft).
      }}*/
      pc->MethodCB("GetHexTs" , "{|s,v| cQw2Hex( s:qft ) }");
      // ---------------------------
      /*{{|method_: - METHOD SetDosDateTime( nDosDateTime )
               | return: Self
               | desc_: Stores a DOS FAT date/time DWORD.
      }}*/
      pc->MethodCB("SetDosDateTime","{|s,v| Ft64_From_DosDateTime(s,v),s}");
      /*{{|method_: - METHOD GetDosDateTime()
               | return: Numeric
               | desc_: Returns the value as a DOS FAT date/time DWORD.
      }}*/
      pc->MethodCB("GetDosDateTime","{|s| Ft64_To_DosDateTime(s)}");
       /*{{|property_: - PROPERTY nDosDateTime
                | type: Numeric
                | desc_: Read/write. The value as a DOS FAT date/time DWORD (ft64_To_DosDateTime /
                  ft64_From_DosDateTime).
       }}*/
       pc->PropertyCB("nDosDateTime","{|s,v| iif(PCount() > 1,Ft64_From_DosDateTime(s,v),Ft64_To_DosDateTime(s))}");
      // ---------------------------
      /*{{|method_: - METHOD SetUnixTime( nUnixTime )
               | return: Self
               | desc_: Stores a 32-bit Unix timestamp.
      }}*/
      pc->MethodCB("SetUnixTime","{|s,v| Ft64_From_UnixTime(s,v),s}");
      /*{{|method_: - METHOD GetUnixTime()
               | return: Numeric
               | desc_: Returns the value as a 32-bit Unix timestamp in seconds.
      }}*/
      pc->MethodCB("GetUnixTime","{|s| Ft64_To_UnixTime(s)}");
      /*{{|property_: - PROPERTY nUnixTime
               | type: Numeric
               | desc_: Read/write. The value as a 32-bit Unix timestamp in seconds (ft64_To_UnixTime /
                 ft64_From_UnixTime).
      }}*/
      pc->PropertyCB("nUnixTime","{|s,v| iif(PCount() > 1,Ft64_From_UnixTime(s,v),Ft64_To_UnixTime(s))}");
      // ---------------------------
      /*{{|method_: - METHOD SetExcelTime( nExcelTime )
               | return: Self
               | desc_: Stores an Excel serial date/time number.
      }}*/
      pc->MethodCB("SetExcelTime","{|s,v| Ft64_From_ExcelTime(s,v),s}");
      /*{{|method_: - METHOD GetExcelTime()
               | return: Numeric
               | desc_: Returns the value as an Excel serial date/time number.
      }}*/
      pc->MethodCB("GetExcelTime","{|s| Ft64_To_ExcelTime(s)}");
      /*{{|property_: - PROPERTY nExcelTime
               | type: Numeric
               | desc_: Read/write. The value as an Excel serial date/time number (ft64_To_ExcelTime /
                 ft64_From_ExcelTime).
      }}*/
      pc->PropertyCB("nExcelTime","{|s,v| iif(PCount() > 1,Ft64_From_ExcelTime(s,v),Ft64_To_ExcelTime(s))}");
      // ---------------------------
      /*{{|method_: - METHOD ToHttp()
               | return: Character
               | desc_: Returns the value as an HTTP date string.
      }}*/
      pc->MethodCB("ToHttp","{|s| Ft64_ToHttp(s)}");
      // ---------------------------      
      /*{{|method_: - METHOD ToLocalTime()
               | return: NIL
               | desc_: Converts the stored UTC value to local time in place.
      }}*/
      pc->MethodCB("ToLocalTime","{|s| FT64_TOLOCALTIME(s)}");
      // ---------------------------
      /*{{|method_: - METHOD SetCkf32Ts( cCkf32Ts )
               | return: Self
               | desc_: Stores a CKF32 timestamp string.
      }}*/
      pc->MethodCB( "SetCkf32Ts", "{|s,v| Ft64_Set_Ckf32Ts(s,v),s}" );
      /*{{|method_: - METHOD GetCkf32Ts()
               | return: Character
               | desc_: Returns the value encoded as a CKF32 timestamp string.
      }}*/
      pc->MethodCB( "GetCkf32Ts", "{|s| Ft64_Get_Ckf32Ts(s)}" );
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
   /*{{|:**END STRUCTURE** }}*/
}
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: dt2iso8601
            | syntax_: `dt2iso8601( dDate, uTime )`
            | category: date-time/filetime
            | _kw_: ISO 8601, format date, timestamp, date time string
   }}*/
/*{{|desc: Formats an Xbase++ date/time pair as an ISO 8601 timestamp.
    | params:
    - `dDate` Date - Xbase++ date value.
    - `uTime` Character/Numeric - Time value accepted by OT4XB date/time conversion helpers.

    Returns Character - Timestamp in YYYY-MM-DDThh:mm:ss format, or an empty string when the date is invalid. }}*/
_XPP_REG_FUN_( DT2ISO8601 )
{
   TXppParamList xpp(pl,2);
   SYSTEMTIME st;
   char sz[64];
   ZeroMemory(sz,64);
   ZeroMemory(&st,sizeof(SYSTEMTIME));
   _conGetDateTimeAsSystemTime(xpp[1]->con(),xpp[2]->con(),&st);
   if( st.wDay > 0 )
   {
      _sprintf_p( sz,64,"%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu",
                  st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
   }
   xpp[0]->PutStr(sz);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_SetRfc822Date
            | syntax_: `void __cdecl ft64_SetRfc822Date( FILETIME* pft, LPSTR ps, LONG* pnShift )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_SetRfc822Date
            | _kw_: RFC 822, RFC 1123, email date, http date, parse, FILETIME
   }}*/
/*{{|desc: Parses an RFC 822 / RFC 1123 date string ps (as used in e-mail and HTTP headers, e.g.
      "Tue, 24 Jan 2012 13:18:22 -0500") and stores the result into the FILETIME pft. Two-digit years are
      expanded (>80 to 1900+, otherwise 2000+). The timezone is decoded from a numeric +/-HHMM offset or a
      named US zone (EST/EDT, CST/CDT, MST/MDT, PST/PDT) and written, in minutes, to pnShift. This is the C
      primitive behind the Xbase++ function ft64_SetRfc822Date().
    | params:
    - `pft` FILETIME* - Destination FILETIME; zeroed first, and left at zero when ps is empty.
    - `ps` LPSTR - RFC 822 date string to parse.
    - `pnShift` LONG* - Receives the timezone shift in minutes; ignored when NULL.

    Returns void

    |seealso: See also: {{ilink: <c-function ft64_SetRfc822Date> ft64_SetRfc822Date}}, {{ilink: <c-function ft64_SetTs> ft64_SetTs}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_SetRfc822Date( FILETIME* pft, LPSTR ps , LONG* pnShift )
{
   LONG cb,n;
   if( pnShift ){ *pnShift = 0; }
   if( pft ){ pft->dwHighDateTime = 0; pft->dwLowDateTime = 0; }
   if( !( pft && ps ) ) return;
   cb = (LONG) _xstrlen(ps);
   if( !cb ){return; }
   char sz[256]; ZeroMemory(sz, sizeof(sz) );
   if( cb >= sizeof(sz)){ cb = sizeof(sz) - 1; }
   _bcopy((LPBYTE) sz, (LPBYTE) ps, (UINT) cb );
   LPSTR pp[16]; ZeroMemory(pp, sizeof(pp) );
   ULONG np = 0;
   ULONG nColon = 0;

   for( n=0; n < cb;n++ )
   {
      if( sz[n] == ',' )
      {
         // don't care about day of week
         sz[n] = 0;         
         ZeroMemory(pp, sizeof(pp) );
         np = 0;
      }
      else if( (sz[n] == '+' ) || (sz[n] == '-' ) )
      {
         np = 15;
         for( pp[np] = &(sz[n]),n++; isdigit( sz[n] ); n++);
         sz[n] = 0;
         n = cb+1;
         np = 16;         
      }
      else if( isalpha( sz[n] ) )
      {
         for( pp[np] = &(sz[n]); isalpha( sz[n] ); n++);
         if( nColon )
         {
            pp[15] = pp[np];
            pp[np] = 0;
            np = 16;
         }
         else
         {
            if( sz[n] == ',' )
            {
               ZeroMemory(pp, sizeof(pp) );         
               np = 0;
            }
            else
            {
               np++;
            }
         }
         sz[n] = 0;         
      }
      else if( isdigit( sz[n] ) )
      {
         for( pp[np] = &(sz[n]); isdigit( sz[n] ); n++);
         if( sz[n] == ':'){ nColon++; }
         sz[n] = 0;
         np++;
      }
      else
      {
         sz[n] = 0;
      }
      if( np > 14)
      {
         n = cb+1;
      }
   }
   SYSTEMTIME st; ZeroMemory(&st,sizeof(st));
   if( (np > 0) && pp[0] )
   {
      st.wDay = (WORD) atoi(pp[0]);
   }
   if( (np > 1) && pp[1] )   
   {
      int ii;
      for( ii=0; (ii < 12) && (st.wMonth == 0); ii++ )
      {
         if( lstrcmpi(pp[1],s_mt[ii]) == 0 )
         {
            st.wMonth = (WORD) ((ii + 1) & 0xFFFF);
         }
      }
   }
   if( (np > 2) && pp[2] )
   {
      st.wYear = (WORD) atoi(pp[2]);
      if( st.wYear < 1900 )
      {
         if( st.wYear > 80 )
         {
            st.wYear += 1900;
         }
         else
         {
            st.wYear += 2000;
         }
      }
   }
   if( (np > 3) && pp[3] && (nColon > 0))
   {
      st.wHour = (WORD) atoi(pp[3]);
   }
   if( (np > 4) && pp[4] && (nColon > 0))   
   {
      st.wMinute = (WORD) atoi(pp[4]);
   }   
   if( (np > 5) && pp[5] && (nColon > 1))
   {
      st.wSecond = (WORD) atoi(pp[5]);
   }      
   
   // Date: Tue, 24 Jan 2012 13:18:22 -0500
   
   if( pp[15] && pnShift )
   {
      LPSTR p = pp[15];   
      if( (*p == '+') || (*p == '-') )
      {
      
         char buffer[8]; 
         LONG mul = ( (*p == '-') ? -1 : 1 );
         LONG ns = 0;
         for( ; *p && !isdigit(*p); p++);
         ZeroMemory(buffer,sizeof(buffer));
         cb = lstrlen(p);
         if( cb >= 2 )
         {
            buffer[0] = *p++; cb--;
            buffer[1] = *p++; cb--;
            ns = atoi(buffer) * 60;
         }
         for( ; cb && !isdigit(*p); p++,cb--);
         if( cb >= 2 )
         {
            buffer[0] = *p++; cb--;
            buffer[1] = *p++; cb--;
            ns += atoi(buffer);
         }
         *pnShift = ns * mul;
      }
      else // named zone
      {
         if( (lstrcmpi(p, "est") == 0) || (lstrcmpi(p, "edt") == 0) ){ *pnShift = -5 * 60; }
         else if( (lstrcmpi(p, "cst") == 0) || (lstrcmpi(p, "cdt") == 0) ){ *pnShift = -6 * 60; }         
         else if( (lstrcmpi(p, "mst") == 0) || (lstrcmpi(p, "mdt") == 0) ){ *pnShift = -7 * 60; }                  
         else if( (lstrcmpi(p, "pst") == 0) || (lstrcmpi(p, "pdt") == 0) ){ *pnShift = -8 * 60; }                           
      }
   }
   SystemTimeToFileTime(&st,pft);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_SetRfc822Date
            | syntax_: `ft64_SetRfc822Date( pft, cRfc822, @nShift )`
            | category: date-time/filetime
            | _kw_: RFC 822, RFC 1123, email date, http date, parse, FILETIME64
   }}*/
/*{{|desc: Stores an RFC822 timestamp string into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `cRfc822` Character - RFC822-style timestamp string.
    - `nShift` Numeric by reference - Receives the timezone shift in minutes when a timezone component is
      present.

    Returns NIL

    |note: Numeric zones such as -0500 are supported. Named US zones EST/EDT, CST/CDT, MST/MDT and PST/PDT are
      also recognized. }}*/
_XPP_REG_FUN_( FT64_SETRFC822DATE)
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      LPSTR ps = _pszParam(pl,2);
      if( ps )
      {
         LONG ns = 0;
         ft64_SetRfc822Date(pft,ps ,&ns);
         _stornl(ns,pl,3,0);
         _xfree((void*) ps );
      }
      _conParamUnLockStrEx(&plk);
   }
   _ret(pl);
   
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// TODO: check the daylight saving on the date we are converting to local
/*{{begin-c-function}}*/
/*{{c-function_: ft64_ToLocalTime
            | syntax_: `void __cdecl ft64_ToLocalTime( FILETIME* pft )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_ToLocalTime
            | _kw_: local time, UTC, timezone offset, FILETIME
   }}*/
/*{{|desc: Converts the FILETIME pft from UTC to local time in place by adding the system's current
      UTC-to-local offset, computed as the difference between GetLocalTime and GetSystemTimeAsFileTime
      sampled at the moment of the call (so it reflects the current DST state, not necessarily the one in
      effect on pft's own date). Does nothing when pft is NULL. This is the C primitive behind the Xbase++
      function ft64_ToLocalTime().
    | params:
    - `pft` FILETIME* - FILETIME to convert in place; ignored when NULL.

    Returns void

    |seealso: See also: {{ilink: <c-function ft64_ToLocalTime> ft64_ToLocalTime}}, {{ilink: <function ft64_Now> ft64_Now}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
void OT4XB_API __cdecl ft64_ToLocalTime( FILETIME* pft)
{  
   if( pft )
   {
      SYSTEMTIME st_local;
      FILETIME   ft_local;
      FILETIME   ft_sys;   
      GetLocalTime(&st_local);
      GetSystemTimeAsFileTime(&ft_sys);
      SystemTimeToFileTime(&st_local,&ft_local);
      ((LONGLONG*) pft)[0] += ((LONGLONG*) &ft_local)[0] - ((LONGLONG*) &ft_sys)[0];
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_ToLocalTime
            | syntax_: `ft64_ToLocalTime( pft )`
            | category: date-time/filetime
            | _kw_: local time, UTC, timezone offset, FILETIME64
   }}*/
/*{{|desc: Converts the stored UTC FILETIME64 value to local time.
    | params:
    - `pft` FILETIME64 extended pointer - FILETIME storage to modify.

    Returns The converted value

    |note: if the parameter is a string or an array should be provided by reference

    |note: The conversion uses the current local/system offset. The source contains a TODO to review daylight
      saving behavior for the date being converted. }}*/
_XPP_REG_FUN_( FT64_TOLOCALTIME)
{
   TXppParamList xpp( pl, 1 );
   
   FILETIME* pft = (FILETIME*) xpp[ 1 ]->LockStrEx(TRUE);
   if( pft )
   {
      ft64_ToLocalTime( pft );
      xpp[ 1 ]->UnLockStrEx();
   }   
   xpp[ 0 ]->Put( xpp[ 1 ]->con() );

   
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_strf
            | syntax_: `LPSTR __cdecl ft64_strf( FILETIME* pft, LPSTR pFormat )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_strf
            | _kw_: strftime, format date, FILETIME, C format
   }}*/
/*{{|desc: Formats the FILETIME pft with a C strftime() format string pFormat and returns the result.
      Convenience wrapper that calls ft64_strf_l with no locale (the current C locale). This is the C
      primitive behind the Xbase++ function ft64_strf().
    | params:
    - `pft` FILETIME* - Source FILETIME to format (interpreted as UTC).
    - `pFormat` LPSTR - strftime()-style format string.

    Returns LPSTR - Pointer to the formatted string (buffer from _xgrab), or NULL when pft or pFormat is
      NULL or formatting yields an empty result.

    |seealso: See also: {{ilink: <c-function ft64_strf_l> ft64_strf_l}}, {{ilink: <c-function ft64_GetTs> ft64_GetTs}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
LPSTR OT4XB_API __cdecl ft64_strf( FILETIME* pft, LPSTR pFormat){ return ft64_strf_l(pft,pFormat,0,0); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ft64_strf_l
            | syntax_: ```
                 LPSTR __cdecl ft64_strf_l( FILETIME* pft, LPSTR pFormat, LPSTR locale_string, int locale_category )
              ```
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_strf_l
            | _kw_: strftime, format date, FILETIME, locale
   }}*/
/*{{|desc: Formats the FILETIME pft with a C strftime() format string pFormat, optionally using a specific
      locale. The FILETIME is converted to a broken-down UTC time with _gmtime64_s and formatted into a
      1024-byte _xgrab buffer. When locale_string is given, a temporary locale is built with
      _create_locale(locale_category, locale_string) and _strftime_l is used; otherwise the plain strftime
      is used. This is the C primitive behind the Xbase++ function ft64_strf().
    | params:
    - `pft` FILETIME* - Source FILETIME to format (interpreted as UTC).
    - `pFormat` LPSTR - strftime()-style format string.
    - `locale_string` LPSTR - Locale name (e.g. "es-ES") or NULL to use the current C locale.
    - `locale_category` int - Locale category passed to _create_locale (e.g. LC_TIME) when
      locale_string is given.

    Returns LPSTR - Pointer to the formatted string (buffer from _xgrab), or NULL when pft or pFormat is
      NULL or the formatted result is empty (in which case the buffer is freed with _xfree).

    |seealso: See also: {{ilink: <c-function ft64_strf> ft64_strf}}, {{ilink: <c-function ft64_GetTs> ft64_GetTs}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
LPSTR OT4XB_API __cdecl ft64_strf_l( FILETIME* pft, LPSTR pFormat , LPSTR locale_string , int locale_category )
{  
   if( pft && pFormat )
   {
      __time64_t q = ((  ((__time64_t*) ((void*) pft))[0] / 10000000ULL) - 11644473600ULL );
      tm stm; ZeroMemory( &stm, sizeof(stm) );  _gmtime64_s(&stm,&q);
      DWORD cb = 1024;
      LPSTR p = (LPSTR) _xgrab( cb );
      if( locale_string )
      {
         _locale_t ls = _create_locale(locale_category, locale_string  );
         cb = _strftime_l(p,cb-1,pFormat,&stm,ls);
         _free_locale(ls);
      }
      else
      {
         cb = strftime(p,cb-1,pFormat,&stm);
      }
      if(cb) 
      {
         return p;
      }
      _xfree( p );
   }
      return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_strf
            | syntax_: `ft64_strf( pft, cFormat [, cLocale [, nLocaleCategory]] )`
            | category: date-time/filetime
            | _kw_: strftime, format date, FILETIME64, C format
   }}*/
/*{{|desc: Formats a FILETIME64 value with the C runtime strftime() formatter.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.
    - `cFormat` Character - strftime() format string.
    - `cLocale` Character - Optional C locale name used with _strftime_l().
    - `nLocaleCategory` Numeric - Optional locale category. Default is LC_TIME.

    Returns Character - Formatted text, or an empty string when the value cannot be formatted.

    |note: The non-standard sequence %S.msc is replaced with seconds plus milliseconds. }}*/
_XPP_REG_FUN_( FT64_STRF )
{
   TXppParamList xpp(pl,4);
   xpp[0]->PutStr("");
   FILETIME* pft = (FILETIME*) xpp[1]->LockStrEx();
   LPSTR pFmt = xpp[2]->LockStrEx();
   LPSTR p = 0;
   
   
          
   if( pft && pFmt )
   {
      if(  ((LONGLONG*)( (void*) pft ))[0] > 116444736000000000LL )
      {
         LPSTR pLocaleString = xpp[3]->LockStrEx();
         try
         {
            p = ft64_strf_l(pft,pFmt,pLocaleString,( xpp[4]->CheckType(XPP_NUMERIC) ? xpp[4]->GetLong() : LC_TIME )  );
            if( strstr( pFmt , "%S.msc" ) )
            {
               LPSTR msc = strstr( p , ".msc" );
               if( msc )
               {
                  SYSTEMTIME st;
                  char sz[16]; ZeroMemory(sz , sizeof(sz));
                  ZeroMemory(&st,sizeof( SYSTEMTIME ) );
                  FileTimeToSystemTime(pft,&st);
                  wsprintf(sz,".%03.3i", MAKELONG(st.wMilliseconds,0));
                  _xstrcpy(msc,sz);
               }
            }
         }
         catch(...) { p = 0;}
      }
   }
   if( p )
   { 
      xpp[0]->PutStr(p);
      _xfree((void*) p); 
   }

}
/*{{end-function}}*/
// -------------------------------------------------------------------------------------------------------------------

/*{{begin-c-function}}*/
/*{{c-function_: ft64_set_Ckf32TsStr
            | syntax_: `BOOL __cdecl ft64_set_Ckf32TsStr( FILETIME* pft, BYTE ckf32ts[8] )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_set_Ckf32TsStr
            | _kw_: CKF32, compact timestamp, 8 bytes, parse, FILETIME
   }}*/
/*{{|desc: Parses an 8-byte CKF32 timestamp string and stores the resulting date and time into the
      FILETIME pft. CKF32 is an in-house ot4xb convention: a non-binary (text) timestamp format that fits a
      date and time down to milliseconds in at most 8 bytes, decoded here with base32_ns::DecodeCkf32Ts.
      This is the C primitive behind the Xbase++ function ft64_Set_Ckf32Ts().
    | params:
    - `pft` FILETIME* - Destination FILETIME.
    - `ckf32ts` BYTE[8] - Source 8-byte CKF32 timestamp string to parse.

    Returns BOOL - TRUE when the string was parsed and converted, FALSE when pft or ckf32ts is NULL or the
      conversion to FILETIME fails.

    |seealso: See also: {{ilink: <function ft64_Set_Ckf32Ts> ft64_Set_Ckf32Ts}}, {{ilink: <c-function ft64_get_Ckf32TsStr> ft64_get_Ckf32TsStr}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
BOOL OT4XB_API __cdecl ft64_set_Ckf32TsStr( FILETIME* pft, BYTE ckf32ts[8] )
{

   if( pft && ckf32ts  )
   {
      int year;
      int month;
      int day;
      int day_milliseconds; 
      base32_ns::DecodeCkf32Ts( (BYTE*) ckf32ts, year, month, day, day_milliseconds);
      SYSTEMTIME st; ZeroMemory( &st, sizeof( st ) );
      st.wYear    = (WORD) year;
      st.wMonth   = (WORD) month;
      st.wDay = (WORD) day;
      st.wHour = (WORD) ( day_milliseconds / ( 60 * 60 * 1000 ) );
      day_milliseconds %= ( 60 * 60 * 1000 );
      st.wMinute = (WORD) ( day_milliseconds / ( 60 * 1000 ) );
      day_milliseconds %= ( 60 * 1000 );
      st.wSecond = (WORD) ( day_milliseconds / 1000 );
      st.wMilliseconds = (WORD) ( day_milliseconds % 1000 );
      return SystemTimeToFileTime( &st, pft );
   }
   return FALSE;
}
/*{{end-c-function}}*/
/*{{begin-c-function}}*/
/*{{c-function_: ft64_get_Ckf32TsStr
            | syntax_: `BOOL __cdecl ft64_get_Ckf32TsStr( FILETIME* pft, BYTE ckf32ts[8] )`
            | category: date-time/filetime
            | header: ot4xb_c_exported.h
            | mangled-name: ft64_get_Ckf32TsStr
            | _kw_: CKF32, compact timestamp, 8 bytes, encode, FILETIME
   }}*/
/*{{|desc: Encodes the FILETIME pft as an 8-byte CKF32 timestamp string and writes it to ckf32ts. CKF32 is
      an in-house ot4xb convention: a non-binary (text) timestamp format that fits a date and time down to
      milliseconds in at most 8 bytes, produced here with base32_ns::EncodeCkf32Ts. This is the C primitive
      behind the Xbase++ function ft64_Get_Ckf32Ts().
    | params:
    - `pft` FILETIME* - Source FILETIME to encode.
    - `ckf32ts` BYTE[8] - Destination 8-byte buffer that receives the CKF32 timestamp string.

    Returns BOOL - TRUE on success, FALSE when pft or ckf32ts is NULL or the FILETIME cannot be converted
      to a system time.

    |seealso: See also: {{ilink: <function ft64_Get_Ckf32Ts> ft64_Get_Ckf32Ts}}, {{ilink: <c-function ft64_set_Ckf32TsStr> ft64_set_Ckf32TsStr}}, {{ilink: <slug filetime64> FILETIME64}} }}*/
BOOL OT4XB_API __cdecl ft64_get_Ckf32TsStr( FILETIME* pft, BYTE ckf32ts[ 8 ] )
{
   if( pft && ckf32ts)
   {
      SYSTEMTIME st;
      if( !FileTimeToSystemTime( pft, &st ) )
      {
         return FALSE;
      }

      int year = st.wYear;
      int month = st.wMonth;
      int day = st.wDay;
      int day_milliseconds = ( st.wHour * 60 * 60 * 1000 ) + ( st.wMinute * 60 * 1000 ) + ( st.wSecond * 1000 ) + st.wMilliseconds;
      base32_ns::EncodeCkf32Ts( year, month, day, day_milliseconds, ckf32ts );
      return TRUE;
   }
   return FALSE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Set_Ckf32Ts
            | syntax_: `ft64_Set_Ckf32Ts( pft, cCkf32Ts )`
            | category: date-time/filetime
            | _kw_: CKF32, compact timestamp, 8 bytes, FILETIME64
   }}*/
/*{{|desc: Stores a CKF32 timestamp string into a FILETIME64 value.
    | params:
    - `pft` FILETIME64 extended pointer - Destination FILETIME storage.
    - `cCkf32Ts` Character - CKF32 timestamp string. The function reads the first 8 bytes.

    Returns Logical - .T. when the timestamp was decoded and stored; otherwise .F. }}*/
_XPP_REG_FUN_( FT64_SET_CKF32TS )
{
   BOOL result = FALSE;
   TXppParamList xpp( pl, 2 );
   FILETIME* pft = (FILETIME*) xpp[ 1 ]->LockStrEx( TRUE );
   if( pft )
   {
      BYTE* ckf32ts = (BYTE*) xpp[ 2 ]->LockStrEx();
      if( ckf32ts )
      {
         if( xpp[ 2 ]->ExLen() > 7 )
         {
            result = ft64_set_Ckf32TsStr( pft, ckf32ts );
         }
         xpp[ 2 ]->UnLockStrEx();
      }
      xpp[ 1 ]->UnLockStrEx();
   }
   xpp[ 0 ]->PutBool( result );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ft64_Get_Ckf32Ts
            | syntax_: `ft64_Get_Ckf32Ts( pft )`
            | category: date-time/filetime
            | _kw_: CKF32, compact timestamp, 8 bytes, FILETIME64
   }}*/
/*{{|desc: Encodes a FILETIME64 value as a CKF32 timestamp string.
    | params:
    - `pft` FILETIME64 extended pointer - Source FILETIME storage.

    Returns Character - CKF32 timestamp string, or an empty string when the source cannot be read. }}*/
_XPP_REG_FUN_( FT64_GET_CKF32TS )
{
   char ckf32ts[ 16 ] = { 0 };
   TXppParamList xpp( pl);
   FILETIME* pft = (FILETIME*) xpp[ 1 ]->LockStrEx();
   if( pft )
   {
      ft64_get_Ckf32TsStr( pft, (BYTE*) ckf32ts );
   }
   xpp[ 0 ]->PutStr( ckf32ts );
}
/*{{end-function}}*/
