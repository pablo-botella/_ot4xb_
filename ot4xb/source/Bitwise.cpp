
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nOr
            | syntax_: `nOr( x1, ... xN )`
            | category: bitwise
            | _kw_: bitwise or, OR, flags, combine, set bits
   }}*/
/*{{|desc: Combines all numeric or logical parameters with bitwise `|`. nOr( x1, x2, ... ) starts with 0 and
      applies `|` to every parameter: `((0 | x1) | x2) | ...`
    | params:
    - `x1..xN` Numeric/Logical - Values to combine with bitwise `|`. If the first parameter is passed by
      reference, the result is stored there.

    Returns Numeric - Result of combining all parameters with `|`.

    |note: nOr( number ) with a single parameter is useful to force Xbase++ to store the value internally as
      __int.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NOR(XppParamList pl)
{
  ULONG nRet    = 0;
  ULONG nMax    = _partype(pl,0);
  ULONG n = 0;
  for( n=1; n <= nMax ; n++){ nRet |= static_cast<ULONG>( _parLongOrBool(pl,n) ); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nXOr
            | syntax_: `nXOr( x1, ... xN )`
            | category: bitwise
            | _kw_: bitwise xor, XOR, exclusive or, toggle bits
   }}*/
/*{{|desc: Combines numeric or logical parameters with bitwise `^`. nXOr( x1, x2, ... ) starts with x1 and
      applies `^` to each remaining parameter: `((x1 ^ x2) ^ x3) ...`
    | params:
    - `x1..xN` Numeric/Logical - Values for cumulative `^` operations. If the first parameter is passed by
      reference, the result is stored there.

    Returns Numeric - Result of cumulative `^` operations.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NXOR(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet ^= (ULONG) _parLongOrBool(pl,n); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nAnd
            | syntax_: `nAnd( x1, ... xN )`
            | category: bitwise
            | _kw_: bitwise and, AND, mask, test bits
   }}*/
/*{{|desc: Combines numeric or logical parameters with bitwise `&`. nAnd( x1, x2, ... ) starts with x1 and
      applies `&` to each remaining parameter: `((x1 & x2) & x3) ...`
    | params:
    - `x1..xN` Numeric/Logical - Values for cumulative `&` operations. If the first parameter is passed by
      reference, the result is stored there.

    Returns Numeric - Result of cumulative `&` operations.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NAND(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) _parLongOrBool(pl,n); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nAndNot
            | syntax_: `nAndNot( nMask, ... nBitsN )`
            | category: bitwise
            | _kw_: clear bits, remove flag, and not, mask off
   }}*/
/*{{|desc: Removes bits from a mask. nAndNot( mask, bits1, bits2, ... ) starts with mask and clears the
      specified bits from it. Equivalent in C: `((mask & ~bits1) & ~bits2) ...`
    | params:
    - `nMask, nBits1..nBitsN` Numeric/Logical - First value is the base mask. Each following value is
      complemented and combined with `&` to clear those bits. If the first parameter is passed by reference, the
      result is stored there.

    Returns Numeric - Result of `nMask & (~nBits1) & (~nBits2) ...`

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NANDNOT(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) ~(_parLongOrBool(pl,n)); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lAnd
            | syntax_: `lAnd( x1, ... xN )`
            | category: bitwise
            | _kw_: bitwise and, AND, test flag, has bit, logical
   }}*/
/*{{|desc: Combines numeric or logical parameters with bitwise `&` and returns a logical result. lAnd( x1, x2,
      ... ) starts with x1 and applies `&` to each remaining parameter.
    | params:
    - `x1..xN` Numeric/Logical - Values to combine with cumulative bitwise `&`.

    Returns Logical - .T. if result is non-zero, .F. otherwise.

    |note: This is useful for tests where values may arrive as numeric, logical or NIL. Parameters are read
      through OT4XB numeric/logical conversion before the bitwise operation, and the final non-zero result is
      returned as .T. or .F. For example, lAnd( NIL ) returns .F. }}*/
XPPRET XPPENTRY LAND(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) _parLongOrBool(pl,n); }
  _retl(pl,(BOOL) nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nNot
            | syntax_: `nNot( nValue )`
            | category: bitwise
            | _kw_: bitwise not, complement, invert bits, NOT
   }}*/
