//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _API_cpp_XbClass_h_
#define _API_cpp_XbClass_h_
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
#pragma pack(push , 4)
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TXbGenError
{
   public:
   ContainerHandle     m_cone;
   TXbGenError(int nCode,LPSTR pOperation , LPSTR pDescription);
   TXbGenError(void);
   ~TXbGenError();
   void args(ContainerHandle cona);
   void add_arg(ContainerHandle con);
   void candefault( BOOL b );
   void canretry( BOOL b );
   void cansubstitute( BOOL b );
   void cargo(ContainerHandle con);
   void description(LPSTR p );
   void filename(LPSTR p);
   void gencode(int i);
   void operation(LPSTR p);
   void oscode(int i);
   void severity( int i);
   void subcode(int i);
   void subsystem(LPSTR p);
   void tries(int val);
   void Launch(void);
};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TXbClass
{
   public:
       BOOL                m_bDisableHooks;
       DWORD               m_dwClsCrc32;
       DWORD               m_dwClsHookHandle;
       ContainerHandle     m_conClassName;
       TXbClsPItem *       m_pLastParent;
       TXbClsMItem *       m_pLastMethod;
       TXbClsVItem *       m_pLastVar;
       ULONG               m_nParentCount;
       ULONG               m_nMethodCount;
       ULONG               m_nVarCount;
       ULONG               m_nDefaultScope;
       LPSTR               m_szPrintfBuffer;
       // ---------------------------------------------------------------------------------
       BOOL                m_bGwst;
       DWORD               m_dwGwstOffset;
       BOOL                m_bGwstUnion;
       DWORD               m_dwGwstUnionSize;
       BOOL                m_bGwstReadOnly;
       TXbClsGwstItem *    m_pLastGwst;
       ULONG               m_nGwstChildCount;
       ULONG               m_nGwstCount;
       // ---------------------------------------------------------------------------------
       static void InitHookList();
       static void FreeHookList(void);
       static DWORD  AddClassHook(LPSTR pClassName , ContainerHandle conoHook ); // ->dwHookId
       static DWORD  GetClassHookHandle(LPSTR pClassName);  // -> dwClassHookHandle
       // ---------------------------------------------------------------------------------
       void * operator new( unsigned int nSize);
       void operator delete( void * pp );
       // ---------------------------------------------------------------------------------
       ContainerHandle Create( ContainerHandle conco = NULLCONTAINER );
       // ---------------------------------------------------------------------------------
       ContainerHandle CollectSuper( void );
       ContainerHandle CollectVars( void );
       ContainerHandle CollectMethods( void );
       // ---------------------------------------------------------------------------------
       void ClassName( LPSTR pClassName );
       void Parent( LPSTR pName );
       void _xparent_( ContainerHandle cono );
       void _xGwstParent_( ContainerHandle concoParent );
       void GwstParent( LPSTR pParent = 0 );
       // ---------------------------------------------------------------------------------
       void EXPORTED(void);
       void HIDDEN(void);
       void PROTECTED(void);
       // ---------------------------------------------------------------------------------
       void _var_( LPSTR pName, ULONG nFlags);
       LPSTR _mkpf1Str_(XbCMethodType pf ,ULONG nParams , LPSTR pExtra = 0);
       void _method_( LPSTR pName, ULONG nFlags, LPSTR pCbString );
       void _property_( LPSTR pName, ULONG nFlags, LPSTR pCbString );
       void _xmethod_( LPSTR pName, ULONG nFlags, ContainerHandle conb );
       void _xproperty_( LPSTR pName, ULONG nFlags, ContainerHandle conb );
       // ---------------------------------------------------------------------------------
       void AddGwstStyleMembers(void);
       // ---------------------------------------------------------------------------------
       void Var( LPSTR pName, ULONG nMoreFlags = 0);
       void ClassVar( LPSTR pName, ULONG nMoreFlags = 0);
       void SharedClassVar( LPSTR pName, ULONG nMoreFlags = 0);
       void Method( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void ClassMethod( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void MethodCB( LPSTR pName, LPSTR pCbString);
       void Method_cbbs( LPSTR pName, LPSTR pCbString, ...);       
       void ClassMethodCB( LPSTR pName, LPSTR pCbString);
       void ClassMethod_cbbs( LPSTR pName, LPSTR pCbString, ...);              
       void Property( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void ClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void PropertyCB( LPSTR pName, LPSTR pCbString);
       void Property_cbbs( LPSTR pName, LPSTR pCbString, ...);              
       void PropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar );
       void ClassPropertyCB( LPSTR pName, LPSTR pCbString);
       void ClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       void ClassPropertyCBMask( LPSTR pName, DWORD dwMask , LPSTR pVar );
       void ROProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void ROClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void ROPropertyCB( LPSTR pName, LPSTR pCbString);
       void ROProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       void ROClassPropertyCB( LPSTR pName, LPSTR pCbString);
       void ROClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);       
       void WOProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void WOClassProperty( LPSTR pName, XbCMethodType pf ,ULONG nParams = 0 , LPSTR pExtra = 0);
       void WOPropertyCB( LPSTR pName, LPSTR pCbString);
       void WOProperty_cbbs( LPSTR pName, LPSTR pCbString,...);
       void WOClassPropertyCB( LPSTR pName, LPSTR pCbString);
       void WOClassProperty_cbbs( LPSTR pName, LPSTR pCbString,...);                     
       // ---------------------------------------------------------------------------------
       void GwstReadOnly(void);
       void GwstReadWrite(void);
       void GwstBeginUnion(void);
       void GwstEndUnion(void);
       void GwstSkipBytes(ULONG nBytes);
       void GwstAdjustSize( ULONG nBytes );
       UINT GwstGetOffset(void);
       void GwstSetOffset( UINT);
       void GwstBack(void);
       void GwstAlignNextMember(DWORD dwAlign);
       void _xchild_(LPSTR pName , ContainerHandle conco );
       void Child(LPSTR pName , LPSTR pClassName);
       void Member(LPSTR pName , ULONG nMType, UINT nSize);
       void Member_Bool(LPSTR pName);
       void Member_Byte(LPSTR pName);
       void Member_Word(LPSTR pName);
       void Member_Int16(LPSTR pName);
       void Member_Short(LPSTR pName);
       void Member_DWord(LPSTR pName);
       void Member_ULong(LPSTR pName);
       void Member_Long(LPSTR pName);
       void Member_UInt(LPSTR pName);
       void Member_Int(LPSTR pName);
       void Member_Int32(LPSTR pName);
       void Member_LParam(LPSTR pName);
       void Member_WParam(LPSTR pName);
       void Member_Pointer(LPSTR pName);
       void Member_Pointer32(LPSTR pName);
       void Member_Handle(LPSTR pName);
       void Member_hWnd(LPSTR pName);
       void Member_hDC(LPSTR pName);
       void Member_pClipVar(LPSTR pName);
       void Member_CodeBlock(LPSTR pName);
       void Member_lpXBase(LPSTR pName);
       void Member_Xbase(LPSTR pName);
       void Member_XDate(LPSTR pName);
       void Member_DWord64(LPSTR pName);
       void Member_Double(LPSTR pName);
       void Member_Float(LPSTR pName);
       void Member_lpStr(LPSTR pName);
       void Member_BinStr(LPSTR pName , UINT nSize);
       void Member_szStr(LPSTR pName , UINT nSize);
       void Member_szWStr(LPSTR pName , UINT nSize);
       void Member_DynSz(LPSTR pName );
       void Member_WordNet(LPSTR pName );
       void Member_DWordNet(LPSTR pName );
       void Member_XppGuiWnd(LPSTR pName );
       void Member_SINT8(LPSTR pName  );
       void Member_SINT16(LPSTR pName );
       void Member_UINT32(LPSTR pName );
       void Member_NINT64(LPSTR pName );
       void Member_ByteBool(LPSTR pName );
       void Member_BitField(LPSTR pName , LPSTR pHolder , DWORD sh, DWORD cb , DWORD nBits = 32);
       void Member_EmbededStructArray(LPSTR pName , LPSTR pCls , LPSTR pHolder, LPSTR pCounter, DWORD sh, DWORD cb);
       // ---------------------------------------------------------------------------------
       LPSTR cbbs(LPSTR s, ... );
       // ---------------------------------------------------------------------------------
       void opaque_prop_ansi2wide( LPSTR pName , DWORD offset );
       void opaque_prop_ARGB( LPSTR pName , DWORD offset );       


};
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API TXbClsParams : public T_ot4xb_base
{
   public:
       XppParamList        m_pl;
       BOOL                m_bResult;
       TXbCPItem *         m_return;
       TXbCPItem *         m_error;
       TXbCPItem *         m_Self;
       TXbCPItem **        m_params;
       ULONG               m_paramsCount;
       TXbCPItem **        m_eparams;
       ULONG               m_eparamsCount;
       TXbCPItem **        m_real;
       ULONG               m_realCount;
       ULONG               m_formalCount;
       // ---------------------------------------------------------------------------------
       TXbClsParams( XppParamList pl);
       ~TXbClsParams( void );       
       // ---------------------------------------------------------------------------------       
       void            ShiftParams(LONG nParams);
       void            ResetShiftParams(void);
       ULONG           PCount(void);
       ULONG           GetParamType(ULONG np);
       BOOL            CheckParamType(ULONG np , ULONG ulType);
       ContainerHandle GetTParam( ULONG np , ULONG ulType , BOOL * pbByRef = 0);
       ContainerHandle GetParam( ULONG np , BOOL * pbByRef = 0);
       void            PutParam( ULONG np , ContainerHandle con );
       BOOL            GetParamBool(ULONG np);
       LONG            GetParamLong(ULONG np);
       DWORD           GetParamDWord(ULONG np);
       LONGLONG        GetParamQWord(ULONG np);
       WORD            GetParamWord(ULONG np);
       DWORD           GetParamLoHi2DWord(ULONG np);
       double          GetParamDouble(ULONG np);
       FLOAT           GetParamFloat(ULONG np);
       HWND            GetParamHWND( ULONG np);
       void            PutParamBool(ULONG np       , BOOL     value );
       void            PutParamLong(ULONG np       , LONG     value );
       void            PutParamDWord(ULONG np      , DWORD    value );
       void            PutParamQWord(ULONG np      , LONGLONG    value );
       void            PutParamWord(ULONG np       , WORD     value );
       void            PutParamDWord2LoHi(ULONG np , DWORD    value );
       void            PutParamDouble(ULONG np     , double   value );
       void            PutParamFloat(ULONG np      , FLOAT    value );
       LPSTR           ParamStrDup(ULONG np , ULONG * pnLen = 0);
       LPWSTR          ParamStrDupW(ULONG np , ULONG * pnBytes = 0);
       ULONG           ParamGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize);
       LPSTR           ParamLockStr(ULONG np , ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       void            ParamUnlockStr(ULONG np);
       void            ParamPutStrLen(ULONG np,LPSTR pStr , ULONG nLen);
       void            ParamPutStr(ULONG np,LPSTR pStr);
       LPSTR           ParamRLockStrEx(ULONG np);
       LPSTR           ParamWLockStrEx(ULONG np);
       LPSTR           ParamRLockStrExF(ULONG np);
       LPSTR           ParamWLockStrExF(ULONG np);
       LPSTR           ParamRLockStrExF8(ULONG np);
       LPSTR           ParamWLockStrExF8(ULONG np);
       void            ParamUnLockStrEx(ULONG np);
       ULONG           ParamExLen(ULONG np);
       // -------------
       BOOL            ParamGetGuid(ULONG np, GUID* pDst);
       BOOL            ParamPutGuid(ULONG np, GUID* pSrc , BOOL bBraces = FALSE);
       // -------------
       void            Param_setprop_ansi2wide( ULONG np , LPWSTR*  ppw );
       // ---------------------------------------------------------------------------------

       // ---------------------------------------------------------------------------------
       ULONG           ECount(void);
       ULONG           GetExtraType(ULONG np);
       BOOL            CheckExtraType(ULONG np , ULONG ulType);
       ContainerHandle GetTExtra( ULONG np , ULONG ulType , BOOL * pbByRef = 0);
       ContainerHandle GetExtra( ULONG np , BOOL * pbByRef = 0);
       void            PutExtra( ULONG np , ContainerHandle con );
       BOOL            GetExtraBool(ULONG np);
       LONG            GetExtraLong(ULONG np);
       DWORD           GetExtraDWord(ULONG np);
       LONGLONG        GetExtraQWord(ULONG np);
       WORD            GetExtraWord(ULONG np);
       DWORD           GetExtraLoHi2DWord(ULONG np);
       double          GetExtraDouble(ULONG np);
       FLOAT           GetExtraFloat(ULONG np);
       ULONG           ExtraGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize);
       void            PutExtraBool(ULONG np       , BOOL     value );
       void            PutExtraLong(ULONG np       , LONG     value );
       void            PutExtraDWord(ULONG np      , DWORD    value );
       void            PutExtraQWord(ULONG np      , LONGLONG    value );
       void            PutExtraWord(ULONG np       , WORD     value );
       void            PutExtraDWord2LoHi(ULONG np , DWORD    value );
       void            PutExtraDouble(ULONG np     , double   value );
       void            PutExtraFloat(ULONG np      , FLOAT    value );
       LPSTR           ExtraLockStr(ULONG np , ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       void            ExtraUnlockStr(ULONG np);
       void            ExtraPutStrLen(ULONG np,LPSTR pStr , ULONG nLen);
       void            ExtraPutStr(ULONG np,LPSTR pStr);
       // ---------------------------------------------------------------------------------
       ContainerHandle GetSelf(void);
       void * GetSelfC(void);
       void SetSelfC(void *);
       void PutReturnSelf(void);
       // ---------------------------------------------------------------------------------
       ULONG GetReturnType(void);
       BOOL CheckReturnType(ULONG ulType);
       ContainerHandle GetReturn(void);
       void PutReturn(ContainerHandle con = 0 );
       BOOL GetReturnBool(void);
       LONG GetReturnLong(void);
       DWORD GetReturnDWord(void);
       LONGLONG GetReturnQWord(void);
       WORD GetReturnWord(void);
       double GetReturnDouble(void);
       FLOAT GetReturnFloat(void);
       void PutReturnBool(BOOL value );
       void PutReturnLong(LONG value );
       void PutReturnDWord(DWORD value );
       void PutReturnQWord(LONGLONG    value );
       void PutReturnWord(WORD value);
       void PutReturnDouble(double value );
       void PutReturnFloat(FLOAT value );
       void PutReturnStrLen(LPSTR pStr , ULONG nLen);
       void PutReturnStr(LPSTR pStr);
       void PutReturnWStr(LPWSTR pWStr);
       LPSTR LockReturnStr(ULONG * pnSize = 0 , BOOL bWrite = FALSE );
       void  UnlockReturnStr(void);
       // ------
       BOOL GetReturnGuid(GUID* pDst);
       BOOL PutReturnGuid(GUID* pSrc , BOOL bBraces = FALSE);
       // ------       
       void PutReturn_getprop_wide2ansi( LPWSTR* ppw );
       // ------
       LPSTR ReturnRLockStrEx(void);
       LPSTR ReturnWLockStrEx(void);
       LPSTR ReturnRLockStrExF(void);
       LPSTR ReturnWLockStrExF(void);
       LPSTR ReturnRLockStrExF8(void);
       LPSTR ReturnWLockStrExF8(void);
       void  ReturnUnLockStrEx(void);
       ULONG ReturnExLen(void);
       BOOL  ReturnNewObj(LPSTR pClassName, ContainerHandle p1 , ... );
       BOOL  ReturnNewObjR(LPSTR pClassName, ContainerHandle p1 , ... );
       void  ReturnNewArray(DWORD nDim = 0, DWORD* pDim = 0);
       // ---------------------------------------------------------------------------------
       void GenError(void);
       ContainerHandle GetError(void);
       void SetErrorArgs(void);
       void SetErrorArgs( ContainerHandle cona );
       void SetErrorDescription( LPSTR );
       void SetErrorFilename( LPSTR );
       void SetErrorGenCode( LONG );
       void SetErrorOperation( LPSTR );
       void SetErrorOsCode( LONG );
       void SetErrorSeverity( LONG );
       void SetErrorSubCode( LONG );
       void SetErrorSubSystem( LPSTR );
       // ---------------------------------------------------------------------------------
       ULONG           GetMemberType(LPSTR pName);
       BOOL            CheckMemberType(LPSTR pName, ULONG ulType);
       ContainerHandle GetTMember(LPSTR pName , ULONG ulType);
       ContainerHandle GetMember(LPSTR pName);
       void            PutMember(LPSTR pName, ContainerHandle con );
       void            PutMemberR(LPSTR pName, ContainerHandle con );       
       LPSTR           GetMemberStr(LPSTR pName , ULONG * pnLen = 0);
       LPWSTR          GetMemberStr2W(LPSTR pName , ULONG * pnLen = 0);       
       BOOL            GetMemberBool(LPSTR pName);
       LONG            GetMemberLong(LPSTR pName);
       DWORD           GetMemberDWord(LPSTR pName);
       WORD            GetMemberWord(LPSTR pName);
       double          GetMemberDouble(LPSTR pName);
       FLOAT           GetMemberFloat(LPSTR pName);
       void            PutMemberBool(LPSTR pName       , BOOL     value );
       void            PutMemberLong(LPSTR pName       , LONG     value );
       void            PutMemberDWord(LPSTR pName      , DWORD    value );
       void            PutMemberWord(LPSTR pName       , WORD     value );
       void            PutMemberDouble(LPSTR pName     , double   value );
       void            PutMemberFloat(LPSTR pName      , FLOAT    value );
       void            MemberPutStrLen(LPSTR pName,LPSTR pStr , ULONG nLen);
       void            MemberPutStr(LPSTR pName,LPSTR pStr);
       // ---------------------------------------------------------------------------------
       void*           Lock(ULONG* pdwSize = 0);
       void            Unlock(void);
       // ---------------------------------------------------------------------------------
};

//----------------------------------------------------------------------------------------------------------------------
// C++ functions
//----------------------------------------------------------------------------------------------------------------------
#pragma pack(pop)
#endif // __cplusplus
//----------------------------------------------------------------------------------------------------------------------
#endif