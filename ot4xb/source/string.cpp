//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <string>
#include <atlenc.h>
//----------------------------------------------------------------------------------------------------------------------
#define MSNIBBLE( ch ) (( ch >> (BYTE) 4) & (BYTE)0x0F)
#define LSNIBBLE( ch ) ( ch & (BYTE)0x0F)
//----------------------------------------------------------------------------------------------------------------------
static char  _pStaticYesNoChar_[ ] = "Y\0N\0";
// -----------------------------------------------------------------------------------------------------------------
static LONG _cHex2Bin_Ex_Mode_ = 1;
//----------------------------------------------------------------------------------------------------------------------
#include "crc32.hpp"
//----------------------------------------------------------------------------------------------------------------------
typedef union DWCHARUNION__union
{
   BYTE  ch[ 4 ];
   DWORD dw;
   int   i;
}  DWCHARUNION;
//----------------------------------------------------------------------------------------------------------------------
typedef union QWCHARUNION__union
{
   BYTE     ch[ 8 ];
   LONGLONG qw;
}  QWCHARUNION;
//----------------------------------------------------------------------------------------------------------------------
static BYTE __HEXNIBBLE__[ ] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
// -----------------------------------------------------------------------------------------------------------------
static BYTE __DEFAULT_WHITE_SPACE_TABLE__[ ] = { 0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

// -----------------------------------------------------------------------------------------------------------------
static BYTE __SAFECHAR__[ ] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
                        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
                        0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
// ----------------------------------------------------------------------------------------------------------------
static BYTE __NIBBLECHAR__[ ] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
// ---------------------------------------------------------------------------------------------------------------------
static BYTE __TEMPLATE_09_AZ_NOCASE__[ ] = { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                                 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
                                 0x40, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
                                 0x60, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
                                 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
                                 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
                                 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
                                 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF };
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nCRC32
            | syntax_: `nCRC32( nCRC32, cBuffer [, nLen] [, @nStart] )`
            | category: string
            | _kw_: nCRC32, Function
   }}*/
/*{{|desc: Calculates a CRC32 value for a character buffer, optionally processing only a byte range.
    | params:
    - `nCRC32` Numeric - Initial CRC32 value. Use 0 for the first block, or the previous return value when
      calculating a CRC32 in several chunks. The parameter is also updated with the returned CRC32 value when
      possible.
    - `cBuffer` Character - Buffer whose bytes are used for the CRC calculation.
    - `nLen` Numeric - Optional number of bytes to process. If omitted, bytes are processed from nStart to
      the end of cBuffer.
    - `nStart` Numeric by reference - Optional zero-based byte offset where processing starts. On success
      it is updated to the byte offset immediately after the processed block.

    Returns Returns the CRC32 value. Returns NIL if cBuffer cannot be locked as a character buffer or if
      nStart/nLen selects a range outside cBuffer.

    |note: nCRC32() always returns the value using the internal 32-bit integer representation. Since Xbase++
      does not expose an internal unsigned 32-bit integer format for this value, CRC32 values with the high bit
      set may be displayed as negative numbers. The bit pattern is preserved. To view the value as a positive
      number, format it as text with cPrintf-style formatting or pass it through unsigned32(), which returns a
      double when the unsigned 32-bit value cannot be represented as a signed LONG. }}*/
XPPRET XPPENTRY NCRC32( XppParamList pl )
{
   DWCHARUNION dwu;
   BOOL        bByRef;
   ContainerHandle conStr = _conParam( pl, 2, &bByRef );
   ULONG       nBuffLen, nLen;
   LPBYTE      pStr;
   ULONG       nStart = _parLong( pl, 4 );

   if( ot4xb_conRLockC( conStr, (LPSTR*) &pStr, &nBuffLen ) != 0 )
   {
      if( !bByRef )
      {
         _conRelease( conStr );
      } _ret( pl ); return;
   }
   if( nStart > 0 )
   {
      if( nStart >= nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
      nLen = ( ( _partype( pl, 3 ) & XPP_NUMERIC ) ? (ULONG) _parLong( pl, 3 ) : nBuffLen - nStart );
      if( nStart + nLen > nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
      pStr += nStart;  nBuffLen -= nStart;
   }
   else
   {
      nLen = ( ( _partype( pl, 3 ) & XPP_NUMERIC ) ? (ULONG) _parLong( pl, 3 ) : nBuffLen );
      if( nLen > nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
   }
   dwu.i = _parLong( pl, 1 );
   dwu.dw = dwCrc32( dwu.dw, pStr, nLen );
   ot4xb_conUnlockC( conStr ); if( !bByRef )_conRelease( conStr );
   _stornl( nStart + nLen, pl, 4, 0 );
   _stornl( dwu.i, pl, 1, 0 );
   _retnl( pl, dwu.i );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl dwCrc8( DWORD dwCrc, char* data, int length );
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nCRC8
            | syntax_: `nCRC8( nCRC8, cBuffer [, nLen] [, @nStart] )`
            | category: string
            | _kw_: nCRC8, Function
   }}*/
/*{{|desc: Calculates a CRC8 value for a character buffer, optionally processing only a byte range.
    | params:
    - `nCRC8` Numeric - Initial CRC8 value. Use 0 for the first block, or the previous return value when
      calculating a CRC8 in several chunks. The parameter is also updated with the returned CRC8 value when
      possible.
    - `cBuffer` Character - Buffer whose bytes are used for the CRC calculation.
    - `nLen` Numeric - Optional number of bytes to process. If omitted, bytes are processed from nStart to
      the end of cBuffer.
    - `nStart` Numeric by reference - Optional zero-based byte offset where processing starts. On success
      it is updated to the byte offset immediately after the processed block.

    Returns Returns the CRC8 value as a positive numeric value in the 0..255 range. Returns NIL if cBuffer
      cannot be locked as a character buffer or if nStart/nLen selects a range outside cBuffer. }}*/
XPPRET XPPENTRY NCRC8( XppParamList pl )
{
   DWCHARUNION dwu;
   BOOL        bByRef;
   ContainerHandle conStr = _conParam( pl, 2, &bByRef );
   ULONG       nBuffLen, nLen;
   LPBYTE      pStr;
   ULONG       nStart = _parLong( pl, 4 );

   if( ot4xb_conRLockC( conStr, (LPSTR*) &pStr, &nBuffLen ) != 0 )
   {
      if( !bByRef )
      {
         _conRelease( conStr );
      } _ret( pl ); return;
   }
   if( nStart > 0 )
   {
      if( nStart >= nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
      nLen = ( ( _partype( pl, 3 ) & XPP_NUMERIC ) ? (ULONG) _parLong( pl, 3 ) : nBuffLen - nStart );
      if( nStart + nLen > nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
      pStr += nStart;  nBuffLen -= nStart;
   }
   else
   {
      nLen = ( ( _partype( pl, 3 ) & XPP_NUMERIC ) ? (ULONG) _parLong( pl, 3 ) : nBuffLen );
      if( nLen > nBuffLen )
      {
         ot4xb_conUnlockC( conStr ); if( !bByRef )
         {
            _conRelease( conStr );
         } _ret( pl ); return;
      }
   }
   dwu.i = _parLong( pl, 1 );
   dwu.dw = dwCrc8( dwu.dw, (LPSTR) pStr, (int) nLen );
   ot4xb_conUnlockC( conStr ); if( !bByRef )_conRelease( conStr );
   _stornl( nStart + nLen, pl, 4, 0 );
   _stornl( dwu.i, pl, 1, 0 );
   _retnl( pl, dwu.i );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------






//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ChrR
            | syntax_: `ChrR( nChar1 [, ... nCharN, nRepeat] )`
            | category: string
            | _kw_: ChrR, Function
   }}*/
/*{{|desc: Builds a character string from numeric character codes, optionally repeating the whole sequence.
    | params:
    - `nChar1...nCharN` Numeric - Character codes to place in the generated string. Each value is converted
      to one byte.
    - `nRepeat` Numeric - Repeat count. When more than one parameter is supplied, the last parameter is
      interpreted as the repeat count and all previous parameters form the character sequence to repeat.

    Returns Returns the generated character string. With one parameter, ChrR(nChar) behaves like Chr(nChar).
      With no parameters, returns an empty string.

    |note: ChrR( 0, nSize ) is a convenient way to create a zero-filled buffer with nSize bytes.

    |example: ? ChrR( 13, 10, 2 ) // CRLF + CRLF ? ChrR( 0, 1024 ) // 1024 zero bytes }}*/
XPPRET XPPENTRY CHRR( XppParamList pl )
{
   ULONG nParams = (ULONG) _partype( pl, 0 );
   if( nParams > 1 )
   {
      ULONG nRep = (ULONG) _parLong( pl, nParams );
      ULONG nLen = (ULONG) ( ( nParams - 1 ) * nRep );
      LPSTR pStr = (LPSTR) _xgrab( nLen );
      ULONG np;
      nParams--;
      for( np = 0; np < nParams; np++ )
      {
         char ch = (char) _parLong( pl, np + 1 );
         ULONG n, nn;
         for( nn = 0, n = np; nn < nRep; nn++, n += nParams ) pStr[ n ] = ch;
      }
      _retclen( pl, pStr, nLen );
      _xfree( (void*) pStr );
   }
   else if( nParams == 1 ) // Chrr(13) == Chr(13)
   {
      char ch = (char) _parLong( pl, 1 );
      _retclen( pl, &ch, 1 );
   }
   else _retc( pl, "" );


}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MkScStr
            | syntax_: `MkScStr( nChar, cColorBytes )`
            | category: string
            | _kw_: MkScStr, Function
   }}*/
/*{{|desc: Makes an old Clipper-style screen string. Console screen captures used one byte for the character
      code, followed by one byte for the color attribute; this helper repeats one character code with a sequence
      of color bytes.
    | params:
    - `nChar` Numeric - Character code placed in the low byte of each generated screen cell.
    - `cColorBytes` Character - Color attribute bytes placed in the high byte of each generated screen
      cell.

    Returns Returns a binary string twice as long as cColorBytes. For each color byte, the function appends
      the character byte first and the color byte after it. Returns an empty string when cColorBytes is empty or
      not supplied.

    |note: This is a legacy helper for old console/screen-buffer style strings. }}*/
XPPRET XPPENTRY MKSCSTR( XppParamList pl )
{

   CON_PLKSTREX plk;
   CHAR  ch = (CHAR) ( _parLong( pl, 1, 0 ) & 0xFF );
   LPSTR pSrc = _conParamRLockStrEx( pl, 2, &plk );
   ULONG nLen = plk.nLen;
   ContainerHandle conr = _conPutC( NULLCONTAINER, "" );
   if( pSrc && nLen )
   {

      WORD* pw = (WORD*) _xgrab( nLen * 2 );
      ULONG n;
      for( n = 0; n < nLen; n++ ) pw[ n ] = MAKEWORD( ch, pSrc[ n ] );
      _conPutCL( conr, (LPSTR) pw, ( nLen * 2 ) );
      _xfree( (void*) pw );
   }
   _conParamUnLockStrEx( &plk );
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lStrBitSet
            | syntax_: `lStrBitSet( @cStr, nBit [, lNewSetting] )`
            | category: string/bit
            | _kw_: lStrBitSet, Function
   }}*/
/*{{|desc: Tests and optionally changes one bit inside a character string.
    | params:
    - `cStr` Character by reference - String whose bytes contain the bit to test or change.
    - `nBit` Numeric - One-based bit position. Bit 1 is the low bit of the first byte, bit 8 is the high
      bit of the first byte, and bit 9 is the low bit of the second byte.
    - `lNewSetting` Logical - Optional new value for the bit. When omitted, the function only tests the
      bit. When supplied, the string is write-locked and the bit is set or cleared.

    Returns Returns .T. if the bit was set before any optional change, or .F. if it was clear or the requested
      bit is outside the string. Returns NIL when nBit is not greater than zero or the string cannot be locked.

    |note: This is useful for using a character string as a compact bitset, packing many boolean flags into a
      small buffer. }}*/
XPPRET XPPENTRY LSTRBITSET( XppParamList pl )
{
   ULONG nBit = (ULONG) _parLong( pl, 2 );
   if( nBit > 0 )
   {
      ULONG nByte = (ULONG) ( ( nBit - 1 ) >> 3 );
      BOOL  bByRef = FALSE;
      ContainerHandle conStr = _conParam( pl, 1, &bByRef );
      LPBYTE pStr = (LPBYTE) 0;
      ULONG nLen = 0;
      BOOL  bWrite = (BOOL) ( _partype( pl, 0 ) > 2 );
      BYTE  chMask;
      BYTE ch;
      BOOL bOn;

      if( conStr == NULLCONTAINER )
      {
         _ret( pl ); return;
      } // Error: missing 1st parameter
      if( bWrite )
      {
         if( ot4xb_conWLockC( conStr, (LPSTR*) &pStr, &nLen ) != 0 )
         {
            _ret( pl );
            if( !bByRef ) _conRelease( conStr );
            return; // Error: error while locking the write pointer
         }
      }
      else if( ot4xb_conRLockC( conStr, (LPSTR*) &pStr, &nLen ) != 0 )
      {
         if( !bByRef ) _conRelease( conStr );
         _ret( pl ); return; // Error: error while locking the read pointer
      }
      if( nByte >= nLen )
      {
         ot4xb_conUnlockC( conStr );
         if( !bByRef ) _conRelease( conStr );
         _retl( pl, FALSE ); return; // .F. request position exceds the string length
      }
      chMask = (BYTE) ( (BYTE) ( 0x01 ) << (BYTE) ( ( nBit - 1 ) - ( nByte << 3 ) ) );
      ch = (BYTE) pStr[ nByte ];
      bOn = (BOOL) ( ch & chMask );
      if( bWrite )
      {
         BOOL bSet = (BOOL) _parl( pl, 3 );
         if( bSet ) pStr[ nByte ] |= chMask;
         else if( bOn ) pStr[ nByte ] ^= chMask;
      }
      ot4xb_conUnlockC( conStr );
      if( !bByRef ) _conRelease( conStr );
      _retl( pl, bOn );
   }
   else _ret( pl );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lPStrBitSet
            | syntax_: `lPStrBitSet( pStr, nBit [, lNewSetting] [, nLen] )`
            | category: string/bit
            | _kw_: lPStrBitSet, Function
   }}*/
/*{{|desc: Tests and optionally changes one bit inside a memory buffer addressed by a pointer.
    | params:
    - `pStr` Numeric pointer - Pointer to the memory buffer whose bytes contain the bit to test or change.
    - `nBit` Numeric - One-based bit position. Bit 1 is the low bit of the first byte, bit 8 is the high
      bit of the first byte, and bit 9 is the low bit of the second byte.
    - `lNewSetting` Logical - Optional new value for the bit. When omitted or not logical, the function
      only tests the bit. When supplied as logical, the bit is set or cleared in the pointed memory.
    - `nLen` Numeric - Length of the memory buffer in bytes. It should be supplied when using this function
      because the first parameter is only a raw pointer. When omitted, the code uses 0xFFFFFFFF as the limit;
      this does not mean the pointed buffer has that length.

    Returns Returns .T. if the bit was set before any optional change, or .F. if it was clear. Returns NIL
      when nBit is not greater than zero, pStr is zero, or nBit falls outside nLen.

    |note: This is the pointer-based variant of lStrBitSet(), kept for code that works directly with memory
      pointers. Since the pointer does not carry the binary buffer length, use nLen to keep the bit access
      bounded. Omitting nLen is unsafe: if nBit points outside the real memory buffer, the function may read or
      write out of bounds and crash the process. }}*/
XPPRET XPPENTRY LPSTRBITSET( XppParamList pl )
{
   ULONG nBit = (ULONG) _parLong( pl, 2 );
   if( nBit > 0 )
   {
      ULONG nByte = (ULONG) ( ( nBit - 1 ) >> 3 );
      LPBYTE pStr = (LPBYTE) _parLong( pl, 1 );
      ULONG nLen = (ULONG) ( ( _partype( pl, 4 ) & XPP_NUMERIC ) ? _parLong( pl, 4 ) : ( (ULONG) -1 ) );
      BOOL  bWrite = (BOOL) ( _partype( pl, 3 ) & XPP_LOGICAL );
      BYTE  chMask;
      BYTE ch;
      BOOL bOn;

      if( ( nByte >= nLen ) || ( pStr == 0 ) )
      {
         _ret( pl ); return; // Error request position exceds the string length
      }
      chMask = (BYTE) ( (BYTE) ( 0x01 ) << (BYTE) ( ( nBit - 1 ) - ( nByte << 3 ) ) );
      ch = (BYTE) pStr[ nByte ];
      bOn = (BOOL) ( ch & chMask );
      if( bWrite )
      {
         BOOL bSet = (BOOL) _parl( pl, 3 );
         if( bSet ) pStr[ nByte ] |= chMask;
         else if( bOn ) pStr[ nByte ] ^= chMask;
      }
      _retl( pl, bOn );
   }
   else _ret( pl );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cStrBitNot
            | syntax_: `cStrBitNot( @cStr )`
            | category: string/bit
            | _kw_: cStrBitNot, Function
   }}*/
/*{{|desc: Inverts all bits in a character string.
    | params:
    - `cStr` Character by reference - String whose bytes are modified in place.

    Returns Returns the modified string. Each byte is XORed with 0xFF, so every bit is flipped. Returns NIL if
      cStr is not a character value or cannot be write-locked. }}*/
XPPRET XPPENTRY CSTRBITNOT( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, 1, &bByRef, XPP_CHARACTER );
   if( con != NULLCONTAINER )
   {
      LPSTR pStr = (LPSTR) 0;
      ULONG nLen = 0;
      if( ot4xb_conWLockC( con, &pStr, &nLen ) == 0 )
      {
         ULONG n;
         CHAR  ch = -1;
         for( n = 0; n < nLen; n++ ) pStr[ n ] ^= ch;
         ot4xb_conUnlockC( con );
         _conReturn( pl, con );
         if( !bByRef ) _conRelease( con );
      }
      else
      {
         if( !bByRef )
         {
            _conRelease( con );
         } _ret( pl ); return;
      }
   }
   else
   {
      _ret( pl ); return;
   }

}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PStrBitNot
            | syntax_: `PStrBitNot( pStr, nLen )`
            | category: string/bit
            | _kw_: PStrBitNot, Function
   }}*/
/*{{|desc: Inverts all bits in a memory buffer addressed by a pointer.
    | params:
    - `pStr` Numeric pointer - Pointer to the memory buffer to modify.
    - `nLen` Numeric - Number of bytes to modify.

    Returns Returns pStr. When pStr is not zero and nLen is not zero, each byte in the memory range is XORed
      with 0xFF, so every bit is flipped.

    |note: This is the pointer-based variant of cStrBitNot(). The caller must ensure that pStr points to a
      writable buffer of at least nLen bytes. }}*/
XPPRET XPPENTRY PSTRBITNOT( XppParamList pl )
{
   LPSTR pStr = (LPSTR) _parLong( pl, 1 );
   ULONG nLen = (ULONG) _parLong( pl, 2 );
   if( ( pStr != 0 ) && ( nLen != 0 ) )
   {
      ULONG n;
      CHAR  ch = -1;
      for( n = 0; n < nLen; n++ ) pStr[ n ] ^= ch;
   }
   _retnl( pl, (LONG) pStr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cStrBitOR
            | syntax_: `cStrBitOR( @cStr, cMask [, lRotate] )`
            | category: string/bit
            | _kw_: cStrBitOR, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise OR between two character strings.
    | params:
    - `cStr` Character by reference - Target string modified in place.
    - `cMask` Character - Mask string whose bytes are ORed with cStr.
    - `lRotate` Logical - Optional rotation flag. When .T. and cStr is longer than cMask, cMask is reused
      from the beginning until all bytes in cStr have been processed. If cMask is empty or not shorter than
      cStr, rotation is ignored.

    Returns Returns the modified cStr. Without rotation, only the common byte range of both strings is
      processed. Returns NIL if either string cannot be obtained or locked.

    |note: This is useful for combining packed bits or binary masks. With lRotate set to .T., a shorter mask is
      cycled repeatedly over the target string. cStrBitOR() and cStrBitAND() are commonly used in massive
      filtering functions that combine large packed bit maps. }}*/
XPPRET XPPENTRY CSTRBITOR( XppParamList pl )
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL) _parl( pl, 3 );
   ContainerHandle conStr = _conTParam( pl, 1, &bStrByRef, XPP_CHARACTER );
   if( conStr != NULLCONTAINER )
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam( pl, 2, &bStr2ByRef, XPP_CHARACTER );
      if( conStr2 != NULLCONTAINER )
      {
         LPSTR pStr = (LPSTR) 0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR) 0;
         ULONG nLen2 = 0;
         if( ot4xb_conWLockC( conStr, &pStr, &nLen ) == 0 )
         {
            if( ot4xb_conRLockC( conStr2, &pStr2, &nLen2 ) == 0 )
            {
               ULONG n;
               if( ( nLen <= nLen2 ) || ( nLen2 == 0 ) ) bRotate = FALSE;
               if( bRotate )
               {
                  ULONG nn = 0;
                  for( n = 0; n < nLen; n++ )
                  {
                     pStr[ n ] |= pStr2[ nn ]; nn++; if( nn >= nLen2 ) nn = 0;
                  }
               }
               else
               {
                  if( nLen > nLen2 ) nLen = nLen2;
                  for( n = 0; n < nLen; n++ ) pStr[ n ] |= pStr2[ n ];
               }
               ot4xb_conUnlockC( conStr2 );
               bOk = TRUE;
            }
            ot4xb_conUnlockC( conStr );
         }
         if( !bStr2ByRef ) _conRelease( conStr2 );
      }
      if( bOk ) _conReturn( pl, conStr ); else _ret( pl );
      if( !bStrByRef ) _conRelease( conStr );
      return;
   }
   _ret( pl );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cStrBitXOR
            | syntax_: `cStrBitXOR( @cStr, cKey [, lRotate] )`
            | category: string/bit
            | _kw_: cStrBitXOR, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise XOR between two character strings.
    | params:
    - `cStr` Character by reference - Target string modified in place.
    - `cKey` Character - Key or mask string whose bytes are XORed with cStr.
    - `lRotate` Logical - Optional rotation flag. When .T. and cStr is longer than cKey, cKey is reused
      from the beginning until all bytes in cStr have been processed. If cKey is empty or not shorter than cStr,
      rotation is ignored.

    Returns Returns the modified cStr. Without rotation, only the common byte range of both strings is
      processed. Returns NIL if either string cannot be obtained or locked.

    |note: XOR is reversible by applying the same key again. With lRotate set to .T., a shorter key can be
      cycled over the target buffer. This helper is also useful for splitting data into two related buffers, for
      example a random byte string and the XORed result, so the pieces can be stored separately and recombined
      later. It is not a complete encryption system by itself. }}*/
XPPRET XPPENTRY CSTRBITXOR( XppParamList pl )
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL) _parl( pl, 3 );
   ContainerHandle conStr = _conTParam( pl, 1, &bStrByRef, XPP_CHARACTER );
   if( conStr != NULLCONTAINER )
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam( pl, 2, &bStr2ByRef, XPP_CHARACTER );
      if( conStr2 != NULLCONTAINER )
      {
         LPSTR pStr = (LPSTR) 0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR) 0;
         ULONG nLen2 = 0;
         if( ot4xb_conWLockC( conStr, &pStr, &nLen ) == 0 )
         {
            if( ot4xb_conRLockC( conStr2, &pStr2, &nLen2 ) == 0 )
            {
               ULONG n;
               if( ( nLen <= nLen2 ) || ( nLen2 == 0 ) ) bRotate = FALSE;
               if( bRotate )
               {
                  ULONG nn = 0;
                  for( n = 0; n < nLen; n++ )
                  {
                     pStr[ n ] ^= pStr2[ nn ]; nn++; if( nn >= nLen2 ) nn = 0;
                  }
               }
               else
               {
                  if( nLen > nLen2 ) nLen = nLen2;
                  for( n = 0; n < nLen; n++ ) pStr[ n ] ^= pStr2[ n ];
               }
               ot4xb_conUnlockC( conStr2 );
               bOk = TRUE;
            }
            ot4xb_conUnlockC( conStr );
         }
         if( !bStr2ByRef ) _conRelease( conStr2 );
      }
      if( bOk ) _conReturn( pl, conStr ); else _ret( pl );
      if( !bStrByRef ) _conRelease( conStr );
      return;
   }
   _ret( pl );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cStrBitAND
            | syntax_: `cStrBitAND( @cStr, cMask [, lRotate] )`
            | category: string/bit
            | _kw_: cStrBitAND, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise AND between two character strings.
    | params:
    - `cStr` Character by reference - Target string modified in place.
    - `cMask` Character - Mask string whose bytes are ANDed with cStr.
    - `lRotate` Logical - Optional rotation flag. When .T. and cStr is longer than cMask, cMask is reused
      from the beginning until all bytes in cStr have been processed. If cMask is empty or not shorter than
      cStr, rotation is ignored.

    Returns Returns the modified cStr. Without rotation, only the common byte range of both strings is
      processed. Returns NIL if either string cannot be obtained or locked.

    |note: This is useful for applying large packed bit maps and reducing searches by combining precomputed
      masks, for example when words or tags are represented by bit positions. With lRotate set to .T., a shorter
      mask is cycled repeatedly over the target string, although the common use case is to combine buffers with
      matching layout. cStrBitOR() and cStrBitAND() are commonly used in massive filtering functions that
      combine large packed bit maps. }}*/
XPPRET XPPENTRY CSTRBITAND( XppParamList pl )
{
   BOOL bOk = FALSE;
   BOOL bStrByRef = FALSE;
   BOOL bRotate = (BOOL) _parl( pl, 3 );
   ContainerHandle conStr = _conTParam( pl, 1, &bStrByRef, XPP_CHARACTER );
   if( conStr != NULLCONTAINER )
   {
      BOOL bStr2ByRef = FALSE;
      ContainerHandle conStr2 = _conTParam( pl, 2, &bStr2ByRef, XPP_CHARACTER );
      if( conStr2 != NULLCONTAINER )
      {
         LPSTR pStr = (LPSTR) 0;
         ULONG nLen = 0;
         LPSTR pStr2 = (LPSTR) 0;
         ULONG nLen2 = 0;
         if( ot4xb_conWLockC( conStr, &pStr, &nLen ) == 0 )
         {
            if( ot4xb_conRLockC( conStr2, &pStr2, &nLen2 ) == 0 )
            {
               ULONG n;
               if( ( nLen <= nLen2 ) || ( nLen2 == 0 ) ) bRotate = FALSE;
               if( bRotate )
               {
                  ULONG nn = 0;
                  for( n = 0; n < nLen; n++ )
                  {
                     pStr[ n ] &= pStr2[ nn ]; nn++; if( nn >= nLen2 ) nn = 0;
                  }
               }
               else
               {
                  if( nLen > nLen2 ) nLen = nLen2;
                  for( n = 0; n < nLen; n++ ) pStr[ n ] &= pStr2[ n ];
               }
               ot4xb_conUnlockC( conStr2 );
               bOk = TRUE;
            }
            ot4xb_conUnlockC( conStr );
         }
         if( !bStr2ByRef ) _conRelease( conStr2 );
      }
      if( bOk ) _conReturn( pl, conStr ); else _ret( pl );
      if( !bStrByRef ) _conRelease( conStr );
      return;
   }
   _ret( pl );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PStrBitOR
            | syntax_: `PStrBitOR( pTarget, nTargetLen, pMask, nMaskLen [, lRotate] )`
            | category: string/bit
            | _kw_: PStrBitOR, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise OR between two memory buffers addressed by pointers.
    | params:
    - `pTarget` Numeric pointer - Pointer to the writable target buffer.
    - `nTargetLen` Numeric - Length of the target buffer in bytes.
    - `pMask` Numeric pointer - Pointer to the mask buffer.
    - `nMaskLen` Numeric - Length of the mask buffer in bytes.
    - `lRotate` Logical - Optional rotation flag. When .T. and the target is longer than the mask, the mask
      is reused from the beginning until all target bytes have been processed.

    Returns Returns pTarget. If pTarget is zero, returns 0. If either length is zero or pMask is zero, no
      bytes are modified and pTarget is returned.

    |note: This is the pointer-based variant of cStrBitOR(). The caller must ensure that both pointers address
      valid buffers of the supplied lengths. }}*/
