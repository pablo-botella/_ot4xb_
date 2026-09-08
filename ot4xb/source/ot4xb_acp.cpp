//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
typedef BOOL ( __stdcall * _VirtualProtect_ft_ )( DWORD , DWORD , DWORD , DWORD* );
// -----------------------------------------------------------------------------------------------------------------
static DWORD pSymFuncFind = (DWORD) GetProcAddress(GetModuleHandle("xpprt1"),"__symFuncFind");
// -----------------------------------------------------------------------------------------------------------------
static XppFuncType _fp_break_hook_ = 0;
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ot4xb_task )
      // ---------------------------------------------------------------------------------
      typedef struct _tag_item_st
      {
         DWORD            id;
         HANDLE           hEvt;
         ContainerHandle  con;
         void*            cargo;
         DWORD            dwFlags;
         DWORD            dwReserved;
      } item_st;
      // ---------------------------------------------------------------------------------
      static LONG init( void );
      // ---------------------------------------------------------------------------------
      static CRITICAL_SECTION  s_cs;
      static TList*            s_list;
      static LONG              s_nn = init();
      // ---------------------------------------------------------------------------------
      static item_st* create_item( void* cargo )
      {
         item_st* item = (item_st*) _xgrab( sizeof( item_st ) );
         item->id    = InterlockedIncrement(&s_nn );
         item->hEvt  = CreateEvent(0,TRUE,FALSE,0);
         item->con   = _ot4xb_thread_new_();
         item->cargo = cargo;
         EnterCriticalSection(&s_cs);
         __try
         {
            DWORD nn = s_list->Count();
            DWORD nPos = (DWORD) -1;
            DWORD n;
            for( n = 0; n < nn ; n++ )
            {
               if( !s_list->Get(n) )
               {
                  nPos = n;
                  nn = 0;
               }
            }
            if(  nPos == (DWORD) -1 )
            {
               s_list->Add( (void*) item );
            }
            else
            {
               s_list->Replace(nPos,(void*) item );
            }
         }
         __finally
         {
            LeaveCriticalSection( &s_cs );
         }
         return item;
      }
      // ---------------------------------------------------------------------------------
      static LONG init( void )
      {
         InitializeCriticalSection(&s_cs);
         s_list = new TList;
         return 0;
      }
      // ---------------------------------------------------------------------------------
      // oThread:atEnd := {|| @ot4xb:_ot4xb_thread_pool_push_( con_t ) }
      static void run( XppParamList pl )
      {
         ContainerHandle* pcon =  0;
         ContainerHandle conr = _conNew(NULLCONTAINER);
         DWORD nParams = _partype(pl,0);
         DWORD sh      = (( _partype(pl,1) & XPP_NUMERIC ) ? 1  : 0 );
         DWORD dwFlags = ( sh ? _parLong(pl,1) : 0 );
         if( ( dwFlags & 0x4000 ) && (nParams == 2) && ( _partype(pl,1 + sh) & XPP_CHARACTER) )
         {
            DWORD dw = 0;
            pcon  = (ContainerHandle*) _pszParam_cb(pl,2,&dw);
            nParams = 0;
            if( pcon )
            {
               if(dw >= 8 )
               {
                  if( ((DWORD) pcon[0]) == ((dw >> 2) - 1) )
                  {
                     if( _conCheckType(pcon[1],XPP_BLOCK) )
                     {
                        nParams = (DWORD) pcon[0];
                     }
                  }
               }
               if( !nParams )
               {
                  if( pcon[0] == (ContainerHandle) ((dw >> 2) - 1) )
                  {
                     if( pcon[0]  )
                     {
                        _conReleasePa( &(pcon[1]) , (ULONG) pcon[0] );
                     }
                  }
                  _xfree((void*) pcon);
                  pcon = 0;
               }
            }
         }
         if( ! pcon )
         {
            nParams -= sh;
            if( nParams )
            {
               if( _partype(pl,1 + sh) & XPP_BLOCK )
               {
                  DWORD n;
                  pcon =  (ContainerHandle*) _xgrab( (nParams + 1) * sizeof(ContainerHandle) );
                  pcon[0] = (ContainerHandle) nParams;
                  for( n = 1; n <= nParams; n++ )
                  {
                     pcon[n] = _conParam(pl,n + sh ,0);
                  }
               }
            }
         }
         if( pcon )
         {
            item_st* item = create_item( (void*) pcon  );
            item->dwFlags = dwFlags;
            _conPutNL(conr,(LONG) item->id );
            _conMCallVoid( (ContainerHandle) item->con ,"start" , "_OT4XB_TASK_INTERNAL_PROC_", (LONG) item );
         }
         _conReturn(pl,conr);
         _conRelease( conr );
      }
      // ---------------------------------------------------------------------------------
      static void wait_any( XppParamList pl )
      {
         DWORD   nTimeOut   = (DWORD) _parLong(pl,2,0);
         HANDLE* event_list = 0;
         DWORD*  id_list    = 0;
         DWORD   count      = 0;
         DWORD   nId        = 0;
         DWORD n;
         EnterCriticalSection(&s_cs);
         __try
         {
            DWORD nn = s_list->Count();
            if( nn )
            {
               event_list = (HANDLE*) _xgrab( nn * sizeof( HANDLE ) );
               id_list = (DWORD*) _xgrab( nn * sizeof( DWORD ) );
               for( n = 0; n < nn; n++ )
               {
                  item_st* item = (item_st*) s_list->Get( n );
                  if( item )
                  {
                     if( item->hEvt )
                     {
                        if( DuplicateHandle( GetCurrentProcess(), item->hEvt, GetCurrentProcess(), &( event_list[ count ] ), SYNCHRONIZE, TRUE, 0 ) )
                        {
                           id_list[ count ] = item->id;
                           count++;
                        }
                     }
                  }
               }
            }
         }
         __finally
         {
            LeaveCriticalSection( &s_cs );
         }
         if( count )
         {
            DWORD result = WaitForMultipleObjects(count,event_list,FALSE,nTimeOut);
            if( (result >= WAIT_OBJECT_0) && ( result < ( WAIT_OBJECT_0 + count) ) )
            {
               nId = id_list[(result - WAIT_OBJECT_0)];
               EnterCriticalSection(&s_cs);
               __try
               {
                  DWORD nn = s_list->Count();
                  for( n = 0; n < nn ; n++ )
                  {
                     item_st* item   = (item_st*) s_list->Get(n);
                     if( item )
                     {
                        if( item->id == nId )
                        {
                           if( item->hEvt )
                           {
                              CloseHandle( item->hEvt );
                              item->hEvt = 0;
                           }
                           nn = 0; // stop search
                        }
                     }
                  }
               }
               __finally
               {
                  LeaveCriticalSection( &s_cs );
               }
            }
            for(n=0; n < count; n++ )
            {
               CloseHandle( event_list[n] );
               event_list[n] = 0;
            }
         }
         if( event_list )
         {
            _xfree((void*) event_list);
            event_list = 0;
         }
         if( id_list )
         {
            _xfree((void*) id_list);
            id_list = 0;
         }
         _retnl(pl,(LONG) nId);
      }
      // ---------------------------------------------------------------------------------
      static void wait( XppParamList pl )
      {
         if( _partype(pl,1) & XPP_UNDEF )
         {
            wait_any(pl);
            return;
         }
         ContainerHandle conr = _conNew(NULLCONTAINER);
         DWORD nId       = (DWORD) _parLong(pl,1,0);
         DWORD nTimeOut  = (DWORD) _parLong(pl,2,0);
         HANDLE hEvent   = INVALID_HANDLE_VALUE;
         EnterCriticalSection(&s_cs);
         __try
         {
            DWORD nn = s_list->Count();
            DWORD n;
            for( n = 0; n < nn ; n++ )
            {
               item_st* item   = (item_st*) s_list->Get(n);
               if( item )
               {
                  if( item->id == nId )
                  {
                     if( item->hEvt )
                     {
                        DuplicateHandle(GetCurrentProcess(),item->hEvt,GetCurrentProcess(),&hEvent,SYNCHRONIZE,TRUE,0);
                     }
                     else
                     {
                        hEvent = 0;
                     }
                     nn = 0; // stop search
                  }
               }
            }
         }
         __finally
         {
            LeaveCriticalSection( &s_cs );
         }
         if( hEvent && ( hEvent != INVALID_HANDLE_VALUE ) )
         {
            DWORD result = WaitForSingleObject(hEvent,nTimeOut);
            if( result == WAIT_OBJECT_0 )
            {
               _conPutL(conr,TRUE);
               EnterCriticalSection(&s_cs);
               __try
               {
                  DWORD nn = s_list->Count();
                  DWORD n;
                  for( n = 0; n < nn ; n++ )
                  {
                     item_st* item   = (item_st*) s_list->Get(n);
                     if( item )
                     {
                        if( item->id == nId )
                        {
                           if( item->hEvt )
                           {
                              CloseHandle( item->hEvt );
                              item->hEvt = 0;
                           }
                           nn = 0; // stop search
                        }
                     }
                  }
               }
               __finally
               {
                  LeaveCriticalSection( &s_cs );
               }
            }
            else
            {
               if( result == WAIT_TIMEOUT )
               {
                  _conPutL(conr,FALSE);
               }
            }
            CloseHandle( hEvent );
            hEvent = INVALID_HANDLE_VALUE;


         }
         else
         {
            if( hEvent != INVALID_HANDLE_VALUE )
            {
               _conPutL(conr,TRUE);
            }
         }
         _conReturn(pl,conr);
         _conRelease( conr );
      }
      // ---------------------------------------------------------------------------------
      static ContainerHandle pop_by_id(  DWORD nId  , BOOL destroy_event_first)
      {
         ContainerHandle result = 0;
         EnterCriticalSection(&s_cs);
         __try
         {
            DWORD nn = s_list->Count();
            DWORD n;
            for( n = 0; n < nn ; n++ )
            {
               item_st* item   = (item_st*) s_list->Get(n);
               if( item )
               {
                  if( item->id == nId )
                  {
                     if( destroy_event_first && item->hEvt )
                     {
                        CloseHandle( item->hEvt );
                        item->hEvt = 0;
                     }
                     else if( item->hEvt && ( WaitForSingleObject( item->hEvt, 0 ) == WAIT_OBJECT_0 ) )
                     {
                        // task finished but never waited on: a signaled event counts as done
                        CloseHandle( item->hEvt );
                        item->hEvt = 0;
                     }
                     if( !item->hEvt )
                     {
                        s_list->Replace(n,0);
                        result = item->con;
                        _xfree( (void*) item );
                        item = 0;
                     }
                     nn = 0; // stop search
                  }
               }
            }
         }
         __finally
         {
            LeaveCriticalSection( &s_cs );
         }
         return result;
      }
      // ---------------------------------------------------------------------------------
      static void pop( XppParamList pl )
      {
         if( _partype(pl,0) == 0 )
         {
            _retnl( pl , (LONG) s_list->Count() );
            return;
         }
         ContainerHandle conr = _conNew(NULLCONTAINER);
         ContainerHandle con_result = pop_by_id( (DWORD) _parLong(pl,1,0) , FALSE);
         if( con_result )
         {
            _conPut( conr , con_result );
            _conRelease( con_result );
         }
         _conReturn(pl,conr);
         _conRelease( conr );
      }
      // ---------------------------------------------------------------------------------
      static void worker( XppParamList pl )
      {
         item_st* item = (item_st*) _parnl(pl,1,0);
         if( item )
         {
            ContainerHandle con_thread = item->con;
            HANDLE hEvent = INVALID_HANDLE_VALUE;
            DWORD nn = reinterpret_cast<DWORD*>(item->cargo)[0];
            item->con = _conNew(NULLCONTAINER);
            DuplicateHandle(GetCurrentProcess(),item->hEvt,GetCurrentProcess(),&hEvent,EVENT_MODIFY_STATE,TRUE,0);
            GetTlsHeapManager()->m_dwOt4xbTaskId = item->id;
            _conEvalBa(  item->con,
                         reinterpret_cast<ContainerHandle*>(item->cargo)[1],
                         nn-1,
                         reinterpret_cast<ContainerHandle*>( _mk_ptr_(LPVOID,item->cargo, 8 ) )
                      );
            _conReleasePa( reinterpret_cast<ContainerHandle*>( _mk_ptr_(LPVOID,item->cargo, 4 )) , nn );
            GetTlsHeapManager()->m_dwOt4xbTaskId = 0;
            _xfree( item->cargo );
            item->cargo = 0;
            char sz[256]; ZeroMemory( sz,sizeof(sz) );
            wsprintf(sz, "{|| nFpCall(%i,%i) }" , (DWORD) _ot4xb_thread_pool_push_ , (DWORD) con_thread );
            ContainerHandle conb_end = _conNewCodeblock(sz );
            _conSetMember( con_thread , "atEnd" , conb_end );
            _conRelease( conb_end );
            conb_end = 0;
            SetEvent( hEvent );
            CloseHandle( hEvent );
            if( item->dwFlags & 0x8000 )
            {
               _conReleaseM( pop_by_id( item->id , TRUE) , 0 );
            }
         }
         _ret(pl);

      }
      // ---------------------------------------------------------------------------------
