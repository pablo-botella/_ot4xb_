//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb )
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conEvalB( conr,conb,0);
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,BOOL)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@H@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , BOOL   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,LONG)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@J@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@J0@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val, ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb,2,conv,con);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@0@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conEvalB( conr , conb,1,con);
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,DWORD)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@K@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , DWORD  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, LONG val1, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@JJ@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val1` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val1 , LONG   val2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   _conEvalB( conr , conb,2,conv1,conv2);
   _conReleaseM( conv1 , conv2 , 0 );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,double)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@N@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , double val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,LPSTR)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@PAD@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalCon(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalCon
            | syntax_: `ContainerHandle _conEvalCon( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalCon@@YAPAUMomHandleEntry@@PAU1@PADJ@Z
            | _kw_: eval codeblock, container result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result in a new container;
      release it with _conRelease.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns ContainerHandle - New container with the result of the code block (NIL when it returns nothing);
      release it with _conRelease.

    |seealso: See also: {{ilink: <tg _conCallCon> _conCallCon}} }}*/
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  pStr , LONG val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 2,conc,conn);
   _conReleaseM( conc,conn,0 );
   return conr;
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb )
{
   _conRelease( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,BOOL)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , BOOL val)
{
   _conRelease( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,LONG)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val)
{
   _conRelease( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val , LONG val2)
{
   _conRelease( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val, ContainerHandle con)
{
   _conRelease( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , ContainerHandle con)
{
   _conRelease( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,DWORD)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , DWORD val)
{
   _conRelease( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,double)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , double val)
{
   _conRelease( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,LPSTR)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR val)
{
   _conRelease( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalVoid(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalVoid
            | syntax_: `void _conEvalVoid( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalVoid@@YAXPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, no result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and discards the result.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns void

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR pStr , LONG val)
{
   _conRelease( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb )
{
   return _conRelease_ret_BOOL( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,BOOL)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,LONG)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,DWORD)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,double)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , double val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,LPSTR)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalBool(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalBool
            | syntax_: `BOOL _conEvalBool( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalBool@@YAHPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, BOOL result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a BOOL (FALSE when
      the result is not a logical value).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns BOOL - The logical result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb )
{
   return _conRelease_ret_LONG( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,BOOL)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,LONG)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,DWORD)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,double)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , double val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,LPSTR)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLong(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalLong
            | syntax_: `LONG _conEvalLong( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLong@@YAJPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, LONG result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a LONG through
      _conGetLong, which keeps the 32-bit representation whatever numeric type came back (0 when the result is
      not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LONG - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb )
{
   return _conRelease_ret_double( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,BOOL)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val)   );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,LONG)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_double( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,DWORD)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,double)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , double val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,LPSTR)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalDouble(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalDouble
            | syntax_: `double _conEvalDouble( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalDouble@@YANPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, double result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a double (0 when
      the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns double - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb )
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,BOOL)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,LONG)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,DWORD)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,double)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , double val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,LPSTR)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalFloat(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalFloat
            | syntax_: `FLOAT _conEvalFloat( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalFloat@@YAMPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, float result, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its result as a FLOAT, the
      double result cast to float (0 when the result is not numeric).
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns FLOAT - The numeric result.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb )
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,BOOL)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, BOOL val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@H@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, logical parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` BOOL - Logical parameter (wrapped with _conPutL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,LONG)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@J@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,LONG,LONG)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, LONG val, LONG val2 )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@JJ@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `val2` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val,val2) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,LONG,ContainerHandle)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, LONG val, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@J0@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,ContainerHandle)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, ContainerHandle con )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@0@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `con` ContainerHandle - Container passed as it is; the caller keeps ownership.

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,con) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,DWORD)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, DWORD val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@K@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, DWORD parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` DWORD - Numeric parameter (wrapped with _conPutNL as LONG).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,double)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, double val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@N@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, double parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` double - Numeric parameter (wrapped with _conPutND).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , double val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,LPSTR)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, LPSTR val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@PAD@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, string parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `val` LPSTR - Character parameter (wrapped with _conPutC).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conEvalLpstr(ContainerHandle,LPSTR,LONG)
            | _tg_: _conEvalLpstr
            | syntax_: `LPSTR _conEvalLpstr( ContainerHandle conb, LPSTR pStr, LONG val )`
            | category: ot4xb-api
            | header: ot4xb_cpp_exported.h
            | mangled-name: ?_conEvalLpstr@@YAPADPAUMomHandleEntry@@PADJ@Z
            | _kw_: eval codeblock, string result, xgrab, C to Xbase++ eval, string parameter, numeric parameter
   }}*/
/*{{|desc: Evaluates the code block conb with the given parameters and returns its character result as a C
      string allocated with _xgrab (_conXStrDup); the caller releases it with _xfree.
    | params:
    - `conb` ContainerHandle - Container holding the code block to evaluate; the caller keeps ownership.
    - `pStr` LPSTR - Character parameter (wrapped with _conPutC).
    - `val` LONG - Numeric parameter (wrapped with _conPutNL).

    Returns LPSTR - Allocated copy of the character result; free it with _xfree.

    |seealso: See also: {{ilink: <tg _conEvalCon> _conEvalCon}} }}*/
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,pStr,val) );
}
/*{{end-cpp-function}}*/
//----------------------------------------------------------------------------------------------------------------------

