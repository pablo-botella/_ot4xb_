
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
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_GetIUnknow
            | syntax_: `LPVOID _variant_t_GetIUnknow( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_GetIUnknow
            | _kw_: variant, VT_UNKNOWN, interface pointer, COM
   }}*/
/*{{|desc: Returns the interface pointer held by a VT_UNKNOWN variant.
    | params:
    - `pv` _variant_t * - Variant to inspect.

    Returns LPVOID - The IUnknown pointer, or NULL when the variant is not VT_UNKNOWN. AddRef is not
      called; the variant keeps ownership of its reference. }}*/
extern "C" LPVOID OT4XB_API _variant_t_GetIUnknow(_variant_t* pv)
{
   if( V_VT(pv) == VT_UNKNOWN ) return (void*) V_UNKNOWN(pv);
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_VT_UI1Array2Str
            | syntax_: `LPBYTE _variant_t_VT_UI1Array2Str( _variant_t * pv, UINT * pcb )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_VT_UI1Array2Str
            | _kw_: variant, byte array, safearray, VT_UI1, to buffer
   }}*/
/*{{|desc: Copies the bytes of a VT_UI1 safearray variant into a newly allocated buffer. On an array
      with several dimensions only the extent of the last dimension is copied.
    | params:
    - `pv` _variant_t * - Variant expected to hold a byte array (VT_UI1 safearray).
    - `pcb` UINT * - Receives the number of bytes copied, 0 on failure. May be NULL.

    Returns LPBYTE - Allocated copy of the bytes; NULL when the variant holds no byte array or the array
      is empty. Free it with _xfree(). }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_SetStrAsUI1Array
            | syntax_: `void _variant_t_SetStrAsUI1Array( _variant_t * pv, LPSTR pStr, int cb )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_SetStrAsUI1Array
            | _kw_: variant, byte array, safearray, VT_UI1, from buffer
   }}*/
/*{{|desc: Loads the variant with a copy of a byte buffer, stored as a VT_UI1 safearray (byte array).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `pStr` LPSTR - Source bytes. When NULL the variant is just cleared (VT_EMPTY).
    - `cb` int - Number of bytes to copy, or -1 to use the zero-terminated length of pStr.

    Returns void }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: str2bstr
            | syntax_: `BSTR str2bstr( LPSTR p, int cb )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: str2bstr
            | _kw_: BSTR, ANSI to BSTR, SysAllocString, COM string
   }}*/
/*{{|desc: Converts an ANSI string into a newly allocated BSTR using the system ANSI code page.
    | params:
    - `p` LPSTR - Source ANSI text.
    - `cb` int - Number of bytes to convert, or -1 to use the zero-terminated length of p.

    Returns BSTR - Allocated wide string. Release it with SysFreeString(). }}*/
extern "C" BSTR OT4XB_API str2bstr(LPSTR p , int cb)
{
   BSTR  pb = (BSTR) 0;
   if( cb == -1 ){ cb = lstrlen(p);}
   pb = SysAllocStringByteLen( 0 , (UINT) (cb * 2) );
   if(p && cb){ MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,p,cb,(LPWSTR)pb,cb);}
   return pb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Get_Type
            | syntax_: `LONG _variant_t_Get_Type( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Get_Type
            | _kw_: variant, VARTYPE, vt, type code
   }}*/
/*{{|desc: Returns the VARTYPE of the variant (its VT_xxxx type code).
    | params:
    - `pv` _variant_t * - Variant to inspect.

    Returns LONG - The VARTYPE value, zero-extended to 32 bits. }}*/
extern "C" LONG OT4XB_API _variant_t_Get_Type(_variant_t* pv)
{
   return MAKELONG( V_VT(pv) , 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_SetString
            | syntax_: `void _variant_t_SetString( _variant_t * pv, LPSTR p )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_SetString
            | _kw_: variant, VT_BSTR, set string, ANSI to BSTR
   }}*/
/*{{|desc: Loads the variant with an ANSI string converted to a BSTR (VT_BSTR). The conversion uses the
      system ANSI code page.
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `p` LPSTR - Zero-terminated ANSI text to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_SetString(_variant_t* pv , LPSTR p)
{
   _variant_t_Clear( pv );
   VariantInit(pv);
   V_VT(pv)   = VT_BSTR;
   V_BSTR(pv) = str2bstr(p,-1);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_GetString
            | syntax_: `LPSTR _variant_t_GetString( _variant_t * pv, UINT * pcb )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_GetString
            | _kw_: variant, get string, BSTR to ANSI, to text
   }}*/
