
// -----------------------------------------------------------------------------------------------------------------
#ifndef WSABASEERR
#define WSABASEERR                                                                                  10000
#define WSAEACCES                                                                                   10013
#define WSAEADDRINUSE                                                                               10048
#define WSAEADDRNOTAVAIL                                                                            10049
#define WSAEAFNOSUPPORT                                                                             10047
#define WSAEALREADY                                                                                 10037
#define WSAEBADF                                                                                    10009
#define WSAECANCELLED                                                                               10103
#define WSAECONNABORTED                                                                             10053
#define WSAECONNREFUSED                                                                             10061
#define WSAECONNRESET                                                                               10054
#define WSAEDESTADDRREQ                                                                             10039
#define WSAEDISCON                                                                                  10101
#define WSAEDQUOT                                                                                   10069
#define WSAEFAULT                                                                                   10014
#define WSAEHOSTDOWN                                                                                10064
#define WSAEHOSTUNREACH                                                                             10065
#define WSAEINPROGRESS                                                                              10036
#define WSAEINTR                                                                                    10004
#define WSAEINVAL                                                                                   10022
#define WSAEINVALIDPROCTABLE                                                                        10104
#define WSAEINVALIDPROVIDER                                                                         10105
#define WSAEISCONN                                                                                  10056
#define WSAELOOP                                                                                    10062
#define WSAEMFILE                                                                                   10024
#define WSAEMSGSIZE                                                                                 10040
#define WSAENAMETOOLONG                                                                             10063
#define WSAENETDOWN                                                                                 10050
#define WSAENETRESET                                                                                10052
#define WSAENETUNREACH                                                                              10051
#define WSAENOBUFS                                                                                  10055
#define WSAENOMORE                                                                                  10102
#define WSAENOPROTOOPT                                                                              10042
#define WSAENOTCONN                                                                                 10057
#define WSAENOTEMPTY                                                                                10066
#define WSAENOTSOCK                                                                                 10038
#define WSAEOPNOTSUPP                                                                               10045
#define WSAEPFNOSUPPORT                                                                             10046
#define WSAEPROCLIM                                                                                 10067
#define WSAEPROTONOSUPPORT                                                                          10043
#define WSAEPROTOTYPE                                                                               10041
#define WSAEPROVIDERFAILEDINIT                                                                      10106
#define WSAEREFUSED                                                                                 10112
#define WSAEREMOTE                                                                                  10071
#define WSAESHUTDOWN                                                                                10058
#define WSAESOCKTNOSUPPORT                                                                          10044
#define WSAESTALE                                                                                   10070
#define WSAETIMEDOUT                                                                                10060
#define WSAETOOMANYREFS                                                                             10059
#define WSAEUSERS                                                                                   10068
#define WSAEWOULDBLOCK                                                                              10035
#define WSAHOST_NOT_FOUND                                                                           11001
#define WSANOTINITIALISED                                                                           10093
#define WSANO_DATA                                                                                  11004
#define WSANO_RECOVERY                                                                              11003
#define WSASERVICE_NOT_FOUND                                                                        10108
#define WSASYSCALLFAILURE                                                                           10107
#define WSASYSNOTREADY                                                                              10091
#define WSATRY_AGAIN                                                                                11002
#define WSATYPE_NOT_FOUND                                                                           10109
#define WSAVERNOTSUPPORTED                                                                          10092
#define WSA_E_CANCELLED                                                                             10111
#define WSA_E_NO_MORE                                                                               10110
#define WSA_QOS_ADMISSION_FAILURE                                                                   11010
#define WSA_QOS_BAD_OBJECT                                                                          11013
#define WSA_QOS_BAD_STYLE                                                                           11012
#define WSA_QOS_EFILTERCOUNT                                                                        11021
#define WSA_QOS_EFILTERSTYLE                                                                        11019
#define WSA_QOS_EFILTERTYPE                                                                         11020
#define WSA_QOS_EFLOWCOUNT                                                                          11023
#define WSA_QOS_EFLOWDESC                                                                           11026
#define WSA_QOS_EFLOWSPEC                                                                           11017
#define WSA_QOS_EOBJLENGTH                                                                          11022
#define WSA_QOS_EPOLICYOBJ                                                                          11025
#define WSA_QOS_EPROVSPECBUF                                                                        11018
#define WSA_QOS_EPSFILTERSPEC                                                                       11028
#define WSA_QOS_EPSFLOWSPEC                                                                         11027
#define WSA_QOS_ESDMODEOBJ                                                                          11029
#define WSA_QOS_ESERVICETYPE                                                                        11016
#define WSA_QOS_ESHAPERATEOBJ                                                                       11030
#define WSA_QOS_EUNKOWNPSOBJ                                                                        11024
#define WSA_QOS_GENERIC_ERROR                                                                       11015
#define WSA_QOS_NO_RECEIVERS                                                                        11008
#define WSA_QOS_NO_SENDERS                                                                          11007
#define WSA_QOS_POLICY_FAILURE                                                                      11011
#define WSA_QOS_RECEIVERS                                                                           11005
#define WSA_QOS_REQUEST_CONFIRMED                                                                   11009
#define WSA_QOS_RESERVED_PETYPE                                                                     11031
#define WSA_QOS_SENDERS                                                                             11006
#define WSA_QOS_TRAFFIC_CTRL_ERROR                                                                  11014
#endif

