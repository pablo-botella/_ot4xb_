//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <malloc.h>
#include <shlwapi.h>
//----------------------------------------------------------------------------------------------------------------------
#define PLKSTREX_PARLEN( plk , np ) ((_partype(pl,np) & XPP_NUMERIC) ? _parLong(pl,np) : ((plk.nLen)) )
#define PLKSTREX_PARLENT( plk , np, es ) ((_partype(pl,np)&XPP_NUMERIC)?_parLong(pl,np):((LONG)((plk.nLen)/sizeof(##es))))
//----------------------------------------------------------------------------------------------------------------------
#define MYHEAPFLAGS    (HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY)
//----------------------------------------------------------------------------------------------------------------------
static void __xb__grab(XppParamList pl, void * (*pfnGrab)(UINT) );
static void __xb__free(XppParamList pl, void (*pfnFree)(void *) );
//----------------------------------------------------------------------------------------------------------------------
typedef BOOL (WINAPI *HeapSetInfoFT_ )(void*,int,void*,UINT );
//----------------------------------------------------------------------------------------------------------------------
static HANDLE hHeap_p = (HANDLE) 0;
static HANDLE h_interlocked_heap = 0;
static HANDLE h_exec_heap = 0;
static LPLONG s_p_interlocked_counter = 0;
BYTE _lower_ansi_char_table_[256];
BYTE _lower_ansi_char_table_09az_[256];
// -----------------------------------------------------------------------------------------------------------------
OT4XB_VHEAP ot4xb_xheap =  {ot4xb_xheap_alloc,ot4xb_xheap_free,0,0,0,0};
//----------------------------------------------------------------------------------------------------------------------
static SYSTEM_INFO _sys_inf_;
//----------------------------------------------------------------------------------------------------------------------
static LONG  _xgrab_count_ = 0;
//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
extern "C" OT4XB_API BOOL __cdecl begin_xwatch_thread(void);
extern "C" OT4XB_API LONG  __cdecl end_xwatch_thread(void);
extern "C" OT4XB_API void  __cdecl on_xwatch_thread(LONG n);
static DWORD _watching_thread_ = 0;
static LONG  _watching_thread_count = 0;
#endif
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_get_xheap
            | syntax_: `OT4XB_VHEAP * ot4xb_get_xheap( void )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_get_xheap
            | _kw_: vheap, heap descriptor, xheap, allocator
   }}*/
/*{{|desc: Returns the built-in OT4XB_VHEAP descriptor whose vgrab/vfree entries route to _xgrab() and
      _xfree(). It lets code working through the OT4XB_VHEAP interface allocate from the default OT4XB
      allocator.

    Returns OT4XB_VHEAP * - Pointer to the global descriptor of the library; never destroy it. }}*/
OT4XB_API OT4XB_VHEAP*  ot4xb_get_xheap(void)
{
   return &ot4xb_xheap;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_xheap_alloc
            | syntax_: `void * ot4xb_xheap_alloc( OT4XB_VHEAP * OT4XB_VHEAP * OT4XB_VHEAP*, UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_xheap_alloc
            | _kw_: vheap, xheap, allocate, vgrab
   }}*/
/*{{|desc: vgrab entry of the built-in xheap descriptor: allocates n bytes with _xgrab(), so the block comes
      zero-filled. The descriptor argument is ignored. Release with ot4xb_xheap_free() or _xfree().
    | params:
    - `OT4XB_VHEAP*` OT4XB_VHEAP * OT4XB_VHEAP * - Ignored; present to match the vgrab signature.
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the zero-filled block. }}*/
OT4XB_API void* __cdecl ot4xb_xheap_alloc( OT4XB_VHEAP*  , UINT  n)
{
   return _xgrab(n);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_xheap_free
            | syntax_: `void ot4xb_xheap_free( OT4XB_VHEAP * OT4XB_VHEAP * OT4XB_VHEAP*, void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_xheap_free
            | _kw_: vheap, xheap, free, vfree
   }}*/
/*{{|desc: vfree entry of the built-in xheap descriptor: releases the block with _xfree(). The descriptor
      argument is ignored.
    | params:
    - `OT4XB_VHEAP*` OT4XB_VHEAP * OT4XB_VHEAP * - Ignored; present to match the vfree signature.
    - `p` void * - Block allocated with ot4xb_xheap_alloc() or _xgrab().

    Returns void }}*/
OT4XB_API void  __cdecl ot4xb_xheap_free( OT4XB_VHEAP*  , void* p)
{
   _xfree(p);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_xheap_min
            | syntax_: `int ot4xb_xheap_min( void )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_xheap_min
            | _kw_: heapmin, return memory, shrink heap, CRT heap
   }}*/
/*{{|desc: Returns unused CRT heap memory to the operating system by calling _heapmin().

    Returns int - 0 on success, -1 on failure. }}*/
OT4XB_API int  __cdecl ot4xb_xheap_min(void)
{
   return _heapmin();
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_vheap_alloc
            | syntax_: `void * ot4xb_vheap_alloc( OT4XB_VHEAP * vh, UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_vheap_alloc
            | _kw_: vheap, private heap, allocate, HeapAlloc
   }}*/
/*{{|desc: vgrab entry used by descriptors built with ot4xb_vheap_create(): allocates n bytes from the Win32
      heap kept in vh->ctx, using the vh->flags1 allocation flags.
    | params:
    - `vh` OT4XB_VHEAP * - Heap descriptor created with ot4xb_vheap_create().
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the new block. With the default flags it is zero-filled and a failure
      raises an exception instead of returning NULL. }}*/
OT4XB_API void* __cdecl ot4xb_vheap_alloc( OT4XB_VHEAP* vh  , UINT  n)
{
   return HeapAlloc((HANDLE) vh->ctx,vh->flags1,n);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_vheap_free
            | syntax_: `void ot4xb_vheap_free( OT4XB_VHEAP * vh, void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_vheap_free
            | _kw_: vheap, private heap, free, HeapFree
   }}*/
/*{{|desc: vfree entry used by descriptors built with ot4xb_vheap_create(): releases a block allocated from
      the Win32 heap kept in vh->ctx, using the vh->flags2 flags.
    | params:
    - `vh` OT4XB_VHEAP * - Heap descriptor the block was allocated from.
    - `p` void * - Block allocated with ot4xb_vheap_alloc() on the same descriptor.

    Returns void }}*/
OT4XB_API void  __cdecl ot4xb_vheap_free( OT4XB_VHEAP*  vh , void* p)
{
   HeapFree( (HANDLE) vh->ctx,vh->flags2,p);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_vheap_destroy
            | syntax_: `void ot4xb_vheap_destroy( OT4XB_VHEAP * vheap )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_vheap_destroy
            | _kw_: vheap, private heap, destroy, HeapDestroy, release all
   }}*/
/*{{|desc: Destroys a virtual heap created with ot4xb_vheap_create(): the Win32 heap is destroyed - every
      block allocated from it vanishes at once - and the descriptor itself is released.
    | params:
    - `vheap` OT4XB_VHEAP * - Descriptor created with ot4xb_vheap_create(); NULL is ignored.

    Returns void }}*/
OT4XB_API void __cdecl ot4xb_vheap_destroy( OT4XB_VHEAP* vheap)
{
	if ( vheap )
	{
		if ( vheap->ctx )
		{
			HeapDestroy( (HANDLE) vheap->ctx );
			vheap->ctx = 0;
		}
		_xfree( (void*) vheap );
	}
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_vheap_create
            | syntax_: `OT4XB_VHEAP * ot4xb_vheap_create( DWORD dwCreationFlags, DWORD dwInitialSize, DWORD dwMaxSize )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_vheap_create
            | _kw_: vheap, private heap, create, HeapCreate, descriptor
   }}*/
/*{{|desc: Creates a private Win32 heap (HeapCreate) and wraps it in a new OT4XB_VHEAP descriptor with
      vgrab/vfree set to ot4xb_vheap_alloc()/ot4xb_vheap_free() and both flags fields preset to
      HEAP_GENERATE_EXCEPTIONS plus HEAP_ZERO_MEMORY. Destroy it with ot4xb_vheap_destroy().
    | params:
    - `dwCreationFlags` DWORD - HeapCreate() options.
    - `dwInitialSize` DWORD - Initial committed size in bytes; 0 commits one page.
    - `dwMaxSize` DWORD - Maximum heap size in bytes, or 0 for a growable heap.

    Returns OT4XB_VHEAP * - Pointer to the new descriptor. }}*/
OT4XB_API OT4XB_VHEAP* __cdecl ot4xb_vheap_create( DWORD dwCreationFlags, DWORD dwInitialSize, DWORD dwMaxSize )
{
	OT4XB_VHEAP* vheap = (OT4XB_VHEAP*) _xgrab( sizeof( OT4XB_VHEAP ) );
	ZeroMemory( vheap, sizeof( OT4XB_VHEAP ) );
	vheap->ctx = (DWORD) HeapCreate( dwCreationFlags, dwInitialSize, dwMaxSize );
	vheap->flags1 = HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY;
	vheap->flags2 = HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY;
	vheap->vgrab = ot4xb_vheap_alloc;
	vheap->vfree = ot4xb_vheap_free;
	return vheap;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_interlocked_next
            | syntax_: `LONG ot4xb_interlocked_next( void )`
            | category: atomic
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_interlocked_next
            | _kw_: unique id, counter, interlocked, thread safe, sequence
   }}*/
/*{{|desc: return a new integer id unique in the instance, thread safe

    Returns LONG next incremented integer  id, 0 if the interlocked counter is not initialized }}*/
OT4XB_API LONG __cdecl ot4xb_interlocked_next(void)
{
   if( s_p_interlocked_counter )
   {
      return InterlockedIncrement( s_p_interlocked_counter );
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
void _API_Memory_InitProc( void)
{
    DWORD dw;
    hHeap_p = GetProcessHeap();
    h_interlocked_heap = HeapCreate(HEAP_GENERATE_EXCEPTIONS,0,0);
    h_exec_heap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE,0,0);
    s_p_interlocked_counter = (LPLONG) ot4xb_interlocked_alloc();

    for( dw = 0; dw < 256 ; dw++ ){ _lower_ansi_char_table_[dw] = (BYTE) ( 0xFF & dw ); }
    CharLowerBuff( (LPSTR) _lower_ansi_char_table_ , 256 );
    for( dw = 0; dw < 256 ; dw++ )
    {
       BYTE ch = _lower_ansi_char_table_[dw];
       if( (ch >= (BYTE) '0') && (ch <= (BYTE) '9') ){ _lower_ansi_char_table_09az_[dw] = ch; }
       else if( (ch >= (BYTE) 'a') && (ch <= (BYTE) 'z') ){ _lower_ansi_char_table_09az_[dw] = ch; }
       else {_lower_ansi_char_table_09az_[dw] = 0;}
    }
}
//----------------------------------------------------------------------------------------------------------------------
void _API_Memory_InitProcXBase( void)
{

    GetSystemInfo( &_sys_inf_ );
    /*
    HINSTANCE hKernel = GetModuleHandle("kernel32");
    if( hKernel != 0 )
    {
       HeapSetInfoFT_  pf = ( HeapSetInfoFT_ ) GetProcAddress( hKernel , "HeapSetInformation");
       if( pf )
       {
          ULONG ul = 2;
          (*pf)( GetProcessHeap() , HeapCompatibilityInformation ,&ul, sizeof(ULONG) );

       }
    }
    */
}
//----------------------------------------------------------------------------------------------------------------------
// INTERNAL
void _API_Memory_ExitProc( void)
{
    ot4xb_interlocked_free( (void*) s_p_interlocked_counter );
    s_p_interlocked_counter = 0;
    HeapDestroy(h_interlocked_heap);
    h_interlocked_heap = 0;
    HeapDestroy(h_exec_heap);
    h_exec_heap = 0;
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _vpagesize
            | syntax_: `UINT _vpagesize( void )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _vpagesize
            | _kw_: page size, virtual memory, VirtualAlloc, allocation granularity
   }}*/
/*{{|desc: Returns the block size that makes a _vgrab() allocation fit exactly in one memory page: the
      system page size minus the 4-byte size header _vgrab() keeps in front of every block.

    Returns UINT - System page size in bytes minus 4. }}*/
OT4XB_API UINT _vpagesize(void){ return (UINT)( _sys_inf_.dwPageSize  - sizeof( UINT) );}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _vgrab1page
            | syntax_: `void * _vgrab1page( UINT * pnSize )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _vgrab1page
            | _kw_: virtual memory, one page, VirtualAlloc, locked memory
   }}*/