/*{{|desc: Extracts the text of a variant into a newly allocated buffer. A VT_UI1 safearray is returned as
      its raw bytes; a VT_BSTR is converted to UTF-8.
    | params:
    - `pv` _variant_t * - Variant to read.
    - `pcb` UINT * - Receives the length in bytes, 0 when nothing is returned. May be NULL.

    Returns LPSTR - Allocated buffer; NULL when the variant holds neither a byte array nor a BSTR. Free
      it with _xfree(). }}*/
extern "C" LPSTR OT4XB_API _variant_t_GetString(_variant_t* pv , UINT* pcb )
{
   if( V_VT(pv) == (VT_ARRAY | VT_UI1)){return (LPSTR) _variant_t_VT_UI1Array2Str(pv,pcb);}
   if( V_VT(pv) == VT_BSTR )
   {
      return w2utf8( (LPWSTR) V_BSTR(pv), (int) SysStringLen( V_BSTR(pv) ) ,(int*) pcb);
   }
   if( pcb ) *pcb = 0;
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Clear
            | syntax_: `void _variant_t_Clear( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Clear
            | _kw_: variant, VariantClear, release, VT_EMPTY
   }}*/
/*{{|desc: Releases whatever the variant holds and leaves it empty (VT_EMPTY). Any exception raised while
      releasing is trapped; in that case the variant memory is simply zeroed.
    | params:
    - `pv` _variant_t * - Variant to clear.

    Returns void }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_Missing
            | syntax_: `void _variant_t_Set_Missing( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_Missing
            | _kw_: variant, missing parameter, optional, DISP_E_PARAMNOTFOUND
   }}*/
/*{{|desc: Loads the variant with the value COM uses for omitted optional parameters: VT_ERROR with
      error code DISP_E_PARAMNOTFOUND.
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_Missing(_variant_t* pv)
{
   _variant_t_Clear( pv );
   V_VT(pv)    = VT_ERROR;
   V_ERROR(pv) = DISP_E_PARAMNOTFOUND;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_I2
            | syntax_: `void _variant_t_Set_I2( _variant_t * pv, short n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_I2
            | _kw_: variant, VT_I2, short, 16-bit
   }}*/
/*{{|desc: Loads the variant with a 16 bit signed integer (VT_I2).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` short - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_I2(_variant_t* pv, short n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I2;
   V_I2(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_UI2
            | syntax_: `void _variant_t_Set_UI2( _variant_t * pv, WORD n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_UI2
            | _kw_: variant, VT_UI2, unsigned short, 16-bit
   }}*/
/*{{|desc: Loads the variant with a 16 bit unsigned integer (VT_UI2).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` WORD - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_UI2(_variant_t* pv, WORD n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI2;
   V_UI2(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_BOOL
            | syntax_: `void _variant_t_Set_BOOL( _variant_t * pv, BOOL b )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_BOOL
            | _kw_: variant, VT_BOOL, VARIANT_TRUE, logical
   }}*/
/*{{|desc: Loads the variant with a logical value (VT_BOOL).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `b` BOOL - Zero stores VARIANT_FALSE, any other value stores VARIANT_TRUE.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_BOOL(_variant_t* pv, BOOL b)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_BOOL;
   V_BOOL(pv) = (b ? VARIANT_TRUE : VARIANT_FALSE);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Get_BOOL
            | syntax_: `BOOL _variant_t_Get_BOOL( _variant_t * pv, BOOL * pVal )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Get_BOOL
            | _kw_: variant, VT_BOOL, read logical
   }}*/
/*{{|desc: Reads a VT_BOOL variant into a C BOOL.
    | params:
    - `pv` _variant_t * - Variant to read.
    - `pVal` BOOL * - Receives 1 when the variant value is exactly VARIANT_TRUE, else 0. When NULL
      the call just returns FALSE.

    Returns BOOL - TRUE when the value was read, FALSE when pVal is NULL or the variant is not VT_BOOL. }}*/
