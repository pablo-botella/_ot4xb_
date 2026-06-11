
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nOr</name>
      <category>bitwise</category>
      <description>
         Combines all numeric or logical parameters with bitwise |.
         nOr( x1, x2, ... ) starts with 0 and applies | to every parameter:
         ((0 | x1) | x2) | ...

         Note: nOr( number ) with a single parameter is useful to force
         Xbase++ to store the value internally as __int.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nOr( x1, ... xN ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>x1..xN</name>
            <type>Numeric | Logical</type>
            <description>
               Values to combine with bitwise |.
               If the first parameter is passed by reference, the result is stored there.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Result of combining all parameters with |.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NOR(XppParamList pl)
{
  ULONG nRet    = 0;
  ULONG nMax    = _partype(pl,0);
  ULONG n = 0;
  for( n=1; n <= nMax ; n++){ nRet |= static_cast<ULONG>( _parLongOrBool(pl,n) ); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nXOr</name>
      <category>bitwise</category>
      <description>
         Combines numeric or logical parameters with bitwise ^.
         nXOr( x1, x2, ... ) starts with x1 and applies ^ to each remaining
         parameter: ((x1 ^ x2) ^ x3) ...

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nXOr( x1, ... xN ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>x1..xN</name>
            <type>Numeric | Logical</type>
            <description>
               Values for cumulative ^ operations.
               If the first parameter is passed by reference, the result is stored there.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Result of cumulative ^ operations.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NXOR(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet ^= (ULONG) _parLongOrBool(pl,n); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nAnd</name>
      <category>bitwise</category>
      <description>
         Combines numeric or logical parameters with bitwise &amp;.
         nAnd( x1, x2, ... ) starts with x1 and applies &amp; to each remaining
         parameter: ((x1 &amp; x2) &amp; x3) ...

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nAnd( x1, ... xN ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>x1..xN</name>
            <type>Numeric | Logical</type>
            <description>
               Values for cumulative &amp; operations.
               If the first parameter is passed by reference, the result is stored there.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Result of cumulative &amp; operations.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NAND(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) _parLongOrBool(pl,n); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nAndNot</name>
      <category>bitwise</category>
      <description>
         Removes bits from a mask.
         nAndNot( mask, bits1, bits2, ... ) starts with mask and clears the
         specified bits from it. Equivalent in C:
         ((mask &amp; ~bits1) &amp; ~bits2) ...

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nAndNot( nMask, ... nBitsN ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nMask, nBits1..nBitsN</name>
            <type>Numeric | Logical</type>
            <description>
               First value is the base mask. Each following value is complemented
               and combined with &amp; to clear those bits.
               If the first parameter is passed by reference, the result is stored there.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Result of nMask &amp; (~nBits1) &amp; (~nBits2) ...</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NANDNOT(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) ~(_parLongOrBool(pl,n)); }
  _stornl(nRet,pl,1,0);
  _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>lAnd</name>
      <category>bitwise</category>
      <description>
         Combines numeric or logical parameters with bitwise &amp; and returns a
         logical result. lAnd( x1, x2, ... ) starts with x1 and applies &amp; to
         each remaining parameter.
      </description>
      <remarks>
         This is useful for tests where values may arrive as numeric, logical or NIL.
         Parameters are read through OT4XB numeric/logical conversion before the bitwise
         operation, and the final non-zero result is returned as .T. or .F.
         For example, lAnd( NIL ) returns .F.
      </remarks>
      <syntax>lAnd( x1, ... xN ) -> lResult</syntax>
      <parameters>
         <parameter>
            <name>x1..xN</name>
            <type>Numeric | Logical</type>
            <description>Values to combine with cumulative bitwise &amp;.</description>
         </parameter>
      </parameters>
      <return>
         <type>Logical</type>
         <description>.T. if result is non-zero, .F. otherwise.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LAND(XppParamList pl)
{
  ULONG nMax    = _partype(pl,0);
  ULONG nRet = (ULONG ) _parLongOrBool(pl,1);
  ULONG n;
  for( n=2; n <= nMax ; n++){ nRet &= (ULONG) _parLongOrBool(pl,n); }
  _retl(pl,(BOOL) nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nNot</name>
      <category>bitwise</category>
      <description>
         Performs bitwise ~ (complement) on a numeric value.
         Inverts all bits.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nNot( nValue ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Value to invert.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Bitwise complement of input value.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NNOT(XppParamList pl)
{
   LONG nRet = (~(_parLongOrBool(pl,1)));
    _stornl(nRet,pl,1,0);
    _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nLShift</name>
      <category>bitwise</category>
      <description>
         Performs left bit shift on a 32-bit value.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nLShift( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Value to shift.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to shift left.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Value shifted left by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/

XPPRET XPPENTRY NLSHIFT(XppParamList pl)
{
   DWORD nRet = (DWORD) _parLong(pl,1) << (DWORD) _parLong(pl,2);
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);    
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nRShift</name>
      <category>bitwise</category>
      <description>
         Performs right bit shift on a 32-bit value.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nRShift( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Value to shift.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to shift right.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Value shifted right by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NRSHIFT(XppParamList pl)
{
   DWORD nRet = (DWORD) _parLong(pl,1) >> (DWORD) _parLong(pl,2);
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nLRot</name>
      <category>bitwise</category>
      <description>
         Performs left bit rotation on a 32-bit value.
         Bits shifted out on the left re-enter on the right.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nLRot( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Value to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate left (1-32).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Value rotated left by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NLROT(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 31) +1;
   nRet = (n << nMask | (n >> (32-nMask)));
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nRRot</name>
      <category>bitwise</category>
      <description>
         Performs right bit rotation on a 32-bit value.
         Bits shifted out on the right re-enter on the left.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nRRot( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Value to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate right (1-32).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Value rotated right by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NRROT(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 31) +1;
   nRet = (n >> nMask | (n << (32-nMask)));
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_rt_r_</name>
      <category>bitwise</category>
      <description>
         Rotates each byte in a buffer right by r bits.
         Bits shifted out on the right re-enter on the left (circular rotation).
         Unlike >> where shifted-out bits are lost, here no bits are discarded.
      </description>
      <syntax>void _str_rt_r_( LPBYTE p, DWORD cb, BYTE r )</syntax>
      <prototype>void _str_rt_r_( LPBYTE p, DWORD cb, BYTE r );</prototype>
      <xbase-syntax>@ot4xb:_str_rt_r_( @buffer, len(buffer), nBitsToRotate )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to byte buffer. Passed by reference - buffer is modified in place.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bytes to process.</description>
         </parameter>
         <parameter>
            <name>r</name>
            <type>BYTE</type>
            <description>Number of bits to rotate right.</description>
         </parameter>
      </parameters>
      <return>
         <type>void</type>
         <description></description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_rt_l_</name>
      <category>bitwise</category>
      <description>
         Rotates each byte in a buffer left by r bits.
         Bits shifted out on the left re-enter on the right (circular rotation).
         Unlike &lt;&lt; where shifted-out bits are lost, here no bits are discarded.
      </description>
      <syntax>void _str_rt_l_( LPBYTE p, DWORD cb, BYTE r )</syntax>
      <prototype>void _str_rt_l_( LPBYTE p, DWORD cb, BYTE r );</prototype>
      <xbase-syntax>@ot4xb:_str_rt_l_( @buffer, len(buffer), nBitsToRotate )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to byte buffer. Passed by reference - buffer is modified in place.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bytes to process.</description>
         </parameter>
         <parameter>
            <name>r</name>
            <type>BYTE</type>
            <description>Number of bits to rotate left.</description>
         </parameter>
      </parameters>
      <return>
         <type>void</type>
         <description></description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_rt_r_ex_</name>
      <category>bitwise</category>
      <description>
         Processes each byte in a buffer: rotates it right by r bits, then increments r by 1.
         Since r is a BYTE, it wraps naturally from 255 back to 0.
         Rotating a byte by 8 returns it to its original value.
         Bits shifted out on the right re-enter on the left (circular rotation).
         Unlike >> where shifted-out bits are lost, here no bits are discarded.
      </description>
      <syntax>void _str_rt_r_ex_( LPBYTE p, DWORD cb, BYTE r )</syntax>
      <prototype>void _str_rt_r_ex_( LPBYTE p, DWORD cb, BYTE r );</prototype>
      <xbase-syntax>@ot4xb:_str_rt_r_ex_( @buffer, len(buffer), nBitsToRotate )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to byte buffer. Passed by reference - buffer is modified in place.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bytes to process.</description>
         </parameter>
         <parameter>
            <name>r</name>
            <type>BYTE</type>
            <description>Initial number of bits to rotate right. Increments by 1 per byte, wraps at 256.</description>
         </parameter>
      </parameters>
      <return>
         <type>void</type>
         <description></description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_rt_l_ex_</name>
      <category>bitwise</category>
      <description>
         Processes each byte in a buffer: rotates it left by r bits, then increments r by 1.
         Since r is a BYTE, it wraps naturally from 255 back to 0.
         Rotating a byte by 8 returns it to its original value.
         Bits shifted out on the left re-enter on the right (circular rotation).
         Unlike &lt;&lt; where shifted-out bits are lost, here no bits are discarded.
      </description>
      <syntax>void _str_rt_l_ex_( LPBYTE p, DWORD cb, BYTE r )</syntax>
      <prototype>void _str_rt_l_ex_( LPBYTE p, DWORD cb, BYTE r );</prototype>
      <xbase-syntax>@ot4xb:_str_rt_l_ex_( @buffer, len(buffer), nBitsToRotate )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to byte buffer. Passed by reference - buffer is modified in place.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bytes to process.</description>
         </parameter>
         <parameter>
            <name>r</name>
            <type>BYTE</type>
            <description>Initial number of bits to rotate left. Increments by 1 per byte, wraps at 256.</description>
         </parameter>
      </parameters>
      <return>
         <type>void</type>
         <description></description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------





/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nLRotByte</name>
      <category>bitwise</category>
      <description>
         Performs left bit rotation on an 8-bit value.
         Bits shifted out on the left re-enter on the right.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nLRotByte( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Byte value (0-255) to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate left (1-8).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Byte value rotated left by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NLROTBYTE(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 7) +1;
   nRet = ((n << nMask | (n >> (8-nMask)))&0x000000FF);
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nRRotByte</name>
      <category>bitwise</category>
      <description>
         Performs right bit rotation on an 8-bit value.
         Bits shifted out on the right re-enter on the left.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nRRotByte( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Byte value (0-255) to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate right (1-8).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Byte value rotated right by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NRROTBYTE(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 7) +1;
   nRet  = ((n >> nMask | (n << (8-nMask)))&0x000000FF);
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nLRotWord</name>
      <category>bitwise</category>
      <description>
         Performs left bit rotation on a 16-bit value.
         Bits shifted out on the left re-enter on the right.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nLRotWord( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Word value (0-65535) to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate left (1-16).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Word value rotated left by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NLROTWORD(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 15) +1;
   nRet = ((n << nMask | (n >> (16-nMask)))&0x0000FFFF);
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>nRRotWord</name>
      <category>bitwise</category>
      <description>
         Performs right bit rotation on a 16-bit value.
         Bits shifted out on the right re-enter on the left.

         Note: The internal representation is preserved as __int32, so values
         greater than 2147483647 (0x7FFFFFFF) may appear as negative.
         Use Unsigned32( number ) to convert to double when unsigned underflow occurs and you need to prevent it.
      </description>
      <syntax>nRRotWord( nValue, nBits ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>Numeric</type>
            <description>
               Word value (0-65535) to rotate.
               If passed by reference, the result is stored there.
            </description>
         </parameter>
         <parameter>
            <name>nBits</name>
            <type>Numeric</type>
            <description>Number of bit positions to rotate right (1-16).</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric</type>
         <description>Word value rotated right by nBits positions.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY NRROTWORD(XppParamList pl)
{
   ULONG n     = (ULONG) _parLong(pl,1);
   ULONG nMask = (ULONG) _parLong(pl,2);
   LONG  nRet;
   if( nMask < 1 ){_retnl(pl,n); return;}
   nMask = ((nMask -1) & 65535) +1;
   nRet = ((n >> nMask | (n << (16-nMask)))&0x0000FFFF);
   _stornl(nRet,pl,1,0);
   _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>lDwBitOnOff</name>
      <category>bitwise</category>
      <description>
         Gets or sets a specific bit in a 32-bit value.
         If lOnOff is passed, sets the bit and updates nValue by reference.
         Always returns the current state of the bit.
      </description>
      <syntax>lDwBitOnOff( @nValue, nBit, [lOnOff] ) -> lOnOff</syntax>
      <parameters>
         <parameter>
            <name>@nValue</name>
            <type>Numeric</type>
            <description>Value to get/set bit. Passed by reference for modification.</description>
         </parameter>
         <parameter>
            <name>nBit</name>
            <type>Numeric</type>
            <description>Bit position (1-32).</description>
         </parameter>
         <parameter>
            <name>lOnOff</name>
            <type>Logical</type>
            <description>Optional. If provided, sets the bit on (.T.) or off (.F.).</description>
         </parameter>
      </parameters>
      <return>
         <type>Logical</type>
         <description>.T. if bit is set, .F. if bit is clear.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LDWBITONOFF(XppParamList pl) // lDwBitOnOff( 1@nNum , 2nBit ,[3lOnOff]) -> lOnOff
{
   DWORD nNum  = (DWORD) _parLong(pl,1,0);
   DWORD nMask = (1 << ((_parLong(pl,2,0)-1) & 0xFF));
   if( _partype(pl,3) & XPP_LOGICAL )
   {
      if( _parl(pl,3,0) ) nNum |= nMask;
      else nNum &= (~nMask);
      _stornl((LONG)nNum,pl,1,0);
   }
   _retl(pl, (BOOL) nNum & nMask);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_dw_bf_get_</name>
      <category>bitwise/bitfield</category>
      <description>
         Extracts a bitfield from a DWORD value.
         Returns cb bits starting at bit position sh.
      </description>
      <syntax>DWORD _dw_bf_get_( DWORD dw, DWORD sh, DWORD cb )</syntax>
      <prototype>DWORD _dw_bf_get_( DWORD dw, DWORD sh, DWORD cb );</prototype>
      <xbase-syntax>@ot4xb:_dw_bf_get_( nValue, nShift, nBits )</xbase-syntax>
      <parameters>
         <parameter>
            <name>dw</name>
            <type>DWORD</type>
            <description>Source value to extract bits from.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>DWORD</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bits to extract.</description>
         </parameter>
      </parameters>
      <return>
         <type>DWORD</type>
         <description>Extracted bitfield value, right-aligned.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API DWORD _dw_bf_get_(DWORD dw,DWORD sh, DWORD cb)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((dw >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_dw_bf_set_</name>
      <category>bitwise/bitfield</category>
      <description>
         Writes a value into a bitfield of a DWORD.
         Sets cb bits starting at bit position sh to the value v.
      </description>
      <syntax>DWORD _dw_bf_set_( DWORD dw, DWORD sh, DWORD cb, DWORD v )</syntax>
      <prototype>DWORD _dw_bf_set_( DWORD dw, DWORD sh, DWORD cb, DWORD v );</prototype>
      <xbase-syntax>@ot4xb:_dw_bf_set_( nValue, nShift, nBits, nNewValue )</xbase-syntax>
      <parameters>
         <parameter>
            <name>dw</name>
            <type>DWORD</type>
            <description>Source value to modify.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>DWORD</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>DWORD</type>
            <description>Number of bits in the bitfield.</description>
         </parameter>
         <parameter>
            <name>v</name>
            <type>DWORD</type>
            <description>Value to write into the bitfield.</description>
         </parameter>
      </parameters>
      <return>
         <type>DWORD</type>
         <description>Modified DWORD with the bitfield set to v.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API DWORD _dw_bf_set_(DWORD dw,DWORD sh, DWORD cb , DWORD v)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   dw &= ~(mask << sh);
   return (dw | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_b1_bf_get_</name>
      <category>bitwise/bitfield</category>
      <description>
         Extracts a bitfield from a BYTE value.
         Returns cb bits starting at bit position sh.
      </description>
      <syntax>BYTE _b1_bf_get_( BYTE b, BYTE sh, BYTE cb )</syntax>
      <prototype>BYTE _b1_bf_get_( BYTE b, BYTE sh, BYTE cb );</prototype>
      <xbase-syntax>@ot4xb:_b1_bf_get_( nValue, nShift, nBits )</xbase-syntax>
      <parameters>
         <parameter>
            <name>b</name>
            <type>BYTE</type>
            <description>Source value to extract bits from.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>BYTE</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>BYTE</type>
            <description>Number of bits to extract.</description>
         </parameter>
      </parameters>
      <return>
         <type>BYTE</type>
         <description>Extracted bitfield value, right-aligned.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API BYTE _b1_bf_get_(BYTE b,BYTE sh, BYTE cb)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((b >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_b1_bf_set_</name>
      <category>bitwise/bitfield</category>
      <description>
         Writes a value into a bitfield of a BYTE.
         Sets cb bits starting at bit position sh to the value v.
      </description>
      <syntax>BYTE _b1_bf_set_( BYTE b, BYTE sh, BYTE cb, BYTE v )</syntax>
      <prototype>BYTE _b1_bf_set_( BYTE b, BYTE sh, BYTE cb, BYTE v );</prototype>
      <xbase-syntax>@ot4xb:_b1_bf_set_( nValue, nShift, nBits, nNewValue )</xbase-syntax>
      <parameters>
         <parameter>
            <name>b</name>
            <type>BYTE</type>
            <description>Source value to modify.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>BYTE</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>BYTE</type>
            <description>Number of bits in the bitfield.</description>
         </parameter>
         <parameter>
            <name>v</name>
            <type>BYTE</type>
            <description>Value to write into the bitfield.</description>
         </parameter>
      </parameters>
      <return>
         <type>BYTE</type>
         <description>Modified BYTE with the bitfield set to v.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API BYTE _b1_bf_set_(BYTE b ,BYTE sh, BYTE cb , BYTE v)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   b &= ~(mask << sh);
   return (b | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_w_bf_get_</name>
      <category>bitwise/bitfield</category>
      <description>
         Extracts a bitfield from a WORD (int16) value.
         Returns cb bits starting at bit position sh.
      </description>
      <syntax>WORD _w_bf_get_( WORD w, WORD sh, WORD cb )</syntax>
      <prototype>WORD _w_bf_get_( WORD w, WORD sh, WORD cb );</prototype>
      <xbase-syntax>@ot4xb:_w_bf_get_( nValue, nShift, nBits )</xbase-syntax>
      <parameters>
         <parameter>
            <name>w</name>
            <type>WORD</type>
            <description>Source value to extract bits from.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>WORD</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>WORD</type>
            <description>Number of bits to extract.</description>
         </parameter>
      </parameters>
      <return>
         <type>WORD</type>
         <description>Extracted bitfield value, right-aligned.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API WORD _w_bf_get_(WORD w,WORD sh, WORD cb)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((w >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_w_bf_set_</name>
      <category>bitwise/bitfield</category>
      <description>
         Writes a value into a bitfield of a WORD (int16).
         Sets cb bits starting at bit position sh to the value v.
      </description>
      <syntax>WORD _w_bf_set_( WORD w, WORD sh, WORD cb, WORD v )</syntax>
      <prototype>WORD _w_bf_set_( WORD w, WORD sh, WORD cb, WORD v );</prototype>
      <xbase-syntax>@ot4xb:_w_bf_set_( nValue, nShift, nBits, nNewValue )</xbase-syntax>
      <parameters>
         <parameter>
            <name>w</name>
            <type>WORD</type>
            <description>Source value to modify.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>WORD</type>
            <description>Bit position (shift) where the bitfield starts.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>WORD</type>
            <description>Number of bits in the bitfield.</description>
         </parameter>
         <parameter>
            <name>v</name>
            <type>WORD</type>
            <description>Value to write into the bitfield.</description>
         </parameter>
      </parameters>
      <return>
         <type>WORD</type>
         <description>Modified WORD with the bitfield set to v.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
OT4XB_API WORD _w_bf_set_(WORD w ,WORD sh, WORD cb , WORD v)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   w &= ~(mask << sh);
   return (w | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_byteflipbits_</name>
      <category>bitwise</category>
      <description>
         Reverses the bit order of a BYTE.
         bit 0 becomes bit 7, bit 1 becomes bit 6, and so on.
      </description>
      <syntax>BYTE _byteflipbits_( BYTE n )</syntax>
      <prototype>BYTE _byteflipbits_( BYTE n );</prototype>
      <xbase-syntax>@ot4xb:_byteflipbits_( nByte )</xbase-syntax>
      <parameters>
         <parameter>
            <name>n</name>
            <type>BYTE</type>
            <description>Byte value to reverse.</description>
         </parameter>
      </parameters>
      <return>
         <type>BYTE</type>
         <description>Byte with bits in reversed order.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_byte_xor_</name>
      <category>bitwise</category>
      <description>
         Computes the cumulative XOR of cb bytes in a buffer starting at offset sh.
         Result is the XOR of all bytes in the specified range.
      </description>
      <syntax>BYTE _str_byte_xor_( LPBYTE p, UINT sh, UINT cb )</syntax>
      <prototype>BYTE _str_byte_xor_( LPBYTE p, UINT sh, UINT cb );</prototype>
      <xbase-syntax>@ot4xb:_str_byte_xor_( pBuffer, nOffset, nBytes )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to the buffer.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>UINT</type>
            <description>Offset in bytes from the start of the buffer.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>UINT</type>
            <description>Number of bytes to process.</description>
         </parameter>
      </parameters>
      <return>
         <type>BYTE</type>
         <description>Cumulative XOR of all bytes in the range.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_byte_sum_</name>
      <category>bitwise</category>
      <description>
         Computes the cumulative sum of cb bytes in a buffer starting at offset sh.
      </description>
      <syntax>BYTE _str_byte_sum_( LPBYTE p, UINT sh, UINT cb )</syntax>
      <prototype>BYTE _str_byte_sum_( LPBYTE p, UINT sh, UINT cb );</prototype>
      <xbase-syntax>@ot4xb:_str_byte_sum_( pBuffer, nOffset, nBytes )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to the buffer.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>UINT</type>
            <description>Offset in bytes from the start of the buffer.</description>
         </parameter>
         <parameter>
            <name>cb</name>
            <type>UINT</type>
            <description>Number of bytes to process.</description>
         </parameter>
      </parameters>
      <return>
         <type>BYTE</type>
         <description>Cumulative sum of all bytes in the range.</description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-c>
   <function>
      <name>_str_reverse_bytes_</name>
      <category>bitwise</category>
      <description>
         Reverses the order of count bytes in a buffer starting at offset sh.
         The buffer is modified in place.
      </description>
      <syntax>void _str_reverse_bytes_( LPBYTE p, UINT sh, UINT count )</syntax>
      <prototype>void _str_reverse_bytes_( LPBYTE p, UINT sh, UINT count );</prototype>
      <xbase-syntax>@ot4xb:_str_reverse_bytes_( @pBuffer, nOffset, nCount )</xbase-syntax>
      <parameters>
         <parameter>
            <name>p</name>
            <type>LPBYTE</type>
            <description>Pointer to the buffer. Modified in place.</description>
         </parameter>
         <parameter>
            <name>sh</name>
            <type>UINT</type>
            <description>Offset in bytes from the start of the buffer.</description>
         </parameter>
         <parameter>
            <name>count</name>
            <type>UINT</type>
            <description>Number of bytes to reverse.</description>
         </parameter>
      </parameters>
      <return>
         <type>void</type>
         <description></description>
      </return>
   </function>
</ot4xb-c>
*******************************************************************************************************************/
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





