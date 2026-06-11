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
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>TCriticalSection</name>
      <export>TCRITICALSECTION</export>
      <source>TCriticalSection.cpp:TCRITICALSECTION</source>
      <visibility>exported</visibility>
      <category>runtime/thread</category>
      <description>
         Xbase++ class wrapper around a Windows CRITICAL_SECTION. Use it to
         serialize access to shared state between threads inside the current
         process.
      </description>
      <constructor>
         <name>TCriticalSection</name>
         <syntax>TCriticalSection():New() -> Self</syntax>
         <description>
            Creates an instance and automatically calls ::init() to initialize
            the internal CRITICAL_SECTION.
         </description>
      </constructor>
      <instance-variables>
         <variable>
            <name>_m__cs_</name>
            <description>Internal CRITICAL_SECTION pointer storage.</description>
         </variable>
      </instance-variables>
      <methods>
         <method-ref>TCriticalSection::init</method-ref>
         <method-ref>TCriticalSection::Lock</method-ref>
         <method-ref>TCriticalSection::TryLock</method-ref>
         <method-ref>TCriticalSection::UnLock</method-ref>
         <method-ref>TCriticalSection::Destroy</method-ref>
      </methods>
      <remarks>
         TCriticalSection is a low-level synchronization primitive. Use it only
         when the caller knows exactly which shared state is being protected
         and can reliably balance every successful entry with a matching leave.
         For normal Xbase++ object synchronization, prefer the language/runtime
         SYNC methods when they fit the problem.
      </remarks>
      <remarks>
         The lock follows Windows CRITICAL_SECTION semantics. The owning thread
         may enter it recursively, but it must leave it the same number of
         times.
      </remarks>
      <remarks>
         TCriticalSection is process-local synchronization. It is not a named
         interprocess mutex.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XPPRET XPPENTRY TCRITICALSECTION(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("TCriticalSection");
   // ---------------------------------------------------------------------------------
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName( "TCriticalSection" );
      pc->EXPORTED();
      // ---------------------------------------------------------------------------------
      pc->Var("_m__cs_");  // cs handle stored as a long member variable, initialized to 0 by default
      // ---------------------------------------------------------------------------------
      pc->Method("init"     , TCriticalSection_Init);     // doc with TCriticalSection::init
      pc->Method("Destroy"  , TCriticalSection_Destroy);  // doc with TCriticalSection::Destroy
      pc->Method("Lock"     , TCriticalSection_Lock);     // doc with TCriticalSection::Lock
      pc->Method("TryLock"  , TCriticalSection_TryLock);  // doc with TCriticalSection::TryLock
      pc->Method("UnLock"   , TCriticalSection_UnLock);   // doc with TCriticalSection::UnLock
      // ---------------------------------------------------------------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   // ---------------------------------------------------------------------------------
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<ot4xb-api>
   <function>
      <name>get_new_initialized_critical_section</name>
      <category>runtime/thread</category>
      <header>ot4xb_c_exported.h</header>
      <description>
         Allocates memory for a Windows CRITICAL_SECTION and initializes it.
      </description>
      <syntax>CRITICAL_SECTION * get_new_initialized_critical_section( void )</syntax>
      <parameters>
      </parameters>
      <return>
         <type>CRITICAL_SECTION*</type>
         <description>Pointer to an initialized CRITICAL_SECTION allocated with ot4xb memory helpers.</description>
      </return>
   </function>
</ot4xb-api>
*******************************************************************************************************************/
OT4XB_API CRITICAL_SECTION * get_new_initialized_critical_section( void )
{
   CRITICAL_SECTION * pcs = (CRITICAL_SECTION *) _xgrab( sizeof(CRITICAL_SECTION) );
   InitializeCriticalSection(pcs);
   return pcs;
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <method>
      <class>TCriticalSection</class>
      <name>init</name>
      <qualified-name>TCriticalSection::init</qualified-name>
      <source>TCriticalSection.cpp:TCriticalSection_Init</source>
      <category>runtime/thread</category>
      <description>
         Initializes the internal CRITICAL_SECTION and returns the object
         itself.
      </description>
      <syntax>oCriticalSection:init() -> Self</syntax>
      <parameters/>
      <return>
         <type>object</type>
         <description>The same TCriticalSection instance.</description>
      </return>
      <remarks>
         This method is normally called automatically by :New(). Calling
         ::init() explicitly is only valid before the instance has been
         initialized.
      </remarks>
   </method>
</xbdoc>
*******************************************************************************************************************/
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
/*******************************************************************************************************************
<xbdoc>
   <method>
      <class>TCriticalSection</class>
      <name>Destroy</name>
      <qualified-name>TCriticalSection::Destroy</qualified-name>
      <source>TCriticalSection.cpp:TCriticalSection_Destroy</source>
      <category>runtime/thread</category>
      <description>
         Releases the internal CRITICAL_SECTION storage owned by this object.
      </description>
      <syntax>oCriticalSection:Destroy() -> NIL</syntax>
      <parameters/>
      <return>NIL</return>
      <remarks>
         Do not use the object after ::Destroy() has been called.
      </remarks>
   </method>
</xbdoc>
*******************************************************************************************************************/
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
/*******************************************************************************************************************
<xbdoc>
   <method>
      <class>TCriticalSection</class>
      <name>Lock</name>
      <qualified-name>TCriticalSection::Lock</qualified-name>
      <source>TCriticalSection.cpp:TCriticalSection_Lock</source>
      <category>runtime/thread</category>
      <description>
         Enters the critical section, blocking until the current thread owns it.
      </description>
      <syntax>oCriticalSection:Lock() -> NIL</syntax>
      <parameters/>
      <return>NIL</return>
      <remarks>
         ::Lock() raises an error when the object is destroyed or not properly
         initialized. Otherwise it blocks until the current thread enters the
         critical section. When ::Lock() returns normally, it must be paired
         with a matching ::UnLock() call by the same thread.
      </remarks>
   </method>
</xbdoc>
*******************************************************************************************************************/
static void TCriticalSection_Lock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "Lock" ,"Object destroyed or not properly initialized.");return;}
   EnterCriticalSection(pcs);
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <method>
      <class>TCriticalSection</class>
      <name>TryLock</name>
      <qualified-name>TCriticalSection::TryLock</qualified-name>
      <source>TCriticalSection.cpp:TCriticalSection_TryLock</source>
      <category>runtime/thread</category>
      <description>
         Tests whether the critical section can be entered immediately, and
         enters it only when it is available.
      </description>
      <syntax>oCriticalSection:TryLock() -> lLocked</syntax>
      <parameters/>
      <return>
         <type>logical</type>
         <description>.T. when ownership was acquired, otherwise .F..</description>
      </return>
      <remarks>
         Use ::TryLock() when the caller must not wait. Call ::UnLock() only
         when ::TryLock() returns .T..
      </remarks>
   </method>
