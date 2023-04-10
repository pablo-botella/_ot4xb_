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
OT4XB_API DWORD __cdecl ot4xb_get_tls_json_encoding_flags(void)
{
	return GetTlsHeapManager()->m_json_encoding_flags;
}
// -----------------------------------------------------------------------------------------------------------------

OT4XB_API void __cdecl ot4xb_set_tls_json_encoding_flags(DWORD dw)
{
	GetTlsHeapManager()->m_json_encoding_flags = dw;
}

// -----------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __cdecl ot4xb_get_tls_variant_to_string_locale(void)
{
	return GetTlsHeapManager()->m_variant_to_string_locale;
}
// -----------------------------------------------------------------------------------------------------------------

OT4XB_API void __cdecl ot4xb_set_tls_variant_to_string_locale(DWORD dw)
{
	GetTlsHeapManager()->m_variant_to_string_locale = dw;
}

// -----------------------------------------------------------------------------------------------------------------
OT4XB_API void __cdecl ot4xb_set_tls_variant_to_string_locale_invariant(void)
{
	GetTlsHeapManager()->m_variant_to_string_locale = LOCALE_INVARIANT;
}