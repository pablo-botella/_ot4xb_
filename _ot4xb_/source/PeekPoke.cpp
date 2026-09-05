//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <shlwapi.h>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_peek_safe
            | syntax_: `int ot4xb_peek_safe( LPBYTE p_from, int cb_to_read, LPBYTE p_out, int cb_out )`
            | header: ot4xb_c_exported.h
            | category: memory
            | mangled-name: ot4xb_peek_safe
            | _kw_: peek, read memory, safe read, access violation, IsBadReadPtr
   }}*/
/*{{|desc: Copies bytes from an arbitrary address into a caller buffer without raising an access violation.
      The transfer is done with ReadProcessMemory() on the current process, so an unreadable source address
      produces an error result instead of a crash.
    | params:
    - `p_from` LPBYTE - Source address to read from.
    - `cb_to_read` int - Number of bytes to read.
    - `p_out` LPBYTE - Buffer receiving the bytes.
    - `cb_out` int - Size of the output buffer. The copy length is the smaller of cb_to_read and cb_out.

    Returns int - Number of bytes actually read, or -1 when the read fails. }}*/
extern "C" int OT4XB_API __cdecl ot4xb_peek_safe(LPBYTE p_from , int cb_to_read, LPBYTE p_out, int cb_out)
{
	int bytes_readed = 0;
	try
	{
		if (!ReadProcessMemory(GetCurrentProcess(), (LPCVOID)p_from, p_out, min(cb_to_read,cb_out) , (SIZE_T*)&bytes_readed))
		{
			bytes_readed = -1;
		}
	}
	catch (int) { bytes_readed = -1; }
	return bytes_readed;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Added behavior: PeekStr(pMem,[@]nShift,-1) Assuming Zero terminated string
// variants of -1:
// -21: nSize = -1; bTrim = TRUE;
// -31: nSize = -1; bLower = TRUE;
// -41: nSize = -1; bLower = TRUE; bTrim = TRUE; 

// Added behavior: PeekStr(pMem,[@]nShift,-2) Assuming UNICODE Zero terminated string
// Added behavior: PeekStr(pMem,[@]nShift,-3) like -2 but translating unicode to ansi
// Added behavior: PeekStr(pMem,[@]nShift,-17,cDelimiter) 
//                 consume string up to delimiter, 
//                 delim not included into result,
//                 sh skip also the delimiter
// variants of -17:
// -27: nSize = -17; bTrim = TRUE;  break;
// -37:  nSize = -17; bLower = TRUE; break;
// -47:  nSize = -17; bLower = TRUE; bTrim = TRUE; break;


// PeekStr(pMem,[@]nShift,nSize) -> cStr
// PeekStr(pMem,[@]nShift,@cStr) -> nSize
// Added behavior: PeekStr(pMem,[@]nShift,-76)  // like -1 but with max size = 76 

// Added behavior: PeekStr(pMem,[@]nShift,-64)  // get base64 string removing trailing spaces and CRLF 
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekStr
            | syntax_: `PeekStr( pMem, @nShift, nSize [, cDelimiter] )`
            | category: memory
            | _kw_: peek, read bytes, extended pointer, offset, memory read
   }}*/
/*{{|desc: Reads character data from an OT4XB extended pointer parameter, using and optionally updating a byte
      offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated as
      a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced by
      the bytes consumed.
    - `nSize` Numeric - Number of bytes to read, or one of the special negative modes listed below.
    - `@cStr` Character by reference - Receives bytes copied from pMem. The return value is the number of
      bytes copied.
    - `aItems` Array - Reads several fields in sequence. Character items use their current length. Numeric
      items give the byte count; negative numeric items read a zero-terminated ANSI string.
    - `cDelimiter` Character - Delimiter used by the -17 family of modes.

    Returns Character/Numeric/Array/NIL - Read value, copied byte count, updated array, or NIL when the
      parameters are not usable.

    |note: Also PeekStr( pMem, @nShift, @cStr ) -> nSize

    |note: Also PeekStr( pMem, @nShift, aItems ) -> aItems

    |note: The first parameter uses the OT4XB extended pointer locking mechanism, not a native Xbase++ pointer
      type. This allows PeekStr() to work with raw numeric pointers, character buffers, compatible structure
      objects, and temporary LONG arrays. Special nSize modes: -1 reads an ANSI zero-terminated string and
      advances past the final zero byte. -21 is -1 with leading and trailing space or TAB trimmed. -31 is -1
      converted to lower case. -41 is -1 trimmed and converted to lower case. -2 reads a UTF-16 zero-terminated
      string as raw wide-character bytes and advances past the final wide zero. -3 reads a UTF-16
      zero-terminated string and converts it to ANSI. -17 reads up to cDelimiter. The delimiter is not included
      in the result, and nShift advances past it. -27 is -17 with leading and trailing space or TAB trimmed. -37
      is -17 converted to lower case. -47 is -17 trimmed and converted to lower case. -76 reads an ANSI
      zero-terminated string with a maximum returned size of 76 bytes. -64 is intended for MIME/base64 bodies:
      if a CRLF CRLF separator is found, it consumes the source range up to and including that separator;
      otherwise it falls back to an ANSI zero-terminated source string. The returned value is transformed by
      removing TAB, LF, CR, and space, so its length can be shorter than the consumed source range.

    |example: local sh := 0 local header := PeekStr( cMime, @sh, -17, __i8(13,10,13,10) ) local body :=
      PeekStr( cMime, @sh, -64 ) sh := 0 PeekStr( header, @sh, -17, "Content-Type: " ) header := PeekStr(
      header, @sh, -17, ";" ) return "data:" + header + ";base64," + body }}*/
