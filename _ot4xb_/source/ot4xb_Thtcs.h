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
class OT4XB_API THtcsItem  : public T_ot4xb_base
{
   public:
      THtcsItem*  m_pNext;
      THtcsItem*  m_pPrev;
      LPSTR       m_pKey;     // Key is provided within pData
      DWORD       m_cbKey;
      DWORD       m_dwCrc;
      void*       m_pData;
      THtcsItem(LPSTR pKey , DWORD cbKey , void* pData );
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API THtcsBucket
{
   public:
      DWORD        m_nCount;
      THtcsItem*   m_pChain;
      // ---------------------------
      THtcsItem *  FindItem(LPSTR pKey , DWORD cbKey);
      THtcsItem *  InsertItem( THtcsTable* pTable , THtcsItem * pNew ); // pOldItem if Replaced
      THtcsItem * _insert_before_( THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      THtcsItem * _replace_item_(  THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      THtcsItem * _insert_after_(  THtcsTable* pTable , THtcsItem * pItem , THtcsItem * pNew );
      THtcsItem * _remove_item_(  THtcsTable* pTable , THtcsItem * pItem);
};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API THtcsTable  : public T_ot4xb_base
{
   public:
      DWORD                m_nCount;
      THtcsItem*           m_pFirstItem;
      THtcsBucket*         m_pBuckets;
      DWORD                m_nBuckets;
      DWORD                m_dwCargo;
      DWORD                m_dwPopIndex;
      DWORD                m_dwMaxPopulation;
      _PFN_DESTROY_ITEM_   m_pfnOnDestroyItem;
      void*                m_cs_cargo;      

      // ---------------------------
      static int Compare( LPSTR p1 , UINT cb1, DWORD dw1 , LPSTR p2 , UINT cb2 , DWORD dw2);
      // ---------------------------
      THtcsTable(DWORD nBuckets = 0,DWORD dwMaxPopulation = 256);
      ~THtcsTable(void);
      void DeleteAllItems( void );
      void ReHtcs( DWORD nBuckets = 0);
      void * FindItem(LPSTR pKey , DWORD cbKey);
      void * RemoveItem(LPSTR pKey , DWORD cbKey);
      BOOL DeleteItem(LPSTR pKey , DWORD cbKey);
      void * InsertItem(LPSTR pKey , DWORD cbKey, void * pData, BOOL bDestroyOnReplace = TRUE);

};
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

