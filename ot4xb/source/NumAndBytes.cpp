//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: dwFix
            | syntax_: `dwFix( nHighWord, nLowWord )`
            | category: numeric/bit
            | _kw_: dwFix, Function
   }}*/
/*{{|desc: Builds a 32-bit value from a high word and a low word.
    | params:
    - `nHighWord` numeric - Value placed in the high 16 bits.
    - `nLowWord` numeric - Value masked to 16 bits and placed in the low word.

    Returns numeric - Combined 32-bit value. }}*/
XPPRET XPPENTRY DWFIX(XppParamList pl)
{
    _retnl(pl,((_parLong(pl,1) << 16) | (_parLong(pl,2)  & 0xFFFF)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: dwMinus
            | syntax_: `dwMinus( @nValue )`
            | category: numeric/bit
            | _kw_: dwMinus, Function
   }}*/
/*{{|desc: Returns the two's-complement negation of a 32-bit numeric value.
    | params:
    - `nValue` numeric - Value to negate. The parameter is also updated with the result.

    Returns numeric - Negated 32-bit value. }}*/
XPPRET XPPENTRY DWMINUS(XppParamList pl)
{
   LONG nResult = (0 - _parLong(pl,1));
   _stornl(nResult,pl,1,0);
   _retnl(pl,nResult);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: unsigned8
            | syntax_: `unsigned8( @nValue )`
            | category: numeric/bit
            | _kw_: unsigned8, Function
   }}*/
/*{{|desc: Converts a numeric value to its unsigned 8-bit representation.
    | params:
    - `nValue` numeric - Value masked with 0xFF. The parameter is also updated with the result.

    Returns numeric - Value in the range 0..255. }}*/
XPPRET XPPENTRY UNSIGNED8( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFF,pl,1,0);
   _retnl(pl,n & 0xFF);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: unsigned16
            | syntax_: `unsigned16( @nValue )`
            | category: numeric/bit
            | _kw_: unsigned16, Function
   }}*/
/*{{|desc: Converts a numeric value to its unsigned 16-bit representation.
    | params:
    - `nValue` numeric - Value masked with 0xFFFF. The parameter is also updated with the result.

    Returns numeric - Value in the range 0..65535. }}*/
XPPRET XPPENTRY UNSIGNED16( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFFFF,pl,1,0);
   _retnl(pl,n & 0xFFFF);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: unsigned32
            | syntax_: `unsigned32( @nValue )`
            | category: numeric/bit
            | _kw_: unsigned32, Function
   }}*/
/*{{|desc: Recovers the unsigned 32-bit value of a LONG that holds an unsigned bit pattern. Xbase++ has only
      LONG (signed 32-bit), no unsigned DWORD, so a value coming from an integer/bitwise operation that is
      logically unsigned arrives as a signed LONG - negative when bit 31 is set (e.g. 0xFFFFFFFF reads as -1).
      This returns the true unsigned magnitude, as a double when it exceeds the signed LONG range.
    | params:
    - `nValue` numeric - Value (normally an integer/LONG) interpreted as an unsigned 32-bit value. The
      parameter is also updated with the result.

    Returns numeric - A LONG when representable as signed 32-bit, otherwise a double.

    |note: The intended input is an integer (LONG). A DOUBLE-typed argument is returned unchanged - a double
      means it was already converted earlier, so it already holds the unsigned value. Use unsigned32 (or %u
      via cPrintf) for DISPLAY only; for comparison or storage keep the raw LONG - its bit pattern compares
      exactly, whereas the converted double form is easier to mismatch (double-vs-LONG, or mixed routes).

    |example: A CRC32 (or any 32-bit hash) with the high bit set reads as a negative LONG in Xbase++;
      unsigned32( nCrc ) - or cPrintf( "%u", nCrc ) - yields the positive value that external tools report. }}*/