/*{{|desc: Allocates one page of virtual memory with _vgrab(), asking for _vpagesize() bytes. Release with
      _vfree().
    | params:
    - `pnSize` UINT * - Optional; when not NULL receives the usable size of the block.

    Returns void * - Pointer to the new block. }}*/
OT4XB_API void * _vgrab1page(UINT * pnSize )
{
   UINT nSize = _vpagesize();
   if( pnSize) pnSize[0] = nSize;
   return _vgrab(nSize);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _vgrab
            | syntax_: `void * _vgrab( UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _vgrab
            | _kw_: virtual memory, VirtualAlloc, VirtualLock, allocate, non paged
   }}*/
/*{{|desc: Allocates n bytes of virtual memory (VirtualAlloc, MEM_COMMIT, PAGE_READWRITE) and locks the
      region into physical memory. The block is zero-filled and a 4-byte size header sits in front of the
      returned pointer, so the committed space is n + 4 rounded up to whole pages. Release with _vfree().
    | params:
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the usable area, 4 bytes past the start of the committed region. }}*/
OT4XB_API void * _vgrab( UINT n)
{
   LPBYTE  p;
   UINT * pn;
   p = (LPBYTE ) VirtualAlloc(NULL,n + sizeof(UINT) ,MEM_COMMIT,PAGE_READWRITE);
   VirtualLock((void*) p,n);
   pn = (UINT *) p;
   pn[0] = n + sizeof(UINT);
   return (void *) (p + sizeof(UINT));
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _vgetsize
            | syntax_: `UINT _vgetsize( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _vgetsize
            | _kw_: block size, virtual memory, header, allocated size
   }}*/
/*{{|desc: Returns the size stored in the header of a block allocated with _vgrab() or _vgrab1page(). The
      stored value includes the 4-byte header itself, so it is the requested size plus 4.
    | params:
    - `p` void * - Block pointer, or NULL.

    Returns UINT - Stored size (requested bytes + 4), or 0 when p is NULL. }}*/
OT4XB_API UINT _vgetsize( void * p)
{
   if( p )
   {
      LPBYTE pp = ((LPBYTE) p)  - sizeof(UINT);
      UINT * pn = (UINT *) pp;
      return pn[0];
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _vfree
            | syntax_: `void _vfree( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _vfree
            | _kw_: virtual memory, VirtualFree, release
   }}*/
/*{{|desc: release a block of memory allocated with _vgrab() or _vgrab1page()
    | params:
    - `p` void * - Block allocated with _vgrab() or _vgrab1page().

    Returns void }}*/
OT4XB_API void _vfree( void * p)
{
   LPBYTE pp = ((LPBYTE) p)  - sizeof(UINT);
   UINT * pn = (UINT *) pp;
   UINT n    = pn[0];
   VirtualUnlock((void *) pp,n);
   VirtualFree((void*) pp,n,MEM_RELEASE);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pgrab
            | syntax_: `void * _pgrab( UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _pgrab
            | _kw_: process heap, HeapAlloc, allocate, zero filled
   }}*/
/*{{|desc: Allocates n zero-filled bytes from the default process heap (HeapAlloc). Release with _pfree().
    | params:
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the zero-filled block; on failure an exception is raised instead of
      returning NULL (the heap is used with HEAP_GENERATE_EXCEPTIONS). }}*/
OT4XB_API void * _pgrab( UINT n)
{
     return HeapAlloc( hHeap_p , MYHEAPFLAGS , n );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pfree
            | syntax_: `void _pfree( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _pfree
            | _kw_: process heap, HeapFree, release
   }}*/
/*{{|desc: release memory allocated with _pgrab()
    | params:
    - `p` void * - Block allocated with _pgrab().

    Returns void }}*/
OT4XB_API void _pfree( void * p)
{
   HeapFree(hHeap_p,0,p);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _exec_m_grab
            | syntax_: `void * _exec_m_grab( UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _exec_m_grab
            | _kw_: executable memory, executable heap, thunk, code buffer, RWX
   }}*/
/*{{|desc: Allocates n zero-filled bytes from the executable heap (HEAP_CREATE_ENABLE_EXECUTE) for runtime
      code thunks / callbacks; the returned block may be executed and stays valid under DEP. Release with
      _exec_m_free().
    | params:
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the zero-filled executable block. }}*/
OT4XB_API void * _exec_m_grab( UINT n)
{
     return HeapAlloc( h_exec_heap , MYHEAPFLAGS , n );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _exec_m_free
            | syntax_: `void _exec_m_free( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _exec_m_free
            | _kw_: executable memory, executable heap, release
   }}*/
/*{{|desc: release memory allocated with _exec_m_grab()
    | params:
    - `p` void * - Block allocated with _exec_m_grab().

    Returns void }}*/
OT4XB_API void _exec_m_free( void * p)
{
   HeapFree( h_exec_heap , 0 , p );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xgrab
            | syntax_: `void * _xgrab( UINT n )`
            | category: memory
            | header: ot4xb_api.h
            | mangled-name: _xgrab
            | _kw_: malloc, allocate, zero filled, default allocator, memory
   }}*/
/*{{|desc: Allocates n bytes with malloc() and zero-fills them. This is the default OT4XB allocator and the
      preferred allocation method. Release with _xfree().
    | params:
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the zero-filled block. }}*/
OT4XB_API void * _xgrab( UINT n)
{
     void * p = malloc(n);
     ZeroMemory(p,n);
     InterlockedIncrement(&_xgrab_count_);
#ifdef _DEBUG
     on_xwatch_thread(1);
#endif
     return p;

}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xgrow
            | syntax_: `void * _xgrow( void * pp, UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _xgrow
            | _kw_: realloc, grow block, resize memory
   }}*/
/*{{|desc: Grows a block to n bytes with realloc. NOTE (doc review): does NOT zero-fill the grown area, unlike
      _xgrab/_xxgrow - it cannot, the previous size is unknown here (realloc does not report it). Use
      _xxgrow( pp, nCurrent, nNew ) when the grown tail must be zeroed.
    | params:
    - `pp` void * - Block to resize, or NULL to allocate a new one.
    - `n` UINT - New size in bytes.

    Returns void * - Pointer to the resized block; it may have moved. }}*/
OT4XB_API void * _xgrow(void* pp  , UINT n)
{
     void * p = realloc(pp,n);
     return p;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xxgrow
            | syntax_: `void * _xxgrow( void * pp, UINT nCurrent, UINT nNew )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _xxgrow
            | _kw_: realloc, grow block, resize memory, zero filled
   }}*/
/*{{|desc: Resizes a _xgrab() block from nCurrent to nNew bytes keeping the zero-fill promise. Growing
      allocates a new zero-filled block, copies nCurrent bytes and releases the old block, so the pointer
      changes. Shrinking keeps the block and just clears the bytes past nNew.
    | params:
    - `pp` void * - Block allocated with _xgrab().
    - `nCurrent` UINT - Current size in bytes; the caller must supply it.
    - `nNew` UINT - Requested size in bytes.

    Returns void * - Pointer to the resized block; a new pointer when the block grew. }}*/
OT4XB_API void* _xxgrow(void* pp ,UINT nCurrent , UINT nNew)
{
   void* p;
   if( nCurrent == nNew ){ return pp; }
   if( nCurrent > nNew ){ _bset( _mk_ptr_(LPBYTE,pp,nNew),0,nCurrent - nNew); return pp;}

   p = _xgrab(nNew);
   _bcopy((LPBYTE) p , (LPBYTE) pp, nCurrent );
   _xfree(pp);
   return p;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xxgrowa
            | syntax_: `void * _xxgrowa( void * pp, UINT nCurrent, UINT nNew, UINT nItemSize )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _xxgrowa
            | _kw_: realloc, grow array, resize memory, items, zero filled
   }}*/
/*{{|desc: Array version of _xxgrow(): resizes a _xgrab() block from nCurrent to nNew items of nItemSize
      bytes each. Item counts are turned into byte sizes and the _xxgrow() rules apply.
    | params:
    - `pp` void * - Block allocated with _xgrab().
    - `nCurrent` UINT - Current number of items.
    - `nNew` UINT - Requested number of items.
    - `nItemSize` UINT - Size of one item in bytes.

    Returns void * - Pointer to the resized block; a new pointer when the block grew. }}*/
OT4XB_API void* _xxgrowa(void* pp ,UINT nCurrent , UINT nNew , UINT nItemSize)
{
   return _xxgrow(pp,nCurrent * nItemSize, nNew * nItemSize);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _mgrab
            | syntax_: `void * _mgrab( UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _mgrab
            | _kw_: malloc, allocate, uninitialized, memory
   }}*/
/*{{|desc: Allocates n bytes with malloc() without clearing them; unlike _xgrab() the content is undefined.
      Release with _mfree().
    | params:
    - `n` UINT - Number of bytes to allocate.

    Returns void * - Pointer to the uninitialized block. }}*/
OT4XB_API void * _mgrab( UINT n)
{
     InterlockedIncrement(&_xgrab_count_);
#ifdef _DEBUG
     on_xwatch_thread(1);
#endif
     return malloc(n);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xfree
            | syntax_: `void _xfree( void * p )`
            | category: memory
            | header: ot4xb_api.h
            | mangled-name: _xfree
            | _kw_: free, release memory, malloc
   }}*/
/*{{|desc: Release memory allocated with _xgrab()
    | params:
    - `p` void * - Block allocated with _xgrab().

    Returns void }}*/
OT4XB_API void _xfree( void * p)
{
   free(p);
   InterlockedDecrement(&_xgrab_count_);
#ifdef _DEBUG
   on_xwatch_thread(-1);
#endif
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _mfree
            | syntax_: `void _mfree( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _mfree
            | _kw_: free, release memory, malloc
   }}*/
/*{{|desc: Release memory allocated with _mgrab()
    | params:
    - `p` void * - Block allocated with _mgrab().

    Returns void }}*/
OT4XB_API void _mfree( void * p)
{
   InterlockedDecrement(&_xgrab_count_);
#ifdef _DEBUG
   on_xwatch_thread(-1);
#endif
   free(p);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _mmsize
            | syntax_: `UINT _mmsize( void * p )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _mmsize
            | _kw_: _msize, block size, malloc, usable size
   }}*/
/*{{|desc: Returns the usable size of a malloc-based block, as reported by the CRT _msize().
    | params:
    - `p` void * - Block allocated with _mgrab(), _xgrab() or another malloc-based grab.

    Returns UINT - Size of the block in bytes. }}*/
OT4XB_API UINT _mmsize(void* p){ return _msize(p);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _mgrow
            | syntax_: `void * _mgrow( void * pp, UINT n )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _mgrow
            | _kw_: realloc, grow block, resize memory
   }}*/
/*{{|desc: Resizes a malloc-based block with realloc(). The grown area is not cleared and the block may
      move; pp may be NULL to allocate a new block.
    | params:
    - `pp` void * - Block to resize, or NULL.
    - `n` UINT - New size in bytes.

    Returns void * - Pointer to the resized block. }}*/
