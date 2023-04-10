//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self ,LPSTR pFN)
{
   return _conMCallConN( pFN, Self, 0);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN,  BOOL   val)
{
   ContainerHandle conv = _conPutL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LONG   val)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LONG   val, ContainerHandle con)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , val);
   ContainerHandle conr = _conMCallConN( pFN, Self,2,conv,con);
   _conRelease( conv );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,ContainerHandle con)
{
   return _conMCallConN( pFN, Self,1,con);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,DWORD  val)
{
   ContainerHandle conv = _conPutNL( NULLCONTAINER , (LONG) val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG   val1 , LONG   val2)
{
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   return _conMCallConNR( pFN, Self,2,conv1,conv2);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG   val1 , LONG   val2 , LONG val3)
{
   ContainerHandle conv1 = _conPutNL( NULLCONTAINER , (LONG) val1);
   ContainerHandle conv2 = _conPutNL( NULLCONTAINER , (LONG) val2);
   ContainerHandle conv3 = _conPutNL( NULLCONTAINER , (LONG) val3);   
   return _conMCallConNR( pFN, Self,3,conv1,conv2,conv3);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , double val)
{
   ContainerHandle conv = _conPutND( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LPSTR  val)
{
   ContainerHandle conv = _conPutC( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 1,conv);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LPSTR  p1 , LPSTR p2)
{
   ContainerHandle conp1 = _conPutC( NULLCONTAINER , p1);
   ContainerHandle conp2 = _conPutC( NULLCONTAINER , p2);
   return _conMCallConNR( pFN, Self, 2,conp1,conp2);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN ,LPSTR  pStr , LONG val)
{
   ContainerHandle conc = _conPutC( NULLCONTAINER , pStr);
   ContainerHandle conn = _conPutNL( NULLCONTAINER , val);
   return _conMCallConNR( pFN, Self, 2,conc,conn);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , LONG v1,BOOL v2)
{
   return _conMCallConNR( pFN, Self,2,_conPutNL(0,v1),_conPutL(0,v2));
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conMCallCon( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   ContainerHandle con  = _conPutNL(NULLCONTAINER , pDw[0]);
   ContainerHandle conr = _conMCallConN( pFN, Self,1, con );
   _conGetLong( con , (LONG*) pDw);
   _conRelease(con);
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  )
{
   _conRelease( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   _conRelease( _conMCallCon(Self,pFN,val,val2) );
}
// -----------------------------------------------------------------------------------------------------------------
 OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2 , LONG val3)
{
   _conRelease( _conMCallCon(Self,pFN,val,val2,val3) );
} 
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   _conRelease( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   _conRelease( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , double val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   _conRelease( _conMCallCon(Self,pFN,val) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR p1 , LPSTR p2)
{
   _conRelease( _conMCallCon(Self,pFN,p1,p2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   _conRelease( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   _conRelease( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void _conMCallVoid( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   _conRelease( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conMCallBool( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_BOOL( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LONG _conMCallLong( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_LONG( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API double _conMCallDouble( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_double( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API FLOAT _conMCallFloat( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_FLOAT( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  )
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , BOOL val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val , LONG val2)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val,val2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self, LPSTR pFN, LONG val, LONG val2, LONG val3 )
{
	return _conRelease_ret_LPSTR( _conMCallCon( Self, pFN, val, val2 , val3) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG val, ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , ContainerHandle con)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,con) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , DWORD val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , double val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LPSTR pStr , LONG val)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,pStr,val) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN  , LONG v1,BOOL v2)
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,v1,v2) );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _conMCallLpstr( ContainerHandle Self , LPSTR pFN , ULONG * pDw )
{
   return _conRelease_ret_LPSTR( _conMCallCon(Self,pFN,pDw) );
}
//----------------------------------------------------------------------------------------------------------------------




