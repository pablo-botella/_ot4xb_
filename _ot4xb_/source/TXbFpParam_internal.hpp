//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_APIcpp_Param_h_
#define _API_cpp_APIcpp_Param_h_
// -----------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
// -----------------------------------------------------------------------------------------------------------------
class TXbFpQParam;
class TXbFpParam;
// -----------------------------------------------------------------------------------------------------------------
class TXbFpParam
{
       // ---------------------------------------------------------------------------------
   public:                        //  typedef struct{ 
       ULONG           m_nType;       //  1 //    ULONG           nType;
       ULONG           m_nLen;        //  2 //    ULONG           nLen;
       BOOL            m_bByRef;      //  3 //    BOOL            bByRef;
       ContainerHandle m_con;         //  4 //    ContainerHandle con;
       LPSTR           m_pStr;        //  5 //    LPSTR           pStr;
       BOOL            m_bWrite;      //  6 //    BOOL            bWrite;
       // DWORD           m_nCntType; // 0 int/byte , 1 FLOAT
       // TList *         m_pComplex;                                  
                                  //  } CON_PLKSTREX;   
                                  
       // ---------------------------------------------------------------------------------
       TXbFpParam *      m_pNext;
       TXbFpParam *      m_pPrev;
       // ---------------------------------------------------------------------------------
       ULONG           m_nPos;
       DWORD           m_dwStackVal;
       // ---------------------------------------------------------------------------------
       BYTE            m_nSplit; // 0 = FALSE , 1 = Next , 2 Prev , 3 not push
       BYTE            m_chQualifier;
       WORD            m_wDummy;
       DWORD           m_dwData;
       // ---------------------------------------------------------------------------------
       double          m_ndData;                                     
       // ---------------------------------------------------------------------------------
       // ---------------------------------------------------------------------------------
       
       // ---------------------------------------------------------------------------------
       static TXbFpParam * InitList(XppParamList pl , ULONG nFirst , LONG * pnCount , BOOL bDisableByRef = 0);
       static ULONG PrepareStackValues(TXbFpParam * pFirst );
       static void  ReleaseAll(TXbFpParam * pFirst );
       // ---------------------------------------------------------------------------------
       void Release(void);
       void Init(XppParamList pl , ULONG nPos,BOOL bDisableByRef = 0);
       // ---------------------------------------------------------------------------------
};
// -----------------------------------------------------------------------------------------------------------------
class TXbFpQParam : public T_ot4xb_base
{
       // ---------------------------------------------------------------------------------
   public: 
       TXbFpQParam *      m_pNext;
       TXbFpQParam *      m_pPrev;
       ULONG              m_nType;  
       ULONG              m_nLen;   
       BOOL               m_bByRef; 
       ContainerHandle    m_con;    
       LPSTR              m_pStr;        // String Pointer _xgrab() or  _conWLockC()
       BOOL               m_bxgrab;      // String buffer must be free
       BOOL               m_bConLock;    // String Container Must be unlock
       BOOL               m_bObjLock;    // gwst object must be released
       DWORD              m_nStackSize;  // size of stack in DWORDs
       DWORD              m_dwq;         // Param Qualifier
       DWORD              m_dwIntMask;   // integer mask for values < 32 bit
       DWORD *            m_pdwStack;
       DWORD              m_dw0;
       DWORD              m_dw1;
       DWORD              m_dw2;
       DWORD              m_dw3;
       DWORD              m_dw4;
       DWORD              m_dw5;
       DWORD              m_dw6;
       DWORD              m_dw7;
       // ---------------------------------------------------------------------------------
       TXbFpQParam();
       ~TXbFpQParam();       
      // ---------------------------------------------------------------------------------
             
       static TXbFpQParam * InitList(XppParamList pl , DWORD* pdwq, ULONG nFirst,DWORD*pdwParams);       
       static void          ReleaseAll(TXbFpQParam * pFirst );
       static DWORD *       PrepareStack( TXbFpQParam * pFirst , DWORD * pnStackSize );
       static void  FCall(ContainerHandle conr,DWORD dwPtr,DWORD dwq,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr);
       static LONG     FCall32I(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr);
       static LONGLONG FCall64I(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr);
       static double   FCall32F(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr);
       static double   FCall64F(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr);
       // ---------------------------------------------------------------------------------
       void Release(void);
       void PutStackValues(DWORD * pStack , DWORD * pnPos);
       BOOL InitParam(XppParamList pl , ULONG nPos , DWORD dwq);
       // ---------------------------------------------------------------------------------
       void IO_QT_LPXBASE(BOOL bOut);
       void IO_QT_BOOL(BOOL bOut );
       void IO_QT_BYTEBOOL(BOOL bOut );       
       void IO_QT_INT8(BOOL bOut );
       void IO_QT_BYTE(BOOL bOut );
       void IO_QT_INT16(BOOL bOut);
       void IO_QT_WORD(BOOL bOut);
       void IO_QT_INT32(BOOL bOut);
       void IO_QT_DWORD(BOOL bOut);
       void IO_QT_INT64(BOOL bOut);
       void IO_QT_QWORD(BOOL bOut);
       void IO_QT_FLOAT(BOOL bOut);
       void IO_QT_DOUBLE(BOOL bOut);
       void IO_QT_POINTER(BOOL bOut);
       void IO_QT_LPBOOL(BOOL bOut);
       void IO_QT_LPBYTEBOOL(BOOL bOut);       
       void IO_QT_LPINT8(BOOL bOut);
       void IO_QT_LPBYTE(BOOL bOut);
       void IO_QT_LPINT16(BOOL bOut);
       void IO_QT_LPWORD(BOOL bOut);
       void IO_QT_LPINT32(BOOL bOut);
       void IO_QT_LPDWORD(BOOL bOut);
       void IO_QT_LPINT64(BOOL bOut);
       void IO_QT_LPQWORD(BOOL bOut);
       void IO_QT_LPFLOAT(BOOL bOut);
       void IO_QT_LPDOUBLE(BOOL bOut);
       void IO_QT_STR2WIDE(BOOL bOut);
       void IO_QT_STR2WIDE_W(BOOL bOut);
       void IO_QT_HWND(BOOL bOut);
       void IO_QT_VARIANT(BOOL bOut);
       // ---------------------------------------------------------------------------------

};
// -----------------------------------------------------------------------------------------------------------------
#endif // __cplusplus
// -----------------------------------------------------------------------------------------------------------------
#endif