//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-note-id}}*/
/*{{note-id: dh-wrappers
            | title_: The DispHelper COM wrappers }}*/
/*{{|:
   Thin OT4XB exports over the bundled DispHelper COM helper library. They make it possible to create,
   retrieve, invoke and enumerate IDispatch-based COM objects from Xbase++ code. This is a low-level
   COM interop API.

   The first call initializes DispHelper for Unicode mode and calls CoInitialize internally through
   dhInitializeImp(.T., .T.). DispHelper exceptions are disabled by default, so the wrappers return the
   HRESULT produced by the underlying dh* function. The latest Win32 error captured by the wrapper can
   be read with nFpGetLastError().

   Parameters follow the C DispHelper signatures. Interface pointers such as IDispatch*, IUnknown* and
   IEnumVARIANT* are numeric pointer values in Xbase++. Out parameters are passed by reference. String
   member names and ProgIds are OLE strings in the underlying API; use the same string representation
   expected by the called DispHelper entry point. }}*/
/*{{include-note-id: com-helpers}}*/
/*{{end-note-id}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-note-id}}*/
/*{{note-id: dh-format-identifiers
            | title_: DispHelper format identifiers }}*/
/*{{|:
   DispHelper format identifiers are case-sensitive. Common identifiers:
     d = VT_I4
     u = VT_UI4
     e = VT_R8
     b = VT_BOOL
     v = VARIANT
     m = missing optional argument
     B = BSTR
     S = wide string
     s = ANSI string
     T = current DispHelper text mode string
     o = IDispatch
     O = IUnknown
     D = DATE
     t = time_t
     W = SYSTEMTIME
     f = FILETIME
     p = pointer value }}*/
/*{{end-note-id}}*/
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
/*{{begin-function}}*/
/*{{function_: _dh_createobject
            | syntax_: `_dh_createobject( cProgId, cMachine, @pDispatch ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, CreateObject, ProgId, CLSID, IDispatch, disphelper
   }}*/
/*{{|desc: Creates a COM object from its ProgId - or from a "{...}" CLSID string - and returns its
      IDispatch pointer in pDispatch. With a machine name the object is created on that remote machine
      (CLSCTX_REMOTE_SERVER); with cMachine NIL it is created locally (in-process or local server).
    | params:
    - `cProgId` Character - ProgId or "{...}" CLSID as an OLE (wide) string.
    - `cMachine` Character - Remote machine name as an OLE string; NIL for the local machine.
    - `pDispatch` Numeric - Output, by reference; receives the IDispatch pointer of the new object.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_CREATEOBJECT       ){ disphelper(pl, (DWORD) dhCreateObject       ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_getobject
            | syntax_: `_dh_getobject( cFile, cProgId, @pDispatch ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, GetObject, running object, moniker, IDispatch, disphelper
   }}*/
/*{{|desc: Returns in pDispatch the IDispatch of an already running COM object or of an object loaded
      from a file. With only cProgId it attaches to the running instance registered for that ProgId
      (GetActiveObject); with only cFile the object comes from the file or moniker path (CoGetObject);
      with both, a new cProgId object is created and told to load cFile through IPersistFile.
    | params:
    - `cFile` Character - File or moniker path as an OLE (wide) string; NIL to attach to a running
      object.
    - `cProgId` Character - ProgId or "{...}" CLSID as an OLE string; NIL to use cFile alone.
    - `pDispatch` Numeric - Output, by reference; receives the IDispatch pointer.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_GETOBJECT          ){ disphelper(pl, (DWORD) dhGetObject          ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_createobjectex
            | syntax_: `_dh_createobjectex( cProgId, pIID, nClsContext, pServerInfo, @pInterface ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, CreateObject, class factory, CLSCTX, IDispatch, disphelper
   }}*/
/*{{|desc: Extended object creation: resolves cProgId - or a "{...}" CLSID string - to a class id, gets
      the class factory with CoGetClassObject in the requested class context and returns the interface
      selected by pIID in pInterface.
    | params:
    - `cProgId` Character - ProgId or "{...}" CLSID as an OLE (wide) string.
    - `pIID` Numeric/Character - Pointer to the IID of the requested interface; a 16-byte binary
      Character holding the IID also works, since Characters are passed as buffer pointers.
    - `nClsContext` Numeric - CLSCTX_* mask passed to CoGetClassObject.
    - `pServerInfo` Numeric - Pointer to a COSERVERINFO structure for a remote server, or NIL/0.
    - `pInterface` Numeric - Output, by reference; receives the requested interface pointer.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_CREATEOBJECTEX     ){ disphelper(pl, (DWORD) dhCreateObjectEx     ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_getobjectex
            | syntax_: `_dh_getobjectex( cFile, cProgId, pIID, nClsContext, pReserved, @pInterface ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, GetObject, running instance, IDispatch, disphelper
   }}*/
