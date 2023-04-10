//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <mswsock.h>
//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#define PXERROR( n , m , d )  px->GenError();px->SetErrorSubSystem("ot4xb"); \
                              px->SetErrorOperation("ot4xb_iocp::"  ##m  "()"); \
                              px->SetErrorDescription( d ); \
                              px->SetErrorGenCode(n);
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( ot4xb_iocp_ns )
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
typedef HANDLE ( __stdcall * CreateIoCompletionPort_ft )(HANDLE,HANDLE,ULONG_PTR,DWORD);
typedef BOOL   ( __stdcall * GetQueuedCompletionStatus_ft)(HANDLE,LPDWORD,PULONG_PTR,LPOVERLAPPED*,DWORD);
typedef BOOL   ( __stdcall * PostQueuedCompletionStatus_ft)(HANDLE,DWORD,ULONG_PTR,LPOVERLAPPED);
// -----------------------------------------------------------------------------------------------------------------
static DWORD LastError_TlsIndex = TLS_OUT_OF_INDEXES;
static CreateIoCompletionPort_ft     fpCreateIoCompletionPort     = 0;
static GetQueuedCompletionStatus_ft  fpGetQueuedCompletionStatus  = 0;
static PostQueuedCompletionStatus_ft fpPostQueuedCompletionStatus = 0;
//----------------------------------------------------------------------------------------------------------------------
void _init_proc_( void )
{
   HMODULE h = GetModuleHandle("kernel32");
   fpCreateIoCompletionPort     = (CreateIoCompletionPort_ft    ) GetProcAddress(h,"CreateIoCompletionPort");
   fpGetQueuedCompletionStatus  = (GetQueuedCompletionStatus_ft ) GetProcAddress(h,"GetQueuedCompletionStatus");
   fpPostQueuedCompletionStatus = (PostQueuedCompletionStatus_ft) GetProcAddress(h,"PostQueuedCompletionStatus");
   if( fpCreateIoCompletionPort )
   {
      LastError_TlsIndex = TlsAlloc();
      TlsSetValue( LastError_TlsIndex , 0 );
   }
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
//      return fpCreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0, (DWORD) nThreads );
//      if( fpCreateIoCompletionPort(h_file,h_iocp,(ULONG_PTR) pdw,0) )
//      if( fpPostQueuedCompletionStatus( h_iocp,0,(ULONG_PTR) pdw,0) )
//      if( fpGetQueuedCompletionStatus(h_iocp,&nBytes,(PULONG_PTR)(&pdw),&pover,dwTimeOut) )
// -----------------------------------------------------------------------------------------------------------------
void iocp_init( TXbClsParams * px)         // ::New( nThreads = 1 ) -> Self       
{
   if( !fpCreateIoCompletionPort ){return;}
   DWORD   nLastError = 0;
   HANDLE  h_iocp     = 0;
   DWORD   n_threads  = 1;  
   if( px->GetMemberLong("h_iocp") )
   {
      PXERROR( -1 , "init" , "Instance already initialized");
      return;
   }
   if( px->CheckParamType(1,XPP_NUMERIC) ){ n_threads = px->GetParamDWord(1); }
   SetLastError(0);   
   h_iocp = fpCreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,n_threads);
   nLastError = GetLastError();
   TlsSetValue( LastError_TlsIndex , (void*) nLastError );
   px->PutMemberLong("h_iocp",(LONG) h_iocp );   
   px->PutReturnSelf();
}
// -----------------------------------------------------------------------------------------------------------------
void iocp_release( TXbClsParams * px)      // ::Release() -> lOk                          
{ 
   HANDLE  h_iocp     = (HANDLE) px->GetMemberLong("h_iocp");
   BOOL result = FALSE;
   DWORD   nLastError = 0;   
   SetLastError(0);      
   if( h_iocp && (h_iocp != INVALID_HANDLE_VALUE) ){ result = CloseHandle(h_iocp); nLastError = GetLastError();}
   TlsSetValue( LastError_TlsIndex , (void*) nLastError );   
   px->PutMemberLong("h_iocp",0 );      
   px->PutReturnBool( result );
}
// -----------------------------------------------------------------------------------------------------------------
void iocp_add_handle( TXbClsParams * px)   // ::add_handle(handle,key) -> lOk      
{ 
   if( !fpCreateIoCompletionPort ){return;}   
   HANDLE  h_iocp     = (HANDLE) px->GetMemberLong("h_iocp");
   HANDLE  h_file     = (HANDLE) px->GetParamLong(1);
   ULONG_PTR key      = (ULONG_PTR) px->GetParamLong(2);
   DWORD   nLastError = 0;      
   HANDLE  result     = 0;
   SetLastError(0);         
   if( h_iocp && (h_iocp != INVALID_HANDLE_VALUE) && h_file && (h_file != INVALID_HANDLE_VALUE) )
   {
      result = fpCreateIoCompletionPort(h_file,h_iocp,key,0);
      nLastError = GetLastError();      
   }
   TlsSetValue( LastError_TlsIndex , (void*) nLastError );   
   px->PutReturnBool( (BOOL) result );   
}
// -----------------------------------------------------------------------------------------------------------------
void iocp_post( TXbClsParams * px)         // ::post(nBytes,key,overlapped)              
{
   if( !fpPostQueuedCompletionStatus ){return;}
   HANDLE      h_iocp        = (HANDLE) px->GetMemberLong("h_iocp");   
   DWORD       n_bytes       = px->GetParamDWord(1);
   ULONG_PTR   p_key         = (ULONG_PTR) px->GetParamLong(2);   
   OVERLAPPED* p_overlapped  = (OVERLAPPED*) px->GetParamLong(3);
   DWORD       nLastError = 0;         
   BOOL        result = FALSE;   
   SetLastError(0);         
   if( h_iocp && (h_iocp != INVALID_HANDLE_VALUE))
   {
      result = fpPostQueuedCompletionStatus(h_iocp,n_bytes,p_key,p_overlapped);
      nLastError = GetLastError();      
   }
   TlsSetValue( LastError_TlsIndex , (void*) nLastError );   
   px->PutReturnBool( (BOOL) result );      
}
// -----------------------------------------------------------------------------------------------------------------

void iocp_get( TXbClsParams * px)          // ::get(@nBytes,@key,@overlapped,dwTimeOut)    
{ 
   if( !fpGetQueuedCompletionStatus){return;}
   HANDLE      h_iocp        = (HANDLE) px->GetMemberLong("h_iocp");   
   DWORD       n_bytes       = 0;
   ULONG_PTR   p_key         = 0;
   OVERLAPPED* p_overlapped  = 0;
   DWORD       n_timeout     = px->GetParamDWord(4);
   DWORD       nLastError = 0;         
   BOOL        result = FALSE;   
   SetLastError(0);         
   if( h_iocp && (h_iocp != INVALID_HANDLE_VALUE))
   {
      OVERLAPPED** ppo = ( px->CheckParamType(3,XPP_NUMERIC) ? &p_overlapped : 0 );
      result = fpGetQueuedCompletionStatus(h_iocp,&n_bytes,&p_key,ppo,n_timeout);
      nLastError = GetLastError();      
   }
   px->PutParamLong(1,(LONG) n_bytes);
   px->PutParamLong(2,(LONG) p_key);
   px->PutParamLong(3,(LONG) p_overlapped);
   TlsSetValue( LastError_TlsIndex , (void*) nLastError );   
   px->PutReturnBool( (BOOL) result );         
}
// -----------------------------------------------------------------------------------------------------------------
//static DWORD load_acceptex( SOCKET s )
//{
//   DWORD dw = 0;
//   DWORD cb = 0;
//   GUID g = WSAID_ACCEPTEX;
//   if(WSAIoctl(s,SIO_GET_EXTENSION_FUNCTION_POINTER,&g,sizeof(g),&dw,4,&cb,0,0) == SOCKET_ERROR){ return 0;}
//   return dw;
//}
// -----------------------------------------------------------------------------------------------------------------
//static DWORD load_getacceptexsockaddrs( SOCKET s )
//{
//   DWORD dw = 0;
//   DWORD cb = 0;
//   GUID g = WSAID_GETACCEPTEXSOCKADDRS;
//   if(WSAIoctl(s,SIO_GET_EXTENSION_FUNCTION_POINTER,&g,sizeof(g),&dw,4,&cb,0,0) == SOCKET_ERROR){ return 0;}
//   return dw;
//}

// -----------------------------------------------------------------------------------------------------------------
static void ot4xb_iocp_methods( TXbClass* pc )
{
   pc->Var( "h_iocp" );
   // ---------------------------------------------------------------------------------
   pc->ClassMethod_cbbs( "GetLastError", "{|s| nFpCall(%i,%i) }",TlsGetValue,LastError_TlsIndex);
   pc->ClassMethod_cbbs( "SetLastError", "{|s,v| nFpCall(%i,%i,v) }",TlsSetValue,LastError_TlsIndex);   
   pc->ClassPropertyCB("nLastError","{|s,v| iif(v == NIL,s:GetLastError() , s:SetLastError(v))}");
   // ---------------------------------------------------------------------------------
   pc->Method( "init"   , iocp_init ,  1 ); // ::New( nThreads = 1 ) -> Self
   pc->Method( "release", iocp_release ); // ::Release()
   pc->Method( "add_handle", iocp_add_handle,2); // ::add_handle(handle,key)   
   pc->Method( "post", iocp_post,3); // ::post(nBytes,key,overlapped)      
   pc->Method( "get", iocp_get,4); // ::get(@nBytes,@key,@overlapped,dwTimeOut)
   // ---------------------------------------------------------------------------------
   //pc->ClassMethod_cbbs("load_acceptex","{|o,s| nFpCall(%i,s)}",load_acceptex);
   //pc->ClassMethod_cbbs("load_getacceptexsockaddrs","{|o,s| nFpCall(%i,s)}",load_getacceptexsockaddrs);   
   // ---------------------------------------------------------------------------------
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------
extern "C" XPPRET XPPENTRY OT4XB_IOCP( XppParamList pl)
{
   if( ! ot4xb_iocp_ns::fpCreateIoCompletionPort ){ _ret(pl); return; }
   ContainerHandle conco = _conClsObj("OT4XB_IOCP");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;pc->ClassName("OT4XB_IOCP");
      pc->EXPORTED();
      {
         ot4xb_iocp_ns::ot4xb_iocp_methods( pc );
      }
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
// -----------------------------------------------------------------------------------------------------------------

