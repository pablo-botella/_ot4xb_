//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function-family>
      <name>DispHelper COM wrappers</name>
      <source>ot4xb_disphelper.cpp</source>
      <category>interop/com</category>
      <description>
         Thin OT4XB exports over the bundled DispHelper COM helper library. They make it possible to create,
         retrieve, invoke and enumerate IDispatch-based COM objects from Xbase++ code.
      </description>
      <status>Low-level COM interop API.</status>
      <remarks>
         The first call initializes DispHelper for Unicode mode and calls CoInitialize internally through
         dhInitializeImp(.T., .T.). DispHelper exceptions are disabled by default, so the wrappers return the
         HRESULT produced by the underlying dh* function. The latest Win32 error captured by the wrapper can be
         read with nFpGetLastError().

         Parameters follow the C DispHelper signatures. Interface pointers such as IDispatch*, IUnknown* and
         IEnumVARIANT* are numeric pointer values in Xbase++. Out parameters are passed by reference. String
         member names and ProgIds are OLE strings in the underlying API; use the same string representation
         expected by the called DispHelper entry point.

         DispHelper format identifiers are case-sensitive. Common identifiers are d=VT_I4, u=VT_UI4, e=VT_R8,
         b=VT_BOOL, v=VARIANT, m=missing optional argument, B=BSTR, S=wide string, s=ANSI string, T=current
         DispHelper text mode string, o=IDispatch, O=IUnknown, D=DATE, t=time_t, W=SYSTEMTIME, f=FILETIME and
         p=pointer value.
      </remarks>
      <functions>
         <function>
            <name>_dh_createobject</name>
            <syntax>_dh_createobject( cProgId, cMachine, @pDispatch ) -> nHRESULT</syntax>
            <description>Creates a COM object by ProgId and returns its IDispatch pointer in @pDispatch.</description>
         </function>
         <function>
            <name>_dh_getobject</name>
            <syntax>_dh_getobject( cFile, cProgId, @pDispatch ) -> nHRESULT</syntax>
            <description>Gets an existing COM object or loads an object from a file and returns IDispatch in @pDispatch.</description>
         </function>
         <function>
            <name>_dh_createobjectex</name>
            <syntax>_dh_createobjectex( cProgId, pIID, nClsContext, pServerInfo, @pInterface ) -> nHRESULT</syntax>
            <description>Extended object creation that requests a specific interface and class context.</description>
         </function>
         <function>
            <name>_dh_getobjectex</name>
            <syntax>_dh_getobjectex( cFile, cProgId, pIID, nClsContext, pReserved, @pInterface ) -> nHRESULT</syntax>
            <description>Extended get-object helper that requests a specific interface.</description>
         </function>
         <function>
            <name>_dh_callmethod</name>
            <syntax>_dh_callmethod( pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Invokes a method or method path on an IDispatch object.</description>
         </function>
         <function>
            <name>_dh_putvalue</name>
            <syntax>_dh_putvalue( pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Sets a property value through IDispatch.</description>
         </function>
         <function>
            <name>_dh_putref</name>
            <syntax>_dh_putref( pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Sets a property by reference through IDispatch.</description>
         </function>
         <function>
            <name>_dh_getvalue</name>
            <syntax>_dh_getvalue( cIdentifier, @xResult, pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Gets a property or method result converted according to cIdentifier.</description>
         </function>
         <function>
            <name>_dh_invoke</name>
            <syntax>_dh_invoke( nInvokeType, nReturnType, pVariantResult, pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Generic IDispatch invocation wrapper.</description>
         </function>
         <function>
            <name>_dh_invokearray</name>
            <syntax>_dh_invokearray( nInvokeType, pVariantResult, nArgs, pDispatch, cMember, pVariantArgs ) -> nHRESULT</syntax>
            <description>Generic IDispatch invocation using an existing VARIANT argument array.</description>
         </function>
         <function>
            <name>_dh_callmethodv</name>
            <syntax>_dh_callmethodv( pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_callmethod(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_putvaluev</name>
            <syntax>_dh_putvaluev( pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_putvalue(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_putrefv</name>
            <syntax>_dh_putrefv( pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_putref(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_getvaluev</name>
            <syntax>_dh_getvaluev( cIdentifier, pResult, pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_getvalue(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_invokev</name>
            <syntax>_dh_invokev( nInvokeType, nReturnType, pVariantResult, pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_invoke(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_enumbegin</name>
            <syntax>_dh_enumbegin( @pEnum, pDispatch, cMember, ... ) -> nHRESULT</syntax>
            <description>Starts enumeration over a COM collection and returns an IEnumVARIANT pointer in @pEnum.</description>
         </function>
         <function>
            <name>_dh_enumbeginv</name>
            <syntax>_dh_enumbeginv( @pEnum, pDispatch, cMember, pVaList ) -> nHRESULT</syntax>
            <description>va_list variant of _dh_enumbegin(); mainly useful for C-level integration.</description>
         </function>
         <function>
            <name>_dh_enumnextobject</name>
            <syntax>_dh_enumnextobject( pEnum, @pDispatch ) -> nHRESULT</syntax>
            <description>Reads the next enumerated item as an IDispatch pointer.</description>
         </function>
         <function>
            <name>_dh_enumnextvariant</name>
            <syntax>_dh_enumnextvariant( pEnum, pVariantResult ) -> nHRESULT</syntax>
            <description>Reads the next enumerated item into a VARIANT buffer.</description>
         </function>
         <function>
            <name>_dh_toggleexceptions</name>
            <syntax>_dh_toggleexceptions( lShow ) -> nHRESULT</syntax>
            <description>Enables or disables DispHelper exception display.</description>
         </function>
      </functions>
   </function-family>
</xbdoc>
*******************************************************************************************************************/
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
