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
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_new
            | syntax_: `void * _tlist_new( void )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_new
            | _kw_: tlist, pointer list, create, growable array
   }}*/
/*{{|desc: Creates a new empty TList, a growable array of void pointers, using the default ot4xb heap.

    Returns void * - Pointer to the new list object. Release it with _tlist_destroy. }}*/
OT4XB_API void*  _tlist_new(void){return (void*) new TList;}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_destroy
            | syntax_: `void _tlist_destroy( void * ls )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_destroy
            | _kw_: tlist, destroy, release list
   }}*/
/*{{|desc: Destroys a list, freeing its slot array and, when the list owns a private heap, that heap too.
      The pointers stored as items are not freed by themselves.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.

    Returns void }}*/
OT4XB_API void   _tlist_destroy(void* ls){delete reinterpret_cast<TList*>(ls);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_grow
            | syntax_: `void _tlist_grow( void * ls, UINT nItems )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_grow
            | _kw_: tlist, capacity, reserve, grow
   }}*/
/*{{|desc: Extends the list capacity by nItems extra slots, reallocating the internal slot array. Useful
      to reserve room before adding many items.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `nItems` UINT - Number of slots to add to the current capacity. Zero does nothing.

    Returns void }}*/
OT4XB_API void   _tlist_grow(void* ls,UINT nItems){reinterpret_cast<TList*>(ls)->GrowBy(nItems);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_add
            | syntax_: `void * _tlist_add( void * ls, void * p )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_add
            | _kw_: tlist, append, add pointer, push
   }}*/
/*{{|desc: Appends a pointer at the end of the list, growing the slot array when it is full.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `p` void * - Pointer to store as the new last item.

    Returns void * - The stored pointer (same value as p). }}*/
OT4XB_API void*  _tlist_add(void* ls , void* p ){return reinterpret_cast<TList*>(ls)->Add(p);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_get
            | syntax_: `void * _tlist_get( void * ls, DWORD n )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_get
            | _kw_: tlist, get item, position
   }}*/
/*{{|desc: Returns the pointer stored at a zero-based position.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `n` DWORD - Zero-based item position.

    Returns void * - The stored pointer, or NULL when n is out of range. A NULL return can also be a
      stored NULL item. }}*/
OT4XB_API void*  _tlist_get(void* ls , DWORD n ){return reinterpret_cast<TList*>(ls)->Get(n);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_replace
            | syntax_: `void * _tlist_replace( void * ls, DWORD n, void * p )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_replace
            | _kw_: tlist, replace item, position
   }}*/
/*{{|desc: Stores a new pointer at a zero-based position and returns the pointer that was there before.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `n` DWORD - Zero-based item position.
    - `p` void * - New pointer to store at that position.

    Returns void * - The previous pointer at that position, or NULL when n is out of range. }}*/
OT4XB_API void*  _tlist_replace(void* ls , DWORD n , void* p ){return reinterpret_cast<TList*>(ls)->Replace(n,p);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_count
            | syntax_: `DWORD _tlist_count( void * ls )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_count
            | _kw_: tlist, count, number of items
   }}*/
/*{{|desc: Returns the number of items currently stored in the list.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.

    Returns DWORD - Item count. }}*/
OT4XB_API DWORD  _tlist_count(void* ls){return reinterpret_cast<TList*>(ls)->Count();}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_insert
            | syntax_: `void * _tlist_insert( void * ls, DWORD n, void * p )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_insert
            | _kw_: tlist, insert item, position
   }}*/
/*{{|desc: Inserts a pointer at a zero-based position, shifting that item and the following ones up one
      slot.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `n` DWORD - Zero-based insert position, from 0 up to the item count. Both the item count and
      (DWORD) -1 append at the end.
    - `p` void * - Pointer to insert.

    Returns void * - The inserted pointer, or NULL when n is beyond the item count. }}*/