XPPRET XPPENTRY PSTRBITOR( XppParamList pl )
{
   LPSTR p1 = (LPSTR) _parLong( pl, 1 );
   ULONG n1 = (ULONG) _parLong( pl, 2 );
   LPSTR p2 = (LPSTR) _parLong( pl, 3 );
   ULONG n2 = (ULONG) _parLong( pl, 4 );
   BOOL bRotate = (BOOL) ( ( n1 <= n2 ) ? FALSE : _parl( pl, 5 ) );
   ULONG n, nn;

   if( p1 == 0 )
   {
      _retnl( pl, 0 ); return;
   }
   if( ( n1 == 0 ) || ( n2 == 0 ) || ( p2 == 0 ) )
   {
      _retnl( pl, (LONG) p1 ); return;
   }
   if( bRotate ) for( n = nn = 0; n < n1; n++ )
   {
      p1[ n ] |= p2[ nn ]; nn++; if( nn >= n2 ) nn = 0;
   }
   else if( n1 > n2 ) for( n = 0; n < n2; n++ ) p1[ n ] |= p2[ n ];
   else for( n = 0; n < n1; n++ ) p1[ n ] |= p2[ n ];
   _retnl( pl, (LONG) p1 );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PStrBitXOR
            | syntax_: `PStrBitXOR( pTarget, nTargetLen, pKey, nKeyLen [, lRotate] )`
            | category: string/bit
            | _kw_: PStrBitXOR, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise XOR between two memory buffers addressed by pointers.
    | params:
    - `pTarget` Numeric pointer - Pointer to the writable target buffer.
    - `nTargetLen` Numeric - Length of the target buffer in bytes.
    - `pKey` Numeric pointer - Pointer to the key or mask buffer.
    - `nKeyLen` Numeric - Length of the key or mask buffer in bytes.
    - `lRotate` Logical - Optional rotation flag. When .T. and the target is longer than the key, the key
      is reused from the beginning until all target bytes have been processed.

    Returns Returns pTarget. If pTarget is zero, returns 0. If either length is zero or pKey is zero, no bytes
      are modified and pTarget is returned.

    |note: This is the pointer-based variant of cStrBitXOR(). XOR is reversible by applying the same key again.
      The caller must ensure that both pointers address valid buffers of the supplied lengths. }}*/
XPPRET XPPENTRY PSTRBITXOR( XppParamList pl )
{
   LPSTR p1 = (LPSTR) _parLong( pl, 1 );
   ULONG n1 = (ULONG) _parLong( pl, 2 );
   LPSTR p2 = (LPSTR) _parLong( pl, 3 );
   ULONG n2 = (ULONG) _parLong( pl, 4 );
   BOOL bRotate = (BOOL) ( ( n1 <= n2 ) ? FALSE : _parl( pl, 5 ) );
   ULONG n, nn;

   if( p1 == 0 )
   {
      _retnl( pl, 0 ); return;
   }
   if( ( n1 == 0 ) || ( n2 == 0 ) || ( p2 == 0 ) )
   {
      _retnl( pl, (LONG) p1 ); return;
   }
   if( bRotate ) for( n = nn = 0; n < n1; n++ )
   {
      p1[ n ] ^= p2[ nn ]; nn++; if( nn >= n2 ) nn = 0;
   }
   else if( n1 > n2 ) for( n = 0; n < n2; n++ ) p1[ n ] ^= p2[ n ];
   else for( n = 0; n < n1; n++ ) p1[ n ] ^= p2[ n ];
   _retnl( pl, (LONG) p1 );
}
/*{{end-function}}*/
// ---------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstr_bit_xor
            | syntax_: `void _xstr_bit_xor( LPBYTE p1, ULONG cb1, LPBYTE p2, ULONG cb2, BOOL bRotate )`
            | category: string/bit
            | header: ot4xb_c_exported.h
            | mangled-name: _xstr_bit_xor
            | _kw_: _xstr_bit_xor, Function
   }}*/
/*{{|desc: XORs a byte buffer in place with the bytes of a second buffer. Without rotation only the common
      length of both buffers is processed. Nothing is done when a pointer is NULL or a length is 0.
    | params:
    - `p1` LPBYTE - Target buffer, modified in place.
    - `cb1` ULONG - Length of the target buffer in bytes.
    - `p2` LPBYTE - Buffer with the XOR key or mask bytes.
    - `cb2` ULONG - Length of the second buffer in bytes.
    - `bRotate` BOOL - When TRUE and the target is longer than the second buffer, the second buffer is
      reused from its beginning until all target bytes have been processed.

    Returns void }}*/
OT4XB_API void _xstr_bit_xor( LPBYTE p1, ULONG cb1, LPBYTE p2, ULONG cb2, BOOL bRotate )
{
   ULONG n, nn;
   if( p1 == 0 ) return;
   if( ( cb1 == 0 ) || ( cb2 == 0 ) || ( p2 == 0 ) ) return;
   if( bRotate ) for( n = nn = 0; n < cb1; n++ )
   {
      p1[ n ] ^= p2[ nn ]; nn++; if( nn >= cb2 ) nn = 0;
   }
   else if( cb1 > cb2 ) for( n = 0; n < cb2; n++ ) p1[ n ] ^= p2[ n ];
   else for( n = 0; n < cb1; n++ ) p1[ n ] ^= p2[ n ];
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PStrBitAND
            | syntax_: `PStrBitAND( pTarget, nTargetLen, pMask, nMaskLen [, lRotate] )`
            | category: string/bit
            | _kw_: PStrBitAND, Function
   }}*/
/*{{|desc: Applies a byte-by-byte bitwise AND between two memory buffers addressed by pointers.
    | params:
    - `pTarget` Numeric pointer - Pointer to the writable target buffer.
    - `nTargetLen` Numeric - Length of the target buffer in bytes.
    - `pMask` Numeric pointer - Pointer to the mask buffer.
    - `nMaskLen` Numeric - Length of the mask buffer in bytes.
    - `lRotate` Logical - Optional rotation flag. When .T. and the target is longer than the mask, the mask
      is reused from the beginning until all target bytes have been processed.

    Returns Returns pTarget. If pTarget is zero, returns 0. If either length is zero or pMask is zero, no
      bytes are modified and pTarget is returned.

    |note: This is the pointer-based variant of cStrBitAND(). The caller must ensure that both pointers address
      valid buffers of the supplied lengths. }}*/
XPPRET XPPENTRY PSTRBITAND( XppParamList pl )
{
   LPSTR p1 = (LPSTR) _parLong( pl, 1 );
   ULONG n1 = (ULONG) _parLong( pl, 2 );
   LPSTR p2 = (LPSTR) _parLong( pl, 3 );
   ULONG n2 = (ULONG) _parLong( pl, 4 );
   BOOL bRotate = (BOOL) ( ( n1 <= n2 ) ? FALSE : _parl( pl, 5 ) );
   ULONG n, nn;

   if( p1 == 0 )
   {
      _retnl( pl, 0 ); return;
   }
   if( ( n1 == 0 ) || ( n2 == 0 ) || ( p2 == 0 ) )
   {
      _retnl( pl, (LONG) p1 ); return;
   }
   if( bRotate ) for( n = nn = 0; n < n1; n++ )
   {
      p1[ n ] &= p2[ nn ]; nn++; if( nn >= n2 ) nn = 0;
   }
   else if( n1 > n2 ) for( n = 0; n < n2; n++ ) p1[ n ] &= p2[ n ];
   else for( n = 0; n < n1; n++ ) p1[ n ] &= p2[ n ];
   _retnl( pl, (LONG) p1 );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nStrBitCount
            | syntax_: `nStrBitCount( cStr )`
            | category: string/bit
            | _kw_: nStrBitCount, Function
   }}*/
/*{{|desc: Counts the bits set to 1 in a character string.
    | params:
    - `cStr` Character - String whose bytes are scanned.

    Returns Returns the number of set bits. Returns 0 when cStr is missing. Returns NIL if the string cannot
      be locked.

    |note: This is useful with strings used as compact bitsets. }}*/
XPPRET XPPENTRY NSTRBITCOUNT( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conParam( pl, 1, &bByRef );
   LPBYTE p = (LPBYTE) 0;
   ULONG  nLen = 0;
   ULONG  nBits = 0;
   ULONG  nByte = 0;
   BYTE   chMask;

   if( conStr == NULLCONTAINER )
   {
      _retnl( pl, 0 ); return;
   }
   if( ot4xb_conRLockC( conStr, (LPSTR*) &p, &nLen ) != 0 )
   {
      if( !bByRef ) _conRelease( conStr );
      _ret( pl ); return; // Error: error while locking the read pointer
   }
   if( nLen > 0 )
   {
      for( nByte = 0; nByte < nLen; nByte++ )
      {
         if( p[ nByte ] != 0 ) for( chMask = 1; chMask != 0; chMask <<= 1 ) if( ( p[ nByte ] & chMask ) != 0 ) nBits++;
      }
   }
   ot4xb_conUnlockC( conStr );
   if( !bByRef ) _conRelease( conStr );
   _retnl( pl, (LONG) nBits );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: aStrBits
            | syntax_: `aStrBits( cStr )`
            | category: string/bit
            | _kw_: aStrBits, Function
   }}*/
/*{{|desc: Returns the one-based positions of all bits set to 1 in a character string.
    | params:
    - `cStr` Character - String whose bytes are scanned.

    Returns Returns an array with the one-based bit positions that are set. Bit 1 is the low bit of the first
      byte. Returns 0 when cStr is missing. Returns NIL if the string cannot be locked.

    |note: This is useful for expanding a compact bitset into a list of enabled flags or item identifiers. }}*/
XPPRET XPPENTRY ASTRBITS( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conParam( pl, 1, &bByRef );
   LPBYTE p = (LPBYTE) 0;
   ULONG  nLen = 0;
   ULONG  nBits = 0;
   ULONG  nByte = 0;
   BYTE   chMask;
   ContainerHandle conaBits;

   if( conStr == NULLCONTAINER )
   {
      _retnl( pl, 0 ); return;
   }
   if( ot4xb_conRLockC( conStr, (LPSTR*) &p, &nLen ) != 0 )
   {
      if( !bByRef ) _conRelease( conStr );
      _ret( pl ); return; // Error: error while locking the read pointer
   }
   if( nLen != 0 )
   {
      for( nByte = 0; nByte < nLen; nByte++ )
      {
         if( p[ nByte ] != 0 ) for( chMask = 1; chMask != 0; chMask <<= 1 ) if( ( p[ nByte ] & chMask ) != 0 ) nBits++;
      }
   }
   conaBits = _conNewArray( 1, nBits );
   if( nBits != 0 )
   {
      ULONG n = 0;
      nBits = 0;
      for( nByte = 0; nByte < nLen; nByte++ )
      {
         if( p[ nByte ] == 0 ) n += 8;
         else
         {
            for( chMask = 1; chMask != 0; chMask <<= 1, n++ )
            {
               if( ( p[ nByte ] & chMask ) != 0 )
               {
                  ContainerHandle con = _conPutNL( NULLCONTAINER, (LONG) n + 1 );
                  nBits++;
                  _conArrayPut( conaBits, con, nBits, 0 );
                  _conRelease( con );
               }
            }
         }
      }
   }
   ot4xb_conUnlockC( conStr );
   if( !bByRef ) _conRelease( conStr );
   _conReturn( pl, conaBits );
   _conRelease( conaBits );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: dwCrc32
            | syntax_: `DWORD dwCrc32( DWORD dwCRC, LPBYTE pStr, ULONG nLen )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: dwCrc32
            | _kw_: dwCrc32, Function
   }}*/
/*{{|desc: Calculates the CRC32 of a byte buffer. The CRC can be calculated in several chunks by feeding the
      value returned for one chunk as dwCRC for the next one.
    | params:
    - `dwCRC` DWORD - Initial value: 0 for a single buffer or for the first chunk, or the value returned
      for the previous chunk to continue.
    - `pStr` LPBYTE - Buffer whose bytes enter the calculation.
    - `nLen` ULONG - Number of bytes to process.

    Returns DWORD - CRC32 value of the processed bytes. }}*/
OT4XB_API DWORD dwCrc32( DWORD dwCRC, LPBYTE pStr, ULONG nLen )
{
   ULONG n;
   dwCRC = dwCRC ^ 0xFFFFFFFF;
   for( n = 0; n < nLen; n++ )
   {
      dwCRC = C_R_C_32_TABLE[ ( (int) dwCRC ^ ( *pStr ) ) & 0xFF ] ^ ( dwCRC >> 8 ); pStr++;
   }

   return( dwCRC ^ 0xFFFFFFFF );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: dwCrc8
            | syntax_: `DWORD dwCrc8( DWORD dwCrc, char * data, int length )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: dwCrc8
            | _kw_: dwCrc8, Function
   }}*/
/*{{|desc: Calculates the CRC8 of a byte buffer using the reflected polynomial 0x8C. The CRC can be
      calculated in several chunks by feeding the value returned for one chunk as dwCrc for the next one.
    | params:
    - `dwCrc` DWORD - Initial value in the low byte: 0 for a single buffer or for the first chunk, or
      the value returned for the previous chunk to continue.
    - `data` char * - Buffer whose bytes enter the calculation.
    - `length` int - Number of bytes to process.

    Returns DWORD - CRC8 value in the range 0 to 255. }}*/
OT4XB_API DWORD dwCrc8( DWORD dwCrc, char* data, int length )
{
   char crc = (char) ( dwCrc & 0xFF );
   char extract;
   char sum;
   for( int i = 0; i < length; i++ )
   {
      extract = *data;
      for( char tempI = 8; tempI; tempI-- )
      {
         sum = ( crc ^ extract ) & 0x01;
         crc >>= 1;
         if( sum )
            crc ^= 0x8C;
         extract >>= 1;
      }
      data++;
   }
   return (DWORD) ( crc & 0xFF );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: dwCrc32WithTable
            | syntax_: `DWORD dwCrc32WithTable( DWORD dwCRC, LPBYTE pStr, ULONG nLen, LPBYTE pTable )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: dwCrc32WithTable
            | _kw_: dwCrc32WithTable, Function
   }}*/
/*{{|desc: Calculates the CRC32 of a byte buffer, translating every byte through a 256-byte map table before
      it enters the calculation. Useful for normalized checksums, such as a case-insensitive CRC32 built
      with a lower-case table.
    | params:
    - `dwCRC` DWORD - Initial value: 0 for a single buffer or for the first chunk, or the value returned
      for the previous chunk to continue.
    - `pStr` LPBYTE - Buffer whose bytes are translated and processed.
    - `nLen` ULONG - Number of bytes to process.
    - `pTable` LPBYTE - 256-byte translation table indexed by the source byte value.

    Returns DWORD - CRC32 value of the translated bytes. }}*/
OT4XB_API DWORD dwCrc32WithTable( DWORD dwCRC, LPBYTE pStr, ULONG nLen, LPBYTE pTable )
{
   ULONG n;
   dwCRC = dwCRC ^ 0xFFFFFFFF;

   for( n = 0; n < nLen; n++, pStr++ )
   {
      BYTE ch = pTable[ *pStr ];
      dwCRC = C_R_C_32_TABLE[ ( (int) dwCRC ^ ch ) & 0xFF ] ^ ( dwCRC >> 8 );
   }
   return( dwCRC ^ 0xFFFFFFFF );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: NoComment
            | syntax_: `NoComment( cText )`
            | category: string
            | _kw_: NoComment, Function
   }}*/
/*{{|desc: Removes C/C++ style comments from a character string.
    | params:
    - `cText` Character - Text to process.

    Returns Returns cText with // line comments removed up to the next CR or LF, and '/'+'*' ... '*'+ '/'
      block comments removed completely. The line break that terminates a // comment is preserved. Returns an
      empty string when cText is not supplied as a character value.

    |note: This is a simple lexical remover. Quotes are not interpreted, so comment markers inside quoted text
      are still treated as comments. This is a legacy helper intended for ordinary cases; nested comments and
      some chained or ambiguous comment patterns are not parsed as a full language lexer would do. }}*/
XPPRET XPPENTRY NOCOMMENT( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conStr = _conTParam( pl, 1, &bByRef, XPP_CHARACTER );
   ContainerHandle conr = _conNew( NULLCONTAINER );
   if( conStr != NULLCONTAINER )
   {
      LPSTR pSrc = NULL;
      int nLen = 0;
      if( ot4xb_conRLockC( conStr, &pSrc, (ULONG*) &nLen ) == 0 )
      {
         int ns = 0;
         int nd = 0;
         LPSTR  pDst = (LPSTR) _xgrab( nLen + 1 );
         while( ns < nLen )
         {
            if( pSrc[ ns ] == '/' )
            {
               if( ( (WORD) ( (WORD*) (void*) ( pSrc + ns ) )[ 0 ] ) == 0x2F2F )  // '/'+'/'
               {
                  for( ns += 2; ( ns < nLen ) && ( pSrc[ ns ] != 13 ) && ( pSrc[ ns ] != 10 ); ns++ );
               }
               else if( ( (WORD) ( (WORD*) (void*) ( pSrc + ns ) )[ 0 ] ) == 0x2A2F )  // '/'+'*'
               {
                  for( ns += 2; ( ns < nLen ) && ( ( (WORD) ( (WORD*) (void*) ( pSrc + ns ) )[ 0 ] ) != 0x2F2A ); ns++ );
                  ns += 2;
               }
               else pDst[ nd++ ] = pSrc[ ns++ ];
            }
            else pDst[ nd++ ] = pSrc[ ns++ ];
         }
         _conPutCL( conr, pDst, nd );
         _xfree( (void*) pDst );
         ot4xb_conUnlockC( conStr ); pSrc = NULL;
      }
      if( !bByRef )  _conRelease( conStr );
   }
   _conReturn( pl, conr ); _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: chHex2Nibble
            | syntax_: `BYTE chHex2Nibble( BYTE chHex )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: chHex2Nibble
            | _kw_: chHex2Nibble, Function
   }}*/
/*{{|desc: Converts one hexadecimal character to its numeric nibble value.
    | params:
    - `chHex` BYTE - Character '0' to '9', 'A' to 'F' or 'a' to 'f'.

    Returns BYTE - Value 0 to 15, or 0 when the character is not a hexadecimal digit. }}*/
OT4XB_API BYTE chHex2Nibble( BYTE chHex )
{
   switch( chHex )
   {
      case '0': return( 0 );
      case '1': return( 1 );
      case '2': return( 2 );
      case '3': return( 3 );
      case '4': return( 4 );
      case '5': return( 5 );
      case '6': return( 6 );
      case '7': return( 7 );
      case '8': return( 8 );
      case '9': return( 9 );
      case 'A':; case 'a': return( 10 );
      case 'B':; case 'b': return( 11 );
      case 'C':; case 'c': return( 12 );
      case 'D':; case 'd': return( 13 );
      case 'E':; case 'e': return( 14 );
      case 'F':; case 'f': return( 15 );
   }
   return( 0 );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cBin2Hex
            | syntax_: `cBin2Hex( cBinary )`
            | category: string/hex
            | _kw_: cBin2Hex, Function
   }}*/
/*{{|desc: Converts a binary string to an uppercase hexadecimal string.
    | params:
    - `cBinary` Character - Binary string to encode.

    Returns Returns two hexadecimal characters for each byte in cBinary. Returns an empty string when cBinary
      is not supplied. }}*/