OT4XB_API void * _mgrow(void* pp  , UINT n){ return realloc(pp,n);}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _mcgrab
            | syntax_: `void * _mcgrab( UINT nItems, UINT nItemSize )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _mcgrab
            | _kw_: calloc, allocate array, zero filled, items
   }}*/
/*{{|desc: Allocates a zero-filled array of nItems items of nItemSize bytes each with calloc(). Release with
      _mfree().
    | params:
    - `nItems` UINT - Number of items.
    - `nItemSize` UINT - Size of one item in bytes.

    Returns void * - Pointer to the zero-filled block. }}*/
OT4XB_API void * _mcgrab(UINT nItems , UINT nItemSize ){ return calloc(nItems , nItemSize );}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xgrab_count_
            | syntax_: `_xgrab_count_()`
            | category: memory
            | _kw_: leak counter, allocation count, diagnostic, deprecated
   }}*/
/*{{|desc: Deprecated diagnostic counter for selected _xgrab() allocations that have not been released.

    Returns Numeric - Current value of the internal diagnostic counter.

    |note: Deprecated. This counter is incomplete: it only tracks some allocation paths and excludes many
      cases, so it must not be used as a general memory-leak detector. It may still be useful occasionally while
      debugging a narrow _xgrab() path, but it can be removed in the future. }}*/
XPPRET XPPENTRY _XGRAB_COUNT_(XppParamList pl){ _retnl(pl,_xgrab_count_);}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xgrab
            | syntax_: `_xgrab( nBytes )`
            | category: memory
            | _kw_: allocate memory, malloc, zero filled, pointer, buffer
   }}*/
/*{{|desc: Allocates a memory block using the current malloc/free based OT4XB allocator and initializes it with
      zeroes.
    | params:
    - `nBytes` Numeric - Number of bytes to allocate. If zero, NIL is returned.
    - `cValue` Character - Optional source buffer copied into the newly allocated block.
    - `@nBytes` Numeric by reference - Receives the allocated size when cValue is used. The size includes
      room for a terminating zero byte.
    - `lUseMinSize` Logical - When .T., the supplied @nBytes value is used as a minimum allocation size.

    Returns Numeric/NIL - Pointer to the allocated memory block, or NIL when no block is allocated.

    |note: Also _xgrab( cValue, @nBytes [, lUseMinSize] ) -> pMem

    |note: The current implementation uses malloc() and then clears the allocated bytes with ZeroMemory().
      Memory returned by _xgrab() must be released with _xfree(). This is the usual allocation pair for OT4XB
      code. }}*/
XPPRET XPPENTRY _XGRAB(XppParamList pl){  __xb__grab(pl, _xgrab ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xfree
            | syntax_: `_xfree( pMem [, @cValue [, nBytes]] )`
            | category: memory
            | _kw_: free memory, release, pointer
   }}*/
/*{{|desc: Releases a memory block allocated with _xgrab().
    | params:
    - `pMem` Numeric - Pointer returned by _xgrab().
    - `@cValue` Character by reference - Optional variable that receives bytes copied from pMem before the
      block is released.
    - `nBytes` Numeric - Number of bytes to copy into @cValue before releasing pMem.

    Returns NIL

    |note: The current implementation releases the block with free(). The optional @cValue copy is a
      convenience for returning data from a pointer buffer before the memory is released. }}*/
XPPRET XPPENTRY _XFREE(XppParamList pl){  __xb__free(pl, _xfree ); }
/*{{end-function}}*/
// ---------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _pgrab
            | syntax_: `_pgrab( nBytes )`
            | category: memory
            | _kw_: process heap, allocate memory, HeapAlloc
   }}*/
/*{{|desc: Allocates a memory block from the process heap.
    | params:
    - `nBytes` Numeric - Number of bytes to allocate. If zero, NIL is returned.
    - `cValue` Character - Optional source buffer copied into the newly allocated block.
    - `@nBytes` Numeric by reference - Receives the allocated size when cValue is used. The size includes
      room for a terminating zero byte.
    - `lUseMinSize` Logical - When .T., the supplied @nBytes value is used as a minimum allocation size.

    Returns Numeric/NIL - Pointer to the allocated memory block, or NIL when no block is allocated.

    |note: Also _pgrab( cValue, @nBytes [, lUseMinSize] ) -> pMem

    |note: _pgrab() uses the process heap through HeapAlloc(). Memory returned by _pgrab() must be released
      with _pfree(). Normal OT4XB code usually uses _xgrab() and _xfree() instead. }}*/
XPPRET XPPENTRY _PGRAB(XppParamList pl){  __xb__grab(pl, _pgrab ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _pfree
            | syntax_: `_pfree( pMem [, @cValue [, nBytes]] )`
            | category: memory
            | _kw_: process heap, free memory, HeapFree
   }}*/
/*{{|desc: Releases a memory block allocated with _pgrab().
    | params:
    - `pMem` Numeric - Pointer returned by _pgrab().
    - `@cValue` Character by reference - Optional variable that receives bytes copied from pMem before the
      block is released.
    - `nBytes` Numeric - Number of bytes to copy into @cValue before releasing pMem.

    Returns NIL

    |note: _pfree() releases process-heap memory through HeapFree(). Use it only with blocks allocated by
      _pgrab(). }}*/
XPPRET XPPENTRY _PFREE(XppParamList pl){  __xb__free(pl, _pfree ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _vgrab
            | syntax_: `_vgrab( nBytes )`
            | category: memory
            | _kw_: virtual memory, allocate, VirtualAlloc
   }}*/
/*{{|desc: Allocates a memory block directly from virtual memory.
    | params:
    - `nBytes` Numeric - Number of bytes to allocate. If zero, NIL is returned.
    - `cValue` Character - Optional source buffer copied into the newly allocated block.
    - `@nBytes` Numeric by reference - Receives the allocated size when cValue is used. The size includes
      room for a terminating zero byte.
    - `lUseMinSize` Logical - When .T., the supplied @nBytes value is used as a minimum allocation size.

    Returns Numeric/NIL - Pointer to the allocated memory block, or NIL when no block is allocated.

    |note: Also _vgrab( cValue, @nBytes [, lUseMinSize] ) -> pMem

    |note: _vgrab() uses VirtualAlloc() directly and keeps an internal size header before the returned pointer.
      Memory returned by _vgrab() must be released with _vfree(). Normal OT4XB code usually uses _xgrab() and
      _xfree() instead. }}*/
XPPRET XPPENTRY _VGRAB(XppParamList pl){  __xb__grab(pl, _vgrab ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _vfree
            | syntax_: `_vfree( pMem [, @cValue [, nBytes]] )`
            | category: memory
            | _kw_: virtual memory, free, VirtualFree
   }}*/
/*{{|desc: Releases a memory block allocated with _vgrab().
    | params:
    - `pMem` Numeric - Pointer returned by _vgrab().
    - `@cValue` Character by reference - Optional variable that receives bytes copied from pMem before the
      block is released.
    - `nBytes` Numeric - Number of bytes to copy into @cValue before releasing pMem.

    Returns NIL

    |note: _vfree() releases virtual memory allocated by _vgrab(). Use it only with blocks allocated by
      _vgrab(). }}*/
XPPRET XPPENTRY _VFREE(XppParamList pl){  __xb__free(pl, _vfree ); }
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// _xGrab(n) || _xGrab(1[@]cVar,2[@nGetSize],3[lTakeP2AsSize)
static void __xb__grab(XppParamList pl, void * (*pfnGrab)(UINT) )
{
   ULONG ulType = _partype(pl,1);
   if( ulType & XPP_CHARACTER)
   {
      UINT nn     = (UINT) _parclen(pl,1);
      UINT nSize;
      LPSTR p;
      if( _parl(pl,3) )
      {
         nSize = (UINT) _parLong(pl,2);
         if(nSize < (nn +1) ){ nSize = nn + 1; }
      }
      else nSize = nn + 1;
      p = (LPSTR) (*pfnGrab)(nSize);
      _parc(p,nSize,pl,1); _stornl((LONG) nSize,pl,2);
      _retnl(pl,(LONG) p);
   }
   else if( ulType & XPP_NUMERIC)
   {
      UINT nSize = (UINT) _parLong(pl,1);
      if( nSize == 0 ) _ret(pl);
      else _retnl( pl , (LONG) (*pfnGrab)(nSize) );
   }
   else _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
// _xFree( 1 hMem ,2[@cVar],3[nSize])
static void __xb__free(XppParamList pl, void (*pfnFree)(void *) )
{
   LPSTR p     = (LPSTR) _parLong(pl,1);
   if( p != 0)
   {
      ULONG nParams  = _partype(pl,0);
      if( nParams > 1)
      {
         ULONG nSize = (ULONG) _parLong(pl,3);
         _storclen(p,nSize,pl,2,0);
      }
      (*pfnFree)((void *)p);
   }
   _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conXGrabSz
            | syntax_: `LPSTR _conXGrabSz( ContainerHandle con, ULONG* puSize )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conXGrabSz
            | _kw_: container to string, copy string, xgrab, zero terminated
   }}*/
/*{{|desc: copy a string from a Xbase++ container into a new _xgrab() memory block. The string is guaranteed to
      be zero terminated, but can contain more zeros at any position must be released with _xfree()
    | params:
    - `con` ContainerHandle - Container holding the source string.
    - `puSize` ULONG * - Optional; when not NULL receives the string length in bytes, terminator
      excluded.

    Returns LPSTR - Pointer to the copy, or 0 when con is NULLCONTAINER or its data cannot be locked. }}*/
OT4XB_API LPSTR _conXGrabSz(ContainerHandle con,ULONG * puSize)
{
   ULONG nSize = 0;
   LPSTR pTmp  = 0;
   LPSTR pRet = 0;
   if( con == NULLCONTAINER) return 0;

   if( ot4xb_conRLockC(con,&pTmp,&nSize) == 0)
   {
      pRet = (LPSTR) _xgrab(nSize+1);
      _bcopy((LPBYTE)pRet, (LPBYTE) pTmp,nSize);
      if( puSize != 0) puSize[0] = nSize;
      ot4xb_conUnlockC(con);
   }
   return pRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bset
            | syntax_: `_bset( pMem, xByte, nBytes )`
            | category: memory
            | _kw_: memset, fill memory, fill buffer, byte value
   }}*/
/*{{|desc: Fills a memory buffer with a byte value.
    | params:
    - `pMem` Numeric - Destination pointer.
    - `xByte` Numeric/Character - Byte value to write.
    - `nBytes` Numeric - Number of bytes to fill.

    Returns Numeric - The destination pointer. }}*/
XPPRET XPPENTRY _BSET( XppParamList pl )
{
   LPBYTE  pStr    = (LPBYTE) _parLong(pl,1);
   CHAR    sz[2];
   UINT    nBytes  = (UINT) _parLong(pl,3);
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,2,0);
   else sz[0] = (CHAR) (_parLong(pl,2) & 0xFF);
   _retnl(pl,(LONG) _bset(pStr,(BYTE)sz[0],nBytes));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bset
            | syntax_: `LPBYTE _bset( LPBYTE pStr, BYTE ch, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bset
            | _kw_: memset, fill memory, fill buffer, byte value
   }}*/
/*{{|desc: init nBytes from pStr with the ch value
    | params:
    - `pStr` LPBYTE - Destination buffer.
    - `ch` BYTE - Byte value to write.
    - `nBytes` UINT - Number of bytes to fill.

    Returns LPBYTE - The destination pointer. }}*/
OT4XB_API LPBYTE _bset(LPBYTE pStr, BYTE ch , UINT nBytes)
{
   UINT n;
   for( n = 0; n < nBytes ; n++) pStr[n] = ch;
   return pStr;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bmove
            | syntax_: `_bmove( pDest, pSrc, nBytes )`
            | category: memory
            | _kw_: memmove, copy memory, overlapping, move bytes
   }}*/
/*{{|desc: Copies bytes between memory buffers, allowing overlapping source and destination ranges.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source pointer.
    - `nBytes` Numeric - Number of bytes to copy.

    Returns Numeric - The destination pointer. }}*/
XPPRET XPPENTRY _BMOVE( XppParamList pl )
{
   _retnl(pl,(LONG) _bmove( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bmove
            | syntax_: `LPBYTE _bmove( LPBYTE pDest, LPBYTE pSrc, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bmove
            | _kw_: memmove, copy memory, overlapping, move bytes
   }}*/
/*{{|desc: copy nBytes of memory from one location to another the locations can be overlapped
    | params:
    - `pDest` LPBYTE - Destination buffer.
    - `pSrc` LPBYTE - Source buffer; may overlap the destination.
    - `nBytes` UINT - Number of bytes to copy.

    Returns LPBYTE - The destination pointer. }}*/
OT4XB_API LPBYTE _bmove(LPBYTE pDest, LPBYTE pSrc , UINT nBytes)
{
   if( nBytes )
   {
      LPBYTE pTmp = (LPBYTE) _xgrab(nBytes);
      UINT n;
      for( n = 0; n < nBytes ; n++) pTmp[n] = pSrc[n];
      for( n = 0; n < nBytes ; n++) pDest[n] = pTmp[n];
      _xfree( (void *) pTmp );
   }
   return pDest;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bdup
            | syntax_: `_bdup( pSrc, nBytes )`
            | category: memory
            | _kw_: duplicate memory, clone buffer, copy bytes, xgrab
   }}*/
/*{{|desc: Duplicates a memory buffer into a new _xgrab() block.
    | params:
    - `pSrc` Numeric - Source pointer.
    - `nBytes` Numeric - Number of bytes to duplicate.

    Returns Numeric/NIL - Pointer to the new block, or 0 when nBytes is zero.

    |note: The returned block is allocated with _xgrab() and must be released with _xfree(). }}*/