XPPRET XPPENTRY UNSIGNED32( XppParamList pl )
{
   if( _partype(pl,1) & _xpp_DOUBLE )
   {
      double nd = _parnd(pl,1);
      _stornd(nd,pl,1,0);
      _retnd(pl,nd);
   }
   else
   {
      DWORD dw = (DWORD) _parLong(pl,1);
      if( dw & 0x80000000 )
      {
         double nd = (double) dw;
         _stornd(nd,pl,1,0);
         _retnd(pl, nd );
      }
      else _retnl(pl,dw);  // no change
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: extendSign8
            | syntax_: `extendSign8( @nValue )`
            | category: numeric/bit
            | _kw_: extendSign8, Function
   }}*/
/*{{|desc: Sign-extends an 8-bit value to a 32-bit signed value.
    | params:
    - `nValue` numeric - Low byte to sign-extend. The parameter is also updated with the result.

    Returns numeric - 32-bit signed value produced from the low 8 bits. }}*/
XPPRET XPPENTRY EXTENDSIGN8( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFF);
   if( n & 0x80) n |= 0xFFFFFF00;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: extendSign16
            | syntax_: `extendSign16( @nValue )`
            | category: numeric/bit
            | _kw_: extendSign16, Function
   }}*/
/*{{|desc: Sign-extends a 16-bit value to a 32-bit signed value.
    | params:
    - `nValue` numeric - Low word to sign-extend. The parameter is also updated with the result.

    Returns numeric - 32-bit signed value produced from the low 16 bits. }}*/
XPPRET XPPENTRY EXTENDSIGN16( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFFFF);
   if( n & 0x8000) n |= 0xFFFF0000;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: long2Double
            | syntax_: `long2Double( @nValue )`
            | category: numeric/conversion
            | _kw_: long2Double, Function
   }}*/
/*{{|desc: Converts a numeric value to Xbase++ double representation.
    | params:
    - `nValue` numeric - Value to convert. The parameter is also updated with the double value.

    Returns numeric - The value returned as a double. }}*/
XPPRET XPPENTRY LONG2DOUBLE( XppParamList pl )
{
   double nd = ( ( _partype(pl,1) & _xpp_DOUBLE ) ? _parnd(pl,1) : (double) _parLong(pl,1) );
   _stornd(nd,pl,1,0);
   _retnd(pl,nd);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: double2Long
            | syntax_: `double2Long( @nValue )`
            | category: numeric/conversion
            | _kw_: double2Long, Function
   }}*/
/*{{|desc: Converts a numeric value to Xbase++ LONG representation.
    | params:
    - `nValue` numeric - Value to convert. The parameter is also updated with the LONG value.

    Returns numeric - The value returned as a LONG. }}*/
XPPRET XPPENTRY DOUBLE2LONG( XppParamList pl )
{
   LONG n =  _parLong(pl,1);
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: LOWORD
            | syntax_: `LOWORD( nValue )`
            | category: numeric/winapi-macro
            | _kw_: LOWORD, Function
   }}*/
/*{{|desc: Returns the low-order word from a 32-bit value.
    | params:
    - `nValue` numeric - 32-bit value.

    Returns numeric - Low 16 bits. }}*/
XPPRET XPPENTRY wapimc_LOWORD(XppParamList pl){_retnl(pl,( _parLong(pl,1) & 0xFFFF ) );}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: HIWORD
            | syntax_: `HIWORD( nValue )`
            | category: numeric/winapi-macro
            | _kw_: HIWORD, Function
   }}*/
/*{{|desc: Returns the high-order word from a 32-bit value.
    | params:
    - `nValue` numeric - 32-bit value.

    Returns numeric - High 16 bits. }}*/
XPPRET XPPENTRY wapimc_HIWORD(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 16) & 0xFFFF ) );}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: LOBYTE
            | syntax_: `LOBYTE( nValue )`
            | category: numeric/winapi-macro
            | _kw_: LOBYTE, Function
   }}*/
/*{{|desc: Returns the low-order byte from a 16-bit or 32-bit value.
    | params:
    - `nValue` numeric - Numeric value.

    Returns numeric - Low 8 bits. }}*/
XPPRET XPPENTRY wapimc_LOBYTE(XppParamList pl){ _retnl(pl,( _parLong(pl,1) & 0xFF ) );}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: HIBYTE
            | syntax_: `HIBYTE( nValue )`
            | category: numeric/winapi-macro
            | _kw_: HIBYTE, Function
   }}*/