XPPRET XPPENTRY CBIN2HEX( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, 1, &bByRef, XPP_CHARACTER );
   ContainerHandle conr = _conNew( NULLCONTAINER );
   if( con != NULLCONTAINER )
   {
      LPSTR pBin = NULL;
      ULONG nCb = 0;
      if( ot4xb_conRLockC( con, &pBin, &nCb ) == 0 )
      {
         ULONG nHexSize = ( nCb * 2 );
         LPSTR pHex = (LPSTR) _xgrab( nHexSize + 1 );
         LPSTR pp = pHex;
         ULONG n;
         for( n = 0; n < nCb; n++ )
         {
            *pp++ = __HEXNIBBLE__[ MSNIBBLE( pBin[ n ] ) ];
            *pp++ = __HEXNIBBLE__[ LSNIBBLE( pBin[ n ] ) ];
         }
         ot4xb_conUnlockC( con );
         _conPutCL( conr, pHex, nHexSize );
         _xfree( (void*) pHex );
      }
      if( !bByRef ) _conRelease( con );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_CHEX2BIN_defmode_
            | syntax_: `LONG ot4xb_CHEX2BIN_defmode_( LONG n )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_CHEX2BIN_defmode_
            | _kw_: ot4xb_CHEX2BIN_defmode_, Function
   }}*/
/*{{|desc: Reads and optionally changes the process-wide default decoding mode used by cHex2Bin() when its
      nMode parameter is omitted. The initial default mode is 1.
    | params:
    - `n` LONG - New default mode: 0, 1 or 2, as described in cHex2Bin(). Any other value only reads the
      current mode.

    Returns LONG - Default mode in effect before the call. }}*/
OT4XB_API LONG ot4xb_CHEX2BIN_defmode_( LONG n )
{
   LONG nn = _cHex2Bin_Ex_Mode_;
   if( ( n >= 0 ) && ( n < 3 ) ) _cHex2Bin_Ex_Mode_ = n;
   return nn;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// nExtended == 0 -> !nibbleChar == Chr(0)  && odd nibbles << 4
// nExtended == 1 -> !nibbleChar skiped
// nExtended == 2 -> !nibbleChar skiped &&  byte separator
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cHex2Bin
            | syntax_: `cHex2Bin( cHex [, nMode] )`
            | category: string/hex
            | _kw_: cHex2Bin, Function
   }}*/
/*{{|desc: Converts a hexadecimal string to binary bytes.
    | params:
    - `cHex` Character - Hexadecimal text to decode.
    - `nMode` Numeric - Optional decoding mode. 0 - non-hex characters are decoded as zero nibbles; odd
      nibbles are shifted into the high half-byte. 1 - non-hex characters are skipped. 2 - non-hex characters
      are skipped and can act as byte separators.

    Returns Returns the decoded binary string. If nMode is omitted, the current default cHex2Bin mode is used. }}*/
XPPRET XPPENTRY CHEX2BIN( XppParamList pl )
{
   ULONG nEx = (ULONG) ( ( _partype( pl, 2 ) & XPP_NUMERIC ) ? _parLong( pl, 2, 0 ) : _cHex2Bin_Ex_Mode_ );
   BOOL  bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, 1, &bByRef, XPP_CHARACTER );
   ContainerHandle conr = _conNew( NULLCONTAINER );
   if( con != NULLCONTAINER )
   {
      LPBYTE pHex = NULL;
      ULONG nCb = 0;
      if( ot4xb_conRLockC( con, (LPSTR*) &pHex, &nCb ) == 0 )
      {
         LPBYTE pp = pHex;
         LPBYTE ppMax = _mk_ptr_( LPBYTE, pHex, nCb );
         LPBYTE pBin = (LPBYTE) _xgrab( ( ( nEx == 2 ) ? nCb : ( nCb >> 1 ) ) + 1 );
         LPBYTE p = pBin;
         ULONG cb = 0;
         BOOL  bh;

         for( bh = 0; pp < ppMax; pp++ )
         {
            if( __NIBBLECHAR__[ *pp ] || ( nEx == 0 ) )
            {
               if( bh )
               {
                  *p = ( ( *p << 4 ) & 0xF0 ) | ( __NIBBLECHAR__[ *pp ] & 0x0F );
                  p++; bh = 0;
               }
               else
               {
                  *p = ( __NIBBLECHAR__[ *pp ] & 0x0F );
                  cb++; bh = 1;
               }
            }
            else if( ( nEx == 2 ) && bh )
            {
               bh = 0; p++;
            }
         }
         ot4xb_conUnlockC( con );
         _conPutCL( conr, (LPSTR) pBin, cb );
         _xfree( (void*) pBin );
      }
      if( !bByRef ) _conRelease( con );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Tokenize
            | syntax_: `Tokenize( cText [, cSeparator] )`
            | category: string
            | _kw_: Tokenize, Function
   }}*/
/*{{|desc: Splits a character string using a literal separator string.
    | params:
    - `cText` Character - Text to split.
    - `cSeparator` Character - Literal separator to search for. If omitted or empty, ';' is used.

    Returns Returns an array with the tokens found before each separator and the final non-empty token. Empty
      tokens between consecutive separators are preserved. A final empty token is not returned when cText ends
      exactly with the separator; append one extra separator if that trailing empty item must be represented.

    |note: The separator is matched as a single literal string, not as a character set. Multi-byte separators
      are accepted, but only one separator string can be supplied. Quotes are not interpreted; separators inside
      quoted text are still treated as separators. }}*/
XPPRET XPPENTRY TOKENIZE( XppParamList pl )
{
   CHAR  szSep[ 128 ];
   ULONG cbStr = _parclen( pl, 1 );
   ULONG cbSep = _parclen( pl, 2 );
   LPSTR pStr = _pszParam( pl, 1 );
   LPSTR pSep = (LPSTR) szSep;
   LPSTR p;
   int   nLen;
   int iAt;
   ULONG n, nItems;
   TList* pList = new TList;
   ContainerHandle conr = NULLCONTAINER;


   if( cbSep == 0 )
   {
      pSep[ 0 ] = ';'; pSep[ 1 ] = 0; cbSep = 1;
   }
   else  _parc( pSep, 128, pl, 2, 0 );

   p = pStr; nLen = (int) cbStr;
   iAt = _xstrat( pSep, cbSep, p, cbStr );
   while( iAt != -1 )
   {
      pList->Add( (void*) iAt );
      nLen -= ( iAt + (int) cbSep );
      p += ( iAt + (int) cbSep );
      iAt = _xstrat( pSep, cbSep, p, nLen );

   }
   if( nLen > 0 ) pList->Add( (void*) nLen );
   p = pStr;
   nItems = pList->Count();
   conr = _conNewArray( 1, nItems );
   for( n = 0; n < nItems; n++ )
   {
      ULONG ul = (ULONG) pList->Get( n );
      _conArrayPutCL( conr, p, ul, ( n + 1 ), 0 );
      p += ( ul + cbSep );
   }
   delete pList; _xfree( (void*) pStr );
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TrimQuotes
            | syntax_: `TrimQuotes( cText )`
            | category: string
            | _kw_: TrimQuotes, Function
   }}*/
/*{{|desc: Removes spaces and double quote characters from both ends of a string.
    | params:
    - `cText` Character - Text to trim.

    Returns Returns cText without leading or trailing spaces and double quotes. Returns an empty string when
      cText is not supplied. }}*/
XPPRET XPPENTRY TRIMQUOTES( XppParamList pl )
{
   LPSTR pStr = _pszParam( pl, 1 );
   LPSTR pOut = NULL;
   if( pStr )
   {
      LPSTR pp;
      for( pOut = pStr; pOut[ 0 ] && ( ( pOut[ 0 ] == 0x20 ) || ( pOut[ 0 ] == 0x22 ) ); pOut++ );
      for( pp = pOut; pp[ 0 ]; pp++ );
      pp--;
      while( ( pp > pOut ) && ( ( pp[ 0 ] == 0x20 ) || ( pp[ 0 ] == 0x22 ) ) )
      {
         pp[ 0 ] = 0; pp--;
      }
      _retc( pl, pOut );
      _xfree( pStr );
   }
   else _retc( pl, "" );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TrimZ
            | syntax_: `TrimZ( cText )`
            | category: string
            | _kw_: TrimZ, Function
   }}*/
/*{{|desc: Returns the zero-terminated portion of a character string.
    | params:
    - `cText` Character - Text that may contain a zero byte.

    Returns Returns the bytes from the start of cText up to the first zero byte, as a C-style zero-terminated
      string. Returns an empty string when cText is not supplied. }}*/
XPPRET XPPENTRY TRIMZ( XppParamList pl )
{
   ContainerHandle conr = _conNew( NULLCONTAINER );
   ContainerHandle conc = _conTParam( pl, 1, 0, XPP_CHARACTER );
   if( conc )
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( conc, &pStr, &cb ) == 0 )
      {
         _conPutC( conr, pStr );
         ot4xb_conUnlockC( conc );
      }
      _conRelease( conc );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: C5AllTrim
            | syntax_: `C5AllTrim( cText )`
            | category: string
            | _kw_: C5AllTrim, Function
   }}*/
/*{{|desc: Removes leading and trailing zero bytes and spaces from a character string.
    | params:
    - `cText` Character - Text to trim.

    Returns Returns cText with leading and trailing bytes 0x00 and 0x20 removed. Returns an empty string when
      cText is not supplied or all bytes are trimmed.

    |note: Compatibility helper for Clipper 5 behavior. Clipper 5 trim functions removed both spaces and null
      characters, while Alaska Xbase++ trim functions remove spaces only. }}*/
XPPRET XPPENTRY C5ALLTRIM( XppParamList pl )
{
   ContainerHandle conr = _conNew( NULLCONTAINER );
   ContainerHandle conc = _conTParam( pl, 1, 0, XPP_CHARACTER );
   if( conc )
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( conc, &pStr, &cb ) == 0 )
      {
         for( ; cb && ( pStr[ 0 ] == 0 || pStr[ 0 ] == 32 ); cb--, pStr++ );
         for( ; cb && ( pStr[ ( cb - 1 ) ] == 0 || pStr[ ( cb - 1 ) ] == 32 ); cb-- );
         if( cb ) _conPutCL( conr, pStr, cb );
         else _conPutC( conr, "" );
         ot4xb_conUnlockC( conc );
      }
      _conRelease( conc );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: C5RTrim
            | syntax_: `C5RTrim( cText )`
            | category: string
            | _kw_: C5RTrim, Function
   }}*/
/*{{|desc: Removes trailing zero bytes and spaces from a character string.
    | params:
    - `cText` Character - Text to trim.

    Returns Returns cText with trailing bytes 0x00 and 0x20 removed. Returns an empty string when cText is not
      supplied or all bytes are trimmed.

    |note: Compatibility helper for Clipper 5 behavior. Clipper 5 trim functions removed both spaces and null
      characters, while Alaska Xbase++ trim functions remove spaces only. }}*/
XPPRET XPPENTRY C5RTRIM( XppParamList pl )
{
   ContainerHandle conr = _conNew( NULLCONTAINER );
   ContainerHandle conc = _conTParam( pl, 1, 0, XPP_CHARACTER );
   if( conc )
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( conc, &pStr, &cb ) == 0 )
      {
         for( ; cb && ( pStr[ ( cb - 1 ) ] == 0 || pStr[ ( cb - 1 ) ] == 32 ); cb-- );
         if( cb ) _conPutCL( conr, pStr, cb );
         else _conPutC( conr, "" );
         ot4xb_conUnlockC( conc );
      }
      _conRelease( conc );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: C5LTrim
            | syntax_: `C5LTrim( cText )`
            | category: string
            | _kw_: C5LTrim, Function
   }}*/
/*{{|desc: Removes leading zero bytes and spaces from a character string.
    | params:
    - `cText` Character - Text to trim.

    Returns Returns cText with leading bytes 0x00 and 0x20 removed. Returns an empty string when cText is not
      supplied or all bytes are trimmed.

    |note: Compatibility helper for Clipper 5 behavior. Clipper 5 trim functions removed both spaces and null
      characters, while Alaska Xbase++ trim functions remove spaces only. }}*/
XPPRET XPPENTRY C5LTRIM( XppParamList pl )
{
   ContainerHandle conr = _conNew( NULLCONTAINER );
   ContainerHandle conc = _conTParam( pl, 1, 0, XPP_CHARACTER );
   if( conc )
   {
      LPSTR pStr = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( conc, &pStr, &cb ) == 0 )
      {
         for( ; cb && ( pStr[ 0 ] == 0 || pStr[ 0 ] == 32 ); cb--, pStr++ );
         if( cb ) _conPutCL( conr, pStr, cb );
         else _conPutC( conr, "" );
         ot4xb_conUnlockC( conc );
      }
      _conRelease( conc );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cQW2Hex
            | syntax_: `cQW2Hex( xValue )`
            | category: string/hex
            | _kw_: cQW2Hex, Function
   }}*/
/*{{|desc: Converts a 64-bit value to a 16-character uppercase hexadecimal string.
    | params:
    - `xValue` Numeric/Array/Character - Value to encode. Numeric values are used directly; arrays are
      interpreted as { nLowDWord, nHighDWord }; character values provide the raw 8 bytes.

    Returns Returns a 16-character hexadecimal string. }}*/
XPPRET XPPENTRY CQW2HEX( XppParamList  pl )
{
   ULONG ulType = _partype( pl, 1 );
   QWCHARUNION qwu;
   BYTE        pHex[ 17 ];
   _bset( qwu.ch, 0, 8 );
   if( ulType & XPP_NUMERIC )
   {
      if( ulType & _xpp_DOUBLE )  qwu.qw = (LONGLONG) _parnd( pl, 1, 0 );
      else qwu.qw = ( 0x00000000FFFFFFFF & ( (LONGLONG) _parLong( pl, 1, 0 ) ) );
   }
   else if( ulType & XPP_ARRAY )
   {
      qwu.qw = ( ( ( (LONGLONG) _parLong( pl, 1, 2, 0 ) ) << 32 ) | ( 0x00000000FFFFFFFF & ( (LONGLONG) _parLong( pl, 1, 1, 0 ) ) ) );
   }
   else
   {
      _bset( pHex, 0, 17 );
      _parc( (LPSTR) pHex, 17, pl, 1, 0 );
      _bcopy( qwu.ch, pHex, 8 );
      _bset( pHex, 0, 17 );
   }
   pHex[ 0 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 7 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 1 ] = __HEXNIBBLE__[ ( qwu.ch[ 7 ] & (BYTE) 0x0F ) ];
   pHex[ 2 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 6 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 3 ] = __HEXNIBBLE__[ ( qwu.ch[ 6 ] & (BYTE) 0x0F ) ];
   pHex[ 4 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 5 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 5 ] = __HEXNIBBLE__[ ( qwu.ch[ 5 ] & (BYTE) 0x0F ) ];
   pHex[ 6 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 4 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 7 ] = __HEXNIBBLE__[ ( qwu.ch[ 4 ] & (BYTE) 0x0F ) ];
   pHex[ 8 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 3 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 9 ] = __HEXNIBBLE__[ ( qwu.ch[ 3 ] & (BYTE) 0x0F ) ];
   pHex[ 10 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 2 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 11 ] = __HEXNIBBLE__[ ( qwu.ch[ 2 ] & (BYTE) 0x0F ) ];
   pHex[ 12 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 1 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 13 ] = __HEXNIBBLE__[ ( qwu.ch[ 1 ] & (BYTE) 0x0F ) ];
   pHex[ 14 ] = __HEXNIBBLE__[ ( ( qwu.ch[ 0 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 15 ] = __HEXNIBBLE__[ ( qwu.ch[ 0 ] & (BYTE) 0x0F ) ];
   pHex[ 16 ] = 0;
   _retc( pl, (LPSTR) pHex );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nHex2QW
            | syntax_: `nHex2QW( cHex )`
            | category: string/hex
            | _kw_: nHex2QW, Function
   }}*/
/*{{|desc: Converts a 16-character hexadecimal QWORD representation to its raw 8-byte binary form.
    | params:
    - `cHex` Character - Hexadecimal text containing up to 16 hex digits.

    Returns Returns an 8-byte binary string containing the decoded QWORD bytes. }}*/
XPPRET XPPENTRY NHEX2QW( XppParamList  pl )
{
   char ss[ 8 ];
   BYTE        pHex[ 17 ];

   _parc( (LPSTR) pHex, 17, pl, 1, 0 );

   ss[ 0 ] = (BYTE) ( ( chHex2Nibble( pHex[ 14 ] ) << 4 ) & 0xF0 );
   ss[ 0 ] |= ( chHex2Nibble( pHex[ 15 ] ) & 0x0F );
   ss[ 1 ] = (BYTE) ( ( chHex2Nibble( pHex[ 12 ] ) << 4 ) & 0xF0 );
   ss[ 1 ] |= ( chHex2Nibble( pHex[ 13 ] ) & 0x0F );
   ss[ 2 ] = (BYTE) ( ( chHex2Nibble( pHex[ 10 ] ) << 4 ) & 0xF0 );
   ss[ 2 ] |= ( chHex2Nibble( pHex[ 11 ] ) & 0x0F );
   ss[ 3 ] = (BYTE) ( ( chHex2Nibble( pHex[ 8 ] ) << 4 ) & 0xF0 );
   ss[ 3 ] |= ( chHex2Nibble( pHex[ 9 ] ) & 0x0F );
   ss[ 4 ] = (BYTE) ( ( chHex2Nibble( pHex[ 6 ] ) << 4 ) & 0xF0 );
   ss[ 4 ] |= ( chHex2Nibble( pHex[ 7 ] ) & 0x0F );
   ss[ 5 ] = (BYTE) ( ( chHex2Nibble( pHex[ 4 ] ) << 4 ) & 0xF0 );
   ss[ 5 ] |= ( chHex2Nibble( pHex[ 5 ] ) & 0x0F );
   ss[ 6 ] = (BYTE) ( ( chHex2Nibble( pHex[ 2 ] ) << 4 ) & 0xF0 );
   ss[ 6 ] |= ( chHex2Nibble( pHex[ 3 ] ) & 0x0F );
   ss[ 7 ] = (BYTE) ( ( chHex2Nibble( pHex[ 0 ] ) << 4 ) & 0xF0 );
   ss[ 7 ] |= ( chHex2Nibble( pHex[ 1 ] ) & 0x0F );
   _retclen( pl, ss, 8 );

   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cDouble2Hex
            | syntax_: `cDouble2Hex( nValue )`
            | category: string/hex
            | _kw_: cDouble2Hex, Function
   }}*/
/*{{|desc: Converts the binary representation of a double to a 16-character uppercase hexadecimal string.
    | params:
    - `nValue` Numeric - Double value to encode.

    Returns Returns the 8 bytes of the double value encoded as 16 hexadecimal characters. }}*/
XPPRET XPPENTRY CDOUBLE2HEX( XppParamList  pl )
{
   double nd = _parnd( pl, 1, 0 );
   LPBYTE p = _mk_ptr_( LPBYTE, &nd, 0 );
   BYTE   ph[ 17 ];
   ph[ 0 ] = __HEXNIBBLE__[ ( ( p[ 7 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 1 ] = __HEXNIBBLE__[ ( p[ 7 ] & (BYTE) 0x0F ) ];
   ph[ 2 ] = __HEXNIBBLE__[ ( ( p[ 6 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 3 ] = __HEXNIBBLE__[ ( p[ 6 ] & (BYTE) 0x0F ) ];
   ph[ 4 ] = __HEXNIBBLE__[ ( ( p[ 5 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 5 ] = __HEXNIBBLE__[ ( p[ 5 ] & (BYTE) 0x0F ) ];
   ph[ 6 ] = __HEXNIBBLE__[ ( ( p[ 4 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 7 ] = __HEXNIBBLE__[ ( p[ 4 ] & (BYTE) 0x0F ) ];
   ph[ 8 ] = __HEXNIBBLE__[ ( ( p[ 3 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 9 ] = __HEXNIBBLE__[ ( p[ 3 ] & (BYTE) 0x0F ) ];
   ph[ 10 ] = __HEXNIBBLE__[ ( ( p[ 2 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 11 ] = __HEXNIBBLE__[ ( p[ 2 ] & (BYTE) 0x0F ) ];
   ph[ 12 ] = __HEXNIBBLE__[ ( ( p[ 1 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 13 ] = __HEXNIBBLE__[ ( p[ 1 ] & (BYTE) 0x0F ) ];
   ph[ 14 ] = __HEXNIBBLE__[ ( ( p[ 0 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   ph[ 15 ] = __HEXNIBBLE__[ ( p[ 0 ] & (BYTE) 0x0F ) ];
   ph[ 16 ] = 0;
   _retc( pl, (LPSTR) ph );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nHex2Double
            | syntax_: `nHex2Double( cHex )`
            | category: string/hex
            | _kw_: nHex2Double, Function
   }}*/
/*{{|desc: Converts a 16-character hexadecimal representation of a double back to a numeric double value.
    | params:
    - `cHex` Character - Hexadecimal text containing the 8 bytes of a double value.

    Returns Returns the decoded double value. }}*/
XPPRET XPPENTRY NHEX2DOUBLE( XppParamList  pl )
{
   double nd = 0.00F;
   LPBYTE p = _mk_ptr_( LPBYTE, &nd, 0 );
   BYTE   ph[ 17 ];
   _bset( ph, 0, 17 );
   _parc( (LPSTR) ph, 17, pl, 1, 0 );

   p[ 0 ] = ( ( chHex2Nibble( ph[ 14 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 15 ] ) & 0x0F );
   p[ 1 ] = ( ( chHex2Nibble( ph[ 12 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 13 ] ) & 0x0F );
   p[ 2 ] = ( ( chHex2Nibble( ph[ 10 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 11 ] ) & 0x0F );
   p[ 3 ] = ( ( chHex2Nibble( ph[ 8 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 9 ] ) & 0x0F );
   p[ 4 ] = ( ( chHex2Nibble( ph[ 6 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 7 ] ) & 0x0F );
   p[ 5 ] = ( ( chHex2Nibble( ph[ 4 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 5 ] ) & 0x0F );
   p[ 6 ] = ( ( chHex2Nibble( ph[ 2 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 3 ] ) & 0x0F );
   p[ 7 ] = ( ( chHex2Nibble( ph[ 0 ] ) << 4 ) & 0xF0 ) | ( chHex2Nibble( ph[ 1 ] ) & 0x0F );
   _retnd( pl, nd );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cDw2Hex
            | syntax_: `cDw2Hex( nValue )`
            | category: string/hex
            | _kw_: cDw2Hex, Function
   }}*/
/*{{|desc: Converts a 32-bit value to an 8-character uppercase hexadecimal string.
    | params:
    - `nValue` Numeric - 32-bit value to encode.

    Returns Returns an 8-character hexadecimal string. }}*/
XPPRET XPPENTRY CDW2HEX( XppParamList  pl )
{
   DWCHARUNION dwu;
   BYTE        pHex[ 9 ];

   dwu.i = _parLong( pl, 1 );
   pHex[ 0 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 3 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 1 ] = __HEXNIBBLE__[ ( dwu.ch[ 3 ] & (BYTE) 0x0F ) ];
   pHex[ 2 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 2 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 3 ] = __HEXNIBBLE__[ ( dwu.ch[ 2 ] & (BYTE) 0x0F ) ];
   pHex[ 4 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 1 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 5 ] = __HEXNIBBLE__[ ( dwu.ch[ 1 ] & (BYTE) 0x0F ) ];
   pHex[ 6 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 0 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 7 ] = __HEXNIBBLE__[ ( dwu.ch[ 0 ] & (BYTE) 0x0F ) ];
   pHex[ 8 ] = 0;
   _retc( pl, (LPSTR) pHex );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nHex2Dw
            | syntax_: `nHex2Dw( cHex )`
            | category: string/hex
            | _kw_: nHex2Dw, Function
   }}*/
/*{{|desc: Converts hexadecimal text to a 32-bit numeric value.
    | params:
    - `cHex` Character - Hexadecimal text to decode. Spaces are ignored by the current implementation.

    Returns Returns the decoded 32-bit value. }}*/
XPPRET XPPENTRY NHEX2DW( XppParamList  pl )
{
   #ifndef _OT4XB_KEEP_OLD_NHEX2DW_BEHAVIOR
   TXppParamList xpp( pl );
   DWORD  dwNum = 0;
   if( xpp[ 1 ]->CheckType( XPP_CHARACTER ) )
   {
      ULONG  cb = 0;
      LPBYTE p = (LPBYTE) xpp[ 1 ]->LockStr( &cb );
      if( p && cb )
      {
         for( ; *p && cb; p++, cb-- )
         {
            DWORD nib = (DWORD) chHex2Nibble( *p );
            if( nib || ( *p == (BYTE) '0' ) )
            {
               dwNum = ( dwNum << 4 ) | nib;
            }
            else
            {
               if( *p != 0x20 )
               {
                  dwNum = 0;
               }
            }
         }
      }
   }
   xpp[ 0 ]->PutLong( dwNum );

   #else
   DWCHARUNION dwu;
   BYTE        pHex[ 9 ];

   _parc( (LPSTR) pHex, 9, pl, 1 );
   dwu.ch[ 0 ] = (BYTE) ( ( chHex2Nibble( pHex[ 6 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 0 ] |= ( chHex2Nibble( pHex[ 7 ] ) & 0x0F );

   dwu.ch[ 1 ] = (BYTE) ( ( chHex2Nibble( pHex[ 4 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 1 ] |= ( chHex2Nibble( pHex[ 5 ] ) & 0x0F );

   dwu.ch[ 2 ] = (BYTE) ( ( chHex2Nibble( pHex[ 2 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 2 ] |= ( chHex2Nibble( pHex[ 3 ] ) & 0x0F );

   dwu.ch[ 3 ] = (BYTE) ( ( chHex2Nibble( pHex[ 0 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 3 ] |= ( chHex2Nibble( pHex[ 1 ] ) & 0x0F );
   _retnl( pl, dwu.i );
   #endif
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cW2Hex
            | syntax_: `cW2Hex( nValue )`
            | category: string/hex
            | _kw_: cW2Hex, Function
   }}*/
/*{{|desc: Converts the low 16 bits of a numeric value to a 4-character uppercase hexadecimal string.
    | params:
    - `nValue` Numeric - Value whose low word is encoded.

    Returns Returns a 4-character hexadecimal string. }}*/
XPPRET XPPENTRY CW2HEX( XppParamList  pl )
{
   DWCHARUNION dwu;
   BYTE        pHex[ 9 ];

   dwu.i = _parLong( pl, 1 );
   pHex[ 0 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 3 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 1 ] = __HEXNIBBLE__[ ( dwu.ch[ 3 ] & (BYTE) 0x0F ) ];
   pHex[ 2 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 2 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 3 ] = __HEXNIBBLE__[ ( dwu.ch[ 2 ] & (BYTE) 0x0F ) ];
   pHex[ 4 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 1 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 5 ] = __HEXNIBBLE__[ ( dwu.ch[ 1 ] & (BYTE) 0x0F ) ];
   pHex[ 6 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 0 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 7 ] = __HEXNIBBLE__[ ( dwu.ch[ 0 ] & (BYTE) 0x0F ) ];
   pHex[ 8 ] = 0;
   _retc( pl, (LPSTR) pHex + 4 );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nHex2W
            | syntax_: `nHex2W( cHex )`
            | category: string/hex
            | _kw_: nHex2W, Function
   }}*/
/*{{|desc: Converts a 4-character hexadecimal word representation to a numeric value.
    | params:
    - `cHex` Character - Hexadecimal text containing up to 4 hex digits.

    Returns Returns the decoded word value. }}*/
XPPRET XPPENTRY NHEX2W( XppParamList  pl )
{
   DWCHARUNION dwu;
   BYTE        pHex[ 9 ];

   _parc( (LPSTR) pHex, 9, pl, 1 );
   dwu.ch[ 0 ] = (BYTE) ( ( chHex2Nibble( pHex[ 2 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 0 ] |= ( chHex2Nibble( pHex[ 3 ] ) & 0x0F );

   dwu.ch[ 1 ] = (BYTE) ( ( chHex2Nibble( pHex[ 0 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 1 ] |= ( chHex2Nibble( pHex[ 1 ] ) & 0x0F );
   dwu.ch[ 2 ] = 0;
   dwu.ch[ 3 ] = 0;
   _retnl( pl, dwu.i );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cByte2Hex
            | syntax_: `cByte2Hex( nValue )`
            | category: string/hex
            | _kw_: cByte2Hex, Function
   }}*/
/*{{|desc: Converts the low byte of a numeric value to a 2-character uppercase hexadecimal string.
    | params:
    - `nValue` Numeric - Value whose low byte is encoded.

    Returns Returns a 2-character hexadecimal string. }}*/
XPPRET XPPENTRY CBYTE2HEX( XppParamList  pl )
{
   DWCHARUNION dwu;
   BYTE        pHex[ 9 ];

   dwu.i = _parLong( pl, 1 );
   pHex[ 0 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 3 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 1 ] = __HEXNIBBLE__[ ( dwu.ch[ 3 ] & (BYTE) 0x0F ) ];
   pHex[ 2 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 2 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 3 ] = __HEXNIBBLE__[ ( dwu.ch[ 2 ] & (BYTE) 0x0F ) ];
   pHex[ 4 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 1 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 5 ] = __HEXNIBBLE__[ ( dwu.ch[ 1 ] & (BYTE) 0x0F ) ];
   pHex[ 6 ] = __HEXNIBBLE__[ ( ( dwu.ch[ 0 ] >> (BYTE) 4 ) & (BYTE) 0x0F ) ];
   pHex[ 7 ] = __HEXNIBBLE__[ ( dwu.ch[ 0 ] & (BYTE) 0x0F ) ];
   pHex[ 8 ] = 0;
   _retc( pl, (LPSTR) ( pHex + 6 ) );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nHex2Byte
            | syntax_: `nHex2Byte( cHex )`
            | category: string/hex
            | _kw_: nHex2Byte, Function
   }}*/
/*{{|desc: Converts a 2-character hexadecimal byte representation to a numeric value.
    | params:
    - `cHex` Character - Hexadecimal text containing up to 2 hex digits.

    Returns Returns the decoded byte value. }}*/
XPPRET XPPENTRY NHEX2BYTE( XppParamList  pl )
{
   DWCHARUNION dwu;
   BYTE        pHex[ 3 ];

   _parc( (LPSTR) pHex, 3, pl, 1 );
   dwu.ch[ 0 ] = (BYTE) ( ( chHex2Nibble( pHex[ 0 ] ) << 4 ) & 0xF0 );
   dwu.ch[ 0 ] |= ( chHex2Nibble( pHex[ 1 ] ) & 0x0F );
   dwu.ch[ 1 ] = 0;
   dwu.ch[ 2 ] = 0;
   dwu.ch[ 3 ] = 0;
   _retnl( pl, dwu.i );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// flags :

//0x010000 = { {k,v},...,{kN,vN}} pair array 
//0x020000 = extract first value  ( or last if flag 4 ) from { {k,v},...,{kN,vN}} pair array 
//0x040000 = extract first pair   ( or last if flag 4 ) from { {k,v},...,{kN,vN}} pair array 
//0x000001 = case insensitive
//0x000002 = return found index ( first or last if flags & 4 ) 
//0x000004 = stop at last ocurrence
//0x000008 = implicit extra begin and end asterisks in mask
//0x000010 = ltrim
//0x000020 = rtrim
//0x000040 = allow ^ at the begining as negation
//0x000100 = use template characters
//0x000200 = ot4xb_regex_match
//0x008000 = ( without regexp) if ` ( character 96) at the begining the expression must exist
//0x008000 = ( without regexp) if ~ ( character 126) at the begining the expression must not exist
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lStrWildCmp
            | syntax_: `lStrWildCmp( cWild | aWild, cStr [, nFlags] )`
            | category: string/match
            | _kw_: lStrWildCmp, Function
   }}*/
/*{{|desc: Legacy-compatible entry point. The implementation is shared with lStrWildCmpEx(); see
      lStrWildCmpEx() documentation for the full flag reference.
    | params:
    - `cWild` Character/Array - Wildcard pattern, regular expression, or array of patterns, as in
      lStrWildCmpEx().
    - `cStr` Character - String to test.
    - `nFlags` Numeric/Logical - Optional flag mask, as in lStrWildCmpEx(). .T. is accepted as 0x0001.

    Returns Returns .T./.F. by default. The flags described in lStrWildCmpEx() can select the found index,
      value, or pair instead. }}*/
XPPRET XPPENTRY LSTRWILDCMP( XppParamList  pl )
{
   return LSTRWILDCMPEX( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lStrWildCmpEx
            | syntax_: `lStrWildCmpEx( cWild | aWild, cStr [, nFlags] [, nRegexFlags] [, nRegexMatchFlags] )`
            | category: string/match
            | _kw_: lStrWildCmpEx, Function
   }}*/
/*{{|desc: Compares a string against one wildcard pattern, an array of wildcard patterns, or a regular
      expression. lStrWildCmp() is the legacy-compatible name; lStrWildCmpEx() is the extended name. Both use
      the same implementation.
    | params:
    - ``cWild | aWild`` Character/Array - Wildcard pattern, regular expression pattern, or array of
      patterns. Wildcard mode uses '*' and '?' like file masks. With arrays, patterns are tested in array
      order unless the last-occurrence flag is used.
    - `cStr` Character - String to test.
    - `nFlags` Numeric/Logical - Optional bit mask. Combine flags with bitwise OR, for example with nOr(
      flag1, ..., flagX ). 0x0001 - case-insensitive match. For compatibility with the old lStrWildCmp() syntax,
      nFlags may also be logical; .T. is treated as 0x0001 and .F. as 0. 0x0002 - return the found index instead
      of a logical value. 0x0004 - keep scanning and return the last occurrence. 0x0008 - add implicit '*' at
      the beginning and end of the wildcard. 0x0010 - compare the left-trimmed string when not using regular
      expressions. 0x0020 - compare the right-trimmed string when not using regular expressions. 0x0040 - allow
      '^' at the beginning of a wildcard as negation. 0x0100 - use template characters. 0x0200 - use
      ot4xb_regex_match() instead of wildcard matching. 0x8000 - array-only, non-regex mode: a leading '~' means
      the expression must not exist and a leading backtick character means the expression must exist. 0x010000 - aWild is an
      array of { cKey, xValue } pairs and cKey is tested. 0x020000 - with a pair array, return the matching
      value. 0x040000 - with a pair array, return the matching pair.
    - `nRegexFlags` Numeric - Flags used only with 0x0200. Combine flags with bitwise OR, for example with
      nOr( flag1, ..., flagX ). 0x0001 - ECMAScript grammar, default when no grammar flag is supplied. 0x0002 -
      basic grammar. 0x0004 - extended grammar. 0x0008 - awk grammar. 0x0010 - grep grammar. 0x0020 - egrep
      grammar. 0x003F - grammar mask. 0x0100 - icase. 0x0200 - nosubs. 0x0400 - optimize. 0x0800 - collate.
    - `nRegexMatchFlags` Numeric - Match flags used only with 0x0200. Combine flags with bitwise OR, for
      example with nOr( flag1, ..., flagX ). 0x0000 - match_default. 0x0001 - match_not_bol. 0x0002 -
      match_not_eol. 0x0004 - match_not_bow. 0x0008 - match_not_eow. 0x0010 - match_any. 0x0020 -
      match_not_null. 0x0040 - match_continuous. 0x0100 - match_prev_avail. 0x0400 - format_sed. 0x0800 -
      format_no_copy. 0x1000 - format_first_only.

    Returns Returns .T./.F. by default. With 0x0002, returns the found index. With pair-array extraction
      flags, returns the requested value or pair instead of the logical result. In regex mode (0x0200), if the
      C++ regex engine fails (for example an invalid pattern, or a stack overflow from heavy backtracking), the
      function returns NIL, so the failure surfaces as an error at the Xbase level instead of a misleading .F./0
      result. ot4xb_regex_match() returns -1 in that case; a NIL result therefore means "the pattern could not
      be evaluated", not "no match".

    |note: Also `lStrWildCmp( cWild | aWild, cStr [, nFlags] ) -> lMatch | nIndex | xFound`

    |note: lStrWildCmpEx() is useful both for simple wildcard filtering and for regular-expression matching.
      Use 0x0200 when the pattern must be interpreted as a C++ regular expression. Array input is useful for
      testing many wildcard masks against the same string without writing an explicit loop.

    |include-note-id: regex-options }}*/
