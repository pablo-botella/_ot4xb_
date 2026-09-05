//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
extern "C" void dhUninitialize(BOOL bUninitializeCOM);
//----------------------------------------------------------------------------------------------------------------------
static DWORD   _dwTls_ = 0; //
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_InitProc(void)
{
   if( _dwTls_ == 0 )  _dwTls_ = TlsAlloc();
}
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_ExitProc_xb(void){;}
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_InitThread(void){;}
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_ExitThread_xb(void){;}
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_ExitProc(void)
{
    _APIcpp_Tls_ExitThread();
   if( _dwTls_ != 0 )  TlsFree(_dwTls_);
   _dwTls_ = 0;
}
//----------------------------------------------------------------------------------------------------------------------
void _APIcpp_Tls_ExitThread(void)
{
   _APIcpp_Tls_ExitThread_xb();
   if( _dwTls_ != 0 )
   {
      TTlsHeapManager * p;
      p = (TTlsHeapManager *) TlsGetValue(_dwTls_);
      if( p != 0 ) delete p;
   }
}
//----------------------------------------------------------------------------------------------------------------------
TTlsHeapManager * GetTlsHeapManager(void)
{
   if( _dwTls_ != 0 )
   {
      TTlsHeapManager * p;
      p = (TTlsHeapManager *) TlsGetValue(_dwTls_);
      if( p != 0 )
      {
         return p;
      }
      else
      {
         p =  new TTlsHeapManager;
         TlsSetValue( _dwTls_ , (void*) p );
         return p;
      }
   }
   return ( TTlsHeapManager * ) NULL;
}
// -----------------------------------------------------------------------------------------------------------------
THashTable * GetTls_ht(void){ return GetTlsHeapManager()->ht(); }
//----------------------------------------------------------------------------------------------------------------------
TTlsHeapManager::TTlsHeapManager()
{
   m_pUser         =  new TLXbStack;
   m_pWithObject   =  new TLXbStack;
   m_pPushDir      =  new TList;   
   m_dwLastError   =  0;
   m_dwLastPointer =  0;   
   m_dwNextFpFlags =  0;   
   m_dwLastFpFlags = 0;
   m_pht          = 0;
   m_disphelper_refcount = 0;
   m_dwOt4xbTaskId = 0;
   m_next_call_critical_section  = 0;
   m_rnd_seed   = 1;
   m_json_encoding_flags = 0;
   m_variant_to_string_locale = 0;
   TlsSetValue( _dwTls_ , (void*) this);   
}
//----------------------------------------------------------------------------------------------------------------------
TTlsHeapManager::~TTlsHeapManager()
{
   if( m_disphelper_refcount > 0 )
   {
      dhUninitialize(TRUE);
   }
   if( m_pUser       ){  delete m_pUser;        m_pUser       = 0; }
   if( m_pWithObject ){  delete m_pWithObject;  m_pWithObject = 0; }
   if( m_pPushDir    )
   {
      while( m_pPushDir->Count() )
      {
         void* p = m_pPushDir->Pop();
         if( p ){ _xfree(p); }
      }
      delete m_pPushDir;
      m_pPushDir    = 0;
   }
   if( m_pht         ){  delete m_pht;          m_pht         = 0; }
   
   m_next_call_critical_section  = 0; // the application is the responsible to initialize or destroy
   TlsSetValue(_dwTls_,0);   
}
// -----------------------------------------------------------------------------------------------------------------
void  TTlsHeapManager::PushNextFpFlags( DWORD dw )
{
   m_dwNextFpFlags = dw;
   m_dwLastFpFlags = dw;
}
// -----------------------------------------------------------------------------------------------------------------
DWORD TTlsHeapManager::PopNextFpFlags(void){ DWORD dw = m_dwNextFpFlags; m_dwNextFpFlags = 0; return dw;}
DWORD TTlsHeapManager::GetLastFpFlags(void){return m_dwLastFpFlags;}
//----------------------------------------------------------------------------------------------------------------------
THashTable* TTlsHeapManager::ht(void)
{
   if( ! m_pht )
   {
      m_pht = new THashTable();
      m_pht->m_pfnOnDestroyItem = THDictItem::_OnDestroyItem_;          
   }
   return m_pht;
}
// -----------------------------------------------------------------------------------------------------------------
void * TTlsHeapManager::Alloc( unsigned int nSize )
{
   return _xgrab(nSize); // HeapAlloc(m_hHeap,HEAP_GENERATE_EXCEPTIONS|HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,nSize);
}
//----------------------------------------------------------------------------------------------------------------------
void TTlsHeapManager::Free( void * p )
{
   _xfree(p); // HeapFree( m_hHeap , HEAP_NO_SERIALIZE , p );
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TTlsHeapManager::GetLastError(void){ return m_dwLastError; }
void TTlsHeapManager::PutLastError(DWORD dw){ m_dwLastError  =  dw; }
//----------------------------------------------------------------------------------------------------------------------
DWORD TTlsHeapManager::GetLastPointer(void){ return m_dwLastPointer; }
void TTlsHeapManager::PutLastPointer(DWORD dw){ m_dwLastPointer  =  dw; }
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_get_tls_json_encoding_flags
            | syntax_: `DWORD ot4xb_get_tls_json_encoding_flags( void )`
            | category: json
            | header: Tls_Internal.hpp
            | mangled-name: ot4xb_get_tls_json_encoding_flags
            | _kw_: json flags, per thread, TLS, encoding
   }}*/
