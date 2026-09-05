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
/*{{begin-c-function}}*/
/*{{c-function_: _conParamRLockStrEx
            | syntax_: `LPSTR _conParamRLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamRLockStrEx
            | _kw_: lock parameter, read pointer, string lock, array lock, GWST lock
   }}*/
/*{{|desc: Retrieves a read only memory pointer from an Xbase++ parameter. Character: locks the internal
      buffer of the string. Numeric: the value is taken as a memory address and returned cast to LPSTR.
      Object: must provide the _lock_() and _unlock_() methods (the GWST structure classes do) that return
      and release the pointer. Array: a temporary buffer with one LONG per element is allocated and filled
      with the element values. Release the lock with _conParamUnLockStrEx().
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `pInfo` CON_PLKSTREX * - Lock state block filled by the call; release with _conParamUnLockStrEx().

    Returns LPSTR - The memory pointer, or NULL on failure (a Numeric 0 or an empty Array also yield NULL). }}*/
OT4XB_API LPSTR _conParamRLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrEx_(pl,nParam,pInfo,FALSE); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conParamWLockStrEx
            | syntax_: `LPSTR _conParamWLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamWLockStrEx
            | _kw_: lock parameter, write pointer, string lock, array lock, GWST lock
   }}*/
/*{{|desc: Retrieves a read/write memory pointer from an Xbase++ parameter. Character: write locks the
      internal buffer of the string; pass the string by reference so the changes reach the caller. Numeric:
      the value is taken as a memory address and returned cast to LPSTR. Object: must provide the _lock_()
      and _unlock_() methods (the GWST structure classes do) that return and release the pointer. Array: a
      temporary buffer with one LONG per element is allocated and filled with the element values; pass the
      array by reference, at unlock time the LONG values are written back to the array elements. Release the
      lock with _conParamUnLockStrEx().
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `pInfo` CON_PLKSTREX * - Lock state block filled by the call; release with _conParamUnLockStrEx().

    Returns LPSTR - The memory pointer, or NULL on failure (a Numeric 0 or an empty Array also yield NULL). }}*/
OT4XB_API LPSTR _conParamWLockStrEx( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrEx_(pl,nParam,pInfo,TRUE); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conLockStrEx_
            | syntax_: ```
                 LPSTR _conLockStrEx_( ContainerHandle con, ULONG nType, BOOL bByRef, CON_PLKSTREX * pInfo, BOOL bWrite )
              ```
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conLockStrEx_
            | _kw_: lock container, memory pointer, string lock, array lock
   }}*/
/*{{|desc: Locks a container as a memory pointer, with the same type handling as _conParamRLockStrEx() and
      _conParamWLockStrEx() but taking the container, its XPP type and the by reference flag directly
      instead of reading them from a parameter list. Release the lock with _conUnLockStrEx_().
    | params:
    - `con` ContainerHandle - Container holding the value to lock.
    - `nType` ULONG - XPP type of the value in con; only XPP_CHARACTER, XPP_NUMERIC, XPP_ARRAY and
      XPP_OBJECT are accepted.
    - `bByRef` BOOL - TRUE keeps con owned by the caller; FALSE makes the call release it once it is no
      longer needed (at lock or at unlock time depending on the type).
    - `pInfo` CON_PLKSTREX * - Lock state block filled by the call; release with _conUnLockStrEx_().
    - `bWrite` BOOL - FALSE for a read only lock; TRUE for a read/write lock (write lock on a Character
      buffer, Array values written back at unlock time).

    Returns LPSTR - The memory pointer, or NULL on failure (a Numeric 0 or an empty Array also yield NULL). }}*/
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
/*{{end-c-function}}*/
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
/*{{begin-c-function}}*/
/*{{c-function_: _conParamUnLockStrEx
            | syntax_: `void _conParamUnLockStrEx( CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamUnLockStrEx
            | _kw_: unlock parameter, release lock, write back
   }}*/
/*{{|desc: Releases a lock obtained with _conParamRLockStrEx() or _conParamWLockStrEx(). For a write locked
      Array the LONG values of the temporary buffer are written back to the array elements before the buffer
      is freed; for an Object the _unlock_() method is called.
    | params:
    - `pInfo` CON_PLKSTREX * - The lock state block filled by the lock call; reset to empty on return.

    Returns void }}*/
OT4XB_API void _conParamUnLockStrEx(CON_PLKSTREX * pInfo){ _conUnLockStrEx_(pInfo); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conUnLockStrEx_
            | syntax_: `void _conUnLockStrEx_( CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conUnLockStrEx_
            | _kw_: unlock container, release lock, write back
   }}*/
/*{{|desc: Releases a lock obtained with _conLockStrEx_(). For a write locked Array the LONG values of the
      temporary buffer are written back to the array elements before the buffer is freed; for an Object the
      _unlock_() method is called; the container is released unless it was flagged as by reference.
    | params:
    - `pInfo` CON_PLKSTREX * - The lock state block filled by the lock call; reset to empty on return.

    Returns void }}*/
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conParamRLockStrExFloat
            | syntax_: `LPSTR _conParamRLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamRLockStrExFloat
            | _kw_: lock parameter, read pointer, float array, packed floats
   }}*/
/*{{|desc: Retrieves a read only memory pointer from an Xbase++ parameter. Same type handling as
      _conParamRLockStrEx() except for an Array: the temporary buffer holds one FLOAT per element instead of
      one LONG. Release the lock with _conParamUnLockStrExFloat().
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `pInfo` CON_PLKSTREX * - Lock state block filled by the call; release with
      _conParamUnLockStrExFloat().

    Returns LPSTR - The memory pointer, or NULL on failure (a Numeric 0 or an empty Array also yield NULL). }}*/
OT4XB_API LPSTR _conParamRLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrExFloat_(pl,nParam,pInfo,FALSE); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conParamWLockStrExFloat
            | syntax_: `LPSTR _conParamWLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamWLockStrExFloat
            | _kw_: lock parameter, write pointer, float array, packed floats
   }}*/
/*{{|desc: Retrieves a read/write memory pointer from an Xbase++ parameter. Same type handling as
      _conParamWLockStrEx() except for an Array: the temporary buffer holds one FLOAT per element instead of
      one LONG, and the FLOAT values are written back to the array elements at unlock time. Release the lock
      with _conParamUnLockStrExFloat().
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `pInfo` CON_PLKSTREX * - Lock state block filled by the call; release with
      _conParamUnLockStrExFloat().

    Returns LPSTR - The memory pointer, or NULL on failure (a Numeric 0 or an empty Array also yield NULL). }}*/
OT4XB_API LPSTR _conParamWLockStrExFloat( XppParamList pl, ULONG nParam, CON_PLKSTREX * pInfo)
{ return _conParamLockStrExFloat_(pl,nParam,pInfo,TRUE); }
/*{{end-c-function}}*/
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
/*{{begin-c-function}}*/
/*{{c-function_: _conParamUnLockStrExFloat
            | syntax_: `void _conParamUnLockStrExFloat( CON_PLKSTREX * pInfo )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conParamUnLockStrExFloat
            | _kw_: unlock parameter, float array, write back
   }}*/
/*{{|desc: Releases a lock obtained with _conParamRLockStrExFloat() or _conParamWLockStrExFloat(). For a
      write locked Array the FLOAT values of the temporary buffer are written back to the array elements
      before the buffer is freed; for an Object the _unlock_() method is called.
    | params:
    - `pInfo` CON_PLKSTREX * - The lock state block filled by the lock call; reset to empty on return.

    Returns void }}*/
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
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