/*{{|desc: Performs bitwise `~` (complement) on a numeric value. Inverts all bits.
    | params:
    - `nValue` Numeric - Value to invert. If passed by reference, the result is stored there.

    Returns Numeric - Bitwise complement of input value.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NNOT(XppParamList pl)
{
   LONG nRet = (~(_parLongOrBool(pl,1)));
    _stornl(nRet,pl,1,0);
    _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nLShift
            | syntax_: `nLShift( nValue, nBits )`
            | category: bitwise
            | _kw_: shift left, <<, bit shift, multiply by 2
   }}*/
/*{{|desc: Performs left bit shift on a 32-bit value.
    | params:
    - `nValue` Numeric - Value to shift. If passed by reference, the result is stored there.
    - `nBits` Numeric - Number of bit positions to shift left.

    Returns Numeric - Value shifted left by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NLSHIFT(XppParamList pl)
{
   DWORD sh = (DWORD) _parLong( pl, 2 );
   DWORD nRet = ( sh > 31 ? 0 : (DWORD) _parLong(pl,1) << sh);
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);    
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nRShift
            | syntax_: `nRShift( nValue, nBits )`
            | category: bitwise
            | _kw_: shift right, >>, bit shift, divide by 2
   }}*/
/*{{|desc: Performs right bit shift on a 32-bit value.
    | params:
    - `nValue` Numeric - Value to shift. If passed by reference, the result is stored there.
    - `nBits` Numeric - Number of bit positions to shift right.

    Returns Numeric - Value shifted right by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NRSHIFT(XppParamList pl)
{
   DWORD sh = (DWORD) _parLong( pl, 2 );
   DWORD nRet = ( sh > 31 ? 0 : (DWORD) _parLong( pl, 1 ) >> sh );
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nLRot
            | syntax_: `nLRot( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate left, rol, circular shift, 32-bit
   }}*/
/*{{|desc: Performs left bit rotation on a 32-bit value. Bits shifted out on the left re-enter on the right.
    | params:
    - `nValue` Numeric - Value to rotate. If passed by reference, the result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate left. Only nBits modulo 32 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Value rotated left by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NLROT(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      mov eax, n;
      mov cl, nMask;
      rol eax, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nRRot
            | syntax_: `nRRot( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate right, ror, circular shift, 32-bit
   }}*/
/*{{|desc: Performs right bit rotation on a 32-bit value. Bits shifted out on the right re-enter on the left.
    | params:
    - `nValue` Numeric - Value to rotate. If passed by reference, the result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate right. Only nBits modulo 32 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Value rotated right by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NRROT(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      mov eax, n;
      mov cl, nMask;
      ror eax, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_rt_r_
            | syntax_: `void _str_rt_r_( LPBYTE p, DWORD cb, BYTE r )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_rt_r_( @buffer, len(buffer), nBitsToRotate )`
            | mangled-name: _str_rt_r_
            | _kw_: rotate right, ror, bytes, buffer, obfuscate
   }}*/
/*{{|desc: Rotates each byte in a buffer right by r bits. Bits shifted out on the right re-enter on the left
      (circular rotation). Unlike `>>` where shifted-out bits are lost, here no bits are discarded.
    | params:
    - `p` LPBYTE - Pointer to byte buffer. Passed by reference - buffer is modified in place.
    - `cb` DWORD - Number of bytes to process.
    - `r` BYTE - Number of bits to rotate right.

    Returns void }}*/
extern "C" OT4XB_API void _str_rt_r_(LPBYTE p, DWORD cb , BYTE r )
{
   while( p && cb )
   {
      BYTE kk = *p;
      __asm
      {
		  mov eax, 0;
		  mov ecx, 0;
		  mov ah, cl;
		  mov cl, r;
		  mov al, kk;
		  ror al, cl;
		  mov cl, ah;
		  mov kk, al;
      }
      *p = kk;
      p++; cb--;
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_rt_l_
            | syntax_: `void _str_rt_l_( LPBYTE p, DWORD cb, BYTE r )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_rt_l_( @buffer, len(buffer), nBitsToRotate )`
            | mangled-name: _str_rt_l_
            | _kw_: rotate left, rol, bytes, buffer, obfuscate
   }}*/
/*{{|desc: Rotates each byte in a buffer left by r bits. Bits shifted out on the left re-enter on the right
      (circular rotation). Unlike `<<` where shifted-out bits are lost, here no bits are discarded.
    | params:
    - `p` LPBYTE - Pointer to byte buffer. Passed by reference - buffer is modified in place.
    - `cb` DWORD - Number of bytes to process.
    - `r` BYTE - Number of bits to rotate left.

    Returns void }}*/