/*{{|desc: Extended form of _dh_getobject(): attaches to the running cProgId instance, or resolves an
      object from a file or moniker path, returning the interface selected by pIID instead of IDispatch.
    | params:
    - `cFile` Character - File or moniker path as an OLE (wide) string; NIL to attach to a running
      object.
    - `cProgId` Character - ProgId or "{...}" CLSID as an OLE string; NIL to use cFile alone.
    - `pIID` Numeric/Character - Pointer to the IID of the requested interface.
    - `nClsContext` Numeric - CLSCTX_* mask; only used when cFile and cProgId are both given (the
      object is then created just to load the file).
    - `pReserved` Numeric - Reserved; pass NIL or 0, anything else fails with E_INVALIDARG.
    - `pInterface` Numeric - Output, by reference; receives the requested interface pointer.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_GETOBJECTEX        ){ disphelper(pl, (DWORD) dhGetObjectEx        ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_callmethod
            | syntax_: `_dh_callmethod( pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, call method, IDispatch, Invoke, disphelper, automation
   }}*/
/*{{|desc: Invokes a method on a COM object through IDispatch. cMember is the method name or a dotted
      member path whose format identifiers describe the extra arguments, e.g. "Documents.Open(%S)"; the
      path is walked object by object and the final member is invoked as a method.
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Method name or member path with format identifiers, as an OLE (wide)
      string.
    - `...` Any - One value per format identifier in cMember, in order; numerics pass as 32-bit
      values, Characters as buffer pointers; pass NIL followed by the number for the 8-byte double of
      %e or %D.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_CALLMETHOD         ){ disphelper(pl, (DWORD) dhCallMethod         ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_putvalue
            | syntax_: `_dh_putvalue( pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, set property, property put, IDispatch, disphelper
   }}*/
/*{{|desc: Sets a property of a COM object through IDispatch (a property put). cMember is the property
      name or a dotted member path; the new value - and any index of the path - is supplied through
      format identifiers, e.g. "Visible(%b)" or "Cells(%d,%d).Value(%S)".
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property name or member path with format identifiers, as an OLE (wide)
      string; the last identifier carries the value to store.
    - `...` Any - One value per format identifier in cMember, in order; numerics pass as 32-bit
      values, Characters as buffer pointers; pass NIL followed by the number for the 8-byte double of
      %e or %D.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_PUTVALUE           ){ disphelper(pl, (DWORD) dhPutValue           ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_putref
            | syntax_: `_dh_putref( pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, put by reference, property putref, IDispatch, disphelper
   }}*/
/*{{|desc: Sets a property of a COM object through IDispatch as a put-by-reference, the flavor used
      for object-valued properties: the property stores the reference itself instead of a converted
      copy. cMember and the arguments work as in a property put, the value typically given with %o.
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property name or member path with format identifiers, as an OLE (wide)
      string; the last identifier carries the reference to store.
    - `...` Any - One value per format identifier in cMember, in order; numerics pass as 32-bit
      values, Characters as buffer pointers; pass NIL followed by the number for the 8-byte double of
      %e or %D.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_PUTREF             ){ disphelper(pl, (DWORD) dhPutRef             ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_getvalue
            | syntax_: `_dh_getvalue( cIdentifier, @xResult, pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, get property, property get, IDispatch, disphelper, convert
   }}*/
/*{{|desc: Reads a property or calls a method and stores the result, converted to the C type selected
      by cIdentifier, into xResult. cMember is the property or method name or a dotted member path with
      format identifiers for its arguments.
    | params:
    - `cIdentifier` Character - Single result-type identifier as an OLE (wide) string, e.g. "%d",
      "%e", "%S", "%o"; the leading % may be omitted.
    - `xResult` Any - Output, by reference; its storage must match cIdentifier: a Numeric for the
      32-bit results of %d, %u, %o, %O and %p; NIL followed by a Numeric for the 8-byte double of %e
      and %D; a writable buffer (or pointer) for %v (16-byte VARIANT), %W (SYSTEMTIME) and %f
      (FILETIME); the string identifiers %B, %S, %s and %T store a string pointer the caller must free.
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property or method name, or member path, as an OLE string.
    - `...` Any - One value per format identifier in cMember, in order.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_GETVALUE           ){ disphelper(pl, (DWORD) dhGetValue           ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_invoke
            | syntax_: `_dh_invoke( nInvokeType, nReturnType, pVarResult, pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, Invoke, DISPATCH flags, IDispatch, disphelper
   }}*/
