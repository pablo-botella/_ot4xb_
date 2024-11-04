//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------------
/******************************
// :create_input_pipe( Self, nSize ) --> lSuccess
static void proc_tool_create_input_pipe( XppParamList pl )
{
   TXppParamList xpp( pl , 2);
   HANDLE hRead = NULL, hWrite = NULL,hTmp = NULL;
   ContainerHandle Self = xpp[ 1 ]->con();
   DWORD nSize = xpp[2]->GetDWord();
   HANDLE hcp = GetCurrentProcess();
   SECURITY_ATTRIBUTES sa;
   sa.nLength = sizeof( SECURITY_ATTRIBUTES );
   sa.bInheritHandle = TRUE;
   sa.lpSecurityDescriptor = NULL;

   hTmp = (HANDLE)  _conGetNLMember( Self, "hStdInputRead");
   if( hTmp != NULL ) { CloseHandle( hTmp ); }
   hTmp = _conGetNLMember( Self, "hStdInputWrite" );
   if( hTmp != NULL ) { CloseHandle( hTmp ); }
   hTmp = 0;

   if( CreatePipe( &hRead, &hTmp, &sa, nSize ) )
   {
      DuplicateHandle( hcp, hTmp, hcp, &hWrite, 0, 0, DUPLICATE_SAME_ACCESS );
      CloseHandle( hTmp );
      _conSetNLMember( Self, "hStdInputRead", (LONG)  hRead );
      _conSetNLMember( Self, "hStdInputWrite", (LONG) hWrite );
      xpp[ 0 ]->PutBool( TRUE );
   }



      local hWriteTmp : = 0
      DEFAULT nSize : = 0
      hRead : = 0
      hWrite : = 0
      if @kernel32 : CreatePipe( @hRead, @hWriteTmp, { 12,0,1 }, nSize ) == 0; return.F.; end
         @kernel32:DuplicateHandle( hcp, hWriteTmp, hcp, @hWrite, 0, 0, 2 )
         @kernel32 : CloseHandle( hWriteTmp )
         return.T.
}
// ---------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------



_XPP_REG_FUN_( OT4XB_PROCESS_T )
{
   ContainerHandle conco = _conClsObj( "OT4XB_PROCESS_T" );
   if( conco == NULLCONTAINER )
   {
      TXbClass* pc = new TXbClass;
      pc->ClassName( "OT4XB_PROCESS_T" );
      pc->GwstParent( "WAPIST_STARTUPINFOEX" );
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Var( "hProcess" );
      pc->Var( "hThread" );
      pc->Var( "dwProcessId" );
      pc->Var( "dwThreadId" );
      pc->Var( "hStdInputRead" );
      pc->Var( "hStdInputWrite" );
      pc->Var( "hStdOutputRead" );
      pc->Var( "hStdOutputWrite" );
      pc->Var( "hStdErrorRead" );
      pc->Var( "hStdErrorWrite" );
      pc->Var( "cCmdLine" );
      pc->Var( "cAppName" );
      pc->Var( "cWorkDir" );
      pc->Var( "cParams" );
      pc->Var( "dwCreationFlags" );
      pc->Var( "lInheritHandles" );
      pc->Var( "env" );
      pc->Var( "lBatFile" );
      pc->Var( "cUser" );
      pc->Var( "cPwd" );
      pc->Var( "cDomain" );

      pc->PropertyCBMask("lCreateBreakawayFromJob"         , 0x01000000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateDefaultErrorMode"         , 0x04000000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateNewConsole"               , 0x00000010  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateNewProcessGroup"          , 0x00000200  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateNoWindow"                 , 0x08000000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateProtectedProcess"         , 0x00040000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreatePreserveCodeAuthzLevel"   , 0x02000000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateSeparateWowVdm"           , 0x00000800  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateSharedWowVdm"             , 0x00001000  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateSuspended"                , 0x00000004  , "dwcreationFlags" );
      pc->PropertyCBMask("lCreateUnicodeEnvironment"       , 0x00000400  , "dwcreationFlags" );
      pc->PropertyCBMask("lDebugOnlyThisProcess"           , 0x00000002  , "dwcreationFlags" );
      pc->PropertyCBMask("lDebugProcess"                   , 0x00000001  , "dwcreationFlags" );
      pc->PropertyCBMask("lDetachedProcess"                , 0x00000008  , "dwcreationFlags" );
      pc->PropertyCBMask("lExtendedStartupInfoPresent"     , 0x00080000  , "dwcreationFlags" );

      pc->ClassMethodCB( "initclass", "{|s| s }" );

      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ) { _ret( pl ); return; }
   }
   _conReturn( pl, conco );
   _conRelease( conco );
}
//-----------------------------------------------------------------------------------------------------------------------
         **************/