/*{{|desc: Returns the high-order byte from a 16-bit value.
    | params:
    - `nValue` numeric - Numeric value.

    Returns numeric - Bits 8..15. }}*/
XPPRET XPPENTRY wapimc_HIBYTE(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 8) & 0xFF ) );}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKEWORD
            | syntax_: `MAKEWORD( nLowByte, nHighByte )`
            | category: numeric/winapi-macro
            | _kw_: MAKEWORD, Function
   }}*/
/*{{|desc: Builds a 16-bit word from low and high byte values.
    | params:
    - `nLowByte` numeric - Low byte.
    - `nHighByte` numeric - High byte.

    Returns numeric - Combined word. }}*/
XPPRET XPPENTRY wapimc_MAKEWORD(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFF;
   LONG hi = _parLong(pl,2) & 0xFF;
	_retnl(pl, MAKEWORD(lo, hi));//  (lo | (hi << 8)) );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKELONG
            | syntax_: `MAKELONG( nLowWord, nHighWord )`
            | category: numeric/winapi-macro
            | _kw_: MAKELONG, Function
   }}*/
/*{{|desc: Builds a 32-bit value from low and high word values.
    | params:
    - `nLowWord` numeric - Low word.
    - `nHighWord` numeric - High word.

    Returns numeric - Combined 32-bit value. }}*/
XPPRET XPPENTRY wapimc_MAKELONG(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG( lo , hi));
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKELANGID
            | syntax_: `MAKELANGID( nPrimaryLanguage, nSubLanguage )`
            | category: numeric/winapi-macro
            | _kw_: MAKELANGID, Function
   }}*/
/*{{|desc: Builds a Windows language identifier from primary language and sublanguage values.
    | params:
    - `nPrimaryLanguage` numeric - Primary language identifier.
    - `nSubLanguage` numeric - Sublanguage identifier.

    Returns numeric - Windows LANGID value. }}*/
XPPRET XPPENTRY wapimc_MAKELANGID(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG(MAKELANGID( lo , hi), 0));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKELPARAM
            | syntax_: `MAKELPARAM( nLowWord, nHighWord )`
            | category: numeric/winapi-macro
            | _kw_: MAKELPARAM, Function
   }}*/
/*{{|desc: Builds an LPARAM-style 32-bit value from low and high word values.
    | params:
    - `nLowWord` numeric - Low word.
    - `nHighWord` numeric - High word.

    Returns numeric - Combined LPARAM-style value. }}*/
XPPRET XPPENTRY wapimc_MAKELPARAM(XppParamList pl){ wapimc_MAKELONG(pl); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKELRESULT
            | syntax_: `MAKELRESULT( nLowWord, nHighWord )`
            | category: numeric/winapi-macro
            | _kw_: MAKELRESULT, Function
   }}*/
/*{{|desc: Builds an LRESULT-style 32-bit value from low and high word values.
    | params:
    - `nLowWord` numeric - Low word.
    - `nHighWord` numeric - High word.

    Returns numeric - Combined LRESULT-style value. }}*/
XPPRET XPPENTRY wapimc_MAKELRESULT(XppParamList pl){ wapimc_MAKELONG(pl); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GET_X_LPARAM
            | syntax_: `GET_X_LPARAM( nLParam )`
            | category: numeric/winapi-macro
            | _kw_: GET_X_LPARAM, Function
   }}*/
/*{{|desc: Returns the low word of an LPARAM value, normally used as the X coordinate.
    | params:
    - `nLParam` numeric - LPARAM value.

    Returns numeric - Low word of the LPARAM. }}*/
XPPRET XPPENTRY wapimc_GET_X_LPARAM(XppParamList pl){ wapimc_LOWORD(pl); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GET_Y_LPARAM
            | syntax_: `GET_Y_LPARAM( nLParam )`
            | category: numeric/winapi-macro
            | _kw_: GET_Y_LPARAM, Function
   }}*/