XPPRET XPPENTRY PEEKSTR(XppParamList pl)
{
   CON_PLKSTREX plk;
   LPSTR p      = (LPSTR) _conParamRLockStrEx(pl,1,&plk);
   LONG nShift  = _parLong(pl,2);
   ULONG ulType = _partype(pl,3); 
   BOOL  bW2A   = FALSE;
   BOOL  bLower = FALSE;
   BOOL  bTrim  = FALSE;
   BOOL bInternalTrim = FALSE;

   if( p == 0){_conUnLockStrEx_(&plk); _ret(pl); return;}

   if( ulType & XPP_CHARACTER )
   {
      BOOL bByRef = FALSE;
      ContainerHandle con = _conParam(pl,3,&bByRef);
      ULONG nSize = 0;
      p += nShift;
      if( con == NULLCONTAINER ){_conUnLockStrEx_(&plk); _ret(pl); return;}
      _conSizeC(con,&nSize);
      _conPutCL(con,p,nSize);
      if(!bByRef) _conRelease(con);
      _stornl(nShift+nSize,pl,2);
      _conUnLockStrEx_(&plk);
      _retnl(pl,nSize);
      return;
   }
   else if( ulType & XPP_NUMERIC)
   {
      ContainerHandle conr = _conNew(NULLCONTAINER);
      LONG nSize = _parLong(pl,3);
      p += nShift;
      if( nSize < 0 )
      {
         switch( nSize )
         {
            case -27: {nSize    = -17; bTrim = TRUE;  break; }
            case -37: {nSize    = -17; bLower   = TRUE; break; }            
            case -47: {nSize    = -17; bLower   = TRUE; bTrim = TRUE; break; }                        
            case -21: {nSize    = -1; bTrim = TRUE;  break; }
            case -31: {nSize    = -1; bLower   = TRUE; break; }            
            case -41: {nSize    = -1; bLower   = TRUE; bTrim = TRUE; break; }                                    
            case -64:
            {
                DWORD cbd = 4; // "\r\n\r\n"
                bInternalTrim = TRUE;
                LPSTR pFound = StrStrA( p, "\r\n\r\n" ); 
                if( pFound )
                {
                    nSize = (LONG) ( ( (DWORD) pFound ) - ( (DWORD) p ) );
                    _stornl( nShift + nSize + cbd , pl, 2 );
                    nSize = nSize + cbd;
                }
                else
                {
                    nSize = -1; 
                    _stornl( nShift, pl, 2 );
                }
                break;
            }
         }
         
         switch( nSize )
         {
            case -1:
            {
               nSize = lstrlen( (LPSTR) p);
               _stornl(nShift+nSize+1,pl,2);
               break;
            }
            case -2:
            {
               nSize = ( lstrlenW( (LPWSTR) p) * 2);
               _stornl(nShift+nSize+2,pl,2);
               break;
            }
            case -3:
            {
               nSize = ( lstrlenW( (LPWSTR) p) * 2);
               _stornl(nShift+nSize+2,pl,2);
               bW2A = TRUE;
               break;
            }
            case -76:
            {
               nSize = lstrlen( (LPSTR) p );
               if( nSize > 76 )
               {
                  nSize = 76;
               }
               _stornl( nShift + nSize + 1, pl, 2 );
               break;

            }
            case -17:            
            {
               nSize = 0; _stornl(nShift,pl,2);
               CON_PLKSTREX plk_delimiter;
               LPSTR pDelimiter = _conParamRLockStrEx(pl,4,&plk_delimiter);
               if( pDelimiter && plk_delimiter.nLen )
               {
                  LPSTR pFound = StrStrA(p,pDelimiter);
                  if( pFound )
                  {
                     nSize = (LONG) (((DWORD) pFound) - ((DWORD) p));
                     _stornl(nShift+nSize+plk_delimiter.nLen,pl,2);
                  }
               }
               _conUnLockStrEx_(&plk_delimiter);
               break;
            }
            default:{ nSize = 0;_stornl(nShift,pl,2);break;}
         }
      }
      else
      {
         _stornl(nShift+nSize,pl,2);
      }
      if( bW2A )
      {                            
         int cc = 0;
         LPSTR pAnsi = pWStr2Ansi((WCHAR*) p,(nSize >> 1),&cc);
         if( pAnsi )
         {
            _conPutCL( conr , pAnsi, (ULONG)cc);
            _xfree(pAnsi);
         }
         else _conPutC(conr,"");
      }
      else 
      {
          if( bInternalTrim )
          {
              LPBYTE buffer = (LPBYTE) _xgrab( nSize + 1 );
              LPBYTE ps = (LPBYTE) p;
              DWORD cb = 0;
              LONG n;
              for( n = 0; n < nSize; n++ , ps++ )
              {
                  if( !( *ps == 0x09 || *ps == 0x0A || *ps == 0x0D || *ps == 0x20 ) )
                  {
                      buffer[cb]  = *ps; cb++; 
                  }
              }
              _conPutCL( conr, (LPSTR) buffer, (ULONG) cb );
              _xfree( (void *) buffer );
          }
          else
          {
              if( bTrim )
              {
                  while( nSize && ( ( p[0] == 0x20 ) || ( p[0] == 0x09 ) ) ){
                      p++; nSize--;
                  }
                  while( nSize && ( ( p[( nSize - 1 )] == 0x20 ) || ( p[( nSize - 1 )] == 0x09 ) ) ){
                      nSize--;
                  }
              }
              if( bLower )
              {
                  LPSTR pLower = (LPSTR) _xgrab( ( (ULONG) nSize ) + 1 );
                  _bcopy( (LPBYTE) pLower, (LPBYTE) p, (ULONG) nSize );
                  CharLowerBuffA( pLower, (DWORD) nSize );
                  _conPutCL( conr, pLower, (ULONG) nSize );
                  _xfree( (void *) pLower );
              }
              else
              {
                  _conPutCL( conr, p, (ULONG) nSize );
              }
          }
      }
      _conUnLockStrEx_(&plk);
      _conReturn( pl , conr );
      _conRelease(conr );
      return;
   }
   else if( ulType & XPP_ARRAY )
   {
      ContainerHandle cona = _conParam(pl,3,0);
      ULONG nItems = 0;
      ULONG nn;
      //LONG  nRead = 0;
      _conSizeA( cona, &nItems , 0 );
      for( nn = 1; nn <= nItems; nn++)
      {
         LONG nSize;
         ulType = 0;
         _conTypeA(cona,&ulType,nn,0);
         if( ulType & XPP_CHARACTER )
         {
            nSize = _conArrayGetSizeC(cona,nn,0);
            _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
            nShift += nSize;
         }
         else
         {
            nSize = _conArrayGetNL(cona,nn,0);
            if( nSize < 0 )
            {
                nSize = lstrlen( p + nShift );
                _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
                nShift += (nSize + 1);
            }
            else
            {
               _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
               nShift += nSize;
            }
         }
         //nRead  += nSize;
      }
      _stornl(nShift,pl,2);
      _conUnLockStrEx_(&plk);
      _conReturn(pl,cona);
      _conRelease(cona);
      return;
   }
   _conUnLockStrEx_(&plk);
   _ret(pl);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeStr
            | syntax_: `PokeStr( pMem, @nShift, cStr )`
            | category: memory
            | _kw_: poke, write bytes, extended pointer, offset, memory write
   }}*/