END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------
static BOOL VProtect( DWORD dwa, DWORD dws , DWORD dw , DWORD* pdw)
{
   static _VirtualProtect_ft_  vp = ( _VirtualProtect_ft_ ) GetProcAddress(GetModuleHandle("kernel32"),"VirtualProtect");
   if( !vp ) return FALSE; // win9x
   return (*vp)(dwa,dws,dw,pdw);
}
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _ot4xb_task_internal_proc_
            | syntax_: `_ot4xb_task_internal_proc_( nTaskCargo )`
            | category: tasks/internal
            | export: _OT4XB_TASK_INTERNAL_PROC_
            | source: ot4xb_acp.cpp:_OT4XB_TASK_INTERNAL_PROC_
            | _kw_: _ot4xb_task_internal_proc_, Function
   }}*/
/*{{|desc: Internal worker entry point used by OT4XB task threads.
    | params:
    - `nTaskCargo` numeric - Internal task cargo pointer created by ot4xb_task_run().

    Returns nil - Always returns NIL.

    |note: This is an internal worker function and must not be called directly from application code.

    |seealso: See also: {{ilink: <function ot4xb_task_run> ot4xb_task_run}}, {{ilink: <function ot4xb_task_id> ot4xb_task_id}}, {{ilink: <function ot4xb_task_wait> ot4xb_task_wait}}, ot4xb_task_pop }}*/
