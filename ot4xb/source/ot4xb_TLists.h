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
/*{{begin-cpp-class}}*/
/*{{cpp-class_: TList
   | parent: {{ilink: <cpp-class T_ot4xb_base_with_vheap> T_ot4xb_base_with_vheap}}
   | category: c-api/classes , c-api/tlist
   | desc: A growable array of `void*`: add, insert, replace, remove, and sort or search with a comparator
     through the C runtime (qsort_s, bsearch_s, _lfind_s). The slot array comes from the heap the list was
     built with (the ot4xb heap, a given OT4XB_VHEAP or a private one, see the parent class); the pointers
     stored are never freed by the list. The C API of the same object is the `_tlist_*` family
     ({{ilink: <c-function _tlist_new> _tlist_new}}, {{ilink: <c-function _tlist_add> _tlist_add}}, ...),
     one function per method, with the same semantics.
     | _kw_: TList, Class }}*/
class OT4XB_API TList    : public T_ot4xb_base_with_vheap
{
   public:
       /*{{|member_: `UINT m_nCapacity` | desc_: Slots allocated. }}*/
	    UINT          m_nCapacity;
       /*{{|member_: `UINT m_nGrowBy` | desc_: Grow() adds this plus one slots (15 by default: 16 at a time). }}*/
       UINT          m_nGrowBy;
       /*{{|member_: `UINT m_nCount` | desc_: Items stored. }}*/
       UINT          m_nCount;
       /*{{|member_: `void** m_pItems` | desc_: The slot array, 0 until the first item. }}*/
       void **       m_pItems;
       /*{{|method_: `TList( void )` | desc_: An empty list on the ot4xb heap. }}*/
       TList(void);
       /*{{|method_: `TList( vheap_flags dw, OT4XB_VHEAP* vheap )` | desc_: An empty list whose memory comes
          from the heap the flags select (vheap_on_init() of the parent class). }}*/
		 TList( vheap_flags dw  , OT4XB_VHEAP* vheap  );
       /*{{|method_: `~TList( void )` | desc_: Frees the slot array and, when the list owns a private heap,
          the heap. The items are not touched. }}*/
       ~TList(void);
		 // ---------------------------------------------------------------------------------
       /*{{|method_: `void GrowBy( UINT n )` | desc_: Adds **n** slots to the capacity, reallocating the
          array; 0 does nothing. }}*/
       void GrowBy(UINT);
       /*{{|method_: `void Grow( void )` | desc_: GrowBy( m_nGrowBy + 1 ). }}*/
       void Grow(void);
       /*{{|method_: `void* Add( void* p )` | desc_: Appends **p**, growing when full; returns p. }}*/
       void * Add( void *  );
       /*{{|method_: `void* Get( UINT nPos )` | desc_: The item at the zero-based position, 0 when out of
          range (or when a 0 was stored). }}*/
       void * Get( UINT );
       /*{{|method_: `void* Replace( UINT nPos, void* p )` | desc_: Stores **p** at the position and returns
          what was there; 0 when out of range. }}*/
       void * Replace( UINT , void *);
       /*{{|method_: `UINT Count( void )` | desc_: Items stored. }}*/
       UINT Count(void);
       /*{{|method_: `void* Insert( UINT nPos, void* p )` | desc_: Inserts **p** at the position, shifting the
          rest up; the count or (UINT) -1 append. Returns p, or 0 when nPos is beyond the count. }}*/
       void * Insert( UINT, void *);
       /*{{|method_: `void* Remove( UINT nPos )` | desc_: Removes the item at the position, shifting the rest
          down, and returns it; 0 when out of range. }}*/
       void * Remove(UINT);
       /*{{|method_: `void* Pop( void )` | desc_: Removes and returns the last item; 0 when empty. }}*/
       void * Pop(void);
       /*{{|method_: `void* Tail( void )` | desc_: The last item, left in place; 0 when empty. }}*/
       void * Tail(void);
       /*{{|method_: `void Truncate( UINT new_count = 0 )` | desc_: Cuts the list to **new_count** items,
          zeroing the abandoned slots; the dropped pointers are not freed, so release them first. A count
          not below the current one changes nothing. }}*/
       void   Truncate(UINT new_count = 0); // note: truncate is abandoning items so be sure not leave unreferenced memory
       // ---------------------------------------------------------------------------------
       // ULONG tokenize_and_append_strings( LPSTR str , char separator , BOOL alloc_separate_strings );
       // ---------------------------------------------------------------------------------
       /*{{|method_: `int iseek( void* key, int (__cdecl* compare)( void*, const void*, const void* ), void* ctx = 0 )`
          | desc_: Binary search (bsearch_s) over a list sorted with the same comparator: the position of a
            matching item, -1 when none. The comparator gets **ctx** and the addresses of two slots; the
            address of **key** plays the part of a slot, so a `void**` is what it receives on both sides.
            The `_tlist_cbk_cmp_*` functions of the C API are ready-made comparators. }}*/
       int iseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       /*{{|method_: `void* pseek( void* key, int (__cdecl* compare)( void*, const void*, const void* ), void* ctx = 0 )`
          | desc_: Same search, returning the matching item instead of its position; 0 when none. }}*/
       void* pseek( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       /*{{|method_: `void qsort( int (__cdecl* compare)( void*, const void*, const void* ), void* ctx = 0 )`
          | desc_: Sorts the items in place (qsort_s) with the comparator. }}*/
       void qsort( int (__cdecl *compare )(void *, const void *, const void *), void * ctx = 0);
       /*{{|method_: `int ilocate( void* key, int (__cdecl* compare)( void*, const void*, const void* ), void* ctx = 0 )`
          | desc_: Linear search (_lfind_s), no order required: the position of the first item the comparator
            reports equal (0) to the key, -1 when none. }}*/
       int ilocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       /*{{|method_: `void* plocate( void* key, int (__cdecl* compare)( void*, const void*, const void* ), void* ctx = 0 )`
          | desc_: Same linear search, returning the item; 0 when none. }}*/
       void* plocate( void *key, int ( __cdecl *compare ) ( void *, const void *, const void *),  void * ctx = 0);
       // ---------------------------------------------------------------------------------
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
OT4XB_API DWORD _tlist_serialize(void* pList, DWORD record_size , DWORD dwStart , DWORD dwCount , HANDLE hFile);
OT4XB_API DWORD _tlist_unserialize(void* pList,DWORD record_size,DWORD dwMax,HANDLE hFile,OT4XB_VHEAP* vh);
OT4XB_API void  _tlist_free_simple_items(void* pList,DWORD nStart , DWORD nEnd , OT4XB_VHEAP* vh);
OT4XB_API int   _tlist_cbk_cmp_combi( DWORD* ctx, void** pp1, void** pp2 );
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
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THpStrList
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , memory/string
   | desc: A list of byte strings copied into a Win32 heap: each Add() or Put() stores its own copy, with the
     length and a lower-case CRC kept in front of the bytes, so Find() compares case insensitively and skips
     the strings whose length or CRC differ. The list owns the copies: they die with the slot (Put(),
     DeleteItems()) or with the list. Slots may be empty (0): InsertBlank() opens them and Find() with no text
     locates the first one. Every public method is serialised with a critical section unless the constructor
     was told not to.
     | _kw_: THpStrList, Class }}*/