XPPRET XPPENTRY LSTRWILDCMPEX( XppParamList  pl )
{
   TXppParamList xpp( pl, 5 );
   DWORD found = 0;
   BOOL  bError = 0;   // set when the regex engine reports an error (-1): the function then returns NIL
   DWORD flags = ( xpp[ 3 ]->CheckType( XPP_LOGICAL ) ? ( xpp[ 3 ]->GetBool() ? 1 : 0 ) : xpp[ 3 ]->GetDWord() );
   LPSTR pStr = xpp[ 2 ]->LockStr();
   LPBYTE tb = ( ( flags & 0x101 ) ? ( ( flags & 0x100 ) ? __TEMPLATE_09_AZ_NOCASE__ : _lower_ansi_char_table_ ) : 0 );
   BOOL   use_regex = ( flags & 0x200 ) ? 1 : 0;
   int regex_flags = 0;
   int  regex_match_flags = 0;

   if( use_regex )
   {
      regex_flags = xpp[ 4 ]->GetLong();
      if( ( regex_flags & 0xFF ) == 0 )
      {
         regex_flags |= 1;
      }
      if( flags & 1 )
      {
         regex_flags |= 0x100;
      }
      regex_match_flags = xpp[ 5 ]->GetLong();
   }

   if( pStr )
   {
      if( xpp[ 1 ]->CheckType( XPP_ARRAY ) )
      {
         DWORD count = _conGetArrayLen( xpp[ 1 ]->con() );
         DWORD dw;
         for( dw = 1; dw <= count; dw++ )
         {
            ContainerHandle con = _conNew( 0 );
            if( flags & 0x070000 )  // { {k,v},... } 
            {
               _conArrayGet( xpp[ 1 ]->con(), con, dw, 1, 0 );
            }
            else
            {
               _conArrayGet( xpp[ 1 ]->con(), con, dw, 0 );
            }
            LPSTR pWild = 0;
            ULONG cbWild = 0;
            if( !ot4xb_conRLockC( con, &pWild, &cbWild ) )
            {
               BOOL b;
               if( ( flags & 8 ) && ( !use_regex ) )
               {
                  UINT cb = cbWild + 16;
                  LPSTR buffer = (LPSTR) _xgrab( cb );
                  sprintf_s( buffer, cb, "*%s*", pWild );
                  b = bStrWildCmpWithTableEx( buffer, pStr, tb, flags, 0, 0 );
                  _xfree( (void*) buffer );
                  buffer = 0;
               }
               else
               {
                  b = ( use_regex ? ot4xb_regex_match( pWild, pStr, regex_flags, regex_match_flags ) : bStrWildCmpWithTableEx( pWild, pStr, tb, flags, 0, 0 ) );
               }
               if( b < 0 ) { bError = 1; b = 0; count = 0; }   // regex engine error -> abort loop, return NIL to Xbase
               if( ( flags & 0x8000 ) && ( !use_regex ) )
               {
                  if( b ? ( *pWild == '~' ) : ( *pWild == '`' ) )
                  {
                     found = 0;
                     count = 0;
                  }
                  else
                  {
                     if( b )
                     {
                        found = dw;
                     }
                  }
               }
               else
               {
                  if( b )
                  {
                     found = dw;
                     if( !( flags & 4 ) )
                     {
                        count = 0;
                     }

                  }
               }
               ot4xb_conUnlockC( con );

               if( b && ( flags & 0x060000 ) )  // { {k,v},... } 
               {
                  _conPut( con, NULLCONTAINER );

                  if( ( flags & 0x060000 ) == 0x020000 )   // extract value{ {k,v},... } 
                  {
                     _conArrayGet( xpp[ 1 ]->con(), xpp[ 0 ]->con(), dw, 2, 0 );
                  }
                  if( ( flags & 0x060000 ) == 0x040000 )   // extract pair { {k,v},... } 
                  {
                     _conArrayGet( xpp[ 1 ]->con(), xpp[ 0 ]->con(), dw, 0 );
                  }


               }


            }
            _conRelease( con ); con = 0;

         }
      }
      else
      {
         if( xpp[ 1 ]->CheckType( XPP_CHARACTER ) )
         {
            LPSTR pWild = xpp[ 1 ]->LockStr();

            BOOL b;
            if( ( flags & 8 ) && ( !use_regex ) )
            {
               UINT cb = xpp[ 1 ]->ExLen() + 16;
               LPSTR buffer = (LPSTR) _xgrab( cb );
               sprintf_s( buffer, cb, "*%s*", pWild );
               b = bStrWildCmpWithTableEx( buffer, pStr, tb, flags, 0, 0 );
               _xfree( (void*) buffer );
               buffer = 0;
            }
            else
            {
               b = use_regex ? ot4xb_regex_match( pWild, pStr, regex_flags, regex_match_flags ) : bStrWildCmpWithTableEx( pWild, pStr, tb, flags );
            }
            if( b < 0 ) { bError = 1; b = 0; }   // regex engine error -> return NIL to Xbase
            if( b )
            {
               found = 1;
            }
         }
      }
   }
   xpp[ 2 ]->UnlockStr();
   if( bError )
   {
      // the C++ regex engine failed (e.g. invalid pattern): return NIL so the failure surfaces as an
      // Xbase-level error instead of a misleading .F./0 result
      _conPut( xpp[ 0 ]->con(), NULLCONTAINER );
   }
   else if( !( flags & 0x060000 ) )
   {
      if( flags & 2 )
      {
         xpp[ 0 ]->PutDWord( found );
      }
      else
      {
         xpp[ 0 ]->PutBool( found );
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cDw2Bits
            | syntax_: `cDw2Bits( nInt32 [, nLen] )`
            | category: string/bit
            | _kw_: cDw2Bits, Function
   }}*/
/*{{|desc: Converts a 32-bit numeric value to a character string made of '0' and '1' bytes.
    | params:
    - `nInt32` Numeric - Value interpreted as a 32-bit integer.
    - `nLen` Numeric - Optional result width. Values from 1 to 31 return the rightmost nLen bits.

    Returns Character - Binary text representation. The default width is 32 characters. }}*/
XPPRET XPPENTRY CDW2BITS( XppParamList  pl )
{
   DWORD dw = (DWORD) _parLong( pl, 1 );
   CHAR  sz[ 32 ];
   DWORD n;
   LPSTR p = sz + 32;
   DWORD nLen = (DWORD) _parLong( pl, 2 );
   _bset( (LPBYTE) sz, 0, 32 );
   for( n = 1; n; n <<= 1 ) *--p = ( ( dw & n ) ? '1' : '0' );
   if( ( nLen > 0 ) && ( nLen < 32 ) )
   {
      p = sz + ( 32 - nLen );
      _retclen( pl, p, nLen );
   }
   else _retclen( pl, sz, 32 );
   return;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nBits2Dw
            | syntax_: `nBits2Dw( cBitStr )`
            | category: string/bit
            | _kw_: nBits2Dw, Function
   }}*/
/*{{|desc: Converts a string of '0' and '1' bytes to a 32-bit numeric value.
    | params:
    - `cBitStr` Character - Bit string. The rightmost character is the least significant bit.

    Returns Numeric - 32-bit integer value represented by the bit string.

    |note: Only characters equal to '1' set bits. Other characters are treated as zero. Bits beyond 32 are
      ignored. }}*/
XPPRET XPPENTRY NBITS2DW( XppParamList  pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, 1, &bByRef, XPP_CHARACTER );
   LPSTR pStr;
   ULONG ul;
   DWORD dw = 0;
   if( con )
   {
      if( ot4xb_conRLockC( con, &pStr, &ul ) == 0 )
      {
         LPSTR p = pStr + ul;
         DWORD n = 1;
         while( ( p > pStr ) && n )
         {
            p--;
            if( p[ 0 ] == '1' ) dw |= n;
            n <<= 1;
         }
         ot4xb_conUnlockC( con );
      }
      if( !bByRef ) _conRelease( con );
   }
   _retnl( pl, (LONG) dw );
}
/*{{end-function}}*/
// ---------------------------------------------------------------------------------------------------------------------

typedef BOOLEAN( WINAPI* SystemFunction036_t )( PVOID, ULONG );
BOOL __gen_rnd_str_buffer( LPBYTE buffer, ULONG cb , DWORD flags )
{
   HMODULE hAdvapi = GetModuleHandleA( "advapi32.dll" );
   if( !hAdvapi )
   {
      hAdvapi = LoadLibraryA( "advapi32.dll" );
      if( !hAdvapi )
      {
         return FALSE;
      }
   }
   SystemFunction036_t pRtlGenRandom = (SystemFunction036_t) GetProcAddress( hAdvapi, "SystemFunction036" );
   if( !pRtlGenRandom )
   {
      return FALSE;
   }
   if( !pRtlGenRandom( buffer, cb ) )
   {
      return FALSE;
   }
   switch( flags )
   {
      case 1: // safe chars
      {
         static const char szsc[ ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
         for( ULONG n = 0; n < cb; n++ )
         {
            buffer[ n ] = (BYTE) szsc[ ( (UINT) ( buffer[ n ] % ( sizeof( szsc ) - 1 ) ) ) ];
         }
         break;
      }
      case 2: // safe and upper only
      {
         static const char szsc[ ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
         for( ULONG n = 0; n < cb; n++ )
         {
            buffer[ n ] = (BYTE) szsc[ ( (UINT) ( buffer[ n ] % ( sizeof( szsc ) - 1 ) ) ) ];
         }
         break;
      }
      case 3: // A-Z only
      {
         static const char szsc[ ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
         for( ULONG n = 0; n < cb; n++ )
         {
            buffer[ n ] = (BYTE) szsc[ ( (UINT) ( buffer[ n ] % ( sizeof( szsc ) - 1 ) ) ) ];
         }
         break;
      }
      default:
         break;
   }
   return TRUE;

}



//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cGenRndStr
            | syntax_: `cGenRndStr( nLen [, nMode | lSafeChars] )`
            | category: string/random
            | _kw_: cGenRndStr, Function
   }}*/
/*{{|desc: Generates a random binary string or a random string restricted to a safe character set.
    | params:
    - `nLen` Numeric - Requested length. The implementation limits the allocation to 8 MB.
    - ``nMode | lSafeChars`` Numeric/Logical - Optional mode. .T. is the same as 1. 0 - raw random bytes.
      1 - letters and digits. 2 - uppercase letters and digits. 3 - uppercase letters only.

    Returns Character - Random string, or NIL if the random provider could not be used.

    |note: Random bytes are obtained through SystemFunction036, also known as RtlGenRandom. }}*/
XPPRET XPPENTRY CGENRNDSTR( XppParamList  pl )
{
   TXppParamList xpp( pl, 2 );

   DWORD flags = xpp[ 2 ]->CheckType( XPP_LOGICAL ) ? ( xpp[ 2 ]->GetBool() ? 1 : 0 ) : xpp[ 2 ]->GetDWord();
   ULONG nSize = (ULONG) ( xpp[ 1 ]->GetDWord() & 0x007FFFFF ); // 8MB max
   LPSTR p = (LPSTR) _xgrab( nSize + 1 );
   if( p )
   {
      if( __gen_rnd_str_buffer( (LPBYTE) p, nSize, flags ) )
      {
         xpp[ 0 ]->PutStrLen( p, nSize );
      }
      _xfree( (void*) p );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_nRand
            | syntax_: `ot4xb_nRand( [nMax] )`
            | category: numeric/random
            | _kw_: ot4xb_nRand, Function
   }}*/
/*{{|desc: Generates a random non-negative integer lower than the requested maximum.
    | params:
    - `nMax` Numeric - Exclusive upper bound. If omitted or zero, 0x7FFFFFFF is used.

    Returns Numeric - Random value in the range 0 to nMax - 1, or 0 if the random provider fails.

    |note: The function uses SystemFunction036/RtlGenRandom and rejection sampling to reduce modulo bias. }}*/
XPPRET XPPENTRY OT4XB_NRAND( XppParamList pl )
{
   TXppParamList xpp( pl, 1 );
   DWORD m = xpp[ 1 ]->GetDWord() & 0x7FFFFFFF;
   if( !m )
      m = 0x7FFFFFFF;

   DWORD r = 0;
   if( __gen_rnd_str_buffer( (LPBYTE) &r, sizeof( DWORD ), 0 ) )
   {
      DWORD limit = ( 0xFFFFFFFFu / m ) * m;
      int tries = 0;

      while( r >= limit && tries++ < 16 )
      {
         if( !__gen_rnd_str_buffer( (LPBYTE) &r, sizeof( DWORD ), 0 ) )
            break;
      }

      r %= m;
      xpp[ 0 ]->PutDWord( r );
   }
   else
   {
      xpp[ 0 ]->PutDWord( 0 );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: TxtSplitLinesToTList
            | syntax_: `TList * TxtSplitLinesToTList( LPSTR pStr, DWORD dwFlags )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: TxtSplitLinesToTList
            | _kw_: TxtSplitLinesToTList, Function
   }}*/
/*{{|desc: Splits a zero-terminated text buffer into lines, overwriting the CRLF, CR or LF separators with
      zero bytes and collecting a pointer to each line in a new TList. Same as TxtSplitLinesToTListEx()
      without the skip-offset output.
    | params:
    - `pStr` LPSTR - Zero-terminated text buffer, modified in place.
    - `dwFlags` DWORD - Bit mask. 0x01 - left-trim each line. 0x02 - right-trim each line. 0x10 - remove
      lines left empty. 0x20 - remove lines starting with ';'. 0x40 - remove lines starting with '['. 0x100 -
      parse e-mail header lines; every other flag is then ignored.

    Returns TList * - New list with one pointer per line, pointing into pStr. The caller deletes the list. }}*/
OT4XB_API TList* TxtSplitLinesToTList( LPSTR pStr, DWORD dwFlags )
{
   return TxtSplitLinesToTListEx( pStr, dwFlags, 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: TxtSplitLinesToTListEx
            | syntax_: `TList * TxtSplitLinesToTListEx( LPSTR pStr, DWORD dwFlags, DWORD * pdwSkip )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: TxtSplitLinesToTListEx
            | _kw_: TxtSplitLinesToTListEx, Function
   }}*/
/*{{|desc: Splits a zero-terminated text buffer into lines, overwriting the CRLF, CR or LF separators with
      zero bytes and collecting a pointer to each line in a new TList. Trimming treats spaces, tabs, CR and
      LF as blank bytes. In e-mail header mode (0x100) scanning stops after the empty line that closes the
      header block, continuation lines starting with a space or tab are joined to the previous line, and
      runs of blank bytes are condensed to a single space.
    | params:
    - `pStr` LPSTR - Zero-terminated text buffer, modified in place.
    - `dwFlags` DWORD - Bit mask. 0x01 - left-trim each line. 0x02 - right-trim each line. 0x10 - remove
      lines left empty. 0x20 - remove lines starting with ';'. 0x40 - remove lines starting with '['. 0x100 -
      parse e-mail header lines; every other flag is then ignored.
    - `pdwSkip` DWORD * - Optional. In e-mail header mode it receives the byte offset just after the
      header block, so the caller can locate the body. May be NULL.

    Returns TList * - New list with one pointer per line, pointing into pStr. The caller deletes the list. }}*/
OT4XB_API TList* TxtSplitLinesToTListEx( LPSTR pStr, DWORD dwFlags, DWORD* pdwSkip )
{
   DWORD dw = 0;
   TList* pList = new TList;
   BYTE bt[ 256 ]; ZeroMemory( bt, 256 );
   bt[ 9 ] = bt[ 10 ] = bt[ 13 ] = bt[ 32 ] = 1;
   if( !pdwSkip )
   {
      pdwSkip = &dw;
   }
   if( dwFlags & 0x100 )
   {
      dwFlags = 0x100;
   }
   if( pStr )
   {

      LPSTR p = pStr;
      pList->Add( (void*) p );
      while( *p )
      {
         BOOL bAdd = FALSE;
         switch( *p )
         {
            case 13:
            {
               *p++ = 0;
               if( *p == 10 )
               {
                  *p++ = 0;
               }
               if( dwFlags & 0x100 ) // email header
               {
                  if( *p == 13 )
                  {  // stop scanning after CRLF + CRLF found
                     *p = 0;
                     if( p[ 1 ] == 10 )
                     {
                        p++;
                        *p = 0;
                     }
                     pdwSkip[ 0 ] = ( ( (DWORD) p ) + 1 ) - ( (DWORD) pStr );
                     break;
                  }
               }
               bAdd = TRUE;
               break;
            }
            case 10:
            {
               *p++ = 0;
               if( dwFlags & 0x100 )  // email header
               {
                  if( *p == 10 )
                  {  // stop scanning after LF + LF found
                     *p = 0;
                     pdwSkip[ 0 ] = ( ( (DWORD) pStr ) + 1 ) - ( (DWORD) p );
                     break;
                  }
               }
               bAdd = TRUE;
               break;
            }
            default:
            {
               p++; break;
            }
         }
         if( bAdd )
         {
            if( dwFlags & 0xFF )
            {
               LPBYTE pp = (LPBYTE) pList->Tail();
               UINT cb = _xstrlen( (LPSTR) pp );
               if( dwFlags & 2 )
               {
                  cb = ByteMapTable_RTrimEx( bt, pp, cb );
               }
               if( dwFlags & 1 )
               {
                  cb = ByteMapTable_LTrimEx( bt, pp, cb );
               }
               if( dwFlags & 3 )
               {
                  pp[ cb ] = 0;
               }
               if( ( ( !cb ) && ( dwFlags & 0x10 ) ) || ( cb && ( dwFlags & 0x20 ) && ( pp[ 0 ] == ';' ) ) || ( cb && ( dwFlags & 0x40 ) && ( pp[ 0 ] == '[' ) ) )
               {
                  pList->Pop();
               }

            }
            else if( dwFlags & 0x100 )
            {
               if( ( ( *p == 9 ) || ( *p == 32 ) ) && pList->Count() )
               {
                  // use LF to join the new line with previous
                  LPBYTE pp = (LPBYTE) pList->Tail();
                  for( ; pp < ( (LPBYTE) p ); pp++ )
                  {
                     if( *pp == 0 )
                     {
                        *pp = 10;
                     }
                  }
                  bAdd = FALSE;
               }

            }
            if( bAdd ) // maybe dissabled by 0x100
            {
               pList->Add( (void*) p );
            }
         }
      }
      if( ( dwFlags & 0xFF ) && pList->Count() ) // ignore empty lines
      {
         LPBYTE pp = (LPBYTE) pList->Tail();
         UINT cb = _xstrlen( (LPSTR) pp );
         if( dwFlags & 2 )
         {
            cb = ByteMapTable_RTrimEx( bt, pp, cb );
         }
         if( dwFlags & 1 )
         {
            cb = ByteMapTable_LTrimEx( bt, pp, cb );
         }
         if( dwFlags & 3 )
         {
            pp[ cb ] = 0;
         }
         if( ( !cb ) && ( dwFlags & 0x10 ) )
         {
            pList->Pop();
         }
      }

      if( dwFlags & 0x100 )
      {
         DWORD n;
         DWORD nn = pList->Count();
         for( n = 0; n < nn; n++ )
         {
            LPBYTE pp = (LPBYTE) pList->Get( n );
            int    cb = ByteMapTable_CondenseString( bt, pp, -1 );
            cb = ByteMapTable_RTrimEx( bt, pp, cb );
            cb = ByteMapTable_LTrimEx( bt, pp, cb );
            pp[ cb ] = 0;
         }
      }



   }
   return pList;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: aSplitTxtLines
            | syntax_: `aSplitTxtLines( cText [, nFlags] [, @nShift] )`
            | category: string
            | _kw_: aSplitTxtLines, Function
   }}*/
/*{{|desc: Splits a text buffer into lines and optionally applies simple trimming, filtering, e-mail-header
      parsing, or INI-style key/value parsing.
    | params:
    - `cText` Character - Text buffer to split. CRLF, CR, and LF line endings are accepted.
    - `nFlags` Numeric - Optional bit mask that controls trimming, filtering, and parsing mode. 0x0001
      trims leading spaces and tabs. 0x0002 trims trailing spaces and tabs. 0x0010 removes empty lines after
      trimming. 0x0020 removes lines whose first remaining character is ';'. 0x0040 removes lines whose first
      remaining character is '['. 0x0100 parses e-mail header lines. 0x0200 parses INI-style lines as key/value
      pairs when possible. 0x1200 is 0x0200 | 0x1000: preserved section, comment, and empty entries are also
      returned as key/value pairs.
    - `nShift` Numeric by reference - Receives the byte offset where scanning stopped. This is mainly used
      by e-mail-header mode to locate the text after the header block. In the ordinary line-split modes it is
      normally 0.

    Returns Returns an array of lines in the ordinary mode. With 0x0100, returns a two-column array where each
      row is { cHeaderName, cHeaderValue }; continuation lines are folded into the previous header. With 0x0200,
      normal INI assignment lines are split at the first '=' and returned as { cKey, cValue }. Ordinary
      non-assignment lines are returned as { cLine, "" }. Empty, comment, and section lines may be removed by
      the filtering flags; if they are preserved, 0x0200 returns them as plain character entries, while 0x1200
      returns them as { cLine, "" } so every preserved INI entry has the same key/value shape. Returns NIL when
      cText is not supplied. }}*/
XPPRET XPPENTRY ASPLITTXTLINES( XppParamList pl )
{
   ContainerHandle conr = NULLCONTAINER;
   LPSTR pStr = _pszParam( pl, 1 );
   DWORD dwFlags = (DWORD) _parnl( pl, 2 );
   DWORD dwShift = 0;
   if( pStr )
   {
      TList* pList = TxtSplitLinesToTListEx( pStr, dwFlags, &dwShift );
      _stornl( (LONG) dwShift, pl, 3 );
      if( pList )
      {
         ULONG n;
         ULONG nItems = pList->Count();
         switch( dwFlags & 0x300 )
         {
            case 0x100:
            {
               conr = _conNewArray( 2, nItems, 2 );
               for( n = 0; n < nItems; n++ )
               {
                  LPSTR k = (LPSTR) pList->Get( n );
                  LPSTR v = 0;
                  LPSTR p;
                  for( p = k; ( ( *p ) && ( v == 0 ) ); p++ )
                  {
                     if( *p == ':' )
                     {
                        *p++ = 0;
                        while( ( *p == 32 ) || ( *p == 9 ) )
                        {
                           *p++ = 0;
                        }
                        v = p;
                     }
                  }

                  _conArrayPutC( conr, k, ( n + 1 ), 1, 0 );
                  if( v )
                  {
                     _conArrayPutC( conr, v, ( n + 1 ), 2, 0 );
                  }
                  else
                  {
                     _conArrayPutC( conr, "", ( n + 1 ), 2, 0 );
                  }
               }
               break;
            }
            case 0x200:
            {
               conr = _conNewArray( 2, nItems, 2 );
               for( n = 0; n < nItems; n++ )
               {
                  LPSTR k = (LPSTR) pList->Get( n );
                  LPSTR v = 0;
                  LPSTR p = k;
                  while( ( *p == 32 ) || ( *p == 9 ) )
                  {
                     p++;
                  }
                  switch( *p )
                  {

                     case '[':
                     {
                        if( !( dwFlags & 0x40 ) )
                        {
                           if( dwFlags & 0x1000 )
                           {
                              _conArrayPutC( conr, p, ( n + 1 ), 1, 0 );
                              _conArrayPutC( conr, "", ( n + 1 ), 2, 0 );
                           }
                           else
                           {
                              _conArrayPutC( conr, p, ( n + 1 ), 0 );
                           }
                        }
                        break;
                     }
                     case ';':
                     {
                        if( !( dwFlags & 0x20 ) )
                        {
                           if( dwFlags & 0x1000 )
                           {
                              _conArrayPutC( conr, p, ( n + 1 ), 1, 0 );
                              _conArrayPutC( conr, "", ( n + 1 ), 2, 0 );
                           }
                           else
                           {
                              _conArrayPutC( conr, p, ( n + 1 ), 0 );
                           }
                        }
                        break;
                     }
                     case 0:
                     {
                        if( !( dwFlags & 0x10 ) )
                        {
                           if( dwFlags & 0x1000 )
                           {
                              _conArrayPutC( conr, p, ( n + 1 ), 1, 0 );
                              _conArrayPutC( conr, "", ( n + 1 ), 2, 0 );
                           }
                           else
                           {
                              _conArrayPutC( conr, "", ( n + 1 ), 0 );
                           }
                        }
                        break;
                     }
                     default:
                     {

                        for( p = k; ( ( *p ) && ( v == 0 ) ); p++ )
                        {
                           if( *p == '=' )
                           {
                              *p++ = 0;
                              while( ( *p == 32 ) || ( *p == 9 ) )
                              {
                                 *p++ = 0;
                              }
                              v = p;
                           }
                        }

                        _conArrayPutC( conr, k, ( n + 1 ), 1, 0 );
                        if( v )
                        {
                           _conArrayPutC( conr, v, ( n + 1 ), 2, 0 );
                        }
                        else
                        {
                           _conArrayPutC( conr, "", ( n + 1 ), 2, 0 );
                        }
                        break;
                     }
                  }
               }
               break;
            }
            default:
            {
               conr = _conNewArray( 1, nItems );
               for( n = 0; n < nItems; n++ )
               {
                  _conArrayPutC( conr, (LPSTR) pList->Get( n ), ( n + 1 ), 0 );
               }
               break;
            }
         }
         delete pList;
      }
      _xfree( (void*) pStr );
   }
   if( conr )
   {
      _conReturn( pl, conr );
      _conRelease( conr );
   }
   else
   {
      _ret( pl );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_urlencode
            | syntax_: `LPSTR ot4xb_urlencode( LPSTR pIn, DWORD cbIn, DWORD * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_urlencode
            | _kw_: ot4xb_urlencode, Function
   }}*/
/*{{|desc: URL-encodes a byte buffer into a newly allocated string. Bytes other than ASCII letters and
      digits are written as '%' followed by two uppercase hexadecimal digits; a space becomes %20, not '+'.
    | params:
    - `pIn` LPSTR - Source buffer.
    - `cbIn` DWORD - Number of source bytes to encode.
    - `pcbOut` DWORD * - Optional. Receives the encoded length in bytes. May be NULL.

    Returns LPSTR - New zero-terminated string allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL. }}*/
OT4XB_API LPSTR ot4xb_urlencode( LPSTR pIn, DWORD cbIn, DWORD* pcbOut )
{
   DWORD cb = 0;
   LPSTR pOut = 0;
   if( pIn )
   {
      DWORD n;
      LPBYTE p, pp;
      cb = cbIn;
      p = (LPBYTE) pIn;
      for( n = 0; n < cbIn; n++, p++ )
      {
         if( !__SAFECHAR__[ *p ] ) cb += 2;
      }
      pOut = (LPSTR) _xgrab( cb + 1 );
      p = (LPBYTE) pIn;
      pp = (LPBYTE) pOut;
      for( n = 0; n < cbIn; n++, p++ )
      {
         if( __SAFECHAR__[ *p ] ) *pp++ = *p;
         else
         {
            *pp++ = '%';
            *pp++ = __HEXNIBBLE__[ MSNIBBLE( p[ 0 ] ) ];
            *pp++ = __HEXNIBBLE__[ LSNIBBLE( p[ 0 ] ) ];
         }
      }
   }
   if( pcbOut ) pcbOut[ 0 ] = cb;
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_urlencode_cb
            | syntax_: `DWORD ot4xb_urlencode_cb( LPBYTE pIn, DWORD cbIn )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_urlencode_cb
            | _kw_: ot4xb_urlencode_cb, Function
   }}*/
