//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
void TXbFpParam::Release( void )
{                                         
   if( m_nType & ( XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT ) )
   {
      _conUnLockStrEx_((CON_PLKSTREX *) ((void*) this));
   }
   else if ( ( m_nType & XPP_NUMERIC ) && m_bWrite &&  m_con && m_bByRef )
   {
      if ( m_dwStackVal == (DWORD) ((void*) & m_ndData) ) _conPutND( m_con , m_ndData);
      else if ( m_dwStackVal == (DWORD) ((void*) & m_dwData) ) _conPutNL( m_con , (LONG) m_dwData);
   }
   else if ( ( m_nType & XPP_LOGICAL) && m_bWrite &&  m_con && m_bByRef )
      _conPutL( m_con , (BOOL) m_dwData);

   if( m_con != NULLCONTAINER )
   {
      if( !m_bByRef ) _conRelease( m_con );
      m_con     = NULLCONTAINER;
   }
   
}
//----------------------------------------------------------------------------------------------------------------------
   typedef LPSTR (__cdecl *LPGETUPDATESOURCESELECTION)( long, long, long, long );

void TXbFpParam::Init(XppParamList pl , ULONG nPos , BOOL bDisableByRef)
{
   GetTlsHeapManager()->PopNextFpFlags(); // reset TLS flags anyway   
   m_pNext        = NULL;
   m_pPrev        = NULL;
   m_nPos         = nPos;
   m_nType        = 0;
   m_bByRef       = FALSE;
   m_dwStackVal   = 0;
   m_nSplit       = 0;
   m_con          = _conParam(pl,nPos, ( bDisableByRef ? 0 : (&m_bByRef)) );
   if( m_con != NULLCONTAINER )  _conType( m_con , &m_nType );
}
//----------------------------------------------------------------------------------------------------------------------
TXbFpParam * TXbFpParam::InitList(XppParamList pl , ULONG nFirst , LONG * pnCount,BOOL bDisableByRef)
{
   ULONG nParams = _partype(pl,0);
   ULONG nCount  = 0;
   TXbFpParam *  pList = NULL;
   if( (nParams > 0 ) && ( nFirst <= nParams ) )
   {
      ULONG np = nFirst;
      ULONG n;
      TXbFpParam * pItem = NULL;
      TXbFpParam * pPrev = NULL;
      nCount = (nParams - nFirst) +1;
      pList  = ( TXbFpParam*) _xgrab( sizeof( TXbFpParam) * nCount );
      for( n = 0; n < nCount; n++ , np++ )
      {
         pPrev = pItem;
         pItem = &(pList[n]);
         pItem ->Init(pl,np,bDisableByRef);
         if( pPrev != NULL )
         {
            pItem->m_pPrev = pPrev;
            pPrev->m_pNext = pItem;
         }
      }
   }
   if( pnCount ) pnCount[0] = (LONG) nCount;
   return pList;
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbFpParam::PrepareStackValues(TXbFpParam * pFirst )
{
   ULONG nCount = 0;
   TXbFpParam * pItem;
   for( pItem = pFirst; pItem ; pItem = pItem->m_pNext )
   {
      nCount++;
      pItem->m_bWrite = pItem->m_bByRef;
      if( pItem->m_nType & ( XPP_CHARACTER | XPP_ARRAY | XPP_OBJECT ) )
      {
         _conLockStrEx_( pItem->m_con , pItem->m_nType,pItem->m_bByRef, (CON_PLKSTREX *) ((void*) pItem),pItem->m_bWrite);
         pItem->m_dwStackVal = (DWORD) ((void*)pItem->m_pStr);
         if( pItem->m_pPrev &&  (pItem->m_nType & XPP_CHARACTER) )
         {
            if( pItem->m_pPrev->m_nSplit == 1) // QWORD
            {
               pItem->m_dwStackVal = 0;
               pItem->m_bWrite = FALSE;
               if( !(pItem->m_bByRef) && (pItem->m_nLen > 7) )
               {       
                  DWORD * pdw = (DWORD*) ( (void*) pItem->m_pStr);
                  pItem->m_pPrev->m_dwStackVal = pdw[0];
                  pItem->m_dwStackVal = pdw[1];
                  pItem->m_nSplit = 2;
               }
               else if (pItem->m_nLen > 7)
               {
                  pItem->m_dwStackVal = (DWORD) ((void*)pItem->m_pStr);
                  pItem->m_pPrev->m_nSplit = 3;
               }
               else pItem->m_bWrite = FALSE;
            }
         }
      }
      else if( pItem->m_nType & XPP_NUMERIC )
      {
         if( (pItem->m_pPrev ? ( pItem->m_pPrev->m_nSplit == 1) : FALSE ) ) // double
         {  
            _conGetND(pItem->m_con,&(pItem->m_ndData));  
            if( pItem->m_bByRef )
            {
               pItem->m_dwStackVal = (DWORD) ( (void*) & pItem->m_ndData);
               pItem->m_bWrite     = TRUE;
               pItem->m_pPrev->m_nSplit = 3;
            }
            else
            {
               DWORD * pdw = (DWORD*) ( (void*) & pItem->m_ndData);
               pItem->m_pPrev->m_dwStackVal = pdw[0];
               pItem->m_dwStackVal = pdw[1];
               pItem->m_nSplit = 2;
            }
         }   
         else
         {
            _conGetLong(pItem->m_con,(LONG*) &pItem->m_dwData);  
            if( pItem->m_bByRef )
            {
               pItem->m_dwStackVal = (DWORD) &pItem->m_dwData;
               pItem->m_bWrite     = TRUE;
            }
            else pItem->m_dwStackVal = (DWORD) pItem->m_dwData;
         }
      }
      else if( pItem->m_nType & XPP_LOGICAL )
      {
         _conGetL(pItem->m_con,(BOOL*) &pItem->m_dwData);  
         if( pItem->m_bByRef )
         {
            pItem->m_dwStackVal = (DWORD) &pItem->m_dwData;
            pItem->m_bWrite     = TRUE;
         }
         else pItem->m_dwStackVal = (DWORD) pItem->m_dwData;
      }
      else if( pItem->m_nType & XPP_UNDEF )
      {
         if( (pItem->m_pNext ? ( pItem->m_pNext->m_nType & (XPP_NUMERIC | XPP_CHARACTER )) : FALSE ) )
         { 
            pItem->m_nSplit = 1;
         }
      }

   }
   return  (nCount * sizeof(DWORD)) ;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpParam::ReleaseAll(TXbFpParam * pFirst )
{
   TXbFpParam * pItem;
   for( pItem = pFirst; pItem ; pItem = pItem->m_pNext ) pItem->Release();
   if( pFirst ) _xfree( (void*) pFirst ) ;
}
//----------------------------------------------------------------------------------------------------------------------