OT4XB_API void*  _tlist_insert(void* ls , DWORD n , void* p ){return reinterpret_cast<TList*>(ls)->Insert(n,p);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_remove
            | syntax_: `void * _tlist_remove( void * ls, DWORD n )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_remove
            | _kw_: tlist, remove item, position
   }}*/
/*{{|desc: Removes the item at a zero-based position, shifting the following items down one slot.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `n` DWORD - Zero-based position of the item to remove.

    Returns void * - The removed pointer, or NULL when n is out of range. The pointed memory is not
      freed. }}*/
OT4XB_API void*  _tlist_remove(void* ls , DWORD n){return reinterpret_cast<TList*>(ls)->Remove(n);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_pop
            | syntax_: `void * _tlist_pop( void * ls )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_pop
            | _kw_: tlist, pop, last item
   }}*/
/*{{|desc: Removes the last item of the list and returns it.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.

    Returns void * - The removed pointer, or NULL when the list is empty. }}*/
OT4XB_API void*  _tlist_pop(void* ls){return reinterpret_cast<TList*>(ls)->Pop();}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_truncate
            | syntax_: `void _tlist_truncate( void * ls, UINT new_count )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_truncate
            | _kw_: tlist, truncate, cut, count
   }}*/
/*{{|desc: Cuts the list down to new_count items, clearing the abandoned slots. The dropped pointers are
      not freed: release them before truncating or their memory leaks.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `new_count` UINT - New item count. A value equal or greater than the current count leaves the
      list unchanged.

    Returns void }}*/
OT4XB_API void _tlist_truncate(void* ls , UINT new_count ){reinterpret_cast<TList*>(ls)->Truncate(new_count);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_iseek
            | syntax_: `int _tlist_iseek( void * ls, void * key, DWORD compare, void * ctx )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_iseek
            | _kw_: tlist, binary search, bsearch, sorted, position
   }}*/
/*{{|desc: Binary search over a list previously sorted with the same comparator. Returns the position of
      a matching item.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `key` void * - Key value; the comparator receives its address as if it were an item slot.
    - `compare` DWORD - Address of an __cdecl comparator (void* ctx, const void*, const void*)
      returning negative, zero or positive; the _tlist_cbk_cmp_* helpers fit here.
    - `ctx` void * - Context passed to the comparator as its first argument.

    Returns int - Zero-based position of a matching item, or -1 when not found. }}*/
OT4XB_API int _tlist_iseek( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->iseek(key,(_PFN_CMPCTXCT_) compare,ctx);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_pseek
            | syntax_: `void * _tlist_pseek( void * ls, void * key, DWORD compare, void * ctx )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_pseek
            | _kw_: tlist, binary search, bsearch, sorted, pointer
   }}*/
/*{{|desc: Binary search over a list previously sorted with the same comparator. Returns the matching
      stored pointer.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `key` void * - Key value; the comparator receives its address as if it were an item slot.
    - `compare` DWORD - Address of an __cdecl comparator (void* ctx, const void*, const void*)
      returning negative, zero or positive; the _tlist_cbk_cmp_* helpers fit here.
    - `ctx` void * - Context passed to the comparator as its first argument.

    Returns void * - The matching stored pointer, or NULL when not found. }}*/
OT4XB_API void* _tlist_pseek( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->pseek(key,(_PFN_CMPCTXCT_) compare,ctx);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_qsort
            | syntax_: `void _tlist_qsort( void * ls, DWORD compare, void * ctx )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_qsort
            | _kw_: tlist, sort, qsort, comparator
   }}*/
/*{{|desc: Sorts the list items in place using the C runtime quick sort and the given comparator.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `compare` DWORD - Address of an __cdecl comparator (void* ctx, const void*, const void*) that
      receives the addresses of two item slots; the _tlist_cbk_cmp_* helpers fit here.
    - `ctx` void * - Context passed to the comparator as its first argument.

    Returns void }}*/
OT4XB_API void _tlist_qsort( void* ls,DWORD compare,void * ctx){return reinterpret_cast<TList*>(ls)->qsort((_PFN_CMPCTXCT_) compare,ctx);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_ilocate
            | syntax_: `int _tlist_ilocate( void * ls, void * key, DWORD compare, void * ctx )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_ilocate
            | _kw_: tlist, linear search, find, position
   }}*/
/*{{|desc: Linear scan of the list, no sort order required. Returns the position of the first matching
      item.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `key` void * - Key value; the comparator receives its address as if it were an item slot.
    - `compare` DWORD - Address of an __cdecl comparator (void* ctx, const void*, const void*)
      returning 0 on a match; the _tlist_cbk_cmp_* helpers fit here.
    - `ctx` void * - Context passed to the comparator as its first argument.

    Returns int - Zero-based position of the first matching item, or -1 when not found. }}*/
OT4XB_API int _tlist_ilocate( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->ilocate(key,(_PFN_CMPCTXCT_) compare,ctx);}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_plocate
            | syntax_: `void * _tlist_plocate( void * ls, void * key, DWORD compare, void * ctx )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_plocate
            | _kw_: tlist, linear search, find, pointer
   }}*/
