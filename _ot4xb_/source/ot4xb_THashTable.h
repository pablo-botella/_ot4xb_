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
class OT4XB_API THashItem  : public T_ot4xb_base
{
   public:
      THashItem*  m_pNext;
      THashItem*  m_pPrev;
      LPSTR       m_pKey;     // Key is provided within pData
      DWORD       m_cbKey;
      DWORD       m_dwCrc;
      void*       m_pData;
      THashItem(LPSTR pKey , DWORD cbKey , void* pData );
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API THashBucket
{
   public:
      DWORD        m_nCount;
      THashItem*   m_pChain;
      // ---------------------------
      THashItem *  FindItem(LPSTR pKey , DWORD cbKey);
      THashItem *  InsertItem( THashTable* pTable , THashItem * pNew ); // pOldItem if Replaced
      THashItem * _insert_before_( THashTable* pTable , THashItem * pItem , THashItem * pNew );
      THashItem * _replace_item_(  THashTable* pTable , THashItem * pItem , THashItem * pNew );
      THashItem * _insert_after_(  THashTable* pTable , THashItem * pItem , THashItem * pNew );
      THashItem * _remove_item_(  THashTable* pTable , THashItem * pItem);
};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API THashTable  : public T_ot4xb_base
{
   public:
      DWORD                m_nCount;
      THashItem*           m_pFirstItem;
      THashBucket*         m_pBuckets;
      DWORD                m_nBuckets;
      DWORD                m_dwCargo;
      DWORD                m_dwPopIndex;
      DWORD                m_dwMaxPopulation;
      _PFN_DESTROY_ITEM_   m_pfnOnDestroyItem;
      void*                m_cs_cargo;         

      // ---------------------------
      static int Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2);
      // ---------------------------
      THashTable(DWORD nBuckets = 0,DWORD dwMaxPopulation = 256);
      ~THashTable(void);
      void DeleteAllItems( void );
      void ReHash( DWORD nBuckets = 0);
      void * FindItem(LPSTR pKey , DWORD cbKey);
      THashItem * FindItemEx(LPSTR pKey , DWORD cbKey);      
      void * RemoveItem(LPSTR pKey , DWORD cbKey);
      BOOL DeleteItem(LPSTR pKey , DWORD cbKey);
      void * InsertItem(LPSTR pKey , DWORD cbKey, void * pData, BOOL bDestroyOnReplace = TRUE);
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TStringMapTable  : public T_ot4xb_base
{
   public:
      BOOL                 m_bCaseSensitive;
      THashTable*          m_ht;
      void*                m_rgx_interface;
      BOOL                 m_ok;
      // ---------------------------
      TStringMapTable(LPSTR search , LPSTR replace );
      ~TStringMapTable();
      LPSTR exec( LPSTR cc );

};
// -----------------------------------------------------------------------------------------------------------------


#if 1
#pragma warning( disable : 4706 )
inline int THashTable::Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2)
{
   int i;
   if( dw1 < dw2 )  return -1;
   if( dw1 > dw2 )  return  1;
   i = 0;
   while(cb1 && cb2 && (!(i = ((int) _lower_ansi_char_table_[(*p1)]) - ((int) _lower_ansi_char_table_[(*p2)]))))
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
#else
inline int THashTable::Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2)
{
   int i;
   if( dw1 < dw2 )  return -1;
   if( dw1 > dw2 )  return  1;
   if( cb1 == cb2 ) return _memicmp((void*)p1,(void*) p2,cb1);
   i = _memicmp((void*)p1,(void*) p2,( (cb1 < cb2) ? cb1 : cb2 ) );
   if( i < 0 ) return -1;
   if( i > 0 ) return  1;
   if( cb1 < cb2 ) return -1;
   if( cb1 > cb2 ) return  1;
   return 0;
}

#endif
// -----------------------------------------------------------------------------------------------------------------
#endif
#endif
// -----------------------------------------------------------------------------------------------------------------

