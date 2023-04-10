//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
extern BYTE _lower_ansi_char_table_[256];
//-------------------------------------------------------------------------------------------------------------------------
THpStrList::THpStrList(HANDLE hHeap,BOOL bNoSerialize )
{
   m_dwFlags  = 0;
   m_pcs      = 0;
   if( hHeap )
   {
      m_hHeap    = hHeap;
      m_dwFlags  = 2 | (bNoSerialize ? 1 : 0);
   }
   else
   {
      m_hHeap    = HeapCreate(HEAP_NO_SERIALIZE,0,0);
   }
   if( (m_dwFlags & 1) == 0 )
   {
      m_pcs = (CRITICAL_SECTION*) _xgrab( sizeof(CRITICAL_SECTION) );
      InitializeCriticalSection(m_pcs);
   }
   m_nCapacity = 0;
   m_nCount    = 0;
   m_pItems    = 0;
}
// -----------------------------------------------------------------------------------------------------------------
void  THpStrList::_lock_(void){ if( m_pcs ){ EnterCriticalSection(m_pcs);} }
void  THpStrList::_unlock_(void){ if( m_pcs ){ LeaveCriticalSection(m_pcs);} }       
// -----------------------------------------------------------------------------------------------------------------
void* THpStrList::_malloc_(UINT n )
{
   if( n && m_hHeap )
   {
      return HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY | (m_dwFlags ? 0 : HEAP_NO_SERIALIZE) , n );
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void  THpStrList::_mfree_(void* p)
{
   if( p && m_hHeap )
   {
      HeapFree(m_hHeap, (m_dwFlags ? 0 : HEAP_NO_SERIALIZE), p );
   }
}
// -----------------------------------------------------------------------------------------------------------------
void*  THpStrList::_mgrow_(void* p, UINT n)
{
   if( !p ) return _malloc_(n);
   if( n && m_hHeap )
   {
      return HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY | (m_dwFlags ? 0 : HEAP_NO_SERIALIZE),p, n );   
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
THpStrList::~THpStrList(void)
{
   _lock_();
   __try
   {
      if( m_dwFlags & 2 )
      {
         UINT n;
         for( n=0; n < m_nCount; n++ )
         {
            LPSTR p = m_pItems[n];
            if( p )
            {
               _mfree_( _mk_ptr_(LPVOID,p,-8) );
            }
         }
         _mfree_( (void*) m_pItems );
      }
      else
      {
         if( m_hHeap ) HeapDestroy(m_hHeap);
      }
      m_hHeap      = 0;
      m_nCapacity  = 0;
      m_nCount     = 0;
      m_pItems     = 0;
   }
   __finally
   {
      if( m_pcs )
      {
         DeleteCriticalSection( m_pcs );
         _xfree((void*) m_pcs);
         m_pcs = 0;         
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void THpStrList::_grow_(UINT nItems)
{
   if(!nItems){ return; }
   _lock_();
   __try
   {
      if( nItems < m_nCapacity ){ nItems = m_nCapacity; }
      if( nItems < 0x1000 ){ if(nItems & 0xFF ){ nItems = (nItems | 0xFF) + 1;} }
      else if( nItems < 0x10000 ){ if(nItems & 0xFFF ){ nItems = (nItems | 0xFFF) + 1;} }
      else { if(nItems & 0xFFFF ){ nItems = (nItems | 0xFFFF) + 1;} }      
      if( m_hHeap && nItems )
      {
         void* p = _mgrow_((void*)m_pItems, (nItems * sizeof(LPSTR)) );
         if( p )
         {
            m_pItems     = (LPSTR*) p;
            m_nCapacity  = nItems;
         }
      }
   }
   __finally
   {
      _unlock_();
   }
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR THpStrList::Add(LPSTR p,UINT cb)
{
   LPSTR pResult = 0;
   
   if(!p) return 0;
   if( cb == INFINITE ){cb = _xstrlen(p);}
   if(!cb) return 0;
   _lock_();   
   __try
   {
      _grow_( m_nCount + 1 );
      if( m_nCapacity > m_nCount )
      {
         DWORD* pNew = (DWORD*) _malloc_(cb + 10);
         if( pNew )
         {
            pResult = _mk_ptr_(LPSTR,pNew,8);
            _bcopy( (LPBYTE) pResult , (LPBYTE) p , cb );
            pNew[0] = cb;                              
            pNew[1] = dwCrc32Lower(0,(LPBYTE) p , cb );
            m_pItems[m_nCount] = pResult;
            m_nCount++;
         }
      }
   }   
   __finally
   {
      _unlock_();
   }   
   return pResult;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR THpStrList::Put(UINT nPos,LPSTR p,UINT cb)
{
   LPSTR pResult = 0;
   if( cb == INFINITE ){if(p){cb = _xstrlen(p);} else { cb = 0; } }
   _lock_();   
   __try
   {
      if( m_nCount > nPos )   
      {
         LPSTR pOld = m_pItems[nPos];
         m_pItems[nPos] = 0;
         if(pOld) { _mfree_( _mk_ptr_(LPVOID,pOld,-8) );}
      }
      _grow_( nPos + 1 );
      if( m_nCapacity > nPos )
      {
         if( p && cb )
         {
            DWORD* pNew = (DWORD*) _malloc_(cb + 10);
            if( pNew )
            {
               pResult = _mk_ptr_(LPSTR,pNew,8);
               _bcopy( (LPBYTE) pResult , (LPBYTE) p , cb );
               pNew[0] = cb;                              
               pNew[1] = dwCrc32Lower(0,(LPBYTE) p , cb );
               m_pItems[nPos] = pResult;
            }
         }
         if( nPos >= m_nCount ){ m_nCount = nPos +1; }
      }
   }   
   __finally
   {
      _unlock_();
   }   
   return pResult;
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR THpStrList::Get(UINT nPos, UINT* pcb)
{
   LPSTR pResult = 0;
   UINT cb = 0;
   _lock_();   
   __try
   {
      if( m_nCount > nPos )   
      {
         pResult = m_pItems[nPos];
         if( pResult ){cb = _mk_ptr_(LPDWORD,pResult,-8)[0];}
      }
   }   
   __finally
   {
      _unlock_();
   }   
   if(pcb){ pcb[0] = cb; }
   return pResult;
}
// -----------------------------------------------------------------------------------------------------------------
UINT THpStrList::Count(void)
{
   UINT n = 0;
   _lock_();   
   __try { n = m_nCount; }   
   __finally { _unlock_(); }   
   return n;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL THpStrList::InsertBlank(UINT nPos,UINT nItems)
{
   BOOL result = FALSE;
   _lock_();   
   __try
   {
      if( nPos >= m_nCount )
      {
         _grow_( nPos + nItems + 1 );
         if( m_nCapacity > (nPos + nItems) )
         {
            m_nCount = nPos + nItems;
            result = TRUE;
         }
      }
      else
      {
         _grow_( m_nCount + nItems + 1 );   
         if( m_nCapacity > ( m_nCount + nItems) )
         {
            LPDWORD pSrc = _mk_ptr_( LPDWORD , m_pItems, ((m_nCount - 1) * 4) );
            LPDWORD pDst = _mk_ptr_( LPDWORD , pSrc, (nItems * 4) );
            UINT n = ( nItems < m_nCount ? nItems : m_nCount);
            while(n)
            {
               n--;
               *pDst = *pSrc;
               pDst = _mk_ptr_( LPDWORD,pDst,-4 );
               pSrc = _mk_ptr_( LPDWORD,pSrc,-4 );
            }
            while(nItems){ m_pItems[nPos] = 0; nPos++; nItems--; }
            result = TRUE;
         }
      }
   }   
   __finally
   {
      _unlock_();
   }   
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL THpStrList::DeleteItems(UINT nPos,UINT nItems)
{
   BOOL result = FALSE;
   _lock_();   
   __try
   {
      if( nItems && (nPos < m_nCount ) )
      {
         UINT n,nn;
         if( (nPos + nItems) > m_nCount ){ nItems = ( m_nCount - nPos );}
         n  = nPos;
         nn = n + nItems;
         for( ;n < nn;n++)
         {
            LPSTR pOld = m_pItems[n];
            m_pItems[n] = 0;
            if( pOld ) { _mfree_( _mk_ptr_(LPVOID,pOld,-8) ); }            
         }
         for( ;nn < m_nCount ; nn++, nPos++ )
         {
            m_pItems[nPos] = m_pItems[nn];
            m_pItems[nn]   = 0;
         }
         m_nCount -= nItems;
         result = TRUE;
      }
   }   
   __finally
   {
      _unlock_();
   }   
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
UINT THpStrList::Find(UINT nStart,LPSTR p,UINT cb)
{
   UINT   result = INFINITE;
   DWORD  dwcrc  = 0;
   DWORD  n;
   if( cb == INFINITE ){if(p){cb = _xstrlen(p);} else { cb = 0; } }
   if( p && cb ){ dwcrc = dwCrc32Lower(0,(LPBYTE) p , cb ); }
   
   _lock_();   
   __try
   {
      if( nStart < m_nCount )
      {
         if( dwcrc )
         {
            for( n = nStart; n < m_nCount; n++ )
            {
               if(!m_pItems[n])
               {
                  result = n;
                  n = INFINITE;
               }
            }
         }
         else
         {
            for( n = nStart; n < m_nCount; n++ )
            {
               LPBYTE pp = (LPBYTE) m_pItems[n];
               if( pp )
               {
                  DWORD* pdw = _mk_ptr_(LPDWORD,pp,-8);
                  if( (pdw[0] == cb) && ( pdw[1] == dwcrc ) )
                  {
                     if( _bcmpwithtable((LPBYTE)p,pp,cb, _lower_ansi_char_table_) == 0 )
                     {
                        result = n;
                        n = INFINITE;
                     }
                  }
               }
            }
         }
      }
   }   
   __finally
   {
      _unlock_();
   }   
   return result;
}   
// -----------------------------------------------------------------------------------------------------------------