/*{{|desc: Linear scan of the list, no sort order required. Returns the first matching stored pointer.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `key` void * - Key value; the comparator receives its address as if it were an item slot.
    - `compare` DWORD - Address of an __cdecl comparator (void* ctx, const void*, const void*)
      returning 0 on a match; the _tlist_cbk_cmp_* helpers fit here.
    - `ctx` void * - Context passed to the comparator as its first argument.

    Returns void * - The first matching stored pointer, or NULL when not found. }}*/
OT4XB_API void* _tlist_plocate( void* ls,void *key,DWORD compare,void* ctx){return reinterpret_cast<TList*>(ls)->plocate(key,(_PFN_CMPCTXCT_) compare,ctx);}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_new_ex
            | syntax_: `void * _tlist_new_ex( DWORD flags, void * vheap )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_new_ex
            | _kw_: tlist, create, vheap, private heap, flags
   }}*/
/*{{|desc: Creates a new empty TList choosing where its memory comes from: the default ot4xb heap, a
      caller supplied OT4XB_VHEAP, or a private heap owned by the list.
    | params:
    - `flags` DWORD - vheap_flags combination: 0 default ot4xb heap, 0x800 use the vheap argument,
      0x100 create a private heap (implies 0x800 and 0x200), 0x200 destroy that heap together with the
      list. 0x800 with a NULL vheap also switches to a private heap destroyed with the list.
    - `vheap` void * - OT4XB_VHEAP to allocate from when flags contain 0x800; ignored otherwise.

    Returns void * - Pointer to the new list object. Release it with _tlist_destroy. }}*/
OT4XB_API void* _tlist_new_ex( DWORD flags, void* vheap ) {	return (void*) new TList( static_cast<TList::vheap_flags>(flags), static_cast<OT4XB_VHEAP*>(vheap) ); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_alloc_bytes
            | syntax_: `void * _tlist_alloc_bytes( void * ls, UINT nBytes )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_alloc_bytes
            | _kw_: tlist, allocate, list heap
   }}*/
/*{{|desc: Allocates a memory block from the heap the list was created with (default ot4xb heap, custom
      vheap or private heap).
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `nBytes` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the allocated block. Free it with _tlist_free_bytes on the same list. }}*/
OT4XB_API void* _tlist_alloc_bytes( void* ls, UINT nBytes ) {return reinterpret_cast<TList*>( ls )->alloc_bytes( nBytes );}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_free_bytes
            | syntax_: `void _tlist_free_bytes( void * ls, void * p )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_free_bytes
            | _kw_: tlist, free, list heap
   }}*/
/*{{|desc: Returns to the list heap a block previously obtained with _tlist_alloc_bytes on the same list.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `p` void * - Block to free.

    Returns void }}*/
OT4XB_API void  _tlist_free_bytes( void* ls, void* p ) {	reinterpret_cast<TList*>( ls )->free_bytes( p );}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_set_granularity
            | syntax_: `void _tlist_set_granularity( void * ls, DWORD nn )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_set_granularity
            | _kw_: tlist, growth step, granularity
   }}*/
/*{{|desc: Sets how many slots the capacity grows by when the list is full. The value is clamped to
      0xFFFF and its low four bits are forced on, so the real growth step (value + 1) is a multiple of 16.
    | params:
    - `ls` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `nn` DWORD - Requested granularity; a new list starts at 15 (steps of 16 slots).

    Returns void }}*/
OT4XB_API void   _tlist_set_granularity(void* ls,DWORD nn)
{
   if( nn > 0xFFFF ){ nn = 0xFFFF; }
   reinterpret_cast<TList*>(ls)->m_nGrowBy = (nn | 0x0F);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_serialize
            | syntax_: ```
                 DWORD _tlist_serialize( void * pList, DWORD record_size, DWORD dwStart, DWORD dwCount, HANDLE hFile )
              ```
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_serialize
            | _kw_: tlist, serialize, write records, file
   }}*/