/*{{|desc: Calculates the length needed to URL-encode a byte buffer, without producing output: one byte per
      ASCII letter or digit and three bytes for any other value.
    | params:
    - `pIn` LPBYTE - Source buffer. NULL yields 0.
    - `cbIn` DWORD - Number of source bytes.

    Returns DWORD - Encoded length in bytes, with no room counted for a zero terminator. }}*/
OT4XB_API DWORD ot4xb_urlencode_cb( LPBYTE pIn, DWORD cbIn )
{
   DWORD cb = 0;
   if( pIn )
   {
      DWORD n;
      cb = cbIn;
      for( n = 0; n < cbIn; n++, pIn++ )
      {
         if( !__SAFECHAR__[ *pIn ] ) cb += 2;
      }
   }
   return cb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_urlencode_buffer
            | syntax_: `DWORD ot4xb_urlencode_buffer( LPBYTE pIn, DWORD cbIn, LPBYTE pOut, DWORD cbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_urlencode_buffer
            | _kw_: ot4xb_urlencode_buffer, Function
   }}*/
/*{{|desc: URL-encodes a byte buffer into a caller-supplied buffer. Bytes other than ASCII letters and
      digits are written as '%' followed by two uppercase hexadecimal digits.
    | params:
    - `pIn` LPBYTE - Source buffer.
    - `cbIn` DWORD - Number of source bytes to encode.
    - `pOut` LPBYTE - Destination buffer.
    - `cbOut` DWORD - Destination capacity in bytes.

    Returns DWORD - Number of bytes written, without any zero terminator, or (DWORD) -1 when a pointer is
      NULL or the encoded data does not fit in cbOut. }}*/
OT4XB_API DWORD ot4xb_urlencode_buffer( LPBYTE pIn, DWORD cbIn, LPBYTE pOut, DWORD cbOut )
{
   if( pIn && pOut )
   {
      DWORD cb = ot4xb_urlencode_cb( pIn, cbIn );
      if( cb > cbOut )
      {
         return (DWORD) -1;
      }
      for( ; cbIn; cbIn--, pIn++ )
      {
         if( __SAFECHAR__[ *pIn ] )
         {
            *pOut++ = *pIn;
         }
         else
         {
            *pOut++ = '%';
            *pOut++ = __HEXNIBBLE__[ MSNIBBLE( pIn[ 0 ] ) ];
            *pOut++ = __HEXNIBBLE__[ LSNIBBLE( pIn[ 0 ] ) ];
         }
      }
      return cb;
   }
   return (DWORD) -1;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: TZString_urlencode_add(TZString*,LPSTR,DWORD)
            | _tg_: TZString_urlencode_add
            | syntax_: `BOOL TZString_urlencode_add( TZString * psc, LPSTR pIn, DWORD cb )`
            | category: string/encoding
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?TZString_urlencode_add@@YAHPAVTZString@@PADK@Z
            | _kw_: TZString_urlencode_add, Function
   }}*/
/*{{|desc: Appends a URL-encoded copy of a byte buffer to a TZString. Bytes other than ASCII letters and
      digits are appended as '%' followed by two uppercase hexadecimal digits.
    | params:
    - `psc` TZString * - Target dynamic string.
    - `pIn` LPSTR - Source buffer.
    - `cb` DWORD - Number of source bytes.

    Returns BOOL - TRUE when the buffer was appended; FALSE when psc or pIn is NULL or cb is 0. }}*/
OT4XB_API BOOL TZString_urlencode_add( TZString* psc, LPSTR pIn, DWORD cb )
{
   if( psc && pIn && cb )
   {
      LPBYTE p = (LPBYTE) pIn;
      DWORD n;
      for( n = 0; n < cb; n++, p++ )
      {
         if( __SAFECHAR__[ *p ] ) psc->AddChar( (char) *p );
         else
         {
            psc->AddChar( '%' );
            psc->AddChar( (char) __HEXNIBBLE__[ MSNIBBLE( *p ) ] );
            psc->AddChar( (char) __HEXNIBBLE__[ LSNIBBLE( *p ) ] );
         }
      }
      return TRUE;
   }
   return FALSE;
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: TZString_urlencode_add_con(TZString*,ContainerHandle)
            | _tg_: TZString_urlencode_add_con
            | syntax_: `BOOL TZString_urlencode_add_con( TZString * psc, ContainerHandle con )`
            | category: string/encoding
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?TZString_urlencode_add_con@@YAHPAVTZString@@PAUMomHandleEntry@@@Z
            | _kw_: TZString_urlencode_add_con, Function
   }}*/
/*{{|desc: Appends a URL-encoded copy of the contents of a character container to a TZString.
    | params:
    - `psc` TZString * - Target dynamic string.
    - `con` ContainerHandle - Container holding a character value.

    Returns BOOL - TRUE when the text was appended. FALSE when psc is NULL, the container does not hold a
      character value, it cannot be locked, or the string is empty. }}*/
OT4XB_API BOOL TZString_urlencode_add_con( TZString* psc, ContainerHandle con )
{
   BOOL bOk = FALSE;
   if( psc && _conCheckType( con, XPP_CHARACTER ) )
   {
      LPSTR p = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( con, &p, &cb ) == 0 )
      {
         bOk = TZString_urlencode_add( psc, p, cb );
         ot4xb_conUnlockC( con );
      }
   }
   return bOk;
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: TZString_add_con(TZString*,ContainerHandle)
            | _tg_: TZString_add_con
            | syntax_: `BOOL TZString_add_con( TZString * psc, ContainerHandle con )`
            | category: string
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?TZString_add_con@@YAHPAVTZString@@PAUMomHandleEntry@@@Z
            | _kw_: TZString_add_con, Function
   }}*/
/*{{|desc: Appends the contents of a character container to a TZString. The text is appended as a C string,
      so it stops at the first zero byte.
    | params:
    - `psc` TZString * - Target dynamic string.
    - `con` ContainerHandle - Container holding a character value.

    Returns BOOL - TRUE when the text was appended; FALSE when psc is NULL, the container does not hold a
      character value, or it cannot be locked. }}*/
OT4XB_API BOOL TZString_add_con( TZString* psc, ContainerHandle con )
{
   BOOL bOk = FALSE;
   if( psc && _conCheckType( con, XPP_CHARACTER ) )
   {
      LPSTR p = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( con, &p, &cb ) == 0 )
      {
         psc->Add( p );
         bOk = TRUE;
         ot4xb_conUnlockC( con );
      }
   }
   return bOk;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: Bin2Hex_buffer
            | syntax_: `int Bin2Hex_buffer( LPBYTE pb, UINT cb, LPSTR buffer, UINT buffer_cb )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: Bin2Hex_buffer
            | _kw_: Bin2Hex_buffer, Function
   }}*/
/*{{|desc: Converts binary bytes to uppercase hexadecimal text in a caller-supplied buffer, two characters
      per source byte. No zero terminator is written.
    | params:
    - `pb` LPBYTE - Source bytes.
    - `cb` UINT - Number of source bytes.
    - `buffer` LPSTR - Destination buffer.
    - `buffer_cb` UINT - Destination capacity in bytes; at least cb * 2.

    Returns int - Number of characters written (cb * 2), or 0 when the destination is too small. }}*/
OT4XB_API int Bin2Hex_buffer( LPBYTE pb, UINT cb, LPSTR buffer, UINT buffer_cb )
{
   if( buffer_cb < ( cb * 2 ) )
   {
      return 0;
   }
   LPSTR pp = buffer;
   ULONG n;
   for( n = 0; n < cb; n++ )
   {
      *pp++ = __HEXNIBBLE__[ MSNIBBLE( pb[ n ] ) ];
      *pp++ = __HEXNIBBLE__[ LSNIBBLE( pb[ n ] ) ];
   }
   return ( cb * 2 );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pBin2Hex
            | syntax_: `LPSTR pBin2Hex( LPBYTE pb, UINT cb )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: pBin2Hex
            | _kw_: pBin2Hex, Function
   }}*/
/*{{|desc: Converts binary bytes to a newly allocated uppercase hexadecimal string, two characters per
      source byte.
    | params:
    - `pb` LPBYTE - Source bytes.
    - `cb` UINT - Number of source bytes.

    Returns LPSTR - New zero-terminated string allocated with _xgrab(); release it with _xfree(). }}*/
OT4XB_API LPSTR pBin2Hex( LPBYTE pb, UINT cb )
{
   LPSTR ph = (LPSTR) _xgrab( ( cb * 2 ) + 1 );
   Bin2Hex_buffer( pb, cb, ph, cb * 2 );
   return ph;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pHex2Bin
            | syntax_: `LPBYTE pHex2Bin( LPSTR ph, DWORD * pcb )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: pHex2Bin
            | _kw_: pHex2Bin, Function
   }}*/
/*{{|desc: Decodes a zero-terminated hexadecimal string into a newly allocated binary buffer. Characters
      that are not hexadecimal digits are skipped and act as byte separators: a lone digit between
      separators produces a byte holding just that nibble value.
    | params:
    - `ph` LPSTR - Zero-terminated text with hexadecimal digits.
    - `pcb` DWORD * - Optional. Receives the number of decoded bytes. May be NULL.

    Returns LPBYTE - New buffer allocated with _xgrab(); release it with _xfree(). }}*/
OT4XB_API LPBYTE pHex2Bin( LPSTR ph, DWORD* pcb )
{
   ULONG cb = 0;
   LPBYTE pp, pb, p;
   BOOL  bh;

   for( pp = (LPBYTE) ph; *pp; pp++ )
   {
      if( __NIBBLECHAR__[ *pp ] )
      {
         cb++;
      }
   }
   if( cb & 1 )
   {
      cb++;
   }
   pb = (LPBYTE) _xgrab( ( cb >> 1 ) + 1 );
   for( cb = 0, p = pb, bh = 0, pp = (LPBYTE) ph; *pp; pp++ )
   {
      if( __NIBBLECHAR__[ *pp ] )
      {
         if( bh )
         {
            *p = ( ( *p << 4 ) & 0xF0 ) | ( __NIBBLECHAR__[ *pp ] & 0x0F ); p++; bh = 0;
         }
         else
         {
            *p = ( __NIBBLECHAR__[ *pp ] & 0x0F ); cb++; bh = 1;
         }
      }
      else if( bh )
      {
         bh = 0; p++;
      }
   }
   if( pcb ) pcb[ 0 ] = cb;
   return pb;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pHex2i64
            | syntax_: `LONGLONG pHex2i64( LPBYTE ph, DWORD cb )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: pHex2i64
            | _kw_: pHex2i64, Function
   }}*/
/*{{|desc: Parses hexadecimal text into a 64-bit integer. Hexadecimal digits are shifted into the result; an
      'x' or 'X' resets the accumulated value, so text with a 0x prefix parses correctly; any other
      character is ignored.
    | params:
    - `ph` LPBYTE - Text buffer to parse. NULL returns 0.
    - `cb` DWORD - Number of bytes to scan. A value with the high bit set, such as (DWORD) -1, scans up
      to the zero terminator.

    Returns LONGLONG - Parsed value. There is no overflow check; extra digits shift the oldest ones out. }}*/
OT4XB_API LONGLONG pHex2i64( LPBYTE ph, DWORD cb )
{
   LONGLONG q = 0;
   if( !ph ) return 0;
   if( cb & 0x80000000 )
   {
      cb = _xstrlen( (LPSTR) ph );
   }
   for( ; ( cb && ( *ph ) ); cb--, ph++ )
   {
      BYTE n = __NIBBLECHAR__[ *ph ];
      if( n )
      {
         q = ( ( q << 4 ) | ( n & 0x0F ) );
      }
      else
      {
         if( ( *ph == 'x' ) || ( *ph == 'X' ) )
         {
            q = 0;
         }
      }
   }
   return q;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: pHex2i32
            | syntax_: `DWORD pHex2i32( LPBYTE ph, DWORD cb )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: pHex2i32
            | _kw_: pHex2i32, Function
   }}*/
/*{{|desc: Parses hexadecimal text into a 32-bit integer. Hexadecimal digits are shifted into the result; an
      'x' or 'X' resets the accumulated value, so text with a 0x prefix parses correctly; any other
      character is ignored.
    | params:
    - `ph` LPBYTE - Text buffer to parse. NULL returns 0.
    - `cb` DWORD - Number of bytes to scan. A value with the high bit set, such as (DWORD) -1, scans up
      to the zero terminator.

    Returns DWORD - Parsed value. There is no overflow check; extra digits shift the oldest ones out. }}*/
OT4XB_API DWORD pHex2i32( LPBYTE ph, DWORD cb )
{
   DWORD dw = 0;
   if( !ph ) return 0;
   if( cb & 0x80000000 )
   {
      cb = _xstrlen( (LPSTR) ph );
   }
   for( ; ( cb && ( *ph ) ); cb--, ph++ )
   {
      BYTE n = __NIBBLECHAR__[ *ph ];
      if( n )
      {
         dw = ( ( dw << 4 ) | ( n & 0x0F ) );
      }
      else
      {
         if( ( *ph == 'x' ) || ( *ph == 'X' ) )
         {
            dw = 0;
         }
      }
   }
   return dw;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_RO_LtrimEx
            | syntax_: ```
                 BOOL ByteMapTable_RO_LtrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn, LPBYTE & pOut, DWORD & cbOut )
              ```
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_RO_LtrimEx
            | _kw_: ByteMapTable_RO_LtrimEx, Function
   }}*/
/*{{|desc: Computes a left-trimmed view of a byte buffer without modifying it: leading bytes flagged in the
      map table are skipped and the resulting pointer and length are returned by reference.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks a byte value to trim. NULL selects the
      default white-space table (tab, LF, CR and space).
    - `pIn` LPBYTE - Source buffer. It is not modified.
    - `cbIn` DWORD - Source length in bytes.
    - `pOut` LPBYTE & - Receives the address of the first byte that is not trimmed.
    - `cbOut` DWORD & - Receives the remaining length.

    Returns BOOL - TRUE on success; FALSE when pIn is NULL or cbIn is negative as an int, leaving pOut and
      cbOut untouched. }}*/
OT4XB_API BOOL  ByteMapTable_RO_LtrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn, LPBYTE& pOut, DWORD& cbOut )
{

   if( pTable == 0 )
   {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }
   if( !pIn || (int) cbIn  < 0 )
   {
      return FALSE;
   }
   pOut = pIn;
   cbOut = cbIn;

   while( cbOut && pTable[ (BYTE) *pOut ] )
   {
      pOut++; cbOut--;
   }
   return TRUE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_RO_RtrimEx
            | syntax_: ```
                 BOOL ByteMapTable_RO_RtrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn, LPBYTE & pOut, DWORD & cbOut )
              ```
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_RO_RtrimEx
            | _kw_: ByteMapTable_RO_RtrimEx, Function
   }}*/
/*{{|desc: Computes a right-trimmed length of a byte buffer without modifying it: cbOut receives the length
      with trailing map-flagged bytes discarded, while pOut receives pIn unchanged.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks a byte value to trim. NULL selects the
      default white-space table (tab, LF, CR and space).
    - `pIn` LPBYTE - Source buffer. It is not modified.
    - `cbIn` DWORD - Source length in bytes.
    - `pOut` LPBYTE & - Receives pIn.
    - `cbOut` DWORD & - Receives the length without the trailing trimmed bytes.

    Returns BOOL - TRUE on success; FALSE when pIn is NULL or cbIn is negative as an int, leaving pOut and
      cbOut untouched. }}*/
OT4XB_API BOOL  ByteMapTable_RO_RtrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn, LPBYTE& pOut, DWORD& cbOut )
{

   if( pTable == 0 )
   {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }
   if( !pIn || (int) cbIn < 0 )
   {
      return FALSE;
   }
   pOut = pIn;
   cbOut = cbIn;

   while( cbOut && pTable[ (BYTE) pOut[ cbOut -1 ]] )
   {
      cbOut--;
   }
   return TRUE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_RTrimEx
            | syntax_: `DWORD ByteMapTable_RTrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_RTrimEx
            | _kw_: ByteMapTable_RTrimEx, Function
   }}*/
/*{{|desc: Returns the length of a byte buffer once trailing bytes flagged in the map table are discarded.
      The buffer itself is not modified.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks a byte value to trim. NULL selects the
      default white-space table (tab, LF, CR and space).
    - `pIn` LPBYTE - Source buffer.
    - `cbIn` DWORD - Source length in bytes. A negative value as an int uses the zero-terminated length.

    Returns DWORD - Length without the trailing trimmed bytes; 0 when pIn is NULL or every byte is trimmed. }}*/
OT4XB_API DWORD ByteMapTable_RTrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn )
{

   if( pTable == 0 )
   {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }
   if( !pIn )
   {
      return 0;
   }
   if( ( (int) cbIn ) < 0 )
   {
      cbIn = _xstrlen( (LPSTR) pIn );
   }
   if( !cbIn )
   {
      return 0;
   }
   for( ; cbIn; cbIn-- )
   {
      if( pTable[ ( pIn[ ( cbIn - 1 ) ] ) ] == 0 )
      {
         return cbIn;
      }
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_LTrimEx
            | syntax_: `DWORD ByteMapTable_LTrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_LTrimEx
            | _kw_: ByteMapTable_LTrimEx, Function
   }}*/
/*{{|desc: Removes leading bytes flagged in the map table by shifting the remaining bytes to the start of
      the buffer. No zero terminator is written at the new length.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks a byte value to trim. NULL selects the
      default white-space table (tab, LF, CR and space).
    - `pIn` LPBYTE - Buffer modified in place.
    - `cbIn` DWORD - Source length in bytes. A negative value as an int uses the zero-terminated length.

    Returns DWORD - Remaining length; 0 when pIn is NULL or every byte is trimmed. }}*/
OT4XB_API DWORD ByteMapTable_LTrimEx( LPBYTE pTable, LPBYTE pIn, DWORD cbIn )
{

   if( pTable == 0 )
   {
      pTable = __DEFAULT_WHITE_SPACE_TABLE__;
   }

   if( !pIn )
   {
      return 0;
   }
   if( ( (int) cbIn ) < 0 )
   {
      cbIn = _xstrlen( (LPSTR) pIn );
   }
   if( !cbIn )
   {
      return 0;
   }


   DWORD n = 0;
   for( ; ( ( n < cbIn ) && pTable[ ( pIn[ n ] ) ] ); n++ );
   if( n )
   {
      cbIn -= n;
      LPBYTE p = _mk_ptr_( LPBYTE, pIn, n );
      for( n = 0; n < cbIn; n++ )
      {
         pIn[ n ] = p[ n ];
      }
   }
   return cbIn;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

//StrTrimEx(1cStr,2cTrimChars,3nFlags,4chReplaceForCondenseSTRING) > cTrimmed string 
//      0x01 - Trim characters on the left side of the string
//      0x02 - Trim characters on the right side of the string
//      0x03 - Trim characters on both sides of the string
//      0x100 - Condense String
//      0x200 - Remove unsafe	( list is safe unless 0x1000 )
//      0x1000 - INVERT TABLE  if 0x200 only then list is unsafe
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: StrTrimEx
            | syntax_: `StrTrimEx( cText, cTableBytes, nFlags [, cCondenseChar] )`
            | category: string
            | _kw_: StrTrimEx, Function
   }}*/
/*{{|desc: Trims, condenses, or filters a string using a caller-supplied byte table.
    | params:
    - `cText` Character - Text to process.
    - `cTableBytes` Character - Bytes used to build the trim/filter table.
    - `nFlags` Numeric - Optional bit mask. 0x0001 - trim table bytes from the left side. 0x0002 - trim
      table bytes from the right side. 0x0003 - trim table bytes from both sides. 0x0100 - condense runs of
      table bytes. 0x0200 - remove unsafe bytes. 0x1000 - invert the table; with 0x0200, cTableBytes is treated
      as the unsafe list.
    - `cCondenseChar` Character - Optional replacement byte used when condensing. Space is used by default.

    Returns Returns the processed string. When 0x0200 is used without 0x1000, cTableBytes is the safe list;
      with 0x1000, cTableBytes is the unsafe list.

    |example: // Keep only digits and ':' from a timestamp-like string. cDigitsAndTime := StrTrimEx(
      cTimestamp, "0123456789:", 0x0200 ) }}*/
_XPP_REG_FUN_( STRTRIMEX )
{
   TXppParamList xpp( pl, 4 );
   BYTE pTable[ 256 ];
   DWORD dwFlags = xpp[ 3 ]->GetDWord();
   DWORD dw;

   if( ( dwFlags & 0x1200 ) == 0x1200 )
   {
      for( dw = 0; dw < sizeof( pTable ); dw++ )
      {
         pTable[ dw ] = (BYTE) ( dw & 0xFF );
      }
   }
   else
   {
      ZeroMemory( pTable, sizeof( pTable ) );
   }

   if( xpp[ 2 ]->CheckType( XPP_CHARACTER ) )
   {
      LPBYTE pt = (LPBYTE) xpp[ 2 ]->RLockStrEx();
      DWORD  cbt = xpp[ 2 ]->ExLen();
      if( pt && cbt )
      {
         if( ( dwFlags & 0x1200 ) == 0x200 )
         {
            for( ; cbt; pt++, cbt-- )
            {
               pTable[ *pt ] = *pt;
            }
         }
         else
         {
            if( ( dwFlags & 0x1200 ) == 0x1200 )
            {
               for( ; cbt; pt++, cbt-- )
               {
                  pTable[ *pt ] = 0;
               }
            }
            else
            {
               for( ; cbt; pt++, cbt-- )
               {
                  pTable[ *pt ] = 1;
               }
            }
         }
      }
      xpp[ 2 ]->UnLockStrEx();
   }
   DWORD   cb = 0;
   LPBYTE  p = (LPBYTE) xpp[ 1 ]->StrDupA( &cb );
   if( p )
   {
      if( dwFlags & 2 )
      {
         cb = ByteMapTable_RTrimEx( pTable, p, cb );
      }
      if( dwFlags & 1 )
      {
         cb = ByteMapTable_LTrimEx( pTable, p, cb );
      }
      if( dwFlags & 0x100 )
      {
         BYTE ch = 0x20;
         xpp[ 4 ]->GetCL( (LPSTR) &ch, 4 );
         cb = ByteMapTable_CondenseString( pTable, p, cb, ch );
      }
      if( dwFlags & 0x200 )
      {
         cb = ByteMapTable_RemoveUnsafe( pTable, p, cb );
      }
      xpp[ 0 ]->PutStrLen( (LPSTR) p, cb );
      _xfree( (void*) p );
   }
   else
   {
      xpp[ 0 ]->PutStr( "" );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_Add
            | syntax_: `void ByteMapTable_Add( LPBYTE pTable, LPBYTE pPos, LPBYTE pMap, DWORD cb )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_Add
            | _kw_: ByteMapTable_Add, Function
   }}*/
/*{{|desc: Fills entries of a 256-byte map table. For each byte in pPos, the table entry indexed by that
      byte value is set to the corresponding byte of pMap.
    | params:
    - `pTable` LPBYTE - 256-byte map table to update.
    - `pPos` LPBYTE - Byte values selecting the table entries to write.
    - `pMap` LPBYTE - Values stored in the selected entries, parallel to pPos.
    - `cb` DWORD - Number of entries to write.

    Returns void }}*/
OT4XB_API void ByteMapTable_Add( LPBYTE pTable, LPBYTE pPos, LPBYTE pMap, DWORD cb )
{
   if( pTable && pPos && pMap && cb )
   {
      DWORD n;
      for( n = 0; n < cb; n++ )
      {
         pTable[ ( pPos[ n ] ) ] = pMap[ n ];
      }
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_IsSafeStr
            | syntax_: `BOOL ByteMapTable_IsSafeStr( LPBYTE pTable, LPBYTE p, int cb )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_IsSafeStr
            | _kw_: ByteMapTable_IsSafeStr, Function
   }}*/
/*{{|desc: Tests whether every byte of a buffer is flagged as accepted (nonzero) in the map table.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks an accepted byte value.
    - `p` LPBYTE - Buffer to test.
    - `cb` int - Number of bytes to test, or -1 to use the zero-terminated length.

    Returns BOOL - TRUE when all bytes are accepted, or when p is NULL or the length is 0; FALSE at the
      first rejected byte. }}*/
OT4XB_API BOOL  ByteMapTable_IsSafeStr( LPBYTE pTable, LPBYTE p, int cb )
{
   BOOL bOk = TRUE;
   if( p )
   {
      if( cb == -1 )
      {
         cb = _xstrlen( (LPSTR) p );
      }
      for( ; cb > 0; cb--, p++ )
      {
         if( !pTable[ ( *p ) ] )
         {
            return FALSE;
         }
      }
   }
   return bOk;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_safe_strlen
            | syntax_: `DWORD ByteMapTable_safe_strlen( BYTE map[ 256 ], LPSTR p )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_safe_strlen
            | _kw_: ByteMapTable_safe_strlen, Function
   }}*/
/*{{|desc: Counts the bytes of a zero-terminated string whose values are flagged (nonzero) in the map table:
      the length the string would have once the unflagged bytes are removed.
    | params:
    - `]` BYTE map[ 256 - 256-byte map where a nonzero entry marks a counted byte value.
    - `p` LPSTR - Zero-terminated string to scan.

    Returns DWORD - Number of flagged bytes; 0 when p or map is NULL. }}*/
OT4XB_API DWORD  ByteMapTable_safe_strlen( BYTE map[ 256 ], LPSTR p )
{
   DWORD cb = 0;

   if( p && map )
   {
      for( ; *p; p++ )
      {
         if( map[ (BYTE) *p ] & 0xFF )
         {
            cb++;
         }
      }
   }
   return cb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_RemoveUnsafe
            | syntax_: `int ByteMapTable_RemoveUnsafe( LPBYTE pTable, LPBYTE p, int cb )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_RemoveUnsafe
            | _kw_: ByteMapTable_RemoveUnsafe, Function
   }}*/
/*{{|desc: Removes the bytes not flagged in the map table, compacting the buffer in place. Kept bytes are
      written back through their table entry, so a map holding translated values converts while it filters.
      No zero terminator is written at the new length.
    | params:
    - `pTable` LPBYTE - 256-byte map. A zero entry removes the byte; a nonzero entry keeps it and
      supplies the value actually stored.
    - `p` LPBYTE - Buffer modified in place.
    - `cb` int - Number of bytes to process, or -1 to use the zero-terminated length.

    Returns int - Remaining length; 0 when p or pTable is NULL. }}*/
