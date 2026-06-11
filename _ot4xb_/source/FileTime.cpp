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
// -----------------------------------------------------------------------------------------------------------------
// ft64_SetTs( @ft , cStr , @nShift  )
// ft64_SetTs( pft , cStr , @nShift , nExtendedFlags )
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_SetTs</name>
      <category>date-time/filetime</category>
      <description>
         Stores a timestamp string into a FILETIME64 value.
      </description>
      <syntax>ft64_SetTs( pft, cTimeStamp, @nShift [, nFlags] ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>cTimeStamp</name>
            <type>Character | FILETIME64 object | NIL</type>
            <description>
               Timestamp string to parse. With flag 0x01 it may also be a FILETIME64-compatible object to copy from.
               With flag 0x10, NIL stores the current time.
            </description>
         </parameter>
         <parameter>
            <name>nShift</name>
            <type>Numeric by reference</type>
            <description>Receives the timezone shift in minutes when the string contains a timezone component.</description>
         </parameter>
         <parameter>
            <name>nFlags</name>
            <type>Numeric</type>
            <description>0x01 allows object copy; 0x10 allows NIL as now UTC; 0x30 allows NIL as now local.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>
         The pft parameter uses OT4XB extended pointer handling. It can be a FILETIME64 object, an
         8-byte character buffer passed by reference when it must be modified, a numeric memory pointer,
         or an array holding the low and high DWORD values.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_GetTs</name>
      <category>date-time/filetime</category>
      <description>
         Formats a FILETIME64 value as a timestamp string.
      </description>
      <syntax>ft64_GetTs( pft [, cFormat [, nFlags]] ) -> cTimeStamp | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>cFormat</name>
            <type>Character</type>
            <description>
               Optional printf-style format. Arguments supplied internally are year, month, day, hour,
               minute, second and millisecond.
            </description>
         </parameter>
         <parameter>
            <name>nFlags</name>
            <type>Numeric</type>
            <description>
               Low nibble 1 uses current local time when pft is NIL; low nibble 2 uses current UTC time.
               Format flags 0x0C00, 0x0E00, 0x0F00 and 0x1700 select built-in timestamp formats when
               cFormat is omitted.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Character | NIL</type>
         <description>Formatted timestamp, or NIL when no FILETIME source can be resolved.</description>
      </return>
      <remarks>
         Default format is YYYY-MM-DD hh:mm:ss. Built-in format 0x0C00 returns YYYYMMDDhhmm,
         0x0E00 returns YYYYMMDDhhmmss, 0x0F00 selects the current 15-character compact
         format, and 0x1700 returns YYYY-MM-DDThh:mm:ss.mmm.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_GETTS ) // ft64_GetTs( @ft , cFmt , flags) // flags 1 default to localtime 2 default to system time
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_ToHttp</name>
      <category>date-time/filetime</category>
      <description>
         Formats a FILETIME64 value as an HTTP date string.
      </description>
      <syntax>ft64_ToHttp( pft [, nFlags] ) -> cHttpDate | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>nFlags</name>
            <type>Numeric</type>
            <description>Low nibble 1 uses current local time when pft is NIL; low nibble 2 uses current UTC time.</description>
         </parameter>
      </parameters>
      <return>
         <type>Character | NIL</type>
         <description>HTTP-style timestamp, or NIL when no FILETIME source can be resolved.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_TOHTTP) // ft64_ToHttp( ft , flags )
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
// -----------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_SetDateTime</name>
      <category>date-time/filetime</category>
      <description>
         Stores an Xbase++ date/time pair into a FILETIME64 value.
      </description>
      <syntax>ft64_SetDateTime( pft, dDate, uTime ) -> NIL</syntax>
      <syntax>ft64_SetDateTime( pft, oFileTime ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>dDate</name>
            <type>Date | Character | FILETIME64 object</type>
            <description>
               Date value to store, or another FILETIME64-compatible value to copy from.
            </description>
         </parameter>
         <parameter>
            <name>uTime</name>
            <type>Character | Numeric</type>
            <description>
               Time as HH:MM:SS.mmm or as seconds after midnight.
            </description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_SETDATETIME ) // ft64_SETDATETIME(pft,d,t)
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
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_GetDateTime</name>
      <category>date-time/filetime</category>
      <description>
         Extracts the date and a time string from a FILETIME64 value.
      </description>
      <syntax>ft64_GetDateTime( pft, @dDate, @cTime ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>dDate</name>
            <type>Date by reference</type>
            <description>Receives the Xbase++ date.</description>
         </parameter>
         <parameter>
            <name>cTime</name>
            <type>Character by reference</type>
            <description>Receives HH:MM:SS.mmm.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_GETDATETIME ) // ft64_GETDATETIME(pft,@d,@t)
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_GetDateTimeSec</name>
      <category>date-time/filetime</category>
      <description>
         Extracts the date and the time as seconds after midnight from a FILETIME64 value.
      </description>
      <syntax>ft64_GetDateTimeSec( pft, @dDate, @nSeconds ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>dDate</name>
            <type>Date by reference</type>
            <description>Receives the Xbase++ date.</description>
         </parameter>
         <parameter>
            <name>nSeconds</name>
            <type>Numeric by reference</type>
            <description>Receives seconds after midnight, including milliseconds as decimals.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_GETDATETIMESEC ) // ft64_GETDATETIMESEC(pft,@d,@t)
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
// -----------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Now</name>
      <category>date-time/filetime</category>
      <description>
         Stores the current time into a FILETIME64 value.
      </description>
      <syntax>ft64_Now( pft [, lLocal] ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>lLocal</name>
            <type>Logical</type>
            <description>When .T., stores local time. Otherwise stores UTC system time.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_NOW ) // ft64_NOW(pft,lLocal)
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
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_ElapMilliSeconds</name>
      <category>date-time/filetime</category>
      <description>
         Returns elapsed milliseconds between two FILETIME64 values.
      </description>
      <syntax>ft64_ElapMilliSeconds( pft [, pft2 [, lLocal [, @cElapsed]]]) -> nMilliseconds | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Start FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>pft2</name>
            <type>FILETIME64 extended pointer</type>
            <description>End FILETIME storage. When omitted, current UTC or local time is used.</description>
         </parameter>
         <parameter>
            <name>lLocal</name>
            <type>Logical</type>
            <description>When pft2 is omitted, .T. compares against current local time; otherwise UTC is used.</description>
         </parameter>
         <parameter>
            <name>cElapsed</name>
            <type>Character by reference</type>
            <description>
               Optional elapsed text. When this fourth parameter is supplied, the function stores the text and
               does not return the numeric value.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>Elapsed milliseconds, unless cElapsed is supplied.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_ELAPMILLISECONDS) // ft64_ElapMilliSeconds(pft,pft2,lLocal[,yyyy days hh:mm:ss.mss)
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_ElapSeconds</name>
      <category>date-time/filetime</category>
      <description>
         Returns elapsed seconds between two FILETIME64 values.
      </description>
      <syntax>ft64_ElapSeconds( pft [, pft2 [, lLocal [, @cElapsed]]]) -> nSeconds | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Start FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>pft2</name>
            <type>FILETIME64 extended pointer</type>
            <description>End FILETIME storage. When omitted, current UTC or local time is used.</description>
         </parameter>
         <parameter>
            <name>lLocal</name>
            <type>Logical</type>
            <description>When pft2 is omitted, .T. compares against current local time; otherwise UTC is used.</description>
         </parameter>
         <parameter>
            <name>cElapsed</name>
            <type>Character by reference</type>
            <description>
               Optional elapsed text. When this fourth parameter is supplied, the function stores the text and
               does not return the numeric value.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>Elapsed seconds, unless cElapsed is supplied.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_ELAPSECONDS) // ft64_ElapSeconds(pft,pft2,lLocal)
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
// -----------------------------------------------------------------------------------------------------------------
// extended Behavior nFlags
// 0 - like before normal comparation
// 1 - and pft2 == NIL -> .T. if pft is before now
// 2 - and pft2 == NIL -> like 1 but using local time
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Compare</name>
      <category>date-time/filetime</category>
      <description>
         Compares two FILETIME64 values.
      </description>
      <syntax>ft64_Compare( pft, pft2 [, nFlags] ) -> nCompare | lBeforeNow | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>First FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>pft2</name>
            <type>FILETIME64 extended pointer</type>
            <description>Second FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>nFlags</name>
            <type>Numeric</type>
            <description>
               With pft2 omitted, 1 compares pft with current UTC time and 2 compares with current local time,
               returning a logical value.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | Logical | NIL</type>
         <description>
            With two FILETIME values, returns 0 when equal, 1 when pft is earlier than pft2, and -1 when pft
            is later than pft2. With flags 1 or 2 and no pft2, returns whether pft is before or equal to now.
         </description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_COMPARE) // ft64_Compare(pft,pft2[,nFlags])
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Add</name>
      <category>date-time/filetime</category>
      <description>
         Adds a millisecond-based offset to a FILETIME64 value.
      </description>
      <syntax>ft64_Add( pft, nMilliseconds [, nMultiplier] ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>FILETIME storage to modify.</description>
         </parameter>
         <parameter>
            <name>nMilliseconds</name>
            <type>Numeric</type>
            <description>Base offset in milliseconds.</description>
         </parameter>
         <parameter>
            <name>nMultiplier</name>
            <type>Numeric</type>
            <description>Optional multiplier. Default is 1.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>
         FILETIME stores 100-nanosecond ticks. This function converts nMilliseconds to FILETIME ticks
         and then applies the optional multiplier.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_ADD ) // Ft64_Add(pft,n,m)
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
// -----------------------------------------------------------------------------------------------------------------
BOOL  OT4XB_API __cdecl ft64_now(FILETIME* pft)
{
	static _PFN_GetSystemTimeAsFileTime fp = 0;
	static BOOL bPrecise = FALSE;
	if (!fp)
	{
		fp = (_PFN_GetSystemTimeAsFileTime) GetProcAddress(GetModuleHandleA("kernel32"), "GetSystemTimePreciseAsFileTime");
		if (fp)
		{
			bPrecise = TRUE;
		}
		else
		{
			fp = (_PFN_GetSystemTimeAsFileTime) GetProcAddress(GetModuleHandleA("kernel32"), "GetSystemTimeAsFileTime");
		}
	}
	(*fp)(pft);
	return bPrecise;
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Add_Y</name>
      <category>date-time/filetime</category>
      <description>
         Adds years to a FILETIME64 value.
      </description>
      <syntax>ft64_Add_Y( pft, nYears ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>FILETIME storage to modify.</description>
         </parameter>
         <parameter>
            <name>nYears</name>
            <type>Numeric</type>
            <description>Number of years to add. Negative values move backwards.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>February 29 is adjusted to February 28 when the target year is not leap.</remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_ADD_Y ) // Ft64_Add_Y(pft,n)
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Add_M</name>
      <category>date-time/filetime</category>
      <description>
         Adds months to a FILETIME64 value.
      </description>
      <syntax>ft64_Add_M( pft, nMonths ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>FILETIME storage to modify.</description>
         </parameter>
         <parameter>
            <name>nMonths</name>
            <type>Numeric</type>
            <description>Number of months to add. Negative values move backwards.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>End-of-month dates are adjusted when the target month has fewer days.</remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_ADD_M ) // Ft64_Add_M(pft,n)
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_To_DosDateTime</name>
      <category>date-time/filetime</category>
      <description>
         Converts a FILETIME64 value to a DOS FAT date/time DWORD.
      </description>
      <syntax>ft64_To_DosDateTime( pft ) -> nDosDateTime | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>DOS date/time value, or NIL if conversion fails.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_TO_DOSDATETIME) // Ft64_To_DosDateTime(pft) -> nDosDateTime
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_From_DosDateTime</name>
      <category>date-time/filetime</category>
      <description>
         Stores a DOS FAT date/time DWORD into a FILETIME64 value.
      </description>
      <syntax>ft64_From_DosDateTime( pft, nDosDateTime ) -> lOk</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>nDosDateTime</name>
            <type>Numeric</type>
            <description>DOS FAT date/time value.</description>
         </parameter>
      </parameters>
      <return>
         <type>Logical</type>
         <description>.T. when the value was converted; otherwise .F.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_FROM_DOSDATETIME) // Ft64_From_DosDateTime(pft,ddt) -> lOk
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
// -----------------------------------------------------------------------------------------------------------------
void OT4XB_API __cdecl ft64_SetUnixTime( FILETIME* pft, DWORD ut )
{
   reinterpret_cast<LONGLONG*>(pft)[0] = Int32x32To64(ut,10000000L) + 116444736000000000LL;
}
// -----------------------------------------------------------------------------------------------------------------
DWORD OT4XB_API __cdecl ft64_GetUnixTime( FILETIME* pft)
{
   LONGLONG ll = reinterpret_cast<LONGLONG*>(pft)[0];
   return (DWORD) (((LONGLONG) ((ll - 116444736000000000LL) / 10000000LL)) & 0xFFFFFFFFLL);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_To_UnixTime</name>
      <category>date-time/filetime</category>
      <description>
         Converts a FILETIME64 value to a 32-bit Unix timestamp.
      </description>
      <syntax>ft64_To_UnixTime( pft ) -> nUnixTime | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>
            Unix time in seconds. Values are returned using the 32-bit numeric representation available
            to Xbase++.
         </description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_TO_UNIXTIME) // Ft64_To_UnixTime(pft) -> nUnixTime
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_From_UnixTime</name>
      <category>date-time/filetime</category>
      <description>
         Stores a 32-bit Unix timestamp into a FILETIME64 value.
      </description>
      <syntax>ft64_From_UnixTime( pft, nUnixTime ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>nUnixTime</name>
            <type>Numeric</type>
            <description>Unix time in seconds.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_FROM_UNIXTIME) // Ft64_From_UnixTime(pft,ut) -> NIL
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
// -----------------------------------------------------------------------------------------------------------------
void OT4XB_API __cdecl ft64_SetUnixTime64( FILETIME* pft, LONGLONG ut )
{
   reinterpret_cast<LONGLONG*>(pft)[0] = (ut * 10000000LL) + 116444736000000000LL;
}
// -----------------------------------------------------------------------------------------------------------------
LONGLONG OT4XB_API __cdecl ft64_GetUnixTime64( FILETIME* pft)
{
   LONGLONG ll = reinterpret_cast<LONGLONG*>(pft)[0];
   return ( (ll - 116444736000000000LL) / 10000000LL );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_To_ExcelTime</name>
      <category>date-time/filetime</category>
      <description>
         Converts a FILETIME64 value to an Excel serial date/time number.
      </description>
      <syntax>ft64_To_ExcelTime( pft ) -> nExcelTime | NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>Excel serial date/time value.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_TO_EXCELTIME) // Ft64_To_EXCELTime(pft) -> nUnixTime
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_From_ExcelTime</name>
      <category>date-time/filetime</category>
      <description>
         Stores an Excel serial date/time number into a FILETIME64 value.
      </description>
      <syntax>ft64_From_ExcelTime( pft, nExcelTime ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>nExcelTime</name>
            <type>Numeric</type>
            <description>Excel serial date/time value.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_FROM_EXCELTIME) // Ft64_From_EXCELTime(pft,ut) -> NIL
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>FILETIME64</name>
      <parent>GWST</parent>
      <source>FileTime.cpp:wapist_FILETIME64</source>
      <category>date-time/filetime</category>
      <description>
         GWST wrapper over the WinAPI FILETIME structure, with helper properties and methods for
         timestamp parsing, formatting, arithmetic and common time representations.
      </description>
      <members>
         <member type="DWORD" name="dwLowDateTime" offset="0" size="4" />
         <member type="DWORD" name="dwHighDateTime" offset="4" size="4" />
         <member type="DWORD64" name="qft" offset="0" size="8">
            Alternate 64-bit view over the same FILETIME storage.
         </member>
      </members>
      <properties>
         <property name="cTimeStamp" type="Character">Default timestamp view, YYYY-MM-DD hh:mm:ss.</property>
         <property name="dDate" type="Date">Date component as an Xbase++ date.</property>
         <property name="cTime" type="Character">Time component as HH:MM:SS.mmm.</property>
         <property name="nTime" type="Numeric">Time component as seconds after midnight.</property>
         <property name="cHexTs" type="Character">64-bit FILETIME value as a hexadecimal string.</property>
         <property name="nDosDateTime" type="Numeric">DOS FAT date/time DWORD.</property>
         <property name="nUnixTime" type="Numeric">Unix timestamp in seconds.</property>
         <property name="nExcelTime" type="Numeric">Excel serial date/time value.</property>
      </properties>
      <methods>
         <method name="SetTimeStamp" returns="Self">Stores a timestamp string, another FILETIME64 object, or now depending on flags.</method>
         <method name="_GetTimeStamp_" returns="Character">Formats the value with a supplied printf-style format.</method>
         <method name="GetTimeStamp" returns="Character">Returns YYYY-MM-DD hh:mm:ss.</method>
         <method name="GetTimeStamp19" returns="Character">Returns YYYY-MM-DD hh:mm:ss.</method>
         <method name="GetTimeStamp14" returns="Character">Returns YYYYMMDDhhmmss.</method>
         <method name="GetIso8601" returns="Character">Returns YYYY-MM-DDThh:mm:ss.</method>
         <method name="json_escape_self" returns="Character">Returns a JSON escaped ISO-like timestamp using tls():json_timezone when present.</method>
         <method name="strf" returns="Character">Formats the value with FT64_STRF().</method>
         <method name="SetDateTime" returns="Self">Stores an Xbase++ date and time.</method>
         <method name="GetDateTime" returns="Self">Stores date and HH:MM:SS.mmm into by-reference parameters.</method>
         <method name="GetDateTimeSec" returns="Self">Stores date and seconds after midnight into by-reference parameters.</method>
         <method name="Now" returns="Self">Stores current UTC time, or local time when lLocal is .T.</method>
         <method name="NowL" returns="Self">Stores current local time.</method>
         <method name="ElapMilliSeconds" returns="Numeric">Returns elapsed milliseconds.</method>
         <method name="ElapMilliSecondsL" returns="Numeric">Returns elapsed milliseconds against local time when no end value is supplied.</method>
         <method name="ElapTimeStr" returns="Character">Returns elapsed time as text.</method>
         <method name="ElapSeconds" returns="Numeric">Returns elapsed seconds.</method>
         <method name="ElapSecondsL" returns="Numeric">Returns elapsed seconds against local time when no end value is supplied.</method>
         <method name="Compare" returns="Numeric">Compares with another FILETIME64 value.</method>
         <method name="SETRFC822" returns="Self">Stores an RFC822 timestamp string.</method>
         <method name="Day" returns="Numeric">Returns day of month.</method>
         <method name="Month" returns="Numeric">Returns month number.</method>
         <method name="Year" returns="Numeric">Returns year number.</method>
         <method name="AddMilliSeconds" returns="Self">Adds milliseconds.</method>
         <method name="AddSeconds" returns="Self">Adds seconds.</method>
         <method name="AddMinutes" returns="Self">Adds minutes.</method>
         <method name="AddHours" returns="Self">Adds hours.</method>
         <method name="AddDays" returns="Self">Adds days.</method>
         <method name="AddMonths" returns="Self">Adds months.</method>
         <method name="AddYears" returns="Self">Adds years.</method>
         <method name="SetHexTs" returns="NIL">Stores a hexadecimal 64-bit FILETIME value.</method>
         <method name="GetHexTs" returns="Character">Returns the hexadecimal 64-bit FILETIME value.</method>
         <method name="SetDosDateTime" returns="Self">Stores a DOS FAT date/time DWORD.</method>
         <method name="GetDosDateTime" returns="Numeric">Returns a DOS FAT date/time DWORD.</method>
         <method name="SetUnixTime" returns="Self">Stores a Unix timestamp.</method>
         <method name="GetUnixTime" returns="Numeric">Returns a Unix timestamp.</method>
         <method name="SetExcelTime" returns="Self">Stores an Excel serial date/time number.</method>
         <method name="GetExcelTime" returns="Numeric">Returns an Excel serial date/time number.</method>
         <method name="ToHttp" returns="Character">Returns an HTTP date string.</method>
         <method name="ToLocalTime" returns="Self">Converts the stored UTC FILETIME to local time.</method>
         <method name="SetCkf32Ts" returns="Self">Stores a CKF32 timestamp string.</method>
         <method name="GetCkf32Ts" returns="Character">Returns a CKF32 timestamp string.</method>
      </methods>
      <remarks>
         FILETIME64 uses the normal GWST storage model. Mutating helper methods generally return Self
         so calls can be chained; methods that only read the value return the requested value.

         The class is named FILETIME64 instead of FileTime to avoid a name conflict with the
         FileTime function/class name used by Alaska XbTools.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapist_FILETIME64( XppParamList pl ) // <doc!xb!!|CLASS{FileTime}from{gwst}| />
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
      pc->Member_DWord("dwLowDateTime"); // <doc!xb!!|ivar{FileTime:dwLowDateTime}|short{}| />
      pc->Member_DWord("dwHighDateTime"); // <doc!xb!!|ivar{FileTime:dwHighDateTime}|short{}| />
      // ---------------------------
      pc->GwstSetOffset(0);
      pc->Member_DWord64("qft");
      // ---------------------------
      
      pc->MethodCB("SetTimeStamp","{|s,c,sh,flags| ft64_SetTs(s,c,@sh,flags),s}");
      pc->MethodCB("_GetTimeStamp_","{|s,f| ft64_GetTs(s,f)}");
      pc->MethodCB("GetTimeStamp","{|s| ft64_GetTs(s)}");
      pc->MethodCB("strf","{|s,fmt,locale| FT64_STRF(s,fmt,locale)}");
      
      pc->MethodCB("GetTimeStamp19","{|s| ft64_GetTs(s)}");
      pc->MethodCB("GetTimeStamp14","{|s| ft64_GetTs(s,'%04.4hu%02.2hu%02.2hu%02.2hu%02.2hu%02.2hu')}");
      pc->MethodCB("GetIso8601","{|s| ft64_GetTs(s,'%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu')}");
      pc->MethodCB("json_escape_self","{|s| '\"' + ft64_GetTs(s,'%04.4hu-%02.2hu-%02.2huT%02.2hu:%02.2hu:%02.2hu.%03.3hu') + __vstr(tls():json_timezone,'') +  '\"' }");

      pc->PropertyCB("cTimeStamp","{|s,v| iif(PCount() > 1,ft64_SetTs(s,v),ft64_GetTs(s))}");
      
      pc->MethodCB("SetDateTime","{|s,d,t| ft64_SetDateTime(s,d,t),s}");
      pc->MethodCB("GetDateTime","{|s,d,t| ft64_GetDateTime(s,@d,@t),s}");
      pc->MethodCB("GetDateTimeSec","{|s,d,t| ft64_GetDateTimeSec(s,@d,@t),s}");
      pc->MethodCB("Now","{|s,lLocal| ft64_Now(s,lLocal),s}");
      pc->MethodCB("NowL","{|s| ft64_Now(s,.T.),s}");
      pc->MethodCB("ElapMilliSeconds","{|s,t2,lLocal| ft64_ElapMilliSeconds(s,t2,lLocal)}");
      pc->MethodCB("ElapMilliSecondsL","{|s,t2| ft64_ElapMilliSeconds(s,t2,.T.)}");
      pc->MethodCB( "ElapTimeStr", "{|s,t2,lLocal,ts| ft64_ElapMilliSeconds(s,t2,lLocal,@ts) , ts}" );
      pc->MethodCB("ElapSeconds","{|s,t2,lLocal| ft64_ElapSeconds(s,t2,lLocal)}");
      pc->MethodCB("ElapSecondsL","{|s,t2| ft64_ElapSeconds(s,t2,.T.)}");
      pc->MethodCB("Compare","{|s,t2| ft64_Compare(s,t2)}");
      // ---------------------------
      pc->MethodCB("SETRFC822","{|s,c,sh| ft64_SetRfc822Date(s,c,@sh),s}");      
      // ---------------------------
      pc->MethodCB("Day","{|s| Day(s:dDate)}");
      pc->MethodCB("Month","{|s| Month(s:dDate)}");
      pc->MethodCB("Year","{|s| Year(s:dDate)}");
      pc->PropertyCB("dDate","{|s,v| iif(PCount() > 1, s:SetDateTime(v) ,s:GetDateTime(@v)),v}");
      pc->PropertyCB("cTime","{|s,v| iif(PCount() > 1, s:SetDateTime(,v) ,s:GetDateTime(,@v)),v}");
      pc->PropertyCB("nTime","{|s,v| iif(PCount() > 1, s:SetDateTime(,v) ,s:GetDateTimeSec(,@v)),v}");
      // ---------------------------
      pc->MethodCB("AddMilliSeconds","{|s,n| ft64_Add(s,n,1),s}");
      pc->MethodCB("AddSeconds","{|s,n| ft64_Add(s,n,1000),s}");
      pc->MethodCB("AddMinutes","{|s,n| ft64_Add(s,n,60000),s}");
      pc->MethodCB("AddHours","{|s,n| ft64_Add(s,n,3600000),s}");
      pc->MethodCB("AddDays","{|s,n| ft64_Add(s,n,86400000),s}");
      // ---------------------------
      pc->MethodCB("AddMonths","{|s,n| Ft64_Add_M(s,n),s}");
      pc->MethodCB("AddYears","{|s,n| Ft64_Add_Y(s,n),s}");
      // ---------------------------
      pc->PropertyCB("cHexTs","{|s,v| iif(PCount() > 1, s:SetHexTs(v) ,s:GetHexTs())}");
      pc->MethodCB("SetHexTs" , "{|s,v| iif( ValType(v) =='C',PokeStr(s,0,nHex2Qw(v)),),NIL }");
      pc->MethodCB("GetHexTs" , "{|s,v| cQw2Hex( s:qft ) }");
      // ---------------------------
      pc->MethodCB("SetDosDateTime","{|s,v| Ft64_From_DosDateTime(s,v),s}");
      pc->MethodCB("GetDosDateTime","{|s| Ft64_To_DosDateTime(s)}");
       pc->PropertyCB("nDosDateTime","{|s,v| iif(PCount() > 1,Ft64_From_DosDateTime(s,v),Ft64_To_DosDateTime(s))}");
      // ---------------------------
      pc->MethodCB("SetUnixTime","{|s,v| Ft64_From_UnixTime(s,v),s}");
      pc->MethodCB("GetUnixTime","{|s| Ft64_To_UnixTime(s)}");
      pc->PropertyCB("nUnixTime","{|s,v| iif(PCount() > 1,Ft64_From_UnixTime(s,v),Ft64_To_UnixTime(s))}");
      // ---------------------------
      pc->MethodCB("SetExcelTime","{|s,v| Ft64_From_ExcelTime(s,v),s}");
      pc->MethodCB("GetExcelTime","{|s| Ft64_To_ExcelTime(s)}");
      pc->PropertyCB("nExcelTime","{|s,v| iif(PCount() > 1,Ft64_From_ExcelTime(s,v),Ft64_To_ExcelTime(s))}");
      // ---------------------------
      pc->MethodCB("ToHttp","{|s| Ft64_ToHttp(s)}");
      // ---------------------------      
      pc->MethodCB("ToLocalTime","{|s| FT64_TOLOCALTIME(s)}");      
      // ---------------------------
      pc->MethodCB( "SetCkf32Ts", "{|s,v| Ft64_Set_Ckf32Ts(s,v),s}" );
      pc->MethodCB( "GetCkf32Ts", "{|s| Ft64_Get_Ckf32Ts(s)}" );
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>dt2iso8601</name>
      <category>date-time/filetime</category>
      <description>
         Formats an Xbase++ date/time pair as an ISO 8601 timestamp.
      </description>
      <syntax>dt2iso8601( dDate, uTime ) -> cIso8601</syntax>
      <parameters>
         <parameter>
            <name>dDate</name>
            <type>Date</type>
            <description>Xbase++ date value.</description>
         </parameter>
         <parameter>
            <name>uTime</name>
            <type>Character | Numeric</type>
            <description>Time value accepted by OT4XB date/time conversion helpers.</description>
         </parameter>
      </parameters>
      <return>
         <type>Character</type>
         <description>Timestamp in YYYY-MM-DDThh:mm:ss format, or an empty string when the date is invalid.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( DT2ISO8601 ) // DT2ISO8601(d,t) -> cIso8601
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_SetRfc822Date</name>
      <category>date-time/filetime</category>
      <description>
         Stores an RFC822 timestamp string into a FILETIME64 value.
      </description>
      <syntax>ft64_SetRfc822Date( pft, cRfc822, @nShift ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>cRfc822</name>
            <type>Character</type>
            <description>RFC822-style timestamp string.</description>
         </parameter>
         <parameter>
            <name>nShift</name>
            <type>Numeric by reference</type>
            <description>Receives the timezone shift in minutes when a timezone component is present.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>
         Numeric zones such as -0500 are supported. Named US zones EST/EDT, CST/CDT, MST/MDT and PST/PDT
         are also recognized.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_SETRFC822DATE) // ft64_SetRfc822Date(pft,cStr,@nShiftInMinutes) -> NIL
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
// -----------------------------------------------------------------------------------------------------------------
// TODO: check the daylight saving on the date we are converting to local
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_ToLocalTime</name>
      <category>date-time/filetime</category>
      <description>
         Converts the stored UTC FILETIME64 value to local time.
      </description>
      <syntax>ft64_ToLocalTime( pft ) -> NIL</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>FILETIME storage to modify.</description>
         </parameter>
      </parameters>
      <return>NIL</return>
      <remarks>
         The conversion uses the current local/system offset. The source contains a TODO to review daylight
         saving behavior for the date being converted.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_TOLOCALTIME) // FT64_TOLOCALTIME(pft) -> NIL
{
   CON_PLKSTREX plk;
   FILETIME* pft = (FILETIME*) _conParamWLockStrEx(pl,1,&plk);
   if( pft )
   {
      ft64_ToLocalTime( pft );
   }   
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR OT4XB_API __cdecl ft64_strf( FILETIME* pft, LPSTR pFormat){ return ft64_strf_l(pft,pFormat,0,0); }
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_strf</name>
      <category>date-time/filetime</category>
      <description>
         Formats a FILETIME64 value with the C runtime strftime() formatter.
      </description>
      <syntax>ft64_strf( pft, cFormat [, cLocale [, nLocaleCategory]] ) -> cText</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>cFormat</name>
            <type>Character</type>
            <description>strftime() format string.</description>
         </parameter>
         <parameter>
            <name>cLocale</name>
            <type>Character</type>
            <description>Optional C locale name used with _strftime_l().</description>
         </parameter>
         <parameter>
            <name>nLocaleCategory</name>
            <type>Numeric</type>
            <description>Optional locale category. Default is LC_TIME.</description>
         </parameter>
      </parameters>
      <return>
         <type>Character</type>
         <description>Formatted text, or an empty string when the value cannot be formatted.</description>
      </return>
      <remarks>
         The non-standard sequence %S.msc is replaced with seconds plus milliseconds.
      </remarks>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_STRF ) // FT64_STRF( @ft , cFmt , locale , locale_category)
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

