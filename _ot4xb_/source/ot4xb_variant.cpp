
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <stdio.h>
#include <shlwapi.h>
#include <comutil.h>
#include <Exdisp.h>
#include <Mshtml.h>
#include <msxml2.h>
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPVOID OT4XB_API _variant_t_GetIUnknow(_variant_t* pv)
{
   if( V_VT(pv) == VT_UNKNOWN ) return (void*) V_UNKNOWN(pv);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPBYTE OT4XB_API _variant_t_VT_UI1Array2Str(_variant_t* pv , UINT* pcb)
{
   UINT     cb = 0;
   LPBYTE   p  = 0;

   if( V_VT(pv) == (VT_ARRAY | VT_UI1))
   {
      SAFEARRAY *pa = reinterpret_cast<SAFEARRAY*> V_BYREF(pv);
      if( pa )
      {
         LONG nl = 0;
         LONG nu = 0;
         UINT nd = SafeArrayGetDim(pa);
         if( nd > 0 )
         {
            BOOL bOk = (SafeArrayGetLBound(pa,nd,&nl) == S_OK );
            if( bOk ) bOk = (SafeArrayGetUBound(pa,nd,&nu) == S_OK );
            if( bOk ) bOk = (nl <= nu);
            if( bOk )
            {
               void* pp = 0;
               if( SafeArrayAccessData(pa,&pp) == S_OK )
               {
                  cb = (nu-nl)+1;
                  p  = _bdup((LPBYTE)pp,cb);
                  SafeArrayUnaccessData(pa);
               }
            }
         }
      }
   }
   if( pcb ) *pcb = cb;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_SetStrAsUI1Array( _variant_t* pv , LPSTR pStr , int cb )
{
   _variant_t_Clear( pv );
   if( pStr )
   {
      LPSAFEARRAY psa;
      if( cb == -1 ){ cb = lstrlen(pStr);}
      psa = SafeArrayCreateVector(VT_UI1, 0, (ULONG) cb );
      VariantInit(pv);
      if(psa)
      {
         LPBYTE p = 0;
         SafeArrayAccessData(psa,(void**)&p);
         _bcopy(p,(LPBYTE)pStr,cb);
         SafeArrayUnaccessData(psa);
         V_VT(pv) = VT_ARRAY | VT_UI1;
         V_ARRAY(pv) = psa;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BSTR OT4XB_API str2bstr(LPSTR p , int cb)
{
   BSTR  pb = (BSTR) 0;
   if( cb == -1 ){ cb = lstrlen(p);}
   pb = SysAllocStringByteLen( 0 , (UINT) (cb * 2) );
   if(p && cb){ MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,p,cb,(LPWSTR)pb,cb);}
   return pb;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" LONG OT4XB_API _variant_t_Get_Type(_variant_t* pv)
{
   return MAKELONG( V_VT(pv) , 0 );
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_SetString(_variant_t* pv , LPSTR p)
{
   _variant_t_Clear( pv );
   VariantInit(pv);
   V_VT(pv)   = VT_BSTR;
   V_BSTR(pv) = str2bstr(p,-1);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPSTR OT4XB_API _variant_t_GetString(_variant_t* pv , UINT* pcb )
{
   if( V_VT(pv) == (VT_ARRAY | VT_UI1)){return (LPSTR) _variant_t_VT_UI1Array2Str(pv,pcb);}
   if( V_VT(pv) == VT_BSTR )
   {
      return w2utf8( (LPWSTR) V_BSTR(pv), (int) SysStringLen( V_BSTR(pv) ) ,(int*) pcb);
   }
   if( pcb ) pcb = 0;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Clear(_variant_t* pv)
{
   __try
   {
      __try
      {
         if( V_VT(pv) == VT_BSTR )
         {
            if( V_BSTR(pv) )
            {
               SysFreeString( V_BSTR(pv) );
               V_BSTR(pv) = 0;
            }
         }
      }
      __finally
      {
         pv->Clear();
      }
   }
   __except(1)
   {
      _bset((LPBYTE)pv,0,sizeof(variant_t));

   }
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_Missing(_variant_t* pv)
{
   _variant_t_Clear( pv );
   V_VT(pv)    = VT_ERROR;
   V_ERROR(pv) = DISP_E_PARAMNOTFOUND;
}
// -----------------------------------------------------------------------------------------------------------------

extern "C" void OT4XB_API _variant_t_Set_I2(_variant_t* pv, short n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I2;
   V_I2(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_UI2(_variant_t* pv, WORD n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI2;
   V_UI2(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_BOOL(_variant_t* pv, BOOL b)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_BOOL;
   V_BOOL(pv) = (b ? VARIANT_TRUE : VARIANT_FALSE);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API _variant_t_Get_BOOL(_variant_t* pv, BOOL* pVal )
{
   if( !pVal ) return FALSE;
   if( V_VT(pv) != VT_BOOL ) return FALSE;
   pVal[0] = (BOOL) (V_BOOL(pv) == VARIANT_TRUE);
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_I4(_variant_t* pv, LONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I4;
   V_I4(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API _variant_t_Get_I4(_variant_t* pv, LONG* pn)
{
   if( V_VT(pv) == VT_I4 ){ pn[0] = V_I4(pv); return TRUE;}
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_UI4(_variant_t* pv, DWORD n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI4;
   V_UI4(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API _variant_t_Get_UI4(_variant_t* pv, DWORD* pn)
{
   if( V_VT(pv) == VT_UI4 ){ pn[0] = V_UI4(pv); return TRUE;}
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_INT(_variant_t* pv, int n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_INT;
   V_INT(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_UINT(_variant_t* pv, UINT n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UINT;
   V_UINT(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" BOOL OT4XB_API _variant_t_Get_Int32(_variant_t* pv, LONG* pn)
{
   switch( V_VT(pv) )
   {
      case VT_I1:
      {
         LONG nn = (LONG) V_I1(pv);
         if( nn & 0x80 ) nn |= 0xFFFFFF00L;
         pn[0] = nn;
         return TRUE;
      }
      case VT_UI1:
      {
         LONG nn = (LONG) V_UI1(pv);
         pn[0] = (nn & 0x000000FFL);
         return TRUE;
      }
      case VT_I2:
      {
         LONG nn = (LONG) V_I2(pv);
         if( nn & 0x8000 ) nn |= 0xFFFF0000L;
         pn[0] = nn;
         return TRUE;
      }
      case VT_UI2:
      {
         LONG nn = (LONG) V_UI2(pv);
         pn[0] = (nn & 0x0000FFFFL);
         return TRUE;
      }
      case VT_I4:
      {
         pn[0] = V_I4(pv);
         return TRUE;
      }
      case VT_UI4:
      {
         pn[0] = (LONG) V_UI4(pv);
         return TRUE;
      }
      case VT_INT:
      {
         pn[0] = (LONG) V_INT(pv);
         return TRUE;
      }
      case VT_UINT:
      {
         pn[0] = (LONG) V_UINT(pv);
         return TRUE;
      }
      case VT_BOOL:
      {
         pn[0] = ( (V_BOOL(pv) == VARIANT_TRUE) ? 1 : 0 );
         return TRUE;
      }
   }
   pn[0] = 0;
   return FALSE;
}

// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_R4(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_R4;
   V_R4(pv) = (float) n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_R8(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_R8;
   V_R8(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_DATE(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv)   = VT_DATE;
   V_DATE(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_IUnknow(_variant_t* pv,IUnknown* p, BOOL bAddRef)
{
   _variant_t_Clear( pv );
   V_VT(pv)   = VT_UNKNOWN;
   V_UNKNOWN(pv) = p;
   if( bAddRef && p ) p->AddRef();
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_UI1(_variant_t* pv, BYTE n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI1;
   V_UI1(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_I1(_variant_t* pv, char n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I1;
   V_I1(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_I8(_variant_t* pv, LONGLONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I8;
   V_I8(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_UI8(_variant_t* pv, ULONGLONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI8;
   V_UI8(pv) = n;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API _variant_t_Set_LPITEMIDLIST(_variant_t* pv,LPITEMIDLIST p )
{
   if( p )
   {
      int cb = sizeof(p->mkid.cb);
      while( p->mkid.cb ){ cb += (int) (p->mkid.cb); p = _mk_ptr_( LPITEMIDLIST , p , p->mkid.cb );}
      _variant_t_SetStrAsUI1Array(pv,(LPSTR) p, cb );
   }
   else { _variant_t_Clear( pv );}
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" ContainerHandle OT4XB_API simple_variant_t_2_con(_variant_t* pv)
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   switch( pv->vt )
   {
      case VT_R8:
      {
         _conPutND(con,V_R8(pv));
         break;
      }
      case VT_R4:
      {
         _conPutND(con,( double) V_R4(pv));
         break;
      }
      case VT_I1:
      {
         _conPutNL(con, (LONG) V_I1(pv) );
         break;
      }
      case VT_I2:
      {
         _conPutNL(con, (LONG) V_I2(pv) );
         break;
      }
      case VT_I4:
      {
         _conPutNL(con, (LONG) V_I4(pv) );
         break;
      }
      case VT_UI1:
      {
         DWORD dw = (DWORD) V_UI1(pv) & 0xFF;
         _conPutNL(con, (LONG) dw);
         break;
      }
      case VT_UI2:
      {
         DWORD dw = (DWORD) V_UI2(pv) & 0xFFFF;
         _conPutNL(con, (LONG) dw);
         break;
      }
      case VT_UI4:
      {
         DWORD dw = (DWORD) V_UI4(pv);
         if( ((int) dw) < 0 )
         {
            _conPutND(con,(double) dw );
         }
         else
         {
            _conPutNL(con, (LONG) dw);
         }
         break;
      }
      case (VT_ARRAY | VT_UI1):
      {
         UINT  cb = 0;
         LPSTR p  = (LPSTR) _variant_t_VT_UI1Array2Str(pv,&cb);
         if( p )
         {
            _conPutCL(con,p,cb);
            _xfree((void*) p);
         }
         else
         {
            _conPutC(con,"");
         }
         break;
      }
      case VT_BSTR:
      {
         UINT  cb = 0;
         LPSTR p  = w2ansi( (LPWSTR) V_BSTR(pv),(int) SysStringLen( V_BSTR(pv) ) , (int*) &cb );
         if( p )
         {
            _conPutCL(con,p,cb);
            _xfree((void*) p);
         }
         else
         {
            _conPutC(con,"");
         }
         break;
      }
      case VT_BOOL:
      {
         _conPutL(con, ( V_BOOL(pv) ? 1 : 0 ) );
         break;
      }
      case VT_CY:
      {
         double nd = 0.00;
         VarR8FromCy( V_CY(pv) , &nd);
         _conPutND(con,nd);
         break;
      }
      case VT_DECIMAL:
      {
         double nd = 0.00;
         VarR8FromDec( &V_DECIMAL(pv) , &nd);
         _conPutND(con,nd);
         break;
      }
      case VT_DATE:
      {
         SYSTEMTIME st;
         if( VariantTimeToSystemTime(V_DATE(pv),&st) )
         {
            char sz[32]; ZeroMemory(sz,sizeof(sz));
            wsprintf(sz,"%04.4i%02.2i%02.2i", MAKELONG(st.wYear,0),MAKELONG(st.wMonth,0),MAKELONG(st.wDay,0));
            _conPutDS(con,sz);
         }
         else
         {
            _conPutDS(con,"");
         }
         break;
      }
   }
   return con;
}
//----------------------------------------------------------------------------------------------------------------------
//--------- http://support.microsoft.com/kb/186122/EN-US
// -----------------------------------------------------------------------------------------------------------------
extern "C" ContainerHandle OT4XB_API _variant_t_VT_ARRAY_2d2con(_variant_t* pv)
{
   ContainerHandle cona = NULLCONTAINER;
   if( V_VT(pv) & VT_ARRAY )
   {
      SAFEARRAY *pa = reinterpret_cast<SAFEARRAY*> V_BYREF(pv);
      if( pa )
      {
         UINT nd = SafeArrayGetDim(pa);
         if( nd == 2 )
         {
            variant_t v;
            LONG nRows = 0; SafeArrayGetUBound(pa,1,&nRows);
            LONG nCols = 0; SafeArrayGetUBound(pa,2,&nCols);
            LONG nRow,nCol;
            cona = _conNewArray(2,nRows,nCols,0);
            for( nRow = 1 ; nRow <= nRows; nRow++ )
            {
               for( nCol = 1 ; nCol <= nCols; nCol++ )
               {
                  LONG rci[2]; rci[0] = nRow; rci[1] = nCol;
                  SafeArrayGetElement(pa,rci,&v);
                  ContainerHandle con = simple_variant_t_2_con(&v);
                  if( con )
                  {
                     _conArrayPut(cona,con,nRow,nCol,0);
                     _conRelease(con);
                     con = NULLCONTAINER;
                  }
               }
            }
         }
      }
   }
   return cona;
}
// -------------------------------------------------------------------------------------------------------------------------------------------------------
extern "C" HRESULT OT4XB_API 
_ot4xb_VariantChangeType(__out VARIANTARG * pvargDest, __in const VARIANTARG * pvarSrc, __in USHORT wFlags, __in VARTYPE vt)
{
	DWORD locale = ot4xb_get_tls_variant_to_string_locale();
	if (locale)
	{
		return VariantChangeTypeEx(pvargDest, pvarSrc, locale, wFlags, vt);
	}
	return VariantChangeType(pvargDest, pvarSrc, wFlags, vt);
}
// -------------------------------------------------------------------------------------------------------------------------------------------------------