extern "C" OT4XB_API void _str_rt_l_(LPBYTE p, DWORD cb , BYTE r )
{
   while( p && cb )
   {
      BYTE kk = *p;
      __asm
      {
		  mov eax, 0;
		  mov ecx, 0;
		  mov ah, cl;
		  mov cl, r;
		  mov al, kk;
		  rol al, cl;
		  mov cl, ah;
		  mov kk, al;
      }
      *p = kk;
      p++; cb--;
   }
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_rt_r_ex_
            | syntax_: `void _str_rt_r_ex_( LPBYTE p, DWORD cb, BYTE r )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_rt_r_ex_( @buffer, len(buffer), nBitsToRotate )`
            | mangled-name: _str_rt_r_ex_
            | _kw_: rotate right, ror, bytes, buffer, incremental, obfuscate
   }}*/
/*{{|desc: Processes each byte in a buffer: rotates it right by r bits, then increments r by 1. Since r is a
      BYTE, it wraps naturally from 255 back to 0. Rotating a byte by 8 returns it to its original value. Bits
      shifted out on the right re-enter on the left (circular rotation). Unlike `>>` where shifted-out bits are
      lost, here no bits are discarded.
    | params:
    - `p` LPBYTE - Pointer to byte buffer. Passed by reference - buffer is modified in place.
    - `cb` DWORD - Number of bytes to process.
    - `r` BYTE - Initial number of bits to rotate right. Increments by 1 per byte, wraps at 256.

    Returns void }}*/
extern "C" OT4XB_API void _str_rt_r_ex_(LPBYTE p, DWORD cb, BYTE r)
{
	while (p && cb)
	{
		BYTE kk = *p;
		__asm
		{
			mov eax ,0;
			mov ecx ,0;
			mov cl, r;
			mov al, kk;
			ror al, cl;
			mov kk, al;
		}
		*p = kk;
		p++; cb--; r++;
	}
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_rt_l_ex_
            | syntax_: `void _str_rt_l_ex_( LPBYTE p, DWORD cb, BYTE r )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_rt_l_ex_( @buffer, len(buffer), nBitsToRotate )`
            | mangled-name: _str_rt_l_ex_
            | _kw_: rotate left, rol, bytes, buffer, incremental, obfuscate
   }}*/
/*{{|desc: Processes each byte in a buffer: rotates it left by r bits, then increments r by 1. Since r is a
      BYTE, it wraps naturally from 255 back to 0. Rotating a byte by 8 returns it to its original value. Bits
      shifted out on the left re-enter on the right (circular rotation). Unlike `<<` where shifted-out bits are
      lost, here no bits are discarded.
    | params:
    - `p` LPBYTE - Pointer to byte buffer. Passed by reference - buffer is modified in place.
    - `cb` DWORD - Number of bytes to process.
    - `r` BYTE - Initial number of bits to rotate left. Increments by 1 per byte, wraps at 256.

    Returns void }}*/
extern "C" OT4XB_API void _str_rt_l_ex_(LPBYTE p, DWORD cb, BYTE r)
{
	while (p && cb)
	{
		BYTE kk = *p;
		__asm
		{
			mov eax , 0;
			mov ecx , 0;
			mov cl, r;
			mov al, kk;
			rol al, cl;
			mov kk, al;
		}
		*p = kk;
		p++; cb--; r++;
	}
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nLRotByte
            | syntax_: `nLRotByte( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate left, rol, byte, 8-bit, circular shift
   }}*/
/*{{|desc: Performs left bit rotation on an 8-bit value. Bits shifted out on the left re-enter on the right.
    | params:
    - `nValue` Numeric - Byte value to rotate; only the low 8 bits are used. If passed by reference, the
      result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate left. Only nBits modulo 8 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Byte value rotated left by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NLROTBYTE(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      movzx eax, byte ptr n;
      mov cl, nMask;
      rol al, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nRRotByte
            | syntax_: `nRRotByte( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate right, ror, byte, 8-bit, circular shift
   }}*/