class OT4XB_API THpStrList  : public T_ot4xb_base
{
   private:
       /*{{|member_: `HANDLE m_hHeap` | desc_: The heap the copies and the slot array live in: private and
          destroyed with the list, or the one given to the constructor. }}*/
       HANDLE              m_hHeap;
       /*{{|member_: `UINT m_nCapacity` | desc_: Slots allocated, rounded up to 256, 4096 or 65536 items. }}*/
       UINT                m_nCapacity;
       /*{{|member_: `UINT m_nCount` | desc_: Slots in use, empty ones included. }}*/
       UINT                m_nCount;
       /*{{|member_: `LPSTR* m_pItems` | desc_: The slot array: a pointer to the bytes of each string (the
          length and CRC sit in the 8 bytes before) or 0 for an empty slot. }}*/
       LPSTR*              m_pItems;
       /*{{|member_: `CRITICAL_SECTION* m_pcs` | desc_: The lock, 0 when serialisation was refused. }}*/
       CRITICAL_SECTION*   m_pcs;
       /*{{|member_: `DWORD m_dwFlags` | desc_: Bit 1 (2): the heap belongs to the caller, the strings are
          freed one by one at the end; bit 0 (1): no critical section. }}*/
       DWORD               m_dwFlags;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void _lock_( void )` | desc_: Enters the critical section when there is one. }}*/
       void  _lock_(void);
       /*{{|method_: `void _unlock_( void )` | desc_: Leaves it. }}*/
       void  _unlock_(void);
       /*{{|method_: `void* _malloc_( UINT n )` | desc_: A zeroed block from the list heap. }}*/
       void* _malloc_(UINT n );
       /*{{|method_: `void _mfree_( void* p )` | desc_: Frees a block of the list heap. }}*/
       void  _mfree_(void* p);
       /*{{|method_: `void* _mgrow_( void* p, UINT n )` | desc_: Reallocates a block of the list heap (a new
          block when p is 0). }}*/
       void* _mgrow_(void* p , UINT n);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `void _grow_( UINT nItems )` | desc_: Makes room for at least nItems slots. }}*/
       void  _grow_(UINT nItems);
       // ---------------------------------------------------------------------------------
   public:
       // ---------------------------------------------------------------------------------
       /*{{|method_: `THpStrList( HANDLE hHeap = 0, BOOL bNoSerialize = 0 )`
          | desc_: An empty list. Without **hHeap** a private, non-serialised heap is created and destroyed
            with the list; with it the strings are allocated there and freed one by one. **bNoSerialize**
            (only honoured with a given heap) skips the critical section. }}*/
       THpStrList(HANDLE hHeap = 0,BOOL bNoSerialize = 0);
       /*{{|method_: `~THpStrList( void )` | desc_: Frees every string and the slot array (or destroys the
          private heap) and the critical section. }}*/
       ~THpStrList(void);
       // ---------------------------------------------------------------------------------
       /*{{|method_: `LPSTR Add( LPSTR p, UINT cb = INFINITE )` | desc_: Appends a copy of **cb** bytes of
          **p** (INFINITE: up to the zero terminator) and returns the copy, zero-terminated; 0 for an empty
          string or no memory. }}*/
       LPSTR Add(LPSTR p,UINT cb = INFINITE);
       /*{{|method_: `LPSTR Put( UINT nPos, LPSTR p, UINT cb = INFINITE )` | desc_: Stores a copy at the
          zero-based slot, freeing what was there; a position past the end extends the list with empty slots.
          A null or empty string leaves the slot empty. Returns the copy, 0 when nothing was stored. }}*/
       LPSTR Put(UINT nPos,LPSTR p,UINT cb = INFINITE);
       /*{{|method_: `LPSTR Get( UINT nPos, UINT* pcb = 0 )` | desc_: The string of the slot (0 when empty or
          out of range) and its length in **pcb**. }}*/
       LPSTR Get(UINT nPos, UINT* pcb = 0);
       /*{{|method_: `UINT Count( void )` | desc_: Slots in use. }}*/
       UINT  Count(void);
       /*{{|method_: `BOOL InsertBlank( UINT nPos, UINT nItems )` | desc_: Opens **nItems** empty slots at the
          position, shifting the rest up; a position at or past the end just extends the list. FALSE when
          there is no memory. }}*/
       BOOL  InsertBlank(UINT nPos,UINT nItems);
       /*{{|method_: `BOOL DeleteItems( UINT nPos, UINT nItems )` | desc_: Frees the strings of **nItems**
          slots from the position (clipped to the end) and closes the gap. FALSE when nItems is 0 or nPos is
          out of range. }}*/
       BOOL  DeleteItems(UINT nPos,UINT nItems);
       /*{{|method_: `UINT Find( UINT nStart, LPSTR p, UINT cb = INFINITE )` | desc_: The first slot from
          **nStart** whose string equals **p** ignoring case (length and CRC checked first); with a null or
          empty p, the first empty slot. INFINITE when there is none. }}*/
       UINT  Find(UINT nStart,LPSTR p,UINT cb = INFINITE);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------

/*{{begin-cpp-class}}*/
/*{{cpp-class_: TContainerHandleList
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container
   | desc: A growable array of ContainerHandle, for a function that creates a number of containers and wants
     to release them all at once with ReleaseAll(). The list does not release anything by itself: what is
     still inside when it is destroyed stays alive.
     | _kw_: TContainerHandleList, Class }}*/
class OT4XB_API TContainerHandleList   : public T_ot4xb_base
{
   public:
       /*{{|member_: `UINT m_nCapacity` | desc_: Slots allocated. }}*/
       UINT       m_nCapacity;
       /*{{|member_: `UINT m_nGrowBy` | desc_: Grow() adds this plus one slots (16 by default). }}*/
       UINT       m_nGrowBy;
       /*{{|member_: `UINT m_nCount` | desc_: Handles stored. }}*/
       UINT       m_nCount;
       /*{{|member_: `ContainerHandle* m_pItems` | desc_: The slot array, in the ot4xb heap. }}*/
       ContainerHandle *  m_pItems;
       // ---------------------------------------------------------------------------------
       /*{{|method_: `TContainerHandleList( void )` | desc_: An empty list. }}*/
       TContainerHandleList(void);
       /*{{|method_: `~TContainerHandleList( void )` | desc_: Frees the slot array; the handles are not
          released. }}*/
       ~TContainerHandleList(void);
       /*{{|method_: `void GrowBy( UINT n )` | desc_: Adds **n** slots to the capacity. }}*/
       void GrowBy(UINT);
       /*{{|method_: `void Grow( void )` | desc_: GrowBy( m_nGrowBy + 1 ). }}*/
       void Grow(void);
       /*{{|method_: `void Release( UINT n )` | desc_: Releases the handle of slot **n** and sets the slot to
          NULLCONTAINER; the slot stays. }}*/
       void Release(UINT );
       /*{{|method_: `void ReleaseAll( void )` | desc_: Releases every handle, leaving the slots at
          NULLCONTAINER. }}*/
       void ReleaseAll(void);
       /*{{|method_: `ContainerHandle Add( ContainerHandle con )` | desc_: Appends the handle and returns it. }}*/
       ContainerHandle Add( ContainerHandle  );
       /*{{|method_: `ContainerHandle Get( UINT n )` | desc_: The handle of slot **n**, NULLCONTAINER when out
          of range. }}*/
       ContainerHandle Get( UINT );
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
#endif
#pragma pack(pop)
