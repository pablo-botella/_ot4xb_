//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#ifdef __cplusplus
typedef void (*XbCMethodType)( TXbClsParams * );
typedef void ( * _PFN_STACKEVAL_)(void * , void * , UINT );
typedef LONG ( * _PFN4TREE_)( void * , DWORD , void *, DWORD );
#endif
//----------------------------------------------------------------------------------------------------------------------
typedef LONG ( __stdcall * _PFN_TLDLIST_)( DWORD*, void *, void *);
typedef void ( __stdcall * _PFN_DESTROY_ITEM_)( void *, DWORD ); // void func( void* pItem , DWORD dwCargo);
typedef int  ( __cdecl   * _PFN_CMPCTX_WITH_CAST )(DWORD*,void**,void**);
typedef int  ( __cdecl   * _PFN_CMPCTX_)( void *, void* , void* );
typedef int  ( __cdecl   * _PFN_CMPCTXCT_)( void *, const void* , const void* );
typedef BOOL ( __cdecl   * _PFN_HDICT_FILTER_)( LPSTR , DWORD , LPSTR , DWORD );
typedef void (__stdcall  * _PFN_GetSystemTimeAsFileTime)(LPFILETIME);


//----------------------------------------------------------------------------------------------------------------------
typedef int ( __cdecl   * _PFN_OT4XB_RECURSE_DIR_CREATE_ITEM_)( WIN32_FIND_DATA* , LPSTR , DWORD );
//----------------------------------------------------------------------------------------------------------------------
// ot4xb_vheap_st
struct OT4XB_VHEAP_structure;
typedef void* ( __cdecl   * _PFN_OT4XB_VHEAP_ALLOC )( OT4XB_VHEAP_structure* , UINT  );
typedef void  ( __cdecl   * _PFN_OT4XB_VHEAP_FREE  )( OT4XB_VHEAP_structure* , void* );
typedef struct OT4XB_VHEAP_structure
{
   _PFN_OT4XB_VHEAP_ALLOC  vgrab;
   _PFN_OT4XB_VHEAP_FREE   vfree;
   DWORD                   ctx;
   DWORD                   flags1;   
   DWORD                   flags2;      
   DWORD                   user_ctx;
} OT4XB_VHEAP;
// -----------------------------------------------------------------------------------------------------------------
extern OT4XB_VHEAP ot4xb_xheap;
//----------------------------------------------------------------------------------------------------------------------
typedef struct CON_PLKSTREX__struct
{
   ULONG           nType;
   ULONG           nLen;
   BOOL            bByRef;
   ContainerHandle con;  
   LPSTR           pStr; 
   BOOL            bWrite;
   DWORD           nCntType; // 0 int/byte , 1 FLOAT
   TList *         pComplex;
} CON_PLKSTREX;
//-----------------------------------------------------------------------------------------------------------------------
typedef struct GWST_DEF_MEMBER_ITEM__struct
{
   DWORD dwCrc32;
   DWORD dwShift;
   DWORD dwSize;
   WORD  wMemPos;
   WORD  wGwstType;
} GWST_DEF_MEMBER_ITEM;
// ---------------------------------------------------------------------------
typedef struct GWST_SORT_ITEM__struct
{
   DWORD dwGwstType;
   DWORD dwShift;
   DWORD dwSize;
   DWORD dwFlags;
   DWORD dw0;
   DWORD dw1;
   DWORD dwTable;
   DWORD dwCompare;
} GWST_SORT_ITEM;
// ---------------------------------------------------------------------------





// -----------------------------------------------------------------------------------------------------------------
#define _retLong(pl,n) ( _retnl(pl,(LONG) n ) )
// ---------------------------------------------------------------------------
#define _parHMENU(pl,n) ( (HMENU) _parLong(pl,n,0) )
#define _parUINT(pl,n) ( (UINT) _parLong(pl,n,0) )
#define _parint(pl,n) ( (int) _parLong(pl,n,0) )
#define _parDWORD(pl,n) ( (DWORD) _parLong(pl,n,0) )
#define _parULONG(pl,n) ( (DWORD) _parLong(pl,n,0) )
//-----------------------------------------------------------------------------------------------------------------------