/*{{|desc: Generic IDispatch invocation: issues cMember with the DISPATCH_* invoke type given in
      nInvokeType and stores the result, coerced to the VARTYPE nReturnType, in the VARIANT pointed to
      by pVarResult.
    | params:
    - `nInvokeType` Numeric - DISPATCH_* invoke type mask (method, property get, put or put-ref).
    - `nReturnType` Numeric - VARTYPE the result is coerced to; 0 (VT_EMPTY) keeps it as returned.
    - `pVarResult` Numeric - Pointer to a VARIANT receiving the result, or NIL/0 for none.
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Member name or dotted member path with format identifiers, as an OLE
      (wide) string.
    - `...` Any - One value per format identifier in cMember, in order; numerics pass as 32-bit
      values, Characters as buffer pointers; pass NIL followed by the number for the 8-byte double of
      %e or %D.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_INVOKE             ){ disphelper(pl, (DWORD) dhInvoke             ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_invokearray
            | syntax_: `_dh_invokearray( nInvokeType, pVarResult, nArgs, pDispatch, cMember, pVarArgs ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, Invoke, VARIANT array, IDispatch, disphelper
   }}*/
/*{{|desc: Generic IDispatch invocation taking a ready-made VARIANT argument array instead of format
      identifiers. cMember is a plain member name (no path, no identifiers) resolved with GetIDsOfNames;
      property put invoke types get the DISPID_PROPERTYPUT named argument set automatically.
    | params:
    - `nInvokeType` Numeric - DISPATCH_* invoke type mask.
    - `pVarResult` Numeric - Pointer to a VARIANT receiving the raw result, or NIL/0 for none.
    - `nArgs` Numeric - Number of VARIANTs in pVarArgs.
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Member name as an OLE (wide) string.
    - `pVarArgs` Numeric - Pointer to the array of nArgs VARIANTs, in the IDispatch calling
      convention order (last argument first).

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_INVOKEARRAY        ){ disphelper(pl, (DWORD) dhInvokeArray        ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_callmethodv
            | syntax_: `_dh_callmethodv( pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, call method, va_list, IDispatch, disphelper
   }}*/
/*{{|desc: Method invocation through IDispatch that takes the values for the format identifiers of
      cMember from a C va_list instead of the parameter list; mainly useful for C-level integration.
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Method name or member path with format identifiers, as an OLE (wide)
      string.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_CALLMETHODV        ){ disphelper(pl, (DWORD) dhCallMethodV        ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_putvaluev
            | syntax_: `_dh_putvaluev( pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, set property, va_list, IDispatch, disphelper
   }}*/
/*{{|desc: Property put through IDispatch that takes the values for the format identifiers of cMember
      from a C va_list instead of the parameter list; mainly useful for C-level integration.
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property name or member path with format identifiers, as an OLE (wide)
      string; the last identifier carries the value to store.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_PUTVALUEV          ){ disphelper(pl, (DWORD) dhPutValueV          ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_putrefv
            | syntax_: `_dh_putrefv( pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, put by reference, va_list, IDispatch, disphelper
   }}*/
/*{{|desc: Property put-by-reference through IDispatch that takes the values for the format identifiers
      of cMember from a C va_list instead of the parameter list; mainly useful for C-level integration.
    | params:
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property name or member path with format identifiers, as an OLE (wide)
      string; the last identifier carries the reference to store.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_PUTREFV            ){ disphelper(pl, (DWORD) dhPutRefV            ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_getvaluev
            | syntax_: `_dh_getvaluev( cIdentifier, pResult, pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, get property, va_list, IDispatch, disphelper
   }}*/
/*{{|desc: Property or method read that stores the result, converted to the C type selected by
      cIdentifier, at the address pResult, taking the values for the format identifiers of cMember from
      a C va_list; mainly useful for C-level integration.
    | params:
    - `cIdentifier` Character - Single result-type identifier as an OLE (wide) string, e.g. "%d";
      the leading % may be omitted.
    - `pResult` Numeric - Pointer to the result storage; its size must match cIdentifier.
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Property or method name, or member path, as an OLE string.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_GETVALUEV          ){ disphelper(pl, (DWORD) dhGetValueV          ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_invokev
            | syntax_: `_dh_invokev( nInvokeType, nReturnType, pVarResult, pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, Invoke, va_list, IDispatch, disphelper
   }}*/
