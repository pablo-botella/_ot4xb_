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
      pc->Var("_m__cs_"); 
      // ---------------------------------------------------------------------------------
      pc->Method("init"     , TCriticalSection_Init);
      pc->Method("Destroy"  , TCriticalSection_Destroy);
      pc->Method("Lock"     , TCriticalSection_Lock);
      pc->Method("TryLock"     , TCriticalSection_TryLock);      
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API CRITICAL_SECTION * get_new_initialized_critical_section( void )
{
   CRITICAL_SECTION * pcs = (CRITICAL_SECTION *) _xgrab( sizeof(CRITICAL_SECTION) );
   InitializeCriticalSection(pcs);
   return pcs;
}
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