_XPP_REG_FUN_( _OT4XB_TASK_INTERNAL_PROC_ ){ ot4xb_task::worker(pl); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_task_id
            | syntax_: `ot4xb_task_id()`
            | category: tasks
            | export: OT4XB_TASK_ID
            | source: ot4xb_acp.cpp:OT4XB_TASK_ID
            | _kw_: ot4xb_task_id, Function
   }}*/
/*{{|desc: Returns the OT4XB task id associated with the current thread.

    Returns numeric - Current OT4XB task id, or 0 when the current thread is not running an OT4XB task worker.

    |seealso: See also: {{ilink: <function ot4xb_task_run> ot4xb_task_run}}, {{ilink: <function ot4xb_task_wait> ot4xb_task_wait}}, ot4xb_task_pop }}*/
_XPP_REG_FUN_( OT4XB_TASK_ID              ){ _retnl(pl,(LONG)GetTlsHeapManager()->m_dwOt4xbTaskId ); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_task_run
            | syntax_: `ot4xb_task_run( bBlock, ... )`
            | category: tasks
            | export: OT4XB_TASK_RUN
            | source: ot4xb_acp.cpp:OT4XB_TASK_RUN
            | _kw_: ot4xb_task_run, Function
   }}*/
/*{{|desc: Evaluates a code block in a separate thread from the OT4XB thread pool.
    | params:
    - `bBlock` codeblock - Code block to evaluate in the task thread.
    - `...` any - Parameters passed to the code block.

    Returns numeric - Task id used by ot4xb_task_wait() and ot4xb_task_pop(), or NIL if a task cannot be
      started.

    |note: The task result remains stored until it is retrieved with ot4xb_task_pop().

    |seealso: See also: {{ilink: <function ot4xb_task_id> ot4xb_task_id}}, {{ilink: <function ot4xb_task_wait> ot4xb_task_wait}}, ot4xb_task_pop }}*/
_XPP_REG_FUN_( OT4XB_TASK_RUN             ){ ot4xb_task::run(pl); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_task_wait
            | syntax_: `ot4xb_task_wait( nTaskId, [nTimeout] )`
            | category: tasks
            | export: OT4XB_TASK_WAIT
            | source: ot4xb_acp.cpp:OT4XB_TASK_WAIT
            | _kw_: ot4xb_task_wait, Function
   }}*/
/*{{|desc: Waits for an OT4XB task to finish, or checks its completion state.
    | params:
    - `nTaskId` numeric - Task id returned by ot4xb_task_run().
    - `nTimeout` numeric - Time to wait in milliseconds. 0 checks the current status without waiting. -1
      waits indefinitely.

    Returns logical/nil - TRUE when the task has finished, FALSE when the timeout expires, or NIL when the
      task is not found or its result was already retrieved.

    |note: When nTaskId is omitted, OT4XB waits for any pending task and returns the id of the task that
      finished, or 0 if none finished before the timeout.

    |seealso: See also: {{ilink: <function ot4xb_task_run> ot4xb_task_run}}, ot4xb_task_pop }}*/
_XPP_REG_FUN_( OT4XB_TASK_WAIT            ){ ot4xb_task::wait(pl); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_task_pop
            | syntax_: `ot4xb_task_pop( nTaskId )`
            | category: tasks
            | export: OT4XB_TASK_POP
            | source: ot4xb_acp.cpp:OT4XB_TASK_POP
            | _kw_: ot4xb_task_pop, Function
   }}*/
/*{{|desc: Retrieves the result of a finished OT4XB task and releases the task resources.
    | params:
    - `nTaskId` numeric - Task id returned by ot4xb_task_run().

    Returns any/nil - The value returned by the task code block, or NIL if the task is still running, was not
      found, or its result was already retrieved.

    |note: Calling ot4xb_task_pop() without parameters returns the current size of the internal task list.

    |seealso: See also: {{ilink: <function ot4xb_task_run> ot4xb_task_run}}, ot4xb_task_wait }}*/
_XPP_REG_FUN_( OT4XB_TASK_POP             ){ ot4xb_task::pop(pl); }
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_apc_post_cb
            | syntax_: `ot4xb_apc_post_cb( oThread, bBlock, ... )`
            | category: threads/apc
            | export: OT4XB_APC_POST_CB
            | source: ot4xb_acp.cpp:OT4XB_APC_POST_CB
            | _kw_: ot4xb_apc_post_cb, Function
   }}*/
/*{{|desc: Queues a code block APC for a target thread.
    | params:
    - `oThread` object - Xbase++ Thread object for the target thread.
    - `bBlock` codeblock - Code block to evaluate in the target thread.
    - `...` any - Parameters passed to the code block.

    Returns logical - TRUE if the APC was queued, otherwise FALSE.

    |note: OT4XB queues the code block with QueueUserAPC() and returns immediately. The code block result is
      not returned to the caller.

    |note: The target thread must enter an alertable wait state for the APC to run the queued code block, for
      example by calling @kernel32:SleepEx( nMilliseconds, 1 ).

    |seealso: See also: {{ilink: <function ot4xb_apc_send_cb> ot4xb_apc_send_cb}}, ot4xb_apc_post_cb_h }}*/
_XPP_REG_FUN_( OT4XB_APC_POST_CB )
{
   TXppParamList xpp(pl);
   HANDLE hThread = _ot4xb_ThreadObject2hThread( xpp[1]->GetT(XPP_OBJECT));
   xpp[0]->PutBool(FALSE);
   if( hThread && xpp[2]->CheckType(XPP_BLOCK) )
   {
      DWORD  dw  = xpp.PCount();
      DWORD* pdw = (DWORD*) _xgrab((dw + 2) * sizeof(DWORD));
      DWORD  n;
      pdw[0] = (dw - 2 );
      for( n = 1; n < dw;n++){ pdw[n] = (DWORD) _conNew( xpp[(n+1)]->Get() );}
      if( QueueUserAPC((PAPCFUNC)_ot4xb_apcproc_cb_,hThread,(ULONG_PTR)pdw) == 0 )
      {
         for( n = 1; n < dw;n++){ _conRelease( (ContainerHandle)pdw[n] ); }
         _xfree( (void*) pdw );
         return;
      }
      xpp[0]->PutBool(TRUE);
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_apc_post_cb_h
            | syntax_: `ot4xb_apc_post_cb_h( hThread, bBlock, ... )`
            | category: threads/apc
            | export: OT4XB_APC_POST_CB_H
            | source: ot4xb_acp.cpp:OT4XB_APC_POST_CB_H
            | _kw_: ot4xb_apc_post_cb_h, Function
   }}*/
/*{{|desc: Queues a code block APC for a target thread handle.
    | params:
    - `hThread` numeric - Windows thread handle for the target thread.
    - `bBlock` codeblock - Code block to evaluate in the target thread.
    - `...` any - Parameters passed to the code block.

    Returns logical - TRUE if the APC was queued, otherwise FALSE.

    |note: OT4XB queues the code block with QueueUserAPC() and returns immediately. The code block result is
      not returned to the caller.

    |note: The thread handle can be obtained from an Xbase++ Thread object by calling the OT4XB C API function
      with the @ot4xb: syntax: @ot4xb:_ot4xb_ThreadObject2hThread( oThread ). Pass 0 to obtain the current
      thread handle: @ot4xb:_ot4xb_ThreadObject2hThread( 0 ).

    |note: The target thread must enter an alertable wait state for the APC to run the queued code block, for
      example by calling @kernel32:SleepEx( nMilliseconds, 1 ).

    |seealso: See also: {{ilink: <function ot4xb_apc_send_cb> ot4xb_apc_send_cb}}, ot4xb_apc_post_cb }}*/
