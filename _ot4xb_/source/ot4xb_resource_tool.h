//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// #pragma pack(push , 4)
// #pragma pack(pop)
class OT4XB_API resource_tool_base_t  : public T_ot4xb_base  
{
   public:
      // ---------------------------------------------------------------------------------
      static void PtAlignDWord( LPVOID & ptr ){ ptr = _align_dword_ptr_(LPVOID,ptr); };
      // ---------------------------------------------------------------------------------
      static LPSTR PtReadStr(LPVOID & ptr , DWORD * pcb = 0)
      {
         int cc = _xstrlenW( (LPWSTR) ptr );
         LPSTR  pStr = w2ansi((LPWSTR) ptr , cc , (int*) pcb );
         ptr = _mk_ptr_( LPVOID , ptr ,((cc+1) * sizeof(WCHAR)) );
         return pStr;
      };
      // ---------------------------------------------------------------------------------
      void PtWriteStr(LPVOID & ptr , LPSTR pu , int cb = -1 )
      {
         if( cb == -1 ) cb = lstrlenA(pu);
         int cc = MultiByteToWideChar(CP_ACP,0,pu,(int)cb,0,0);
         cc = MultiByteToWideChar(CP_ACP,0,pu,(int)cb,(LPWSTR) ptr ,cc+1);
         reinterpret_cast<LPWSTR>(ptr)[cc] = 0;
         ptr = _mk_ptr_( LPVOID , ptr ,((cc+1) * sizeof(WCHAR)) );                  
      };
      // ---------------------------------------------------------------------------------
      static DWORD PtReadDWord(LPVOID & ptr ){ DWORD n = _mk_ptr_(LPDWORD,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(DWORD)); return n; };
      static LONG  PtReadLong( LPVOID & ptr ){ LONG  n = _mk_ptr_(LPLONG,ptr,0)[0];  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LONG));  return n; };
      static WORD  PtReadWord( LPVOID & ptr ){ WORD  n = _mk_ptr_(LPWORD ,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(WORD) ); return n; };      
      static short PtReadshort(LPVOID & ptr ){ short n = _mk_ptr_(PSHORT ,ptr,0)[0]; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(short)); return n; };            
      // ---------------------------------------------------------------------------------
      static void PtWriteDWord(LPVOID & ptr  , DWORD n ){ _mk_ptr_(LPDWORD,ptr,0)[0] = n; ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LPDWORD)); };
      static void PtWriteLong( LPVOID & ptr  , LONG  n ){ _mk_ptr_(LPLONG,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LPLONG)); };      
      static void PtWriteWord( LPVOID & ptr  , WORD  n ){ _mk_ptr_(LPWORD,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(LPWORD)); };      
      static void PtWriteShort(LPVOID & ptr  , short n ){ _mk_ptr_(PSHORT,ptr,0)[0] = n;  ptr = _mk_ptr_( LPVOID , ptr ,sizeof(PSHORT)); };      
      // ---------------------------------------------------------------------------------      
      static LONG GdiGetCharDimensions(HDC hDC, TEXTMETRIC * pTm = 0 , LONG * pHeight = 0);
};
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