//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
static DWORD _dwFpCallErrorFlags_ = 1;
static XppFuncType _pDllExecuteCall_ = (XppFuncType) GetProcAddress( GetModuleHandle( "xpprt1" ), "DLLEXECUTECALL" );
//----------------------------------------------------------------------------------------------------------------------
typedef struct _XPP_DLL_TEMPLATE__struct
{
   CHAR  szDll[ 4 ];
   DWORD hDll;
   DWORD fp;
   WORD  wMode;
   WORD  wDummy;
} _XPP_DLL_TEMPLATE_;
//----------------------------------------------------------------------------------------------------------------------
static DWORD _dwGetFpParam_( XppParamList pl, ULONG nPos );
static DWORD vtlbn2fp( LONG n, LONG v );
static DWORD pt_list_get_pointer( LONG n, LONG v );
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: _dwGetFpParam_
            | title_: How to provide the fp parameter
|note:
The fp parameter selects the function to call. It may be:
- a numeric function pointer, e.g. the result of nGetProcAddress();
- a character DLL-call template, the result of DllPrepareCall();
- a two-element array { cDllOrHandle, cProcNameOrOrdinal }: the module is a numeric handle, or a DLL name loaded
  with GetModuleHandle()/LoadLibrary(); the export is resolved with GetProcAddress() by name (character) or by
  ordinal (numeric, since ot4xb 1.8.0.1).
}}*/

static DWORD _dwGetFpParam_( XppParamList pl, ULONG nPos )
{
   DWORD dw = _partype( pl, nPos );
   if( dw & XPP_NUMERIC ) return (DWORD) _parLong( pl, nPos, 0 );
   else if( dw & XPP_CHARACTER )
   {
      _XPP_DLL_TEMPLATE_ tp;
      tp.fp = 0;
      _parc( (LPSTR) &tp, sizeof( _XPP_DLL_TEMPLATE_ ), pl, nPos );
      return tp.fp;
   }
   else if( dw & XPP_ARRAY )
   {
      if( _paralen( pl, nPos, 0 ) > 1 )
      {

         HMODULE hDll = (HMODULE) 0;
         CHAR sz[ 260 ];
         if( _paratype( pl, nPos, 1, 0 ) & XPP_NUMERIC ) hDll = (HMODULE) _parLong( pl, nPos, 1, 0 );
         else
         {
            _bset( (LPBYTE) sz, 0, 260 );
            if( _parc( sz, 260, pl, nPos, 1, 0 ) )
            {
               hDll = GetModuleHandle( sz );
               if( !hDll ) hDll = LoadLibrary( sz );
            }
         }
         if( hDll )
         {
            if( _paratype( pl, nPos, 2, 0 ) & XPP_NUMERIC )
            {
               return (DWORD) GetProcAddress( hDll, (LPCSTR) _parLong( pl, nPos, 2, 0 ) );
            }
            _bset( (LPBYTE) sz, 0, 260 );
            if( _parc( sz, 260, pl, nPos, 2, 0 ) )
            {
               return (DWORD) GetProcAddress( hDll, sz );
            }
         }

      }
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
/*{{function_: Set_FpCall_Flags
            | syntax_: `Set_FpCall_Flags( [nFlags] ) -> nOldFlags`
            | category: function-pointer
            | desc: Reads and optionally replaces the global fpCall error-handling flags, returning the previous
                value. When nFlags is numeric it becomes the new flag mask; when omitted the current value is only
                read. Bit 1 makes fpCall functions raise an Xbase++ runtime error (TXbGenError) when the target
                function pointer cannot be resolved (the function is not found) instead of failing silently.
            | params:
              - `nFlags` Numeric - New flag mask; omit to read the current value without changing it.
            | flags:
              - `0x01` Raise an Xbase++ error when the target function cannot be resolved (not found) instead of
                failing silently.

              Returns Numeric - The flag mask that was in effect before the call.

            | note: This flag only governs the not-found case. fpCall does not validate the calling convention,
                argument layout or the pointer itself; a wrong prototype or an invalid pointer can crash the process
                regardless of this flag.
   | _kw_: fpCall, flags, error handling, function pointer call
   }}*/
XPPRET XPPENTRY SET_FPCALL_FLAGS( XppParamList pl )
{
   DWORD dw = _dwFpCallErrorFlags_;
   if( _partype( pl, 1 ) & XPP_NUMERIC ) _dwFpCallErrorFlags_ = (DWORD) _parLong( pl, 1, 0 );
   _retnl( pl, (LONG) dw );
}

// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nFpGet
            | syntax_: `nFpGet( fp ) -> pFunction`
            | category: function-pointer
            | _kw_: function pointer, resolve, GetProcAddress, dll function, address
   }}*/
/*{{|desc: Resolves a function-pointer specification (fp, see the note below) to a numeric function
      pointer, or 0 when it cannot be resolved. This is the Xbase++ face of the internal fp resolver; it
      only resolves the pointer, it does not call it.
    | params:
    - `fp` Numeric/Character/Array - The function-pointer specification; see the note below.

    Returns Numeric - The resolved function pointer, or 0 when it cannot be resolved.

    |note: Typical use is to pre-resolve a pointer once (e.g. into a static or local) ahead of a very hot
      loop, so the loop passes the already-resolved numeric pointer and skips re-resolving fp on every
      call; the speed gain is small.

    |seealso: See also: {{ilink: <function nGetProcAddress> nGetProcAddress}}, {{ilink: <function nFpCall> nFpCall}} }}*/
XPPRET XPPENTRY NFPGET( XppParamList pl )
{
   LONG nfp = (LONG) _dwGetFpParam_( pl, 1 );
   _retnl( pl, nfp );
}
/*{{include-note-id: _dwGetFpParam_}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: F2T
            | syntax_: `F2T( pFunction [, nCallingConvention] ) -> cDllTemplate`
            | category: function-pointer
            | _kw_: template, DllPrepareCall, function pointer, prototype
   }}*/
/*{{|desc: Builds a template string similar to the one created by DllPrepareCall(), wrapping the numeric
      function pointer pFunction and targeting the current module (GetModuleHandle(0)). Its only real use is
      to feed DllExecuteCall(): it offers no advantage to the ot4xb function-pointer call functions (nFpCall,
      ndFpCall, ...), which take a resolved pointer directly. The returned string is a two-slot
      _XPP_DLL_TEMPLATE_ array, the second slot left zeroed as a terminator.
    | params:
    - `pFunction` Numeric - Function pointer, assumed to belong to the current module.
    - `nCallingConvention` Numeric - Optional calling convention stored in the template (its wMode
      field); default 0. See the note below. It only matters when the template is used with DllExecuteCall();
      the ot4xb fpCall functions ignore it.

    Returns Character - The template string wrapping pFunction.

    |note: The nCallingConvention parameter was added in ot4xb 1.8.0.1.

    |seealso: See also: DllExecuteCall, {{ilink: <function XbFpCall> XbFpCall}} }}*/
