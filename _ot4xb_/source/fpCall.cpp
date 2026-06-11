//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
static DWORD _dwFpCallErrorFlags_= 1;
static XppFuncType _pDllExecuteCall_ = (XppFuncType) GetProcAddress(GetModuleHandle("xpprt1"),"DLLEXECUTECALL");
//----------------------------------------------------------------------------------------------------------------------
typedef struct _XPP_DLL_TEMPLATE__struct{
     CHAR  szDll[4];
     DWORD hDll;
     DWORD fp;
     WORD  wMode;
     WORD  wDummy;
  } _XPP_DLL_TEMPLATE_;
//----------------------------------------------------------------------------------------------------------------------
static DWORD _dwGetFpParam_( XppParamList pl , ULONG nPos);
static DWORD vtlbn2fp( LONG n , LONG v );
static DWORD pt_list_get_pointer( LONG n , LONG v );
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function-family>
      <name>Function pointer calls</name>
      <source>fpCall.cpp</source>
      <category>interop/function-pointer</category>
      <description>
         Low-level OT4XB helpers for loading DLLs, resolving function pointers and calling stdcall or cdecl
         functions from Xbase++.
      </description>
      <remarks>
         These functions are intended for Win32 interop code. The caller is responsible for using the correct
         function pointer, calling convention, return type and parameter layout. Fastcall and thiscall functions
         are not supported.

         The fp parameter accepted by nFpCall(), ndFpCall(), qwFpCall() and FpQCall() can be a numeric function
         pointer, a DllPrepareCall() template string, or an array { hDllOrDllName, cProcName }.

         nFpCall(), ndFpCall() and qwFpCall() infer parameter conversion from the supplied Xbase++ values:
         logical values are passed as BOOL, numeric values as LONG, character values as LPCSTR or LPSTR when
         passed by reference, numeric arrays as temporary arrays of 32-bit values, and GWST objects as OT4XB
         extended pointers locked for the duration of the call. A NIL marker before a character value passes an
         8-byte integer value; a NIL marker before a numeric value passes a double value.

         FpQCall(), IFpQCall(), FpLQCall() and FpLQCall2() use a prototype string. The string contains one
         4-character template for the return value followed by one template for each parameter.
      </remarks>
      <functions>
         <function>
            <name>set_fpcall_flags</name>
            <syntax>set_fpcall_flags( [nFlags] ) -> nOldFlags</syntax>
            <description>Reads or replaces the global fpCall error flags. Flag 1 raises a BASE error when a function pointer cannot be resolved.</description>
         </function>
         <function>
            <name>_fpcall_pushflags_</name>
            <syntax>_fpcall_pushflags_( nFlags ) -> NIL</syntax>
            <description>Pushes flags for the next fpCall on the current thread. Flag 1 disables by-reference parameter conversion for that call.</description>
         </function>
         <function>
            <name>nfpget</name>
            <syntax>nfpget( fpSpec ) -> pFunction</syntax>
            <description>Resolves a numeric pointer, DllPrepareCall() template or { hDllOrDllName, cProcName } array to a function pointer.</description>
         </function>
         <function>
            <name>f2t</name>
            <syntax>f2t( pFunction ) -> cDllTemplate</syntax>
            <description>Builds a small Xbase++ DLL call template string for a function pointer in the current module.</description>
         </function>
         <function>
            <name>xbfpcall</name>
            <syntax>xbfpcall( @cTemplateOrPointer, ... ) -> xResult</syntax>
            <description>Calls the Xbase++ runtime DLLEXECUTECALL entry after storing an OT4XB template in the first parameter.</description>
         </function>
         <function>
            <name>nfpcall</name>
            <syntax>nfpcall( fpSpec, ... ) -> n32BitResult</syntax>
            <description>Calls a stdcall or cdecl function and returns the 32-bit result from EAX.</description>
         </function>
         <function>
            <name>ndfpcall</name>
            <syntax>ndfpcall( fpSpec, ... ) -> nDouble</syntax>
            <description>Calls a stdcall or cdecl function that returns a 64-bit floating point value.</description>
         </function>
         <function>
            <name>qwfpcall</name>
            <syntax>qwfpcall( fpSpec, ... ) -> cQword</syntax>
            <description>Calls a stdcall or cdecl function that returns a 64-bit integer and returns the raw 8-byte value.</description>
         </function>
         <function>
            <name>nfpgetlasterror</name>
            <syntax>nfpgetlasterror() -> nLastError</syntax>
            <description>Returns the Win32 GetLastError() value saved by the latest fpCall operation on the current thread.</description>
         </function>
         <function>
            <name>qfpgetlastpointer</name>
            <syntax>qfpgetlastpointer() -> pPointer</syntax>
            <description>Returns the thread-local last pointer value stored by OT4XB helper code.</description>
         </function>
         <function>
            <name>qfpsetlastpointer</name>
            <syntax>qfpsetlastpointer( pPointer ) -> NIL</syntax>
            <description>Stores a thread-local last pointer value for OT4XB helper code.</description>
         </function>
         <function>
            <name>nloadlibrary</name>
            <syntax>nloadlibrary( cDllName [, @nLastError] ) -> hDll</syntax>
            <description>Loads a DLL and returns its module handle. @nLastError receives GetLastError() when loading fails.</description>
         </function>
         <function>
            <name>lfreelibrary</name>
            <syntax>lfreelibrary( hDll ) -> lOk</syntax>
            <description>Releases a module handle with FreeLibrary().</description>
         </function>
         <function>
            <name>ngetprocaddress</name>
            <syntax>ngetprocaddress( hDllOrDllName, cProcName | nOrdinal ) -> pFunction</syntax>
            <description>Returns a DLL export pointer. A DLL name is loaded if the module is not already loaded.</description>
         </function>
         <function>
            <name>fpqcall</name>
            <syntax>fpqcall( fpSpec, cPrototype, ... ) -> xResult</syntax>
            <description>Calls a stdcall or cdecl function using a 4-character prototype template for the return value and each parameter.</description>
         </function>
         <function>
            <name>ifpqcall</name>
            <syntax>ifpqcall( nVTableIndex, cPrototype, pInterface, ... ) -> xResult</syntax>
            <description>Calls a COM interface method resolved from the interface vtable.</description>
         </function>
         <function>
            <name>fplqcall</name>
            <syntax>fplqcall( nIndex, cPrototype, pPointerList, ... ) -> xResult</syntax>
            <description>Calls a function pointer read from a pointer list and passes user parameters after the list argument.</description>
         </function>
         <function>
            <name>fplqcall2</name>
            <syntax>fplqcall2( nIndex, cPrototype, pThisOrList, ... ) -> xResult</syntax>
            <description>Variant of fplqcall() that reads the function pointer directly from the supplied pointer list.</description>
         </function>
         <function>
            <name>_dummystdcbk</name>
            <syntax>_dummystdcbk( nParams ) -> pFunction | NIL</syntax>
            <description>Returns a dummy stdcall callback pointer that returns 0 and pops nParams DWORD parameters. Supported values are 0 through 16.</description>
         </function>
         <function>
            <name>pt2gp</name>
            <syntax>pt2gp( pPointer ) -> oGenericPointer</syntax>
            <description>Wraps a numeric pointer in an OT4XB_GENERIC_POINTER object so it can be used where an OT4XB extended pointer is expected.</description>
         </function>
         <function>
            <name>cprintf</name>
            <syntax>cprintf( cFormat, ... ) -> cText</syntax>
            <description>Formats a string with C sprintf() conversion rules and returns the generated text.</description>
         </function>
         <function>
            <name>cprintf</name>
            <syntax>cprintf( NIL, cFormatWithEscapes, ... ) -> cText</syntax>
            <description>Same as cprintf(), but first expands C-style escapes such as \n, \r, \t, \xHH, \dDDD, \q and \\.</description>
         </function>
         <function>
            <name>__printf</name>
            <syntax>__printf( cFormat, ... ) -> nChars</syntax>
            <description>Prints with C printf() conversion rules and returns the number of characters written.</description>
         </function>
         <function>
            <name>lWriteLogLine</name>
            <syntax>lWriteLogLine( cFile, cFormat, ... ) -> lOk</syntax>
            <description>Formats a log line using C formatting rules and appends it to a log file.</description>
         </function>
         <function>
            <name>cFmtSysMsg</name>
            <syntax>cFmtSysMsg( nMessageId [, nLangId] ) -> cMessage</syntax>
            <description>Formats a system message with FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM).</description>
         </function>
         <function>
            <name>cFmtResMsg</name>
            <syntax>cFmtResMsg( hDll, nMessageId [, nLangId], ... ) -> cMessage</syntax>
            <description>Formats a message resource from a module. When hDll is NIL or 0, the current executable module is used.</description>
         </function>
         <function>
            <name>cFmtStrMsg</name>
            <syntax>cFmtStrMsg( cTemplate, ... ) -> cMessage</syntax>
            <description>Formats an in-memory message template with FormatMessage(FORMAT_MESSAGE_FROM_STRING).</description>
         </function>
      </functions>
      <templates name="FpQCall prototype">
         <template code="__vo" type="VOID" />
         <template code="__xb" type="PXBASEVAR" />
         <template code="__bo" type="BOOL" />
         <template code="__sc" type="INT8" />
         <template code="__uc" type="BYTE" />
         <template code="__ss" type="INT16" />
         <template code="__us" type="WORD" />
         <template code="__sl" type="INT32" />
         <template code="__ul" type="DWORD" />
         <template code="__sq" type="INT64" />
         <template code="__uq" type="QWORD" />
         <template code="__f4" type="FLOAT" />
         <template code="__f8" type="DOUBLE" />
         <template code="__pt" type="POINTER" />
         <template code="?@sl" type="PSL_OR_PT" />
         <template code="_@bo" type="LPBOOL" />
         <template code="_@sc" type="LPINT8" />
         <template code="_@uc" type="LPUINT8" />
         <template code="_@ss" type="LPINT16" />
         <template code="_@us" type="LPWORD" />
         <template code="_@sl" type="LPINT32" />
         <template code="_@ul" type="LPDWORD" />
         <template code="_@sq" type="LPINT64" />
         <template code="_@uq" type="LPQWORD" />
         <template code="_@f4" type="LPFLOAT" />
         <template code="_@f8" type="LPDOUBLE" />
         <template code="c_sw" type="STR2WIDE" />
         <template code="c@sw" type="STR2WIDE_W" />
         <template code="c_sz" type="ZSTRING" />
         <template code="__hw" type="HWND" />
         <template code="__vt" type="VARIANT" />
      </templates>
      <example><![CDATA[
local hUser32 := nLoadLibrary( "user32.dll" )
local pMsgBox := nGetProcAddress( hUser32, "MessageBoxA" )

nFpCall( pMsgBox, 0, "Hello from OT4XB", "fpCall", 0 )
lFreeLibrary( hUser32 )
      ]]></example>
   </function-family>

   <class>
      <name>OT4XB_GENERIC_POINTER</name>
      <source>fpCall.cpp:OT4XB_GENERIC_POINTER</source>
      <category>interop/pointer</category>
      <description>
         Minimal wrapper over a numeric pointer. The object exposes ::_lock_() and ::_unlock_() so it can be
         passed to OT4XB functions that accept extended pointers.
      </description>
      <syntax>OT4XB_GENERIC_POINTER():new( pPointer ) -> Self</syntax>
      <members>
         <member name="_m__pt_" type="numeric">Stored pointer value.</member>
      </members>
      <methods>
         <method name="init" returns="Self">Stores the pointer value, or 0 when NIL is supplied.</method>
         <method name="_lock_" returns="numeric">Returns the stored pointer value.</method>
         <method name="_unlock_" returns="NIL">No-op unlock method for extended pointer compatibility.</method>
      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------------