/*
INLINE CLASS METHOD CreateInputPipe(hRead,hWrite,nSize)
       local hcp := @kernel32:GetCurrentProcess()
       local hWriteTmp := 0
       DEFAULT nSize := 0
       hRead  := 0
       hWrite := 0
       if @kernel32:CreatePipe(@hRead,@hWriteTmp,{12,0,1},nSize) == 0 ; return .F. ; end
       @kernel32:DuplicateHandle(hcp,hWriteTmp,hcp,@hWrite,0,0,2)
       @kernel32:CloseHandle(hWriteTmp)
       return .T.
       // ---------------------------------------------------------------------------------
INLINE CLASS METHOD CreateOutputPipe(hRead,hWrite,nSize)
       local hcp := @kernel32:GetCurrentProcess()
       DEFAULT nSize := 0
       hRead  := 0 ; hWrite := 0
       if @kernel32:CreatePipe(@hRead,@hWrite,{12,0,1},nSize) == 0 ; return .F. ; end
       if @kernel32:SetHandleInformation(hRead,1,0) == 0
          @kernel32:CloseHandle(hRead ); hRead  := 0
          @kernel32:CloseHandle(hWrite); hWrite := 0
          return .F.
       end
       return .T.
       // ---------------------------------------------------------------------------------
INLINE CLASS METHOD initclass ; return Self // required for gwst inheritance
       // ---------------------------------------------------------------------------------
INLINE CLASS METHOD _CreateProcess_(cUser,cPwd,app,cmd,pa,ta,ih,flags,env,cd,psi,ppi)
       DEFAULT pa :=  {12,0,0} ; DEFAULT ta :=  {12,0,0}
       if cUser == NIL
          return FpQCall( {"kernel32","CreateProcessA"} ,;
                          "__bo__pt__pt__pt__pt__bo__sl__pt__pt__pt__pt",;
                          app,cmd,pa,ta,ih,flags,env,cd,psi,@ppi ;
                        )
       end
       DEFAULT cUser := ""
       DEFAULT cPwd  := 0
       PokeStr(cmd,0,cSzAnsi2Wide(PeekStr(cmd,0,-1)))
       return FpQCall( {"advapi32","CreateProcessWithLogonW"} ,;
                      "__boc_swc_swc_sw__slc_sw__pt__sl__ptc_sw__pt__pt",;
                          cUser,".",cPwd,1,app,cmd,flags,env,cd,psi,@ppi ;
                     )
       // ---------------------------------------------------------------------------------
INLINE METHOD GetExitCodeById()
       local hp := NIL
       local dw := 0
       if Empty(::dwProcessId) ; return NIL ; end
       hp := @kernel32:OpenProcess(0x400,0,::dwProcessId)
       if( Empty(hp) ); return NIL; end
       if @kernel32:GetExitCodeProcess(hp,@dw) == 0 ; dw := NIL ; end
       @kernel32:CloseHandle(hp)
       return dw
       // ---------------------------------------------------------------------------------
INLINE METHOD lTestActiveById()
       local dw := ::GetExitCodeById()
       if dw == NIL ; return .F. ; end
       if dw == NIL ; return .F. ; end
       return (dw == 259)
       // ---------------------------------------------------------------------------------
INLINE METHOD KillById(nExitCode)
       local hp := NIL
       local dw := 0
       local lOk := .F.
       DEFAULT nExitCode := -1
       if Empty(::dwProcessId) ; return NIL ; end
       hp := @kernel32:OpenProcess(1,0,::dwProcessId)
       if( Empty(hp) ); return NIL; end
       lOk := !Empty(@kernel32:TerminateProcess(hp , nExitCode ))
       @kernel32:CloseHandle(hp)
       return dw
       // ---------------------------------------------------------------------------------
INLINE METHOD Release()
       if Valtype(::_env_) == "N" ; _hdict_destroy(::_env_) ; ::_env_ := NIL ; end
       if !Empty( ::hProcess) ; @kernel32:CloseHandle( ::hProcess) ; end
       if !Empty( ::hThread ) ; @kernel32:CloseHandle( ::hThread ) ; end
       ::hProcess := ::hThread := NIL
       ::cDesktop  := NIL ; ::cTitle    := NIL
       return Self
       // --------------------------------------------------------------------
INLINE METHOD init(cUser,cPwd)
       ::hProcess := ::hThread := ::dwProcessId := ::dwThreadId := NIL
       ::_gwst_() ; PokeDWord(Self,0,68)
       ::cCmdLine := ::cAppName := ::cWorkDir := ::cParams := NIL
       ::dwCreationFlags := 0
       ::lInheritHandles := .F.
       ::_env_    := NIL
       ::lBatFile := .F.
       if !lIsWin9x()
          ::cUser    := cUser
          ::cPwd     := cPwd
       end
       return Self
       // ---------------------------------------------------------------------------------
INLINE METHOD Start()
       local aProcInfo     := AFill(Array(4),0)
       local pCmdLine      := 0
       local n,nn,ct
       local lOk           := .F.
       local env           := NIL
       local pa := NIL
       local ta := NIL
       ::hProcess := ::hThread := ::dwProcessId := ::dwThreadId := NIL
       // ---------
       if (::cAppName == NIL) .and. ( ::cCmdLine == NIL ) ; return .F. ; end
       pCmdLine := _xgrab( 0x8000 )  ; n := 0
       if( ::cCmdLine == NIL )
           PokeStr( pCmdLine , @n , ::cAppName )
           if !Empty( ::cParams )
              PokeStr( pCmdLine , @n , Chr(32) + ::cParams )
           end
       else
          PokeStr( pCmdLine , @n , ::cCmdLine )
       end
       // ---------
       if !lIsVista()
          ::lExtendedStartupInfoPresent := .F.
          ::lCreateProtectedProcess     := .F.
       end
       if !lIsXp()
          ::lCreatePreserveCodeAuthzLevel := .F.
       end
       if lIsWin9x()
          ::lCreateBreakawayFromJob   := .F.
          ::lCreateNoWindow           := .F.
          ::lCreateSeparateWowVdm     := .F.
          ::lCreateUnicodeEnvironment := .F.
          ::lDebugProcess             := .F.
       end

       if ::lCreateNewConsole
          ::lDetachedProcess       := .F.
          ::lCreateNewProcessGroup := .F.
       end
       // ---------
       ct := Valtype( ::_env_ )
       if ::_env_ == NIL
          env := 0
       elseif ct == "A"
          env := "" ; nn := Len(::_env_)
          for n := 1 to nn
             if( Valtype(::_env_[n]) == "A" )
                env += AllTrim(::_env_[n][1]) + "=" + AllTrim(::_env_[n][2]) + Chr(0)
             else
                env += AllTrim(::_env_[n]) + Chr(0)
             end
          next
          env += Chrr(0,4)
       elseif ct == "C"
          env := ::_env_ + Chrr(0,4)
       elseif ct == "N"
          env := ""
          _hdict_iterate_cb( ::_env_ , {|_n,_k,_v,_x| _x += cPrintf("%s=%s",_k,_v) + Chr(0) , NIL},@env )
          _hdict_destroy(::_env_) ; ::_env_ := NIL
          env += Chrr(0,4)
       end
       // ---------
       // ---------
       lOk := ::_CreateProcess_(::cUser,::cPwd,::cAppName,pCmdLine,pa,ta,::lInheritHandles,::dwCreationFlags,;
                                 env,::cWorkDir,Self,@aProcInfo)
       _xfree( pCmdLine )
       if lOk
          ::hProcess     := aProcInfo[1]
          ::hThread      := aProcInfo[2]
          ::dwProcessId  := aProcInfo[3]
          ::dwThreadId   := aProcInfo[4]
       end
       return lOk
       // ---------------------------------------------------------------------------------
INLINE METHOD GetExitCode(lActive)
       local dw := 0
       lActive := NIL

       if Empty( ::hProcess ) ; return NIL ; end
       if @kernel32:GetExitCodeProcess(::hProcess,@dw) == 0
          dw := NIL
       elseif dw == 259
          lActive := .T.
       else
          lActive := .F.
       end
       return dw
       // ---------------------------------------------------------------------------------
INLINE METHOD Wait( nMilliseconds) // lComplete | NIL on error
       local oStartTime
       local dw := 0
       local nn := 0
       oStartTime := FileTime64():New():Now()
       DEFAULT nMilliseconds := 0
       if Empty( ::hProcess ) ; return NIL ; end
       while .T.
          dw := @kernel32:WaitForSingleObjectEx( ::hProcess , nMilliseconds - nn , .T.)
          if dw == 0 ; return .T. ; end  // object is signaled
          if dw == 0x102 ; return .F. ; end // WAIT_TIMEOUT
          if dw == 0x80  ; return NIL ; end // WAIT_ABANDONED // must never happen
          if dw == 0xC0  // WAIT_IO_COMPLETION
             if nMilliSeconds > 0
                nn := oStartTime:ElapMilliSeconds()
                if nn >= nMilliseconds ; return .F. ; end  // timeout
             end
          else
             return NIL  // WAIT_FAILED
          end
       end
       return NIL
       // ---------------------------------------------------------------------------------
INLINE METHOD Kill(nExitCode)
       DEFAULT nExitCode := -1
       if Empty( ::hProcess ) ; return NIL ; end
       if !Empty(::wait(0)) ; return .T. ; end
       return !Empty(@kernel32:TerminateProcess(::hProcess , nExitCode ))
       // ---------------------------------------------------------------------------------
INLINE METHOD Cmd( cCmdLine , cParams)
       local np := PCount()
       local n,v
       ::lForceOnFeedback := .T.
       ::lForceOffFeedback := .T.
       ::lDetachedProcess := .F.
       if lIsWin9x()
          ::cAppName := GetEnv("comspec")
          if Empty( ::cAppName )
             ::cAppName := cPathCombine( GetWinDir() , "command.com")
          end
       else
          ::cAppName := cPathCombine( GetSysDir() , "cmd.exe")
       end
       ::cCmdLine := ::cAppName
       if !Empty( cCmdLine )
          if np > 1
             ::cCmdLine += cPrintf(," /c \q%s\q", cCmdLine )
          else
             ::cCmdLine += " /c " + cCmdLine
          end
       end
       for n := 2 to np
          v := PValue(n)
          if Valtype(v) == "C"
             ::cCmdLine += Chr(32) + PValue(n)
          end
       next
       return NIL
       // ---------------------------------------------------------------------------------
INLINE METHOD Start16( cApp16 , cParams )
       if Empty( cApp16 ) ; return .F. ; end
       ::cAppName := NIL
       ::cCmdLine := cApp16
       if !Empty( cParams ) ; ::cCmdLine += Space(1) + cParams ; end
       return ::Start()
       // ---------------------------------------------------------------------------------
INLINE METHOD ResetEnv(bClone)
       if Valtype(::_env_) == "N" ; _hdict_destroy(::_env_) ; ::_env_ := NIL ; end
       ::_env_ := _hdict_new()
       if( !Empty(bClone) )
          _hdict_add_env_strings(::_env_)
       end
       return Self
       // ---------------------------------------------------------------------------------
INLINE METHOD GetEnv( k )
       if Valtype(::_env_) != "N" ; ::_env_ := ::_env_ := _hdict_new(); end
       return _hdict_GetProp(::_env_,k)
       // ---------------------------------------------------------------------------------
INLINE METHOD SetEnv( k , v)
       if Valtype(::_env_) != "N" ; ::_env_ := ::_env_ := _hdict_new(); end
       if Valtype(v) == "C"
          _hdict_SetProp(::_env_,k,v)
       else
          _hdict_RemoveProp(::_env_,k)
       end
       return Self
       // ---------------------------------------------------------------------------------
ENDCLASS
//----------------------------------------------------------------------------------------------------------------------


*/