XPPRET XPPENTRY _BDUP( XppParamList pl )
{
   _retnl(pl,(LONG) _bdup( (LPBYTE) _parLong(pl,1),(UINT) _parLong( pl,2,0)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bdup
            | syntax_: `LPBYTE _bdup( LPBYTE pSrc, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bdup
            | _kw_: duplicate memory, clone buffer, copy bytes, xgrab
   }}*/
/*{{|desc: Clone a memory buffer of nBytes using _xgrab() to allocate it .
    | params:
    - `pSrc` LPBYTE - Source buffer.
    - `nBytes` UINT - Number of bytes to duplicate.

    Returns LPBYTE - Pointer to the copy (release with _xfree()), or 0 when nBytes is 0. }}*/
OT4XB_API LPBYTE _bdup(LPBYTE pSrc , UINT nBytes)
{
   if( nBytes )
   {
      LPBYTE pNew = (LPBYTE) _xgrab(nBytes);
      UINT n;
      for( n = 0; n < nBytes ; n++) pNew[n] = pSrc[n];
      return pNew;
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bcopywithtable
            | syntax_: `_bcopywithtable( pDest, pSrc, nBytes, pTable )`
            | category: memory
            | _kw_: copy with table, translate bytes, byte mapping, transcode
   }}*/
/*{{|desc: Copies bytes from one buffer to another, translating each byte through a 256-byte table.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source pointer.
    - `nBytes` Numeric - Number of bytes to copy.
    - `pTable` Numeric - Pointer to a 256-byte translation table.

    Returns Numeric - The destination pointer. }}*/
XPPRET XPPENTRY _BCOPYWITHTABLE( XppParamList pl )
{
   _retnl(pl, (LONG) _bcopywithtable((LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),
                                     (UINT) _parLong( pl,3),(LPBYTE)  _parLong(pl,4))
         );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcopywithtable
            | syntax_: `LPBYTE _bcopywithtable( LPBYTE pDest, LPBYTE pSrc, UINT nBytes, LPBYTE pTable )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcopywithtable
            | _kw_: copy with table, translate bytes, byte mapping, transcode
   }}*/
/*{{|desc: Copy nBytes from pSrc to pDest using a mapping character table. pTable must be string at least 256
      BYTES
    | params:
    - `pDest` LPBYTE - Destination buffer.
    - `pSrc` LPBYTE - Source buffer.
    - `nBytes` UINT - Number of bytes to copy.
    - `pTable` LPBYTE - 256-byte translation table indexed by the source byte value.

    Returns LPBYTE - The destination pointer. }}*/
OT4XB_API LPBYTE _bcopywithtable(LPBYTE pDest, LPBYTE pSrc , UINT nBytes, LPBYTE pTable)
{
   if( nBytes )
   {
      UINT n;
      for( n = 0; n < nBytes ; n++) pDest[n] = pTable[pSrc[n]];
   }
   return pDest;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bcopy
            | syntax_: `_bcopy( pDest, pSrc, nBytes )`
            | category: memory
            | _kw_: memcpy, copy memory, copy bytes
   }}*/
/*{{|desc: Copies bytes from one memory buffer to another.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source pointer.
    - `nBytes` Numeric - Number of bytes to copy.

    Returns Numeric - The destination pointer.

    |note: For overlapping ranges use _bmove(). }}*/
XPPRET XPPENTRY _BCOPY( XppParamList pl )
{
   _retnl(pl,(LONG) _bcopy( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcopy
            | syntax_: `LPBYTE _bcopy( LPBYTE pDest, LPBYTE pSrc, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcopy
            | _kw_: memcpy, copy memory, copy bytes
   }}*/
/*{{|desc: copy nBytes of memory from one location to another if the locations are overlapped results can be
      unpredictables. For overlapped locations use _bmove() instead
    | params:
    - `pDest` LPBYTE - Destination buffer.
    - `pSrc` LPBYTE - Source buffer.
    - `nBytes` UINT - Number of bytes to copy.

    Returns LPBYTE - The destination pointer. }}*/
OT4XB_API LPBYTE _bcopy(LPBYTE pDest, LPBYTE pSrc , UINT nBytes)
{
   if( nBytes )
   {
      UINT n;
	  for (n = 0; n < nBytes; n++) { pDest[n] = pSrc[n]; }
   }
   return pDest;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcopy_no_overlap
            | syntax_: `LPBYTE _bcopy_no_overlap( LPBYTE pDest, LPBYTE pSrc, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcopy_no_overlap
            | _kw_: memmove, copy memory, overlapping safe
   }}*/
/*{{|desc: Copies nBytes from pSrc to pDest so that overlap between the source and destination ranges does not
      spoil the copy - which is what the name means. It copies forward when pSrc >= pDest and backward
      otherwise, so no source byte is overwritten before it is read (memmove semantics). Same result as
      _bmove(), but done in place - no temporary buffer.
    | params:
    - `pDest` LPBYTE - Destination pointer.
    - `pSrc` LPBYTE - Source pointer.
    - `nBytes` UINT - Number of bytes to copy.

    Returns LPBYTE - The destination pointer (pDest). }}*/
OT4XB_API LPBYTE _bcopy_no_overlap(LPBYTE pDest, LPBYTE pSrc, UINT nBytes)
{
	if ( ((DWORD)pSrc) >= ((DWORD)pDest) )
	{
		return  _bcopy(pDest, pSrc, nBytes);
	}
	if (nBytes)
	{
		UINT n;
		for (n = nBytes; n; n--) { pDest[n - 1] = pSrc[n - 1]; }
	}
	return pDest;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcopyex
            | syntax_: `LPBYTE _bcopyex( LPBYTE pDest, DWORD dshift, LPBYTE pSrc, DWORD sshift, UINT nBytes )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcopyex
            | _kw_: memcpy, copy memory, offset, shifted pointers
   }}*/
/*{{|desc: Copies nBytes like _bcopy() but shifts both pointers first: bytes go from pSrc + sshift to
      pDest + dshift. Overlapping ranges are not handled.
    | params:
    - `pDest` LPBYTE - Destination base pointer.
    - `dshift` DWORD - Byte offset added to pDest.
    - `pSrc` LPBYTE - Source base pointer.
    - `sshift` DWORD - Byte offset added to pSrc.
    - `nBytes` UINT - Number of bytes to copy.

    Returns LPBYTE - The shifted destination pointer (pDest + dshift). }}*/
OT4XB_API LPBYTE __cdecl _bcopyex(LPBYTE pDest, DWORD dshift , LPBYTE pSrc , DWORD sshift , UINT nBytes)
{
   pDest = _mk_ptr_(LPBYTE,pDest,dshift);
   pSrc  = _mk_ptr_(LPBYTE,pSrc,sshift);
   if( nBytes )
   {
      UINT n;
      for( n = 0; n < nBytes ; n++) pDest[n] = pSrc[n];
   }
   return pDest;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bcopyf
            | syntax_: `_bcopyf( pDest, pSrc, nDestBytes, nSrcBytes )`
            | category: memory
            | _kw_: copy fixed buffer, pad, memcpy, fixed size
   }}*/
/*{{|desc: Copies bytes from a source buffer into a fixed-size destination buffer.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source pointer.
    - `nDestBytes` Numeric - Destination buffer size in bytes.
    - `nSrcBytes` Numeric - Source buffer size in bytes.

    Returns NIL

    |note: Copies min(nDestBytes, nSrcBytes) bytes; if the source is shorter than the destination, the
      remaining destination bytes are filled with spaces (0x20). }}*/
XPPRET XPPENTRY _BCOPYF( XppParamList pl )
{
   _bcopyf( (LPBYTE) _parLong(pl,1),
            (LPBYTE) _parLong(pl,2),
            (UINT) _parLong( pl,3,0),
            (UINT) _parLong( pl,4,0));
   _ret(pl);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcopyf
            | syntax_: `void _bcopyf( LPBYTE pDest, LPBYTE pSrc, UINT nDstSize, UINT nSrcSize )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcopyf
            | _kw_: copy fixed buffer, pad, memcpy, fixed size
   }}*/
/*{{|desc: Copies min(nSrcSize, nDstSize) bytes from pSrc to pDest; if pSrc is shorter than pDest, the
      remaining destination bytes are space-padded (0x20).
    | params:
    - `pDest` LPBYTE - Destination buffer.
    - `pSrc` LPBYTE - Source buffer.
    - `nDstSize` UINT - Destination size in bytes.
    - `nSrcSize` UINT - Source size in bytes.

    Returns void }}*/
OT4XB_API void _bcopyf(LPBYTE pDest, LPBYTE pSrc , UINT nDstSize, UINT nSrcSize)
{
   UINT nBytes = ( (nDstSize < nSrcSize) ? nDstSize : nSrcSize) ;
   UINT n;
   for( n = 0; n < nBytes ; n++) { pDest[n] = pSrc[n]; }
   if( nDstSize > nBytes ) { for( n = nBytes; n < nDstSize ; n++) { pDest[n] = 0x20; } }
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bscan
            | syntax_: `_bscan( pMem, nBytes, xByte )`
            | category: memory
            | _kw_: memchr, find byte, search buffer, position
   }}*/
/*{{|desc: Searches a byte value inside a memory buffer.
    | params:
    - `pMem` Numeric - Buffer pointer.
    - `nBytes` Numeric - Number of bytes to scan.
    - `xByte` Numeric/Character - Byte value to find.

    Returns Numeric - Zero-based byte position, or nBytes when the byte is not found. }}*/
XPPRET XPPENTRY _BSCAN( XppParamList pl )
{
   LPBYTE  pStr    = (LPBYTE) _parLong(pl,1);
   UINT    nBytes  = (UINT) _parLong(pl,2);
   CHAR    sz[2];
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,3,0);
   else sz[0] = (CHAR) (_parLong(pl,3) & 0xFF);
   _retnl(pl,(LONG) _bscan(pStr,nBytes,(BYTE)sz[0]));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bscan
            | syntax_: `UINT _bscan( LPBYTE pStr, UINT nBytes, BYTE ch )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bscan
            | _kw_: memchr, find byte, search buffer, position
   }}*/
/*{{|desc: Returns the zero-based position of the first occurrence of the byte ch within the buffer pStr.
      The result is less than nBytes only when ch was found.
    | params:
    - `pStr` LPBYTE - Buffer to scan.
    - `nBytes` UINT - Number of bytes to scan.
    - `ch` BYTE - Byte value to find.

    Returns UINT - Zero-based position of ch, or nBytes when it is not found. }}*/
OT4XB_API UINT  _bscan(LPBYTE pStr, UINT nBytes , BYTE ch)
{
   UINT n;
   for( n = 0; n < nBytes; n++)
   {
      if( pStr[n] == ch ) return n;
   }
   return nBytes;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrcpy
            | syntax_: `_xstrcpy( pDest, pSrc )`
            | category: memory/string
            | _kw_: strcpy, copy string, zero terminated
   }}*/
/*{{|desc: Copies a zero-terminated string to a destination buffer.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source zero-terminated string pointer.

    Returns Numeric - The destination pointer. }}*/
XPPRET XPPENTRY _XSTRCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrcpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcpy
            | syntax_: `LPSTR _xstrcpy( LPSTR pDest, LPSTR pSrc )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcpy
            | _kw_: strcpy, copy string, zero terminated
   }}*/
/*{{|desc: Copy a NULL terminated string pointed to by pSrc to pDest memory location. return the destination
      buffer
    | params:
    - `pDest` LPSTR - Destination buffer; must have room for the string and its terminator.
    - `pSrc` LPSTR - Source zero-terminated string.

    Returns LPSTR - The destination pointer. }}*/
