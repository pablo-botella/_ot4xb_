//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>dwFix</name>
      <category>numeric/bit</category>
      <description>Builds a 32-bit value from a high word and a low word.</description>
      <syntax>dwFix( nHighWord, nLowWord ) -> nDWord</syntax>
      <parameters>
         <parameter>
            <name>nHighWord</name>
            <type>numeric</type>
            <description>Value placed in the high 16 bits.</description>
         </parameter>
         <parameter>
            <name>nLowWord</name>
            <type>numeric</type>
            <description>Value masked to 16 bits and placed in the low word.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Combined 32-bit value.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY DWFIX(XppParamList pl)
{
    _retnl(pl,((_parLong(pl,1) << 16) | (_parLong(pl,2)  & 0xFFFF)));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>dwMinus</name>
      <category>numeric/bit</category>
      <description>Returns the two's-complement negation of a 32-bit numeric value.</description>
      <syntax>dwMinus( @nValue ) -> nResult</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value to negate. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Negated 32-bit value.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY DWMINUS(XppParamList pl)
{
   LONG nResult = (0 - _parLong(pl,1));
   _stornl(nResult,pl,1,0);
   _retnl(pl,nResult);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>unsigned8</name>
      <category>numeric/bit</category>
      <description>Converts a numeric value to its unsigned 8-bit representation.</description>
      <syntax>unsigned8( @nValue ) -> nUnsigned8</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value masked with 0xFF. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Value in the range 0..255.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY UNSIGNED8( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFF,pl,1,0);
   _retnl(pl,n & 0xFF);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>unsigned16</name>
      <category>numeric/bit</category>
      <description>Converts a numeric value to its unsigned 16-bit representation.</description>
      <syntax>unsigned16( @nValue ) -> nUnsigned16</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value masked with 0xFFFF. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Value in the range 0..65535.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY UNSIGNED16( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFFFF,pl,1,0);
   _retnl(pl,n & 0xFFFF);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>unsigned32</name>
      <category>numeric/bit</category>
      <description>Converts a numeric value to its unsigned 32-bit representation.</description>
      <syntax>unsigned32( @nValue ) -> nUnsigned32</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value interpreted as an unsigned 32-bit value. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>A LONG when representable as signed 32-bit, otherwise a double.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>extendSign8</name>
      <category>numeric/bit</category>
      <description>Sign-extends an 8-bit value to a 32-bit signed value.</description>
      <syntax>extendSign8( @nValue ) -> nSigned32</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Low byte to sign-extend. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>32-bit signed value produced from the low 8 bits.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY EXTENDSIGN8( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFF);
   if( n & 0x80) n |= 0xFFFFFF00;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>extendSign16</name>
      <category>numeric/bit</category>
      <description>Sign-extends a 16-bit value to a 32-bit signed value.</description>
      <syntax>extendSign16( @nValue ) -> nSigned32</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Low word to sign-extend. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>32-bit signed value produced from the low 16 bits.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY EXTENDSIGN16( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFFFF);
   if( n & 0x8000) n |= 0xFFFF0000;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>long2Double</name>
      <category>numeric/conversion</category>
      <description>Converts a numeric value to Xbase++ double representation.</description>
      <syntax>long2Double( @nValue ) -> nDouble</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value to convert. The parameter is also updated with the double value.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>The value returned as a double.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY LONG2DOUBLE( XppParamList pl )
{
   double nd = ( ( _partype(pl,1) & _xpp_DOUBLE ) ? _parnd(pl,1) : (double) _parLong(pl,1) );
   _stornd(nd,pl,1,0);
   _retnd(pl,nd);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>double2Long</name>
      <category>numeric/conversion</category>
      <description>Converts a numeric value to Xbase++ LONG representation.</description>
      <syntax>double2Long( @nValue ) -> nLong</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value to convert. The parameter is also updated with the LONG value.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>The value returned as a LONG.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY DOUBLE2LONG( XppParamList pl )
{
   LONG n =  _parLong(pl,1);
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>LOWORD</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the low-order word from a 32-bit value.</description>
      <syntax>LOWORD( nValue ) -> nLowWord</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>32-bit value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Low 16 bits.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_LOWORD(XppParamList pl){_retnl(pl,( _parLong(pl,1) & 0xFFFF ) );}
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>HIWORD</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the high-order word from a 32-bit value.</description>
      <syntax>HIWORD( nValue ) -> nHighWord</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>32-bit value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>High 16 bits.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_HIWORD(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 16) & 0xFFFF ) );}
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>LOBYTE</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the low-order byte from a 16-bit or 32-bit value.</description>
      <syntax>LOBYTE( nValue ) -> nLowByte</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>Numeric value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Low 8 bits.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_LOBYTE(XppParamList pl){ _retnl(pl,( _parLong(pl,1) & 0xFF ) );}
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>HIBYTE</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the high-order byte from a 16-bit value.</description>
      <syntax>HIBYTE( nValue ) -> nHighByte</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>Numeric value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Bits 8..15.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_HIBYTE(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 8) & 0xFF ) );}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKEWORD</name>
      <category>numeric/winapi-macro</category>
      <description>Builds a 16-bit word from low and high byte values.</description>
      <syntax>MAKEWORD( nLowByte, nHighByte ) -> nWord</syntax>
      <parameters>
         <parameter><name>nLowByte</name><type>numeric</type><description>Low byte.</description></parameter>
         <parameter><name>nHighByte</name><type>numeric</type><description>High byte.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Combined word.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKEWORD(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFF;
   LONG hi = _parLong(pl,2) & 0xFF;
	_retnl(pl, MAKEWORD(lo, hi));//  (lo | (hi << 8)) );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKELONG</name>
      <category>numeric/winapi-macro</category>
      <description>Builds a 32-bit value from low and high word values.</description>
      <syntax>MAKELONG( nLowWord, nHighWord ) -> nLong</syntax>
      <parameters>
         <parameter><name>nLowWord</name><type>numeric</type><description>Low word.</description></parameter>
         <parameter><name>nHighWord</name><type>numeric</type><description>High word.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Combined 32-bit value.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKELONG(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG( lo , hi));
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKELANGID</name>
      <category>numeric/winapi-macro</category>
      <description>Builds a Windows language identifier from primary language and sublanguage values.</description>
      <syntax>MAKELANGID( nPrimaryLanguage, nSubLanguage ) -> nLangId</syntax>
      <parameters>
         <parameter><name>nPrimaryLanguage</name><type>numeric</type><description>Primary language identifier.</description></parameter>
         <parameter><name>nSubLanguage</name><type>numeric</type><description>Sublanguage identifier.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Windows LANGID value.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKELANGID(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG(MAKELANGID( lo , hi), 0));
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKELPARAM</name>
      <category>numeric/winapi-macro</category>
      <description>Builds an LPARAM-style 32-bit value from low and high word values.</description>
      <syntax>MAKELPARAM( nLowWord, nHighWord ) -> nLParam</syntax>
      <parameters>
         <parameter><name>nLowWord</name><type>numeric</type><description>Low word.</description></parameter>
         <parameter><name>nHighWord</name><type>numeric</type><description>High word.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Combined LPARAM-style value.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKELPARAM(XppParamList pl){ wapimc_MAKELONG(pl); }
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKELRESULT</name>
      <category>numeric/winapi-macro</category>
      <description>Builds an LRESULT-style 32-bit value from low and high word values.</description>
      <syntax>MAKELRESULT( nLowWord, nHighWord ) -> nLResult</syntax>
      <parameters>
         <parameter><name>nLowWord</name><type>numeric</type><description>Low word.</description></parameter>
         <parameter><name>nHighWord</name><type>numeric</type><description>High word.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Combined LRESULT-style value.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKELRESULT(XppParamList pl){ wapimc_MAKELONG(pl); }
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>GET_X_LPARAM</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the low word of an LPARAM value, normally used as the X coordinate.</description>
      <syntax>GET_X_LPARAM( nLParam ) -> nX</syntax>
      <parameters>
         <parameter><name>nLParam</name><type>numeric</type><description>LPARAM value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Low word of the LPARAM.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_GET_X_LPARAM(XppParamList pl){ wapimc_LOWORD(pl); }
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>GET_Y_LPARAM</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the high word of an LPARAM value, normally used as the Y coordinate.</description>
      <syntax>GET_Y_LPARAM( nLParam ) -> nY</syntax>
      <parameters>
         <parameter><name>nLParam</name><type>numeric</type><description>LPARAM value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>High word of the LPARAM.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_GET_Y_LPARAM(XppParamList pl){ wapimc_HIWORD(pl); }
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>dwByteRev</name>
      <category>numeric/byte-order</category>
      <description>Reverses the byte order of a 32-bit value.</description>
      <syntax>dwByteRev( @nValue ) -> nReversed</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>32-bit value whose bytes are reversed. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Value with byte order 0-1-2-3 changed to 3-2-1-0.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY DWBYTEREV(XppParamList pl)  // dwByteRev( nDw0123 ) -> nDw3210
{
   BYTE ch;
   union{LONG n;BYTE ch[4];}u;
   u.n = _parLong(pl,1,0);
   ch = u.ch[0]; u.ch[0] = u.ch[3]; u.ch[3] = ch;
   ch = u.ch[1]; u.ch[1] = u.ch[2]; u.ch[2] = ch;
   _stornl(u.n,pl,1,0);
   _retnl(pl,u.n);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>whlByteRev</name>
      <category>numeric/byte-order</category>
      <description>Swaps bytes inside each 16-bit word of a 32-bit value.</description>
      <syntax>whlByteRev( @nValue ) -> nReversed</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>32-bit value whose word-local byte order is reversed. The parameter is also updated with the result.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Value with byte order 0-1-2-3 changed to 1-0-3-2.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY WHLBYTEREV(XppParamList pl)  // whlByteRev( nDw0123 ) -> nDw1032
{
   BYTE ch;
   union{LONG n;BYTE ch[4];}u;
   u.n = _parLong(pl,1,0);
   ch = u.ch[1]; u.ch[1] = u.ch[0]; u.ch[0] = ch;
   ch = u.ch[3]; u.ch[3] = u.ch[2]; u.ch[2] = ch;
   _stornl(u.n,pl,1,0);
   _retnl(pl,u.n);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>packFloat32</name>
      <category>numeric/conversion</category>
      <description>Packs a numeric value into the raw 32-bit IEEE float representation.</description>
      <syntax>packFloat32( @nValue ) -> nPacked</syntax>
      <parameters>
         <parameter>
            <name>nValue</name>
            <type>numeric</type>
            <description>Value converted to FLOAT. The parameter is also updated with the packed 32-bit value.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Raw 32-bit bit pattern of the FLOAT value.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY PACKFLOAT32( XppParamList pl ) // PackFloat32( nNum ) -> nPacked
{
   FLOAT  nf = (FLOAT) _parnd(pl,1);
   _stornl(((LONG*) ((void*) &nf))[0],pl,1,0);
   _retnl(pl,((LONG*) ((void*) &nf))[0]);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>unpackFloat32</name>
      <category>numeric/conversion</category>
      <description>Unpacks a raw 32-bit IEEE float representation into an Xbase++ numeric value.</description>
      <syntax>unpackFloat32( @nPacked ) -> nValue</syntax>
      <parameters>
         <parameter>
            <name>nPacked</name>
            <type>numeric</type>
            <description>Raw 32-bit FLOAT bit pattern. The parameter is also updated with the unpacked numeric value.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Unpacked floating-point value returned as a double.</description>
      </return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY UNPACKFLOAT32( XppParamList pl ) // UnPackFloat32( nPacked ) -> nNum
{
   LONG n    = _parLong(pl,1);
   _stornd((double) (((FLOAT*) ((void*) &n))[0]) , pl,1,0 );
   _retnd(pl,(double) (((FLOAT*) ((void*) &n))[0])  );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>MAKEBYTE</name>
      <category>numeric/winapi-macro</category>
      <description>Builds a byte from low and high nibble values.</description>
      <syntax>MAKEBYTE( nLowNibble, nHighNibble ) -> nByte</syntax>
      <parameters>
         <parameter><name>nLowNibble</name><type>numeric</type><description>Low 4 bits.</description></parameter>
         <parameter><name>nHighNibble</name><type>numeric</type><description>High 4 bits.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Combined byte value.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_MAKEBYTE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) | ((_parLong(pl,2) & 0x0F)<<4) );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>LONIBBLE</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the low-order nibble from a byte value.</description>
      <syntax>LONIBBLE( nValue ) -> nNibble</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>Numeric value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Low 4 bits.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_LONIBBLE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>HINIBBLE</name>
      <category>numeric/winapi-macro</category>
      <description>Returns the high-order nibble from a byte value.</description>
      <syntax>HINIBBLE( nValue ) -> nNibble</syntax>
      <parameters>
         <parameter><name>nValue</name><type>numeric</type><description>Numeric value.</description></parameter>
      </parameters>
      <return><type>numeric</type><description>Bits 4..7.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY wapimc_HINIBBLE(XppParamList pl)
{
   _retnl(pl, ((_parLong(pl,1) & 0xF0)>> 4) );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ot4xb_parse_number</name>
      <category>numeric/conversion</category>
      <description>
         Parses a character string as an Xbase++ numeric value using the
         current legacy implementation.
      </description>
      <syntax>ot4xb_parse_number( cNumber ) -> nNumber | NIL</syntax>
      <parameters>
         <parameter>
            <name>cNumber</name>
            <type>character</type>
            <description>String containing the number to parse.</description>
         </parameter>
      </parameters>
      <return>
         <type>numeric | NIL</type>
         <description>
            NIL when the input string is empty. A double when the string
            contains a decimal point or when the parsed integer does not fit in
            a positive signed 32-bit LONG. Otherwise a LONG.
         </description>
      </return>
      <remarks>
         The current implementation is intentionally simple: it uses atof() for
         decimal-point values and atoll() for integer values, with base 10
         parsing only.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
// TODO internal: evaluate an extended parser with nMode, nBase and nFormat.
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ot4xb_parse_int</name>
      <category>numeric/conversion</category>
      <description>
         Parses the initial integer part of a character string using atoi(),
         with a caller-provided default value used when parsing is not possible.
      </description>
      <syntax>ot4xb_parse_int( cValue, [nDefault] ) -> nInt</syntax>
      <parameters>
         <parameter>
            <name>cValue</name>
            <type>character</type>
            <description>
               String to parse. Parsing stops before the first '.', '|' or ','
               character.
            </description>
         </parameter>
         <parameter>
            <name>nDefault</name>
            <type>numeric</type>
            <description>
               Optional value returned when cValue is not a character string or
               is empty. Defaults to 0.
            </description>
         </parameter>
      </parameters>
      <return>
         <type>numeric</type>
         <description>Parsed integer value, or nDefault when no string is parsed.</description>
      </return>
      <remarks>
         This is a simple atoi()-based helper. It does not report conversion
         errors separately from a parsed zero.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
_XPP_REG_FUN_( OT4XB_PARSE_INT )   // ot4xb_parse_int( str , nDefault ) -> nNumber
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
// -----------------------------------------------------------------------------------------------------------------
