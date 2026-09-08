//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// #pragma pack(push , 4)
// #pragma pack(pop)
/*{{begin-cpp-class}}*/
/*{{cpp-class_: resource_tool_base_t
   | parent: {{ilink: <cpp-class T_ot4xb_base> T_ot4xb_base}}
   | category: c-api/classes , winapi/resources
   | desc: Helpers for reading and writing the binary layout of Windows resources (dialog templates, and the
     like): every Pt* function takes the pointer by reference, reads or writes one field at it, and moves
     the pointer past the field, so a template is parsed or built by a plain sequence of calls. Strings in
     resources are UTF-16 and are converted from and to the ANSI code page on the way. Meant to be the
     base of a resource-handling class; on its own it only holds static functions.
     | _kw_: resource_tool_base_t, Class }}*/
class OT4XB_API resource_tool_base_t  : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      /*{{|method_: `static void PtAlignDWord( LPVOID& ptr )` | desc_: Rounds the pointer up to the next
         DWORD boundary. }}*/
      static void PtAlignDWord( LPVOID & ptr ){ ptr = _align_dword_ptr_(LPVOID,ptr); };
      // ---------------------------------------------------------------------------------
      /*{{|method_: `static LPSTR PtReadStr( LPVOID& ptr, DWORD* pcb = 0 )` | desc_: Reads a zero-terminated
         UTF-16 string, returns it converted to ANSI as a new string in the ot4xb heap (its length in
         **pcb**; free it with _xfree) and moves the pointer past the terminator. }}*/
      static LPSTR PtReadStr(LPVOID & ptr , DWORD * pcb = 0)
      {
         int cc = _xstrlenW( (LPWSTR) ptr );
         LPSTR  pStr = w2ansi((LPWSTR) ptr , cc , (int*) pcb );
         ptr = _mk_ptr_( LPVOID , ptr ,((cc+1) * sizeof(WCHAR)) );
         return pStr;
      };
      // ---------------------------------------------------------------------------------
      /*{{|method_: `void PtWriteStr( LPVOID& ptr, LPSTR pu, int cb = -1 )` | desc_: Writes **cb** bytes of
         an ANSI string (-1: up to the terminator) as a zero-terminated UTF-16 string at the pointer and
         moves it past the terminator. }}*/
      void PtWriteStr(LPVOID & ptr , LPSTR pu , int cb = -1 )
      {
         if( cb == -1 ) cb = lstrlenA(pu);
         int cc = MultiByteToWideChar(CP_ACP,0,pu,(int)cb,0,0);
         cc = MultiByteToWideChar(CP_ACP,0,pu,(int)cb,(LPWSTR) ptr ,cc+1);
         reinterpret_cast<LPWSTR>(ptr)[cc] = 0;
         ptr = _mk_ptr_( LPVOID , ptr ,((cc+1) * sizeof(WCHAR)) );                  
      };
      // ---------------------------------------------------------------------------------
      /*{{|method_: `static DWORD PtReadDWord( LPVOID& ptr )` | desc_: Reads a DWORD and moves the pointer 4
         bytes; PtReadLong(), PtReadWord() and PtReadshort() do the same for a LONG, a WORD and a short. }}*/
      static DWORD PtReadDWord(LPVOID & ptr ){ DWORD n = _mk_ptr_(LPDWORD,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(DWORD)); return n; };
      static LONG  PtReadLong( LPVOID & ptr ){ LONG  n = _mk_ptr_(LPLONG,ptr,0)[0];  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LONG));  return n; };
      static WORD  PtReadWord( LPVOID & ptr ){ WORD  n = _mk_ptr_(LPWORD ,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(WORD) ); return n; };
      static short PtReadshort(LPVOID & ptr ){ short n = _mk_ptr_(PSHORT ,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(short)); return n; };
      // ---------------------------------------------------------------------------------
      /*{{|method_: `static void PtWriteDWord( LPVOID& ptr, DWORD n )` | desc_: Writes a DWORD and moves the
         pointer 4 bytes; PtWriteLong(), PtWriteWord() and PtWriteShort() do the same for a LONG, a WORD
         and a short. }}*/
      static void PtWriteDWord(LPVOID & ptr  , DWORD n ){ _mk_ptr_(LPDWORD,ptr,0)[0] = n; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(DWORD)); };
      static void PtWriteLong( LPVOID & ptr  , LONG  n ){ _mk_ptr_(LPLONG,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LONG)); };
      static void PtWriteWord( LPVOID & ptr  , WORD  n ){ _mk_ptr_(LPWORD,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(WORD)); };
      static void PtWriteShort(LPVOID & ptr  , short n ){ _mk_ptr_(PSHORT,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(short)); };
      // ---------------------------------------------------------------------------------
      /*{{|method_: `static LONG GdiGetCharDimensions( HDC hDC, TEXTMETRIC* pTm = 0, LONG* pHeight = 0 )`
         | desc_: The average character width of the font selected in **hDC**, measured on the 52 letters
           the way Windows computes dialog base units; the text height comes back in **pHeight** and the
           metrics in **pTm** when asked for. 0 when the GDI calls fail. }}*/
      static LONG GdiGetCharDimensions(HDC hDC, TEXTMETRIC * pTm = 0 , LONG * pHeight = 0);
};
/*{{end-cpp-class}}*/
//-------------------------------------------------------------------------------------------------------------------------
/*
class XPPGUI_API TResourceHeader : public TResTpBase
{
   public:
       // vtbl*
       DWORD     m_dwDataSize;
       DWORD     m_dwHeaderSize;
       WORD      m_wMemoryFlags;
       WORD      m_wLanguageId;
       WORD      m_wResType;
       WORD      m_wResName;
       LPSTR     m_pResType;
       LPSTR     m_pResName;
       DWORD     m_dwResTypeLen;
       DWORD     m_dwResNameLen;
       DWORD     m_dwDataVersion;
       DWORD     m_dwVersion;        
       DWORD     m_dwCharacteristics;
       // ---------------------------
       virtual void Clean(void);
       LPSTR LoadFromStr(LPSTR pStr );
       DWORD CalculateSize(void);
       LPSTR ToStr(void);
       // ---------------------------
};
//-------------------------------------------------------------------------------------------------------------------------
// Implementation in TDlgTp.cpp
//-------------------------------------------------------------------------------------------------------------------------
class XPPGUI_API TDlgTp : public TResTpBase
{
   public:
                                  
       HINSTANCE    m_hInstance;
       TDlgTpItem * m_pFirstItem;
       TDlgTpItem * m_pLastItem;
       BOOL         m_bExtendedDlg;
       DWORD        m_dwHelpID;
       DWORD        m_dwStyleEx;
       DWORD        m_dwStyle;
       DWORD        m_dwItems;   
       short        m_x;
       short        m_y;
       short        m_cx;
       short        m_cy;
       WORD         m_wMenuId;
       WORD         m_wClassId;
       LPSTR        m_pMenuName;  
       LPSTR        m_pClassName;
       LPSTR        m_pCaption;
       WORD         m_wFontSize;
       WORD         m_wFontWeight;
       BYTE         m_chFontItalic;
       BYTE         m_chFontCharSet;
       LPSTR        m_pFontName;
       RECT *       m_pRect; 
       LONG         m_nXBaseUnit;
       LONG         m_nYBaseUnit;
       
       // ----------
       virtual void Clean(void);
       // ----------
       void DetachItem( TDlgTpItem * pItem );
       void RemoveItem( TDlgTpItem * pItem );
       TDlgTpItem * InsertItem( TDlgTpItem * pItem = 0 , TDlgTpItem * pNext = 0);
       TDlgTpItem * AddItem( TDlgTpItem * pItem = 0 );
       BOOL  LoadFromResource( HMODULE hModule , LPSTR pName );
       LPSTR LoadFromStr(LPSTR pStr );
       LPSTR ToStr( DWORD * pdwSize = 0 );
       // ----------
       void         CalculateBaseUnits(void);
       void         ToPixel(void);
       void         ToPoint(void);
       // ----------
       DWORD        CalculateStrSize(void);
       // ----------
       TDlgTpItem * GetItemById( DWORD wId );
       void SetClassName( LPSTR pClassName );  
       
       
       
};
// ---------------------------------------------------------------------------
class XPPGUI_API TDlgTpItem : public TResTpBase
{
   public:                            
       TDlgTp     * m_pParent;
       TDlgTpItem * m_pNext;
       TDlgTpItem * m_pPrev;
       DWORD        m_dwId;
       DWORD        m_dwHelpID;
       DWORD        m_dwStyle;
       DWORD        m_dwStyleEx;
       LONG         m_x;
       LONG         m_y;
       LONG         m_cx;
       LONG         m_cy;
       LPSTR        m_pClassName;
       WORD         m_wSysClassId;
       WORD         m_wIconId;
       DWORD        m_xppgui_flags; // 1 ValidIconId
       LPSTR        m_pCaption;
       DWORD        m_dwExtraDataLen;
       LPBYTE       m_pExtraData;
       RECT *       m_pRect;       
          
       // -------------------------
       virtual void Clean(void);   
       void         Detach(void);
       void         ToPixel(void);
       void         ToPoint(void);
       void         LoadFromStr(WORD ** ppw );
       // -------------------------
       DWORD        CalculateStrSize(void);
       void         ToStr(WORD ** ppw );
       // -------------------------
       void         SetClassName( LPSTR pClassName , WORD wSysClassId = 0);
       
};
// ---------------------------------------------------------------------------
*/