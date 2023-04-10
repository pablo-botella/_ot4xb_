#pragma once
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
class THDictKey : public T_ot4xb_base
{
   public:
      LPSTR                m_pKey;
      DWORD                m_cbKey;
      THDictKey(LPSTR pKey, DWORD cb, BOOL bDup = FALSE);
      ~THDictKey(void);
      THDictItem* Find(THashTable* pht);     
      THDictItem* Find(THtcsTable* pht);           
      // ---------------------------------------------------------------------------------
      static THDictKey* FromPl( XppParamList pl , ULONG np);
      static THDictKey* FromXbItem(ContainerHandle con);
      static LPSTR XbItemToPointer(ContainerHandle con, DWORD * pcb );
};
// -----------------------------------------------------------------------------------------------------------------
class THDictItem : public T_ot4xb_base
{
   public:
      LPSTR                m_pKey;
      DWORD                m_cbKey;
      DWORD                m_dwDataSize;
      enum {hdi_empty=0,hdi_bool,hdi_int,hdi_double,hdi_xdate,hdi_str,hdi_xbase} m_nDataType;
      void *               m_pData;
      DWORD                m_dwExtra;

      THDictItem( THDictKey* pdk, ContainerHandle conData);
      THDictItem( LPSTR pKey , UINT cbKey , LPSTR pData , UINT cbData , BOOL bDup);
      THDictItem( LPSTR pKey , UINT cbKey , DWORD value , BOOL bDup);
      ~THDictItem(void);
      static void __stdcall _OnDestroyItem_(void* p,DWORD);
      ContainerHandle ConPutValue( ContainerHandle con = NULLCONTAINER );
      void AddToHashTable( THashTable* pht );
      void AddToHashTable( THtcsTable* pht );      
      
};
// -----------------------------------------------------------------------------------------------------------------
