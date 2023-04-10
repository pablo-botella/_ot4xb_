
//------------------------------------------------------------
// Project: Open Tools for Xbase++ -
// Repository : http://www.xbwin.com -
// Author: Pablo Botella Navarro ( http://www.xbwin.com ) -
//------------------------------------------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <winsock2.h>
#include <ws2def.h>
#include <ws2tcpip.h>
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
/*
void defout( LPSTR & ps , int* pcb , LPSTR def , DWORD val , LPSTR old)
{
   int cb = wsprintf( ps,"\r\n#define %s 0x%08.8X " "/" "/ %s" , def , val , old );
   ps = _mk_ptr_(LPSTR,ps,cb);
   pcb[0] = pcb[0] + cb;
}
//----------------------------------------------------------------------------------------------------------------------
#define o( d , o ) defout( ps,pcb,#d,(DWORD)d,#o)
*/
//----------------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------

#pragma warning( disable : 4127 )
OT4XB_API int  wsa_select(SOCKET s , int ms , DWORD mask ) // mask: 1 read , 2 write , 4 error 
{
    if( ms == -1 ){ return 0; }
    fd_set r_st;
    fd_set w_st;
    fd_set e_st;
    fd_set* r  = 0;
    fd_set* w  = 0;
    fd_set* e  = 0;
    struct timeval tv;

    ZeroMemory(&tv,sizeof(tv));
    if( ms )
    {
       tv.tv_sec  = (int) (ms / 1000);
       tv.tv_usec = (ms - (tv.tv_sec*1000)) * 1000;
    } 
    if( mask & 1 ){ r = &r_st; FD_ZERO(r); FD_SET(s,r); }
    if( mask & 2 ){ w = &w_st; FD_ZERO(w); FD_SET(s,w); }    
    if( mask & 4 ){ e = &e_st; FD_ZERO(e); FD_SET(s,e); }    
    return select(1,r,w,e,&tv);
}
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4127 )
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL wsa_send_data( SOCKET s , LPSTR p , int cb , int ms )
{
   int i = 0;
   if( cb == -1){ if(p){ cb = _xstrlen(p); }}
   if( wsa_select(s,ms,2) < 0 ) return FALSE;
   while( cb > 0 )
   {
      int n = send(s,p,cb,0);
      if( n < 0 )
      {
         if( i > 5 ){ return FALSE; }
         int code = WSAGetLastError();
         if( code != WSAEWOULDBLOCK ){ return FALSE; }
         Sleep(100);
         i++;
      }
      else
      {
         cb -= n;
         p = _mk_ptr_(LPSTR,p,n);
         i = 0;
      }
   }
   return TRUE;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int wsa_receive_data( SOCKET s , LPBYTE buffer , int buffer_size , int ms )
{
   int result = 0;
   _bset(buffer,0,buffer_size); 
   if( ms != -2 )
   {
      if( wsa_select(s,ms,1) < 0) return FALSE;
   }
   while( !result )
   {
      result = recv(s,(LPSTR) buffer,buffer_size,0);
      if( result == 0 ){ return 0; }      
      if( result < 0 )
      {
         if( ms == -2 ){ return 0; }
         int code = WSAGetLastError();
         if( code != WSAEWOULDBLOCK ){ return 0; }
         if( wsa_select(s,1,1) < 0) return 0;
      } 
      return result;     
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API SOCKET get_connected_socket( LPSTR host , int port )
{
   addrinfo   hints;
   addrinfo * info = 0;
   char sz_port[16];

   ZeroMemory(&hints,sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;

   ZeroMemory(sz_port,sizeof(sz_port));
   wsprintf(sz_port,"%i",port);

   if(  getaddrinfo(host, sz_port, &hints, &info) == 0 )
   {
      if( info != 0 )
      {
         SOCKET s = INVALID_SOCKET;
         if( info->ai_addrlen >= sizeof(sockaddr_in) )
         {
            s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if( connect(s,info->ai_addr,sizeof(sockaddr)) != 0 ){ closesocket(s); s = INVALID_SOCKET; }
         }
         freeaddrinfo(info);
         info = 0;
         return s;
      }
   }
   return INVALID_SOCKET;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API SOCKET get_connected_socket2( LPSTR host , int port , LPSTR bind_ip )
{
   if( !bind_ip)
   {
      return get_connected_socket( host , port );
   }
   addrinfo   hints;
   addrinfo * info = 0;
   char sz_port[16];

   ZeroMemory(&hints,sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;

   ZeroMemory(sz_port,sizeof(sz_port));
   wsprintf(sz_port,"%i",port);


   
      
   if(  getaddrinfo(host, sz_port, &hints, &info) == 0 )
   {
      if( info != 0 )
      {
         SOCKET s = INVALID_SOCKET;
         if( info->ai_addrlen >= sizeof(sockaddr_in) )
         {
            s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            
            sockaddr_in    sai_bind;
            ZeroMemory( &sai_bind , sizeof(sockaddr_in) );
            sai_bind.sin_family = AF_INET;
            sai_bind.sin_port   = 0;
            sai_bind.sin_addr.s_addr = inet_addr(bind_ip);            
            if( bind( s,(sockaddr*) &sai_bind,sizeof(sai_bind)) != 0 )
            {
               closesocket(s);
               freeaddrinfo(info);
               bind_ip[0] = 0;
               return INVALID_SOCKET;
            }
            if( connect(s,info->ai_addr,sizeof(sockaddr)) != 0 ){ closesocket(s); s = INVALID_SOCKET; }
         }
         freeaddrinfo(info);
         info = 0;
         return s;
      }
   }
   return INVALID_SOCKET;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API int socks5_ssc_connect( SOCKET s , LPSTR host , int port , LPSTR user , LPSTR pwd , DWORD flags, void** keep_response)
{
   int cb_host = (int) ( host ? _xstrlen(host) : 0 );
   void* buffer = _xgrab(1024 );
   LPBYTE p = (LPBYTE) buffer;
   int cb;
   int result = 0;
   if( keep_response ){ *keep_response = 0; }
   
   
   if( (!s )|| (s == INVALID_SOCKET) ){ result = -1; goto label_cleanup; }
   if( (cb_host  < 1) || (cb_host > 255)  ){ result = -2; goto label_cleanup;}     
   if( (port  < 1) || (port > 0xFFFF)  ){ result = -3; goto label_cleanup;}        

   cb = 3;
   p[0] = 5; 
   p[1] = 1;
   p[2] = 0; // no authentication      
   p[3] = 2; // user/pwd method
   if( user && pwd ){ p[1] = 2; cb = 4; } 
   if( !wsa_send_data(s,(LPSTR)p,cb,0) ){ result = -101; goto label_cleanup;}
   ZeroMemory(p,4);
   if( wsa_receive_data(s,p,2,0) < 2 ){ result = -102; goto label_cleanup;}
   if( p[0] != 5 ){ result = -4; goto label_cleanup;}
   if( p[1] == 2 ) // user /pwd authorization
   {
      LPBYTE p2   = _mk_ptr_(LPBYTE,buffer,8);   
      int cb_user = (int) ( user ? _xstrlen(user) : 0 );
      int cb_pwd  = (int) ( pwd  ? _xstrlen(pwd)  : 0 );      
      if( (cb_user < 1) || (cb_user > 255)  ){ result = -501; goto label_cleanup;}
      if( (cb_pwd  < 1) || (cb_pwd  > 255)  ){ result = -502; goto label_cleanup;}  
      LPBYTE pp   = p2;
      
      *pp++ = 1;
      *pp++ = (BYTE) (cb_user & 0xFF);
      _bcopy(pp,(LPBYTE) user,(UINT) cb_user);
      pp = _mk_ptr_(LPBYTE,pp, cb_user);
      *pp++ = (BYTE) (cb_pwd & 0xFF);      
      _bcopy(pp,(LPBYTE) pwd,(UINT) cb_pwd);      
      pp = _mk_ptr_(LPBYTE,pp, cb_pwd); 
      cb = 3 + cb_user + cb_pwd;
      if( !wsa_send_data(s,(LPSTR)p2,cb,0) ){ result = -503; goto label_cleanup;}      
      ZeroMemory(p2,cb);
      if( wsa_receive_data(s,p2,2,0) < 2 ){ result = -504; goto label_cleanup;}      
      if( p2[1] != 0 ){ result = -205; goto label_cleanup;}      
   }
   else
   {
       if( p[1] != 0 ){ result = -500; goto label_cleanup;}
   }
   ZeroMemory(p,2); 
   *p++ = 5;
   *p++ = 1; // connect
   *p++ = 0;
   cb = 4 + 4 + 2;
   if( (flags & 0xFF) == 3 ) // host name
   {
      *p++ = 3; 
      *p++ = (BYTE) (cb_host & 0xFF);
      _bcopy(p,(LPBYTE) host,(UINT) cb_host);
      p = _mk_ptr_(LPBYTE,p, cb_host);
      cb = 4 + 1 + cb_host + 2;      
   }
   else // IP V4
   {
      *p++ = 1;  
      reinterpret_cast<DWORD*>(p)[0] = inet_addr( host );
      p = _mk_ptr_(LPBYTE,p, sizeof(DWORD));      
   }
   reinterpret_cast<WORD*>(p)[0] = htons( LOWORD(port) );
   p = (LPBYTE) buffer;   
   if( !wsa_send_data(s,(LPSTR)p,cb,0) ){ result = -110; goto label_cleanup;}         
   ZeroMemory(p,cb);   
   p = _mk_ptr_(LPBYTE,buffer,sizeof(DWORD));   
   cb = wsa_receive_data(s,p,512,0);
   if( keep_response )
   {
      *keep_response = buffer;
      _mk_ptr_(LPLONG,buffer,0)[0] = cb;
      buffer = 0;
   }
   if( cb < 6 ){ result = -111; goto label_cleanup;}
   if( p[1] != 0)
   {
      result = -(1000 + MAKELONG(MAKEWORD(p[1],0),0) );
      goto label_cleanup;
   }
   result = 0;
   label_cleanup: ;
   if( buffer){ _xfree( buffer ); buffer = 0; }
   return result;
}

// -----------------------------------------------------------------------------------------------------------------
     
END_EXTERN_C

