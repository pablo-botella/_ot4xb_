// ---------------------------------------------------------------------------
// --------     Project: Open Source Tools for Xbase++                --------
// ----------   Repository : www.xbwin.com                          ----------
// --------     Author: Pablo Botella Navarro ( ot4xb@xbwin.com )     --------
// ---------------------------------------------------------------------------
#include <ot4xb_api.h>
#include <ot4xb_version.h>
// -----------------------------------------------------------------------------------------------------------------
#pragma comment( lib , "kernel32")
#pragma comment( lib , "user32")
#pragma comment( lib , "gdi32")
#pragma comment( lib , "shell32")
#pragma comment( lib , "Rpcrt4")
#pragma comment( lib , "xpprt1")
#pragma comment( lib , "Ws2_32")
#pragma comment( lib , "Oleaut32")
#pragma comment( lib , "ole32")
#pragma comment( lib , "olepro32")
#pragma comment( lib , "shlwapi")
#pragma comment( lib , "comsuppw")
#pragma comment( lib , "comctl32")
//----------------------------------------------------------------------------------------------------------------------
static TGXbStack * _thread_pool_stack_ = 0;
static TGXbStack * _exit_codeblocks_stack_ = 0;
static ContainerHandle _exit_cb_frame_ = 0;
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
//----------------------------------------------------------------------------------------------------------------------
BOOL WINAPI DllMain( HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved );
//----------------------------------------------------------------------------------------------------------------------
#include <xbrt1request.hpp>
OT4XB_API ULONG _xpp_REFERENCE                  =  0x0100;
OT4XB_API ULONG _xpp_MEMO                       =  0x0200;
OT4XB_API ULONG _xpp_DOUBLE                     =  0x0400;
OT4XB_API BOOL  _bXppIs19_                      =  FALSE;
OT4XB_API UINT  g_nMsgProxiRemoveSubclass = RegisterWindowMessage( "msg_76A22932_AD05_40E2_A6E3_7600F117E21A" );
OT4XB_API UINT  g_nMsgDirtyNotify         = RegisterWindowMessage( "msg_845B1B1B_8F23_4D5C_80D6_CFBCEC3DC197" );

