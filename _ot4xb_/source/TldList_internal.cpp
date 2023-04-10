//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TLdList_Master::TLdList_Master(LPSTR pClsName , DWORD nItemSize)
{
   m_dwHSize = sizeof( TLdList_Master );
   m_pFirst = m_pLast = m_pCurrent = 0;
   m_nItemSize = nItemSize;
   m_nItems = m_nRecNo = 0;
   m_dwStatus = 7;
   m_pClassName = 0; m_dwClsCRC32 = 0;
   if( pClsName )
   {
      m_pClassName = _xstrdup(pClsName);
      m_dwClsCRC32 = gwst_x_name2crc(pClsName,_xstrlen(pClsName));
   }
}
//----------------------------------------------------------------------------------------------------------------------
TLdList_Master::~TLdList_Master(void)
{
   TLdList_Item * p = m_pFirst;
   while( p )
   {
      TLdList_Item * pp = p;
      p = p->m_pNext;
      _DestroyItem_( pp );
   }
   m_pFirst = m_pLast = m_pCurrent = 0;
   m_nItems = m_nRecNo = 0;
   m_dwStatus = 7;
   if( m_pf_OnDestroy)(*m_pf_OnDestroy)(&m_dwpfCargo,0,0);
   if( m_pClassName ){_xfree( (void*) m_pClassName );}
}
// -----------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::GetGhPt( void ){ return (LONG) &m_pCurrent; }
//----------------------------------------------------------------------------------------------------------------------
void TLdList_Master::_DestroyItem_( TLdList_Item * pItem )
{
   if( pItem )
   {
      if( m_pf_OnDestroyItem )(*m_pf_OnDestroyItem)(&m_dwpfCargo,pItem,0);
      delete pItem;
   }
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Bof( void ){ return (BOOL) ( m_dwStatus & 1); }
BOOL TLdList_Master::Eof( void ){ return (BOOL) ( m_dwStatus & 2); }
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::RecNo(void)
{
   if( m_dwStatus & 4) return 0;
   if( Bof() ) return 0;
   if( Eof() ) return (m_nItems + 1);
   return m_nRecNo;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::GoTop(void)
{
   if( m_dwStatus & 4) return FALSE;
   m_pCurrent = m_pFirst;
   m_nRecNo = 1;
   m_dwStatus = 0;
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::GoBottom( void )
{
   if( m_dwStatus & 4) return FALSE;
   m_pCurrent = m_pLast;
   m_nRecNo   = m_nItems;
   m_dwStatus = 0;
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
void TLdList_Master::GoBof(void)
{
   m_nRecNo   = 0;
   if( !m_pFirst ) m_dwStatus = 7;
   else m_dwStatus = 1;
   m_pCurrent = 0;
}
//----------------------------------------------------------------------------------------------------------------------
void TLdList_Master::GoEof( void )
{
   m_nRecNo   = m_nItems + 1;
   if( !m_pFirst ) m_dwStatus = 7;
   else m_dwStatus = 2;
   m_pCurrent = 0;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Skip( LONG nSkip )
{
   LONG nSkipped =  Skipper( nSkip );
   if( nSkipped == nSkip ) return TRUE;
   if( nSkip > 0 ) GoEof();
   else GoBof();
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::Skipper( LONG nSkip )
{
   LONG nNewPos,nSkipped;
   if( m_dwStatus & 4 ) return 0;
   if( Bof() ) GoTop();
   if( Eof() ) GoBottom();
   if( nSkip == 0 ) return 0;
   nNewPos = m_nRecNo + nSkip;
   if( nSkip < 0 ){ if( nNewPos < 1 ) nNewPos = 1; }
   else { if( nNewPos > m_nItems ) nNewPos = m_nItems; }
   nSkipped = nNewPos - m_nRecNo;
   if( nSkipped == 0 ) return 0;
   m_nRecNo = nNewPos;
   if( nSkipped < 0 )
   {
      LONG n;
      for( n=0; ((n > nSkipped) && m_pCurrent); n--) m_pCurrent = m_pCurrent->m_pPrev;

   }
   else
   {
      LONG n;
      for( n=0; ((n < nSkipped) && m_pCurrent); n++) m_pCurrent = m_pCurrent->m_pNext;
   }
   return nSkipped;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Goto( LONG nRecord )
{
   if( m_dwStatus & 4 ) return FALSE;
   if( nRecord < 1 ){ GoBof(); return FALSE; }
   if( nRecord > m_nItems ){ GoEof(); return FALSE; }
   if( Eof() ) GoBottom();
   else if( Bof() ) GoTop();
   if( nRecord == m_nRecNo ) return TRUE;
   if( nRecord > m_nRecNo )
   {
      LONG nb = (m_nItems - nRecord );
      LONG nc = nRecord - m_nRecNo;
      if( nc < nb ) return Skip(nc);
      GoBottom(); return Skip( -nb );
   }
   else // if( nRecord < m_nRecNo )
   {
      LONG nt = (nRecord - 1);
      LONG nc = m_nRecNo - nRecord;
      if( nc < nt ) return Skip( -nc );
      GoTop(); return Skip( nt );
   }
   // return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::SwapRecords( LONG n1 , LONG n2 )
{
   if( (n1 < 1) || (n1 > m_nItems) || (n2 < 1) || (n2 > m_nItems) ) return FALSE;
   else if(n1 == n2) return TRUE;
   else
   {
      LONG  nOldRec     = m_nRecNo;
      DWORD dwOldStatus = m_dwStatus;
      TLdList_Item * p1 = 0;
      TLdList_Item * p2 = 0;
      TLdList_Item * p;
      if( n1 == m_nRecNo ){ p1 = m_pCurrent; Goto(n2); p2 = m_pCurrent; } // m_pCurrend is now swapped
      else if( n2 == m_nRecNo ){ p2 = m_pCurrent; Goto(n1); p1 = m_pCurrent; }
      else
      {
         p = m_pCurrent;
         Goto(n1); p1 = m_pCurrent;
         Goto(n2); p2 = m_pCurrent;
         m_pCurrent = p;
      }
      m_nRecNo = nOldRec; m_dwStatus = dwOldStatus;
      if( p1 == m_pFirst ) m_pFirst = p2;
      else if( p2 == m_pFirst ) m_pFirst = p1;
      if( p1 == m_pLast ) m_pLast = p2;
      else if( p2 == m_pLast ) m_pLast = p1;
      p = p1->m_pPrev; p1->m_pPrev = p2->m_pPrev; p2->m_pPrev = p;
      if( p1->m_pPrev ) p1->m_pPrev->m_pNext = p1;
      if( p2->m_pPrev ) p2->m_pPrev->m_pNext = p2;
      p = p1->m_pNext; p1->m_pNext = p2->m_pNext; p2->m_pNext = p;
      if( p1->m_pNext ) p1->m_pNext->m_pPrev = p1;
      if( p2->m_pNext ) p2->m_pNext->m_pPrev = p2;
   }
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Append( void ){GoEof(); return Insert(); }
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Insert( void )
{
   TLdList_Item * pItem = (TLdList_Item *) _xgrab( m_nItemSize );
   if( !m_pCurrent )
   {
      if( Eof() ) GoEof();
      else GoBof();
   }

   if( Bof() || (m_pCurrent == m_pFirst) ) // if(m_nRecNo == 1) insert before 1st also
   {
      pItem->m_pNext = m_pFirst;
      if( m_pFirst ) m_pFirst->m_pPrev = pItem;
      if( !m_pLast ) m_pLast = pItem;
      m_pFirst = m_pCurrent = pItem;
      m_nItems++; m_nRecNo = 1;
      m_dwStatus = 0; // reset BOF && EOF flags
      return TRUE;
   }
   if( Eof() )
   {
      pItem->m_pPrev = m_pLast;
      if( m_pLast ) m_pLast->m_pNext = pItem;
      if( !m_pFirst ) m_pFirst = pItem; // this must never happen because already handled in Bof() case
      m_pLast = m_pCurrent = pItem;
      m_nItems++; m_nRecNo = m_nItems;
      m_dwStatus = 0; // reset BOF && EOF flags
      return TRUE;
   }

   // If we've reached this line we can assume the following
   // ASSERTIONS:
   // m_pCurrent will always exist
   // m_pCurrent will never be equal to m_pFirst but can be equal to m_pLast

   pItem->m_pNext = m_pCurrent;
   pItem->m_pPrev = m_pCurrent->m_pPrev;
   if( pItem->m_pPrev ) pItem->m_pPrev->m_pNext = pItem;
   else m_pFirst = pItem; // this must never be happen because already handled in Bof() case
   if( pItem->m_pNext ) pItem->m_pNext->m_pPrev = pItem;
   else m_pLast = pItem; // this must never be happen because already handled in Eof() case
   m_nItems++; // m_nRecNo will remain the same as (m_nRecNo == 1) Bof() and Eof() have previously managed
   m_pCurrent = pItem;
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TLdList_Master::Delete( void )
{

   TLdList_Item * pItem = m_pCurrent;
   if( m_dwStatus  ) return FALSE; // EOF or BOF
   if( !pItem ) return FALSE; // this must never be happen
   m_nItems--;
   if( pItem == m_pLast )
   {
      if(pItem == m_pFirst)
      {
         m_pFirst = m_pLast = m_pCurrent = 0;
         m_nItems = m_nRecNo = 0;
         m_dwStatus = 7;
      }
      else
      {
         m_nRecNo = m_nItems;
         m_pLast = m_pCurrent = pItem->m_pPrev;
         m_pCurrent->m_pNext  = 0;
      }
   }
   else if( pItem == m_pFirst )
   {
      m_nRecNo = 1;
      m_pFirst = m_pCurrent = pItem->m_pNext;
      m_pCurrent->m_pPrev   = 0;
   }
   else
   {
      m_pCurrent = pItem->m_pNext;
      pItem->m_pNext->m_pPrev = pItem->m_pPrev;
      pItem->m_pPrev->m_pNext = pItem->m_pNext;
   }
   _DestroyItem_( pItem );
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
TLdList_Item * TLdList_Master::CloneItem( TLdList_Item * pSrc)
{
   if( pSrc )
   {
      TLdList_Item * pItem = (TLdList_Item *) _xgrab( m_nItemSize );
      if( pSrc) _bcopy( ((LPBYTE) (void*) pItem ) , ((LPBYTE) (void*) pSrc ) , m_nItemSize );
      pItem->m_pPrev = pItem->m_pNext = 0;
      if(m_pf_OnCloneItem) (*m_pf_OnCloneItem)(&m_dwpfCargo,pSrc,pItem);
      return pItem;
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
TLdList_Item * TLdList_Master::CloneItems( LONG nItems , LONG * pnCount)
{
   LONG __n__;
   TLdList_Item * pSrc  = ( (nItems == -1) ? m_pFirst : m_pCurrent );

   if(! pnCount ) pnCount = &__n__;
   pnCount[0] = 0;
   if( nItems == -1 ) nItems = 0x7FFFFFFF;
   else if( m_dwStatus ) nItems = 0; // cannot clone partial list if eof or bof
   if( m_dwStatus  && pSrc && (nItems > 0) )
   {
      TLdList_Item * pDst  = CloneItem( pSrc );
      TLdList_Item * p     = pDst;
      pnCount[0]++;
      while( pnCount[0] < nItems )
      {
         pSrc = pSrc->m_pNext;
         if( !pSrc) return pDst;
         p->m_pNext = CloneItem( pSrc );
         p->m_pNext->m_pPrev = p;
         p = p->m_pNext;
         pnCount[0]++;
      }
      return pDst;
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
TLdList_Item * TLdList_Master::DetachItems( LONG nItems , LONG * pnCount)
{
   LONG __n__;
   if(! pnCount ) pnCount = &__n__;
   pnCount[0] = 0;

   if( nItems == -1 ) // Detach the entire list
   {
      TLdList_Item * pItems = m_pFirst;
      pnCount[0] = m_nItems;
      m_pFirst = m_pLast = m_pCurrent = 0;
      m_nItems = m_nRecNo = 0;
      m_dwStatus = 7;
      return pItems;
   }
   else if( (nItems > 0) && m_pCurrent )
   {
      TLdList_Item * pFirst = m_pCurrent;
      TLdList_Item * pLast  = pFirst;
      pnCount[0]++;
      while( pLast->m_pNext && (pnCount[0] < nItems) )
      {
         pLast = pLast->m_pNext;
         pnCount[0]++;
      }
      m_nItems -= pnCount[0]; 
      if( pLast->m_pNext && pFirst->m_pPrev )
      {
         pFirst->m_pPrev->m_pNext = m_pCurrent =  pLast->m_pNext;
         pLast->m_pNext->m_pPrev = pFirst->m_pPrev;
         m_dwStatus = 7;
         pFirst->m_pPrev = 0;
         pLast->m_pNext  = 0;
         return pFirst;
      }
      if( pLast->m_pNext )
      {
         m_pCurrent = m_pFirst = pLast->m_pNext;
         pLast->m_pNext->m_pPrev = 0;
         m_nRecNo = 1;
         m_dwStatus = 0;
         pFirst->m_pPrev = 0;
         pLast->m_pNext  = 0;
         return pFirst;
      }
      if( pFirst->m_pPrev )
      {
         m_pCurrent = m_pLast = pFirst->m_pPrev;
         pFirst->m_pPrev->m_pNext = 0;
         m_nRecNo = m_nItems;
         m_dwStatus = 0;
         pFirst->m_pPrev = 0;
         pLast->m_pNext  = 0;
         return pFirst;
      }
      else
      {
         m_pFirst = m_pLast = m_pCurrent = 0;
         m_nItems = m_nRecNo = 0;
         m_dwStatus = 7;
         return pFirst;
      }
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::AttachItems( TLdList_Item * pFirst  , LONG * pnCount)
{
   LONG __n__;
   if(! pnCount ) pnCount = &__n__;
   pnCount[0] = 0;
   if( pFirst )
   {
      TLdList_Item * pLast = pFirst;
      pnCount[0] = 1;
      pFirst->m_pPrev = 0; // forced detach of previous item
      while( pLast->m_pNext )
      {
         pnCount[0]++;
         pLast = pLast->m_pNext;
      }
      if( !m_pCurrent ){if( Eof() ) GoEof();else GoBof();}
      if( Bof() || (m_pCurrent == m_pFirst) ) // if(m_nRecNo == 1) insert before 1st also
      {
         pLast->m_pNext = m_pFirst;
         if( m_pFirst ) m_pFirst->m_pPrev = pFirst;
         if( !m_pLast ) m_pLast = pLast;
         m_pFirst = m_pCurrent = pFirst;
         m_nItems += pnCount[0];
         m_nRecNo = 1;
         m_dwStatus = 0; // reset BOF && EOF flags
         return pnCount[0];
      }
      if( Eof() )
      {
         pFirst->m_pPrev = m_pLast;
         if( m_pLast ) m_pLast->m_pNext = pFirst;
         if( m_pFirst ){ m_nRecNo = m_nItems; m_pCurrent = m_pLast; }
         else{ m_pFirst = m_pCurrent = pFirst; m_nRecNo = 1;}
         m_pLast = pLast;
         m_nItems += pnCount[0];
         m_dwStatus = 0; // reset BOF && EOF flags
         return pnCount[0];
      }
      m_nItems += pnCount[0];
      pFirst->m_pPrev = m_pCurrent;
      pLast->m_pNext  = m_pCurrent->m_pNext;
      if( m_pCurrent->m_pNext ) m_pCurrent->m_pNext->m_pPrev = pLast;
      else m_pLast = pLast;
      m_pCurrent->m_pNext = pFirst;
      m_dwStatus = 0; // reset BOF && EOF flags
   }
   return pnCount[0];
}
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::StealItems( TLdList_Master * pList , LONG nItems )
{
    TLdList_Item * pFirst = pList->DetachItems(nItems); 
    return AttachItems(pFirst);      
}
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::MergeClone( TLdList_Master * pList)
{
   TLdList_Item * pFirst = pList->CloneItems(-1);
   return AttachItems(pFirst);
}
//----------------------------------------------------------------------------------------------------------------------
LONG TLdList_Master::EatList( TLdList_Master * pList){ return StealItems(pList,-1); }
//----------------------------------------------------------------------------------------------------------------------