_XPP_REG_FUN_( OT4XB_APC_POST_CB_H )
{
   TXppParamList xpp(pl);
   HANDLE hThread = (HANDLE) xpp[1]->GetLong();
   if( !hThread ){ xpp[0]->PutBool(FALSE); return;}
   xpp[0]->PutBool(FALSE);
   if( hThread && xpp[2]->CheckType(XPP_BLOCK) )
   {
      DWORD  dw  = xpp.PCount();
      DWORD* pdw = (DWORD*) _xgrab((dw + 2) * sizeof(DWORD));
      DWORD  n;
      pdw[0] = (dw - 2 );
      for( n = 1; n < dw;n++){ pdw[n] = (DWORD) _conNew( xpp[(n+1)]->Get() );}
      if( QueueUserAPC((PAPCFUNC)_ot4xb_apcproc_cb_,hThread,(ULONG_PTR)pdw) == 0 )
      {
         for( n = 1; n < dw;n++){ _conRelease( (ContainerHandle)pdw[n] ); }
         _xfree( (void*) pdw );
         return;
      }
      xpp[0]->PutBool(TRUE);
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_apcproc_stksync_
            | syntax_: `void _ot4xb_apcproc_stksync_( DWORD * pdw )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: __ot4xb_apcproc_stksync_@4
            | _kw_: _ot4xb_apcproc_stksync_, Function
   }}*/
/*{{|desc: APC procedure queued by ot4xb_apc_send_cb(). Runs on the target thread: pushes the packed
      arguments, calls the target function, then signals the completion event for the caller.
    | params:
    - `pdw` DWORD * - Packed call block: pdw[0] event to signal on completion, pdw[1] index of the
      last argument slot, pdw[2] the function pointer to call, then the arguments pushed right to left.

    Returns void }}*/
OT4XB_API void __stdcall _ot4xb_apcproc_stksync_(DWORD* pdw )
{
   DWORD dw;
   LONG  sp1 = 0;
   DWORD n;

   __asm mov sp1 ,esp;
   for( n = pdw[1]; n > 2 ; n-- )
   {
      dw = pdw[n];
      __asm mov eax,dw;
      __asm push eax;
   }
   dw = pdw[2];
   __asm mov eax , dw;
   __asm call eax;
   __asm mov esp ,sp1;
   SetEvent( (HANDLE) pdw[0] );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_apc_send_cb
            | syntax_: `ot4xb_apc_send_cb( oThread, bBlock, ... )`
            | category: threads/apc
            | export: OT4XB_APC_SEND_CB
            | source: ot4xb_acp.cpp:OT4XB_APC_SEND_CB
            | _kw_: ot4xb_apc_send_cb, Function
   }}*/
/*{{|desc: Synchronously evaluates a code block in a target thread that enters an alertable wait state.
    | params:
    - `oThread` object - Xbase++ Thread object for the target thread.
    - `bBlock` codeblock - Code block to evaluate in the target thread.
    - `...` any - Parameters passed to the code block.

    Returns any/nil - The value returned by the code block, or NIL if the target thread cannot be resolved or
      the arguments are invalid.

    |note: OT4XB queues the code block with QueueUserAPC() and waits until the APC procedure signals
      completion. The target thread must enter an alertable wait state for the APC to execute, for example by
      calling @kernel32:SleepEx( nMilliseconds, 1 ).

    |note: Because this function waits for the code block result, it can deadlock if the target thread does not
      enter an alertable wait state, or if the target thread waits back on the caller while the caller is
      blocked in ot4xb_apc_send_cb().

    |note: If oThread refers to the current thread, OT4XB evaluates the code block directly instead of queuing
      an APC.

    |seealso: See also: {{ilink: <function ot4xb_apc_post_cb> ot4xb_apc_post_cb}}, ot4xb_apc_post_cb_h }}*/
_XPP_REG_FUN_( OT4XB_APC_SEND_CB )
{
   HANDLE hThread;
   TXppParamList xpp(pl);
   DWORD np = xpp.PCount();
   DWORD dw,n;

   if( np < 2 || !(xpp[1]->CheckType(XPP_OBJECT) && xpp[2]->CheckType(XPP_BLOCK))){ return;}

   hThread    = _ot4xb_ThreadObject2hThread( xpp[1]->GetT(XPP_OBJECT));

   if( hThread == _ot4xb_ThreadObject2hThread(0) ) // same thread
   {
      LONG   sp1 = 0;
      __asm mov sp1 ,esp;
      for( n=np; n > 2;n--)
      {
         xpp[n]->con();
         __asm push eax;
      }

      dw = np - 2;
      __asm mov eax , dw;
      __asm push eax;

      xpp[2]->con();
      __asm push eax;

      xpp[0]->con();
      __asm push eax;

      dw = (DWORD) _conEvalB;
      __asm mov eax , dw;
      __asm call eax;
      __asm mov esp ,sp1;
      return;
   }
   if( hThread )
   {
      DWORD* pdw = (DWORD*) _xgrab((np + 8) * sizeof(DWORD));
      pdw[0] = (DWORD) CreateEvent(0,0,0,0);
      pdw[1] = np+3;
      pdw[2] = (DWORD) _conEvalB;
      pdw[3] = (DWORD) xpp[0]->con();
      pdw[4] = (DWORD) xpp[2]->con();
      pdw[5] = np-2;
      for( n = 3; n <= np ; n++ )
      {
         pdw[3+n] = (DWORD) xpp[n]->con();
      }
      if( QueueUserAPC((PAPCFUNC)_ot4xb_apcproc_stksync_,hThread,(ULONG_PTR)pdw) )
      {
         WaitForSingleObject((HANDLE) pdw[0] , INFINITE );
      }
      CloseHandle( (HANDLE) pdw[0] );
      _xfree( (void*) pdw );
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_ThreadObject2hThread
            | syntax_: `HANDLE _ot4xb_ThreadObject2hThread( ContainerHandle cono )`
            | category: runtime/thread
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_ThreadObject2hThread
            | _kw_: _ot4xb_ThreadObject2hThread, Function
   }}*/
/*{{|desc: Resolves an Xbase++ thread reference to a native Windows thread handle.
    | params:
    - `cono` ContainerHandle - Xbase++ Thread object, a numeric Xbase++ thread id, or NULLCONTAINER
      for the current thread.

    Returns HANDLE - Windows thread handle, or 0 if the thread cannot be resolved. }}*/
OT4XB_API HANDLE _ot4xb_ThreadObject2hThread(ContainerHandle cono)
{
   HANDLE hThread = 0;
   LONG   xbId    = 0;
   if( cono == NULLCONTAINER ) xbId = _conCallLong("ThreadID");
   else if( _conCheckType(cono,XPP_OBJECT) ) xbId = _conGetNLMember(cono,"ThreadId");
   else if( _conCheckType(cono,XPP_NUMERIC) ) _conGetLong(cono,&xbId);
   if( xbId > 0 )
   {
      ContainerHandle  cona = _conCallCon("ThreadInfo",2,xbId);
      hThread = (HANDLE) _conArrayGetNL(cona,1,1,0);
      _conRelease(cona);
   }
   return hThread;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_thread_new_
            | syntax_: `ContainerHandle _ot4xb_thread_new_( void )`
            | category: runtime/thread
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_thread_new_
            | _kw_: _ot4xb_thread_new_, Function
   }}*/
/*{{|desc: Returns a ready-to-use Xbase++ Thread object, reusing one from the internal thread pool when
      available, otherwise creating a new Thread object.

    Returns ContainerHandle - Thread object taken from the pool, or a newly created one. }}*/
OT4XB_API ContainerHandle _ot4xb_thread_new_(void)
{
   ContainerHandle cono = _ot4xb_thread_pool_pop_();
   if( cono ) return cono;
   return _conNewObj("Thread",NULLCONTAINER);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_thread_
            | syntax_: `ContainerHandle _ot4xb_thread_( LPTHREAD_START_ROUTINE fp, void * lp )`
            | category: runtime/thread
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_thread_
            | _kw_: _ot4xb_thread_, Function
   }}*/
/*{{|desc: Starts a new Xbase++ thread that runs a C function pointer. It obtains a Thread object and calls
      its Start method so the thread executes fp(lp).
    | params:
    - `fp` LPTHREAD_START_ROUTINE - Function pointer to run in the new thread.
    - `lp` void * - Argument passed to fp.

    Returns ContainerHandle - The Xbase++ Thread object running the function. }}*/
OT4XB_API ContainerHandle _ot4xb_thread_( LPTHREAD_START_ROUTINE fp , void* lp )
{
   ContainerHandle pcon[4];
   ContainerHandle conr = _conNew(NULLCONTAINER);
   pcon[0] = _ot4xb_thread_new_();
   pcon[1] = _conPutC(NULLCONTAINER,"nFpCall");
   pcon[2] = _conPutNL(NULLCONTAINER,(LONG) fp);
   pcon[3] = _conPutNL(NULLCONTAINER,(LONG) lp);
   _conCallMethodPa(conr,"Start",4,pcon);
   _conReleaseM( conr, pcon[1],pcon[2],pcon[3],0);
   return pcon[0];
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void __cdecl _ot4xb_fp_map_break_hook_(XppParamList pl)
{
   ContainerHandle con = _conParam(pl,1,0);
   THashTable * pHt = GetTls_ht();
   THDictKey* phk  = new THDictKey("break_hook_parameter",(DWORD) -1,TRUE);
   THDictItem* phi = new THDictItem(phk,con);
   _conRelease(con);
   phi->AddToHashTable( pHt );
   delete phk;
   ( *_fp_break_hook_)(pl);
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_setup_break_hook_
            | syntax_: `void _ot4xb_setup_break_hook_( void )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_setup_break_hook_
            | _kw_: _ot4xb_setup_break_hook_, Function
   }}*/