</xbdoc>
*******************************************************************************************************************/
static void TCriticalSection_TryLock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "TryLock" ,"Object destroyed or not properly initialized.");return;}
   px->PutReturnBool( TryEnterCriticalSection(pcs) );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <method>
      <class>TCriticalSection</class>
      <name>UnLock</name>
      <qualified-name>TCriticalSection::UnLock</qualified-name>
      <source>TCriticalSection.cpp:TCriticalSection_UnLock</source>
      <category>runtime/thread</category>
      <description>
         Leaves the critical section previously entered by the current thread.
      </description>
      <syntax>oCriticalSection:UnLock() -> NIL</syntax>
      <parameters/>
      <return>NIL</return>
      <remarks>
         The current thread must own the critical section before calling
         ::UnLock().
      </remarks>
   </method>
</xbdoc>
*******************************************************************************************************************/
static void TCriticalSection_UnLock( TXbClsParams * px )
{
   CRITICAL_SECTION * pcs;
   pcs = (CRITICAL_SECTION *) px->GetMemberLong("_m__cs_");
   if( !pcs ){PXERROR( 2,  "Unlock" ,"Object destroyed or not properly initialized.");return;}
   LeaveCriticalSection(pcs);
}
//----------------------------------------------------------------------------------------------------------------------