// -------------------------------------------------------------------------------------------------------------------

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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Set_Ckf32Ts</name>
      <category>date-time/filetime</category>
      <description>
         Stores a CKF32 timestamp string into a FILETIME64 value.
      </description>
      <syntax>ft64_Set_Ckf32Ts( pft, cCkf32Ts ) -> lOk</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Destination FILETIME storage.</description>
         </parameter>
         <parameter>
            <name>cCkf32Ts</name>
            <type>Character</type>
            <description>CKF32 timestamp string. The function reads the first 8 bytes.</description>
         </parameter>
      </parameters>
      <return>
         <type>Logical</type>
         <description>.T. when the timestamp was decoded and stored; otherwise .F.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_SET_CKF32TS ) // FT64_SET_CKF32TS( @ft , ckf32ts )
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
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ft64_Get_Ckf32Ts</name>
      <category>date-time/filetime</category>
      <description>
         Encodes a FILETIME64 value as a CKF32 timestamp string.
      </description>
      <syntax>ft64_Get_Ckf32Ts( pft ) -> cCkf32Ts</syntax>
      <parameters>
         <parameter>
            <name>pft</name>
            <type>FILETIME64 extended pointer</type>
            <description>Source FILETIME storage.</description>
         </parameter>
      </parameters>
      <return>
         <type>Character</type>
         <description>CKF32 timestamp string, or an empty string when the source cannot be read.</description>
      </return>
      <see-also>FILETIME64</see-also>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( FT64_GET_CKF32TS ) // FT64_GET_CKF32TS( @ft ) -> CKF32TS
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
