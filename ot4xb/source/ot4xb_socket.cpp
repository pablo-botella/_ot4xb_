
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
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------

#pragma warning( disable : 4127 )
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: wsa_select
            | syntax_: `int wsa_select( SOCKET s, int ms, DWORD mask )`
            | header: ot4xb_c_exported.h
            | category: c-api/socket
            | mangled-name: wsa_select
            | _kw_: wsa_select, Function
   }}*/
/*{{|desc: Tests one socket for readiness with a single select() call, waiting at most ms milliseconds.
    | params:
    - `s` SOCKET - Socket to test.
    - `ms` int - Timeout in milliseconds. 0 reports the current state without waiting; -1 skips the
      test completely and returns 0.
    - `mask` DWORD - Conditions to test, any combination of: 1 readable, 2 writable, 4 error.

    Returns int - Positive when the socket is ready for at least one requested condition, 0 on timeout
      (always 0 when ms is -1), SOCKET_ERROR when select() fails. }}*/
OT4XB_API int  wsa_select(SOCKET s , int ms , DWORD mask )
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#pragma warning( default : 4127 )
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: wsa_send_data
            | syntax_: `BOOL wsa_send_data( SOCKET s, LPSTR p, int cb, int ms )`
            | header: ot4xb_c_exported.h
            | category: c-api/socket
            | mangled-name: wsa_send_data
            | _kw_: wsa_send_data, Function
   }}*/
/*{{|desc: Sends a data block through a socket, looping until every byte is sent. On WSAEWOULDBLOCK it
      retries every 100 ms, up to 6 times in a row, then gives up; any other send error aborts.
    | params:
    - `s` SOCKET - Connected socket to send through.
    - `p` LPSTR - Data to send.
    - `cb` int - Number of bytes to send; -1 sends p as a zero terminated string.
    - `ms` int - Milliseconds to wait for the socket to become writable before sending; 0 or -1 start
      sending at once. A timed out wait does not abort the send, only a failed select() does.

    Returns BOOL - TRUE when the whole block was sent, FALSE on error or when the retry limit is reached. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: wsa_receive_data
            | syntax_: `int wsa_receive_data( SOCKET s, LPBYTE buffer, int buffer_size, int ms )`
            | header: ot4xb_c_exported.h
            | category: c-api/socket
            | mangled-name: wsa_receive_data
            | _kw_: wsa_receive_data, Function
   }}*/
/*{{|desc: Receives up to buffer_size bytes from a socket. The buffer is zero filled first. On
      WSAEWOULDBLOCK it waits up to 1 ms more for data and retries; still not readable, it returns 0.
    | params:
    - `s` SOCKET - Connected socket to read from.
    - `buffer` LPBYTE - Destination buffer, zero filled before receiving.
    - `buffer_size` int - Capacity of buffer in bytes.
    - `ms` int - Milliseconds to wait for data before reading; 0 or -1 read at once; -2 performs one
      single recv() attempt with no wait and no retry.

    Returns int - Number of bytes received, or 0 on timeout, on error or when the peer closed the
      connection. }}*/
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
         if( wsa_select(s,1,1) <= 0){ return 0; }   // not readable within the wait: give up
         result = 0;                              // readable: loop back and retry recv
      } 
      if( result > 0 ){ return result; }     
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: get_connected_socket
            | syntax_: `SOCKET get_connected_socket( LPSTR host, int port )`
            | header: ot4xb_c_exported.h
            | category: c-api/socket
            | mangled-name: get_connected_socket
            | _kw_: get_connected_socket, Function
   }}*/
/*{{|desc: Resolves a host name and opens a TCP connection to it (IPv4 only).
    | params:
    - `host` LPSTR - Host name or dotted IP address to connect to.
    - `port` int - TCP port to connect to.

    Returns SOCKET - Connected socket, or INVALID_SOCKET when resolution or connection fails. Release it
      with closesocket(). }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: get_connected_socket2
            | syntax_: `SOCKET get_connected_socket2( LPSTR host, int port, LPSTR bind_ip )`
            | header: ot4xb_c_exported.h
            | category: c-api/socket
            | mangled-name: get_connected_socket2
            | _kw_: get_connected_socket2, Function
   }}*/
/*{{|desc: Same as get_connected_socket() but the new socket is bound to a local IP address before
      connecting, so the caller chooses the outgoing interface.
    | params:
    - `host` LPSTR - Host name or dotted IP address to connect to.
    - `port` int - TCP port to connect to.
    - `bind_ip` LPSTR - Local IP address (dotted string) to bind the socket to; the local port is
      left to the system. NULL behaves exactly like get_connected_socket().

    Returns SOCKET - Connected socket, or INVALID_SOCKET when resolution, bind or connection fails. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: socks5_ssc_connect
            | syntax_: ```
            | header: ot4xb_c_exported.h
                 int socks5_ssc_connect( SOCKET s, LPSTR host, int port, LPSTR user, LPSTR pwd, DWORD flags, void * * keep_response )
              ```
            | category: c-api/socket
            | mangled-name: socks5_ssc_connect
            | _kw_: socks5_ssc_connect, Function
   }}*/
/*{{|desc: Runs the SOCKS5 client handshake on a socket already connected to a proxy server, asking the
      proxy to connect to host:port. On success the socket has become a tunnel to that target.
    | params:
    - `s` SOCKET - Socket already connected to the SOCKS5 proxy.
    - `host` LPSTR - Target host, 1 to 255 characters. See flags for how it is sent to the proxy.
    - `port` int - Target TCP port, 1 to 65535.
    - `user` LPSTR - User name, 1 to 255 characters; NULL for no authentication. When both user and
      pwd are given the proxy may still pick no authentication.
    - `pwd` LPSTR - Password, 1 to 255 characters; NULL for no authentication.
    - `flags` DWORD - Low byte 3 sends host as a name for the proxy to resolve; any other value
      converts host with inet_addr() and sends it as an IPv4 address.
    - `keep_response` void * * - Optional; when not NULL receives a _xgrab() block holding the raw
      proxy answer to the connect request: a LONG byte count followed by the answer bytes. Release it with
      _xfree(). Left NULL when the handshake fails before that answer.

    Returns int - 0 on success. Negative on failure: -(1000+n) is a proxy denial with SOCKS5 reply code
      n, other values flag bad parameters, authentication or send/receive errors. }}*/
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
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
     
END_EXTERN_C

