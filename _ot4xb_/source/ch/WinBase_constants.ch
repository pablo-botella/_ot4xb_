




// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_WINBASE_CONSTANTS_
#define _XB_WINBASE_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define FILE_FLAG_WRITE_THROUGH                   dwfix(0x8000,0x0000)
#define FILE_FLAG_OVERLAPPED                      dwfix(0x4000,0x0000)
#define FILE_FLAG_NO_BUFFERING                    dwfix(0x2000,0x0000)
#define FILE_FLAG_RANDOM_ACCESS                   dwfix(0x1000,0x0000)
#define FILE_FLAG_SEQUENTIAL_SCAN                 0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE                 0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS                0x02000000
#define FILE_FLAG_POSIX_SEMANTICS                 0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT              0x00200000
#define FILE_FLAG_OPEN_NO_RECALL                  0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE             0x00080000
#define PROGRESS_CONTINUE                         0
#define PROGRESS_CANCEL                           1
#define PROGRESS_STOP                             2
#define PROGRESS_QUIET                            3
#define CALLBACK_CHUNK_FINISHED                   0x00000000
#define CALLBACK_STREAM_SWITCH                    0x00000001
#define COPY_FILE_FAIL_IF_EXISTS                  0x00000001
#define COPY_FILE_RESTARTABLE                     0x00000002
#define COPY_FILE_OPEN_SOURCE_FOR_WRITE           0x00000004
#define COPY_FILE_ALLOW_DECRYPTED_DESTINATION     0x00000008
#define REPLACEFILE_WRITE_THROUGH                 0x00000001
#define REPLACEFILE_IGNORE_MERGE_ERRORS           0x00000002
#define PIPE_ACCESS_INBOUND                       0x00000001
#define PIPE_ACCESS_OUTBOUND                      0x00000002
#define PIPE_ACCESS_DUPLEX                        0x00000003
#define PIPE_CLIENT_END                           0x00000000
#define PIPE_SERVER_END                           0x00000001
#define PIPE_WAIT                                 0x00000000
#define PIPE_NOWAIT                               0x00000001
#define PIPE_READMODE_BYTE                        0x00000000
#define PIPE_READMODE_MESSAGE                     0x00000002
#define PIPE_TYPE_BYTE                            0x00000000
#define PIPE_TYPE_MESSAGE                         0x00000004
#define PIPE_UNLIMITED_INSTANCES                  255
//#define SECURITY_ANONYMOUS                      (SecurityAnonymous << 16)
//#define SECURITY_IDENTIFICATION                 (SecurityIdentification << 16)
//#define SECURITY_IMPERSONATION                  (SecurityImpersonation << 16)
//#define SECURITY_DELEGATION                     (SecurityDelegation << 16)
#define SECURITY_CONTEXT_TRACKING                 0x00040000
#define SECURITY_EFFECTIVE_ONLY                   0x00080000
#define SECURITY_SQOS_PRESENT                     0x00100000
#define SECURITY_VALID_SQOS_FLAGS                 0x001F0000
#define SP_SERIALCOMM                             0x00000001
#define PST_UNSPECIFIED                           0x00000000
#define PST_RS232                                 0x00000001
#define PST_PARALLELPORT                          0x00000002
#define PST_RS422                                 0x00000003
#define PST_RS423                                 0x00000004
#define PST_RS449                                 0x00000005
#define PST_MODEM                                 0x00000006
#define PST_FAX                                   0x00000021
#define PST_SCANNER                               0x00000022
#define PST_NETWORK_BRIDGE                        0x00000100
#define PST_LAT                                   0x00000101
#define PST_TCPIP_TELNET                          0x00000102
#define PST_X25                                   0x00000103
#define PCF_DTRDSR                                0x0001
#define PCF_RTSCTS                                0x0002
#define PCF_RLSD                                  0x0004
#define PCF_PARITY_CHECK                          0x0008
#define PCF_XONXOFF                               0x0010
#define PCF_SETXCHAR                              0x0020
#define PCF_TOTALTIMEOUTS                         0x0040
#define PCF_INTTIMEOUTS                           0x0080
#define PCF_SPECIALCHARS                          0x0100
#define PCF_16BITMODE                             0x0200
#define SP_PARITY                                 0x0001
#define SP_BAUD                                   0x0002
#define SP_DATABITS                               0x0004
#define SP_STOPBITS                               0x0008
#define SP_HANDSHAKING                            0x0010
#define SP_PARITY_CHECK                           0x0020
#define SP_RLSD                                   0x0040
#define BAUD_075                                  0x00000001
#define BAUD_110                                  0x00000002
#define BAUD_134_5                                0x00000004
#define BAUD_150                                  0x00000008
#define BAUD_300                                  0x00000010
#define BAUD_600                                  0x00000020
#define BAUD_1200                                 0x00000040
#define BAUD_1800                                 0x00000080
#define BAUD_2400                                 0x00000100
#define BAUD_4800                                 0x00000200
#define BAUD_7200                                 0x00000400
#define BAUD_9600                                 0x00000800
#define BAUD_14400                                0x00001000
#define BAUD_19200                                0x00002000
#define BAUD_38400                                0x00004000
#define BAUD_56K                                  0x00008000
#define BAUD_128K                                 0x00010000
#define BAUD_115200                               0x00020000
#define BAUD_57600                                0x00040000
#define BAUD_USER                                 dwfix(0x1000,0x0000)
#define DATABITS_5                                0x0001
#define DATABITS_6                                0x0002
#define DATABITS_7                                0x0004
#define DATABITS_8                                0x0008
#define DATABITS_16                               0x0010
#define DATABITS_16X                              0x0020
#define STOPBITS_10                               0x0001
#define STOPBITS_15                               0x0002
#define STOPBITS_20                               0x0004
#define PARITY_NONE                               0x0100
#define PARITY_ODD                                0x0200
#define PARITY_EVEN                               0x0400
#define PARITY_MARK                               0x0800
#define PARITY_SPACE                              0x1000
#define COMMPROP_INITIALIZED                      dwfix(0xE73C,0xF52E)
#define DTR_CONTROL_DISABLE                       0x00
#define DTR_CONTROL_ENABLE                        0x01
#define DTR_CONTROL_HANDSHAKE                     0x02
#define RTS_CONTROL_DISABLE                       0x00
#define RTS_CONTROL_ENABLE                        0x01
#define RTS_CONTROL_HANDSHAKE                     0x02
#define RTS_CONTROL_TOGGLE                        0x03
#define GMEM_FIXED                                0x0000
#define GMEM_MOVEABLE                             0x0002
#define GMEM_NOCOMPACT                            0x0010
#define GMEM_NODISCARD                            0x0020
#define GMEM_ZEROINIT                             0x0040
#define GMEM_MODIFY                               0x0080
#define GMEM_DISCARDABLE                          0x0100
#define GMEM_NOT_BANKED                           0x1000
#define GMEM_SHARE                                0x2000
#define GMEM_DDESHARE                             0x2000
#define GMEM_NOTIFY                               0x4000
#define GMEM_LOWER                                GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS                          0x7F72
#define GMEM_INVALID_HANDLE                       0x8000
#define GHND                                      nOr(GMEM_MOVEABLE,GMEM_ZEROINIT)
#define GPTR                                      nOr(GMEM_FIXED,GMEM_ZEROINIT)
#define GMEM_DISCARDED                            0x4000
#define GMEM_LOCKCOUNT                            0x00FF
#define LMEM_FIXED                                0x0000
#define LMEM_MOVEABLE                             0x0002
#define LMEM_NOCOMPACT                            0x0010
#define LMEM_NODISCARD                            0x0020
#define LMEM_ZEROINIT                             0x0040
#define LMEM_MODIFY                               0x0080
#define LMEM_DISCARDABLE                          0x0F00
#define LMEM_VALID_FLAGS                          0x0F72
#define LMEM_INVALID_HANDLE                       0x8000
#define LHND                                      nOr(LMEM_MOVEABLE,LMEM_ZEROINIT)
#define LPTR                                      nOr(LMEM_FIXED,LMEM_ZEROINIT)
#define NONZEROLHND                               LMEM_MOVEABLE
#define NONZEROLPTR                               LMEM_FIXED
#define LMEM_DISCARDED                            0x4000
#define LMEM_LOCKCOUNT                            0x00FF
#define DEBUG_PROCESS                             0x00000001
#define DEBUG_ONLY_THIS_PROCESS                   0x00000002
#define CREATE_SUSPENDED                          0x00000004
#define DETACHED_PROCESS                          0x00000008
#define CREATE_NEW_CONSOLE                        0x00000010
#define NORMAL_PRIORITY_CLASS                     0x00000020
#define IDLE_PRIORITY_CLASS                       0x00000040
#define HIGH_PRIORITY_CLASS                       0x00000080
#define REALTIME_PRIORITY_CLASS                   0x00000100
#define CREATE_NEW_PROCESS_GROUP                  0x00000200
#define CREATE_UNICODE_ENVIRONMENT                0x00000400
#define CREATE_SEPARATE_WOW_VDM                   0x00000800
#define CREATE_SHARED_WOW_VDM                     0x00001000
#define CREATE_FORCEDOS                           0x00002000
#define BELOW_NORMAL_PRIORITY_CLASS               0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS               0x00008000
#define STACK_SIZE_PARAM_IS_A_RESERVATION         0x00010000
#define CREATE_BREAKAWAY_FROM_JOB                 0x01000000
#define CREATE_PRESERVE_CODE_AUTHZ_LEVEL          0x02000000
#define CREATE_DEFAULT_ERROR_MODE                 0x04000000
#define CREATE_NO_WINDOW                          0x08000000
#define PROFILE_USER                              dwfix(0x1000,0x0000)
#define PROFILE_KERNEL                            dwfix(0x2000,0x0000)
#define PROFILE_SERVER                            dwfix(0x4000,0x0000)
#define CREATE_IGNORE_SYSTEM_DEFAULT              dwfix(0x8000,0x0000)
#define THREAD_PRIORITY_LOWEST                    THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL              (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL                    0
#define THREAD_PRIORITY_HIGHEST                   THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL              (THREAD_PRIORITY_HIGHEST-1)
#define THREAD_PRIORITY_ERROR_RETURN              (MAXLONG)
#define THREAD_PRIORITY_TIME_CRITICAL             THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE                      THREAD_BASE_PRIORITY_IDLE
#define EXCEPTION_DEBUG_EVENT                     1
#define CREATE_THREAD_DEBUG_EVENT                 2
#define CREATE_PROCESS_DEBUG_EVENT                3
#define EXIT_THREAD_DEBUG_EVENT                   4
#define EXIT_PROCESS_DEBUG_EVENT                  5
#define LOAD_DLL_DEBUG_EVENT                      6
#define UNLOAD_DLL_DEBUG_EVENT                    7
#define OUTPUT_DEBUG_STRING_EVENT                 8
#define RIP_EVENT                                 9
#define FILE_TYPE_UNKNOWN                         0x0000
#define FILE_TYPE_DISK                            0x0001
#define FILE_TYPE_CHAR                            0x0002
#define FILE_TYPE_PIPE                            0x0003
#define FILE_TYPE_REMOTE                          0x8000
#define STD_INPUT_HANDLE                          dwminus(10)
#define STD_OUTPUT_HANDLE                         dwminus(11)
#define STD_ERROR_HANDLE                          dwminus(12)
#define NOPARITY                                  0
#define ODDPARITY                                 1
#define EVENPARITY                                2
#define MARKPARITY                                3
#define SPACEPARITY                               4
#define ONESTOPBIT                                0
#define ONE5STOPBITS                              1
#define TWOSTOPBITS                               2
#define IGNORE                                    0 // Ignore signal
#define INFINITE                                  dwfix(0xFFFF,0xFFFF) // Infinite timeout
#define CBR_110                                   110
#define CBR_300                                   300
#define CBR_600                                   600
#define CBR_1200                                  1200
#define CBR_2400                                  2400
#define CBR_4800                                  4800
#define CBR_9600                                  9600
#define CBR_14400                                 14400
#define CBR_19200                                 19200
#define CBR_38400                                 38400
#define CBR_56000                                 56000
#define CBR_57600                                 57600
#define CBR_115200                                115200
#define CBR_128000                                128000
#define CBR_256000                                256000
#define CE_RXOVER                                 0x0001 // Receive Queue overflow
#define CE_OVERRUN                                0x0002 // Receive Overrun Error
#define CE_RXPARITY                               0x0004 // Receive Parity Error
#define CE_FRAME                                  0x0008 // Receive Framing error
#define CE_BREAK                                  0x0010 // Break Detected
#define CE_TXFULL                                 0x0100 // TX Queue is full
#define CE_PTO                                    0x0200 // LPTx Timeout
#define CE_IOE                                    0x0400 // LPTx I/O Error
#define CE_DNS                                    0x0800 // LPTx Device not selected
#define CE_OOP                                    0x1000 // LPTx Out-Of-Paper
#define CE_MODE                                   0x8000 // Requested mode unsupported
#define IE_BADID                                  dwminus(1) // Invalid or unsupported id
#define IE_OPEN                                   dwminus(2) // Device Already Open
#define IE_NOPEN                                  dwminus(3) // Device Not Open
#define IE_MEMORY                                 dwminus(4) // Unable to allocate queues
#define IE_DEFAULT                                dwminus(5) // Error in default parameters
#define IE_HARDWARE                               dwminus(10) // Hardware Not Present
#define IE_BYTESIZE                               dwminus(11) // Illegal Byte Size
#define IE_BAUDRATE                               dwminus(12) // Unsupported BaudRate
#define EV_RXCHAR                                 0x0001 // Any Character received
#define EV_RXFLAG                                 0x0002 // Received certain character
#define EV_TXEMPTY                                0x0004 // Transmitt Queue Empty
#define EV_CTS                                    0x0008 // CTS changed state
#define EV_DSR                                    0x0010 // DSR changed state
#define EV_RLSD                                   0x0020 // RLSD changed state
#define EV_BREAK                                  0x0040 // BREAK received
#define EV_ERR                                    0x0080 // Line status error occurred
#define EV_RING                                   0x0100 // Ring signal detected
#define EV_PERR                                   0x0200 // Printer error occured
#define EV_RX80FULL                               0x0400 // Receive buffer is 80 percent full
#define EV_EVENT1                                 0x0800 // Provider specific event 1
#define EV_EVENT2                                 0x1000 // Provider specific event 2
#define SETXOFF                                   1 // Simulate XOFF received
#define SETXON                                    2 // Simulate XON received
#define SETRTS                                    3 // Set RTS high
#define CLRRTS                                    4 // Set RTS low
#define SETDTR                                    5 // Set DTR high
#define CLRDTR                                    6 // Set DTR low
#define RESETDEV                                  7 // Reset device if possible
#define SETBREAK                                  8 // Set the device break line.
#define CLRBREAK                                  9 // Clear the device break line.
#define PURGE_TXABORT                             0x0001 // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT                             0x0002 // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR                             0x0004 // Kill the transmit queue if there.
#define PURGE_RXCLEAR                             0x0008 // Kill the typeahead buffer if there.
#define LPTx                                      0x80 // Set if ID is for LPT device
#define MS_CTS_ON                                 (0x0010)
#define MS_DSR_ON                                 (0x0020)
#define MS_RING_ON                                (0x0040)
#define MS_RLSD_ON                                (0x0080)
#define S_QUEUEEMPTY                              0
#define S_THRESHOLD                               1
#define S_ALLTHRESHOLD                            2
#define S_NORMAL                                  0
#define S_LEGATO                                  1
#define S_STACCATO                                2
#define S_PERIOD512                               0 // Freq = N/512 high pitch, less coarse hiss
#define S_PERIOD1024                              1 // Freq = N/1024
#define S_PERIOD2048                              2 // Freq = N/2048 low pitch, more coarse hiss
#define S_PERIODVOICE                             3 // Source is frequency from voice channel (3)
#define S_WHITE512                                4 // Freq = N/512 high pitch, less coarse hiss
#define S_WHITE1024                               5 // Freq = N/1024
#define S_WHITE2048                               6 // Freq = N/2048 low pitch, more coarse hiss
#define S_WHITEVOICE                              7 // Source is frequency from voice channel (3)
#define S_SERDVNA                                 dwminus(1) // Device not available
#define S_SEROFM                                  dwminus(2) // Out of memory
#define S_SERMACT                                 dwminus(3) // Music active
#define S_SERQFUL                                 dwminus(4) // Queue full
#define S_SERBDNT                                 dwminus(5) // Invalid note
#define S_SERDLN                                  dwminus(6) // Invalid note length
#define S_SERDCC                                  dwminus(7) // Invalid note count
#define S_SERDTP                                  dwminus(8) // Invalid tempo
#define S_SERDVL                                  dwminus(9) // Invalid volume
#define S_SERDMD                                  dwminus(10) // Invalid mode
#define S_SERDSH                                  dwminus(11) // Invalid shape
#define S_SERDPT                                  dwminus(12) // Invalid pitch
#define S_SERDFQ                                  dwminus(13) // Invalid frequency
#define S_SERDDR                                  dwminus(14) // Invalid duration
#define S_SERDSR                                  dwminus(15) // Invalid source
#define S_SERDST                                  dwminus(16) // Invalid state
#define NMPWAIT_WAIT_FOREVER                      dwfix(0xFFFF,0xFFFF)
#define NMPWAIT_NOWAIT                            0x00000001
#define NMPWAIT_USE_DEFAULT_WAIT                  0x00000000
#define FS_CASE_IS_PRESERVED                      FILE_CASE_PRESERVED_NAMES
#define FS_CASE_SENSITIVE                         FILE_CASE_SENSITIVE_SEARCH
#define FS_UNICODE_STORED_ON_DISK                 FILE_UNICODE_ON_DISK
#define FS_PERSISTENT_ACLS                        FILE_PERSISTENT_ACLS
#define FS_VOL_IS_COMPRESSED                      FILE_VOLUME_IS_COMPRESSED
#define FS_FILE_COMPRESSION                       FILE_FILE_COMPRESSION
#define FS_FILE_ENCRYPTION                        FILE_SUPPORTS_ENCRYPTION
#define FILE_MAP_COPY                             SECTION_QUERY
#define FILE_MAP_WRITE                            SECTION_MAP_WRITE
#define FILE_MAP_READ                             SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS                       SECTION_ALL_ACCESS
#define OF_READ                                   0x00000000
#define OF_WRITE                                  0x00000001
#define OF_READWRITE                              0x00000002
#define OF_SHARE_COMPAT                           0x00000000
#define OF_SHARE_EXCLUSIVE                        0x00000010
#define OF_SHARE_DENY_WRITE                       0x00000020
#define OF_SHARE_DENY_READ                        0x00000030
#define OF_SHARE_DENY_NONE                        0x00000040
#define OF_PARSE                                  0x00000100
#define OF_DELETE                                 0x00000200
#define OF_VERIFY                                 0x00000400
#define OF_CANCEL                                 0x00000800
#define OF_CREATE                                 0x00001000
#define OF_PROMPT                                 0x00002000
#define OF_EXIST                                  0x00004000
#define OF_REOPEN                                 0x00008000
#define OFS_MAXPATHNAME                           128
#define MAXINTATOM                                0xC000
#define INVALID_ATOM                              0
#define PROCESS_HEAP_REGION                       0x0001
#define PROCESS_HEAP_UNCOMMITTED_RANGE            0x0002
#define PROCESS_HEAP_ENTRY_BUSY                   0x0004
#define PROCESS_HEAP_ENTRY_MOVEABLE               0x0010
#define PROCESS_HEAP_ENTRY_DDESHARE               0x0020
#define SCS_32BIT_BINARY                          0
#define SCS_DOS_BINARY                            1
#define SCS_WOW_BINARY                            2
#define SCS_PIF_BINARY                            3
#define SCS_POSIX_BINARY                          4
#define SCS_OS216_BINARY                          5
#define SCS_64BIT_BINARY                          6
#define FIBER_FLAG_FLOAT_SWITCH                   0x1 // context switch floating point
#define SEM_FAILCRITICALERRORS                    0x0001
#define SEM_NOGPFAULTERRORBOX                     0x0002
#define SEM_NOALIGNMENTFAULTEXCEPT                0x0004
#define SEM_NOOPENFILEERRORBOX                    0x8000
#define LOCKFILE_FAIL_IMMEDIATELY                 0x00000001
#define LOCKFILE_EXCLUSIVE_LOCK                   0x00000002
#define HANDLE_FLAG_INHERIT                       0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE            0x00000002
#define HINSTANCE_ERROR                           32
#define GET_TAPE_MEDIA_INFORMATION                0
#define GET_TAPE_DRIVE_INFORMATION                1
#define SET_TAPE_MEDIA_INFORMATION                0
#define SET_TAPE_DRIVE_INFORMATION                1
#define FORMAT_MESSAGE_ALLOCATE_BUFFER            0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS             0x00000200
#define FORMAT_MESSAGE_FROM_STRING                0x00000400
#define FORMAT_MESSAGE_FROM_HMODULE               0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM                0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY             0x00002000
#define FORMAT_MESSAGE_MAX_WIDTH_MASK             0x000000FF
#define FILE_ENCRYPTABLE                          0
#define FILE_IS_ENCRYPTED                         1
#define FILE_SYSTEM_ATTR                          2
#define FILE_ROOT_DIR                             3
#define FILE_SYSTEM_DIR                           4
#define FILE_UNKNOWN                              5
#define FILE_SYSTEM_NOT_SUPPORT                   6
#define FILE_USER_DISALLOWED                      7
#define FILE_READ_ONLY                            8
#define FILE_DIR_DISALLOWED                       9
#define EFS_USE_RECOVERY_KEYS                     (0x1)
#define CREATE_FOR_IMPORT                         (1)
#define CREATE_FOR_DIR                            (2)
#define OVERWRITE_HIDDEN                          (4)
#define FLS_OUT_OF_INDEXES                        (dwfix(0xFFFF,0xFFFF))
#define TLS_OUT_OF_INDEXES                        (dwfix(0xFFFF,0xFFFF))
#define BACKUP_INVALID                            0x00000000
#define BACKUP_DATA                               0x00000001
#define BACKUP_EA_DATA                            0x00000002
#define BACKUP_SECURITY_DATA                      0x00000003
#define BACKUP_ALTERNATE_DATA                     0x00000004
#define BACKUP_LINK                               0x00000005
#define BACKUP_PROPERTY_DATA                      0x00000006
#define BACKUP_OBJECT_ID                          0x00000007
#define BACKUP_REPARSE_DATA                       0x00000008
#define BACKUP_SPARSE_BLOCK                       0x00000009
#define STREAM_NORMAL_ATTRIBUTE                   0x00000000
#define STREAM_MODIFIED_WHEN_READ                 0x00000001
#define STREAM_CONTAINS_SECURITY                  0x00000002
#define STREAM_CONTAINS_PROPERTIES                0x00000004
#define STREAM_SPARSE_ATTRIBUTE                   0x00000008
#define STARTF_USESHOWWINDOW                      0x00000001
#define STARTF_USESIZE                            0x00000002
#define STARTF_USEPOSITION                        0x00000004
#define STARTF_USECOUNTCHARS                      0x00000008
#define STARTF_USEFILLATTRIBUTE                   0x00000010
#define STARTF_RUNFULLSCREEN                      0x00000020 // ignored for non-x86 platforms
#define STARTF_FORCEONFEEDBACK                    0x00000040
#define STARTF_FORCEOFFFEEDBACK                   0x00000080
#define STARTF_USESTDHANDLES                      0x00000100
#define STARTF_USEHOTKEY                          0x00000200
#define DONT_RESOLVE_DLL_REFERENCES               0x00000001
#define LOAD_LIBRARY_AS_DATAFILE                  0x00000002
#define LOAD_WITH_ALTERED_SEARCH_PATH             0x00000008
#define LOAD_IGNORE_CODE_AUTHZ_LEVEL              0x00000010
#define GET_MODULE_HANDLE_EX_FLAG_PIN             (0x00000001)
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT (0x00000002)
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS    (0x00000004)
#define DDD_RAW_TARGET_PATH                       0x00000001
#define DDD_REMOVE_DEFINITION                     0x00000002
#define DDD_EXACT_MATCH_ON_REMOVE                 0x00000004
#define DDD_NO_BROADCAST_SYSTEM                   0x00000008
#define DDD_LUID_BROADCAST_DRIVE                  0x00000010
#define FIND_FIRST_EX_CASE_SENSITIVE              0x00000001
#define MOVEFILE_REPLACE_EXISTING                 0x00000001
#define MOVEFILE_COPY_ALLOWED                     0x00000002
#define MOVEFILE_DELAY_UNTIL_REBOOT               0x00000004
#define MOVEFILE_WRITE_THROUGH                    0x00000008
#define MOVEFILE_CREATE_HARDLINK                  0x00000010
#define MOVEFILE_FAIL_IF_NOT_TRACKABLE            0x00000020
#define EVENTLOG_FULL_INFO                        0
#define MAX_COMPUTERNAME_LENGTH                   31
#define LOGON32_LOGON_INTERACTIVE                 2
#define LOGON32_LOGON_NETWORK                     3
#define LOGON32_LOGON_BATCH                       4
#define LOGON32_LOGON_SERVICE                     5
#define LOGON32_LOGON_UNLOCK                      7
#define LOGON32_LOGON_NETWORK_CLEARTEXT           8
#define LOGON32_LOGON_NEW_CREDENTIALS             9
#define LOGON32_PROVIDER_DEFAULT                  0
#define LOGON32_PROVIDER_WINNT35                  1
#define LOGON32_PROVIDER_WINNT40                  2
#define LOGON32_PROVIDER_WINNT50                  3
#define LOGON_WITH_PROFILE                        0x00000001
#define LOGON_NETCREDENTIALS_ONLY                 0x00000002
#define LOGON_ZERO_PASSWORD_BUFFER                dwfix(0x8000,0x0000)
#define HW_PROFILE_GUIDLEN                        39 // 36-characters plus NULL terminator
#define MAX_PROFILE_LEN                           80
#define DOCKINFO_UNDOCKED                         (0x1)
#define DOCKINFO_DOCKED                           (0x2)
#define DOCKINFO_USER_SUPPLIED                    (0x4)
#define DOCKINFO_USER_UNDOCKED                    nOr(DOCKINFO_USER_SUPPLIED,DOCKINFO_UNDOCKED)
#define DOCKINFO_USER_DOCKED                      nOr(DOCKINFO_USER_SUPPLIED,DOCKINFO_DOCKED)
#define TC_NORMAL                                 0
#define TC_HARDERR                                1
#define TC_GP_TRAP                                2
#define TC_SIGNAL                                 3
#define AC_LINE_OFFLINE                           0x00
#define AC_LINE_ONLINE                            0x01
#define AC_LINE_BACKUP_POWER                      0x02
#define AC_LINE_UNKNOWN                           0xFF
#define BATTERY_FLAG_HIGH                         0x01
#define BATTERY_FLAG_LOW                          0x02
#define BATTERY_FLAG_CRITICAL                     0x04
#define BATTERY_FLAG_CHARGING                     0x08
#define BATTERY_FLAG_NO_BATTERY                   0x80
#define BATTERY_FLAG_UNKNOWN                      0xFF
#define BATTERY_PERCENTAGE_UNKNOWN                0xFF
#define BATTERY_LIFE_UNKNOWN                      dwfix(0xFFFF,0xFFFF)
#define ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID  (0x00000001)
#define ACTCTX_FLAG_LANGID_VALID                  (0x00000002)
#define ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID      (0x00000004)
#define ACTCTX_FLAG_RESOURCE_NAME_VALID           (0x00000008)
#define ACTCTX_FLAG_SET_PROCESS_DEFAULT           (0x00000010)
#define ACTCTX_FLAG_APPLICATION_NAME_VALID        (0x00000020)
#define ACTCTX_FLAG_SOURCE_IS_ASSEMBLYREF         (0x00000040)
#define ACTCTX_FLAG_HMODULE_VALID                 (0x00000080)
#define DEACTIVATE_ACTCTX_FLAG_FORCE_EARLY_DEACTIVATION (0x00000001)
#define FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX    (0x00000001)
#define FIND_ACTCTX_SECTION_KEY_RETURN_FLAGS      (0x00000002)
#define FIND_ACTCTX_SECTION_KEY_RETURN_ASSEMBLY_METADATA (0x00000004)
#define QUERY_ACTCTX_FLAG_USE_ACTIVE_ACTCTX       (0x00000004)
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_HMODULE       (0x00000008)
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_ADDRESS       (0x00000010)
#define QUERY_ACTCTX_FLAG_NO_ADDREF               dwfix(0x8000,0x0000)
//----------------------------------------------------------------------------------------------------------------------
// FROM WinNT.h ---
#define STATUS_WAIT_0                    dwfix(0x0000,0x0000)    
#define STATUS_ABANDONED_WAIT_0          dwfix(0x0000,0x0080)    
#define STATUS_USER_APC                  dwfix(0x0000,0x00C0)    
#define STATUS_TIMEOUT                   dwfix(0x0000,0x0102)    
#define STATUS_PENDING                   dwfix(0x0000,0x0103)    
#define DBG_EXCEPTION_HANDLED            dwfix(0x0001,0x0001)    
#define DBG_CONTINUE                     dwfix(0x0001,0x0002)    
#define STATUS_SEGMENT_NOTIFICATION      dwfix(0x4000,0x0005)    
#define DBG_TERMINATE_THREAD             dwfix(0x4001,0x0003)    
#define DBG_TERMINATE_PROCESS            dwfix(0x4001,0x0004)    
#define DBG_CONTROL_C                    dwfix(0x4001,0x0005)    
#define DBG_CONTROL_BREAK                dwfix(0x4001,0x0008)    
#define DBG_COMMAND_EXCEPTION            dwfix(0x4001,0x0009)    
#define STATUS_GUARD_PAGE_VIOLATION      dwfix(0x8000,0x0001)    
#define STATUS_DATATYPE_MISALIGNMENT     dwfix(0x8000,0x0002)    
#define STATUS_BREAKPOINT                dwfix(0x8000,0x0003)    
#define STATUS_SINGLE_STEP               dwfix(0x8000,0x0004)    
#define DBG_EXCEPTION_NOT_HANDLED        dwfix(0x8001,0x0001)    
#define STATUS_ACCESS_VIOLATION          dwfix(0xC000,0x0005)    
#define STATUS_IN_PAGE_ERROR             dwfix(0xC000,0x0006)    
#define STATUS_INVALID_HANDLE            dwfix(0xC000,0x0008)    
#define STATUS_NO_MEMORY                 dwfix(0xC000,0x0017)    
#define STATUS_ILLEGAL_INSTRUCTION       dwfix(0xC000,0x001D)    
#define STATUS_NONCONTINUABLE_EXCEPTION  dwfix(0xC000,0x0025)    
#define STATUS_INVALID_DISPOSITION       dwfix(0xC000,0x0026)    
#define STATUS_ARRAY_BOUNDS_EXCEEDED     dwfix(0xC000,0x008C)    
#define STATUS_FLOAT_DENORMAL_OPERAND    dwfix(0xC000,0x008D)    
#define STATUS_FLOAT_DIVIDE_BY_ZERO      dwfix(0xC000,0x008E)    
#define STATUS_FLOAT_INEXACT_RESULT      dwfix(0xC000,0x008F)    
#define STATUS_FLOAT_INVALID_OPERATION   dwfix(0xC000,0x0090)    
#define STATUS_FLOAT_OVERFLOW            dwfix(0xC000,0x0091)    
#define STATUS_FLOAT_STACK_CHECK         dwfix(0xC000,0x0092)    
#define STATUS_FLOAT_UNDERFLOW           dwfix(0xC000,0x0093)    
#define STATUS_INTEGER_DIVIDE_BY_ZERO    dwfix(0xC000,0x0094)    
#define STATUS_INTEGER_OVERFLOW          dwfix(0xC000,0x0095)    
#define STATUS_PRIVILEGED_INSTRUCTION    dwfix(0xC000,0x0096)    
#define STATUS_STACK_OVERFLOW            dwfix(0xC000,0x00FD)    
#define STATUS_CONTROL_C_EXIT            dwfix(0xC000,0x013A)    
#define STATUS_FLOAT_MULTIPLE_FAULTS     dwfix(0xC000,0x02B4)    
#define STATUS_FLOAT_MULTIPLE_TRAPS      dwfix(0xC000,0x02B5)    
#define STATUS_REG_NAT_CONSUMPTION       dwfix(0xC000,0x02C9)    
#define STATUS_SXS_EARLY_DEACTIVATION    dwfix(0xC015,0x000F)    
#define STATUS_SXS_INVALID_DEACTIVATION  dwfix(0xC015,0x0010)    
// ----------------                                  
// wait status

#define WAIT_FAILED                         dwfix(0xFFFF,0xFFFF)
#define WAIT_OBJECT_0                       STATUS_WAIT_0
#define WAIT_ABANDONED                      STATUS_ABANDONED_WAIT_0
#define WAIT_ABANDONED_0                    STATUS_ABANDONED_WAIT_0
#define WAIT_IO_COMPLETION                  STATUS_USER_APC
#define STILL_ACTIVE                        STATUS_PENDING
#define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
#define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
#define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
#define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
#define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
#define EXCEPTION_POSSIBLE_DEADLOCK         STATUS_POSSIBLE_DEADLOCK
#define CONTROL_C_EXIT                      STATUS_CONTROL_C_EXIT
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_WINBASE_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
