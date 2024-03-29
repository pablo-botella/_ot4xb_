//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TokenizeEx_t : public T_ot4xb_base  
{
   public:
      // ---------------------------------------------------------------------------------
      class separator_t : public T_ot4xb_base
      {
         public:      
         LPBYTE m_str;
         int    m_cb;
         // ---------------------------------------------------------------------------------
         separator_t( LPBYTE str = 0,  int cb = 0);     
         ~separator_t(void);
         // ---------------------------------------------------------------------------------
         BOOL test(LPBYTE p , int cb );
         // ---------------------------------------------------------------------------------                  
      };
      // ---------------------------------------------------------------------------------
      class item_t : public T_ot4xb_base
      {
         public:            
         LPBYTE m_start;
         int    m_cb;
         // ---------------------------------------------------------------------------------
         item_t( LPBYTE start = 0,  int cb = 0);     
         // ---------------------------------------------------------------------------------                  
      };
      // ---------------------------------------------------------------------------------      
      TList* m_sep_list;
      TList* m_item_list;
      LPBYTE m_buffer;
      int    m_cb;
      // ---------------------------------------------------------------------------------            
      TokenizeEx_t(void);
      ~TokenizeEx_t(void);
      // ---------------------------------------------------------------------------------                  
      void ClearItemList(void);
      void FreeBuffer(void);
      void SetBuffer( LPBYTE buffer , int cb );
      void SetBuffer( XppParamList pl , ULONG nParam);
      void AddSeparator( LPBYTE s , int cb );
      // ---------------------------------------------------------------------------------
      int test_sep( LPBYTE p , int cb ); // separator size or 0 if not sep
      // ---------------------------------------------------------------------------------
      void run(void);
      void run_xbase( XppParamList pl );
      // ---------------------------------------------------------------------------------
      
      
      
      
      
};
//----------------------------------------------------------------------------------------------------------------------








