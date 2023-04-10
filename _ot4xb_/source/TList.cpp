//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <search.h>
// -----------------------------------------------------------------------------------------------------------------
typedef unsigned short *  LPSHORT;
typedef LONGLONG*         LPLONGLONG;
typedef ULONGLONG*        LPULONGLONG;
typedef float*            LPFLOAT;
typedef double*           LPDOUBLE;
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void*  _tlist_new(void){return (void*) new TList;}
OT4XB_API void   _tlist_destroy(void* ls){delete reinterpret_cast<TList*>(ls);}
OT4XB_API void   _tlist_grow(void* ls,UINT nItems){reinterpret_cast<TList*>(ls)->GrowBy(nItems);}
OT4XB_API void*  _tlist_add(void* ls , void* p ){return reinterpret_cast<TList*>(ls)->Add(p);}
OT4XB_API void*  _tlist_get(void* ls , DWORD n ){return reinterpret_cast<TList*>(ls)->Get(n);}
OT4XB_API void*  _tlist_replace(void* ls , DWORD n , void* p ){return reinterpret_cast<TList*>(ls)->Replace(n,p);}
OT4XB_API DWORD  _tlist_count(void* ls){return reinterpret_cast<TList*>(ls)->Count();}
OT4XB_API void*  _tlist_insert(void* ls , DWORD n , void* p ){return reinterpret_cast<TList*>(ls)->Insert(n,p);}
OT4XB_API void*  _tlist_remove(void* ls , DWORD n){return reinterpret_cast<TList*>(ls)->Remove(n);}
OT4XB_API void*  _tlist_pop(void* ls){return reinterpret_cast<TList*>(ls)->Pop();}
OT4XB_API void _tlist_truncate(void* ls , UINT new_count ){reinterpret_cast<TList*>(ls)->Truncate(new_count);}
OT4XB_API int _tlist_iseek( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->iseek(key,(_PFN_CMPCTXCT_) compare,ctx);}
OT4XB_API void* _tlist_pseek( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->pseek(key,(_PFN_CMPCTXCT_) compare,ctx);}
OT4XB_API void _tlist_qsort( void* ls,DWORD compare,void * ctx){return reinterpret_cast<TList*>(ls)->qsort((_PFN_CMPCTXCT_) compare,ctx);}
OT4XB_API int _tlist_ilocate( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->ilocate(key,(_PFN_CMPCTXCT_) compare,ctx);}
OT4XB_API void* _tlist_plocate( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->plocate(key,(_PFN_CMPCTXCT_) compare,ctx);}
// ---------------------------------------------------------------------------
OT4XB_API void* _tlist_new_ex( DWORD flags, void* vheap ) {	return (void*) new TList( static_cast<TList::vheap_flags>(flags), static_cast<OT4XB_VHEAP*>(vheap) ); }
OT4XB_API void* _tlist_alloc_bytes( void* ls, UINT nBytes ) {return reinterpret_cast<TList*>( ls )->alloc_bytes( nBytes );}
OT4XB_API void  _tlist_free_bytes( void* ls, void* p ) {	reinterpret_cast<TList*>( ls )->free_bytes( p );}
// ---------------------------------------------------------------------------
OT4XB_API void   _tlist_set_granularity(void* ls,DWORD nn)
{
   if( nn > 0xFFFF ){ nn = 0xFFFF; }
   reinterpret_cast<TList*>(ls)->m_nGrowBy = (nn | 0x0F);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD _tlist_serialize(void* pList, DWORD record_size , DWORD dwStart , DWORD dwCount , HANDLE hFile)
{
   TList* ls = reinterpret_cast<TList*>(pList);
   if( !( ls && hFile && (hFile != INVALID_HANDLE_VALUE) && (((int) record_size) > 0) ) ){ return (DWORD) -1; }
   if( dwStart > ls->Count() ){return 0;}
   DWORD dwMax =  ls->Count() - dwStart;
   if( dwCount > dwMax ){ dwCount = dwMax; }
   DWORD dw;
   dwMax = dwCount; dwCount = 0;
   for( dw = 0; dw < dwMax; dw++ )
   {
      void* p = ls->Get(dw);
      if( p )
      {
         DWORD wr = 0;
         if( WriteFile(hFile,p,record_size,&wr,0) )
         {
            dwCount++;
         }
         else
         {
            return (DWORD) -3;
         }
      }
   }
   return dwCount;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD _tlist_unserialize(void* pList,DWORD record_size,DWORD dwMax,HANDLE hFile,OT4XB_VHEAP* vh)
{
   if( !vh ){ vh = &ot4xb_xheap; }
   TList* ls = reinterpret_cast<TList*>(pList);
   if( !( ls && hFile && (hFile != INVALID_HANDLE_VALUE) && (((int) record_size) > 0) ) ){ return (DWORD) -1; }
   DWORD dw;
   DWORD dwCount = 0;
   if( dwMax == ((DWORD) -1) )
   {
      LARGE_INTEGER li_pos;
      LARGE_INTEGER li_mov;
      LARGE_INTEGER li_eof;      
      li_pos.QuadPart = 0LL;
      li_mov.QuadPart = 0LL;      
      li_eof.QuadPart = 0LL;            
      SetFilePointerEx(hFile,li_mov,&li_pos, FILE_CURRENT );
      SetFilePointerEx(hFile,li_mov,&li_eof, FILE_END     );      
      SetFilePointerEx(hFile,li_pos,&li_mov, FILE_BEGIN   );
      li_mov.QuadPart = li_eof.QuadPart -  li_pos.QuadPart;
      ls->GrowBy( ((DWORD) (li_mov.LowPart / record_size)) + 1 );
   }
   else
   {
      ls->GrowBy( dwMax );
   }
   for( dw = 0; dw < dwMax; dw++ )
   {
      void* p = vh->vgrab(vh,record_size);
      if( !p ){ return (DWORD) -2; }
      ZeroMemory(p,record_size);
      DWORD rcb = 0;
      if( ReadFile(hFile,p,record_size,&rcb,0) )
      {
         if( rcb == record_size )
         {
            ls->Add(p);
            dwCount++;
         }
         else
         {
            vh->vfree(vh,p);
            return dwCount;
         }
      }
      else
      {
         vh->vfree(vh,p);
         return (DWORD) -4;
      }
   }
   return dwCount;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void  _tlist_free_simple_items(void* pList,DWORD nStart , DWORD nEnd , OT4XB_VHEAP* vh)
{
   if( !vh ){ vh = &ot4xb_xheap; }
   TList* ls = reinterpret_cast<TList*>(pList);
   if( ls )
   {
      if( nEnd > ls->Count() ){ nEnd = ls->Count(); }
      DWORD n;
      for( n = nStart; n < nEnd; n++ )
      {
         void* p = ls->Replace(n,0);
         if( p ){ vh->vfree(vh,p); }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// ctx[0] = nRules
// ctx[1] = sizeof_rule
// ctx[ 1 + (nRule*sizeof_rule) ] = { fp, ctx1,ctx2,ctx3}
OT4XB_API int __cdecl _tlist_cbk_cmp_combi( DWORD* ctx, void** pp1,void** pp2)
{
   int result = 0;
   int   nn  = (int) ctx[0];
   DWORD rule_size = ctx[1];
   if( rule_size < 24 ){ return 0; }    
   int n;
   ctx = _mk_ptr_(LPDWORD,ctx,8);
   if( !( pp1[0] && pp2[0]) )
   {
      return ( pp1[0] ? 1 : (pp2[0] ? -1 : 0));
   
   }
   for( n=0; (n < nn) && (result == 0) ; n++ , ctx = _mk_ptr_(LPDWORD,ctx,rule_size) )
   {
      _PFN_CMPCTX_WITH_CAST fp = (_PFN_CMPCTX_WITH_CAST) ctx[0];
      result = (*fp)( _mk_ptr_(LPDWORD,ctx,4),pp1,pp2);
   }
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
static BOOL _tlist_cmp_resolve_indirection_level( DWORD* ctx, void** & pp1,void** & pp2, int & result)
{
   DWORD i;
   
   for( i = ctx[3]; i ; i-- )
   {
      pp1 = (void**) pp1[0];
      pp2 = (void**) pp2[0];
      
      if( !( pp1[0] && pp2[0]) )
      {
         result = ( pp1[0] ? 1 : (pp2[0] ? -1 : 0));
         return TRUE;
      }
   }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,cb,descend,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmpi_cb( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   int n = _bcmpwithtable( _mk_ptr_(LPBYTE,pp1[0],ctx[0]) , _mk_ptr_(LPBYTE,pp2[0],ctx[0]),ctx[1], _lower_ansi_char_table_ );
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,cb,descend,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_cb( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   int n = _bcmp( _mk_ptr_(LPBYTE , pp1[0] , ctx[0] ),_mk_ptr_(LPBYTE , pp2[0] , ctx[0] ),ctx[1]);
   return ( ctx[2]  ? -n : n );
}
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_char( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   char dw1  = *_mk_ptr_(LPSTR , pp1[0] , ctx[0] );
   char dw2  = *_mk_ptr_(LPSTR , pp2[0] , ctx[0] );
   char mask = (char) LOBYTE(LOWORD(ctx[1])); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_BYTE( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   BYTE dw1 = *_mk_ptr_(LPBYTE , pp1[0] , ctx[0] );
   BYTE dw2 = *_mk_ptr_(LPBYTE , pp2[0] , ctx[0] );
   BYTE mask = LOBYTE(LOWORD(ctx[1])); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_short( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   short dw1 = *_mk_ptr_(LPSHORT, pp1[0] , ctx[0] );
   short dw2 = *_mk_ptr_(LPSHORT , pp2[0] , ctx[0] );
   short mask = (short) LOWORD(ctx[1]); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_WORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   WORD dw1 = *_mk_ptr_(LPWORD , pp1[0] , ctx[0] );
   WORD dw2 = *_mk_ptr_(LPWORD , pp2[0] , ctx[0] );
   WORD mask = LOWORD(ctx[1]); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_LONG( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   LONG dw1 = *_mk_ptr_(LPLONG , pp1[0] , ctx[0] );
   LONG dw2 = *_mk_ptr_(LPLONG , pp2[0] , ctx[0] );
   LONG mask = (LONG) ctx[1]; if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
//----------------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,mask,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_DWORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   DWORD dw1 = *_mk_ptr_(LPDWORD , pp1[0] , ctx[0] );
   DWORD dw2 = *_mk_ptr_(LPDWORD , pp2[0] , ctx[0] );
   if( ctx[1] ){ dw1 &= ctx[1]; dw2 &= ctx[1]; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,0,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_LONGLONG( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   LONGLONG dw1 = *_mk_ptr_(LPLONGLONG , pp1[0] , ctx[0] );
   LONGLONG dw2 = *_mk_ptr_(LPLONGLONG , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,0,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_QWORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   ULONGLONG dw1 = *_mk_ptr_(LPULONGLONG , pp1[0] , ctx[0] );
   ULONGLONG dw2 = *_mk_ptr_(LPULONGLONG , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,0,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_float( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   float dw1 = *_mk_ptr_(LPFLOAT , pp1[0] , ctx[0] );
   float dw2 = *_mk_ptr_(LPFLOAT , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
// DWORD ctx[4] = { offset,0,descend ,indirection_level }
OT4XB_API int __cdecl _tlist_cbk_cmp_double( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   double dw1 = *_mk_ptr_(LPDOUBLE , pp1[0] , ctx[0] );
   double dw2 = *_mk_ptr_(LPDOUBLE , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
// -----------------------------------------------------------------------------------------------------------------
TList::TList( void )
{
	m_nGrowBy = 15; // +1
	m_nCapacity = 0;
	m_nCount = 0;
	m_pItems = 0;
	vheap_on_init( e_zero , 0 );
}
// -----------------------------------------------------------------------------------------------------------------
TList::TList( vheap_flags dw , OT4XB_VHEAP* vheap )
{
	m_nGrowBy = 15; // +1
	m_nCapacity = 0;
	m_nCount = 0;
	m_pItems = 0;
	vheap_on_init( dw , vheap );
}
//----------------------------------------------------------------------------------------------------------------------
TList::~TList(void)
{
	if ( m_pItems != 0 )
	{
		free_bytes( (void *) m_pItems );
	}
   m_pItems = 0;
	vheap_on_destroy();
}
//----------------------------------------------------------------------------------------------------------------------
void TList::GrowBy(UINT n)
{
   UINT        nCapacity;
   void **  pItems;
   if(n == 0) return;
   nCapacity = n + m_nCapacity;
   pItems    = (void ** ) alloc_bytes( nCapacity * sizeof(void * ));
   if( m_pItems != 0 )
   {
      UINT i;
      for( i = 0; i < m_nCount ; i++ ) pItems[i] = m_pItems[i];
      free_bytes( (void*) m_pItems );
   }
   m_pItems = pItems;
   m_nCapacity = nCapacity;
}
//----------------------------------------------------------------------------------------------------------------------
void TList::Grow(void){ GrowBy( m_nGrowBy +1 ); }
//----------------------------------------------------------------------------------------------------------------------
void * TList::Get( UINT nPos )
{
   if( nPos <  m_nCount) return m_pItems[nPos];
   return (void *) 0;
}
//----------------------------------------------------------------------------------------------------------------------
void * TList::Replace( UINT nPos , void * pNew)
{
   if( nPos <  m_nCount)
   {
      void * pOld = m_pItems[nPos];
      m_pItems[nPos] = pNew;
      return pOld;
   }
   return (void *) 0;
}
//----------------------------------------------------------------------------------------------------------------------
void * TList::Add( void * pNew )
{
   if( m_nCapacity <= m_nCount) Grow();
   m_pItems[m_nCount] = pNew;
   m_nCount++;
   return pNew;
}
//----------------------------------------------------------------------------------------------------------------------
void * TList::Insert( UINT nPos , void * pNew )
{
   UINT n;
	if ( nPos == (UINT) -1 ) return Add( pNew );
   if( nPos > m_nCount) return NULL;
   if( m_nCount == 0) return Add(pNew);
   if( m_nCapacity <= m_nCount) Grow();
   for( n = m_nCount; n > nPos; n-- ) m_pItems[n] = m_pItems[(n-1)];
   m_pItems[nPos] = pNew;
   m_nCount++;
   return pNew;
}
//----------------------------------------------------------------------------------------------------------------------
void * TList::Pop(void)
{
   if(m_nCount){ return Remove( m_nCount -1 ); }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
void * TList::Tail(void)
{
   if(m_nCount){ return m_pItems[(m_nCount -1)]; }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
void TList::Truncate(UINT new_count)
{
   if( new_count < m_nCount )
   {
      UINT n;
      for( n = new_count; n < m_nCount ; n++ ){ m_pItems[n] = 0; }
      m_nCount = new_count;
   }
}
// -----------------------------------------------------------------------------------------------------------------
void * TList::Remove( UINT nPos)
{
   UINT n;
   void * pItem;
   if( nPos >= m_nCount) return NULL;
   if( m_nCount == 0) return NULL;
   pItem = m_pItems[nPos];
   m_nCount--;
   for( n = nPos; n < m_nCount; n++ ) m_pItems[n] = m_pItems[(n+1)];
   m_pItems[m_nCount] = NULL;
   return pItem;
}
//----------------------------------------------------------------------------------------------------------------------
#ifdef OT4XB_OLD_QSORT
void * TList::SortedRemove( void *key, int (__cdecl *comp)(const void *, const void *))
{
   int i = iSeek( key , comp);
   if( i != -1 ) return Remove((UINT) i);
   return NULL;
}
#endif
//----------------------------------------------------------------------------------------------------------------------
UINT TList::Count(void){ return m_nCount;}
//----------------------------------------------------------------------------------------------------------------------
int TList::iseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx)
{
   DWORD r = (DWORD) ::bsearch_s(&key,(void*) m_pItems, m_nCount,sizeof(void*),compare,ctx );
   if( !r ) return -1;
   return  ((((DWORD) m_pItems) - r ) >> 2 );
};
// -----------------------------------------------------------------------------------------------------------------
void* TList::pseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx)
{
   void** r = (void**) ::bsearch_s(&key,(void*) m_pItems, m_nCount,sizeof(void*),compare,ctx );
   if( !r ) return 0;
   return  r[0];
};
// -----------------------------------------------------------------------------------------------------------------
void TList::qsort( int (__cdecl *compare )(void *, const void *, const void *), void * ctx)
{
   ::qsort_s((void*) m_pItems, m_nCount,sizeof(void*),compare,ctx);
};
// -----------------------------------------------------------------------------------------------------------------
int TList::ilocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx)
{
   DWORD r = (DWORD) ::_lfind_s(&key,(void*) m_pItems,&m_nCount,sizeof(void*),compare,ctx );
   if( !r ) return -1;
   return  ((((DWORD) m_pItems) - r ) >> 2 );
}
// -----------------------------------------------------------------------------------------------------------------
void* TList::plocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx)
{
   void** r = (void**) ::_lfind_s(&key,(void*) m_pItems,&m_nCount,sizeof(void*),compare,ctx );
   if( !r ) return 0;
   return  r[0];
};
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
TContainerHandleList::TContainerHandleList(void)
{
   m_nCapacity =  0;
   m_nGrowBy   = 15;
   m_nCount    =  0;
   m_pItems    =  0;
}
// -----------------------------------------------------------------------------------------------------------------
TContainerHandleList::~TContainerHandleList(void)
{
   if( m_pItems ){ _xfree( (void *) m_pItems );}
   m_pItems    =  0;
   m_nCapacity =  0;
   m_nCount    =  0;
}
//----------------------------------------------------------------------------------------------------------------------
void TContainerHandleList::GrowBy(UINT n)
{
   UINT        nCapacity;
   ContainerHandle*  pItems;
   if(n == 0) return;
   nCapacity = n + m_nCapacity;
   pItems    = (ContainerHandle* ) _xgrab( nCapacity * sizeof(ContainerHandle ));
   if( m_pItems != 0 )
   {
      UINT i;
      for( i = 0; i < m_nCount ; i++ ) pItems[i] = m_pItems[i];
      _xfree( (void*) m_pItems );
   }
   m_pItems = pItems;
   m_nCapacity = nCapacity;
}
//----------------------------------------------------------------------------------------------------------------------
void TContainerHandleList::Grow(void){ GrowBy( m_nGrowBy +1 ); }
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TContainerHandleList::Get( UINT nPos )
{
   if( nPos <  m_nCount) return m_pItems[nPos];
   return (ContainerHandle) 0;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TContainerHandleList::Add( ContainerHandle pNew )
{
   if( m_nCapacity <= m_nCount) Grow();
   m_pItems[m_nCount] = pNew;
   m_nCount++;
   return pNew;
}
//----------------------------------------------------------------------------------------------------------------------
void TContainerHandleList::ReleaseAll(void)
{
   UINT n;
   for(n=0; n < m_nCount; n++)
   {
      if(m_pItems[m_nCount] != NULLCONTAINER) _conRelease(m_pItems[m_nCount]);
      m_pItems[m_nCount] = NULLCONTAINER;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TContainerHandleList::Release(UINT n)
{
   if( n <  m_nCount)
   {
      if(m_pItems[n] != NULLCONTAINER) _conRelease(m_pItems[n]);
      m_pItems[n] = NULLCONTAINER;
   }
}
//----------------------------------------------------------------------------------------------------------------------

