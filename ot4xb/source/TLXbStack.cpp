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
/*{{begin-function}}*/
/*{{function_: TlsStackTop
            | syntax_: `TlsStackTop( [nSkip] [, @pCtx] )`
            | category: runtime/thread
            | _kw_: TlsStackTop, Function
   }}*/
/*{{|desc: Returns an item from the current thread's OT4XB ThreadLocalStorage Stack without removing it.
      Each thread has its own independent ThreadLocalStorage Stack for application use; TlsStackPush() and
      TlsStackPop() add and remove items.
    | params:
    - `nSkip` Numeric - Zero-based distance from the top of the stack. The default value is 0 (top item).
    - `pCtx` Numeric by reference - Optional variable that receives the memory address of the context
      DWORD stored with the item, or 0 when no item exists at the requested position. The application can
      change the context through that address; TlsStackPop() returns the context value with the popped item.

    Returns The stored value, or NIL when no item exists at the requested position.

    |seealso: See also: {{ilink: <function TlsStackPush> TlsStackPush}}, {{ilink: <function TlsStackPop> TlsStackPop}}, {{ilink: <function TlsStackCount> TlsStackCount}} }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TlsStackPush
            | syntax_: `TlsStackPush( xValue )`
            | category: runtime/thread
            | _kw_: TlsStackPush, Function
   }}*/
/*{{|desc: Pushes a value on the current thread's OT4XB ThreadLocalStorage Stack.
    | params:
    - `xValue` Any - Value to store on top of the stack. The item is stored with a context value of 0.

    Returns NIL }}*/
XPPRET XPPENTRY TLSSTACKPUSH( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   pHMan->m_pUser->Push(_conParam(pl,1,0));
   _ret(pl);
} 
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TlsStackPop
            | syntax_: `TlsStackPop( [@nCtx] )`
            | category: runtime/thread
            | _kw_: TlsStackPop, Function
   }}*/
/*{{|desc: Pops the top value from the current thread's OT4XB ThreadLocalStorage Stack.
    | params:
    - `nCtx` Numeric by reference - Optional variable that receives the context value stored with the
      popped item (0 unless the application changed it through the context pointer from TlsStackTop).

    Returns The popped value, or NIL when the stack is empty. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TlsStackCount
            | syntax_: `TlsStackCount()`
            | category: runtime/thread
            | _kw_: TlsStackCount, Function
   }}*/
/*{{|desc: Returns the number of items in the current thread's OT4XB ThreadLocalStorage Stack.

    Returns Numeric - Current item count. }}*/
XPPRET XPPENTRY TLSSTACKCOUNT( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  _retnl( pl,(LONG) pHMan->m_pUser->Count()); 
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: XbTlsAlloc
            | syntax_: `XbTlsAlloc()`
            | category: runtime/thread
            | _kw_: XbTlsAlloc, Function
   }}*/
/*{{|desc: Allocates a Win32 TLS (thread local storage) slot for the process by calling the TlsAlloc()
      Win32 API. The returned index is valid in every thread of the process, but each thread keeps its own
      value for it. The XbTls* functions are thin low-level wrappers over the Win32 TLS slot API:
      XbTlsSetValue() and XbTlsGetValue() store and read Xbase++ values in the slot, and XbTlsFree()
      releases the index.

    Returns Numeric - The allocated TLS index, or NIL when the allocation fails (TlsAlloc() returned
      TLS_OUT_OF_INDEXES).

    |seealso: See also: {{ilink: <function XbTlsFree> XbTlsFree}}, {{ilink: <function XbTlsSetValue> XbTlsSetValue}}, {{ilink: <function XbTlsGetValue> XbTlsGetValue}} }}*/
XPPRET XPPENTRY XBTLSALLOC( XppParamList pl)
{                 
   DWORD dwTls = TlsAlloc();
   if( dwTls == TLS_OUT_OF_INDEXES){ _ret(pl); }
   else _retnl(pl,(LONG) dwTls);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: XbTlsFree
            | syntax_: `XbTlsFree( nTlsIndex )`
            | category: runtime/thread
            | _kw_: XbTlsFree, Function
   }}*/
/*{{|desc: Frees a Win32 TLS slot allocated with XbTlsAlloc().
    | params:
    - `nTlsIndex` Numeric - TLS index to release.

    Returns Logical - .T. when the index was freed, .F. on failure.

    |note: Freeing the index does not release values still stored in the slot by any thread. Set the slot
      value to NIL in every thread that used it before freeing the index, or those values are never released. }}*/
XPPRET XPPENTRY XBTLSFREE( XppParamList pl){ _retl(pl,TlsFree((DWORD) _parLong(pl,1)));}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: XbTlsSetValue
            | syntax_: `XbTlsSetValue( nTlsIndex [, xValue] )`
            | category: runtime/thread
            | _kw_: XbTlsSetValue, Function
   }}*/