OT4XB_API int  ByteMapTable_RemoveUnsafe( LPBYTE pTable, LPBYTE p, int cb )
{
   if( !( p && pTable ) )
   {
      return 0;
   }
   LPBYTE pp = p;
   int n, nn;
   if( cb == -1 )
   {
      cb = _xstrlen( (LPSTR) p );
   }
   nn = cb;
   for( n = 0; n < nn; n++, p++ )
   {
      if( pTable[ *p ] )
      {
         *pp = pTable[ *p ];
         pp++;
      }
      else
      {
         *p = 0;
         cb--;
      }
   }
   return cb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_CondenseString
            | syntax_: `int ByteMapTable_CondenseString( LPBYTE pTable, LPBYTE p, int cb, BYTE chFill )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_CondenseString
            | _kw_: ByteMapTable_CondenseString, Function
   }}*/
/*{{|desc: Collapses each run of map-flagged bytes into one single byte, modifying the buffer in place.
      Typically used with a white-space table to condense repeated blanks. No zero terminator is written at
      the new length.
    | params:
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks the byte values to condense.
    - `p` LPBYTE - Buffer modified in place.
    - `cb` int - Number of bytes to process, or -1 to use the zero-terminated length.
    - `chFill` BYTE - Replacement written for each run. 0 keeps the first byte of the run instead.

    Returns int - Remaining length; 0 when p or pTable is NULL. }}*/
OT4XB_API int  ByteMapTable_CondenseString( LPBYTE pTable, LPBYTE p, int cb, BYTE chFill )
{
   if( !( p && pTable ) )
   {
      return 0;
   }
   LPBYTE pp = p;
   int n, nn;
   BOOL b = FALSE;
   if( cb == -1 )
   {
      cb = _xstrlen( (LPSTR) p );
   }
   nn = cb;
   for( n = 0; n < nn; n++, p++ )
   {
      if( pTable[ *p ] )
      {
         if( b )
         {
            *p = 0;
            cb--;
         }
         else
         {
            b = TRUE;
            *pp = ( chFill ? chFill : *p );
            pp++;
         }
      }
      else
      {
         b = FALSE;
         *pp = *p;
         pp++;
      }
   }
   return cb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_FillSeq
            | syntax_: `void ByteMapTable_FillSeq( LPBYTE pTable, LPWORD pSeq, DWORD sc )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_FillSeq
            | _kw_: ByteMapTable_FillSeq, Function
   }}*/
/*{{|desc: Fills identity entries of a 256-byte map table from a sequence of byte ranges: every table entry
      inside each range is set to its own index value.
    | params:
    - `pTable` LPBYTE - 256-byte map table to update.
    - `pSeq` LPWORD - Range words. In each WORD the low byte is the first value of the range and the
      high byte is the last one, both inclusive.
    - `sc` DWORD - Number of range words in pSeq.

    Returns void }}*/
OT4XB_API void ByteMapTable_FillSeq( LPBYTE pTable, LPWORD pSeq, DWORD sc )
{
   if( pTable && pSeq && sc )
   {
      DWORD ss;
      for( ss = 0; ss < sc; ss++ )
      {
         WORD n;
         WORD nn = MAKEWORD( HIBYTE( pSeq[ ss ] ), 0 );
         for( n = MAKEWORD( LOBYTE( pSeq[ ss ] ), 0 ); n <= nn; n++ )
         {
            pTable[ n ] = ( n & 0xFF );
         }
      }
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ByteMapTable_StrFindFlag
            | syntax_: `DWORD ByteMapTable_StrFindFlag( LPBYTE pSrc, int cb, int nStart, LPBYTE pTable, DWORD dwFlags )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ByteMapTable_StrFindFlag
            | _kw_: ByteMapTable_StrFindFlag, Function
   }}*/
/*{{|desc: Moves a cursor position to the next or previous word boundary in a byte buffer. Bytes flagged in
      the map table act as word separators.
    | params:
    - `pSrc` LPBYTE - Buffer to scan.
    - `cb` int - Buffer length in bytes.
    - `nStart` int - Current zero-based position. Out-of-range values are clamped into the buffer.
    - `pTable` LPBYTE - 256-byte map where a nonzero entry marks a separator byte.
    - `dwFlags` DWORD - 1 - find the start of the next word. 2 - find the start of the previous word.

    Returns DWORD - New zero-based position, or (DWORD) -1 when cb is lower than 1, a pointer is NULL, or
      dwFlags is not 1 or 2. }}*/
OT4XB_API DWORD ByteMapTable_StrFindFlag( LPBYTE pSrc, int cb, int nStart, LPBYTE pTable, DWORD dwFlags )
{
   if( cb < 1 ) return (DWORD) -1;
   if( nStart < 0 ) nStart = 0;
   if( nStart >= cb ) nStart = ( cb - 1 );
   if( pSrc && cb && pTable )
   {
      switch( dwFlags )
      {
         case 0x0001: // find next word
         {
            int n = nStart;
            if( n > 0 ) n++;
            if( n >= cb ) return cb - 1;
            if( !pTable[ ( pSrc[ n ] ) ] )
            {
               while( ( n < cb ) && ( !pTable[ ( pSrc[ n ] ) ] ) ) n++;
            }
            else
            {
               while( ( n < cb ) && ( pTable[ ( pSrc[ n ] ) ] ) ) n++;
               while( ( n < cb ) && ( !pTable[ ( pSrc[ n ] ) ] ) ) n++;
            }
            return n;
         }
         case 0x0002: // find prev word
         {
            int n = nStart;
            if( n > 0 ) n--;
            if( !pTable[ ( pSrc[ n ] ) ] )
            {
               while( ( n > 0 ) && ( !pTable[ ( pSrc[ n ] ) ] ) ) n--;
               if( n )
               {
                  while( ( n > 0 ) && pTable[ ( pSrc[ n ] ) ] ) n--;
                  if( !pTable[ ( pSrc[ n ] ) ] ) n++;
               }
            }
            else
            {
               while( n && pTable[ ( pSrc[ n ] ) ] ) n--;
               if( !pTable[ ( pSrc[ n ] ) ] ) n++;
            }
            return n;
         }
      }
   }
   return (DWORD) -1;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: cp850_to_html
            | syntax_: `LPSTR cp850_to_html( LPSTR pIn, UINT * pcbOut, DWORD dwFlags )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: cp850_to_html
            | _kw_: cp850_to_html, Function
   }}*/
/*{{|desc: Converts code page 850 text to HTML in a newly allocated buffer. Characters above 127 become HTML
      entities and the markup characters '&', '<' and '>' are escaped.
    | params:
    - `pIn` LPSTR - Zero-terminated source text.
    - `pcbOut` UINT * - Optional. Receives the length of the converted text. May be NULL.
    - `dwFlags` DWORD - Bit mask. 0x01 - convert line breaks to `<br>`. 0x02 - emit a space followed by
      another space as &nbsp;. 0x04 - map accented letters to their upper-case entities. 0x10 - without
      0x01, drop the LF of each CRLF pair.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or empty. }}*/
OT4XB_API LPSTR cp850_to_html( LPSTR pIn, UINT* pcbOut, DWORD dwFlags )
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp850_to_html( pIn, dwFlags );
   pOut = zs.Detach( pcbOut, 0 );
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: cp437_to_html
            | syntax_: `LPSTR cp437_to_html( LPSTR pIn, UINT * pcbOut, DWORD dwFlags )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: cp437_to_html
            | _kw_: cp437_to_html, Function
   }}*/
/*{{|desc: Converts code page 437 text to HTML in a newly allocated buffer. Characters above 127 become HTML
      entities and the markup characters '&', '<' and '>' are escaped.
    | params:
    - `pIn` LPSTR - Zero-terminated source text.
    - `pcbOut` UINT * - Optional. Receives the length of the converted text. May be NULL.
    - `dwFlags` DWORD - Bit mask. 0x01 - convert line breaks to `<br>`. 0x02 - emit a space followed by
      another space as &nbsp;. 0x04 - map accented letters to their upper-case entities. 0x10 - without
      0x01, drop the LF of each CRLF pair.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or empty. }}*/
OT4XB_API LPSTR cp437_to_html( LPSTR pIn, UINT* pcbOut, DWORD dwFlags )
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp437_to_html( pIn, dwFlags );
   pOut = zs.Detach( pcbOut, 0 );
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: cp1252_to_html
            | syntax_: `LPSTR cp1252_to_html( LPSTR pIn, UINT * pcbOut, DWORD dwFlags )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: cp1252_to_html
            | _kw_: cp1252_to_html, Function
   }}*/
/*{{|desc: Converts code page 1252 (Windows ANSI) text to HTML in a newly allocated buffer. Characters above
      127 become HTML entities and the markup characters '&', '<' and '>' are escaped.
    | params:
    - `pIn` LPSTR - Zero-terminated source text.
    - `pcbOut` UINT * - Optional. Receives the length of the converted text. May be NULL.
    - `dwFlags` DWORD - Bit mask. 0x01 - convert line breaks to `<br>`. 0x02 - emit a space followed by
      another space as &nbsp;. 0x04 - map accented letters to their upper-case entities. 0x10 - without
      0x01, drop the LF of each CRLF pair.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or empty. }}*/
OT4XB_API LPSTR cp1252_to_html( LPSTR pIn, UINT* pcbOut, DWORD dwFlags )
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_cp1252_to_html( pIn, dwFlags );
   pOut = zs.Detach( pcbOut, 0 );
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: escape_to_xml
            | syntax_: `LPSTR escape_to_xml( LPSTR pIn, UINT * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: escape_to_xml
            | _kw_: escape_to_xml, Function
   }}*/
/*{{|desc: Escapes text for XML or HTML content in a newly allocated buffer: '&' becomes &amp;, '"' becomes
      &quot;, '<' becomes &lt;, '>' becomes &gt; and the single quote becomes &#39;. Every other byte is
      copied unchanged.
    | params:
    - `pIn` LPSTR - Zero-terminated source text.
    - `pcbOut` UINT * - Optional. Receives the length of the escaped text. May be NULL.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or empty. }}*/
OT4XB_API LPSTR escape_to_xml( LPSTR pIn, UINT* pcbOut )
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_to_xml( pIn );
   pOut = zs.Detach( pcbOut, 0 );
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: escape_to_json
            | syntax_: `LPSTR escape_to_json( LPSTR pIn, int cb, UINT * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: escape_to_json
            | _kw_: escape_to_json, Function
   }}*/
/*{{|desc: Escapes text for the body of a JSON string in a newly allocated buffer. Control bytes, '"' and
      the backslash use the standard JSON escapes and bytes above 127 are converted from ANSI to \uXXXX
      escapes. The surrounding double quotes are not added.
    | params:
    - `pIn` LPSTR - Source text.
    - `cb` int - Number of bytes to escape, or -1 to use the zero-terminated length.
    - `pcbOut` UINT * - Optional. Receives the length of the escaped text. May be NULL.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or nothing was produced. }}*/
OT4XB_API LPSTR escape_to_json( LPSTR pIn, int cb, UINT* pcbOut )
{
   TZString zs;
   LPSTR pOut = 0;
   zs.Add_to_json( pIn, cb );
   pOut = zs.Detach( pcbOut, 0 );
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xbenc2bin
            | syntax_: `LPSTR ot4xbenc2bin( LPSTR pIn, UINT cb, UINT * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xbenc2bin
            | _kw_: ot4xbenc2bin, Function
   }}*/
/*{{|desc: Decodes ot4xb escape-encoded text back to binary. Backslash escapes are expanded: \xHH gives a
      hexadecimal byte, \dNNN a decimal byte, \0 a zero byte, \s a space, \q a double quote, \a \b \f \n \r
      \t \v the usual control bytes and \\ a backslash; a backslash before any other character yields that
      character unchanged.
    | params:
    - `pIn` LPSTR - Encoded text.
    - `cb` UINT - Number of bytes to decode. Pass INFINITE to use the zero-terminated length.
    - `pcbOut` UINT * - Optional. Receives the decoded length. May be NULL.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL. }}*/
OT4XB_API LPSTR ot4xbenc2bin( LPSTR pIn, UINT cb, UINT* pcbOut )
{
   LPSTR pOut = 0;
   UINT  cbo = 0;
   if( cb == INFINITE ) cb = _xstrlen( pIn );
   if( pIn )
   {
      UINT n;
      pOut = (LPSTR) _xgrab( cb + 1 );

      for( n = 0; n < cb; n++ )
      {
         if( ( pIn[ n ] == '\\' ) && ( ( n + 1 ) < cb ) )
         {
            n++;
            switch( (BYTE) pIn[ n ] )
            {
               case 'x': // \x00
               {
                  BYTE hnib;
                  BYTE lnib;
                  n++; hnib = chHex2Nibble( ( n < cb ) ? ( (BYTE) pIn[ n ] ) : 0 );
                  n++; lnib = chHex2Nibble( ( n < cb ) ? ( (BYTE) pIn[ n ] ) : 0 );
                  pOut[ cbo ] = (char) ( ( hnib << 4 ) | lnib );
                  cbo++;
                  break;
               }
               case 'd': // \d000
               {
                  char sz[ 4 ];
                  n++; sz[ 0 ] = ( ( n < cb ) ? pIn[ n ] : 0 );
                  n++; sz[ 1 ] = ( ( n < cb ) ? pIn[ n ] : 0 );
                  n++; sz[ 2 ] = ( ( n < cb ) ? pIn[ n ] : 0 );
                  sz[ 3 ] = 0;
                  pOut[ cbo ] = (char) ( atoi( sz ) & 0xFF );
                  cbo++;
                  break;
               }
               case '0':
               {
                  pOut[ cbo ] = 0; cbo++; break;
               } //  NULL
               case 's':
               {
                  pOut[ cbo ] = 0x20; cbo++; break;
               } //  space
               case 'q':
               {
                  pOut[ cbo ] = 0x22; cbo++; break;
               } //  Double Quote
               case 'a':
               {
                  pOut[ cbo ] = '\a'; cbo++; break;
               } //  Bell (alert)
               case 'b':
               {
                  pOut[ cbo ] = '\b'; cbo++; break;
               } //  Backspace
               case 'f':
               {
                  pOut[ cbo ] = '\f'; cbo++; break;
               } //  Formfeed
               case 'n':
               {
                  pOut[ cbo ] = '\n'; cbo++; break;
               } //  New line
               case 'r':
               {
                  pOut[ cbo ] = '\r'; cbo++; break;
               } //  Carriage return
               case 't':
               {
                  pOut[ cbo ] = '\t'; cbo++; break;
               } //  Horizontal tab
               case 'v':
               {
                  pOut[ cbo ] = '\v'; cbo++; break;
               } //  Vertical tab
               case '\\':
               {
                  pOut[ cbo ] = '\\'; cbo++; break;
               } //  Backslash
               default:
               {
                  pOut[ cbo ] = pIn[ n ]; cbo++; break;
               } //
            }
         }
         else
         {
            pOut[ cbo ] = pIn[ n ]; cbo++;
         } //
      }
   }
   if( pOut )
   {
      pOut[ cbo ] = 0;
   }
   if( pcbOut ) pcbOut[ 0 ] = cbo;
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bin2ot4xbenc_ta
            | syntax_: `LPSTR bin2ot4xbenc_ta( LPSTR pIn, UINT cb, UINT * pcbOut, UINT * lt, UINT * rt )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: bin2ot4xbenc_ta
            | _kw_: bin2ot4xbenc_ta, Function
   }}*/
/*{{|desc: Encodes binary data like bin2ot4xbenc() but first strips leading and trailing spaces from the
      input and reports how many were removed on each side, so the exact original string can be rebuilt when
      the counts are stored apart.
    | params:
    - `pIn` LPSTR - Source bytes.
    - `cb` UINT - Number of source bytes. Pass (UINT) -1 to use the zero-terminated length.
    - `pcbOut` UINT * - Optional. Receives the encoded length. May be NULL.
    - `lt` UINT * - Receives the number of leading spaces removed. Must not be NULL.
    - `rt` UINT * - Receives the number of trailing spaces removed. Must not be NULL.

    Returns LPSTR - New zero-terminated string allocated with _xgrab(); release it with _xfree(). }}*/
OT4XB_API LPSTR bin2ot4xbenc_ta( LPSTR pIn, UINT cb, UINT* pcbOut, UINT* lt, UINT* rt )
{

   if( cb == ( (UINT) -1 ) )
   {
      cb = _xstrlen( pIn );
   }
   lt[ 0 ] = 0; rt[ 0 ] = 0;
   while( cb && pIn[ 0 ] == 0x20 )
   {
      cb--; lt[ 0 ]++; pIn = _mk_ptr_( LPSTR, pIn, 1 );
   }
   while( cb && pIn[ ( cb - 1 ) ] == 0x20 )
   {
      cb--; rt[ 0 ]++;
   }
   return bin2ot4xbenc( pIn, cb, pcbOut );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bin2ot4xbenc
            | syntax_: `LPSTR bin2ot4xbenc( LPSTR pIn, UINT cb, UINT * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: bin2ot4xbenc
            | _kw_: bin2ot4xbenc, Function
   }}*/
/*{{|desc: Encodes binary data into the printable ot4xb escape encoding, reversible with ot4xbenc2bin().
      Bytes outside the 32 to 127 range become \xHH escapes and the usual control bytes use their short
      escapes; '%', '&', '<' and '>' are escaped as \xHH, '"' becomes \q and a backslash is doubled. A space
      stays literal unless it is the last byte or is followed by another space, in which case it becomes \s.
    | params:
    - `pIn` LPSTR - Source bytes.
    - `cb` UINT - Number of source bytes. Pass (UINT) -1 to use the zero-terminated length.
    - `pcbOut` UINT * - Optional. Receives the encoded length. May be NULL.

    Returns LPSTR - New zero-terminated string allocated with _xgrab(); release it with _xfree(). }}*/
OT4XB_API LPSTR bin2ot4xbenc( LPSTR pIn, UINT cb, UINT* pcbOut )
{
   if( cb == ( (UINT) -1 ) )
   {
      cb = _xstrlen( pIn );
   }

   TZString z( cb );
   UINT n;
   for( n = 0; n < cb; n++ )
   {
      BYTE ch = (BYTE) pIn[ n ];
      switch( ch )
      {
         case 0:
         {
            z.Add( "\\0" ); break;
         }
         case 0x20:
         {
            if( n == ( cb - 1 ) )
            {
               z.Add( "\\s" );
            }
            else
            {
               if( ( (BYTE) pIn[ ( n + 1 ) ] ) == ch )
               {
                  z.Add( "\\s" );
               }
               else
               {
                  z.AddChar( (char) ch );
               }
            }
            break;
         }
         case '%':
         {
            z.Add( "\\x25" ); break;
         }
         case '&':
         {
            z.Add( "\\x26" ); break;
         }
         case '<':
         {
            z.Add( "\\x3C" ); break;
         }
         case '>':
         {
            z.Add( "\\x3E" ); break;
         }
         case '"':
         {
            z.Add( "\\q" ); break;
         } //  Double Quote
         case '\a':
         {
            z.Add( "\\a" ); break;
         } //  Bell (alert)
         case '\b':
         {
            z.Add( "\\b" ); break;
         } //  Backspace
         case '\f':
         {
            z.Add( "\\f" ); break;
         } //  Formfeed
         case '\n':
         {
            z.Add( "\\n" ); break;
         } //  New line
         case '\r':
         {
            z.Add( "\\r" ); break;
         } //  Carriage return
         case '\t':
         {
            z.Add( "\\t" ); break;
         } //  Horizontal tab
         case '\v':
         {
            z.Add( "\\v" ); break;
         } //  Vertical tab
         case '\\':
         {
            z.AddChar( '\\' ); z.AddChar( '\\' ); break;
         } //  Backslash
         default:
         {
            if( ( ch < 32 ) || ( ch > 127 ) )
            {
               z.printf( "\\x%02.2X", ch );
            }
            else
            {
               z.AddChar( (char) ch );
            }
            break;
         }
      }
   }
   return z.Detach( pcbOut );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// quot 0x22  - 5
// amp  0x26  - 4
// apos 0x27  - 5
// lt   0x3C  - 3
// gt   0x3E  - 3
// -----------------------------------------------------------------------------------------------------------------
// x_www_form_urlencoded_to_cp1252(LPSTR pIn , UINT cb, void** ppInfo) -> pString
// return a decoded string ( urldecode + utftoansi )
// optionally ppInfo will retrieve a pointer to x_www_form_cp1252_Header_t
// followed by nItems x_www_form_cp1252_KeyVal_t
// this info is marshalled inside pString only 1 pointer to release
static LPSTR x_www_form_urlencoded_internal( LPSTR pIn, UINT cb, void** ppInfo, BOOL u2a_convert )
{
   x_www_form_cp1252_Header_t* h = 0;
   LPSTR pOut = 0;
   UINT  nItemCount = 0;
   if( pIn )
   {
      if( ( (int) cb ) < 0 )
      {
         cb = _xstrlen( pIn );
      }
   }
   if( pIn && cb )
   {
      LPSTR p = pIn;
      UINT  n = 0;
      if( p[ 0 ] == '?' )
      {
         n++;
      }
      if( ( n < cb ) && ( p[ n ] ) )
      {
         nItemCount++;
      }
      for( ; ( n < cb ) && p[ n ]; n++ )
      {
         if( p[ n ] == '&' )
         {
            nItemCount++;
         }
      }
   }
   if( !nItemCount )
   {
      if( ppInfo )
      {
         ppInfo[ 0 ] = 0;
      } return 0;
   }
   pOut = x_www_form_cp1252_Header_t::AllocStr( cb, nItemCount, h );
   if( ppInfo )
   {
      ppInfo[ 0 ] = (void*) h;
   }
   h->decode_and_parse_string( pIn, cb, u2a_convert );
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: x_www_form_urlencoded_to_cp1252
            | syntax_: `LPSTR x_www_form_urlencoded_to_cp1252( LPSTR pIn, UINT cb, void * * ppInfo )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: x_www_form_urlencoded_to_cp1252
            | _kw_: x_www_form_urlencoded_to_cp1252, Function
   }}*/
/*{{|desc: Decodes application/x-www-form-urlencoded data, such as an URL query string or a POST body, into
      key and value pairs. Percent escapes and '+' are decoded and every value is converted from UTF-8 to
      the ANSI code page. The result is marshalled inside one allocation: the returned string block also
      holds a x_www_form_cp1252_Header_t followed by one x_www_form_cp1252_KeyVal_t per item.
    | params:
    - `pIn` LPSTR - Form-encoded source. A leading '?' is skipped.
    - `cb` UINT - Number of source bytes. A negative value as an int uses the zero-terminated length.
    - `ppInfo` void * * - Optional. Receives the pointer to the x_www_form_cp1252_Header_t stored inside
      the returned allocation. May be NULL.

    Returns LPSTR - Decoded block allocated with _xgrab(); releasing this single pointer with _xfree() also
      releases the parsed info. NULL when the source holds no items. }}*/
OT4XB_API LPSTR x_www_form_urlencoded_to_cp1252( LPSTR pIn, UINT cb, void** ppInfo )
{
   return x_www_form_urlencoded_internal( pIn, cb, ppInfo, TRUE );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: x_www_form_urlencoded_ncp
            | syntax_: `LPSTR x_www_form_urlencoded_ncp( LPSTR pIn, UINT cb, void * * ppInfo )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: x_www_form_urlencoded_ncp
            | _kw_: x_www_form_urlencoded_ncp, Function
   }}*/
/*{{|desc: Same parsing as x_www_form_urlencoded_to_cp1252() for content that is already in the target code
      page: percent escapes and '+' are decoded but the values get no UTF-8 conversion.
    | params:
    - `pIn` LPSTR - Form-encoded source. A leading '?' is skipped.
    - `cb` UINT - Number of source bytes. A negative value as an int uses the zero-terminated length.
    - `ppInfo` void * * - Optional. Receives the pointer to the x_www_form_cp1252_Header_t stored inside
      the returned allocation. May be NULL.

    Returns LPSTR - Decoded block allocated with _xgrab(); releasing this single pointer with _xfree() also
      releases the parsed info. NULL when the source holds no items. }}*/
OT4XB_API LPSTR x_www_form_urlencoded_ncp( LPSTR pIn, UINT cb, void** ppInfo )
{
   return x_www_form_urlencoded_internal( pIn, cb, ppInfo, FALSE );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
x_www_form_cp1252_KeyVal_t* x_www_form_cp1252_KeyVal_t::next( void )
{
   return (x_www_form_cp1252_KeyVal_t*) _mk_ptr_( LPVOID, this, sizeof( x_www_form_cp1252_KeyVal_t ) );
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR x_www_form_cp1252_Header_t::AllocStr( UINT cb, UINT nItemCount, x_www_form_cp1252_Header_t*& ph )
{
   UINT cbb = cb + ( nItemCount * 2 ) + 4;
   UINT cbt = cbb + sizeof( x_www_form_cp1252_Header_t ) + ( sizeof( x_www_form_cp1252_KeyVal_t ) * ( nItemCount + 1 ) );
   void* p = _xgrab( cbt );
   ph = (x_www_form_cp1252_Header_t*) _mk_ptr_( LPVOID, p, cbb );
   ph->m_pBuffer = (LPSTR) p;
   ph->m_cbBuffer = cbt;
   ph->m_cbString = 0;
   ph->m_nItemCount = 0;
   return (LPSTR) p;
}
// -----------------------------------------------------------------------------------------------------------------
x_www_form_cp1252_KeyVal_t* x_www_form_cp1252_Header_t::first( void )
{
   return (x_www_form_cp1252_KeyVal_t*) _mk_ptr_( LPVOID, this, sizeof( x_www_form_cp1252_Header_t ) );
}
// -----------------------------------------------------------------------------------------------------------------
void x_www_form_cp1252_Header_t::decode_and_parse_string( LPSTR p, UINT cb, BOOL u2a_convert )
{
   if( cb < 1 )
   {
      return;
   }
   if( *p == '?' )
   {
      cb--; p++;
   }
   if( cb < 1 )
   {
      return;
   }
   x_www_form_cp1252_KeyVal_t* k;
   LPSTR pOut = m_pBuffer;
   void* buffer = _xgrab( m_cbBuffer );
   for( k = first(); cb; k = k->next() )
   {
      if( k->read_and_decode( p, cb, pOut, m_cbString, buffer, u2a_convert ) ) m_nItemCount++;
   }
   _xfree( buffer );
}
// -----------------------------------------------------------------------------------------------------------------
BOOL x_www_form_cp1252_KeyVal_t::read_and_decode( LPSTR& pIn, UINT& cbIn, LPSTR& pOut, UINT& cbOut, void* buffer, BOOL u2a_convert )
{
   if( !cbIn )
   {
      return 0;
   }
   LPSTR p = (LPSTR) buffer;
   UINT cb = 0;
   BOOL bk = FALSE;
   while( cbIn )
   {
      char ch = *pIn; pIn++; cbIn--;
      switch( ch )
      {
         case '\0':
         case '&':
         {
            goto label_exit_loop_1;
         }
         case '+':
         {
            p[ cb ] = 0x20; cb++; break;
         }
         case '\r':
         case '\n':
         case '\t':
         case 0x20:
         {
            break;
         } // ignore blank spaces and line feeds
         case '%':
         {
            if( cbIn < 2 )
            {
               cbIn = 0; goto label_exit_loop_1;
            }
            BYTE hi = __NIBBLECHAR__[ ( (BYTE) *pIn ) ]; pIn++; cbIn--;
            BYTE lo = __NIBBLECHAR__[ ( (BYTE) *pIn ) ]; pIn++; cbIn--;
            if( hi && lo )
            {
               p[ cb ] = (char) ( ( ( hi << 4 ) & 0xF0 ) | ( lo & 0x0F ) );
               cb++;
            }
            break;
         }
         case '=':
         {
            if( bk ) // usually encoded but are allowed inside the value
            {
               p[ cb ] = ch; cb++;
            }
            else
            {
               bk = TRUE;
               p[ cb ] = 0; cb++;
               m_pKey = pOut;
               m_cbKey = cb - 1;
               _bcopy( (LPBYTE) pOut, (LPBYTE) buffer, cb );
               pOut = _mk_ptr_( LPSTR, pOut, cb );
               cbOut += cb;
               p = (LPSTR) buffer; cb = 0;
            }
            break;
         }
         default:
         {
            p[ cb ] = ch; cb++; break;
         }
      }
   }
label_exit_loop_1:;
   if( !bk )
   {
      m_pKey = pOut; m_cbKey = 0; pOut[ 0 ] = 0; pOut++; cbOut++;
   }
   p[ cb ] = 0;
   if( cb )
   {
      if( u2a_convert )
      {
         int    cc = 0;
         LPWSTR pw = utf82w( (LPSTR) buffer, cb, &cc );
         m_pVal = pOut;
         cb = WideCharToMultiByte( CP_ACP, 0, pw, cc, NULL, 0, 0, 0 );
         m_cbVal = WideCharToMultiByte( CP_ACP, 0, pw, cc, m_pVal, cb + 1, 0, 0 );
         pOut = _mk_ptr_( LPSTR, pOut, cb + 1 );
         cbOut += cb + 1;
         _xfree( (void*) pw );
      }
      else
      {
         m_pVal = pOut;
         _bcopy( (LPBYTE) m_pVal, (LPBYTE) buffer, cb + 1 );
         m_cbVal = cb + 1;
         pOut = _mk_ptr_( LPSTR, pOut, cb + 1 );
         cbOut += cb + 1;
      }
   }
   else
   {
      m_pVal = pOut; m_cbVal = 0; pOut[ 0 ] = 0; pOut++; cbOut++;
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_urldecode
            | syntax_: `LPSTR ot4xb_urldecode( LPSTR pIn, DWORD cbIn, DWORD * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_urldecode
            | _kw_: ot4xb_urldecode, Function
   }}*/