/*{{|desc: Installs, once, a hook on the Xbase++ runtime _BREAK function so the value passed to Break() is
      stored per thread before the original _BREAK runs.

    Returns void }}*/
OT4XB_API void __cdecl _ot4xb_setup_break_hook_(void)
{
   if( _fp_break_hook_ == 0 )
   {
      DWORD fps = (DWORD) GetProcAddress(GetModuleHandle("xpprt1"),"_BREAK");
      _fp_break_hook_ = (XppFuncType) _ot4xb_fp_map_(fps, (DWORD) _ot4xb_fp_map_break_hook_ );
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_redirect_xppapi_call_ex_
            | syntax_: ```
            | category: threads , tasks
                 void _ot4xb_redirect_xppapi_call_ex_( XppParamList pl, ContainerHandle Self, LPSTR pMethodName, XppFuncType pBreak )
              ```
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_redirect_xppapi_call_ex_
            | _kw_: _ot4xb_redirect_xppapi_call_ex_, Function
   }}*/
/*{{|desc: Forwards the parameters of the current Xbase++ call to method pMethodName of object Self and
      returns its result. If the method returns 333 and pBreak is set, pBreak is called instead.
    | params:
    - `pl` XppParamList - Parameter list of the current Xbase++ call.
    - `Self` ContainerHandle - Object that receives the redirected method call, passed as argument 0.
    - `pMethodName` LPSTR - Name of the method to invoke on Self.
    - `pBreak` XppFuncType - Fallback called when the method returns 333; may be 0.

    Returns void }}*/
OT4XB_API void __cdecl _ot4xb_redirect_xppapi_call_ex_(XppParamList pl , ContainerHandle Self , LPSTR pMethodName , XppFuncType pBreak )
{
   ULONG nParams = _partype(pl,0);
   ContainerHandle* pcon = (ContainerHandle*) _xgrab( sizeof(ContainerHandle) * ( nParams +2 ) );
   BOOL*            pref = (BOOL*) _xgrab( sizeof(BOOL) * ( nParams +2 ) );
   UINT n;
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ULONG result;
   for( n=1; n <= nParams; n++ )
   {
      pcon[n] = _conParam(pl,n,&(pref[n]) );
   }
   pcon[0] = Self;
   result = _conCallMethodPa(conr,pMethodName,nParams+1,pcon );
   for( n=1; n <= nParams; n++ )
   {
      if( !pref[n] )
      {
         _conRelease(pcon[n]);
      }
   }
   if( pcon ) { _xfree( (void*) pcon ); pcon = 0; }
   if( pref ) { _xfree( (void*) pref ); pref = 0; }
   if( result == 333 )
   {
      if( pBreak)
      {
         _conRelease(conr);
         (*pBreak)(pl);
         return;
      }
   }
   _conReturn( pl,conr);
   _conRelease(conr);

}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_redirect_xppapi_call_
            | syntax_: `void _ot4xb_redirect_xppapi_call_( XppParamList pl, ContainerHandle Self, LPSTR pMethodName )`
            | category: threads , tasks
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_redirect_xppapi_call_
            | _kw_: _ot4xb_redirect_xppapi_call_, Function
   }}*/
/*{{|desc: Forwards the parameters of the current Xbase++ call to method pMethodName of object Self and
      returns its result to the caller.
    | params:
    - `pl` XppParamList - Parameter list of the current Xbase++ call.
    - `Self` ContainerHandle - Object that receives the redirected method call, passed as argument 0.
    - `pMethodName` LPSTR - Name of the method to invoke on Self.

    Returns void }}*/