/*{{|desc: Performs right bit rotation on an 8-bit value. Bits shifted out on the right re-enter on the left.
    | params:
    - `nValue` Numeric - Byte value to rotate; only the low 8 bits are used. If passed by reference, the
      result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate right. Only nBits modulo 8 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Byte value rotated right by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NRROTBYTE(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      movzx eax, byte ptr n;
      mov cl, nMask;
      ror al, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nLRotWord
            | syntax_: `nLRotWord( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate left, rol, word, 16-bit, circular shift
   }}*/
/*{{|desc: Performs left bit rotation on a 16-bit value. Bits shifted out on the left re-enter on the right.
    | params:
    - `nValue` Numeric - Word value to rotate; only the low 16 bits are used. If passed by reference, the
      result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate left. Only nBits modulo 16 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Word value rotated left by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NLROTWORD(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      movzx eax, word ptr n;
      mov cl, nMask;
      rol ax, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nRRotWord
            | syntax_: `nRRotWord( nValue, nBits )`
            | category: bitwise
            | _kw_: rotate right, ror, word, 16-bit, circular shift
   }}*/
/*{{|desc: Performs right bit rotation on a 16-bit value. Bits shifted out on the right re-enter on the left.
    | params:
    - `nValue` Numeric - Word value to rotate; only the low 16 bits are used. If passed by reference, the
      result is stored there.
    - `nBits` Numeric - Number of bit positions to rotate right. Only nBits modulo 16 matters: full turns
      are discarded, so 0, negative or larger values are safe.

    Returns Numeric - Word value rotated right by nBits positions.

    |note: The internal representation is preserved as __int32, so values greater than 2147483647 (0x7FFFFFFF)
      may appear as negative. Use Unsigned32( number ) to convert to double when unsigned underflow occurs and
      you need to prevent it. }}*/
XPPRET XPPENTRY NRROTWORD(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   BYTE  nMask = (BYTE)( _parLong(pl,2) & 0xFF );
   LONG  nRet;
   __asm
   {
      movzx eax, word ptr n;
      mov cl, nMask;
      ror ax, cl;
      mov nRet, eax;
   }
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lDwBitOnOff
            | syntax_: `lDwBitOnOff( @nValue, nBit, [lOnOff] )`
            | category: bitwise
            | _kw_: bit, get bit, set bit, test bit, flag, by reference
   }}*/
/*{{|desc: Gets or sets a specific bit in a 32-bit value. If lOnOff is passed, sets the bit and updates nValue
      by reference. Always returns the current state of the bit.
    | params:
    - `@nValue` Numeric - Value to get/set bit. Passed by reference for modification.
    - `nBit` Numeric - Bit position (1-32).
    - `lOnOff` Logical - Optional. If provided, sets the bit on (.T.) or off (.F.).

    Returns Logical - .T. if bit is set, .F. if bit is clear. }}*/
XPPRET XPPENTRY LDWBITONOFF(XppParamList pl)
{
   DWORD nNum  = (DWORD) _parLong(pl,1,0);
   DWORD nMask = (1 << ((_parLong(pl,2,0)-1) & 0xFF));
   if( _partype(pl,3) & XPP_LOGICAL )
   {
      if( _parl(pl,3,0) ) nNum |= nMask;
      else nNum &= (~nMask);
      _stornl((LONG)nNum,pl,1,0);
   }
   _retl(pl, (BOOL) (nNum & nMask) ) ;
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dw_bf_get_
            | syntax_: `DWORD _dw_bf_get_( DWORD dw, DWORD sh, DWORD cb )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_dw_bf_get_( nValue, nShift, nBits )`
            | mangled-name: _dw_bf_get_
            | _kw_: bitfield, bit field, extract bits, DWORD
   }}*/
/*{{|desc: Extracts a bitfield from a DWORD value. Returns cb bits starting at bit position sh.
    | params:
    - `dw` DWORD - Source value to extract bits from.
    - `sh` DWORD - Bit position (shift) where the bitfield starts.
    - `cb` DWORD - Number of bits to extract.

    Returns DWORD - Extracted bitfield value, right-aligned. }}*/
OT4XB_API DWORD _dw_bf_get_(DWORD dw,DWORD sh, DWORD cb)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((dw >> sh) & mask);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dw_bf_set_
            | syntax_: `DWORD _dw_bf_set_( DWORD dw, DWORD sh, DWORD cb, DWORD v )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_dw_bf_set_( nValue, nShift, nBits, nNewValue )`
            | mangled-name: _dw_bf_set_
            | _kw_: bitfield, bit field, write bits, DWORD
   }}*/