/*{{|desc: Writes character data into an OT4XB extended pointer parameter, using and optionally updating a byte
      offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide the
      OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced by
      the bytes written.
    - `cStr` Character - Bytes to copy into pMem at the current offset.
    - `aStr` Array - Array of character values written sequentially into pMem.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeStr( pMem, @nShift, aStr ) -> nBytes

    |note: PokeStr() uses the OT4XB extended pointer locking mechanism for the destination parameter. It does
      not append a terminating zero byte unless that byte is already present in the supplied character data. }}*/
XPPRET XPPENTRY POKESTR(XppParamList pl)
{
    CON_PLKSTREX plk;
    LPSTR p      = (LPSTR) _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( p == 0){_conUnLockStrEx_(&plk); _ret(pl); return;}
    if( ulType & XPP_CHARACTER )
    {
       BOOL bByRef = FALSE;
       ContainerHandle con = _conTParam(pl,3,&bByRef,XPP_CHARACTER);
       if( con != NULLCONTAINER )
       {
          LPSTR pTmp = (LPSTR)0;
          ULONG nSize = 0;
          p += nShift;
          if( ot4xb_conRLockC(con,&pTmp,&nSize) == 0)
          {
             ULONG n;
             for(n=0;n<nSize;n++) p[n] = pTmp[n];
             ot4xb_conUnlockC(con);
          }
          if(!bByRef) _conRelease(con);
          _stornl(nShift+nSize,pl,2);
          _conUnLockStrEx_(&plk);
          _retnl(pl,nSize);
          return;
       }
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       ULONG nItems = 0;
       ULONG nn;
       LONG  nWrite = 0;
       _conSizeA( cona, &nItems , 0 );
       for( nn = 1; nn <= nItems; nn++)
       {
          LONG nSize = 0;
          ContainerHandle con = _conNew(NULLCONTAINER);
          con = _conArrayGet(cona,con,nn,0);
          if( con != NULLCONTAINER )
          {
             if(_conSizeC(con,(ULONG *) &nSize) != 0) nSize = 0;
             _conGetCL(con, (ULONG *) &nSize , p + nShift , nSize);
             nShift  += nSize;
             nWrite  += nSize;
             _conRelease(con);
          }
       }
       if( !bByRef ) _conRelease(cona);
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _retnl(pl,nWrite);
       return;
    }
    _conUnLockStrEx_(&plk);
    _ret(pl);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>PeekByte</name>
      <category>memory</category>
      <description>Reads one or more unsigned 8-bit values from an OT4XB extended pointer parameter.</description>
      <syntax>PeekByte( pMem, @nShift [, nItems] ) -> nByte | aBytes</syntax>
      <parameters>
         <parameter><name>pMem</name><type>Numeric | Character | Object | Array</type><description>OT4XB extended pointer source.</description></parameter>
         <parameter><name>@nShift</name><type>Numeric by reference</type><description>Byte offset advanced by one byte per item read.</description></parameter>
         <parameter><name>nItems</name><type>Numeric</type><description>Optional number of items to read. When supplied, an array is returned.</description></parameter>
      </parameters>
      <return><type>Numeric | Array | NIL</type><description>Single value, array of values, or NIL when pMem cannot be locked.</description></return>
   </function>
   <function>
      <name>PokeByte</name>
      <category>memory</category>
      <description>Writes one or more unsigned 8-bit values into an OT4XB extended pointer parameter.</description>
      <syntax>PokeByte( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeByte( pMem, @nShift, aValues ) -> nBytes</syntax>
      <parameters>
         <parameter><name>pMem</name><type>Numeric | Character | Object | Array</type><description>OT4XB extended pointer destination.</description></parameter>
         <parameter><name>@nShift</name><type>Numeric by reference</type><description>Byte offset advanced by one byte per value written.</description></parameter>
         <parameter><name>nValue</name><type>Numeric</type><description>Value written as BYTE.</description></parameter>
         <parameter><name>aValues</name><type>Array</type><description>Array of numeric values written sequentially as BYTE values.</description></parameter>
      </parameters>
      <return><type>Numeric | NIL</type><description>Number of bytes written, or NIL when pMem cannot be locked.</description></return>
   </function>
   <function>
      <name>PeekWord</name>
      <category>memory</category>
      <description>Reads one or more unsigned 16-bit values using host byte order.</description>
      <syntax>PeekWord( pMem, @nShift [, nItems] ) -> nWord | aWords</syntax>
      <return><type>Numeric | Array | NIL</type><description>Single WORD, array of WORD values, or NIL.</description></return>
   </function>
   <function>
      <name>PeekShort</name>
      <category>memory</category>
      <description>Reads one or more signed 16-bit values using host byte order.</description>
      <syntax>PeekShort( pMem, @nShift [, nItems] ) -> nShort | aShorts</syntax>
      <return><type>Numeric | Array | NIL</type><description>Single SHORT, array of SHORT values, or NIL.</description></return>
   </function>
   <function>
      <name>PokeWord</name>
      <category>memory</category>
      <description>Writes one or more unsigned 16-bit values using host byte order.</description>
      <syntax>PokeWord( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeWord( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written, or NIL.</description></return>
   </function>
   <function>
      <name>PeekDWord</name>
      <category>memory</category>
      <description>Reads one or more unsigned 32-bit values using host byte order.</description>
      <syntax>PeekDWord( pMem, @nShift [, nItems] ) -> nDWord | aDWords</syntax>
      <return><type>Numeric | Array | NIL</type><description>Single DWORD, array of DWORD values, or NIL.</description></return>
   </function>
   <function>
      <name>PokeDWord</name>
      <category>memory</category>
      <description>Writes one or more unsigned 32-bit values using host byte order.</description>
      <syntax>PokeDWord( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeDWord( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written, or NIL.</description></return>
   </function>
   <function>
      <name>PeekDouble</name>
      <category>memory</category>
      <description>Reads one or more 64-bit floating point values.</description>
      <syntax>PeekDouble( pMem, @nShift [, nItems] ) -> nDouble | aDoubles</syntax>
      <return><type>Numeric | Array | NIL</type><description>Single double value, array of double values, or NIL.</description></return>
   </function>
   <function>
      <name>PokeDouble</name>
      <category>memory</category>
      <description>Writes one or more 64-bit floating point values.</description>
      <syntax>PokeDouble( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeDouble( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written, or NIL.</description></return>
   </function>
   <function>
      <name>PeekFloat</name>
      <category>memory</category>
      <description>Reads one or more 32-bit floating point values and returns them as Xbase++ numeric values.</description>
      <syntax>PeekFloat( pMem, @nShift [, nItems] ) -> nFloat | aFloats</syntax>
      <return><type>Numeric | Array | NIL</type><description>Single float value, array of float values, or NIL.</description></return>
   </function>
   <function>
      <name>PokeFloat</name>
      <category>memory</category>
      <description>Writes one or more numeric values as 32-bit floating point values.</description>
      <syntax>PokeFloat( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeFloat( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written, or NIL.</description></return>
   </function>
   <function>
      <name>PeekWordNet</name>
      <category>memory</category>
      <description>Reads one or more 16-bit values stored in network byte order.</description>
      <syntax>PeekWordNet( pMem, @nShift [, nItems] ) -> nWord | aWords</syntax>
      <return><type>Numeric | Array | NIL</type><description>Value or values converted with ntohs().</description></return>
   </function>
   <function>
      <name>PeekDWordNet</name>
      <category>memory</category>
      <description>Reads one or more 32-bit values stored in network byte order.</description>
      <syntax>PeekDWordNet( pMem, @nShift [, nItems] ) -> nDWord | aDWords</syntax>
      <return><type>Numeric | Array | NIL</type><description>Value or values converted with ntohl().</description></return>
   </function>
   <function>
      <name>PokeWordNet</name>
      <category>memory</category>
      <description>Writes one or more 16-bit values in network byte order.</description>
      <syntax>PokeWordNet( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeWordNet( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written after converting values with htons().</description></return>
   </function>
   <function>
      <name>PokeDWordNet</name>
      <category>memory</category>
      <description>Writes one or more 32-bit values in network byte order.</description>
      <syntax>PokeDWordNet( pMem, @nShift, nValue [, nValueN] ) -> nBytes</syntax>
      <syntax>PokeDWordNet( pMem, @nShift, aValues ) -> nBytes</syntax>
      <return><type>Numeric | NIL</type><description>Number of bytes written after converting values with ntohl().</description></return>
   </function>
   <remarks>
      All Peek/Poke scalar functions in this group use the OT4XB extended pointer locking mechanism for pMem. A
      numeric pMem is treated as a raw pointer; character, object, and array values are handled by the same extended
      pointer rules used by PeekStr() and PokeStr(). Peek functions return a single value by default and an array when
      nItems is supplied as the third parameter. Poke functions accept either several numeric values or an array.
   </remarks>
   <function>
      <name>__i8</name>
      <category>memory/packing</category>
      <description>Packs numeric parameters into a binary string of BYTE values.</description>
      <syntax>__i8( nValue [, nValueN] ) -> cBytes</syntax>
      <return><type>Character</type><description>Binary string with one byte per parameter.</description></return>
   </function>
   <function>
      <name>__i16</name>
      <category>memory/packing</category>
      <description>Packs numeric parameters into a binary string of WORD values using host byte order.</description>
      <syntax>__i16( nValue [, nValueN] ) -> cBytes</syntax>
      <return><type>Character</type><description>Binary string with two bytes per parameter.</description></return>
   </function>
   <function>
      <name>__i32</name>
      <category>memory/packing</category>
      <description>Packs numeric parameters into a binary string of DWORD values using host byte order.</description>
      <syntax>__i32( nValue [, nValueN] ) -> cBytes</syntax>
      <return><type>Character</type><description>Binary string with four bytes per parameter.</description></return>
   </function>
   <function>
      <name>__f32</name>
      <category>memory/packing</category>
      <description>Packs numeric parameters into a binary string of 32-bit floating point values.</description>
      <syntax>__f32( nValue [, nValueN] ) -> cBytes</syntax>
      <return><type>Character</type><description>Binary string with four bytes per parameter.</description></return>
   </function>
   <function>
      <name>__f64</name>
      <category>memory/packing</category>
      <description>Packs numeric parameters into a binary string of 64-bit floating point values.</description>
      <syntax>__f64( nValue [, nValueN] ) -> cBytes</syntax>
      <return><type>Character</type><description>Binary string with eight bytes per parameter.</description></return>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY PEEKBYTE(XppParamList pl) // PeekByte(pMem,[@]nShift[,nItems]) -> nByte | aBytes
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk); _ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          LPBYTE p = ( LPBYTE ) (np + nShift);
          BYTE   n = p[0];
          _conArrayPutNL(cona,(LONG) n , nn , 0);
          nShift += sizeof(BYTE);
       }
       _stornl(nShift,pl,2);
        _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       LPBYTE p = ( LPBYTE ) (np + nShift);
       BYTE   n = p[0];
       _stornl(nShift+sizeof(BYTE),pl,2);
       _conUnLockStrEx_(&plk);
       _retnl(pl,(LONG) n);
    }
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeByte
            | syntax_: `PokeByte( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write byte, extended pointer, offset
   }}*/
/*{{|desc: Writes one or more numeric values as single bytes into an OT4XB extended pointer parameter, using
      and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as one byte. Only the lowest 8 bits are stored. Each additional
      numeric parameter is written in the same way.
    - `aValues` Array - Array of numeric values written sequentially, one byte each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeByte( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEBYTE(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          LPBYTE p = ( LPBYTE ) (np + nShift);
          BYTE   n = ( BYTE ) _parLong(pl,nn+2);
          p[0] = n;
          nShift += sizeof(BYTE);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _retnl( pl, nItems * sizeof(BYTE));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             LPBYTE p = ( LPBYTE ) (np + nShift);
             BYTE   n = ( BYTE ) _conArrayGetNL(cona,nn,0);
             p[0] = n;
             nShift += sizeof(BYTE);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);
       _retnl( pl, nItems * sizeof(BYTE) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekWord
            | syntax_: `PeekWord( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read word, 16-bit, extended pointer, offset
   }}*/
/*{{|desc: Reads one or more unsigned 16-bit values in host byte order from an OT4XB extended pointer
      parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable. }}*/
XPPRET XPPENTRY PEEKWORD(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          LPWORD p = ( LPWORD ) (np + nShift);
          WORD   n = p[0];
          _conArrayPutNL(cona,(LONG) n , nn , 0);
          nShift += sizeof(WORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       LPWORD p = ( LPWORD ) (np + nShift);
       WORD   n = p[0];
       _stornl(nShift+sizeof(WORD),pl,2);
       _conUnLockStrEx_(&plk);_retnl(pl,(LONG) n);
    }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekShort
            | syntax_: `PeekShort( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read short, signed 16-bit, extended pointer
   }}*/
/*{{|desc: Reads one or more signed 16-bit values in host byte order from an OT4XB extended pointer
      parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable. }}*/
XPPRET XPPENTRY PEEKSHORT(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          SHORT* p = ( SHORT* ) (np + nShift);
          SHORT  n = p[0];
          _conArrayPutNL(cona,(LONG) n , nn , 0);
          nShift += sizeof(SHORT);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       SHORT* p = ( SHORT* ) (np + nShift);
       SHORT  n = p[0];
       _stornl(nShift+sizeof(SHORT),pl,2);
       _conUnLockStrEx_(&plk);_retnl(pl,(LONG) n);
    }
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekWordNet
            | syntax_: `PeekWordNet( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read word, network byte order, big endian, ntohs
   }}*/
/*{{|desc: Reads one or more unsigned 16-bit values stored in network byte order from an OT4XB extended
      pointer parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable. }}*/
XPPRET XPPENTRY PEEKWORDNET(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          LPWORD p = ( LPWORD ) (np + nShift);
          WORD   n = p[0];
          _conArrayPutNL(cona,(LONG) ntohs(n) , nn , 0);
          nShift += sizeof(WORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       LPWORD p = ( LPWORD ) (np + nShift);
       WORD   n = p[0];
       _stornl(nShift+sizeof(WORD),pl,2);
       _conUnLockStrEx_(&plk);_retnl(pl,(LONG) ntohs(n));
    }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeWord
            | syntax_: `PokeWord( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write word, 16-bit, extended pointer
   }}*/
/*{{|desc: Writes one or more numeric values as 16-bit words in host byte order into an OT4XB extended
      pointer parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 16-bit word. Only the lowest 16 bits are stored. Each
      additional numeric parameter is written in the same way.
    - `aValues` Array - Array of numeric values written sequentially, two bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeWord( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEWORD(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          LPWORD p = ( LPWORD ) (np + nShift);
          WORD   n = ( WORD ) _parLong(pl,nn+2);
          p[0] = n;
          nShift += sizeof(WORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(WORD));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             LPWORD p = ( LPWORD ) (np + nShift);
             WORD   n = ( WORD ) _conArrayGetNL(cona,nn,0);
             p[0] = n;
             nShift += sizeof(WORD);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(WORD) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeWordNet
            | syntax_: `PokeWordNet( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write word, network byte order, big endian, htons
   }}*/
/*{{|desc: Writes one or more numeric values as 16-bit words in network byte order into an OT4XB extended
      pointer parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 16-bit word. Only the lowest 16 bits are stored. Each
      additional numeric parameter is written in the same way.
    - `aValues` Array - Array of numeric values written sequentially, two bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeWordNet( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEWORDNET(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          LPWORD p = ( LPWORD ) (np + nShift);
          WORD   n = ( WORD ) _parLong(pl,nn+2);
          p[0] = htons(n);
          nShift += sizeof(WORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(WORD));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             LPWORD p = ( LPWORD ) (np + nShift);
             WORD   n = ( WORD ) _conArrayGetNL(cona,nn,0);
             p[0] = htons(n);
             nShift += sizeof(WORD);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(WORD) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekDWord
            | syntax_: `PeekDWord( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read DWORD, 32-bit, extended pointer, offset
   }}*/
/*{{|desc: Reads one or more 32-bit values in host byte order from an OT4XB extended pointer parameter,
      using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable.

    |note: Values are returned through a signed 32-bit conversion: a value with the high bit set appears as
      a negative number. }}*/
XPPRET XPPENTRY PEEKDWORD(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          LPDWORD p = ( LPDWORD ) (np + nShift);
          DWORD   n = p[0];
          _conArrayPutNL(cona,(LONG) n , nn , 0);
          nShift += sizeof(DWORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       LPDWORD p = ( LPDWORD ) (np + nShift);
       DWORD   n = p[0];
       _stornl(nShift+sizeof(DWORD),pl,2);
       _conUnLockStrEx_(&plk);_retnl(pl,(LONG) n);
    }
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekDWordNet
            | syntax_: `PeekDWordNet( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read DWORD, network byte order, big endian, ntohl
   }}*/
/*{{|desc: Reads one or more 32-bit values stored in network byte order from an OT4XB extended pointer
      parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable.

    |note: Values are returned through a signed 32-bit conversion: a value with the high bit set appears as
      a negative number. }}*/
XPPRET XPPENTRY PEEKDWORDNET(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          LPDWORD p = ( LPDWORD ) (np + nShift);
          DWORD   n = p[0];
          _conArrayPutNL(cona,(LONG) ntohl(n) , nn , 0);
          nShift += sizeof(DWORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       LPDWORD p = ( LPDWORD ) (np + nShift);
       DWORD   n = p[0];
       _stornl(nShift+sizeof(DWORD),pl,2);
       _conUnLockStrEx_(&plk);_retnl(pl,(LONG) ntohl(n));
    }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeDWord
            | syntax_: `PokeDWord( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write DWORD, 32-bit, extended pointer
   }}*/
/*{{|desc: Writes one or more numeric values as 32-bit values in host byte order into an OT4XB extended
      pointer parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 32-bit value. Each additional numeric parameter is written
      in the same way.
    - `aValues` Array - Array of numeric values written sequentially, four bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeDWord( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEDWORD(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          LPDWORD p = ( LPDWORD ) (np + nShift);
          DWORD   n = ( DWORD ) _parLong(pl,nn+2);
          p[0] = n;
          nShift += sizeof(DWORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(DWORD));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             LPDWORD p = ( LPDWORD ) (np + nShift);
             DWORD   n = ( DWORD ) _conArrayGetNL(cona,nn,0);
             p[0] = n;
             nShift += sizeof(DWORD);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(DWORD) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeDWordNet
            | syntax_: `PokeDWordNet( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write DWORD, network byte order, big endian, htonl
   }}*/
/*{{|desc: Writes one or more numeric values as 32-bit values in network byte order into an OT4XB extended
      pointer parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 32-bit value. Each additional numeric parameter is written
      in the same way.
    - `aValues` Array - Array of numeric values written sequentially, four bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeDWordNet( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEDWORDNET(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          LPDWORD p = ( LPDWORD ) (np + nShift);
          DWORD   n = ( DWORD ) _parLong(pl,nn+2);
          p[0] = ntohl(n);
          nShift += sizeof(DWORD);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(DWORD));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             LPDWORD p = ( LPDWORD ) (np + nShift);
             DWORD   n = ( DWORD ) _conArrayGetNL(cona,nn,0);
             p[0] = ntohl(n);
             nShift += sizeof(DWORD);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(DWORD) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekDouble
            | syntax_: `PeekDouble( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read double, 64-bit float, extended pointer
   }}*/
/*{{|desc: Reads one or more 64-bit floating point values from an OT4XB extended pointer parameter, using
      and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable. }}*/
XPPRET XPPENTRY PEEKDOUBLE(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          double* p = ( double*) (np + nShift);
          double  n = p[0];
          _conArrayPutND(cona,n , nn , 0);
          nShift += sizeof(double);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       double* p = ( double* ) (np + nShift);
       double   n = p[0];
       _stornl(nShift+sizeof(double),pl,2);
       _conUnLockStrEx_(&plk);_retnd(pl, n);
    }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeDouble
            | syntax_: `PokeDouble( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write double, 64-bit float, extended pointer
   }}*/
/*{{|desc: Writes one or more numeric values as 64-bit floating point values into an OT4XB extended pointer
      parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 64-bit floating point value. Each additional numeric
      parameter is written in the same way.
    - `aValues` Array - Array of numeric values written sequentially, eight bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeDouble( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEDOUBLE(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          double * p = ( double * ) (np + nShift);
          double   n = _parnd(pl,nn+2);
          p[0] = n;
          nShift += sizeof(double);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(double));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             double * p = ( double * ) (np + nShift);
             double   n = ( double ) _conArrayGetND(cona,nn,0);
             p[0] = n;
             nShift += sizeof(double);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(double) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PeekFloat
            | syntax_: `PeekFloat( pMem, @nShift [, nItems] )`
            | category: memory
            | _kw_: peek, read float, 32-bit float, extended pointer
   }}*/
/*{{|desc: Reads one or more 32-bit floating point values from an OT4XB extended pointer parameter, using
      and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer source. A numeric value is treated
      as a pointer; a character value locks its internal buffer; an object must provide the OT4XB
      ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is treated as a
      temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes read.
    - `nItems` Numeric - Optional number of consecutive values to read. When present, the result is an
      array of nItems values.

    Returns Numeric/Array/NIL - Single value, array of values, or NIL when pMem is not usable. }}*/
XPPRET XPPENTRY PEEKFLOAT(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( _partype(pl,0) == 3)
    {
       LONG nItems = _parLong(pl,3);
       LONG nn;
       ContainerHandle cona = _conNewArray(1,nItems);
       for( nn = 1; nn <= nItems; nn++)
       {
          FLOAT* p = ( FLOAT*) (np + nShift);
          FLOAT  n = p[0];
          _conArrayPutND(cona,(double) n , nn , 0);
          nShift += sizeof(FLOAT);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
    }
    else
    {
       FLOAT* p = ( FLOAT* ) (np + nShift);
       FLOAT   n = p[0];
       _stornl(nShift+sizeof(FLOAT),pl,2);
       _conUnLockStrEx_(&plk);_retnd(pl,(double) n);
    }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PokeFloat
            | syntax_: `PokeFloat( pMem, @nShift, nValue [, nValueN] )`
            | category: memory
            | _kw_: poke, write float, 32-bit float, extended pointer
   }}*/
/*{{|desc: Writes one or more numeric values as 32-bit floating point values into an OT4XB extended pointer
      parameter, using and optionally updating a byte offset.
    | params:
    - `pMem` Numeric/Character/Object/Array - OT4XB extended pointer destination. A numeric value is
      treated as a pointer; a character value locks its internal buffer for writing; an object must provide
      the OT4XB ::_lock_()/::_unlock_() pointer protocol, normally through a GWST subclass; an array is
      treated as a temporary LONG buffer.
    - `@nShift` Numeric by reference - Byte offset inside pMem. When passed by reference, it is advanced
      by the bytes written.
    - `nValue` Numeric - Value written as a 32-bit floating point value. Each additional numeric
      parameter is written in the same way.
    - `aValues` Array - Array of numeric values written sequentially, four bytes each.

    Returns Numeric/NIL - Number of bytes written, or NIL when the parameters are not usable.

    |note: Also PokeFloat( pMem, @nShift, aValues ) -> nBytes }}*/
XPPRET XPPENTRY POKEFLOAT(XppParamList pl)
{
    CON_PLKSTREX plk;
    LONG np = (LONG)  _conParamWLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);
    if( np == 0){_conUnLockStrEx_(&plk);_ret(pl); return;}
    if( ulType & XPP_NUMERIC )
    {
       LONG nItems = (LONG) ( _partype(pl,0) - 2);
       LONG nn;
       for( nn = 1; nn <= nItems; nn++)
       {
          FLOAT * p = ( FLOAT * ) (np + nShift);
          FLOAT   n = (FLOAT) _parnd(pl,nn+2);
          p[0] = n;
          nShift += sizeof(FLOAT);
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(FLOAT));
    }
    else if( ulType & XPP_ARRAY )
    {
       BOOL bByRef = FALSE;
       ContainerHandle cona = _conParam(pl,3,&bByRef);
       LONG nItems = 0;
       if( cona != NULLCONTAINER)
       {
          LONG nn;
          _conSizeA( cona , (ULONG * ) &nItems, 0);
          for( nn = 1; nn <= nItems; nn++)
          {
             FLOAT * p = ( FLOAT * ) (np + nShift);
             FLOAT   n = ( FLOAT ) _conArrayGetND(cona,nn,0);
             p[0] = n;
             nShift += sizeof(FLOAT);
          }
          _stornl(nShift,pl,2);
          if( !bByRef) _conRelease(cona);
       }
       _conUnLockStrEx_(&plk);_retnl( pl, nItems * sizeof(FLOAT) );
    }
    else { _conUnLockStrEx_(&plk); _ret(pl); }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __i8
            | syntax_: `__i8( nValue [, nValueN] )`
            | category: memory/packing
            | _kw_: pack bytes, binary string, int8, struct packing
   }}*/
/*{{|desc: Packs its numeric parameters into a binary string, one byte per parameter.
    | params:
    - `nValue` Numeric - Value stored as one byte. Only the lowest 8 bits are used.

    Returns Character - Binary string with one byte per parameter, or an empty string when called without
      parameters. }}*/
XPPRET XPPENTRY __I8( XppParamList pl )
{
   ULONG np = _partype(pl,0);
   if( np )
   {
      ULONG  ns  = np * sizeof(BYTE);
      LPBYTE p  = (LPBYTE) _xgrab(ns);
      ULONG n;
      for( n=0; n < np; n++) p[n] = (BYTE) ( _parLong(pl,n+1,0) & 0xFF );
      _retclen(pl,(LPSTR) p, ns);
      _xfree((void*) p);
   }
   else _retc(pl,"");
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __i16
            | syntax_: `__i16( nValue [, nValueN] )`
            | category: memory/packing
            | _kw_: pack words, binary string, int16, struct packing
   }}*/
/*{{|desc: Packs its numeric parameters into a binary string, one 16-bit word per parameter, using host byte
      order.
    | params:
    - `nValue` Numeric - Value stored as a 16-bit word. Only the lowest 16 bits are used.

    Returns Character - Binary string with two bytes per parameter, or an empty string when called without
      parameters. }}*/
XPPRET XPPENTRY __I16( XppParamList pl )
{
   ULONG np = _partype(pl,0);
   if( np )
   {
      ULONG  ns  = np * sizeof(WORD);
      LPWORD p  = (LPWORD) _xgrab(ns);
      ULONG n;
      for( n=0; n < np; n++) p[n] = (WORD) ( _parLong(pl,n+1,0) & 0xFFFF );
      _retclen(pl,(LPSTR) p, ns);
      _xfree((void*) p);
   }
   else _retc(pl,"");
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __i32
            | syntax_: `__i32( nValue [, nValueN] )`
            | category: memory/packing
            | _kw_: pack DWORDs, binary string, int32, struct packing
   }}*/
/*{{|desc: Packs its numeric parameters into a binary string, one 32-bit value per parameter, using host byte
      order.
    | params:
    - `nValue` Numeric - Value stored as a 32-bit value.

    Returns Character - Binary string with four bytes per parameter, or an empty string when called without
      parameters. }}*/
XPPRET XPPENTRY __I32( XppParamList pl )
{
   ULONG np = _partype(pl,0);
   if( np )
   {
      ULONG  ns  = np * sizeof(DWORD);
      LPDWORD p  = (LPDWORD) _xgrab(ns);
      ULONG n;
      for( n=0; n < np; n++) p[n] = (DWORD) _parLong(pl,n+1,0);
      _retclen(pl,(LPSTR) p, ns);
      _xfree((void*) p);
   }
   else _retc(pl,"");
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __f32
            | syntax_: `__f32( nValue [, nValueN] )`
            | category: memory/packing
            | _kw_: pack floats, binary string, float, struct packing
   }}*/
/*{{|desc: Packs its numeric parameters into a binary string, one 32-bit floating point value per parameter.
    | params:
    - `nValue` Numeric - Value stored as a 32-bit floating point value.

    Returns Character - Binary string with four bytes per parameter, or an empty string when called without
      parameters. }}*/
XPPRET XPPENTRY __F32( XppParamList pl )
{
   ULONG np = _partype(pl,0);
   if( np )
   {
      ULONG  ns  = np * sizeof(FLOAT);
      PFLOAT p   = (PFLOAT) _xgrab(ns);
      ULONG n;
      for( n=0; n < np; n++) p[n] = (FLOAT) _parnd(pl,n+1,0);
      _retclen(pl,(LPSTR) p, ns);
      _xfree((void*) p);
   }
   else _retc(pl,"");
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __f64
            | syntax_: `__f64( nValue [, nValueN] )`
            | category: memory/packing
            | _kw_: pack doubles, binary string, double, struct packing
   }}*/
/*{{|desc: Packs its numeric parameters into a binary string, one 64-bit floating point value per parameter.
    | params:
    - `nValue` Numeric - Value stored as a 64-bit floating point value.

    Returns Character - Binary string with eight bytes per parameter, or an empty string when called without
      parameters. }}*/
XPPRET XPPENTRY __F64( XppParamList pl )
{
   ULONG np = _partype(pl,0);
   if( np )
   {
      ULONG   ns  = np * sizeof(double);
      double* p   = (double*) _xgrab(ns);
      ULONG n;
      for( n=0; n < np; n++) p[n] =  _parnd(pl,n+1,0);
      _retclen(pl,(LPSTR) p, ns);
      _xfree((void*) p);
   }
   else _retc(pl,"");
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function>
      <name>ppVtbl2A</name>
      <category>memory/com</category>
      <description>
         Returns entries from the virtual table of a COM-style interface pointer.
      </description>
      <syntax>ppVtbl2A( pInterface, nMethods ) -> aVtbl</syntax>
      <parameters>
         <parameter>
            <name>pInterface</name>
            <type>Numeric</type>
            <description>
               Pointer to an interface/object whose first DWORD is the vtable pointer.
            </description>
         </parameter>
         <parameter>
            <name>nMethods</name>
            <type>Numeric</type>
            <description>Number of vtable entries to copy into the returned array.</description>
         </parameter>
      </parameters>
      <return>
         <type>Array | NIL</type>
         <description>Array with the requested vtable function pointers, or NIL when pInterface cannot be read.</description>
      </return>
      <remarks>
         This function expects a raw numeric pointer, not an OT4XB extended pointer parameter. It is a low-level helper
         for inspecting COM-style interfaces in 32-bit builds.
      </remarks>
   </function>
   <function>
      <name>ppVtbl2N</name>
      <category>memory/com</category>
      <description>
         Returns one entry from the virtual table of a COM-style interface pointer.
      </description>
      <syntax>ppVtbl2N( pInterface, nIndex ) -> pMethod</syntax>
      <parameters>
         <parameter>
            <name>pInterface</name>
            <type>Numeric</type>
            <description>
               Pointer to an interface/object whose first DWORD is the vtable pointer.
            </description>
         </parameter>
         <parameter>
            <name>nIndex</name>
            <type>Numeric</type>
            <description>Zero-based vtable entry index.</description>
         </parameter>
      </parameters>
      <return>
         <type>Numeric | NIL</type>
         <description>Function pointer stored at the requested vtable index, or NIL when pInterface cannot be read.</description>
      </return>
      <remarks>
         This function expects a raw numeric pointer, not an OT4XB extended pointer parameter.
      </remarks>
   </function>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY PPVTBL2A(XppParamList pl) // ppVtbl2A(p,mc)
{
   DWORD** ppv = (DWORD**) _parLong(pl,1,0);
   DWORD*  pv  = 0;
   if( ppv ){ __try{ pv = ppv[0];} __finally{;} }
   if( pv )
   {
      DWORD   cm  = (DWORD) _parLong(pl,2,0);
      DWORD   dw;
      ContainerHandle conr = _conNewArray(1,cm);
      __try
      {
         for( dw=0; dw < cm; dw++){ _conArrayPutNL(conr,(LONG) pv[dw], dw+1, 0); }
      }
      __finally
      {
         _conReturn(pl,conr);
         _conRelease(conr);
      }
      return;
    }
    _ret(pl);
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ppVtbl2N
            | syntax_: `ppVtbl2N( pInterface, nIndex )`
            | category: memory/com
            | _kw_: vtable, COM interface, method pointer, virtual table entry
   }}*/
/*{{|desc: Returns one entry from the virtual table of a COM-style interface pointer.
    | params:
    - `pInterface` Numeric - Raw pointer to an interface or object whose first DWORD is the pointer to
      its virtual table. This parameter is a plain numeric pointer, not an OT4XB extended pointer.
    - `nIndex` Numeric - Zero-based index of the virtual table entry.

    Returns Numeric/NIL - Function pointer stored at the requested index, or NIL when pInterface or its
      virtual table pointer is zero. }}*/
XPPRET XPPENTRY PPVTBL2N(XppParamList pl)
{
   DWORD** ppv = (DWORD**) _parLong(pl,1,0);
   DWORD*  pv  = 0;
   if( ppv ){ __try{ pv = ppv[0];} __finally{;} }
   if( pv )
   {
      DWORD   dw  = 0;
      __try{dw = pv[(DWORD) _parLong(pl,2,0)];}__finally{_retnl(pl,(LONG) dw);}
      return;
    }
    _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
