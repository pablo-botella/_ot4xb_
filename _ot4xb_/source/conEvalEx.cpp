//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb )
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conEvalB( conr,conb,0);
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , BOOL   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val, ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb,2,conv,con);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conEvalB( conr , conb,1,con);
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , DWORD  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LONG   val1 , LONG   val2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   _conEvalB( conr , conb,2,conv1,conv2);
   _conReleaseM( conv1 , conv2 , 0 );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , double val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   _conEvalB( conr , conb, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conEvalCon( ContainerHandle conb , LPSTR  pStr , LONG val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   _conEvalB( conr , conb, 2,conc,conn);
   _conReleaseM( conc,conn,0 );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb )
{
   _conRelease( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , BOOL val)
{
   _conRelease( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val)
{
   _conRelease( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val , LONG val2)
{
   _conRelease( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , LONG val, ContainerHandle con)
{
   _conRelease( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , ContainerHandle con)
{
   _conRelease( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , DWORD val)
{
   _conRelease( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , double val)
{
   _conRelease( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR val)
{
   _conRelease( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conEvalVoid( ContainerHandle conb , LPSTR pStr , LONG val)
{
   _conRelease( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb )
{
   return _conRelease_ret_BOOL( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , double val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conEvalBool( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb )
{
   return _conRelease_ret_LONG( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , double val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conEvalLong( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb )
{
   return _conRelease_ret_double( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val)   );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_double( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , double val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_double( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conEvalDouble( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb )
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , double val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conEvalFloat( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb )
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , BOOL val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , DWORD val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , double val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conEvalLpstr( ContainerHandle conb , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conEvalCon(conb,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------