// -----------------------------------------------------------------------------------------------------------------
static HINSTANCE hOT4XBInstance  =  0;
static HANDLE    hCurrentProcess = 0;
//----------------------------------------------------------------------------------------------------------------------
static HMODULE   hShell32  = 0;
//----------------------------------------------------------------------------------------------------------------------
BEGIN_REGISTER_XBASE_TABLE()
#include <ot4xb_xbfunclist.hpp>
END_REGISTER_XBASE_TABLE()
//----------------------------------------------------------------------------------------------------------------------
BOOL WINAPI DllMain( HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved )
{
   lpReserved; // UNUSED PARAM
   switch( dwReason )
   {
       case DLL_PROCESS_ATTACH:
       {
          WNDCLASSEX wc;
          ZeroMemory( &wc, sizeof(WNDCLASSEX));
          wc.cbSize        = sizeof(WNDCLASSEX) ;
          wc.lpfnWndProc   = DefWindowProc;
          wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
          wc.hIconSm       = LoadIcon(0, IDI_APPLICATION);
          wc.hCursor       = LoadCursor(0, IDC_ARROW);
          wc.hbrBackground = (HBRUSH)(COLOR_WINDOW +1 );
          wc.hInstance     = (HINSTANCE) GetModuleHandle(0);
          wc.lpszClassName = "_OT4XB_GENERIC_WINDOW_";
          RegisterClassEx(&wc);

          hOT4XBInstance = hDll;
          _API_Memory_InitProc();
          _API_DrTool_InitProc();  // init before TXbClass as it uses _drtool_get_pcs_()
          TXbClass::InitHookList();
          _APIcpp_Tls_InitProc();
          _API_OSVer_InitProc();
          // _hook_parclen();
          ot4xb_iocp_ns::_init_proc_();
          if (!_conRegisterDll((ULONG) hDll, &__dllreg__)) return 0;
          break;
       }
       case DLL_THREAD_ATTACH:
       {
          _APIcpp_Tls_InitThread();

          break;
       }
       case DLL_THREAD_DETACH:
       {
          _APIcpp_Tls_ExitThread();
          break;
       }
       case DLL_PROCESS_DETACH:
       {
          TXbClass::FreeHookList();       
          _API_DrTool_ExitProc();
          _APIcpp_Tls_ExitProc();
          _API_Memory_ExitProc();
          _conUnRegisterDll( (ULONG) hDll);
          if( hCurrentProcess ){ CloseHandle( hCurrentProcess ); hCurrentProcess = 0;}
          break;
       }

    }
    return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
XBASE_INIT_PROC(  )
{
    HMODULE hXppRt1;

    _API_Memory_InitProcXBase(); // Init Heaps
    hXppRt1 = GetModuleHandle("XPPRT1");
    if( hXppRt1 )
    {
       UINT nItems = (UINT) ( sizeof(xbrt1flist) / sizeof(XppRegisterFunction) );
       UINT n;
       for( n = 0; n < nItems; n++ )
       {
          (xbrt1flist[n]).capiFunc = (XppFuncType) GetProcAddress(hXppRt1,(xbrt1flist[n]).functionName);
       }
       _conRegisterF(xbrt1flist,nItems,&xbrt1ft);
       bxbrt1 = TRUE;
       if( GetProcAddress(hXppRt1,"AUTOMATIONADDREF") != 0)
       {
          _bXppIs19_ = TRUE;
          _xpp_REFERENCE = 0x10000000;
          _xpp_MEMO      = 0x40000000;
          _xpp_DOUBLE    = 0x01000000;
       }
    }
    GWST(0); // Init GWST CLASS
    if( !_thread_pool_stack_  )
    {
       _thread_pool_stack_ = new TGXbStack;
       _thread_pool_stack_->SyncMode();
    }

    if( !_exit_codeblocks_stack_ )
    {
       _exit_codeblocks_stack_ = new TGXbStack;
       _exit_codeblocks_stack_->SyncMode();
       _exit_cb_frame_ = _conNewCodeblock("{|cb,eb| eb := ErrorBlock(_conGenericBreakCB()),Eval(cb) , ErrorBlock(eb),NIL}");
    }
   return 1;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------
XBASE_EXIT_PROC()
{
   if( _exit_codeblocks_stack_ )
   {
      TGXbStack* stk = _exit_codeblocks_stack_;
      _exit_codeblocks_stack_->Lock();
      _exit_codeblocks_stack_ = 0;
      __try
      {
         while( stk->Count() )
         {
            ContainerHandle conb = stk->Pop();
            __try
            {
               if( _conCheckType(conb,XPP_BLOCK ) )
               {
                  _conEvalVoid(_exit_cb_frame_,conb);
               }
            }
            __finally { _conRelease( conb ); }
         }
      } __finally { stk->UnLock(); }
      delete stk;
      _conRelease( _exit_cb_frame_ ); _exit_cb_frame_ = 0;
   }
   if( _thread_pool_stack_ )
   {
      TGXbStack* stk = _thread_pool_stack_;
      _thread_pool_stack_ = 0;
      delete stk;
   }
   _APIcpp_Tls_ExitThread_xb();
   if( hShell32  != NULL ) FreeLibrary( hShell32 );
   hShell32 = NULL;
    if( bxbrt1 ) _conUnRegisterF(&xbrt1ft);
   return 1;
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( OT4XB_PUSH_EXIT_CB )
{
   BOOL bByRef = FALSE;
   ContainerHandle conb = _conTParam(pl,1,&bByRef,XPP_BLOCK);
   __try
   {
      if( conb && _exit_codeblocks_stack_ )
      {
         _exit_codeblocks_stack_->Lock();
         __try{ _exit_codeblocks_stack_->Push(_conNew(conb)); }
         __finally { _exit_codeblocks_stack_->UnLock(); }
      }
   } __finally {if( conb && (!bByRef) ){_conRelease(conb);}}
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY APPINSTANCE( XppParamList pl){_retnl(pl,(LONG)GetModuleHandle(0));}
//-----------------------------------------------------------------------------------------------------------------------

XPPRET XPPENTRY GETCURRENTPROCESSHANDLE( XppParamList pl)
{
   if( !hCurrentProcess )
   {
      // HANDLE h =  GetCurrentProcess();
      // if( !DuplicateHandle( h,h,h,&hCurrentProcess,PROCESS_CREATE_THREAD,TRUE,0) ) hCurrentProcess = 0;
      hCurrentProcess =  OpenProcess(PROCESS_DUP_HANDLE, 0, GetCurrentProcessId());
   }
   _retnl(pl,(LONG) hCurrentProcess);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY GETHKERNEL32( XppParamList pl){_retnl(pl,(LONG)GetModuleHandle("kernel32"));}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY GETHUSER32( XppParamList pl){_retnl(pl,(LONG)GetModuleHandle("user32"));}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY GETHOT4XB( XppParamList pl){_retnl(pl,(LONG)hOT4XBInstance);}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY GETHSHELL32( XppParamList pl)
{
   if( hShell32  == NULL ) hShell32 = LoadLibrary( "shell32.dll" );
   if( pl ){ _retnl(pl,(LONG) hShell32 ); }
   __asm mov eax , hShell32 ;
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY OT4XB( XppParamList pl){_retc(pl, OT4XB_VERSION_STRING );}
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API void* _ot4xb_stdctxcbk_new_(DWORD dwCtx , DWORD dwFp){return (void*) new TStdCtxCbk(dwCtx,dwFp);}
OT4XB_API void  _ot4xb_stdctxcbk_delete_(void* p){ delete reinterpret_cast<TStdCtxCbk*>(p);}
OT4XB_API void __cdecl _ot4xb_thread_pool_push_(ContainerHandle conThread){_thread_pool_stack_->Add(conThread);}
OT4XB_API ContainerHandle __cdecl  _ot4xb_thread_pool_pop_(void){ return _thread_pool_stack_->Pop(); }
END_EXTERN_C
//----------------------------------------------------------------------------------------------------------------------
void * T_ot4xb_base::operator new( unsigned int n ){ return _xgrab(n); }
void T_ot4xb_base::operator delete( void * p){ _xfree( p ); }
// ---------------------------------------------------------------------------------------------------------------------
void T_ot4xb_base_with_vheap::vheap_on_init( T_ot4xb_base_with_vheap::vheap_flags dw, OT4XB_VHEAP* vheap )
{

	m_vheap_flags = dw;
	m_vheap = 0;
	if ( ( dw & e_use_custom_heap ) && ( vheap == 0 ) ) { dw = (vheap_flags) ( dw | e_create_new_heap | e_destroy_heap_on_release ); }
	if ( dw & e_create_new_heap )
	{
		m_vheap = ot4xb_vheap_create( HEAP_GENERATE_EXCEPTIONS, 0, 0 );
		m_vheap_flags = (vheap_flags) ( dw | e_use_custom_heap | e_destroy_heap_on_release );
	}
	else
	{
		if ( dw & e_use_custom_heap )
		{
			m_vheap = vheap;
		}
	}
}
// -----------------------------------------------------------------------------------------------------------------
void T_ot4xb_base_with_vheap::vheap_on_destroy( void )
{
	if ( m_vheap_flags & e_destroy_heap_on_release )
	{
		ot4xb_vheap_destroy( m_vheap );
		m_vheap = 0;
	}
}
// ---------------------------------------------------------------------------------
void* T_ot4xb_base_with_vheap::alloc_bytes( UINT nBytes )
{
	if ( m_vheap_flags == e_use_custom_heap )
	{
		if ( m_vheap )
		{
			return m_vheap->vgrab( m_vheap, nBytes );
		}
	}
	else
	{
		return _xgrab( nBytes );
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------
void  T_ot4xb_base_with_vheap::free_bytes( void* p )
{
	if ( m_vheap_flags == e_use_custom_heap )
	{
		if ( m_vheap )
		{
			return m_vheap->vfree( m_vheap, p );
		}
	}
	else
	{
		return _xfree( p );
	}
}
// ---------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
TStdCtxCbk::TStdCtxCbk(DWORD dwCtx,DWORD dwFp )
{
   DWORD dw = static_cast<DWORD>( static_cast<LONG>(dwFp) - (reinterpret_cast<LONG>(this)+12) );
   m_pw[0] = 0x6858;
   m_pw[1] = LOWORD( dwCtx ); m_pw[2] = HIWORD( dwCtx );
   m_pw[3] = 0xE950;
   m_pw[4] = LOWORD( dw ); m_pw[5] = HIWORD( dw );
   dw = 0; VirtualProtect(reinterpret_cast<void*>(this),12,64,&dw);
   m_pw[6] = LOWORD( dw ); m_pw[7] = HIWORD( dw );
}
// -----------------------------------------------------------------------------------------------------------------
TStdCtxCbk::~TStdCtxCbk(void)
{
   DWORD dw  = reinterpret_cast<DWORD*>(this)[3];
   VirtualProtect(reinterpret_cast<void*>(this),12,dw,&dw);
}
// -----------------------------------------------------------------------------------------------------------------
DWORD TStdCtxCbk::GetCtx(void){ return MAKELONG( m_pw[1] , m_pw[2] ); }
//----------------------------------------------------------------------------------------------------------------------
