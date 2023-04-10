
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY NNOT(XppParamList pl)
{
   LONG nRet = (~(_parLongOrBool(pl,1)));
    _stornl(nRet,pl,1,0);
    _retnl(pl,nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/

XPPRET XPPENTRY NLSHIFT(XppParamList pl)
{
   DWORD nRet = (DWORD) _parLong(pl,1) << (DWORD) _parLong(pl,2);
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);    
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY NRSHIFT(XppParamList pl)
{
   DWORD nRet = (DWORD) _parLong(pl,1) >> (DWORD) _parLong(pl,2);
   _stornl((LONG) nRet,pl,1,0);
   _retnl(pl,(LONG) nRet);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
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
OT4XB_API DWORD _dw_bf_get_(DWORD dw,DWORD sh, DWORD cb)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((dw >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD _dw_bf_set_(DWORD dw,DWORD sh, DWORD cb , DWORD v)
{
   DWORD mask = 0;
   DWORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   dw &= ~(mask << sh);
   return (dw | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BYTE _b1_bf_get_(BYTE b,BYTE sh, BYTE cb)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((b >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BYTE _b1_bf_set_(BYTE b ,BYTE sh, BYTE cb , BYTE v)
{
   BYTE mask = 0;
   BYTE n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   b &= ~(mask << sh);
   return (b | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API WORD _w_bf_get_(WORD w,WORD sh, WORD cb)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   return ((w >> sh) & mask);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API WORD _w_bf_set_(WORD w ,WORD sh, WORD cb , WORD v)
{
   WORD mask = 0;
   WORD n,ns;
   for( n=0,ns=0; n < cb; n++,ns++ ) mask |= (1 << ns);
   w &= ~(mask << sh);
   return (w | (v << sh));
}
//----------------------------------------------------------------------------------------------------------------------
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