/*{{|desc: Returns the JSON encoding flags kept, per thread, in the ot4xb thread local storage block.
      Every thread starts with the value 0. The library itself never reads these flags: this getter and
      its setter companion just expose the per thread slot to application code.

    Returns DWORD - JSON encoding flags of the calling thread; 0 when never set in this thread. }}*/
OT4XB_API DWORD __cdecl ot4xb_get_tls_json_encoding_flags(void)
{
	return GetTlsHeapManager()->m_json_encoding_flags;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_set_tls_json_encoding_flags
            | syntax_: `void ot4xb_set_tls_json_encoding_flags( DWORD dw )`
            | category: json
            | header: Tls_Internal.hpp
            | mangled-name: ot4xb_set_tls_json_encoding_flags
            | _kw_: json flags, per thread, TLS, encoding
   }}*/
/*{{|desc: Stores the given value as the JSON encoding flags of the calling thread, in the ot4xb thread
      local storage block. Each thread has its own copy, starting at 0. The library itself never reads
      these flags: this setter and its getter companion just expose the per thread slot to application
      code.
    | params:
    - `dw` DWORD - New JSON encoding flags for the calling thread.

    Returns void }}*/
OT4XB_API void __cdecl ot4xb_set_tls_json_encoding_flags(DWORD dw)
{
	GetTlsHeapManager()->m_json_encoding_flags = dw;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_get_tls_variant_to_string_locale
            | syntax_: `DWORD ot4xb_get_tls_variant_to_string_locale( void )`
            | category: c-api/variant
            | header: Tls_Internal.hpp
            | mangled-name: ot4xb_get_tls_variant_to_string_locale
            | _kw_: variant locale, per thread, TLS, LCID, VariantChangeType
   }}*/
/*{{|desc: Returns the locale identifier the calling thread applies when the library changes the type of
      a COM variant value, typically when automation values are converted to strings. Kept per thread in
      the ot4xb thread local storage block, starting at 0 in every new thread. 0 selects the plain
      VariantChangeType() Windows behavior, driven by the user regional settings; any other LCID makes
      the library call VariantChangeTypeEx() with that locale.

    Returns DWORD - LCID used by this thread for variant conversions; 0 means default Windows behavior. }}*/
OT4XB_API DWORD __cdecl ot4xb_get_tls_variant_to_string_locale(void)
{
	return GetTlsHeapManager()->m_variant_to_string_locale;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_set_tls_variant_to_string_locale
            | syntax_: `void ot4xb_set_tls_variant_to_string_locale( DWORD dw )`
            | category: c-api/variant
            | header: Tls_Internal.hpp
            | mangled-name: ot4xb_set_tls_variant_to_string_locale
            | _kw_: variant locale, per thread, TLS, LCID, VariantChangeType
   }}*/
/*{{|desc: Sets the locale identifier the calling thread applies when the library changes the type of a
      COM variant value, typically when automation values are converted to strings. A nonzero LCID routes
      those conversions through VariantChangeTypeEx() with that locale; 0, the per thread default,
      selects the plain VariantChangeType() Windows behavior, driven by the user regional settings. The
      Xbase++ command SET VARIANT TO STRING LOCALE DEFAULT calls this function with 0.
    | params:
    - `dw` DWORD - LCID for variant conversions in this thread; 0 restores the default Windows
      behavior.

    Returns void }}*/
OT4XB_API void __cdecl ot4xb_set_tls_variant_to_string_locale(DWORD dw)
{
	GetTlsHeapManager()->m_variant_to_string_locale = dw;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_set_tls_variant_to_string_locale_invariant
            | syntax_: `void ot4xb_set_tls_variant_to_string_locale_invariant( void )`
            | category: c-api/variant
            | header: Tls_Internal.hpp
            | mangled-name: ot4xb_set_tls_variant_to_string_locale_invariant
            | _kw_: variant locale, invariant, LOCALE_INVARIANT, TLS
   }}*/
/*{{|desc: Sets the variant conversion locale of the calling thread to LOCALE_INVARIANT, so COM variant
      values converted by the library, typically to strings, are formatted the same way on any machine
      regardless of the user regional settings. Same as calling ot4xb_set_tls_variant_to_string_locale()
      with LOCALE_INVARIANT. The Xbase++ command SET VARIANT TO STRING LOCALE INVARIANT calls this
      function.

    Returns void }}*/
OT4XB_API void __cdecl ot4xb_set_tls_variant_to_string_locale_invariant(void)
{
	GetTlsHeapManager()->m_variant_to_string_locale = LOCALE_INVARIANT;
}
/*{{end-c-function}}*/