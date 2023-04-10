//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
#include <commctrl.h>
#include <Vssym32.h>
#include <shobjidl.h>
// -----------------------------------------------------------------------------------------------------------------
// ---- bits 0  - 1  MONITOR FLAGS ( MUTUALLY EXCLUSIVE )
#define OT4XB_DDF_MONITOR_MASK       0x00000003
#define OT4XB_DDF_MONITOR_DONTCARE   0x00000000    // DEFAULT
#define OT4XB_DDF_MONITOR_PRIMARY    0x00000001  // display in primary monitor
#define OT4XB_DDF_MONITOR_WINDOW     0x00000002  // display in Reference Window monitor
#define OT4XB_DDF_MONITOR_MOUSE      0x00000003  // display in mouse monitor
// ---- bit 2-3 ( MUTUALLY EXCLUSIVE )
#define OT4XB_DDF_DISPLAY_MASK       0x0000000C
#define OT4XB_DDF_DISPLAY_CENTERED   0x00000004
#define OT4XB_DDF_DISPLAY_MAXIMIZED  0x00000008
// ---- byte 1 coordinate system
#define OT4XB_DDF_COORD_MASK       0x00000030    // DEFAULT
#define OT4XB_DDF_COORD_SCREEN     0x00000000    // DEFAULT
// setting bit 0x10 or will reset monitor flags to OT4XB_DDF_MONITOR_DONTCARE
#define OT4XB_DDF_COORD_WINDOW     0x00000010
#define OT4XB_DDF_COORD_CLIENT     0x00000030
#define OT4XB_DDF_NOTASKBAR        0x00000100  // hide from task bar
#define OT4XB_DDF_CHILD            0x00000200  // hide from task bar
#define OT4XB_DDF_TITLE            0x00000800
#define OT4XB_DDF_DISABLEPARENT    0x00000400
#define OT4XB_DDF_CLIENT_EDGE      0x01000000  // draws a border arround the tab client window
// -----------
#define OT4XB_DDF_USETHREAD        0x00008000  // run in ot4xb thread pool
#define OT4XB_DDF_TOP              0x00010000
#define OT4XB_DDF_DUMMYHIT         0x00020000
#define OT4XB_DDF_BTNTABSTOP       0x00040000
#define OT4XB_DDF_HOOKPARENT       0x00080000
// -----------
#define OT4XB_DDN_CREATE_DLG       1
#define OT4XB_DDN_CREATE_TAB       2
#define OT4XB_DDN_CREATE_PAGE      3
#define OT4XB_DDN_CREATE_PGCON     4
#define OT4XB_DDN_CREATE_SAY       5
#define OT4XB_DDN_CREATE_CTRL      6
#define OT4XB_DDN_CREATE_BTN       7
#define OT4XB_DDN_BTNCLICK         8
// -----------

