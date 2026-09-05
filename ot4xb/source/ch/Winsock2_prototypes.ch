#xtranslate wsa.accept( [<params,...>])  => FpQCall({"ws2_32","accept"},"__sl__sl__pt_@sl" [,<params>] )
#xtranslate wsa.bind( [<params,...>])  => FpQCall({"ws2_32","bind"},"__sl__sl__pt__sl" [,<params>] )
#xtranslate wsa.closesocket( [<params,...>])  => FpQCall({"ws2_32","closesocket"},"__sl__sl" [,<params>] )
#xtranslate wsa.connect( [<params,...>])  => FpQCall({"ws2_32","connect"},"__sl__sl__pt__sl" [,<params>] )
#xtranslate wsa.freeaddrinfo( [<params,...>]) => FpQCall({"ws2_32","freeaddrinfo"},"__vo__sl" [,<params>] )
#xtranslate wsa.getaddrinfo( [<params,...>])  => FpQCall({"ws2_32","getaddrinfo"},"__sl__pt__pt__pt_@sl" [,<params>] )
#xtranslate wsa.getnameinfo( [<p,...>])  => FpQCall({"ws2_32","getnameinfo"},"__sl__pt__sl__pt__sl__pt__sl__sl" [,<p>] )
#xtranslate wsa.recv( [<params,...>])  => FpQCall({"ws2_32","recv"},"__sl__sl__pt__sl__sl" [,<params>] )
#xtranslate wsa.send( [<params,...>])  => FpQCall({"ws2_32","send"},"__sl__sl__pt__sl__sl" [,<params>] )
#xtranslate wsa.shutdown( [<params,...>])  => FpQCall({"ws2_32","shutdown"},"__sl__sl__sl" [,<params>] )
#xtranslate wsa.socket( [<params,...>])  => FpQCall({"ws2_32","socket"},"__sl__sl__sl__sl" [,<params>] )
#xtranslate wsa.sendto( [<params,...>])    => FpQCall({"ws2_32","sendto"},"__sl__sl__pt__sl__sl__pt__sl" [,<params>] )
#xtranslate wsa.recvfrom( [<params,...>])  => FpQCall({"ws2_32","recvfrom"},"__sl__sl__pt__sl__sl__pt_@sl" [,<params>] )

#xtranslate wsa.htons( [<params,...>])  => FpQCall({"ws2_32","htons"},"__us__us" [,<params>] )
#xtranslate wsa.inet_addr( [<params,...>])  => FpQCall({"ws2_32","inet_addr"},"__sl__pt" [,<params>] )
#xtranslate wsa.inet_ntoa( [<params,...>])  => FpQCall({"ws2_32","inet_ntoa"},"c_sz__sl" [,<params>] )

#xtranslate wsa.listen( [<params,...>])  => FpQCall({"ws2_32","listen"},"__sl__sl__sl" [,<params>] )
#xtranslate wsa.getsockopt( [<p,...>])  => FpQCall({"ws2_32","getsockopt"},"__sl__sl__sl__sl?@sl_@sl" [,<p>] )

#xtranslate wsa.ioctlsocket( [<p,...>])  => FpQCall({"ws2_32","ioctlsocket"},"__sl__sl__sl_@sl" [,<p>] )
#xtranslate WSAAsyncSelect( [<params,...>])  => FpQCall({"ws2_32","WSAAsyncSelect"},"__sl__sl__hw__sl__sl" [,<params>] )

#xtranslate WSACleanup( [<params,...>])  => FpQCall({"ws2_32","WSACleanup"},"__vo" [,<params>] )
#xtranslate WSAGetLastError( [<params,...>])  => FpQCall({"ws2_32","WSAGetLastError"},"__sl" [,<params>] )
#xtranslate WSAStartup( [<params,...>])  => FpQCall({"ws2_32","WSAStartup"},"__sl__us__pt" [,<params>] )

#xtranslate WSAIoctl( [<p,...>])  => FpQCall({"ws2_32","WSAIoctl"},"__sl__sl__sl__pt__sl__pt__sl_@sl__pt__sl" [,<p>] )
#xtranslate WSAEventSelect( [<p,...>])  => FpQCall({"ws2_32","WSAEventSelect"},"__sl__sl__sl__sl" [,<p>] )
#xtranslate WSAWaitForMultipleEvents( [<p,...>])  => FpQCall({"ws2_32","WSAWaitForMultipleEvents"},"__sl__sl__pt__bo__sl__bo" [,<p>] )
#xtranslate WSAEnumNetworkEvents( [<p,...>])  =>FpQCall({"ws2_32","WSAEnumNetworkEvents"},"__sl__sl__sl__pt" [,<p>] )
#xtranslate WSAGetOverlappedResult( [<p,...>])  => FpQCall({"ws2_32","WSAGetOverlappedResult"},"__bo__sl__pt_@sl__bo_@sl" [,<p>] )
#xtranslate WSARecv( [<p,...>])  => FpQCall({"ws2_32","WSARecv"},"__sl__sl__pt__sl_@sl_@sl__pt__sl" [,<p>] )
#xtranslate WSASend( [<p,...>])  => FpQCall({"ws2_32","WSASend"},"__sl__sl__pt__sl_@sl__sl__pt__sl" [,<p>] )
//----------------------------------------------------------------------------------------------------------------------


