//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define OT4XB_FPFLAGS_JSON_MINIMAL_ENCODING     0x08000000
#define OT4XB_FPFLAGS_JSON_CODEPAGE_OEM         0x01000000  
#define OT4XB_FPFLAGS_JSON_CODEPAGE_CUSTOM      0x02000000  //loword is the codepage 
#define OT4XB_FPFLAGS_JSON_CODEPAGE_UTF8        0x04000000
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
TZString::TZString( void )
{
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0; m_nMinPrintf = 1024;
}
// -----------------------------------------------------------------------------------------------------------------
TZString::TZString( LPSTR pStr )
{
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0; m_nMinPrintf = 1024;
   Add( pStr );
}
// -----------------------------------------------------------------------------------------------------------------
TZString::TZString( UINT cb )
{
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0; m_nMinPrintf = 1024;
   _grow_cb_( cb );
}
// -----------------------------------------------------------------------------------------------------------------
TZString::~TZString( void )
{
   if( m_pBuffer ) _xfree( (void *) m_pBuffer );
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0;
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::_reset_( void )
{
   UINT n;
   m_nLen = 0;
   _grow_cb_( 16 );
   for( n = 0; n < 16; n++ ) m_pBuffer[n] = 0;
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::_grow_cb_( UINT cb )
{
   cb &= 0x7FFFFFFF;
   if( m_nBuffSize <= cb )
   {
      UINT ncb = 64;
      while( ncb < cb ) ncb = ncb << 1;
      if( m_nBuffSize < ncb )
      {
         LPSTR pn = (LPSTR) _xgrab( ncb );
         if( m_pBuffer )
         {
            UINT n;
            for( n = 0; n < m_nLen; n++ ) pn[n] = m_pBuffer[n];
            _xfree( (void *) m_pBuffer );
         }
         m_pBuffer = pn; m_nBuffSize = ncb;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::operator+=( LPSTR  pStr )
{
   Add( pStr );
}
void TZString::operator+=( LPWSTR pWide )
{
   AddW( pWide );
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TZString::GetBuffer( void )
{
   return m_pBuffer;
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add( LPSTR pStr )
{
   UINT n;
   if( pStr )
   {
      for( n = 0; pStr[n]; n++ );
      _grow_cb_( n + m_nLen + 1 );
      for( n = 0; pStr[n]; n++ )
      {
         m_pBuffer[m_nLen] = pStr[n];
         m_nLen++;
      }
      m_pBuffer[m_nLen] = 0;
   }
}
DWORD TZString::AddStrCb( LPSTR pStr, DWORD cb, DWORD offset, DWORD  bytes_to_write, DWORD flags ) // flags & 1 = 1252 to utf8
{
   if( offset >= cb )
   {
      return 0;
   }
   cb = cb - offset;
   if( bytes_to_write < cb )
   {
      cb = bytes_to_write;
   }
   LPSTR p = _mk_ptr_( LPSTR, pStr, offset );
   for( ; cb && *p; p++, cb-- )
   {
      if( flags & 1 )
      {
         AddChar_1252_to_utf8( *p );
      }
      else
      {
         AddChar( *p );
      }
      offset++;
   }
   return offset;
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_RTrim( LPSTR pStr )
{
   UINT n;
   if( pStr )
   {
      for( n = 0; pStr[n]; n++ );
      _grow_cb_( n + m_nLen + 1 );
      for( n = 0; pStr[n]; n++ )
      {
         m_pBuffer[m_nLen] = pStr[n];
         m_nLen++;
      }
      while( n )
      {
         n--;
         if( pStr[n] == 0x20 )
         {
            m_nLen--;
         }
         else
         {
            n = 0;
         }
      }
      m_pBuffer[m_nLen] = 0;
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_LTrim( LPSTR pStr )
{
   if( pStr )
   {
      while( *pStr == 0x20 )
      {
         pStr++;
      }
      Add( pStr );
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_AllTrim( LPSTR pStr )
{
   if( pStr )
   {
      while( *pStr == 0x20 )
      {
         pStr++;
      }
      Add_RTrim( pStr );
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::AddW( LPWSTR pWide )
{
   if( pWide )
   {
      int cc = (int) _xstrlenW( pWide );
      if( cc )
      {
         LPSTR  pAnsi = _pt_next_( (UINT) cc + 16 );
         cc = WideCharToMultiByte( CP_ACP, WC_COMPOSITECHECK, pWide, cc, pAnsi, cc, 0, 0 );
         m_nLen += cc;
         m_pBuffer[m_nLen] = 0;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::AddChar( char ch )
{
   if( ch )
   {
      _grow_cb_( m_nLen + 4 );
      m_pBuffer[m_nLen] = ch;
      m_nLen++;
      m_pBuffer[m_nLen] = 0;
   }
}
// ------------------------------------------------------------------------------------------------------------------
void TZString::AddChar_1252_to_utf8( char ch )
{
   static const WORD w_1252_table[] =
   {
      0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
      0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
      0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
      0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
      0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
      0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
      0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
      0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178,
      0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7,0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
      0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7,0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
      0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7,0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
      0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7,0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
      0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7,0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
      0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7,0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
   };
   if( ch < 0x80 )
   {
      AddChar( ch );
      return;
   }
   WORD code = w_1252_table[(BYTE) ch];
   if( !code )
   {
      AddChar( 0x20 );
      return;
   }
   WORD uc = ( ( ( code << 2 ) & 0x1FF ) || ( code & 0x1F00 ) ) || 0xC080;
   AddChar( (char) ( ( uc >> 8 ) & 0xFF ) );
   AddChar( (char) ( uc & 0xFF ) );
}
static DWORD svc_value_need_quotes( LPSTR p, DWORD cb, DWORD flags )
{
   DWORD  need_quotes = 0;
   DWORD n;
   DWORD non_digit = 0;
   DWORD digit = 0;
   DWORD e_pressent = 0;
   for( n = 0; n < cb; n++ )
   {
      BYTE ch = (BYTE) p[n];
      if( ch == (BYTE) '\"' && flags && 0x800 )
      {
         ch = (BYTE) '\'';
      }

      if( ( ch >= (BYTE) '0' && ch <= (BYTE) '9' ) )
      {
         digit++;
      }
      else
      {
         switch( ch )
         {
            case 9: case 10: case 13:
            {
               if( !( flags & 0x400 ) )
               {
                  need_quotes |= 1;
               }
               break;
            }
            case (BYTE) '\"': case (BYTE) '\'':
            {
               need_quotes |= 1;
               non_digit++;
               break;
            }
            case (BYTE) '.': case (BYTE) '+': case (BYTE) '-': case (BYTE) '/':
            {
               digit++;
               break;
            }
            case (BYTE) ',':
            {
               need_quotes |= 1;
               break;
            }
            case (BYTE) 'e': case (BYTE) 'E':
            {
               e_pressent++;
               non_digit++;
               break;
            }
            default:
            {
               non_digit++;
               break;
            }
         }

      }
   }
   if( flags & 0x108 )
   {
      if( digit )
      {
         if( ( !non_digit ) || e_pressent == non_digit )
         {
            need_quotes |= 2;
            if( flags & 0x008 )
            {
               need_quotes |= 4;
            }
         }
      }
   }
   return need_quotes;
}

// ------------------------------------------------------------------------------------------------------------------------------------
   // flags
   // 0x0001 LTrim
   // 0x0002 Rtrim
   // 0x0008 put ' before numbers
   // 0x0100 quote numbers
   // 0x0200 do not convert 1252-to-utf8
   // 0x0400 CR LF or TAB to space 
   // 0x0800 double quote to single
   // 0x4000 limit length to 40
   // 0x8000 limit length to 80
   // 0xC000 limit length to 120
void TZString::str_1252_to_svc_utf8_cell( LPSTR p, DWORD cb, DWORD flags )
{

   DWORD pos;
   DWORD need_quotes;
   BOOL bInit = 0;
   DWORD nLen = 0;

   if( flags & 0xC000 )
   {
      DWORD cb_max = ( ( ( flags & 0xC000 ) >> 12 ) & 0xC ) * 100;
      if( cb > cb_max )
      {
         cb = cb_max;
      }
   }
   need_quotes = svc_value_need_quotes( p, cb, flags );

   if( need_quotes )
   {
      AddChar( '\"' );
   }
   if( need_quotes & 0x04 )
   {
      if( !( cb > 0 && ( p[cb] == '\'' || ( p[cb] == '\"' && flags & 0x800 ) ) ) )
      {
         AddChar( '\'' );
      }
   }
   char last_char = 0;
   for( pos = 0; pos < cb; pos++ )
   {
      char ch = p[pos];
      if( ch == (BYTE) '\"' && flags && 0x800 )
      {
         ch = (BYTE) '\'';
      }
      switch( ch )
      {
         case 9: case 10: case 13:
         {
            if( flags & 0x400 )
            {
               if( !( last_char == 13 || last_char == 10 || last_char == 9 || last_char == 32 ) )
               {
                  if( ( !( flags & 1 ) ) || bInit )
                  {
                     AddChar( 32 );
                  }
               }
            }
            else
            {
               if( ch == 9 )
               {
                  if( ( !( flags & 1 ) ) || bInit )
                  {
                     AddChar( 9 );
                  }
               }
               else
               {
                  if( !( last_char == 13 || last_char == 10 ) )
                  {
                     AddChar( 10 );
                     bInit = 1;
                  }
               }
            }
            break;
         }
         case (BYTE) '\"':
         {
            AddChar( '\"' );
            AddChar( '\"' );
            bInit = 1;
            break;
         }
         case 0x20:
         {
            if( ( !( flags & 1 ) ) || bInit )
            {
               if( !( flags & 0x400 && !( ( last_char == 13 || last_char == 10 || last_char == 9 || last_char == 32 ) ) ) )
               {
                  AddChar( 32 );
               }
            }
            break;
         }
         default:
         {
            if( ch < 32 )
            {
               ch = 32;
            }
            if( flags & 0x200 )
            {
               AddChar( ch );
            }
            else
            {
               AddChar_1252_to_utf8( ch );
            }
            break;
         }
      }
      if( ch != 0x20 )
      {
         nLen = m_nLen;
      }
      last_char = ch;
   }
   if( flags & 2 )
   {
      if( m_nLen > nLen )
      {
         m_nLen = nLen;
         m_pBuffer[m_nLen] = 0;
      }
   }
   if( need_quotes )
   {
      AddChar( 0x22 );
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::RTrim( void )
{
   if( m_nLen < 1 )
   {
      return;
   }
   while( m_nLen > 0 ? m_pBuffer[m_nLen - 1] == 0x20 : 0 )
   {
      m_nLen--;
      m_pBuffer[m_nLen] = 0;
   }

}
// -----------------------------------------------------------------------------------------------------------------
void TZString::TrimZ( BOOL bRealloc )
{
   UINT n;
   if( m_pBuffer )
   {
      if( m_nLen )
      {
         for( n = 0; m_pBuffer[n]; n++ );
         m_nLen = ( n ? n - 1 : 0 );
      }
      if( m_nBuffSize == ( m_nLen + 1 ) ) bRealloc = FALSE;
      if( bRealloc )
      {
         if( m_nLen )
         {
            LPSTR pn = (LPSTR) _xgrab( m_nLen + 1 );
            for( n = 0; n < m_nLen; n++ ) pn[n] = m_pBuffer[n];
            _xfree( (void *) m_pBuffer );
            m_pBuffer = pn; m_nBuffSize = m_nLen + 1;
         }
         else {
            _xfree( (void *) m_pBuffer ); m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TZString::Detach( UINT * pcb, UINT * pcs )
{
   LPSTR p = m_pBuffer;
   if( pcb ) pcb[0] = m_nLen;
   if( pcs ) pcs[0] = m_nBuffSize;
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TZString::Detach_mb2mb( UINT nAcpFrom, UINT nAcpTo, DWORD * pcb_out, DWORD flags1, DWORD flags2 )
{
   DWORD cbs = 0;
   LPSTR ps = Detach( (UINT *) &cbs );
   if( ( nAcpFrom == nAcpTo ) || ( !ps ) )
   {
      if( pcb_out )
      {
         *pcb_out = cbs;
      }
      return ps;
   }
   DWORD cbd = 0;
   LPSTR pd = mb2mb( ps, (int) cbs, (int *) &cbd, nAcpFrom, nAcpTo, flags1, flags2 );
   if( pcb_out )
   {
      *pcb_out = cbd;
   }
   _xfree( ps );
   ps = 0;
   return pd;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TZString::_pt_next_( UINT nSize )
{
   _grow_cb_( nSize + m_nLen + 1 );
   return _mk_ptr_( LPSTR, m_pBuffer, m_nLen );
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TZString::_pt_( void )
{
   _grow_cb_( m_nLen + 1 ); return m_pBuffer;
}
// -----------------------------------------------------------------------------------------------------------------
#include <stdio.h>
// -----------------------------------------------------------------------------------------------------------------
void TZString::printf( LPSTR pt, ... )
{
   if( pt )
   {
      LPSTR p = _pt_next_( m_nMinPrintf );
      va_list( arglist );
      va_start( arglist, pt );
      m_nLen += vsprintf( p, pt, arglist );
   }
}
// -----------------------------------------------------------------------------------------------------------------
CHAR TZString::LastChar( void )
{
   if( m_nLen && m_pBuffer ) return m_pBuffer[( m_nLen - 1 )];
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
ULONG TZString::len( void )
{
   if( m_nLen && m_pBuffer ) return m_nLen;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
ULONG TZString::dump( LPSTR pOut, ULONG cbMax )
{
   ULONG n = 0;
   if( pOut && m_pBuffer && m_nLen )
      for( ; ( n < m_nLen ) && ( n < cbMax ); n++ ) pOut[n] = m_pBuffer[n];
   return n;
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_cp850_to_html( LPSTR pStr, DWORD dwFlags )
{
   if( !pStr ) return;

   for( ; *pStr; pStr++ )
   {
      switch( (BYTE) *pStr )
      {
         case 0x0D:
         {
            if( dwFlags & 1 ) {
               Add( "<br \\>" ); if( ( (BYTE) pStr[1] ) == 0x0A ){
                  pStr++;
               }
            }
            else {
               AddChar( 0x0D );
            }
            break;
         }
         case 0x0A:
         {
            if( dwFlags & 1 ){
               Add( "<br \\>" );
            }
            else {
               AddChar( 0x0A );
            }
            break;
         }
         case 0x20:
         {
            if( dwFlags & 2 )
            {
               if( pStr[1] == 0x20 ){
                  Add( "&nbsp;" );
               }
               else {
                  AddChar( 0x20 );
               }
            }
            else {
               AddChar( 0x20 );
            }
            break;
         }
         case 0x26:
         {
            Add( "&amp;" ); break;
         }
         case 0x3C:
         {
            Add( "&lt;" ); break;
         }
         case 0x3E:
         {
            Add( "&gt;" ); break;
         }
         case 0x7F:
         {
            Add( "&nbsp;" ); break;
         }
         case 0x80:
         {
            Add( "&Ccedil;" ); break;
         }
         case 0x81:
         {
            if( dwFlags & 4 ){
               Add( "&Uuml;" );
            }
            else {
               Add( "&uuml;" );
            } break;
         }
         case 0x82:
         {
            if( dwFlags & 4 ){
               Add( "&Eacute;" );
            }
            else {
               Add( "&eacute;" );
            } break;
         }
         case 0x83:
         {
            if( dwFlags & 4 ){
               Add( "&Acirc;" );
            }
            else {
               Add( "&acirc;" );
            } break;
         }
         case 0x84:
         {
            if( dwFlags & 4 ){
               Add( "&Auml;" );
            }
            else {
               Add( "&auml;" );
            } break;
         }
         case 0x85:
         {
            if( dwFlags & 4 ){
               Add( "&Agrave;" );
            }
            else {
               Add( "&agrave;" );
            } break;
         }
         case 0x86:
         {
            if( dwFlags & 4 ){
               Add( "&Aring;" );
            }
            else {
               Add( "&aring;" );
            } break;
         }
         case 0x87:
         {
            if( dwFlags & 4 ){
               Add( "&Ccedil;" );
            }
            else {
               Add( "&ccedil;" );
            } break;
         }
         case 0x88:
         {
            if( dwFlags & 4 ){
               Add( "&Ecirc;" );
            }
            else {
               Add( "&ecirc;" );
            } break;
         }
         case 0x89:
         {
            if( dwFlags & 4 ){
               Add( "&Euml;" );
            }
            else {
               Add( "&euml;" );
            } break;
         }
         case 0x8A:
         {
            if( dwFlags & 4 ){
               Add( "&Egrave;" );
            }
            else {
               Add( "&egrave;" );
            } break;
         }
         case 0x8B:
         {
            if( dwFlags & 4 ){
               Add( "&Iuml;" );
            }
            else {
               Add( "&iuml;" );
            } break;
         }
         case 0x8C:
         {
            if( dwFlags & 4 ){
               Add( "&Icirc;" );
            }
            else {
               Add( "&icirc;" );
            } break;
         }
         case 0x8D:
         {
            if( dwFlags & 4 ){
               Add( "&Igrave;" );
            }
            else {
               Add( "&igrave;" );
            } break;
         }
         case 0x8E:
         {
            Add( "&Auml" ); break;
         }
         case 0x8F:
         {
            Add( "&Aring" ); break;
         }
         case 0x90:
         {
            Add( "&Eacute" ); break;
         }
         case 0x91:
         {
            if( dwFlags & 4 ){
               Add( "&Aelig" );
            }
            else {
               Add( "&aelig" );
            } break;
         }
         case 0x92:
         {
            Add( "&AElig" ); break;
         }
         case 0x93:
         {
            if( dwFlags & 4 ){
               Add( "&Ocirc;" );
            }
            else {
               Add( "&ocirc;" );
            } break;
         }
         case 0x94:
         {
            if( dwFlags & 4 ){
               Add( "&Ouml;" );
            }
            else {
               Add( "&ouml;" );
            } break;
         }
         case 0x95:
         {
            if( dwFlags & 4 ){
               Add( "&Ograve;" );
            }
            else {
               Add( "&ograve;" );
            } break;
         }
         case 0x96:
         {
            if( dwFlags & 4 ){
               Add( "&Ucirc;" );
            }
            else {
               Add( "&ucirc;" );
            } break;
         }
         case 0x97:
         {
            if( dwFlags & 4 ){
               Add( "&Ugrave;" );
            }
            else {
               Add( "&ugrave;" );
            } break;
         }
         case 0x98:
         {
            if( dwFlags & 4 ){
               Add( "&Yuml;" );
            }
            else {
               Add( "&yuml;" );
            } break;
         }
         case 0x99:
         {
            Add( "&Ouml;" ); break;
         }
         case 0x9A:
         {
            Add( "&Uuml;" ); break;
         }
         case 0x9B:
         {
            if( dwFlags & 4 ){
               Add( "&Oslash;" );
            }
            else {
               Add( "&oslash;" );
            } break;
         }
         case 0x9C:
         {
            Add( "&pound;" ); break;
         }
         case 0x9D:
         {
            Add( "&Oslash;" ); break;
         }
         case 0x9E:
         {
            Add( "&times;" ); break;
         }
         case 0x9F:
         {
            Add( "&fnof;" ); break;
         }
         case 0xA0:
         {
            if( dwFlags & 4 ){
               Add( "&Aacute;" );
            }
            else {
               Add( "&aacute;" );
            } break;
         }
         case 0xA1:
         {
            if( dwFlags & 4 ){
               Add( "&Iacute;" );
            }
            else {
               Add( "&iacute;" );
            } break;
         }
         case 0xA2:
         {
            if( dwFlags & 4 ){
               Add( "&Oacute;" );
            }
            else {
               Add( "&oacute;" );
            } break;
         }
         case 0xA3:
         {
            if( dwFlags & 4 ){
               Add( "&Uacute;" );
            }
            else {
               Add( "&uacute;" );
            } break;
         }
         case 0xA4:
         {
            if( dwFlags & 4 ){
               Add( "&Ntilde;" );
            }
            else {
               Add( "&ntilde;" );
            } break;
         }
         case 0xA5:
         {
            Add( "&Ntilde;" ); break;
         }
         case 0xA6:
         {
            Add( "&ordf;" ); break;
         }
         case 0xA7:
         {
            Add( "&ordm;" ); break;
         }
         case 0xA8:
         {
            Add( "&iquest;" ); break;
         }
         case 0xA9:
         {
            Add( "&reg;" ); break;
         }
         case 0xAA:
         {
            Add( "&not;" ); break;
         }
         case 0xAB:
         {
            Add( "&frac12;" ); break;
         }
         case 0xAC:
         {
            Add( "&frac14;" ); break;
         }
         case 0xAD:
         {
            Add( "&iexcl;" ); break;
         }
         case 0xAE:
         {
            Add( "&laquo;" ); break;
         }
         case 0xAF:
         {
            Add( "&raquo;" ); break;
         }
         case 0xB5:
         {
            Add( "&Aacute;" ); break;
         }
         case 0xB6:
         {
            Add( "&Acirc;" ); break;
         }
         case 0xB7:
         {
            Add( "&Agrave;" ); break;
         }
         case 0xB8:
         {
            Add( "&copy;" ); break;
         }
         case 0xBD:
         {
            Add( "&cent;" ); break;
         }
         case 0xBE:
         {
            Add( "&yen;" ); break;
         }
         case 0xC6:
         {
            if( dwFlags & 4 ){
               Add( "&Atilde;" );
            }
            else {
               Add( "&atilde;" );
            } break;
         }
         case 0xC7:
         {
            Add( "&Atilde;" ); break;
         }
         case 0xCF:
         {
            Add( "&curren;" ); break;
         }
         case 0xD0:
         {
            Add( "&eth;" ); break;
         }
         case 0xD1:
         {
            Add( "&ETH;" ); break;
         }
         case 0xD2:
         {
            Add( "&Ecirc;" ); break;
         }
         case 0xD3:
         {
            Add( "&Euml;" ); break;
         }
         case 0xD4:
         {
            Add( "&Egrave;" ); break;
         }
         case 0xD5:
         {
            Add( "&#305;" ); break;
         }
         case 0xD6:
         {
            Add( "&Iacute;" ); break;
         }
         case 0xD7:
         {
            Add( "&Icirc;" ); break;
         }
         case 0xD8:
         {
            Add( "&Iuml;" ); break;
         }
         case 0xDD:
         {
            Add( "&brvbar;" ); break;
         }
         case 0xDE:
         {
            Add( "&Igrave;" ); break;
         }
         case 0xE0:
         {
            Add( "&Oacute;" ); break;
         }
         case 0xE1:
         {
            Add( "&szlig;" ); break;
         }
         case 0xE2:
         {
            Add( "&Ocirc;" ); break;
         }
         case 0xE3:
         {
            Add( "&Ograve;" ); break;
         }
         case 0xE4:
         {
            if( dwFlags & 4 ){
               Add( "&Otilde;" );
            }
            else {
               Add( "&otilde;" );
            } break;
         }
         case 0xE5:
         {
            Add( "&Otilde;" ); break;
         }
         case 0xE6:
         {
            Add( "&micro;" ); break;
         }
         case 0xE7:
         {
            Add( "&thorn;" ); break;
         }
         case 0xE8:
         {
            Add( "&THORN;" ); break;
         }
         case 0xE9:
         {
            Add( "&Uacute;" ); break;
         }
         case 0xEA:
         {
            Add( "&Ucirc;" ); break;
         }
         case 0xEB:
         {
            Add( "&Ugrave;" ); break;
         }
         case 0xEC:
         {
            if( dwFlags & 4 ){
               Add( "&Yacute;" );
            }
            else {
               Add( "&yacute;" );
            } break;
         }
         case 0xED:
         {
            Add( "&Yacute;" ); break;
         }
         case 0xEE:
         {
            Add( "&macr;" ); break;
         }
         case 0xEF:
         {
            Add( "&acute;" ); break;
         }
         case 0xF0:
         {
            Add( "&shy;" ); break;
         }
         case 0xF1:
         {
            Add( "&plusmn;" ); break;
         }
         case 0xF3:
         {
            Add( "&frac34;" ); break;
         }
         case 0xF4:
         {
            Add( "&para;" ); break;
         }
         case 0xF5:
         {
            Add( "&sect;" ); break;
         }
         case 0xF6:
         {
            Add( "&divide;" ); break;
         }
         case 0xF7:
         {
            Add( "&cedil;" ); break;
         }
         case 0xF8:
         {
            Add( "&deg;" ); break;
         }
         case 0xF9:
         {
            Add( "&uml;" ); break;
         }
         case 0xFA:
         {
            Add( "&middot;" ); break;
         }
         case 0xFB:
         {
            Add( "&sup1;" ); break;
         }
         case 0xFC:
         {
            Add( "&sup3;" ); break;
         }
         case 0xFD:
         {
            Add( "&sup2;" ); break;
         }
         case 0xFF:
         {
            Add( "&nbsp;" ); break;
         }
         default:
         {
            if( ( *pStr < 0x20 ) || ( *pStr > 0x7E ) ) {
               Add( "&nbsp;" );
            }
            else
            {
               if( ( dwFlags & 4 ) && ( ( (BYTE) *pStr ) >= 'a' ) && ( *pStr <= 'z' ) ){
                  AddChar( ( ( (BYTE) *pStr ) ) - ( 'a' - 'A' ) );
               }
               else AddChar( *pStr );
            }
            break;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_cp437_to_html( LPSTR pStr, DWORD dwFlags )
{
   if( !pStr ) return;

   for( ; *pStr; pStr++ )
   {
      switch( (BYTE) *pStr )
      {
         case 0x0D:
         {
            if( dwFlags & 1 ) {
               Add( "<br \\>" ); if( ( (BYTE) pStr[1] ) == 0x0A ){
                  pStr++;
               }
            }
            else {
               AddChar( 0x0D );
            }
            break;
         }
         case 0x0A:
         {
            if( dwFlags & 1 ){
               Add( "<br \\>" );
            }
            else {
               AddChar( 0x0A );
            }
            break;
         }
         case 0x20:
         {
            if( dwFlags & 2 )
            {
               if( pStr[1] == 0x20 ){
                  Add( "&nbsp;" );
               }
               else {
                  AddChar( 0x20 );
               }
            }
            else {
               AddChar( 0x20 );
            }
            break;
         }
         case 0x26:
         {
            Add( "&amp;" ); break;
         }
         case 0x3C:
         {
            Add( "&lt;" ); break;
         }
         case 0x3E:
         {
            Add( "&gt;" ); break;
         }
         case 0x7F:
         {
            Add( "&nbsp;" ); break;
         }
         case 0x80:
         {
            Add( "&Ccedil;" ); break;
         }
         case 0x81:
         {
            if( dwFlags & 4 ){
               Add( "&Uuml;" );
            }
            else {
               Add( "&uuml;" );
            } break;
         }
         case 0x82:
         {
            if( dwFlags & 4 ){
               Add( "&Egrave;" );
            }
            else {
               Add( "&egrave;" );
            } break;
         }
         case 0x83:
         {
            if( dwFlags & 4 ){
               Add( "&Acirc;" );
            }
            else {
               Add( "&acirc;" );
            } break;
         }
         case 0x84:
         {
            if( dwFlags & 4 ){
               Add( "&Auml;" );
            }
            else {
               Add( "&auml;" );
            } break;
         }
         case 0x85:
         {
            if( dwFlags & 4 ){
               Add( "&Agrave;" );
            }
            else {
               Add( "&agrave;" );
            } break;
         }
         case 0x86:
         {
            if( dwFlags & 4 ){
               Add( "&Aring;" );
            }
            else {
               Add( "&aring;" );
            } break;
         }
         case 0x87:
         {
            if( dwFlags & 4 ){
               Add( "&Ccedil;" );
            }
            else {
               Add( "&ccedil;" );
            } break;
         }
         case 0x88:
         {
            if( dwFlags & 4 ){
               Add( "&Ecirc;" );
            }
            else {
               Add( "&ecirc;" );
            } break;
         }
         case 0x89:
         {
            if( dwFlags & 4 ){
               Add( "&Euml;" );
            }
            else {
               Add( "&euml;" );
            } break;
         }
         case 0x8A:
         {
            if( dwFlags & 4 ){
               Add( "&Egrave;" );
            }
            else {
               Add( "&egrave;" );
            } break;
         }
         case 0x8B:
         {
            if( dwFlags & 4 ){
               Add( "&Iuml;" );
            }
            else {
               Add( "&iuml;" );
            } break;
         }
         case 0x8C:
         {
            if( dwFlags & 4 ){
               Add( "&Icirc;" );
            }
            else {
               Add( "&icirc;" );
            } break;
         }
         case 0x8D:
         {
            if( dwFlags & 4 ){
               Add( "&Igrave;" );
            }
            else {
               Add( "&igrave;" );
            } break;
         }
         case 0x8E:
         {
            Add( "&Auml" ); break;
         }
         case 0x8F:
         {
            Add( "&Aring" ); break;
         }
         case 0x90:
         {
            Add( "&Eacute" ); break;
         }
         case 0x91:
         {
            if( dwFlags & 4 ){
               Add( "&Aelig" );
            }
            else {
               Add( "&aelig" );
            } break;
         }
         case 0x92:
         {
            Add( "&AElig" ); break;
         }
         case 0x93:
         {
            if( dwFlags & 4 ){
               Add( "&Ocirc" );
            }
            else {
               Add( "&ocirc" );
            } break;
         }
         case 0x94:
         {
            if( dwFlags & 4 ){
               Add( "&Ouml" );
            }
            else {
               Add( "&ouml" );
            } break;
         }
         case 0x95:
         {
            if( dwFlags & 4 ){
               Add( "&Ograve" );
            }
            else {
               Add( "&ograve" );
            } break;
         }
         case 0x96:
         {
            if( dwFlags & 4 ){
               Add( "&Ucirc" );
            }
            else {
               Add( "&ucirc" );
            } break;
         }
         case 0x97:
         {
            if( dwFlags & 4 ){
               Add( "&Ugrave" );
            }
            else {
               Add( "&ugrave" );
            } break;
         }
         case 0x98:
         {
            if( dwFlags & 4 ){
               Add( "&Yuml" );
            }
            else {
               Add( "&yuml" );
            } break;
         }
         case 0x99:
         {
            Add( "&Ouml" ); break;
         }
         case 0x9A:
         {
            Add( "&Uuml" ); break;
         }
         case 0x9B:
         {
            Add( "&cent;" ); break;
         }
         case 0x9C:
         {
            Add( "&pound;" ); break;
         }
         case 0x9D:
         {
            Add( "&yen;" ); break;
         }
         case 0x9E:
         {
            Add( "&#8359;" ); break;
         }
         case 0x9F:
         {
            Add( "&fnof;" ); break;
         }
         case 0xA0:
         {
            if( dwFlags & 4 ){
               Add( "&Aacute;" );
            }
            else {
               Add( "&aacute;" );
            } break;
         }
         case 0xA1:
         {
            if( dwFlags & 4 ){
               Add( "&Iacute;" );
            }
            else {
               Add( "&iacute;" );
            } break;
         }
         case 0xA2:
         {
            if( dwFlags & 4 ){
               Add( "&Oacute;" );
            }
            else {
               Add( "&oacute;" );
            } break;
         }
         case 0xA3:
         {
            if( dwFlags & 4 ){
               Add( "&Uacute;" );
            }
            else {
               Add( "&uacute;" );
            } break;
         }
         case 0xA4:
         {
            if( dwFlags & 4 ){
               Add( "&Ntilde;" );
            }
            else {
               Add( "&ntilde;" );
            } break;
         }
         case 0xA5:
         {
            Add( "&Ntilde;" ); break;
         }
         case 0xA6:
         {
            Add( "&ordf;" ); break;
         }
         case 0xA7:
         {
            Add( "&ordm;" ); break;
         }
         case 0xA8:
         {
            Add( "&iquest;" ); break;
         }
         case 0xA9:
         {
            Add( "&#8976;" ); break;
         }
         case 0xAA:
         {
            Add( "&not;" ); break;
         }
         case 0xAB:
         {
            Add( "&frac12;" ); break;
         }
         case 0xAC:
         {
            Add( "&frac14;" ); break;
         }
         case 0xAD:
         {
            Add( "&iexcl;" ); break;
         }
         case 0xAE:
         {
            Add( "&laquo;" ); break;
         }
         case 0xAF:
         {
            Add( "&raquo;" ); break;
         }
         case 0xE0:
         {
            Add( "&alpha;" ); break;
         }
         case 0xE1:
         {
            Add( "&szlig;" ); break;
         }
         case 0xE2:
         {
            Add( "&Gamma;" ); break;
         }
         case 0xE3:
         {
            Add( "&pi;" ); break;
         }
         case 0xE4:
         {
            Add( "&Sigma;" ); break;
         }
         case 0xE5:
         {
            Add( "&sigma;" ); break;
         }
         case 0xE6:
         {
            Add( "&micro;" ); break;
         }
         case 0xE7:
         {
            Add( "&tau;" ); break;
         }
         case 0xE8:
         {
            Add( "&Phi;" ); break;
         }
         case 0xE9:
         {
            Add( "&Theta;" ); break;
         }
         case 0xEA:
         {
            Add( "&Omega;" ); break;
         }
         case 0xEB:
         {
            Add( "&delta;" ); break;
         }
         case 0xEC:
         {
            Add( "&infin;" ); break;
         }
         case 0xED:
         {
            Add( "&phi;" ); break;
         }
         case 0xEE:
         {
            Add( "&epsilon;" ); break;
         }
         case 0xEF:
         {
            Add( "&#8745;" ); break;
         }
         case 0xF0:
         {
            Add( "&equiv;" ); break;
         }
         case 0xF1:
         {
            Add( "&plusmn;" ); break;
         }
         case 0xF2:
         {
            Add( "&ge;" ); break;
         }
         case 0xF3:
         {
            Add( "&le;" ); break;
         }
         case 0xF4:
         {
            Add( "&#8992;" ); break;
         }
         case 0xF5:
         {
            Add( "&#8993;" ); break;
         }
         case 0xF6:
         {
            Add( "&divide;" ); break;
         }
         case 0xF7:
         {
            Add( "&#8776;" ); break;
         }
         case 0xF8:
         {
            Add( "&deg;" ); break;
         }
         case 0xF9:
         {
            Add( "&#8729;" ); break;
         }
         case 0xFA:
         {
            Add( "&middot;" ); break;
         }
         case 0xFB:
         {
            Add( "&radic;" ); break;
         }
         case 0xFC:
         {
            Add( "&#8319;" ); break;
         }
         case 0xFD:
         {
            Add( "&sup2;" ); break;
         }
         case 0xFE:
         {
            Add( "&#9632;" ); break;
         }
         case 0xFF:
         {
            Add( "&nbsp;" ); break;
         }
         default:
         {
            if( ( ( (BYTE) *pStr ) < 0x20 ) || ( ( (BYTE) *pStr ) > 0x7E ) ) {
               Add( "&nbsp;" );
            }
            else
            {
               if( ( dwFlags & 4 ) && ( ( (BYTE) *pStr ) >= 'a' ) && ( ( (BYTE) *pStr ) <= 'z' ) )
               {
                  AddChar( ( *pStr ) - ( 'a' - 'A' ) );
               }
               else AddChar( *pStr );
            }
            break;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_cp1252_to_html( LPSTR pStr, DWORD dwFlags )
{
   if( !pStr ) return;

   for( ; *pStr; pStr++ )
   {
      switch( (BYTE) *pStr )
      {
         case 0x0D:
         {
            if( dwFlags & 1 ) {
               Add( "<br />" ); if( ( (BYTE) pStr[1] ) == 0x0A ){
                  pStr++;
               }
            }
            else {
               AddChar( 0x0D );
            }
            break;
         }
         case 0x0A:
         {
            if( dwFlags & 1 ){
               Add( "<br />" );
            }
            else {
               AddChar( 0x0A );
            }
            break;
         }
         case 0x20:
         {
            if( dwFlags & 2 )
            {
               if( pStr[1] == 0x20 ){
                  Add( "&nbsp;" );
               }
               else {
                  AddChar( 0x20 );
               }
            }
            else {
               AddChar( 0x20 );
            }
            break;
         }
         case 0x26:
         {
            Add( "&amp;" ); break;
         }
         case 0x22:
         {
            Add( "&quot;" ); break;
         }
         case 0x3C:
         {
            Add( "&lt;" ); break;
         }
         case 0x3E:
         {
            Add( "&gt;" ); break;
         }
         case 0x27:
         {
            Add( "&#39;" ); break;
         }
         case 0xA0:
         {
            Add( "&nbsp;" ); break;
         }
         case 0xA1:
         {
            Add( "&iexcl;" ); break;
         }
         case 0xA2:
         {
            Add( "&cent;" ); break;
         }
         case 0xA3:
         {
            Add( "&pound;" ); break;
         }
         case 0xA4:
         {
            Add( "&curren;" ); break;
         }
         case 0xA5:
         {
            Add( "&yen;" ); break;
         }
         case 0xA6:
         {
            Add( "&brvbar;" ); break;
         }
         case 0xA7:
         {
            Add( "&sect;" ); break;
         }
         case 0xA8:
         {
            Add( "&uml;" ); break;
         }
         case 0xA9:
         {
            Add( "&copy;" ); break;
         }
         case 0xAA:
         {
            Add( "&ordf;" ); break;
         }
         case 0xAB:
         {
            Add( "&laquo;" ); break;
         }
         case 0xAC:
         {
            Add( "&not;" ); break;
         }
         case 0xAD:
         {
            Add( "&shy;" ); break;
         }
         case 0xAE:
         {
            Add( "&reg;" ); break;
         }
         case 0xAF:
         {
            Add( "&macr;" ); break;
         }
         case 0xB0:
         {
            Add( "&deg;" ); break;
         }
         case 0xB1:
         {
            Add( "&plusmn;" ); break;
         }
         case 0xB2:
         {
            Add( "&sup2;" ); break;
         }
         case 0xB3:
         {
            Add( "&sup3;" ); break;
         }
         case 0xB4:
         {
            Add( "&acute;" ); break;
         }
         case 0xB5:
         {
            Add( "&micro;" ); break;
         }
         case 0xB6:
         {
            Add( "&para;" ); break;
         }
         case 0xB7:
         {
            Add( "&middot;" ); break;
         }
         case 0xB8:
         {
            Add( "&cedil;" ); break;
         }
         case 0xB9:
         {
            Add( "&sup1;" ); break;
         }
         case 0xBA:
         {
            Add( "&ordm;" ); break;
         }
         case 0xBB:
         {
            Add( "&raquo;" ); break;
         }
         case 0xBC:
         {
            Add( "&frac14;" ); break;
         }
         case 0xBD:
         {
            Add( "&frac12;" ); break;
         }
         case 0xBE:
         {
            Add( "&frac34;" ); break;
         }
         case 0xBF:
         {
            Add( "&iquest;" ); break;
         }
         case 0xC0:
         {
            Add( "&Agrave;" ); break;
         }
         case 0xC1:
         {
            Add( "&Aacute;" ); break;
         }
         case 0xC2:
         {
            Add( "&Acirc;" ); break;
         }
         case 0xC3:
         {
            Add( "&Atilde;" ); break;
         }
         case 0xC4:
         {
            Add( "&Auml;" ); break;
         }
         case 0xC5:
         {
            Add( "&Aring;" ); break;
         }
         case 0xC6:
         {
            Add( "&AElig;" ); break;
         }
         case 0xC7:
         {
            Add( "&Ccedil;" ); break;
         }
         case 0xC8:
         {
            Add( "&Egrave;" ); break;
         }
         case 0xC9:
         {
            Add( "&Eacute;" ); break;
         }
         case 0xCA:
         {
            Add( "&Ecirc;" ); break;
         }
         case 0xCB:
         {
            Add( "&Euml;" ); break;
         }
         case 0xCC:
         {
            Add( "&Igrave;" ); break;
         }
         case 0xCD:
         {
            Add( "&Iacute;" ); break;
         }
         case 0xCE:
         {
            Add( "&Icirc;" ); break;
         }
         case 0xCF:
         {
            Add( "&Iuml;" ); break;
         }
         case 0xD0:
         {
            Add( "&ETH;" ); break;
         }
         case 0xD1:
         {
            Add( "&Ntilde;" ); break;
         }
         case 0xD2:
         {
            Add( "&Ograve;" ); break;
         }
         case 0xD3:
         {
            Add( "&Oacute;" ); break;
         }
         case 0xD4:
         {
            Add( "&Ocirc;" ); break;
         }
         case 0xD5:
         {
            Add( "&Otilde;" ); break;
         }
         case 0xD6:
         {
            Add( "&Ouml;" ); break;
         }
         case 0xD7:
         {
            Add( "&times;" ); break;
         }
         case 0xD8:
         {
            Add( "&Oslash;" ); break;
         }
         case 0xD9:
         {
            Add( "&Ugrave;" ); break;
         }
         case 0xDA:
         {
            Add( "&Uacute;" ); break;
         }
         case 0xDB:
         {
            Add( "&Ucirc;" ); break;
         }
         case 0xDC:
         {
            Add( "&Uuml;" ); break;
         }
         case 0xDD:
         {
            Add( "&Yacute;" ); break;
         }
         case 0xDE:
         {
            Add( "&THORN;" ); break;
         }
         case 0xDF:
         {
            Add( "&szlig;" ); break;
         }
         case 0xE0:
         {
            if( dwFlags & 4 ){
               Add( "&Agrave;" );
            }
            else {
               Add( "&agrave;" );
            } break;
         }
         case 0xE1:
         {
            if( dwFlags & 4 ){
               Add( "&Aacute;" );
            }
            else {
               Add( "&aacute;" );
            } break;
         }
         case 0xE2:
         {
            if( dwFlags & 4 ){
               Add( "&Acirc;" );
            }
            else {
               Add( "&acirc;" );
            } break;
         }
         case 0xE3:
         {
            if( dwFlags & 4 ){
               Add( "&Atilde;" );
            }
            else {
               Add( "&atilde;" );
            } break;
         }
         case 0xE4:
         {
            if( dwFlags & 4 ){
               Add( "&Auml;" );
            }
            else {
               Add( "&auml;" );
            } break;
         }
         case 0xE5:
         {
            if( dwFlags & 4 ){
               Add( "&Aring;" );
            }
            else {
               Add( "&aring;" );
            } break;
         }
         case 0xE6:
         {
            if( dwFlags & 4 ){
               Add( "&Aelig;" );
            }
            else {
               Add( "&aelig;" );
            } break;
         }
         case 0xE7:
         {
            if( dwFlags & 4 ){
               Add( "&Ccedil;" );
            }
            else {
               Add( "&ccedil;" );
            } break;
         }
         case 0xE8:
         {
            if( dwFlags & 4 ){
               Add( "&Egrave;" );
            }
            else {
               Add( "&egrave;" );
            } break;
         }
         case 0xE9:
         {
            if( dwFlags & 4 ){
               Add( "&Eacute;" );
            }
            else {
               Add( "&eacute;" );
            } break;
         }
         case 0xEA:
         {
            if( dwFlags & 4 ){
               Add( "&Ecirc;" );
            }
            else {
               Add( "&ecirc;" );
            } break;
         }
         case 0xEB:
         {
            if( dwFlags & 4 ){
               Add( "&Euml;" );
            }
            else {
               Add( "&euml;" );
            } break;
         }
         case 0xEC:
         {
            if( dwFlags & 4 ){
               Add( "&Igrave;" );
            }
            else {
               Add( "&igrave;" );
            } break;
         }
         case 0xED:
         {
            if( dwFlags & 4 ){
               Add( "&Iacute;" );
            }
            else {
               Add( "&iacute;" );
            } break;
         }
         case 0xEE:
         {
            if( dwFlags & 4 ){
               Add( "&Icirc;" );
            }
            else {
               Add( "&icirc;" );
            } break;
         }
         case 0xEF:
         {
            if( dwFlags & 4 ){
               Add( "&Iuml;" );
            }
            else {
               Add( "&iuml;" );
            } break;
         }
         case 0xF0:
         {
            Add( "&eth;" ); break;
         }
         case 0xF1:
         {
            if( dwFlags & 4 ){
               Add( "&Ntilde;" );
            }
            else {
               Add( "&ntilde;" );
            } break;
         }
         case 0xF2:
         {
            if( dwFlags & 4 ){
               Add( "&Ograve;" );
            }
            else {
               Add( "&ograve;" );
            } break;
         }
         case 0xF3:
         {
            if( dwFlags & 4 ){
               Add( "&Oacute;" );
            }
            else {
               Add( "&oacute;" );
            } break;
         }
         case 0xF4:
         {
            if( dwFlags & 4 ){
               Add( "&Ocirc;" );
            }
            else {
               Add( "&ocirc;" );
            } break;
         }
         case 0xF5:
         {
            if( dwFlags & 4 ){
               Add( "&Otilde;" );
            }
            else {
               Add( "&otilde;" );
            } break;
         }
         case 0xF6:
         {
            if( dwFlags & 4 ){
               Add( "&Ouml;" );
            }
            else {
               Add( "&ouml;" );
            } break;
         }
         case 0xF7:
         {
            Add( "&divide;" ); break;
         }
         case 0xF8:
         {
            Add( "&oslash;" ); break;
         }
         case 0xF9:
         {
            if( dwFlags & 4 ){
               Add( "&Ugrave;" );
            }
            else {
               Add( "&ugrave;" );
            } break;
         }
         case 0xFA:
         {
            if( dwFlags & 4 ){
               Add( "&Uacute;" );
            }
            else {
               Add( "&uacute;" );
            } break;
         }
         case 0xFB:
         {
            if( dwFlags & 4 ){
               Add( "&Ucirc;" );
            }
            else {
               Add( "&ucirc;" );
            } break;
         }
         case 0xFC:
         {
            if( dwFlags & 4 ){
               Add( "&Uuml;" );
            }
            else {
               Add( "&uuml;" );
            } break;
         }
         case 0xFD:
         {
            if( dwFlags & 4 ){
               Add( "&Yacute;" );
            }
            else {
               Add( "&yacute;" );
            } break;
         }
         case 0xFE:
         {
            Add( "&thorn;" ); break;
         }
         case 0xFF:
         {
            if( dwFlags & 4 ){
               Add( "&Yuml;" );
            }
            else {
               Add( "&yuml;" );
            } break;
         }
         default:
         {
            if( ( ( (BYTE) *pStr ) < 0x20 ) || ( ( (BYTE) *pStr ) > 0x7E ) ) {
               Add( "&nbsp;" );
            }
            else
            {
               if( ( dwFlags & 4 ) && ( ( (BYTE) *pStr ) >= 'a' ) && ( ( (BYTE) *pStr ) <= 'z' ) )
               {
                  AddChar( ( *pStr ) - ( 'a' - 'A' ) );
               }
               else AddChar( *pStr );
            }
            break;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_to_sql( LPSTR pStr )
{
   if( !pStr ) return;
   DWORD cb = escape_to_sql_required_size((LPBYTE) pStr , (DWORD)-1) + 1;
   LPBYTE buffer = (LPBYTE) _pt_next_(cb);
   m_nLen +=  escape_to_sql_buffer((LPBYTE)pStr, (DWORD)-1, (LPBYTE) buffer, cb, (DWORD)escape_to_sql_buffer_flags::zero_terminated_string );
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_to_sql_bin(LPBYTE p, DWORD cb)
{
   if (!p) return;
   DWORD cbo = escape_to_sql_required_size(p,cb) + 1;
   LPBYTE buffer = (LPBYTE)_pt_next_(cb);
   m_nLen += escape_to_sql_buffer(p,cb,buffer, cbo, (DWORD) escape_to_sql_buffer_flags::binary_string);

}
void TZString::Add_to_sql_q(LPSTR pStr)
{
   if (!pStr) return;
   DWORD cb = escape_to_sql_required_size((LPBYTE)pStr, (DWORD)-1) + 1;
   LPBYTE buffer = (LPBYTE)_pt_next_(cb);
   m_nLen += escape_to_sql_buffer((LPBYTE)pStr, (DWORD)-1, (LPBYTE)buffer, cb,
             (DWORD)escape_to_sql_buffer_flags::zero_terminated_string || (DWORD)escape_to_sql_buffer_flags::add_quotes);
}
void TZString::Add_to_sql_bin_q(LPBYTE p, DWORD cb)
{
   if (!p) return;
   DWORD cbo = escape_to_sql_required_size(p, cb) + 1;
   LPBYTE buffer = (LPBYTE)_pt_next_(cb);
   m_nLen += escape_to_sql_buffer(p, cb, buffer, cbo, 
      (DWORD)escape_to_sql_buffer_flags::binary_string || (DWORD)escape_to_sql_buffer_flags::add_quotes);
}
// -----------------------------------------------------------------------------------------------------------------
void TZString::Add_to_xml( LPSTR pStr )
{
   if( !pStr ) return;

   for( ; *pStr; pStr++ )
   {
      switch( (BYTE) *pStr )
      {
         case 0x26:
         {
            Add( "&amp;" ); break;
         }
         case 0x22:
         {
            Add( "&quot;" ); break;
         }
         case 0x3C:
         {
            Add( "&lt;" ); break;
         }
         case 0x3E:
         {
            Add( "&gt;" ); break;
         }
         case 0x27:
         {
            Add( "&#39;" ); break;
         }
         default:
         {
            AddChar( *pStr );
            break;
         }
      }
   }
}
// -------------------------------------------------------------------------------------------------------------------


void TZString::Add_to_json( LPSTR pStr, int cb )
{
 //DWORD dwFlags = GetTlsHeapManager()->GetLastFpFlags();
   if( !pStr ) return;
   if( cb == -1 )
   {
      cb = (int) _xstrlen( pStr );
   }
   for( ; cb > 0; pStr++, cb-- )
   {
      BYTE ch = (BYTE) *pStr;
      switch( ch )
      {
         case 0x00:
         {
            Add( "\\u0000" ); break;
         }
         case 0x08:
         {
            Add( "\\b" ); break;
         }
         case 0x09:
         {
            Add( "\\t" ); break;
         }
         case 0x0A:
         {
            Add( "\\n" ); break;
         }
         case 0x0C:
         {
            Add( "\\f" ); break;
         }
         case 0x0D:
         {
            Add( "\\r" ); break;
         }
         case 0x22:
         {
            Add( "\\\"" ); break;
         }
         case '\\':
         {
            Add( "\\\\" ); break;
         }
         default:
         {
            if( ( ch > 31 ) && ( ch < 128 ) )
            {
               AddChar( ch );
            }
            else
            {
               WCHAR ws[4];
               char  sz[16]; ZeroMemory( sz, sizeof( sz ) );
               MultiByteToWideChar( 0, 0, (LPSTR) &ch, 1, ws, 4 );
               wsprintf( sz, "\\u%04.4X", MAKELONG( ws[0], 0 ) );
               Add( sz );
            }
            break;
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TByteStream::_grow_cb_( UINT cb )
{
   _grow_( cb );
}
// -----------------------------------------------------------------------------------------------------------------
LPBYTE TByteStream::Detach( UINT * pcb, UINT * pcs )
{
   LPBYTE p = (LPBYTE) m_pBuffer;
   if( pcb ) pcb[0] = m_nLen;
   if( pcs ) pcs[0] = m_nBuffSize;
   m_pBuffer = 0; m_nBuffSize = 0; m_nLen = 0;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
LPBYTE TByteStream::GetBuffer( void )
{
   return (LPBYTE) m_pBuffer;
}
// -----------------------------------------------------------------------------------------------------------------
ULONG TByteStream::len( void )
{
   return m_nLen;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TByteStream::Add( LPBYTE p, UINT cb )
{
   if( !p ){
      return FALSE;
   }
   if( ( (int) cb ) < 0 ){
      cb = _xstrlen( (LPSTR) p );
   }
   if( !cb ){
      return FALSE;
   }
   LPBYTE dst = (LPBYTE) _reserve_bytes_( cb + 1 );
   if( !dst ){
      return FALSE;
   }
   _bcopy( dst, (LPBYTE) p, cb );
   dst[cb] = 0;
   m_nLen += cb;
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
IStream * TByteStream::get_IStream( void )
{
   return ( IStream * ) new IByteStream( this );
}
// -----------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE  TByteStream::IByteStream::QueryInterface( REFIID iid, void ** ppvObject )
{
   if( ( iid == __uuidof( IUnknown ) ) || ( iid == __uuidof( IStream ) ) || ( iid == __uuidof( ISequentialStream ) ) )
   {
      *ppvObject = static_cast<IStream *>( this );
      AddRef();
      return S_OK;
   }
   return E_NOINTERFACE;
}
//----------------------------------------------------------------------------------------------------------------------
ULONG   STDMETHODCALLTYPE  TByteStream::IByteStream::AddRef( void )
{
   return (ULONG) InterlockedIncrement( &m_refcount );
}
//----------------------------------------------------------------------------------------------------------------------
ULONG   STDMETHODCALLTYPE  TByteStream::IByteStream::Release( void )
{
   ULONG n = (ULONG) InterlockedDecrement( &m_refcount );
   if( n == 0 )
   {
      delete this;
   }
   return n;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE  TByteStream::IByteStream::Read( void * pv, ULONG cb, ULONG * pcbRead )
{
   if( !pv )
   {
      return STG_E_INVALIDPOINTER;
   }
   DWORD cb_max = m_xstream->_offset_len_( m_pos );
   if( cb > cb_max )
   {
      cb = cb_max;
   }
   void * p = m_xstream->_offset_ptr_( m_pos, cb );
   _bcopy( (LPBYTE) pv, (LPBYTE) p, cb );
   m_pos += cb;
   if( pcbRead )
   {
      pcbRead[0] = cb;
   }
   return S_OK;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE  TByteStream::IByteStream::Write( void const * pv, ULONG cb, ULONG * pcbWritten )
{
   if( !pv )
   {
      return STG_E_INVALIDPOINTER;
   }

   void * p = m_xstream->_reserve_bytes_( m_pos, cb );
   if( !p )
   {
      return STG_E_MEDIUMFULL;
   }
   _bcopy( (LPBYTE) p, (LPBYTE) pv, cb );
   m_pos += cb;
   if( m_pos > m_xstream->m_nLen )
   {
      m_xstream->m_nLen = m_pos;
   }
   if( pcbWritten )
   {
      pcbWritten[0] = cb;
   }
   return S_OK;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::SetSize( ULARGE_INTEGER li )
{
   if( li.HighPart )
   {
      return STG_E_INVALIDFUNCTION; // only 32 bit supported
   }
   m_xstream->_grow_cb_( li.LowPart );
   if( li.LowPart > m_xstream->m_nBuffSize )
   {
      return STG_E_MEDIUMFULL;
   }
   m_xstream->m_nLen = li.LowPart;
   return S_OK;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::CopyTo( IStream *, ULARGE_INTEGER, ULARGE_INTEGER *, ULARGE_INTEGER * )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::Commit( DWORD )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::Revert( void )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::LockRegion( ULARGE_INTEGER, ULARGE_INTEGER, DWORD )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::UnlockRegion( ULARGE_INTEGER, ULARGE_INTEGER, DWORD )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::Clone( IStream ** )
{
   return E_NOTIMPL;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::Seek( LARGE_INTEGER liDistanceToMove, DWORD dwOrigin, ULARGE_INTEGER * lpNewPos )
{
   if( !( ( liDistanceToMove.HighPart == 0 ) || ( liDistanceToMove.HighPart == -1 ) ) )
   {
      return STG_E_INVALIDPARAMETER; // only 32 bit supported
   }
   LONG nPos = (LONG) m_pos;
   LONG nn = (LONG) liDistanceToMove.LowPart;
   switch( dwOrigin )
   {
      case STREAM_SEEK_SET:
      {
         nPos = nn;
         break;
      }
      case STREAM_SEEK_CUR:
      {
         nPos += nn;
         break;
      }
      case STREAM_SEEK_END:
      {
         nPos = ( (LONG) m_xstream->m_nLen ) - nn;
         break;
      }
      default:
      {
         return STG_E_INVALIDFUNCTION;
         break;
      }
   }
   if( nPos < 0 )
   {
      nPos = 0;
   }
   if( nPos > ( LONG ) m_xstream->m_nLen )
   {
      nPos = (LONG) m_xstream->m_nLen;
   }
   liDistanceToMove.LowPart = (DWORD) nPos;
   m_pos = (DWORD) nPos;
   if( lpNewPos )
   {
      lpNewPos->HighPart = 0;
      lpNewPos->LowPart = m_pos;
   }
   return S_OK;
}
//----------------------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE TByteStream::IByteStream::Stat( STATSTG * pStatstg, DWORD grfStatFlag )
{
   if( grfStatFlag == STATFLAG_NONAME )
   {
      pStatstg->cbSize.HighPart = 0;
      pStatstg->cbSize.LowPart = m_xstream->m_nLen;
      return S_OK;
   }
   return STG_E_INVALIDFLAG;

}
// -----------------------------------------------------------------------------------------------------------------

OT4XB_API TByteStream * __cdecl TByteStream_new( DWORD nInitialSize, DWORD nBlockSize )
{
   return new TByteStream( nInitialSize, nBlockSize );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void __cdecl TByteStream_destroy( TByteStream * pbs )
{
   delete pbs;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream__grow_( TByteStream * pbs, DWORD nNewSize )
{
   return pbs->_grow_( nNewSize );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void * __cdecl TByteStream__reserve_bytes_( TByteStream * pbs, DWORD nBytes )
{
   return pbs->_reserve_bytes_( nBytes );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void * __cdecl TByteStream__reserve_bytes_at( TByteStream * pbs, DWORD offset, DWORD nBytes )
{
   return pbs->_reserve_bytes_( offset, nBytes );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream__skip_bytes_( TByteStream * pbs, DWORD nBytes )
{
   return pbs->_skip_bytes_( nBytes );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void * __cdecl TByteStream__offset_ptr_( TByteStream * pbs, DWORD offset, DWORD cb )
{
   return pbs->_offset_ptr_( offset, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl TByteStream__offset_len_( TByteStream * pbs, DWORD offset )
{
   return pbs->_offset_len_( offset );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl TByteStream__truncate_buffer_( TByteStream * pbs, DWORD len )
{
   return pbs->_truncate_buffer_( len );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_buffer( TByteStream * pbs, void * p, DWORD cb )
{
   return pbs->append_buffer( p, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_BYTE( TByteStream * pbs, BYTE n )
{
   return pbs->append_BYTE( n );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_WORD( TByteStream * pbs, WORD n )
{
   return pbs->append_WORD( n );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_DWORD( TByteStream * pbs, DWORD n )
{
   return pbs->append_DWORD( n );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_ansi_to_utf8( TByteStream * pbs, LPSTR pa, int cb )
{
   return pbs->append_ansi_to_utf8( pa, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_ansi_to_xform_utf8( TByteStream * pbs, LPSTR p, int cb, int nLevel )
{
   return pbs->append_ansi_to_xform_utf8( p, cb, nLevel );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_decode_base64( TByteStream * pbs, LPSTR p, int cb )
{
   return pbs->append_decode_base64( p, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_decode_qp( TByteStream * pbs, LPSTR p, int cb, DWORD nFlags )// flags: 1 dot , 2 add CRLF
{
   return pbs->append_decode_qp( p, cb, nFlags );// flags: 1 dot , 2 add CRLF;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_append_decode_uu( TByteStream * pbs, LPSTR p, int cb )
{
   return pbs->append_decode_uu( p, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void __cdecl TByteStream_ansi_ZTrim( TByteStream * pbs )
{
   return pbs->ansi_ZTrim();
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void __cdecl TByteStream_ansi_ZSafe( TByteStream * pbs )
{
   return pbs->ansi_ZSafe();
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void __cdecl TByteStream__grow_cb_( TByteStream * pbs, UINT cb )
{
   return pbs->_grow_cb_( cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE __cdecl TByteStream_Detach( TByteStream * pbs, UINT * pcb, UINT * pcs )
{
   return pbs->Detach( pcb, pcs );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPBYTE __cdecl TByteStream_GetBuffer( TByteStream * pbs )
{
   return pbs->GetBuffer();
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ULONG __cdecl TByteStream_len( TByteStream * pbs )
{
   return pbs->len();
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __cdecl TByteStream_Add( TByteStream * pbs, LPBYTE p, UINT cb )
{
   return pbs->Add( p, cb );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API IStream * __cdecl TByteStream_get_IStream( TByteStream * pbs )
{
   return pbs->get_IStream();
}
//----------------------------------------------------------------------------------------------------------------------