OT4XB_API LPSTR _xstrcpy(LPSTR pDest, LPSTR pSrc)
{
   LPSTR p = pDest;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcpyW
            | syntax_: `LPWSTR _xstrcpyW( LPWSTR pDest, LPWSTR pSrc )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcpyW
            | _kw_: wcscpy, copy wide string, UTF-16
   }}*/
/*{{|desc: Wide-character version of _xstrcpy(): copies a zero-terminated UTF-16 string, terminator
      included.
    | params:
    - `pDest` LPWSTR - Destination buffer; must have room for the string and its terminator.
    - `pSrc` LPWSTR - Source zero-terminated wide string.

    Returns LPWSTR - The destination pointer. }}*/
OT4XB_API LPWSTR _xstrcpyW(LPWSTR pDest, LPWSTR pSrc)
{
   LPWSTR p = pDest;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xxstrcpy
            | syntax_: `_xxstrcpy( pDest, pSrc )`
            | category: memory/string
            | _kw_: strcpy, copy string, end pointer, append
   }}*/
/*{{|desc: Copies a zero-terminated string and returns the destination pointer positioned at the final zero.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source zero-terminated string pointer.

    Returns Numeric - Pointer to the terminating zero written in the destination buffer. }}*/
XPPRET XPPENTRY _XXSTRCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xxstrcpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location.
// _xxstrcpy() will return ( pDst + nBytesCopied )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xxstrcpy
            | syntax_: `LPSTR _xxstrcpy( LPSTR pDest, LPSTR pSrc )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xxstrcpy
            | _kw_: strcpy, copy string, end pointer, append
   }}*/
/*{{|desc: Copies a zero-terminated string like _xstrcpy() but returns the position of the terminating zero
      written in the destination, so successive copies can be chained to concatenate strings.
    | params:
    - `pDest` LPSTR - Destination buffer; must have room for the string and its terminator.
    - `pSrc` LPSTR - Source zero-terminated string.

    Returns LPSTR - Pointer to the terminating zero in the destination (pDest + bytes copied). }}*/
OT4XB_API LPSTR _xxstrcpy(LPSTR pDest, LPSTR pSrc)
{
   while( (BOOL)(*pDest = *pSrc) ){pDest++;pSrc++;}
   return( pDest );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstccpy
            | syntax_: `_xstccpy( pDest, pSrc, nMax )`
            | category: memory/string
            | _kw_: strncpy, copy string, max bytes
   }}*/
/*{{|desc: Copies a zero-terminated string up to a maximum number of bytes.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source zero-terminated string pointer.
    - `nMax` Numeric - Maximum number of bytes to copy.

    Returns Numeric - Number of bytes copied. }}*/
XPPRET XPPENTRY _XSTCCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstccpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2),(UINT) _parLong(pl,3,0)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstccpy
            | syntax_: `UINT _xstccpy( LPSTR pDest, LPSTR pSrc, UINT nMax )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstccpy
            | _kw_: strncpy, copy string, max bytes
   }}*/
/*{{|desc: Copy a NULL terminated string pointed to by pSrc to pDest memory location stopping at nMax bytes if
      NULL not found before.
    | params:
    - `pDest` LPSTR - Destination buffer of at least nMax bytes.
    - `pSrc` LPSTR - Source zero-terminated string.
    - `nMax` UINT - Maximum number of bytes to write; 0 writes nothing.

    Returns UINT - Number of bytes written, terminator included when the whole string fits. When the nMax
      limit stops the copy, the destination is left without a terminating zero. }}*/
OT4XB_API UINT _xstccpy(LPSTR pDest, LPSTR pSrc, UINT nMax)
{
   UINT  n = 0;
   if( nMax ){ do{ pDest[n] = *pSrc;n++;} while(*pSrc++ && (n < nMax) ); }
   return( n );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrncpy
            | syntax_: `_xstrncpy( pDest, pSrc, nDestBytes )`
            | category: memory/string
            | _kw_: strncpy, copy string, fixed buffer, truncate
   }}*/
/*{{|desc: Copies a zero-terminated string into a fixed-size destination buffer.
    | params:
    - `pDest` Numeric - Destination pointer.
    - `pSrc` Numeric - Source zero-terminated string pointer.
    - `nDestBytes` Numeric - Destination buffer size in bytes.

    Returns Numeric - The destination pointer.

    |note: The destination buffer is always zero-terminated when nDestBytes is greater than zero. }}*/
XPPRET XPPENTRY _XSTRNCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrncpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2),(UINT) _parLong(pl,3,0)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location
// stopping at nMax bytes if NULL not found before.
// If bytes copied are less than nMax fill the rest of pDest with NULLs up to nMax bytes.
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrncpy
            | syntax_: `LPSTR _xstrncpy( LPSTR pDest, LPCSTR pSrc, UINT destination_cb )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrncpy
            | _kw_: strncpy, copy string, fixed buffer, truncate
   }}*/
/*{{|desc: Copies a zero-terminated string into a destination buffer of destination_cb bytes, truncating
      when needed. The whole buffer is always written: the copy is padded with zeros, so the result is
      always zero terminated.
    | params:
    - `pDest` LPSTR - Destination buffer.
    - `pSrc` LPCSTR - Source zero-terminated string.
    - `destination_cb` UINT - Total size of the destination buffer in bytes; 0 does nothing.

    Returns LPSTR - The destination pointer. }}*/
OT4XB_API LPSTR _xstrncpy( LPSTR pDest, LPCSTR pSrc, UINT destination_cb )
{
   UINT i = 0;
   if( destination_cb )
   {
      destination_cb--;
      pDest[ destination_cb ] = 0;
      for( ; i < destination_cb && pSrc[ i ]; i++ )
         pDest[ i ] = pSrc[ i ];

      for( ; i < destination_cb; i++ )
         pDest[ i ] = 0;
   }
   return pDest;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrcat
            | syntax_: `_xstrcat( pDest, pSrc )`
            | category: memory/string
            | _kw_: strcat, append string, concatenate
   }}*/
/*{{|desc: Appends a zero-terminated source string to a zero-terminated destination string.
    | params:
    - `pDest` Numeric - Destination string pointer.
    - `pSrc` Numeric - Source string pointer.

    Returns Numeric - The destination pointer. }}*/
XPPRET XPPENTRY _XSTRCAT( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrcat( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcat
            | syntax_: `LPSTR _xstrcat( LPSTR pDest, LPSTR pSrc )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcat
            | _kw_: strcat, append string, concatenate
   }}*/
/*{{|desc: Append the string pointed to by pSrc to pDest . Assuming both strings are NULL terminated.
    | params:
    - `pDest` LPSTR - Destination string; must have room for the concatenated result.
    - `pSrc` LPSTR - Source string appended after the destination content.

    Returns LPSTR - The destination pointer. }}*/
OT4XB_API LPSTR _xstrcat( LPSTR pDest, LPSTR pSrc )
{
   LPSTR p = pDest;
   while(*p) p++;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstpchr
            | syntax_: `_xstpchr( pStr, xChar )`
            | category: memory/string
            | _kw_: strchr, find character, string search
   }}*/
/*{{|desc: Finds a character inside a zero-terminated string.
    | params:
    - `pStr` Numeric - Zero-terminated string pointer.
    - `xChar` Numeric/Character - Character to find.

    Returns Numeric - Pointer to the character, or 0 when it is not found before the final zero. }}*/
XPPRET XPPENTRY _XSTPCHR( XppParamList pl )
{
   CHAR    sz[2];
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,2,0);
   else sz[0] = (CHAR) (_parLong(pl,2) & 0xFF);
   _retnl(pl,(LONG) _xstpchr( (LPSTR) _parLong(pl,1),sz[0]));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstpchr
            | syntax_: `LPSTR _xstpchr( LPSTR pStr, CHAR ch )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstpchr
            | _kw_: strchr, find character, string search
   }}*/
/*{{|desc: Returns the memory pointer of the first occurrence of the character ch within the zero-terminated
      string pStr, or 0 when the string ends before ch is found.
    | params:
    - `pStr` LPSTR - Zero-terminated string to scan.
    - `ch` CHAR - Character to find.

    Returns LPSTR - Pointer to the first occurrence of ch, or 0 when not found. }}*/
OT4XB_API LPSTR _xstpchr( LPSTR pStr , CHAR ch )
{
   while (*pStr && (*pStr != ch)) pStr++;
   if( *pStr == ch ) return pStr;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstpblk
            | syntax_: `_xstpblk( pStr )`
            | category: memory/string
            | _kw_: skip blanks, skip whitespace, ltrim pointer
   }}*/
/*{{|desc: Skips TAB, space, CR, and LF characters at the start of a zero-terminated string.
    | params:
    - `pStr` Numeric - Zero-terminated string pointer.

    Returns Numeric - Pointer to the first non-blank character, or to the final zero. }}*/
XPPRET XPPENTRY _XSTPBLK( XppParamList pl )
{
   _retnl(pl,(LONG) _xstpblk( (LPSTR) _parLong(pl,1)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstpblk
            | syntax_: `LPSTR _xstpblk( LPSTR pStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstpblk
            | _kw_: skip blanks, skip whitespace, ltrim pointer
   }}*/
/*{{|desc: Skips TAB, space, CR and LF characters at the start of a zero-terminated string.
    | params:
    - `pStr` LPSTR - Zero-terminated string.

    Returns LPSTR - Pointer to the first character that is not TAB, space, CR or LF, or to the final zero
      when the string holds nothing else. }}*/
OT4XB_API LPSTR _xstpblk(LPSTR pStr)
{
  while( *pStr )
  {
      switch( *pStr )
      {
          case 9: case 10: case 13: case 32: pStr++;break;
          default:  return pStr;
      }
  }
  return pStr;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrlen
            | syntax_: `_xstrlen( pStr )`
            | category: memory/string
            | _kw_: strlen, string length, zero terminated
   }}*/
/*{{|desc: Returns the length of a zero-terminated string.
    | params:
    - `pStr` Numeric - Zero-terminated string pointer.

    Returns Numeric - Number of bytes before the first zero byte. }}*/
XPPRET XPPENTRY _XSTRLEN( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrlen( (LPSTR) _parLong(pl,1)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrlen
            | syntax_: `UINT _xstrlen( LPSTR pStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrlen
            | _kw_: strlen, string length, zero terminated
   }}*/
/*{{|desc: Count the characters of pStr up to the first NULL
    | params:
    - `pStr` LPSTR - Zero-terminated string.

    Returns UINT - Number of bytes before the first zero byte. }}*/
OT4XB_API UINT _xstrlen(LPSTR pStr)
{
  UINT n = 0;
  while( pStr[n] ) n++;
  return n;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrlenW
            | syntax_: `UINT _xstrlenW( LPWSTR pStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrlenW
            | _kw_: wcslen, wide string length, UTF-16
   }}*/
/*{{|desc: Wide-character version of _xstrlen(): counts the characters of a zero-terminated UTF-16 string.
    | params:
    - `pStr` LPWSTR - Zero-terminated wide string.

    Returns UINT - Number of wide characters before the terminating zero (not bytes). }}*/
OT4XB_API UINT _xstrlenW(LPWSTR pStr)
{
  UINT n = 0;
  while( pStr[n] ) n++;
  return n;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrdup
            | syntax_: `_xstrdup( pStr )`
            | category: memory/string
            | _kw_: strdup, duplicate string, clone string, xgrab
   }}*/
/*{{|desc: Duplicates a zero-terminated string into a new _xgrab() block.
    | params:
    - `pStr` Numeric - Source zero-terminated string pointer.

    Returns Numeric - Pointer to the duplicated string, or 0 when pStr is 0.

    |note: The returned pointer must be released with _xfree(). }}*/
XPPRET XPPENTRY _XSTRDUP( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrdup( (LPSTR) _parLong(pl,1)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrdup
            | syntax_: `LPSTR _xstrdup( LPSTR pStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrdup
            | _kw_: strdup, duplicate string, clone string, xgrab
   }}*/
/*{{|desc: Clone a zero terminated string using _xgrab() to allocate it .
    | params:
    - `pStr` LPSTR - Source zero-terminated string, or NULL.

    Returns LPSTR - Pointer to the copy (release with _xfree()), or 0 when pStr is NULL. }}*/
OT4XB_API LPSTR _xstrdup(LPSTR pStr )
{
   LPSTR pNew;
   if( !pStr) return 0;
   pNew = (LPSTR) _xgrab(_xstrlen(pStr) + 1);
   if(pNew) return  _xstrcpy(pNew,pStr);
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrdupandgetlen
            | syntax_: `LPSTR _xstrdupandgetlen( LPSTR pStr, UINT * pnLen )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrdupandgetlen
            | _kw_: strdup, duplicate string, length, xgrab
   }}*/
/*{{|desc: Like _xstrdup() but also reports the length: clones pStr into a new _xgrab() block and stores the
      string length, terminator excluded, in pnLen[0].
    | params:
    - `pStr` LPSTR - Source zero-terminated string, or NULL.
    - `pnLen` UINT * - Required; receives the length in bytes (0 when pStr is NULL).

    Returns LPSTR - Pointer to the copy (release with _xfree()), or 0 when pStr or pnLen is NULL. }}*/
OT4XB_API LPSTR _xstrdupandgetlen(LPSTR pStr , UINT* pnLen)
{
   LPSTR pNew;
   if( !pnLen ) return 0;
   pnLen[0] = 0;
   if( !pStr) return 0;
   pnLen[0] = _xstrlen(pStr);
   pNew = (LPSTR) _xgrab(pnLen[0] + 1);
   if(pNew) return  _xstrcpy(pNew,pStr);
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xssr_
            | syntax_: `LPSTR _xssr_( LPSTR * pp, LPSTR p )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xssr_
            | _kw_: string slot, replace string, free and dup, string member
   }}*/
/*{{|desc: String slot replace: releases with _xfree() the string currently held in the pp slot, then stores
      a _xstrdup() copy of p in its place. With p == NULL the slot is just cleared. Handy to maintain an
      owned string variable or member.
    | params:
    - `pp` LPSTR * - Address of the string pointer to update.
    - `p` LPSTR - New string to copy into the slot, or NULL to only clear it.

    Returns LPSTR - The new slot value: the copy, or 0. }}*/
OT4XB_API LPSTR _xssr_(LPSTR* pp , LPSTR p)
{
   if( !pp ) return 0;
   if( pp[0] ){ _xfree( (void*) (pp[0]) ); pp[0] = 0; }
   if( p ){ pp[0] = _xstrdup(p);}
   return pp[0];
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xssr_cb_
            | syntax_: `LPSTR _xssr_cb_( LPSTR * ppd, UINT * pcbd, LPSTR ps, UINT cbs )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xssr_cb_
            | _kw_: string slot, replace string, counted, string member
   }}*/
/*{{|desc: Counted variant of _xssr_(): replaces the string held in the ppd slot with a copy of the first
      cbs bytes of ps and keeps the stored length in the optional pcbd slot. The previous string is released
      with _xfree(); the copy is allocated with _xgrab() and zero terminated.
    | params:
    - `ppd` LPSTR * - Address of the string pointer to update.
    - `pcbd` UINT * - Optional; receives the stored length in bytes.
    - `ps` LPSTR - Source buffer, or NULL to only clear the slot.
    - `cbs` UINT - Bytes to copy, or (UINT) -1 to take the zero-terminated length of ps.

    Returns LPSTR - The new slot value: the copy, or 0. }}*/
OT4XB_API LPSTR _xssr_cb_(LPSTR * ppd , UINT * pcbd , LPSTR ps , UINT cbs  )
{
   if( ppd )
   {
      if(*ppd)
      {
         _xfree( (void*) *ppd );
         *ppd = 0;
         if( pcbd ){ *pcbd = 0;}
      }
      if( ps )
      {
         LPSTR p;
         if( cbs == (UINT) -1 ){ cbs = _xstrlen(ps); }
         if( pcbd ){ *pcbd = cbs;}
         *ppd = (LPSTR) _xgrab( cbs + 1 );
         for( p=*ppd; cbs; p++ , ps++ ){ *p = *ps; cbs--;}
      }
      return *ppd;
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _assr_cb_
            | syntax_: `LPSTR _assr_cb_( LPSTR * ppd, UINT * pcbd, LPSTR ps, UINT cbs )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _assr_cb_
            | _kw_: string slot, take ownership, assign string, string member
   }}*/