/*{{|desc: Writes a value into a bitfield of a DWORD. Sets cb bits starting at bit position sh to the value v.
    | params:
    - `dw` DWORD - Source value to modify.
    - `sh` DWORD - Bit position (shift) where the bitfield starts.
    - `cb` DWORD - Number of bits in the bitfield.
    - `v` DWORD - Value to write into the bitfield.

    Returns DWORD - Modified DWORD with the bitfield set to v. }}*/
OT4XB_API DWORD _dw_bf_set_(DWORD dw,DWORD sh, DWORD cb , DWORD v)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   dw &= ~(mask << sh);
   return (dw | ((v & mask) << sh));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _b1_bf_get_
            | syntax_: `BYTE _b1_bf_get_( BYTE b, BYTE sh, BYTE cb )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_b1_bf_get_( nValue, nShift, nBits )`
            | mangled-name: _b1_bf_get_
            | _kw_: bitfield, bit field, extract bits, BYTE
   }}*/
/*{{|desc: Extracts a bitfield from a BYTE value. Returns cb bits starting at bit position sh.
    | params:
    - `b` BYTE - Source value to extract bits from.
    - `sh` BYTE - Bit position (shift) where the bitfield starts.
    - `cb` BYTE - Number of bits to extract.

    Returns BYTE - Extracted bitfield value, right-aligned. }}*/
OT4XB_API BYTE _b1_bf_get_(BYTE b,BYTE sh, BYTE cb)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((b >> sh) & mask);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _b1_bf_set_
            | syntax_: `BYTE _b1_bf_set_( BYTE b, BYTE sh, BYTE cb, BYTE v )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_b1_bf_set_( nValue, nShift, nBits, nNewValue )`
            | mangled-name: _b1_bf_set_
            | _kw_: bitfield, bit field, write bits, BYTE
   }}*/
/*{{|desc: Writes a value into a bitfield of a BYTE. Sets cb bits starting at bit position sh to the value v.
    | params:
    - `b` BYTE - Source value to modify.
    - `sh` BYTE - Bit position (shift) where the bitfield starts.
    - `cb` BYTE - Number of bits in the bitfield.
    - `v` BYTE - Value to write into the bitfield.

    Returns BYTE - Modified BYTE with the bitfield set to v. }}*/
OT4XB_API BYTE _b1_bf_set_(BYTE b ,BYTE sh, BYTE cb , BYTE v)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   b &= ~(mask << sh);
   return (b | ((v & mask) << sh));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _w_bf_get_
            | syntax_: `WORD _w_bf_get_( WORD w, WORD sh, WORD cb )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_w_bf_get_( nValue, nShift, nBits )`
            | mangled-name: _w_bf_get_
            | _kw_: bitfield, bit field, extract bits, WORD
   }}*/
/*{{|desc: Extracts a bitfield from a WORD (int16) value. Returns cb bits starting at bit position sh.
    | params:
    - `w` WORD - Source value to extract bits from.
    - `sh` WORD - Bit position (shift) where the bitfield starts.
    - `cb` WORD - Number of bits to extract.

    Returns WORD - Extracted bitfield value, right-aligned. }}*/
OT4XB_API WORD _w_bf_get_(WORD w,WORD sh, WORD cb)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((w >> sh) & mask);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _w_bf_set_
            | syntax_: `WORD _w_bf_set_( WORD w, WORD sh, WORD cb, WORD v )`
            | category: bitwise/bitfield
            | xbase-syntax: `@ot4xb:_w_bf_set_( nValue, nShift, nBits, nNewValue )`
            | mangled-name: _w_bf_set_
            | _kw_: bitfield, bit field, write bits, WORD
   }}*/
/*{{|desc: Writes a value into a bitfield of a WORD (int16). Sets cb bits starting at bit position sh to the
      value v.
    | params:
    - `w` WORD - Source value to modify.
    - `sh` WORD - Bit position (shift) where the bitfield starts.
    - `cb` WORD - Number of bits in the bitfield.
    - `v` WORD - Value to write into the bitfield.

    Returns WORD - Modified WORD with the bitfield set to v. }}*/
