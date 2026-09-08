//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallConN(LPSTR,ContainerHandle,ULONG,...)
            | _tg_: _conMCallConN
            | syntax_: `ContainerHandle _conMCallConN( LPSTR pFN, ContainerHandle Self, ULONG nParams, ... )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallConN@@YAPAUMomHandleEntry@@PADPAU1@KZZ
            | _kw_: _conMCallConN, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with nParams container parameters passed as a variable
      argument list and returns its result in a new container; release it with _conRelease. The parameter
      containers are not released: the caller keeps ownership (see _conMCallConNR).
    | params:
    - `pFN` LPSTR - Name of the method to call.
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `nParams` ULONG - Number of container parameters that follow.
    - `...` ContainerHandle - The nParams parameters, one container each, in order.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conMCallConNR> _conMCallConNR}} }}*/
OT4XB_API ContainerHandle _conMCallConN( LPSTR pFN , ContainerHandle Self , ULONG nParams , ... )
{
   va_list pa;       
   ContainerHandle conr   = _conNew( NULLCONTAINER);
   ContainerHandle * pcon = (ContainerHandle*) _xgrab( (nParams + 1 )* sizeof(ContainerHandle) );
   ULONG n;                     
   pcon[0] = Self;
   for( n = 1 , va_start(pa,nParams);n <= nParams; n++) pcon[n] = va_arg(pa,ContainerHandle);
   _conCallMethodPa( conr , pFN, nParams +1, pcon);
   _xfree( (void*) pcon);
   return conr;                          
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallConNR(LPSTR,ContainerHandle,ULONG,...)
            | _tg_: _conMCallConNR
            | syntax_: `ContainerHandle _conMCallConNR( LPSTR pFN, ContainerHandle Self, ULONG nParams, ... )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallConNR@@YAPAUMomHandleEntry@@PADPAU1@KZZ
            | _kw_: _conMCallConNR, Function
   }}*/
/*{{|desc: Like _conMCallConN, but releases the nParams parameter containers after the call (Self is never
      released): the caller hands them over. Returns the result in a new container; release it with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the method to call.
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `nParams` ULONG - Number of container parameters that follow.
    - `...` ContainerHandle - The nParams parameters, one container each, in order.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conMCallConN> _conMCallConN}} }}*/