// -----------------------------------------------------------------------------------------------------------------

#define AF_UNSPEC                    0
#define AF_UNIX                      1
#define AF_INET                      2
#define AF_IMPLINK                   3
#define AF_PUP                       4
#define AF_CHAOS                     5
#define AF_NS                        6
#define AF_IPX                       AF_NS
#define AF_ISO                       7
#define AF_OSI                       AF_ISO
#define AF_ECMA                      8
#define AF_DATAKIT                   9
#define AF_CCITT                     10
#define AF_SNA                       11
#define AF_DECnet                    12
#define AF_DLI                       13
#define AF_LAT                       14
#define AF_HYLINK                    15
#define AF_APPLETALK                 16
#define AF_NETBIOS                   17
#define AF_VOICEVIEW                 18
#define AF_FIREFOX                   19
#define AF_UNKNOWN1                  20
#define AF_BAN                       21
#define AF_ATM                       22
#define AF_INET6                     23
#define AF_CLUSTER                   24
#define AF_12844                     25
#define AF_IRDA                      26
#define AF_NETDES                    28
#define AF_TCNPROCESS                29
#define AF_TCNMESSAGE                30
#define AF_ICLFXBM                   31
#define AF_BTH                       32
#define SOCK_STREAM                  1
#define SOCK_DGRAM                   2
#define SOCK_RAW                     3
#define SOCK_RDM                     4
#define SOCK_SEQPACKET               5
#define SOL_SOCKET                   0xFFFF
#define SO_DEBUG                     0x0001
#define SO_ACCEPTCONN                0x0002
#define SO_REUSEADDR                 0x0004
#define SO_KEEPALIVE                 0x0008
#define SO_DONTROUTE                 0x0010
#define SO_BROADCAST                 0x0020
#define SO_USELOOPBACK               0x0040
#define SO_LINGER                    0x0080
#define SO_OOBINLINE                 0x0100
#define SO_DONTLINGER 0xFFFFFF7F // nNot(SO_LINGER)
#define SO_EXCLUSIVEADDRUSE 0xFFFFFFFB // nNot(SO_REUSEADDR)
#define SO_SNDBUF                    0x1001
#define SO_RCVBUF                    0x1002
#define SO_SNDLOWAT                  0x1003
#define SO_RCVLOWAT                  0x1004
#define SO_SNDTIMEO                  0x1005
#define SO_RCVTIMEO                  0x1006
#define SO_ERROR                     0x1007
#define SO_TYPE                      0x1008
#define SO_BSP_STATE                 0x1009
#define SO_GROUP_ID                  0x2001
#define SO_GROUP_PRIORITY            0x2002
#define SO_MAX_MSG_SIZE              0x2003
#define SO_PROTOCOL_INFOA            0x2004
#define SO_PROTOCOL_INFOW            0x2005
#define SO_PROTOCOL_INFO             SO_PROTOCOL_INFOA
#define PVD_CONFIG                   0x3001
#define SO_CONDITIONAL_ACCEPT        0x3002
#define SO_PAUSE_ACCEPT              0x3003
#define SO_COMPARTMENT_ID            0x3004
#define SO_RANDOMIZE_PORT            0x3005
#define WSK_SO_BASE                  0x4000
#define TCP_NODELAY                  0x0001
#define _SS_MAXSIZE                  128
#define _SS_ALIGNSIZE                8
#define _SS_PAD1SIZE                 6
#define _SS_PAD2SIZE                 112
#define IOC_UNIX                     0x00000000
#define IOC_WS2                      0x08000000
#define IOC_PROTOCOL                 0x10000000
#define IOC_VENDOR                   0x18000000
#define IOC_WSK 0x0F000000 // nOr( IOC_WS2 , 0x07000000)
#xtranslate _WSAIO(<x>,<y>)          => nOr(IOC_VOID ,<x>,<y>)
#xtranslate _WSAIOR(<x>,<y>)         => nOr(IOC_OUT  ,<x>,<y>)
#xtranslate _WSAIOW(<x>,<y>)         => nOr(IOC_IN   ,<x>,<y>)
#xtranslate _WSAIORW(<x>,<y>)        => nOr(IOC_INOUT,<x>,<y>)
#define SIO_ENABLE_CIRCULAR_QUEUEING 0x28000002 // "nOr(IOC_VOID,IOC_WS2,2)"

