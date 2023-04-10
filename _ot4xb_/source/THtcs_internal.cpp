//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <string.h>
// -----------------------------------------------------------------------------------------------------------------
THtcsTable::THtcsTable(DWORD nBuckets,DWORD dwMaxPopulation)
{
   m_cs_cargo = 0;
   if( dwMaxPopulation < 64) dwMaxPopulation = 64;
   else if( dwMaxPopulation > 0x7FFFFFFF) dwMaxPopulation = 0x7FFFFFFF;
   m_dwMaxPopulation = dwMaxPopulation;
   ReHtcs( nBuckets );
}
// -----------------------------------------------------------------------------------------------------------------
THtcsTable::~THtcsTable(void)
{
  DeleteAllItems();
  m_dwCargo          = 0;
  m_dwPopIndex       = 0;
  m_pfnOnDestroyItem = 0;
}
// -----------------------------------------------------------------------------------------------------------------
void THtcsTable::DeleteAllItems( void )
{
  THtcsItem* pItem = m_pFirstItem;
  while( pItem )
  {
     THtcsItem* pNext = pItem->m_pNext;
     if( m_pfnOnDestroyItem ){ (* m_pfnOnDestroyItem )( (void*) pItem->m_pData , m_dwCargo); }
     delete pItem;
     pItem = pNext;
  }
  if( m_pBuckets ) _xfree( (void*) m_pBuckets );
  m_nCount           = 0;
  m_pFirstItem       = 0;
  m_pBuckets         = 0;
  m_nBuckets         = 0;
  m_dwPopIndex       = 0;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem *  THtcsBucket::InsertItem( THtcsTable* pTable , THtcsItem * pNew) // pOldItem if Replaced
{
   pNew->m_pNext = 0;
   pNew->m_pPrev = 0;
   if( m_pChain )
   {
      THtcsItem * pItem = m_pChain;
      THtcsItem * pLast = 0;
      DWORD dw = 0;
      // for( ; ((dw < m_nCount) && (pNew->m_dwCrc > pItem->m_dwCrc)) ; dw++ , pItem = pItem->m_pNext) pLast = pItem;
      for( ; dw < m_nCount; dw++ , pItem = pItem->m_pNext)
      {
         int i = THtcsTable::Compare( pNew->m_pKey ,pNew->m_cbKey ,pNew->m_dwCrc,
                                      pItem->m_pKey,pItem->m_cbKey,pItem->m_dwCrc);
         if( i <  0 ) return _insert_before_( pTable , pItem , pNew );
         if( i == 0 ) return _replace_item_(  pTable , pItem , pNew );
         pLast = pItem;
      }
      if( pItem )  return _insert_before_( pTable , pItem , pNew );  // next bucket
      return _insert_after_( pTable , pLast , pNew ); // current bucket
   }
   if( pTable->m_pFirstItem ) pTable->m_pFirstItem->m_pPrev = pNew;
   pNew->m_pNext = pTable->m_pFirstItem;
   pTable->m_pFirstItem = pNew;
   m_pChain = pNew;
   pTable->m_nCount++; m_nCount++;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem * THtcsBucket::_replace_item_(  THtcsTable* , THtcsItem * pItem , THtcsItem * pNew )
{
   LPSTR pKey   = pItem->m_pKey ;
   DWORD cbKey  = pItem->m_cbKey;
   DWORD dwCrc  = pItem->m_dwCrc;
   void* pData  = pItem->m_pData;
   pItem->m_pKey    = pNew->m_pKey ; pNew->m_pKey    = pKey ;
   pItem->m_cbKey   = pNew->m_cbKey; pNew->m_cbKey   = cbKey;
   pItem->m_dwCrc   = pNew->m_dwCrc; pNew->m_dwCrc   = dwCrc;
   pItem->m_pData   = pNew->m_pData; pNew->m_pData   = pData;
   return pNew;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem * THtcsBucket::_insert_before_( THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew )
{
   pTable->m_nCount++; m_nCount++;
   if( pTable->m_dwPopIndex < m_nCount ) pTable->m_dwPopIndex = m_nCount;
   if( pItem == pTable->m_pFirstItem ) pTable->m_pFirstItem = pNew;
   if( pItem == m_pChain ) m_pChain = pNew;
   if( pItem->m_pPrev ) pItem->m_pPrev->m_pNext = pNew;
   pNew->m_pPrev = pItem->m_pPrev; pItem->m_pPrev =  pNew;
   pNew->m_pNext = pItem;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem * THtcsBucket::_insert_after_(  THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew )
{
   pTable->m_nCount++; m_nCount++;
   if( pTable->m_dwPopIndex < m_nCount ) pTable->m_dwPopIndex = m_nCount;
   if( pItem->m_pNext ) pItem->m_pNext->m_pPrev = pNew;
   pNew->m_pNext = pItem->m_pNext; pItem->m_pNext =  pNew;
   pNew->m_pPrev = pItem;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem * THtcsBucket::_remove_item_(THtcsTable* pTable , THtcsItem * pItem)
{
   pTable->m_nCount--; m_nCount--;
   if( pItem == pTable->m_pFirstItem ) pTable->m_pFirstItem = pItem->m_pNext;
   if( pItem == m_pChain ) m_pChain = (( m_nCount > 1 ) ? pItem->m_pNext : 0);   
   if( pItem->m_pPrev ) pItem->m_pPrev->m_pNext = pItem->m_pNext;
   if( pItem->m_pNext ) pItem->m_pNext->m_pPrev = pItem->m_pPrev;
   pItem->m_pPrev = 0;
   pItem->m_pNext = 0;
   pTable->m_nCount--; m_nCount--;
   if( m_nCount == 0 )
   {
      m_pChain = 0;
   }   
   return pItem;
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem * THtcsBucket::FindItem(LPSTR pKey , DWORD cbKey)
{
   if( m_pChain )
   {
      DWORD dwCrc = dwCrc32(0,(LPBYTE) pKey,cbKey);
      THtcsItem * pItem = m_pChain;
      DWORD dw = 0;
      // for( ; ((dw < m_nCount) && (dwCrc > pItem->m_dwCrc)) ; dw++ , pItem = pItem->m_pNext) ;
      for( dw = 0, pItem = m_pChain; dw < m_nCount; dw++ , pItem = pItem->m_pNext)
      {
         int i = THtcsTable::Compare(pKey,cbKey,dwCrc,pItem->m_pKey,pItem->m_cbKey ,pItem->m_dwCrc);
         if( i < 0 ) return 0;
         if( i == 0 ) return pItem;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void * THtcsTable::FindItem(LPSTR pKey , DWORD cbKey)
{
   if( m_nCount )
   {
      DWORD dw = ( _xstrhtcs(pKey,cbKey)  &  (m_nBuckets -1) );
      THtcsItem * pItem = m_pBuckets[dw].FindItem(pKey,cbKey);
      if( pItem ) return pItem->m_pData;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void * THtcsTable::RemoveItem(LPSTR pKey , DWORD cbKey)
{
   if( m_nCount )
   {
      DWORD dw = ( _xstrhtcs(pKey,cbKey)  &  (m_nBuckets -1) );
      THtcsItem * pItem = m_pBuckets[dw].FindItem(pKey,cbKey);
      if( pItem )
      {
         void * pData;
         m_pBuckets[dw]._remove_item_(this,pItem);
         pData = pItem->m_pData;
         delete pItem;
         return pData;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL THtcsTable::DeleteItem(LPSTR pKey , DWORD cbKey)
{
   void * pData = RemoveItem(pKey,cbKey);
   if( pData && m_pfnOnDestroyItem ){ (* m_pfnOnDestroyItem )( (void*) pData , m_dwCargo); return TRUE;}
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
void * THtcsTable::InsertItem(LPSTR pKey , DWORD cbKey, void * pData, BOOL bDestroyOnReplace)
{
   if( m_nBuckets < 8 ) ReHtcs(8);
   // if( (m_dwPopIndex > m_dwMaxPopulation) && ((m_nCount << 1)  > m_nBuckets) ) ReHtcs(m_nBuckets * 2);
   if( (m_nCount << 1)  > m_nBuckets  ) ReHtcs(m_nBuckets * 2);
   THtcsItem * pNew = new THtcsItem( pKey , cbKey , pData );
   DWORD dw = ( _xstrhtcs(pKey,cbKey)  &  (m_nBuckets -1) );
   THtcsItem * pItem = m_pBuckets[dw].InsertItem(this,pNew);
   if( pItem )
   {
       void * p_data = pItem->m_pData;
       if( bDestroyOnReplace && pData && m_pfnOnDestroyItem ){ (* m_pfnOnDestroyItem )( (void*) p_data , m_dwCargo);}
       else return p_data;
   }
   return 0;     
}
// -----------------------------------------------------------------------------------------------------------------
THtcsItem::THtcsItem(LPSTR pKey , DWORD cbKey , void* pData )
{
      m_pKey  = pKey;
      m_cbKey = cbKey;
      m_pData = pData;
      m_dwCrc = dwCrc32(0,(LPBYTE) pKey,cbKey);
}
// -----------------------------------------------------------------------------------------------------------------
void THtcsTable::ReHtcs( DWORD nBuckets)
{
   DWORD dw;
   THtcsItem* pItem = m_pFirstItem;
   for( dw = 8; dw < nBuckets; dw = (dw * 2) );
   if( dw > 0x7FFFFFFF) dw = 0x7FFFFFFF;
   if( dw == m_nBuckets ) return;
   if( m_pBuckets ) _xfree( (void*) m_pBuckets );
   m_pBuckets     = (THtcsBucket*) _xgrab(dw * sizeof(THtcsBucket));
   m_nBuckets     = dw;
   m_nCount       = 0;
   m_pFirstItem   = 0;
   m_dwPopIndex   = 0;
   while( pItem )
   {
      THtcsItem* pNext = pItem->m_pNext;
      pItem->m_pNext = 0; pItem->m_pPrev = 0;
      dw = ( _xstrhtcs(pItem->m_pKey,pItem->m_cbKey)  &  (m_nBuckets -1) );
      m_pBuckets[dw].InsertItem(this,pItem);
      pItem = pNext;
   }
}
// -----------------------------------------------------------------------------------------------------------------




 