extern "C" BOOL OT4XB_API _variant_t_Get_BOOL(_variant_t* pv, BOOL* pVal )
{
   if( !pVal ) return FALSE;
   if( V_VT(pv) != VT_BOOL ) return FALSE;
   pVal[0] = (BOOL) (V_BOOL(pv) == VARIANT_TRUE);
   return TRUE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_I4
            | syntax_: `void _variant_t_Set_I4( _variant_t * pv, LONG n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_I4
            | _kw_: variant, VT_I4, long, 32-bit
   }}*/
/*{{|desc: Loads the variant with a 32 bit signed integer (VT_I4).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` LONG - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_I4(_variant_t* pv, LONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I4;
   V_I4(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Get_I4
            | syntax_: `BOOL _variant_t_Get_I4( _variant_t * pv, LONG * pn )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Get_I4
            | _kw_: variant, VT_I4, read long
   }}*/
/*{{|desc: Reads a VT_I4 variant into a LONG.
    | params:
    - `pv` _variant_t * - Variant to read.
    - `pn` LONG * - Receives the value. Must not be NULL. Left untouched when the call fails.

    Returns BOOL - TRUE when the variant is VT_I4, FALSE otherwise. }}*/
extern "C" BOOL OT4XB_API _variant_t_Get_I4(_variant_t* pv, LONG* pn)
{
   if( V_VT(pv) == VT_I4 ){ pn[0] = V_I4(pv); return TRUE;}
   return FALSE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_UI4
            | syntax_: `void _variant_t_Set_UI4( _variant_t * pv, DWORD n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_UI4
            | _kw_: variant, VT_UI4, unsigned long, DWORD
   }}*/
/*{{|desc: Loads the variant with a 32 bit unsigned integer (VT_UI4).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` DWORD - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_UI4(_variant_t* pv, DWORD n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI4;
   V_UI4(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Get_UI4
            | syntax_: `BOOL _variant_t_Get_UI4( _variant_t * pv, DWORD * pn )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Get_UI4
            | _kw_: variant, VT_UI4, read DWORD
   }}*/
/*{{|desc: Reads a VT_UI4 variant into a DWORD.
    | params:
    - `pv` _variant_t * - Variant to read.
    - `pn` DWORD * - Receives the value. Must not be NULL. Left untouched when the call fails.

    Returns BOOL - TRUE when the variant is VT_UI4, FALSE otherwise. }}*/
extern "C" BOOL OT4XB_API _variant_t_Get_UI4(_variant_t* pv, DWORD* pn)
{
   if( V_VT(pv) == VT_UI4 ){ pn[0] = V_UI4(pv); return TRUE;}
   return FALSE;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_INT
            | syntax_: `void _variant_t_Set_INT( _variant_t * pv, int n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_INT
            | _kw_: variant, VT_INT, integer
   }}*/
/*{{|desc: Loads the variant with a signed integer tagged as VT_INT.
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` int - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_INT(_variant_t* pv, int n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_INT;
   V_INT(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_UINT
            | syntax_: `void _variant_t_Set_UINT( _variant_t * pv, UINT n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_UINT
            | _kw_: variant, VT_UINT, unsigned integer
   }}*/
/*{{|desc: Loads the variant with an unsigned integer tagged as VT_UINT.
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` UINT - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_UINT(_variant_t* pv, UINT n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UINT;
   V_UINT(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Get_Int32
            | syntax_: `BOOL _variant_t_Get_Int32( _variant_t * pv, LONG * pn )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Get_Int32
            | _kw_: variant, read integer, any integer type, 32-bit
   }}*/
/*{{|desc: Reads any integer variant of 32 bits or less into a LONG. Handled types: VT_I1, VT_UI1, VT_I2,
      VT_UI2, VT_I4, VT_UI4, VT_INT, VT_UINT and VT_BOOL (stored as 1 or 0). Signed values are
      sign-extended, unsigned values are zero-extended; a VT_UI4 above 0x7FFFFFFF comes out negative.
    | params:
    - `pv` _variant_t * - Variant to read.
    - `pn` LONG * - Receives the value, 0 when the type is not handled. Must not be NULL.

    Returns BOOL - TRUE when the variant type was handled, FALSE otherwise. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_R4
            | syntax_: `void _variant_t_Set_R4( _variant_t * pv, double n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_R4
            | _kw_: variant, VT_R4, float, single
   }}*/
/*{{|desc: Loads the variant with a floating point value narrowed to single precision (VT_R4).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` double - Value to store; it is cast to float.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_R4(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_R4;
   V_R4(pv) = (float) n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_R8
            | syntax_: `void _variant_t_Set_R8( _variant_t * pv, double n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_R8
            | _kw_: variant, VT_R8, double
   }}*/
/*{{|desc: Loads the variant with a double precision floating point value (VT_R8).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` double - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_R8(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_R8;
   V_R8(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_DATE
            | syntax_: `void _variant_t_Set_DATE( _variant_t * pv, double n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_DATE
            | _kw_: variant, VT_DATE, OLE date, DATE
   }}*/
/*{{|desc: Loads the variant with an OLE Automation date (VT_DATE).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` double - OLE date serial: days since 1899-12-30, time of day in the fractional part.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_DATE(_variant_t* pv, double n)
{
   _variant_t_Clear( pv );
   V_VT(pv)   = VT_DATE;
   V_DATE(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_IUnknow
            | syntax_: `void _variant_t_Set_IUnknow( _variant_t * pv, IUnknown * p, BOOL bAddRef )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_IUnknow
            | _kw_: variant, VT_UNKNOWN, interface pointer, COM
   }}*/
/*{{|desc: Loads the variant with a COM interface pointer (VT_UNKNOWN).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `p` IUnknown * - Interface pointer to store. May be NULL.
    - `bAddRef` BOOL - When TRUE and p is not NULL, AddRef() is called on p.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_IUnknow(_variant_t* pv,IUnknown* p, BOOL bAddRef)
{
   _variant_t_Clear( pv );
   V_VT(pv)   = VT_UNKNOWN;
   V_UNKNOWN(pv) = p;
   if( bAddRef && p ) p->AddRef();
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_UI1
            | syntax_: `void _variant_t_Set_UI1( _variant_t * pv, BYTE n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_UI1
            | _kw_: variant, VT_UI1, byte
   }}*/
/*{{|desc: Loads the variant with an 8 bit unsigned integer (VT_UI1).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` BYTE - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_UI1(_variant_t* pv, BYTE n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI1;
   V_UI1(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_I1
            | syntax_: `void _variant_t_Set_I1( _variant_t * pv, char n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_I1
            | _kw_: variant, VT_I1, signed byte, char
   }}*/
/*{{|desc: Loads the variant with an 8 bit signed integer (VT_I1).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` char - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_I1(_variant_t* pv, char n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I1;
   V_I1(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_I8
            | syntax_: `void _variant_t_Set_I8( _variant_t * pv, LONGLONG n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_I8
            | _kw_: variant, VT_I8, int64, 64-bit
   }}*/
/*{{|desc: Loads the variant with a 64 bit signed integer (VT_I8).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` LONGLONG - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_I8(_variant_t* pv, LONGLONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_I8;
   V_I8(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_UI8
            | syntax_: `void _variant_t_Set_UI8( _variant_t * pv, ULONGLONG n )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_Set_UI8
            | _kw_: variant, VT_UI8, uint64, 64-bit
   }}*/
/*{{|desc: Loads the variant with a 64 bit unsigned integer (VT_UI8).
    | params:
    - `pv` _variant_t * - Destination variant. Its previous content is released.
    - `n` ULONGLONG - Value to store.

    Returns void }}*/
extern "C" void OT4XB_API _variant_t_Set_UI8(_variant_t* pv, ULONGLONG n)
{
   _variant_t_Clear( pv );
   V_VT(pv) = VT_UI8;
   V_UI8(pv) = n;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_Set_LPITEMIDLIST
            | syntax_: `void _variant_t_Set_LPITEMIDLIST( _variant_t * pv, LPITEMIDLIST p )`
            | category: c-api/variant
            | mangled-name: _variant_t_Set_LPITEMIDLIST
            | _kw_: variant, PIDL, ITEMIDLIST, shell item, blob
   }}*/
/*{{|desc: Stores a shell item id list in a variant as a binary blob: walks the SHITEMID chain up to its
      terminator (cb == 0) and copies the whole list, terminator included, into pv as a VT_UI1 safearray
      (_variant_t_SetStrAsUI1Array). A NULL p clears the variant.
    | params:
    - `pv` _variant_t * - Variant that receives the item id list.
    - `p` LPITEMIDLIST - Item id list to copy; NULL clears pv.

    Returns void }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: simple_variant_t_2_con
            | syntax_: `ContainerHandle simple_variant_t_2_con( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: simple_variant_t_2_con
            | _kw_: variant to container, variant to Xbase++, convert, COM value
   }}*/
/*{{|desc: Builds a new Xbase++ value container from a simple variant. Integer types up to 32 bits, float
      types, VT_CY and VT_DECIMAL become Numeric; VT_BSTR (converted to ANSI) and VT_UI1 safearrays
      become Character; VT_BOOL becomes Logical; VT_DATE becomes a Date and its time part is discarded.
      Any other type (VT_INT, VT_UINT, VT_I8 and VT_UI8 included) leaves the container NIL.
    | params:
    - `pv` _variant_t * - Variant to convert.

    Returns ContainerHandle - New container owned by the caller; release it with _conRelease(). }}*/
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//--------- http://support.microsoft.com/kb/186122/EN-US
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _variant_t_VT_ARRAY_2d2con
            | syntax_: `ContainerHandle _variant_t_VT_ARRAY_2d2con( _variant_t * pv )`
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _variant_t_VT_ARRAY_2d2con
            | _kw_: variant, safearray, 2d array, to Xbase++ array, Excel range
   }}*/
/*{{|desc: Converts a variant holding a two-dimensional safearray into a new two-dimensional Xbase++
      Array. Each element becomes Numeric, Character, Logical, Date or NIL according to its variant
      type. Source lower bounds are honored; the resulting Array is always indexed from 1.
    | params:
    - `pv` _variant_t * - Variant expected to hold a two-dimensional safearray.

    Returns ContainerHandle - New Array container owned by the caller (release it with _conRelease()),
      or NULLCONTAINER when the variant does not hold a two-dimensional safearray. }}*/
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
            LONG nRowL = 0; SafeArrayGetLBound(pa,1,&nRowL);
            LONG nRowU = 0; SafeArrayGetUBound(pa,1,&nRowU);
            LONG nColL = 0; SafeArrayGetLBound(pa,2,&nColL);
            LONG nColU = 0; SafeArrayGetUBound(pa,2,&nColU);
            LONG nRows = nRowU - nRowL + 1; // honor the real lower bound: ADO-style arrays are 0-based
            LONG nCols = nColU - nColL + 1;
            LONG nRow,nCol;
            cona = _conNewArray(2,nRows,nCols,0);
            for( nRow = 0 ; nRow < nRows; nRow++ )
            {
               for( nCol = 0 ; nCol < nCols; nCol++ )
               {
                  LONG rci[2]; rci[0] = nRowL + nRow; rci[1] = nColL + nCol;
                  v.Clear(); // SafeArrayGetElement does not clear the destination
                  SafeArrayGetElement(pa,rci,&v);
                  ContainerHandle con = simple_variant_t_2_con(&v);
                  if( con )
                  {
                     _conArrayPut(cona,con,nRow+1,nCol+1,0);
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
/*{{end-c-function}}*/
// -------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_VariantChangeType
            | syntax_: ```
                 HRESULT _ot4xb_VariantChangeType( VARIANTARG * pvargDest, const VARIANTARG * pvarSrc, USHORT wFlags,
                    VARTYPE vt )
              ```
            | category: c-api/variant
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_VariantChangeType
            | _kw_: variant, VariantChangeType, convert type, coerce
   }}*/
/*{{|desc: Converts a variant to the requested type. Same contract as the Win32 VariantChangeType(),
      but when the thread has a variant-to-string locale set (ot4xb_set_tls_variant_to_string_locale)
      the conversion is done with VariantChangeTypeEx() using that locale instead of the default one.
    | params:
    - `pvargDest` VARIANTARG * - Destination variant receiving the converted value.
    - `pvarSrc` const VARIANTARG * - Source variant to convert.
    - `wFlags` USHORT - VariantChangeType flags.
    - `vt` VARTYPE - Target type.

    Returns HRESULT - As returned by VariantChangeType/VariantChangeTypeEx. }}*/
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
/*{{end-c-function}}*/
// -------------------------------------------------------------------------------------------------------------------------------------------------------
