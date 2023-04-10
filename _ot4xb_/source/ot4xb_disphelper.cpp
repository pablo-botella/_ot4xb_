//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
HRESULT dhCreateObject(LPCOLESTR szProgId, LPCWSTR szMachine, IDispatch ** ppDisp);
HRESULT dhGetObject(LPCOLESTR szFile, LPCOLESTR szProgId, IDispatch ** ppDisp);
HRESULT dhCreateObjectEx(LPCOLESTR szProgId, REFIID riid, DWORD dwClsContext, COSERVERINFO * pServerInfo, void ** ppv);
HRESULT dhGetObjectEx(LPCOLESTR szFile, LPCOLESTR szProgId, REFIID riid, DWORD dwClsContext, LPVOID lpvReserved, void ** ppv);
HRESULT dhCallMethod(IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhPutValue(IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhPutRef(IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhGetValue(LPCWSTR szIdentifier, void * pResult, IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhInvoke(int invokeType, VARTYPE returnType, VARIANT * pvResult, IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhInvokeArray(int invokeType, VARIANT * pvResult, UINT cArgs, IDispatch * pDisp, LPCOLESTR szMember, VARIANT * pArgs);
HRESULT dhCallMethodV(IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhPutValueV(IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhPutRefV(IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhGetValueV(LPCWSTR szIdentifier, void * pResult, IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhInvokeV(int invokeType, VARTYPE returnType, VARIANT * pvResult, IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhEnumBegin(IEnumVARIANT ** ppEnum, IDispatch * pDisp, LPCOLESTR szMember, ...);
HRESULT dhEnumBeginV(IEnumVARIANT ** ppEnum, IDispatch * pDisp, LPCOLESTR szMember, va_list * marker);
HRESULT dhEnumNextObject(IEnumVARIANT * pEnum, IDispatch ** ppDisp);
HRESULT dhEnumNextVariant(IEnumVARIANT * pEnum, VARIANT * pvResult);
HRESULT dhInitializeImp(BOOL bInitializeCOM, BOOL bUnicode);
void dhUninitialize(BOOL bUninitializeCOM);
HRESULT dhToggleExceptions(BOOL bShow);
// -----------------------------------------------------------------------------------------------------------------
END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
static void disphelper( XppParamList pl , DWORD dwFPtr)
{
   if( GetTlsHeapManager()->m_disphelper_refcount < 1 )
   {
      dhInitializeImp(TRUE,TRUE);   
      dhToggleExceptions(FALSE);
      GetTlsHeapManager()->m_disphelper_refcount = 1;      
   }

   LONG nParams,n;
   BOOL bDisableByRef = (BOOL) (GetTlsHeapManager()->PopNextFpFlags() & 1);
   TXbFpParam * pParams = TXbFpParam::InitList(pl,1,&nParams,bDisableByRef);
   DWORD nStack       = TXbFpParam::PrepareStackValues(pParams);
   LONG sp1,sp2;
   LONG nl;

   _asm mov sp1 ,esp; // Save the stack before
   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         DWORD dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }
   _asm mov eax , dwFPtr;
   _asm call eax;
   _asm mov sp2 ,esp; // Save the stack after
   _asm mov nl ,eax;
   if( sp1 > sp2 ) _asm add esp , nStack; // Restore the stack if needed

   GetTlsHeapManager()->PutLastError(GetLastError());
   TXbFpParam::ReleaseAll(pParams);
   _retnl(pl,nl);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _DH_CREATEOBJECT       ){ disphelper(pl, (DWORD) dhCreateObject       ); }
_XPP_REG_FUN_( _DH_GETOBJECT          ){ disphelper(pl, (DWORD) dhGetObject          ); }
_XPP_REG_FUN_( _DH_CREATEOBJECTEX     ){ disphelper(pl, (DWORD) dhCreateObjectEx     ); }
_XPP_REG_FUN_( _DH_GETOBJECTEX        ){ disphelper(pl, (DWORD) dhGetObjectEx        ); }
_XPP_REG_FUN_( _DH_CALLMETHOD         ){ disphelper(pl, (DWORD) dhCallMethod         ); }
_XPP_REG_FUN_( _DH_PUTVALUE           ){ disphelper(pl, (DWORD) dhPutValue           ); }
_XPP_REG_FUN_( _DH_PUTREF             ){ disphelper(pl, (DWORD) dhPutRef             ); }
_XPP_REG_FUN_( _DH_GETVALUE           ){ disphelper(pl, (DWORD) dhGetValue           ); }
_XPP_REG_FUN_( _DH_INVOKE             ){ disphelper(pl, (DWORD) dhInvoke             ); }
_XPP_REG_FUN_( _DH_INVOKEARRAY        ){ disphelper(pl, (DWORD) dhInvokeArray        ); }
_XPP_REG_FUN_( _DH_CALLMETHODV        ){ disphelper(pl, (DWORD) dhCallMethodV        ); }
_XPP_REG_FUN_( _DH_PUTVALUEV          ){ disphelper(pl, (DWORD) dhPutValueV          ); }
_XPP_REG_FUN_( _DH_PUTREFV            ){ disphelper(pl, (DWORD) dhPutRefV            ); }
_XPP_REG_FUN_( _DH_GETVALUEV          ){ disphelper(pl, (DWORD) dhGetValueV          ); }
_XPP_REG_FUN_( _DH_INVOKEV            ){ disphelper(pl, (DWORD) dhInvokeV            ); }
_XPP_REG_FUN_( _DH_ENUMBEGIN          ){ disphelper(pl, (DWORD) dhEnumBegin          ); }
_XPP_REG_FUN_( _DH_ENUMBEGINV         ){ disphelper(pl, (DWORD) dhEnumBeginV         ); }
_XPP_REG_FUN_( _DH_ENUMNEXTOBJECT     ){ disphelper(pl, (DWORD) dhEnumNextObject     ); }
_XPP_REG_FUN_( _DH_ENUMNEXTVARIANT    ){ disphelper(pl, (DWORD) dhEnumNextVariant    ); }
_XPP_REG_FUN_( _DH_TOGGLEEXCEPTIONS   ){ disphelper(pl, (DWORD) dhToggleExceptions   ); }
// -----------------------------------------------------------------------------------------------------------------
