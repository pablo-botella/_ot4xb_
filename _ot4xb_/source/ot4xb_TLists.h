//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#pragma once
#pragma pack(push , 4)
#ifdef __cplusplus
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TList    : public T_ot4xb_base_with_vheap
{
   public:
	    UINT          m_nCapacity;
       UINT          m_nGrowBy;
       UINT          m_nCount;
       void **       m_pItems;
       TList(void);
		 TList( vheap_flags dw  , OT4XB_VHEAP* vheap  );
       ~TList(void);
		 // ---------------------------------------------------------------------------------
       void GrowBy(UINT);
       void Grow(void);
       void * Add( void *  );
       void * Get( UINT );
       void * Replace( UINT , void *);
       UINT Count(void);
       void * Insert( UINT, void *);
       void * Remove(UINT);
       void * Pop(void);
       void * Tail(void);       
       void   Truncate(UINT new_count = 0); // note: truncate is abandoning items so be sure not leave unreferenced memory
       // ---------------------------------------------------------------------------------
       // ULONG tokenize_and_append_strings( LPSTR str , char separator , BOOL alloc_separate_strings ); 
       // ---------------------------------------------------------------------------------
       int iseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       void* pseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       void qsort( int (__cdecl *compare )(void *, const void *, const void *), void * ctx = 0);
       int ilocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       void* plocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
OT4XB_API DWORD _tlist_serialize(void* pList, DWORD record_size , DWORD dwStart , DWORD dwCount , HANDLE hFile);
OT4XB_API DWORD _tlist_unserialize(void* pList,DWORD record_size,DWORD dwMax,HANDLE hFile,OT4XB_VHEAP* vh);
OT4XB_API void  _tlist_free_simple_items(void* pList,DWORD nStart , DWORD nEnd , OT4XB_VHEAP* vh);
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void   _tlist_set_granularity(void* ls,DWORD nn);
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void* _tlist_new_ex( DWORD flags, void* vheap );
OT4XB_API void* _tlist_alloc_bytes( void* ls, UINT nBytes );
OT4XB_API void  _tlist_free_bytes( void* ls, void* p );
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void* _tlist_new(void);
OT4XB_API void  _tlist_destroy(void* ls);
OT4XB_API void  _tlist_grow(void* ls,UINT nItems);
OT4XB_API void* _tlist_add(void* ls , void* p );
OT4XB_API void* _tlist_get(void* ls , DWORD n );
OT4XB_API void* _tlist_replace(void* ls , DWORD n , void* p );
OT4XB_API DWORD _tlist_count(void* ls);
OT4XB_API void* _tlist_insert(void* ls , DWORD n , void* p );
OT4XB_API void* _tlist_remove(void* ls , DWORD n);
OT4XB_API void* _tlist_pop(void* ls);
OT4XB_API void  _tlist_truncate(void* ls , UINT new_count );
OT4XB_API int   _tlist_iseek( void* ls,void *key, DWORD compare,  void * ctx);
OT4XB_API void* _tlist_pseek( void* ls,void *key, DWORD compare,  void * ctx);
OT4XB_API void  _tlist_qsort( void* ls, DWORD compare,  void * ctx);
OT4XB_API int   _tlist_ilocate( void* ls,void *key, DWORD compare,  void * ctx);
OT4XB_API void* _tlist_plocate( void* ls,void *key, DWORD compare,  void * ctx);
// ---------------------------------------------------------------------------
OT4XB_API int __cdecl _tlist_cbk_cmpi_cb( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_cb( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_char( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_BYTE( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_short( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_WORD( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_LONG( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_DWORD( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_LONGLONG( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_QWORD( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_float( DWORD* ctx, void** pp1,void** pp2);
OT4XB_API int __cdecl _tlist_cbk_cmp_double( DWORD* ctx, void** pp1,void** pp2);
// ---------------------------------------------------------------------------

END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// TODO: añadir funciones THpStrList a nivel prg
class OT4XB_API THpStrList  : public T_ot4xb_base
{
   private:
       HANDLE              m_hHeap;
       UINT                m_nCapacity;
       UINT                m_nCount;
       LPSTR*              m_pItems;
       CRITICAL_SECTION*   m_pcs;
       DWORD               m_dwFlags;
       // ---------------------------------------------------------------------------------
       void  _lock_(void);
       void  _unlock_(void);
       void* _malloc_(UINT n );
       void  _mfree_(void* p);
       void* _mgrow_(void* p , UINT n);
       // ---------------------------------------------------------------------------------
       void  _grow_(UINT nItems);
       // ---------------------------------------------------------------------------------
   public:
       // ---------------------------------------------------------------------------------
       THpStrList(HANDLE hHeap = 0,BOOL bNoSerialize = 0);
       ~THpStrList(void);
       // ---------------------------------------------------------------------------------
       LPSTR Add(LPSTR p,UINT cb = INFINITE);
       LPSTR Put(UINT nPos,LPSTR p,UINT cb = INFINITE);
       LPSTR Get(UINT nPos, UINT* pcb = 0);
       UINT  Count(void);
       BOOL  InsertBlank(UINT nPos,UINT nItems);
       BOOL  DeleteItems(UINT nPos,UINT nItems);
       UINT  Find(UINT nStart,LPSTR p,UINT cb = INFINITE);
};
// -----------------------------------------------------------------------------------------------------------------

class OT4XB_API TContainerHandleList   : public T_ot4xb_base
{
   public:
       UINT       m_nCapacity;
       UINT       m_nGrowBy;
       UINT       m_nCount;
       ContainerHandle *  m_pItems;
       // ---------------------------------------------------------------------------------
       TContainerHandleList(void);
       ~TContainerHandleList(void);
       void GrowBy(UINT);
       void Grow(void);
       void Release(UINT );
       void ReleaseAll(void);
       ContainerHandle Add( ContainerHandle  );
       ContainerHandle Get( UINT );
};
// -----------------------------------------------------------------------------------------------------------------
#endif
#pragma pack(pop)