static DWORD _dwGetFpParam_( XppParamList pl , ULONG nPos)
{
   DWORD dw = _partype(pl,nPos);
   if( dw & XPP_NUMERIC ) return (DWORD) _parLong(pl,nPos,0);
   else if( dw & XPP_CHARACTER )
   {
      _XPP_DLL_TEMPLATE_ tp;
      tp.fp = 0;
      _parc( (LPSTR) &tp , sizeof( _XPP_DLL_TEMPLATE_ ), pl , nPos );
      return tp.fp;
   }
   else if( dw & XPP_ARRAY )
   {
      if( _paralen(pl,nPos,0) > 1 )
      {
         {
            HMODULE hDll = (HMODULE) 0;
            CHAR sz[260];
            if( _paratype(pl,nPos,1,0) & XPP_NUMERIC ) hDll = (HMODULE) _parLong(pl,nPos,1,0);
            else
            {
               _bset((LPBYTE)sz,0,260);
               if( _parc(sz,260,pl,nPos,1,0))
               {
                  hDll = GetModuleHandle( sz );
                  if( !hDll ) hDll = LoadLibrary( sz );
               }
            }
            if( hDll )
            {
              // TODO: add suport to import by ordinal
               _bset((LPBYTE)sz,0,260);
               if( _parc(sz,260,pl,nPos,2,0))
               {
                  return (DWORD) GetProcAddress( hDll , sz );
               }
            }
         }
      }
   }
   return 0;
}
//----------------------------------------------------------------------------------------------------------------------
// static DWORD _dwFpCallErrorFlags_= 1;
XPPRET XPPENTRY SET_FPCALL_FLAGS( XppParamList pl )
{
   DWORD dw = _dwFpCallErrorFlags_;
   if( _partype(pl,1) & XPP_NUMERIC ) _dwFpCallErrorFlags_ = (DWORD) _parLong(pl,1,0);
   _retnl( pl, (LONG) dw);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NFPGET( XppParamList pl )
{
   LONG nfp = (LONG ) _dwGetFpParam_(pl,1);
   _retnl( pl, nfp );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY F2T( XppParamList pl ) // function pointer to  _XPP_DLL_TEMPLATE_
{
   _XPP_DLL_TEMPLATE_ tp[2];  
   ZeroMemory(tp, sizeof(tp));
   _bcopy( (LPBYTE) tp[0].szDll ,(LPBYTE) "_DLL",4);
   tp[0].hDll   = (DWORD) GetModuleHandle(0);
   tp[0].fp     = (DWORD) _parLong(pl,1);
   tp[0].wMode  = 1;
   tp[0].wDummy = 0;
   _retclen(pl,(LPSTR) tp, sizeof(tp) );
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void next_xbfpcall_use_critical_section( CRITICAL_SECTION * pcs)
{
   GetTlsHeapManager()->m_next_call_critical_section = pcs;
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY XBFPCALL( XppParamList pl )
{

   _XPP_DLL_TEMPLATE_ tp[4];  
   ZeroMemory(tp, sizeof(tp));
   _bcopy( (LPBYTE) tp[0].szDll ,(LPBYTE) "_DLL",4);
   tp[0].hDll   = (DWORD) GetModuleHandle(0);
   tp[0].fp     = (DWORD) _parLong(pl,1);
   tp[0].wMode  = 1;
   tp[0].wDummy = 0;
   _storclen((LPSTR) tp,sizeof(tp),pl,1,0);
   CRITICAL_SECTION* pcs = GetTlsHeapManager()->m_next_call_critical_section;
   GetTlsHeapManager()->m_next_call_critical_section = 0;
   __try
   {
      if( pcs ){ EnterCriticalSection(pcs); }      
      (*_pDllExecuteCall_)(pl);   
   }
   __finally
   {
      if( pcs ){ LeaveCriticalSection(pcs); }   
   }
   
   
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _FPCALL_PUSHFLAGS_( XppParamList pl ){ GetTlsHeapManager()->PushNextFpFlags( (DWORD) _parLong(pl,1,0)); _ret(pl);}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NFPCALL( XppParamList pl )
{
   LONG nParams,n;
   DWORD dwFPtr        = _dwGetFpParam_(pl,1);
   BOOL bDisableByRef = (BOOL) (GetTlsHeapManager()->PopNextFpFlags() & 1);
   if( dwFPtr )
   {
      TXbFpParam * pParams = TXbFpParam::InitList(pl,2,&nParams,bDisableByRef);
      LONG spt;      
      LONG nl;

      TXbFpParam::PrepareStackValues(pParams);
      
      _asm mov spt ,esp; // Save the stack before      
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
      _asm mov nl  ,eax; // get the result      
      _asm mov esp ,spt;  // restore the stack      

      GetTlsHeapManager()->PutLastError(GetLastError());
      TXbFpParam::ReleaseAll(pParams);
      _retnl(pl,nl);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret(pl);
   }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NDFPCALL( XppParamList pl )
{
   LONG nParams,n;
   DWORD dwFPtr       = _dwGetFpParam_(pl,1);
   BOOL bDisableByRef = (BOOL) (GetTlsHeapManager()->PopNextFpFlags() & 1);   
   if( dwFPtr )
   {
      TXbFpParam * pParams = TXbFpParam::InitList(pl,2,&nParams,bDisableByRef);
      LONG spt;            
      double nd;

      TXbFpParam::PrepareStackValues(pParams);
      
      _asm mov spt ,esp; // Save the stack before            
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
      _asm fstp qword ptr nd;
      _asm mov esp ,spt;  // restore the stack            
      GetTlsHeapManager()->PutLastError(GetLastError());
      TXbFpParam::ReleaseAll(pParams);
      _retnd(pl,nd);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret(pl);
   }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY QWFPCALL( XppParamList pl )
{
   LONG nParams,n;
   DWORD dwFPtr       = _dwGetFpParam_(pl,1);
   BOOL bDisableByRef = (BOOL) (GetTlsHeapManager()->PopNextFpFlags() & 1);   
   if( dwFPtr )
   {
      TXbFpParam * pParams = TXbFpParam::InitList(pl,2,&nParams,bDisableByRef);
      LONG spt;            
      char  sz[8];
      TXbFpParam::PrepareStackValues(pParams);      

      _asm mov spt ,esp; // Save the stack before      
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
      _asm mov dword ptr sz[0]   , eax;
      _asm mov dword ptr sz[4]   , edx;
      _asm mov esp ,spt;  // restore the stack            
      GetTlsHeapManager()->PutLastError(GetLastError());
      TXbFpParam::ReleaseAll(pParams);
      _retclen(pl,sz,8);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
      _ret(pl);
   }
}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl ot4xb_GetFpLastError(void){ return GetTlsHeapManager()->GetLastError(); }
OT4XB_API void  __cdecl ot4xb_PutFpLastError(DWORD dw){ GetTlsHeapManager()->PutLastError(dw); }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NFPGETLASTERROR( XppParamList pl ){ _retnl(pl,(LONG) GetTlsHeapManager()->GetLastError()); }
XPPRET XPPENTRY QFPGETLASTPOINTER( XppParamList pl ){ _retnl(pl,(LONG) GetTlsHeapManager()->GetLastPointer()); }
XPPRET XPPENTRY QFPSETLASTPOINTER( XppParamList pl ){ GetTlsHeapManager()->PutLastPointer((DWORD) _parLong(pl,1));_ret(pl);}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NGETPROCADDRESS( XppParamList pl ) // nGetProcAddress( hDLL , cFuncName ) -> fp
{
   CHAR sz[260];
   HMODULE  hDll = (HMODULE ) 0;
   LONG     nFp  = 0;

   switch( _partype(pl,1) & 0xFF )
   {
      case XPP_CHARACTER :
      {
         if( _parc(sz,260,pl,1) )
         {
            hDll = GetModuleHandle( sz );
            if( !hDll ) hDll = LoadLibrary( sz );
         }
         break;
      }
      case XPP_NUMERIC :
      {
         hDll = (HMODULE) _parLong(pl,1);
         break;
      }
   }
   if( hDll )
   {
      switch( _partype(pl,2) & 0xFF )
      {
         case XPP_CHARACTER :
         {
            if( _parc(sz,260,pl,2) ) nFp = (LONG) GetProcAddress( hDll , sz );
            break;
         }
         case XPP_NUMERIC :
         {
            nFp = (LONG) GetProcAddress( hDll , (LPSTR) _parLong(pl,2) );
            break;
         }
      }
   }
   _retnl(pl,nFp);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY NLOADLIBRARY( XppParamList pl ) // nLoadLibrary( cDllName [,@nLastError] ) -> hDll
{
   LPSTR    pName  = _pszParam(pl,1);
   HMODULE  hDll   = 0;
   DWORD  nLastError = 0;
   if( pName )
   {
      hDll = LoadLibrary( pName );
      if(!hDll)
      {
         nLastError = GetLastError();
      }
      _xfree(pName);
   }
   _stornl((LONG) nLastError,pl,2,0);
   _retnl(pl,(LONG) hDll );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LFREELIBRARY( XppParamList pl ) // lFreeLibrary( hDll ) -> hDll
{
   HMODULE  hDll    = (HMODULE) _parLong(pl,1);
   BOOL     bResult = FALSE;
   if( hDll )   bResult = FreeLibrary( hDll );
   _retl(pl,bResult );
}
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-----------------------------------------------------------------------------------------------------------------------
static DWORD _format_msg_(DWORD dwf,void* ps,DWORD id,DWORD lan,LPSTR pb,DWORD cb , ... )
{
   DWORD result;
   va_list args; va_start(args,cb);
   result = FormatMessage(dwf,ps,id,lan,pb,cb,&args);
   va_end(args);
   return result;
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CFMTSYSMSG( XppParamList pl ) // cFmtSysMsg(nId,nLang)
{
   LPSTR pBuffer = 0;
   DWORD dw = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER|
                             FORMAT_MESSAGE_FROM_SYSTEM|
                             FORMAT_MESSAGE_IGNORE_INSERTS,
                             NULL, (DWORD) _parLong(pl,1,0),
                             (DWORD) _parLong(pl,2,0) & 0xFFFF,
                             (LPTSTR) &pBuffer,0, NULL );
   if( dw && pBuffer ) _retclen(pl,pBuffer,dw);
   else _retc(pl,"");
   if( pBuffer ) LocalFree( pBuffer );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CFMTRESMSG( XppParamList pl ) // cFmtResMsg(hDll,nId,nLang,...)
{
   LONG nParams,n;
   TXbFpParam * pParams = TXbFpParam::InitList(pl,4,&nParams,TRUE);
   LONG sp1;
   DWORD dw;
   LPSTR pBuffer = 0;


   TXbFpParam::PrepareStackValues(pParams);
   _asm mov sp1 ,esp; // Save the stack before
   _asm mov eax , 0 ;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   dw = 1024; // size
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD)((void*) &pBuffer);
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _parLong(pl,3); // lang
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _parLong(pl,2);  // nMsgId
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _parLong(pl,1);  // hDll | NIL = exe
   if( !dw ) dw = (DWORD) GetModuleHandle(0);
   _asm mov eax , dw ;
   _asm push eax;

   dw = ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE );
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _format_msg_;
   _asm mov eax , dw;
   _asm call eax;
   _asm mov dw ,eax;
   _asm mov eax ,sp1;
   _asm mov esp ,eax;
   GetTlsHeapManager()->PutLastError(GetLastError());
   TXbFpParam::ReleaseAll(pParams);
   if( dw && pBuffer ) _retclen(pl,pBuffer,dw);
   else _retc(pl,"");
   if( pBuffer ) LocalFree( pBuffer );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CFMTSTRMSG( XppParamList pl ) // cFmtStrMsg(cStr,...)
{
   LONG nParams,n;
   TXbFpParam * pParams;
   LONG sp1;
   DWORD dw;
   LPSTR pBuffer = 0;
   LPSTR pStr = _pszParam(pl,1);

   if(!pStr ){_retc(pl,"");return;}

   pParams = TXbFpParam::InitList(pl,2,&nParams,TRUE);
   TXbFpParam::PrepareStackValues(pParams);
   _asm mov sp1 ,esp; // Save the stack before
   _asm mov eax , 0 ;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   dw = 1024; // size
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD)((void*) &pBuffer);
   _asm mov eax , dw ;
   _asm push eax;

   dw = 0;
   _asm mov eax , dw ;
   _asm push eax;
   _asm push eax;

   dw = (DWORD) pStr;
   _asm mov eax , dw ;
   _asm push eax;

   dw = ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_MAX_WIDTH_MASK);
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _format_msg_;
   _asm mov eax , dw;
   _asm call eax;
   _asm mov dw ,eax;
   _asm mov eax ,sp1;
   _asm mov esp ,eax;
   GetTlsHeapManager()->PutLastError(GetLastError());
   TXbFpParam::ReleaseAll(pParams);
   if( dw && pBuffer ) _retclen(pl,pBuffer,dw);
   else _retc(pl,"");
   if( pBuffer ) LocalFree( pBuffer );
   _xfree((void*) pStr);
}
// -----------------------------------------------------------------------------------------------------------------
static int ot4xb_cprintf_cb_internal(LPSTR pFmt ,  TXbFpParam * pParams , LONG nParams)
{
   LONG  n;
   LONG  sp1;
   DWORD dw;

   _asm mov sp1 ,esp;
   _asm mov eax , 0 ;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   dw = (DWORD) pFmt;
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) _scprintf;
   _asm mov eax , dw;
   _asm call eax;
   _asm mov dw ,eax;

   _asm mov eax ,sp1;
   _asm mov esp ,eax;

   GetTlsHeapManager()->PutLastError(GetLastError());
   return (int) dw;
}
// -----------------------------------------------------------------------------------------------------------------
static int ot4xb_cprintf_internal(LPSTR pFmt , TXbFpParam * pParams , LONG nParams , LPSTR pBuffer )
{
   LONG  n;
   LONG  sp1;
   DWORD dw;

   _asm mov sp1 ,esp;
   _asm mov eax , 0 ;
   _asm push eax;
   _asm push eax;
   _asm push eax;
   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   dw = (DWORD) pFmt;
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) pBuffer;
   _asm mov eax , dw ;
   _asm push eax;

   dw = (DWORD) sprintf;
   _asm mov eax , dw;
   _asm call eax;
   _asm mov dw ,eax;

   _asm mov eax ,sp1;
   _asm mov esp ,eax;
   GetTlsHeapManager()->PutLastError(GetLastError());
   return (int) dw;
}
// -----------------------------------------------------------------------------------------------------------------
static int ot4xb_printf_internal( LPSTR pFmt, TXbFpParam * pParams, LONG nParams )
{
	LONG  n;
	LONG  sp1;
	DWORD dw;

	_asm mov sp1, esp;
	_asm mov eax, 0;
	_asm push eax;
	_asm push eax;
	_asm push eax;
	for ( n = nParams - 1; n >= 0; n-- )
	{
		if ( pParams[n].m_nSplit < 3 )
		{
			dw = pParams[n].m_dwStackVal;
			_asm mov eax, dw;
			_asm push eax;
		}
	}

	dw = (DWORD) pFmt;
	_asm mov eax, dw;
	_asm push eax;

	dw = (DWORD) printf;
	_asm mov eax, dw;
	_asm call eax;
	_asm mov dw, eax;

	_asm mov eax, sp1;
	_asm mov esp, eax;
	GetTlsHeapManager()->PutLastError( GetLastError() );
	return (int) dw;
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPSTR OT4XB_API __cdecl _ot4xb_cprintf_c_escape_( LPSTR pStr )
{
   LPSTR pOut = 0;
   if( pStr )
   {
      LPSTR p;
      LPSTR pp  = pOut = (LPSTR) _xgrab(_xstrlen(pStr)+1);
      for( p = pStr; p[0] ; p++ )
      {
         if( p[0] == '\\')
         {
            switch(p[1])
            {
               case 'x' : // \x00
               {
                  if(p[2] && p[3])
                  {
                     *pp++  = (char) ((chHex2Nibble((BYTE) p[2]) << 4) | chHex2Nibble((BYTE) p[3]));
                     p += 3;
                  }
                  else{ *pp++ = *p; }
                  break;
               }
               case 'd' : // \d000
               {
                  if(p[2] && p[3] && p[4])
                  {
                     char sz[4]; sz[0] = p[2]; sz[1] = p[3]; sz[2] = p[4];  sz[3] = 0;
                     *pp++  = (char) (atoi(sz) & 0xFF);   
                     p += 4;
                  }
                  else{ *pp++ = *p; }
                  break;
               }
               case 'q' : { *pp++ = 0x22 ; p++; break; } //  Double Quote
               case 'a' : { *pp++ = '\a' ; p++; break; } //  Bell (alert)
               case 'b' : { *pp++ = '\b' ; p++; break; } //  Backspace
               case 'f' : { *pp++ = '\f' ; p++; break; } //  Formfeed
               case 'n' : { *pp++ = '\n' ; p++; break; } //  New line
               case 'r' : { *pp++ = '\r' ; p++; break; } //  Carriage return
               case 't' : { *pp++ = '\t' ; p++; break; } //  Horizontal tab
               case 'v' : { *pp++ = '\v' ; p++; break; } //  Vertical tab
               case '\\': { *pp++ = '\\' ; p++; break; } //  Backslash
               default  : { *pp++ = *p   ; break; }
            }
         }
         else *pp++ = *p;
      }
   }
   return pOut;
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CPRINTF( XppParamList pl )
{
   ContainerHandle conr = _conPutC(NULLCONTAINER,"");   
   ULONG nFirst = 2;
   LPSTR pFmt = 0;
   if( _partype(pl,1) & XPP_UNDEF )
   {
      LPSTR p = _pszParam(pl,2);
      nFirst++;
      if(p){pFmt = _ot4xb_cprintf_c_escape_(p); _xfree( (void*) p); }
   }
   else
   {
      pFmt = _pszParam(pl,1);
   }
   if( pFmt )
   {
      LONG nParams;
      TXbFpParam * pParams = TXbFpParam::InitList(pl,nFirst,&nParams,TRUE);
      int cb;

      TXbFpParam::PrepareStackValues(pParams);
      cb = ot4xb_cprintf_cb_internal(pFmt,pParams,nParams);
      if( cb > 0 )
      {
         LPSTR pOut = (LPSTR) _xgrab((UINT) ((cb + 256) & 0xFFFFFFF0) );
         cb = ot4xb_cprintf_internal(pFmt,pParams,nParams,pOut);
         if( cb >= 0 ){ _conPutCL(conr,pOut,(ULONG) cb ); }
         _xfree((void*) pOut);
      }
      TXbFpParam::ReleaseAll(pParams);
      _xfree( (void*) pFmt);
   }
   _conReturn(pl,conr);
   _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY __PRINTF( XppParamList pl )
{
	ULONG nFirst = 2;
	LPSTR pFmt = 0;
	int cb = 0;
	if ( _partype( pl, 1 ) & XPP_UNDEF )
	{
		LPSTR p = _pszParam( pl, 2 );
		nFirst++;
		if ( p ) { pFmt = _ot4xb_cprintf_c_escape_( p ); _xfree( (void*) p ); }
	}
	else
	{
		pFmt = _pszParam( pl, 1 );
	}
	if ( pFmt )
	{
		LONG nParams;
		TXbFpParam * pParams = TXbFpParam::InitList( pl, nFirst, &nParams, TRUE );
		

		TXbFpParam::PrepareStackValues( pParams );
		cb = ot4xb_printf_internal( pFmt, pParams, nParams );
		TXbFpParam::ReleaseAll( pParams );
		_xfree( (void*) pFmt );
	}
	_retnl( pl, cb );
	
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PT2GP(XppParamList pl)
{
   ContainerHandle conp = _conPutNL( NULLCONTAINER , _parLong(pl,1));
   ContainerHandle cono = _conNewObj("OT4XB_GENERIC_POINTER", conp , NULLCONTAINER);
   _conRelease(conp);
   _conReturn(pl,cono);
   _conRelease(cono);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY OT4XB_GENERIC_POINTER(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("OT4XB_GENERIC_POINTER");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "OT4XB_GENERIC_POINTER" );
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->Var( "_m__pt_"    );  // memory pointer ,character buffer or parent object
      // ---------------------------------------------------------------------------------
      pc->MethodCB( "init"       , "{|s,v| s:_m__pt_ := iif(v == NIL,0,v), s}");
      pc->MethodCB( "_lock_"     , "{|s,n| n := 0, s:_m__pt_ }");
      pc->MethodCB( "_unlock_"   , "{|s| NIL }");
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER )
      {
         if(pl){ _ret(pl); }
         return;
      }
   }
   // ---------------------------------------------------------------------------------
   if(pl) _conReturn(pl,conco);
   _conRelease(conco);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY FPQCALL( XppParamList pl ) // FpQCall( fp,q,params... )
{
   ContainerHandle conr = _conNew( NULLCONTAINER);
   DWORD  dwFPtr       = _dwGetFpParam_(pl,1);
   DWORD  nParams = (DWORD) (_parclen(pl,2,0) >> 2);
   DWORD nLErr    = 0;

   if( nParams > 0){nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = (nParams + 2) * sizeof( DWORD) ;
      DWORD* pdwq  = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ((void*) pdwq) , nBuffSize,pl,2,0) )
      {
         TXbFpQParam * pParams = TXbFpQParam::InitList(pl,pdwq,3,&nParams);
         DWORD         dwStackSize = 0;
         DWORD *       pdwStack    = TXbFpQParam::PrepareStack(pParams,&dwStackSize );
         TXbFpQParam::FCall(conr,dwFPtr,pdwq[0],pdwStack,dwStackSize,&nLErr);
         TXbFpQParam::ReleaseAll(pParams);
         _xfree( (void*) pdwStack );
         
      }
      _xfree( (void*) pdwq);
      GetTlsHeapManager()->PutLastError(nLErr);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl,conr ); _conRelease( conr );
}
//----------------------------------------------------------------------------------------------------------------------
BOOL OT4XB_API bWriteLogLine( LPSTR pFName , LPSTR pFmt , ... )
{
   va_list(arglist);
   BOOL  bOk = FALSE;
   BYTE  buffer[1024];
   DWORD cb;
   LONGLONG qLocator = 0;

   va_start(arglist, pFmt);
   cb = (DWORD) vsprintf( (LPSTR) buffer ,pFmt, arglist );
   va_end(arglist);
   ZeroMemory(buffer,sizeof(buffer));
   dwWriteLogData(pFName,(void*) buffer, cb ,&qLocator);
   bOk = ( (qLocator == 0 ) ? 0 : 1 );
   return bOk;
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LWRITELOGLINE( XppParamList pl ) // lWriteLogLine( cFile , cStr , ... )
{
   LONG nParams,n;
   DWORD dwFPtr       = (DWORD) bWriteLogLine;
   TXbFpParam * pParams = TXbFpParam::InitList(pl,1,&nParams,TRUE);
   LONG sp1;
   DWORD dw;

   TXbFpParam::PrepareStackValues(pParams);

   _asm mov sp1 ,esp; // Save the stack before

   _asm mov eax , 0 ; // Put some zeros at the end
   _asm push eax;   // 1
   _asm push eax;   // 2
   _asm push eax;   // 3

   for( n = nParams-1; n >= 0 ; n-- )
   {
      if( pParams[n].m_nSplit < 3 )
      {
         dw = pParams[n].m_dwStackVal;
         _asm mov eax , dw;
         _asm push eax;
      }
   }

   _asm mov eax , dwFPtr;
   _asm call eax;

   _asm mov dw ,eax;
   _asm mov eax ,sp1;
   _asm mov esp ,eax;

   GetTlsHeapManager()->PutLastError(GetLastError());
   TXbFpParam::ReleaseAll(pParams);
   _retl(pl,(BOOL) dw);
}
// -----------------------------------------------------------------------------------------------------------------
#define DUMMY_N( n ) __asm push ebp __asm mov ebp,esp __asm mov eax,0 __asm pop ebp __asm retn n

static __declspec( naked ) void dummy00(void){ DUMMY_N( 0x00 ) }
static __declspec( naked ) void dummy01(void){ DUMMY_N( 0x04 ) }
static __declspec( naked ) void dummy02(void){ DUMMY_N( 0x08 ) }
static __declspec( naked ) void dummy03(void){ DUMMY_N( 0x0C ) }
static __declspec( naked ) void dummy04(void){ DUMMY_N( 0x10 ) }
static __declspec( naked ) void dummy05(void){ DUMMY_N( 0x14 ) }
static __declspec( naked ) void dummy06(void){ DUMMY_N( 0x18 ) }
static __declspec( naked ) void dummy07(void){ DUMMY_N( 0x1C ) }
static __declspec( naked ) void dummy08(void){ DUMMY_N( 0x20 ) }
static __declspec( naked ) void dummy09(void){ DUMMY_N( 0x24 ) }
static __declspec( naked ) void dummy10(void){ DUMMY_N( 0x28 ) }
static __declspec( naked ) void dummy11(void){ DUMMY_N( 0x2C ) }
static __declspec( naked ) void dummy12(void){ DUMMY_N( 0x30 ) }
static __declspec( naked ) void dummy13(void){ DUMMY_N( 0x34 ) }
static __declspec( naked ) void dummy14(void){ DUMMY_N( 0x38 ) }
static __declspec( naked ) void dummy15(void){ DUMMY_N( 0x3C ) }
static __declspec( naked ) void dummy16(void){ DUMMY_N( 0x40 ) }
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _DUMMYSTDCBK( XppParamList pl )
{
   LONG n = 0;
   switch( _parnl(pl,1) )
   {
      case 0  : { n = (LONG) dummy00; break;}
      case 1  : { n = (LONG) dummy01; break;}
      case 2  : { n = (LONG) dummy02; break;}
      case 3  : { n = (LONG) dummy03; break;}
      case 4  : { n = (LONG) dummy04; break;}
      case 5  : { n = (LONG) dummy05; break;}
      case 6  : { n = (LONG) dummy06; break;}
      case 7  : { n = (LONG) dummy07; break;}
      case 8  : { n = (LONG) dummy08; break;}
      case 9  : { n = (LONG) dummy09; break;}
      case 10 : { n = (LONG) dummy10; break;}
      case 11 : { n = (LONG) dummy11; break;}
      case 12 : { n = (LONG) dummy12; break;}
      case 13 : { n = (LONG) dummy13; break;}
      case 14 : { n = (LONG) dummy14; break;}
      case 15 : { n = (LONG) dummy15; break;}
      case 16 : { n = (LONG) dummy16; break;}
   }
   if( n ) _retnl(pl,n);
   else _ret(pl);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY FPLQCALL2( XppParamList pl ) // FPLQCALL2(n,q,this,params... )
{                                                
   if( _partype(pl,0) < 3 ){ _ret(pl); return;}
   ContainerHandle conr = _conNew( NULLCONTAINER);              
   DWORD  dwFPtr        = pt_list_get_pointer( _parLong(pl,1,0) , _parLong(pl,3,0));
   DWORD  nParams = (DWORD) (_parclen(pl,2,0) >> 2);
   DWORD nLErr    = 0;

   if( nParams > 0){nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = (nParams + 2) * sizeof( DWORD) ;
      DWORD* pdwq  = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ((void*) pdwq) , nBuffSize,pl,2,0) )
      {
         TXbFpQParam * pParams = TXbFpQParam::InitList(pl,pdwq,3,&nParams);
         DWORD         dwStackSize = 0;
         DWORD *       pdwStack    = TXbFpQParam::PrepareStack(pParams,&dwStackSize );
         TXbFpQParam::FCall(conr,dwFPtr,pdwq[0],pdwStack,dwStackSize,&nLErr);
         TXbFpQParam::ReleaseAll(pParams);
         _xfree( (void*) pdwStack );         
      }
      _xfree( (void*) pdwq);
      GetTlsHeapManager()->PutLastError(nLErr);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl,conr ); _conRelease( conr );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY IFPQCALL( XppParamList pl ) // IFpQCall(n,q,this,params... )
{                                                
   if( _partype(pl,0) < 3 ){ _ret(pl); return;}
   ContainerHandle conr = _conNew( NULLCONTAINER);              
   DWORD  dwFPtr        = vtlbn2fp( _parLong(pl,1,0) , _parLong(pl,3,0));
   DWORD  nParams = (DWORD) (_parclen(pl,2,0) >> 2);
   DWORD nLErr    = 0;

   if( nParams > 0){nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = (nParams + 2) * sizeof( DWORD) ;
      DWORD* pdwq  = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ((void*) pdwq) , nBuffSize,pl,2,0) )
      {
         TXbFpQParam * pParams = TXbFpQParam::InitList(pl,pdwq,3,&nParams);
         DWORD         dwStackSize = 0;
         DWORD *       pdwStack    = TXbFpQParam::PrepareStack(pParams,&dwStackSize );
         TXbFpQParam::FCall(conr,dwFPtr,pdwq[0],pdwStack,dwStackSize,&nLErr);
         TXbFpQParam::ReleaseAll(pParams);
         _xfree( (void*) pdwStack );         
      }
      _xfree( (void*) pdwq);
      GetTlsHeapManager()->PutLastError(nLErr);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl,conr ); _conRelease( conr );
}
//----------------------------------------------------------------------------------------------------------------------
static DWORD pt_list_get_pointer( LONG n , LONG v )
{
   DWORD*  pv  = (DWORD*) v;
   if( pv )
   {
      DWORD   dw  = 0;
      __try{dw = pv[(DWORD) n];}__except(1){ dw = 0; }
      return dw;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------

static DWORD vtlbn2fp( LONG n , LONG v )
{
   DWORD** ppv = (DWORD**) v;
   DWORD*  pv  = 0;
   if( ppv ){ __try{ pv = ppv[0];} __finally{;} }
   if( pv )
   {
      DWORD   dw  = 0;
      __try{dw = pv[(DWORD) n];}__except(1){ dw = 0; }
      return dw;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY FPLQCALL( XppParamList pl ) // FplQCall(n,q,list,params... )
{                                                
   if( _partype(pl,0) < 3 ){ _ret(pl); return;}
   ContainerHandle conr = _conNew( NULLCONTAINER);              
   DWORD  dwFPtr        = vtlbn2fp( _parLong(pl,1,0) , _parLong(pl,3,0));
   DWORD  nParams = (DWORD) (_parclen(pl,2,0) >> 2);
   DWORD nLErr    = 0;

   if( nParams > 0){nParams--; }
   if( dwFPtr )
   {
      ULONG nBuffSize = (nParams + 2) * sizeof( DWORD) ;
      DWORD* pdwq  = (DWORD*) _xgrab( nBuffSize ); // first param is result and terminating (DWORD) 0
      if( _parc( (LPSTR) ((void*) pdwq) , nBuffSize,pl,2,0) )
      {
         TXbFpQParam * pParams = TXbFpQParam::InitList(pl,pdwq,4,&nParams);
         DWORD         dwStackSize = 0;
         DWORD *       pdwStack    = TXbFpQParam::PrepareStack(pParams,&dwStackSize );
         TXbFpQParam::FCall(conr,dwFPtr,pdwq[0],pdwStack,dwStackSize,&nLErr);
         TXbFpQParam::ReleaseAll(pParams);
         _xfree( (void*) pdwStack );         
      }
      _xfree( (void*) pdwq);
      GetTlsHeapManager()->PutLastError(nLErr);
   }
   else
   {
      if( _dwFpCallErrorFlags_ & 1)
      {
         TXbGenError e;
         e.subsystem( "BASE" );
         e.description("Function is not declared");
         e.gencode(21);
         e.operation( __FUNCTION__ );
         e.Launch();
      }
   }
   _conReturn( pl,conr ); _conRelease( conr );
}
// -----------------------------------------------------------------------------------------------------------------