/*{{|desc: Returns the high word of an LPARAM value, normally used as the Y coordinate.
    | params:
    - `nLParam` numeric - LPARAM value.

    Returns numeric - High word of the LPARAM. }}*/
XPPRET XPPENTRY wapimc_GET_Y_LPARAM(XppParamList pl){ wapimc_HIWORD(pl); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: dwByteRev
            | syntax_: `dwByteRev( @nValue )`
            | category: numeric/byte-order
            | _kw_: dwByteRev, Function
   }}*/
/*{{|desc: Reverses the byte order of a 32-bit value.
    | params:
    - `nValue` numeric - 32-bit value whose bytes are reversed. The parameter is also updated with the
      result.

    Returns numeric - Value with byte order 0-1-2-3 changed to 3-2-1-0. }}*/
XPPRET XPPENTRY DWBYTEREV(XppParamList pl)
{
   BYTE ch;
   union{LONG n;BYTE ch[4];}u;
   u.n = _parLong(pl,1,0);
   ch = u.ch[0]; u.ch[0] = u.ch[3]; u.ch[3] = ch;
   ch = u.ch[1]; u.ch[1] = u.ch[2]; u.ch[2] = ch;
   _stornl(u.n,pl,1,0);
   _retnl(pl,u.n);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: whlByteRev
            | syntax_: `whlByteRev( @nValue )`
            | category: numeric/byte-order
            | _kw_: whlByteRev, Function
   }}*/
/*{{|desc: Swaps bytes inside each 16-bit word of a 32-bit value.
    | params:
    - `nValue` numeric - 32-bit value whose word-local byte order is reversed. The parameter is also
      updated with the result.

    Returns numeric - Value with byte order 0-1-2-3 changed to 1-0-3-2. }}*/
XPPRET XPPENTRY WHLBYTEREV(XppParamList pl)
{
   BYTE ch;
   union{LONG n;BYTE ch[4];}u;
   u.n = _parLong(pl,1,0);
   ch = u.ch[1]; u.ch[1] = u.ch[0]; u.ch[0] = ch;
   ch = u.ch[3]; u.ch[3] = u.ch[2]; u.ch[2] = ch;
   _stornl(u.n,pl,1,0);
   _retnl(pl,u.n);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: packFloat32
            | syntax_: `packFloat32( @nValue )`
            | category: numeric/conversion
            | _kw_: packFloat32, Function
   }}*/
/*{{|desc: Packs a numeric value into the raw 32-bit IEEE float representation.
    | params:
    - `nValue` numeric - Value converted to FLOAT. The parameter is also updated with the packed 32-bit
      value.

    Returns numeric - Raw 32-bit bit pattern of the FLOAT value. }}*/
XPPRET XPPENTRY PACKFLOAT32( XppParamList pl )
{
   FLOAT  nf = (FLOAT) _parnd(pl,1);
   _stornl(((LONG*) ((void*) &nf))[0],pl,1,0);
   _retnl(pl,((LONG*) ((void*) &nf))[0]);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: unpackFloat32
            | syntax_: `unpackFloat32( @nPacked )`
            | category: numeric/conversion
            | _kw_: unpackFloat32, Function
   }}*/
/*{{|desc: Unpacks a raw 32-bit IEEE float representation into an Xbase++ numeric value.
    | params:
    - `nPacked` numeric - Raw 32-bit FLOAT bit pattern. The parameter is also updated with the unpacked
      numeric value.

    Returns numeric - Unpacked floating-point value returned as a double. }}*/
XPPRET XPPENTRY UNPACKFLOAT32( XppParamList pl )
{
   LONG n    = _parLong(pl,1);
   _stornd((double) (((FLOAT*) ((void*) &n))[0]) , pl,1,0 );
   _retnd(pl,(double) (((FLOAT*) ((void*) &n))[0])  );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: MAKEBYTE
            | syntax_: `MAKEBYTE( nLowNibble, nHighNibble )`
            | category: numeric/winapi-macro
            | _kw_: MAKEBYTE, Function
   }}*/
