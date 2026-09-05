#pragma once
#include <ot4xb_TLists.h>
// -----------------------------------------------------------------------------------------------------------------
class ot4xb_dirty_dlgedit;
// -----------------------------------------------------------------------------------------------------------------
#define DIRTY_DLGEDIT_CLSNAME "ot4xb_463BB094_607D_4109_B867_F45AD4479828"
#define DIRTY_PGPANEL_CLSNAME "ot4xb_519347DA_AF5B_41D0_888A_291B15F9D29D"

// -----------------------------------------------------------------------------------------------------------------

class ot4xb_dirty_dlgedit  : public T_ot4xb_base
{
   public:
      // ----------------
      class edit_spec_t : public T_ot4xb_base
      {
         public:
            // -------------------------
            DWORD m_nGPos; // 1 based position in the Xbase++ array
            DWORD m_nTab;  // zero based Tab pos
            HWND  m_hLabel;
            HWND  m_hValue;
            RECT  m_rcLabel;  // x,y,cx,cy
            RECT  m_rcValue;    // x,y,cx,cy
            DWORD m_nFlags;
            LPSTR m_pLabel;
            LPSTR m_pValue;
            DWORD m_cbValue;
            LONG  m_nlValue;            
            DWORD m_dwXbType;
            TList* m_pList;
            // -------------------------
            edit_spec_t(void);
            ~edit_spec_t( void );
            // -------------------------
            void CalcMinSizes(HDC hDC);
            void SetLabel( LPSTR p );
            LPSTR GetLabel(void);
            void SetValue( LPSTR p , BOOL bCopy = TRUE);
            LPSTR GetValue(void);
            void PutValue( ContainerHandle cona);
            void CollectEditBuffer(void);            
            // -------------------------
            void AddPickValue( LPSTR p , BOOL bCopy = TRUE);            
      };
      // --------------------------------------------------------
      class page_spec_t : public T_ot4xb_base
      {
         public:
            // -------------------------
            HWND  m_hPage;
            int   m_nTab;  // zero based Tab pos
            LONG  m_cx_min;
            LONG  m_label_max;
            LONG  m_cy_step;            
            LONG  m_cy_total;            
            LONG  m_y_max_scroll;
            LONG  m_y_scroll_pos;
            LPSTR m_pCaption;
            LONG  m_layout_mode;
            LONG  m_pos_focused;
            LONG  m_last_editable;            
            int   m_i_accelerator_pos;
            ot4xb_dirty_dlgedit* m_pDlgEdit;
            TList m_Edits;
            // -------------------------
            page_spec_t(LPSTR pCaption, BOOL bCopy , ot4xb_dirty_dlgedit* pDlgEdit);
            ~page_spec_t( void );
            // -------------------------
            void RefreshAcceleratorPos(void);
            // -------------------------            
            void SetCaption( LPSTR p );
            LPSTR GetCaption(void);
            // -------------------------
            BOOL create(void);
            // -------------------------
            edit_spec_t* AddEdit( DWORD nGPos , DWORD nFlags , LPSTR pLabel , void* pValue , DWORD dwXbType, LPSTR pCap = 0);
            void CreateEditControls(HDC hDC , SIZE & border , HFONT hFont);
            void AdjustEditControls(HDC hDC , SIZE & border);
            // -------------------------            
            void show(void);
            void hide(void);
            // -------------------------  
            BOOL IsHotKey( UINT vk );
            BOOL PreTranslateMessage( MSG* pmsg);
            // -------------------------  
            LRESULT HandleVScroll(HWND hWnd , WORD wScroll , WORD wAction );
            LRESULT HandleWheel( LONG nDelta);
            // -------------------------  
            LONG find_edit( HWND hWnd );
            void on_edit_focus( LPARAM lp );
            void on_activate(void);
            // -------------------------                          
                        
      };
      // --------------------------------------------------------
      class button_spec_t : public T_ot4xb_base
      {
         public:
            // -------------------------  
            HWND m_hBtn;
            LPSTR m_pCaption;            
            DWORD m_nGPos; // 1 based position in the Xbase++ array            
            // -------------------------              
            button_spec_t(LONG nGPos , LPSTR pCaption, BOOL bCopy );
            ~button_spec_t(void);
            // -------------------------                          
            void SetCaption( LPSTR p );
            LPSTR GetCaption(void);
            // -------------------------
      };
      // --------------------------------------------------------      
      HINSTANCE m_hApp;
      BOOL    m_bLoop;
      HWND    m_hWndParent;
      HWND    m_hWndTopInvisible;
      HWND    m_hWnd;      
      HWND    m_hWndNotify;
      HWND    m_hTab;
      HWND    m_hPageCon;
      RECT    m_rc;
      LPSTR   m_pTitle;
      DWORD   m_dwStyle;
      DWORD   m_dwExStyle;
      DWORD   m_dwFlags;
      BOOL    m_bInSizeLoop;
      int     m_iPageSel;
      LONG    m_button_cy;
      LRESULT m_dlg_result;
      int     m_initial_tab_focus;
      // ----------------
      // ----------------
      TList   m_Btns; // contain button_spec_t pointers
      TList   m_Pages; // contain page_spec_t pointers      
      TList   m_GdiHandles;

