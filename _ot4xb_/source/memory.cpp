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
OT4XB_API OT4XB_VHEAP*  ot4xb_get_xheap(void)
{
   return &ot4xb_xheap;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void* __cdecl ot4xb_xheap_alloc( OT4XB_VHEAP*  , UINT  n)
{
   return _xgrab(n);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void  __cdecl ot4xb_xheap_free( OT4XB_VHEAP*  , void* p)
{
   _xfree(p);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int  __cdecl ot4xb_xheap_min(void)
{
   return _heapmin();
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void* __cdecl ot4xb_vheap_alloc( OT4XB_VHEAP* vh  , UINT  n)
{
   return HeapAlloc((HANDLE) vh->ctx,vh->flags1,n);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void  __cdecl ot4xb_vheap_free( OT4XB_VHEAP*  vh , void* p)
{
   HeapFree( (HANDLE) vh->ctx,vh->flags2,p);
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LONG __cdecl ot4xb_interlocked_next(void)
{
   if( s_p_interlocked_counter )
   {
      return InterlockedIncrement( s_p_interlocked_counter );
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
void _API_Memory_InitProc( void)
{
    DWORD dw;
    hHeap_p = GetProcessHeap();
    h_interlocked_heap = HeapCreate(HEAP_GENERATE_EXCEPTIONS,0,0);
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
}
//----------------------------------------------------------------------------------------------------------------------
// return the size of a page of memory
OT4XB_API UINT _vpagesize(void){ return (UINT)( _sys_inf_.dwPageSize  - sizeof( UINT) );}
//----------------------------------------------------------------------------------------------------------------------
// alloc 1 page of virtual memory
// if pnSize is provided the page size will be stored
// must be released with _vfree
OT4XB_API void * _vgrab1page(UINT * pnSize )
{
   UINT nSize = _vpagesize();
   if( pnSize) pnSize[0] = nSize;
   return _vgrab(nSize);
}
//----------------------------------------------------------------------------------------------------------------------
// alloc at least n bytes of virtual memory
// must be released with _vfree
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
//----------------------------------------------------------------------------------------------------------------------
// return the size of a memory block allocated with _vgrab() or _vgrab1page()
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
//----------------------------------------------------------------------------------------------------------------------
// release a block of memory allocated with _vgrab() or _vgrab1page()
OT4XB_API void _vfree( void * p)
{
   LPBYTE pp = ((LPBYTE) p)  - sizeof(UINT);
   UINT * pn = (UINT *) pp;
   UINT n    = pn[0];
   VirtualUnlock((void *) pp,n);
   VirtualFree((void*) pp,n,MEM_RELEASE);
}
//----------------------------------------------------------------------------------------------------------------------
// alloc memory from the default process heap
OT4XB_API void * _pgrab( UINT n)
{
     return HeapAlloc( hHeap_p , MYHEAPFLAGS , n );
}
//----------------------------------------------------------------------------------------------------------------------
// release memory allocated with _pgrab()
OT4XB_API void _pfree( void * p)
{
   HeapFree(hHeap_p,0,p);
}
//----------------------------------------------------------------------------------------------------------------------
// alloc memory from the ot4xb default heap
// this can be the preferred allocation method
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void * _xgrow(void* pp  , UINT n)
{
     void * p = realloc(pp,n);
     return p;
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void* _xxgrowa(void* pp ,UINT nCurrent , UINT nNew , UINT nItemSize)
{
   return _xxgrow(pp,nCurrent * nItemSize, nNew * nItemSize);
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void * _mgrab( UINT n)
{
     InterlockedIncrement(&_xgrab_count_);
#ifdef _DEBUG
     on_xwatch_thread(1);
#endif
     return malloc(n);
}
//----------------------------------------------------------------------------------------------------------------------
// Release memory allocated with _xgrab()
OT4XB_API void _xfree( void * p)
{
   free(p);
   InterlockedDecrement(&_xgrab_count_);
#ifdef _DEBUG
   on_xwatch_thread(-1);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
// Release memory allocated with _mgrab()
OT4XB_API void _mfree( void * p)
{
   InterlockedDecrement(&_xgrab_count_);
#ifdef _DEBUG
   on_xwatch_thread(-1);
#endif
   free(p);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API UINT _mmsize(void* p){ return _msize(p);}
OT4XB_API void * _mgrow(void* pp  , UINT n){ return realloc(pp,n);}
OT4XB_API void * _mcgrab(UINT nItems , UINT nItemSize ){ return calloc(nItems , nItemSize );}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XGRAB_COUNT_(XppParamList pl){ _retnl(pl,_xgrab_count_);}
XPPRET XPPENTRY _XGRAB(XppParamList pl){  __xb__grab(pl, _xgrab ); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XFREE(XppParamList pl){  __xb__free(pl, _xfree ); }
// ---------------------------------------------------------------------------
XPPRET XPPENTRY _PGRAB(XppParamList pl){  __xb__grab(pl, _pgrab ); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _PFREE(XppParamList pl){  __xb__free(pl, _pfree ); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _VGRAB(XppParamList pl){  __xb__grab(pl, _vgrab ); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _VFREE(XppParamList pl){  __xb__free(pl, _vfree ); }
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
// copy a string from a Xbase++ container into a new _xgrab() memory block.
// The string is guaranteed to be zero terminated, but can contain more zeros at any position
// must be released with _xfree()
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BSET( XppParamList pl )
{
   LPBYTE  pStr    = (LPBYTE) _parLong(pl,1);
   CHAR    sz[2];
   UINT    nBytes  = (UINT) _parLong(pl,3);
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,2,0);
   else sz[0] = (CHAR) (_parLong(pl,2) & 0xFF);
   _retnl(pl,(LONG) _bset(pStr,(BYTE)sz[0],nBytes));
}
//----------------------------------------------------------------------------------------------------------------------
// init nBytes from pStr with the ch value
OT4XB_API LPBYTE _bset(LPBYTE pStr, BYTE ch , UINT nBytes)
{
   UINT n;
   for( n = 0; n < nBytes ; n++) pStr[n] = ch;
   return pStr;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BMOVE( XppParamList pl )
{
   _retnl(pl,(LONG) _bmove( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
//----------------------------------------------------------------------------------------------------------------------
// copy nBytes of memory from one location to another
// the locations can be overlapped
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BDUP( XppParamList pl )
{
   _retnl(pl,(LONG) _bdup( (LPBYTE) _parLong(pl,1),(UINT) _parLong( pl,2,0)));
}
//----------------------------------------------------------------------------------------------------------------------
// Clone a memory buffer of nBytes using _xgrab() to allocate it .
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BCOPYWITHTABLE( XppParamList pl )
{
   _retnl(pl, (LONG) _bcopywithtable((LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),
                                     (UINT) _parLong( pl,3),(LPBYTE)  _parLong(pl,4))
         );
}
//----------------------------------------------------------------------------------------------------------------------
// Copy  nBytes from pSrc to pDest using a mapping character table.
// pTable must be string at least 256 BYTES
OT4XB_API LPBYTE _bcopywithtable(LPBYTE pDest, LPBYTE pSrc , UINT nBytes, LPBYTE pTable)
{
   if( nBytes )
   {
      UINT n;
      for( n = 0; n < nBytes ; n++) pDest[n] = pTable[pSrc[n]];
   }
   return pDest;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BCOPY( XppParamList pl )
{
   _retnl(pl,(LONG) _bcopy( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
//----------------------------------------------------------------------------------------------------------------------
// copy nBytes of memory from one location to another
// if the locations are overlapped results can be unpredictables.
// For overlapped locations use _bmove() instead
OT4XB_API LPBYTE _bcopy(LPBYTE pDest, LPBYTE pSrc , UINT nBytes)
{
   if( nBytes )
   {
      UINT n;
	  for (n = 0; n < nBytes; n++) { pDest[n] = pSrc[n]; }
   }
   return pDest;
}
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BCOPYF( XppParamList pl )
{
   _bcopyf( (LPBYTE) _parLong(pl,1),
            (LPBYTE) _parLong(pl,2),
            (UINT) _parLong( pl,3,0),
            (UINT) _parLong( pl,4,0));
   _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
// Copy the minimum value betwen nSrcSize and nDstSize  bytes from pSrc  to pDest memory pointers.
OT4XB_API void _bcopyf(LPBYTE pDest, LPBYTE pSrc , UINT nDstSize, UINT nSrcSize)
{
   UINT nBytes = ( (nDstSize < nSrcSize) ? nDstSize : nSrcSize) ;
   UINT n;
   for( n = 0; n < nBytes ; n++) pDest[n] = pSrc[n];
   if(nSrcSize > nBytes) for( n = nBytes; n < nDstSize ; n++) pDest[n] = 0x20;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BSCAN( XppParamList pl )
{
   LPBYTE  pStr    = (LPBYTE) _parLong(pl,1);
   UINT    nBytes  = (UINT) _parLong(pl,2);
   CHAR    sz[2];
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,3,0);
   else sz[0] = (CHAR) (_parLong(pl,3) & 0xFF);
   _retnl(pl,(LONG) _bscan(pStr,nBytes,(BYTE)sz[0]));
}
//----------------------------------------------------------------------------------------------------------------------
// Return the position of the first ocurrence of the BYTE ch whithin the buffer pStr.
// nPos will be < nBytes if ch is found.
OT4XB_API UINT  _bscan(LPBYTE pStr, UINT nBytes , BYTE ch)
{
   UINT n;
   for( n = 0; n < nBytes; n++)
   {
      if( pStr[n] == ch ) return n;
   }
   return nBytes;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrcpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location.
// return the destination buffer
OT4XB_API LPSTR _xstrcpy(LPSTR pDest, LPSTR pSrc)
{
   LPSTR p = pDest;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPWSTR _xstrcpyW(LPWSTR pDest, LPWSTR pSrc)
{
   LPWSTR p = pDest;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XXSTRCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xxstrcpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location.
// _xxstrcpy() will return ( pDst + nBytesCopied )

OT4XB_API LPSTR _xxstrcpy(LPSTR pDest, LPSTR pSrc)
{
   while( (BOOL)(*pDest = *pSrc) ){pDest++;pSrc++;}
   return( pDest );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTCCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstccpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2),(UINT) _parLong(pl,3,0)));
}
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location stopping
// at nMax bytes if NULL not found before.
OT4XB_API UINT _xstccpy(LPSTR pDest, LPSTR pSrc, UINT nMax)
{
   UINT  n = 0;
   if( nMax ){ do{ pDest[n] = *pSrc;n++;} while(*pSrc++ && (n < nMax) ); }
   return( n );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRNCPY( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrncpy( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2),(UINT) _parLong(pl,3,0)));
}
//----------------------------------------------------------------------------------------------------------------------
// Copy a NULL terminated string pointed to by pSrc to pDest memory location
// stopping at nMax bytes if NULL not found before.
// If bytes copied are less than nMax fill the rest of pDest with NULLs up to nMax bytes.

OT4XB_API LPSTR _xstrncpy(LPSTR pDest, LPSTR pSrc, UINT nMax)
{
   UINT  n = 0;
   if( nMax )
   {
      do{ pDest[n] = *pSrc;n++;} while(*pSrc++ && (n < nMax) );
      for( ; n < nMax; n++) pDest[n] = 0;
   }
   return pDest;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRCAT( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrcat( (LPSTR) _parLong(pl,1),(LPSTR) _parLong(pl,2)));
}
//----------------------------------------------------------------------------------------------------------------------
// Append the string pointed to by pSrc to pDest . Assuming both strings are NULL terminated.
OT4XB_API LPSTR _xstrcat( LPSTR pDest, LPSTR pSrc )
{
   LPSTR p = pDest;
   while(*p) p++;
   while( (BOOL)(*p++ = *pSrc++) );
   return( pDest );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTPCHR( XppParamList pl )
{
   CHAR    sz[2];
   if( _partype(pl,2) & XPP_CHARACTER ) _parc(sz,2,pl,2,0);
   else sz[0] = (CHAR) (_parLong(pl,2) & 0xFF);
   _retnl(pl,(LONG) _xstpchr( (LPSTR) _parLong(pl,1),sz[0]));
}
//----------------------------------------------------------------------------------------------------------------------
// Return the memory pointer of the first occurence of the character ch whithin
// the NULL terminated pStr. Return 0 if NULL is found before ch.
OT4XB_API LPSTR _xstpchr( LPSTR pStr , CHAR ch )
{
   while (*pStr && (*pStr != ch)) pStr++;
   if( *pStr == ch ) return pStr;
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTPBLK( XppParamList pl )
{
   _retnl(pl,(LONG) _xstpblk( (LPSTR) _parLong(pl,1)));
}
//----------------------------------------------------------------------------------------------------------------------
// Return the memory pointer of the first occurence of a character
// not matching TAB,SPACE, CR or  LF whithin the NULL terminated pStr.
// Return 0 if NULL is found before TAB,SPACE, CR or  LF
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRLEN( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrlen( (LPSTR) _parLong(pl,1)));
}
//----------------------------------------------------------------------------------------------------------------------
// Count the characters of pStr up to the first NULL
OT4XB_API UINT _xstrlen(LPSTR pStr)
{
  UINT n = 0;
  while( pStr[n] ) n++;
  return n;
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API UINT _xstrlenW(LPWSTR pStr)
{
  UINT n = 0;
  while( pStr[n] ) n++;
  return n;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRDUP( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrdup( (LPSTR) _parLong(pl,1)));
}
//----------------------------------------------------------------------------------------------------------------------
// Clone a zero terminated string  using _xgrab() to allocate it .
OT4XB_API LPSTR _xstrdup(LPSTR pStr )
{
   LPSTR pNew;
   if( !pStr) return 0;
   pNew = (LPSTR) _xgrab(_xstrlen(pStr) + 1);
   if(pNew) return  _xstrcpy(pNew,pStr);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR _xssr_(LPSTR* pp , LPSTR p)
{
   if( !pp ) return 0;
   if( pp[0] ){ _xfree( (void*) (pp[0]) ); pp[0] = 0; }
   if( p ){ pp[0] = _xstrdup(p);}
   return pp[0];
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
 // like xssr but get the ownership of the source pointer instead of allocate a new one
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPWSTR _xstrdupW(LPWSTR pStr )
{
   LPWSTR pNew;
   if( !pStr) return 0;
   pNew = (LPWSTR) _xgrab( (_xstrlenW(pStr) + 1) * 2 );
   if(pNew) return  _xstrcpyW(pNew,pStr);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _XSTRAT( XppParamList pl )
{
   _retnl(pl,(LONG) _xstrat( (LPSTR) _parLong(pl,1), (int) _parLong(pl,2), (LPSTR) _parLong(pl,3),(int) _parLong(pl,4)));
}
//----------------------------------------------------------------------------------------------------------------------
// Return the position of the first ocurrence of pSep within the string pointed to by pStr.
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR __cdecl _xstr_nextline( LPSTR p , int* pcb )
{
   int cb;

   for( cb = pcb[0] ; cb ; cb-- , p++ )
   {
      if( p[0] == 0x0D )
      {
         cb--;p++;
         if( cb )
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 ) // warning C4706: assignment within conditional expression
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
OT4XB_API int    _xstrcmpi( LPSTR p1 , LPSTR p2 )
{
   return _xstrcmpwithtable(p1,p2,_lower_ansi_char_table_ );
}
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
OT4XB_API int    _xsstrcmpi( LPSTR p1 , ULONG cb1 , LPSTR p2 , ULONG cb2)
{
   return _xsstrcmpwithtable(p1,cb1,p2,cb2,_lower_ansi_char_table_ );
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _BCMP( XppParamList pl )
{
   _retnl(pl, _bcmp( (LPBYTE) _parLong(pl,1),(LPBYTE) _parLong(pl,2),(UINT) _parLong( pl,3,0)));
}
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
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
#pragma warning( default : 4706 )
//-----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD dwCrc32Lower(DWORD dwCRC,LPBYTE pStr,ULONG nLen)
{
   return dwCrc32WithTable(dwCRC,pStr,nLen,_lower_ansi_char_table_);
}
// -----------------------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
//static HANDLE h_interlocked_heap = 0
// INTERLOCKED
OT4XB_API void*  __cdecl ot4xb_interlocked_alloc(void)
{
   return HeapAlloc( h_interlocked_heap , MYHEAPFLAGS , 4 );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl ot4xb_interlocked_free(void* p)
{
   HeapFree( h_interlocked_heap , 0 , p);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_cmpi(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   if( cb_pat > cb_key ){ return FALSE; }
   return (BOOL) (_bcmpwithtable((LPBYTE) key,(LPBYTE) pat , cb_pat, _lower_ansi_char_table_ ) == 0);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_strstri(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   if( cb_pat > cb_key ){ return FALSE; }
   return (BOOL) StrStrI(key,pat);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" OT4XB_API BOOL  __cdecl _hdict_filter_wildcmpi(LPSTR key, DWORD cb_key, LPSTR pat , DWORD cb_pat )
{
   if( !(cb_key && cb_pat && key && pat )){ return FALSE; }
   return (BOOL) bStrWildCmpI(pat,key);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _SHIFT_PTR_  ) // _shift_ptr_( @p,@cb, nSkip ) -> cb > 0
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
// -----------------------------------------------------------------------------------------------------------------
///<cdecl_function name="_dwscan">
///<short></short>
///<proto>OT4XB_API int _dwscan(LPDWORD pdw, int item_count , DWORD dwValue )</proto>
///<description>Return the 0 based position of dwValue into the DWORD array pdw or -1 if not found</description>
///</cdecl_function>
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
// -----------------------------------------------------------------------------------------------------------------
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
		pdw = _mk_ptr_( LPDWORD, pdw, (DWORD) ( ( item_start >> 2 ) & 0x3FFFFFFF ) );
	}
	return _dwscan( pdw, item_count, crc );
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
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
extern "C" OT4XB_API LONG  __cdecl count_xwatch_thread(void)
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      return _watching_thread_count;
   }
   return (DWORD) -1;
}
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
extern "C" OT4XB_API void  __cdecl on_xwatch_thread(LONG n)
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      _watching_thread_count += n;
   }
}

#endif
// -----------------------------------------------------------------------------------------------------------------