OT4XB_API void __cdecl _ot4xb_redirect_xppapi_call_(XppParamList pl , ContainerHandle Self , LPSTR pMethodName )
{
   ULONG nParams = _partype(pl,0);
   ContainerHandle* pcon = (ContainerHandle*) _xgrab( sizeof(ContainerHandle) * ( nParams +2 ) );
   BOOL*            pref = (BOOL*) _xgrab( sizeof(BOOL) * ( nParams +2 ) );
   UINT n;
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ULONG result;
   for( n=1; n <= nParams; n++ )
   {
      pcon[n] = _conParam(pl,n,&(pref[n]) );
   }
   pcon[0] = Self;
   result = _conCallMethodPa(conr,pMethodName,nParams+1,pcon );
   for( n=1; n <= nParams; n++ )
   {
      if( !pref[n] )
      {
         _conRelease(pcon[n]);
      }
   }
   _conReturn( pl,conr);
   _conRelease(conr);
   if( pcon ) { _xfree( (void*) pcon ); }
   if( pref ) { _xfree( (void*) pref ); }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_hook_func_in_mod_
            | syntax_: `DWORD _ot4xb_hook_func_in_mod_( HMODULE hFrom, LPSTR pDllFrom, LPSTR pFName, DWORD pfNew )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_hook_func_in_mod_
            | _kw_: _ot4xb_hook_func_in_mod_, Function
   }}*/
/*{{|desc: Redirects the calls that module hFrom makes to function pFName of DLL pDllFrom by patching its
      import table entry to pfNew. Returns the original address so the caller can chain to it.
    | params:
    - `hFrom` HMODULE - Module whose import table is patched.
    - `pDllFrom` LPSTR - Name of the imported DLL that exports the function.
    - `pFName` LPSTR - Name of the imported function to redirect.
    - `pfNew` DWORD - Address of the replacement function.

    Returns DWORD - Original function address on success, or 0 on failure. }}*/
OT4XB_API DWORD _ot4xb_hook_func_in_mod_(HMODULE hFrom,LPSTR pDllFrom,LPSTR pFName, DWORD pfNew)
{
   DWORD pfOld;
   PIMAGE_DOS_HEADER pdh;
   PIMAGE_NT_HEADERS pnth;
   PIMAGE_IMPORT_DESCRIPTOR pid;
   PIMAGE_THUNK_DATA ptd;

   if(IsBadCodePtr(reinterpret_cast<FARPROC>(pfNew)) ) return 0;
   pfOld = (DWORD) GetProcAddress(GetModuleHandle(pDllFrom),pFName);
   if(!pfOld) return 0;
   pdh = (PIMAGE_DOS_HEADER)hFrom;
   if(IsBadReadPtr(pdh, sizeof(IMAGE_DOS_HEADER))) return 0;
   if(pdh->e_magic != IMAGE_DOS_SIGNATURE ) return 0;
   pnth = _mk_ptr_(PIMAGE_NT_HEADERS , pdh, pdh->e_lfanew);
   if(IsBadReadPtr(pnth, sizeof(IMAGE_NT_HEADERS))) return 0;
   if(pnth->Signature != IMAGE_NT_SIGNATURE) return 0;
   pid = _mk_ptr_( PIMAGE_IMPORT_DESCRIPTOR,
                  pdh,
                  pnth->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress
                );
   if( pid == ((PIMAGE_IMPORT_DESCRIPTOR)pnth)) return 0;
   while ( pid->Name )
   {
      LPSTR dll_name = _mk_ptr_(LPSTR, pdh, pid->Name);
      if(lstrcmpi( dll_name , pDllFrom) == 0) break;
      pid++;
   }
   if(pid->Name == 0) return 0;
   ptd = _mk_ptr_(PIMAGE_THUNK_DATA, pdh, pid->FirstThunk);
   while(ptd->u1.Function)
   {
      if( ptd->u1.Function == pfOld )
      {
         DWORD dw = 0;
         VProtect((DWORD) &ptd->u1.Function,4,4,&dw);
         ptd->u1.Function = pfNew;
         VProtect( (DWORD) &ptd->u1.Function,4,dw,&dw);
         return pfOld;
      }
      ptd++;
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_find_sym_
            | syntax_: `DWORD _ot4xb_find_sym_( LPSTR p )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_find_sym_
            | _kw_: _ot4xb_find_sym_, Function
   }}*/
/*{{|desc: Looks up an Xbase++ runtime symbol by name and returns its function pointer.
    | params:
    - `p` LPSTR - Symbol name to look up.

    Returns DWORD - Function pointer of the symbol, or 0 if it is not found. }}*/
OT4XB_API DWORD _ot4xb_find_sym_(LPSTR p)
{
   if( p )
   {
      DWORD* pdw = 0;
      LONG sp1;
      __asm mov sp1 ,esp;
      __asm mov ecx , pSymFuncFind;
      __asm mov eax , p;
      __asm call ecx;
      __asm mov pdw ,eax;
      __asm mov eax ,sp1;
      __asm mov esp ,eax;
      if( pdw ) return pdw[1];
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_fp_map_
            | syntax_: `DWORD _ot4xb_fp_map_( DWORD fps, DWORD fpd )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_fp_map_
            | _kw_: _ot4xb_fp_map_, Function
   }}*/
/*{{|desc: Redirects a function: writes a jump to fpd at the entry of the function at fps and returns a
      callable pointer to the original (its relocated first bytes followed by a jump back). Recognizes
      several prologue shapes; returns 0 if none matches or the memory cannot be unprotected.
    | params:
    - `fps` DWORD - Address of the function to redirect (source).
    - `fpd` DWORD - Address of the replacement function (destination).

    Returns DWORD - Pointer that calls the original function, or 0 on failure. }}*/
OT4XB_API DWORD _ot4xb_fp_map_(DWORD fps,DWORD fpd)
{
   DWORD dws = 0;
   DWORD dw;
   if( (!fps) || (!fpd) ) return 0;
   if( VProtect(fps,12,4,&dws) )
   {
      LPBYTE fpn = (LPBYTE) _pgrab(16);
      _bcopy( fpn , (LPBYTE) fps,12 );
      _mk_ptr_(BYTE* ,fps,0)[0] = 0xE9;
      _mk_ptr_(DWORD*,fps,1)[0] = (fpd - (fps+5));

      if( fpn[0] == 0xFF ) // jmp far
      {
         VProtect((DWORD)fpn,6,64,&dw);
      }
      else if( fpn[0] == 0xE9 )  // JMP near
      {
         _mk_ptr_(LONG* ,fpn,1)[0] += (((LONG) fps) - ((LONG) fpn)); // (fps+5) - (fpn+5)
         VProtect((DWORD)fpn,5,64,&dw);
      }
      else if(  (fpn[0] == 0x55) &&                    // 55                 push ebp               00
                (_mk_ptr_(WORD*,fpn,1)[0] == 0x158B)&& // 8B 15 XX XX XX XX  mov  edx, ds:TlsIndex  01 02 03 04 05 06
                (_mk_ptr_(WORD*,fpn,7)[0] == 0xEC8B)   // 8B EC              mov ebp , esp          07 08
             )                                         // E9 XX XX XX XX     jmp restoration_point  09 10 11 12 13
      {
         DWORD dw_src = _mk_ptr_(DWORD,fpn,9);
         DWORD dw_dst = _mk_ptr_(DWORD,fps,9);

         _mk_ptr_(BYTE* ,dw_src,0)[0] = 0xE9;
         _mk_ptr_(DWORD*,dw_src,1)[0] = (dw_dst - (dw_src+5));
         VProtect((DWORD)fpn,14,64,&dw);
      }
      else if((_mk_ptr_(WORD*,fpn,0)[0] == 0x8B55) && (fpn[2] == 0x0D))
      {
         DWORD dw_src = _mk_ptr_(DWORD,fpn,7);
         DWORD dw_dst = _mk_ptr_(DWORD,fps,7);

         _mk_ptr_(BYTE* ,dw_src,0)[0] = 0xE9;
         _mk_ptr_(DWORD*,dw_src,1)[0] = (dw_dst - (dw_src+5));
         VProtect((DWORD)fpn,12,64,&dw);
      }
      else
      {
         _bcopy((LPBYTE) fps,fpn,12 );
         _pfree( (void*) fpn );
         fpn = 0;
      }
      VProtect(fps,12,dws,&dws);
      return (DWORD) fpn;
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_fp_map2_
            | syntax_: `void _ot4xb_fp_map2_( DWORD fps, DWORD fpd )`
            | category: function-pointer
            | header: ot4xb_c_exported.h
            | mangled-name: _ot4xb_fp_map2_
            | _kw_: _ot4xb_fp_map2_, Function
   }}*/
/*{{|desc: Redirects a function by writing a jump to fpd at the entry of the function at fps. Unlike
      _ot4xb_fp_map_() it keeps no way to call the original.
    | params:
    - `fps` DWORD - Address of the function to redirect (source).
    - `fpd` DWORD - Address of the replacement function (destination).

    Returns void }}*/
OT4XB_API void _ot4xb_fp_map2_(DWORD fps,DWORD fpd)
{
   DWORD dws = 0;
   if( (!fps) || (!fpd) ) return ;
   if( VProtect(fps,5,4,&dws) )
   {
      _mk_ptr_(BYTE* ,fps,0)[0] = 0xE9;
      _mk_ptr_(DWORD*,fps,1)[0] = (fpd - (fps+5));
      VProtect(fps,5,dws,&dws);
   }
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ot4xb_apcproc_cb_
            | syntax_: `void _ot4xb_apcproc_cb_( DWORD * pdw )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: __ot4xb_apcproc_cb_@4
            | _kw_: _ot4xb_apcproc_cb_, Function
   }}*/
