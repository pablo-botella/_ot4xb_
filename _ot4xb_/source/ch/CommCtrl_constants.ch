// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_COMMCTRL_CONSTANTS_
#define _XB_COMMCTRL_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define ACM_OPEN                                                (WM_USER+100)
#define ACM_PLAY                                                (WM_USER+101)
#define ACM_STOP                                                (WM_USER+102)
#define ACN_START                                               1
#define ACN_STOP                                                2
#define ACS_AUTOPLAY                                            0x04
#define ACS_CENTER                                              0x01
#define ACS_TIMER                                               0x08
#define ACS_TRANSPARENT                                         0x02
#define ANIMATE_CLASS                                           "SysAnimate32"
#define BCM_FIRST                                               0x1600
#define BCM_GETIDEALSIZE                                        (BCM_FIRST + 0x01)
#define BCM_GETIMAGELIST                                        (BCM_FIRST + 0x03)
#define BCM_GETTEXTMARGIN                                       (BCM_FIRST + 0x05)
#define BCM_SETIMAGELIST                                        (BCM_FIRST + 0x02)
#define BCM_SETTEXTMARGIN                                       (BCM_FIRST + 0x04)
#define BCN_FIRST                                               dwminus(1250)
#define BCN_HOTITEMCHANGE                                       (BCN_FIRST + 0x01)
#define BCN_LAST                                                dwminus(1350)
#define BST_HOT                                                 0x200
#define BTNS_AUTOSIZE                                           TBSTYLE_AUTOSIZE
#define BTNS_BUTTON                                             TBSTYLE_BUTTON
#define BTNS_CHECK                                              TBSTYLE_CHECK
#define BTNS_CHECKGROUP                                         TBSTYLE_CHECKGROUP
#define BTNS_DROPDOWN                                           TBSTYLE_DROPDOWN
#define BTNS_GROUP                                              TBSTYLE_GROUP
#define BTNS_NOPREFIX                                           TBSTYLE_NOPREFIX
#define BTNS_SEP                                                TBSTYLE_SEP
#define BTNS_SHOWTEXT                                           0x040
#define BTNS_WHOLEDROPDOWN                                      0x080
#define BUTTON_IMAGELIST_ALIGN_BOTTOM                           3
#define BUTTON_IMAGELIST_ALIGN_CENTER                           4
#define BUTTON_IMAGELIST_ALIGN_LEFT                             0
#define BUTTON_IMAGELIST_ALIGN_RIGHT                            1
#define BUTTON_IMAGELIST_ALIGN_TOP                              2
#define CB_GETMINVISIBLE                                        (CBM_FIRST + 2)
#define CB_SETMINVISIBLE                                        (CBM_FIRST + 1)
#define CBEIF_DI_SETITEM                                        0x10000000
#define CBEIF_IMAGE                                             0x02
#define CBEIF_INDENT                                            0x10
#define CBEIF_LPARAM                                            0x20
#define CBEIF_OVERLAY                                           0x08
#define CBEIF_SELECTEDIMAGE                                     0x04
#define CBEIF_TEXT                                              0x01
#define CBEM_DELETEITEM                                         CB_DELETESTRING
#define CBEM_GETCOMBOCONTROL                                    (WM_USER + 6)
#define CBEM_GETEDITCONTROL                                     (WM_USER + 7)
#define CBEM_GETEXSTYLE                                         (WM_USER + 9)
#define CBEM_GETEXTENDEDSTYLE                                   (WM_USER + 9)
#define CBEM_GETIMAGELIST                                       (WM_USER + 3)
#define CBEM_GETITEM                                            (WM_USER + 4)
#define CBEM_GETUNICODEFORMAT                                   CCM_GETUNICODEFORMAT
#define CBEM_HASEDITCHANGED                                     (WM_USER + 10)
#define CBEM_INSERTITEM                                         (WM_USER + 1)
#define CBEM_SETEXSTYLE                                         (WM_USER + 8)
#define CBEM_SETEXTENDEDSTYLE                                   (WM_USER + 14)
#define CBEM_SETIMAGELIST                                       (WM_USER + 2)
#define CBEM_SETITEM                                            (WM_USER + 5)
#define CBEM_SETUNICODEFORMAT                                   CCM_SETUNICODEFORMAT
#define CBEM_SETWINDOWTHEME                                     CCM_SETWINDOWTHEME
#define CBEMAXSTRLEN                                            260
#define CBEN_BEGINEDIT                                          (CBEN_FIRST - 4)
#define CBEN_DELETEITEM                                         (CBEN_FIRST - 2)
#define CBEN_DRAGBEGIN                                          (CBEN_FIRST - 8)
#define CBEN_ENDEDIT                                            (CBEN_FIRST - 5)
#define CBEN_FIRST                                              dwminus(800)
#define CBEN_GETDISPINFO                                        (CBEN_FIRST - 0)
#define CBEN_INSERTITEM                                         (CBEN_FIRST - 1)
#define CBEN_LAST                                               dwminus(830)
#define CBENF_DROPDOWN                                          4
#define CBENF_ESCAPE                                            3
#define CBENF_KILLFOCUS                                         1
#define CBENF_RETURN                                            2
#define CBES_EX_CASESENSITIVE                                   0x10
#define CBES_EX_NOEDITIMAGE                                     0x01
#define CBES_EX_NOEDITIMAGEINDENT                               0x02
#define CBES_EX_NOSIZELIMIT                                     0x08
#define CBES_EX_PATHWORDBREAKPROC                               0x04
#define CBM_FIRST                                               0x1700
#define CCM_DPISCALE                                            (CCM_FIRST + 0xc)
#define CCM_FIRST                                               0x2000
#define CCM_GETCOLORSCHEME                                      (CCM_FIRST + 3)
#define CCM_GETDROPTARGET                                       (CCM_FIRST + 4)
#define CCM_GETUNICODEFORMAT                                    (CCM_FIRST + 6)
#define CCM_GETVERSION                                          (CCM_FIRST + 0x8)
#define CCM_SETBKCOLOR                                          (CCM_FIRST + 1)
#define CCM_SETCOLORSCHEME                                      (CCM_FIRST + 2)
#define CCM_SETNOTIFYWINDOW                                     (CCM_FIRST + 0x9)
#define CCM_SETUNICODEFORMAT                                    (CCM_FIRST + 5)
#define CCM_SETVERSION                                          (CCM_FIRST + 0x7)
#define CCM_SETWINDOWTHEME                                      (CCM_FIRST + 0xb)
#define CCS_ADJUSTABLE                                          0x20
#define CCS_BOTTOM                                              0x03
#define CCS_LEFT                                                nOr(CCS_VERT , CCS_TOP)
#define CCS_NODIVIDER                                           0x040
#define CCS_NOMOVEX                                             nOr(CCS_VERT , CCS_NOMOVEY)
#define CCS_NOMOVEY                                             0x02
#define CCS_NOPARENTALIGN                                       0x08
#define CCS_NORESIZE                                            0x04
#define CCS_RIGHT                                               nOr(CCS_VERT , CCS_BOTTOM)
#define CCS_TOP                                                 0x01
#define CCS_VERT                                                0x080
#define CDDS_ITEM                                               0x010000
#define CDDS_ITEMPOSTERASE                                      nOr(CDDS_ITEM , CDDS_POSTERASE)
#define CDDS_ITEMPOSTPAINT                                      nOr(CDDS_ITEM , CDDS_POSTPAINT)
#define CDDS_ITEMPREERASE                                       nOr(CDDS_ITEM , CDDS_PREERASE)
#define CDDS_ITEMPREPAINT                                       nOr(CDDS_ITEM , CDDS_PREPAINT)
#define CDDS_POSTERASE                                          0x04
#define CDDS_POSTPAINT                                          0x02
#define CDDS_PREERASE                                           0x03
#define CDDS_PREPAINT                                           0x01
#define CDDS_SUBITEM                                            0x020000
#define CDIS_CHECKED                                            0x08
#define CDIS_DEFAULT                                            0x20
#define CDIS_DISABLED                                           0x04
#define CDIS_FOCUS                                              0x10
#define CDIS_GRAYED                                             0x02
#define CDIS_HOT                                                0x040
#define CDIS_INDETERMINATE                                      0x0100
#define CDIS_MARKED                                             0x080
#define CDIS_SELECTED                                           0x01
#define CDIS_SHOWKEYBOARDCUES                                   0x200
#define CDN_FIRST                                               dwminus(601)
#define CDN_LAST                                                dwminus(699)
#define CDRF_DODEFAULT                                          0
#define CDRF_NEWFONT                                            0x02
#define CDRF_NOTIFYITEMDRAW                                     0x20
#define CDRF_NOTIFYPOSTERASE                                    0x040
#define CDRF_NOTIFYPOSTPAINT                                    0x10
#define CDRF_NOTIFYSUBITEMDRAW                                  0x20
#define CDRF_SKIPDEFAULT                                        0x04
#define CLR_DEFAULT                                             dwfix( 0xFF00,0)
#define CLR_HILIGHT                                             CLR_DEFAULT
#define CLR_NONE                                                dwminus(1)
#define CMB_MASKED                                              0x02
#define DA_LAST                                                 dwfix(0x7FFF,0xFFFF)
#define DATETIMEPICK_CLASS                                      "SysDateTimePick32"
#define DL_BEGINDRAG                                            (WM_USER+133)
#define DL_CANCELDRAG                                           (WM_USER+136)
#define DL_COPYCURSOR                                           2
#define DL_CURSORSET                                            0
#define DL_DRAGGING                                             (WM_USER+134)
#define DL_DROPPED                                              (WM_USER+135)
#define DL_MOVECURSOR                                           3
#define DL_STOPCURSOR                                           1
#define DPA_APPEND                                              dwfix(0x7FFF,0xFFFF)
#define DPA_ERR                                                 dwminus(1)
#define DPAS_INSERTAFTER                                        0x04
#define DPAS_INSERTBEFORE                                       0x02
#define DPAS_SORTED                                             0x01
#define DRAGLISTMSGSTRING                                       "commctrl_DragListMsg"
#define DSA_APPEND                                              dwfix(0x7FFF,0xFFFF)
#define DSA_ERR                                                 dwminus(1)
#define DTM_FIRST                                               0x1000
#define DTM_GETMCCOLOR                                          (DTM_FIRST +  7)
#define DTM_GETMCFONT                                           (DTM_FIRST +  10)
#define DTM_GETMONTHCAL                                         (DTM_FIRST +  8)
#define DTM_GETRANGE                                            (DTM_FIRST +  3)
#define DTM_GETSYSTEMTIME                                       (DTM_FIRST +  1)
#define DTM_SETFORMAT                                           (DTM_FIRST +  5)
#define DTM_SETMCCOLOR                                          (DTM_FIRST +  6)
#define DTM_SETMCFONT                                           (DTM_FIRST +  9)
#define DTM_SETRANGE                                            (DTM_FIRST +  4)
#define DTM_SETSYSTEMTIME                                       (DTM_FIRST +  2)
#define DTN_CLOSEUP                                             (DTN_FIRST +  7)
#define DTN_DATETIMECHANGE                                      (DTN_FIRST +  1)
#define DTN_DROPDOWN                                            (DTN_FIRST +  6)
#define DTN_FIRST                                               dwminus(760)
#define DTN_FORMAT                                              (DTN_FIRST +  4)
#define DTN_FORMATQUERY                                         (DTN_FIRST +  5)
#define DTN_LAST                                                dwminus(799)
#define DTN_USERSTRING                                          (DTN_FIRST +  2)
#define DTN_WMKEYDOWN                                           (DTN_FIRST +  3)
#define DTS_APPCANPARSE                                         0x10
#define DTS_LONGDATEFORMAT                                      0x04
#define DTS_RIGHTALIGN                                          0x20
#define DTS_SHORTDATECENTURYFORMAT                              0x0C
#define DTS_SHORTDATEFORMAT                                     0
#define DTS_SHOWNONE                                            0x02
#define DTS_TIMEFORMAT                                          0x09
#define DTS_UPDOWN                                              0x01
#define ECM_FIRST                                               0x1500
#define EM_GETCUEBANNER                                         (ECM_FIRST +  2)
#define EM_HIDEBALLOONTIP                                       (ECM_FIRST +  4)
#define EM_SETCUEBANNER                                         (ECM_FIRST +  1)
#define EM_SHOWBALLOONTIP                                       (ECM_FIRST +  3)
#define FSB_ENCARTA_MODE                                        1
#define FSB_FLAT_MODE                                           2
#define FSB_REGULAR_MODE                                        0
#define GDT_ERROR                                               dwminus(1)
#define GDT_NONE                                                1
#define GDT_VALID                                               0
#define GDTR_MAX                                                0x02
#define GDTR_MIN                                                0x01
#define GMR_DAYSTATE                                            1
#define GMR_VISIBLE                                             0
#define HDF_BITMAP                                              0x2000
#define HDF_BITMAP_ON_RIGHT                                     0x1000
#define HDF_CENTER                                              0x02
#define HDF_IMAGE                                               0x0800
#define HDF_JUSTIFYMASK                                         0x03
#define HDF_LEFT                                                0
#define HDF_OWNERDRAW                                           0x8000
#define HDF_RIGHT                                               0x01
#define HDF_RTLREADING                                          0x04
#define HDF_SORTDOWN                                            0x200
#define HDF_SORTUP                                              0x0400
#define HDF_STRING                                              0x4000
#define HDFT_HASNOVALUE                                         0x8000
#define HDFT_ISNUMBER                                           0x01
#define HDFT_ISSTRING                                           0
#define HDI_BITMAP                                              0x10
#define HDI_DI_SETITEM                                          0x040
#define HDI_FILTER                                              0x0100
#define HDI_FORMAT                                              0x04
#define HDI_HEIGHT                                              HDI_WIDTH
#define HDI_IMAGE                                               0x20
#define HDI_LPARAM                                              0x08
#define HDI_ORDER                                               0x080
#define HDI_TEXT                                                0x02
#define HDI_WIDTH                                               0x01
#define HDM_CLEARFILTER                                         (HDM_FIRST + 24)
#define HDM_CREATEDRAGIMAGE                                     (HDM_FIRST +  16)
#define HDM_DELETEITEM                                          (HDM_FIRST +  2)
#define HDM_EDITFILTER                                          (HDM_FIRST + 23)
#define HDM_FIRST                                               0x1200
#define HDM_GETBITMAPMARGIN                                     (HDM_FIRST +  21)
#define HDM_GETIMAGELIST                                        (HDM_FIRST +  9)
#define HDM_GETITEM                                             (HDM_FIRST +  3)
#define HDM_GETITEMCOUNT                                        (HDM_FIRST +  0)
#define HDM_GETORDERARRAY                                       (HDM_FIRST +  17)
#define HDM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define HDM_INSERTITEM                                          (HDM_FIRST +  1)
#define HDM_ORDERTOINDEX                                        (HDM_FIRST +  15)
#define HDM_SETBITMAPMARGIN                                     (HDM_FIRST +  20)
#define HDM_SETFILTERCHANGETIMEOUT                              (HDM_FIRST + 22)
#define HDM_SETHOTDIVIDER                                       (HDM_FIRST +  19)
#define HDM_SETIMAGELIST                                        (HDM_FIRST +  8)
#define HDM_SETITEM                                             (HDM_FIRST +  4)
#define HDM_SETORDERARRAY                                       (HDM_FIRST +  18)
#define HDM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define HDN_BEGINDRAG                                           (HDN_FIRST - 10)
#define HDN_BEGINTRACK                                          (HDN_FIRST - 6)
#define HDN_DIVIDERDBLCLICK                                     (HDN_FIRST - 5)
#define HDN_ENDDRAG                                             (HDN_FIRST - 11)
#define HDN_ENDTRACK                                            (HDN_FIRST - 7)
#define HDN_FILTERBTNCLICK                                      (HDN_FIRST - 13)
#define HDN_FILTERCHANGE                                        (HDN_FIRST - 12)
#define HDN_FIRST                                               dwMinus(300)
#define HDN_GETDISPINFO                                         (HDN_FIRST - 9)
#define HDN_ITEMCHANGED                                         (HDN_FIRST - 1)
#define HDN_ITEMCHANGING                                        (HDN_FIRST - 0)
#define HDN_ITEMCLICK                                           (HDN_FIRST - 2)
#define HDN_ITEMDBLCLICK                                        (HDN_FIRST - 3)
#define HDN_LAST                                                dwMinus(399)
#define HDN_TRACK                                               (HDN_FIRST - 8)
#define HDS_BUTTONS                                             0x02
#define HDS_DRAGDROP                                            0x040
#define HDS_FILTERBAR                                           0x0100
#define HDS_FLAT                                                0x200
#define HDS_FULLDRAG                                            0x080
#define HDS_HIDDEN                                              0x08
#define HDS_HORZ                                                0
#define HDS_HOTTRACK                                            0x04
#define HHT_ABOVE                                               0x0100
#define HHT_BELOW                                               0x200
#define HHT_NOWHERE                                             0x01
#define HHT_ONDIVIDER                                           0x04
#define HHT_ONDIVOPEN                                           0x08
#define HHT_ONFILTER                                            0x10
#define HHT_ONFILTERBUTTON                                      0x20
#define HHT_ONHEADER                                            0x02
#define HHT_TOLEFT                                              0x0800
#define HHT_TORIGHT                                             0x0400
#define HICF_ACCELERATOR                                        0x04
#define HICF_ARROWKEYS                                          0x02
#define HICF_DUPACCEL                                           0x08
#define HICF_ENTERING                                           0x10
#define HICF_LEAVING                                            0x20
#define HICF_LMOUSE                                             0x080
#define HICF_MOUSE                                              0x01
#define HICF_OTHER                                              0
#define HICF_RESELECT                                           0x040
#define HICF_TOGGLEDROPDOWN                                     0x0100
#define HINST_COMMCTRL                                          dwminus(1)
#define HIST_ADDTOFAVORITES                                     3
#define HIST_BACK                                               0
#define HIST_FAVORITES                                          2
#define HIST_FORWARD                                            1
#define HIST_VIEWTREE                                           4
#define HKCOMB_A                                                0x08
#define HKCOMB_C                                                0x04
#define HKCOMB_CA                                               0x040
#define HKCOMB_NONE                                             0x01
#define HKCOMB_S                                                0x02
#define HKCOMB_SA                                               0x20
#define HKCOMB_SC                                               0x10
#define HKCOMB_SCA                                              0x080
#define HKM_GETHOTKEY                                           (WM_USER+2)
#define HKM_SETHOTKEY                                           (WM_USER+1)
#define HKM_SETRULES                                            (WM_USER+3)
#define HOTKEY_CLASS                                            "msctls_hotkey32"
#define HOTKEYF_ALT                                             0x04
#define HOTKEYF_CONTROL                                         0x02
#define HOTKEYF_EXT                                             0x08
#define HOTKEYF_SHIFT                                           0x01
#define I_CHILDRENCALLBACK                                      dwminus(1)
#define I_COLUMNSCALLBACK                                       dwminus(1)
#define I_GROUPIDCALLBACK                                       dwminus(1)
#define I_GROUPIDNONE                                           dwminus(2)
#define I_IMAGECALLBACK                                         dwminus(1)
#define I_IMAGENONE                                             dwminus(2)
#define I_INDENTCALLBACK                                        dwminus(1)
#define ICC_ANIMATE_CLASS                                       0x080
#define ICC_BAR_CLASSES                                         0x04
#define ICC_COOL_CLASSES                                        0x0400
#define ICC_DATE_CLASSES                                        0x0100
#define ICC_HOTKEY_CLASS                                        0x040
#define ICC_INTERNET_CLASSES                                    0x0800
#define ICC_LINK_CLASS                                          0x08000
#define ICC_LISTVIEW_CLASSES                                    0x01
#define ICC_NATIVEFNTCTL_CLASS                                  0x02000
#define ICC_PAGESCROLLER_CLASS                                  0x1000
#define ICC_PROGRESS_CLASS                                      0x20
#define ICC_STANDARD_CLASSES                                    0x04000
#define ICC_TAB_CLASSES                                         0x08
#define ICC_TREEVIEW_CLASSES                                    0x02
#define ICC_UPDOWN_CLASS                                        0x10
#define ICC_USEREX_CLASSES                                      0x200
#define ICC_WIN95_CLASSES                                       0x0FF
#define IDB_HIST_LARGE_COLOR                                    9
#define IDB_HIST_SMALL_COLOR                                    8
#define IDB_STD_LARGE_COLOR                                     1
#define IDB_STD_SMALL_COLOR                                     0
#define IDB_VIEW_LARGE_COLOR                                    5
#define IDB_VIEW_SMALL_COLOR                                    4
#define ILC_COLOR                                               0
#define ILC_COLOR16                                             0x10
#define ILC_COLOR24                                             0x18
#define ILC_COLOR32                                             0x20
#define ILC_COLOR4                                              0x04
#define ILC_COLOR8                                              0x08
#define ILC_COLORDDB                                            0x0FE
#define ILC_MASK                                                0x01
#define ILC_MIRROR                                              0x02000
#define ILC_PALETTE                                             0x0800
#define ILC_PERITEMMIRROR                                       0x08000
#define ILCF_MOVE                                               0
#define ILCF_SWAP                                               1
#define ILD_BLEND                                               ILD_BLEND50
#define ILD_BLEND25                                             0x02
#define ILD_BLEND50                                             0x04
#define ILD_DPISCALE                                            0x04000
#define ILD_FOCUS                                               ILD_BLEND25
#define ILD_IMAGE                                               0x20
#define ILD_MASK                                                0x10
#define ILD_NORMAL                                              0
#define ILD_OVERLAYMASK                                         0x0F00
#define ILD_PRESERVEALPHA                                       0x1000
#define ILD_ROP                                                 0x040
#define ILD_SCALE                                               0x02000
#define ILD_SELECTED                                            ILD_BLEND50
#define ILD_TRANSPARENT                                         0x01
#define ILP_DOWNLEVEL                                           1
#define ILP_NORMAL                                              0
#define ILS_ALPHA                                               0x08
#define ILS_GLOW                                                0x01
#define ILS_NORMAL                                              0
#define ILS_SATURATE                                            0x04
#define ILS_SHADOW                                              0x02
#define INFOTIPSIZE                                             1024
#define INVALID_LINK_INDEX                                      dwminus(1)
#define IPM_CLEARADDRESS                                        (WM_USER+100)
#define IPM_GETADDRESS                                          (WM_USER+102)
#define IPM_ISBLANK                                             (WM_USER+105)
#define IPM_SETADDRESS                                          (WM_USER+101)
#define IPM_SETFOCUS                                            (WM_USER+104)
#define IPM_SETRANGE                                            (WM_USER+103)
#define IPN_FIELDCHANGED                                        (IPN_FIRST - 0)
#define IPN_FIRST                                               dwminus(860)
#define IPN_LAST                                                dwminus(879)
#define LIF_ITEMID                                              0x04
#define LIF_ITEMINDEX                                           0x01
#define LIF_STATE                                               0x02
#define LIF_URL                                                 0x08
#define LIS_ENABLED                                             0x02
#define LIS_FOCUSED                                             0x01
#define LIS_VISITED                                             0x04
#define LM_GETIDEALHEIGHT                                       (WM_USER+0x301)
#define LM_GETITEM                                              (WM_USER+0x303)
#define LM_HITTEST                                              (WM_USER+0x300)
#define LM_SETITEM                                              (WM_USER+0x302)
//#define LPHITTESTINFO                                           LPTTHITTESTINFO
//#define LPNM_CACHEHINT                                          LPNMLVCACHEHINT
//#define LPNM_FINDITEM                                           LPNMLVFINDITEM
//#define LPNM_LISTVIEW                                           LPNMLISTVIEW
//#define LPNM_ODSTATECHANGE                                      LPNMLVODSTATECHANGE
//#define LPNM_TREEVIEW                                           LPNMTREEVIEW
//#define LPNM_UPDOWN                                             LPNMUPDOWN
//#define LPNMLISTVIEW                                            LPNM_LISTVIEW
//#define LPNMTTDISPINFO                                          LPTOOLTIPTEXT
//#define LPNMUPDOWN                                              LPNM_UPDOWN
#define LPSTR_TEXTCALLBACK                                      dwminus(1)
//#define LPTC_HITTESTINFO                                        LPTCHITTESTINFO
//#define LPTCHITTESTINFO                                         LPTC_HITTESTINFO
//#define LPTOOLINFO                                              LPTTTOOLINFO
//#define LPTOOLTIPTEXT                                           LPNMTTDISPINFO
//#define LPTTHITTESTINFO                                         LPHITTESTINFO
//#define LPTTTOOLINFO                                            LPTOOLINFO
//#define LPTV_HITTESTINFO                                        LPTVHITTESTINFO
//#define LPTV_INSERTSTRUCT                                       LPTVINSERTSTRUCT
//#define LPTV_ITEM                                               LPTVITEM
//#define LPTV_SORTCB                                             LPTVSORTCB
//#define LPTVHITTESTINFO                                         LPTV_HITTESTINFO
//#define LPTVINSERTSTRUCT                                        LPTV_INSERTSTRUCT
//#define LPTVITEM                                                LPTV_ITEM
//#define LPTVSORTCB                                              LPTV_SORTCB
#define LV_MAX_WORKAREAS                                        16
#define LV_VIEW_DETAILS                                         0x01
#define LV_VIEW_ICON                                            0
#define LV_VIEW_LIST                                            0x03
#define LV_VIEW_MAX                                             0x04
#define LV_VIEW_SMALLICON                                       0x02
#define LV_VIEW_TILE                                            0x04
#define LVA_ALIGNLEFT                                           0x01
#define LVA_ALIGNTOP                                            0x02
#define LVA_DEFAULT                                             0
#define LVA_SNAPTOGRID                                          0x05
#define LVBKIF_FLAG_TILEOFFSET                                  0x0100
#define LVBKIF_SOURCE_HBITMAP                                   0x01
#define LVBKIF_SOURCE_MASK                                      0x03
#define LVBKIF_SOURCE_NONE                                      0
#define LVBKIF_SOURCE_URL                                       0x02
#define LVBKIF_STYLE_MASK                                       0x10
#define LVBKIF_STYLE_NORMAL                                     0
#define LVBKIF_STYLE_TILE                                       0x10
#define LVBKIF_TYPE_WATERMARK                                   0x10000000
#define LVCDI_GROUP                                             0x01
#define LVCDI_ITEM                                              0
#define LVCDRF_NOGROUPFRAME                                     0x020000
#define LVCDRF_NOSELECT                                         0x010000
#define LVCF_FMT                                                0x01
#define LVCF_IMAGE                                              0x10
#define LVCF_ORDER                                              0x20
#define LVCF_SUBITEM                                            0x08
#define LVCF_TEXT                                               0x04
#define LVCF_WIDTH                                              0x02
#define LVCFMT_BITMAP_ON_RIGHT                                  0x1000
#define LVCFMT_CENTER                                           0x02
#define LVCFMT_COL_HAS_IMAGES                                   0x8000
#define LVCFMT_IMAGE                                            0x0800
#define LVCFMT_JUSTIFYMASK                                      0x03
#define LVCFMT_LEFT                                             0
#define LVCFMT_RIGHT                                            0x01
// #define LVCOLUMN                                                LV_COLUMN
#define LVFI_NEARESTXY                                          0x040
#define LVFI_PARAM                                              0x01
#define LVFI_PARTIAL                                            0x08
#define LVFI_STRING                                             0x02
#define LVFI_WRAP                                               0x20
// #define LVFINDINFO                                              LV_FINDINFO
#define LVGA_FOOTER_CENTER                                      0x10
#define LVGA_FOOTER_LEFT                                        0x08
#define LVGA_FOOTER_RIGHT                                       0x20
#define LVGA_HEADER_CENTER                                      0x02
#define LVGA_HEADER_LEFT                                        0x01
#define LVGA_HEADER_RIGHT                                       0x04
#define LVGF_ALIGN                                              0x08
#define LVGF_FOOTER                                             0x02
#define LVGF_GROUPID                                            0x10
#define LVGF_HEADER                                             0x01
#define LVGF_NONE                                               0
#define LVGF_STATE                                              0x04
#define LVGIT_UNFOLDED                                          0x01
#define LVGMF_BORDERCOLOR                                       0x02
#define LVGMF_BORDERSIZE                                        0x01
#define LVGMF_NONE                                              0
#define LVGMF_TEXTCOLOR                                         0x04
#define LVGS_COLLAPSED                                          0x01
#define LVGS_HIDDEN                                             0x02
#define LVGS_NORMAL                                             0
#define LVHT_ABOVE                                              0x08
#define LVHT_BELOW                                              0x10
#define LVHT_NOWHERE                                            0x01
#define LVHT_ONITEM                                             nOr(LVHT_ONITEMICON ,LVHT_ONITEMLABEL,LVHT_ONITEMSTATEICON)
#define LVHT_ONITEMICON                                         0x02
#define LVHT_ONITEMLABEL                                        0x04
#define LVHT_ONITEMSTATEICON                                    0x08
#define LVHT_TOLEFT                                             0x040
#define LVHT_TORIGHT                                            0x20
#define LVIF_COLUMNS                                            0x200
#define LVIF_DI_SETITEM                                         0x1000
#define LVIF_GROUPID                                            0x0100
#define LVIF_IMAGE                                              0x02
#define LVIF_INDENT                                             0x10
#define LVIF_NORECOMPUTE                                        0x0800
#define LVIF_PARAM                                              0x04
#define LVIF_STATE                                              0x08
#define LVIF_TEXT                                               0x01
#define LVIM_AFTER                                              0x01
#define LVIR_BOUNDS                                             0
#define LVIR_ICON                                               1
#define LVIR_LABEL                                              2
#define LVIR_SELECTBOUNDS                                       3
#define LVIS_ACTIVATING                                         0x20
#define LVIS_CUT                                                0x04
#define LVIS_DROPHILITED                                        0x08
#define LVIS_FOCUSED                                            0x01
#define LVIS_GLOW                                               0x10
#define LVIS_OVERLAYMASK                                        0x0F00
#define LVIS_SELECTED                                           0x02
#define LVIS_STATEIMAGEMASK                                     0xF000
#define LVKF_ALT                                                0x01
#define LVKF_CONTROL                                            0x02
#define LVKF_SHIFT                                              0x04
#define LVM_APPROXIMATEVIEWRECT                                 (LVM_FIRST + 64)
#define LVM_ARRANGE                                             (LVM_FIRST + 22)
#define LVM_CANCELEDITLABEL                                     (LVM_FIRST + 179)
#define LVM_CREATEDRAGIMAGE                                     (LVM_FIRST + 33)
#define LVM_DELETEALLITEMS                                      (LVM_FIRST + 9)
#define LVM_DELETECOLUMN                                        (LVM_FIRST + 28)
#define LVM_DELETEITEM                                          (LVM_FIRST + 8)
#define LVM_EDITLABEL                                           (LVM_FIRST + 23)
#define LVM_ENABLEGROUPVIEW                                     (LVM_FIRST + 157)
#define LVM_ENSUREVISIBLE                                       (LVM_FIRST + 19)
#define LVM_FINDITEM                                            (LVM_FIRST + 13)
#define LVM_FIRST                                               0x1000
#define LVM_GETBKCOLOR                                          (LVM_FIRST + 0)
#define LVM_GETBKIMAGE                                          (LVM_FIRST + 69)
#define LVM_GETCALLBACKMASK                                     (LVM_FIRST + 10)
#define LVM_GETCOLUMN                                           (LVM_FIRST + 25)
#define LVM_GETCOLUMNORDERARRAY                                 (LVM_FIRST + 59)
#define LVM_GETCOLUMNWIDTH                                      (LVM_FIRST + 29)
#define LVM_GETCOUNTPERPAGE                                     (LVM_FIRST + 40)
#define LVM_GETEDITCONTROL                                      (LVM_FIRST + 24)
#define LVM_GETEXTENDEDLISTVIEWSTYLE                            (LVM_FIRST + 55)
#define LVM_GETGROUPINFO                                        (LVM_FIRST + 149)
#define LVM_GETGROUPMETRICS                                     (LVM_FIRST + 156)
#define LVM_GETHEADER                                           (LVM_FIRST + 31)
#define LVM_GETHOTCURSOR                                        (LVM_FIRST + 63)
#define LVM_GETHOTITEM                                          (LVM_FIRST + 61)
#define LVM_GETHOVERTIME                                        (LVM_FIRST + 72)
#define LVM_GETIMAGELIST                                        (LVM_FIRST + 2)
#define LVM_GETINSERTMARK                                       (LVM_FIRST + 167)
#define LVM_GETINSERTMARKCOLOR                                  (LVM_FIRST + 171)
#define LVM_GETINSERTMARKRECT                                   (LVM_FIRST + 169)
#define LVM_GETISEARCHSTRING                                    (LVM_FIRST + 52)
#define LVM_GETITEM                                             (LVM_FIRST + 5)
#define LVM_GETITEMCOUNT                                        (LVM_FIRST + 4)
#define LVM_GETITEMPOSITION                                     (LVM_FIRST + 16)
#define LVM_GETITEMRECT                                         (LVM_FIRST + 14)
#define LVM_GETITEMSPACING                                      (LVM_FIRST + 51)
#define LVM_GETITEMSTATE                                        (LVM_FIRST + 44)
#define LVM_GETITEMTEXT                                         (LVM_FIRST + 45)
#define LVM_GETNEXTITEM                                         (LVM_FIRST + 12)
#define LVM_GETNUMBEROFWORKAREAS                                (LVM_FIRST + 73)
#define LVM_GETORIGIN                                           (LVM_FIRST + 41)
#define LVM_GETOUTLINECOLOR                                     (LVM_FIRST + 176)
#define LVM_GETSELECTEDCOLUMN                                   (LVM_FIRST + 174)
#define LVM_GETSELECTEDCOUNT                                    (LVM_FIRST + 50)
#define LVM_GETSELECTIONMARK                                    (LVM_FIRST + 66)
#define LVM_GETSTRINGWIDTH                                      (LVM_FIRST + 17)
#define LVM_GETSUBITEMRECT                                      (LVM_FIRST + 56)
#define LVM_GETTEXTBKCOLOR                                      (LVM_FIRST + 37)
#define LVM_GETTEXTCOLOR                                        (LVM_FIRST + 35)
#define LVM_GETTILEINFO                                         (LVM_FIRST + 165)
#define LVM_GETTILEVIEWINFO                                     (LVM_FIRST + 163)
#define LVM_GETTOOLTIPS                                         (LVM_FIRST + 78)
#define LVM_GETTOPINDEX                                         (LVM_FIRST + 39)
#define LVM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define LVM_GETVIEW                                             (LVM_FIRST + 143)
#define LVM_GETVIEWRECT                                         (LVM_FIRST + 34)
#define LVM_GETWORKAREAS                                        (LVM_FIRST + 70)
#define LVM_HASGROUP                                            (LVM_FIRST + 161)
#define LVM_HITTEST                                             (LVM_FIRST + 18)
#define LVM_INSERTCOLUMN                                        (LVM_FIRST + 27)
#define LVM_INSERTGROUP                                         (LVM_FIRST + 145)
#define LVM_INSERTGROUPSORTED                                   (LVM_FIRST + 159)
#define LVM_INSERTITEM                                          (LVM_FIRST + 7)
#define LVM_INSERTMARKHITTEST                                   (LVM_FIRST + 168)
#define LVM_ISGROUPVIEWENABLED                                  (LVM_FIRST + 175)
#define LVM_MAPIDTOINDEX                                        (LVM_FIRST + 181)
#define LVM_MAPINDEXTOID                                        (LVM_FIRST + 180)
#define LVM_MOVEGROUP                                           (LVM_FIRST + 151)
#define LVM_MOVEITEMTOGROUP                                     (LVM_FIRST + 154)
#define LVM_REDRAWITEMS                                         (LVM_FIRST + 21)
#define LVM_REMOVEALLGROUPS                                     (LVM_FIRST + 160)
#define LVM_REMOVEGROUP                                         (LVM_FIRST + 150)
#define LVM_SCROLL                                              (LVM_FIRST + 20)
#define LVM_SETBKCOLOR                                          (LVM_FIRST + 1)
#define LVM_SETBKIMAGE                                          (LVM_FIRST + 68)
#define LVM_SETCALLBACKMASK                                     (LVM_FIRST + 11)
#define LVM_SETCOLUMN                                           (LVM_FIRST + 26)
#define LVM_SETCOLUMNORDERARRAY                                 (LVM_FIRST + 58)
#define LVM_SETCOLUMNWIDTH                                      (LVM_FIRST + 30)
#define LVM_SETEXTENDEDLISTVIEWSTYLE                            (LVM_FIRST + 54)
#define LVM_SETGROUPINFO                                        (LVM_FIRST + 147)
#define LVM_SETGROUPMETRICS                                     (LVM_FIRST + 155)
#define LVM_SETHOTCURSOR                                        (LVM_FIRST + 62)
#define LVM_SETHOTITEM                                          (LVM_FIRST + 60)
#define LVM_SETHOVERTIME                                        (LVM_FIRST + 71)
#define LVM_SETICONSPACING                                      (LVM_FIRST + 53)
#define LVM_SETIMAGELIST                                        (LVM_FIRST + 3)
#define LVM_SETINFOTIP                                          (LVM_FIRST + 173)
#define LVM_SETINSERTMARK                                       (LVM_FIRST + 166)
#define LVM_SETINSERTMARKCOLOR                                  (LVM_FIRST + 170)
#define LVM_SETITEM                                             (LVM_FIRST + 6)
#define LVM_SETITEMCOUNT                                        (LVM_FIRST + 47)
#define LVM_SETITEMPOSITION                                     (LVM_FIRST + 15)
#define LVM_SETITEMPOSITION32                                   (LVM_FIRST + 49)
#define LVM_SETITEMSTATE                                        (LVM_FIRST + 43)
#define LVM_SETITEMTEXT                                         (LVM_FIRST + 46)
#define LVM_SETOUTLINECOLOR                                     (LVM_FIRST + 177)
#define LVM_SETSELECTEDCOLUMN                                   (LVM_FIRST + 140)
#define LVM_SETSELECTIONMARK                                    (LVM_FIRST + 67)
#define LVM_SETTEXTBKCOLOR                                      (LVM_FIRST + 38)
#define LVM_SETTEXTCOLOR                                        (LVM_FIRST + 36)
#define LVM_SETTILEINFO                                         (LVM_FIRST + 164)
#define LVM_SETTILEVIEWINFO                                     (LVM_FIRST + 162)
#define LVM_SETTILEWIDTH                                        (LVM_FIRST + 141)
#define LVM_SETTOOLTIPS                                         (LVM_FIRST + 74)
#define LVM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define LVM_SETVIEW                                             (LVM_FIRST + 142)
#define LVM_SETWORKAREAS                                        (LVM_FIRST + 65)
#define LVM_SORTGROUPS                                          (LVM_FIRST + 158)
#define LVM_SORTITEMS                                           (LVM_FIRST + 48)
#define LVM_SORTITEMSEX                                         (LVM_FIRST + 81)
#define LVM_SUBITEMHITTEST                                      (LVM_FIRST + 57)
#define LVM_UPDATE                                              (LVM_FIRST + 42)
#define LVN_BEGINDRAG                                           (LVN_FIRST-9)
#define LVN_BEGINLABELEDIT                                      (LVN_FIRST-5)
#define LVN_BEGINRDRAG                                          (LVN_FIRST-11)
#define LVN_COLUMNCLICK                                         (LVN_FIRST-8)
#define LVN_DELETEALLITEMS                                      (LVN_FIRST-4)
#define LVN_DELETEITEM                                          (LVN_FIRST-3)
#define LVN_ENDLABELEDIT                                        (LVN_FIRST-6)
#define LVN_FIRST                                               dwMinus(100)
#define LVN_GETDISPINFO                                         (LVN_FIRST-50)
#define LVN_GETINFOTIP                                          (LVN_FIRST-57)
#define LVN_HOTTRACK                                            (LVN_FIRST-21)
#define LVN_INSERTITEM                                          (LVN_FIRST-2)
#define LVN_ITEMACTIVATE                                        (LVN_FIRST-14)
#define LVN_ITEMCHANGED                                         (LVN_FIRST-1)
#define LVN_ITEMCHANGING                                        (LVN_FIRST-0)
#define LVN_KEYDOWN                                             (LVN_FIRST-55)
#define LVN_LAST                                                dwMinus(199)
#define LVN_MARQUEEBEGIN                                        (LVN_FIRST-56)
#define LVN_ODCACHEHINT                                         (LVN_FIRST-13)
#define LVN_ODFINDITEM                                          (LVN_FIRST-52)
#define LVN_ODSTATECHANGED                                      (LVN_FIRST-15)
#define LVN_SETDISPINFO                                         (LVN_FIRST-51)
#define LVNI_ABOVE                                              0x0100
#define LVNI_ALL                                                0
#define LVNI_BELOW                                              0x200
#define LVNI_CUT                                                0x04
#define LVNI_DROPHILITED                                        0x08
#define LVNI_FOCUSED                                            0x01
#define LVNI_SELECTED                                           0x02
#define LVNI_TOLEFT                                             0x0400
#define LVNI_TORIGHT                                            0x0800
#define LVS_ALIGNLEFT                                           0x0800
#define LVS_ALIGNMASK                                           0x0c00
#define LVS_ALIGNTOP                                            0
#define LVS_AUTOARRANGE                                         0x0100
#define LVS_EDITLABELS                                          0x200
#define LVS_EX_BORDERSELECT                                     0x08000
#define LVS_EX_CHECKBOXES                                       0x04
#define LVS_EX_DOUBLEBUFFER                                     0x010000
#define LVS_EX_FLATSB                                           0x0100
#define LVS_EX_FULLROWSELECT                                    0x20
#define LVS_EX_GRIDLINES                                        0x01
#define LVS_EX_HEADERDRAGDROP                                   0x10
#define LVS_EX_HIDELABELS                                       0x020000
#define LVS_EX_INFOTIP                                          0x0400
#define LVS_EX_LABELTIP                                         0x04000
#define LVS_EX_MULTIWORKAREAS                                   0x02000
#define LVS_EX_ONECLICKACTIVATE                                 0x040
#define LVS_EX_REGIONAL                                         0x200
#define LVS_EX_SIMPLESELECT                                     0x100000
#define LVS_EX_SINGLEROW                                        0x040000
#define LVS_EX_SNAPTOGRID                                       0x080000
#define LVS_EX_SUBITEMIMAGES                                    0x02
#define LVS_EX_TRACKSELECT                                      0x08
#define LVS_EX_TWOCLICKACTIVATE                                 0x080
#define LVS_EX_UNDERLINECOLD                                    0x1000
#define LVS_EX_UNDERLINEHOT                                     0x0800
#define LVS_ICON                                                0
#define LVS_LIST                                                0x03
#define LVS_NOCOLUMNHEADER                                      0x4000
#define LVS_NOLABELWRAP                                         0x080
#define LVS_NOSCROLL                                            0x2000
#define LVS_NOSORTHEADER                                        0x8000
#define LVS_OWNERDATA                                           0x1000
#define LVS_OWNERDRAWFIXED                                      0x0400
#define LVS_REPORT                                              0x01
#define LVS_SHAREIMAGELISTS                                     0x040
#define LVS_SHOWSELALWAYS                                       0x08
#define LVS_SINGLESEL                                           0x04
#define LVS_SMALLICON                                           0x02
#define LVS_SORTASCENDING                                       0x10
#define LVS_SORTDESCENDING                                      0x20
#define LVS_TYPEMASK                                            0x03
#define LVS_TYPESTYLEMASK                                       0xfc00
#define LVSCW_AUTOSIZE                                          dwminus(1)
#define LVSCW_AUTOSIZE_USEHEADER                                dwminus(2)
#define LVSICF_NOINVALIDATEALL                                  0x01
#define LVSICF_NOSCROLL                                         0x02
#define LVSIL_NORMAL                                            0
#define LVSIL_SMALL                                             1
#define LVSIL_STATE                                             2
#define LVTVIF_AUTOSIZE                                         0
#define LVTVIF_FIXEDHEIGHT                                      0x02
#define LVTVIF_FIXEDSIZE                                        0x03
#define LVTVIF_FIXEDWIDTH                                       0x01
#define LVTVIM_COLUMNS                                          0x02
#define LVTVIM_LABELMARGIN                                      0x04
#define LVTVIM_TILESIZE                                         0x01
#define LWS_IGNORERETURN                                        0x02
#define LWS_TRANSPARENT                                         0x01
#define MAX_LINKID_TEXT                                         48
#define MCHT_CALENDAR                                           0x020000
#define MCHT_CALENDARBK                                         nOr(MCHT_CALENDAR)
#define MCHT_CALENDARDATE                                       nOr(MCHT_CALENDAR , 0x01)
#define MCHT_CALENDARDATENEXT                                   nOr(MCHT_CALENDARDATE , MCHT_NEXT)
#define MCHT_CALENDARDATEPREV                                   nOr(MCHT_CALENDARDATE , MCHT_PREV)
#define MCHT_CALENDARDAY                                        nOr(MCHT_CALENDAR , 0x02)
#define MCHT_CALENDARWEEKNUM                                    nOr(MCHT_CALENDAR , 0x03)
#define MCHT_NEXT                                               0x1000000
#define MCHT_NOWHERE                                            0
#define MCHT_PREV                                               0x02000000
#define MCHT_TITLE                                              0x010000
#define MCHT_TITLEBK                                            (MCHT_TITLE)
#define MCHT_TITLEBTNNEXT                                       nOr(MCHT_TITLE , MCHT_NEXT , 0x03)
#define MCHT_TITLEBTNPREV                                       nOr(MCHT_TITLE , MCHT_PREV , 0x03)
#define MCHT_TITLEMONTH                                         nOr(MCHT_TITLE , 0x01)
#define MCHT_TITLEYEAR                                          nOr(MCHT_TITLE , 0x02)
#define MCHT_TODAYLINK                                          0x030000
#define MCM_FIRST                                               0x1000
#define MCM_GETCOLOR                                            (MCM_FIRST + 11)
#define MCM_GETCURSEL                                           (MCM_FIRST + 1)
#define MCM_GETFIRSTDAYOFWEEK                                   (MCM_FIRST + 16)
#define MCM_GETMAXSELCOUNT                                      (MCM_FIRST + 3)
#define MCM_GETMAXTODAYWIDTH                                    (MCM_FIRST + 21)
#define MCM_GETMINREQRECT                                       (MCM_FIRST + 9)
#define MCM_GETMONTHDELTA                                       (MCM_FIRST + 19)
#define MCM_GETMONTHRANGE                                       (MCM_FIRST + 7)
#define MCM_GETRANGE                                            (MCM_FIRST + 17)
#define MCM_GETSELRANGE                                         (MCM_FIRST + 5)
#define MCM_GETTODAY                                            (MCM_FIRST + 13)
#define MCM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define MCM_HITTEST                                             (MCM_FIRST + 14)
#define MCM_SETCOLOR                                            (MCM_FIRST + 10)
#define MCM_SETCURSEL                                           (MCM_FIRST + 2)
#define MCM_SETDAYSTATE                                         (MCM_FIRST + 8)
#define MCM_SETFIRSTDAYOFWEEK                                   (MCM_FIRST + 15)
#define MCM_SETMAXSELCOUNT                                      (MCM_FIRST + 4)
#define MCM_SETMONTHDELTA                                       (MCM_FIRST + 20)
#define MCM_SETRANGE                                            (MCM_FIRST + 18)
#define MCM_SETSELRANGE                                         (MCM_FIRST + 6)
#define MCM_SETTODAY                                            (MCM_FIRST + 12)
#define MCM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define MCN_FIRST                                               dwminus(750)
#define MCN_GETDAYSTATE                                         (MCN_FIRST + 3)
#define MCN_LAST                                                dwminus(759)
#define MCN_SELCHANGE                                           (MCN_FIRST + 1)
#define MCN_SELECT                                              (MCN_FIRST + 4)
#define MCS_DAYSTATE                                            0x01
#define MCS_MULTISELECT                                         0x02
#define MCS_NOTODAY                                             0x10
#define MCS_NOTODAYCIRCLE                                       0x08
#define MCS_WEEKNUMBERS                                         0x04
#define MCSC_BACKGROUND                                         0
#define MCSC_MONTHBK                                            4
#define MCSC_TEXT                                               1
#define MCSC_TITLEBK                                            2
#define MCSC_TITLETEXT                                          3
#define MCSC_TRAILINGTEXT                                       5
#define MINSYSCOMMAND                                           SC_SIZE
#define MONTHCAL_CLASS                                          "SysMonthCal32"
#define MSGF_COMMCTRL_BEGINDRAG                                 0x4200
#define MSGF_COMMCTRL_DRAGSELECT                                0x4202
#define MSGF_COMMCTRL_SIZEHEADER                                0x4201
#define MSGF_COMMCTRL_TOOLBARCUST                               0x4203
#define NFS_ALL                                                 0x10
#define NFS_BUTTON                                              0x08
#define NFS_EDIT                                                0x01
#define NFS_LISTCOMBO                                           0x04
#define NFS_STATIC                                              0x02
#define NFS_USEFONTASSOC                                        0x20
// #define NM_CACHEHINT                                            NMLVCACHEHINT
#define NM_CHAR                                                 (NM_FIRST-18)
#define NM_CLICK                                                (NM_FIRST-2)
#define NM_CUSTOMDRAW                                           (NM_FIRST-12)
#define NM_DBLCLK                                               (NM_FIRST-3)
//#define NM_FINDITEM                                             NMLVFINDITEM
#define NM_FIRST                                                dwMinus( 0)
#define NM_HOVER                                                (NM_FIRST-13)
#define NM_KEYDOWN                                              (NM_FIRST-15)
#define NM_KILLFOCUS                                            (NM_FIRST-8)
#define NM_LAST                                                 dwMinus( 99)
#define NM_LDOWN                                                (NM_FIRST-20)
#define NM_LISTVIEW                                             NMLISTVIEW
#define NM_NCHITTEST                                            (NM_FIRST-14)
// #define NM_ODSTATECHANGE                                        NMLVODSTATECHANGE
#define NM_OUTOFMEMORY                                          (NM_FIRST-1)
#define NM_RCLICK                                               (NM_FIRST-5)
#define NM_RDBLCLK                                              (NM_FIRST-6)
#define NM_RDOWN                                                (NM_FIRST-21)
#define NM_RELEASEDCAPTURE                                      (NM_FIRST-16)
#define NM_RETURN                                               (NM_FIRST-4)
#define NM_SETCURSOR                                            (NM_FIRST-17)
#define NM_SETFOCUS                                             (NM_FIRST-7)
#define NM_THEMECHANGED                                         (NM_FIRST-22)
#define NM_TOOLTIPSCREATED                                      (NM_FIRST-19)
// #define NM_TREEVIEW                                             NMTREEVIEW
// #define NM_UPDOWN                                               NMUPDOWN
// #define NMLISTVIEW                                              NM_LISTVIEW
// #define NMLVDISPINFO                                            LV_DISPINFO
//#define NMLVKEYDOWN                                             LV_KEYDOWN
//#define NMTREEVIEW                                              NM_TREEVIEW
//#define NMTTDISPINFO                                            TOOLTIPTEXT
//#define NMTVDISPINFO                                            TV_DISPINFO
//#define NMTVKEYDOWN                                             TV_KEYDOWN
//#define NMUPDOWN                                                NM_UPDOWN
#define ODT_HEADER                                              100
#define ODT_LISTVIEW                                            102
#define ODT_TAB                                                 101
#define PBM_DELTAPOS                                            (WM_USER+3)
#define PBM_GETPOS                                              (WM_USER+8)
#define PBM_GETRANGE                                            (WM_USER+7)
#define PBM_SETBARCOLOR                                         (WM_USER+9)
#define PBM_SETBKCOLOR                                          CCM_SETBKCOLOR
#define PBM_SETMARQUEE                                          (WM_USER+10)
#define PBM_SETPOS                                              (WM_USER+2)
#define PBM_SETRANGE                                            (WM_USER+1)
#define PBM_SETRANGE32                                          (WM_USER+6)
#define PBM_SETSTEP                                             (WM_USER+4)
#define PBM_STEPIT                                              (WM_USER+5)
#define PBS_MARQUEE                                             0x08
#define PBS_SMOOTH                                              0x01
#define PBS_VERTICAL                                            0x04
#define PGB_BOTTOMORRIGHT                                       1
#define PGB_TOPORLEFT                                           0
#define PGF_CALCHEIGHT                                          2
#define PGF_CALCWIDTH                                           1
#define PGF_DEPRESSED                                           4
#define PGF_GRAYED                                              2
#define PGF_HOT                                                 8
#define PGF_INVISIBLE                                           0
#define PGF_NORMAL                                              1
#define PGF_SCROLLDOWN                                          2
#define PGF_SCROLLLEFT                                          4
#define PGF_SCROLLRIGHT                                         8
#define PGF_SCROLLUP                                            1
#define PGK_CONTROL                                             2
#define PGK_MENU                                                4
#define PGK_SHIFT                                               1
#define PGM_FIRST                                               0x1400
#define PGM_FORWARDMOUSE                                        (PGM_FIRST + 3)
#define PGM_GETBKCOLOR                                          (PGM_FIRST + 5)
#define PGM_GETBORDER                                           (PGM_FIRST + 7)
#define PGM_GETBUTTONSIZE                                       (PGM_FIRST + 11)
#define PGM_GETBUTTONSTATE                                      (PGM_FIRST + 12)
#define PGM_GETDROPTARGET                                       CCM_GETDROPTARGET
#define PGM_GETPOS                                              (PGM_FIRST + 9)
#define PGM_RECALCSIZE                                          (PGM_FIRST + 2)
#define PGM_SETBKCOLOR                                          (PGM_FIRST + 4)
#define PGM_SETBORDER                                           (PGM_FIRST + 6)
#define PGM_SETBUTTONSIZE                                       (PGM_FIRST + 10)
#define PGM_SETCHILD                                            (PGM_FIRST + 1)
#define PGM_SETPOS                                              (PGM_FIRST + 8)
#define PGN_CALCSIZE                                            (PGN_FIRST-2)
#define PGN_FIRST                                               dwminus(900)
#define PGN_HOTITEMCHANGE                                       (PGN_FIRST-3)
#define PGN_LAST                                                dwminus(950)
#define PGN_SCROLL                                              (PGN_FIRST-1)
#define PGS_AUTOSCROLL                                          0x02
#define PGS_DRAGNDROP                                           0x04
#define PGS_HORZ                                                0x01
#define PGS_VERT                                                0
//#define PNM_CACHEHINT                                           LPNMLVCACHEHINT
//#define PNM_FINDITEM                                            LPNMLVFINDITEM
//#define PNM_ODSTATECHANGE                                       LPNMLVODSTATECHANGE
#define PROGRESS_CLASS                                          "msctls_progress32"
#define RB_BEGINDRAG                                            (WM_USER + 24)
#define RB_DELETEBAND                                           (WM_USER + 2)
#define RB_DRAGMOVE                                             (WM_USER + 26)
#define RB_ENDDRAG                                              (WM_USER + 25)
#define RB_GETBANDBORDERS                                       (WM_USER + 34)
#define RB_GETBANDCOUNT                                         (WM_USER + 12)
#define RB_GETBANDINFO                                          (WM_USER + 29)
#define RB_GETBANDMARGINS                                       (WM_USER + 40)
#define RB_GETBARHEIGHT                                         (WM_USER + 27)
#define RB_GETBARINFO                                           (WM_USER + 3)
#define RB_GETBKCOLOR                                           (WM_USER + 20)
#define RB_GETCOLORSCHEME                                       CCM_GETCOLORSCHEME
#define RB_GETDROPTARGET                                        (CCM_GETDROPTARGET)
#define RB_GETPALETTE                                           (WM_USER + 38)
#define RB_GETRECT                                              (WM_USER + 9)
#define RB_GETROWCOUNT                                          (WM_USER + 13)
#define RB_GETROWHEIGHT                                         (WM_USER + 14)
#define RB_GETTEXTCOLOR                                         (WM_USER + 22)
#define RB_GETTOOLTIPS                                          (WM_USER + 17)
#define RB_GETUNICODEFORMAT                                     CCM_GETUNICODEFORMAT
#define RB_HITTEST                                              (WM_USER + 8)
#define RB_IDTOINDEX                                            (WM_USER + 16)
#define RB_INSERTBAND                                           (WM_USER + 1)
#define RB_MAXIMIZEBAND                                         (WM_USER + 31)
#define RB_MINIMIZEBAND                                         (WM_USER + 30)
#define RB_MOVEBAND                                             (WM_USER + 39)
#define RB_PUSHCHEVRON                                          (WM_USER + 43)
#define RB_SETBANDINFO                                          (WM_USER + 6)
#define RB_SETBARINFO                                           (WM_USER + 4)
#define RB_SETBKCOLOR                                           (WM_USER + 19)
#define RB_SETCOLORSCHEME                                       CCM_SETCOLORSCHEME
#define RB_SETPALETTE                                           (WM_USER + 37)
#define RB_SETPARENT                                            (WM_USER + 7)
#define RB_SETTEXTCOLOR                                         (WM_USER + 21)
#define RB_SETTOOLTIPS                                          (WM_USER + 18)
#define RB_SETUNICODEFORMAT                                     CCM_SETUNICODEFORMAT
#define RB_SETWINDOWTHEME                                       CCM_SETWINDOWTHEME
#define RB_SHOWBAND                                             (WM_USER + 35)
#define RB_SIZETORECT                                           (WM_USER + 23)
#define RBAB_ADDBAND                                            0x02
#define RBAB_AUTOSIZE                                           0x01
#define RBBIM_BACKGROUND                                        0x080
#define RBBIM_CHILD                                             0x10
#define RBBIM_CHILDSIZE                                         0x20
#define RBBIM_COLORS                                            0x02
#define RBBIM_HEADERSIZE                                        0x0800
#define RBBIM_ID                                                0x0100
#define RBBIM_IDEALSIZE                                         0x200
#define RBBIM_IMAGE                                             0x08
#define RBBIM_LPARAM                                            0x0400
#define RBBIM_SIZE                                              0x040
#define RBBIM_STYLE                                             0x01
#define RBBIM_TEXT                                              0x04
#define RBBS_BREAK                                              0x01
#define RBBS_CHILDEDGE                                          0x04
#define RBBS_FIXEDBMP                                           0x20
#define RBBS_FIXEDSIZE                                          0x02
#define RBBS_GRIPPERALWAYS                                      0x080
#define RBBS_HIDDEN                                             0x08
#define RBBS_HIDETITLE                                          0x0400
#define RBBS_NOGRIPPER                                          0x0100
#define RBBS_NOVERT                                             0x10
#define RBBS_TOPALIGN                                           0x0800
#define RBBS_USECHEVRON                                         0x200
#define RBBS_VARIABLEHEIGHT                                     0x040
#define RBHT_CAPTION                                            0x02
#define RBHT_CHEVRON                                            0x08
#define RBHT_CLIENT                                             0x03
#define RBHT_GRABBER                                            0x04
#define RBHT_NOWHERE                                            0x01
#define RBIM_IMAGELIST                                          0x01
#define RBN_AUTOBREAK                                           (RBN_FIRST - 22)
#define RBN_AUTOSIZE                                            (RBN_FIRST - 3)
#define RBN_BEGINDRAG                                           (RBN_FIRST - 4)
#define RBN_CHEVRONPUSHED                                       (RBN_FIRST - 10)
#define RBN_CHILDSIZE                                           (RBN_FIRST - 8)
#define RBN_DELETEDBAND                                         (RBN_FIRST - 7)
#define RBN_DELETINGBAND                                        (RBN_FIRST - 6)
#define RBN_ENDDRAG                                             (RBN_FIRST - 5)
#define RBN_FIRST                                               dwminus(831)
#define RBN_GETOBJECT                                           (RBN_FIRST - 1)
#define RBN_HEIGHTCHANGE                                        (RBN_FIRST - 0)
#define RBN_LAST                                                dwminus(859)
#define RBN_LAYOUTCHANGED                                       (RBN_FIRST - 2)
#define RBN_MINMAX                                              (RBN_FIRST - 21)
#define RBNM_ID                                                 0x01
#define RBNM_LPARAM                                             0x04
#define RBNM_STYLE                                              0x02
#define RBS_AUTOSIZE                                            0x2000
#define RBS_BANDBORDERS                                         0x0400
#define RBS_DBLCLKTOGGLE                                        0x8000
#define RBS_FIXEDORDER                                          0x0800
#define RBS_REGISTERDROP                                        0x1000
#define RBS_TOOLTIPS                                            0x0100
#define RBS_VARHEIGHT                                           0x200
#define RBS_VERTICALGRIPPER                                     0x4000
#define RBSTR_CHANGERECT                                        0x01
#define REBARCLASSNAME                                          "ReBarWindow32"
#define SB_GETBORDERS                                           (WM_USER+7)
#define SB_GETICON                                              (WM_USER+20)
#define SB_GETPARTS                                             (WM_USER+6)
#define SB_GETRECT                                              (WM_USER+10)
#define SB_GETTEXT                                              (WM_USER+2)
#define SB_GETTEXTLENGTH                                        (WM_USER+3)
#define SB_GETTIPTEXT                                           (WM_USER+18)
#define SB_GETUNICODEFORMAT                                     CCM_GETUNICODEFORMAT
#define SB_ISSIMPLE                                             (WM_USER+14)
#define SB_SETBKCOLOR                                           CCM_SETBKCOLOR
#define SB_SETICON                                              (WM_USER+15)
#define SB_SETMINHEIGHT                                         (WM_USER+8)
#define SB_SETPARTS                                             (WM_USER+4)
#define SB_SETTEXT                                              (WM_USER+1)
#define SB_SETTIPTEXT                                           (WM_USER+16)
#define SB_SETUNICODEFORMAT                                     CCM_SETUNICODEFORMAT
#define SB_SIMPLE                                               (WM_USER+9)
#define SB_SIMPLEID                                             0x0ff
#define SBARS_SIZEGRIP                                          0x0100
#define SBARS_TOOLTIPS                                          0x0800
#define SBN_FIRST                                               dwminus(880)
#define SBN_LAST                                                dwminus(899)
#define SBN_SIMPLEMODECHANGE                                    (SBN_FIRST - 0)
#define SBT_NOBORDERS                                           0x0100
#define SBT_NOTABPARSING                                        0x0800
#define SBT_OWNERDRAW                                           0x1000
#define SBT_POPOUT                                              0x200
#define SBT_RTLREADING                                          0x0400
#define SBT_TOOLTIPS                                            0x0800
#define STATUSCLASSNAME                                         "msctls_statusbar32"
#define STD_COPY                                                1
#define STD_CUT                                                 0
#define STD_DELETE                                              5
#define STD_FILENEW                                             6
#define STD_FILEOPEN                                            7
#define STD_FILESAVE                                            8
#define STD_FIND                                                12
#define STD_HELP                                                11
#define STD_PASTE                                               2
#define STD_PRINT                                               14
#define STD_PRINTPRE                                            9
#define STD_PROPERTIES                                          10
#define STD_REDOW                                               4
#define STD_REPLACE                                             13
#define STD_UNDO                                                3
#define TB_ADDBITMAP                                            (WM_USER + 19)
#define TB_ADDBUTTONS                                           (WM_USER + 20)
#define TB_ADDSTRING                                            (WM_USER + 28)
#define TB_AUTOSIZE                                             (WM_USER + 33)
#define TB_BOTTOM                                               7
#define TB_BUTTONCOUNT                                          (WM_USER + 24)
#define TB_BUTTONSTRUCTSIZE                                     (WM_USER + 30)
#define TB_CHANGEBITMAP                                         (WM_USER + 43)
#define TB_CHECKBUTTON                                          (WM_USER + 2)
#define TB_COMMANDTOINDEX                                       (WM_USER + 25)
#define TB_CUSTOMIZE                                            (WM_USER + 27)
#define TB_DELETEBUTTON                                         (WM_USER + 22)
#define TB_ENABLEBUTTON                                         (WM_USER + 1)
#define TB_ENDTRACK                                             8
#define TB_GETANCHORHIGHLIGHT                                   (WM_USER + 74)
#define TB_GETBITMAP                                            (WM_USER + 44)
#define TB_GETBITMAPFLAGS                                       (WM_USER + 41)
#define TB_GETBUTTON                                            (WM_USER + 23)
#define TB_GETBUTTONINFO                                        (WM_USER + 65)
#define TB_GETBUTTONSIZE                                        (WM_USER + 58)
#define TB_GETBUTTONTEXT                                        (WM_USER + 45)
#define TB_GETCOLORSCHEME                                       CCM_GETCOLORSCHEME
#define TB_GETDISABLEDIMAGELIST                                 (WM_USER + 55)
#define TB_GETEXTENDEDSTYLE                                     (WM_USER + 85)
#define TB_GETHOTIMAGELIST                                      (WM_USER + 53)
#define TB_GETHOTITEM                                           (WM_USER + 71)
#define TB_GETIMAGELIST                                         (WM_USER + 49)
#define TB_GETINSERTMARK                                        (WM_USER + 79)
#define TB_GETINSERTMARKCOLOR                                   (WM_USER + 89)
#define TB_GETITEMRECT                                          (WM_USER + 29)
#define TB_GETMAXSIZE                                           (WM_USER + 83)
#define TB_GETMETRICS                                           (WM_USER + 101)
#define TB_GETOBJECT                                            (WM_USER + 62)
#define TB_GETPADDING                                           (WM_USER + 86)
#define TB_GETRECT                                              (WM_USER + 51)
#define TB_GETROWS                                              (WM_USER + 40)
#define TB_GETSTATE                                             (WM_USER + 18)
#define TB_GETSTRING                                            (WM_USER + 92)
#define TB_GETSTYLE                                             (WM_USER + 57)
#define TB_GETTEXTROWS                                          (WM_USER + 61)
#define TB_GETTOOLTIPS                                          (WM_USER + 35)
#define TB_GETUNICODEFORMAT                                     CCM_GETUNICODEFORMAT
#define TB_HIDEBUTTON                                           (WM_USER + 4)
#define TB_HITTEST                                              (WM_USER + 69)
#define TB_INDETERMINATE                                        (WM_USER + 5)
#define TB_INSERTBUTTON                                         (WM_USER + 21)
#define TB_INSERTMARKHITTEST                                    (WM_USER + 81)
#define TB_ISBUTTONCHECKED                                      (WM_USER + 10)
#define TB_ISBUTTONENABLED                                      (WM_USER + 9)
#define TB_ISBUTTONHIDDEN                                       (WM_USER + 12)
#define TB_ISBUTTONHIGHLIGHTED                                  (WM_USER + 14)
#define TB_ISBUTTONINDETERMINATE                                (WM_USER + 13)
#define TB_ISBUTTONPRESSED                                      (WM_USER + 11)
#define TB_LINEDOWN                                             1
#define TB_LINEUP                                               0
#define TB_LOADIMAGES                                           (WM_USER + 50)
#define TB_MAPACCELERATOR                                       (WM_USER + 78)
#define TB_MARKBUTTON                                           (WM_USER + 6)
#define TB_MOVEBUTTON                                           (WM_USER + 82)
#define TB_PAGEDOWN                                             3
#define TB_PAGEUP                                               2
#define TB_PRESSBUTTON                                          (WM_USER + 3)
#define TB_REPLACEBITMAP                                        (WM_USER + 46)
#define TB_SAVERESTORE                                          (WM_USER + 26)
#define TB_SETANCHORHIGHLIGHT                                   (WM_USER + 73)
#define TB_SETBITMAPSIZE                                        (WM_USER + 32)
#define TB_SETBUTTONINFO                                        (WM_USER + 66)
#define TB_SETBUTTONSIZE                                        (WM_USER + 31)
#define TB_SETBUTTONWIDTH                                       (WM_USER + 59)
#define TB_SETCMDID                                             (WM_USER + 42)
#define TB_SETCOLORSCHEME                                       CCM_SETCOLORSCHEME
#define TB_SETDISABLEDIMAGELIST                                 (WM_USER + 54)
#define TB_SETDRAWTEXTFLAGS                                     (WM_USER + 70)
#define TB_SETEXTENDEDSTYLE                                     (WM_USER + 84)
#define TB_SETHOTIMAGELIST                                      (WM_USER + 52)
#define TB_SETHOTITEM                                           (WM_USER + 72)
#define TB_SETIMAGELIST                                         (WM_USER + 48)
#define TB_SETINDENT                                            (WM_USER + 47)
#define TB_SETINSERTMARK                                        (WM_USER + 80)
#define TB_SETINSERTMARKCOLOR                                   (WM_USER + 88)
#define TB_SETMAXTEXTROWS                                       (WM_USER + 60)
#define TB_SETMETRICS                                           (WM_USER + 102)
#define TB_SETPADDING                                           (WM_USER + 87)
#define TB_SETPARENT                                            (WM_USER + 37)
#define TB_SETROWS                                              (WM_USER + 39)
#define TB_SETSTATE                                             (WM_USER + 17)
#define TB_SETSTYLE                                             (WM_USER + 56)
#define TB_SETTOOLTIPS                                          (WM_USER + 36)
#define TB_SETUNICODEFORMAT                                     CCM_SETUNICODEFORMAT
#define TB_SETWINDOWTHEME                                       CCM_SETWINDOWTHEME
#define TB_THUMBPOSITION                                        4
#define TB_THUMBTRACK                                           5
#define TB_TOP                                                  6
#define TBBF_LARGE                                              0x01
#define TBCD_CHANNEL                                            0x03
#define TBCD_THUMB                                              0x02
#define TBCD_TICS                                               0x01
#define TBCDRF_BLENDICON                                        0x0200000
#define TBCDRF_HILITEHOTTRACK                                   0x020000
#define TBCDRF_NOBACKGROUND                                     0x0400000
#define TBCDRF_NOEDGES                                          0x010000
#define TBCDRF_NOETCHEDEFFECT                                   0x100000
#define TBCDRF_NOMARK                                           0x080000
#define TBCDRF_NOOFFSET                                         0x040000
#define TBDDRET_DEFAULT                                         0
#define TBDDRET_NODEFAULT                                       1
#define TBDDRET_TREATPRESSED                                    2
#define TBIF_BYINDEX                                            0x80000000
#define TBIF_COMMAND                                            0x20
#define TBIF_IMAGE                                              0x01
#define TBIF_LPARAM                                             0x10
#define TBIF_SIZE                                               0x040
#define TBIF_STATE                                              0x04
#define TBIF_STYLE                                              0x08
#define TBIF_TEXT                                               0x02
#define TBIMHT_AFTER                                            0x01
#define TBIMHT_BACKGROUND                                       0x02
#define TBM_CLEARSEL                                            (WM_USER+19)
#define TBM_CLEARTICS                                           (WM_USER+9)
#define TBM_GETBUDDY                                            (WM_USER+33)
#define TBM_GETCHANNELRECT                                      (WM_USER+26)
#define TBM_GETLINESIZE                                         (WM_USER+24)
#define TBM_GETNUMTICS                                          (WM_USER+16)
#define TBM_GETPAGESIZE                                         (WM_USER+22)
#define TBM_GETPOS                                              (WM_USER)
#define TBM_GETPTICS                                            (WM_USER+14)
#define TBM_GETRANGEMAX                                         (WM_USER+2)
#define TBM_GETRANGEMIN                                         (WM_USER+1)
#define TBM_GETSELEND                                           (WM_USER+18)
#define TBM_GETSELSTART                                         (WM_USER+17)
#define TBM_GETTHUMBLENGTH                                      (WM_USER+28)
#define TBM_GETTHUMBRECT                                        (WM_USER+25)
#define TBM_GETTIC                                              (WM_USER+3)
#define TBM_GETTICPOS                                           (WM_USER+15)
#define TBM_GETTOOLTIPS                                         (WM_USER+30)
#define TBM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define TBM_SETBUDDY                                            (WM_USER+32)
#define TBM_SETLINESIZE                                         (WM_USER+23)
#define TBM_SETPAGESIZE                                         (WM_USER+21)
#define TBM_SETPOS                                              (WM_USER+5)
#define TBM_SETRANGE                                            (WM_USER+6)
#define TBM_SETRANGEMAX                                         (WM_USER+8)
#define TBM_SETRANGEMIN                                         (WM_USER+7)
#define TBM_SETSEL                                              (WM_USER+10)
#define TBM_SETSELEND                                           (WM_USER+12)
#define TBM_SETSELSTART                                         (WM_USER+11)
#define TBM_SETTHUMBLENGTH                                      (WM_USER+27)
#define TBM_SETTIC                                              (WM_USER+4)
#define TBM_SETTICFREQ                                          (WM_USER+20)
#define TBM_SETTIPSIDE                                          (WM_USER+31)
#define TBM_SETTOOLTIPS                                         (WM_USER+29)
#define TBM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define TBMF_BARPAD                                             0x02
#define TBMF_BUTTONSPACING                                      0x04
#define TBMF_PAD                                                0x01
#define TBN_BEGINADJUST                                         (TBN_FIRST-3)
#define TBN_BEGINDRAG                                           (TBN_FIRST-1)
#define TBN_CUSTHELP                                            (TBN_FIRST-9)
#define TBN_DELETINGBUTTON                                      (TBN_FIRST - 15)
#define TBN_DRAGOUT                                             (TBN_FIRST - 14)
#define TBN_DROPDOWN                                            (TBN_FIRST - 10)
#define TBN_ENDADJUST                                           (TBN_FIRST-4)
#define TBN_ENDDRAG                                             (TBN_FIRST-2)
#define TBN_FIRST                                               dwminus(700)
#define TBN_GETBUTTONINFO                                       (TBN_FIRST-0)
#define TBN_GETDISPINFO                                         (TBN_FIRST - 16)
#define TBN_GETINFOTIP                                          (TBN_FIRST - 18)
#define TBN_GETOBJECT                                           (TBN_FIRST - 12)
#define TBN_HOTITEMCHANGE                                       (TBN_FIRST - 13)
#define TBN_INITCUSTOMIZE                                       (TBN_FIRST - 23)
#define TBN_LAST                                                dwminus(720)
#define TBN_QUERYDELETE                                         (TBN_FIRST-7)
#define TBN_QUERYINSERT                                         (TBN_FIRST-6)
#define TBN_RESET                                               (TBN_FIRST-5)
#define TBN_RESTORE                                             (TBN_FIRST - 21)
#define TBN_SAVE                                                (TBN_FIRST - 22)
#define TBN_TOOLBARCHANGE                                       (TBN_FIRST-8)
#define TBNF_DI_SETITEM                                         0x10000000
#define TBNF_IMAGE                                              0x01
#define TBNF_TEXT                                               0x02
#define TBNRF_ENDCUSTOMIZE                                      0x02
#define TBNRF_HIDEHELP                                          0x01
#define TBS_AUTOTICKS                                           0x01
#define TBS_BOTH                                                0x08
#define TBS_BOTTOM                                              0
#define TBS_DOWNISLEFT                                          0x0400
#define TBS_ENABLESELRANGE                                      0x20
#define TBS_FIXEDLENGTH                                         0x040
#define TBS_HORZ                                                0
#define TBS_LEFT                                                0x04
#define TBS_NOTHUMB                                             0x080
#define TBS_NOTICKS                                             0x10
#define TBS_REVERSED                                            0x200
#define TBS_RIGHT                                               0
#define TBS_TOOLTIPS                                            0x0100
#define TBS_TOP                                                 0x04
#define TBS_VERT                                                0x02
#define TBSTATE_CHECKED                                         0x01
#define TBSTATE_ELLIPSES                                        0x40
#define TBSTATE_ENABLED                                         0x04
#define TBSTATE_HIDDEN                                          0x08
#define TBSTATE_INDETERMINATE                                   0x10
#define TBSTATE_MARKED                                          0x80
#define TBSTATE_PRESSED                                         0x02
#define TBSTATE_WRAP                                            0x20
#define TBSTYLE_ALTDRAG                                         0x0400
#define TBSTYLE_AUTOSIZE                                        0x10
#define TBSTYLE_BUTTON                                          0
#define TBSTYLE_CHECK                                           0x02
#define TBSTYLE_CHECKGROUP                                      nOr(TBSTYLE_GROUP , TBSTYLE_CHECK)
#define TBSTYLE_CUSTOMERASE                                     0x2000
#define TBSTYLE_DROPDOWN                                        0x08
#define TBSTYLE_EX_DOUBLEBUFFER                                 0x080
#define TBSTYLE_EX_DRAWDDARROWS                                 0x01
#define TBSTYLE_EX_HIDECLIPPEDBUTTONS                           0x10
#define TBSTYLE_EX_MIXEDBUTTONS                                 0x08
#define TBSTYLE_FLAT                                            0x0800
#define TBSTYLE_GROUP                                           0x04
#define TBSTYLE_LIST                                            0x1000
#define TBSTYLE_NOPREFIX                                        0x20
#define TBSTYLE_REGISTERDROP                                    0x4000
#define TBSTYLE_SEP                                             0x01
#define TBSTYLE_TOOLTIPS                                        0x0100
#define TBSTYLE_TRANSPARENT                                     0x8000
#define TBSTYLE_WRAPABLE                                        0x200
#define TBTS_BOTTOM                                             2
#define TBTS_LEFT                                               1
#define TBTS_RIGHT                                              3
#define TBTS_TOP                                                0
//#define TC_HITTESTINFO                                          TCHITTESTINFO
//#define TC_ITEM                                                 TCITEM
//#define TC_ITEMHEADER                                           TCITEMHEADER
//#define TCHITTESTINFO                                           TC_HITTESTINFO
#define TCHT_NOWHERE                                            0x01
#define TCHT_ONITEM                                             nOr(TCHT_ONITEMICON , TCHT_ONITEMLABEL)
#define TCHT_ONITEMICON                                         0x02
#define TCHT_ONITEMLABEL                                        0x04
#define TCIF_IMAGE                                              0x02
#define TCIF_PARAM                                              0x08
#define TCIF_RTLREADING                                         0x04
#define TCIF_STATE                                              0x10
#define TCIF_TEXT                                               0x01
#define TCIS_BUTTONPRESSED                                      0x01
#define TCIS_HIGHLIGHTED                                        0x02
// #define TCITEM                                                  TC_ITEM
// #define TCITEMHEADER                                            TC_ITEMHEADER
#define TCM_ADJUSTRECT                                          (TCM_FIRST + 40)
#define TCM_DELETEALLITEMS                                      (TCM_FIRST + 9)
#define TCM_DELETEITEM                                          (TCM_FIRST + 8)
#define TCM_DESELECTALL                                         (TCM_FIRST + 50)
#define TCM_FIRST                                               0x1300
#define TCM_GETCURFOCUS                                         (TCM_FIRST + 47)
#define TCM_GETCURSEL                                           (TCM_FIRST + 11)
#define TCM_GETEXTENDEDSTYLE                                    (TCM_FIRST + 53)
#define TCM_GETIMAGELIST                                        (TCM_FIRST + 2)
#define TCM_GETITEM                                             (TCM_FIRST + 5)
#define TCM_GETITEMCOUNT                                        (TCM_FIRST + 4)
#define TCM_GETITEMRECT                                         (TCM_FIRST + 10)
#define TCM_GETROWCOUNT                                         (TCM_FIRST + 44)
#define TCM_GETTOOLTIPS                                         (TCM_FIRST + 45)
#define TCM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define TCM_HIGHLIGHTITEM                                       (TCM_FIRST + 51)
#define TCM_HITTEST                                             (TCM_FIRST + 13)
#define TCM_INSERTITEM                                          (TCM_FIRST + 7)
#define TCM_REMOVEIMAGE                                         (TCM_FIRST + 42)
#define TCM_SETCURFOCUS                                         (TCM_FIRST + 48)
#define TCM_SETCURSEL                                           (TCM_FIRST + 12)
#define TCM_SETEXTENDEDSTYLE                                    (TCM_FIRST + 52)
#define TCM_SETIMAGELIST                                        (TCM_FIRST + 3)
#define TCM_SETITEM                                             (TCM_FIRST + 6)
#define TCM_SETITEMEXTRA                                        (TCM_FIRST + 14)
#define TCM_SETITEMSIZE                                         (TCM_FIRST + 41)
#define TCM_SETMINTABWIDTH                                      (TCM_FIRST + 49)
#define TCM_SETPADDING                                          (TCM_FIRST + 43)
#define TCM_SETTOOLTIPS                                         (TCM_FIRST + 46)
#define TCM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define TCN_FIRST                                               dwMinus(550)
#define TCN_FOCUSCHANGE                                         (TCN_FIRST - 4)
#define TCN_GETOBJECT                                           (TCN_FIRST - 3)
#define TCN_KEYDOWN                                             (TCN_FIRST - 0)
#define TCN_LAST                                                dwMinus(580)
#define TCN_SELCHANGE                                           (TCN_FIRST - 1)
#define TCN_SELCHANGING                                         (TCN_FIRST - 2)
#define TCS_BOTTOM                                              0x02
#define TCS_BUTTONS                                             0x0100
#define TCS_EX_FLATSEPARATORS                                   0x01
#define TCS_EX_REGISTERDROP                                     0x02
#define TCS_FIXEDWIDTH                                          0x0400
#define TCS_FLATBUTTONS                                         0x08
#define TCS_FOCUSNEVER                                          0x8000
#define TCS_FOCUSONBUTTONDOWN                                   0x1000
#define TCS_FORCEICONLEFT                                       0x10
#define TCS_FORCELABELLEFT                                      0x20
#define TCS_HOTTRACK                                            0x040
#define TCS_MULTILINE                                           0x200
#define TCS_MULTISELECT                                         0x04
#define TCS_OWNERDRAWFIXED                                      0x2000
#define TCS_RAGGEDRIGHT                                         0x0800
#define TCS_RIGHT                                               0x02
#define TCS_RIGHTJUSTIFY                                        0
#define TCS_SCROLLOPPOSITE                                      0x01
#define TCS_SINGLELINE                                          0
#define TCS_TABS                                                0
#define TCS_TOOLTIPS                                            0x4000
#define TCS_VERTICAL                                            0x080
#define TOOLBARCLASSNAME                                        "ToolbarWindow32"
//#define TOOLINFO                                                TTTOOLINFO
#define TOOLTIPS_CLASS                                          "tooltips_class32"
//#define TOOLTIPTEXT                                             NMTTDISPINFO
#define TRACKBAR_CLASS                                          "msctls_trackbar32"
#define TTDT_AUTOMATIC                                          0
#define TTDT_AUTOPOP                                            2
#define TTDT_INITIAL                                            3
#define TTDT_RESHOW                                             1
#define TTF_ABSOLUTE                                            0x080
#define TTF_CENTERTIP                                           0x02
#define TTF_DI_SETITEM                                          0x8000
#define TTF_IDISHWND                                            0x01
#define TTF_PARSELINKS                                          0x1000
#define TTF_RTLREADING                                          0x04
#define TTF_SUBCLASS                                            0x10
#define TTF_TRACK                                               0x20
#define TTF_TRANSPARENT                                         0x0100
#define TTI_ERROR                                               3
#define TTI_INFO                                                1
#define TTI_NONE                                                0
#define TTI_WARNING                                             2
#define TTM_ACTIVATE                                            (WM_USER + 1)
#define TTM_ADDTOOL                                             (WM_USER + 4)
#define TTM_ADJUSTRECT                                          (WM_USER + 31)
#define TTM_DELTOOL                                             (WM_USER + 5)
#define TTM_ENUMTOOLS                                           (WM_USER +14)
#define TTM_GETBUBBLESIZE                                       (WM_USER + 30)
#define TTM_GETCURRENTTOOL                                      (WM_USER + 15)
#define TTM_GETDELAYTIME                                        (WM_USER + 21)
#define TTM_GETMARGIN                                           (WM_USER + 27)
#define TTM_GETMAXTIPWIDTH                                      (WM_USER + 25)
#define TTM_GETTEXT                                             (WM_USER +11)
#define TTM_GETTIPBKCOLOR                                       (WM_USER + 22)
#define TTM_GETTIPTEXTCOLOR                                     (WM_USER + 23)
#define TTM_GETTITLE                                            (WM_USER + 35)
#define TTM_GETTOOLCOUNT                                        (WM_USER +13)
#define TTM_GETTOOLINFO                                         (WM_USER + 8)
#define TTM_HITTEST                                             (WM_USER +10)
#define TTM_NEWTOOLRECT                                         (WM_USER + 6)
#define TTM_POP                                                 (WM_USER + 28)
#define TTM_POPUP                                               (WM_USER + 34)
#define TTM_RELAYEVENT                                          (WM_USER + 7)
#define TTM_SETDELAYTIME                                        (WM_USER + 3)
#define TTM_SETMARGIN                                           (WM_USER + 26)
#define TTM_SETMAXTIPWIDTH                                      (WM_USER + 24)
#define TTM_SETTIPBKCOLOR                                       (WM_USER + 19)
#define TTM_SETTIPTEXTCOLOR                                     (WM_USER + 20)
#define TTM_SETTITLE                                            (WM_USER + 32)
#define TTM_SETTOOLINFO                                         (WM_USER + 9)
#define TTM_SETWINDOWTHEME                                      CCM_SETWINDOWTHEME
#define TTM_TRACKACTIVATE                                       (WM_USER + 17)
#define TTM_TRACKPOSITION                                       (WM_USER + 18)
#define TTM_UPDATE                                              (WM_USER + 29)
#define TTM_UPDATETIPTEXT                                       (WM_USER +12)
#define TTM_WINDOWFROMPOINT                                     (WM_USER + 16)
#define TTN_FIRST                                               dwMinus(520)
#define TTN_GETDISPINFO                                         (TTN_FIRST - 0)
#define TTN_LAST                                                dwMinus(549)
#define TTN_LINKCLICK                                           (TTN_FIRST - 3)
#define TTN_NEEDTEXT                                            TTN_GETDISPINFO
#define TTN_POP                                                 (TTN_FIRST - 2)
#define TTN_SHOW                                                (TTN_FIRST - 1)
#define TTS_ALWAYSTIP                                           0x01
#define TTS_BALLOON                                             0x40
#define TTS_CLOSE                                               0x80
#define TTS_NOANIMATE                                           0x10
#define TTS_NOFADE                                              0x20
#define TTS_NOPREFIX                                            0x02
//#define TTTOOLINFO                                              TOOLINFO
//#define TV_DISPINFO                                             NMTVDISPINFO
#define TV_FIRST                                                0x1100
//#define TV_HITTESTINFO                                          TVHITTESTINFO
//#define TV_INSERTSTRUCT                                         TVINSERTSTRUCT
//#define TV_ITEM                                                 TVITEM
//#define TV_KEYDOWN                                              NMTVKEYDOWN
//#define TV_SORTCB                                               TVSORTCB
#define TVC_BYKEYBOARD                                          0x02
#define TVC_BYMOUSE                                             0x01
#define TVC_UNKNOWN                                             0
#define TVCDRF_NOIMAGES                                         0x010000
#define TVE_COLLAPSE                                            0x01
#define TVE_COLLAPSERESET                                       0x8000
#define TVE_EXPAND                                              0x02
#define TVE_EXPANDPARTIAL                                       0x4000
#define TVE_TOGGLE                                              0x03
#define TVGN_CARET                                              0x09
#define TVGN_CHILD                                              0x04
#define TVGN_DROPHILITE                                         0x08
#define TVGN_FIRSTVISIBLE                                       0x05
#define TVGN_LASTVISIBLE                                        0x0A
#define TVGN_NEXT                                               0x01
#define TVGN_NEXTVISIBLE                                        0x06
#define TVGN_PARENT                                             0x03
#define TVGN_PREVIOUS                                           0x02
#define TVGN_PREVIOUSVISIBLE                                    0x07
#define TVGN_ROOT                                               0
// #define TVHITTESTINFO                                           TV_HITTESTINFO
#define TVHT_ABOVE                                              0x0100
#define TVHT_BELOW                                              0x200
#define TVHT_NOWHERE                                            0x01
#define TVHT_ONITEM                                             nOr(TVHT_ONITEMICON ,TVHT_ONITEMLABEL ,TVHT_ONITEMSTATEICON)
#define TVHT_ONITEMBUTTON                                       0x10
#define TVHT_ONITEMICON                                         0x02
#define TVHT_ONITEMINDENT                                       0x08
#define TVHT_ONITEMLABEL                                        0x04
#define TVHT_ONITEMRIGHT                                        0x20
#define TVHT_ONITEMSTATEICON                                    0x040
#define TVHT_TOLEFT                                             0x0800
#define TVHT_TORIGHT                                            0x0400
#define TVI_FIRST                                               dwminus(0x0FFFF)
#define TVI_LAST                                                dwminus(0x0FFFE)
#define TVI_ROOT                                                dwminus(0x10000)
#define TVI_SORT                                                dwminus(0x0FFFD)
#define TVIF_CHILDREN                                           0x040
#define TVIF_DI_SETITEM                                         0x1000
#define TVIF_HANDLE                                             0x10
#define TVIF_IMAGE                                              0x02
#define TVIF_INTEGRAL                                           0x080
#define TVIF_PARAM                                              0x04
#define TVIF_SELECTEDIMAGE                                      0x20
#define TVIF_STATE                                              0x08
#define TVIF_TEXT                                               0x01
// #define TVINSERTSTRUCT                                          TV_INSERTSTRUCT
#define TVIS_BOLD                                               0x10
#define TVIS_CUT                                                0x04
#define TVIS_DROPHILITED                                        0x08
#define TVIS_EXPANDED                                           0x20
#define TVIS_EXPANDEDONCE                                       0x040
#define TVIS_EXPANDPARTIAL                                      0x080
#define TVIS_OVERLAYMASK                                        0x0F00
#define TVIS_SELECTED                                           0x02
#define TVIS_STATEIMAGEMASK                                     0xF000
#define TVIS_USERMASK                                           0xF000
// #define TVITEM                                                  TV_ITEM
#define TVM_CREATEDRAGIMAGE                                     (TV_FIRST + 18)
#define TVM_EDITLABEL                                           (TV_FIRST + 14)
#define TVM_ENDEDITLABELNOW                                     (TV_FIRST + 22)
#define TVM_ENSUREVISIBLE                                       (TV_FIRST + 20)
#define TVM_EXPAND                                              (TV_FIRST + 2)
#define TVM_GETBKCOLOR                                          (TV_FIRST + 31)
#define TVM_GETCOUNT                                            (TV_FIRST + 5)
#define TVM_GETEDITCONTROL                                      (TV_FIRST + 15)
#define TVM_GETIMAGELIST                                        (TV_FIRST + 8)
#define TVM_GETINDENT                                           (TV_FIRST + 6)
#define TVM_GETINSERTMARKCOLOR                                  (TV_FIRST + 38)
#define TVM_GETISEARCHSTRING                                    (TV_FIRST + 23)
#define TVM_GETITEM                                             (TV_FIRST + 12)
#define TVM_GETITEMHEIGHT                                       (TV_FIRST + 28)
#define TVM_GETITEMRECT                                         (TV_FIRST + 4)
#define TVM_GETITEMSTATE                                        (TV_FIRST + 39)
#define TVM_GETLINECOLOR                                        (TV_FIRST + 41)
#define TVM_GETNEXTITEM                                         (TV_FIRST + 10)
#define TVM_GETSCROLLTIME                                       (TV_FIRST + 34)
#define TVM_GETTEXTCOLOR                                        (TV_FIRST + 32)
#define TVM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define TVM_GETVISIBLECOUNT                                     (TV_FIRST + 16)
#define TVM_HITTEST                                             (TV_FIRST + 17)
#define TVM_INSERTITEM                                          (TV_FIRST + 0)
#define TVM_DELETEITEM                                          (TV_FIRST + 1 )
#define TVM_MAPACCIDTOHTREEITEM                                 (TV_FIRST + 42)
#define TVM_MAPHTREEITEMTOACCID                                 (TV_FIRST + 43)
#define TVM_SELECTITEM                                          (TV_FIRST + 11)
#define TVM_SETBKCOLOR                                          (TV_FIRST + 29)
#define TVM_SETIMAGELIST                                        (TV_FIRST + 9)
#define TVM_SETINDENT                                           (TV_FIRST + 7)
#define TVM_SETINSERTMARK                                       (TV_FIRST + 26)
#define TVM_SETINSERTMARKCOLOR                                  (TV_FIRST + 37)
#define TVM_SETITEM                                             (TV_FIRST + 13)
#define TVM_SETITEMHEIGHT                                       (TV_FIRST + 27)
#define TVM_SETLINECOLOR                                        (TV_FIRST + 40)
#define TVM_SETSCROLLTIME                                       (TV_FIRST + 33)
#define TVM_SETTEXTCOLOR                                        (TV_FIRST + 30)
#define TVM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define TVM_SORTCHILDREN                                        (TV_FIRST + 19)
#define TVM_SORTCHILDRENCB                                      (TV_FIRST + 21)
#define TVN_BEGINDRAG                                           (TVN_FIRST-7)
#define TVN_BEGINLABELEDIT                                      (TVN_FIRST-10)
#define TVN_BEGINRDRAG                                          (TVN_FIRST-8)
#define TVN_DELETEITEM                                          (TVN_FIRST-9)
#define TVN_ENDLABELEDIT                                        (TVN_FIRST-11)
#define TVN_FIRST                                               dwMinus(400)
#define TVN_GETDISPINFO                                         (TVN_FIRST-3)
#define TVN_GETINFOTIP                                          (TVN_FIRST-13)
#define TVN_ITEMEXPANDED                                        (TVN_FIRST-6)
#define TVN_ITEMEXPANDING                                       (TVN_FIRST-5)
#define TVN_KEYDOWN                                             (TVN_FIRST-12)
#define TVN_LAST                                                dwMinus(499)
#define TVN_SELCHANGED                                          (TVN_FIRST-2)
#define TVN_SELCHANGING                                         (TVN_FIRST-1)
#define TVN_SETDISPINFO                                         (TVN_FIRST-4)
#define TVN_SINGLEEXPAND                                        (TVN_FIRST-15)
#define TVNRET_DEFAULT                                          0
#define TVNRET_SKIPNEW                                          2