/*{{|desc: like xssr but get the ownership of the source pointer instead of allocate a new one
    | params:
    - `ppd` LPSTR * - Address of the string pointer to update.
    - `pcbd` UINT * - Optional; receives the stored length in bytes.
    - `ps` LPSTR - Pointer stored as-is in the slot; it must come from _xgrab() because the slot
      releases its content with _xfree() on the next replace. NULL only clears the slot.
    - `cbs` UINT - Its length in bytes, or (UINT) -1 to take the zero-terminated length.

    Returns LPSTR - The new slot value: ps, or 0. }}*/
OT4XB_API LPSTR  __cdecl _assr_cb_(LPSTR * ppd , UINT * pcbd , LPSTR ps , UINT cbs  )
{
   if( ppd )
   {
      if(*ppd)
      {
         _xfree( (void*) *ppd );
         *ppd = 0;
         if( pcbd ){ *pcbd = 0;}
      }
      if( ps )
      {
         if( cbs == (UINT) -1 ){ cbs = _xstrlen(ps); }
         if( pcbd ){ *pcbd = cbs;}
         *ppd = ps;
      }
      return *ppd;
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrdupW
            | syntax_: `LPWSTR _xstrdupW( LPWSTR pStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrdupW
            | _kw_: wcsdup, duplicate wide string, UTF-16, xgrab
   }}*/
/*{{|desc: Wide-character version of _xstrdup(): clones a zero-terminated UTF-16 string into a new _xgrab()
      block.
    | params:
    - `pStr` LPWSTR - Source zero-terminated wide string, or NULL.

    Returns LPWSTR - Pointer to the wide copy (release with _xfree()), or 0 when pStr is NULL. }}*/
OT4XB_API LPWSTR _xstrdupW(LPWSTR pStr )
{
   LPWSTR pNew;
   if( !pStr) return 0;
   pNew = (LPWSTR) _xgrab( (_xstrlenW(pStr) + 1) * 2 );
   if(pNew) return  _xstrcpyW(pNew,pStr);
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _xstrat
            | syntax_: `_xstrat( pSep, nSepBytes, pStr, nStrBytes )`
            | category: memory/string
            | _kw_: strstr, find substring, search bytes, position
   }}*/
/*{{|desc: Searches a byte sequence inside another byte sequence.
    | params:
    - `pSep` Numeric - Pointer to the byte sequence to find.
    - `nSepBytes` Numeric - Length of the sequence to find.
    - `pStr` Numeric - Pointer to the buffer to search.
    - `nStrBytes` Numeric - Length of the buffer to search.

    Returns Numeric - Zero-based position of pSep inside pStr, or -1 when not found. }}*/
XPPRET XPPENTRY _XSTRAT( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrat( (LPSTR) _parLong(pl,1), (int) _parLong(pl,2), (LPSTR) _parLong(pl,3),(int) _parLong(pl,4)));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrat
            | syntax_: `int _xstrat( LPSTR pSep, int cbSep, LPSTR pStr, int cbStr )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrat
            | _kw_: strstr, find substring, search bytes, position
   }}*/
/*{{|desc: Return the position of the first occurrence of pSep within the string pointed to by pStr.
    | params:
    - `pSep` LPSTR - Byte sequence to find.
    - `cbSep` int - Length of pSep in bytes.
    - `pStr` LPSTR - Buffer to search.
    - `cbStr` int - Length of pStr in bytes.

    Returns int - Zero-based position of pSep inside pStr, or -1 when not found or cbSep is smaller than 1
      or larger than cbStr. }}*/
OT4XB_API int _xstrat(LPSTR pSep, int cbSep , LPSTR pStr, int cbStr )
{
   int n = 0;
   if( cbSep < 1 ) return -1;
   if( cbSep > cbStr ) return -1;

   for( n = 0; n < cbStr; n++ )
   {
      if( pStr[n] == pSep[0] )
      {
         if( (cbStr - n) < cbSep) return -1;
         if( _bcmp( (BYTE*)(pStr+n), (BYTE*) pSep , cbSep) == 0) return n;
      }
   }
   return -1;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstr_nextline
            | syntax_: `LPSTR _xstr_nextline( LPSTR p, int * pcb )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstr_nextline
            | _kw_: next line, split lines, CRLF, text buffer, line iterator
   }}*/
/*{{|desc: Steps to the next line inside a text buffer: finds the first CR, LF or CRLF break within the
      pcb[0] bytes at p, stores in pcb[0] the byte count remaining after the break and returns the position
      of the next line.
    | params:
    - `p` LPSTR - Start of the current line.
    - `pcb` int * - In: bytes available at p. Out: bytes remaining from the returned position.

    Returns LPSTR - Pointer to the next line, or 0 when there is none: either no break exists in the
      buffer (pcb[0] is then left untouched) or the break closes the buffer (pcb[0] becomes 0). }}*/
OT4XB_API LPSTR __cdecl _xstr_nextline( LPSTR p , int* pcb )
{
   int cb;

   for( cb = pcb[0] ; cb ; cb-- , p++ )
   {
      if( p[0] == 0x0D || p[0] == 0x0A )
      {
         char ch = p[0];
         cb--;p++;
         if( cb && ch == 0x0D )
         {
            if( p[0] == 0x0A ){cb--;p++; }
         }
         pcb[0] = cb;
         if( cb )
         {
            return p;
         }
         return 0;
      }
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 ) // warning C4706: assignment within conditional expression
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcmp
            | syntax_: `int _xstrcmp( LPSTR p1, LPSTR p2 )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcmp
            | _kw_: strcmp, compare strings, case sensitive
   }}*/
/*{{|desc: Compares two zero-terminated strings byte by byte, case sensitive, taking each byte as unsigned.
    | params:
    - `p1` LPSTR - First string.
    - `p2` LPSTR - Second string.

    Returns int - -1 when p1 sorts lower than p2, 0 when both strings are equal, 1 when p1 sorts higher. }}*/
OT4XB_API int _xstrcmp( LPSTR p1 , LPSTR p2 )
{
   int i = 0;
   while( (!( i = (*(LPBYTE)p1) - (*(LPBYTE)p2) )) && *p2 )
   {
      p1++;
      p2++;
   }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcmpwithtable
            | syntax_: `int _xstrcmpwithtable( LPSTR p1, LPSTR p2, LPBYTE pt )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcmpwithtable
            | _kw_: compare strings, translation table, case folding
   }}*/
/*{{|desc: Compares two zero-terminated strings folding every byte through the 256-byte table pt before
      comparing - for example a lowercase table gives a case-insensitive order. With pt == NULL it behaves
      like _xstrcmp().
    | params:
    - `p1` LPSTR - First string.
    - `p2` LPSTR - Second string.
    - `pt` LPBYTE - 256-byte translation table, or NULL.

    Returns int - -1, 0 or 1 as in _xstrcmp(). }}*/
OT4XB_API int    _xstrcmpwithtable( LPSTR p1 , LPSTR p2 , LPBYTE pt)
{
   int i = 0;
   if(!pt) return _xstrcmp(p1,p2);
   while( (!(i = pt[(*(LPBYTE)p1)] - pt[(*(LPBYTE)p2)])) && *p2 )
   {
      p1++;
      p2++;
   }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcmpi
            | syntax_: `int _xstrcmpi( LPSTR p1, LPSTR p2 )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcmpi
            | _kw_: stricmp, compare strings, case insensitive
   }}*/
/*{{|desc: Case-insensitive version of _xstrcmp(): both strings are compared through the internal ANSI
      lowercase table, built with the Windows CharLower rules of the current locale.
    | params:
    - `p1` LPSTR - First string.
    - `p2` LPSTR - Second string.

    Returns int - -1, 0 or 1 as in _xstrcmp(). }}*/
OT4XB_API int    _xstrcmpi( LPSTR p1 , LPSTR p2 )
{
   return _xstrcmpwithtable(p1,p2,_lower_ansi_char_table_ );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrcmpi_09az
            | syntax_: `int _xstrcmpi_09az( LPSTR p1, LPSTR p2 )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrcmpi_09az
            | _kw_: compare strings, alphanumeric only, case insensitive, relaxed
   }}*/
/*{{|desc: Relaxed case-insensitive compare: characters are lowercased and everything outside 0-9 and a-z is
      skipped, so only the plain alphanumeric content of both strings is compared. NULL pointers are
      accepted: a NULL string sorts before a non-NULL one and two NULLs are equal.
    | params:
    - `p1` LPSTR - First zero-terminated string, or NULL.
    - `p2` LPSTR - Second zero-terminated string, or NULL.

    Returns int - -1, 0 or 1 as in _xstrcmp(). }}*/
OT4XB_API int _xstrcmpi_09az( LPSTR p1 , LPSTR p2 )
{
   char i = 0;
   if( !p1 ) return ( p2 ? -1 : 0 );
   if( !p2 ) return ( p1 ?  1 : 0 );
   loop_begin: ;
   while( (i==0) && *p1 && *p2 )
   {
      char ch1 = (char) _lower_ansi_char_table_09az_[ (BYTE)(*p1)];
      char ch2 = (char) _lower_ansi_char_table_09az_[ (BYTE)(*p2)];
      if( !ch1 ){ p1++; goto loop_begin;}
      if( !ch2 ){ p2++; goto loop_begin;}
      i = ch1 - ch2; p1++; p2++;
   }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xsstrcmp
            | syntax_: `int _xsstrcmp( LPSTR p1, ULONG cb1, LPSTR p2, ULONG cb2 )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xsstrcmp
            | _kw_: compare counted strings, strncmp, case sensitive
   }}*/