      // ---------------------------------------------------------------------------------
      ot4xb_dirty_dlgedit(void)
      {
         _register_();
         m_hWndTopInvisible = 0;
         m_hApp = (HINSTANCE) GetModuleHandle(0);
         m_hWndParent  = 0;
         m_hWnd        = 0;
         m_hWndNotify  = 0;
         m_hTab        = 0;
         m_hPageCon    = 0;
         m_bLoop       = FALSE;
         ZeroMemory( &m_rc  , sizeof( m_rc ) );
         m_pTitle      = 0;
         m_dwStyle     = 0;
         m_dwExStyle   = 0;
         m_bInSizeLoop = 0;
         m_iPageSel    = -1;
         m_button_cy   = 30;  
         m_dlg_result  = -1; 
         m_dwFlags     =  0;   
         m_initial_tab_focus = -1;
      }
      // ---------------------------------------------------------------------------------
      ~ot4xb_dirty_dlgedit(void)
      {
         while( m_GdiHandles.Count() )
         {
            HGDIOBJ h = (HGDIOBJ) m_GdiHandles.Pop();
            if( h )  DeleteObject( (HGDIOBJ) h );
         }
         _xssr_(&m_pTitle,0);

         while( m_Pages.Count() )
         {
            page_spec_t* p = (page_spec_t*) m_Pages.Pop();
            if( p ) delete p;
         }
         while( m_Btns.Count() )
         {
            button_spec_t* p = (button_spec_t*) m_Btns.Pop();
            if( p ) delete p;
         }
         

      }
      // ---------------------------------------------------------------------------------
      void RegisterGdiHandle( HGDIOBJ h ){ m_GdiHandles.Add( (void*) h ); }
      // ---------------------------------------------------------------------------------
      void run( TXppParamList & xpp );
      // ---------------------------------------------------------------------------------
      void SetTitle( LPSTR pTitle );
      void SetParent( HWND hParent);
      void SetBoundingRect( int x , int y , int cx , int cy );
      void AddTab( LPSTR pCaption = 0 , BOOL bCopy = TRUE);
      void AddBtn( DWORD nGPos , LPSTR pCaption = 0 , BOOL bCopy = TRUE);      
      // ---------------------------------------------------------------------------------
      LRESULT OnTabChange( void );
      page_spec_t* GetPage(  int iPage = -1);
      void ShowPage( int iPage );
      void HidePage( int iPage );
      // ---------------------------------------------------------------------------------
      void _register_(void);
      // ---------------------------------------------------------------------------------
      BOOL create(void);
      // ---------------------------------------------------------------------------------
      BOOL    PreTranslateMessage( MSG* pmsg);
      LRESULT msgloop(void);
      LRESULT parent_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc);
      LRESULT dlg_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc);      
      LRESULT tab_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc);
      LRESULT pagecon_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc);
      LRESULT page_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc);
      void    adjust_rects(void);
      // ---------------------------------------------------------------------------------
      void CollectEditBuffers(void);
      // ---------------------------------------------------------------------------------
      void CreateEditControls(void);
      void ApplyFlagsToBoundingRect(void);      
      // ---------------------------------------------------------------------------------
      static DWORD __stdcall thread_proc(void* ctx );      

};
