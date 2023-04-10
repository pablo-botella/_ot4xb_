//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
BOOL   _conRelease_ret_BOOL( ContainerHandle con )
{
   BOOL result = FALSE;
   _conGetL( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
LONG   _conRelease_ret_LONG( ContainerHandle con )
{
   LONG result = 0;
   _conGetLong( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
double _conRelease_ret_double( ContainerHandle con )
{
   double result = FALSE;
   _conGetND( con , &result );
   _conRelease(con);
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
FLOAT  _conRelease_ret_FLOAT( ContainerHandle con ){ return (FLOAT) _conRelease_ret_double(con); }
//----------------------------------------------------------------------------------------------------------------------
LPSTR  _conRelease_ret_LPSTR( ContainerHandle con )
{
   LPSTR result = _conXStrDup( con );
   _conRelease(con);
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// C++ Only
// Specialiced forms of _conCall()
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN )
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conCall( conr , pFN, 0);
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , BOOL   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN,2,conv,con);
   _conRelease( conv );
   return conr;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val, ContainerHandle con ,  ContainerHandle con2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN,3,conv,con,con2);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , ContainerHandle con)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   _conCall( conr , pFN,1,con);
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , DWORD  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LONG   val1 , LONG   val2)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   _conCall( conr , pFN,2,conv1,conv2);
   _conReleaseM( conv1 , conv2 , 0 );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , double val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   _conCall( conr , pFN, 1,conv);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCallCon( LPSTR pFN , LPSTR  pStr , LONG val)
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   _conCall( conr , pFN, 2,conc,conn);
   _conReleaseM( conc,conn,0 );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN )
{
   _conRelease( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , BOOL val)
{
   _conRelease( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val)
{
   _conRelease( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val , LONG val2)
{
   _conRelease( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con)
{
   _conRelease( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LONG val, ContainerHandle con,ContainerHandle con2)
{
   _conRelease( _conCallCon(pFN,val,con,con2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , ContainerHandle con)
{
   _conRelease( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , DWORD val)
{
   _conRelease( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , double val)
{
   _conRelease( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR val)
{
   _conRelease( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conCallVoid( LPSTR pFN , LPSTR pStr , LONG val)
{
   _conRelease( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN )
{
   return _conRelease_ret_BOOL( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2 )
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val,con,con2) );
}

//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , double val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCallBool( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN )
{
   return _conRelease_ret_LONG( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val,con, con2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , double val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conCallLong( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN )
{
   return _conRelease_ret_double( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val)   );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_double( _conCallCon(pFN,val,con,con2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_double( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , double val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_double( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conCallDouble( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN )
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val,con,con2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , double val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conCallFloat( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN )
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , BOOL val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN, LONG val, LONG val2 , LONG val3 )
{
	return _conRelease_ret_LPSTR( _conCallCon( pFN, val, val2 , val3) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,con) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LONG val, ContainerHandle con, ContainerHandle con2)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val,con,con2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , DWORD val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , double val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conCallLpstr( LPSTR pFN , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conCallCon(pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------