/*{{|desc: Compares two counted strings p1/p2 (cb1/cb2 are the buffer sizes). A string ends at the first
      `\0`, so bytes after a NUL are not part of the string and are not compared. For raw bytes / binary data
      use `_bcmp` instead.
    | params:
    - `p1` LPSTR - First string buffer.
    - `cb1` ULONG - Size of p1 in bytes.
    - `p2` LPSTR - Second string buffer.
    - `cb2` ULONG - Size of p2 in bytes.

    Returns int - -1, 0 or 1; when the compared parts tie, the remaining sizes decide (cb1 - cb2), so with
      equal content the bigger buffer sorts higher. }}*/
OT4XB_API int    _xsstrcmp( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2)
{
   int i = 0;
   while( cb1 && cb2 && (!(i = (*(LPBYTE)p1) - (*(LPBYTE)p2))) && *p2 )
   {
      p1++; p2++;
      cb1--; cb2--;
   }
   if( i == 0 ){ i = ((int) cb1) - ((int) cb2); }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xsstrcmpwithtable
            | syntax_: `int _xsstrcmpwithtable( LPSTR p1, ULONG cb1, LPSTR p2, ULONG cb2, LPBYTE pt )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xsstrcmpwithtable
            | _kw_: compare counted strings, translation table, case folding
   }}*/
/*{{|desc: Like _xsstrcmp but folds each byte through the translation table pt (e.g. a lowercase table for a
      case-insensitive compare). A string ends at the first `\0`, so bytes after a NUL are not part of the
      string and are not compared. For raw bytes / binary data use `_bcmp` instead.
    | params:
    - `p1` LPSTR - First string buffer.
    - `cb1` ULONG - Size of p1 in bytes.
    - `p2` LPSTR - Second string buffer.
    - `cb2` ULONG - Size of p2 in bytes.
    - `pt` LPBYTE - 256-byte translation table, or NULL to behave like _xsstrcmp().

    Returns int - -1, 0 or 1; ties resolved by the remaining sizes as in _xsstrcmp(). }}*/
OT4XB_API int    _xsstrcmpwithtable( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2 , LPBYTE pt)
{
   int i = 0;
   if(!pt) return _xsstrcmp(p1,cb1,p2,cb2);
   while( cb1 && cb2 && (!(i = (int) (((int)pt[(*(LPBYTE)p1)]) - (int)(pt[(*(LPBYTE)p2)]) ))) && *p2 )
   {
      p1++; p2++;
      cb1--; cb2--;
   }
   if( i == 0 ){ i = ((int) cb1) - ((int) cb2); }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xsstrcmpi
            | syntax_: `int _xsstrcmpi( LPSTR p1, ULONG cb1, LPSTR p2, ULONG cb2 )`
            | category: memory/string
            | header: ot4xb_c_exported.h
            | mangled-name: _xsstrcmpi
            | _kw_: compare counted strings, strnicmp, case insensitive
   }}*/
/*{{|desc: Counted-string version of _xstrcmpi(): case-insensitive compare of two counted strings through
      the internal ANSI lowercase table, with the _xsstrcmp() rules for NULs and sizes.
    | params:
    - `p1` LPSTR - First string buffer.
    - `cb1` ULONG - Size of p1 in bytes.
    - `p2` LPSTR - Second string buffer.
    - `cb2` ULONG - Size of p2 in bytes.

    Returns int - -1, 0 or 1; ties resolved by the remaining sizes as in _xsstrcmp(). }}*/
OT4XB_API int    _xsstrcmpi( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2)
{
   return _xsstrcmpwithtable(p1,cb1,p2,cb2,_lower_ansi_char_table_ );
}
/*{{end-c-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _bcmp
            | syntax_: `_bcmp( p1, p2, nBytes )`
            | category: memory
            | _kw_: memcmp, compare memory, compare bytes
   }}*/
/*{{|desc: Compares two memory buffers byte by byte.
    | params:
    - `p1` Numeric - First buffer pointer.
    - `p2` Numeric - Second buffer pointer.
    - `nBytes` Numeric - Number of bytes to compare.

    Returns Numeric - -1 when p1 is lower, 0 when both buffers match, and 1 when p1 is greater. }}*/
XPPRET XPPENTRY _BCMP( XppParamList pl )
{
   _retnl(pl, _bcmp( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcmp
            | syntax_: `int _bcmp( LPBYTE p1, LPBYTE p2, UINT cb )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcmp
            | _kw_: memcmp, compare memory, compare bytes
   }}*/
/*{{|desc: Binary compare of cb raw bytes of two buffers; zero bytes have no special meaning.
    | params:
    - `p1` LPBYTE - First buffer.
    - `p2` LPBYTE - Second buffer.
    - `cb` UINT - Number of bytes to compare.

    Returns int - -1 when p1 sorts lower, 0 when the cb bytes match, 1 when p1 sorts higher. }}*/
OT4XB_API int   _bcmp(LPBYTE p1, LPBYTE p2 , UINT cb)
{
   int i = 0;
   while( cb && (!(i = (*p1) - (*p2) )) )
   {
      p1++; p2++;
      cb--;
   }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _bcmpwithtable
            | syntax_: `int _bcmpwithtable( LPBYTE p1, LPBYTE p2, UINT cb, LPBYTE pt )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _bcmpwithtable
            | _kw_: compare memory, translation table, case folding
   }}*/
/*{{|desc: Like _bcmp() but folds every byte through the 256-byte table pt before comparing - for example a
      lowercase table gives a case-insensitive binary compare. With pt == NULL it behaves like _bcmp().
    | params:
    - `p1` LPBYTE - First buffer.
    - `p2` LPBYTE - Second buffer.
    - `cb` UINT - Number of bytes to compare.
    - `pt` LPBYTE - 256-byte translation table, or NULL.

    Returns int - -1, 0 or 1 as in _bcmp(). }}*/
OT4XB_API int _bcmpwithtable(LPBYTE p1, LPBYTE p2 , UINT cb, LPBYTE pt)
{
   int i = 0;
   if(!pt) return _bcmp(p1,p2,cb);
   while( cb && (!(i = pt[(*p1)] - pt[(*p2)] )) )
   {
      p1++; p2++;
      cb--;
   }
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: dwCrc32Lower
            | syntax_: `DWORD dwCrc32Lower( DWORD dwCRC, LPBYTE pStr, ULONG nLen )`
            | category: hash/crc32
            | header: ot4xb_c_exported.h
            | mangled-name: dwCrc32Lower
            | _kw_: crc32, lowercase, case insensitive hash, checksum
   }}*/
/*{{|desc: CRC32 of a buffer folded to lowercase: every byte goes through the internal ANSI lowercase table
      before entering the CRC, so strings differing only in case give the same value. The CRC can be built
      in chunks by feeding the previous result back through dwCRC.
    | params:
    - `dwCRC` DWORD - 0 for the first chunk, or the value returned for the previous chunk.
    - `pStr` LPBYTE - Buffer to process.
    - `nLen` ULONG - Number of bytes.

    Returns DWORD - Updated CRC32 value. }}*/
OT4XB_API DWORD dwCrc32Lower(DWORD dwCRC,LPBYTE pStr,ULONG nLen)
{
   return dwCrc32WithTable(dwCRC,pStr,nLen,_lower_ansi_char_table_);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrhash
            | syntax_: `DWORD _xstrhash( LPSTR pKey, DWORD cb )`
            | category: hash
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrhash
            | _kw_: string hash, case insensitive, hash function
   }}*/
/*{{|desc: Case-insensitive string hash: every byte is folded through the internal ANSI lowercase table and
      mixed with a shift-xor scheme.
    | params:
    - `pKey` LPSTR - Buffer to hash.
    - `cb` DWORD - Number of bytes.

    Returns DWORD - Hash value, masked to 31 bits so it always fits a positive signed integer. }}*/
OT4XB_API DWORD _xstrhash(LPSTR pKey, DWORD cb)
{
   DWORD dwh = 0;
   DWORD n;
   for( n=0;n < cb; n++)
   {
      BYTE ch = _lower_ansi_char_table_[(reinterpret_cast<LPBYTE>(pKey)[n])];
      dwh = (dwh << 3) ^ dwh ^ (( DWORD) ch ) ;
   }
  return (DWORD)(dwh & 0x7FFFFFFF);
}
/*{{end-c-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _xstrhtcs
            | syntax_: `DWORD _xstrhtcs( LPSTR pKey, DWORD cb )`
            | category: hash
            | header: ot4xb_c_exported.h
            | mangled-name: _xstrhtcs
            | _kw_: string hash, case sensitive, hash function
   }}*/
/*{{|desc: Case-sensitive variant of _xstrhash(): same shift-xor mixing, but bytes are hashed as they are.
    | params:
    - `pKey` LPSTR - Buffer to hash.
    - `cb` DWORD - Number of bytes.

    Returns DWORD - Hash value, masked to 31 bits so it always fits a positive signed integer. }}*/
OT4XB_API DWORD _xstrhtcs(LPSTR pKey, DWORD cb)
{
   DWORD dwh = 0;
   DWORD n;
   for( n=0;n < cb; n++)
   {
      BYTE ch = reinterpret_cast<LPBYTE>(pKey)[n];
      dwh = (dwh << 3) ^ dwh ^ (( DWORD) ch ) ;
   }
  return (DWORD)(dwh & 0x7FFFFFFF);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_interlocked_alloc
            | syntax_: `void * ot4xb_interlocked_alloc( void )`
            | category: atomic
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_interlocked_alloc
            | _kw_: interlocked counter, atomic, allocate counter, thread safe
   }}*/
/*{{|desc: Allocates a zero-initialized 4-byte counter from a private heap reserved for interlocked
      counters, ready for the Windows Interlocked* functions. Release with ot4xb_interlocked_free().

    Returns void * - Pointer to the new LONG counter, initialized to 0. }}*/
OT4XB_API void*  __cdecl ot4xb_interlocked_alloc(void)
{
   return HeapAlloc( h_interlocked_heap , MYHEAPFLAGS , 4 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_interlocked_free
            | syntax_: `DWORD ot4xb_interlocked_free( void * p )`
            | category: atomic
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_interlocked_free
            | _kw_: interlocked counter, atomic, free counter
   }}*/
/*{{|desc: Releases a counter allocated with ot4xb_interlocked_alloc().
    | params:
    - `p` void * - Counter returned by ot4xb_interlocked_alloc().

    Returns DWORD - Always 0. }}*/
OT4XB_API DWORD __cdecl ot4xb_interlocked_free(void* p)
{
   HeapFree( h_interlocked_heap , 0 , p);
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _hdict_filter_cmpi
            | syntax_: `BOOL _hdict_filter_cmpi( LPSTR key, DWORD cb_key, LPSTR pat, DWORD cb_pat )`
            | header: ot4xb_c_exported.h
            | category: string/match
            | mangled-name: _hdict_filter_cmpi
            | _kw_: hdict filter, prefix match, key filter, iterate
   }}*/
/*{{|desc: Ready-made key filter for _hdict_iterate_step() (prefix match): accepts a key when its first
      cb_pat bytes equal pat ignoring case, through the internal ANSI lowercase table. A pattern longer than
      the key, or any NULL/zero argument, gives FALSE.
    | params:
    - `key` LPSTR - Key to test.
    - `cb_key` DWORD - Key length in bytes.
    - `pat` LPSTR - Pattern to match.
    - `cb_pat` DWORD - Pattern length in bytes.

    Returns BOOL - TRUE when the key starts with the pattern, case-insensitive. }}*/
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_cmpi(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   if( cb_pat > cb_key ){ return FALSE; }
   return (BOOL) (_bcmpwithtable((LPBYTE) key,(LPBYTE) pat , cb_pat, _lower_ansi_char_table_ ) == 0);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _hdict_filter_strstri
            | syntax_: `BOOL _hdict_filter_strstri( LPSTR key, DWORD cb_key, LPSTR pat, DWORD cb_pat )`
            | header: ot4xb_c_exported.h
            | category: string/match
            | mangled-name: _hdict_filter_strstri
            | _kw_: hdict filter, substring match, key filter, iterate
   }}*/
/*{{|desc: Ready-made key filter for _hdict_iterate_step() (substring match): accepts a key when pat appears
      anywhere inside it, ignoring case (StrStrI). Both strings must be zero terminated; the lengths are
      only used to reject empty or oversized patterns.
    | params:
    - `key` LPSTR - Zero-terminated key to test.
    - `cb_key` DWORD - Key length in bytes.
    - `pat` LPSTR - Zero-terminated pattern to find.
    - `cb_pat` DWORD - Pattern length in bytes.

    Returns BOOL - TRUE when pat is found inside key. }}*/
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_strstri(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   if( cb_pat > cb_key ){ return FALSE; }
   return (BOOL) StrStrI(key,pat);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _hdict_filter_wildcmpi
            | syntax_: `BOOL _hdict_filter_wildcmpi( LPSTR key, DWORD cb_key, LPSTR pat, DWORD cb_pat )`
            | header: ot4xb_c_exported.h
            | category: string/match
            | mangled-name: _hdict_filter_wildcmpi
            | _kw_: hdict filter, wildcard match, key filter, iterate
   }}*/
/*{{|desc: Ready-made key filter for _hdict_iterate_step() (wildcard match): accepts a key when it matches
      the pattern with bStrWildCmpI(), a case-insensitive wildcard compare. Both strings must be zero
      terminated; the lengths are only used to reject NULL or empty arguments.
    | params:
    - `key` LPSTR - Zero-terminated key to test.
    - `cb_key` DWORD - Key length in bytes.
    - `pat` LPSTR - Zero-terminated wildcard pattern.
    - `cb_pat` DWORD - Pattern length in bytes.

    Returns BOOL - TRUE when the key matches the pattern. }}*/
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_wildcmpi(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   return (BOOL) bStrWildCmpI(pat,key);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _shift_ptr_
            | syntax_: `_shift_ptr_( @pMem, @nBytes, nSkip )`
            | category: memory
            | _kw_: pointer arithmetic, advance pointer, offset, byte count
   }}*/
/*{{|desc: Shifts a pointer, and optionally reduces an associated byte count.
    | params:
    - `@pMem` Numeric by reference - Pointer to shift by nSkip bytes.
    - `@nBytes` Numeric by reference - Optional remaining byte count reduced by nSkip.
    - `nSkip` Numeric - Number of bytes to add to the pointer.

    Returns Logical/Numeric - When nBytes is supplied, returns .T. while bytes remain. Otherwise returns the
      shifted pointer.

    |note: Also _shift_ptr_( pMem, NIL, nSkip ) -> pShifted }}*/
_XPP_REG_FUN_( _SHIFT_PTR_  )
{
   TXppParamList xpp(pl,3);
   LONG p  = xpp[1]->GetLong();
   LONG  sh = xpp[3]->GetLong();
   if( xpp[2]->CheckType(XPP_NUMERIC) )
   {
      LONG cb = xpp[2]->GetLong();
      xpp[1]->PutLong( p + sh );
      xpp[2]->PutLong( cb - sh );
      xpp[0]->PutBool( (cb - sh) > 0  );
   }
   else
   {
      xpp[0]->PutLong( p + sh );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dwscan
            | syntax_: `int _dwscan( LPDWORD pdw, int item_count, DWORD dwValue )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _dwscan
            | _kw_: find DWORD, search array, position, scan
   }}*/