/*{{|desc: URL-decodes a byte buffer into a newly allocated string. '+' becomes a space and every valid %XX
      pair becomes one byte; carriage returns, line feeds, tabs and spaces in the source are ignored;
      scanning stops at a zero byte.
    | params:
    - `pIn` LPSTR - Encoded source.
    - `cbIn` DWORD - Number of source bytes. A value with the high bit set is treated as 0.
    - `pcbOut` DWORD * - Optional. Receives the decoded length. May be NULL.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL or the length is 0. }}*/
OT4XB_API LPSTR ot4xb_urldecode( LPSTR pIn, DWORD cbIn, DWORD* pcbOut )
{
   LPSTR pOut = 0;
   DWORD cb = 0;
   if( cbIn & 0x80000000 )
   {
      cbIn = 0;
   } // disallow negative numbers

   if( pIn && cbIn )
   {
      LPSTR p = pOut = (LPSTR) _xgrab( cbIn + 2 );
      while( cbIn )
      {
         char ch = *pIn; pIn++; cbIn--;
         switch( ch )
         {
            case '\0':
            {
               goto label_exit_loop_1;
            }
            case '+':
            {
               p[ cb ] = 0x20; cb++; break;
            }
            case '\r':
            case '\n':
            case '\t':
            case 0x20:
            {
               break;
            } // ignore blank spaces and line feeds
            case '%':
            {
               if( cbIn < 2 )
               {
                  cbIn = 0; goto label_exit_loop_1;
               }
               BYTE hi = __NIBBLECHAR__[ ( (BYTE) *pIn ) ]; pIn++; cbIn--;
               BYTE lo = __NIBBLECHAR__[ ( (BYTE) *pIn ) ]; pIn++; cbIn--;
               if( hi && lo )
               {
                  p[ cb ] = (char) ( ( ( hi << 4 ) & 0xF0 ) | ( lo & 0x0F ) );
                  cb++;
               }
               break;
            }
            default:
            {
               p[ cb ] = ch; cb++; break;
            }
         }
      }
   label_exit_loop_1:;
      p[ cb ] = 0;
   }
   if( pcbOut )
   {
      pcbOut[ 0 ] = cb;
   }
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#define lw_( ch ) ( (char) _lower_ansi_char_table_[ (BYTE) (ch) ] )
#define lwtb_( ch , tb) ( tb ? ( (char) tb[ (BYTE) (ch) ] ) : ch)
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bStrWildCmp
            | syntax_: `BOOL bStrWildCmp( LPSTR pWild, LPSTR pStr )`
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bStrWildCmp
            | _kw_: bStrWildCmp, Function
   }}*/
/*{{|desc: Case-sensitive wildcard match of a zero-terminated string against a pattern where '*' matches any
      run of characters and '?' matches one character.
    | params:
    - `pWild` LPSTR - Wildcard pattern.
    - `pStr` LPSTR - String to test.

    Returns BOOL - TRUE when the whole string matches the pattern. }}*/
OT4XB_API BOOL bStrWildCmp( LPSTR pWild, LPSTR pStr )
{
   return bStrWildCmpWithTableEx( pWild, pStr, 0, 0, 0, 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bStrWildCmpEx
            | syntax_: `BOOL bStrWildCmpEx( LPSTR pWild, LPSTR pStr, DWORD flags, DWORD DWORD DWORD, DWORD DWORD DWORD )`
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bStrWildCmpEx
            | _kw_: bStrWildCmpEx, Function
   }}*/
/*{{|desc: Wildcard match with flags and no translation table. Same matching as bStrWildCmpWithTableEx()
      with a NULL table.
    | params:
    - `pWild` LPSTR - Wildcard pattern.
    - `pStr` LPSTR - String to test.
    - `flags` DWORD - Flag mask as in bStrWildCmpWithTableEx().
    - `DWORD` DWORD DWORD - Reserved. Ignored.
    - `DWORD` DWORD DWORD - Reserved. Ignored.

    Returns BOOL - TRUE when the whole string matches the pattern; the negation flag inverts the meaning. }}*/
OT4XB_API BOOL bStrWildCmpEx( LPSTR pWild, LPSTR pStr, DWORD flags, DWORD, DWORD )
{
   return bStrWildCmpWithTableEx( pWild, pStr, 0, flags, 0, 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bStrWildCmpWithTable
            | syntax_: `BOOL bStrWildCmpWithTable( LPSTR pWild, LPSTR pStr, LPBYTE tb )`
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bStrWildCmpWithTable
            | _kw_: bStrWildCmpWithTable, Function
   }}*/
/*{{|desc: Wildcard match that translates both pattern and string bytes through a 256-byte table before
      comparing, so a lower-case table gives a case-insensitive match.
    | params:
    - `pWild` LPSTR - Wildcard pattern. '*' matches any run of characters and '?' matches one character.
    - `pStr` LPSTR - String to test.
    - `tb` LPBYTE - 256-byte translation table applied to both sides. NULL compares raw bytes.

    Returns BOOL - TRUE when the whole string matches the pattern. }}*/
OT4XB_API BOOL bStrWildCmpWithTable( LPSTR pWild, LPSTR pStr, LPBYTE tb )
{
   return bStrWildCmpWithTableEx( pWild, pStr, tb, 0, 0, 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bStrWildCmpWithTableEx
            | syntax_: ```
                 BOOL bStrWildCmpWithTableEx( LPSTR pWild, LPSTR pStr, LPBYTE tb, DWORD flags, DWORD DWORD DWORD, DWORD DWORD DWORD )
              ```
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bStrWildCmpWithTableEx
            | _kw_: bStrWildCmpWithTableEx, Function
   }}*/
/*{{|desc: Wildcard match engine behind the bStrWildCmp() family and lStrWildCmpEx(). The pattern uses '*'
      for any run of characters and '?' for one character; when a translation table is given, both pattern
      and string bytes are translated before comparing.
    | params:
    - `pWild` LPSTR - Wildcard pattern.
    - `pStr` LPSTR - String to test.
    - `tb` LPBYTE - Optional 256-byte translation table applied to both sides. NULL compares raw bytes.
    - `flags` DWORD - Bit mask. 0x10 - ignore leading spaces of pStr. 0x20 - ignore trailing spaces of
      pStr. 0x40 - a '^' at the start of the pattern negates the result. 0x8000 - a '~' or a backtick at the start
      of the pattern is skipped; the caller gives those prefixes their meaning.
    - `DWORD` DWORD DWORD - Reserved. Ignored.
    - `DWORD` DWORD DWORD - Reserved. Ignored.

    Returns BOOL - TRUE when the whole string matches the pattern, FALSE otherwise; 0x40 inverts the
      result. }}*/
OT4XB_API BOOL bStrWildCmpWithTableEx( LPSTR pWild, LPSTR pStr, LPBYTE tb, DWORD flags, DWORD, DWORD )
{
   LPSTR cp = NULL;
   LPSTR mp = NULL;
   int   cb = -1;
   int   cbb = 0;
   BOOL  bTrue = TRUE;
   BOOL  bFalse = FALSE;


   if( ( flags & 0x40 ) && ( *pWild == '^' ) )
   {
      pWild++;
      bTrue = FALSE;
      bFalse = TRUE;
   }

   if( ( flags & 0x8000 ) && ( ( *pWild == '~' ) || ( *pWild == '`' ) ) )
   {
      pWild++;
   }


   if( flags & 0x10 )
   {
      while( *pStr == 32 )
      {
         pStr++; cb--;
      }
   }
   if( flags & 0x20 )
   {
      for( cb = _xstrlen( pStr ); cb && pStr[ cb - 1 ] == 32; cb-- );
   }

   while( ( *pStr ) && cb && ( *pWild != '*' ) )
   {
      if( ( lwtb_( *pWild, tb ) != lwtb_( *pStr, tb ) ) && ( *pWild != '?' ) )
      {
         return bFalse;
      }
      pWild++; pStr++; cb--;
   }
   while( *pStr && cb )
   {
      if( *pWild == '*' )
      {
         pWild++;
         if( !*pWild )
         {
            return bTrue;
         }
         mp = pWild;
         cp = pStr + 1;
         cbb = cb - 1;

      }
      else
      {
         if( ( lwtb_( *pWild, tb ) == lwtb_( *pStr, tb ) ) || ( *pWild == '?' ) )
         {
            pWild++; pStr++; cb--;
         }
         else
         {
            pWild = mp; pStr = cp++; cb = cbb--;
         }
      }
   }
   while( *pWild == '*' )
   {
      pWild++;
   }
   return ( (BOOL) !*pWild ? bTrue : bFalse );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bAnyStrWildCmpI
            | syntax_: `BOOL bAnyStrWildCmpI( TList * wild_list, LPSTR pStr )`
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bAnyStrWildCmpI
            | _kw_: bAnyStrWildCmpI, Function
   }}*/
/*{{|desc: Tests a string against every zero-terminated wildcard pattern held in a TList, comparing
      case-insensitively, until one matches.
    | params:
    - `wild_list` TList * - List whose items are pointers to wildcard patterns. Must not be NULL.
    - `pStr` LPSTR - String to test.

    Returns BOOL - TRUE at the first matching pattern; FALSE when none matches. }}*/
OT4XB_API BOOL bAnyStrWildCmpI( TList* wild_list, LPSTR pStr )
{
   UINT n;
   UINT nn = wild_list->Count();
   for( n = 0; n < nn; n++ )
   {
      if( bStrWildCmpWithTable( (LPSTR) wild_list->Get( n ), pStr, _lower_ansi_char_table_ ) )
      {
         return TRUE;
      }
   }
   return FALSE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bStrWildCmpI
            | syntax_: `BOOL bStrWildCmpI( LPSTR pWild, LPSTR pStr )`
            | category: string/match
            | header: ot4xb_c_exported.h
            | mangled-name: bStrWildCmpI
            | _kw_: bStrWildCmpI, Function
   }}*/
/*{{|desc: Case-insensitive wildcard match of a zero-terminated string against a pattern where '*' matches
      any run of characters and '?' matches one character.
    | params:
    - `pWild` LPSTR - Wildcard pattern.
    - `pStr` LPSTR - String to test.

    Returns BOOL - TRUE when the whole string matches the pattern. }}*/
OT4XB_API BOOL bStrWildCmpI( LPSTR pWild, LPSTR pStr )
{
   return bStrWildCmpWithTable( pWild, pStr, _lower_ansi_char_table_ );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ansi_capitalize
            | syntax_: `void ansi_capitalize( LPSTR p, int cb )`
            | category: string
            | header: ot4xb_c_exported.h
            | mangled-name: ansi_capitalize
            | _kw_: ansi_capitalize, Function
   }}*/
/*{{|desc: Capitalizes text in place: the first character of every word is converted to upper case and the
      rest to lower case using the Windows ANSI conversion. Any byte with value 32 or lower separates words.
    | params:
    - `p` LPSTR - Buffer modified in place. NULL does nothing.
    - `cb` int - Number of bytes to process, or a negative value to use the zero-terminated length.

    Returns void }}*/
OT4XB_API void ansi_capitalize( LPSTR p, int cb )
{
   if( !p )
   {
      return;
   }
   if( cb < 0 )
   {
      cb = (int) _xstrlen( p );
   }
   BOOL bf = TRUE;
   for( ; cb > 0; cb--, p++ )
   {
      if( ( (BYTE) *p ) > 32 )
      {
         if( bf )
         {
            CharUpperBuff( p, 1 ); bf = FALSE;
         }
         else
         {
            CharLowerBuff( p, 1 );
         }
      }
      else
      {
         bf = TRUE;
      }
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bIsNibble
            | syntax_: `BOOL bIsNibble( char ch, DWORD * pNibble, int nNibble )`
            | category: string/hex
            | header: ot4xb_c_exported.h
            | mangled-name: bIsNibble
            | _kw_: bIsNibble, Function
   }}*/
/*{{|desc: Tests whether a character is a hexadecimal digit and, when it is, stores its value shifted to a
      chosen nibble position.
    | params:
    - `ch` char - Character to test.
    - `pNibble` DWORD * - Optional. Receives the digit value shifted left nNibble * 4 bits. May be NULL.
    - `nNibble` int - Zero-based nibble position for the shift.

    Returns BOOL - TRUE when ch is a hexadecimal digit; FALSE otherwise, leaving pNibble untouched. }}*/
OT4XB_API BOOL bIsNibble( char ch, DWORD* pNibble, int nNibble )
{
   BYTE b = __NIBBLECHAR__[ (BYTE) ch ];
   DWORD dw = ( ( b & 0x0F ) << ( nNibble * 4 ) );
   if( !b )
   {
      return FALSE;
   }
   if( pNibble )
   {
      pNibble[ 0 ] = dw;
   }
   return TRUE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ansi_byte_to_utf8_urlenc
            | syntax_: `int ansi_byte_to_utf8_urlenc( BYTE ch, LPBYTE buffer, int nLevel )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ansi_byte_to_utf8_urlenc
            | _kw_: ansi_byte_to_utf8_urlenc, Function
   }}*/
/*{{|desc: Converts one ANSI (code page 1252) byte to UTF-8 and URL-escapes it according to nLevel, writing
      the result to a caller buffer. Letters and digits stay literal and a space becomes '+' below level 5.
      Control bytes, bytes above 126 and the characters '+' '%' '^' '&' backtick '{' '}' '[' ']' '"' '<' '>', the
      backslash and the vertical bar are always escaped; ':' '/' '?' and '#' only above level 1; above level
      4 everything except letters and digits is escaped. A negative level escapes only '%' and emits every
      other byte as raw UTF-8.
    | params:
    - `ch` BYTE - ANSI byte to convert.
    - `buffer` LPBYTE - Destination buffer with room for at least 12 bytes.
    - `nLevel` int - Encoding level as described above; 4 is the usual default.

    Returns int - Number of bytes written to buffer. }}*/
OT4XB_API int ansi_byte_to_utf8_urlenc( BYTE ch, LPBYTE buffer, int nLevel )
{
   BOOL b = FALSE;
   if( nLevel < 0 )
   {
      b = (BOOL) ( ch == '%' );
   }
   else
   {
      if( ( ch == 0x20 ) && ( nLevel < 5 ) )
      {
         buffer[ 0 ] = (BYTE) '+'; return 1;
      }
      if( isalnum( ch ) )
      {
         buffer[ 0 ] = ch; return 1;
      }
      b = ( ( ( ch < 33 ) || ( ch > 126 ) ) ? 1 : 0 );
      if( nLevel > 4 )
      {
         b = TRUE;
      }
      if( !b )
      {
         switch( ch )
         {
            case '+': case '%': case '^': case '&': case '`': case '{': case '}': case '|': case ']': case '[':
            case 0x22: case '<': case '>': case 0x5C:
            {
               b = TRUE; break;
            }
            case ':':  case '/': case '?': case '#':
            {
               b = (BOOL) ( nLevel > 1 ); break;
            }
            default:
            {
               break;
            }
         }
      }
   }

   BYTE wsz[ 8 ]; ZeroMemory( wsz, sizeof( wsz ) );
   int  wcb = MultiByteToWideChar( 1252, 0, (LPSTR) &ch, 1, (LPWSTR) wsz, 2 );
   BYTE usz[ 16 ]; ZeroMemory( usz, sizeof( usz ) );
   int  ucb = WideCharToMultiByte( CP_UTF8, 0, (LPWSTR) wsz, wcb, (LPSTR) usz, 16, 0, 0 );
   int n;
   if( b )
   {
      for( n = 0; n < ucb; n++ )
      {
         buffer[ 0 ] = (BYTE) '%';
         buffer[ 1 ] = __HEXNIBBLE__[ MSNIBBLE( usz[ n ] ) ];
         buffer[ 2 ] = __HEXNIBBLE__[ LSNIBBLE( usz[ n ] ) ];
         buffer = _mk_ptr_( LPBYTE, buffer, 3 );
      }
      return ( ucb * 3 );
   }
   for( n = 0; n < ucb; n++ )
   {
      buffer[ n ] = usz[ n ];
   }
   return ucb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_qp_decode
            | syntax_: `BOOL ot4xb_qp_decode( LPBYTE p, int cb, LPSTR p_out, int * pcb_out, DWORD dwFlags )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_qp_decode
            | _kw_: ot4xb_qp_decode, Function
   }}*/
/*{{|desc: Decodes quoted-printable data into a caller buffer. Without flag 0x8000 the work is delegated to
      the ATL QPDecode() function. With 0x8000, '=' followed by CRLF (a soft line break) is removed while
      hard CRLFs are preserved, and '=' followed by two uppercase hexadecimal digits becomes the encoded
      byte.
    | params:
    - `p` LPBYTE - Source data.
    - `cb` int - Source length in bytes.
    - `p_out` LPSTR - Destination buffer.
    - `pcb_out` int * - On entry the destination capacity in bytes; on return the decoded length.
    - `dwFlags` DWORD - Flags passed to QPDecode(), plus 0x8000 to select the CRLF-preserving decoder.

    Returns BOOL - TRUE on success; FALSE when a pointer is NULL, a length is 0, or the destination is too
      small. }}*/
OT4XB_API BOOL ot4xb_qp_decode( LPBYTE p, int cb, LPSTR p_out, int* pcb_out, DWORD dwFlags )
{
   if( !( dwFlags & 0x8000 ) )
   {
      // let the atl QPDecode() do the work
      return QPDecode( p, cb, p_out, pcb_out, dwFlags );
   }
   if( !( p && cb && p_out && pcb_out ) )
   {
      return FALSE;
   }

   if( cb > *pcb_out )
   {
      return FALSE;
   }

   int cbo = 0;
   for( ; cb > 0; cb--, p++ )
   {
      if( *p == (BYTE) '=' )
      {
         if( cb > 2 )
         {
            if( ( p[ 1 ] == 13 ) && ( p[ 2 ] == 10 ) )
            {
               cb -= 2;  p = _mk_ptr_( LPBYTE, p, 2 );
            }
            else
            {
               if( ( ( ( p[ 1 ] >= 'A' ) && ( p[ 1 ] <= 'F' ) ) || ( ( p[ 1 ] >= '0' ) && ( p[ 1 ] <= '9' ) ) ) &&
                   ( ( ( p[ 2 ] >= 'A' ) && ( p[ 2 ] <= 'F' ) ) || ( ( p[ 2 ] >= '0' ) && ( p[ 2 ] <= '9' ) ) ) )
               {
                  p_out[ cbo ] = ( chHex2Nibble( p[ 1 ] ) << 4 ) | chHex2Nibble( p[ 2 ] ); cbo++;
                  cb -= 2;  p = _mk_ptr_( LPBYTE, p, 2 );
               }
            }
         }
      }
      else
      {
         p_out[ cbo ] = (char) *p;
         cbo++;
      }
   }
   pcb_out[ 0 ] = cbo;
   return TRUE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_qp_decode_required_length
            | syntax_: `int ot4xb_qp_decode_required_length( int nSrcLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_qp_decode_required_length
            | _kw_: ot4xb_qp_decode_required_length, Function
   }}*/
/*{{|desc: Returns the destination size needed to decode quoted-printable data. Thin wrapper over the ATL
      QPDecodeGetRequiredLength() function.
    | params:
    - `nSrcLen` int - Source length in bytes.

    Returns int - Required destination size in bytes. }}*/
