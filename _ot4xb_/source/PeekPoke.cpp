//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <shlwapi.h>
//----------------------------------------------------------------------------------------------------------------------
extern "C" int OT4XB_API __cdecl ot4xb_peek_safe(LPBYTE p_from , int cb_to_read, LPBYTE p_out, int cb_out) // -> bytes_readed
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
                    nSize = -1;
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKESTR(XppParamList pl) // PokeStr(pMem,[@]nShift,[@]cStr|aStr) -> nBytes
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
//----------------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY POKEBYTE(XppParamList pl) // PokeByte(pMem,[@]nShift,nValue,...) | PokeByte(pMem,[@]nShift,aValues)
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
    else _conUnLockStrEx_(&plk); _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKWORD(XppParamList pl) // PeekWORD(pMem,[@]nShift[,@c]) -> nWORD
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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKSHORT(XppParamList pl) // PeekShort(pMem,[@]nShift[,@c]) -> nShort
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
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKWORDNET(XppParamList pl) // PeekWORDNET(pMem,[@]nShift[,@c]) -> nWORD
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEWORD(XppParamList pl) // PokeWORD(pMem,[@]nShift,nValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEWORDNET(XppParamList pl) // PokeWORDNET(pMem,[@]nShift,nValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKDWORD(XppParamList pl) // PeekDWORD(pMem,[@]nShift[,@c]) -> nDWORD
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
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKDWORDNET(XppParamList pl) // PeekDWORDNET(pMem,[@]nShift[,@c]) -> nDWORD
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEDWORD(XppParamList pl) // PokeDWORD(pMem,[@]nShift,nValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEDWORDNET(XppParamList pl) // PokeDWORDNET(pMem,[@]nShift,nValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKDOUBLE(XppParamList pl) // Peekdouble(pMem,[@]nShift[,@c]) -> nDouble
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEDOUBLE(XppParamList pl) // PokeDouble(pMem,[@]nShift,ndValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PEEKFLOAT(XppParamList pl) // PeekFloat(pMem,[@]nShift[,@c]) -> nFloat
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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY POKEFLOAT(XppParamList pl) // PokeFloat(pMem,[@]nShift,nfValue|cValue)
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
    else _conUnLockStrEx_(&plk);_ret(pl);
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY PPVTBL2N(XppParamList pl) // ppVtbl2N(p,n)
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
// -----------------------------------------------------------------------------------------------------------------