// -----------------------------------------------------------------------------------------------------------------
namespace ot4xb_dirty_dlgedit_ns {  // BEGIN NAMESPACE
   // ---------------------------------------------------------------------------------
   static BOOL b_clsreg = FALSE;
   // ---------------------------------------------------------------------------------
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_dlgproc , ot4xb_dirty_dlgedit , dlg_proc );
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_tabproc , ot4xb_dirty_dlgedit , tab_proc );
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_pageconproc , ot4xb_dirty_dlgedit , pagecon_proc );
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_pageproc , ot4xb_dirty_dlgedit , page_proc );
   static _TSTDCTXCBK_PROXI_WNDPROC_( proxi_parentproc , ot4xb_dirty_dlgedit , parent_proc );   
   // ---------------------------------------------------------------------------------
   static void RegisterWndClass(void)
   {
      if( b_clsreg ){ return; }

      INITCOMMONCONTROLSEX  icce;
      icce.dwSize = sizeof( INITCOMMONCONTROLSEX );
      icce.dwICC  = ICC_WIN95_CLASSES;
      InitCommonControlsEx(&icce);
      // --------------
      WNDCLASSEX  wc;
      HBRUSH      hbr = 0;
      ZeroMemory( &wc , sizeof(WNDCLASSEX) );
      wc.cbSize        = sizeof(WNDCLASSEX);
      if( GetClassInfoEx(0, WC_TABCONTROL ,&wc) ) { hbr =  wc.hbrBackground; }
      else { hbr = (HBRUSH) GetStockObject(LTGRAY_BRUSH);}
      // --------------
      char sz[1024];
      ZeroMemory( &wc , sizeof(WNDCLASSEX) );
      wc.cbSize        = sizeof(WNDCLASSEX);
      wc.style         = 0;
      wc.lpfnWndProc   = DefWindowProc;
      wc.cbClsExtra    = 0 ;
      wc.cbWndExtra    = 0 ;
      wc.hInstance     = (HINSTANCE) GetModuleHandle(0);
      wc.hIcon         = LoadIcon(0,IDI_APPLICATION);
      wc.hCursor       = LoadCursor(0,IDC_ARROW);
      wc.hbrBackground = hbr;
      wc.lpszMenuName  = 0;
      wc.lpszClassName = sz;
      wc.hIconSm       = LoadIcon(0,IDI_APPLICATION);

      wsprintf(sz,"%s",DIRTY_DLGEDIT_CLSNAME );
      RegisterClassEx(&wc);

      wsprintf(sz,"%s",DIRTY_PGPANEL_CLSNAME );
      RegisterClassEx(&wc);

      b_clsreg = TRUE;
   }
   // ---------------------------------------------------------------------------------


   // ---------------------------------------------------------------------------------

} //END_NAMESPACE
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::edit_spec_t::edit_spec_t(void)
{
   m_nGPos   = 0;
   m_nTab    = 0;
   m_hLabel  = 0;
   m_hValue  = 0;
   ZeroMemory(&m_rcLabel, sizeof(RECT));
   ZeroMemory(&m_rcValue, sizeof(RECT));
   m_nFlags  = 0;
   m_pLabel  = 0;
   m_pValue  = 0;
   m_cbValue = 0;
   m_dwXbType = XPP_CHARACTER;
   m_nlValue  = 0;
   m_pList    = 0;
}
//----------------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::edit_spec_t::~edit_spec_t( void )
{
   _xssr_(&m_pLabel,0);
   _xssr_cb_(&m_pValue,(UINT*) &m_cbValue,0,0);
   if( m_pList )
   {
      DWORD n;
      DWORD nn = m_pList->Count();
      for( n = 0; n < nn ; n++ )
      {
         void* p = m_pList->Replace(n,0);
         if(p){ _xfree(p);}
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::AddPickValue( LPSTR p , BOOL bCopy )
{
   if( p )
   {
      if( !m_pList ){ m_pList = new TList(); }
      m_pList->Add( ( bCopy ? _xstrdup(p) : p ) );
   }
}
//----------------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::CalcMinSizes(HDC hDC)
{
   if( !hDC ) return;
   m_rcLabel.right = m_rcLabel.bottom = 0;
   if(m_dwXbType & XPP_LOGICAL )
   {
      SIZE pt;
      GetTextExtentPoint32(hDC,"B",1,&pt);
      m_rcLabel.right = (pt.cx * 3);
      m_rcLabel.bottom = pt.cy;
      m_rcValue.right = (pt.cx * (4 + (m_pLabel ?  _xstrlen(m_pLabel) :0)) );
      m_rcValue.bottom = pt.cy + 2;
      return;
   }

   if( m_pLabel )
   {
      int cb = _xstrlen(m_pLabel);
      GetTextExtentPoint32(hDC,m_pLabel,cb,_mk_ptr_( LPSIZE,sizeof(SIZE),&m_rcLabel));
   }
   m_rcValue.right = m_rcValue.bottom = 0;
   if( m_pValue && m_cbValue)
   {
      GetTextExtentPoint32(hDC,m_pValue,m_cbValue,_mk_ptr_( LPSIZE,sizeof(SIZE),&m_rcValue));
   }
   else
   {
      GetTextExtentPoint32(hDC,"1234567890",10,_mk_ptr_( LPSIZE,sizeof(SIZE),&m_rcValue));
   }
   m_rcValue.bottom += 2;  m_rcValue.right  += 2;
}
//----------------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::SetLabel( LPSTR p ){ _xssr_(&m_pLabel,p); }
//----------------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::SetValue( LPSTR p , BOOL bCopy )
{
   if( bCopy ) {   _xssr_cb_(&m_pValue,(UINT*) &m_cbValue,p,(UINT)-1);}
   else {   _assr_cb_(&m_pValue,(UINT*) &m_cbValue,p,(UINT) -1);}
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR ot4xb_dirty_dlgedit::edit_spec_t::GetLabel(void){ return m_pLabel; }
//----------------------------------------------------------------------------------------------------------------------
LPSTR ot4xb_dirty_dlgedit::edit_spec_t::GetValue(void){ return m_pValue; }
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::PutValue( ContainerHandle cona)
{
   switch( m_dwXbType & 0xFF )
   {
      case XPP_LOGICAL:
      {
         _conArrayPutL(cona,(m_nlValue ? 1 : 0 ),m_nGPos+1,4,0);
         break;
      }
      default:
      {
         _conArrayPutCL(cona,(m_pValue ? m_pValue : "" ),m_cbValue,m_nGPos+1,4,0);
         break;
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::edit_spec_t::CollectEditBuffer(void)
{
   if(!m_hValue ){ return; }
   switch( m_dwXbType & 0xFF )
   {
      case XPP_LOGICAL:
      {
         BOOL b = (BOOL) SendMessage(m_hValue,BM_GETCHECK,0,0);
         m_nlValue = ( b ? 1 : 0 );
         break;
      }
      default:
      {
         DWORD cb_new = GetWindowTextLength(m_hValue);
         if( cb_new > m_cbValue ){ _assr_cb_(&m_pValue,(UINT*) &m_cbValue, (LPSTR) _xgrab(cb_new+1),cb_new);}
         m_cbValue = (DWORD) GetWindowText(m_hValue,m_pValue,m_cbValue + 1);
         break;
      }
   }

}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::button_spec_t::button_spec_t(LONG nGPos,LPSTR pCaption, BOOL bCopy )
{
   m_nGPos = nGPos;
   m_hBtn  = 0;
   m_pCaption = 0;
   if( pCaption && bCopy ){ SetCaption(pCaption); }
   else { m_pCaption = pCaption; }
}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::button_spec_t::~button_spec_t(void)
{
      SetCaption(0);
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::button_spec_t::SetCaption( LPSTR p ){ _xssr_(&m_pCaption,p); }
// -----------------------------------------------------------------------------------------------------------------
LPSTR ot4xb_dirty_dlgedit::button_spec_t::GetCaption(void){ return m_pCaption; }
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

ot4xb_dirty_dlgedit::page_spec_t::page_spec_t(LPSTR pCaption, BOOL bCopy , ot4xb_dirty_dlgedit* pDlgEdit)
{
   m_i_accelerator_pos = -1;
   m_pDlgEdit      = pDlgEdit;
   m_nTab          = m_pDlgEdit->m_Pages.Count();
   m_pDlgEdit->m_Pages.Add( (void*) this);
   m_hPage         = 0;
   m_cy_total      = 0;
   m_y_max_scroll  = 0;
   m_y_scroll_pos  = 0;
   m_pCaption      = 0;
   m_layout_mode   = 1;  // try put labes at the left
   m_cy_step       = 40;
   m_cx_min        = 300;
   m_label_max     = 0;
   m_pos_focused   = 0;
   m_last_editable = -1;

   if( pCaption && bCopy ){ SetCaption(pCaption); }
   else { m_pCaption = pCaption; RefreshAcceleratorPos(); }
}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::page_spec_t::~page_spec_t( void )
{
   while( m_Edits.Count() )
   {
      edit_spec_t* p = (edit_spec_t*) m_Edits.Pop();
      if( p ) delete p;
   }
   SetCaption(0);
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::RefreshAcceleratorPos(void)
{
   if( m_pCaption )
   {
      for(m_i_accelerator_pos = 0; m_pCaption[m_i_accelerator_pos];m_i_accelerator_pos++)
      {
         if(m_pCaption[m_i_accelerator_pos] == '&'){m_i_accelerator_pos++; return;}
      }
   }
   m_i_accelerator_pos = -1;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::SetCaption( LPSTR p ){ _xssr_(&m_pCaption,p); RefreshAcceleratorPos(); }
// -----------------------------------------------------------------------------------------------------------------
LPSTR ot4xb_dirty_dlgedit::page_spec_t::GetCaption(void){ return m_pCaption; };
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_dirty_dlgedit::page_spec_t::create(void)
{
   if( !m_pDlgEdit->m_hTab ){ return FALSE; }
   TCITEM item;
   ZeroMemory( &item , sizeof(TCITEM) );
   item.mask = TCIF_TEXT | TCIF_PARAM;
   item.lParam = (LPARAM) this;
   if( !m_pCaption )
   {
      char sz[256];
      wsprintf(sz,"%i", m_nTab+1 );
      SetCaption( sz );
   }
   item.pszText     = m_pCaption;
   item.cchTextMax  = _xstrlen( m_pCaption);
   TabCtrl_InsertItem( m_pDlgEdit->m_hTab , m_nTab , &item);
   m_hPage = CreateWindowEx(WS_EX_CONTROLPARENT,DIRTY_PGPANEL_CLSNAME,0,
                            WS_CHILD |WS_CLIPCHILDREN | WS_TABSTOP ,
                            0,0,0,0,m_pDlgEdit->m_hPageCon,(HMENU) (500 + m_nTab),m_pDlgEdit->m_hApp,0);
   _TSTDCTXCBK_SUBCLASS_( m_hPage, ot4xb_dirty_dlgedit_ns::proxi_pageproc , m_pDlgEdit );
   if( m_pDlgEdit->m_hWndNotify )
   {
      PostMessage( m_pDlgEdit->m_hWndNotify,
                   g_nMsgDirtyNotify,
                   (WPARAM) MAKELONG(OT4XB_DDN_CREATE_PAGE,m_nTab),
                   (LPARAM) m_hPage );
   }
   
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::edit_spec_t*
ot4xb_dirty_dlgedit::page_spec_t::AddEdit( DWORD nGPos,DWORD nFlags,LPSTR pLabel,void* pValue,DWORD dwXbType,LPSTR pCap)
{
   if( !pValue ) return 0;
   edit_spec_t* p = new edit_spec_t();
   p->m_nTab = m_nTab;
   if( pLabel ){ p->SetLabel(0); p->m_pLabel = pLabel;}
   else { p->SetLabel("");}
   p->m_nGPos = nGPos;
   p->m_nFlags = nFlags;
   // -----------
   m_Edits.Add( (void*) p );
   if( !(nFlags & ES_READONLY ) ){ m_last_editable = ((LONG) m_Edits.Count()) - 1; }
   switch( dwXbType & 0xFF )
   {
      case XPP_LOGICAL:
      {
         p->m_dwXbType = XPP_LOGICAL;
         p->m_nlValue = ( ((BOOL*) pValue)[0] ? 1 : 0 );
         if( pCap ) p->SetValue(pCap,TRUE);
         break;
      }
      default:
      {
         p->m_dwXbType = XPP_CHARACTER;
         if( pValue ){ p->SetValue((LPSTR) pValue,FALSE);}
         else { p->SetValue("",TRUE);}
         break;
      }
   }
   // -----------
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::CreateEditControls(HDC hDC , SIZE & border , HFONT hFont)
{
   DWORD n;
   DWORD nn = m_Edits.Count();
   AdjustEditControls(hDC,border);
   for( n=0; n < nn ; n++ )
   {
      edit_spec_t* ps = (edit_spec_t*) m_Edits.Get(n);
      if( ps )
      {
         if( ps->m_pLabel )
         {
            ps->m_hLabel = CreateWindowEx(0,"STATIC",ps->m_pLabel,
                           WS_VISIBLE|WS_CHILD,// | ( m_layout_mode ? SS_RIGHT : 0 ),
                           ps->m_rcLabel.left,ps->m_rcLabel.top,
                           ps->m_rcLabel.right,ps->m_rcLabel.bottom,
                           m_hPage,(HMENU) (0x300|(n << 1)),m_pDlgEdit->m_hApp,0);
            SendMessage(ps->m_hLabel, WM_SETFONT , (WPARAM) hFont , 1 );
         }

         if( ps->m_dwXbType & XPP_LOGICAL )
         {
            ps->m_hValue = CreateWindowEx(0,"BUTTON",ps->m_pValue,
                           WS_TABSTOP| WS_VISIBLE|WS_CHILD| BS_CHECKBOX,
                           ps->m_rcValue.left,ps->m_rcValue.top,
                           300,ps->m_rcValue.bottom,
                           m_hPage,(HMENU) (0x300 | n) + 1,m_pDlgEdit->m_hApp,0);
            SendMessage(ps->m_hValue,BM_SETCHECK,(ps->m_nlValue ? 1 : 0),0);
            SendMessage(ps->m_hValue , WM_SETFONT , (WPARAM) hFont , 1 );
         }
         else
         {
            if( ps->m_pList )
            {
               ps->m_hValue = CreateWindowEx(WS_EX_CLIENTEDGE ,"COMBOBOX","",
                              WS_VISIBLE|WS_CHILD| CBS_DROPDOWN | WS_TABSTOP | CBS_AUTOHSCROLL,
                              ps->m_rcValue.left,ps->m_rcValue.top,
                              300,ps->m_rcValue.bottom + 500,
                              m_hPage,(HMENU) (0x300 | n) + 1,m_pDlgEdit->m_hApp,0);
               DWORD i;
               DWORD ii = ps->m_pList->Count();
               for( i = 0; i < ii ; i++){ SendMessage(ps->m_hValue,CB_ADDSTRING,0,(LPARAM)ps->m_pList->Get(i));}
               SendMessage(ps->m_hValue , WM_SETFONT , (WPARAM) hFont , 1 );
               if( ps->m_pValue )
               {
                  SetWindowText(ps->m_hValue,ps->m_pValue);
                  SendMessage( ps->m_hValue , WM_KILLFOCUS,0,0);
               }


            }
            else
            {
               ps->m_hValue = CreateWindowEx(WS_EX_CLIENTEDGE ,"EDIT",( ps->m_pValue ? ps->m_pValue : ""),
                              WS_VISIBLE|WS_CHILD|
                              ((ps->m_nFlags & ES_READONLY) ? 0 : WS_TABSTOP ) |
                              ES_AUTOHSCROLL| ps->m_nFlags,
                              ps->m_rcValue.left,ps->m_rcValue.top,
                              300,ps->m_rcValue.bottom,
                              m_hPage,(HMENU) (0x300 | n) + 1,m_pDlgEdit->m_hApp,0);
               if(!(ps->m_nFlags & ES_PASSWORD))
               {
                  SendMessage(ps->m_hValue , WM_SETFONT , (WPARAM) hFont , 1 );
               }
            }
         }
      }
      if( m_pDlgEdit->m_hWndNotify )
      {
         if( ps->m_hLabel )
         {
            PostMessage( m_pDlgEdit->m_hWndNotify,
                         g_nMsgDirtyNotify,
                        (WPARAM) MAKELONG(OT4XB_DDN_CREATE_SAY,ps->m_nGPos),
                        (LPARAM) ps->m_hLabel );
         }
         if( ps->m_hValue )         
         {
            PostMessage( m_pDlgEdit->m_hWndNotify,
                         g_nMsgDirtyNotify,
                        (WPARAM) MAKELONG(OT4XB_DDN_CREATE_CTRL,ps->m_nGPos),
                        (LPARAM) ps->m_hValue);
         }         
      }            
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::AdjustEditControls(HDC hDC , SIZE & border)
{
   DWORD n;
   DWORD nn = m_Edits.Count();
   SIZE  label_max; ZeroMemory( &label_max , sizeof(SIZE));
   SIZE  value_max; ZeroMemory( &value_max , sizeof(SIZE));
   m_cy_total = 0;
   for( n=0; n < nn ; n++ )
   {
      edit_spec_t* ps = (edit_spec_t*) m_Edits.Get(n);
      if( ps )
      {
         ps->CalcMinSizes(hDC);
         if( ps->m_rcLabel.bottom > label_max.cy ){ label_max.cy = ps->m_rcLabel.bottom; }
         if( ps->m_rcLabel.right  > label_max.cx ){ label_max.cx = ps->m_rcLabel.right;  }
         if( ps->m_rcValue.bottom > value_max.cy ){ value_max.cy = ps->m_rcValue.bottom; }
         if( ps->m_rcValue.right  > value_max.cx ){ value_max.cx = ps->m_rcValue.right;  }
      }
   }
   m_layout_mode = 1;
   if( label_max.cx > 250 ) m_layout_mode = 0;
   if( m_layout_mode )
   {
      m_cx_min = label_max.cx + 300;
      for( n=0; n < nn ; n++ )
      {
         edit_spec_t* ps = (edit_spec_t*) m_Edits.Get(n);
         if( ps )
         {
            m_cy_total += 4;
            ps->m_rcValue.top  = m_cy_total;
            ps->m_rcValue.bottom +=  2 + ( border.cy * 2 );
            m_cy_total += ps->m_rcValue.bottom;
            ps->m_rcValue.left = 8 + label_max.cx;
            ps->m_rcLabel.top    = ps->m_rcValue.top + ((ps->m_rcValue.bottom - ps->m_rcLabel.bottom) - 5);
            ps->m_rcLabel.left = 1;
            ps->m_rcLabel.right = ps->m_rcLabel.left + label_max.cx;
         }
      }
   }
   else
   {
      m_cx_min = 300;
      for( n=0; n < nn ; n++ )
      {
         edit_spec_t* ps = (edit_spec_t*) m_Edits.Get(n);
         if( ps )
         {
            m_cy_total += 4;
            if( ps->m_pLabel )
            {
               ps->m_rcLabel.left = 4;
               ps->m_rcLabel.top  = m_cy_total;
               m_cy_total += ps->m_rcLabel.bottom + 4;
            }
            ps->m_rcValue.left = 4;
            ps->m_rcValue.top  = m_cy_total;
            ps->m_rcValue.bottom +=  2 + ( border.cy * 2 );
            m_cy_total += ps->m_rcValue.bottom;
         }
      }
   }
   m_label_max = label_max.cx;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::show(void)
{

   RECT rc;
   HWND hPageCon = m_pDlgEdit->m_hPageCon;
   SCROLLINFO si; ZeroMemory( &si , sizeof(si)); si.cbSize = sizeof(si);
   GetClientRect(hPageCon,&rc);
   if( rc.bottom < m_cy_total )
   {
      m_y_max_scroll = m_cy_total - rc.bottom;
      si.nMin = 0;
      si.nMax = m_y_max_scroll;
      si.nPage = (UINT) (si.nMax / m_Edits.Count());
      si.nPos  = m_y_scroll_pos;
      si.fMask = SIF_ALL;
      SetScrollInfo(hPageCon,SB_VERT,&si,1);
   }
   else
   {
      m_y_max_scroll = 0;
      si.nMin = 0;
      si.nMax = 0;
      si.nPage = 0;
      si.nPos  =  m_y_scroll_pos = 0;
      si.fMask = SIF_ALL;
      SetScrollInfo(hPageCon,SB_VERT,&si,1);
   }

   GetClientRect(hPageCon,&rc);
   DWORD nn  = m_Edits.Count();
   if( rc.bottom < m_cy_total ){ rc.bottom = m_cy_total; }
   SetWindowPos( m_hPage,0,0,(0 - m_y_scroll_pos),rc.right,rc.bottom,SWP_SHOWWINDOW|SWP_NOZORDER);
   DWORD n;
   DWORD flags = SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOOWNERZORDER ;
   HDWP  hwp = ::BeginDeferWindowPos( nn );
   for( n=0;n < nn ; n++ )
   {
      edit_spec_t* ps = (edit_spec_t*) m_Edits.Get(n);
      ::DeferWindowPos(hwp,ps->m_hValue,0,0,0,rc.right - ( 4 + ps->m_rcValue.left) , ps->m_rcValue.bottom, flags);
   }
   ::EndDeferWindowPos( hwp);

}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::hide(void)
{
   SetWindowPos( m_hPage,0,0,0,0,0,SWP_HIDEWINDOW|SWP_NOZORDER|SWP_NOREPOSITION|SWP_NOMOVE);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_dirty_dlgedit::page_spec_t::PreTranslateMessage( MSG* pmsg)
{
   if( (m_pDlgEdit->m_dwFlags & OT4XB_DDF_BTNTABSTOP) && (pmsg->message == WM_KEYDOWN) && ((pmsg->wParam == VK_RETURN) || (pmsg->wParam == VK_TAB )) )
   {
      if( GetProp(GetFocus(),"IsButton") == (HANDLE) 1 ){ return FALSE; }   
      int nMove = 1;
      if(pmsg->wParam == VK_RETURN)
      {
         if( (GetKeyState(VK_CONTROL)|GetKeyState(VK_MENU)|GetKeyState(VK_SHIFT)) & 0x8000 ){ nMove = 0; }
      } 
      else
      {
         if( GetKeyState(VK_SHIFT) & 0x8000 ){ nMove = -1; }
         if( (GetKeyState(VK_CONTROL)|GetKeyState(VK_MENU)) & 0x8000 ){ nMove = 0; }
      }
      if( nMove )
      {
         if( m_pos_focused == (LONG) ((nMove == 1) ? m_last_editable : 0 ) )
         {
            edit_spec_t* p = (edit_spec_t*) m_Edits.Get(m_pos_focused);
            HWND hEdit = 0;
            if( p )
            {
               hEdit = p->m_hValue;
               if( p->m_pList ) // is a combobox
               {
                  COMBOBOXINFO cbi; ZeroMemory(&cbi,sizeof(cbi)); cbi.cbSize = sizeof(cbi);
                  if( !GetComboBoxInfo(hEdit,&cbi) ){ hEdit = 0; }
                  else
                  {
                     hEdit = cbi.hwndItem;
                     if( IsWindowVisible(cbi.hwndList) ){ hEdit = 0;}
                  } 
               }
            }
            if( hEdit && ( hEdit == GetFocus() ))
            {
               HWND hCtrl =GetNextDlgTabItem(m_pDlgEdit->m_hWnd,m_pDlgEdit->m_hTab,(BOOL) (nMove < 0));
               if( hCtrl )
               {
                  SetFocus( hCtrl);
                  SendMessage(hCtrl,EM_SETSEL,0,-1);
               }
               return TRUE;               
            }
         }
      }
   }

   if( (pmsg->message == WM_KEYDOWN) && (pmsg->wParam == VK_RETURN) )
   {
      if( GetProp(GetFocus(),"IsButton") == (HANDLE) 1 ){ return FALSE; }      
      if( (GetKeyState(VK_CONTROL)|GetKeyState(VK_MENU)|GetKeyState(VK_SHIFT)) & 0x8000 ) return FALSE;
      HWND hCtrl = 0;
      edit_spec_t* p = (edit_spec_t*) m_Edits.Get(m_pos_focused);
      if( p && p->m_hValue )
      {
         hCtrl = p->m_hValue;
         if( p->m_pList ) // is a combobox
         {
            COMBOBOXINFO cbi; ZeroMemory(&cbi,sizeof(cbi)); cbi.cbSize = sizeof(cbi);
            if( GetComboBoxInfo(hCtrl,&cbi) )
            {
               if( IsWindowVisible(cbi.hwndList) ){ return IsDialogMessage(m_hPage,pmsg); }
            } 
         }         
      }
      hCtrl = GetNextDlgTabItem(m_hPage,hCtrl,0);
      if( hCtrl )
      {
         SetFocus( hCtrl);
         SendMessage(hCtrl,EM_SETSEL,0,-1);
      }
      return TRUE;
   }
   if( IsDialogMessage(m_hPage,pmsg) ) return TRUE;
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_dirty_dlgedit::page_spec_t::IsHotKey( UINT vk )
{
   if( !m_pCaption ){ return FALSE;}
   if( m_i_accelerator_pos < 0 ){ return FALSE;}
   char ch = (char) ( 0xFF & MapVirtualKey(vk,MAPVK_VK_TO_CHAR));
   if( ch == m_pCaption[m_i_accelerator_pos] ){ return TRUE; }
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::page_spec_t::HandleVScroll(HWND hWnd , WORD wScroll , WORD wAction )
{
   SCROLLINFO si;
   if( ! m_y_max_scroll ) return 0;


   switch( wAction)
   {
      case SB_TOP:           { m_y_scroll_pos = 0; break;  }
      case SB_BOTTOM :       { m_y_scroll_pos = m_y_max_scroll; break; }
      case SB_THUMBTRACK:
      case SB_THUMBPOSITION: { m_y_scroll_pos = (LONG) ((__int16) wScroll ); break; }
      case SB_LINEDOWN:
      case SB_PAGEDOWN:      { m_y_scroll_pos += 40; break;  }
      case SB_LINEUP:
      case SB_PAGEUP:        { m_y_scroll_pos -= 40; break;  }
      default: { return 0; }
   }
   if( m_y_scroll_pos < 0 ){ m_y_scroll_pos = 0; }
   if( m_y_scroll_pos > m_y_max_scroll ){ m_y_scroll_pos = m_y_max_scroll; }
   ZeroMemory( &si , sizeof(si));
   si.cbSize = sizeof(si);
   si.fMask  = SIF_POS;
   si.nPos   = m_y_scroll_pos;
   SetScrollInfo(hWnd,SB_VERT,&si,TRUE);
   SetWindowPos( m_hPage,0,0,(0 - m_y_scroll_pos),0,0,SWP_NOZORDER|SWP_NOSIZE);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::page_spec_t::HandleWheel( LONG nDelta)
{
   SCROLLINFO si;
   if( ! m_y_max_scroll ) return 0;
   m_y_scroll_pos -= (LONG) (nDelta/2);
   if( m_y_scroll_pos < 0 ){ m_y_scroll_pos = 0; }
   if( m_y_scroll_pos > m_y_max_scroll ){ m_y_scroll_pos = m_y_max_scroll; }
   ZeroMemory( &si , sizeof(si));
   si.cbSize = sizeof(si);
   si.fMask  = SIF_POS;
   si.nPos   = m_y_scroll_pos;
   SetScrollInfo(m_pDlgEdit->m_hPageCon,SB_VERT,&si,TRUE);
   SetWindowPos( m_hPage,0,0,(0 - m_y_scroll_pos),0,0,SWP_NOZORDER|SWP_NOSIZE);
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LONG ot4xb_dirty_dlgedit::page_spec_t::find_edit( HWND hWnd )
{
   DWORD n;
   DWORD nn = m_Edits.Count();
   for( n=0; n < nn; n++)
   {
      edit_spec_t* p = (edit_spec_t*) m_Edits.Get( n);
      if( p && (p->m_hValue == hWnd ) )
      {
         return (LONG) n;
      }
   }
   return -1;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::on_edit_focus( LPARAM lp )
{
   m_pos_focused = find_edit( (HWND) lp );
   edit_spec_t* p = (edit_spec_t*) m_Edits.Get(m_pos_focused);
   if( p && m_y_max_scroll )
   {
      HWND hPageCon = m_pDlgEdit->m_hPageCon;
      RECT rc,rcpc;
      LONG nToScroll = 0;
      if(m_pos_focused == (LONG) m_Edits.Count())
      {
         nToScroll = m_y_max_scroll;
      }
      else if( m_pos_focused )
      {
         GetClientRect( hPageCon , &rcpc );
         ZeroMemory(&rc,sizeof(RECT));
         rc.top      = ( m_layout_mode ? p->m_rcValue.top : p->m_rcLabel.top);
         rc.bottom   = (p->m_rcValue.top + p->m_rcValue.bottom) - rc.top;
         ClientToScreen(m_hPage,(POINT*) &rc);
         ScreenToClient(hPageCon,(POINT*) &rc);
         rc.bottom += rc.top;
         if( rc.top < 0 ){ nToScroll = ( m_layout_mode ? p->m_rcValue.top : p->m_rcLabel.top);}
         else if(rc.bottom > rcpc.bottom )
         {
            nToScroll = ( m_layout_mode ? p->m_rcValue.top : p->m_rcLabel.top) - (rcpc.bottom>>2);
         }
         else { nToScroll = m_y_scroll_pos; }
      }
      if( nToScroll > m_y_max_scroll ) { nToScroll = m_y_max_scroll; }
      if( nToScroll != m_y_scroll_pos ){ HandleVScroll(hPageCon, (WORD) nToScroll, SB_THUMBTRACK);}
   }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::page_spec_t::on_activate(void)
{
   DWORD nn = m_Edits.Count();
   if( !nn ) return;
   DWORD nStart = (DWORD) m_pos_focused;
   if( nStart > nn ) nStart = 0;
   DWORD n;
   for( n = nStart; n < nn ; n++ )
   {
      edit_spec_t* p = (edit_spec_t*) m_Edits.Get( n);
      if(p && !(p->m_nFlags & ES_READONLY) ){ SetFocus( p->m_hValue ); return;}
   }
   if( nStart == 0 ) return;
   for( n = 0; n < nStart ; n++ )
   {
      edit_spec_t* p = (edit_spec_t*) m_Edits.Get( n);
      if(p && !(p->m_nFlags & ES_READONLY) ){ SetFocus( p->m_hValue ); return;}
   }
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::SetTitle( LPSTR pTitle )
{
   _xssr_(&m_pTitle,( pTitle ? pTitle : ""));
   if( m_hWnd ){ SendMessageA( m_hWnd,WM_SETTEXT,0,(LPARAM) m_pTitle); }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::_register_(void){ ot4xb_dirty_dlgedit_ns::RegisterWndClass(); }
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::SetParent( HWND hParent )
{
   m_hWndParent = hParent;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::SetBoundingRect( int x , int y , int cx , int cy )
{
   m_rc.left   = x;
   m_rc.top    = y;
   m_rc.right  = cx;
   m_rc.bottom = cy;
   if( m_hWnd ){ SetWindowPos(m_hWnd,0,x,y,cx,cy, SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOZORDER ); }
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::ApplyFlagsToBoundingRect(void)
{
   BOOL adj_cx = (BOOL) (m_rc.right  == -1);
   BOOL adj_cy = (BOOL) (m_rc.bottom == -1);
   if( m_rc.right  < 200 ){ m_rc.right  = 200;}
   if( m_rc.bottom < 200 ){ m_rc.bottom = 200;}
   if( !m_hWndParent ){ m_dwFlags = m_dwFlags & (~OT4XB_DDF_COORD_MASK); }
   if( m_dwFlags & OT4XB_DDF_COORD_WINDOW )
   {
      RECT rc;
      ZeroMemory(&rc,sizeof(RECT));
      if( m_dwFlags &  (OT4XB_DDF_COORD_CLIENT | OT4XB_DDF_CHILD))
      {
         GetClientRect(m_hWndParent,&rc);
         if( ! (m_dwFlags &  OT4XB_DDF_CHILD) )
         {
            ClientToScreen(m_hWndParent,(POINT*) &rc);
         }
      }
      else
      {
         GetWindowRect(m_hWndParent,&rc);
         rc.right  -= rc.left;
         rc.bottom -= rc.top;
      }
      if( adj_cx ){ m_rc.left = rc.left; m_rc.right = rc.right; }
      if( adj_cy ){ m_rc.top  = rc.top; m_rc.bottom = rc.bottom; }
      switch( m_dwFlags & OT4XB_DDF_DISPLAY_MASK )
      {
         case OT4XB_DDF_DISPLAY_CENTERED:
         {
            if( !adj_cx) { m_rc.left = rc.left + ( (rc.right  - m_rc.right ) >> 1);}
            if( !adj_cy) { m_rc.top  = rc.top  + ( (rc.bottom - m_rc.bottom) >> 1);}
            break;
         }
         case OT4XB_DDF_DISPLAY_MAXIMIZED:
         {
            CopyRect(&m_rc,&rc);
            break;
         }
         default:
         {
            if( !adj_cx) { m_rc.left += rc.left; }
            if( !adj_cy) {m_rc.top  += rc.top; }
            break;
         }
      }
   }
   else
   {
      HMONITOR hMonitor = 0;
      switch( m_dwFlags & OT4XB_DDF_MONITOR_MASK)
      {
         case 0:
         {
            RECT rc;
            CopyRect(&rc,&m_rc);
            rc.right  += rc.left;
            rc.bottom += rc.top;
            hMonitor = MonitorFromRect(&m_rc,MONITOR_DEFAULTTONEAREST);
            break;
         }
         case OT4XB_DDF_MONITOR_PRIMARY :
         {
            hMonitor = MonitorFromWindow(0,MONITOR_DEFAULTTOPRIMARY);
            break;
         }
         case OT4XB_DDF_MONITOR_WINDOW  :
         {
            hMonitor = MonitorFromWindow(m_hWndParent,MONITOR_DEFAULTTOPRIMARY);
            break;
         }
         case OT4XB_DDF_MONITOR_MOUSE   :
         {
            POINT pt;
            GetCursorPos(&pt);
            hMonitor = MonitorFromPoint(pt,MONITOR_DEFAULTTONEAREST);
            break;
         }
      }
      if( hMonitor )
      {
         MONITORINFO mi;
         int mcx,mcy,mx,my;
         ZeroMemory( &mi, sizeof(MONITORINFO));
         mi.cbSize = sizeof(MONITORINFO);
         if( !GetMonitorInfo(hMonitor,&mi)){ return;}
         mx  = mi.rcWork.left;
         my  = mi.rcWork.top;
         mcx = (mi.rcWork.right  - mx);
         mcy = (mi.rcWork.bottom - my);
         if( m_rc.right  > mcx ){ m_rc.right  = mcx;}
         if( m_rc.bottom > mcy ){ m_rc.bottom = mcy;}
         switch( m_dwFlags & OT4XB_DDF_DISPLAY_MASK )
         {
            case OT4XB_DDF_DISPLAY_CENTERED:
            {
               m_rc.left = mx + ((mcx - m_rc.right ) >> 1);
               m_rc.top  = my + ((mcy - m_rc.bottom) >> 1);
               break;
            }
            case OT4XB_DDF_DISPLAY_MAXIMIZED:
            {

               m_rc.left = mx; m_rc.right  = mcx;
               m_rc.top  = my; m_rc.bottom = mcy;
               break;
            }
            default:
            {
               int xx,yy;
               if( m_rc.left < mx){ m_rc.left = mx;}
               if( m_rc.top  < my){ m_rc.top  = my;}
               xx = m_rc.left + m_rc.right;
               yy = m_rc.top  + m_rc.bottom;
               if( xx > mi.rcWork.right ){ m_rc.left = m_rc.right  - mcx;}
               if( yy > mi.rcWork.bottom){ m_rc.top  = m_rc.bottom - mcy;}
               break;
            }
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------

BOOL ot4xb_dirty_dlgedit::create(void)
{
   HINSTANCE hApp = (HINSTANCE) GetModuleHandle(0);
   DWORD dw;
   HWND  hParent = 0;
   if( m_hWnd ){ return FALSE; }
   m_dwStyle     =  WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
   m_dwExStyle   = 0;

   if( (m_hWndParent == 0) || ((m_dwFlags & OT4XB_DDF_CHILD) == 0) )
   {
      m_dwFlags &= (~OT4XB_DDF_TITLE);
   }

   if(m_dwFlags & OT4XB_DDF_TOP)
   {
      m_dwFlags &= (~OT4XB_DDF_CHILD);
      m_dwStyle |=  WS_OVERLAPPEDWINDOW;
      m_dwExStyle |= WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
   }

   if( m_hWndParent && (m_dwFlags & OT4XB_DDF_CHILD) )
   {
      m_dwFlags &= (~(OT4XB_DDF_MONITOR_PRIMARY |OT4XB_DDF_MONITOR_WINDOW|OT4XB_DDF_MONITOR_WINDOW));
      m_dwFlags &= (~(OT4XB_DDF_NOTASKBAR |OT4XB_DDF_DISABLEPARENT));
      m_dwFlags |= OT4XB_DDF_COORD_CLIENT;
      m_dwStyle |=  WS_CHILD | WS_DLGFRAME ;

   }
   else
   {
      m_dwFlags &= (~OT4XB_DDF_CHILD);
      m_dwStyle |=  WS_OVERLAPPEDWINDOW;
   }


   ApplyFlagsToBoundingRect();
   if( (m_dwFlags & OT4XB_DDF_TOP) == 0 )
   {
      if( (m_dwFlags & ( OT4XB_DDF_NOTASKBAR | OT4XB_DDF_CHILD)) )
      {
         m_hWndTopInvisible = CreateWindowExA(0,DIRTY_DLGEDIT_CLSNAME,0,0,0,0,0,0,0,0,hApp,0);
      }
   }
   hParent = m_hWndTopInvisible;

   // create the dialog window
   m_hWnd = CreateWindowExA( m_dwExStyle,DIRTY_DLGEDIT_CLSNAME,m_pTitle,m_dwStyle,
                             m_rc.left,m_rc.top,m_rc.right,m_rc.bottom,
                             hParent,0,hApp, 0);

   if( !m_hWnd ){ return FALSE; }
   if( m_hWndTopInvisible )
   {
      if( m_dwFlags & OT4XB_DDF_CHILD)
      {
         ::SetParent(m_hWnd , m_hWndParent);
      }
      else
      {
         ::SetParent(m_hWnd , 0);
      }
   }
   _TSTDCTXCBK_SUBCLASS_( m_hWnd, ot4xb_dirty_dlgedit_ns::proxi_dlgproc , this );
   if( (m_dwFlags & (OT4XB_DDF_TITLE | OT4XB_DDF_DISABLEPARENT | OT4XB_DDF_HOOKPARENT)) && m_hWndParent )
   {
      _TSTDCTXCBK_SUBCLASS_( m_hWndParent, ot4xb_dirty_dlgedit_ns::proxi_parentproc, this );   
   
   }
   

   // create the tab control
   m_hTab = CreateWindowEx(WS_EX_CONTROLPARENT,WC_TABCONTROL,"",
                           WS_CHILD |WS_CLIPCHILDREN | WS_VISIBLE | WS_TABSTOP |
                           TCS_FIXEDWIDTH|TCS_FLATBUTTONS | TCS_TOOLTIPS ,
                           0,0,100,100,m_hWnd,(HMENU) 500,hApp,0);
   _TSTDCTXCBK_SUBCLASS_( m_hTab, ot4xb_dirty_dlgedit_ns::proxi_tabproc , this );
   if( !m_hTab ) return FALSE;
   SendMessage(m_hTab , WM_SETFONT , (WPARAM) GetStockObject(ANSI_VAR_FONT) , 1 );
   // create the Page Container window
   dw = WS_EX_CONTROLPARENT;
   if(m_dwFlags & OT4XB_DDF_CLIENT_EDGE ){ dw |= WS_EX_CLIENTEDGE; }
   m_hPageCon = CreateWindowEx(dw,DIRTY_PGPANEL_CLSNAME,0,
                           WS_CHILD |WS_CLIPCHILDREN | WS_VISIBLE | WS_TABSTOP,
                           0,0,0,0,m_hTab,(HMENU) 500,hApp,0);
   _TSTDCTXCBK_SUBCLASS_( m_hPageCon, ot4xb_dirty_dlgedit_ns::proxi_pageconproc , this );

  if( m_hWndNotify )
   {
      PostMessage( m_hWndNotify,
                   g_nMsgDirtyNotify,
                   (WPARAM) MAKELONG(OT4XB_DDN_CREATE_DLG,0),
                   (LPARAM) m_hWnd );
      PostMessage( m_hWndNotify,
                   g_nMsgDirtyNotify,
                   (WPARAM) MAKELONG(OT4XB_DDN_CREATE_TAB,0),
                   (LPARAM) m_hTab );                   
      PostMessage( m_hWndNotify,
                   g_nMsgDirtyNotify,
                   (WPARAM) MAKELONG(OT4XB_DDN_CREATE_PGCON,0),
                   (LPARAM) m_hPageCon );                   
   } 
   // create the buttons
   DWORD nn = m_Btns.Count();
   DWORD n;
   for( n = 0; n < nn ; n++ )
   {
      button_spec_t* p = (button_spec_t*) m_Btns.Get(n);
      p->m_hBtn = CreateWindowEx(0,"BUTTON",p->GetCaption(),
                           WS_CHILD |WS_CLIPCHILDREN | WS_VISIBLE | WS_TABSTOP |
                           ( n ? BS_PUSHBUTTON : BS_DEFPUSHBUTTON ),
                           0,0,100,30,m_hWnd,(HMENU) n,hApp,0);
      SendMessage(p->m_hBtn , WM_SETFONT , (WPARAM) GetStockObject(ANSI_VAR_FONT) , 1 );
      SetProp( p->m_hBtn ,"IsButton",(HANDLE) 1 );
      if( m_hWndNotify )
      {
         PostMessage( m_hWndNotify,
                      g_nMsgDirtyNotify,
                      (WPARAM) MAKELONG(OT4XB_DDN_CREATE_BTN,p->m_nGPos),
                      (LPARAM) p->m_hBtn );                         
      }
      
   }
   //----------------
   nn = m_Pages.Count();
   for( n = 0; n < nn ; n++ )
   {
      page_spec_t* p = (page_spec_t*) m_Pages.Get(n);
      if(p){ p->create();}
   }
   //----------------
   CreateEditControls();

   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::AddTab( LPSTR pCaption , BOOL bCopy )
{
   new page_spec_t(pCaption,bCopy,this);
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::AddBtn( DWORD nGPos , LPSTR pCaption, BOOL bCopy)
{
   m_Btns.Add( (void*) new button_spec_t(nGPos,pCaption,bCopy) );
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::adjust_rects(void)
{
   RECT rc;
   DWORD nBtns = m_Btns.Count();
   LONG ty = ( (m_dwFlags & OT4XB_DDF_TITLE) ? GetSystemMetrics(SM_CYCAPTION) : 0 );   
   if(!nBtns){ m_button_cy = 0;}
   GetClientRect( m_hWnd , &rc );
   SetWindowPos(m_hTab,0,rc.left,rc.top + ty,rc.right,rc.bottom - (m_button_cy + ty) ,SWP_NOOWNERZORDER);
   PostMessage(m_hTab,WM_SIZE,(WPARAM) -1,0);
   // adj the buttons
   if( nBtns )
   {
      DWORD n;
      LONG cx = (LONG) (rc.right / ((LONG) nBtns) );
      LONG nx = rc.right - (cx * ((LONG) nBtns) );
      DWORD flags = SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_SHOWWINDOW ;
      LONG x = 0;
      LONG y = rc.bottom - m_button_cy;
      for( n = 0; n < nBtns ; n++ )
      {
         button_spec_t* p = (button_spec_t*) m_Btns.Get(n);
         SetWindowPos(p->m_hBtn,0,x,y,cx + ( nx ? 1 : 0 ),m_button_cy, flags);
         x += cx + ( nx ? 1 : 0 );
         if( nx ){ nx--; }
      }
   }

}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::CollectEditBuffers(void)
{
   DWORD npc = m_Pages.Count();
   DWORD np;
   for( np=0; np < npc; np++ )
   {
      page_spec_t* pg = GetPage((int) np);
      if( pg )
      {
         DWORD nec = pg->m_Edits.Count();
         DWORD ne;
         for( ne = 0; ne < nec; ne++ )
         {
            edit_spec_t* e = (edit_spec_t*) pg->m_Edits.Get(ne);
            if( e ){ e->CollectEditBuffer();}
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::parent_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)
{
   if( nMsg == g_nMsgProxiRemoveSubclass )
   {
      return 0;
   }
   if( (nMsg == WM_NCACTIVATE) || (nMsg == WM_ACTIVATE) ||  (nMsg == WM_ACTIVATEAPP)){PostMessage( m_hWnd,WM_APP + 1 ,wp,0);}   
   return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::dlg_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)
{
   if( nMsg == g_nMsgDirtyNotify )
   {
      if( wp == 0 )
      {
         if( lp )
         {
            ShowWindow( hWnd , SW_SHOW);
            SetForegroundWindow(hWnd);         
            BringWindowToTop(hWnd);
            SetActiveWindow(hWnd);
         }
         else
         {
            ShowWindow( hWnd , SW_HIDE);         
         }
      }
      return 0;
   }
   switch( nMsg)
   {
      case WM_APP + 1:      
      {
         InvalidateRect(m_hWnd,0,TRUE);
         if( wp )
         {
            SetForegroundWindow(hWnd);         
            BringWindowToTop(hWnd);
            SetActiveWindow(hWnd);
         }
         return 0;
      }
      case WM_ERASEBKGND:            
      {
         LRESULT result = CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);
         if( m_dwFlags & OT4XB_DDF_TITLE )
         {
            RECT rc;
            GetClientRect( hWnd , &rc );
            rc.bottom = GetSystemMetrics(SM_CYCAPTION);
           DrawCaption(hWnd,(HDC)wp,&rc, ( ((GetForegroundWindow() == m_hWndParent) ? DC_ACTIVE : 0 ) | DC_TEXT | DC_GRADIENT ));
         }
         return result;
      }
      case WM_NCHITTEST:
      {
         LRESULT result = CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);
         if( (m_dwFlags & OT4XB_DDF_DUMMYHIT) && (result == HTCAPTION)  )
         {
            return HTCLIENT;
         }
         return result;

      }
      case WM_MOUSEWHEEL:
      {
         page_spec_t* p = GetPage();
         if( p ) return p->HandleWheel( (LONG) ((short) HIWORD(wp)));
         break;
      }
      case WM_ENTERSIZEMOVE:
      {
         m_bInSizeLoop = TRUE;
         break;
      }
      case WM_EXITSIZEMOVE:
      {
         m_bInSizeLoop = FALSE;
         adjust_rects();
         break;
      }
      case WM_SIZE:
      {
         if( (wp != SIZE_MINIMIZED) && (!m_bInSizeLoop) ){ adjust_rects(); }
         return 0;
      }
      case WM_SYSCOMMAND:
      {
         if( wp == SC_CLOSE )
         {
            if( (int) GetProp(hWnd,"NoClose") == 1 )
            {
               ShowWindow(hWnd,SW_HIDE);
               return 0;
            }
         
         }
         return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);         
      }
      case WM_CLOSE:
      {
         if( (int) GetProp(hWnd,"NoClose") == 1 ){ return 0; }
         GetWindowRect(m_hWnd,&m_rc);
         m_rc.right  -= m_rc.left;
         m_rc.bottom -= m_rc.top;
         CollectEditBuffers();
         DestroyWindow(hWnd);
         return 0;
      }
      case WM_DESTROY:
      {
         if( m_hWndParent && IsWindow(m_hWndParent) )
         {
            SendMessage(m_hWndParent , g_nMsgProxiRemoveSubclass ,0,0);
         }         
         break;
      }
      case WM_NCDESTROY:
      {
         CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);
         if( m_hWndTopInvisible){  DestroyWindow(m_hWndTopInvisible); }
         m_bLoop = FALSE;
         return 0;
      }
      case WM_NOTIFY:
      {
         HWND hCtrl = reinterpret_cast<NMHDR*>(lp)->hwndFrom;
         if( hCtrl == m_hTab )
         {
            UINT nCode = reinterpret_cast<NMHDR*>(lp)->code;
            if( nCode == TCN_SELCHANGE )
            {
               return OnTabChange();
            }
         }
         break;
      }
      case WM_ACTIVATE:
      {
         page_spec_t* page = GetPage();
         if( page )
         {
            page->on_activate();
            return 0;
         }
      }
      case WM_COMMAND:
      {
         if( lp )
         {
            switch( HIWORD(wp) )
            {
               case BN_CLICKED:
               {
                  m_dlg_result = GetWindowLong((HWND) lp,GWL_ID);// - 0x600;
                  if( GetProp(m_hWnd,"NoClose") )
                  {
                     if( m_hWndNotify )
                     {
                        PostMessage( m_hWndNotify,
                        g_nMsgDirtyNotify,
                        (WPARAM) MAKELONG(OT4XB_DDN_BTNCLICK,m_dlg_result ),
                        (LPARAM) m_hWnd );
                     }
                  }
                  PostMessage(m_hWnd,WM_CLOSE,0,0);
                  return 0;
               }
            }
         }
         break;
      }
   }
   return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);

}
// -----------------------------------------------------------------------------------------------------------------
ot4xb_dirty_dlgedit::page_spec_t* ot4xb_dirty_dlgedit::GetPage(  int iPage )
{
   if( iPage == -1 ) iPage = m_iPageSel;
   if( iPage < 0 ) return 0;
   if( iPage >= ((int) m_Pages.Count()) ) return 0;
   return ( page_spec_t*) m_Pages.Get((int) iPage );
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::ShowPage( int iPage )
{
   page_spec_t* p = (page_spec_t*) m_Pages.Get( (UINT) iPage );
   if( p ) p->show();
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::HidePage( int iPage )
{
   page_spec_t* p = (page_spec_t*) m_Pages.Get( (UINT) iPage );
   if( p ) p->hide();
}

// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::OnTabChange(void)
{
   if( !( m_hTab && m_hPageCon && m_Pages.Count() ) ){ return 0; }
   int iOld    = m_iPageSel;
   // int iCount  = (int) m_Pages.Count();
   m_iPageSel = TabCtrl_GetCurSel( m_hTab );
   ShowPage( m_iPageSel );
   if( iOld != m_iPageSel ){ HidePage( iOld ); }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::tab_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)
{
   switch( nMsg)
   {
      case WM_SIZE:
      {
         if( wp  == -1 )
         {
            RECT rc;
            GetClientRect(m_hTab,&rc);
            TabCtrl_AdjustRect(m_hTab,0,&rc);
            rc.right  -= rc.left; rc.bottom -= rc.top;
            SetWindowPos(m_hPageCon,0,rc.left,rc.top,rc.right,rc.bottom,SWP_NOOWNERZORDER);
            return 0;
         }
         break;
      }
   }
   return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);

}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::pagecon_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)
{
   switch( nMsg)
   {
      case WM_SIZE:
      {
         if( wp != SIZE_MINIMIZED )
         {
            OnTabChange();
            return 0;
         }
         break;
      }
      case WM_VSCROLL:
      {
         page_spec_t* p = GetPage();
         if( p ) return p->HandleVScroll(hWnd,HIWORD( wp) , LOWORD(wp));
         return 0;
      }
   }
   return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);

}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::page_proc( HWND hWnd , UINT nMsg,WPARAM wp , LPARAM lp , WNDPROC oldproc)
{
   switch( nMsg)
   {
      case WM_SIZE:
      {
         if( wp  == -1 )
         {
            return 0;
         }
         break;
      }

      case WM_ERASEBKGND:
      {
         BOOL bDefault = TRUE;
         HTHEME hTheme = 0;
         if( ot4xb_IsAppThemed() )
         {
            hTheme = vhti_OpenThemeData(hWnd,L"TAB");
            if( hTheme )
            {
               RECT rc;
               GetClientRect(hWnd,&rc);
               if( vhti_IsThemeBackgroundPartiallyTransparent(hTheme,TABP_BODY,0) )
               {
                  vhti_DrawThemeParentBackground(hWnd,(HDC)wp,&rc);
               }
               vhti_DrawThemeBackground(hTheme,(HDC)wp,TABP_BODY,0,&rc,0);
               bDefault = FALSE;
            }
         }
         if( bDefault ) CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);
         page_spec_t* ps = GetPage();
         DWORD nn = ( ps ? ps->m_Edits.Count() : 0 );
         if( ps && ps->m_layout_mode && nn )
         {
            DWORD n;
            for( n = 0; n < nn ; n++)
            {
               edit_spec_t* p = (edit_spec_t*) ps->m_Edits.Get(n);
               if( p )
               {
                  RECT rc;
                  rc.left = 0;
                  rc.right = rc.left + ps->m_label_max + 4;
                  rc.top  = p->m_rcValue.top;
                  rc.bottom = rc.top + p->m_rcValue.bottom;
                  if( hTheme )
                  {
                     vhti_DrawThemeEdge( hTheme,(HDC)wp,
                                    TABP_BODY,TIS_NORMAL,
                                    &rc , EDGE_ETCHED , BF_BOTTOM ,0);

                  }
                  else
                  {
                     DrawEdge((HDC)wp,&rc, EDGE_ETCHED , BF_BOTTOM );
                  }
               }
            }
         }
         if( hTheme ) vhti_CloseThemeData(hTheme);
         return 1;
      }
      case WM_CTLCOLORSTATIC:
      {
         if( GetWindowLong( (HWND) lp , GWL_EXSTYLE) & WS_EX_CLIENTEDGE)
         {
            SetBkColor((HDC) wp, GetSysColor( COLOR_INFOBK) );
            SetTextColor((HDC) wp, GetSysColor(COLOR_INFOTEXT));
            return (LRESULT) COLOR_INFOBK + 1;
         }
         if( ot4xb_IsAppThemed() )
         {
            HTHEME hTheme = vhti_OpenThemeData((HWND) lp  ,L"TAB");
            if( hTheme )
            {
               RECT rc;
               GetClientRect((HWND) lp ,&rc);
               vhti_DrawThemeParentBackground((HWND) lp,(HDC)wp,&rc);
               vhti_CloseThemeData(hTheme);
               SetBkMode( (HDC)wp , TRANSPARENT );
               return (LRESULT) GetStockObject(NULL_BRUSH);
            }
         }
         break;

      }
      case WM_COMMAND:
      {
         if( lp )
         {
            switch( HIWORD(wp) )
            {
               case CBN_SETFOCUS:
               case BN_SETFOCUS:
               case EN_SETFOCUS: { GetPage()->on_edit_focus(lp); return 0; }
               case BN_CLICKED:
               {
                  BOOL b = (BOOL) SendMessage( (HWND) lp,BM_GETCHECK,0,0);
                  SendMessage( (HWND) lp,BM_SETCHECK,(b ?0 : 1),0);
                  return 0;
               }
            }
         }
         break;
      }
      case WM_CHILDACTIVATE:
      {
         GetPage()->on_activate();
         return 0;
      }

   }
   return CallWindowProcA(oldproc,hWnd,nMsg,wp,lp);

}
// -----------------------------------------------------------------------------------------------------------------
BOOL ot4xb_dirty_dlgedit::PreTranslateMessage(MSG* pmsg )
{
   if( (pmsg->message == WM_CLOSE ) && (pmsg->hwnd == 0 ) )
   {
      RemoveProp(m_hWnd,"NoClose" );
      PostMessage(m_hWnd , WM_CLOSE , 0 , 0 );
   }
   BOOL bDlg    = FALSE;
   HWND hFocus  = GetFocus();
   if( !IsChild( m_hWnd , hFocus) ) return FALSE;
   if( pmsg->message == WM_SYSCHAR )
   {
      bDlg = TRUE;
      if( IsDialogMessage(m_hWnd,pmsg) ) return TRUE;
   }

   int  nPages  = (int) m_Pages.Count();
   BOOL bKbDn   = (pmsg->message == WM_KEYDOWN) || (pmsg->message == WM_SYSKEYDOWN);

   if( bKbDn && (pmsg->wParam != VK_CONTROL)  && m_hTab && (GetKeyState(VK_CONTROL) & 0x8000) )
   {
      int iPageSel = m_iPageSel;
      if( pmsg->wParam == VK_TAB )
      {
         BOOL bShift = (BOOL) (GetKeyState(VK_SHIFT) & 0x8000);
         iPageSel += ( bShift ? -1 : 1 );
         if( iPageSel >= nPages ){  iPageSel = 0;}
         if( iPageSel <0 ){  iPageSel = (nPages-1);}
      }
      else
      {
         int n;
         for( n = 0; (n < nPages) && ( iPageSel == m_iPageSel) ; n++ )
         {
            page_spec_t* pp = GetPage(n);
            if( pp &&  pp->IsHotKey((UINT) pmsg->wParam) ){ iPageSel = n;}
         }
      }
      if( !( iPageSel == m_iPageSel) )
      {
         TabCtrl_SetCurSel(m_hTab,iPageSel);
         OnTabChange();
         return TRUE;
      }
   }
   page_spec_t* pPage = GetPage(m_iPageSel);
   if( pPage )
   {
      if( pPage->PreTranslateMessage(pmsg) ) return TRUE;
   }
   if( (!bDlg) && IsDialogMessage(m_hWnd,pmsg) ) return TRUE;
   return FALSE;
}
// -----------------------------------------------------------------------------------------------------------------
LRESULT ot4xb_dirty_dlgedit::msgloop(void)
{
   BOOL bStartHidden = FALSE;
   HWND hWndDelegate = _ot4xb_get_hwnd_delegate_();
   HWND hDisable = 0;
   MSG msg;
   if( !IsWindow(m_hWnd) ) return -2;
   if( (int) GetProp(m_hWnd,"StartHidden") == 1 ){ bStartHidden = TRUE; }
   ShowWindow(m_hWnd, ( bStartHidden ? SW_HIDE : SW_NORMAL) );
   adjust_rects();
   m_bInSizeLoop = FALSE;
   m_bLoop = TRUE;
   if( (m_dwFlags & OT4XB_DDF_DISABLEPARENT) && m_hWndParent && hWndDelegate )
   {
      hDisable = GetAncestor( m_hWndParent , GA_ROOT );
      if( !IsWindowEnabled( hDisable) ){ hDisable = 0; }
      if( hDisable){ PostMessage( hWndDelegate,WM_COMMAND,MAKELONG(-1,2),(LPARAM) hDisable );}
   }
   if( !bStartHidden )
   {
      SetForegroundWindow(m_hWnd );
      BringWindowToTop(m_hWnd );
   }
   if( m_initial_tab_focus >= 0 )
   {
      int  nPages  = (int) m_Pages.Count();   
      if( m_initial_tab_focus < nPages )
      {
         TabCtrl_SetCurSel(m_hTab,m_initial_tab_focus);
         OnTabChange();      
      }
   }
   if( m_hWndNotify )
   {
      PostMessage( m_hWndNotify,g_nMsgDirtyNotify,0,0);
   }
   while( m_bLoop )
   {
      BOOL result = GetMessage(&msg,0,0,0);
      if( result == -1 ){ return -1; }
      if( result == 0  ){ return 0;  }
      if( !PreTranslateMessage(&msg) )
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }
   if( hDisable )
   {
      PostMessage( hWndDelegate,WM_COMMAND,MAKELONG(-1,1),(LPARAM) hDisable);
      PostMessage( hWndDelegate,WM_COMMAND,MAKELONG(-1,3),(LPARAM) m_hWndParent);
   }
   return 1;


}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::CreateEditControls(void)
{
   HDC hDC = GetDC(0); // get the screen hDC
   SIZE border;
   border.cx = GetSystemMetrics( SM_CXBORDER ) + 1;
   border.cy = GetSystemMetrics( SM_CYBORDER ) + 1;
   HFONT hAnsiFont = (HFONT) GetStockObject(ANSI_VAR_FONT);
   HFONT hOldFont = (HFONT) SelectObject(hDC,hAnsiFont);
   DWORD n;
   DWORD nn = m_Pages.Count();
   for( n=0; n < nn ; n++ )
   {
      page_spec_t* p = (page_spec_t*) m_Pages.Get(n);
      if( p )
      {
         p->CreateEditControls( hDC,border,hAnsiFont);
      }
   }
   (HFONT) SelectObject(hDC,hOldFont);
   ReleaseDC(0,hDC);
}
// -----------------------------------------------------------------------------------------------------------------
void ot4xb_dirty_dlgedit::run( TXppParamList & xpp)
{
   // param 1 hWndParent
   SetParent( xpp[1]->GetHWND() );
   // param 2 bounding rect

   RECT* prct = ( RECT*) xpp[2]->LockStrEx();
   if( xpp[2]->ExLen() < sizeof(RECT) ){ prct = 0;}
   if( prct ){ SetBoundingRect(prct->left,prct->top,prct->right,prct->bottom); }
   xpp[2]->UnLockStrEx();

   // param 3 flags
   if( xpp[3]->CheckType(XPP_NUMERIC) )
   {
      m_dwFlags = xpp[3]->GetDWord();
   }

   // param 4 cTitle
   if( xpp[4]->CheckType(XPP_CHARACTER) )
   {
      SetTitle( xpp[4]->LockStr() );
      xpp[4]->UnlockStr();
   }
   // -----
   // param 6 aBtn
   if( xpp[6]->CheckType( XPP_ARRAY ) )
   {
      DWORD nItems = xpp[6]->con_size();
      DWORD nn;
      for( nn = 0; nn < nItems ; nn++ )
      {

         ContainerHandle con = (*xpp[6])[nn];
         if( con   )
         {
            AddBtn(nn+1, _conXStrDup(con) , FALSE );
            _conRelease(con);
         }
      }
   }
   // -----
   // param 5 aTabs
   if( xpp[5]->CheckType( XPP_ARRAY ) )
   {
      DWORD nItems = xpp[5]->con_size();
      DWORD nn;
      for( nn = 0; nn < nItems ; nn++ )
      {

         ContainerHandle con = (*xpp[5])[nn];
         if( con   )
         {
            AddTab( _conXStrDup(con) , FALSE );
            _conRelease(con);
         }
      }
   }
   else { AddTab( (m_pTitle ? m_pTitle : "") ); }
   // param 7 aEdits
   if( xpp[7]->CheckType( XPP_ARRAY ) )
   {
      DWORD nGCount= xpp[7]->con_size();
      DWORD nGPos;
      for( nGPos = 0; nGPos < nGCount ; nGPos++ )
      {
         ContainerHandle cona = (*xpp[7])[nGPos];
         if( cona )
         {
            ULONG ulsz = _conGetArrayLen(cona);
            if( ulsz < 4 )
            {
               _conResizeA(cona,4);
               _conArrayPut(xpp[7]->Get(),cona,nGPos+1,0);
            }
            ULONG ul = 0;
            int    nTab    = _conArrayGetNL(cona,1,0);
            page_spec_t* pPage =  (page_spec_t*) m_Pages.Get( nTab - 1);
            if( pPage )
            {
               DWORD  nFlags  = _conArrayGetNL(cona,2,0);
               LPSTR  pLabel  = _conArrayGetXStrDup(cona,3,0);
               _conTypeA(cona,&ul,4,0);
               if( ul & XPP_LOGICAL )
               {
                  BOOL b = _conArrayGetL(cona,4,0);
                  LPSTR pCap = ( ulsz > 4 ? _conArrayGetXStrDup(cona,5,0) :0);
                  if( !pPage->AddEdit(nGPos,nFlags,pLabel,(void*)&b,XPP_LOGICAL,pCap) )
                  {
                      if( pLabel){ _xfree((void*) pLabel); }
                  }
                  if( pCap ){ _xfree((void*) pCap);}
               }
               else
               {
                  edit_spec_t* pe;
                  void* pValue  = (void*) _conArrayGetXStrDup(cona,4,0);
                  if( !pValue ){ pValue = _xgrab(1); }
                  pe = pPage->AddEdit(nGPos,nFlags,pLabel,pValue,XPP_CHARACTER,0);
                  if( pe)
                  {
                     if( ulsz > 4 )
                     {
                        DWORD nType = 0;
                        _conTypeA(cona,&nType,5,0);
                        if( nType & XPP_ARRAY )
                        {
                           DWORD n;
                           DWORD nn = 0;
                           _conSizeA(cona,&nn,5,0);
                           for( n = 0; n < nn ; n++ )
                           {
                              pe->AddPickValue(_conArrayGetXStrDup(cona,5,n+1,0));
                           }
                        }
                     }
                  }
                  else
                  {
                     if(pLabel) _xfree(pLabel);
                     if(pValue) _xfree(pValue);
                  }
               }
            }
            _conRelease(cona);
         }
      }
   }
   // ---   
   // param 8 hWndNotify
   if( xpp[8]->CheckType( XPP_NUMERIC) )
   {
      m_hWndNotify = xpp[8]->GetHWND();
   }
   // param 9 nActiveTab
   if( xpp[9]->CheckType( XPP_NUMERIC) )   
   {
      m_initial_tab_focus  = xpp[9]->GetLong();
   }
   // ---
   if( m_dwFlags & OT4XB_DDF_USETHREAD )
   {
      SECURITY_ATTRIBUTES sa;
      ZeroMemory(&sa,sizeof(sa));
      sa.nLength = sizeof(sa);
      sa.bInheritHandle = TRUE;
      DWORD dwId = 0;
      HANDLE hThread = CreateThread(&sa,0,ot4xb_dirty_dlgedit::thread_proc,(void*) this,0,&dwId);
      if( hThread ){ CloseHandle( hThread );     xpp[0]->PutDWord(dwId); }
      return;
   }
   // ---

   if( !create() ) return;
   msgloop();

   xpp[0]->PutLong( m_dlg_result + 1  );

   xpp[2]->PutDwArray((DWORD*) &m_rc,4);

   if( xpp[7]->CheckType( XPP_ARRAY ) && m_Pages.Count() )
   {
      DWORD nPages = m_Pages.Count();
      DWORD np;
      ContainerHandle cona = xpp[7]->con();
      for( np = 0; np < nPages; np++ )
      {
         page_spec_t* pPage = GetPage(np );
         if( pPage )
         {
            DWORD nEdits = pPage->m_Edits.Count();
            DWORD n;
            for( n=0; n < nEdits;n++)
            {
               edit_spec_t* pe = (edit_spec_t*) pPage->m_Edits.Get(n);
               if(pe){ pe->PutValue(cona);}
            }
         }
      }
   }
   // ---
}
// -----------------------------------------------------------------------------------------------------------------
DWORD __stdcall ot4xb_dirty_dlgedit::thread_proc(void* ctx )
{
   ot4xb_dirty_dlgedit* d = (ot4xb_dirty_dlgedit*) ctx;
   if(d->create() ){ d->msgloop(); }
   delete d;
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//  ot4xb_dirty_DlgEdit( 1hParent , 2rect , 3nFlags , 4cTitle , 5aTabs, 6aBtn , 7aEdits , 8hWndNotify, 9 nActiveTab)
//
//
//
//
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY OT4XB_DIRTY_DLGEDIT( XppParamList pl )
{
   TXppParamList xpp(pl,0);

   ot4xb_dirty_dlgedit* d = new ot4xb_dirty_dlgedit();
   d->run(xpp);
   if(d->m_dwFlags & OT4XB_DDF_USETHREAD ){ return; }
   delete d;
}
// -----------------------------------------------------------------------------------------------------------------