/*{{|desc: Builds a byte from low and high nibble values.
    | params:
    - `nLowNibble` numeric - Low 4 bits.
    - `nHighNibble` numeric - High 4 bits.

    Returns numeric - Combined byte value. }}*/
XPPRET XPPENTRY wapimc_MAKEBYTE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) | ((_parLong(pl,2) & 0x0F)<<4) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: LONIBBLE
            | syntax_: `LONIBBLE( nValue )`
            | category: numeric/winapi-macro
            | _kw_: LONIBBLE, Function
   }}*/
/*{{|desc: Returns the low-order nibble from a byte value.
    | params:
    - `nValue` numeric - Numeric value.

    Returns numeric - Low 4 bits. }}*/
XPPRET XPPENTRY wapimc_LONIBBLE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: HINIBBLE
            | syntax_: `HINIBBLE( nValue )`
            | category: numeric/winapi-macro
            | _kw_: HINIBBLE, Function
   }}*/
/*{{|desc: Returns the high-order nibble from a byte value.
    | params:
    - `nValue` numeric - Numeric value.

    Returns numeric - Bits 4..7. }}*/
XPPRET XPPENTRY wapimc_HINIBBLE(XppParamList pl)
{
   _retnl(pl, ((_parLong(pl,1) & 0xF0)>> 4) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_parse_number
            | syntax_: `ot4xb_parse_number( cNumber )`
            | category: numeric/conversion
            | _kw_: ot4xb_parse_number, Function
   }}*/
/*{{|desc: Parses a character string as an Xbase++ numeric value using the current legacy implementation.
    | params:
    - `cNumber` character - String containing the number to parse.

    Returns numeric/NIL - NIL when the input string is empty. A double when the string contains a decimal
      point or when the parsed integer does not fit in a positive signed 32-bit LONG. Otherwise a LONG.

    |note: The current implementation is intentionally simple: it uses atof() for decimal-point values and
      atoll() for integer values, with base 10 parsing only. }}*/
_XPP_REG_FUN_( OT4XB_PARSE_NUMBER)
{
   char sz[256]; ZeroMemory(sz,sizeof(sz));
   UINT cb = _parc(sz,sizeof(sz)-1,pl,1,0);
   
   if( !cb )
   {
      _ret(pl); 
      return;
   }
   if( _bscan((LPBYTE) sz , cb , '.') < cb )
   {
      _retnd(pl, atof(sz) );
      return;
   }
   LARGE_INTEGER li;
   li.QuadPart =  atoll(sz);
   if( li.HighPart || li.LowPart & 0x80000000 )
   {
      ContainerHandle conr = _conPutNDF( 0, atof( sz ), 20, 0 );
      _conReturn( pl, conr );
      _conRelease( conr );
      return;
   }
   _retnl(pl, li.LowPart );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_parse_int
            | syntax_: `ot4xb_parse_int( cValue, [nDefault] )`
            | category: numeric/conversion
            | _kw_: ot4xb_parse_int, Function
   }}*/
/*{{|desc: Parses the initial integer part of a character string using atoi(), with a caller-provided default
      value used when parsing is not possible.
    | params:
    - `cValue` character - String to parse. Parsing stops before the first '.', `|` or ',' character.
    - `nDefault` numeric - Optional value returned when cValue is not a character string or is empty.
      Defaults to 0.

    Returns numeric - Parsed integer value, or nDefault when no string is parsed.

    |note: This is a simple atoi()-based helper. It does not report conversion errors separately from a parsed
      zero. }}*/
_XPP_REG_FUN_( OT4XB_PARSE_INT )
{
   LONG nInt = _parnl(pl,2,0);
   if( _partype(pl,1) & XPP_CHARACTER )
   {
      char sz[64]; ZeroMemory(sz,sizeof(sz));   
      UINT cb = _parc(sz,sizeof(sz)-1,pl,1,0);
      if( cb )
      {
         UINT n;
         for( n = 0; n < cb; n++ )
         {
            if( (sz[n] == '.' ) || (sz[n] == '|' ) || (sz[n] == ',' ) )
            {
               sz[n] = 0;
            }
         }
         nInt = atoi(sz);
      }
   }
   _retnl(pl,nInt);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