#define TVN_ITEMCHANGINGA                                       (TVN_FIRST-16)
#define TVN_ITEMCHANGINGW                                       (TVN_FIRST-17)
#define TVN_ITEMCHANGING                                        TVN_ITEMCHANGINGA
#define TVN_ITEMCHANGEDA                                        (TVN_FIRST-18)
#define TVN_ITEMCHANGEDW                                        (TVN_FIRST-19)
#define TVN_ITEMCHANGED                                         TVN_ITEMCHANGEDA
#define TVN_ASYNCDRAW                                           (TVN_FIRST-20)

#define TVNRET_SKIPOLD                                          1
#define TVS_CHECKBOXES                                          0x0100
#define TVS_DISABLEDRAGDROP                                     0x10
#define TVS_EDITLABELS                                          0x08
#define TVS_FULLROWSELECT                                       0x1000
#define TVS_HASBUTTONS                                          0x01
#define TVS_HASLINES                                            0x02
#define TVS_INFOTIP                                             0x0800
#define TVS_LINESATROOT                                         0x04
#define TVS_NOHSCROLL                                           0x8000
#define TVS_NONEVENHEIGHT                                       0x4000
#define TVS_NOSCROLL                                            0x2000
#define TVS_NOTOOLTIPS                                          0x080
#define TVS_RTLREADING                                          0x040
#define TVS_SHOWSELALWAYS                                       0x20
#define TVS_SINGLEEXPAND                                        0x0400
#define TVS_TRACKSELECT                                         0x200
#define TVSI_NOSINGLEEXPAND                                     0x8000
#define TVSIL_NORMAL                                            0
#define TVSIL_STATE                                             2
#define TVSORTCB                                                TV_SORTCB
#define UD_MAXVAL                                               0x7fff
#define UD_MINVAL                                               dwminus( 0x7fff )
#define UDM_GETACCEL                                            (WM_USER+108)
#define UDM_GETBASE                                             (WM_USER+110)
#define UDM_GETBUDDY                                            (WM_USER+106)
#define UDM_GETPOS                                              (WM_USER+104)
#define UDM_GETPOS32                                            (WM_USER+114)
#define UDM_GETRANGE                                            (WM_USER+102)
#define UDM_GETRANGE32                                          (WM_USER+112)
#define UDM_GETUNICODEFORMAT                                    CCM_GETUNICODEFORMAT
#define UDM_SETACCEL                                            (WM_USER+107)
#define UDM_SETBASE                                             (WM_USER+109)
#define UDM_SETBUDDY                                            (WM_USER+105)
#define UDM_SETPOS                                              (WM_USER+103)
#define UDM_SETPOS32                                            (WM_USER+113)
#define UDM_SETRANGE                                            (WM_USER+101)
#define UDM_SETRANGE32                                          (WM_USER+111)
#define UDM_SETUNICODEFORMAT                                    CCM_SETUNICODEFORMAT
#define UDN_DELTAPOS                                            (UDN_FIRST - 1)
#define UDN_FIRST                                               dwminus(721)
#define UDN_LAST                                                dwminus(740)
#define UDS_ALIGNLEFT                                           0x08
#define UDS_ALIGNRIGHT                                          0x04
#define UDS_ARROWKEYS                                           0x20
#define UDS_AUTOBUDDY                                           0x10
#define UDS_HORZ                                                0x040
#define UDS_HOTTRACK                                            0x0100
#define UDS_NOTHOUSANDS                                         0x080
#define UDS_SETBUDDYINT                                         0x02
#define UDS_WRAP                                                0x01
#define UPDOWN_CLASS                                            "msctls_updown32"
#define VIEW_DETAILS                                            3
#define VIEW_LARGEICONS                                         0
#define VIEW_LIST                                               2
#define VIEW_NETCONNECT                                         9
#define VIEW_NETDISCONNECT                                      10
#define VIEW_NEWFOLDER                                          11
#define VIEW_PARENTFOLDER                                       8
#define VIEW_SMALLICONS                                         1
#define VIEW_SORTDATE                                           6
#define VIEW_SORTNAME                                           4
#define VIEW_SORTSIZE                                           5
#define VIEW_SORTTYPE                                           7
#define VIEW_VIEWMENU                                           12
#define WC_BUTTON                                               "Button"
#define WC_COMBOBOX                                             "ComboBox"
#define WC_COMBOBOXEX                                           "ComboBoxEx32"
#define WC_EDIT                                                 "Edit"
#define WC_HEADER                                               "SysHeader32"
#define WC_IPADDRESS                                            "SysIPAddress32"
#define WC_LINK                                                 "SysLink"
#define WC_LISTBOX                                              "ListBox"
#define WC_LISTVIEW                                             "SysListView32"
#define WC_NATIVEFONTCTL                                        "NativeFontCtl"
#define WC_PAGESCROLLER                                         "SysPager"
#define WC_SCROLLBAR                                            "ScrollBar"
#define WC_STATIC                                               "Static"
#define WC_TABCONTROL                                           "SysTabControl32"
#define WC_TREEVIEW                                             "SysTreeView32"
#define WMN_FIRST                                               dwminus(1000)
#define WMN_LAST                                                dwminus(1200)
#define WSB_PROP_CXHSCROLL                                      0x02
#define WSB_PROP_CXHTHUMB                                       0x10
#define WSB_PROP_CXVSCROLL                                      0x08
#define WSB_PROP_CYHSCROLL                                      0x04
#define WSB_PROP_CYVSCROLL                                      0x01
#define WSB_PROP_CYVTHUMB                                       0x20
#define WSB_PROP_HBKGCOLOR                                      0x080
#define WSB_PROP_HSTYLE                                         0x200
#define WSB_PROP_MASK                                           0x0FFF
#define WSB_PROP_PALETTE                                        0x0800
#define WSB_PROP_VBKGCOLOR                                      0x040
#define WSB_PROP_VSTYLE                                         0x0100
#define WSB_PROP_WINSTYLE                                       0x0400
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#define LVM_GETGROUPCOUNT         (LVM_FIRST + 152)
#define LVM_GETGROUPINFOBYINDEX         (LVM_FIRST + 153)
#define LVM_GETGROUPRECT               (LVM_FIRST + 98)
#define LVM_GETGROUPSTATE               (LVM_FIRST + 92)
#define LVM_GETFOCUSEDGROUP             (LVM_FIRST + 93)
#define LVM_ISITEMVISIBLE    (LVM_FIRST + 182)
#define LVSIL_GROUPHEADER       3
#define LVM_GETEMPTYTEXT (LVM_FIRST + 204)
#define LVM_GETFOOTERRECT (LVM_FIRST + 205)
#define LVM_GETFOOTERINFO (LVM_FIRST + 206)
#define LVM_GETFOOTERITEMRECT (LVM_FIRST + 207)
#define LVM_GETFOOTERITEM (LVM_FIRST + 208)
#define LVM_GETITEMINDEXRECT    (LVM_FIRST + 209)
#define LVM_SETITEMINDEXSTATE   (LVM_FIRST + 210)
#define LVM_GETNEXTITEMINDEX    (LVM_FIRST + 211)
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_COMMCTRL_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