/*{{|desc: Writes the memory blocks referenced by the list items to an open file, one fixed size record
      of record_size bytes per item. Items holding NULL are skipped.
    | params:
    - `pList` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `record_size` DWORD - Bytes written from each block; must be positive as a signed int.
    - `dwStart` DWORD - Index of the first record to write (0-based); 0 when it exceeds the item count.
    - `dwCount` DWORD - Maximum number of records to write; clamped to the item count minus dwStart.
    - `hFile` HANDLE - Open Win32 file handle, written at its current position.

    Returns DWORD - Number of records written. (DWORD) -1 on bad arguments, (DWORD) -3 when a WriteFile
      call fails. }}*/
OT4XB_API DWORD _tlist_serialize(void* pList, DWORD record_size , DWORD dwStart , DWORD dwCount , HANDLE hFile)
{
   TList* ls = reinterpret_cast<TList*>(pList);
   if( !( ls && hFile && (hFile != INVALID_HANDLE_VALUE) && (((int) record_size) > 0) ) ){ return (DWORD) -1; }
   if( dwStart > ls->Count() ){return 0;}
   DWORD dwMax =  ls->Count() - dwStart;
   if( dwCount > dwMax ){ dwCount = dwMax; }
   DWORD dw;
   dwMax = dwStart + dwCount; dwCount = 0;
   for( dw = dwStart; dw < dwMax; dw++ )
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_unserialize
            | syntax_: ```
                 DWORD _tlist_unserialize( void * pList, DWORD record_size, DWORD dwMax, HANDLE hFile, OT4XB_VHEAP * vh )
              ```
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_unserialize
            | _kw_: tlist, unserialize, read records, file
   }}*/
/*{{|desc: Reads fixed size records from an open file; each record is allocated as a separate block,
      filled from the file and appended to the list.
    | params:
    - `pList` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `record_size` DWORD - Bytes of one record; must be positive as a signed int.
    - `dwMax` DWORD - Maximum number of records to read; (DWORD) -1 reads until the end of the file.
    - `hFile` HANDLE - Open Win32 file handle, read from its current position.
    - `vh` OT4XB_VHEAP * - Heap each record block is allocated from; NULL uses the internal ot4xb
      heap.

    Returns DWORD - Number of records appended. (DWORD) -1 on bad arguments, (DWORD) -2 when an
      allocation fails, (DWORD) -4 when a ReadFile call fails. A trailing partial record is discarded. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_free_simple_items
            | syntax_: `void _tlist_free_simple_items( void * pList, DWORD nStart, DWORD nEnd, OT4XB_VHEAP * vh )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_free_simple_items
            | _kw_: tlist, free items, release blocks, range
   }}*/
/*{{|desc: Frees the blocks referenced by a range of items and stores NULL in their slots. The item count
      does not change.
    | params:
    - `pList` void * - List pointer returned by _tlist_new or _tlist_new_ex.
    - `nStart` DWORD - Zero-based position of the first item to free.
    - `nEnd` DWORD - Position after the last item to free; clamped to the item count.
    - `vh` OT4XB_VHEAP * - Heap the blocks were allocated from; NULL uses the internal ot4xb heap.

    Returns void }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_combi
            | syntax_: `int _tlist_cbk_cmp_combi( DWORD* ctx, void** pp1, void** pp2 )`
            | header: ot4xb_TLists.h
            | category: c-api/tlist
            | mangled-name: _tlist_cbk_cmp_combi
            | _kw_: tlist comparator, multi key, sort rules, chain
   }}*/
