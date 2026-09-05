#pragma once
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_APIcpp_Hash_h_
#define _API_cpp_APIcpp_Hash_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THashItem
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/hash
   | desc: One entry of a {{ilink: <cpp-class THashTable> THashTable}}: the key, its CRC and the data pointer,
     linked with the other entries of the table. The key is not copied: **m_pKey** points to memory the
     | _kw_: hash table entry, key, crc, data pointer
     caller keeps alive (typically inside the data itself) for as long as the entry exists. }}*/
class OT4XB_API THashItem  : public T_ot4xb_base
{
   public:
      /*{{|member_: `THashItem* m_pNext` | desc_: Next entry in the table's list (the entries of one bucket are
         contiguous, sorted by CRC and key). }}*/
      THashItem*  m_pNext;
      /*{{|member_: `THashItem* m_pPrev` | desc_: Previous entry. }}*/
      THashItem*  m_pPrev;
      /*{{|member_: `LPSTR m_pKey` | desc_: The key bytes, owned by the caller. }}*/
      LPSTR       m_pKey;     // Key is provided within pData
      /*{{|member_: `DWORD m_cbKey` | desc_: Length of the key in bytes. }}*/
      DWORD       m_cbKey;
      /*{{|member_: `DWORD m_dwCrc` | desc_: CRC32 of the key in lower case, the first comparison criterion. }}*/
      DWORD       m_dwCrc;
      /*{{|member_: `void* m_pData` | desc_: The data of the entry. }}*/
      void*       m_pData;
      /*{{|method_: `THashItem( LPSTR pKey, DWORD cbKey, void* pData )` | desc_: An unlinked entry with its
         CRC computed. }}*/
      THashItem(LPSTR pKey , DWORD cbKey , void* pData );
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THashBucket
   | category: c-api/classes , container/hash
   | desc: One slot of a {{ilink: <cpp-class THashTable> THashTable}}: the head of its chain of entries and
     their number. The chain is a run of the table's single list, kept sorted by CRC and then by key (case
     insensitive), so a lookup walks the run and stops as soon as it passes the key. The methods maintain the
     | _kw_: hash bucket, chain, sorted entries
     chain and the table counters together; they are the table's business, not the caller's. }}*/
class OT4XB_API THashBucket
{
   public:
      /*{{|member_: `DWORD m_nCount` | desc_: Entries in this bucket. }}*/
      DWORD        m_nCount;
      /*{{|member_: `THashItem* m_pChain` | desc_: First entry of the bucket, 0 when empty. }}*/
      THashItem*   m_pChain;
      // ---------------------------
      /*{{|method_: `THashItem* FindItem( LPSTR pKey, DWORD cbKey )` | desc_: The entry with that key, 0 when
         it is not in the bucket. }}*/
      THashItem *  FindItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `THashItem* InsertItem( THashTable* pTable, THashItem* pNew )`
         | desc_: Links **pNew** in its sorted place. When an entry with the same key exists its key, CRC
           and data are swapped with the new one's and the now-old item is returned for the caller to
           dispose of; 0 when the entry is new. }}*/
      THashItem *  InsertItem( THashTable* pTable , THashItem * pNew ); // pOldItem if Replaced
      /*{{|method_: `THashItem* _insert_before_( THashTable* pTable, THashItem* pItem, THashItem* pNew )`
         | desc_: Links pNew before pItem, updating the table's first entry and the counters. Returns 0. }}*/
      THashItem * _insert_before_( THashTable* pTable , THashItem * pItem , THashItem * pNew );
      /*{{|method_: `THashItem* _replace_item_( THashTable* pTable, THashItem* pItem, THashItem* pNew )`
         | desc_: Swaps the contents of pItem and pNew (the linked entry keeps its place) and returns pNew,
           which now carries the old key and data. }}*/
      THashItem * _replace_item_(  THashTable* pTable , THashItem * pItem , THashItem * pNew );
      /*{{|method_: `THashItem* _insert_after_( THashTable* pTable, THashItem* pItem, THashItem* pNew )`
         | desc_: Links pNew after pItem, updating the counters. Returns 0. }}*/
      THashItem * _insert_after_(  THashTable* pTable , THashItem * pItem , THashItem * pNew );
      /*{{|method_: `THashItem* _remove_item_( THashTable* pTable, THashItem* pItem )`
         | desc_: Unlinks pItem, updating the chain head, the table's first entry and the counters, and
           returns it (not deleted). }}*/
      THashItem * _remove_item_(  THashTable* pTable , THashItem * pItem);
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THashTable
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/hash
   | desc: A hash table from byte-string keys, compared case insensitively (ANSI lower case), to `void*`
     data. The buckets are a power of two (8 at least) and double whenever the entries exceed half the
     buckets; every entry is also linked in one list from **m_pFirstItem**, bucket after bucket, so the whole
     table can be walked. The data pointers are opaque: the table only touches them through the optional
     destroy callback **m_pfnOnDestroyItem**, called with **m_dwCargo** when an entry is deleted or the table
     destroyed. Keys are not copied.
   | note: Create it with `new`: the constructor relies on the zeroed memory of the ot4xb heap for the
     members it does not set (m_pBuckets, m_pFirstItem, m_pfnOnDestroyItem, m_dwCargo). Set the callback
     | _kw_: hash table, case insensitive keys, void data, destroy callback
     and the cargo right after construction when the data needs disposing. }}*/
