//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("TCriticalSection::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(0x10201000 + n);
// -----------------------------------------------------------------------------------------------------------------
static void TCriticalSection_Init( TXbClsParams * px );
static void TCriticalSection_Destroy( TXbClsParams * px );
static void TCriticalSection_TryLock( TXbClsParams * px );
static void TCriticalSection_Lock( TXbClsParams * px );
static void TCriticalSection_UnLock( TXbClsParams * px );
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: TCriticalSection
            | _slug_: tcriticalsection
            | class-function: TCRITICALSECTION
            | category: runtime/thread
            | desc: Xbase++ class wrapper around a Windows CRITICAL_SECTION. Use it to serialize access to shared
              state between threads inside the current process. Instances are created with
              TCriticalSection():New() -> Self, which automatically calls ::init() to initialize the internal
              CRITICAL_SECTION.
            | note: TCriticalSection is a low-level synchronization primitive. Use it only when the caller knows
              exactly which shared state is being protected and can reliably balance every successful entry with a
              matching leave. For normal Xbase++ object synchronization, prefer the language/runtime SYNC methods
              when they fit the problem.
            | note: The lock follows Windows CRITICAL_SECTION semantics. The owning thread may enter it recursively,
              but it must leave it the same number of times.
            | note: TCriticalSection is process-local synchronization. It is not a named interprocess mutex.
            | note: ::Lock(), ::TryLock(), ::UnLock() and ::Destroy() raise a runtime error when the object has been
              destroyed or is not properly initialized.
   | _kw_: critical section, mutex, lock, synchronize, thread safety
   }}*/
XPPRET XPPENTRY TCRITICALSECTION(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TCriticalSection");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TCriticalSection" );
      /*{{|:**BEGIN CLASS  TCriticalSection** }}*/
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      /*{{|ivar_: - VAR _m__cs_
               | desc_: Internal CRITICAL_SECTION pointer stored as a numeric member variable, 0 by default until
                 ::init() allocates and initializes the critical section.
               | note: Internal state, not meant to be manipulated outside the class.
      }}*/
      pc->Var("_m__cs_");  // cs handle stored as a long member variable, initialized to 0 by default
      // ---------------------------------------------------------------------------------
      /*{{|method_: - METHOD init()
               | return: Self
               | desc_: Allocates and initializes the internal CRITICAL_SECTION and returns the object itself. It is
                 called automatically by :New().
               | note: Calling ::init() explicitly is only valid before the instance has been initialized: on an
                 already initialized instance it raises a runtime error.
      }}*/
      pc->Method("init"     , TCriticalSection_Init);
      /*{{|method_: - METHOD Destroy()
               | return: NIL
               | desc_: Releases the internal CRITICAL_SECTION storage owned by this object.
               | note: ::Destroy() enters the critical section before deleting it, so it blocks until it can be
                 owned by the current thread. Do not use the object after ::Destroy() has been called.
      }}*/
      pc->Method("Destroy"  , TCriticalSection_Destroy);
      /*{{|method_: - METHOD Lock()
               | return: NIL
               | desc_: Enters the critical section, blocking until the current thread owns it.
               | note: When ::Lock() returns normally, it must be paired with a matching ::UnLock() call by the same
                 thread.
      }}*/
      pc->Method("Lock"     , TCriticalSection_Lock);
      /*{{|method_: - METHOD TryLock()
               | return: lLocked
               | desc_: Tests whether the critical section can be entered immediately, and enters it only when it is
                 available. Returns .T. when ownership was acquired, otherwise .F..
               | note: Use ::TryLock() when the caller must not wait. Call ::UnLock() only when ::TryLock() returned
                 .T..
      }}*/
      pc->Method("TryLock"  , TCriticalSection_TryLock);
      /*{{|method_: - METHOD UnLock()
               | return: NIL
               | desc_: Leaves the critical section previously entered by the current thread.
               | note: The current thread must own the critical section before calling ::UnLock().
      }}*/
      /*{{|:**END CLASS** }}*/
      pc->Method("UnLock"   , TCriticalSection_UnLock);
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   // ---------------------------------------------------------------------------------
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: get_new_initialized_critical_section
            | syntax_: `CRITICAL_SECTION * get_new_initialized_critical_section( void )`
            | category: runtime/thread
            | header: ot4xb_c_exported.h
            | mangled-name: get_new_initialized_critical_section
            | _kw_: critical section, allocate, InitializeCriticalSection
   }}*/
/*{{|desc: Allocates memory for a Windows CRITICAL_SECTION and initializes it.

    Returns CRITICAL_SECTION* - Pointer to an initialized CRITICAL_SECTION allocated with ot4xb memory
      helpers. }}*/
OT4XB_API CRITICAL_SECTION * get_new_initialized_critical_section( void )
{
   CRITICAL_SECTION * pcs = (CRITICAL_SECTION *) _xgrab( sizeof(CRITICAL_SECTION) );
   InitializeCriticalSection(pcs);
   return pcs;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
static void TCriticalSection_Init( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if(pcs){PXERROR( 1 , "init" , "TCriticalSection:init() can not be called explicity");return;}
   pcs = (CRITICAL_SECTION *) _xgrab( sizeof(CRITICAL_SECTION) );
   InitializeCriticalSection(pcs);
   px->PutMemberLong("_m__cs_", (LONG) pcs);
   px->PutReturnSelf();
}
// -----------------------------------------------------------------------------------------------------------------
static void TCriticalSection_Destroy( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "Destroy" ,"Object destroyed or not properly initialized.");return;}
   EnterCriticalSection(pcs);
   px->PutMemberLong("_m__cs_",0);
   DeleteCriticalSection(pcs);
   _xfree( (void *) pcs );
}
//----------------------------------------------------------------------------------------------------------------------
static void TCriticalSection_Lock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "Lock" ,"Object destroyed or not properly initialized.");return;}
   EnterCriticalSection(pcs);
}
//----------------------------------------------------------------------------------------------------------------------
static void TCriticalSection_TryLock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "TryLock" ,"Object destroyed or not properly initialized.");return;}
   px->PutReturnBool( TryEnterCriticalSection(pcs) );
}
//----------------------------------------------------------------------------------------------------------------------
static void TCriticalSection_UnLock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "Unlock" ,"Object destroyed or not properly initialized.");return;}
   LeaveCriticalSection(pcs);
}
//----------------------------------------------------------------------------------------------------------------------