OT4XB_API int ot4xb_qp_decode_required_length( int nSrcLen )
{
   return QPDecodeGetRequiredLength( nSrcLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_base64_encode_required_length
            | syntax_: `int ot4xb_base64_encode_required_length( int nSrcLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_base64_encode_required_length
            | _kw_: ot4xb_base64_encode_required_length, Function
   }}*/
/*{{|desc: Returns the destination size needed to Base64-encode a buffer. Thin wrapper over the ATL
      Base64EncodeGetRequiredLength() function.
    | params:
    - `nSrcLen` int - Source length in bytes.

    Returns int - Required destination size in bytes. }}*/
OT4XB_API int ot4xb_base64_encode_required_length( int nSrcLen )
{
   return Base64EncodeGetRequiredLength( nSrcLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_base64_encode
            | syntax_: ```
                 BOOL ot4xb_base64_encode( LPBYTE pSrc, int nSrcLen, LPSTR szDest, int * pnDestLen, DWORD dwFlags )
              ```
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_base64_encode
            | _kw_: ot4xb_base64_encode, Function
   }}*/
/*{{|desc: Encodes binary data as Base64 text into a caller buffer. Thin wrapper over the ATL Base64Encode()
      function.
    | params:
    - `pSrc` LPBYTE - Source bytes.
    - `nSrcLen` int - Source length in bytes.
    - `szDest` LPSTR - Destination buffer.
    - `pnDestLen` int * - On entry the destination capacity in bytes; on return the encoded length.
    - `dwFlags` DWORD - ATL Base64 flags; 2 requests output without CRLF line breaks.

    Returns BOOL - TRUE on success. }}*/
OT4XB_API BOOL ot4xb_base64_encode( LPBYTE pSrc, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD dwFlags )
{
   return Base64Encode( pSrc, nSrcLen, szDest, pnDestLen, dwFlags );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_base64_decode_required_length
            | syntax_: `int ot4xb_base64_decode_required_length( int nSrcLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_base64_decode_required_length
            | _kw_: ot4xb_base64_decode_required_length, Function
   }}*/
/*{{|desc: Returns the destination size needed to decode Base64 text. Thin wrapper over the ATL
      Base64DecodeGetRequiredLength() function.
    | params:
    - `nSrcLen` int - Source length in bytes.

    Returns int - Required destination size in bytes. }}*/
OT4XB_API int ot4xb_base64_decode_required_length( int nSrcLen )
{
   return Base64DecodeGetRequiredLength( nSrcLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_base64_decode
            | syntax_: `BOOL ot4xb_base64_decode( LPSTR szSrc, int nSrcLen, BYTE * pbDest, int * pnDestLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_base64_decode
            | _kw_: ot4xb_base64_decode, Function
   }}*/
/*{{|desc: Decodes Base64 text into a caller buffer. Thin wrapper over the ATL Base64Decode() function.
    | params:
    - `szSrc` LPSTR - Base64 source text.
    - `nSrcLen` int - Source length in bytes.
    - `pbDest` BYTE * - Destination buffer.
    - `pnDestLen` int * - On entry the destination capacity in bytes; on return the decoded length.

    Returns BOOL - TRUE on success. }}*/
OT4XB_API BOOL ot4xb_base64_decode( LPSTR szSrc, int nSrcLen, BYTE* pbDest, int* pnDestLen )
{
   return Base64Decode( szSrc, nSrcLen, pbDest, pnDestLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_uu_decode_required_length
            | syntax_: `BOOL ot4xb_uu_decode_required_length( int nSrcLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_uu_decode_required_length
            | _kw_: ot4xb_uu_decode_required_length, Function
   }}*/
/*{{|desc: Returns the destination size needed to decode uuencoded data. Thin wrapper over the ATL
      UUDecodeGetRequiredLength() function.
    | params:
    - `nSrcLen` int - Source length in bytes.

    Returns BOOL - Required destination size in bytes, despite the BOOL declaration (BOOL is a 32-bit int). }}*/
OT4XB_API BOOL ot4xb_uu_decode_required_length( int nSrcLen )
{
   return UUDecodeGetRequiredLength( nSrcLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_uu_decode
            | syntax_: `BOOL ot4xb_uu_decode( BYTE * pbSrcData, int nSrcLen, BYTE * pbDest, int * pnDestLen )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_uu_decode
            | _kw_: ot4xb_uu_decode, Function
   }}*/
/*{{|desc: Decodes uuencoded data into a caller buffer. Thin wrapper over the ATL UUDecode() function.
    | params:
    - `pbSrcData` BYTE * - Source data.
    - `nSrcLen` int - Source length in bytes.
    - `pbDest` BYTE * - Destination buffer.
    - `pnDestLen` int * - On entry the destination capacity in bytes; on return the decoded length.

    Returns BOOL - TRUE on success. }}*/
OT4XB_API BOOL ot4xb_uu_decode( BYTE* pbSrcData, int nSrcLen, BYTE* pbDest, int* pnDestLen )
{
   return UUDecode( pbSrcData, nSrcLen, pbDest, pnDestLen );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: unescape_from_json
            | syntax_: `LPSTR unescape_from_json( LPSTR pIn, UINT * pcbOut )`
            | category: string/encoding
            | header: ot4xb_c_exported.h
            | mangled-name: unescape_from_json
            | _kw_: unescape_from_json, Function
   }}*/
/*{{|desc: Decodes a JSON string literal, surrounding double quotes included, into a newly allocated ANSI
      string. The standard JSON backslash escapes and \uXXXX sequences are decoded and the result is
      converted from UTF-8 to the ANSI code page.
    | params:
    - `pIn` LPSTR - Text holding the quoted literal. Blanks before the opening quote are accepted.
    - `pcbOut` UINT * - Optional. Receives the decoded length. May be NULL.

    Returns LPSTR - New buffer allocated with _xgrab(); release it with _xfree(). NULL when pIn is NULL or
      the literal is malformed. }}*/
OT4XB_API LPSTR unescape_from_json( LPSTR pIn, UINT* pcbOut )
{
   TZString z;
   LPSTR pOut = 0;
   UINT  cbOut = 0;
   if( pIn )
   {
      LPSTR p = pIn;
      int status = 0;
      for( ; *p && ( status == 0 ); p++ )
      {
         switch( *p )
         {
            case 0x09: case 0x10: case 0x13: case 0x20:
            {
               break;
            }
            case 0x22:
            {
               status = 1; break;
            }
            default:
            {
               status = -1; break;
            }
         }
      }
      if( status > 0 )
      {
         WORD w = 0;
         for( ; *p && ( status > 0 ); p++ )
         {
            if( status == 1 )
            {
               switch( *p )
               {
                  case 0x22:
                  {
                     status = 0; break;
                  }
                  case '\\':
                  {
                     status = 2; break;
                  }
                  case 0x09: case 0x10: case 0x13:
                  {
                     break;
                  } // ignore unencoded tabs or CRLFs
                  default:
                  {
                     z.AddChar( *p );
                     break;
                  }
               }
            }
            else if( status == 2 ) // \ found
            {
               switch( *p )
               {
                  case 'u':
                  {
                     w = 0; status = 3; break;
                  }
                  case '\\':
                  {
                     z.AddChar( *p ); status = 1; break;
                  }
                  case '/':
                  {
                     z.AddChar( *p ); status = 1; break;
                  }
                  case 0x22:
                  {
                     z.AddChar( *p ); status = 1; break;
                  }
                  case 'b':
                  {
                     z.AddChar( 0x08 ); status = 1; break;
                  }
                  case 't':
                  {
                     z.AddChar( 0x09 ); status = 1; break;
                  }
                  case 'n':
                  {
                     z.AddChar( 0x0A ); status = 1; break;
                  }
                  case 'f':
                  {
                     z.AddChar( 0x0C ); status = 1; break;
                  }
                  case 'r':
                  {
                     z.AddChar( 0x0D ); status = 1; break;
                  }
                  default:
                  {
                     status = -1;
                     break;
                  }
               }
            }
            else if( ( status > 2 ) && ( status < 7 ) ) // \u found  3456
            {
               BYTE nibble = chHex2Nibble( (BYTE) *p );
               if( nibble || ( *p == '0' ) )
               {
                  w = ( w << 4 ) | nibble;
                  status++;
                  if( status > 6 )
                  {
                     char sz[ 8 ]; ZeroMemory( sz, sizeof( sz ) );
                     WideCharToMultiByte( CP_UTF8, 0, (LPWSTR) &w, 1, sz, sizeof( sz ) - 1, 0, 0 );
                     z.Add( sz );
                     status = 1;
                  }
               }
               else
               {
                  status = -1;
               }
            }
            else
            {
               status = -1;
            }
         }
         if( status == 0 )
         {
            pOut = mb2mb( z.GetBuffer(), (int) z.len(), (int*) &cbOut, CP_UTF8, CP_ACP, 0, 0 );
         }
      }
   }
   if( pcbOut )
   {
      pcbOut[ 0 ] = cbOut;
   }
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
DWORD rfc2047_hash2codepage( DWORD dwcph )
{
   switch( dwcph )
   {
      case 0xDC3AD16D:
      {
         return    37;
      } // IBM037
      case 0xDB3379B1:
      {
         return   437;
      } // IBM437
      case 0x6FB8D5E6:
      {
         return   500;
      } // IBM500
      case 0x8FD34379:
      {
         return   708;
      } // ASMO-708
      case 0x1D907033:
      {
         return   720;
      } // DOS-720
      case 0xD975C7E8:
      {
         return   737;
      } // ibm737
      case 0x531763C0:
      {
         return   775;
      } // ibm775
      case 0x1A17B2F0:
      {
         return   850;
      } // ibm850
      case 0xF419D3DC:
      {
         return   852;
      } // ibm852
      case 0x6A7D467F:
      {
         return   855;
      } // IBM855
      case 0x84732753:
      {
         return   857;
      } // ibm857
      case 0xF384AB96:
      {
         return   858;
      } // IBM00858
      case 0x313AE133:
      {
         return   860;
      } // IBM860
      case 0x463DD1A5:
      {
         return   861;
      } // ibm861
      case 0x9CAE9326:
      {
         return   862;
      } // DOS-862
      case 0xA833B089:
      {
         return   863;
      } // IBM863
      case 0x3657252A:
      {
         return   864;
      } // IBM864
      case 0x415015BC:
      {
         return   865;
      } // IBM865
      case 0x1F51EAD8:
      {
         return   866;
      } // cp866
      case 0x48E65997:
      {
         return   869;
      } // ibm869
      case 0x2821D072:
      {
         return   870;
      } // IBM870
      case 0x4D542171:
      {
         return   874;
      } // windows-874
      case 0x9F438A23:
      {
         return   875;
      } // cp875
      case 0x4BE552A4:
      {
         return   932;
      } // shift_jis
      case 0x354487BD:
      {
         return   936;
      } // gb2312
      case 0x6FB9286F:
      {
         return   949;
      } // ks_c_5601-1987
      case 0x8B622978:
      {
         return   950;
      } // big5
      case 0xE9EA7059:
      {
         return  1026;
      } // IBM1026
      case 0xCC8FB19B:
      {
         return  1047;
      } // IBM01047
      case 0x53294E0F:
      {
         return  1140;
      } // IBM01140
      case 0x242E7E99:
      {
         return  1141;
      } // IBM01141
      case 0xBD272F23:
      {
         return  1142;
      } // IBM01142
      case 0xCA201FB5:
      {
         return  1143;
      } // IBM01143
      case 0x54448A16:
      {
         return  1144;
      } // IBM01144
      case 0x2343BA80:
      {
         return  1145;
      } // IBM01145
      case 0xBA4AEB3A:
      {
         return  1146;
      } // IBM01146
      case 0xCD4DDBAC:
      {
         return  1147;
      } // IBM01147
      case 0x5DF2C63D:
      {
         return  1148;
      } // IBM01148
      case 0x2AF5F6AB:
      {
         return  1149;
      } // IBM01149
      case 0xC1409499:
      {
         return  1200;
      } // utf-16
      case 0x665924FF:
      {
         return  1201;
      } // unicodeFFFE
      case 0xB14C768A:
      {
         return  1250;
      } // windows-1250
      case 0xC64B461C:
      {
         return  1251;
      } // windows-1251
      case 0x5F4217A6:
      {
         return  1252;
      } // windows-1252
      case 0x28452730:
      {
         return  1253;
      } // windows-1253
      case 0xB621B293:
      {
         return  1254;
      } // windows-1254
      case 0xC1268205:
      {
         return  1255;
      } // windows-1255
      case 0x582FD3BF:
      {
         return  1256;
      } // windows-1256
      case 0x2F28E329:
      {
         return  1257;
      } // windows-1257
      case 0xBF97FEB8:
      {
         return  1258;
      } // windows-1258
      case 0xEF7BBFAE:
      {
         return  1361;
      } // Johab
      case 0x046E6B37:
      {
         return 10000;
      } // macintosh
      case 0xFDA39FA1:
      {
         return 10001;
      } // x-mac-japanese
      case 0x7127DDCB:
      {
         return 10002;
      } // x-mac-chinesetrad
      case 0xAB037EF6:
      {
         return 10003;
      } // x-mac-korean
      case 0x636316E2:
      {
         return 10004;
      } // x-mac-arabic
      case 0x2E509B57:
      {
         return 10005;
      } // x-mac-hebrew
      case 0x4316E1CF:
      {
         return 10006;
      } // x-mac-greek
      case 0x37F31003:
      {
         return 10007;
      } // x-mac-cyrillic
      case 0x4AEC3292:
      {
         return 10008;
      } // x-mac-chinesesimp
      case 0x5BB68F18:
      {
         return 10010;
      } // x-mac-romanian
      case 0xBCFEABC1:
      {
         return 10017;
      } // x-mac-ukrainian
      case 0x4EA582DD:
      {
         return 10021;
      } // x-mac-thai
      case 0xCECB6F84:
      {
         return 10029;
      } // x-mac-ce
      case 0xB5C89EA8:
      {
         return 10079;
      } // x-mac-icelandic
      case 0xE765D5FD:
      {
         return 10081;
      } // x-mac-turkish
      case 0x9FC25553:
      {
         return 10082;
      } // x-mac-croatian
      case 0xB9DDEA84:
      {
         return 20000;
      } // x-Chinese_CNS
      case 0xFF449943:
      {
         return 20001;
      } // x-cp20001
      case 0xE39C8FCC:
      {
         return 20002;
      } // x_Chinese-Eten
      case 0x114AF86F:
      {
         return 20003;
      } // x-cp20003
      case 0x8F2E6DCC:
      {
         return 20004;
      } // x-cp20004
      case 0xF8295D5A:
      {
         return 20005;
      } // x-cp20005
      case 0x308B459A:
      {
         return 20105;
      } // x-IA5
      case 0x02C0ADAF:
      {
         return 20106;
      } // x-IA5-German
      case 0x54385AC2:
      {
         return 20107;
      } // x-IA5-Swedish
      case 0x2BE4476B:
      {
         return 20108;
      } // x-IA5-Norwegian
      case 0xF038B127:
      {
         return 20127;
      } // us-ascii
      case 0xAA9AEAAB:
      {
         return 20261;
      } // x-cp20261
      case 0xA4416299:
      {
         return 20269;
      } // x-cp20269
      case 0xBCBF041E:
      {
         return 20273;
      } // IBM273
      case 0xBBD2C007:
      {
         return 20277;
      } // IBM277
      case 0x2B6DDD96:
      {
         return 20278;
      } // IBM278
      case 0xA22E496B:
      {
         return 20280;
      } // IBM280
      case 0xA5438D72:
      {
         return 20284;
      } // IBM284
      case 0xD244BDE4:
      {
         return 20285;
      } // IBM285
      case 0xBB35782A:
      {
         return 20290;
      } // IBM290
      case 0x2551ED89:
      {
         return 20297;
      } // IBM297
      case 0x5C4CDD53:
      {
         return 20420;
      } // IBM420
      case 0xC5458CE9:
      {
         return 20423;
      } // IBM423
      case 0x5B21194A:
      {
         return 20424;
      } // IBM424
      case 0xBEF68E3F:
      {
         return 20833;
      } // x-EBCDIC-KoreanExtended
      case 0xD185E04D:
      {
         return 20838;
      } // IBM-Thai
      case 0x3AE4F8F8:
      {
         return 20866;
      } // koi8-r
      case 0x5F26E0E4:
      {
         return 20871;
      } // IBM871
      case 0xAFB9CCBD:
      {
         return 20880;
      } // IBM880
      case 0x16C8D80D:
      {
         return 20905;
      } // IBM905
      case 0xB4B11B4D:
      {
         return 20924;
      } // IBM00924
      case 0x0ED82FBA:
      {
         return 20932;
      } // EUC-JP
      case 0x45DC64AC:
      {
         return 20936;
      } // x-cp20936
      case 0x9A22EFFA:
      {
         return 20949;
      } // x-cp20949
      case 0x114FD69E:
      {
         return 21025;
      } // cp1025
      case 0xA4806D5B:
      {
         return 21866;
      } // koi8-u
      case 0x4434A849:
      {
         return 28591;
      } // iso-8859-1
      case 0xDD3DF9F3:
      {
         return 28592;
      } // iso-8859-2
      case 0xAA3AC965:
      {
         return 28593;
      } // iso-8859-3
      case 0x345E5CC6:
      {
         return 28594;
      } // iso-8859-4
      case 0x43596C50:
      {
         return 28595;
      } // iso-8859-5
      case 0xDA503DEA:
      {
         return 28596;
      } // iso-8859-6
      case 0xAD570D7C:
      {
         return 28597;
      } // iso-8859-7
      case 0x3DE810ED:
      {
         return 28598;
      } // iso-8859-8
      case 0x4AEF207B:
      {
         return 28599;
      } // iso-8859-9
      case 0x62964307:
      {
         return 28603;
      } // iso-8859-13
      case 0x8BF5E632:
      {
         return 28605;
      } // iso-8859-15
      case 0x4AC13074:
      {
         return 29001;
      } // x-Europa
      case 0xA3FA31C1:
      {
         return 38598;
      } // iso-8859-8-i
      case 0xF90E5180:
      {
         return 50220;
      } // iso-2022-jp
      case 0x4A670F2B:
      {
         return 50221;
      } // csISO2022JP
   //case 0xF90E5180 : { return 50222; } // iso-2022-jp
      case 0x0E1B01ED:
      {
         return 50225;
      } // iso-2022-kr
      case 0x95B5568A:
      {
         return 50227;
      } // x-cp50227
   //case 0x0ED82FBA : { return 51932; } // euc-jp
      case 0x2515A990:
      {
         return 51936;
      } // EUC-CN
      case 0xF9CD7FD7:
      {
         return 51949;
      } // euc-kr
      case 0x66BD1860:
      {
         return 52936;
      } // hz-gb-2312
      case 0xC946F230:
      {
         return 54936;
      } // GB18030
      case 0x373E874E:
      {
         return 57002;
      } // x-iscii-de
      case 0x616420C8:
      {
         return 57003;
      } // x-iscii-be
      case 0x7A915106:
      {
         return 57004;
      } // x-iscii-ta
      case 0x7DFC951F:
      {
         return 57005;
      } // x-iscii-te
      case 0xBE9DC65A:
      {
         return 57006;
      } // x-iscii-as
      case 0x5719DB42:
      {
         return 57007;
      } // x-iscii-or
      case 0xB7CB5F98:
      {
         return 57008;
      } // x-iscii-ka
      case 0xE191F81E:
      {
         return 57009;
      } // x-iscii-ma
      case 0x01A4C4E9:
      {
         return 57010;
      } // x-iscii-gu
      case 0x1EFD9402:
      {
         return 57011;
      } // x-iscii-pa
      case 0xC780E71B:
      {
         return 65000;
      } // utf-7
      case 0x573FFA8A:
      {
         return 65001;
      } // utf-8



   }
   return (DWORD) 0;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: rfc2047decode
            | syntax_: `LPSTR rfc2047decode( LPSTR pIn, UINT * pcbOut, DWORD nOutCodePage, DWORD nBlockSize )`
            | header: ot4xb_c_exported.h
            | category: string/encoding
            | mangled-name: rfc2047decode
            | _kw_: rfc2047decode, Function
   }}*/
/*{{|desc: Decodes RFC 2047 encoded words, the =?charset?B?...?= and =?charset?Q?...?= forms used in e-mail
      headers. Each encoded word is Base64- or quoted-printable-decoded and converted from its character set
      to the requested output code page; anything that fails to decode is copied unchanged.
    | params:
    - `pIn` LPSTR - Zero-terminated header text.
    - `pcbOut` UINT * - Optional. Receives the decoded length. May be NULL.
    - `nOutCodePage` DWORD - Windows code page for the output text.
    - `nBlockSize` DWORD - Working buffer block size in bytes, clamped between 4096 and 0x100000.

    Returns LPSTR - New zero-terminated buffer allocated with _xgrab(); release it with _xfree(). NULL when
      pIn is NULL. }}*/
extern "C" OT4XB_API LPSTR rfc2047decode( LPSTR pIn, UINT* pcbOut, DWORD nOutCodePage, DWORD nBlockSize )
{
   LPSTR pOut = 0;
   UINT  cbOut = 0;
   if( nBlockSize < 4096 )
   {
      nBlockSize = 4096;
   }
   if( nBlockSize > 0x100000 )
   {
      nBlockSize = 0x100000;
   }


   if( pIn )
   {
      xstream_t z( nBlockSize, nBlockSize );
      LPSTR p = pIn;
      LPSTR p1 = 0;
      DWORD dwcph = 0;
      DWORD dwcp = 0;
      for( ; *p; p++ )
      {
         if( p1 )
         {
            if( *p == '?' )
            {
               dwcp = rfc2047_hash2codepage( dwcph );
               if( dwcp && ( p[ 1 ] == 'Q' ) || ( p[ 1 ] == 'q' ) || ( p[ 1 ] == 'B' ) || ( p[ 1 ] == 'b' ) )
               {
                  if( p[ 2 ] == '?' )
                  {
                     LPSTR ps = _mk_ptr_( LPSTR, p, 3 );
                     DWORD cbs = 0;
                     for( ; ps[ cbs ] && ( ps[ cbs ] == '?' ? ps[ cbs + 1 ] != '=' : 1 ); cbs++ );
                     if( ps[ cbs ] )
                     {
                        DWORD offset = z._offset_len_();
                        if( ( p[ 1 ] == 'Q' ) || ( p[ 1 ] == 'q' ) )
                        {
                           z.append_decode_qp( ps, (int) cbs, 0 );
                        }
                        else
                        {
                           z.append_decode_base64( ps, (int) cbs );
                        }
                        int cbd = 0;
                        LPSTR pd = mb2mb( (LPSTR) z._offset_ptr_( offset ), (int) z._offset_len_( offset ), &cbd, dwcp, nOutCodePage, 0, 0 );
                        if( pd )
                        {
                           z._truncate_buffer_( offset );
                           z.append_buffer( (void*) pd, (DWORD) cbd );
                           _xfree( (void*) pd );
                        }
                        cbd = 0; pd = 0;
                        p = _mk_ptr_( LPSTR, ps, cbs + 1 );
                        p1 = 0;
                        goto LabelEndLoop;
                     }
                  }
               }
               // if anything fail just add the string without decode
               p = p1; p1 = 0;
               for( ; *p && ( *p == '?' ? p[ 1 ] != '=' : 1 ); p++ )
               {
                  z.append_BYTE( (BYTE) *p );
               }
               if( *p && ( *p == '?' ? p[ 1 ] == '=' : 0 ) )
               {
                  z.append_BYTE( (BYTE) *p );
                  p++;
                  z.append_BYTE( (BYTE) *p );
               }
               goto LabelEndLoop;
            }
            else
            {
               dwcph = dwCrc32Lower( dwcph, (LPBYTE) p, 1 );
            }
         }
         else
         {
            if( *p == '=' )
            {
               if( p[ 1 ] == '?' )
               {
                  p1 = p;
                  p++;
                  dwcph = 0;
                  goto LabelEndLoop;
               }
            }
            z.append_BYTE( (BYTE) *p );
            goto LabelEndLoop;
         }
      LabelEndLoop:;
      }
      if( p1 )
      {
         z.append_buffer( (void*) p1, (DWORD) -1 );
      }
      z.ansi_ZSafe();
      pOut = (LPSTR) z.Detach( &cbOut );
   }
   if( pcbOut )
   {
      pcbOut[ 0 ] = cbOut;
   }
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------
// flags & 1 = insert CRLF every 76 chars
// split_data_uri( str , @header , flags ) -> body
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: split_data_uri
            | syntax_: `split_data_uri( cDataUri, @cHeader [, nFlags] )`
            | category: string/encoding
            | _kw_: split_data_uri, Function
   }}*/
/*{{|desc: Splits a data URI into its header and payload parts.
    | params:
    - `cDataUri` Character - Data URI text. The first comma separates the header from the body.
    - `cHeader` Character by reference - Receives the text before the first comma, without the comma.
      Receives an empty string if no comma is found.
    - `nFlags` Numeric - Optional bit mask. Combine flags with bitwise OR, for example with nOr( flag1,
      ..., flagX ). 0x0001 - insert CRLF after each 76 body characters.

    Returns Character - Body text after the first comma, optionally wrapped at 76 characters.

    |note: This function only splits and optionally wraps the URI body. It does not decode base64 or
      percent-encoded data. }}*/
_XPP_REG_FUN_( SPLIT_DATA_URI )
{
   TXppParamList xpp( pl, 3 );
   DWORD cb = 0;
   LPSTR p = xpp[ 1 ]->LockStr( &cb );
   DWORD pos = 0;
   TZString str;
   DWORD flags = xpp[ 3 ]->GetDWord();
   for( ; pos < cb && ( !( p[ pos ] == ',' ) ); pos++ );
   if( pos < cb && ( p[ pos ] == ',' ) )
   {
      xpp[ 2 ]->PutStrLen( p, pos );
   }
   else
   {
      xpp[ 2 ]->PutStr( "" );
   }
   pos++;
   while( pos < cb && pos )
   {
      DWORD n;
      for( n = 0; pos < cb && n < 76; pos++, n++ )
      {
         str.AddChar( p[ pos ] );
      }
      if( flags & 1 )
      {
         str.AddChar( 13 );
         str.AddChar( 10 );
      }
   }
   xpp[ 0 ]->PutStrLen( str.GetBuffer(), str.len() );

}
/*{{end-function}}*/
// -------------------------------------------------------------------------------------------------------------------------------------
// __b64enc( cStr, nFlags )
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __b64enc
            | syntax_: `__b64enc( cData [, nFlags] )`
            | category: string/encoding
            | _kw_: __b64enc, Function
   }}*/
/*{{|desc: Encodes a binary string as Base64 text.
    | params:
    - `cData` Character - Binary string to encode.
    - `nFlags` Numeric - Optional flags passed to the underlying ATL Base64Encode() function. Combine flags
      with bitwise OR, for example with nOr( flag1, ..., flagX ). A commonly used value is 2, which requests
      output without CRLF line breaks.

    Returns Character - Base64 encoded text, or an empty string if the source is empty or encoding fails.

    |note: This is a thin wrapper over the underlying ATL Base64 encoder. }}*/
_XPP_REG_FUN_( __B64ENC )
{
   TXppParamList xpp( pl, 2 );
   DWORD cb_source = 0;
   LPSTR p_source = xpp[ 1 ]->LockStr( &cb_source );
   DWORD cb_result = 0;
   if( p_source && ( (int) cb_source ) > 0 )
   {
      int cb = ot4xb_base64_encode_required_length( (int) cb_source );
      if( cb > 0 )
      {
         cb = cb + 16;
         LPSTR buffer = (LPSTR) _xgrab( cb + 1 );
         if( ot4xb_base64_encode( (LPBYTE) p_source, (int) cb_source, buffer, &cb, xpp[ 2 ]->GetDWord() ) )
         {
            cb_result = (DWORD) cb;
            xpp[ 0 ]->PutStrLen( buffer, cb_result );
         }
         _xfree( (void*) buffer );
         buffer = 0;
      }
   }
   if( !cb_result )
   {
      xpp[ 0 ]->PutStr( "" );
   }
}
/*{{end-function}}*/
// -------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __b64dec
            | syntax_: `__b64dec( cBase64 )`
            | category: string/encoding
            | _kw_: __b64dec, Function
   }}*/
/*{{|desc: Decodes Base64 text into its binary string representation.
    | params:
    - `cBase64` Character - Base64 text to decode.

    Returns Character - Decoded binary string, or an empty string if the source is empty or decoding fails.

    |note: This is a thin wrapper over the underlying ATL Base64 decoder. }}*/
_XPP_REG_FUN_( __B64DEC )
{

   TXppParamList xpp( pl, 2 );
   DWORD cb_source = 0;
   LPSTR p_source = xpp[ 1 ]->LockStr( &cb_source );
   DWORD cb_result = 0;
   if( p_source && ( (int) cb_source ) > 0 )
   {
      int cb = ot4xb_base64_decode_required_length( (int) cb_source );
      if( cb > 0 )
      {
         LPSTR buffer = (LPSTR) _xgrab( cb + 1 );
         if( ot4xb_base64_decode( p_source, (int) cb_source, (LPBYTE) buffer, &cb ) )
         {
            cb_result = (DWORD) cb;
            xpp[ 0 ]->PutStrLen( buffer, cb_result );
         }
         _xfree( (void*) buffer );
         buffer = 0;
      }
   }
   if( !cb_result )
   {
      xpp[ 0 ]->PutStr( "" );
   }
}
/*{{end-function}}*/
// -------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __aJoin
            | syntax_: `__aJoin( aItems [, cDelimiter] [, nFlags] )`
            | category: string
            | _kw_: __aJoin, Function
   }}*/
/*{{|desc: Joins the character items of an array into one string using a literal delimiter. It is the inverse
      operation normally paired with Tokenize().
    | params:
    - `aItems` Array - Array whose character items are joined.
    - `cDelimiter` Character - Delimiter inserted between joined items. If omitted or not character, ',' is
      used.
    - `nFlags` Numeric - Optional bit mask. 0x00000001 - includes empty strings after processing.
      0x00000002 - wraps each item in single quotes. 0x00000004 - wraps each item in double quotes. 0x00000010 -
      trims leading whitespace. 0x00000020 - trims trailing whitespace. 0x00000400 - converts numeric items to
      integer strings. 0x01000000 - removes bytes not present in the internal safe map before joining.
      0x00100000 - initializes that safe map with digits '0' to '9'.

    Returns Returns the joined string. Non-character items are ignored unless 0x00000400 is set for numeric
      items. Empty strings are skipped unless 0x00000001 is set. No delimiter is appended after the last joined
      item.

    |note: The delimiter is inserted literally. Quotes added by the quote flags are not escaped and item
      contents are not parsed. }}*/
_XPP_REG_FUN_( __AJOIN )
{
   TXppParamList xpp( pl, 3 );
   DWORD flags = xpp[ 3 ]->GetDWord();
   BYTE table_bytes[ 256 ] = { 0 };
   BYTE* map = 0;
   TZString s( 1024 );

   if( flags & 0x01000000 )
   {
      map = table_bytes;
      if( flags & 0x00100000 ) // 0 to 9
      {
         _bcopy( _mk_ptr_( LPBYTE, map, ( (BYTE) '0' ) ), (LPBYTE) "0123456789", 10 );
      }
   }

   if( xpp[ 1 ]->CheckType( XPP_ARRAY ) )
   {
      ULONG item_count = xpp[ 1 ]->con_size();
      if( item_count )
      {
         char default_delimiter[ ] = ",";
         LPSTR delimiter = ( xpp[ 2 ]->CheckType( XPP_CHARACTER ) ? xpp[ 2 ]->LockStr() : default_delimiter );
         ContainerHandle con = _conNew( NULLCONTAINER );
         DWORD dw = 0;
         DWORD tmp_cb = 1024;
         void* tmp_buffer = _xgrab( tmp_cb +1);
         if( tmp_buffer )
         {
            for( ULONG item_pos = 1; item_pos <= item_count; item_pos++ )
            {
               if( _conArrayGet( xpp[ 1 ]->con(), con, item_pos, 0 ) )
               {
                  DWORD t = 0;
                  LPSTR p = 0;
                  DWORD cb = 0;
                  _conType( con, &t );
                  switch( t & 0xFF )
                  {
                     case XPP_NUMERIC:
                     {
                        if( flags & 0x400 )
                        {
                           LONG n; _conGetNL( con, &n );
                           p = (LPSTR) tmp_buffer;
                           cb = wsprintf( p, "%i", n );
                        }
                        break;
                     }
                     case XPP_CHARACTER:
                     {
                        LPSTR item_p = 0;
                        DWORD item_cb = 0;
                        if( _conRLockC( con, &item_p, &item_cb ) == 0 )
                        {
                           if( item_cb >= tmp_cb )
                           {
                              _xfree( tmp_buffer );
                              tmp_cb = ( item_cb | 0x1FF ) + 1;
                              tmp_buffer = _xgrab( tmp_cb );
                              if( tmp_buffer == nullptr )
                              {
                                 tmp_cb = 0;
                              }
                           }
                           if( tmp_buffer )
                           {
                              _bcopy( (LPBYTE) tmp_buffer, (LPBYTE) item_p, item_cb );
                              p = (LPSTR) tmp_buffer;
                              cb = item_cb;
                              p[ cb ] = 0;
                           }

                           _conUnlockC( con );
                        }
                        break;
                     }
                  }
                  if( p )
                  {
                     if( flags & 0x01000000 )
                     {
                        cb = (DWORD) ByteMapTable_RemoveUnsafe( map, (LPBYTE) p, (int) cb );
                     }
                     if( flags & 0x10 )
                     {
                        cb = ByteMapTable_LTrimEx( 0, (LPBYTE) p, cb );
                     }
                     if( flags & 0x20 )
                     {
                        cb = ByteMapTable_RTrimEx( 0, (LPBYTE) p, cb );
                     }

                     BOOL validate = cb || flags & 1;
                     if( validate )
                     {
                        if( dw )
                        {
                           s += delimiter;
                        }
                        if( flags & 4 ) { s += "\""; }
                        if( flags & 2 ) { s += "'"; }

                        s.AddStrCb( p, cb, 0, cb, 0 );

                        if( flags & 2 ) { s += "'"; }
                        if( flags & 4 ) { s += "\""; }
                        dw++;
                     }
                  }
               }
            }
         }
         _conRelease( con );
         con = NULLCONTAINER;
         if( tmp_buffer )
         {
            _xfree( tmp_buffer );
            tmp_buffer = 0;
         }
      }
   }
   xpp[ 0 ]->PutStr( s.GetBuffer() );
}
/*{{end-function}}*/