//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _conParamLockStrEx_( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo, BOOL bWrite);
static LPSTR _conParamLockStrExFloat_( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo, BOOL bWrite);
//----------------------------------------------------------------------------------------------------------------------
// Retrieve a READ ONLY memory pointer from a param of Xbase++ type:
// CHARACTER: Lock the container internal buffer
// NUMERIC:  Will consider it as a memory pointer so will cast value to LPSTR
// OBJECT:   Must be a GST subclass or contain ::_lock_() and ::_unlock_() methods to provide and release pointers
// ARRAY:    Elements must contain numeric values, a string of sizeof(LONG) * Len(aItems) will be created
//           to hold temporally the values
// Must be released with _conParamUnLockStrEx()
OT4XB_API LPSTR _conParamRLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrEx_(pl,nParam,pInfo,FALSE); }
//----------------------------------------------------------------------------------------------------------------------
// Retrieve a READ/WRITEmemory pointer from a param of Xbase++ type:
// CHARACTER: Lock the container internal buffer ( must be passed by reference)
// NUMERIC:  Will consider it as a memory pointer so will cast value to LPSTR
// OBJECT:   Must be a GST subclass or contain ::_lock_() and ::_unlock_() methods to provide and release pointers
// ARRAY:    Elements must contain numeric values, a string of sizeof(LONG) * Len(aItems) will be created
//           to hold temporally the values ( must be passed by reference), the LONG items will be written back to
//           it's corresponding array positions on the next call of _conParamUnLockStrEx.
// Must be released with _conParamUnLockStrEx()
OT4XB_API LPSTR _conParamWLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrEx_(pl,nParam,pInfo,TRUE); }
//----------------------------------------------------------------------------------------------------------------------
// Like _conParamRLockStrEx() and _conParamWLockStrEx() but using a container instead of the Xbase++ paramList pointer
// Must be released with _conUnLockStrEx_()
OT4XB_API LPSTR _conLockStrEx_( ContainerHandle con , ULONG nType , BOOL bByRef , CON_PLKSTREX * pInfo, BOOL bWrite)
{
   if( pInfo != NULL )
   {
      pInfo->nType   = nType;
      pInfo->nLen    = 0;
      pInfo->bByRef  = bByRef;
      pInfo->pStr    = NULL;
      pInfo->con     = con;
      pInfo->bWrite  = bWrite;

      if( (pInfo->con == NULLCONTAINER) || (!(nType & (XPP_NUMERIC | XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT ))) )
      {
         pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
         return NULL;
      }
      else
      {
         if( pInfo->nType & XPP_OBJECT )
         {
            pInfo->pStr = (LPSTR) _conMCallLong( pInfo->con , "_lock_",&pInfo->nLen);
            return pInfo->pStr;
         }
         else if( pInfo->nType & XPP_CHARACTER )
         {
            if( bWrite )
            {
               if( ot4xb_conWLockC( pInfo->con , &(pInfo->pStr) , &(pInfo->nLen)) == 0)
               {
                  return pInfo->pStr;
               }
               pInfo->pStr = NULL;
            }
            else
            {
               if( ot4xb_conRLockC( pInfo->con , &(pInfo->pStr) , &(pInfo->nLen)) == 0)
               {
                  return pInfo->pStr;
               }
               pInfo->pStr = NULL;
            }
         }
         else if( pInfo->nType & XPP_NUMERIC )
         {
            LONG nn = 0;
            _conGetLong(pInfo->con,&nn);
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=(LPSTR)nn;pInfo->con = 0;
            return ( LPSTR) nn;
         }
         else if( pInfo->nType & XPP_ARRAY )
         {
            ULONG nLen = 0;
            _conSizeA(pInfo->con,&nLen,0);
            pInfo->pStr  = NULL;
            if( nLen != 0 )
            {
               LONG * pLong;
               ULONG  n;
               pInfo->nLen  = (ULONG) (nLen * sizeof(LONG));
               pInfo->pStr  = (LPSTR) _xgrab( (UINT) pInfo->nLen + sizeof(LONG) );
               pLong = (LONG * ) pInfo->pStr;
               for( n = 0; n < nLen; n++ ) pLong[n] = _conArrayGetNL(pInfo->con,n+1,0);
            }
            if( !bWrite )
            {
               if( !pInfo->bByRef ) _conRelease(pInfo->con);
               pInfo->con = NULLCONTAINER;
            }
            return pInfo->pStr;
         }
         if( !pInfo->bByRef ) _conRelease(pInfo->con);
         pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
      }
   }
   return NULL;
}
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _conParamLockStrEx_( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo, BOOL bWrite)
{
   if( pInfo != NULL )
   {
      ULONG           nType  = (XPP_NUMERIC | XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT );
      BOOL            bByRef =  FALSE;
      ContainerHandle con    = _conTpParam(pl,nParam,&bByRef,&nType);
      return _conLockStrEx_(con,nType,bByRef,pInfo,bWrite);
   }
   return NULL;
}
//----------------------------------------------------------------------------------------------------------------------
// Unlock a param previous locked with _conParamRLockStrEx() or _conParamWLockStrEx()
OT4XB_API void _conParamUnLockStrEx(CON_PLKSTREX * pInfo){ _conUnLockStrEx_(pInfo); }
//----------------------------------------------------------------------------------------------------------------------
// Unlock a param previous locked with _conLockStrEx_()
OT4XB_API void _conUnLockStrEx_(CON_PLKSTREX * pInfo)
{
   if( pInfo != NULL )
   {
      if( pInfo->nType & XPP_OBJECT )
      {
         _conMCallVoid( pInfo->con , "_unlock_");
         if( pInfo->con != NULLCONTAINER)
         {
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_CHARACTER )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            if( pInfo->pStr != NULL)  ot4xb_conUnlockC(pInfo->con);
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_NUMERIC )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_ARRAY )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            if( pInfo->bWrite && pInfo->pStr )
            {
               ULONG nLen = (pInfo->nLen >> 2);
               if( nLen != 0 )
               {
                  LONG * pLong = (LONG*)( (void*)pInfo->pStr );
                  ULONG  n;
                  for( n = 0; n < nLen; n++ ) _conArrayPutNL(pInfo->con,pLong[n],n+1,0);
               }
            }
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
         if( pInfo->pStr ) _xfree( (void*) pInfo->pStr );
         pInfo->pStr = NULL;
      }
      if( pInfo->con != NULLCONTAINER)
      {
         if( !pInfo->bByRef ) _conRelease(pInfo->con);
         pInfo->con = NULLCONTAINER;
      }
      pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
   }
}
//----------------------------------------------------------------------------------------------------------------------
// Like _conParamRLockStrEx() but if the param is a Xbase++ array must translate it to an
// array of float values
// Mjst be released with _conParamUnLockStrExFloat()
OT4XB_API LPSTR _conParamRLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrExFloat_(pl,nParam,pInfo,FALSE); }
//----------------------------------------------------------------------------------------------------------------------
// Like _conParamWLockStrEx() but if the param is a Xbase++ array must translate it to an
// array of float values
// Mjst be released with _conParamUnLockStrExFloat()
OT4XB_API LPSTR _conParamWLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrExFloat_(pl,nParam,pInfo,TRUE); }
//----------------------------------------------------------------------------------------------------------------------
static LPSTR _conParamLockStrExFloat_( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo, BOOL bWrite)
{
   if( pInfo != NULL )
   {
      pInfo->nType   = (XPP_NUMERIC | XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT );
      pInfo->nLen    = 0;
      pInfo->bByRef  = FALSE;
      pInfo->pStr    = NULL;
      pInfo->con     = _conTpParam(pl,nParam,&(pInfo->bByRef),&(pInfo->nType));
      pInfo->bWrite  = bWrite;

      if( pInfo->con == NULLCONTAINER )
      {
         pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
         return NULL;
      }
      else
      {
         if( pInfo->nType & XPP_OBJECT )
         {
            pInfo->pStr = (LPSTR) _conMCallLong( pInfo->con , "_lock_",&pInfo->nLen);
            return pInfo->pStr;
         }
         else if( pInfo->nType & XPP_CHARACTER )
         {
            if( bWrite )
            {
               if( ot4xb_conWLockC( pInfo->con , &(pInfo->pStr) , &(pInfo->nLen)) == 0)
               {
                  return pInfo->pStr;
               }
               pInfo->pStr = NULL;
            }
            else
            {
               if( ot4xb_conRLockC( pInfo->con , &(pInfo->pStr) , &(pInfo->nLen)) == 0)
               {
                  return pInfo->pStr;
               }
               pInfo->pStr = NULL;
            }
         }
         else if( pInfo->nType & XPP_NUMERIC )
         {
            LONG nn = 0;
            _conGetLong(pInfo->con,&nn);
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=(LPSTR)nn;pInfo->con = 0;
            return ( LPSTR) nn;
         }
         else if( pInfo->nType & XPP_ARRAY )
         {
            ULONG nLen = 0;
            _conSizeA(pInfo->con,&nLen,0);
            pInfo->pStr  = NULL;
            if( nLen != 0 )
            {
               FLOAT * pFloat;
               ULONG  n;
               pInfo->nLen  = (ULONG) (nLen * sizeof(FLOAT));
               pInfo->pStr  = (LPSTR) _xgrab( (UINT) pInfo->nLen + sizeof(FLOAT) );
               pFloat = (FLOAT * ) pInfo->pStr;
               for( n = 0; n < nLen; n++ ) pFloat[n] = ( FLOAT) _conArrayGetND(pInfo->con,n+1,0);
            }
            if( !bWrite )
            {
               if( !pInfo->bByRef ) _conRelease(pInfo->con);
               pInfo->con = NULLCONTAINER;
            }
            return pInfo->pStr;
         }
         if( !pInfo->bByRef ) _conRelease(pInfo->con);
         pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
      }
   }
   return NULL;
}
//----------------------------------------------------------------------------------------------------------------------
// Unlock a param previous locked with _conParamRLockStrExFloat() or _conParamWLockStrExFloat()
OT4XB_API void _conParamUnLockStrExFloat(CON_PLKSTREX * pInfo)
{
   if( pInfo != NULL )
   {
      if( pInfo->nType & XPP_OBJECT )
      {
         _conMCallVoid( pInfo->con , "_unlock_");
         if( pInfo->con != NULLCONTAINER)
         {
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_CHARACTER )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            if( pInfo->pStr != NULL)  ot4xb_conUnlockC(pInfo->con);
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_NUMERIC )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            pInfo->pStr = NULL;
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
      }
      else if( pInfo->nType & XPP_ARRAY )
      {
         if( pInfo->con != NULLCONTAINER)
         {
            if( pInfo->bWrite && pInfo->pStr )
            {
               ULONG nLen = (pInfo->nLen >> 2);
               if( nLen != 0 )
               {
                  FLOAT* pFloat = (FLOAT*)( (void*)pInfo->pStr );
                  ULONG  n;
                  for( n = 0; n < nLen; n++ ) _conArrayPutND(pInfo->con,(double) pFloat[n],n+1,0);
               }
            }
            if( !pInfo->bByRef ) _conRelease(pInfo->con);
            pInfo->con = NULLCONTAINER;
         }
         if( pInfo->pStr ) _xfree( (void*) pInfo->pStr );
         pInfo->pStr = NULL;
      }
      if( pInfo->con != NULLCONTAINER)
      {
         if( !pInfo->bByRef ) _conRelease(pInfo->con);
         pInfo->con = NULLCONTAINER;
      }
      pInfo->nType = 0; pInfo->nLen=0;pInfo->bByRef=FALSE;pInfo->pStr=0;pInfo->con = 0;
   }
}

//----------------------------------------------------------------------------------------------------------------------