XPPRET XPPENTRY F2T( XppParamList pl )
{
   _XPP_DLL_TEMPLATE_ tp[ 2 ];
   ZeroMemory( tp, sizeof( tp ) );
   _bcopy( (LPBYTE) tp[ 0 ].szDll, (LPBYTE) "_DLL", 4 );
   tp[ 0 ].hDll = (DWORD) GetModuleHandle( 0 );
   tp[ 0 ].fp = (DWORD) _parLong( pl, 1 );
   tp[ 0 ].wMode = 1 | ( _parLong( pl, 2, 0 ) & 0xFFFF );
   tp[ 0 ].wDummy = 0;
   _retclen( pl, (LPSTR) tp, sizeof( tp ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: next_xbfpcall_use_critical_section
            | syntax_: `void next_xbfpcall_use_critical_section( CRITICAL_SECTION * pCriticalSection )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: next_xbfpcall_use_critical_section
            | _kw_: XbFpCall, synchronized, critical section, SYNC
   }}*/
/*{{|desc: Building block for a synchronized (SYNC) XbFpCall. The function itself only passes a
      CRITICAL_SECTION pointer to the next XbFpCall on this thread, like a piece of cargo: it stores
      pCriticalSection in a per-thread TLS slot and does nothing else. Only XbFpCall reads and consumes
      the slot (see XbFpCall); the other fpCall functions ignore it.
    | params:
    - `pCriticalSection` CRITICAL_SECTION * - Critical section for the next call, or NULL to clear the
      slot.

    Returns void

    |note: The guard applies to a single XbFpCall and nothing is automatic: set it before each call you
      want to guard. The application owns the CRITICAL_SECTION and must initialize and destroy it. As with
      all synchronization, use this only if you know what you are doing.

    |note: Called from Xbase++ with the ot4xb DLL-export syntax:
      @ot4xb:next_xbfpcall_use_critical_section( pCs )

    |seealso: See also: {{ilink: <function XbFpCall> XbFpCall}} }}*/
OT4XB_API void next_xbfpcall_use_critical_section( CRITICAL_SECTION* pcs )
{
   GetTlsHeapManager()->m_next_call_critical_section = pcs;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: XbFpCall
            | syntax_: `XbFpCall( pFunction, ... ) -> xResult`
            | category: function-pointer
            | _kw_: call function pointer, XPPENTRY, Xbase++ function pointer, forward arguments
   }}*/
/*{{|desc: Calls pFunction - a pointer to an Xbase++-prototyped (XPPENTRY) function - forwarding the
      remaining arguments to it and returning whatever it returns. Unlike nFpCall/ndFpCall (which call C
      stdcall/cdecl functions), XbFpCall targets a function that uses the Xbase++ calling prototype.
    | params:
    - `pFunction` Numeric - Pointer to an Xbase++-prototyped (XPPENTRY) function.
    - `...` Any - Arguments forwarded to the called function.

    Returns The value returned by the called function.

    |note: Typical use is to expose a C++ function that has an Xbase++ prototype - even a non-exported one
      living inside a namespace - as an Xbase++ method or code block, by embedding its pointer, without
      registering it as a global function.

    |note: If next_xbfpcall_use_critical_section() armed a CRITICAL_SECTION on this thread, XbFpCall
      consumes it (one-shot): it clears the slot and runs the call inside EnterCriticalSection within a
      __try, with a __finally that guarantees LeaveCriticalSection even if the call raises - a synchronized
      (SYNC) call for functions that are not thread-safe.

    |example: 
      ```
       pc->ClassMethod_cbbs( "rc4_decrypt", 
           "{|s,encr,flags| XbFpCall(%i,encr,flags) }",
           ot4xb_cng_ns::rc4_encrypt_decrypt );
      ```

    |seealso: See also: {{ilink: <c-function next_xbfpcall_use_critical_section> next_xbfpcall_use_critical_section}}, {{ilink: <function nFpGet> nFpGet}} }}*/
XPPRET XPPENTRY XBFPCALL( XppParamList pl )
{

   _XPP_DLL_TEMPLATE_ tp[ 4 ];
   ZeroMemory( tp, sizeof( tp ) );
   _bcopy( (LPBYTE) tp[ 0 ].szDll, (LPBYTE) "_DLL", 4 );
   tp[ 0 ].hDll = (DWORD) GetModuleHandle( 0 );
   tp[ 0 ].fp = (DWORD) _parLong( pl, 1 );
   tp[ 0 ].wMode = 1;
   tp[ 0 ].wDummy = 0;
   _storclen( (LPSTR) tp, sizeof( tp ), pl, 1, 0 );
   CRITICAL_SECTION* pcs = GetTlsHeapManager()->m_next_call_critical_section;
   GetTlsHeapManager()->m_next_call_critical_section = 0;
   __try
   {
      if( pcs ) { EnterCriticalSection( pcs ); }
      ( *_pDllExecuteCall_ )( pl );
   }
   __finally
   {
      if( pcs ) { LeaveCriticalSection( pcs ); }
   }


}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _FpCall_PushFlags_
            | syntax_: `_FpCall_PushFlags_( nFlags ) -> NIL`
            | category: function-pointer
            | _kw_: fpCall, flags, next call, one-shot, TLS
   }}*/
/*{{|desc: Sets flags that apply only to the next fpCall on the current thread. The value is stored in a
      one-shot per-thread TLS slot that the next call reads and clears, so it affects a single call and
      then resets. Currently only bit 1 is defined.
    | params:
    - `nFlags` Numeric - Flag mask for the next call.
    | flags:
    - `0x01` Disable by-reference parameter conversion for the next call.

    Returns NIL

    |note: The guard is one-shot and nothing is automatic: set it right before the fpCall you want to
      affect. It is consumed by nFpCall / ndFpCall / qwFpCall (and disphelper), not by XbFpCall.

    |seealso: See also: {{ilink: <function Set_FpCall_Flags> Set_FpCall_Flags}}, {{ilink: <function nFpCall> nFpCall}} }}*/
XPPRET XPPENTRY _FPCALL_PUSHFLAGS_( XppParamList pl ) { GetTlsHeapManager()->PushNextFpFlags( (DWORD) _parLong( pl, 1, 0 ) ); _ret( pl ); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nFpCall
            | syntax_: `nFpCall( fp, params... ) -> n32BitResult`
            | category: function-pointer
            | _kw_: call function pointer, stdcall, cdecl, dll call, EAX, DllCall
   }}*/
/*{{|desc: Calls an stdcall or cdecl function through a function pointer and returns the 32-bit result
      (the EAX register) as a number.
    | params:
    - `fp` Numeric/Character/Array - The function to call; see the notes below.
    - `params` Any - Arguments; converted from their Xbase++ types (see the notes below).

    Returns Numeric - The 32-bit return value taken from EAX.

    |note: If the called function returns a 32-bit float, convert the result with UnPackFloat32().

    |seealso: See also: {{ilink: <function nFpGet> nFpGet}}, {{ilink: <function ndFpCall> ndFpCall}}, {{ilink: <function qwFpCall> qwFpCall}}, {{ilink: <function Set_FpCall_Flags> Set_FpCall_Flags}}, {{ilink: <function _FpCall_PushFlags_> _FpCall_PushFlags_}}, {{ilink: <function nFpGetLastError> nFpGetLastError}}

    |note: The `@dll:function( ... )` shorthand of ot4xb.ch expands to a call to this function; see
      {{ilink: <topic quick_call_dll_functions> quick_call_dll_functions}}. }}*/
XPPRET XPPENTRY NFPCALL( XppParamList pl )
{
   LONG nParams, n;
   DWORD dwFPtr = _dwGetFpParam_( pl, 1 );
   BOOL bDisableByRef = (BOOL) ( GetTlsHeapManager()->PopNextFpFlags() & 1 );
   if( dwFPtr )
   {
      TXbFpParam* pParams = TXbFpParam::InitList( pl, 2, &nParams, bDisableByRef );
      LONG spt;
      LONG nl;

      TXbFpParam::PrepareStackValues( pParams );

      _asm mov spt, esp; // Save the stack before      
      for( n = nParams - 1; n >= 0; n-- )
      {
         if( pParams[ n ].m_nSplit < 3 )
         {
            DWORD dw = pParams[ n ].m_dwStackVal;
            _asm mov eax, dw;
            _asm push eax;
         }
      }
      _asm mov eax, dwFPtr;
      _asm call eax;
      _asm mov nl, eax; // get the result      
      _asm mov esp, spt;  // restore the stack      

      GetTlsHeapManager()->PutLastError( GetLastError() );
      TXbFpParam::ReleaseAll( pParams );
      _retnl( pl, nl );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret( pl );
   }
}
/*{{include-note-id: _dwGetFpParam_}}*/
/*{{include-note-id: fp-np-call}}*/
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ndFpCall
            | syntax_: `ndFpCall( fp, params... ) -> n64BitFloatResult`
            | category: function-pointer
            | _kw_: call function pointer, double result, stdcall, cdecl, dll call
   }}*/
/*{{|desc: Calls an stdcall or cdecl function that returns a 64-bit floating-point value and returns it
      as a number. Same as nFpCall except the result is taken from the FPU (ST0) instead of EAX.
    | params:
    - `fp` Numeric/Character/Array - The function to call; see the notes below.
    - `params` Any - Arguments; converted from their Xbase++ types (see the notes below).

    Returns Numeric - The 64-bit floating-point (double) return value taken from the FPU (ST0).

    |seealso: See also: {{ilink: <function nFpCall> nFpCall}}, {{ilink: <function qwFpCall> qwFpCall}}, {{ilink: <function nFpGet> nFpGet}}, {{ilink: <function Set_FpCall_Flags> Set_FpCall_Flags}}, {{ilink: <function nFpGetLastError> nFpGetLastError}} }}*/
XPPRET XPPENTRY NDFPCALL( XppParamList pl )
{
   LONG nParams, n;
   DWORD dwFPtr = _dwGetFpParam_( pl, 1 );
   BOOL bDisableByRef = (BOOL) ( GetTlsHeapManager()->PopNextFpFlags() & 1 );
   if( dwFPtr )
   {
      TXbFpParam* pParams = TXbFpParam::InitList( pl, 2, &nParams, bDisableByRef );
      LONG spt;
      double nd;

      TXbFpParam::PrepareStackValues( pParams );

      _asm mov spt, esp; // Save the stack before            
      for( n = nParams - 1; n >= 0; n-- )
      {
         if( pParams[ n ].m_nSplit < 3 )
         {
            DWORD dw = pParams[ n ].m_dwStackVal;
            _asm mov eax, dw;
            _asm push eax;
         }
      }
      _asm mov eax, dwFPtr;
      _asm call eax;
      _asm fstp qword ptr nd;
      _asm mov esp, spt;  // restore the stack            
      GetTlsHeapManager()->PutLastError( GetLastError() );
      TXbFpParam::ReleaseAll( pParams );
      _retnd( pl, nd );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret( pl );
   }
}
/*{{include-note-id: _dwGetFpParam_}}*/
/*{{include-note-id: fp-np-call}}*/
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: qwFpCall
            | syntax_: `qwFpCall( fp, params... ) -> n64BitInt`
            | category: function-pointer
            | _kw_: call function pointer, 64-bit result, QWORD, stdcall, cdecl
   }}*/
/*{{|desc: Calls an stdcall or cdecl function that returns a 64-bit integer and returns the raw 8-byte
      value as a character string. Same as nFpCall except the result is taken from the EDX:EAX register
      pair (EAX in bytes 0-3, EDX in bytes 4-7).
    | params:
    - `fp` Numeric/Character/Array - The function to call; see the notes below.
    - `params` Any - Arguments; converted from their Xbase++ types (see the notes below).

    Returns Character - The raw 8-byte (QWORD) value from EDX:EAX.

    |seealso: See also: {{ilink: <function nFpCall> nFpCall}}, {{ilink: <function ndFpCall> ndFpCall}}, {{ilink: <function nFpGet> nFpGet}}, {{ilink: <function Set_FpCall_Flags> Set_FpCall_Flags}}, {{ilink: <function nFpGetLastError> nFpGetLastError}} }}*/
XPPRET XPPENTRY QWFPCALL( XppParamList pl )
{
   LONG nParams, n;
   DWORD dwFPtr = _dwGetFpParam_( pl, 1 );
   BOOL bDisableByRef = (BOOL) ( GetTlsHeapManager()->PopNextFpFlags() & 1 );
   if( dwFPtr )
   {
      TXbFpParam* pParams = TXbFpParam::InitList( pl, 2, &nParams, bDisableByRef );
      LONG spt;
      char  sz[ 8 ];
      TXbFpParam::PrepareStackValues( pParams );

      _asm mov spt, esp; // Save the stack before      
      for( n = nParams - 1; n >= 0; n-- )
      {
         if( pParams[ n ].m_nSplit < 3 )
         {
            DWORD dw = pParams[ n ].m_dwStackVal;
            _asm mov eax, dw;
            _asm push eax;
         }
      }
      _asm mov eax, dwFPtr;
      _asm call eax;
      _asm mov dword ptr sz[ 0 ], eax;
      _asm mov dword ptr sz[ 4 ], edx;
      _asm mov esp, spt;  // restore the stack            
      GetTlsHeapManager()->PutLastError( GetLastError() );
      TXbFpParam::ReleaseAll( pParams );
      _retclen( pl, sz, 8 );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret( pl );
   }
}
/*{{include-note-id: _dwGetFpParam_}}*/
/*{{include-note-id: fp-np-call}}*/
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_GetFpLastError
            | syntax_: `DWORD ot4xb_GetFpLastError( void )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_GetFpLastError
            | _kw_: GetLastError, fpCall, last error, TLS
   }}*/
/*{{|desc: Returns the Win32 GetLastError() value that the most recent fpCall on this thread saved in the
      TLS heap manager. C primitive behind nFpGetLastError().

    Returns DWORD - The saved last-error code. }}*/
OT4XB_API DWORD __cdecl ot4xb_GetFpLastError( void ) { return GetTlsHeapManager()->GetLastError(); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_PutFpLastError
            | syntax_: `void ot4xb_PutFpLastError( DWORD dw )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_PutFpLastError
            | _kw_: SetLastError, fpCall, last error, TLS
   }}*/
/*{{|desc: Stores dw as the fpCall last-error value in the TLS heap manager for the current thread.
    | params:
    - `dw` DWORD - The last-error code to store.

    Returns void }}*/
OT4XB_API void  __cdecl ot4xb_PutFpLastError( DWORD dw ) { GetTlsHeapManager()->PutLastError( dw ); }
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nFpGetLastError
            | syntax_: `nFpGetLastError() -> nLastError`
            | category: function-pointer
            | _kw_: GetLastError, last error, fpCall, win32 error
   }}*/
/*{{|desc: Returns the Win32 GetLastError() value saved by the most recent fpCall on the current thread.

    Returns Numeric - The saved last-error code.

    |seealso: See also: {{ilink: <function nFpCall> nFpCall}}, {{ilink: <c-function ot4xb_GetFpLastError> ot4xb_GetFpLastError}} }}*/
XPPRET XPPENTRY NFPGETLASTERROR( XppParamList pl ) { _retnl( pl, (LONG) GetTlsHeapManager()->GetLastError() ); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: QFpGetLastPointer
            | syntax_: `QFpGetLastPointer() -> pPointer`
            | category: function-pointer
            | _kw_: FpQCall, last pointer, out parameter, TLS
   }}*/
/*{{|desc: Returns the last pointer value for the last FpQCall() on this thread. See the notes below.

    Returns Numeric - The stored last-pointer value.

    |seealso: See also: {{ilink: <function QFpSetLastPointer> QFpSetLastPointer}} }}*/
XPPRET XPPENTRY QFPGETLASTPOINTER( XppParamList pl ) { _retnl( pl, (LONG) GetTlsHeapManager()->GetLastPointer() ); }
/*{{include-note-id: qfp-last-pointer}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: QFpSetLastPointer
            | syntax_: `QFpSetLastPointer( pPointer ) -> NIL`
            | category: function-pointer
            | _kw_: FpQCall, last pointer, override, TLS
   }}*/
/*{{|desc: The QFpSetLastPointer() only exist
      to override the  slot, but cannot think now in a good reason to do it.
    | params:
    - `pPointer` Numeric - The pointer value to store.

    Returns NIL

    |seealso: See also: {{ilink: <function QFpGetLastPointer> QFpGetLastPointer}} }}*/
XPPRET XPPENTRY QFPSETLASTPOINTER( XppParamList pl ) { GetTlsHeapManager()->PutLastPointer( (DWORD) _parLong( pl, 1 ) ); _ret( pl ); }
/*{{include-note-id: qfp-last-pointer}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{ note-id: qfp-last-pointer
               | note: The "last pointer" is a thread-local value that FpQCall() stores when the return value is 
                 automatically converted from LPSTR or LPWSTR to an Xbase++ Character value. This automatic
                 conversion may prevent the pointer returned by the called function properly released. To avoid 
                 a memory leak the application is responsible to release the pointer properly according to 
                 the nature of that pointer. The prg level function QFpGetLastPointer() must be used inmediatly 
                 after the FpQCall() to store the pointer in the proper place. 
                 }}*/

// ----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nGetProcAddress
            | syntax_: `nGetProcAddress( hDllOrName, cProcNameOrOrdinal ) -> pFunction`
            | category: function-pointer
            | _kw_: GetProcAddress, dll export, function address, function pointer
   }}*/
/*{{|desc: Returns the address of a DLL export as a numeric function pointer. The module is taken from a
      numeric handle, or from GetModuleHandle()/LoadLibrary() when a name is given. The export is resolved
      with GetProcAddress() by name (character) or by ordinal (numeric). Returns 0 when it cannot be
      resolved.
    | params:
    - `hDllOrName` Numeric/Character - Module handle, or a DLL name that is loaded if not already
      loaded.
    - `cProcNameOrOrdinal` Character/Numeric - Export name, or an ordinal number.

    Returns Numeric - The resolved export address, or 0.

    |seealso: See also: {{ilink: <function nLoadLibrary> nLoadLibrary}}, {{ilink: <function nFpGet> nFpGet}}, {{ilink: <function nFpCall> nFpCall}} }}*/
XPPRET XPPENTRY NGETPROCADDRESS( XppParamList pl )
{
   CHAR sz[ 260 ];
   HMODULE  hDll = (HMODULE) 0;
   LONG     nFp = 0;

   switch( _partype( pl, 1 ) & 0xFF )
   {
      case XPP_CHARACTER:
      {
         if( _parc( sz, 260, pl, 1 ) )
         {
            hDll = GetModuleHandle( sz );
            if( !hDll ) hDll = LoadLibrary( sz );
         }
         break;
      }
      case XPP_NUMERIC:
      {
         hDll = (HMODULE) _parLong( pl, 1 );
         break;
      }
   }
   if( hDll )
   {
      switch( _partype( pl, 2 ) & 0xFF )
      {
         case XPP_CHARACTER:
         {
            if( _parc( sz, 260, pl, 2 ) ) nFp = (LONG) GetProcAddress( hDll, sz );
            break;
         }
         case XPP_NUMERIC:
         {
            nFp = (LONG) GetProcAddress( hDll, (LPSTR) _parLong( pl, 2 ) );
            break;
         }
      }
   }
   _retnl( pl, nFp );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: load-unload-dll
             | title_: Loading and unloading DLLs
|note:
nLoadLibrary() called several times just increases the DLL's reference counter, and lFreeLibrary() just
decreases it; the DLL is unloaded when the counter reaches zero. Once a DLL is loaded it makes no difference
whether it was loaded dynamically, statically linked to the program, or the code lives in the executable itself.

A common belief is that freeing a DLL as soon as possible after using it minimizes memory use, and sometimes it
does. But some DLLs are needed by the Xbase++ runtime itself - kernel32.dll, user32.dll, advapi32.dll, mpr.dll,
version.dll and winspool.drv - so do not even bother unloading them; it does nothing.

Other times a clean unload is hard: leftovers that cannot be freed may remain, and loading and unloading the
same DLL repeatedly ends up consuming all the memory - the exact opposite of the intended effect.

Another belief, this time always false, is that what happens in a DLL stays in the DLL. The container is the
process: memory and resources are only freed when the process ends, not when the DLL is unloaded - the only
guarantee they are released is the process ending.

So unload a DLL only when its use is clear, you are sure it leaves no residue, and the cost of re-initializing
it (often not the DLL's size but the environment it sets up) is worth paying. Otherwise, just leave it loaded.
}}*/

// ----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: nLoadLibrary
            | syntax_: `nLoadLibrary( cDllName [, @nLastError] ) -> hDll`
            | category: function-pointer
            | _kw_: LoadLibrary, load dll, module handle
   }}*/
/*{{|desc: Loads a DLL with LoadLibrary() and returns its module handle, or 0 on failure. When loading
      fails, the optional nLastError argument receives the Win32 GetLastError() code.
    | params:
    - `cDllName` Character - Name of the DLL to load.
    - `nLastError` Numeric by reference - Receives GetLastError() when loading fails; 0 otherwise.

    Returns Numeric - The module handle, or 0 on failure.

    |seealso: See also: {{ilink: <function lFreeLibrary> lFreeLibrary}}, {{ilink: <function nGetProcAddress> nGetProcAddress}} }}*/
XPPRET XPPENTRY NLOADLIBRARY( XppParamList pl )
{
   LPSTR    pName = _pszParam( pl, 1 );
   HMODULE  hDll = 0;
   DWORD  nLastError = 0;
   if( pName )
   {
      hDll = LoadLibrary( pName );
      if( !hDll )
      {
         nLastError = GetLastError();
      }
      _xfree( pName );
   }
   _stornl( (LONG) nLastError, pl, 2, 0 );
   _retnl( pl, (LONG) hDll );
}
/*{{include-note-id: load-unload-dll}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lFreeLibrary
            | syntax_: `lFreeLibrary( hDll ) -> lOk`
            | category: function-pointer
            | _kw_: FreeLibrary, unload dll, module handle
   }}*/
/*{{|desc: Releases a module handle with FreeLibrary(). Returns the result of FreeLibrary() (.T. on
      success), or .F. when hDll is zero.
    | params:
    - `hDll` Numeric - Module handle returned by nLoadLibrary or nGetProcAddress.

    Returns Logical - .T. on success, .F. otherwise.

    |seealso: See also: {{ilink: <function nLoadLibrary> nLoadLibrary}} }}*/
XPPRET XPPENTRY LFREELIBRARY( XppParamList pl )
{
   HMODULE  hDll = (HMODULE) _parLong( pl, 1 );
   BOOL     bResult = FALSE;
   if( hDll )   bResult = FreeLibrary( hDll );
   _retl( pl, bResult );
}
/*{{include-note-id: load-unload-dll}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-----------------------------------------------------------------------------------------------------------------------
static DWORD _format_msg_( DWORD dwf, void* ps, DWORD id, DWORD lan, LPSTR pb, DWORD cb, ... )
{
   DWORD result;
   va_list args; va_start( args, cb );
   result = FormatMessage( dwf, ps, id, lan, pb, cb, &args );
   va_end( args );
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cFmtSysMsg
            | syntax_: `cFmtSysMsg( nMessageId [, nLangId] ) -> cMessage`
            | category: messages
            | _kw_: FormatMessage, system error message, error text, GetLastError
   }}*/
/*{{|desc: Formats a Win32 system message with FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM) and returns it.
      Inserts are ignored (FORMAT_MESSAGE_IGNORE_INSERTS). Returns an empty string when it cannot be
      formatted.
    | params:
    - `nMessageId` Numeric - System message identifier (e.g. a GetLastError code).
    - `nLangId` Numeric - Language identifier (low 16 bits); optional.

    Returns Character - The formatted system message, or "" on failure.

    |seealso: See also: {{ilink: <function cFmtResMsg> cFmtResMsg}}, {{ilink: <function cFmtStrMsg> cFmtStrMsg}} }}*/
XPPRET XPPENTRY CFMTSYSMSG( XppParamList pl )
{
   LPSTR pBuffer = 0;
   DWORD dw = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                             FORMAT_MESSAGE_FROM_SYSTEM |
                             FORMAT_MESSAGE_IGNORE_INSERTS,
                             NULL, (DWORD) _parLong( pl, 1, 0 ),
                             (DWORD) _parLong( pl, 2, 0 ) & 0xFFFF,
                             (LPTSTR) &pBuffer, 0, NULL );
   if( dw && pBuffer ) _retclen( pl, pBuffer, dw );
   else _retc( pl, "" );
   if( pBuffer ) LocalFree( pBuffer );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cFmtResMsg
            | syntax_: `cFmtResMsg( hDll, nMessageId [, nLangId], ... ) -> cMessage`
            | category: msg-string
            | _kw_: FormatMessage, message resource, module message, error text
   }}*/
/*{{|desc: Formats a message resource from a module with FormatMessage(FORMAT_MESSAGE_FROM_HMODULE) and
      returns it. When hDll is NIL or 0 the current executable module is used. The extra arguments are
      passed as message inserts. Returns an empty string when it cannot be formatted.
    | params:
    - `hDll` Numeric - Module handle holding the message table; NIL or 0 uses the current .exe.
    - `nMessageId` Numeric - Message identifier in the module message table.
    - `nLangId` Numeric - Language identifier; optional.
    - `...` Any - Insert arguments for the message.

    Returns Character - The formatted message, or "" on failure.

    |seealso: See also: {{ilink: <function cFmtSysMsg> cFmtSysMsg}}, {{ilink: <function cFmtStrMsg> cFmtStrMsg}} }}*/
XPPRET XPPENTRY CFMTRESMSG( XppParamList pl )
{
   LONG nParams, n;
   TXbFpParam* pParams = TXbFpParam::InitList( pl, 4, &nParams, TRUE );
   LONG sp1;
   DWORD dw;
   LPSTR pBuffer = 0;


   TXbFpParam::PrepareStackValues( pParams );
   _asm mov sp1, esp; // Save the stack before
   _asm mov eax, 0;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams - 1; n >= 0; n-- )
   {
      if( pParams[ n ].m_nSplit < 3 )
      {
         dw = pParams[ n ].m_dwStackVal;
         _asm mov eax, dw;
         _asm push eax;
      }
   }

   dw = 1024; // size
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) ( (void*) &pBuffer );
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _parLong( pl, 3 ); // lang
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _parLong( pl, 2 );  // nMsgId
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _parLong( pl, 1 );  // hDll | NIL = exe
   if( !dw ) dw = (DWORD) GetModuleHandle( 0 );
   _asm mov eax, dw;
   _asm push eax;

   dw = ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE );
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _format_msg_;
   _asm mov eax, dw;
   _asm call eax;
   _asm mov dw, eax;
   _asm mov eax, sp1;
   _asm mov esp, eax;
   GetTlsHeapManager()->PutLastError( GetLastError() );
   TXbFpParam::ReleaseAll( pParams );
   if( dw && pBuffer ) _retclen( pl, pBuffer, dw );
   else _retc( pl, "" );
   if( pBuffer ) LocalFree( pBuffer );
}
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cFmtStrMsg
            | syntax_: `cFmtStrMsg( cTemplate, ... ) -> cMessage`
            | category: msg-string
            | _kw_: FormatMessage, message template, inserts, %1
   }}*/
/*{{|desc: Formats an in-memory message template with FormatMessage(FORMAT_MESSAGE_FROM_STRING) and
      returns it. The extra arguments are passed as message inserts. Returns an empty string when the
      template is missing or cannot be formatted.
    | params:
    - `cTemplate` Character - The message template (FormatMessage insert syntax, e.g. %1, %2).
    - `...` Any - Insert arguments for the template.

    Returns Character - The formatted message, or "" on failure.

    |seealso: See also: {{ilink: <function cFmtSysMsg> cFmtSysMsg}}, {{ilink: <function cFmtResMsg> cFmtResMsg}} }}*/
XPPRET XPPENTRY CFMTSTRMSG( XppParamList pl )
{
   LONG nParams, n;
   TXbFpParam* pParams;
   LONG sp1;
   DWORD dw;
   LPSTR pBuffer = 0;
   LPSTR pStr = _pszParam( pl, 1 );

   if( !pStr ) { _retc( pl, "" ); return; }

   pParams = TXbFpParam::InitList( pl, 2, &nParams, TRUE );
   TXbFpParam::PrepareStackValues( pParams );
   _asm mov sp1, esp; // Save the stack before
   _asm mov eax, 0;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams - 1; n >= 0; n-- )
   {
      if( pParams[ n ].m_nSplit < 3 )
      {
         dw = pParams[ n ].m_dwStackVal;
         _asm mov eax, dw;
         _asm push eax;
      }
   }

   dw = 1024; // size
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) ( (void*) &pBuffer );
   _asm mov eax, dw;
   _asm push eax;

   dw = 0;
   _asm mov eax, dw;
   _asm push eax;
   _asm push eax;

   dw = (DWORD) pStr;
   _asm mov eax, dw;
   _asm push eax;

   dw = ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_MAX_WIDTH_MASK );
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _format_msg_;
   _asm mov eax, dw;
   _asm call eax;
   _asm mov dw, eax;
   _asm mov eax, sp1;
   _asm mov esp, eax;
   GetTlsHeapManager()->PutLastError( GetLastError() );
   TXbFpParam::ReleaseAll( pParams );
   if( dw && pBuffer ) _retclen( pl, pBuffer, dw );
   else _retc( pl, "" );
   if( pBuffer ) LocalFree( pBuffer );
   _xfree( (void*) pStr );
}
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static int ot4xb_cprintf_cb_internal( LPSTR pFmt, TXbFpParam* pParams, LONG nParams )
{
   LONG  n;
   LONG  sp1;
   DWORD dw;

   _asm mov sp1, esp;
   _asm mov eax, 0;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams - 1; n >= 0; n-- )
   {
      if( pParams[ n ].m_nSplit < 3 )
      {
         dw = pParams[ n ].m_dwStackVal;
         _asm mov eax, dw;
         _asm push eax;
      }
   }

   dw = (DWORD) pFmt;
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) _scprintf;
   _asm mov eax, dw;
   _asm call eax;
   _asm mov dw, eax;

   _asm mov eax, sp1;
   _asm mov esp, eax;

   GetTlsHeapManager()->PutLastError( GetLastError() );
   return (int) dw;
}
// -----------------------------------------------------------------------------------------------------------------
static int ot4xb_cprintf_internal( LPSTR pFmt, TXbFpParam* pParams, LONG nParams, LPSTR pBuffer )
{
   LONG  n;
   LONG  sp1;
   DWORD dw;

   _asm mov sp1, esp;
   _asm mov eax, 0;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams - 1; n >= 0; n-- )
   {
      if( pParams[ n ].m_nSplit < 3 )
      {
         dw = pParams[ n ].m_dwStackVal;
         _asm mov eax, dw;
         _asm push eax;
      }
   }

   dw = (DWORD) pFmt;
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) pBuffer;
   _asm mov eax, dw;
   _asm push eax;

   dw = (DWORD) sprintf;
   _asm mov eax, dw;
   _asm call eax;
   _asm mov dw, eax;

   _asm mov eax, sp1;
   _asm mov esp, eax;
   GetTlsHeapManager()->PutLastError( GetLastError() );
   return (int) dw;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_cprintf_c_escape_
            | syntax_: `LPSTR __cdecl _ot4xb_cprintf_c_escape_( LPSTR pStr )`
            | category: strings
            | mangled-name: _ot4xb_cprintf_c_escape_
            | _kw_: C escapes, backslash escapes, unescape, newline tab, string
   }}*/
/*{{|desc: Returns a newly allocated copy of pStr with C-style backslash escapes expanded: \n \r \t \a \b
      \f \v \\ (the usual C escapes), \q (a double quote), \xHH (a byte from two hex digits) and \dDDD (a
      byte from three decimal digits). Any other escaped character is copied unchanged. Returns NULL when
      pStr is NULL. Used by cPrintf when the format is given with a leading NIL.
    | params:
    - `pStr` LPSTR - Source string to process.

    Returns LPSTR - Newly allocated (_xgrab) copy with escapes expanded, or NULL. }}*/
extern "C" LPSTR OT4XB_API __cdecl _ot4xb_cprintf_c_escape_( LPSTR pStr )
{
   LPSTR pOut = 0;
   if( pStr )
   {
      LPSTR p;
      LPSTR pp = pOut = (LPSTR) _xgrab( _xstrlen( pStr ) + 1 );
      for( p = pStr; p[ 0 ]; p++ )
      {
         if( p[ 0 ] == '\\' )
         {
            switch( p[ 1 ] )
            {
               case 'x': // \x00
               {
                  if( p[ 2 ] && p[ 3 ] )
                  {
                     *pp++ = (char) ( ( chHex2Nibble( (BYTE) p[ 2 ] ) << 4 ) | chHex2Nibble( (BYTE) p[ 3 ] ) );
                     p += 3;
                  }
                  else { *pp++ = *p; }
                  break;
               }
               case 'd': // \d000
               {
                  if( p[ 2 ] && p[ 3 ] && p[ 4 ] )
                  {
                     char sz[ 4 ]; sz[ 0 ] = p[ 2 ]; sz[ 1 ] = p[ 3 ]; sz[ 2 ] = p[ 4 ];  sz[ 3 ] = 0;
                     *pp++ = (char) ( atoi( sz ) & 0xFF );
                     p += 4;
                  }
                  else { *pp++ = *p; }
                  break;
               }
               case 'q': { *pp++ = 0x22; p++; break; } //  Double Quote
               case 'a': { *pp++ = '\a'; p++; break; } //  Bell (alert)
               case 'b': { *pp++ = '\b'; p++; break; } //  Backspace
               case 'f': { *pp++ = '\f'; p++; break; } //  Formfeed
               case 'n': { *pp++ = '\n'; p++; break; } //  New line
               case 'r': { *pp++ = '\r'; p++; break; } //  Carriage return
               case 't': { *pp++ = '\t'; p++; break; } //  Horizontal tab
               case 'v': { *pp++ = '\v'; p++; break; } //  Vertical tab
               case '\\': { *pp++ = '\\'; p++; break; } //  Backslash
               default: { *pp++ = *p; break; }
            }
         }
         else *pp++ = *p;
      }
   }
   return pOut;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: cPrintf
            | syntax_: ``cPrintf( cFormat, ... ) -> cText  | cPrintf( NIL, cFormatWithEscapes, ... )``
            | category: strings
            | _kw_: sprintf, printf, format string, C format
   }}*/
/*{{|desc: Formats text with C sprintf() conversion rules and returns the generated string. If the first
      argument is NIL, the next argument is taken as the format and its C escapes are expanded first (see
      _ot4xb_cprintf_c_escape_): cPrintf(NIL, cFormatWithEscapes, ...).
    | params:
    - `cFormat` Character - printf-style format string (or NIL to expand escapes in the next arg).
    - `...` Any - Values to format; see the note below.

    Returns Character - The formatted text.

    |note: The former __printf() function and the DECLARE APPLICATION COUT CLASS METHODS #xcommand (which
      redefined QOut()/QQOut() through __printf) were removed in ot4xb 1.8.0.1 - they wrote to the C runtime
      stdout, which is not the Xbase++ console. To keep old __printf(...) code compiling, route it to
      cPrintf and the standard Xbase++ console with a #xtranslate in your own header (see example).

    |example: ```
         // Drop-in replacement for the removed __printf(), sent to the Xbase++ console via cPrintf:
         #xtranslate __printf( <x,...> ) => QQOut( cPrintf( <x> ) )
      ```

    |seealso: See also: {{ilink: <c-function _ot4xb_cprintf_c_escape_> _ot4xb_cprintf_c_escape_}} }}*/
XPPRET XPPENTRY CPRINTF( XppParamList pl )
{
   ContainerHandle conr = _conPutC( NULLCONTAINER, "" );
   ULONG nFirst = 2;
   LPSTR pFmt = 0;
   if( _partype( pl, 1 ) & XPP_UNDEF )
   {
      LPSTR p = _pszParam( pl, 2 );
      nFirst++;
      if( p ) { pFmt = _ot4xb_cprintf_c_escape_( p ); _xfree( (void*) p ); }
   }
   else
   {
      pFmt = _pszParam( pl, 1 );
   }
   if( pFmt )
   {
      LONG nParams;
      TXbFpParam* pParams = TXbFpParam::InitList( pl, nFirst, &nParams, TRUE );
      int cb;

      TXbFpParam::PrepareStackValues( pParams );
      cb = ot4xb_cprintf_cb_internal( pFmt, pParams, nParams );
      if( cb > 0 )
      {
         LPSTR pOut = (LPSTR) _xgrab( (UINT) ( ( cb + 256 ) & 0xFFFFFFF0 ) );
         cb = ot4xb_cprintf_internal( pFmt, pParams, nParams, pOut );
         if( cb >= 0 ) { _conPutCL( conr, pOut, (ULONG) cb ); }
         _xfree( (void*) pOut );
      }
      TXbFpParam::ReleaseAll( pParams );
      _xfree( (void*) pFmt );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: pt2gp
            | syntax_: `pt2gp( pPointer ) -> oGenericPointer`
            | category: pointer
            | _kw_: generic pointer, wrap pointer, extended pointer, _lock_
   }}*/
/*{{|desc: Wraps a numeric pointer in an OT4XB_GENERIC_POINTER object so it can be passed where an OT4XB
      extended pointer (an object exposing ::_lock_()/::_unlock_()) is expected.
    | params:
    - `pPointer` Numeric - The pointer value to wrap.

    Returns Object - A new OT4XB_GENERIC_POINTER holding pPointer.

    |seealso: See also: {{ilink: <slug ot4xb_generic_pointer> OT4XB_GENERIC_POINTER}} }}*/
XPPRET XPPENTRY PT2GP( XppParamList pl )
{
   ContainerHandle conp = _conPutNL( NULLCONTAINER, _parLong( pl, 1 ) );
   ContainerHandle cono = _conNewObj( "OT4XB_GENERIC_POINTER", conp, NULLCONTAINER );
   _conRelease( conp );
   _conReturn( pl, cono );
   _conRelease( cono );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: OT4XB_GENERIC_POINTER
            | _slug_: ot4xb_generic_pointer
            | class-function: OT4XB_GENERIC_POINTER
            | category: pointer
            | desc: Minimal wrapper over a numeric pointer. It exposes ::_lock_() and ::_unlock_() so the object
              can be passed to OT4XB functions that accept extended pointers. Created from PRG via pt2gp() or
              OT4XB_GENERIC_POINTER():new(pPointer). The class registers itself lazily and is EXPORTED.
            | ivar_: - VAR _m__pt_ | type: Numeric | desc_: Holds the wrapped pointer value (a memory pointer, character buffer or parent
              object). Registered EXPORTED so Xbase++ can access it.
            | method_: - `init(pPointer) -> Self` | desc_: Stores pPointer, or 0 when NIL. Called from new().
            | method_: - `_lock_(@n) -> pPointer` | desc_: Returns the stored pointer (sets n to 0); extended-pointer
              lock hook.
            | method_: - `_unlock_() -> NIL` | desc_: No-op unlock hook for extended-pointer compatibility.
            | _kw_: generic pointer, pointer wrapper, _lock_, _unlock_, extended pointer
   }}*/
XPPRET XPPENTRY OT4XB_GENERIC_POINTER( XppParamList pl )
{
   ContainerHandle conco = _conClsObj( "OT4XB_GENERIC_POINTER" );
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass* pc = new TXbClass;
      pc->ClassName( "OT4XB_GENERIC_POINTER" );
      /*{{|:**BEGIN CLASS  OT4XB_GENERIC_POINTER** }}*/
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->Var( "_m__pt_" );  // memory pointer ,character buffer or parent object
      // ---------------------------------------------------------------------------------
      pc->MethodCB( "init", "{|s,v| s:_m__pt_ := iif(v == NIL,0,v), s}" );
      pc->MethodCB( "_lock_", "{|s,n| n := 0, s:_m__pt_ }" );
      pc->MethodCB( "_unlock_", "{|s| NIL }" );
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         if( pl ) { _ret( pl ); }
         return;
      }
   }
   // ---------------------------------------------------------------------------------
   if( pl ) _conReturn( pl, conco );
   _conRelease( conco );
}
   /*{{|:**END CLASS** }}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{note-id: character-as-memory-buffer
   |: Xbase++ CHARACTER variables have an internal buffer that may be shared by different variables
      until one of them changes. This is perfectly controlled by the Xbase++ mechanism at PRG level,
      but when we provide it to low-level operations we should be aware of that and provide CHARACTER
      params by value only when we know the internal buffer will not be modified.
}}*/
/*{{note-id: nil-parameter
   |: Every parameter value in the stack defaults to 0 (a 0 value or a NULL pointer, as corresponds
      to the expected type). A NIL argument leaves it unchanged, so NIL always passes that 0.
}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: FpQCall
            | syntax_: `FpQCall( fpSpec, cPrototype, ... ) -> xResult`
            | category: function-pointer
            | _kw_: call function pointer, prototype string, quick call, dll call, marshalling
   }}*/
/*{{|desc: Calls a stdcall or cdecl function using an explicit prototype string. fpSpec selects the
      function (resolved as in nFpGet); cPrototype is a string of 4-character templates, one for the return
      value followed by one per parameter, so the argument types come from the prototype instead of being
      inferred. The remaining arguments are converted according to the prototype. Raises an Xbase++ error
      (gencode 21) when the pointer cannot be resolved and Set_FpCall_Flags bit 1 is set.
    | params:
    - `fpSpec` Numeric/Character/Array - The function to call (resolved as in nFpGet).
    - `cPrototype` Character - Prototype: 4-char template for the return value plus one per parameter.
    - `...` Any - Arguments, converted according to the prototype.

    Returns The value returned by the called function, as typed by the prototype.

    |seealso: See also: {{ilink: <function nFpCall> nFpCall}}, {{ilink: <function IFpQCall> IFpQCall}}, {{ilink: <function FpLQCall> FpLQCall}}, {{ilink: <function nFpGet> nFpGet}}

    |note: The `@dll:[prototype]:function( ... )` shorthand of ot4xb.ch expands to a call to this function; see
      {{ilink: <topic quick_call_dll_functions> quick_call_dll_functions}}. }}*/
XPPRET XPPENTRY FPQCALL( XppParamList pl )
{
   ContainerHandle conr = _conNew( NULLCONTAINER );
   DWORD  dwFPtr = _dwGetFpParam_( pl, 1 );
   DWORD  nParams = (DWORD) ( _parclen( pl, 2, 0 ) >> 2 );
   DWORD nLErr = 0;

   if( nParams > 0 ) { nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = ( nParams + 2 ) * sizeof( DWORD );
      DWORD* pdwq = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ( (void*) pdwq ), nBuffSize, pl, 2, 0 ) )
      {
         TXbFpQParam* pParams = TXbFpQParam::InitList( pl, pdwq, 3, &nParams );
         DWORD         dwStackSize = 0;
         DWORD* pdwStack = TXbFpQParam::PrepareStack( pParams, &dwStackSize );
         TXbFpQParam::FCall( conr, dwFPtr, pdwq[ 0 ], pdwStack, dwStackSize, &nLErr );
         TXbFpQParam::ReleaseAll( pParams );
         _xfree( (void*) pdwStack );

      }
      _xfree( (void*) pdwq );
      GetTlsHeapManager()->PutLastError( nLErr );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl, conr ); _conRelease( conr );
}
/*{{include-note-id: _dwGetFpParam_}}*/
/*{{include-note-id: fp-qtype-prototype}}*/
/*{{include-note-id: qcall-return-values}}*/
/*{{include-note-id: character-as-memory-buffer}}*/
/*{{include-note-id: nil-parameter}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: bWriteLogLine
            | syntax_: `BOOL bWriteLogLine( LPSTR pFName, LPSTR pFmt, ... )`
            | category: log
            | header: ot4xb_c_exported.h
            | mangled-name: bWriteLogLine
            | _kw_: log, write log line, append file, printf
   }}*/
/*{{|desc: Formats a log line with vsprintf(pFmt, ...) and appends it to the log file pFName via
      dwWriteLogData. Returns TRUE when the write produced a non-zero locator. C primitive behind
      lWriteLogLine().
    | params:
    - `pFName` LPSTR - Log file name.
    - `pFmt` LPSTR - printf-style format string; the variadic arguments follow.

    Returns BOOL - TRUE on success (non-zero locator), FALSE otherwise. }}*/
BOOL OT4XB_API bWriteLogLine( LPSTR pFName, LPSTR pFmt, ... )
{
   va_list( arglist );
   BOOL  bOk = FALSE;
   BYTE  buffer[ 1024 ];
   DWORD cb;
   LONGLONG qLocator = 0;
   ZeroMemory( buffer, sizeof( buffer ) );

   va_start( arglist, pFmt );
   cb = (DWORD) vsprintf( (LPSTR) buffer, pFmt, arglist );
   va_end( arglist );
   
   dwWriteLogData( pFName, (void*) buffer, cb, &qLocator );
   bOk = ( ( qLocator == 0 ) ? 0 : 1 );
   return bOk;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lWriteLogLine
            | syntax_: `lWriteLogLine( cFile, cFormat, ... ) -> lOk`
            | category: log
            | _kw_: log, write log line, append file, C format
   }}*/
/*{{|desc: Formats a log line with C formatting rules and appends it to a log file, by calling
      bWriteLogLine through the fpCall machinery. Returns .T. on success.
    | params:
    - `cFile` Character - Log file name.
    - `cFormat` Character - printf-style format string.
    - `...` Any - Values to format.

    Returns Logical - .T. on success, .F. otherwise.

    |seealso: See also: {{ilink: <c-function bWriteLogLine> bWriteLogLine}} }}*/
XPPRET XPPENTRY LWRITELOGLINE( XppParamList pl )
{
   LONG nParams, n;
   DWORD dwFPtr = (DWORD) bWriteLogLine;
   TXbFpParam* pParams = TXbFpParam::InitList( pl, 1, &nParams, TRUE );
   LONG sp1;
   DWORD dw;

   TXbFpParam::PrepareStackValues( pParams );

   _asm mov sp1, esp; // Save the stack before

   _asm mov eax, 0; // Put some zeros at the end
   _asm push eax;   // 1
   _asm push eax;   // 2
   _asm push eax;   // 3

   for( n = nParams - 1; n >= 0; n-- )
   {
      if( pParams[ n ].m_nSplit < 3 )
      {
         dw = pParams[ n ].m_dwStackVal;
         _asm mov eax, dw;
         _asm push eax;
      }
   }

   _asm mov eax, dwFPtr;
   _asm call eax;

   _asm mov dw, eax;
   _asm mov eax, sp1;
   _asm mov esp, eax;

   GetTlsHeapManager()->PutLastError( GetLastError() );
   TXbFpParam::ReleaseAll( pParams );
   _retl( pl, (BOOL) dw );
}
/*{{include-note-id: fp-np-parameter-inference}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#define DUMMY_N( n ) __asm push ebp __asm mov ebp,esp __asm mov eax,0 __asm pop ebp __asm retn n

static __declspec( naked ) void dummy00( void ) { DUMMY_N( 0x00 ) }
static __declspec( naked ) void dummy01( void ) { DUMMY_N( 0x04 ) }
static __declspec( naked ) void dummy02( void ) { DUMMY_N( 0x08 ) }
static __declspec( naked ) void dummy03( void ) { DUMMY_N( 0x0C ) }
static __declspec( naked ) void dummy04( void ) { DUMMY_N( 0x10 ) }
static __declspec( naked ) void dummy05( void ) { DUMMY_N( 0x14 ) }
static __declspec( naked ) void dummy06( void ) { DUMMY_N( 0x18 ) }
static __declspec( naked ) void dummy07( void ) { DUMMY_N( 0x1C ) }
static __declspec( naked ) void dummy08( void ) { DUMMY_N( 0x20 ) }
static __declspec( naked ) void dummy09( void ) { DUMMY_N( 0x24 ) }
static __declspec( naked ) void dummy10( void ) { DUMMY_N( 0x28 ) }
static __declspec( naked ) void dummy11( void ) { DUMMY_N( 0x2C ) }
static __declspec( naked ) void dummy12( void ) { DUMMY_N( 0x30 ) }
static __declspec( naked ) void dummy13( void ) { DUMMY_N( 0x34 ) }
static __declspec( naked ) void dummy14( void ) { DUMMY_N( 0x38 ) }
static __declspec( naked ) void dummy15( void ) { DUMMY_N( 0x3C ) }
static __declspec( naked ) void dummy16( void ) { DUMMY_N( 0x40 ) }
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _dummyStdCbk
            | syntax_: `_dummyStdCbk( nParams ) -> pFunction | NIL`
            | category: function-pointer
            | _kw_: dummy callback, stdcall stub, no-op callback, pop parameters
   }}*/
/*{{|desc: Returns a pointer to a dummy stdcall callback that does nothing, returns 0, and pops nParams
      DWORD parameters off the stack on return. Useful where an API requires a stdcall callback you do not
      need to implement. Supported values are 0 through 16; any other value returns NIL.
    | params:
    - `nParams` Numeric - Number of DWORD parameters the callback must pop (0 to 16).

    Returns Numeric - Pointer to the matching dummy callback, or NIL when nParams is out of range. }}*/
XPPRET XPPENTRY _DUMMYSTDCBK( XppParamList pl )
{
   LONG n = 0;
   switch( _parnl( pl, 1 ) )
   {
      case 0: { n = (LONG) dummy00; break; }
      case 1: { n = (LONG) dummy01; break; }
      case 2: { n = (LONG) dummy02; break; }
      case 3: { n = (LONG) dummy03; break; }
      case 4: { n = (LONG) dummy04; break; }
      case 5: { n = (LONG) dummy05; break; }
      case 6: { n = (LONG) dummy06; break; }
      case 7: { n = (LONG) dummy07; break; }
      case 8: { n = (LONG) dummy08; break; }
      case 9: { n = (LONG) dummy09; break; }
      case 10: { n = (LONG) dummy10; break; }
      case 11: { n = (LONG) dummy11; break; }
      case 12: { n = (LONG) dummy12; break; }
      case 13: { n = (LONG) dummy13; break; }
      case 14: { n = (LONG) dummy14; break; }
      case 15: { n = (LONG) dummy15; break; }
      case 16: { n = (LONG) dummy16; break; }
   }
   if( n ) _retnl( pl, n );
   else _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: FpLQCall2
            | syntax_: `FpLQCall2( nIndex, cPrototype, pThisOrList, ... ) -> xResult`
            | category: function-pointer
            | _kw_: vtable, pointer list, call function pointer, prototype string
   }}*/
/*{{|desc: Variant of FpLQCall that reads the function pointer directly from the supplied pointer list.
      The pointer is resolved from nIndex and pThisOrList; cPrototype is the 4-character-template prototype
      string. Arguments are converted according to the prototype.
    | params:
    - `nIndex` Numeric - Index into the pointer list.
    - `cPrototype` Character - Prototype string (return template plus one per parameter).
    - `pThisOrList` Numeric - Pointer list (or this-pointer) to read the function pointer from.
    - `...` Any - Arguments, converted according to the prototype.

    Returns The value returned by the called function, as typed by the prototype.

    |seealso: See also: {{ilink: <function FpLQCall> FpLQCall}}, {{ilink: <function FpQCall> FpQCall}} }}*/
XPPRET XPPENTRY FPLQCALL2( XppParamList pl )
{
   if( _partype( pl, 0 ) < 3 ) { _ret( pl ); return; }
   ContainerHandle conr = _conNew( NULLCONTAINER );
   DWORD  dwFPtr = pt_list_get_pointer( _parLong( pl, 1, 0 ), _parLong( pl, 3, 0 ) );
   DWORD  nParams = (DWORD) ( _parclen( pl, 2, 0 ) >> 2 );
   DWORD nLErr = 0;

   if( nParams > 0 ) { nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = ( nParams + 2 ) * sizeof( DWORD );
      DWORD* pdwq = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ( (void*) pdwq ), nBuffSize, pl, 2, 0 ) )
      {
         TXbFpQParam* pParams = TXbFpQParam::InitList( pl, pdwq, 3, &nParams );
         DWORD         dwStackSize = 0;
         DWORD* pdwStack = TXbFpQParam::PrepareStack( pParams, &dwStackSize );
         TXbFpQParam::FCall( conr, dwFPtr, pdwq[ 0 ], pdwStack, dwStackSize, &nLErr );
         TXbFpQParam::ReleaseAll( pParams );
         _xfree( (void*) pdwStack );
      }
      _xfree( (void*) pdwq );
      GetTlsHeapManager()->PutLastError( nLErr );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl, conr ); _conRelease( conr );
}
/*{{include-note-id: fp-qtype-prototype}}*/
/*{{include-note-id: qcall-return-values}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: IFpQCall
            | syntax_: `IFpQCall( nVTableIndex, cPrototype, pInterface, ... ) -> xResult`
            | category: function-pointer
            | _kw_: COM, interface method, vtable, call, prototype string
   }}*/
/*{{|desc: Calls a COM interface method resolved from the interface vtable. The function pointer is taken
      from vtable slot nVTableIndex of pInterface; cPrototype is the 4-character-template prototype string
      (return plus one per parameter). Arguments are converted according to the prototype.
    | params:
    - `nVTableIndex` Numeric - Zero-based index of the method in the interface vtable.
    - `cPrototype` Character - Prototype string (return template plus one per parameter).
    - `pInterface` Numeric - Pointer to the COM interface.
    - `...` Any - Arguments, converted according to the prototype.

    Returns The value returned by the method, as typed by the prototype.

    |seealso: See also: {{ilink: <function FpQCall> FpQCall}}, {{ilink: <function FpLQCall> FpLQCall}} }}*/
XPPRET XPPENTRY IFPQCALL( XppParamList pl )
{
   if( _partype( pl, 0 ) < 3 ) { _ret( pl ); return; }
   ContainerHandle conr = _conNew( NULLCONTAINER );
   DWORD  dwFPtr = vtlbn2fp( _parLong( pl, 1, 0 ), _parLong( pl, 3, 0 ) );
   DWORD  nParams = (DWORD) ( _parclen( pl, 2, 0 ) >> 2 );
   DWORD nLErr = 0;

   if( nParams > 0 ) { nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = ( nParams + 2 ) * sizeof( DWORD );
      DWORD* pdwq = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ( (void*) pdwq ), nBuffSize, pl, 2, 0 ) )
      {
         TXbFpQParam* pParams = TXbFpQParam::InitList( pl, pdwq, 3, &nParams );
         DWORD         dwStackSize = 0;
         DWORD* pdwStack = TXbFpQParam::PrepareStack( pParams, &dwStackSize );
         TXbFpQParam::FCall( conr, dwFPtr, pdwq[ 0 ], pdwStack, dwStackSize, &nLErr );
         TXbFpQParam::ReleaseAll( pParams );
         _xfree( (void*) pdwStack );
      }
      _xfree( (void*) pdwq );
      GetTlsHeapManager()->PutLastError( nLErr );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl, conr ); _conRelease( conr );
}
/*{{include-note-id: fp-qtype-prototype}}*/
/*{{include-note-id: qcall-return-values}}*/
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
static DWORD pt_list_get_pointer( LONG n, LONG v )
{
   DWORD* pv = (DWORD*) v;
   if( pv )
   {
      DWORD   dw = 0;
      __try { dw = pv[ (DWORD) n ]; }
      __except( 1 ) { dw = 0; }
      return dw;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------

static DWORD vtlbn2fp( LONG n, LONG v )
{
   DWORD** ppv = (DWORD**) v;
   DWORD* pv = 0;
   if( ppv ) { __try { pv = ppv[ 0 ]; } __finally { ; } }
   if( pv )
   {
      DWORD   dw = 0;
      __try { dw = pv[ (DWORD) n ]; }
      __except( 1 ) { dw = 0; }
      return dw;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: FpLQCall
            | syntax_: `FpLQCall( nIndex, cPrototype, pPointerList, ... ) -> xResult`
            | category: function-pointer
            | _kw_: pointer list, call function pointer, prototype string, vtable
   }}*/
/*{{|desc: Calls a function pointer read from a pointer list. The pointer is resolved from nIndex and
      pPointerList; cPrototype is the 4-character-template prototype string. Arguments after the list are
      converted according to the prototype.
    | params:
    - `nIndex` Numeric - Index into the pointer list.
    - `cPrototype` Character - Prototype string (return template plus one per parameter).
    - `pPointerList` Numeric - Pointer list to read the function pointer from.
    - `...` Any - Arguments, converted according to the prototype.

    Returns The value returned by the called function, as typed by the prototype.

    |seealso: See also: {{ilink: <function FpLQCall2> FpLQCall2}}, {{ilink: <function FpQCall> FpQCall}} }}*/
XPPRET XPPENTRY FPLQCALL( XppParamList pl )
{
   if( _partype( pl, 0 ) < 3 ) { _ret( pl ); return; }
   ContainerHandle conr = _conNew( NULLCONTAINER );
   DWORD  dwFPtr = vtlbn2fp( _parLong( pl, 1, 0 ), _parLong( pl, 3, 0 ) );
   DWORD  nParams = (DWORD) ( _parclen( pl, 2, 0 ) >> 2 );
   DWORD nLErr = 0;

   if( nParams > 0 ) { nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = ( nParams + 2 ) * sizeof( DWORD );
      DWORD* pdwq = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ( (void*) pdwq ), nBuffSize, pl, 2, 0 ) )
      {
         TXbFpQParam* pParams = TXbFpQParam::InitList( pl, pdwq, 4, &nParams );
         DWORD         dwStackSize = 0;
         DWORD* pdwStack = TXbFpQParam::PrepareStack( pParams, &dwStackSize );
         TXbFpQParam::FCall( conr, dwFPtr, pdwq[ 0 ], pdwStack, dwStackSize, &nLErr );
         TXbFpQParam::ReleaseAll( pParams );
         _xfree( (void*) pdwStack );
      }
      _xfree( (void*) pdwq );
      GetTlsHeapManager()->PutLastError( nLErr );
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1 )
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description( "Function is not declared" );
         e.gencode( 21 );
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl, conr ); _conRelease( conr );
}
/*{{include-note-id: fp-qtype-prototype}}*/
/*{{include-note-id: qcall-return-values}}*/
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
/*{{ note-id: fp-np-parameter-inference
| title_: Non Prototyped Function Pointer Parameters Type Inference
|note:
Parameter type conversion - each argument is converted to a C type from its Xbase++ type and by-value/by-reference:
- LOGICAL by value -> BOOL
- LOGICAL by reference -> BOOL*, updated when the function returns
- NUMERIC by value -> LONG (decimals truncated); shorter prototypes (WORD, __int16, BYTE, CHAR) also work, since
  CDECL/STDCALL pass values in 32-bit packs so the high part is ignored
- NUMERIC by reference -> LONG*, updated on return; for pointers to shorter values (WORD*, __int16*, BYTE*, CHAR*)
  adjust the result afterwards with LoWord() or LoByte()
- CHARACTER by value -> READ-ONLY buffer (LPCSTR)
- CHARACTER by reference -> READ-WRITE buffer (LPSTR)
64-bit integer parameters:
- NIL + CHARACTER by value -> __int64; the string MUST be 8 bytes, the binary representation of the 64-bit integer
  (build it from a double with Double2LongLong())
- NIL + CHARACTER by reference -> __int64*, written back on return
Float double values:
- NIL + NUMERIC by value -> double
- NIL + NUMERIC by reference -> double*, written back on return
32-bit float values:
- pack them into an Xbase++ numeric with PackFloat32(), or pass a pointer to a 32-bit float by reference
OT4XB extended pointers (structures via arrays and objects):
- ARRAY of NUMERICs -> a buffer holding an array of int32 values; if passed by reference, it is written back to
  your array
- GWST object -> the pointer to the structure is passed (a GWST subclass instance created with the structure
  commands)
| note: to avoid the parameter inference  we have the function FpQCall() that have param and return value template.
}}*/


// ---------------------------------------------------------------------------------------------------------------------
/*{{ note-id: fp-np-call
             | title_: Non Prototyped Function Pointer Call
|note:
Common to nFpCall, ndFpCall and qwFpCall - they call a STDCALL or CDECL function through a pointer.
- Both CDECL and STDCALL work: the caller saves the stack pointer (ESP) before the call and restores it
  afterwards - that restore does the cleanup cdecl needs and does not disturb stdcall (whose callee already
  cleaned the stack). FASTCALL and THISCALL are NOT supported.
- Precede the call with _FpCall_PushFlags_(1) to disable by-reference parameter conversion for that one call.
- If fp cannot be resolved, an Xbase++ error is raised ("Function is not declared", gencode 21) when
  Set_FpCall_Flags bit 1 is set, otherwise NIL is returned. The Win32 GetLastError() after the call is saved and
  can be read with nFpGetLastError().
}}*/

// ---------------------------------------------------------------------------------------------------------------------