/*{{|desc: APC procedure queued by ot4xb_apc_post_cb() and ot4xb_apc_post_cb_h(). On the target thread it
      evaluates the queued code block with its parameters and releases the block. No result is returned.
    | params:
    - `pdw` DWORD * - Packed block: pdw[0] parameter count, pdw[1] the code block, and pdw[2] upward
      the parameters, all as containers.

    Returns void }}*/
OT4XB_API void __stdcall _ot4xb_apcproc_cb_(DWORD* pdw )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   LONG sp1 = 0;
   DWORD dw,n;

   __asm mov sp1 ,esp;
   for( n = pdw[0]; n; n-- )
   {
      dw = pdw[n+1];
      __asm mov eax , dw;
      __asm push eax;
   }
   dw = pdw[0];
   __asm mov eax , dw;
   __asm push eax;

   dw = pdw[1];
   __asm mov eax , dw;
   __asm push eax;

   dw = (DWORD) conr;
   __asm mov eax , dw;
   __asm push eax;

   dw = (DWORD) _conEvalB;
   __asm mov eax , dw;
   __asm call eax;
   __asm mov esp ,sp1;

   for( n = 1; n <= pdw[0] ; n++ ){ if( pdw[n]) _conRelease( (ContainerHandle) ((void*) pdw[n]) ); }
   _xfree( (void*) pdw);
   _conRelease( conr );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase call function 
static void __stdcall _ot4xb_apc_ratxbf_(DWORD* pdw)
{
   pdw[1] = _conCallPa((ContainerHandle)pdw[2],(LPSTR)pdw[3],(ULONG)pdw[4],_mk_ptr_( ContainerHandle*,pdw,20));
   if( pdw[0] ){ SetEvent( (HANDLE) pdw[0] ); }
}
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase call method 
static void __stdcall _ot4xb_apc_ratxbm_(DWORD* pdw)
{
   pdw[1] = _conCallMethodPa((ContainerHandle)pdw[2],(LPSTR)pdw[3],(ULONG)pdw[4],_mk_ptr_( ContainerHandle*,pdw,20));
   if( pdw[0] ){ SetEvent( (HANDLE) pdw[0] ); }
}
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase set member
static  void __stdcall _ot4xb_apc_ratxbs_(DWORD* pdw)
{
   pdw[1] = _conSetMember((ContainerHandle)pdw[5],(LPSTR)pdw[3],(ContainerHandle)pdw[6]);
   if( pdw[0] ){ SetEvent( (HANDLE) pdw[0] ); }
}
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase get member
static  void __stdcall _ot4xb_apc_ratxbg_(DWORD* pdw)
{
   pdw[1] = _conGetMember((ContainerHandle)pdw[5],(LPSTR)pdw[3],(ContainerHandle)pdw[2]);
   if( pdw[0] ){ SetEvent( (HANDLE) pdw[0] ); }
}
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase internal function 
/*{{begin-c-function}}*/
/*{{c-function_: _ratx_if_
            | syntax_: `DWORD _ratx_if_( DWORD dw )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: _ratx_if_
            | _kw_: _ratx_if_, Function
   }}*/
/*{{|desc: Returns the run-at-thread APC procedure for an operation code: 1 call function, 2 call method,
      3 set member, 4 get member; 0 for any other code.
    | params:
    - `dw` DWORD - Operation selector (1 call function, 2 call method, 3 set member, 4 get member).

    Returns DWORD - Address of the matching APC procedure, or 0 for an unknown code. }}*/
OT4XB_API DWORD __cdecl _ratx_if_(DWORD dw)
{
   switch( dw )
   {
      case 1: return (DWORD) _ot4xb_apc_ratxbf_;
      case 2: return (DWORD) _ot4xb_apc_ratxbm_;
      case 3: return (DWORD) _ot4xb_apc_ratxbs_;
      case 4: return (DWORD) _ot4xb_apc_ratxbg_;
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase prepare
/*{{begin-c-function}}*/
/*{{c-function_: _ratx_prep_
            | syntax_: `DWORD * _ratx_prep_( DWORD np, LPSTR pStr, DWORD nFlags )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: _ratx_prep_
            | _kw_: _ratx_prep_, Function
   }}*/
/*{{|desc: Allocates and initializes the parameter block for a run-at-thread Xbase++ call. Bit 1 of nFlags
      creates a completion event and bit 2 creates a container; the name is copied and the count stored.
    | params:
    - `np` DWORD - Number of parameters the block must hold.
    - `pStr` LPSTR - Function or method name to execute (copied into the block).
    - `nFlags` DWORD - Bit 1 creates a completion event; bit 2 creates a container.

    Returns DWORD * - Newly allocated call block, released later with _ratx_clr_(). }}*/
OT4XB_API DWORD*  __cdecl _ratx_prep_(DWORD np, LPSTR pStr,DWORD nFlags)
{
   DWORD* pdw = (DWORD*) _xgrab( sizeof(DWORD) * (np + 5) );
   if( nFlags & 1 ){ pdw[0] = (DWORD) CreateEvent(0,0,0,0); }
   if( nFlags & 2 ){ pdw[2] = (DWORD) _conNew(NULLCONTAINER);}
   pdw[3] = (DWORD) _xstrdup( pStr );    // function or method name to execute
   pdw[4] = np; // number of parameters
   return pdw; 
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ratx_set_
            | syntax_: `void _ratx_set_( DWORD * pdw, ULONG np, DWORD con )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: _ratx_set_
            | _kw_: _ratx_set_, Function
   }}*/
/*{{|desc: Stores the np-th parameter container into a run-at-thread call block.
    | params:
    - `pdw` DWORD * - Call block from _ratx_prep_().
    - `np` ULONG - 1-based parameter position.
    - `con` DWORD - Parameter container to store.

    Returns void }}*/
OT4XB_API void __cdecl _ratx_set_(DWORD* pdw,ULONG np,DWORD con){pdw[(np+4)] = con;}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _ratx_get_
            | syntax_: `DWORD _ratx_get_( DWORD * pdw, ULONG np )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: _ratx_get_
            | _kw_: _ratx_get_, Function
   }}*/
/*{{|desc: Reads a value back from a run-at-thread call block: returns the container slot (pdw[2]) when np
      is nonzero, or the stored parameter count (pdw[4]) when np is 0.
    | params:
    - `pdw` DWORD * - Call block from _ratx_prep_().
    - `np` ULONG - Selector: 0 reads the parameter count, nonzero reads the container slot.

    Returns DWORD - The container slot, or the parameter count when np is 0. }}*/
OT4XB_API DWORD __cdecl _ratx_get_(DWORD* pdw,ULONG np){return ( np ? pdw[2] : pdw[(np+4)] );}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// run at thread xbase cleanup
/*{{begin-c-function}}*/
/*{{c-function_: _ratx_clr_
            | syntax_: `void _ratx_clr_( DWORD * pdw )`
            | category: threads/apc
            | header: ot4xb_c_exported.h
            | mangled-name: _ratx_clr_
            | _kw_: _ratx_clr_, Function
   }}*/
/*{{|desc: Releases a run-at-thread call block: closes its event, releases its container and parameters,
      frees the name string, and frees the block itself.
    | params:
    - `pdw` DWORD * - Call block from _ratx_prep_().

    Returns void }}*/
OT4XB_API void __cdecl _ratx_clr_(DWORD* pdw)
{
   if( pdw[0] ) CloseHandle( (HANDLE) pdw[0] );
   if( pdw[2] ) _conRelease((ContainerHandle) pdw[2]);
   if( pdw[3] ) _xfree( (void*) pdw[3]);
   _conReleasePa(_mk_ptr_( ContainerHandle*,pdw,20),pdw[4]);
   _xfree( (void*) pdw );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: kill_process_by_id
            | syntax_: `BOOL kill_process_by_id( DWORD id, UINT nCode )`
            | category: runtime
            | header: ot4xb_c_exported.h
            | mangled-name: kill_process_by_id
            | _kw_: kill_process_by_id, Function
   }}*/
