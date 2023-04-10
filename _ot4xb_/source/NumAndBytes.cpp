//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DWFIX(XppParamList pl)
{
    _retnl(pl,((_parLong(pl,1) << 16) | (_parLong(pl,2)  & 0xFFFF)));
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DWMINUS(XppParamList pl)
{
   LONG nResult = (0 - _parLong(pl,1));
   _stornl(nResult,pl,1,0);
   _retnl(pl,nResult);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY UNSIGNED8( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFF,pl,1,0);
   _retnl(pl,n & 0xFF);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY UNSIGNED16( XppParamList pl )
{
   LONG n = 0;
   if( _partype(pl,1) & _xpp_DOUBLE ) n = (LONG) _parnd(pl,1);
   else n = _parLong(pl,1);
   _stornl(n & 0xFFFF,pl,1,0);
   _retnl(pl,n & 0xFFFF);
}
//----------------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY EXTENDSIGN8( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFF);
   if( n & 0x80) n |= 0xFFFFFF00;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY EXTENDSIGN16( XppParamList pl )
{
   LONG n = (_parLong(pl,1) & 0xFFFF);
   if( n & 0x8000) n |= 0xFFFF0000;
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LONG2DOUBLE( XppParamList pl )
{
   double nd = ( ( _partype(pl,1) & _xpp_DOUBLE ) ? _parnd(pl,1) : (double) _parLong(pl,1) );
   _stornd(nd,pl,1,0);
   _retnd(pl,nd);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DOUBLE2LONG( XppParamList pl )
{
   LONG n =  _parLong(pl,1);
   _stornl(n,pl,1,0);
   _retnl(pl,n);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_LOWORD(XppParamList pl){_retnl(pl,( _parLong(pl,1) & 0xFFFF ) );}
XPPRET XPPENTRY wapimc_HIWORD(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 16) & 0xFFFF ) );}
XPPRET XPPENTRY wapimc_LOBYTE(XppParamList pl){ _retnl(pl,( _parLong(pl,1) & 0xFF ) );}
XPPRET XPPENTRY wapimc_HIBYTE(XppParamList pl){ _retnl(pl,( (_parLong(pl,1) >> 8) & 0xFF ) );}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_MAKEWORD(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFF;
   LONG hi = _parLong(pl,2) & 0xFF;
	_retnl(pl, MAKEWORD(lo, hi));//  (lo | (hi << 8)) );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_MAKELONG(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG( lo , hi));
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_MAKELANGID(XppParamList pl)
{
   LONG lo = _parLong(pl,1) & 0xFFFF;
   LONG hi = _parLong(pl,2) & 0xFFFF;
   _retnl( pl , (LONG) MAKELONG(MAKELANGID( lo , hi), 0));
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_MAKELPARAM(XppParamList pl){ wapimc_MAKELONG(pl); }
XPPRET XPPENTRY wapimc_MAKELRESULT(XppParamList pl){ wapimc_MAKELONG(pl); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_GET_X_LPARAM(XppParamList pl){ wapimc_LOWORD(pl); }
XPPRET XPPENTRY wapimc_GET_Y_LPARAM(XppParamList pl){ wapimc_HIWORD(pl); }
//----------------------------------------------------------------------------------------------------------------------
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
XPPRET XPPENTRY PACKFLOAT32( XppParamList pl ) // PackFloat32( nNum ) -> nPacked
{
   FLOAT  nf = (FLOAT) _parnd(pl,1);
   _stornl(((LONG*) ((void*) &nf))[0],pl,1,0);
   _retnl(pl,((LONG*) ((void*) &nf))[0]);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY UNPACKFLOAT32( XppParamList pl ) // UnPackFloat32( nPacked ) -> nNum
{
   LONG n    = _parLong(pl,1);
   _stornd((double) (((FLOAT*) ((void*) &n))[0]) , pl,1,0 );
   _retnd(pl,(double) (((FLOAT*) ((void*) &n))[0])  );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_MAKEBYTE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) | ((_parLong(pl,2) & 0x0F)<<4) );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_LONIBBLE(XppParamList pl)
{
   _retnl(pl, (_parLong(pl,1) & 0x0F) );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapimc_HINIBBLE(XppParamList pl)
{
   _retnl(pl, ((_parLong(pl,1) & 0xF0)>> 4) );
}
// -----------------------------------------------------------------------------------------------------------------
// ot4xb_parse_number( str ) -> nNumber
// TODO: extended syntax (build: 1,6,0,????):
// ot4xb_parse_number( str , nMode = 0, nBase = 10 , nFormat = 0 ) -> cnNumber | NIL
// nMode: 
//          0 - DEFAULT - if have a decimal point or LONG overflow parsed as double otherwise LONG // only base 10
//         -1 - double   // only base 10
//          7 - signed   __int8
//          8 - unsigned __int8
//         15 - signed   __int16
//         16 - unsigned __int16
//         15 - signed   __int16
//         16 - unsigned __int16
//         31 - signed   __int32
//         32 - unsigned __int32
//         63 - signed   __int64
//         64 - unsigned __int64
// nBase:   2 to 36
//         10 - DEFAULT 
//          0 - Prefix 0x -> Hex , Prefix 0-> Octal , else decimal
// nFormat:
//          0 - DEFAULT - Xbase++ numeric ( int64 converted to LONG or double )
//          1 - binary -> 1,2,4,8 byte string
//          2 - integer or NIL if not representable
//          4 - double

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
