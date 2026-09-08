#pragma once
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_APIcpp_Htcs_h_
#define _API_cpp_APIcpp_Htcs_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THtcsItem
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/hash
   | desc: One entry of a {{ilink: <cpp-class THtcsTable> THtcsTable}}: the same layout as
     {{ilink: <cpp-class THashItem> THashItem}} (key, length, CRC, data, links), with the CRC computed on
     the key bytes as they are. The key is not copied.
     | _kw_: THtcsItem, Class }}*/
class OT4XB_API THtcsItem  : public T_ot4xb_base
{
   public:
      /*{{|member_: `THtcsItem* m_pNext` | desc_: Next entry in the table's list. }}*/
      THtcsItem*  m_pNext;
      /*{{|member_: `THtcsItem* m_pPrev` | desc_: Previous entry. }}*/
      THtcsItem*  m_pPrev;
      /*{{|member_: `LPSTR m_pKey` | desc_: The key bytes, owned by the caller. }}*/
      LPSTR       m_pKey;     // Key is provided within pData
      /*{{|member_: `DWORD m_cbKey` | desc_: Length of the key in bytes. }}*/
      DWORD       m_cbKey;
      /*{{|member_: `DWORD m_dwCrc` | desc_: CRC32 of the key, case preserved. }}*/
      DWORD       m_dwCrc;
      /*{{|member_: `void* m_pData` | desc_: The data of the entry. }}*/
      void*       m_pData;
      /*{{|method_: `THtcsItem( LPSTR pKey, DWORD cbKey, void* pData )` | desc_: An unlinked entry with its
         CRC computed. }}*/
      THtcsItem(LPSTR pKey , DWORD cbKey , void* pData );
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THtcsBucket
   | category: c-api/classes , container/hash
   | desc: One slot of a {{ilink: <cpp-class THtcsTable> THtcsTable}}, the case-sensitive twin of
     {{ilink: <cpp-class THashBucket> THashBucket}}: the head of a sorted run of entries in the table's list
     and their number. The methods maintain the chain and the table counters; they are the table's business.
     | _kw_: THtcsBucket, Class }}*/