/*{{|desc: Terminates a process by its identifier and waits up to 5 seconds for it to end.
    | params:
    - `id` DWORD - Process identifier.
    - `nCode` UINT - Exit code passed to TerminateProcess().

    Returns BOOL - TRUE if the process was terminated and ended within the timeout, otherwise FALSE. }}*/
OT4XB_API BOOL __cdecl kill_process_by_id(DWORD id , UINT nCode)
{
   BOOL   result = FALSE;
   if(id)
   {
      HANDLE hp = OpenProcess(SYNCHRONIZE |  PROCESS_TERMINATE,0,id);
      if( hp )
      {
         if( TerminateProcess(hp,nCode) )
         {
            result = (BOOL) ((WaitForSingleObjectEx(hp,5000,FALSE) == WAIT_OBJECT_0 ) ? 1 : 0);
         }
         else
         {
            result = FALSE;
         }

         CloseHandle(hp);
      }
   }
   return result;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: process_wait_by_id
            | syntax_: `LONG process_wait_by_id( DWORD id, DWORD nTimeOut )`
            | category: runtime
            | header: ot4xb_c_exported.h
            | mangled-name: process_wait_by_id
            | _kw_: process_wait_by_id, Function
   }}*/
/*{{|desc: Waits for a process, identified by its id, to finish or until the timeout expires.
    | params:
    - `id` DWORD - Process identifier.
    - `nTimeOut` DWORD - Time to wait in milliseconds.

    Returns LONG - 0 if the process ended, 1 if it is still running at the timeout, or a negative value
      on error. }}*/
OT4XB_API LONG __cdecl process_wait_by_id(DWORD id , DWORD nTimeOut )
{
   LONG result = -1;
   if(id)
   {
      HANDLE hp = OpenProcess(SYNCHRONIZE |  PROCESS_TERMINATE,0,id);
      if( hp )
      {
         for(;;)
         {
            DWORD dwt = GetTickCount();
            switch( WaitForSingleObjectEx(hp, nTimeOut,TRUE) )
            {
               case 0:
               {
                  result = 0;
                  goto label_end_loop;
               }
               case WAIT_TIMEOUT:
               {
                  result = 1;
                  goto label_end_loop;
               }
               case WAIT_ABANDONED:
               {
                  result = -2;
                  goto label_end_loop;
               }
               case WAIT_IO_COMPLETION:
               {
                  result = 1;
                  if( ((int) nTimeOut ) >= 0 )
                  {
                     DWORD nn  = GetTickCount() & 0xFFFFFFFF;
                     DWORD dwe = nn - dwt;
                     if( nTimeOut <= dwe ){ goto label_end_loop; }
                     nTimeOut -= dwe;
                  }
                  break;
               }
               default:
               {
                  result = -1;
                  goto label_end_loop;
               }
            }
         }
         label_end_loop: ;
         CloseHandle(hp);
      }
   }
   return result;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
extern "C" LPSTR __cdecl __unDName(LPSTR buffer,LPSTR mangled, int buflen,DWORD pAlloc, DWORD pFree,WORD wFlags);
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_unmangle_cpp_name
            | syntax_: `LPSTR ot4xb_unmangle_cpp_name( LPSTR pName )`
            | category: cpp/symbols
            | header: ot4xb_xbexports.hpp
            | mangled-name: ot4xb_unmangle_cpp_name
            | _kw_: ot4xb_unmangle_cpp_name, Function
   }}*/
/*{{|desc: Converts a Microsoft C++ decorated symbol name into a readable C++ function or method signature.
    | params:
    - `pName` LPSTR - Microsoft C++ decorated symbol name.

    Returns LPSTR - Readable undecorated name allocated with ot4xb memory, or 0 if it cannot be decoded. }}*/
extern "C" OT4XB_API LPSTR  ot4xb_unmangle_cpp_name(LPSTR pName )
{
   return __unDName(0,pName,0,(DWORD) _xgrab, (DWORD)_xfree,0);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_unmangle_cpp_name
            | syntax_: `ot4xb_unmangle_cpp_name( cMangledName )`
            | category: cpp/symbols
            | export: OT4XB_UNMANGLE_CPP_NAME
            | source: ot4xb_acp.cpp:OT4XB_UNMANGLE_CPP_NAME
            | _kw_: ot4xb_unmangle_cpp_name, Function
   }}*/
/*{{|desc: Converts a Microsoft C++ decorated symbol name into a readable C++ function or method signature.
    | params:
    - `cMangledName` string - Microsoft C++ decorated symbol name.

    Returns string/nil - Readable undecorated C++ name, or NIL if the input is not a string or the name cannot
      be decoded.

    |note: This function uses the Microsoft runtime __unDName() helper. It is mainly useful when inspecting C++
      exports, debug traces, or symbol names returned by other tools. }}*/
_XPP_REG_FUN_( OT4XB_UNMANGLE_CPP_NAME )
{
   TXppParamList xpp(pl,1);
   if( xpp[1]->CheckType( XPP_CHARACTER ) )
   {
      LPSTR pStr = __unDName(0,xpp[1]->LockStr(),0,(DWORD) _xgrab, (DWORD)_xfree,0);
      xpp[1]->UnlockStr();
      if( pStr )
      {
         xpp[0]->PutStr( pStr );
         _xfree((void*) pStr );
         pStr = 0;
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