class OT4XB_API THashTable  : public T_ot4xb_base
{
   public:
      /*{{|member_: `DWORD m_nCount` | desc_: Number of entries. }}*/
      DWORD                m_nCount;
      /*{{|member_: `THashItem* m_pFirstItem` | desc_: First entry of the list of all entries. }}*/
      THashItem*           m_pFirstItem;
      /*{{|member_: `THashBucket* m_pBuckets` | desc_: The bucket array, m_nBuckets long. }}*/
      THashBucket*         m_pBuckets;
      /*{{|member_: `DWORD m_nBuckets` | desc_: Number of buckets, a power of two. }}*/
      DWORD                m_nBuckets;
      /*{{|member_: `DWORD m_dwCargo` | desc_: Second argument of the destroy callback. }}*/
      DWORD                m_dwCargo;
      /*{{|member_: `DWORD m_dwPopIndex` | desc_: Longest bucket chain seen since the last ReHash(). }}*/
      DWORD                m_dwPopIndex;
      /*{{|member_: `DWORD m_dwMaxPopulation` | desc_: Chain length limit given to the constructor (64 at
         least), kept for the rehash policy; the current policy only looks at the entry count. }}*/
      DWORD                m_dwMaxPopulation;
      /*{{|member_: `_PFN_DESTROY_ITEM_ m_pfnOnDestroyItem`
         | desc_: `void __stdcall fn( void* pData, DWORD dwCargo )`, called for the data of every entry that
           DeleteItem(), DeleteAllItems(), the destructor or a replacing InsertItem() get rid of; 0 means the
           data is never touched. }}*/
      _PFN_DESTROY_ITEM_   m_pfnOnDestroyItem;
      /*{{|member_: `void* m_cs_cargo` | desc_: Zeroed by the constructor and free for the owner (a lock,
         for example). }}*/
      void*                m_cs_cargo;
      // ---------------------------
      /*{{|method_: `static int Compare( LPSTR p1, UINT cb1, DWORD dw1, LPSTR p2, UINT cb2, DWORD dw2 )`
         | desc_: The ordering of the entries: by CRC (**dw1**, **dw2**) first, then by the keys compared
           byte by byte in ANSI lower case, a shorter key first. Returns -1, 0 or 1. With both CRCs 0 it is
           a plain case-insensitive key comparison. }}*/
      static int Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2);
      // ---------------------------
      /*{{|method_: `THashTable( DWORD nBuckets = 0, DWORD dwMaxPopulation = 256 )`
         | desc_: An empty table with **nBuckets** rounded up to a power of two (8 at least). }}*/
      THashTable(DWORD nBuckets = 0,DWORD dwMaxPopulation = 256);
      /*{{|method_: `~THashTable( void )` | desc_: DeleteAllItems(). }}*/
      ~THashTable(void);
      /*{{|method_: `void DeleteAllItems( void )` | desc_: Runs the destroy callback on every data pointer,
         deletes every entry and frees the buckets: an empty table with no buckets. }}*/
      void DeleteAllItems( void );
      /*{{|method_: `void ReHash( DWORD nBuckets = 0 )` | desc_: Rebuilds the buckets with **nBuckets** rounded
         up to a power of two (8 at least) and relinks every entry; nothing happens when the count does not
         change. }}*/
      void ReHash( DWORD nBuckets = 0);
      /*{{|method_: `void* FindItem( LPSTR pKey, DWORD cbKey )` | desc_: The data of the entry with that key, 0
         when there is none. **cbKey** -1 means the zero-terminated length. }}*/
      void * FindItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `THashItem* FindItemEx( LPSTR pKey, DWORD cbKey )` | desc_: The entry itself instead of
         its data, 0 when there is none. }}*/
      THashItem * FindItemEx(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `void* RemoveItem( LPSTR pKey, DWORD cbKey )` | desc_: Unlinks and deletes the entry and
         returns its data, untouched, for the caller; 0 when the key is not there. }}*/
      void * RemoveItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `BOOL DeleteItem( LPSTR pKey, DWORD cbKey )` | desc_: RemoveItem() plus the destroy
         callback on the data. TRUE only when the entry existed, had data and there is a callback. }}*/
      BOOL DeleteItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `void* InsertItem( LPSTR pKey, DWORD cbKey, void* pData, BOOL bDestroyOnReplace = TRUE )`
         | desc_: Adds an entry (growing the buckets first when needed). When the key already exists the entry
           takes the new key pointer and data: with **bDestroyOnReplace** and a callback the old data is
           destroyed and 0 returned, otherwise the old data is returned for the caller to dispose of. 0 for
           a new key. }}*/
      void * InsertItem(LPSTR pKey , DWORD cbKey, void * pData, BOOL bDestroyOnReplace = TRUE);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
inline int THashTable::Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2)
{
   int i;
   if( dw1 < dw2 )  return -1;
   if( dw1 > dw2 )  return  1;
   i = 0;
   while(cb1 && cb2 && (!(i = ((int) _lower_ansi_char_table_[(BYTE)(*p1)]) - ((int) _lower_ansi_char_table_[(BYTE)(*p2)]))))
   {
      p1++; p2++;
      cb1--; cb2--;
   }    
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   if( cb1)    return -1;
   if( cb2)    return  1;
   return 0;
}
#pragma warning( default : 4706 )
// -----------------------------------------------------------------------------------------------------------------
#endif
#endif
// -----------------------------------------------------------------------------------------------------------------

