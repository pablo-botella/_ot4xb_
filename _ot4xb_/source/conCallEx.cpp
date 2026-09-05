//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// internal: not documented
BOOL   _conRelease_ret_BOOL( ContainerHandle con )
{
   BOOL result = FALSE;
   _conGetL( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
// internal: not documented
LONG   _conRelease_ret_LONG( ContainerHandle con )
{
   LONG result = 0;
   _conGetLong( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
// internal: not documented
double _conRelease_ret_double( ContainerHandle con )
{
   double result = FALSE;
   _conGetND( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
// internal: not documented
FLOAT  _conRelease_ret_FLOAT( ContainerHandle con ){ return (FLOAT) _conRelease_ret_double(con); }
//----------------------------------------------------------------------------------------------------------------------
// internal: not documented
LPSTR  _conRelease_ret_LPSTR( ContainerHandle con )
{
   LPSTR result = _conXStrDup( con );
   _conRelease(con);
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallConR(LPSTR,...)
            | _tg_: _conCallConR
            | syntax_: `ContainerHandle _conCallConR( LPSTR pFN, ... )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallConR@@YAPAUMomHandleEntry@@PADZZ
            | _kw_: call function by name, container result, variadic containers, C to Xbase++ call, variadic
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with a variable list of container parameters, terminated by NULLCONTAINER, and
      returns its result in a new container; release it with _conRelease. Takes ownership of the containers passed (the
      R suffix): they are all released before returning, so the caller must not use or release them afterwards. To keep
      ownership of the parameters, use _conCallCon instead.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `...` ContainerHandle - The parameters, one container each, in order, terminated by NULLCONTAINER.

    Returns ContainerHandle - New container with the result; release it with _conRelease.

    |seealso: See also: _conCallCon }}*/
OT4XB_API ContainerHandle _conCallConR( LPSTR pFN , ... )
{
   va_list va;
   ContainerHandle conr   = _conNew( NULLCONTAINER);
   TContainerHandleList p;
   va_start(va,pFN);
   while( p.Add( (ContainerHandle) va_arg(va,ContainerHandle)) ) ;
   _conCallPa(conr,pFN,p.m_nCount -1 , p.m_pItems );
   p.ReleaseAll();
   return conr;                          
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// C++ Only
// Specialiced forms of _conCall()
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PAD@Z
            | _kw_: call function by name, container result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN )
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conCall( conr , pFN, 0);
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,BOOL)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADH@Z
            | _kw_: call function by name, container result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , BOOL   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LONG)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADJ@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADJPAU1@@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN,2,conv,con);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADJPAU1@1@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con ,  ContainerHandle con2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN,3,conv,con,con2);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,ContainerHandle)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADPAU1@@Z
            | _kw_: call function by name, container result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conCall( conr , pFN,1,con);
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,DWORD)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADK@Z
            | _kw_: call function by name, container result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , DWORD  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LONG,LONG)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LONG val1, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADJJ@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val1 , LONG   val2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   _conCall( conr , pFN,2,conv1,conv2);
   _conReleaseM( conv1 , conv2 , 0 );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LONG,LONG,LONG)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LONG val1, LONG val2, LONG val3 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADJJJ@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val3` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN, LONG   val1, LONG   val2 , LONG val3)
{
	ContainerHandle conr = _conNew( NULLCONTAINER );
	ContainerHandle conv1 = _conPutNL( NULLCONTAINER, (LONG) val1 );
	ContainerHandle conv2 = _conPutNL( NULLCONTAINER, (LONG) val2 );
	ContainerHandle conv3 = _conPutNL( NULLCONTAINER, (LONG) val3 );
	_conCall( conr, pFN, 3, conv1, conv2 , conv3);
	_conReleaseM( conv1, conv2, conv3 , 0 );
	return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,double)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PADN@Z
            | _kw_: call function by name, container result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , double val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LPSTR)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PAD0@Z
            | _kw_: call function by name, container result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallCon(LPSTR,LPSTR,LONG)
            | _tg_: _conCallCon
            | syntax_: `ContainerHandle _conCallCon( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallCon@@YAPAUMomHandleEntry@@PAD0J@Z
            | _kw_: call function by name, container result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result in a new container; release it
      with _conRelease.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the function (NIL when it returns nothing); release it
      with _conRelease. }}*/
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  pStr , LONG val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN, 2,conc,conn);
   _conReleaseM( conc,conn,0 );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPAD@Z
            | _kw_: call function by name, no result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN )
{
   _conRelease( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,BOOL)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADH@Z
            | _kw_: call function by name, no result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , BOOL val)
{
   _conRelease( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LONG)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADJ@Z
            | _kw_: call function by name, no result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val)
{
   _conRelease( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LONG,LONG)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADJJ@Z
            | _kw_: call function by name, no result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val , LONG val2)
{
   _conRelease( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, no result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con)
{
   _conRelease( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, no result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con,ContainerHandle con2)
{
   _conRelease( _conCallCon(pFN,val,con,con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,ContainerHandle)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, no result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , ContainerHandle con)
{
   _conRelease( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,DWORD)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADK@Z
            | _kw_: call function by name, no result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , DWORD val)
{
   _conRelease( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,double)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPADN@Z
            | _kw_: call function by name, no result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , double val)
{
   _conRelease( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LPSTR)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPAD0@Z
            | _kw_: call function by name, no result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR val)
{
   _conRelease( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallVoid(LPSTR,LPSTR,LONG)
            | _tg_: _conCallVoid
            | syntax_: `void _conCallVoid( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallVoid@@YAXPAD0J@Z
            | _kw_: call function by name, no result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and discards the result.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR pStr , LONG val)
{
   _conRelease( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPAD@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN )
{
   return _conRelease_ret_BOOL( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,BOOL)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADH@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LONG)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADJ@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LONG,LONG)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADJJ@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2 )
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,con,con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,ContainerHandle)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,DWORD)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADK@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,double)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPADN@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , double val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LPSTR)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPAD0@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallBool(LPSTR,LPSTR,LONG)
            | _tg_: _conCallBool
            | syntax_: `BOOL _conCallBool( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallBool@@YAHPAD0J@Z
            | _kw_: call function by name, BOOL result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a BOOL (FALSE
      when the result is not a logical value).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPAD@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN )
{
   return _conRelease_ret_LONG( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,BOOL)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADH@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LONG)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADJ@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LONG,LONG)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADJJ@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,con, con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,ContainerHandle)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,DWORD)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADK@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,double)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPADN@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , double val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LPSTR)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPAD0@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLong(LPSTR,LPSTR,LONG)
            | _tg_: _conCallLong
            | syntax_: `LONG _conCallLong( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLong@@YAJPAD0J@Z
            | _kw_: call function by name, LONG result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPAD@Z
            | _kw_: call function by name, double result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN )
{
   return _conRelease_ret_double( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,BOOL)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADH@Z
            | _kw_: call function by name, double result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val)   );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LONG)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADJ@Z
            | _kw_: call function by name, double result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LONG,LONG)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADJJ@Z
            | _kw_: call function by name, double result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, double result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, double result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,con,con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,ContainerHandle)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, double result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_double( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,DWORD)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADK@Z
            | _kw_: call function by name, double result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,double)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPADN@Z
            | _kw_: call function by name, double result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , double val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LPSTR)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPAD0@Z
            | _kw_: call function by name, double result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallDouble(LPSTR,LPSTR,LONG)
            | _tg_: _conCallDouble
            | syntax_: `double _conCallDouble( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallDouble@@YANPAD0J@Z
            | _kw_: call function by name, double result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPAD@Z
            | _kw_: call function by name, float result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN )
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,BOOL)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADH@Z
            | _kw_: call function by name, float result, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LONG)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADJ@Z
            | _kw_: call function by name, float result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LONG,LONG)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADJJ@Z
            | _kw_: call function by name, float result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, float result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, float result, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,con,con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,ContainerHandle)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, float result, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,DWORD)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADK@Z
            | _kw_: call function by name, float result, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,double)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPADN@Z
            | _kw_: call function by name, float result, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , double val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LPSTR)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPAD0@Z
            | _kw_: call function by name, float result, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallFloat(LPSTR,LPSTR,LONG)
            | _tg_: _conCallFloat
            | syntax_: `FLOAT _conCallFloat( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallFloat@@YAMPAD0J@Z
            | _kw_: call function by name, float result, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPAD@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN )
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,BOOL)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADH@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, logical parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LONG)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADJ@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LONG,LONG)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADJJ@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LONG,LONG,LONG)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LONG val, LONG val2, LONG val3 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADJJJ@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val3` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN, LONG val, LONG val2 , LONG val3 )
{
	return _conRelease_ret_LPSTR( _conCallCon( pFN, val, val2 , val3) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LONG,ContainerHandle)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADJPAUMomHandleEntry@@@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,con) );
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LONG,ContainerHandle,ContainerHandle)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LONG val, ContainerHandle con, ContainerHandle con2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADJPAUMomHandleEntry@@1@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.
    - `con2` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,con,con2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,ContainerHandle)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADPAUMomHandleEntry@@@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, container parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,DWORD)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADK@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, DWORD parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,double)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPADN@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, double parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , double val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LPSTR)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPAD0@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conCallLpstr(LPSTR,LPSTR,LONG)
            | _tg_: _conCallLpstr
            | syntax_: `LPSTR _conCallLpstr( LPSTR pFN, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conCallLpstr@@YAPADPAD0J@Z
            | _kw_: call function by name, string result, xgrab, C to Xbase++ call, numeric parameter
   }}*/
/*{{|desc: Calls the Xbase++ function pFN with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `pFN` LPSTR - Name of the Xbase++ function to call (pFunctionName).
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------