#define SIO_FLUSH 0x28000004 // "nOr(IOC_VOID,IOC_WS2,4)"
#define SIO_ADDRESS_LIST_CHANGE 0x28000017 // "nOr(IOC_VOID,IOC_WS2,23)"
#define SIO_ASSOCIATE_HANDLE 0x88000001 // "nOr(IOC_IN,IOC_WS2,1)"
#define SIO_MULTIPOINT_LOOPBACK 0x88000009 // "nOr(IOC_IN,IOC_WS2,9)"
#define SIO_MULTICAST_SCOPE 0x8800000A // "nOr(IOC_IN,IOC_WS2,10)"
#define SIO_SET_QOS 0x8800000B // "nOr(IOC_IN,IOC_WS2,11)"
#define SIO_SET_GROUP_QOS 0x8800000C // "nOr(IOC_IN,IOC_WS2,12)"
#define SIO_ROUTING_INTERFACE_CHANGE 0x88000015 // "nOr(IOC_IN,IOC_WS2,21)"
#define SIO_ADDRESS_LIST_QUERY 0x48000016 // "nOr(IOC_OUT,IOC_WS2,22)"


#define SIO_QUERY_TARGET_PNP_HANDLE 0x48000018 // "nOr(IOC_OUT,IOC_WS2,24)"
#define SIO_FIND_ROUTE 0x48000003 // "nOr(IOC_OUT,IOC_WS2,3)"
#define SIO_GET_BROADCAST_ADDRESS 0x48000005 // "nOr(IOC_OUT,IOC_WS2,5)"
#define SIO_GET_EXTENSION_FUNCTION_POINTER 0xC8000006 // "nOr(IOC_INOUT,IOC_WS2,6)"
#define SIO_GET_QOS 0xC8000007 // "nOr(IOC_INOUT,IOC_WS2,7)"
#define SIO_GET_GROUP_QOS 0xC8000008 // "nOr(IOC_INOUT,IOC_WS2,8)"
#define SIO_TRANSLATE_HANDLE 0xC800000D // "nOr(IOC_INOUT,IOC_WS2,13)"
#define SIO_ROUTING_INTERFACE_QUERY 0xC8000014 // "nOr(IOC_INOUT,IOC_WS2,20)"
#define SIO_ADDRESS_LIST_SORT 0xC8000019 // "nOr(IOC_INOUT,IOC_WS2,25)"
#define SIO_RESERVED_1 0x8800001A // "nOr(IOC_IN,IOC_WS2,26)"
#define SIO_RESERVED_2 0x88000021 // "nOr(IOC_IN,IOC_WS2,33)"
#define IPPROTO_IP                           0
#define IPPROTO_HOPOPTS                      0
#define IPPROTO_ICMP                         1
#define IPPROTO_IGMP                         2
#define IPPROTO_GGP                          3
#define IPPROTO_IPV4                         4
#define IPPROTO_ST                           5
#define IPPROTO_TCP                          6
#define IPPROTO_CBT                          7
#define IPPROTO_EGP                          8
#define IPPROTO_IGP                          9
#define IPPROTO_PUP                          12
#define IPPROTO_UDP                          17
#define IPPROTO_IDP                          22
#define IPPROTO_RDP                          27
#define IPPROTO_IPV6                         41
#define IPPROTO_ROUTING                      43
#define IPPROTO_FRAGMENT                     44
#define IPPROTO_ESP                          50
#define IPPROTO_AH                           51
#define IPPROTO_ICMPV6                       58
#define IPPROTO_NONE                         59
#define IPPROTO_DSTOPTS                      60
#define IPPROTO_ND                           77
#define IPPROTO_ICLFXBM                      78
#define IPPROTO_PIM                          103
#define IPPROTO_PGM                          113
#define IPPROTO_L2TP                         115
#define IPPROTO_SCTP                         132
#define IPPROTO_RAW                          255
#define IPPROTO_MAX                          256
#define IPPROTO_RESERVED_RAW                 257
#define IPPROTO_RESERVED_IPSEC               258
#define IPPROTO_RESERVED_IPSECOFFLOAD        259
#define IPPROTO_RESERVED_MAX                 260
#define IPPORT_TCPMUX           1
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_QOTD             17
#define IPPORT_MSP              18
#define IPPORT_CHARGEN          19
#define IPPORT_FTP_DATA         20
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95
#define IPPORT_POP3             110
#define IPPORT_NTP              123
#define IPPORT_EPMAP            135
#define IPPORT_NETBIOS_NS       137
#define IPPORT_NETBIOS_DGM      138
#define IPPORT_NETBIOS_SSN      139
#define IPPORT_IMAP             143
#define IPPORT_SNMP             161
#define IPPORT_SNMP_TRAP        162
#define IPPORT_IMAP3            220
#define IPPORT_LDAP             389
#define IPPORT_HTTPS            443
#define IPPORT_MICROSOFT_DS     445
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
#define IPPORT_RESERVED         1024
#define IPPORT_REGISTERED_MIN   IPPORT_RESERVED
#define IPPORT_REGISTERED_MAX   0xBFFF
#define IPPORT_DYNAMIC_MIN      0xC000
#define IPPORT_DYNAMIC_MAX      0xFFFF
#define IN_CLASSA(i)            (nAnd( i , dwFix(0x8000,0)) == 0)
#define IN_CLASSA_NET           dwfix(0xFF00,0)
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          0x00FFFFFF
#define IN_CLASSA_MAX           128
#define IN_CLASSB(i)            (nAnd(i,dwFix(0xC000,0)) == dwFix(0x8000,0) )
#define IN_CLASSB_NET           dwfix(0xFFFF,0)
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          0x0000FFFF
#define IN_CLASSB_MAX           65536
#define IN_CLASSC(i)            (nAnd(i,dwFix(0xE000,0)) == dwFix(0xC000,0) )
#define IN_CLASSC_NET           dwfix(0xFFFF,0xFF00)
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          0x000000FF
#define IN_CLASSD(i)            (nAnd(i,dwFix(0xF000,0)) == dwFix(0xE000,0) )
#define IN_CLASSD_NET           dwfix(0xF000,0)
#define IN_CLASSD_NSHIFT        28
#define IN_CLASSD_HOST          dwfix(0x0FFF,0xFFFF)
#define IN_MULTICAST(i)         IN_CLASSD(i)
#define INADDR_ANY              0
#define INADDR_LOOPBACK         dwfix(0x7F00,0x0001)
#define INADDR_BROADCAST        dwfix(0xFFFF,0xFFFF)
#define INADDR_NONE             dwfix(0xFFFF,0xFFFF)
#xtranslate ScopeLevel.Interface    => 1
#xtranslate ScopeLevel.Link         => 2
#xtranslate ScopeLevel.Subnet       => 3
#xtranslate ScopeLevel.Admin        => 4
#xtranslate ScopeLevel.Site         => 5
#xtranslate ScopeLevel.Organization => 8
#xtranslate ScopeLevel.Global       => 14
#xtranslate ScopeLevel.Count        => 16
#define SCOPEID_UNSPECIFIED_INIT    __i32(0,0)
#define IOCPARM_MASK                0x7F
#define IOC_VOID                    0x20000000
#define IOC_OUT                     0x40000000
#define IOC_IN                      0x80000000
#define IOC_INOUT                   0xC0000000 // "nOr(IOC_IN,IOC_OUT)"
#xtranslate _IO(<x>,<y>)       =>   nOr(IOC_VOID,nLShift(<x>,8),<y>)
#xtranslate _IOR(<x>,<y>,<typesize>)  =>   nOr(IOC_OUT,nLShift(nAnd(<typesize>,IOCPARM_MASK),16),nLShift(<x>,8),<y>)
#xtranslate _IOW(<x>,<y>,<typesize>)  =>   nOr(IOC_IN ,nLShift(nAnd(<typesize>,IOCPARM_MASK),16),nLShift(<x>,8),<y>)
#define MSG_TRUNC       0x0100
#define MSG_CTRUNC      0x0200
#define MSG_BCAST       0x0400
#define MSG_MCAST       0x0800
#define FIONREAD        0x4004667F // "_IOR(0x66, 127, 4)"
#define FIONBIO         dwfix(0x8004,0x667E) // "_IOW(0x66, 126, 4)"
#define FIOASYNC        dwfix(0x8004,0x667D) // "_IOW(0x66, 125, 4)"
#define SIOCSHIWAT      dwfix(0x8004,0x7300) // "_IOW(0x73, 0,4)"
#define SIOCGHIWAT      0x40047301) // "_IOR(0x73, 1,4)"
#define SIOCSLOWAT      dwfix(0x8004,0x7302) // "_IOW(0x73, 2,4)"
#define SIOCGLOWAT      0x40047303 // "_IOR(0x73, 3,4)"
#define SIOCATMARK      0x40047307 // "_IOR(0x73, 7,4)"
#define IMPLINK_IP              155
#define IMPLINK_LOWEXPER        156
#define IMPLINK_HIGHEXPER       158
#define ADDR_ANY                INADDR_ANY
#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128
#define INVALID_SOCKET          nNot(0)
#define SOCKET_ERROR            dwminus(1)
#define FROM_PROTOCOL_INFO      dwminus(1)
#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_IPX          AF_IPX
#define PF_ISO          AF_ISO
#define PF_OSI          AF_OSI
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK
#define PF_VOICEVIEW    AF_VOICEVIEW
#define PF_FIREFOX      AF_FIREFOX
#define PF_UNKNOWN1     AF_UNKNOWN1
#define PF_BAN          AF_BAN
#define PF_ATM          AF_ATM
#define PF_INET6        AF_INET6
#define PF_BTH          AF_BTH
#define PF_MAX          AF_MAX
#define SOMAXCONN       0x7FFFFFFF
#define MSG_OOB         0x1
#define MSG_PEEK        0x2
#define MSG_DONTROUTE   0x4
#define MSG_WAITALL     0x8
#define MSG_PARTIAL     0x8000
#define MSG_INTERRUPT   0x10
#define MSG_MAXIOVLEN   16
#define MAXGETHOSTSTRUCT        1024
#define FD_READ_BIT      0
#define FD_READ 0x00000001 // "nLShift(1,FD_READ_BIT)"
#define FD_WRITE_BIT     1
#define FD_WRITE 0x00000002 // "nLShift(1,FD_WRITE_BIT)"
#define FD_OOB_BIT       2
#define FD_OOB 0x00000004 // "nLShift(1,FD_OOB_BIT)"
#define FD_ACCEPT_BIT    3
#define FD_ACCEPT 0x00000008 // "nLShift(1,FD_ACCEPT_BIT)"
#define FD_CONNECT_BIT   4
#define FD_CONNECT 0x00000010 // "nLShift(1,FD_CONNECT_BIT)"
#define FD_CLOSE_BIT     5
#define FD_CLOSE 0x00000020 // "nLShift(1,FD_CLOSE_BIT)"
#define FD_QOS_BIT       6
#define FD_QOS 0x00000040 // "nLShift(1,FD_QOS_BIT)"
#define FD_GROUP_QOS_BIT 7
#define FD_GROUP_QOS 0x00000080 // "nLShift(1,FD_GROUP_QOS_BIT)"
#define FD_ROUTING_INTERFACE_CHANGE_BIT 8
#define FD_ROUTING_INTERFACE_CHANGE 0x00000100 // "nLShift(1,FD_ROUTING_INTERFACE_CHANGE_BIT)"
#define FD_ADDRESS_LIST_CHANGE_BIT 9
#define FD_ADDRESS_LIST_CHANGE 0x00000200 // "nLShift(1,FD_ADDRESS_LIST_CHANGE_BIT)"
#define FD_MAX_EVENTS    10
#define FD_ALL_EVENTS 0x000003FF // "(nLShift(1,FD_MAX_EVENTS) - 1)"
//----------------------------------------------------------------------------------------------------------------------
#define WSA_IO_PENDING          997
#define WSA_IO_INCOMPLETE       996
#define WSA_INVALID_HANDLE      6
#define WSA_INVALID_PARAMETER   87
#define WSA_NOT_ENOUGH_MEMORY   8
#define WSA_OPERATION_ABORTED   995
#define WSA_INVALID_EVENT       0
#define WSA_MAXIMUM_WAIT_EVENTS 64
#define WSA_WAIT_FAILED         dwfix(0xFFFF,0xFFFF)
#define WSA_WAIT_EVENT_0        0
#define WSA_WAIT_IO_COMPLETION  0xC0
#define WSA_WAIT_TIMEOUT        258
#define WSA_INFINITE            dwfix(0xFFFF,0xFFFF)
//----------------------------------------------------------------------------------------------------------------------
#define SERVICETYPE_NOTRAFFIC               0x0000
#define SERVICETYPE_BESTEFFORT              0x0001
#define SERVICETYPE_CONTROLLEDLOAD          0x0002
#define SERVICETYPE_GUARANTEED              0x0003
#define SERVICETYPE_NETWORK_UNAVAILABLE     0x0004
#define SERVICETYPE_GENERAL_INFORMATION     0x0005
#define SERVICETYPE_NOCHANGE                0x0006
#define SERVICETYPE_NONCONFORMING           0x0009
#define SERVICETYPE_NETWORK_CONTROL         0x000A
#define SERVICETYPE_QUALITATIVE             0x000D
#define SERVICE_BESTEFFORT                  dwfix(0x8001,0)
#define SERVICE_CONTROLLEDLOAD              dwfix(0x8002,0)
#define SERVICE_GUARANTEED                  dwfix(0x8004,0)
#define SERVICE_QUALITATIVE                 dwfix(0x8020,0)
#define SERVICE_NO_TRAFFIC_CONTROL          dwfix(0x8100,0)
#define SERVICE_NO_QOS_SIGNALING            dwfix(0x4000,0)
//----------------------------------------------------------------------------------------------------------------------
#define QOS_NOT_SPECIFIED            dwfix(0xFFFF,0xFFFF)
#define POSITIVE_INFINITY_RATE       dwfix(0xFFFF,0xFFFE)
#define   QOS_GENERAL_ID_BASE        2000
#define   QOS_OBJECT_END_OF_LIST     (0x0001 + QOS_GENERAL_ID_BASE)
#define   QOS_OBJECT_SD_MODE         (0x0002 + QOS_GENERAL_ID_BASE)
#define   QOS_OBJECT_SHAPING_RATE	 (0x0003 + QOS_GENERAL_ID_BASE)
#define   QOS_OBJECT_DESTADDR        (0x0004 + QOS_GENERAL_ID_BASE)
//----------------------------------------------------------------------------------------------------------------------
#define TC_NONCONF_BORROW      0
#define TC_NONCONF_SHAPE       1
#define TC_NONCONF_DISCARD     2
#define TC_NONCONF_BORROW_PLUS 3
#define CF_ACCEPT       0x0000
#define CF_REJECT       0x0001
#define CF_DEFER        0x0002
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02
#define SG_UNCONSTRAINED_GROUP   0x01
#define SG_CONSTRAINED_GROUP     0x02
#define MAX_PROTOCOL_CHAIN 7
#define BASE_PROTOCOL      1
#define LAYERED_PROTOCOL   0
#define WSAPROTOCOL_LEN  255
#define PFL_MULTIPLE_PROTO_ENTRIES          0x00000001
#define PFL_RECOMMENDED_PROTO_ENTRY         0x00000002
#define PFL_HIDDEN                          0x00000004
#define PFL_MATCHES_PROTOCOL_ZERO           0x00000008
#define XP1_CONNECTIONLESS                  0x00000001
#define XP1_GUARANTEED_DELIVERY             0x00000002
#define XP1_GUARANTEED_ORDER                0x00000004
#define XP1_MESSAGE_ORIENTED                0x00000008
#define XP1_PSEUDO_STREAM                   0x00000010
#define XP1_GRACEFUL_CLOSE                  0x00000020
#define XP1_EXPEDITED_DATA                  0x00000040
#define XP1_CONNECT_DATA                    0x00000080
#define XP1_DISCONNECT_DATA                 0x00000100
#define XP1_SUPPORT_BROADCAST               0x00000200
#define XP1_SUPPORT_MULTIPOINT              0x00000400
#define XP1_MULTIPOINT_CONTROL_PLANE        0x00000800
#define XP1_MULTIPOINT_DATA_PLANE           0x00001000
#define XP1_QOS_SUPPORTED                   0x00002000
#define XP1_INTERRUPT                       0x00004000
#define XP1_UNI_SEND                        0x00008000
#define XP1_UNI_RECV                        0x00010000
#define XP1_IFS_HANDLES                     0x00020000
#define XP1_PARTIAL_MESSAGE                 0x00040000
#define XP1_SAN_SUPPORT_SDP                 0x00080000
#define BIGENDIAN                           0x0000
#define LITTLEENDIAN                        0x0001
#define SECURITY_PROTOCOL_NONE              0x0000
#define JL_SENDER_ONLY                      0x01
#define JL_RECEIVER_ONLY                    0x02
#define JL_BOTH                             0x04
#define WSA_FLAG_OVERLAPPED                 0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT          0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF          0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT          0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF          0x10
#define WSA_FLAG_ACCESS_SYSTEM_SECURITY     0x40
#define SIO_NSP_NOTIFY_CHANGE               dwfix(0x8800,0x0019) // "_WSAIOW(IOC_WS2,25)"
#define NSP_NOTIFY_IMMEDIATELY              0
#define NSP_NOTIFY_HWND                     1
#define NSP_NOTIFY_EVENT                    2
#define NSP_NOTIFY_PORT                     3
#define NSP_NOTIFY_APC                      4
#define TH_NETDEV                           0x00000001
#define TH_TAPI                             0x00000002
#define SERVICE_MULTIPLE                    0x00000001
#define NS_ALL                              0
#define NS_SAP                              1
#define NS_NDS                              2
#define NS_PEER_BROWSE                      3
#define NS_SLP                              5
#define NS_DHCP                             6
#define NS_TCPIP_LOCAL                      10
#define NS_TCPIP_HOSTS                      11
#define NS_DNS                              12
#define NS_NETBT                            13
#define NS_WINS                             14
#define NS_NLA                              15
#define NS_BTH                              16
#define NS_NBP                              20
#define NS_MS                               30
#define NS_STDA                             31
#define NS_NTDS                             32
#define NS_EMAIL                            37
#define NS_PNRPNAME                         38
#define NS_PNRPCLOUD                        39
#define NS_X500                             40
#define NS_NIS                              41
#define NS_NISPLUS                          42
#define NS_WRQ                              50
#define NS_NETDES                           60
#define RES_UNUSED_1                        0x00000001
#define RES_FLUSH_CACHE                     0x00000002
#define RES_SERVICE                         0x00000004
#define SERVICE_TYPE_VALUE_IPXPORT          "IpxSocket"
#define SERVICE_TYPE_VALUE_SAPID            "SapId"
#define SERVICE_TYPE_VALUE_TCPPORT          "TcpPort"
#define SERVICE_TYPE_VALUE_UDPPORT          "UdpPort"
#define SERVICE_TYPE_VALUE_OBJECTID         "ObjectId"
#define COMP_EQUAL                          0
#define COMP_NOTLESS                        1
#define LUP_DEEP                            0x0001
#define LUP_CONTAINERS                      0x0002
#define LUP_NOCONTAINERS                    0x0004
#define LUP_NEAREST                         0x0008
#define LUP_RETURN_NAME                     0x0010
#define LUP_RETURN_TYPE                     0x0020
#define LUP_RETURN_VERSION                  0x0040
#define LUP_RETURN_COMMENT                  0x0080
#define LUP_RETURN_ADDR                     0x0100
#define LUP_RETURN_BLOB                     0x0200
#define LUP_RETURN_ALIASES                  0x0400
#define LUP_RETURN_QUERY_STRING             0x0800
#define LUP_RETURN_ALL                      0x0FF0
#define LUP_RES_SERVICE                     0x8000
#define LUP_FLUSHCACHE                      0x1000
#define LUP_FLUSHPREVIOUS                   0x2000
#define LUP_NON_AUTHORITATIVE               0x4000
#define LUP_SECURE                          0x8000
#define LUP_RETURN_PREFERRED_NAMES          0x10000
#define LUP_ADDRCONFIG                      0x00100000
#define LUP_DUAL_ADDR                       0x00200000
#define RESULT_IS_ALIAS                     0x0001
#define RESULT_IS_ADDED                     0x0010
#define RESULT_IS_CHANGED                   0x0020
#define RESULT_IS_DELETED                   0x0040
#define RNRSERVICE_REGISTER                 0
#define RNRSERVICE_DEREGISTER               1
#define RNRSERVICE_DELETE                   2
//----------------------------------------------------------------------------------------------------------------------
#define POLLRDNORM  0x0100
#define POLLRDBAND  0x0200
#define POLLIN      nOr(POLLRDNORM,POLLRDBAND)
#define POLLPRI     0x0400
#define POLLWRNORM  0x0010
#define POLLOUT     (POLLWRNORM)
#define POLLWRBAND  0x0020
#define POLLERR     0x0001
#define POLLHUP     0x0002
#define POLLNVAL    0x0004
#define WSAMAKEASYNCREPLY(buflen,error)     MAKELONG(buflen,error)
#define WSAMAKESELECTREPLY(event,error)     MAKELONG(event,error)
#define WSAGETASYNCBUFLEN(lParam)           LOWORD(lParam)
#define WSAGETASYNCERROR(lParam)            HIWORD(lParam)
#define WSAGETSELECTEVENT(lParam)           LOWORD(lParam)
#define WSAGETSELECTERROR(lParam)           HIWORD(lParam)
#define UDP_NOCHECKSUM  1
#define UDP_CHECKSUM_COVERAGE   20
#define EAI_AGAIN       WSATRY_AGAIN
#define EAI_BADFLAGS    WSAEINVAL
#define EAI_FAIL        WSANO_RECOVERY
#define EAI_FAMILY      WSAEAFNOSUPPORT
#define EAI_MEMORY      WSA_NOT_ENOUGH_MEMORY
#define EAI_NONAME      WSAHOST_NOT_FOUND
#define EAI_SERVICE     WSATYPE_NOT_FOUND
#define EAI_SOCKTYPE    WSAESOCKTNOSUPPORT
#define EAI_NODATA      EAI_NONAME
#define AI_PASSIVE      0x00000001
#define AI_CANONNAME    0x00000002
#define AI_NUMERICHOST  0x00000004
#define AI_NUMERICSERV  0x00000008
#define AI_ALL          0x00000100
#define AI_ADDRCONFIG   0x00000400
#define AI_V4MAPPED     0x00000800
#define AI_NON_AUTHORITATIVE        LUP_NON_AUTHORITATIVE
#define AI_SECURE                   LUP_SECURE
#define AI_RETURN_PREFERRED_NAMES   LUP_RETURN_PREFERRED_NAMES
#define NI_MAXHOST  1025
#define NI_MAXSERV    32
#define NI_NOFQDN       0x01
#define NI_NUMERICHOST  0x02
#define NI_NAMEREQD     0x04
#define NI_NUMERICSERV  0x08
#define NI_DGRAM        0x10
// -----------------------------------------------------------------------------------------------------------------
// ..........  
// -----------------------------------------------------------------------------------------------------------------
#define WSAID_ACCEPTEX              UuidFromString("{B5367DF1-CBAC-11CF-95CA-00805F48A192}")
#define WSAID_GETACCEPTEXSOCKADDRS  UuidFromString("{B5367DF2-CBAC-11CF-95CA-00805F48A192}")
// -----------------------------------------------------------------------------------------------------------------
#define SO_MAXDG                    0x7009
#define SO_MAXPATHDG                0x700A
#define SO_UPDATE_ACCEPT_CONTEXT    0x700B
#define SO_CONNECT_TIME             0x700C
#define SO_UPDATE_CONNECT_CONTEXT   0x7010