OT4XB_API WORD _w_bf_set_(WORD w ,WORD sh, WORD cb , WORD v)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   w &= ~(mask << sh);
   return (w | ((v & mask) << sh));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _byteflipbits_
            | syntax_: `BYTE _byteflipbits_( BYTE n )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_byteflipbits_( nByte )`
            | mangled-name: _byteflipbits_
            | _kw_: reverse bits, mirror bits, bit order, byte
   }}*/
/*{{|desc: Reverses the bit order of a BYTE. bit 0 becomes bit 7, bit 1 becomes bit 6, and so on.
    | params:
    - `n` BYTE - Byte value to reverse.

    Returns BYTE - Byte with bits in reversed order. }}*/
OT4XB_API BYTE _byteflipbits_(BYTE n)
{
   BYTE nn = ((n >> 7) & 0x01);
        nn |= ((n >> 5) & 0x02);
        nn |= ((n >> 3) & 0x04);
        nn |= ((n >> 1) & 0x08);
        nn |= ((n << 1) & 0x10);
        nn |= ((n << 3) & 0x20);
        nn |= ((n << 5) & 0x40);
        nn |= ((n << 7) & 0x80);
   return nn;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_byte_xor_
            | syntax_: `BYTE _str_byte_xor_( LPBYTE p, UINT sh, UINT cb )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_byte_xor_( pBuffer, nOffset, nBytes )`
            | mangled-name: _str_byte_xor_
            | _kw_: xor checksum, xor bytes, buffer, checksum
   }}*/
/*{{|desc: Computes the cumulative XOR of cb bytes in a buffer starting at offset sh. Result is the XOR of all
      bytes in the specified range.
    | params:
    - `p` LPBYTE - Pointer to the buffer.
    - `sh` UINT - Offset in bytes from the start of the buffer.
    - `cb` UINT - Number of bytes to process.

    Returns BYTE - Cumulative XOR of all bytes in the range. }}*/
OT4XB_API BYTE _str_byte_xor_(LPBYTE p , UINT sh , UINT cb)
{
   BYTE   b = 0;
   if(cb && p )
   {
      ULONG n = 0;
      p = _mk_ptr_(LPBYTE,p,sh);
      b = p[n]; n++;
      while( n < cb ){ b ^= p[n]; n++;}
   }
   return b;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_byte_sum_
            | syntax_: `BYTE _str_byte_sum_( LPBYTE p, UINT sh, UINT cb )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_byte_sum_( pBuffer, nOffset, nBytes )`
            | mangled-name: _str_byte_sum_
            | _kw_: byte sum, checksum, buffer, add bytes
   }}*/
/*{{|desc: Computes the cumulative sum of cb bytes in a buffer starting at offset sh.
    | params:
    - `p` LPBYTE - Pointer to the buffer.
    - `sh` UINT - Offset in bytes from the start of the buffer.
    - `cb` UINT - Number of bytes to process.

    Returns BYTE - Cumulative sum of all bytes in the range. }}*/
OT4XB_API BYTE _str_byte_sum_(LPBYTE p , UINT sh , UINT cb)
{
   BYTE   b = 0;
   if(cb && p )
   {
      ULONG n = 0;
      p = _mk_ptr_(LPBYTE,p,sh);
      b = p[n]; n++;
      while( n < cb )
      {
          b = (BYTE) b + p[n];
          n++;
      }
   }
   return b;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _str_reverse_bytes_
            | syntax_: `void _str_reverse_bytes_( LPBYTE p, UINT sh, UINT count )`
            | category: bitwise
            | xbase-syntax: `@ot4xb:_str_reverse_bytes_( @pBuffer, nOffset, nCount )`
            | mangled-name: _str_reverse_bytes_
            | _kw_: reverse bytes, byte order, swap, endian, in place
   }}*/
/*{{|desc: Reverses the order of count bytes in a buffer starting at offset sh. The buffer is modified in
      place.
    | params:
    - `p` LPBYTE - Pointer to the buffer. Modified in place.
    - `sh` UINT - Offset in bytes from the start of the buffer.
    - `count` UINT - Number of bytes to reverse.

    Returns void }}*/
OT4XB_API void _str_reverse_bytes_(LPBYTE p, UINT sh, UINT count )
{
   p = _mk_ptr_(LPBYTE, p, sh);
   for (; count > 1; count = count-2, p++)
   {
      BYTE swap = p[count - 1];
      p[count - 1] = p[0];
      p[0] = swap;
   }
}
/*{{end-c-function}}*/