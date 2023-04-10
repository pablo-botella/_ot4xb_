//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TXppParamList : public T_ot4xb_base
{
   public:
       XppParamList        m_pl;
       TXbCPItem **        m_pItems;
       ULONG               m_nPCount;
       ULONG               m_nCapacity;       
       ULONG               m_nFormalCount;              
       // ---------------------------------------------------------------------------------
       TXppParamList( XppParamList pl = 0 , ULONG nFormalCount = 0);       
       ~TXppParamList( void );       
       void init_formal_params(void); // will be usefull for thread delegation       
        TXbCPItem* _get_(ULONG n);
        TXbCPItem* operator[]( int n );         
        ULONG PCount(void);
        DWORD Eval(UINT nParams = 0);
};
// -----------------------------------------------------------------------------------------------------------------
class OT4XB_API TXbCPItem : public T_ot4xb_base
{
   public:
       XppParamList    m_pl;
       ULONG           m_nRealPosition;
       BOOL            m_bInit;               // typedef struct{
       ULONG           m_nType;               //  ULONG           nType;
       ULONG           m_nLockLen;            //  ULONG           nLen;
       BOOL            m_bByRef;              //  BOOL            bByRef;
       ContainerHandle m_con;                 //  ContainerHandle con;
       LPSTR           m_pLockStr;            //  LPSTR           pStr;
       BOOL            m_bLockW;              //  BOOL            bWrite;
       DWORD           m_nCntType;            //  DWORD           nCntType; // 0 int/byte , 1 FLOAT
       TList *         m_pComplex;            //  TList *         pComplex;
       BOOL            m_bStrLockEx;          // } CON_PLKSTREX;

       // ---------------------------------------------------------------------------------
       TXbCPItem( void );
       TXbCPItem( XppParamList,ULONG  );
       TXbCPItem( ContainerHandle con , BOOL bByRef);
       ~TXbCPItem( void );
       ContainerHandle detach(void);
       void init(void );       
       // ---------------------------------------------------------------------------------
       ULONG           GetType(void);
       BOOL            CheckType(ULONG ulType);
       ContainerHandle GetT( ULONG ulType , BOOL * pbByRef = 0);
       ContainerHandle Get( BOOL * pbByRef = 0);
       ContainerHandle con(void);       
       void            Put( ContainerHandle con = 0);
       void            Put( TXbCPItem* p);       
       BOOL            GetBool(void);
       LONG            GetLong(void);
       HANDLE          GetHandle( void);
       LONGLONG        GetQWord(void);
       DWORD           GetDWord(void);
       WORD            GetWord(void);
       double          GetDouble(void);
       FLOAT           GetFloat(void);
	   LONGLONG        GetSqlStrMoney(void);
	   void            PutSqlStrMoney(LONGLONG qn, DWORD flags, DWORD pad);
       void            PutBool(BOOL value );
       void            PutLong(LONG value );
       void            PutQWord(LONGLONG value );
       void            PutDWord(DWORD value );
       void            PutWord(WORD value );
       void            PutDouble(double value );
       void            PutDoubleFormat(double ndValue , int nDigits , int nDec );
       void            PutFloat(FLOAT value );
       void            PutDateString( LPSTR ds );       
		 void            PutJulianDate( DWORD dw );
		 DWORD           GetJulianDate( void);
       LPSTR           GetDateString(void); 
       void            GetDateString(LPSTR ds);
       LPSTR           StrDupA(ULONG * pnLen = 0);
       LPWSTR          StrDupW(ULONG * pnBytes = 0);
       BSTR            StrDupBSTR(void);
       ULONG           GetCL(LPSTR p , ULONG nBuffSize);
       void            PutStrLen(LPSTR pStr , ULONG nLen);
       void            PutStr(LPSTR pStr);
       void            PutBSTR2a(BSTR bs);       
       LPSTR           LockStr( ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       void            UnlockStr(void);
       HWND            GetHWND(void);
       void            PutDwArray(DWORD* pdw , DWORD cc);
       void            PutNewArray(ULONG nDim,...);
       // --------------------------------
       BOOL            PutEmptyData(ULONG nType,LONG nLen = 0, LONG nDec = 0);
       BOOL            resize(ULONG nNewSize);       
       ULONG           con_size(void);              
       // --------------------------------
       ContainerHandle operator[]( DWORD n );
       // --------------------------------       
       BOOL            GetGuid(GUID* pDst);
       BOOL            PutGuid(GUID* pSrc , BOOL bBraces = FALSE);
       // --------------------------------
       LPSTR           LockStrEx(BOOL bWrite = FALSE);
       UINT            ExLen(void);
       LPSTR           _LockStrEx_(BOOL bWrite = FALSE, DWORD nCntType = 0);
       LPSTR           RLockStrEx(void);
       LPSTR           WLockStrEx(void);
       LPSTR           RLockStrExF(void);
       LPSTR           WLockStrExF(void);
       LPSTR           RLockStrExF8(void);
       LPSTR           WLockStrExF8(void);
       void            UnLockStrEx(void);
       // --------------------------------

       LPSTR str(void);       
       // --------------------------------       
       void setprop_ansi2wide( LPWSTR*  ppw );
       void getprop_wide2ansi( LPWSTR*  ppw );       
};
// -----------------------------------------------------------------------------------------------------------------
