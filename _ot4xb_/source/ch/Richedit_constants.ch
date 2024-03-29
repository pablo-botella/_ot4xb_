



// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_RICHEDIT_CONSTANTS_
#define _XB_RICHEDIT_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define  cchTextLimitDefault                           32767
#define  EM_CANPASTE                                   (WM_USER + 50)
#define  EM_DISPLAYBAND                                (WM_USER + 51)
#define  EM_EXGETSEL                                   (WM_USER + 52)
#define  EM_EXLIMITTEXT                                (WM_USER + 53)
#define  EM_EXLINEFROMCHAR                             (WM_USER + 54)
#define  EM_EXSETSEL                                   (WM_USER + 55)
#define  EM_FINDTEXT                                   (WM_USER + 56)
#define  EM_FORMATRANGE                                (WM_USER + 57)
#define  EM_GETCHARFORMAT                              (WM_USER + 58)
#define  EM_GETEVENTMASK                               (WM_USER + 59)
#define  EM_GETOLEINTERFACE                            (WM_USER + 60)
#define  EM_GETPARAFORMAT                              (WM_USER + 61)
#define  EM_GETSELTEXT                                 (WM_USER + 62)
#define  EM_HIDESELECTION                              (WM_USER + 63)
#define  EM_PASTESPECIAL                               (WM_USER + 64)
#define  EM_REQUESTRESIZE                              (WM_USER + 65)
#define  EM_SELECTIONTYPE                              (WM_USER + 66)
#define  EM_SETBKGNDCOLOR                              (WM_USER + 67)
#define  EM_SETCHARFORMAT                              (WM_USER + 68)
#define  EM_SETEVENTMASK                               (WM_USER + 69)
#define  EM_SETOLECALLBACK                             (WM_USER + 70)
#define  EM_SETPARAFORMAT                              (WM_USER + 71)
#define  EM_SETTARGETDEVICE                            (WM_USER + 72)
#define  EM_STREAMIN                                   (WM_USER + 73)
#define  EM_STREAMOUT                                  (WM_USER + 74)
#define  EM_GETTEXTRANGE                               (WM_USER + 75)
#define  EM_FINDWORDBREAK                              (WM_USER + 76)
#define  EM_SETOPTIONS                                 (WM_USER + 77)
#define  EM_GETOPTIONS                                 (WM_USER + 78)
#define  EM_FINDTEXTEX                                 (WM_USER + 79)
#define  EM_GETWORDBREAKPROCEX                         (WM_USER + 80)
#define  EM_SETWORDBREAKPROCEX                         (WM_USER + 81)
#define  EM_SETUNDOLIMIT                               (WM_USER + 82)
#define  EM_REDO                                       (WM_USER + 84)
#define  EM_CANREDO                                    (WM_USER + 85)
#define  EM_GETUNDONAME                                (WM_USER + 86)
#define  EM_GETREDONAME                                (WM_USER + 87)
#define  EM_STOPGROUPTYPING                            (WM_USER + 88)
#define  EM_SETTEXTMODE                                (WM_USER + 89)
#define  EM_GETTEXTMODE                                (WM_USER + 90)
#define  EM_AUTOURLDETECT                              (WM_USER + 91)
#define  EM_GETAUTOURLDETECT                           (WM_USER + 92)
#define  EM_SETPALETTE                                 (WM_USER + 93)
#define  EM_GETTEXTEX                                  (WM_USER + 94)
#define  EM_GETTEXTLENGTHEX                            (WM_USER + 95)
#define  EM_SHOWSCROLLBAR                              (WM_USER + 96)
#define  EM_SETTEXTEX                                  (WM_USER + 97)
#define  EM_SETPUNCTUATION                             (WM_USER + 100)
#define  EM_GETPUNCTUATION                             (WM_USER + 101)
#define  EM_SETWORDWRAPMODE                            (WM_USER + 102)
#define  EM_GETWORDWRAPMODE                            (WM_USER + 103)
#define  EM_SETIMECOLOR                                (WM_USER + 104)
#define  EM_GETIMECOLOR                                (WM_USER + 105)
#define  EM_SETIMEOPTIONS                              (WM_USER + 106)
#define  EM_GETIMEOPTIONS                              (WM_USER + 107)
#define  EM_CONVPOSITION                               (WM_USER + 108)
#define  EM_SETLANGOPTIONS                             (WM_USER + 120)
#define  EM_GETLANGOPTIONS                             (WM_USER + 121)
#define  EM_GETIMECOMPMODE                             (WM_USER + 122)
#define  EM_FINDTEXTW                                  (WM_USER + 123)
#define  EM_FINDTEXTEXW                                (WM_USER + 124)
#define  EM_RECONVERSION                               (WM_USER + 125)
#define  EM_SETIMEMODEBIAS                             (WM_USER + 126)
#define  EM_GETIMEMODEBIAS                             (WM_USER + 127)
#define  EM_SETBIDIOPTIONS                             (WM_USER + 200)
#define  EM_GETBIDIOPTIONS                             (WM_USER + 201)
#define  EM_SETTYPOGRAPHYOPTIONS                       (WM_USER + 202)
#define  EM_GETTYPOGRAPHYOPTIONS                       (WM_USER + 203)
#define  EM_SETEDITSTYLE                               (WM_USER + 204)
#define  EM_GETEDITSTYLE                               (WM_USER + 205)
#define  SES_EMULATESYSEDIT                            1
#define  SES_BEEPONMAXTEXT                             2
#define  SES_EXTENDBACKCOLOR                           4
#define  SES_MAPCPS                                    8
#define  SES_EMULATE10                                 16
#define  SES_USECRLF                                   32
#define  SES_NOXLTSYMBOLRANGE                          32
#define  SES_USEAIMM                                   64
#define  SES_NOIME                                     128
#define  SES_ALLOWBEEPS                                256
#define  SES_UPPERCASE                                 512
#define  SES_LOWERCASE                                 1024
#define  SES_NOINPUTSEQUENCECHK                        2048
#define  SES_BIDI                                      4096
#define  SES_SCROLLONKILLFOCUS                         8192
#define  SES_XLTCRCRLFTOCR                             16384
#define  SES_DRAFTMODE                                 32768
#define  SES_USECTF                                    0x0010000
#define  SES_HIDEGRIDLINES                             0x0020000
#define  SES_USEATFONT                                 0x0040000
#define  SES_CUSTOMLOOK                                0x0080000
#define  SES_LBSCROLLNOTIFY                            0x0100000
#define  SES_CTFALLOWEMBED                             0x0200000
#define  SES_CTFALLOWSMARTTAG                          0x0400000
#define  SES_CTFALLOWPROOFING                          0x0800000
#define  IMF_AUTOKEYBOARD                              0x0001
#define  IMF_AUTOFONT                                  0x0002
#define  IMF_IMECANCELCOMPLETE                         0x0004
#define  IMF_IMEALWAYSSENDNOTIFY                       0x0008
#define  IMF_AUTOFONTSIZEADJUST                        0x0010
#define  IMF_UIFONTS                                   0x0020
#define  IMF_DUALFONT                                  0x0080
#define  ICM_NOTOPEN                                   0x0000
#define  ICM_LEVEL3                                    0x0001
#define  ICM_LEVEL2                                    0x0002
#define  ICM_LEVEL2_5                                  0x0003
#define  ICM_LEVEL2_SUI                                0x0004
#define  ICM_CTF                                       0x0005
#define  TO_ADVANCEDTYPOGRAPHY                         1
#define  TO_SIMPLELINEBREAK                            2
#define  TO_DISABLECUSTOMTEXTOUT                       4
#define  TO_ADVANCEDLAYOUT                             8
#define  EM_OUTLINE                                    (WM_USER + 220)
#define  EM_GETSCROLLPOS                               (WM_USER + 221)
#define  EM_SETSCROLLPOS                               (WM_USER + 222)
#define  EM_SETFONTSIZE                                (WM_USER + 223)
#define  EM_GETZOOM                                    (WM_USER + 224)
#define  EM_SETZOOM                                    (WM_USER + 225)
#define  EM_GETVIEWKIND                                (WM_USER + 226)
#define  EM_SETVIEWKIND                                (WM_USER + 227)
#define  EM_GETPAGE                                    (WM_USER + 228)
#define  EM_SETPAGE                                    (WM_USER + 229)
#define  EM_GETHYPHENATEINFO                           (WM_USER + 230)
#define  EM_SETHYPHENATEINFO                           (WM_USER + 231)
#define  EM_GETPAGEROTATE                              (WM_USER + 235)
#define  EM_SETPAGEROTATE                              (WM_USER + 236)
#define  EM_GETCTFMODEBIAS                             (WM_USER + 237)
#define  EM_SETCTFMODEBIAS                             (WM_USER + 238)
#define  EM_GETCTFOPENSTATUS                           (WM_USER + 240)
#define  EM_SETCTFOPENSTATUS                           (WM_USER + 241)
#define  EM_GETIMECOMPTEXT                             (WM_USER + 242)
#define  EM_ISIME                                      (WM_USER + 243)
#define  EM_GETIMEPROPERTY                             (WM_USER + 244)
#define  EM_GETQUERYRTFOBJ                             (WM_USER + 269)
#define  EM_SETQUERYRTFOBJ                             (WM_USER + 270)
#define  EPR_0                                         0
#define  EPR_270                                       1
#define  EPR_180                                       2
#define  EPR_90                                        3
#define  CTFMODEBIAS_DEFAULT                           0x0000
#define  CTFMODEBIAS_FILENAME                          0x0001
#define  CTFMODEBIAS_NAME                              0x0002
#define  CTFMODEBIAS_READING                           0x0003
#define  CTFMODEBIAS_DATETIME                          0x0004
#define  CTFMODEBIAS_CONVERSATION                      0x0005
#define  CTFMODEBIAS_NUMERIC                           0x0006
#define  CTFMODEBIAS_HIRAGANA                          0x0007
#define  CTFMODEBIAS_KATAKANA                          0x0008
#define  CTFMODEBIAS_HANGUL                            0x0009
#define  CTFMODEBIAS_HALFWIDTHKATAKANA                 0x000A
#define  CTFMODEBIAS_FULLWIDTHALPHANUMERIC             0x000B
#define  CTFMODEBIAS_HALFWIDTHALPHANUMERIC             0x000C
#define  IMF_SMODE_PLAURALCLAUSE                       0x0001
#define  IMF_SMODE_NONE                                0x0002
#define  ICT_RESULTREADSTR                             1
#define  EMO_EXIT                                      0
#define  EMO_ENTER                                     1
#define  EMO_PROMOTE                                   2
#define  EMO_EXPAND                                    3
#define  EMO_MOVESELECTION                             4
#define  EMO_GETVIEWMODE                               5
#define  EMO_EXPANDSELECTION                           0
#define  EMO_EXPANDDOCUMENT                            1
#define  VM_NORMAL                                     4
#define  VM_OUTLINE                                    2
#define  VM_PAGE                                       9
#define  EN_MSGFILTER                                  0x0700
#define  EN_REQUESTRESIZE                              0x0701
#define  EN_SELCHANGE                                  0x0702
#define  EN_DROPFILES                                  0x0703
#define  EN_PROTECTED                                  0x0704
#define  EN_CORRECTTEXT                                0x0705
#define  EN_STOPNOUNDO                                 0x0706
#define  EN_IMECHANGE                                  0x0707
#define  EN_SAVECLIPBOARD                              0x0708
#define  EN_OLEOPFAILED                                0x0709
#define  EN_OBJECTPOSITIONS                            0x070a
#define  EN_LINK                                       0x070b
#define  EN_DRAGDROPDONE                               0x070c
#define  EN_PARAGRAPHEXPANDED                          0x070d
#define  EN_PAGECHANGE                                 0x070e
#define  EN_LOWFIRTF                                   0x070f
#define  EN_ALIGNLTR                                   0x0710
#define  EN_ALIGNRTL                                   0x0711
#define  ENM_NONE                                      0x00000000
#define  ENM_CHANGE                                    0x00000001
#define  ENM_UPDATE                                    0x00000002
#define  ENM_SCROLL                                    0x00000004
#define  ENM_SCROLLEVENTS                              0x00000008
#define  ENM_DRAGDROPDONE                              0x00000010
#define  ENM_PARAGRAPHEXPANDED                         0x00000020
#define  ENM_PAGECHANGE                                0x00000040
#define  ENM_KEYEVENTS                                 0x00010000
#define  ENM_MOUSEEVENTS                               0x00020000
#define  ENM_REQUESTRESIZE                             0x00040000
#define  ENM_SELCHANGE                                 0x00080000
#define  ENM_DROPFILES                                 0x00100000
#define  ENM_PROTECTED                                 0x00200000
#define  ENM_CORRECTTEXT                               0x00400000
#define  ENM_IMECHANGE                                 0x00800000
#define  ENM_LANGCHANGE                                0x01000000
#define  ENM_OBJECTPOSITIONS                           0x02000000
#define  ENM_LINK                                      0x04000000
#define  ENM_LOWFIRTF                                  0x08000000
#define  ES_SAVESEL                                    0x00008000
#define  ES_SUNKEN                                     0x00004000
#define  ES_DISABLENOSCROLL                            0x00002000
#define  ES_SELECTIONBAR                               0x01000000
#define  ES_NOOLEDRAGDROP                              0x00000008
#define  ES_VERTICAL                                   0x00400000
#define  ES_NOIME                                      0x00080000
#define  ES_SELFIME                                    0x00040000
#define  ECO_AUTOWORDSELECTION                         0x00000001
#define  ECO_AUTOVSCROLL                               0x00000040
#define  ECO_AUTOHSCROLL                               0x00000080
#define  ECO_NOHIDESEL                                 0x00000100
#define  ECO_READONLY                                  0x00000800
#define  ECO_WANTRETURN                                0x00001000
#define  ECO_SAVESEL                                   0x00008000
#define  ECO_SELECTIONBAR                              0x01000000
#define  ECO_VERTICAL                                  0x00400000
#define  ECOOP_SET                                     0x0001
#define  ECOOP_OR                                      0x0002
#define  ECOOP_AND                                     0x0003
#define  ECOOP_XOR                                     0x0004
#define  WB_CLASSIFY                                   3
#define  WB_MOVEWORDLEFT                               4
#define  WB_MOVEWORDRIGHT                              5
#define  WB_LEFTBREAK                                  6
#define  WB_RIGHTBREAK                                 7
#define  WB_MOVEWORDPREV                               4
#define  WB_MOVEWORDNEXT                               5
#define  WB_PREVBREAK                                  6
#define  WB_NEXTBREAK                                  7
#define  PC_FOLLOWING                                  1
#define  PC_LEADING                                    2
#define  PC_OVERFLOW                                   3
#define  PC_DELIMITER                                  4
#define  WBF_WORDWRAP                                  0x010
#define  WBF_WORDBREAK                                 0x020
#define  WBF_OVERFLOW                                  0x040
#define  WBF_LEVEL1                                    0x080
#define  WBF_LEVEL2                                    0x100
#define  WBF_CUSTOM                                    0x200
#define  IMF_FORCENONE                                 0x0001
#define  IMF_FORCEENABLE                               0x0002
#define  IMF_FORCEDISABLE                              0x0004
#define  IMF_CLOSESTATUSWINDOW                         0x0008
#define  IMF_VERTICAL                                  0x0020
#define  IMF_FORCEACTIVE                               0x0040
#define  IMF_FORCEINACTIVE                             0x0080
#define  IMF_FORCEREMEMBER                             0x0100
#define  IMF_MULTIPLEEDIT                              0x0400
#define  WBF_CLASS                                     (0x0F)
#define  WBF_ISWHITE                                   (0x10)
#define  WBF_BREAKLINE                                 (0x20)
#define  WBF_BREAKAFTER                                (0x40)
#define  CHARFORMATDELTA                               (CHARFORMAT2():_mc__size_ - CHARFORMAT():_mc__size_)
#define  CFM_BOLD                                      0x00000001
#define  CFM_ITALIC                                    0x00000002
#define  CFM_UNDERLINE                                 0x00000004
#define  CFM_STRIKEOUT                                 0x00000008
#define  CFM_PROTECTED                                 0x00000010
#define  CFM_LINK                                      0x00000020
#define  CFM_SIZE                                      dwfix(0x8000,0x0000) 
#define  CFM_COLOR                                     0x40000000
#define  CFM_FACE                                      0x20000000
#define  CFM_OFFSET                                    0x10000000
#define  CFM_CHARSET                                   0x08000000
#define  CFE_BOLD                                      0x0001
#define  CFE_ITALIC                                    0x0002
#define  CFE_UNDERLINE                                 0x0004
#define  CFE_STRIKEOUT                                 0x0008
#define  CFE_PROTECTED                                 0x0010
#define  CFE_LINK                                      0x0020
#define  CFE_AUTOCOLOR                                 0x40000000
#define  CFM_SMALLCAPS                                 0x0040
#define  CFM_ALLCAPS                                   0x0080
#define  CFM_HIDDEN                                    0x0100
#define  CFM_OUTLINE                                   0x0200
#define  CFM_SHADOW                                    0x0400
#define  CFM_EMBOSS                                    0x0800
#define  CFM_IMPRINT                                   0x1000
#define  CFM_DISABLED                                  0x2000
#define  CFM_REVISED                                   0x4000
#define  CFM_BACKCOLOR                                 0x04000000
#define  CFM_LCID                                      0x02000000
#define  CFM_UNDERLINETYPE                             0x00800000
#define  CFM_WEIGHT                                    0x00400000
#define  CFM_SPACING                                   0x00200000
#define  CFM_KERNING                                   0x00100000
#define  CFM_STYLE                                     0x00080000
#define  CFM_ANIMATION                                 0x00040000
#define  CFM_REVAUTHOR                                 0x00008000
#define  CFE_SUBSCRIPT                                 0x00010000
#define  CFE_SUPERSCRIPT                               0x00020000
#define  CFM_SUBSCRIPT                                 nOr(CFE_SUBSCRIPT,CFE_SUPERSCRIPT)
#define  CFM_SUPERSCRIPT                               CFM_SUBSCRIPT
#define  CFM_EFFECTS                                   nOr(CFM_BOLD,CFM_ITALIC,CFM_UNDERLINE,CFM_COLOR,CFM_STRIKEOUT,CFE_PROTECTED,CFM_LINK)
#define  CFM_ALL                                       nOr(CFM_EFFECTS,CFM_SIZE,CFM_FACE,CFM_OFFSET,CFM_CHARSET)
#define  CFM_EFFECTS2                                  nOr(CFM_EFFECTS,CFM_DISABLED,CFM_SMALLCAPS,CFM_ALLCAPS,CFM_HIDDEN,CFM_OUTLINE,CFM_SHADOW,CFM_EMBOSS,CFM_IMPRINT,CFM_DISABLED,CFM_REVISED,CFM_SUBSCRIPT,CFM_SUPERSCRIPT,CFM_BACKCOLOR)
#define  CFM_ALL2                                      nOr(CFM_ALL,CFM_EFFECTS2,CFM_BACKCOLOR,CFM_LCID,CFM_UNDERLINETYPE,CFM_WEIGHT,CFM_REVAUTHOR,CFM_SPACING,CFM_KERNING,CFM_STYLE,CFM_ANIMATION)
#define  CFE_SMALLCAPS                                 CFM_SMALLCAPS
#define  CFE_ALLCAPS                                   CFM_ALLCAPS
#define  CFE_HIDDEN                                    CFM_HIDDEN
#define  CFE_OUTLINE                                   CFM_OUTLINE
#define  CFE_SHADOW                                    CFM_SHADOW
#define  CFE_EMBOSS                                    CFM_EMBOSS
#define  CFE_IMPRINT                                   CFM_IMPRINT
#define  CFE_DISABLED                                  CFM_DISABLED
#define  CFE_REVISED                                   CFM_REVISED
#define  CFE_AUTOBACKCOLOR                             CFM_BACKCOLOR
#define  CFU_CF1UNDERLINE                              0xFF
#define  CFU_INVERT                                    0xFE
#define  CFU_UNDERLINETHICKLONGDASH                    18
#define  CFU_UNDERLINETHICKDOTTED                      17
#define  CFU_UNDERLINETHICKDASHDOTDOT                  16
#define  CFU_UNDERLINETHICKDASHDOT                     15
#define  CFU_UNDERLINETHICKDASH                        14
#define  CFU_UNDERLINELONGDASH                         13
#define  CFU_UNDERLINEHEAVYWAVE                        12
#define  CFU_UNDERLINEDOUBLEWAVE                       11
#define  CFU_UNDERLINEHAIRLINE                         10
#define  CFU_UNDERLINETHICK                            9
#define  CFU_UNDERLINEWAVE                             8
#define  CFU_UNDERLINEDASHDOTDOT                       7
#define  CFU_UNDERLINEDASHDOT                          6
#define  CFU_UNDERLINEDASH                             5
#define  CFU_UNDERLINEDOTTED                           4
#define  CFU_UNDERLINEDOUBLE                           3
#define  CFU_UNDERLINEWORD                             2
#define  CFU_UNDERLINE                                 1
#define  CFU_UNDERLINENONE                             0
#define  yHeightCharPtsMost                            1638
#define  SCF_SELECTION                                 0x0001
#define  SCF_WORD                                      0x0002
#define  SCF_DEFAULT                                   0x0000
#define  SCF_ALL                                       0x0004
#define  SCF_USEUIRULES                                0x0008
#define  SCF_ASSOCIATEFONT                             0x0010
#define  SCF_NOKBUPDATE                                0x0020
#define  SCF_ASSOCIATEFONT2                            0x0040
#define  SF_TEXT                                       0x0001
#define  SF_RTF                                        0x0002
#define  SF_RTFNOOBJS                                  0x0003
#define  SF_TEXTIZED                                   0x0004
#define  SF_UNICODE                                    0x0010
#define  SF_USECODEPAGE                                0x0020
#define  SF_NCRFORNONASCII                             0x40
#define  SFF_WRITEXTRAPAR                              0x80
#define  SFF_SELECTION                                 0x8000
#define  SFF_PLAINRTF                                  0x4000
#define  SFF_PERSISTVIEWSCALE                          0x2000
#define  SFF_KEEPDOCINFO                               0x1000
#define  SFF_PWD                                       0x0800
#define  SF_RTFVAL                                     0x0700
#define  MAX_TAB_STOPS                                 32
#define  lDefaultTab                                   720
#define  MAX_TABLE_CELLS                               63
#define  PFM_STARTINDENT                               0x00000001
#define  PFM_RIGHTINDENT                               0x00000002
#define  PFM_OFFSET                                    0x00000004
#define  PFM_ALIGNMENT                                 0x00000008
#define  PFM_TABSTOPS                                  0x00000010
#define  PFM_NUMBERING                                 0x00000020
#define  PFM_OFFSETINDENT                              dwfix(0x8000,0x0000)
#define  PFM_SPACEBEFORE                               0x00000040
#define  PFM_SPACEAFTER                                0x00000080
#define  PFM_LINESPACING                               0x00000100
#define  PFM_STYLE                                     0x00000400
#define  PFM_BORDER                                    0x00000800
#define  PFM_SHADING                                   0x00001000
#define  PFM_NUMBERINGSTYLE                            0x00002000
#define  PFM_NUMBERINGTAB                              0x00004000
#define  PFM_NUMBERINGSTART                            0x00008000
#define  PFM_RTLPARA                                   0x00010000
#define  PFM_KEEP                                      0x00020000
#define  PFM_KEEPNEXT                                  0x00040000
#define  PFM_PAGEBREAKBEFORE                           0x00080000
#define  PFM_NOLINENUMBER                              0x00100000
#define  PFM_NOWIDOWCONTROL                            0x00200000
#define  PFM_DONOTHYPHEN                               0x00400000
#define  PFM_SIDEBYSIDE                                0x00800000
#define  PFM_TABLE                                     0x40000000
#define  PFM_TEXTWRAPPINGBREAK                         0x20000000
#define  PFM_TABLEROWDELIMITER                         0x10000000
#define  PFM_COLLAPSED                                 0x01000000
#define  PFM_OUTLINELEVEL                              0x02000000
#define  PFM_BOX                                       0x04000000
#define  PFM_RESERVED2                                 0x08000000
#define  PFM_ALL                                       nOr(PFM_STARTINDENT,PFM_RIGHTINDENT,PFM_OFFSET,PFM_ALIGNMENT,PFM_TABSTOPS,PFM_NUMBERING,PFM_OFFSETINDENT,PFM_RTLPARA)
#define  PFM_EFFECTS                                   nOr(PFM_RTLPARA,PFM_KEEP,PFM_KEEPNEXT,PFM_TABLE,PFM_PAGEBREAKBEFORE,PFM_NOLINENUMBER,PFM_NOWIDOWCONTROL,PFM_DONOTHYPHEN,PFM_SIDEBYSIDE,PFM_TABLE,PFM_TABLEROWDELIMITER)
#define  PFM_ALL2                                      nOr(PFM_ALL,PFM_EFFECTS,PFM_SPACEBEFORE,PFM_SPACEAFTER,PFM_LINESPACING,PFM_STYLE,PFM_SHADING,PFM_BORDER,PFM_NUMBERINGTAB,PFM_NUMBERINGSTART,PFM_NUMBERINGSTYLE)
#define  PFE_RTLPARA                                   nRShift(PFM_RTLPARA,16)
#define  PFE_KEEP                                      nRShift(PFM_KEEP,16)
#define  PFE_KEEPNEXT                                  nRShift(PFM_KEEPNEXT,16)
#define  PFE_PAGEBREAKBEFORE                           nRShift(PFM_PAGEBREAKBEFORE,16)
#define  PFE_NOLINENUMBER                              nRShift(PFM_NOLINENUMBER,16)
#define  PFE_NOWIDOWCONTROL                            nRShift(PFM_NOWIDOWCONTROL,16)
#define  PFE_DONOTHYPHEN                               nRShift(PFM_DONOTHYPHEN,16)
#define  PFE_SIDEBYSIDE                                nRShift(PFM_SIDEBYSIDE,16)
#define  PFE_TEXTWRAPPINGBREAK                         nRShift(PFM_TEXTWRAPPINGBREAK,16)
#define  PFE_COLLAPSED                                 nRShift(PFM_COLLAPSED,16)
#define  PFE_BOX                                       nRShift(PFM_BOX,16)
#define  PFE_TABLE                                     nRShift(PFM_TABLE,16)
#define  PFE_TABLEROWDELIMITER                         nRShift(PFM_TABLEROWDELIMITER,16)
#define  PFN_BULLET                                    1
#define  PFN_ARABIC                                    2
#define  PFN_LCLETTER                                  3
#define  PFN_UCLETTER                                  4
#define  PFN_LCROMAN                                   5
#define  PFN_UCROMAN                                   6
#define  PFNS_PAREN                                    0x000
#define  PFNS_PARENS                                   0x100
#define  PFNS_PERIOD                                   0x200
#define  PFNS_PLAIN                                    0x300
#define  PFNS_NONUMBER                                 0x400
#define  PFNS_NEWNUMBER                                0x8000
#define  PFA_LEFT                                      1
#define  PFA_RIGHT                                     2
#define  PFA_CENTER                                    3
#define  PFA_JUSTIFY                                   4
#define  PFA_FULL_INTERWORD                            4
#define  PFA_FULL_INTERLETTER                          5
#define  PFA_FULL_SCALED                               6
#define  PFA_FULL_GLYPHS                               7
#define  PFA_SNAP_GRID                                 8
#define  SEL_EMPTY                                     0x0000
#define  SEL_TEXT                                      0x0001
#define  SEL_OBJECT                                    0x0002
#define  SEL_MULTICHAR                                 0x0004
#define  SEL_MULTIOBJECT                               0x0008
#define  GCM_RIGHTMOUSEDROP                            0x8000
#define  OLEOP_DOVERB                                  1
#define  CF_RTF                                        "Rich Text Format"
#define  CF_RTFNOOBJS                                  "Rich Text Format Without Objects"
#define  CF_RETEXTOBJ                                  "RichEdit Text and Objects"
#define  ST_DEFAULT                                    0
#define  ST_KEEPUNDO                                   1
#define  ST_SELECTION                                  2
#define  ST_NEWCHARS                                   4
#define  GT_DEFAULT                                    0
#define  GT_USECRLF                                    1
#define  GT_SELECTION                                  2
#define  GT_RAWTEXT                                    4
#define  GT_NOHIDDENTEXT                               8
#define  GTL_DEFAULT                                   0
#define  GTL_USECRLF                                   1
#define  GTL_PRECISE                                   2
#define  GTL_CLOSE                                     4
#define  GTL_NUMCHARS                                  8
#define  GTL_NUMBYTES                                  16
#define  BOM_DEFPARADIR                                0x0001
#define  BOM_PLAINTEXT                                 0x0002
#define  BOM_NEUTRALOVERRIDE                           0x0004
#define  BOM_CONTEXTREADING                            0x0008
#define  BOM_CONTEXTALIGNMENT                          0x0010
#define  BOM_LEGACYBIDICLASS                           0x0040
#define  BOE_RTLDIR                                    0x0001
#define  BOE_PLAINTEXT                                 0x0002
#define  BOE_NEUTRALOVERRIDE                           0x0004
#define  BOE_CONTEXTREADING                            0x0008
#define  BOE_CONTEXTALIGNMENT                          0x0010
#define  BOE_LEGACYBIDICLASS                           0x0040
#define  FR_MATCHDIAC                                  0x20000000
#define  FR_MATCHKASHIDA                               0x40000000
#define  FR_MATCHALEFHAMZA                             dwfix(0x8000,0x0000)
// -----------------------------------------------------------------------------------------------------------------
#endif // _XB_RICHEDIT_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// EOF
// -----------------------------------------------------------------------------------------------------------------
