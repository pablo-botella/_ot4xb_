//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
#ifdef _OT4XB_API_
// ---------------------------------------------------------------------------
#ifdef __cplusplus
// ---------------------------------------------------------------------------
TTlsHeapManager * GetTlsHeapManager(void);
THashTable * GetTls_ht(void);
// -----------------------------------------------------------------------------------------------------------------
extern "C"
{
	OT4XB_API  DWORD __cdecl ot4xb_get_tls_json_encoding_flags(void);
	OT4XB_API  void __cdecl ot4xb_set_tls_json_encoding_flags(DWORD dw);
	OT4XB_API  DWORD __cdecl ot4xb_get_tls_variant_to_string_locale(void);
	OT4XB_API  void __cdecl ot4xb_set_tls_variant_to_string_locale(DWORD dw);
	OT4XB_API  void __cdecl ot4xb_set_tls_variant_to_string_locale_invariant(void);
}
// -----------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TTlsHeapManager : public T_ot4xb_base    // TODO: TTlsHeapManager intentar reducir overheap al minimo
{
   public:
       TLXbStack*         m_pWithObject;
       TLXbStack*         m_pUser;
       DWORD              m_dwLastError;
       DWORD              m_dwLastPointer;
       DWORD              m_dwNextFpFlags;       
       DWORD              m_dwLastFpFlags;       
       THashTable*        m_pht;
       LONG               m_disphelper_refcount;              
       TList*             m_pPushDir;              
       DWORD              m_dwOt4xbTaskId;    
       LPCRITICAL_SECTION m_next_call_critical_section;
       DWORD              m_rnd_seed;   
       DWORD              m_json_encoding_flags;   
	   DWORD              m_variant_to_string_locale;
       // --------------------------------------------------------------------
       TTlsHeapManager();       
       ~TTlsHeapManager();              
       THashTable* ht( void );
       void * Alloc( unsigned int );
       void Free( void * );
       DWORD GetLastError(void);
       void  PutLastError(DWORD);
       DWORD GetLastPointer(void);
       void  PutLastPointer(DWORD);
       void  PushNextFpFlags( DWORD dw );
       DWORD PopNextFpFlags(void);
       DWORD GetLastFpFlags(void);
       // --------------------------------------------------------------------
};
// ---------------------------------------------------------------------------
class TLXbStack
{
   private:
   // ---------------------------------------------------------------------------------
   class item_t : public T_ot4xb_base
   {
      public:         
      item_t*           m_prev;
      item_t*           m_next;
      ContainerHandle   m_con;
      DWORD             m_ctx;
      // ----------------------------------
      item_t(ContainerHandle con , DWORD dwCtx = 0);
      ~item_t(void);
      // ----------------------------------         
      ContainerHandle DetachXbData( void );
      // ----------------------------------         
      void detach( item_t** pp_base , item_t** pp_top , DWORD* pdw_count );
      void add( item_t** pp_base , item_t** pp_top , DWORD* pdw_count );
      void push( item_t** pp_base , item_t** pp_top , DWORD* pdw_count );
      // ----------------------------------                  
   };
   // ---------------------------------------------------------------------------------
   private: 
   item_t*  m_top;
   item_t*  m_base;   
   DWORD    m_element_capacity;
   // ---------------------------------------------------------------------------------      
   public:
   // ---------------------------------------------------------------------------------      
   TLXbStack(void);
   ~TLXbStack(void);   
   // ---------------------------------------------------------------------------------         
   DWORD GetTosCtx(UINT nSkip = 0);
   ContainerHandle  GetTos(UINT nSkip = 0 , DWORD** ppctx = 0);   
   ContainerHandle  GetBase(UINT nSkip = 0 , DWORD** ppctx = 0);   
   ContainerHandle  Pop(DWORD* pctx = 0);
   void Push( ContainerHandle con = 0, DWORD ctx = 0);
   void Add( ContainerHandle con = 0 , DWORD ctx = 0);
   ContainerHandle PushNew( DWORD** ppctx = 0 );
   ContainerHandle AddNew( DWORD** ppctx = 0 );
   void PopAndDestroy( void );
   DWORD Count(void);
};
// ---------------------------------------------------------------------------





// ---------------------------------------------------------------------------
#endif
#endif
