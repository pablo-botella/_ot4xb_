//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static ContainerHandle _cono_tls_static_ = NULLCONTAINER;
// -----------------------------------------------------------------------------------------------------------------
TLXbStack::item_t::item_t(ContainerHandle con , DWORD dwCtx)
{
   m_prev = 0;
   m_next = 0;
   m_con  = con;
   m_ctx  = dwCtx;
}  
// -----------------------------------------------------------------------------------------------------------------
TLXbStack::item_t::~item_t(void)
{
   if(m_con){ _conRelease( m_con ); }
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::item_t::DetachXbData(void)
{
   ContainerHandle con = m_con;
   m_con = 0;
   return con;
}
// -----------------------------------------------------------------------------------------------------------------
void TLXbStack::item_t::detach( item_t** pp_base , item_t** pp_top , DWORD* pdw_count )
{
   pdw_count[0]--;
   if( pp_base[0] == this ){ pp_base[0] = m_next; }
   if( pp_top[0] == this ){ pp_top[0] = m_prev; }   
   if( m_prev ){ m_prev->m_next = m_next; }
   if( m_next ){ m_next->m_prev = m_prev; }   
   m_prev = 0; m_next = 0;   
}
// -----------------------------------------------------------------------------------------------------------------
void TLXbStack::item_t::add( item_t** pp_base , item_t** pp_top , DWORD* pdw_count )
{
   pdw_count[0]++;
   if( pp_top[0] == 0 ){ pp_top[0] = pp_base[0] = this; m_prev = m_next = 0; }
   else 
   {
      m_next     = pp_base[0];    
      pp_base[0]  = this;
      m_prev = 0;
      m_next->m_prev = this;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TLXbStack::item_t::push( item_t** pp_base , item_t** pp_top , DWORD* pdw_count )
{
   pdw_count[0]++;
   if( pp_base[0] == 0 ){ pp_top[0] = pp_base[0] = this; m_prev = m_next = 0; }
   else 
   {
      m_prev     = pp_top[0];    
      pp_top[0]  = this;
      m_next = 0;
      m_prev->m_next = this;
   }
}
//----------------------------------------------------------------------------------------------------------------------
TLXbStack::TLXbStack(void){ m_top = m_base = 0; m_element_capacity = 0;}
TLXbStack::~TLXbStack(void){ while( m_top ){ PopAndDestroy(); } }
// -----------------------------------------------------------------------------------------------------------------
DWORD TLXbStack::GetTosCtx(UINT nSkip )
{
   item_t* p_item = 0;
   for( p_item = m_top; p_item && nSkip ; --nSkip , p_item = p_item->m_prev ){;}
   if( p_item ){ return p_item->m_ctx; }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::GetTos(UINT nSkip , DWORD** ppctx)
{
   item_t* p_item = 0;
   for( p_item = m_top; p_item && nSkip ; --nSkip , p_item = p_item->m_prev ){;}
   if( p_item )
   {
      if( ppctx ){ ppctx[0] = &(p_item->m_ctx); }
      return p_item->m_con;
   }
   if( ppctx ){ ppctx[0] = 0; }
   return NULLCONTAINER;
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::GetBase(UINT nSkip, DWORD** ppctx)   
{
   item_t* p_item = 0;
   for( p_item = m_base; p_item && nSkip ; --nSkip , p_item = p_item->m_next ){;}
   if( p_item )
   {
      if( ppctx ){ ppctx[0] = &(p_item->m_ctx); }
      return p_item->m_con;
   }
   if( ppctx ){ ppctx[0] = 0; }
   return NULLCONTAINER;
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::Pop(DWORD* pctx)
{
   DWORD ctx = 0;
   ContainerHandle con = NULLCONTAINER;
   item_t* p_item = m_top;   
   if( p_item )
   {
      ctx = p_item->m_ctx;
      con = p_item->DetachXbData();
      p_item->detach(&m_base,&m_top,&m_element_capacity);
      delete p_item;
   }
   if( pctx ){ pctx[0] = ctx; }
   return con;
}   
// -----------------------------------------------------------------------------------------------------------------
void TLXbStack::Push( ContainerHandle con , DWORD ctx)
{
   ( new item_t(con,ctx) )->push(&m_base,&m_top,&m_element_capacity);
}
// -----------------------------------------------------------------------------------------------------------------
void TLXbStack::Add( ContainerHandle con , DWORD ctx)
{
   ( new item_t(con,ctx) )->add(&m_base,&m_top,&m_element_capacity);
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::PushNew( DWORD** ppctx )
{
   item_t* p_item = new item_t(_conNew(NULLCONTAINER),0);
   p_item->push(&m_base,&m_top,&m_element_capacity);
   if( ppctx ){ ppctx[0] = &(p_item->m_ctx); }   
   return p_item->m_con;
}
// -----------------------------------------------------------------------------------------------------------------
ContainerHandle TLXbStack::AddNew( DWORD** ppctx )
{
   item_t* p_item = new item_t(_conNew(NULLCONTAINER),0);
   p_item->add(&m_base,&m_top,&m_element_capacity);
   if( ppctx ){ ppctx[0] = &(p_item->m_ctx); }   
   return p_item->m_con;
}
// -----------------------------------------------------------------------------------------------------------------
void TLXbStack::PopAndDestroy( void ){ _conReleaseM(Pop(),0);}
      // ---------------------------------------------------------------------------------
DWORD TLXbStack::Count( void ){ return m_element_capacity; }
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TLSSTACKTOP( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   UINT n = (UINT) _parLong(pl,1);
   DWORD* pctx = 0;
   ContainerHandle   con   = _conNew( pHMan->m_pUser->GetTos(n,&pctx) );
   if( _partype(pl,0) > 1 ){ _stornl((LONG) pctx,pl,2,0); }
   _conReturn(pl,con);
   _conRelease(con);
} 
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TLSSTACKPUSH( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   pHMan->m_pUser->Push(_conParam(pl,1,0));
   _ret(pl);
} 
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TLSSTACKPOP( XppParamList pl)    
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   DWORD ctx = 0;   
   ContainerHandle con = pHMan->m_pUser->Pop(&ctx);
   if( _partype(pl,0) > 0 ){ _stornl((LONG) ctx,pl,1,0); }   
   if(con == NULLCONTAINER ){_ret(pl); return;}
   _conReturn(pl,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY TLSSTACKCOUNT( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  _retnl( pl,(LONG) pHMan->m_pUser->Count()); 
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY XBTLSALLOC( XppParamList pl)
{                 
   DWORD dwTls = TlsAlloc();
   if( dwTls == TLS_OUT_OF_INDEXES){ _ret(pl); }
   else _retnl(pl,(LONG) dwTls);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY XBTLSFREE( XppParamList pl){ _retl(pl,TlsFree((DWORD) _parLong(pl,1)));}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY XBTLSSETVALUE( XppParamList pl)
{                                             
   DWORD dwIndex = (DWORD) _parLong(pl,1);
   ContainerHandle con = (ContainerHandle) TlsGetValue(dwIndex);
   if( con != NULLCONTAINER ) _conRelease(con); 
   con = NULLCONTAINER;
   if (!( _partype(pl,2) & XPP_UNDEF ))
   {
      BOOL bByRef = FALSE;
      ContainerHandle conTmp = _conParam(pl,2,&bByRef);
      con = _conNew(conTmp);
      if(!bByRef) _conRelease(conTmp);
   }
   _retl(pl,TlsSetValue(dwIndex,(void*)con));
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY XBTLSGETVALUE( XppParamList pl){ _conReturn(pl,(ContainerHandle) TlsGetValue((DWORD)_parLong(pl,1)));}
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _WithObject_StackTop_( UINT n )
{
   return GetTlsHeapManager()->m_pWithObject->GetTos(n);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY WITHOBJECTSTACKTOP( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   UINT n = (UINT) _parLong(pl,1);
   ContainerHandle   con   = _conNew( pHMan->m_pWithObject->GetTos(n) );
   _conReturn(pl,con);
   _conRelease(con);
} 
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY WITHOBJECTSTACKPUSH( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   pHMan->m_pWithObject->Push(_conParam(pl,1,0));
   _ret(pl);
} 
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY WITHOBJECTSTACKPOP( XppParamList pl)    
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   ContainerHandle con = pHMan->m_pWithObject->Pop();
   if(con == NULLCONTAINER ){_ret(pl); return;}
   _conReturn(pl,con);
   _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY WITHOBJECTSTACKCOUNT( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  _retnl( pl,(LONG) pHMan->m_pWithObject->Count()); 
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY WITHOBJECTSTACKRECOVER( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  int i = _parLong(pl,1,0);
  _ret( pl );  
  if(i < 0){ i = 0; }
  while( pHMan->m_pWithObject->Count() > ((DWORD) i) ){ _conReleaseM(pHMan->m_pWithObject->Pop() , 0);  }
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_ARRAY_ITERATOR )
{
   TXppParamList xpp(pl,1);
   TLXbStack* s = GetTlsHeapManager()->m_pWithObject;
   if( xpp[1]->CheckType(XPP_ARRAY) && xpp[1]->con_size() )
   {
       s->Push( _conNew( xpp[1]->Get() ) , (DWORD) -1 );
   }
   else { s->Push( 0 , (DWORD) -2 ); }
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_ARRAY_ITERATOR_STEP )
{
   TXppParamList xpp(pl,1);
   TLXbStack* s = GetTlsHeapManager()->m_pWithObject;
   DWORD dw  = s->GetTosCtx(0);
   DWORD* p_ctx = 0;   
   
   xpp[0]->PutBool(FALSE);
   if( dw == 0  ){ return;} // not inside an array iterator
   if( dw == (DWORD) -2 ){  s->PopAndDestroy(); return;} // empty or not array
   if( dw == (DWORD) -1  ) // start
   {
      if( !_conCheckType(s->GetTos(0,&p_ctx),XPP_ARRAY) ){  s->PopAndDestroy(); return;} // not array
      p_ctx[0] = (DWORD) -3 ; // inside loop
      s->PushNew(&p_ctx);
      p_ctx[0] = dw = 0;
   }
   
   if( s->GetTosCtx(1) == (DWORD) -3 )
   {
      ContainerHandle cona = s->GetTos(1);      
      DWORD cona_size = _conGetArrayLen(cona);
      ContainerHandle con  = NULLCONTAINER;
      DWORD dwMask = ( xpp[1]->CheckType(XPP_NUMERIC) ? xpp[1]->GetDWord() : (DWORD) -1 );
      
      ITERATE_ITEMS_LABEL: ;  
          
      con  = s->GetTos(0,&p_ctx);            
      if( dw >=  cona_size )
      {
         s->PopAndDestroy();  // item    
         s->PopAndDestroy();  // array   
         return;
      }
      dw++;
      p_ctx[0] = dw;
      _conArrayGet(cona,con,dw,0);  
      if( !_conCheckType(con, dwMask) )
      {
         goto ITERATE_ITEMS_LABEL;
      }
      xpp[0]->PutBool(TRUE);
   }      
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_ARRAY_ITERATOR_INDEX )
{
   _retnl(pl,(LONG) GetTlsHeapManager()->m_pWithObject->GetTosCtx(0));
}
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( TLS )
{
   if( _cono_tls_static_ == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;pc->ClassName("TLS");
      pc->EXPORTED();
      pc->Var("v_70e74aad_5183_4e9b_aaad_02aab4fe2b57");  // 
      
      pc->Method_cbbs("remove_all","{|s,cc| _hdict_removeall(nFpCall(%i),cc) }", GetTls_ht );
	  pc->Method_cbbs("remove_prop", "{|s,cc| _hdict_removeprop(nFpCall(%i),cc) }", GetTls_ht);
	  pc->Method_cbbs("get_prop", "{|s,cc| _hdict_getprop(nFpCall(%i),cc) }", GetTls_ht);
      pc->Method_cbbs("getNoIVar","{|s,cc| _hdict_getprop(nFpCall(%i),cc) }", GetTls_ht );      
      pc->Method_cbbs("set_prop","{|s,cc,vv| iif(vv == NIL,_hdict_removeprop(nFpCall(%i),cc), _hdict_setprop(nFpCall(%i),cc,vv)) }", GetTls_ht,GetTls_ht );
      pc->Method_cbbs("setNoIVar","{|s,cc,vv| iif(vv == NIL,_hdict_removeprop(nFpCall(%i),cc), _hdict_setprop(nFpCall(%i),cc,vv)) }", GetTls_ht,GetTls_ht );      
      pc->Method_cbbs("_get_ht_handle_","{|s| nFpCall(%i) }", GetTls_ht );
      ContainerHandle conco = pc->Create(); delete pc; 
      if( conco )
      {
         _cono_tls_static_ = _conMCallCon(conco,"New");
         _conRelease( conco );
      }
   }
   ContainerHandle conr = _conNew( _cono_tls_static_ );
   _conReturn( pl , conr ); 
   _conRelease( conr );
}
// -----------------------------------------------------------------------------------------------------------------
