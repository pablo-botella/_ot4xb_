




// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_SHELLAPI_CONSTANTS_
#define _XB_SHELLAPI_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define ABM_NEW                                    0x00000000
#define ABM_REMOVE                                 0x00000001
#define ABM_QUERYPOS                               0x00000002
#define ABM_SETPOS                                 0x00000003
#define ABM_GETSTATE                               0x00000004
#define ABM_GETTASKBARPOS                          0x00000005
#define ABM_ACTIVATE                               0x00000006
#define ABM_GETAUTOHIDEBAR                         0x00000007
#define ABM_SETAUTOHIDEBAR                         0x00000008
#define ABM_WINDOWPOSCHANGED                       0x00000009
#define ABM_SETSTATE                               0x0000000A
#define ABN_STATECHANGE                            0x00000000
#define ABN_POSCHANGED                             0x00000001
#define ABN_FULLSCREENAPP                          0x00000002
#define ABN_WINDOWARRANGE                          0x00000003
#define ABS_AUTOHIDE                               0x00000001
#define ABS_ALWAYSONTOP                            0x00000002
#define ABE_LEFT                                   0
#define ABE_TOP                                    1
#define ABE_RIGHT                                  2
#define ABE_BOTTOM                                 3
#define FO_MOVE                                    0x0001
#define FO_COPY                                    0x0002
#define FO_DELETE                                  0x0003
#define FO_RENAME                                  0x0004
#define FOF_MULTIDESTFILES                         0x0001
#define FOF_CONFIRMMOUSE                           0x0002
#define FOF_SILENT                                 0x0004
#define FOF_RENAMEONCOLLISION                      0x0008
#define FOF_NOCONFIRMATION                         0x0010
#define FOF_WANTMAPPINGHANDLE                      0x0020
#define FOF_ALLOWUNDO                              0x0040
#define FOF_FILESONLY                              0x0080
#define FOF_SIMPLEPROGRESS                         0x0100
#define FOF_NOCONFIRMMKDIR                         0x0200
#define FOF_NOERRORUI                              0x0400
#define FOF_NOCOPYSECURITYATTRIBS                  0x0800
#define FOF_NORECURSION                            0x1000
#define FOF_NO_CONNECTED_ELEMENTS                  0x2000
#define FOF_WANTNUKEWARNING                        0x4000
#define FOF_NORECURSEREPARSE                       0x8000
#define PO_DELETE                                  0x0013
#define PO_RENAME                                  0x0014
#define PO_PORTCHANGE                              0x0020
#define PO_REN_PORT                                0x0034
#define SE_ERR_FNF                                 2
#define SE_ERR_PNF                                 3
#define SE_ERR_ACCESSDENIED                        5
#define SE_ERR_OOM                                 8
#define SE_ERR_DLLNOTFOUND                         32
#define SE_ERR_SHARE                               26
#define SE_ERR_ASSOCINCOMPLETE                     27
#define SE_ERR_DDETIMEOUT                          28
#define SE_ERR_DDEFAIL                             29
#define SE_ERR_DDEBUSY                             30
#define SE_ERR_NOASSOC                             31
#define SEE_MASK_CLASSNAME                         0x00000001
#define SEE_MASK_CLASSKEY                          0x00000003
#define SEE_MASK_IDLIST                            0x00000004
#define SEE_MASK_INVOKEIDLIST                      0x0000000C
#define SEE_MASK_ICON                              0x00000010
#define SEE_MASK_HOTKEY                            0x00000020
#define SEE_MASK_NOCLOSEPROCESS                    0x00000040
#define SEE_MASK_CONNECTNETDRV                     0x00000080
#define SEE_MASK_FLAG_DDEWAIT                      0x00000100
#define SEE_MASK_DOENVSUBST                        0x00000200
#define SEE_MASK_FLAG_NO_UI                        0x00000400
#define SEE_MASK_UNICODE                           0x00004000
#define SEE_MASK_NO_CONSOLE                        0x00008000
#define SEE_MASK_ASYNCOK                           0x00100000
#define SEE_MASK_HMONITOR                          0x00200000
#define SEE_MASK_NOZONECHECKS                      0x00800000
#define SEE_MASK_NOQUERYCLASSSTORE                 0x01000000
#define SEE_MASK_WAITFORINPUTIDLE                  0x02000000
#define SEE_MASK_FLAG_LOG_USAGE                    0x04000000
#define SHERB_NOCONFIRMATION                       0x00000001
#define SHERB_NOPROGRESSUI                         0x00000002
#define SHERB_NOSOUND                              0x00000004
#define NIN_SELECT                                 (WM_USER + 0)
#define NINF_KEY                                   0x01
#define NIN_KEYSELECT                              nOr(NIN_SELECT,NINF_KEY)
#define NIN_BALLOONSHOW                            (WM_USER + 2)
#define NIN_BALLOONHIDE                            (WM_USER + 3)
#define NIN_BALLOONTIMEOUT                         (WM_USER + 4)
#define NIN_BALLOONUSERCLICK                       (WM_USER + 5)
#define NIM_ADD                                    0x00000000
#define NIM_MODIFY                                 0x00000001
#define NIM_DELETE                                 0x00000002
#define NIM_SETFOCUS                               0x00000003
#define NIM_SETVERSION                             0x00000004
#define NOTIFYICON_VERSION                         3
#define NIF_MESSAGE                                0x00000001
#define NIF_ICON                                   0x00000002
#define NIF_TIP                                    0x00000004
#define NIF_STATE                                  0x00000008
#define NIF_INFO                                   0x00000010
#define NIF_GUID                                   0x00000020
#define NIS_HIDDEN                                 0x00000001
#define NIS_SHAREDICON                             0x00000002
#define NIIF_NONE                                  0x00000000
#define NIIF_INFO                                  0x00000001
#define NIIF_WARNING                               0x00000002
#define NIIF_ERROR                                 0x00000003
#define NIIF_ICON_MASK                             0x0000000F
#define NIIF_NOSOUND                               0x00000010
#define SHGFI_ICON                                 0x00000100
#define SHGFI_DISPLAYNAME                          0x00000200
#define SHGFI_TYPENAME                             0x00000400
#define SHGFI_ATTRIBUTES                           0x00000800
#define SHGFI_ICONLOCATION                         0x00001000
#define SHGFI_EXETYPE                              0x00002000
#define SHGFI_SYSICONINDEX                         0x00004000
#define SHGFI_LINKOVERLAY                          0x00008000
#define SHGFI_SELECTED                             0x00010000
#define SHGFI_ATTR_SPECIFIED                       0x00020000
#define SHGFI_LARGEICON                            0x00000000
#define SHGFI_SMALLICON                            0x00000001
#define SHGFI_OPENICON                             0x00000002
#define SHGFI_SHELLICONSIZE                        0x00000004
#define SHGFI_PIDL                                 0x00000008
#define SHGFI_USEFILEATTRIBUTES                    0x00000010
#define SHGFI_ADDOVERLAYS                          0x00000020
#define SHGFI_OVERLAYINDEX                         0x00000040
#define SHGNLI_PIDL                                0x00000001
#define SHGNLI_PREFIXNAME                          0x00000002
#define SHGNLI_NOUNIQUE                            0x00000004
#define SHGNLI_NOLNK                               0x00000008
#define PRINTACTION_OPEN                           0
#define PRINTACTION_PROPERTIES                     1
#define PRINTACTION_NETINSTALL                     2
#define PRINTACTION_NETINSTALLLINK                 3
#define PRINTACTION_TESTPAGE                       4
#define PRINTACTION_OPENNETPRN                     5
#define PRINTACTION_DOCUMENTDEFAULTS               6
#define PRINTACTION_SERVERPROPERTIES               7
#define OFFLINE_STATUS_LOCAL                       0x0001
#define OFFLINE_STATUS_REMOTE                      0x0002
#define OFFLINE_STATUS_INCOMPLETE                  0x0004
#define SHIL_LARGE                                 0
#define SHIL_SMALL                                 1
#define SHIL_EXTRALARGE                            2
#define SHIL_SYSSMALL                              3
#define SHIL_LAST                                  SHIL_SYSSMALL
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_SHELLAPI_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