/*{{|desc: Return the 0 based position of dwValue into the DWORD array pdw or -1 if not found
    | params:
    - `pdw` LPDWORD - Array to scan.
    - `item_count` int - Number of items in the array.
    - `dwValue` DWORD - Value to find.

    Returns int - Zero-based position of the first match, or -1 when not found. }}*/
OT4XB_API int _dwscan(LPDWORD pdw, int item_count , DWORD dwValue )
{
   int n;
   for( n = 0; n < item_count; n++)
   {
      if( pdw[n] == dwValue )
      {
         return n;
      }
   }
   return -1;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
///<cdecl_function name="_dwscan_lwstrcrc32">
///<short></short>
///<proto>OT4XB_API int _dwscan_lwstrcrc32(LPDWORD pdw, int item_count , LPSTR k , int cb, DWORD* pdwcrc)</proto>
///<description>
/// Return the 0 based position of dwCrc32Lower(0,k,cb) into the array pdw or -1 if not found.
/// If pdwcrc not NULL will retrieve the string dwCrc32Lower().
/// You can use cb = -1 if k is Zero terminated
///</description>
///</cdecl_function>
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dwscan_lwstrcrc32
            | syntax_: `int _dwscan_lwstrcrc32( LPDWORD pdw, int item_count, LPSTR k, int cb, DWORD * pdwcrc )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _dwscan_lwstrcrc32
            | _kw_: find crc32, key lookup, DWORD array, lowercase crc
   }}*/
/*{{|desc: Scans a DWORD array for the lowercase CRC32 of a key: computes dwCrc32Lower(0,k,cb) and returns
      its position inside pdw, or -1 when the value is not there.
    | params:
    - `pdw` LPDWORD - Array of CRC32 values to scan.
    - `item_count` int - Number of items in the array.
    - `k` LPSTR - Key string.
    - `cb` int - Key length in bytes, or -1 to take the zero-terminated length of k.
    - `pdwcrc` DWORD * - Optional; receives the computed CRC32 of the key.

    Returns int - Zero-based position of the first match, or -1 when not found. }}*/
OT4XB_API int _dwscan_lwstrcrc32(LPDWORD pdw, int item_count , LPSTR k , int cb, DWORD* pdwcrc)
{
   if( cb == -1 )
   {
      cb = _xstrlen(k);
   }
   DWORD crc = dwCrc32Lower(0,(LPBYTE) k,(ULONG) cb);
   if( pdwcrc ){ pdwcrc[0] = crc; }
   return _dwscan( pdw,item_count,crc);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dwscan_lwstrcrc32_ex
            | syntax_: ```
                 int _dwscan_lwstrcrc32_ex( LPDWORD pdw, int item_count, LPSTR k, int cb, DWORD * pdwcrc, int item_start )
              ```
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _dwscan_lwstrcrc32_ex
            | _kw_: find crc32, key lookup, DWORD array, start item
   }}*/
/*{{|desc: Like _dwscan_lwstrcrc32() but the scan can start at a given item: with item_start > 0 the first
      item_start items are skipped.
    | params:
    - `pdw` LPDWORD - Array of CRC32 values to scan.
    - `item_count` int - Total number of items in the array.
    - `k` LPSTR - Key string.
    - `cb` int - Key length in bytes, or -1 to take the zero-terminated length of k.
    - `pdwcrc` DWORD * - Optional; receives the computed CRC32 of the key.
    - `item_start` int - Zero-based item where the scan starts; 0 or negative scans from the first one.

    Returns int - Position relative to item_start (add item_start for the absolute index), or -1 when not
      found. }}*/
OT4XB_API int _dwscan_lwstrcrc32_ex( LPDWORD pdw, int item_count, LPSTR k, int cb, DWORD* pdwcrc , int item_start)
{
	if ( cb == -1 )
	{
		cb = _xstrlen( k );
	}
	DWORD crc = dwCrc32Lower( 0, (LPBYTE) k, (ULONG) cb );
	if ( pdwcrc ) { pdwcrc[0] = crc; }
	if ( item_start > 0)
	{
		item_count -= item_start;
		pdw = _mk_ptr_( LPDWORD, pdw, ( ( (DWORD) item_start & 0x3FFFFFFF ) << 2 ) );
	}
	return _dwscan( pdw, item_count, crc );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _qwscan
            | syntax_: `int _qwscan( ULONGLONG * pqw, int item_count, ULONGLONG * pvalue )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _qwscan
            | _kw_: find 64-bit, search array, ULONGLONG, position
   }}*/
/*{{|desc: Returns the zero-based position of a 64-bit value inside the ULONGLONG array pqw, or -1 when it
      is not there. The value to find is read from pvalue[0].
    | params:
    - `pqw` ULONGLONG * - Array to scan.
    - `item_count` int - Number of items in the array.
    - `pvalue` ULONGLONG * - Points to the value to find.

    Returns int - Zero-based position of the first match, or -1 when not found. }}*/
OT4XB_API int _qwscan(ULONGLONG * pqw, int item_count, ULONGLONG * pvalue)
{
	int n;
	ULONGLONG qw = pvalue[0];
	for (n = 0; n < item_count; n++)
	{
		if (pqw[n] == qw)
		{
			return n;
		}
	}
	return -1;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _qwscan_atoqw
            | syntax_: `int _qwscan_atoqw( ULONGLONG * pqw, int item_count, LPSTR int_string, ULONGLONG * pqvalue )`
            | category: memory
            | header: ot4xb_c_exported.h
            | mangled-name: _qwscan_atoqw
            | _kw_: find 64-bit, decimal string, search array, ULONGLONG
   }}*/
/*{{|desc: Like _qwscan() but the value arrives as text: int_string is parsed as a decimal unsigned 64-bit
      number (strtoull) and searched in the array.
    | params:
    - `pqw` ULONGLONG * - Array to scan.
    - `item_count` int - Number of items in the array.
    - `int_string` LPSTR - Decimal string holding the value to find.
    - `pqvalue` ULONGLONG * - Optional; receives the parsed value.

    Returns int - Zero-based position of the first match, or -1 when not found. }}*/
OT4XB_API int _qwscan_atoqw(ULONGLONG * pqw, int item_count, LPSTR int_string, ULONGLONG * pqvalue)
{
	LPSTR p = 0;
	ULONGLONG q = 0;
	int result;
	if (!pqvalue) { pqvalue = &q;  }
	pqvalue[0] = strtoull(int_string, &p, 10);
	result =  _qwscan(pqw, item_count, pqvalue);
	return result;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: begin_xwatch_thread
            | syntax_: `BOOL begin_xwatch_thread( void )`
            | category: memory
            | _kw_: memory watch, leak detection, debug, thread
   }}*/
/*{{|desc: Debug builds only. Starts a memory watch on the calling thread: resets the watch counter that _xgrab()/_mgrab()
      increment and _xfree()/_mfree() decrement while called from this thread. Only one thread can watch at a time.

    Returns BOOL - TRUE when the watch started, FALSE when another watch is already active. }}*/
extern "C" OT4XB_API BOOL __cdecl begin_xwatch_thread(void)
{
   if( _watching_thread_ )
   {
      return FALSE;
   }
   _watching_thread_ = GetCurrentThreadId();
   _watching_thread_count = 0;
   return TRUE;
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: count_xwatch_thread
            | syntax_: `LONG count_xwatch_thread( void )`
            | category: memory
            | _kw_: memory watch, leak detection, balance, debug
   }}*/
/*{{|desc: Debug builds only. Returns the current balance of the memory watch started with
      begin_xwatch_thread(): allocations minus releases seen so far on the watched thread.

    Returns LONG - Watch counter, or -1 when the calling thread is not the watched one. }}*/
extern "C" OT4XB_API LONG  __cdecl count_xwatch_thread(void)
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      return _watching_thread_count;
   }
   return (DWORD) -1;
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: end_xwatch_thread
            | syntax_: `LONG end_xwatch_thread( void )`
            | category: memory
            | _kw_: memory watch, leak detection, report, debug
   }}*/
/*{{|desc: Debug builds only. Stops the memory watch started with begin_xwatch_thread() and reports the
      final balance; a non-zero value means unbalanced allocations on the watched thread.

    Returns LONG - Final watch counter, or -1 when the calling thread is not the watched one (the watch is
      then left running). }}*/
extern "C" OT4XB_API LONG  __cdecl end_xwatch_thread(void)
{
   DWORD n = (DWORD) -1;
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      n = (LONG) _watching_thread_count;
      _watching_thread_count = 0;
      _watching_thread_      = 0;
   }
   return n;
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: on_xwatch_thread
            | syntax_: `void on_xwatch_thread( LONG n )`
            | category: memory
            | _kw_: memory watch, leak detection, counter, debug
   }}*/
/*{{|desc: Debug builds only. Adds n to the memory watch counter when the calling thread is the watched
      one. The allocation functions call it with 1 and the release functions with -1.
    | params:
    - `n` LONG - Value added to the watch counter.

    Returns void }}*/
extern "C" OT4XB_API void  __cdecl on_xwatch_thread(LONG n)
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      _watching_thread_count += n;
   }
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#endif
// -----------------------------------------------------------------------------------------------------------------