/*
#define BUFSIZE 4096

// ot4xb_proccess_wait_and_read_pipes( 1 hProcess, 2 nMilliseconds,3 @ dw_process_state, 4 on_stdout_read, 5 stdout_cargo, 6 on_stderr_read, 7 stderr_cargo, 8 hStdOutRead, 9 hStdErrRead )
_XPP_REG_FUN_( OT4XB_PROCESS_WAIT_AND_READ_PIPES )
{


}



// Callback para leer datos de stdout y stderr
typedef void ( *PipeReadCallback )( void* cargo, void* data_chunk, size_t chunk_size );

// Función para leer las tuberías y verificar el estado del proceso
int wait_and_read_pipes( DWORD nMilliseconds, HANDLE hProcess, int* p_process_state,
                         PipeReadCallback on_stdout_read, void* stdout_cargo,
                         PipeReadCallback on_stderr_read, void* stderr_cargo,
                         HANDLE hStdOutRead, HANDLE hStdErrRead )
{
   DWORD bytesRead;
   char buffer[ BUFSIZE ];
   int dataRead = 0;

   // Intentar leer stdout si hay datos disponibles
   DWORD available = 0;
   if( PeekNamedPipe( hStdOutRead, NULL, 0, NULL, &available, NULL ) && available > 0 )
   {
      if( ReadFile( hStdOutRead, buffer, BUFSIZE, &bytesRead, NULL ) && bytesRead > 0 )
      {
         on_stdout_read( stdout_cargo, buffer, bytesRead );
         dataRead = 1;
      }
   }

   // Intentar leer stderr si hay datos disponibles
   if( PeekNamedPipe( hStdErrRead, NULL, 0, NULL, &available, NULL ) && available > 0 )
   {
      if( ReadFile( hStdErrRead, buffer, BUFSIZE, &bytesRead, NULL ) && bytesRead > 0 )
      {
         on_stderr_read( stderr_cargo, buffer, bytesRead );
         dataRead = 1;
      }
   }

   // Si se leyeron datos, retornar sin esperar
   if( dataRead )
   {
      *p_process_state = 0;  // El proceso sigue vivo
      return 0;
   }

   // Si no hay datos, esperar hasta nMilliseconds o hasta que el proceso termine
   DWORD result = WaitForSingleObject( hProcess, nMilliseconds );

   if( result == WAIT_TIMEOUT )
   {
      *p_process_state = 0;  // El proceso sigue vivo
      return 0;
   }
   else
   {
      *p_process_state = 1;  // El proceso ha terminado
      return 1;
   }
}

// Ejemplo de callback de lectura para stdout y stderr
void on_stdout_read( void* cargo, void* data_chunk, size_t chunk_size )
{
   fwrite( data_chunk, 1, chunk_size, (FILE*) cargo );  // Escribir stdout en un archivo
}

void on_stderr_read( void* cargo, void* data_chunk, size_t chunk_size )
{
   fwrite( data_chunk, 1, chunk_size, (FILE*) cargo );  // Escribir stderr en un archivo
}

int main()
{
   SECURITY_ATTRIBUTES sa;
   PROCESS_INFORMATION pi;
   STARTUPINFOA si;
   HANDLE hStdOutRead = NULL, hStdOutWrite = NULL;
   HANDLE hStdErrRead = NULL, hStdErrWrite = NULL;

   // Inicializar seguridad para herencia
   sa.nLength = sizeof( SECURITY_ATTRIBUTES );
   sa.bInheritHandle = TRUE;
   sa.lpSecurityDescriptor = NULL;

   // Crear tuberías para stdout y stderr
   if( !CreatePipe( &hStdOutRead, &hStdOutWrite, &sa, 0 ) ||
       !CreatePipe( &hStdErrRead, &hStdErrWrite, &sa, 0 ) )
   {
      fprintf( stderr, "Error creating pipes\n" );
      return 1;
   }

   // Configurar para no heredar el lado de lectura de las tuberías
   SetHandleInformation( hStdOutRead, HANDLE_FLAG_INHERIT, 0 );
   SetHandleInformation( hStdErrRead, HANDLE_FLAG_INHERIT, 0 );

   // Configurar STARTUPINFO para redirigir stdout y stderr
   ZeroMemory( &si, sizeof( STARTUPINFOA ) );
   si.cb = sizeof( STARTUPINFOA );
   si.hStdOutput = hStdOutWrite;
   si.hStdError = hStdErrWrite;
   si.dwFlags |= STARTF_USESTDHANDLES;

   ZeroMemory( &pi, sizeof( PROCESS_INFORMATION ) );

   // Crear el proceso
   if( !CreateProcessA( NULL, "your_executable.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi ) )
   {
      fprintf( stderr, "Error creating process\n" );
      return 1;
   }

   // Cerrar los handles de escritura en el proceso padre
   CloseHandle( hStdOutWrite );
   CloseHandle( hStdErrWrite );

   // Abrir archivos para almacenar la salida
   FILE* stdoutFile = fopen( "stdout_output.txt", "wb" );
   FILE* stderrFile = fopen( "stderr_output.txt", "wb" );

   int process_state = 0;

   // Bucle para leer datos mientras el proceso esté activo
   while( wait_and_read_pipes( 100, pi.hProcess, &process_state,
                               on_stdout_read, stdoutFile,
                               on_stderr_read, stderrFile,
                               hStdOutRead, hStdErrRead ) == 0 )
   {
      // Bucle continúa mientras el proceso esté activo y aún haya datos por leer
   }

   // Leer los datos pendientes después de que el proceso termine
   if( process_state == 1 )
   {
      wait_and_read_pipes( 0, pi.hProcess, &process_state,
                           on_stdout_read, stdoutFile,
                           on_stderr_read, stderrFile,
                           hStdOutRead, hStdErrRead );
   }

   // Limpiar y cerrar
   fclose( stdoutFile );
   fclose( stderrFile );
   CloseHandle( hStdOutRead );
   CloseHandle( hStdErrRead );
   CloseHandle( pi.hProcess );
   CloseHandle( pi.hThread );

   return 0;
}

*/