/*{{|desc: Multi-key comparator for the list sort and search functions: runs a chain of rule comparators
      in order and returns the first non-zero result. NULL items sort before non-NULL items.
    | params:
    - `ctx` DWORD * - Rule table: ctx[0] rule count, ctx[1] size of one rule in bytes (at least 24);
      the rules follow from byte offset 8. Each rule starts with the address of an __cdecl comparator and
      the rest of the rule is passed to it as its own ctx, so the _tlist_cbk_cmp_* helpers fit as rules.
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - First non-zero rule result (negative or positive), 0 when all rules report equal.
      Always 0 when ctx[1] is below 24. }}*/
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
/*{{end-c-function}}*/
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
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmpi_cb
            | syntax_: `int _tlist_cbk_cmpi_cb( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmpi_cb
            | _kw_: tlist comparator, byte range, case insensitive, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a byte range at a fixed offset
      inside both items, case insensitive through the ANSI lower case table. The stored item pointers
      must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, cb, descend, indirection }: byte offset of the field,
      bytes to compare, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmpi_cb( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   int n = _bcmpwithtable( _mk_ptr_(LPBYTE,pp1[0],ctx[0]) , _mk_ptr_(LPBYTE,pp2[0],ctx[0]),ctx[1], _lower_ansi_char_table_ );
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_cb
            | syntax_: `int _tlist_cbk_cmp_cb( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_cb
            | _kw_: tlist comparator, byte range, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a byte range at a fixed offset
      inside both items as raw unsigned bytes (case sensitive). The stored item pointers must not be
      NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, cb, descend, indirection }: byte offset of the field,
      bytes to compare, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_cb( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   int n = _bcmp( _mk_ptr_(LPBYTE , pp1[0] , ctx[0] ),_mk_ptr_(LPBYTE , pp2[0] , ctx[0] ),ctx[1]);
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_char
            | syntax_: `int _tlist_cbk_cmp_char( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_char
            | _kw_: tlist comparator, char field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a signed char field at a fixed
      offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (low byte used, 0 for none), non-zero to reverse the order, pointer
      hops to follow from each item before comparing (a NULL met on a hop ends the compare, NULL sorting
      first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_char( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   char dw1  = *_mk_ptr_(LPSTR , pp1[0] , ctx[0] );
   char dw2  = *_mk_ptr_(LPSTR , pp2[0] , ctx[0] );
   char mask = (char) LOBYTE(LOWORD(ctx[1])); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_BYTE
            | syntax_: `int _tlist_cbk_cmp_BYTE( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_BYTE
            | _kw_: tlist comparator, BYTE field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares an unsigned BYTE field at a fixed
      offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (low byte used, 0 for none), non-zero to reverse the order, pointer
      hops to follow from each item before comparing (a NULL met on a hop ends the compare, NULL sorting
      first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_BYTE( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   BYTE dw1 = *_mk_ptr_(LPBYTE , pp1[0] , ctx[0] );
   BYTE dw2 = *_mk_ptr_(LPBYTE , pp2[0] , ctx[0] );
   BYTE mask = LOBYTE(LOWORD(ctx[1])); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_short
            | syntax_: `int _tlist_cbk_cmp_short( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_short
            | _kw_: tlist comparator, short field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a signed short field at a fixed
      offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (low word used, 0 for none), non-zero to reverse the order, pointer
      hops to follow from each item before comparing (a NULL met on a hop ends the compare, NULL sorting
      first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_short( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   short dw1 = *_mk_ptr_(LPSHORT, pp1[0] , ctx[0] );
   short dw2 = *_mk_ptr_(LPSHORT , pp2[0] , ctx[0] );
   short mask = (short) LOWORD(ctx[1]); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_WORD
            | syntax_: `int _tlist_cbk_cmp_WORD( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_WORD
            | _kw_: tlist comparator, WORD field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares an unsigned WORD field at a fixed
      offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (low word used, 0 for none), non-zero to reverse the order, pointer
      hops to follow from each item before comparing (a NULL met on a hop ends the compare, NULL sorting
      first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_WORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   WORD dw1 = *_mk_ptr_(LPWORD , pp1[0] , ctx[0] );
   WORD dw2 = *_mk_ptr_(LPWORD , pp2[0] , ctx[0] );
   WORD mask = LOWORD(ctx[1]); if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_LONG
            | syntax_: `int _tlist_cbk_cmp_LONG( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_LONG
            | _kw_: tlist comparator, LONG field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a signed LONG field at a fixed
      offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (0 for none), non-zero to reverse the order, pointer hops to follow
      from each item before comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_LONG( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   LONG dw1 = *_mk_ptr_(LPLONG , pp1[0] , ctx[0] );
   LONG dw2 = *_mk_ptr_(LPLONG , pp2[0] , ctx[0] );
   LONG mask = (LONG) ctx[1]; if( mask ){ dw1 &= mask; dw2 &= mask; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_DWORD
            | syntax_: `int _tlist_cbk_cmp_DWORD( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_DWORD
            | _kw_: tlist comparator, DWORD field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares an unsigned DWORD field at a
      fixed offset inside both items, optionally AND masked. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, mask, descend, indirection }: byte offset of the
      field, AND mask for both values (0 for none), non-zero to reverse the order, pointer hops to follow
      from each item before comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_DWORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   DWORD dw1 = *_mk_ptr_(LPDWORD , pp1[0] , ctx[0] );
   DWORD dw2 = *_mk_ptr_(LPDWORD , pp2[0] , ctx[0] );
   if( ctx[1] ){ dw1 &= ctx[1]; dw2 &= ctx[1]; }
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_LONGLONG
            | syntax_: `int _tlist_cbk_cmp_LONGLONG( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_LONGLONG
            | _kw_: tlist comparator, LONGLONG field, int64, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a signed LONGLONG field at a
      fixed offset inside both items. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, 0, descend, indirection }: byte offset of the field,
      ctx[1] unused, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_LONGLONG( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   LONGLONG dw1 = *_mk_ptr_(LPLONGLONG , pp1[0] , ctx[0] );
   LONGLONG dw2 = *_mk_ptr_(LPLONGLONG , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_QWORD
            | syntax_: `int _tlist_cbk_cmp_QWORD( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_QWORD
            | _kw_: tlist comparator, QWORD field, uint64, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares an unsigned 64 bit (ULONGLONG)
      field at a fixed offset inside both items. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, 0, descend, indirection }: byte offset of the field,
      ctx[1] unused, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_QWORD( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   ULONGLONG dw1 = *_mk_ptr_(LPULONGLONG , pp1[0] , ctx[0] );
   ULONGLONG dw2 = *_mk_ptr_(LPULONGLONG , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_float
            | syntax_: `int _tlist_cbk_cmp_float( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_float
            | _kw_: tlist comparator, float field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a float field at a fixed offset
      inside both items. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, 0, descend, indirection }: byte offset of the field,
      ctx[1] unused, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_float( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   float dw1 = *_mk_ptr_(LPFLOAT , pp1[0] , ctx[0] );
   float dw2 = *_mk_ptr_(LPFLOAT , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _tlist_cbk_cmp_double
            | syntax_: `int _tlist_cbk_cmp_double( DWORD * ctx, void * * pp1, void * * pp2 )`
            | category: c-api/tlist
            | header: ot4xb_TLists.h
            | mangled-name: _tlist_cbk_cmp_double
            | _kw_: tlist comparator, double field, offset
   }}*/
/*{{|desc: Comparator for the list sort and search functions: compares a double field at a fixed offset
      inside both items. The stored item pointers must not be NULL.
    | params:
    - `ctx` DWORD * - DWORD ctx[4] = { offset, 0, descend, indirection }: byte offset of the field,
      ctx[1] unused, non-zero to reverse the order, pointer hops to follow from each item before
      comparing (a NULL met on a hop ends the compare, NULL sorting first).
    - `pp1` void * * - Address of the first item slot to compare.
    - `pp2` void * * - Address of the second item slot to compare.

    Returns int - -1, 0 or 1 as the first field compares below, equal or above the second. }}*/
OT4XB_API int __cdecl _tlist_cbk_cmp_double( DWORD* ctx, void** pp1,void** pp2)
{
   int r = 0; if( _tlist_cmp_resolve_indirection_level(ctx,pp1,pp2,r)){ return r; }
   double dw1 = *_mk_ptr_(LPDOUBLE , pp1[0] , ctx[0] );
   double dw2 = *_mk_ptr_(LPDOUBLE , pp2[0] , ctx[0] );
   int n = ( ( dw1 == dw2 ) ?  0 : (dw1 > dw2 ? 1 : -1));
   return ( ctx[2]  ? -n : n );
}
/*{{end-c-function}}*/
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
   return  ((r - ((DWORD) m_pItems)) >> 2 );
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
   return  ((r - ((DWORD) m_pItems)) >> 2 );
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
      if(m_pItems[n] != NULLCONTAINER) _conRelease(m_pItems[n]);
      m_pItems[n] = NULLCONTAINER;
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