/*{{|desc: Replaces the current thread's value for a Win32 TLS slot. The previously stored value is released
      first; when xValue is omitted the slot is left empty.
    | params:
    - `nTlsIndex` Numeric - TLS index allocated with XbTlsAlloc().
    - `xValue` Any - Optional new value for the slot. Each thread keeps its own value for the same index.

    Returns Logical - .T. when the value was stored, .F. on failure. }}*/
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
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: XbTlsGetValue
            | syntax_: `XbTlsGetValue( nTlsIndex )`
            | category: runtime/thread
            | _kw_: XbTlsGetValue, Function
   }}*/
/*{{|desc: Returns the current thread's value stored in a Win32 TLS slot.
    | params:
    - `nTlsIndex` Numeric - TLS index allocated with XbTlsAlloc().

    Returns The stored value, or NIL when the current thread has not stored a value in that slot. }}*/
XPPRET XPPENTRY XBTLSGETVALUE( XppParamList pl){ _conReturn(pl,(ContainerHandle) TlsGetValue((DWORD)_parLong(pl,1)));}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _WithObject_StackTop_
            | syntax_: `ContainerHandle _WithObject_StackTop_( UINT n )`
            | category: runtime/thread
            | header: ot4xb_c_exported.h
            | mangled-name: _WithObject_StackTop_
            | _kw_: _WithObject_StackTop_, Function
   }}*/
/*{{|desc: C-level access to the current thread's with-object stack: returns an item without removing it.
    | params:
    - `n` UINT - Zero-based distance from the top of the stack; 0 reads the top item.

    Returns ContainerHandle - Handle stored at the requested position, or NULLCONTAINER when the stack holds
      n items or fewer. The handle stays owned by the stack; call _conNew() on it to keep a reference. }}*/
OT4XB_API ContainerHandle _WithObject_StackTop_( UINT n )
{
   return GetTlsHeapManager()->m_pWithObject->GetTos(n);
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: WithObjectStackTop
            | _tg_: with_object
            | syntax_: `WithObjectStackTop( [nSkip] )`
            | category: runtime/thread
            | _kw_: WithObjectStackTop, Function
   }}*/
/*{{|desc: Returns an item from the current thread's with-object stack without removing it. The with.item
      and with.this shorthands translate to a call to this function, and the .: shorthand sends the message
      written after it to the top item, so .:DoIt() is WithObjectStackTop():DoIt().
    | params:
    - `nSkip` Numeric - Zero-based distance from the top of the stack; 0 (the default) reads the top
      item. The shorthands ..: , ...: and ....: read positions 1, 2 and 3, and .:(n): reads position n.

    Returns The stored value, or NIL when no item exists at the requested position.

    |note: The with-object stack is driven by the ot4xb.ch commands WITH OBJECT, END WITH, WITH FRAME and
      END FRAME; application code normally uses those commands instead of calling these functions directly.

    |seealso: See also: {{ilink: <function WithObjectStackPush> WithObjectStackPush}}, {{ilink: <function WithObjectStackPop> WithObjectStackPop}}, {{ilink: <function WithObjectStackCount> WithObjectStackCount}}, {{ilink: <function WithObjectStackRecover> WithObjectStackRecover}} }}*/
XPPRET XPPENTRY WITHOBJECTSTACKTOP( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   UINT n = (UINT) _parLong(pl,1);
   ContainerHandle   con   = _conNew( pHMan->m_pWithObject->GetTos(n) );
   _conReturn(pl,con);
   _conRelease(con);
} 
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: WithObjectStackPush
            | _tg_: with_object
            | syntax_: `WithObjectStackPush( xValue )`
            | category: runtime/thread
            | _kw_: WithObjectStackPush, Function
   }}*/
/*{{|desc: Pushes a value on the current thread's with-object stack. The WITH OBJECT command translates to a
      call to this function, and the pushed value becomes reachable as with.item or through the .: shorthand.
    | params:
    - `xValue` Any - Value to store on top of the stack. Usually an object, but any value is accepted.

    Returns NIL }}*/
XPPRET XPPENTRY WITHOBJECTSTACKPUSH( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   pHMan->m_pWithObject->Push(_conParam(pl,1,0));
   _ret(pl);
} 
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: WithObjectStackPop
            | _tg_: with_object
            | syntax_: `WithObjectStackPop()`
            | category: runtime/thread
            | _kw_: WithObjectStackPop, Function
   }}*/
/*{{|desc: Pops the top value from the current thread's with-object stack. The END WITH command translates to
      a call to this function.

    Returns The popped value, or NIL when the stack is empty. }}*/
XPPRET XPPENTRY WITHOBJECTSTACKPOP( XppParamList pl)
{
   TTlsHeapManager * pHMan = GetTlsHeapManager();
   ContainerHandle con = pHMan->m_pWithObject->Pop();
   if(con == NULLCONTAINER ){_ret(pl); return;}
   _conReturn(pl,con);
   _conRelease(con);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: WithObjectStackCount
            | _tg_: with_object
            | syntax_: `WithObjectStackCount()`
            | category: runtime/thread
            | _kw_: WithObjectStackCount, Function
   }}*/