/*{{|desc: Generic IDispatch invocation that takes the values for the format identifiers of cMember
      from a C va_list instead of the parameter list; mainly useful for C-level integration.
    | params:
    - `nInvokeType` Numeric - DISPATCH_* invoke type mask (method, property get, put or put-ref).
    - `nReturnType` Numeric - VARTYPE the result is coerced to; 0 (VT_EMPTY) keeps it as returned.
    - `pVarResult` Numeric - Pointer to a VARIANT receiving the result, or NIL/0 for none.
    - `pDispatch` Numeric - IDispatch pointer of the object.
    - `cMember` Character - Member name or dotted member path with format identifiers, as an OLE
      (wide) string.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_INVOKEV            ){ disphelper(pl, (DWORD) dhInvokeV            ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_enumbegin
            | syntax_: `_dh_enumbegin( @pEnum, pDispatch, cMember, ... ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, enumerate collection, IEnumVARIANT, for each, disphelper
   }}*/
/*{{|desc: Starts enumeration over a COM collection: reads the collection selected by cMember - or
      uses pDispatch itself when cMember is NIL - asks it for its standard enumerator and returns the
      IEnumVARIANT pointer in pEnum.
    | params:
    - `pEnum` Numeric - Output, by reference; receives the IEnumVARIANT pointer.
    - `pDispatch` Numeric - IDispatch pointer of the object holding the collection.
    - `cMember` Character - Collection member name or dotted path with format identifiers, as an
      OLE (wide) string; NIL to enumerate pDispatch itself.
    - `...` Any - One value per format identifier in cMember, in order.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_ENUMBEGIN          ){ disphelper(pl, (DWORD) dhEnumBegin          ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_enumbeginv
            | syntax_: `_dh_enumbeginv( @pEnum, pDispatch, cMember, pVaList ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, enumerate collection, va_list, IEnumVARIANT, disphelper
   }}*/
/*{{|desc: Starts enumeration over a COM collection, taking the values for the format identifiers of
      cMember from a C va_list instead of the parameter list; mainly useful for C-level integration.
    | params:
    - `pEnum` Numeric - Output, by reference; receives the IEnumVARIANT pointer.
    - `pDispatch` Numeric - IDispatch pointer of the object holding the collection.
    - `cMember` Character - Collection member name or dotted path with format identifiers, as an
      OLE (wide) string; NIL to enumerate pDispatch itself.
    - `pVaList` Numeric - Pointer to a C va_list holding the identifier values.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_ENUMBEGINV         ){ disphelper(pl, (DWORD) dhEnumBeginV         ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{include-note-id: dh-format-identifiers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_enumnextobject
            | syntax_: `_dh_enumnextobject( pEnum, @pDispatch ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, enumeration next, IDispatch item, for each, disphelper
   }}*/
/*{{|desc: Fetches the next item of an enumeration as an IDispatch pointer stored in pDispatch,
      converting the item to an object when it is not one already.
    | params:
    - `pEnum` Numeric - IEnumVARIANT pointer returned by an enum-begin function.
    - `pDispatch` Numeric - Output, by reference; receives the IDispatch pointer of the item.

    Returns Numeric - 0 (S_OK) means an item was delivered, 1 (S_FALSE) means the enumeration is
      exhausted; failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_ENUMNEXTOBJECT     ){ disphelper(pl, (DWORD) dhEnumNextObject     ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_enumnextvariant
            | syntax_: `_dh_enumnextvariant( pEnum, pVarResult ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, enumeration next, VARIANT item, for each, disphelper
   }}*/
/*{{|desc: Fetches the next item of an enumeration into the VARIANT pointed to by pVarResult, without
      converting it; clearing the received VARIANT is up to the caller.
    | params:
    - `pEnum` Numeric - IEnumVARIANT pointer returned by an enum-begin function.
    - `pVarResult` Numeric - Pointer to a VARIANT that receives the item.

    Returns Numeric - 0 (S_OK) means an item was delivered, 1 (S_FALSE) means the enumeration is
      exhausted; failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_ENUMNEXTVARIANT    ){ disphelper(pl, (DWORD) dhEnumNextVariant    ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dh_toggleexceptions
            | syntax_: `_dh_toggleexceptions( lShow ) -> nHRESULT`
            | category: interop/com
            | _kw_: COM, exceptions, error display, disphelper
   }}*/
/*{{|desc: Turns the DispHelper exception display on or off. The wrappers switch it off when they
      initialize, so COM errors are only reported through the returned HRESULTs; switching it on makes
      DispHelper describe each failure in a message box (and re-enables exception recording).
    | params:
    - `lShow` Logical - .T. shows DispHelper exceptions, .F. silences them.

    Returns Numeric - The HRESULT of the call; 0 is S_OK, failure codes read as negative numbers. }}*/
_XPP_REG_FUN_( _DH_TOGGLEEXCEPTIONS   ){ disphelper(pl, (DWORD) dhToggleExceptions   ); }
/*{{include-note-id: dh-wrappers}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