OT4XB_API ContainerHandle _conMCallConNR( LPSTR pFN , ContainerHandle Self , ULONG nParams , ... )
{
   va_list pa;       
   ContainerHandle conr   = _conNew( NULLCONTAINER);
   ContainerHandle * pcon = (ContainerHandle*) _xgrab( (nParams + 1 )* sizeof(ContainerHandle) );
   ULONG n;                     
   pcon[0] = Self;
   for( n = 1 , va_start(pa,nParams);n <= nParams; n++)
   {
      pcon[n] = va_arg(pa,ContainerHandle);
   }
   _conCallMethodPa( conr , pFN, nParams + 1 , pcon);
   for( n = 1 ;n <= nParams; n++)
   {
       _conRelease( pcon[n] ); // Self not released
   }
   _xfree( (void*) pcon);
   return conr;                          
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PAD@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self ,LPSTR pFN)
{
   return _conMCallConN( pFN, Self, 0);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADH@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN,  BOOL   val)
{
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADJ@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LONG   val)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADJ0@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LONG   val, ContainerHandle con)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   ContainerHandle conr = _conMCallConN( pFN, Self,2,conv,con);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PAD0@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,ContainerHandle con)
{
   return _conMCallConN( pFN, Self,1,con);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADK@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,DWORD  val)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LONG val1, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADJJ@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG   val1 , LONG   val2)
{
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   return _conMCallConNR( pFN, Self,2,conv1,conv2);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LONG,LONG,LONG)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LONG val1, LONG val2, LONG val3 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADJJJ@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val3` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG   val1 , LONG   val2 , LONG val3)
{
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   ContainerHandle conv3 = _conPutNL( NULLCONTAINER , (LONG) val3);   
   return _conMCallConNR( pFN, Self,3,conv1,conv2,conv3);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADN@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , double val)
{
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PAD1@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LPSTR  val)
{
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LPSTR,LPSTR)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LPSTR p1, LPSTR p2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PAD11@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `p1` LPSTR - Character parameter (wrapped with _conPutC).
    - `p2` LPSTR - Character parameter (wrapped with _conPutC).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LPSTR  p1 , LPSTR p2)
{
   ContainerHandle conp1 = _conPutC( NULLCONTAINER , p1);
   ContainerHandle conp2 = _conPutC( NULLCONTAINER , p2);
   return _conMCallConNR( pFN, Self, 2,conp1,conp2);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PAD1J@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LPSTR  pStr , LONG val)
{
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 2,conc,conn);
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADJH@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG v1,BOOL v2)
{
   return _conMCallConNR( pFN, Self,2,_conPutNL(0,v1),_conPutL(0,v2));
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallCon(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallCon
            | syntax_: `ContainerHandle _conMCallCon( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallCon@@YAPAUMomHandleEntry@@PAU1@PADPAK@Z
            | _kw_: _conMCallCon, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result in a new
      container; release it with _conRelease.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns ContainerHandle - New container with the result of the method (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   ContainerHandle con  = _conPutNL(NULLCONTAINER , pDw[0]);
   ContainerHandle conr = _conMCallConN( pFN, Self,1, con );
   _conGetLong( con , (LONG*) pDw);
   _conRelease(con);
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  )
{
   _conRelease( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   _conRelease( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LONG,LONG,LONG)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2, LONG val3 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADJJJ@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val3` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
 OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2 , LONG val3)
{
   _conRelease( _conMCallCon(Self,pFN,val,val2,val3) );
} 
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   _conRelease( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   _conRelease( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , double val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LPSTR,LPSTR)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LPSTR p1, LPSTR p2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PAD11@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `p1` LPSTR - Character parameter (wrapped with _conPutC).
    - `p2` LPSTR - Character parameter (wrapped with _conPutC).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR p1 , LPSTR p2)
{
   _conRelease( _conMCallCon(Self,pFN,p1,p2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   _conRelease( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   _conRelease( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallVoid(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallVoid
            | syntax_: `void _conMCallVoid( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallVoid@@YAXPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallVoid, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and discards the result.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns void

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   _conRelease( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallBool(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallBool
            | syntax_: `BOOL _conMCallBool( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallBool@@YAHPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallBool, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a BOOL
      (FALSE when the result is not a logical value).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLong(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallLong
            | syntax_: `LONG _conMCallLong( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLong@@YAJPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallLong, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a LONG
      through _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the
      result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallDouble(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallDouble
            | syntax_: `double _conMCallDouble( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallDouble@@YANPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallDouble, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a double
      (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallFloat(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallFloat
            | syntax_: `FLOAT _conMCallFloat( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallFloat@@YAMPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallFloat, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its result as a FLOAT,
      the double result cast to float (0 when the result is not numeric).
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PAD@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,BOOL)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADH@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LONG)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADJ@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LONG,LONG)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADJJ@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LONG,LONG,LONG)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2, LONG val3 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADJJJ@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val3` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2, LONG val3 )
{
	return _conRelease_ret_LPSTR( _conMCallCon( Self, pFN, val, val2 , val3) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LONG,ContainerHandle)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADJ0@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,ContainerHandle)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PAD0@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,DWORD)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADK@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,double)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADN@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LPSTR)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PAD1@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LPSTR,LONG)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PAD1J@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,LONG,BOOL)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG v1, BOOL v2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADJH@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `v1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `v2` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,v1,v2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conMCallLpstr(ContainerHandle,LPSTR,ULONG*)
            | _tg_: _conMCallLpstr
            | syntax_: `LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, ULONG * pDw )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conMCallLpstr@@YAPADPAUMomHandleEntry@@PADPAK@Z
            | _kw_: _conMCallLpstr, Function
   }}*/
/*{{|desc: Calls the method pFN of the object Self with the given parameters and returns its character result
      as a C string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `Self` ContainerHandle - The object whose method is called; passed as it is, never released.
    - `pFN` LPSTR - Name of the method to call.
    - `pDw` ULONG * - Numeric parameter passed by reference: *pDw goes in as a LONG and, after the call,
      receives the value the method left in that parameter.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conMCallCon> _conMCallCon}} }}*/
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,pDw) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------