/*{{|desc: Returns the number of items in the current thread's with-object stack. The WITH FRAME command
      records this value so that END FRAME can restore the stack depth with WithObjectStackRecover().

    Returns Numeric - Current item count. }}*/
XPPRET XPPENTRY WITHOBJECTSTACKCOUNT( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  _retnl( pl,(LONG) pHMan->m_pWithObject->Count()); 
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: WithObjectStackRecover
            | _tg_: with_object
            | syntax_: `WithObjectStackRecover( nCount )`
            | category: runtime/thread
            | _kw_: WithObjectStackRecover, Function
   }}*/
/*{{|desc: Pops and discards items until the current thread's with-object stack holds at most nCount items.
      The END FRAME command uses it to unwind entries left on the stack when a WITH FRAME block is abandoned.
    | params:
    - `nCount` Numeric - Number of items to keep on the stack. Negative values are treated as 0.

    Returns NIL }}*/
XPPRET XPPENTRY WITHOBJECTSTACKRECOVER( XppParamList pl)
{
  TTlsHeapManager * pHMan = GetTlsHeapManager();
  int i = _parLong(pl,1,0);
  _ret( pl );  
  if(i < 0){ i = 0; }
  while( pHMan->m_pWithObject->Count() > ((DWORD) i) ){ _conReleaseM(pHMan->m_pWithObject->Pop() , 0);  }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_array_iterator
            | _tg_: with_object
            | syntax_: `ot4xb_array_iterator( aArray )`
            | category: array/iteration
            | _kw_: ot4xb_array_iterator, Function
   }}*/
/*{{|desc: Starts an array iterator on the current thread's with-object stack. The ITERATE ARRAY command
      translates to a call to this function followed by a while loop on ot4xb_array_iterator_step(), which
      advances the iterator and removes its state when the iteration ends. Because the state lives on the
      with-object stack, with.item reads the current item and with.index the current index inside the loop.
    | params:
    - `aArray` Array - The array to iterate. When the value is not an array or is an empty array, a
      special marker is pushed instead and the first ot4xb_array_iterator_step() call ends the iteration.

    Returns NIL

    |example: ```
      ITERATE ARRAY aItems VALID TYPES XPP_CHARACTER
         ? with.index, with.item
      END ITERATE
      ```

    |seealso: See also: {{ilink: <function ot4xb_array_iterator_step> ot4xb_array_iterator_step}}, {{ilink: <function ot4xb_array_iterator_index> ot4xb_array_iterator_index}} }}*/
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_array_iterator_step
            | _tg_: with_object
            | syntax_: `ot4xb_array_iterator_step( [nTypeMask] )`
            | category: array/iteration
            | _kw_: ot4xb_array_iterator_step, Function
   }}*/
/*{{|desc: Advances the array iterator started by ot4xb_array_iterator() and loads the next array item on top
      of the current thread's with-object stack, where with.item and with.index read it. The ITERATE ARRAY
      command generates this call as its loop condition.
    | params:
    - `nTypeMask` Numeric - Optional or-ed mask of XPP_* type constants. Items whose type is not in the
      mask are skipped. When omitted, every item is visited.

    Returns Logical - .T. when an item was loaded, .F. when the iteration is finished or no iterator is
      active. When the iteration ends, the iterator state is removed from the with-object stack. }}*/
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_array_iterator_index
            | _tg_: with_object
            | syntax_: `ot4xb_array_iterator_index()`
            | category: array/iteration
            | _kw_: ot4xb_array_iterator_index, Function
   }}*/
/*{{|desc: Returns the 1-based index of the current array item while inside an ITERATE ARRAY loop. The
      with.index shorthand translates to a call to this function.

    Returns Numeric - Current 1-based array index. Outside an active iterator loop the value is meaningless. }}*/
_XPP_REG_FUN_( OT4XB_ARRAY_ITERATOR_INDEX )
{
   _retnl(pl,(LONG) GetTlsHeapManager()->m_pWithObject->GetTosCtx(0));
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: TLS
            | syntax_: `TLS()`
            | category: runtime/thread
            | _kw_: TLS, Function
   }}*/
/*{{|desc: Returns the current thread's TLS expando object.

    Returns Object - Thread-local expando object backed by an internal OT4XB hash table.

    |note: Each thread has its own TLS object for application data. It behaves like _ot4xb_expando_(), but the
      backing hash table is local to the current thread. Properties can be read and written using normal expando
      syntax, for example:

    |example: ```
      TLS():mykey := xValue
      ? TLS():mykey
      TLS():mykey := NIL   // removes the property
      ``` }}*/
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
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