class OT4XB_API THtcsBucket
{
   public:
      /*{{|member_: `DWORD m_nCount` | desc_: Entries in this bucket. }}*/
      DWORD        m_nCount;
      /*{{|member_: `THtcsItem* m_pChain` | desc_: First entry of the bucket, 0 when empty. }}*/
      THtcsItem*   m_pChain;
      // ---------------------------
      /*{{|method_: `THtcsItem* FindItem( LPSTR pKey, DWORD cbKey )` | desc_: The entry with exactly that
         key, 0 when it is not in the bucket. }}*/
      THtcsItem *  FindItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `THtcsItem* InsertItem( THtcsTable* pTable, THtcsItem* pNew )` | desc_: Links **pNew** in
         its sorted place; when the key exists the contents are swapped and the now-old item returned, 0 for
         a new key. }}*/
      THtcsItem *  InsertItem( THtcsTable* pTable , THtcsItem * pNew ); // pOldItem if Replaced
      /*{{|method_: `THtcsItem* _insert_before_( THtcsTable* pTable, THtcsItem* pItem, THtcsItem* pNew )`
         | desc_: Links pNew before pItem. Returns 0. }}*/
      THtcsItem * _insert_before_( THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      /*{{|method_: `THtcsItem* _replace_item_( THtcsTable* pTable, THtcsItem* pItem, THtcsItem* pNew )`
         | desc_: Swaps the contents of pItem and pNew and returns pNew with the old key and data. }}*/
      THtcsItem * _replace_item_(  THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      /*{{|method_: `THtcsItem* _insert_after_( THtcsTable* pTable, THtcsItem* pItem, THtcsItem* pNew )`
         | desc_: Links pNew after pItem. Returns 0. }}*/
      THtcsItem * _insert_after_(  THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      /*{{|method_: `THtcsItem* _remove_item_( THtcsTable* pTable, THtcsItem* pItem )` | desc_: Unlinks
         pItem, keeping the chain head, the first entry and the counters right, and returns it. }}*/
      THtcsItem * _remove_item_(  THtcsTable* pTable , THtcsItem * pItem);
};
/*{{end-cpp-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: THtcsTable
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , container/hash
   | desc: The case-sensitive hash table: the same structure and rules as
     {{ilink: <cpp-class THashTable> THashTable}} (power-of-two buckets that double when the entries exceed
     half of them, one list of all entries, opaque data with an optional destroy callback, keys not copied)
     with keys compared byte by byte and hashed as they are, so "Key" and "key" are two entries. Create it
     with `new` for the same reason as THashTable.
     | _kw_: THtcsTable, Class }}*/
class OT4XB_API THtcsTable  : public T_ot4xb_base
{
   public:
      /*{{|member_: `DWORD m_nCount` | desc_: Number of entries. }}*/
      DWORD                m_nCount;
      /*{{|member_: `THtcsItem* m_pFirstItem` | desc_: First entry of the list of all entries. }}*/
      THtcsItem*           m_pFirstItem;
      /*{{|member_: `THtcsBucket* m_pBuckets` | desc_: The bucket array. }}*/
      THtcsBucket*         m_pBuckets;
      /*{{|member_: `DWORD m_nBuckets` | desc_: Number of buckets, a power of two. }}*/
      DWORD                m_nBuckets;
      /*{{|member_: `DWORD m_dwCargo` | desc_: Second argument of the destroy callback. }}*/
      DWORD                m_dwCargo;
      /*{{|member_: `DWORD m_dwPopIndex` | desc_: Longest bucket chain seen since the last ReHtcs(). }}*/
      DWORD                m_dwPopIndex;
      /*{{|member_: `DWORD m_dwMaxPopulation` | desc_: Chain length limit given to the constructor (64 at
         least), kept for the rehash policy. }}*/
      DWORD                m_dwMaxPopulation;
      /*{{|member_: `_PFN_DESTROY_ITEM_ m_pfnOnDestroyItem` | desc_: `void __stdcall fn( void* pData, DWORD dwCargo )`
         for the data the table gets rid of; 0 means the data is never touched. }}*/
      _PFN_DESTROY_ITEM_   m_pfnOnDestroyItem;
      /*{{|member_: `void* m_cs_cargo` | desc_: Zeroed by the constructor and free for the owner. }}*/
      void*                m_cs_cargo;
      // ---------------------------
      /*{{|method_: `static int Compare( LPSTR p1, UINT cb1, DWORD dw1, LPSTR p2, UINT cb2, DWORD dw2 )`
         | desc_: The ordering of the entries: by CRC first, then by the key bytes, a shorter key first.
           Returns -1, 0 or 1. }}*/
      static int Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2);
      // ---------------------------
      /*{{|method_: `THtcsTable( DWORD nBuckets = 0, DWORD dwMaxPopulation = 256 )` | desc_: An empty table
         with **nBuckets** rounded up to a power of two (8 at least). }}*/
      THtcsTable(DWORD nBuckets = 0,DWORD dwMaxPopulation = 256);
      /*{{|method_: `~THtcsTable( void )` | desc_: DeleteAllItems(). }}*/
      ~THtcsTable(void);
      /*{{|method_: `void DeleteAllItems( void )` | desc_: Runs the destroy callback on every data pointer,
         deletes every entry and frees the buckets. }}*/
      void DeleteAllItems( void );
      /*{{|method_: `void ReHtcs( DWORD nBuckets = 0 )` | desc_: Rebuilds the buckets with **nBuckets** rounded
         up to a power of two (8 at least) and relinks every entry. }}*/
      void ReHtcs( DWORD nBuckets = 0);
      /*{{|method_: `void* FindItem( LPSTR pKey, DWORD cbKey )` | desc_: The data of the entry with that key,
         0 when there is none (**cbKey** -1: the zero-terminated length). }}*/
      void * FindItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `void* RemoveItem( LPSTR pKey, DWORD cbKey )` | desc_: Unlinks and deletes the entry and
         returns its data untouched; 0 when the key is not there. }}*/
      void * RemoveItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `BOOL DeleteItem( LPSTR pKey, DWORD cbKey )` | desc_: RemoveItem() plus the destroy
         callback. TRUE only when the entry existed, had data and there is a callback. }}*/
      BOOL DeleteItem(LPSTR pKey , DWORD cbKey);
      /*{{|method_: `void* InsertItem( LPSTR pKey, DWORD cbKey, void* pData, BOOL bDestroyOnReplace = TRUE )`
         | desc_: Adds an entry; an existing key takes the new key pointer and data, the old data being
           destroyed (with **bDestroyOnReplace** and a callback) or returned. 0 for a new key. }}*/
      void * InsertItem(LPSTR pKey , DWORD cbKey, void * pData, BOOL bDestroyOnReplace = TRUE);
};
/*{{end-cpp-class}}*/
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( disable : 4706 )
inline int THtcsTable::Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2)
{
   int i;
   if( dw1 < dw2 )  return -1;
   if( dw1 > dw2 )  return  1;
   i = 0;
   while(cb1 && cb2 && (!(i = ((int) (*p1)) - ((int) (*p2))   )) )
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

