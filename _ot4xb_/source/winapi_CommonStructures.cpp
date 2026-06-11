#define _WIN32_WINNT   0x0500
#define _WIN32_WINDOWS 0x0410
#include <Winsock2.h>
#include <ot4xb_api.h>
#include <Richedit.h>
#include <wininet.h>
// -----------------------------------------------------------------------------------------------------------------
static void* pt_dummy = 0;
// -----------------------------------------------------------------------------------------------------------------
#define XB_BEGIN_STRUCTURE( structName ) \
XPPRET XPPENTRY WAPIST_##structName( XppParamList pl ) \
{ \
   ContainerHandle conco = _conClsObj("WAPIST_" #structName); \
   if( conco == NULLCONTAINER ) \
   { \
   TXbClass * pc = new TXbClass; pc->ClassName("WAPIST_" #structName); pc->GwstParent();pc->EXPORTED(); pc->GwstReadWrite();
// -----------------------------------------------------------------------------------------------------------------
#define XB_END_STRUCTURE  conco = pc->Create(); \
        delete pc; if( conco == NULLCONTAINER ){_ret(pl); return;} \
        } _conReturn(pl,conco); _conRelease(conco); }
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_BOOL(       name  )        pc->Member_Bool( #name );
#define _XBST_BYTE(       name  )        pc->Member_Byte(#name);
#define _XBST_CHAR(       name  )        pc->Member_Byte(#name);
#define _XBST_TCHAR(      name  )        pc->Member_Byte(#name);
#define _XBST_USHORT(     name  )        pc->Member_Word(#name);
#define _XBST_WORD(       name  )        pc->Member_Word(#name);
#define _XBST_ATOM(       name  )        pc->Member_Word(#name);
#define _XBST_INT16(      name  )        pc->Member_Int16(#name);
#define _XBST_short(      name  )        pc->Member_Short(#name);
#define _XBST_SHORT(      name  )        pc->Member_Short(#name);
#define _XBST_DWORD(      name  )        pc->Member_DWord(#name);
#define _XBST_SIZE_T(     name  )        pc->Member_DWord(#name);
#define _XBST_LCID(       name  )        pc->Member_DWord(#name);
#define _XBST_ACCESS_MASK( name )        pc->Member_DWord(#name);
#define _XBST_ULONG(      name  )        pc->Member_ULong(#name);
#define _XBST_LONG(       name  )        pc->Member_Long(#name);
#define _XBST_HRESULT(    name  )        pc->Member_Long(#name);
#define _XBST_COLORREF(   name  )        pc->Member_Long(#name);
#define _XBST_UINT(       name  )        pc->Member_UInt(#name);
#define _XBST_int(        name  )        pc->Member_Int32(#name);
#define _XBST_INT(        name  )        pc->Member_Int32(#name);
#define _XBST_INT32(      name  )        pc->Member_Int32(#name);
#define _XBST_INT64(      name  )        pc->Member_NINT64(#name);
#define _XBST_LPARAM(     name  )        pc->Member_LParam(#name);
#define _XBST_WPARAM(     name  )        pc->Member_WParam(#name);
#define _XBST_POINTER(    name  )        pc->Member_Pointer32(#name);
#define _XBST_WNDPROC(    name  )        pc->Member_Pointer32(#name);
#define _XBST_ULONG_PTR(  name  )        pc->Member_Pointer32(#name);
#define _XBST_PVOID(      name  )        pc->Member_Pointer32(#name);
#define _XBST_LPVOID(     name  )        pc->Member_Pointer32(#name);
#define _XBST_POINTER32(  name  )        pc->Member_Pointer32(#name);
#define _XBST_HCURSOR(    name  )        pc->Member_Handle(#name);
#define _XBST_HBITMAP(    name  )        pc->Member_Handle(#name);
#define _XBST_HINSTANCE(  name  )        pc->Member_Handle(#name);
#define _XBST_HICON(      name  )        pc->Member_Handle(#name);
#define _XBST_HIMAGELIST( name  )        pc->Member_Handle(#name);
#define _XBST_HMETAFILE(  name  )        pc->Member_Handle(#name);
#define _XBST_HMENU(      name  )        pc->Member_Handle(#name);
#define _XBST_HBRUSH(     name  )        pc->Member_Handle(#name);
#define _XBST_HPEN(       name  )        pc->Member_Handle(#name);
#define _XBST_HANDLE(     name  )        pc->Member_Handle(#name);

#define _XBST_HWND(       name  )        pc->Member_hWnd( #name);
#define _XBST_HDC(        name  )        pc->Member_hDC( #name);
#define _XBST_PCLIPVAR(   name  )        pc->Member_pClipVar( #name);
#define _XBST_CODEBLOCK(  name  )        pc->Member_CodeBlock( #name);
#define _XBST_LPXBASE(    name  )        pc->Member_lpXBase( #name);
#define _XBST_XBASE(      name  )        pc->Member_Xbase( #name);
#define _XBST_DWORD64(    name  )        pc->Member_DWord64( #name);
#define _XBST_DWORDLONG(  name  )        pc->Member_DWord64( #name);
#define _XBST_DOUBLE(     name  )        pc->Member_Double( #name);
#define _XBST_FLOAT(      name  )        pc->Member_Float( #name);
#define _XBST_LPSTR(      name  )        pc->Member_lpStr( #name);
#define _XBST_LPBYTE(     name  )        pc->Member_lpStr( #name);
#define _XBST_BINSTR(     name  , size ) pc->Member_BinStr( #name , size );
#define _XBST_SZWSTR(     name  , size ) pc->Member_szWStr( #name , size );
#define _XBST_SZSTR(      name  , size ) pc->Member_szStr( #name  , size );
#define _XBST_DYNSZ(      name  )        pc->Member_DynSz( #name );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_LPSTR_DYNSZ( name , dname ) {pc->Member_lpStr( #name);pc->GwstBack();pc->Member_DynSz( #dname );}
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_POINT( name )                           pc->Child( #name , "WAPIST_POINT");
#define _XBST_POINTS( name )                          pc->Child( #name , "WAPIST_POINTS");
#define _XBST_POINTL( name )                          pc->Child( #name , "WAPIST_POINTL");
#define _XBST_MSG( name )                             pc->Child( #name , "WAPIST_MSG");
#define _XBST_BITMAP( name )                          pc->Child( #name , "WAPIST_BITMAP");
#define _XBST_BITMAPINFOHEADER( name )                pc->Child( #name , "WAPIST_BITMAPINFOHEADER");
#define _XBST_DIBSECTION( name )                      pc->Child( #name , "WAPIST_DIBSECTION");
#define _XBST_EXTLOGPEN( name )                       pc->Child( #name , "WAPIST_EXTLOGPEN");
#define _XBST_LOGPEN( name )                          pc->Child( #name , "WAPIST_LOGPEN");
#define _XBST_LOGBRUSH( name )                        pc->Child( #name , "WAPIST_LOGBRUSH");
#define _XBST_LOGBRUSH32( name )                      pc->Child( #name , "WAPIST_LOGBRUSH32");
#define _XBST_LOGFONT( name )                         pc->Child( #name , "WAPIST_LOGFONT");
#define _XBST_BLENDFUNCTION( name )                   pc->Child( #name , "WAPIST_BLENDFUNCTION");
#define _XBST_RGBQUAD( name )                         pc->Child( #name , "WAPIST_RGBQUAD");
#define _XBST_BITMAPINFO( name )                      pc->Child( #name , "WAPIST_BITMAPINFO");
#define _XBST_SIZE( name )                            pc->Child( #name , "WAPIST_SIZE");
#define _XBST_SIZEL( name )                           pc->Child( #name , "WAPIST_SIZEL");
#define _XBST_TRIVERTEX( name )                       pc->Child( #name , "WAPIST_TRIVERTEX");
#define _XBST_PALETTEENTRY( name )                    pc->Child( #name , "WAPIST_PALETTEENTRY");
#define _XBST_LOGPALETTE( name )                      pc->Child( #name , "WAPIST_LOGPALETTE");
#define _XBST_XFORM( name )                           pc->Child( #name , "WAPIST_XFORM");
#define _XBST_RECT( name )                            pc->Child( #name , "WAPIST_RECT");
#define _XBST_RECTL( name )                           pc->Child( #name , "WAPIST_RECTL");
#define _XBST_ABC( name )                             pc->Child( #name , "WAPIST_ABC");
#define _XBST_ABCFLOAT( name )                        pc->Child( #name , "WAPIST_ABCFLOAT");
#define _XBST_DRAWTEXTPARAMS( name )                  pc->Child( #name , "WAPIST_DRAWTEXTPARAMS");
#define _XBST_ENUMLOGFONT( name )                     pc->Child( #name , "WAPIST_ENUMLOGFONT");
#define _XBST_ENUMLOGFONTEX( name )                   pc->Child( #name , "WAPIST_ENUMLOGFONTEX");
#define _XBST_EXTLOGFONT( name )                      pc->Child( #name , "WAPIST_EXTLOGFONT");
#define _XBST_FIXED( name )                           pc->Child( #name , "WAPIST_FIXED");
#define _XBST_GCP_RESULTS( name )                     pc->Child( #name , "WAPIST_GCP_RESULTS");
#define _XBST_GLYPHMETRICS( name )                    pc->Child( #name , "WAPIST_GLYPHMETRICS");
#define _XBST_GLYPHSET( name )                        pc->Child( #name , "WAPIST_GLYPHSET");
#define _XBST_KERNINGPAIR( name )                     pc->Child( #name , "WAPIST_KERNINGPAIR");
#define _XBST_MAT2( name )                            pc->Child( #name , "WAPIST_MAT2");
#define _XBST_NEWTEXTMETRIC( name )                   pc->Child( #name , "WAPIST_NEWTEXTMETRIC");
#define _XBST_NEWTEXTMETRICEX( name )                 pc->Child( #name , "WAPIST_NEWTEXTMETRICEX");
#define _XBST_OUTLINETEXTMETRIC( name )               pc->Child( #name , "WAPIST_OUTLINETEXTMETRIC");
#define _XBST_PANOSE( name )                          pc->Child( #name , "WAPIST_PANOSE");
#define _XBST_POINTFX( name )                         pc->Child( #name , "WAPIST_POINTFX");
#define _XBST_POLYTEXT( name )                        pc->Child( #name , "WAPIST_POLYTEXT");
#define _XBST_RASTERIZER_STATUS( name )               pc->Child( #name , "WAPIST_RASTERIZER_STATUS");
#define _XBST_TEXTMETRIC( name )                      pc->Child( #name , "WAPIST_TEXTMETRIC");
#define _XBST_TTPOLYCURVE( name )                     pc->Child( #name , "WAPIST_TTPOLYCURVE");
#define _XBST_TTPOLYGONHEADER( name )                 pc->Child( #name , "WAPIST_TTPOLYGONHEADER");
#define _XBST_WCRANGE( name )                         pc->Child( #name , "WAPIST_WCRANGE");
#define _XBST_FONTSIGNATURE( name )                   pc->Child( #name , "WAPIST_FONTSIGNATURE");
#define _XBST_NMHDR( name )                           pc->Child( #name , "WAPIST_NMHDR");

// -----------------------------------------------------------------------------------------------------------------
#define _XBST_MONITORINFO( name )                     pc->Child( #name , "WAPIST_MONITORINFO");
#define _XBST_MONITORINFOEX( name )                   pc->Child( #name , "WAPIST_MONITORINFOEX");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_PAINTSTRUCT( name )                     pc->Child( #name , "WAPIST_PAINTSTRUCT");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_FILETIME( name )                        pc->Child( #name , "FILETIME64");
#define _XBST_SYSTEMTIME( name )                      pc->Child( #name , "WAPIST_SYSTEMTIME");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_ADDJOB_INFO_1( name )                    pc->Child( #name , "WAPIST_ADDJOB_INFO_1" );
#define _XBST_DATATYPES_INFO_1( name )                 pc->Child( #name , "WAPIST_DATATYPES_INFO_1" );
#define _XBST_DEVMODEA( name )                          pc->Child( #name , "WAPIST_DEVMODEA" );
#define _XBST_DEVMODEW( name )                          pc->Child( #name , "WAPIST_DEVMODEW" );
#define _XBST_DOC_INFO_1( name )                       pc->Child( #name , "WAPIST_DOC_INFO_1" );
#define _XBST_DOC_INFO_2( name )                       pc->Child( #name , "WAPIST_DOC_INFO_2" );
#define _XBST_DOC_INFO_3( name )                       pc->Child( #name , "WAPIST_DOC_INFO_3" );
#define _XBST_DOCINFO( name )                          pc->Child( #name , "WAPIST_DOCINFO" );
#define _XBST_DRAWPATRECT( name )                      pc->Child( #name , "WAPIST_DRAWPATRECT" );
#define _XBST_DRIVER_INFO_1( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_1" );
#define _XBST_DRIVER_INFO_2( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_2" );
#define _XBST_DRIVER_INFO_3( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_3" );
#define _XBST_DRIVER_INFO_4( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_4" );
#define _XBST_DRIVER_INFO_5( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_5" );
#define _XBST_DRIVER_INFO_6( name )                    pc->Child( #name , "WAPIST_DRIVER_INFO_6" );
#define _XBST_FORM_INFO_1( name )                      pc->Child( #name , "WAPIST_FORM_INFO_1" );
#define _XBST_JOB_INFO_1( name )                       pc->Child( #name , "WAPIST_JOB_INFO_1" );
#define _XBST_JOB_INFO_2( name )                       pc->Child( #name , "WAPIST_JOB_INFO_2" );
#define _XBST_JOB_INFO_3( name )                       pc->Child( #name , "WAPIST_JOB_INFO_3" );
#define _XBST_MONITOR_INFO_1( name )                   pc->Child( #name , "WAPIST_MONITOR_INFO_1" );
#define _XBST_MONITOR_INFO_2( name )                   pc->Child( #name , "WAPIST_MONITOR_INFO_2" );
#define _XBST_PORT_INFO_1( name )                      pc->Child( #name , "WAPIST_PORT_INFO_1" );
#define _XBST_PORT_INFO_2( name )                      pc->Child( #name , "WAPIST_PORT_INFO_2" );
#define _XBST_PORT_INFO_3( name )                      pc->Child( #name , "WAPIST_PORT_INFO_3" );
#define _XBST_PRINTER_DEFAULTS( name )                 pc->Child( #name , "WAPIST_PRINTER_DEFAULTS" );
#define _XBST_PRINTER_ENUM_VALUES( name )              pc->Child( #name , "WAPIST_PRINTER_ENUM_VALUES" );
#define _XBST_PRINTER_INFO_1( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_1" );
#define _XBST_PRINTER_INFO_2( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_2" );
#define _XBST_PRINTER_INFO_3( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_3" );
#define _XBST_PRINTER_INFO_4( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_4" );
#define _XBST_PRINTER_INFO_5( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_5" );
#define _XBST_PRINTER_INFO_6( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_6" );
#define _XBST_PRINTER_INFO_7( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_7" );
#define _XBST_PRINTER_INFO_8( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_8" );
#define _XBST_PRINTER_INFO_9( name )                   pc->Child( #name , "WAPIST_PRINTER_INFO_9" );
#define _XBST_PRINTER_NOTIFY_INFO( name )              pc->Child( #name , "WAPIST_PRINTER_NOTIFY_INFO" );
#define _XBST__PRINTER_NOTIFY_INFO_DATA___DATA( name ) pc->Child( #name , "WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA" );

#define _XBST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA( name ) pc->Child( #name , "WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA" );


#define _XBST_PRINTER_NOTIFY_INFO_DATA( name )         pc->Child( #name , "WAPIST_PRINTER_NOTIFY_INFO_DATA" );
#define _XBST_PRINTER_NOTIFY_OPTIONS( name )           pc->Child( #name , "WAPIST_PRINTER_NOTIFY_OPTIONS" );
#define _XBST_PRINTER_NOTIFY_OPTIONS_TYPE( name )      pc->Child( #name , "WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE" );
#define _XBST_PRINTPROCESSOR_CAPS_1( name )            pc->Child( #name , "WAPIST_PRINTPROCESSOR_CAPS_1" );
#define _XBST_PRINTPROCESSOR_INFO_1( name )            pc->Child( #name , "WAPIST_PRINTPROCESSOR_INFO_1" );
#define _XBST_PROVIDOR_INFO_1( name )                  pc->Child( #name , "WAPIST_PROVIDOR_INFO_1" );
#define _XBST_PROVIDOR_INFO_2( name )                  pc->Child( #name , "WAPIST_PROVIDOR_INFO_2" );
#define _XBST_PSFEATURE_CUSTPAPER( name )              pc->Child( #name , "WAPIST_PSFEATURE_CUSTPAPER" );
#define _XBST_PSFEATURE_OUTPUT( name )                 pc->Child( #name , "WAPIST_PSFEATURE_OUTPUT" );
#define _XBST_PSINJECTDATA( name )                     pc->Child( #name , "WAPIST_PSINJECTDATA" );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_RGNDATA( name )                          pc->Child( #name , "WAPIST_RGNDATA" );
#define _XBST_RGNDATAHEADER( name )                    pc->Child( #name , "WAPIST_RGNDATAHEADER" );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_DISPLAY_DEVICE( name ) pc->Child( #name , "WAPIST_DISPLAY_DEVICE" );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_ALTTABINFO( name )      pc->Child( #name , "WAPIST_ALTTABINFO" );
#define _XBST_TITLEBARINFO( name )    pc->Child( #name , "WAPIST_TITLEBARINFO");
#define _XBST_WINDOWINFO( name )      pc->Child( #name , "WAPIST_WINDOWINFO");
#define _XBST_WINDOWPLACEMENT( name ) pc->Child( #name , "WAPIST_WINDOWPLACEMENT");
#define _XBST_GUITHREADINFO( name )   pc->Child( #name , "WAPIST_GUITHREADINFO");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_ICONINFO( name )    pc->Child( #name , "WAPIST_ICONINFO");
#define _XBST_ICONMETRICS( name ) pc->Child( #name , "WAPIST_ICONMETRICS");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_METAFILEPICT( name ) pc->Child( #name , "WAPIST_METAFILEPICT");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_MDINEXTMENU( name )                        pc->Child( #name , "WAPIST_MDINEXTMENU" );
#define _XBST_MENUBARINFO( name )                        pc->Child( #name , "WAPIST_MENUBARINFO" );
#define _XBST_MENUEX_TEMPLATE_HEADER( name )             pc->Child( #name , "WAPIST_MENUEX_TEMPLATE_HEADER" );
#define _XBST_MENUEX_TEMPLATE_ITEM( name )               pc->Child( #name , "WAPIST_MENUEX_TEMPLATE_ITEM" );
#define _XBST_MENUGETOBJECTINFO( name )                  pc->Child( #name , "WAPIST_MENUGETOBJECTINFO" );
#define _XBST_MENUINFO( name )                           pc->Child( #name , "WAPIST_MENUINFO" );
#define _XBST_MENUITEMINFO( name )                       pc->Child( #name , "WAPIST_MENUITEMINFO" );
#define _XBST_MENUITEMTEMPLATE( name )                   pc->Child( #name , "WAPIST_MENUITEMTEMPLATE" );
#define _XBST_MENUITEMTEMPLATEHEADER( name )             pc->Child( #name , "WAPIST_MENUITEMTEMPLATEHEADER" );
#define _XBST_TPMPARAMS( name )                          pc->Child( #name , "WAPIST_TPMPARAMS" );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_HARDWAREINPUT( name )       pc->Child( #name , "WAPIST_HARDWAREINPUT" );
#define _XBST_INPUT( name )               pc->Child( #name , "WAPIST_INPUT" );
#define _XBST_KEYBDINPUT( name )          pc->Child( #name , "WAPIST_KEYBDINPUT" );
#define _XBST_LASTINPUTINFO( name )       pc->Child( #name , "WAPIST_LASTINPUTINFO" );
#define _XBST_MOUSEINPUT( name )          pc->Child( #name , "WAPIST_MOUSEINPUT" );
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_BIDIOPTIONS( name )      pc->Child( #name ,"WAPIST_BIDIOPTIONS");
#define _XBST_CHARFORMAT( name )       pc->Child( #name ,"WAPIST_CHARFORMAT");
#define _XBST_CHARFORMAT2( name )      pc->Child( #name ,"WAPIST_CHARFORMAT2");
#define _XBST_CHARRANGE( name )        pc->Child( #name ,"WAPIST_CHARRANGE");
#define _XBST_COMPCOLOR( name )        pc->Child( #name ,"WAPIST_COMPCOLOR");
#define _XBST_EDITSTREAM( name )       pc->Child( #name ,"WAPIST_EDITSTREAM");
#define _XBST_ENCORRECTTEXT( name )    pc->Child( #name ,"WAPIST_ENCORRECTTEXT");
#define _XBST_ENDROPFILES( name )      pc->Child( #name ,"WAPIST_ENDROPFILES");
#define _XBST_ENLINK( name )           pc->Child( #name ,"WAPIST_ENLINK");
#define _XBST_ENLOWFIRTF( name )       pc->Child( #name ,"WAPIST_ENLOWFIRTF");
#define _XBST_ENOLEOPFAILED( name )    pc->Child( #name ,"WAPIST_ENOLEOPFAILED");
#define _XBST_ENPROTECTED( name )      pc->Child( #name ,"WAPIST_ENPROTECTED");
#define _XBST_ENSAVECLIPBOARD( name )  pc->Child( #name ,"WAPIST_ENSAVECLIPBOARD");
#define _XBST_FINDTEXT( name )         pc->Child( #name ,"WAPIST_FINDTEXT");
#define _XBST_FINDTEXTEX( name )       pc->Child( #name ,"WAPIST_FINDTEXTEX");
#define _XBST_FORMATRANGE( name )      pc->Child( #name ,"WAPIST_FORMATRANGE");
#define _XBST_GETTEXTEX( name )        pc->Child( #name ,"WAPIST_GETTEXTEX");
#define _XBST_GETTEXTLENGTHEX( name )  pc->Child( #name ,"WAPIST_GETTEXTLENGTHEX");
#define _XBST_HYPHENATEINFO( name )    pc->Child( #name ,"WAPIST_HYPHENATEINFO");
#define _XBST_HYPHRESULT( name )       pc->Child( #name ,"WAPIST_HYPHRESULT");
#define _XBST_IMECOMPTEXT( name )      pc->Child( #name ,"WAPIST_IMECOMPTEXT");
#define _XBST_MSGFILTER( name )        pc->Child( #name ,"WAPIST_MSGFILTER");
#define _XBST_OBJECTPOSITIONS( name )  pc->Child( #name ,"WAPIST_OBJECTPOSITIONS");
#define _XBST_PARAFORMAT( name )       pc->Child( #name ,"WAPIST_PARAFORMAT");
#define _XBST_PARAFORMAT2( name )      pc->Child( #name ,"WAPIST_PARAFORMAT2");
#define _XBST_PUNCTUATION( name )      pc->Child( #name ,"WAPIST_PUNCTUATION");
#define _XBST_REOBJECT( name )         pc->Child( #name ,"WAPIST_REOBJECT");
#define _XBST_REPASTESPECIAL( name )   pc->Child( #name ,"WAPIST_REPASTESPECIAL");
#define _XBST_REQRESIZE( name )        pc->Child( #name ,"WAPIST_REQRESIZE");
#define _XBST_SELCHANGE( name )        pc->Child( #name ,"WAPIST_SELCHANGE");
#define _XBST_SETTEXTEX( name )        pc->Child( #name ,"WAPIST_SETTEXTEX");
#define _XBST_TEXTRANGE( name )        pc->Child( #name ,"WAPIST_TEXTRANGE");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_GUID( name )         pc->Child( #name ,"WAPIST_GUID");
#define _XBST_CLSID( name )        pc->Child( #name ,"WAPIST_CLSID");
//----------------------------------------------------------------------------------------------------------------------
// winsock
#define _XBST_SOCKET( name )                pc->Member_DWord(#name);
#define _XBST_IN_ADDR( name )               pc->Child( #name ,"WAPIST_IN_ADDR");
#define _XBST_SOCKADDR( name )              pc->Child( #name ,"WAPIST_SOCKADDR");
#define _XBST_SOCKET_ADDRESS( name )        pc->Child( #name ,"WAPIST_SOCKET_ADDRESS");
#define _XBST_SOCKET_ADDRESS_LIST( name )   pc->Child( #name ,"WAPIST_SOCKET_ADDRESS_LIST");
#define _XBST_CSADDR_INFO( name )           pc->Child( #name ,"WAPIST_CSADDR_INFO");
#define _XBST_SOCKADDR_STORAGE( name )      pc->Child( #name ,"WAPIST_SOCKADDR_STORAGE");
#define _XBST_SOCKADDR_SCOPE_ID( name )     pc->Child( #name ,"WAPIST_SCOPE_ID");
#define _XBST_SOCKADDR_IN( name )           pc->Child( #name ,"WAPIST_SOCKADDR_IN");
#define _XBST_WSABUF( name )                pc->Child( #name ,"WAPIST_WSABUF");
#define _XBST_WSAMSG( name )                pc->Child( #name ,"WAPIST_WSAMSG");
#define _XBST_WSACMSGHDR( name )            pc->Child( #name ,"WAPIST_WSACMSGHDR");
#define _XBST_FD_SET( name )                pc->Child( #name ,"WAPIST_FD_SET");
#define _XBST_TIMEVAL( name )               pc->Child( #name ,"WAPIST_TIMEVAL");
#define _XBST_HOSTENT( name )               pc->Child( #name ,"WAPIST_HOSTENT");
#define _XBST_NETENT( name )                pc->Child( #name ,"WAPIST_NETENT");
#define _XBST_SERVENT( name )               pc->Child( #name ,"WAPIST_SERVENT");
#define _XBST_PROTOENT( name )              pc->Child( #name ,"WAPIST_PROTOENT");
#define _XBST_WSADATA( name )               pc->Child( #name ,"WAPIST_WSADATA");
#define _XBST_SOCKPROTO( name )             pc->Child( #name ,"WAPIST_SOCKPROTO");
#define _XBST_LINGER( name )                pc->Child( #name ,"WAPIST_LINGER");
#define _XBST_FLOWSPEC( name )              pc->Child( #name ,"WAPIST_FLOWSPEC");
#define _XBST_QOS_OBJECT_HDR( name )        pc->Child( #name ,"WAPIST_QOS_OBJECT_HDR");
#define _XBST_QOS_SD_MODE( name )           pc->Child( #name ,"WAPIST_QOS_SD_MODE");
#define _XBST_QOS_SHAPING_RATE( name )                  pc->Child( #name ,"WAPIST_QOS_SHAPING_RATE");
#define _XBST_QOS( name )                               pc->Child( #name ,"WAPIST_QOS");
#define _XBST_WSANETWORKEVENTS( name )                  pc->Child( #name ,"WAPIST_WSANETWORKEVENTS");
#define _XBST_WSAPROTOCOLCHAIN( name )                  pc->Child( #name ,"WAPIST_WSAPROTOCOLCHAIN");
#define _XBST_WSAPROTOCOL_INFO( name )                  pc->Child( #name ,"WAPIST_WSAPROTOCOL_INFO");
#define _XBST_WSACOMPLETION_NS_WINDOWMESSAGE( name )    pc->Child( #name ,"WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE");
#define _XBST_WSACOMPLETION_NS_EVENT( name )            pc->Child( #name ,"WAPIST_WSACOMPLETION_NS_EVENT");
#define _XBST_WSACOMPLETION_NS_APC( name )              pc->Child( #name ,"WAPIST_WSACOMPLETION_NS_APC");
#define _XBST_WSACOMPLETION_NS_PORT( name )             pc->Child( #name ,"WAPIST_WSACOMPLETION_NS_PORT");
#define _XBST_WSACOMPLETION_NS_PARAMETERS( name )       pc->Child( #name ,"WAPIST_WSACOMPLETION_NS_PARAMETERS");
#define _XBST_WSACOMPLETION( name )                     pc->Child( #name ,"WAPIST_WSACOMPLETION");
#define _XBST_BLOB( name )                              pc->Child( #name ,"WAPIST_BLOB");
#define _XBST_AFPROTOCOLS( name )                       pc->Child( #name ,"WAPIST_AFPROTOCOLS");
#define _XBST_WSAVERSION( name )                        pc->Child( #name ,"WAPIST_WSAVERSION");
#define _XBST_WSAQUERYSET( name )                       pc->Child( #name ,"WAPIST_WSAQUERYSET");
#define _XBST_WSAQUERYSET2( name )                      pc->Child( #name ,"WAPIST_WSAQUERYSET2");
#define _XBST_WSANSCLASSINFO( name )                    pc->Child( #name ,"WAPIST_WSANSCLASSINFO");
#define _XBST_WSASERVICECLASSINFO( name )               pc->Child( #name ,"WAPIST_WSASERVICECLASSINFO");
#define _XBST_WSANAMESPACE_INFO( name )                 pc->Child( #name ,"WAPIST_WSANAMESPACE_INFO");
#define _XBST_WSANAMESPACE_INFOEX( name )               pc->Child( #name ,"WAPIST_WSANAMESPACE_INFOEX");
#define _XBST_WSAPOLLFD( name )                         pc->Child( #name ,"WAPIST_WSAPOLLFD");
#define _XBST_ADDRINFO( name )                          pc->Child( #name ,"WAPIST_ADDRINFO");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_OPENFILENAME( name )                      pc->Child( #name , "WAPIST_OPENFILENAME");



// -----------------------------------------------------------------------------------------------------------------
// HID
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_RAWHID( name )                      pc->Child( #name , "WAPIST_RAWHID");
#define _XBST_RAWINPUT( name )                    pc->Child( #name , "WAPIST_RAWINPUT");
#define _XBST_RAWINPUT_DATA_UNION( name )            pc->Child( #name , "WAPIST_RAWINPUT_DATA_UNION");
#define _XBST_RAWINPUTDEVICE( name )              pc->Child( #name , "WAPIST_RAWINPUTDEVICE");
#define _XBST_RAWINPUTDEVICELIST( name )          pc->Child( #name , "WAPIST_RAWINPUTDEVICELIST");
#define _XBST_RAWINPUTHEADER( name )              pc->Child( #name , "WAPIST_RAWINPUTHEADER");
#define _XBST_RAWKEYBOARD( name )                 pc->Child( #name , "WAPIST_RAWKEYBOARD");
#define _XBST_RAWMOUSE( name )                    pc->Child( #name , "WAPIST_RAWMOUSE");
#define _XBST_RID_DEVICE_INFO( name )             pc->Child( #name , "WAPIST_RID_DEVICE_INFO");
#define _XBST_RID_DEVICE_INFO_HID( name )         pc->Child( #name , "WAPIST_RID_DEVICE_INFO_HID");
#define _XBST_RID_DEVICE_INFO_KEYBOARD( name )    pc->Child( #name , "WAPIST_RID_DEVICE_INFO_KEYBOARD");
#define _XBST_RID_DEVICE_INFO_MOUSE( name )       pc->Child( #name , "WAPIST_RID_DEVICE_INFO_MOUSE");

// -----------------------------------------------------------------------------------------------------------------
// IPHLPR
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_IP_ADDR_STRING( name )                  pc->Child( #name ,"WAPIST_IP_ADDR_STRING");
#define _XBST_IP_ADAPTER_INFO( name )                 pc->Child( #name ,"WAPIST_IP_ADAPTER_INFO");
#define _XBST_IP_PER_ADAPTER_INFO( name )             pc->Child( #name ,"WAPIST_IP_PER_ADAPTER_INFO");
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// Synchronization
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_OVERLAPPED( name )             pc->Child( #name ,"WAPIST_OVERLAPPED");
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// Windows System Information
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_SYSTEM_INFO( name )             pc->Child( #name ,"WAPIST_SYSTEM_INFO");


// -----------------------------------------------------------------------------------------------------------------
// common controls - listview support
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_LVBKIMAGE( name )                       pc->Child( #name , "WAPIST_LVBKIMAGE");
#define _XBST_LVCOLUMN( name )                        pc->Child( #name , "WAPIST_LVCOLUMN");
#define _XBST_LVFINDINFO( name )                      pc->Child( #name , "WAPIST_LVFINDINFO");
#define _XBST_LVFOOTERINFO( name )                    pc->Child( #name , "WAPIST_LVFOOTERINFO");
#define _XBST_LVFOOTERITEM( name )                    pc->Child( #name , "WAPIST_LVFOOTERITEM");
#define _XBST_LVGROUP( name )                         pc->Child( #name , "WAPIST_LVGROUP");
#define _XBST_LVGROUPMETRICS( name )                  pc->Child( #name , "WAPIST_LVGROUPMETRICS");
#define _XBST_LVHITTESTINFO( name )                   pc->Child( #name , "WAPIST_LVHITTESTINFO");
#define _XBST_LVINSERTGROUPSORTED( name )             pc->Child( #name , "WAPIST_LVINSERTGROUPSORTED");
#define _XBST_LVINSERTMARK( name )                    pc->Child( #name , "WAPIST_LVINSERTMARK");
#define _XBST_LVITEM( name )                          pc->Child( #name , "WAPIST_LVITEM");
#define _XBST_LVITEMINDEX( name )                     pc->Child( #name , "WAPIST_LVITEMINDEX");
#define _XBST_LVSETINFOTIP( name )                    pc->Child( #name , "WAPIST_LVSETINFOTIP");
#define _XBST_LVTILEINFO( name )                      pc->Child( #name , "WAPIST_LVTILEINFO");
#define _XBST_LVTILEVIEWINFO( name )                  pc->Child( #name , "WAPIST_LVTILEVIEWINFO");
#define _XBST_NMITEMACTIVATE( name )                  pc->Child( #name , "WAPIST_NMITEMACTIVATE");
#define _XBST_NMLISTVIEW( name )                      pc->Child( #name , "WAPIST_NMLISTVIEW");
#define _XBST_NMLVCACHEHINT( name )                   pc->Child( #name , "WAPIST_NMLVCACHEHINT");
#define _XBST_NMLVCUSTOMDRAW( name )                  pc->Child( #name , "WAPIST_NMLVCUSTOMDRAW");
#define _XBST_NMLVDISPINFO( name )                    pc->Child( #name , "WAPIST_NMLVDISPINFO");
#define _XBST_NMLVEMPTYMARKUP( name )                 pc->Child( #name , "WAPIST_NMLVEMPTYMARKUP");
#define _XBST_NMLVFINDITEM( name )                    pc->Child( #name , "WAPIST_NMLVFINDITEM");
#define _XBST_NMLVGETINFOTIP( name )                  pc->Child( #name , "WAPIST_NMLVGETINFOTIP");
#define _XBST_NMLVKEYDOWN( name )                     pc->Child( #name , "WAPIST_NMLVKEYDOWN");
#define _XBST_NMLVLINK( name )                        pc->Child( #name , "WAPIST_NMLVLINK");
#define _XBST_NMLVODSTATECHANGE( name )               pc->Child( #name , "WAPIST_NMLVODSTATECHANGE");
#define _XBST_NMLVSCROLL( name )                      pc->Child( #name , "WAPIST_NMLVSCROLL");
//----------------------------------------------------------------------------------------------------------------------
#define _XBST_LITEM( name )                      pc->Child( #name , "WAPIST_LITEM");
#define _XBST_NMCUSTOMDRAW( name )               pc->Child( #name , "WAPIST_NMCUSTOMDRAW");
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------






//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

#define _XBST_WINDOWPOS( name ) pc->Child( #name , "WAPIST_WINDOWPOS" );
#define _XBST_COLORSCHEME( name ) pc->Child( #name , "WAPIST_COLORSCHEME" );
#define _XBST_DPASTREAMINFO( name ) pc->Child( #name , "WAPIST_DPASTREAMINFO" );
#define _XBST_NMCHAR( name ) pc->Child( #name , "WAPIST_NMCHAR" );
#define _XBST_NMCUSTOMSPLITRECTINFO( name ) pc->Child( #name , "WAPIST_NMCUSTOMSPLITRECTINFO" );
#define _XBST_NMCUSTOMTEXT( name ) pc->Child( #name , "WAPIST_NMCUSTOMTEXT" );
#define _XBST_NMKEY( name ) pc->Child( #name , "WAPIST_NMKEY" );
#define _XBST_NMMOUSE( name ) pc->Child( #name , "WAPIST_NMMOUSE" );
#define _XBST_NMOBJECTNOTIFY( name ) pc->Child( #name , "WAPIST_NMOBJECTNOTIFY" );
#define _XBST_NMTOOLTIPSCREATED( name ) pc->Child( #name , "WAPIST_NMTOOLTIPSCREATED" );
#define _XBST_READERMODEINFO( name ) pc->Child( #name , "WAPIST_READERMODEINFO" );
#define _XBST_BUTTON_IMAGELIST( name ) pc->Child( #name , "WAPIST_BUTTON_IMAGELIST" );
#define _XBST_BUTTON_SPLITINFO( name ) pc->Child( #name , "WAPIST_BUTTON_SPLITINFO" );
#define _XBST_NMBCDROPDOWN( name ) pc->Child( #name , "WAPIST_NMBCDROPDOWN" );
#define _XBST_NMBCHOTITEM( name ) pc->Child( #name , "WAPIST_NMBCHOTITEM" );
#define _XBST_COMBOBOXINFO( name ) pc->Child( #name , "WAPIST_COMBOBOXINFO" );
#define _XBST_COMPAREITEMSTRUCT( name ) pc->Child( #name , "WAPIST_COMPAREITEMSTRUCT" );
#define _XBST_DRAWITEMSTRUCT( name ) pc->Child( #name , "WAPIST_DRAWITEMSTRUCT" );
#define _XBST_MEASUREITEMSTRUCT( name ) pc->Child( #name , "WAPIST_MEASUREITEMSTRUCT" );
#define _XBST_COMBOBOXEXITEM( name ) pc->Child( #name , "WAPIST_COMBOBOXEXITEM" );
#define _XBST_NMCBEDRAGBEGIN( name ) pc->Child( #name , "WAPIST_NMCBEDRAGBEGIN" );
#define _XBST_NMCBEENDEDIT( name ) pc->Child( #name , "WAPIST_NMCBEENDEDIT" );
#define _XBST_NMCOMBOBOXEX( name ) pc->Child( #name , "WAPIST_NMCOMBOBOXEX" );
#define _XBST_DATETIMEPICKERINFO( name ) pc->Child( #name , "WAPIST_DATETIMEPICKERINFO" );
#define _XBST_NMDATETIMECHANGE( name ) pc->Child( #name , "WAPIST_NMDATETIMECHANGE" );
#define _XBST_NMDATETIMEFORMAT( name ) pc->Child( #name , "WAPIST_NMDATETIMEFORMAT" );
#define _XBST_NMDATETIMEFORMATQUERY( name ) pc->Child( #name , "WAPIST_NMDATETIMEFORMATQUERY" );
#define _XBST_NMDATETIMESTRING( name ) pc->Child( #name , "WAPIST_NMDATETIMESTRING" );
#define _XBST_NMDATETIMEWMKEYDOWN( name ) pc->Child( #name , "WAPIST_NMDATETIMEWMKEYDOWN" );
#define _XBST_DRAGLISTINFO( name ) pc->Child( #name , "WAPIST_DRAGLISTINFO" );
#define _XBST_EDITBALLOONTIP( name ) pc->Child( #name , "WAPIST_EDITBALLOONTIP" );
#define _XBST_HDHITTESTINFO( name ) pc->Child( #name , "WAPIST_HDHITTESTINFO" );
#define _XBST_HDITEM( name ) pc->Child( #name , "WAPIST_HDITEM" );
#define _XBST_HDLAYOUT( name ) pc->Child( #name , "WAPIST_HDLAYOUT" );
#define _XBST_HDTEXTFILTER( name ) pc->Child( #name , "WAPIST_HDTEXTFILTER" );
#define _XBST_NMHDDISPINFO( name ) pc->Child( #name , "WAPIST_NMHDDISPINFO" );
#define _XBST_NMHDFILTERBTNCLICK( name ) pc->Child( #name , "WAPIST_NMHDFILTERBTNCLICK" );
#define _XBST_NMHEADER( name ) pc->Child( #name , "WAPIST_NMHEADER" );
#define _XBST_IMAGEINFO( name ) pc->Child( #name , "WAPIST_IMAGEINFO" );
#define _XBST_IMAGELISTDRAWPARAMS( name ) pc->Child( #name , "WAPIST_IMAGELISTDRAWPARAMS" );
#define _XBST_NMIPADDRESS( name ) pc->Child( #name , "WAPIST_NMIPADDRESS" );
#define _XBST_DELETEITEMSTRUCT( name ) pc->Child( #name , "WAPIST_DELETEITEMSTRUCT" );
#define _XBST_MCGRIDINFO( name ) pc->Child( #name , "WAPIST_MCGRIDINFO" );
#define _XBST_MCHITTESTINFO( name ) pc->Child( #name , "WAPIST_MCHITTESTINFO" );
#define _XBST_NMDAYSTATE( name ) pc->Child( #name , "WAPIST_NMDAYSTATE" );
#define _XBST_NMSELCHANGE( name ) pc->Child( #name , "WAPIST_NMSELCHANGE" );
#define _XBST_NMVIEWCHANGE( name ) pc->Child( #name , "WAPIST_NMVIEWCHANGE" );
#define _XBST_NMPGCALCSIZE( name ) pc->Child( #name , "WAPIST_NMPGCALCSIZE" );
#define _XBST_NMPGHOTITEM( name ) pc->Child( #name , "WAPIST_NMPGHOTITEM" );
#define _XBST_NMPGSCROLL( name ) pc->Child( #name , "WAPIST_NMPGSCROLL" );
#define _XBST_PBRANGE( name ) pc->Child( #name , "WAPIST_PBRANGE" );
#define _XBST_NMRBAUTOSIZE( name ) pc->Child( #name , "WAPIST_NMRBAUTOSIZE" );
#define _XBST_NMREBAR( name ) pc->Child( #name , "WAPIST_NMREBAR" );
#define _XBST_NMREBARAUTOBREAK( name ) pc->Child( #name , "WAPIST_NMREBARAUTOBREAK" );
#define _XBST_NMREBARCHEVRON( name ) pc->Child( #name , "WAPIST_NMREBARCHEVRON" );
#define _XBST_NMREBARCHILDSIZE( name ) pc->Child( #name , "WAPIST_NMREBARCHILDSIZE" );
#define _XBST_NMREBARSPLITTER( name ) pc->Child( #name , "WAPIST_NMREBARSPLITTER" );
#define _XBST_RBHITTESTINFO( name ) pc->Child( #name , "WAPIST_RBHITTESTINFO" );
#define _XBST_REBARBANDINFO( name ) pc->Child( #name , "WAPIST_REBARBANDINFO" );
#define _XBST_REBARINFO( name ) pc->Child( #name , "WAPIST_REBARINFO" );
#define _XBST_SCROLLBARINFO( name ) pc->Child( #name , "WAPIST_SCROLLBARINFO" );
#define _XBST_SCROLLINFO( name ) pc->Child( #name , "WAPIST_SCROLLINFO" );
#define _XBST_LHITTESTINFO( name ) pc->Child( #name , "WAPIST_LHITTESTINFO" );
#define _XBST_NMLINK( name ) pc->Child( #name , "WAPIST_NMLINK" );
#define _XBST_NMTCKEYDOWN( name ) pc->Child( #name , "WAPIST_NMTCKEYDOWN" );
#define _XBST_TCHITTESTINFO( name ) pc->Child( #name , "WAPIST_TCHITTESTINFO" );
#define _XBST_TCITEM( name ) pc->Child( #name , "WAPIST_TCITEM" );
#define _XBST_TCITEMHEADER( name ) pc->Child( #name , "WAPIST_TCITEMHEADER" );
#define _XBST_COLORMAP( name ) pc->Child( #name , "WAPIST_COLORMAP" );
#define _XBST_NMTBCUSTOMDRAW( name ) pc->Child( #name , "WAPIST_NMTBCUSTOMDRAW" );
#define _XBST_NMTBDISPINFO( name ) pc->Child( #name , "WAPIST_NMTBDISPINFO" );
#define _XBST_NMTBGETINFOTIP( name ) pc->Child( #name , "WAPIST_NMTBGETINFOTIP" );
#define _XBST_NMTBHOTITEM( name ) pc->Child( #name , "WAPIST_NMTBHOTITEM" );
#define _XBST_NMTBRESTORE( name ) pc->Child( #name , "WAPIST_NMTBRESTORE" );
#define _XBST_NMTBSAVE( name ) pc->Child( #name , "WAPIST_NMTBSAVE" );
#define _XBST_NMTOOLBAR( name ) pc->Child( #name , "WAPIST_NMTOOLBAR" );
#define _XBST_TBADDBITMAP( name ) pc->Child( #name , "WAPIST_TBADDBITMAP" );
#define _XBST_TBBUTTON( name ) pc->Child( #name , "WAPIST_TBBUTTON" );
#define _XBST_TBBUTTONINFOA( name ) pc->Child( #name , "WAPIST_TBBUTTONINFOA" );
#define _XBST_TBINSERTMARK( name ) pc->Child( #name , "WAPIST_TBINSERTMARK" );
#define _XBST_TBMETRICS( name ) pc->Child( #name , "WAPIST_TBMETRICS" );
#define _XBST_TBREPLACEBITMAP( name ) pc->Child( #name , "WAPIST_TBREPLACEBITMAP" );
#define _XBST_TBSAVEPARAMS( name ) pc->Child( #name , "WAPIST_TBSAVEPARAMS" );
#define _XBST_NMTTCUSTOMDRAW( name ) pc->Child( #name , "WAPIST_NMTTCUSTOMDRAW" );
#define _XBST_NMTTDISPINFO( name ) pc->Child( #name , "WAPIST_NMTTDISPINFO" );
#define _XBST_TOOLINFO( name ) pc->Child( #name , "WAPIST_TOOLINFO" );
#define _XBST_TTGETTITLE( name ) pc->Child( #name , "WAPIST_TTGETTITLE" );
#define _XBST_TTHITTESTINFO( name ) pc->Child( #name , "WAPIST_TTHITTESTINFO" );
#define _XBST_NMTREEVIEW( name ) pc->Child( #name , "WAPIST_NMTREEVIEW" );
#define _XBST_NMTVASYNCDRAW( name ) pc->Child( #name , "WAPIST_NMTVASYNCDRAW" );
#define _XBST_NMTVCUSTOMDRAW( name ) pc->Child( #name , "WAPIST_NMTVCUSTOMDRAW" );
#define _XBST_NMTVDISPINFO( name ) pc->Child( #name , "WAPIST_NMTVDISPINFO" );
#define _XBST_NMTVDISPINFOEX( name ) pc->Child( #name , "WAPIST_NMTVDISPINFOEX" );
#define _XBST_NMTVGETINFOTIP( name ) pc->Child( #name , "WAPIST_NMTVGETINFOTIP" );
#define _XBST_NMTVITEMCHANGE( name ) pc->Child( #name , "WAPIST_NMTVITEMCHANGE" );
#define _XBST_NMTVKEYDOWN( name ) pc->Child( #name , "WAPIST_NMTVKEYDOWN" );
#define _XBST_NMTVSTATEIMAGECHANGING( name ) pc->Child( #name , "WAPIST_NMTVSTATEIMAGECHANGING" );
#define _XBST_TVGETITEMPARTRECTINFO( name ) pc->Child( #name , "WAPIST_TVGETITEMPARTRECTINFO" );
#define _XBST_TVHITTESTINFO( name ) pc->Child( #name , "WAPIST_TVHITTESTINFO" );
#define _XBST_TVINSERTSTRUCT( name ) pc->Child( #name , "WAPIST_TVINSERTSTRUCT" );
#define _XBST_TVITEM( name ) pc->Child( #name , "WAPIST_TVITEM" );
#define _XBST_TVITEMEX( name ) pc->Child( #name , "WAPIST_TVITEMEX" );
#define _XBST_TVSORTCB( name ) pc->Child( #name , "WAPIST_TVSORTCB" );
#define _XBST_NMUPDOWN( name ) pc->Child( #name , "WAPIST_NMUPDOWN" );
#define _XBST_UDACCEL( name ) pc->Child( #name , "WAPIST_UDACCEL" );
//----------------------------------------------------------------------------------------------------------------------
#define _XBST_URL_COMPONENTS( name ) pc->Child( #name , "WAPIST_URL_COMPONENTS" );
#define _XBST_INTERNET_ASYNC_RESULT( name ) pc->Child( #name , "WAPIST_INTERNET_ASYNC_RESULT" );
#define _XBST_INTERNET_DIAGNOSTIC_SOCKET_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO");
#define _XBST_INTERNET_PROXY_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_PROXY_INFO");
#define _XBST_INTERNET_PER_CONN_OPTION( name ) pc->Child( #name , "WAPIST_INTERNET_PER_CONN_OPTION");
#define _XBST_INTERNET_PER_CONN_OPTION___VALUE( name ) pc->Child( #name , "WAPIST_INTERNET_PER_CONN_OPTION___VALUE");
#define _XBST_INTERNET_PER_CONN_OPTION_LIST( name ) pc->Child( #name , "WAPIST_INTERNET_PER_CONN_OPTION_LIST");
#define _XBST_INTERNET_VERSION_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_VERSION_INFO");
#define _XBST_HTTP_VERSION_INFO( name ) pc->Child( #name , "WAPIST_HTTP_VERSION_INFO");
#define _XBST_INTERNET_CONNECTED_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_CONNECTED_INFO");
#define _XBST_INTERNET_CERTIFICATE_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_CERTIFICATE_INFO");
#define _XBST_INTERNET_BUFFERS( name ) pc->Child( #name , "WAPIST_INTERNET_BUFFERS");
#define _XBST_IncomingCookieState( name ) pc->Child( #name , "WAPIST_IncomingCookieState");
#define _XBST_OutgoingCookieState( name ) pc->Child( #name , "WAPIST_OutgoingCookieState");
#define _XBST_InternetCookieHistory( name ) pc->Child( #name , "WAPIST_InternetCookieHistory");
#define _XBST_CookieDecision( name ) pc->Child( #name , "WAPIST_CookieDecision");
#define _XBST_INTERNET_AUTH_NOTIFY_DATA( name ) pc->Child( #name , "WAPIST_INTERNET_AUTH_NOTIFY_DATA");
#define _XBST_INTERNET_CACHE_ENTRY_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_CACHE_ENTRY_INFO");
#define _XBST_INTERNET_CACHE_TIMESTAMPS( name ) pc->Child( #name , "WAPIST_INTERNET_CACHE_TIMESTAMPS");
#define _XBST_INTERNET_CACHE_GROUP_INFO( name ) pc->Child( #name , "WAPIST_INTERNET_CACHE_GROUP_INFO");
#define _XBST_AUTO_PROXY_SCRIPT_BUFFER( name ) pc->Child( #name , "WAPIST_AUTO_PROXY_SCRIPT_BUFFER");
// -----------------------------------------------------------------------------------------------------------------
#define _XBST_TRACKMOUSEEVENT( name ) pc->Child( #name , "WAPIST_TRACKMOUSEEVENT");
#define _XBST_MOUSEMOVEPOINT( name ) pc->Child( #name , "WAPIST_MOUSEMOVEPOINT");
#define _XBST_PREVENT_MEDIA_REMOVAL( name ) pc->Child( #name , "WAPIST_PREVENT_MEDIA_REMOVAL");
#define _XBST_SHFILEINFO( name ) pc->Child( #name , "WAPIST_SHFILEINFO");


//----------------------------------------------------------------------------------------------------------------------


// #define _XBST_( name )        pc->Child( #name ,"WAPIST_");
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_POINT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_POINT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi POINT structure.
         Defined as POINT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-point</ref-url>
      <members>
         <member type="LONG" name="x" offset="0">x coordinate.</member>
         <member type="LONG" name="y" offset="4">y coordinate.</member>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( POINT )
   _XBST_LONG ( x )
   _XBST_LONG ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_POINTS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_POINTS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi POINTS structure.
         Defined as POINTS in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="SHORT" name="x" offset="0" size="2" />
         <member type="SHORT" name="y" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( POINTS )
   _XBST_SHORT ( x )
   _XBST_SHORT ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_POINTL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_POINTL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi POINTL structure.
         Defined as POINTL in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LONG" name="x" offset="0" size="4" />
         <member type="LONG" name="y" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( POINTL )
   _XBST_LONG ( x )
   _XBST_LONG ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MSG</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MSG</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MSG structure.
         Defined as MSG in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="HWND" name="hwnd" offset="0" size="4" />
         <member type="UINT" name="message" offset="4" size="4" />
         <member type="WPARAM" name="wParam" offset="8" size="4" />
         <member type="LPARAM" name="lParam" offset="12" size="4" />
         <member type="DWORD" name="time" offset="16" size="4" />
         <member type="WAPIST_POINT" name="pt" offset="20" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( MSG )
   _XBST_HWND   ( hwnd    )
   _XBST_UINT   ( message )
   _XBST_WPARAM ( wParam  )
   _XBST_LPARAM ( lParam  )
   _XBST_DWORD  ( time    )
   _XBST_POINT  ( pt      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BITMAP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BITMAP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BITMAP structure.
         Defined as BITMAP in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="LONG" name="bmType" offset="0" size="4" />
         <member type="LONG" name="bmWidth" offset="4" size="4" />
         <member type="LONG" name="bmHeight" offset="8" size="4" />
         <member type="LONG" name="bmWidthBytes" offset="12" size="4" />
         <member type="WORD" name="bmPlanes" offset="16" size="2" />
         <member type="WORD" name="bmBitsPixel" offset="18" size="2" />
         <member type="POINTER32" name="bmBits" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( BITMAP       )
   _XBST_LONG      ( bmType       )
   _XBST_LONG      ( bmWidth      )
   _XBST_LONG      ( bmHeight     )
   _XBST_LONG      ( bmWidthBytes )
   _XBST_WORD      ( bmPlanes     )
   _XBST_WORD      ( bmBitsPixel  )
   _XBST_POINTER32 ( bmBits       )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BITMAPINFOHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BITMAPINFOHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BITMAPINFOHEADER structure.
         Defined as BITMAPINFOHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="DWORD" name="biSize" offset="0" size="4" />
         <member type="LONG" name="biWidth" offset="4" size="4" />
         <member type="LONG" name="biHeight" offset="8" size="4" />
         <member type="WORD" name="biPlanes" offset="12" size="2" />
         <member type="WORD" name="biBitCount" offset="14" size="2" />
         <member type="DWORD" name="biCompression" offset="16" size="4" />
         <member type="DWORD" name="biSizeImage" offset="20" size="4" />
         <member type="LONG" name="biXPelsPerMeter" offset="24" size="4" />
         <member type="LONG" name="biYPelsPerMeter" offset="28" size="4" />
         <member type="DWORD" name="biClrUsed" offset="32" size="4" />
         <member type="DWORD" name="biClrImportant" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( BITMAPINFOHEADER )
   _XBST_DWORD ( biSize          )
   _XBST_LONG  ( biWidth         )
   _XBST_LONG  ( biHeight        )
   _XBST_WORD  ( biPlanes        )
   _XBST_WORD  ( biBitCount      )
   _XBST_DWORD ( biCompression   )
   _XBST_DWORD ( biSizeImage     )
   _XBST_LONG  ( biXPelsPerMeter )
   _XBST_LONG  ( biYPelsPerMeter )
   _XBST_DWORD ( biClrUsed       )
   _XBST_DWORD ( biClrImportant  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DIBSECTION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DIBSECTION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DIBSECTION structure.
         Defined as DIBSECTION in ot4xb_wapist_map.ch.
      </description>
      <size>84</size>
      <members>
         <member type="WAPIST_BITMAP" name="dsBm" offset="0" size="24" child="true" />
         <member type="WAPIST_BITMAPINFOHEADER" name="dsBmih" offset="24" size="40" child="true" />
         <member type="DWORD" name="dsBitfield_R" offset="64" size="4" />
         <member type="DWORD" name="dsBitfield_G" offset="68" size="4" />
         <member type="DWORD" name="dsBitfield_B" offset="72" size="4" />
         <member type="HANDLE" name="dshSection" offset="76" size="4" />
         <member type="DWORD" name="dsOffset" offset="80" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( DIBSECTION )
   _XBST_BITMAP           ( dsBm          )
   _XBST_BITMAPINFOHEADER ( dsBmih        )
   _XBST_DWORD            ( dsBitfield_R  )
   _XBST_DWORD            ( dsBitfield_G  )
   _XBST_DWORD            ( dsBitfield_B  )
   _XBST_HANDLE           ( dshSection    )
   _XBST_DWORD            ( dsOffset      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_EXTLOGPEN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_EXTLOGPEN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi EXTLOGPEN structure.
         Defined as EXTLOGPEN in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="DWORD" name="elpPenStyle" offset="0" size="4" />
         <member type="DWORD" name="elpWidth" offset="4" size="4" />
         <member type="UINT" name="elpBrushStyle" offset="8" size="4" />
         <member type="ULONG" name="elpColor" offset="12" size="4" />
         <member type="POINTER32" name="elpHatch" offset="16" size="4" />
         <member type="DWORD" name="elpNumEntries" offset="20" size="4" />
         <member type="DWORD" name="elpStyleEntry0" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( EXTLOGPEN )
   _XBST_DWORD      ( elpPenStyle      )
   _XBST_DWORD      ( elpWidth         )
   _XBST_UINT       ( elpBrushStyle    )
   _XBST_ULONG      ( elpColor         )
   _XBST_POINTER32  ( elpHatch         )
   _XBST_DWORD      ( elpNumEntries    )
   _XBST_DWORD      ( elpStyleEntry0   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LOGPEN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LOGPEN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LOGPEN structure.
         Defined as LOGPEN in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="lopnPenStyle" offset="0" size="4" />
         <member type="WAPIST_POINT" name="lopnWidth" offset="4" size="8" child="true" />
         <member type="ULONG" name="lopnColor" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( LOGPEN )
   _XBST_DWORD ( lopnPenStyle )
   _XBST_POINT ( lopnWidth    )
   _XBST_ULONG ( lopnColor    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LOGBRUSH</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LOGBRUSH</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LOGBRUSH structure.
         Defined as LOGBRUSH in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="UINT" name="lbStyle" offset="0" size="4" />
         <member type="ULONG" name="lbColor" offset="4" size="4" />
         <member type="LONG" name="lbHatch" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( LOGBRUSH )
   _XBST_UINT  ( lbStyle )
   _XBST_ULONG ( lbColor )
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LOGBRUSH32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LOGBRUSH32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LOGBRUSH32 structure.
         Defined as LOGBRUSH32 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="UINT" name="lbStyle" offset="0" size="4" />
         <member type="ULONG" name="lbColor" offset="4" size="4" />
         <member type="LONG" name="lbHatch" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( LOGBRUSH32 )
   _XBST_UINT  ( lbStyle )
   _XBST_ULONG ( lbColor )
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LOGFONT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LOGFONT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LOGFONT structure.
         Defined as LOGFONT in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="LONG" name="lfHeight" offset="0" size="4" />
         <member type="LONG" name="lfWidth" offset="4" size="4" />
         <member type="LONG" name="lfEscapement" offset="8" size="4" />
         <member type="LONG" name="lfOrientation" offset="12" size="4" />
         <member type="LONG" name="lfWeight" offset="16" size="4" />
         <member type="BYTE" name="lfItalic" offset="20" size="1" />
         <member type="BYTE" name="lfUnderline" offset="21" size="1" />
         <member type="BYTE" name="lfStrikeOut" offset="22" size="1" />
         <member type="BYTE" name="lfCharSet" offset="23" size="1" />
         <member type="BYTE" name="lfOutPrecision" offset="24" size="1" />
         <member type="BYTE" name="lfClipPrecision" offset="25" size="1" />
         <member type="BYTE" name="lfQuality" offset="26" size="1" />
         <member type="BYTE" name="lfPitchAndFamily" offset="27" size="1" />
         <member type="SZSTR" name="lfFaceName" offset="28" size="LF_FACESIZE" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( LOGFONT )
   _XBST_LONG   ( lfHeight                 )
   _XBST_LONG   ( lfWidth                  )
   _XBST_LONG   ( lfEscapement             )
   _XBST_LONG   ( lfOrientation            )
   _XBST_LONG   ( lfWeight                 )
   _XBST_BYTE   ( lfItalic                 )
   _XBST_BYTE   ( lfUnderline              )
   _XBST_BYTE   ( lfStrikeOut              )
   _XBST_BYTE   ( lfCharSet                )
   _XBST_BYTE   ( lfOutPrecision           )
   _XBST_BYTE   ( lfClipPrecision          )
   _XBST_BYTE   ( lfQuality                )
   _XBST_BYTE   ( lfPitchAndFamily         )
   _XBST_SZSTR  ( lfFaceName , LF_FACESIZE )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BLENDFUNCTION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BLENDFUNCTION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BLENDFUNCTION structure.
         Defined as BLENDFUNCTION in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="BYTE" name="BlendOp" offset="0" size="1" />
         <member type="BYTE" name="BlendFlags" offset="1" size="1" />
         <member type="BYTE" name="SourceConstantAlpha" offset="2" size="1" />
         <member type="BYTE" name="AlphaFormat" offset="3" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( BLENDFUNCTION )
   _XBST_BYTE ( BlendOp             )
   _XBST_BYTE ( BlendFlags          )
   _XBST_BYTE ( SourceConstantAlpha )
   _XBST_BYTE ( AlphaFormat         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RGBQUAD</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RGBQUAD</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RGBQUAD structure.
         Defined as RGBQUAD in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="BYTE" name="rgbBlue" offset="0" size="1" />
         <member type="BYTE" name="rgbGreen" offset="1" size="1" />
         <member type="BYTE" name="rgbRed" offset="2" size="1" />
         <member type="BYTE" name="rgbReserved" offset="3" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( RGBQUAD )
   _XBST_BYTE ( rgbBlue     )
   _XBST_BYTE ( rgbGreen    )
   _XBST_BYTE ( rgbRed      )
   _XBST_BYTE ( rgbReserved )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BITMAPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BITMAPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BITMAPINFO structure.
         Defined as BITMAPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="WAPIST_BITMAPINFOHEADER" name="bmiHeader" offset="0" size="40" child="true" />
         <member type="WAPIST_RGBQUAD" name="bmiColors" offset="40" size="4" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( BITMAPINFO )
   _XBST_BITMAPINFOHEADER ( bmiHeader )
   _XBST_RGBQUAD          ( bmiColors )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SIZE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SIZE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SIZE structure.
         Defined as SIZE in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LONG" name="cx" offset="0" size="4" />
         <member type="LONG" name="cy" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( SIZE )
   _XBST_LONG ( cx )
   _XBST_LONG ( cy )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SIZEL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SIZEL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SIZEL structure.
         Defined as SIZEL in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LONG" name="cx" offset="0" size="4" />
         <member type="LONG" name="cy" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( SIZEL )
   _XBST_LONG ( cx )
   _XBST_LONG ( cy )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TRIVERTEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TRIVERTEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TRIVERTEX structure.
         Defined as TRIVERTEX in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="LONG" name="x" offset="0" size="4" />
         <member type="LONG" name="y" offset="4" size="4" />
         <member type="WORD" name="Red" offset="8" size="2" />
         <member type="WORD" name="Green" offset="10" size="2" />
         <member type="WORD" name="Blue" offset="12" size="2" />
         <member type="WORD" name="Alpha" offset="14" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( TRIVERTEX )
   _XBST_LONG ( x     )
   _XBST_LONG ( y     )
   _XBST_WORD ( Red   )
   _XBST_WORD ( Green )
   _XBST_WORD ( Blue  )
   _XBST_WORD ( Alpha )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PALETTEENTRY</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PALETTEENTRY</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PALETTEENTRY structure.
         Defined as PALETTEENTRY in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="BYTE" name="peRed" offset="0" size="1" />
         <member type="BYTE" name="peGreen" offset="1" size="1" />
         <member type="BYTE" name="peBlue" offset="2" size="1" />
         <member type="BYTE" name="peFlags" offset="3" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( PALETTEENTRY )
   _XBST_BYTE ( peRed   )
   _XBST_BYTE ( peGreen )
   _XBST_BYTE ( peBlue  )
   _XBST_BYTE ( peFlags )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LOGPALETTE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LOGPALETTE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LOGPALETTE structure.
         Defined as LOGPALETTE in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="WORD" name="palVersion" offset="0" size="2" />
         <member type="WORD" name="palNumEntries" offset="2" size="2" />
         <member type="WAPIST_PALETTEENTRY" name="palPalEntry0" offset="4" size="4" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( LOGPALETTE )
   _XBST_WORD         ( palVersion    )
   _XBST_WORD         ( palNumEntries )
   _XBST_PALETTEENTRY ( palPalEntry0  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_XFORM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_XFORM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi XFORM structure.
         Defined as XFORM in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="FLOAT" name="eM11" offset="0" size="4" />
         <member type="FLOAT" name="eM12" offset="4" size="4" />
         <member type="FLOAT" name="eM21" offset="8" size="4" />
         <member type="FLOAT" name="eM22" offset="12" size="4" />
         <member type="FLOAT" name="eDx" offset="16" size="4" />
         <member type="FLOAT" name="eDy" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( XFORM )
   _XBST_FLOAT ( eM11 )
   _XBST_FLOAT ( eM12 )
   _XBST_FLOAT ( eM21 )
   _XBST_FLOAT ( eM22 )
   _XBST_FLOAT ( eDx  )
   _XBST_FLOAT ( eDy  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RECT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RECT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RECT structure.
         Defined as RECT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="LONG" name="left" offset="0" size="4" />
         <member type="LONG" name="top" offset="4" size="4" />
         <member type="LONG" name="right" offset="8" size="4" />
         <member type="LONG" name="bottom" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( RECT )
   _XBST_LONG ( left   )
   _XBST_LONG ( top    )
   _XBST_LONG ( right  )
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RECTL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RECTL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RECTL structure.
         Defined as RECTL in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="LONG" name="left" offset="0" size="4" />
         <member type="LONG" name="top" offset="4" size="4" />
         <member type="LONG" name="right" offset="8" size="4" />
         <member type="LONG" name="bottom" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( RECTL )
   _XBST_LONG ( left   )
   _XBST_LONG ( top    )
   _XBST_LONG ( right  )
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ABC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ABC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ABC structure.
         Defined as ABC in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="INT" name="abcA" offset="0" size="4" />
         <member type="UINT" name="abcB" offset="4" size="4" />
         <member type="INT" name="abcC" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( ABC )
   _XBST_INT  ( abcA )
   _XBST_UINT ( abcB )
   _XBST_INT  ( abcC )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ABCFLOAT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ABCFLOAT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ABCFLOAT structure.
         Defined as ABCFLOAT in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="FLOAT" name="abcfA" offset="0" size="4" />
         <member type="FLOAT" name="abcfB" offset="4" size="4" />
         <member type="FLOAT" name="abcfC" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( ABCFLOAT )
   _XBST_FLOAT ( abcfA )
   _XBST_FLOAT ( abcfB )
   _XBST_FLOAT ( abcfC )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRAWTEXTPARAMS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRAWTEXTPARAMS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRAWTEXTPARAMS structure.
         Defined as DRAWTEXTPARAMS in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="INT" name="iTabLength" offset="4" size="4" />
         <member type="INT" name="iLeftMargin" offset="8" size="4" />
         <member type="INT" name="iRightMargin" offset="12" size="4" />
         <member type="UINT" name="uiLengthDrawn" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( DRAWTEXTPARAMS )
   _XBST_UINT ( cbSize        )
   _XBST_int  ( iTabLength    )
   _XBST_int  ( iLeftMargin   )
   _XBST_int  ( iRightMargin  )
   _XBST_UINT ( uiLengthDrawn )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENUMLOGFONT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENUMLOGFONT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENUMLOGFONT structure.
         Defined as ENUMLOGFONT in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_LOGFONT" name="elfLogFont" offset="0" size="28" child="true" />
         <member type="SZSTR" name="elfFullName" offset="28" size="LF_FULLFACESIZE" access="string" />
         <member type="SZSTR" name="elfStyle" offset="28" size="LF_FACESIZE" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( ENUMLOGFONT )
   _XBST_LOGFONT ( elfLogFont                    )
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENUMLOGFONTEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENUMLOGFONTEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENUMLOGFONTEX structure.
         Defined as ENUMLOGFONTEX in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_LOGFONT" name="elfLogFont" offset="0" size="28" child="true" />
         <member type="SZSTR" name="elfFullName" offset="28" size="LF_FULLFACESIZE" access="string" />
         <member type="SZSTR" name="elfStyle" offset="28" size="LF_FACESIZE" access="string" />
         <member type="SZSTR" name="elfScript" offset="28" size="LF_FACESIZE" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( ENUMLOGFONTEX )
   _XBST_LOGFONT ( elfLogFont                    )
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
   _XBST_SZSTR   ( elfScript   , LF_FACESIZE     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_EXTLOGFONT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_EXTLOGFONT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi EXTLOGFONT structure.
         Defined as EXTLOGFONT in ot4xb_wapist_map.ch.
      </description>
      <size>58</size>
      <members>
         <member type="WAPIST_LOGFONT" name="elfLogFont" offset="0" size="28" child="true" />
         <member type="SZSTR" name="elfFullName" offset="28" size="LF_FULLFACESIZE" access="string" />
         <member type="SZSTR" name="elfStyle" offset="28" size="LF_FACESIZE" access="string" />
         <member type="DWORD" name="elfVersion" offset="28" size="4" />
         <member type="DWORD" name="elfStyleSize" offset="32" size="4" />
         <member type="DWORD" name="elfMatch" offset="36" size="4" />
         <member type="DWORD" name="elfReserved" offset="40" size="4" />
         <member type="BINSTR" name="elfVendorId" offset="44" size="ELF_VENDOR_SIZE" />
         <member type="DWORD" name="elfCulture" offset="44" size="4" />
         <member type="WAPIST_PANOSE" name="elfPanose" offset="48" size="10" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( EXTLOGFONT )
   _XBST_LOGFONT ( elfLogFont                     )
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE  )
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE      )
   _XBST_DWORD   ( elfVersion                     )
   _XBST_DWORD   ( elfStyleSize                   )
   _XBST_DWORD   ( elfMatch                       )
   _XBST_DWORD   ( elfReserved                    )
   _XBST_BINSTR  ( elfVendorId , ELF_VENDOR_SIZE  )
   _XBST_DWORD   ( elfCulture                     )
   _XBST_PANOSE  ( elfPanose                      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FIXED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FIXED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FIXED structure.
         Defined as FIXED in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="WORD" name="fract" offset="0" size="2" />
         <member type="SHORT" name="value" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( FIXED )
   _XBST_WORD  ( fract )
   _XBST_short ( value )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GCP_RESULTS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GCP_RESULTS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GCP_RESULTS structure.
         Defined as GCP_RESULTS in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="DWORD" name="lStructSize" offset="0" size="4" />
         <member type="LPSTR" name="lpOutString" offset="4" size="4" />
         <member type="POINTER32" name="lpOrder" offset="8" size="4" />
         <member type="POINTER32" name="lpDx" offset="12" size="4" />
         <member type="POINTER32" name="lpCaretPos" offset="16" size="4" />
         <member type="LPSTR" name="lpClass" offset="20" size="4" />
         <member type="POINTER32" name="lpGlyphs" offset="24" size="4" />
         <member type="UINT" name="nGlyphs" offset="28" size="4" />
         <member type="INT" name="nMaxFit" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( GCP_RESULTS )
   _XBST_DWORD     ( lStructSize )
   _XBST_LPSTR     ( lpOutString )
   _XBST_POINTER32 ( lpOrder )
   _XBST_POINTER32 ( lpDx )
   _XBST_POINTER32 ( lpCaretPos )
   _XBST_LPSTR     ( lpClass )
   _XBST_POINTER32 ( lpGlyphs )
   _XBST_UINT      ( nGlyphs )
   _XBST_int       ( nMaxFit )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GLYPHMETRICS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GLYPHMETRICS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GLYPHMETRICS structure.
         Defined as GLYPHMETRICS in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="gmBlackBoxX" offset="0" size="4" />
         <member type="UINT" name="gmBlackBoxY" offset="4" size="4" />
         <member type="WAPIST_POINT" name="gmptGlyphOrigin" offset="8" size="8" child="true" />
         <member type="SHORT" name="gmCellIncX" offset="16" size="2" />
         <member type="SHORT" name="gmCellIncY" offset="18" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( GLYPHMETRICS )
   _XBST_UINT      ( gmBlackBoxX )
   _XBST_UINT      ( gmBlackBoxY )
   _XBST_POINT     ( gmptGlyphOrigin )
   _XBST_short     ( gmCellIncX )
   _XBST_short     ( gmCellIncY )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GLYPHSET</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GLYPHSET</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GLYPHSET structure.
         Defined as GLYPHSET in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="DWORD" name="cbThis" offset="0" size="4" />
         <member type="DWORD" name="flAccel" offset="4" size="4" />
         <member type="DWORD" name="cGlyphsSupported" offset="8" size="4" />
         <member type="DWORD" name="cRanges" offset="12" size="4" />
         <member type="WAPIST_WCRANGE" name="ranges0" offset="16" size="4" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( GLYPHSET )
   _XBST_DWORD   ( cbThis )
   _XBST_DWORD   ( flAccel )
   _XBST_DWORD   ( cGlyphsSupported )
   _XBST_DWORD   ( cRanges )
   _XBST_WCRANGE ( ranges0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_KERNINGPAIR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_KERNINGPAIR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi KERNINGPAIR structure.
         Defined as KERNINGPAIR in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="WORD" name="wFirst" offset="0" size="2" />
         <member type="WORD" name="wSecond" offset="2" size="2" />
         <member type="INT" name="iKernAmount" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( KERNINGPAIR )
   _XBST_WORD ( wFirst )
   _XBST_WORD ( wSecond )
   _XBST_int  ( iKernAmount )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MAT2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MAT2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MAT2 structure.
         Defined as MAT2 in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_FIXED" name="eM11" offset="0" size="4" child="true" />
         <member type="WAPIST_FIXED" name="eM12" offset="4" size="4" child="true" />
         <member type="WAPIST_FIXED" name="eM21" offset="8" size="4" child="true" />
         <member type="WAPIST_FIXED" name="eM22" offset="12" size="4" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( MAT2 )
   _XBST_FIXED ( eM11 )
   _XBST_FIXED ( eM12 )
   _XBST_FIXED ( eM21 )
   _XBST_FIXED ( eM22 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NEWTEXTMETRIC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NEWTEXTMETRIC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NEWTEXTMETRIC structure.
         Defined as NEWTEXTMETRIC in ot4xb_wapist_map.ch.
      </description>
      <size>69</size>
      <members>
         <member type="LONG" name="tmHeight" offset="0" size="4" />
         <member type="LONG" name="tmAscent" offset="4" size="4" />
         <member type="LONG" name="tmDescent" offset="8" size="4" />
         <member type="LONG" name="tmInternalLeading" offset="12" size="4" />
         <member type="LONG" name="tmExternalLeading" offset="16" size="4" />
         <member type="LONG" name="tmAveCharWidth" offset="20" size="4" />
         <member type="LONG" name="tmMaxCharWidth" offset="24" size="4" />
         <member type="LONG" name="tmWeight" offset="28" size="4" />
         <member type="LONG" name="tmOverhang" offset="32" size="4" />
         <member type="LONG" name="tmDigitizedAspectX" offset="36" size="4" />
         <member type="LONG" name="tmDigitizedAspectY" offset="40" size="4" />
         <member type="BYTE" name="tmFirstChar" offset="44" size="1" />
         <member type="BYTE" name="tmLastChar" offset="45" size="1" />
         <member type="BYTE" name="tmDefaultChar" offset="46" size="1" />
         <member type="BYTE" name="tmBreakChar" offset="47" size="1" />
         <member type="BYTE" name="tmItalic" offset="48" size="1" />
         <member type="BYTE" name="tmUnderlined" offset="49" size="1" />
         <member type="BYTE" name="tmStruckOut" offset="50" size="1" />
         <member type="BYTE" name="tmPitchAndFamily" offset="51" size="1" />
         <member type="BYTE" name="tmCharSet" offset="52" size="1" />
         <member type="DWORD" name="ntmFlags" offset="53" size="4" />
         <member type="UINT" name="ntmSizeEM" offset="57" size="4" />
         <member type="UINT" name="ntmCellHeight" offset="61" size="4" />
         <member type="UINT" name="ntmAvgWidth" offset="65" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( NEWTEXTMETRIC )
   _XBST_LONG  ( tmHeight           )
   _XBST_LONG  ( tmAscent           )
   _XBST_LONG  ( tmDescent          )
   _XBST_LONG  ( tmInternalLeading  )
   _XBST_LONG  ( tmExternalLeading  )
   _XBST_LONG  ( tmAveCharWidth     )
   _XBST_LONG  ( tmMaxCharWidth     )
   _XBST_LONG  ( tmWeight           )
   _XBST_LONG  ( tmOverhang         )
   _XBST_LONG  ( tmDigitizedAspectX )
   _XBST_LONG  ( tmDigitizedAspectY )
   _XBST_TCHAR ( tmFirstChar        )
   _XBST_TCHAR ( tmLastChar         )
   _XBST_TCHAR ( tmDefaultChar      )
   _XBST_TCHAR ( tmBreakChar        )
   _XBST_BYTE  ( tmItalic           )
   _XBST_BYTE  ( tmUnderlined       )
   _XBST_BYTE  ( tmStruckOut        )
   _XBST_BYTE  ( tmPitchAndFamily   )
   _XBST_BYTE  ( tmCharSet          )
   _XBST_DWORD ( ntmFlags           )
   _XBST_UINT  ( ntmSizeEM          )
   _XBST_UINT  ( ntmCellHeight      )
   _XBST_UINT  ( ntmAvgWidth        )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NEWTEXTMETRICEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NEWTEXTMETRICEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NEWTEXTMETRICEX structure.
         Defined as NEWTEXTMETRICEX in ot4xb_wapist_map.ch.
      </description>
      <size>93</size>
      <members>
         <member type="WAPIST_NEWTEXTMETRIC" name="ntmTm" offset="0" size="69" child="true" />
         <member type="WAPIST_FONTSIGNATURE" name="ntmFontSig" offset="69" size="24" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( NEWTEXTMETRICEX )
   _XBST_NEWTEXTMETRIC ( ntmTm      )
   _XBST_FONTSIGNATURE ( ntmFontSig )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OUTLINETEXTMETRIC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OUTLINETEXTMETRIC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi OUTLINETEXTMETRIC structure.
         Defined as OUTLINETEXTMETRIC in ot4xb_wapist_map.ch.
      </description>
      <size>208</size>
      <members>
         <member type="UINT" name="otmSize" offset="0" size="4" />
         <member type="WAPIST_TEXTMETRIC" name="otmTextMetrics" offset="4" size="53" child="true" />
         <member type="BYTE" name="otmFiller" offset="57" size="1" />
         <member type="WAPIST_PANOSE" name="otmPanoseNumber" offset="58" size="10" child="true" />
         <member type="UINT" name="otmfsSelection" offset="68" size="4" />
         <member type="UINT" name="otmfsType" offset="72" size="4" />
         <member type="INT" name="otmsCharSlopeRise" offset="76" size="4" />
         <member type="INT" name="otmsCharSlopeRun" offset="80" size="4" />
         <member type="INT" name="otmItalicAngle" offset="84" size="4" />
         <member type="UINT" name="otmEMSquare" offset="88" size="4" />
         <member type="INT" name="otmAscent" offset="92" size="4" />
         <member type="INT" name="otmDescent" offset="96" size="4" />
         <member type="UINT" name="otmLineGap" offset="100" size="4" />
         <member type="UINT" name="otmsCapEmHeight" offset="104" size="4" />
         <member type="UINT" name="otmsXHeight" offset="108" size="4" />
         <member type="WAPIST_RECT" name="otmrcFontBox" offset="112" size="16" child="true" />
         <member type="INT" name="otmMacAscent" offset="128" size="4" />
         <member type="INT" name="otmMacDescent" offset="132" size="4" />
         <member type="UINT" name="otmMacLineGap" offset="136" size="4" />
         <member type="UINT" name="otmusMinimumPPEM" offset="140" size="4" />
         <member type="WAPIST_POINT" name="otmptSubscriptSize" offset="144" size="8" child="true" />
         <member type="WAPIST_POINT" name="otmptSubscriptOffset" offset="152" size="8" child="true" />
         <member type="WAPIST_POINT" name="otmptSuperscriptSize" offset="160" size="8" child="true" />
         <member type="WAPIST_POINT" name="otmptSuperscriptOffset" offset="168" size="8" child="true" />
         <member type="UINT" name="otmsStrikeoutSize" offset="176" size="4" />
         <member type="INT" name="otmsStrikeoutPosition" offset="180" size="4" />
         <member type="INT" name="otmsUnderscoreSize" offset="184" size="4" />
         <member type="INT" name="otmsUnderscorePosition" offset="188" size="4" />
         <member type="LPSTR" name="otmpFamilyName" offset="192" size="4" />
         <member type="LPSTR" name="otmpFaceName" offset="196" size="4" />
         <member type="LPSTR" name="otmpStyleName" offset="200" size="4" />
         <member type="LPSTR" name="otmpFullName" offset="204" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( OUTLINETEXTMETRIC )
   _XBST_UINT       ( otmSize                   )
   _XBST_TEXTMETRIC ( otmTextMetrics            )
   _XBST_BYTE       ( otmFiller                 )
   _XBST_PANOSE     ( otmPanoseNumber           )
   _XBST_UINT       ( otmfsSelection            )
   _XBST_UINT       ( otmfsType                 )
   _XBST_int        ( otmsCharSlopeRise         )
   _XBST_int        ( otmsCharSlopeRun          )
   _XBST_int        ( otmItalicAngle            )
   _XBST_UINT       ( otmEMSquare               )
   _XBST_int        ( otmAscent                 )
   _XBST_int        ( otmDescent                )
   _XBST_UINT       ( otmLineGap                )
   _XBST_UINT       ( otmsCapEmHeight           )
   _XBST_UINT       ( otmsXHeight               )
   _XBST_RECT       ( otmrcFontBox              )
   _XBST_int        ( otmMacAscent              )
   _XBST_int        ( otmMacDescent             )
   _XBST_UINT       ( otmMacLineGap             )
   _XBST_UINT       ( otmusMinimumPPEM          )
   _XBST_POINT      ( otmptSubscriptSize        )
   _XBST_POINT      ( otmptSubscriptOffset      )
   _XBST_POINT      ( otmptSuperscriptSize      )
   _XBST_POINT      ( otmptSuperscriptOffset    )
   _XBST_UINT       ( otmsStrikeoutSize         )
   _XBST_int        ( otmsStrikeoutPosition     )
   _XBST_int        ( otmsUnderscoreSize        )
   _XBST_int        ( otmsUnderscorePosition    )
   _XBST_LPSTR      ( otmpFamilyName            )
   _XBST_LPSTR      ( otmpFaceName              )
   _XBST_LPSTR      ( otmpStyleName             )
   _XBST_LPSTR      ( otmpFullName              )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PANOSE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PANOSE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PANOSE structure.
         Defined as PANOSE in ot4xb_wapist_map.ch.
      </description>
      <size>10</size>
      <members>
         <member type="BYTE" name="bFamilyType" offset="0" size="1" />
         <member type="BYTE" name="bSerifStyle" offset="1" size="1" />
         <member type="BYTE" name="bWeight" offset="2" size="1" />
         <member type="BYTE" name="bProportion" offset="3" size="1" />
         <member type="BYTE" name="bContrast" offset="4" size="1" />
         <member type="BYTE" name="bStrokeVariation" offset="5" size="1" />
         <member type="BYTE" name="bArmStyle" offset="6" size="1" />
         <member type="BYTE" name="bLetterform" offset="7" size="1" />
         <member type="BYTE" name="bMidline" offset="8" size="1" />
         <member type="BYTE" name="bXHeight" offset="9" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( PANOSE )
   _XBST_BYTE ( bFamilyType      )
   _XBST_BYTE ( bSerifStyle      )
   _XBST_BYTE ( bWeight          )
   _XBST_BYTE ( bProportion      )
   _XBST_BYTE ( bContrast        )
   _XBST_BYTE ( bStrokeVariation )
   _XBST_BYTE ( bArmStyle        )
   _XBST_BYTE ( bLetterform      )
   _XBST_BYTE ( bMidline         )
   _XBST_BYTE ( bXHeight         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_POINTFX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_POINTFX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi POINTFX structure.
         Defined as POINTFX in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="WAPIST_FIXED" name="x" offset="0" size="4" child="true" />
         <member type="WAPIST_FIXED" name="y" offset="4" size="4" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( POINTFX )
   _XBST_FIXED ( x )
   _XBST_FIXED ( y )

XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_POLYTEXT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_POLYTEXT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi POLYTEXT structure.
         Defined as POLYTEXT in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="INT" name="x" offset="0" size="4" />
         <member type="INT" name="y" offset="4" size="4" />
         <member type="UINT" name="n" offset="8" size="4" />
         <member type="LPSTR" name="lpstr" offset="12" size="4" />
         <member type="UINT" name="uiFlags" offset="16" size="4" />
         <member type="WAPIST_RECT" name="rcl" offset="20" size="16" child="true" />
         <member type="POINTER32" name="pdx" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE ( POLYTEXT )
   _XBST_int       ( x       )
   _XBST_int       ( y       )
   _XBST_UINT      ( n       )
   _XBST_LPSTR     ( lpstr   )
   _XBST_UINT      ( uiFlags )
   _XBST_RECT      ( rcl     )
   _XBST_POINTER32 ( pdx     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RASTERIZER_STATUS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RASTERIZER_STATUS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RASTERIZER_STATUS structure.
         Defined as RASTERIZER_STATUS in ot4xb_wapist_map.ch.
      </description>
      <size>6</size>
      <members>
         <member type="SHORT" name="nSize" offset="0" size="2" />
         <member type="SHORT" name="wFlags" offset="2" size="2" />
         <member type="SHORT" name="nLanguageID" offset="4" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RASTERIZER_STATUS )
_XBST_short( nSize )
_XBST_short( wFlags )
_XBST_short( nLanguageID )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TEXTMETRIC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TEXTMETRIC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TEXTMETRIC structure.
         Defined as TEXTMETRIC in ot4xb_wapist_map.ch.
      </description>
      <size>53</size>
      <members>
         <member type="LONG" name="tmHeight" offset="0" size="4" />
         <member type="LONG" name="tmAscent" offset="4" size="4" />
         <member type="LONG" name="tmDescent" offset="8" size="4" />
         <member type="LONG" name="tmInternalLeading" offset="12" size="4" />
         <member type="LONG" name="tmExternalLeading" offset="16" size="4" />
         <member type="LONG" name="tmAveCharWidth" offset="20" size="4" />
         <member type="LONG" name="tmMaxCharWidth" offset="24" size="4" />
         <member type="LONG" name="tmWeight" offset="28" size="4" />
         <member type="LONG" name="tmOverhang" offset="32" size="4" />
         <member type="LONG" name="tmDigitizedAspectX" offset="36" size="4" />
         <member type="LONG" name="tmDigitizedAspectY" offset="40" size="4" />
         <member type="BYTE" name="tmFirstChar" offset="44" size="1" />
         <member type="BYTE" name="tmLastChar" offset="45" size="1" />
         <member type="BYTE" name="tmDefaultChar" offset="46" size="1" />
         <member type="BYTE" name="tmBreakChar" offset="47" size="1" />
         <member type="BYTE" name="tmItalic" offset="48" size="1" />
         <member type="BYTE" name="tmUnderlined" offset="49" size="1" />
         <member type="BYTE" name="tmStruckOut" offset="50" size="1" />
         <member type="BYTE" name="tmPitchAndFamily" offset="51" size="1" />
         <member type="BYTE" name="tmCharSet" offset="52" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TEXTMETRIC )
_XBST_LONG( tmHeight )
_XBST_LONG( tmAscent )
_XBST_LONG( tmDescent )
_XBST_LONG( tmInternalLeading )
_XBST_LONG( tmExternalLeading )
_XBST_LONG( tmAveCharWidth )
_XBST_LONG( tmMaxCharWidth )
_XBST_LONG( tmWeight )
_XBST_LONG( tmOverhang )
_XBST_LONG( tmDigitizedAspectX )
_XBST_LONG( tmDigitizedAspectY )
_XBST_TCHAR( tmFirstChar )
_XBST_TCHAR( tmLastChar )
_XBST_TCHAR( tmDefaultChar )
_XBST_TCHAR( tmBreakChar )
_XBST_BYTE( tmItalic )
_XBST_BYTE( tmUnderlined )
_XBST_BYTE( tmStruckOut )
_XBST_BYTE( tmPitchAndFamily )
_XBST_BYTE( tmCharSet )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TTPOLYCURVE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TTPOLYCURVE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TTPOLYCURVE structure.
         Defined as TTPOLYCURVE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WORD" name="wType" offset="0" size="2" />
         <member type="WORD" name="cpfx" offset="2" size="2" />
         <member type="WAPIST_POINTFX" name="apfx0" offset="4" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TTPOLYCURVE )
_XBST_WORD( wType )
_XBST_WORD( cpfx )
_XBST_POINTFX( apfx0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TTPOLYGONHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TTPOLYGONHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TTPOLYGONHEADER structure.
         Defined as TTPOLYGONHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="cb" offset="0" size="4" />
         <member type="DWORD" name="dwType" offset="4" size="4" />
         <member type="WAPIST_POINTFX" name="pfxStart" offset="8" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TTPOLYGONHEADER )
_XBST_DWORD( cb )
_XBST_DWORD( dwType )
_XBST_POINTFX( pfxStart )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WCRANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WCRANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WCRANGE structure.
         Defined as WCRANGE in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="SHORT" name="wcLow" offset="0" size="2" />
         <member type="USHORT" name="cGlyphs" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WCRANGE )
_XBST_short( wcLow )
_XBST_USHORT( cGlyphs )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FONTSIGNATURE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FONTSIGNATURE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FONTSIGNATURE structure.
         Defined as FONTSIGNATURE in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="DWORD" name="fsUsb0" offset="0" size="4" />
         <member type="DWORD" name="fsUsb1" offset="4" size="4" />
         <member type="DWORD" name="fsUsb2" offset="8" size="4" />
         <member type="DWORD" name="fsUsb3" offset="12" size="4" />
         <member type="DWORD" name="fsCsb0" offset="16" size="4" />
         <member type="DWORD" name="fsCsb1" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FONTSIGNATURE )
_XBST_DWORD( fsUsb0 )
_XBST_DWORD( fsUsb1 )
_XBST_DWORD( fsUsb2 )
_XBST_DWORD( fsUsb3 )
_XBST_DWORD( fsCsb0 )
_XBST_DWORD( fsCsb1 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MONITORINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MONITORINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MONITORINFO structure.
         Defined as MONITORINFO in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcMonitor" offset="4" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcWork" offset="20" size="16" child="true" />
         <member type="DWORD" name="dwFlags" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MONITORINFO )
_XBST_DWORD( cbSize )
_XBST_RECT( rcMonitor )
_XBST_RECT( rcWork )
_XBST_DWORD( dwFlags )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MONITORINFOEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MONITORINFOEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MONITORINFOEX structure.
         Defined as MONITORINFOEX in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcMonitor" offset="4" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcWork" offset="20" size="16" child="true" />
         <member type="DWORD" name="dwFlags" offset="36" size="4" />
         <member type="SZSTR" name="szDevice" offset="40" size="CCHDEVICENAME" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MONITORINFOEX )
_XBST_DWORD( cbSize )
_XBST_RECT( rcMonitor )
_XBST_RECT( rcWork )
_XBST_DWORD( dwFlags )
_XBST_SZSTR( szDevice, CCHDEVICENAME )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PAINTSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PAINTSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PAINTSTRUCT structure.
         Defined as PAINTSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <size>64</size>
      <members>
         <member type="HDC" name="hdc" offset="0" size="4" />
         <member type="BOOL" name="fErase" offset="4" size="4" />
         <member type="WAPIST_RECT" name="rcPaint" offset="8" size="16" child="true" />
         <member type="BOOL" name="fRestore" offset="24" size="4" />
         <member type="BOOL" name="fIncUpdate" offset="28" size="4" />
         <member type="BINSTR" name="rgbReserved" offset="32" size="32" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PAINTSTRUCT )
_XBST_HDC( hdc )
_XBST_BOOL( fErase )
_XBST_RECT( rcPaint )
_XBST_BOOL( fRestore )
_XBST_BOOL( fIncUpdate )
_XBST_BINSTR( rgbReserved, 32 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SYSTEMTIME</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SYSTEMTIME</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SYSTEMTIME structure.
         Defined as SYSTEMTIME in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WORD" name="wYear" offset="0" size="2" />
         <member type="WORD" name="wMonth" offset="2" size="2" />
         <member type="WORD" name="wDayOfWeek" offset="4" size="2" />
         <member type="WORD" name="wDay" offset="6" size="2" />
         <member type="WORD" name="wHour" offset="8" size="2" />
         <member type="WORD" name="wMinute" offset="10" size="2" />
         <member type="WORD" name="wSecond" offset="12" size="2" />
         <member type="WORD" name="wMilliseconds" offset="14" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SYSTEMTIME )
_XBST_WORD( wYear )
_XBST_WORD( wMonth )
_XBST_WORD( wDayOfWeek )
_XBST_WORD( wDay )
_XBST_WORD( wHour )
_XBST_WORD( wMinute )
_XBST_WORD( wSecond )
_XBST_WORD( wMilliseconds )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ADDJOB_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ADDJOB_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ADDJOB_INFO_1 structure.
         Defined as ADDJOB_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LPSTR" name="Path" offset="0" size="4" />
         <member type="DWORD" name="JobId" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ADDJOB_INFO_1 )
_XBST_LPSTR( Path )
_XBST_DWORD( JobId )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DATATYPES_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DATATYPES_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DATATYPES_INFO_1 structure.
         Defined as DATATYPES_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DATATYPES_INFO_1 )
_XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DEVMODEA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DEVMODEA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DEVMODEA structure.
         Defined as DEVMODEA in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-devmodea</ref-url>
      <size>124</size>
      <members>
         <member type="SZSTR" name="dmDeviceName" offset="0" size="32" access="string" />
         <member type="WORD" name="dmSpecVersion" offset="32" size="2" />
         <member type="WORD" name="dmDriverVersion" offset="34" size="2" />
         <member type="WORD" name="dmSize" offset="36" size="2" />
         <member type="WORD" name="dmDriverExtra" offset="38" size="2" />
         <member type="DWORD" name="dmFields" offset="40" size="4" />
         <union offset="44" size="16">
            <struct offset="44" size="16">
               <member type="SHORT" name="dmOrientation" offset="44" size="2" />
               <member type="SHORT" name="dmPaperSize" offset="46" size="2" />
               <member type="SHORT" name="dmPaperLength" offset="48" size="2" />
               <member type="SHORT" name="dmPaperWidth" offset="50" size="2" />
               <member type="SHORT" name="dmScale" offset="52" size="2" />
               <member type="SHORT" name="dmCopies" offset="54" size="2" />
               <member type="SHORT" name="dmDefaultSource" offset="56" size="2" />
               <member type="SHORT" name="dmPrintQuality" offset="58" size="2" />
            </struct>
            <member type="WAPIST_POINTL" name="dmPosition" offset="44" size="8" child="true" />
            <member type="DWORD" name="dmDisplayOrientation" offset="44" size="4" />
            <member type="DWORD" name="dmDisplayFixedOutput" offset="44" size="4" />
         </union>
         <member type="SHORT" name="dmColor" offset="60" size="2" />
         <member type="SHORT" name="dmDuplex" offset="62" size="2" />
         <member type="SHORT" name="dmYResolution" offset="64" size="2" />
         <member type="SHORT" name="dmTTOption" offset="66" size="2" />
         <member type="SHORT" name="dmCollate" offset="68" size="2" />
         <member type="SZSTR" name="dmFormName" offset="70" size="32" access="string" />
         <member type="WORD" name="dmLogPixels" offset="102" size="2" />
         <member type="DWORD" name="dmBitsPerPel" offset="104" size="4" />
         <member type="DWORD" name="dmPelsWidth" offset="108" size="4" />
         <member type="DWORD" name="dmPelsHeight" offset="112" size="4" />
         <union offset="116" size="4">
            <member type="DWORD" name="dmDisplayFlags" offset="116" size="4" />
            <member type="DWORD" name="dmNup" offset="116" size="4" />
         </union>
         <member type="DWORD" name="dmDisplayFrequency" offset="120" size="4" />
         <member type="DWORD" name="dmICMMethod" offset="124" size="4" />
         <member type="DWORD" name="dmICMIntent" offset="128" size="4" />
         <member type="DWORD" name="dmMediaType" offset="132" size="4" />
         <member type="DWORD" name="dmDitherType" offset="136" size="4" />
         <member type="DWORD" name="dmReserved1" offset="140" size="4" />
         <member type="DWORD" name="dmReserved2" offset="144" size="4" />
         <member type="DWORD" name="dmPanningWidth" offset="148" size="4" />
         <member type="DWORD" name="dmPanningHeight" offset="152" size="4" />
      </members>
   </class>
   <class>
      <name>WAPIST_DEVMODEW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DEVMODEW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DEVMODEW structure.
         Defined as DEVMODEW in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-devmodew</ref-url>
      <size>188</size>
      <members>
         <member type="SZWSTR" name="dmDeviceName" offset="0" size="64" chars="32" access="string" />
         <member type="WORD" name="dmSpecVersion" offset="64" size="2" />
         <member type="WORD" name="dmDriverVersion" offset="66" size="2" />
         <member type="WORD" name="dmSize" offset="68" size="2" />
         <member type="WORD" name="dmDriverExtra" offset="70" size="2" />
         <member type="DWORD" name="dmFields" offset="72" size="4" />
         <union offset="76" size="16">
            <struct offset="76" size="16">
               <member type="SHORT" name="dmOrientation" offset="76" size="2" />
               <member type="SHORT" name="dmPaperSize" offset="78" size="2" />
               <member type="SHORT" name="dmPaperLength" offset="80" size="2" />
               <member type="SHORT" name="dmPaperWidth" offset="82" size="2" />
               <member type="SHORT" name="dmScale" offset="84" size="2" />
               <member type="SHORT" name="dmCopies" offset="86" size="2" />
               <member type="SHORT" name="dmDefaultSource" offset="88" size="2" />
               <member type="SHORT" name="dmPrintQuality" offset="90" size="2" />
            </struct>
            <member type="WAPIST_POINTL" name="dmPosition" offset="76" size="8" child="true" />
            <member type="DWORD" name="dmDisplayOrientation" offset="76" size="4" />
            <member type="DWORD" name="dmDisplayFixedOutput" offset="76" size="4" />
         </union>
         <member type="SHORT" name="dmColor" offset="92" size="2" />
         <member type="SHORT" name="dmDuplex" offset="94" size="2" />
         <member type="SHORT" name="dmYResolution" offset="96" size="2" />
         <member type="SHORT" name="dmTTOption" offset="98" size="2" />
         <member type="SHORT" name="dmCollate" offset="100" size="2" />
         <member type="SZSTR" name="dmFormName" offset="102" size="32" access="string" />
         <member type="WORD" name="dmLogPixels" offset="134" size="2" />
         <member type="DWORD" name="dmBitsPerPel" offset="136" size="4" />
         <member type="DWORD" name="dmPelsWidth" offset="140" size="4" />
         <member type="DWORD" name="dmPelsHeight" offset="144" size="4" />
         <union offset="148" size="4">
            <member type="DWORD" name="dmDisplayFlags" offset="148" size="4" />
            <member type="DWORD" name="dmNup" offset="148" size="4" />
         </union>
         <member type="DWORD" name="dmDisplayFrequency" offset="152" size="4" />
         <member type="DWORD" name="dmICMMethod" offset="156" size="4" />
         <member type="DWORD" name="dmICMIntent" offset="160" size="4" />
         <member type="DWORD" name="dmMediaType" offset="164" size="4" />
         <member type="DWORD" name="dmDitherType" offset="168" size="4" />
         <member type="DWORD" name="dmReserved1" offset="172" size="4" />
         <member type="DWORD" name="dmReserved2" offset="176" size="4" />
         <member type="DWORD" name="dmPanningWidth" offset="180" size="4" />
         <member type="DWORD" name="dmPanningHeight" offset="184" size="4" />
      </members>
   </class>
   <compatibility>
      WAPIST_DEVMODE is the neutral compatibility export mapped to WAPIST_DEVMODEW.
      It is not a separate class; it returns the Unicode DEVMODEW class object.
   </compatibility>
</xbdoc>
*******************************************************************************************************************/
static void __cdecl devmode_structure( XppParamList pl, BOOL bUnicode );
// WAPIST_DEVMODE is intentionally kept as the neutral compatibility export mapped to WAPIST_DEVMODEW.
// It returns the Unicode DEVMODEW class object rather than creating a separate neutral class.
void __cdecl WAPIST_DEVMODE( XppParamList pl )
{
   devmode_structure( pl, TRUE );
}
void __cdecl WAPIST_DEVMODEW( XppParamList pl )
{
   devmode_structure( pl, TRUE );
}
void __cdecl WAPIST_DEVMODEA( XppParamList pl )
{
   devmode_structure( pl, FALSE );
}

static void __cdecl devmode_structure( XppParamList pl , BOOL bUnicode )
{
      ContainerHandle conco = _conClsObj( bUnicode ?  "WAPIST_DEVMODEW" : "WAPIST_DEVMODEA");

   if( conco == ( (ContainerHandle) ( (MomHandle) 0 ) ) )
   {
      TXbClass* pc = new TXbClass; pc->ClassName( bUnicode ? "WAPIST_DEVMODEW" : "WAPIST_DEVMODEA"  ); pc->GwstParent(); pc->EXPORTED(); pc->GwstReadWrite();
      if( bUnicode )
      {
         _XBST_SZWSTR( dmDeviceName, CCHDEVICENAME )
      }
      else
      {
         _XBST_SZSTR( dmDeviceName, CCHDEVICENAME )
      }

         _XBST_WORD( dmSpecVersion )
         _XBST_WORD( dmDriverVersion )
         _XBST_WORD( dmSize )
         _XBST_WORD( dmDriverExtra )
         _XBST_DWORD( dmFields )
      {
         UINT nP1 = pc->GwstGetOffset();
         UINT nMax;
         {
            _XBST_short( dmOrientation )
               _XBST_short( dmPaperSize )
               _XBST_short( dmPaperLength )
               _XBST_short( dmPaperWidth )
               _XBST_short( dmScale )
               _XBST_short( dmCopies )
               _XBST_short( dmDefaultSource )
               _XBST_short( dmPrintQuality )
         }
         nMax = pc->GwstGetOffset(); pc->GwstSetOffset( nP1 );
         _XBST_POINTL( dmPosition )
            if( pc->GwstGetOffset() > nMax ) { nMax = pc->GwstGetOffset(); } pc->GwstSetOffset( nP1 );
         _XBST_DWORD( dmDisplayOrientation )
            if( pc->GwstGetOffset() > nMax ) { nMax = pc->GwstGetOffset(); } pc->GwstSetOffset( nP1 );
         _XBST_DWORD( dmDisplayFixedOutput )
            if( pc->GwstGetOffset() < nMax ) pc->GwstSetOffset( nMax );
      }
      _XBST_short( dmColor )
         _XBST_short( dmDuplex )
         _XBST_short( dmYResolution )
         _XBST_short( dmTTOption )
         _XBST_short( dmCollate )
         _XBST_SZSTR( dmFormName, CCHFORMNAME )
         _XBST_WORD( dmLogPixels )
         _XBST_DWORD( dmBitsPerPel )
         _XBST_DWORD( dmPelsWidth )
         _XBST_DWORD( dmPelsHeight )
         pc->GwstBeginUnion();
      _XBST_DWORD( dmDisplayFlags )
         _XBST_DWORD( dmNup )
         pc->GwstEndUnion();
      _XBST_DWORD( dmDisplayFrequency )
         _XBST_DWORD( dmICMMethod )
         _XBST_DWORD( dmICMIntent )
         _XBST_DWORD( dmMediaType )
         _XBST_DWORD( dmDitherType )
         _XBST_DWORD( dmReserved1 )
         _XBST_DWORD( dmReserved2 )
         _XBST_DWORD( dmPanningWidth )
         _XBST_DWORD( dmPanningHeight )
         conco = pc->Create(); delete pc;
      if( conco == ( (ContainerHandle) ( (MomHandle) 0 ) ) )
      {
         _ret( pl ); return;
      }
   } _conReturn( pl, conco ); _conRelease( conco );
}

// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DOC_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DOC_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DOC_INFO_1 structure.
         Defined as DOC_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="LPSTR" name="pDocName" offset="0" size="4" />
         <member type="LPSTR" name="pOutputFile" offset="4" size="4" />
         <member type="LPSTR" name="pDatatype" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DOC_INFO_1 )
  _XBST_LPSTR( pDocName     )
  _XBST_LPSTR( pOutputFile  )
  _XBST_LPSTR( pDatatype    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DOC_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DOC_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DOC_INFO_2 structure.
         Defined as DOC_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="LPSTR" name="pDocName" offset="0" size="4" />
         <member type="LPSTR" name="pOutputFile" offset="4" size="4" />
         <member type="LPSTR" name="pDatatype" offset="8" size="4" />
         <member type="DWORD" name="dwMode" offset="12" size="4" />
         <member type="DWORD" name="JobId" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DOC_INFO_2 )
  _XBST_LPSTR( pDocName    )
  _XBST_LPSTR( pOutputFile )
  _XBST_LPSTR( pDatatype   )
  _XBST_DWORD( dwMode      )
  _XBST_DWORD( JobId       )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DOC_INFO_3</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DOC_INFO_3</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DOC_INFO_3 structure.
         Defined as DOC_INFO_3 in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="LPSTR" name="pDocName" offset="0" size="4" />
         <member type="LPSTR" name="pOutputFile" offset="4" size="4" />
         <member type="LPSTR" name="pDatatype" offset="8" size="4" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DOC_INFO_3 )
  _XBST_LPSTR( pDocName    )
  _XBST_LPSTR( pOutputFile )
  _XBST_LPSTR( pDatatype   )
  _XBST_DWORD( dwFlags     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DOCINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DOCINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DOCINFO structure.
         Defined as DOCINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="INT" name="cbSize" offset="0" size="4" />
         <member type="LPSTR" name="lpszDocName" offset="4" size="4" />
         <member type="LPSTR" name="lpszOutput" offset="8" size="4" />
         <member type="LPSTR" name="lpszDatatype" offset="12" size="4" />
         <member type="DWORD" name="fwType" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DOCINFO )
  _XBST_int   (  cbSize         )
  _XBST_LPSTR (  lpszDocName    )
  _XBST_LPSTR (  lpszOutput     )
  _XBST_LPSTR (  lpszDatatype   )
  _XBST_DWORD (  fwType         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRAWPATRECT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRAWPATRECT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRAWPATRECT structure.
         Defined as DRAWPATRECT in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_POINT" name="ptPosition" offset="0" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptSize" offset="8" size="8" child="true" />
         <member type="WORD" name="wStyle" offset="16" size="2" />
         <member type="WORD" name="wPattern" offset="18" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRAWPATRECT )
   _XBST_POINT ( ptPosition  )
   _XBST_POINT ( ptSize      )
   _XBST_WORD  ( wStyle      )
   _XBST_WORD  ( wPattern    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_1 structure.
         Defined as DRIVER_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_2 structure.
         Defined as DRIVER_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="DWORD" name="cVersion" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="8" size="4" />
         <member type="LPSTR" name="pDriverPath" offset="12" size="4" />
         <member type="LPSTR" name="pDataFile" offset="16" size="4" />
         <member type="LPSTR" name="pConfigFile" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_2 )
   _XBST_DWORD ( cVersion      )
   _XBST_LPSTR ( pName         )
   _XBST_LPSTR ( pEnvironment  )
   _XBST_LPSTR ( pDriverPath   )
   _XBST_LPSTR ( pDataFile     )
   _XBST_LPSTR ( pConfigFile   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_3</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_3</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_3 structure.
         Defined as DRIVER_INFO_3 in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="DWORD" name="cVersion" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="8" size="4" />
         <member type="LPSTR" name="pDriverPath" offset="12" size="4" />
         <member type="LPSTR" name="pDataFile" offset="16" size="4" />
         <member type="LPSTR" name="pConfigFile" offset="20" size="4" />
         <member type="LPSTR" name="pHelpFile" offset="24" size="4" />
         <member type="LPSTR" name="pDependentFiles" offset="28" size="4" />
         <member type="LPSTR" name="pMonitorName" offset="32" size="4" />
         <member type="LPSTR" name="pDefaultDataType" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_3 )
   _XBST_DWORD (  cVersion          )
   _XBST_LPSTR ( pName              )
   _XBST_LPSTR ( pEnvironment       )
   _XBST_LPSTR ( pDriverPath        )
   _XBST_LPSTR ( pDataFile          )
   _XBST_LPSTR ( pConfigFile        )
   _XBST_LPSTR ( pHelpFile          )
   _XBST_LPSTR ( pDependentFiles    )
   _XBST_LPSTR ( pMonitorName       )
   _XBST_LPSTR ( pDefaultDataType   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_4</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_4</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_4 structure.
         Defined as DRIVER_INFO_4 in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="DWORD" name="cVersion" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="8" size="4" />
         <member type="LPSTR" name="pDriverPath" offset="12" size="4" />
         <member type="LPSTR" name="pDataFile" offset="16" size="4" />
         <member type="LPSTR" name="pConfigFile" offset="20" size="4" />
         <member type="LPSTR" name="pHelpFile" offset="24" size="4" />
         <member type="LPSTR" name="pDependentFiles" offset="28" size="4" />
         <member type="LPSTR" name="pMonitorName" offset="32" size="4" />
         <member type="LPSTR" name="pDefaultDataType" offset="36" size="4" />
         <member type="LPSTR" name="pszzPreviousNames" offset="40" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_4 )
   _XBST_DWORD (  cVersion          )
   _XBST_LPSTR (  pName             )
   _XBST_LPSTR (  pEnvironment      )
   _XBST_LPSTR (  pDriverPath       )
   _XBST_LPSTR (  pDataFile         )
   _XBST_LPSTR (  pConfigFile       )
   _XBST_LPSTR (  pHelpFile         )
   _XBST_LPSTR (  pDependentFiles   )
   _XBST_LPSTR (  pMonitorName      )
   _XBST_LPSTR (  pDefaultDataType  )
   _XBST_LPSTR (  pszzPreviousNames )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_5</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_5</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_5 structure.
         Defined as DRIVER_INFO_5 in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="DWORD" name="cVersion" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="8" size="4" />
         <member type="LPSTR" name="pDriverPath" offset="12" size="4" />
         <member type="LPSTR" name="pDataFile" offset="16" size="4" />
         <member type="LPSTR" name="pConfigFile" offset="20" size="4" />
         <member type="DWORD" name="dwDriverAttributes" offset="24" size="4" />
         <member type="DWORD" name="dwConfigVersion" offset="28" size="4" />
         <member type="DWORD" name="dwDriverVersion" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_5 )
   _XBST_DWORD  (  cVersion             )
   _XBST_LPSTR  (  pName                )
   _XBST_LPSTR  (  pEnvironment         )
   _XBST_LPSTR  (  pDriverPath          )
   _XBST_LPSTR  (  pDataFile            )
   _XBST_LPSTR  (  pConfigFile          )
   _XBST_DWORD  (  dwDriverAttributes   )
   _XBST_DWORD  (  dwConfigVersion      )
   _XBST_DWORD  (  dwDriverVersion      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRIVER_INFO_6</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRIVER_INFO_6</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRIVER_INFO_6 structure.
         Defined as DRIVER_INFO_6 in ot4xb_wapist_map.ch.
      </description>
      <size>68</size>
      <members>
         <member type="DWORD" name="cVersion" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="8" size="4" />
         <member type="LPSTR" name="pDriverPath" offset="12" size="4" />
         <member type="LPSTR" name="pDataFile" offset="16" size="4" />
         <member type="LPSTR" name="pConfigFile" offset="20" size="4" />
         <member type="LPSTR" name="pHelpFile" offset="24" size="4" />
         <member type="LPSTR" name="pDependentFiles" offset="28" size="4" />
         <member type="LPSTR" name="pMonitorName" offset="32" size="4" />
         <member type="LPSTR" name="pDefaultDataType" offset="36" size="4" />
         <member type="LPSTR" name="pszzPreviousNames" offset="40" size="4" />
         <member type="WAPIST_FILETIME" name="ftDriverDate" offset="44" size="?" child="true" />
         <member type="DWORD64" name="dwlDriverVersion" offset="44" size="8" />
         <member type="LPSTR" name="pszMfgName" offset="52" size="4" />
         <member type="LPSTR" name="pszOEMUrl" offset="56" size="4" />
         <member type="LPSTR" name="pszHardwareID" offset="60" size="4" />
         <member type="LPSTR" name="pszProvider" offset="64" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRIVER_INFO_6 )
   _XBST_DWORD       (  cVersion           )
   _XBST_LPSTR       (  pName              )
   _XBST_LPSTR       (  pEnvironment       )
   _XBST_LPSTR       (  pDriverPath        )
   _XBST_LPSTR       (  pDataFile          )
   _XBST_LPSTR       (  pConfigFile        )
   _XBST_LPSTR       (  pHelpFile          )
   _XBST_LPSTR       (  pDependentFiles    )
   _XBST_LPSTR       (  pMonitorName       )
   _XBST_LPSTR       (  pDefaultDataType   )
   _XBST_LPSTR       (  pszzPreviousNames  )
   _XBST_FILETIME    (  ftDriverDate       )
   _XBST_DWORDLONG   (  dwlDriverVersion   )
   _XBST_LPSTR       (  pszMfgName         )
   _XBST_LPSTR       (  pszOEMUrl          )
   _XBST_LPSTR       (  pszHardwareID      )
   _XBST_LPSTR       (  pszProvider        )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FORM_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FORM_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FORM_INFO_1 structure.
         Defined as FORM_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="DWORD" name="Flags" offset="0" size="4" />
         <member type="LPSTR" name="pName" offset="4" size="4" />
         <member type="WAPIST_SIZEL" name="Size" offset="8" size="8" child="true" />
         <member type="WAPIST_RECTL" name="ImageableArea" offset="16" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FORM_INFO_1 )
   _XBST_DWORD ( Flags         )
   _XBST_LPSTR ( pName         )
   _XBST_SIZEL ( Size          )
   _XBST_RECTL ( ImageableArea )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_JOB_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_JOB_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi JOB_INFO_1 structure.
         Defined as JOB_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>64</size>
      <members>
         <member type="DWORD" name="JobId" offset="0" size="4" />
         <member type="LPSTR" name="pPrinterName" offset="4" size="4" />
         <member type="LPSTR" name="pMachineName" offset="8" size="4" />
         <member type="LPSTR" name="pUserName" offset="12" size="4" />
         <member type="LPSTR" name="pDocument" offset="16" size="4" />
         <member type="LPSTR" name="pDatatype" offset="20" size="4" />
         <member type="LPSTR" name="pStatus" offset="24" size="4" />
         <member type="DWORD" name="Status" offset="28" size="4" />
         <member type="DWORD" name="Priority" offset="32" size="4" />
         <member type="DWORD" name="Position" offset="36" size="4" />
         <member type="DWORD" name="TotalPages" offset="40" size="4" />
         <member type="DWORD" name="PagesPrinted" offset="44" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="Submitted" offset="48" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( JOB_INFO_1 )
   _XBST_DWORD       ( JobId         )
   _XBST_LPSTR       ( pPrinterName  )
   _XBST_LPSTR       ( pMachineName  )
   _XBST_LPSTR       ( pUserName     )
   _XBST_LPSTR       ( pDocument     )
   _XBST_LPSTR       ( pDatatype     )
   _XBST_LPSTR       ( pStatus       )
   _XBST_DWORD       ( Status        )
   _XBST_DWORD       ( Priority      )
   _XBST_DWORD       ( Position      )
   _XBST_DWORD       ( TotalPages    )
   _XBST_DWORD       ( PagesPrinted  )
   _XBST_SYSTEMTIME  ( Submitted     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_JOB_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_JOB_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi JOB_INFO_2 structure.
         Defined as JOB_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>104</size>
      <members>
         <member type="DWORD" name="JobId" offset="0" size="4" />
         <member type="LPSTR" name="pPrinterName" offset="4" size="4" />
         <member type="LPSTR" name="pMachineName" offset="8" size="4" />
         <member type="LPSTR" name="pUserName" offset="12" size="4" />
         <member type="LPSTR" name="pDocument" offset="16" size="4" />
         <member type="LPSTR" name="pNotifyName" offset="20" size="4" />
         <member type="LPSTR" name="pDatatype" offset="24" size="4" />
         <member type="LPSTR" name="pPrintProcessor" offset="28" size="4" />
         <member type="LPSTR" name="pParameters" offset="32" size="4" />
         <member type="LPSTR" name="pDriverName" offset="36" size="4" />
         <member type="POINTER32" name="pDevMode" offset="40" size="4" />
         <member type="LPSTR" name="pStatus" offset="44" size="4" />
         <member type="POINTER32" name="pSecurityDescriptor" offset="48" size="4" />
         <member type="DWORD" name="Status" offset="52" size="4" />
         <member type="DWORD" name="Priority" offset="56" size="4" />
         <member type="DWORD" name="Position" offset="60" size="4" />
         <member type="DWORD" name="StartTime" offset="64" size="4" />
         <member type="DWORD" name="UntilTime" offset="68" size="4" />
         <member type="DWORD" name="TotalPages" offset="72" size="4" />
         <member type="DWORD" name="Size" offset="76" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="Submitted" offset="80" size="16" child="true" />
         <member type="DWORD" name="Time" offset="96" size="4" />
         <member type="DWORD" name="PagesPrinted" offset="100" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( JOB_INFO_2 )
   _XBST_DWORD      ( JobId                 )
   _XBST_LPSTR      ( pPrinterName          )
   _XBST_LPSTR      ( pMachineName          )
   _XBST_LPSTR      ( pUserName             )
   _XBST_LPSTR      ( pDocument             )
   _XBST_LPSTR      ( pNotifyName           )
   _XBST_LPSTR      ( pDatatype             )
   _XBST_LPSTR      ( pPrintProcessor       )
   _XBST_LPSTR      ( pParameters           )
   _XBST_LPSTR      ( pDriverName           )
   _XBST_POINTER32  ( pDevMode              )
   _XBST_LPSTR      ( pStatus               )
   _XBST_POINTER32  ( pSecurityDescriptor   )
   _XBST_DWORD      ( Status                )
   _XBST_DWORD      ( Priority              )
   _XBST_DWORD      ( Position              )
   _XBST_DWORD      ( StartTime             )
   _XBST_DWORD      ( UntilTime             )
   _XBST_DWORD      ( TotalPages            )
   _XBST_DWORD      ( Size                  )
   _XBST_SYSTEMTIME ( Submitted             )
   _XBST_DWORD      ( Time                  )
   _XBST_DWORD      ( PagesPrinted          )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_JOB_INFO_3</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_JOB_INFO_3</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi JOB_INFO_3 structure.
         Defined as JOB_INFO_3 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="DWORD" name="JobId" offset="0" size="4" />
         <member type="DWORD" name="NextJobId" offset="4" size="4" />
         <member type="DWORD" name="Reserved" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( JOB_INFO_3 )
   _XBST_DWORD  ( JobId     )
   _XBST_DWORD  ( NextJobId )
   _XBST_DWORD  ( Reserved  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MONITOR_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MONITOR_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MONITOR_INFO_1 structure.
         Defined as MONITOR_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MONITOR_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MONITOR_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MONITOR_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MONITOR_INFO_2 structure.
         Defined as MONITOR_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="4" size="4" />
         <member type="LPSTR" name="pDLLName" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MONITOR_INFO_2 )
   _XBST_LPSTR ( pName        )
   _XBST_LPSTR ( pEnvironment )
   _XBST_LPSTR ( pDLLName     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PORT_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PORT_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PORT_INFO_1 structure.
         Defined as PORT_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PORT_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PORT_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PORT_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PORT_INFO_2 structure.
         Defined as PORT_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="LPSTR" name="pPortName" offset="0" size="4" />
         <member type="LPSTR" name="pMonitorName" offset="4" size="4" />
         <member type="LPSTR" name="pDescription" offset="8" size="4" />
         <member type="DWORD" name="fPortType" offset="12" size="4" />
         <member type="DWORD" name="Reserved" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PORT_INFO_2 )
   _XBST_LPSTR ( pPortName    )
   _XBST_LPSTR ( pMonitorName )
   _XBST_LPSTR ( pDescription )
   _XBST_DWORD ( fPortType    )
   _XBST_DWORD ( Reserved     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PORT_INFO_3</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PORT_INFO_3</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PORT_INFO_3 structure.
         Defined as PORT_INFO_3 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="DWORD" name="dwStatus" offset="0" size="4" />
         <member type="LPSTR" name="pszStatus" offset="4" size="4" />
         <member type="DWORD" name="dwSeverity" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PORT_INFO_3 )
   _XBST_DWORD( dwStatus   )
   _XBST_LPSTR( pszStatus  )
   _XBST_DWORD( dwSeverity )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_DEFAULTS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_DEFAULTS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_DEFAULTS structure.
         Defined as PRINTER_DEFAULTS in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="LPSTR" name="pDatatype" offset="0" size="4" />
         <member type="POINTER32" name="pDevMode" offset="4" size="4" />
         <member type="ACCESS_MASK" name="DesiredAccess" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_DEFAULTS )
   _XBST_LPSTR       ( pDatatype     )
   _XBST_POINTER32   ( pDevMode      )
   _XBST_ACCESS_MASK ( DesiredAccess )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_ENUM_VALUES</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_ENUM_VALUES</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_ENUM_VALUES structure.
         Defined as PRINTER_ENUM_VALUES in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="LPSTR" name="pValueName" offset="0" size="4" />
         <member type="DWORD" name="cbValueName" offset="4" size="4" />
         <member type="DWORD" name="dwType" offset="8" size="4" />
         <member type="LPBYTE" name="pData" offset="12" size="4" />
         <member type="DWORD" name="cbData" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_ENUM_VALUES )
   _XBST_LPSTR   ( pValueName  )
   _XBST_DWORD   ( cbValueName )
   _XBST_DWORD   ( dwType      )
   _XBST_LPBYTE  ( pData       )
   _XBST_DWORD   ( cbData      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_1 structure.
         Defined as PRINTER_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-1</ref-url>
      <size>16</size>
      <members>
         <member type="DWORD" name="Flags" offset="0" size="4" />
         <member type="LPSTR" name="pDescription" offset="4" size="4" />
         <member type="LPSTR" name="pName" offset="8" size="4" />
         <member type="LPSTR" name="pComment" offset="12" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cDescription" target="pDescription" offset="4" size="4" access="string" />
         <helper type="DYNSZ" name="cName" target="pName" offset="8" size="4" access="string" />
         <helper type="DYNSZ" name="cComment" target="pComment" offset="12" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_1 )
   _XBST_DWORD ( Flags        )
   _XBST_LPSTR_DYNSZ ( pDescription , cDescription)
   _XBST_LPSTR_DYNSZ ( pName        , cName       )
   _XBST_LPSTR_DYNSZ ( pComment     , cComment    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_2 structure.
         Defined as PRINTER_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-2</ref-url>
      <size>84</size>
      <members>
         <member type="LPSTR" name="pServerName" offset="0" size="4" />
         <member type="LPSTR" name="pPrinterName" offset="4" size="4" />
         <member type="LPSTR" name="pShareName" offset="8" size="4" />
         <member type="LPSTR" name="pPortName" offset="12" size="4" />
         <member type="LPSTR" name="pDriverName" offset="16" size="4" />
         <member type="LPSTR" name="pComment" offset="20" size="4" />
         <member type="LPSTR" name="pLocation" offset="24" size="4" />
         <member type="PDEVMODE" name="pDevMode" offset="28" size="4" />
         <member type="LPSTR" name="pSepFile" offset="32" size="4" />
         <member type="LPSTR" name="pPrintProcessor" offset="36" size="4" />
         <member type="LPSTR" name="pDatatype" offset="40" size="4" />
         <member type="LPSTR" name="pParameters" offset="44" size="4" />
         <member type="PSECURITY_DESCRIPTOR" name="pSecurityDescriptor" offset="48" size="4" />
         <member type="DWORD" name="Attributes" offset="52" size="4" />
         <member type="DWORD" name="Priority" offset="56" size="4" />
         <member type="DWORD" name="DefaultPriority" offset="60" size="4" />
         <member type="DWORD" name="StartTime" offset="64" size="4" />
         <member type="DWORD" name="UntilTime" offset="68" size="4" />
         <member type="DWORD" name="Status" offset="72" size="4" />
         <member type="DWORD" name="cJobs" offset="76" size="4" />
         <member type="DWORD" name="AveragePPM" offset="80" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cServerName" target="pServerName" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cPrinterName" target="pPrinterName" offset="4" size="4" access="string" />
         <helper type="DYNSZ" name="cShareName" target="pShareName" offset="8" size="4" access="string" />
         <helper type="DYNSZ" name="cPortName" target="pPortName" offset="12" size="4" access="string" />
         <helper type="DYNSZ" name="cDriverName" target="pDriverName" offset="16" size="4" access="string" />
         <helper type="DYNSZ" name="cComment" target="pComment" offset="20" size="4" access="string" />
         <helper type="DYNSZ" name="cLocation" target="pLocation" offset="24" size="4" access="string" />
         <helper type="DYNSZ" name="cSepFile" target="pSepFile" offset="32" size="4" access="string" />
         <helper type="DYNSZ" name="cPrintProcessor" target="pPrintProcessor" offset="36" size="4" access="string" />
         <helper type="DYNSZ" name="cDatatype" target="pDatatype" offset="40" size="4" access="string" />
         <helper type="DYNSZ" name="cParameters" target="pParameters" offset="44" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_2 )
   _XBST_LPSTR_DYNSZ ( pServerName   , cServerName          )
   _XBST_LPSTR_DYNSZ ( pPrinterName  , cPrinterName         )
   _XBST_LPSTR_DYNSZ ( pShareName    , cShareName           )
   _XBST_LPSTR_DYNSZ ( pPortName     , cPortName            )
   _XBST_LPSTR_DYNSZ ( pDriverName   , cDriverName          )
   _XBST_LPSTR_DYNSZ ( pComment      , cComment             )
   _XBST_LPSTR_DYNSZ ( pLocation     , cLocation            )
   _XBST_POINTER32 ( pDevMode            )
   _XBST_LPSTR_DYNSZ ( pSepFile         , cSepFile           )
   _XBST_LPSTR_DYNSZ ( pPrintProcessor  , cPrintProcessor    )
   _XBST_LPSTR_DYNSZ ( pDatatype        , cDatatype          )
   _XBST_LPSTR_DYNSZ ( pParameters      , cParameters        )
   _XBST_POINTER32 ( pSecurityDescriptor )
   _XBST_DWORD     ( Attributes          )
   _XBST_DWORD     ( Priority            )
   _XBST_DWORD     ( DefaultPriority     )
   _XBST_DWORD     ( StartTime           )
   _XBST_DWORD     ( UntilTime           )
   _XBST_DWORD     ( Status              )
   _XBST_DWORD     ( cJobs               )
   _XBST_DWORD     ( AveragePPM          )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_3</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_3</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_3 structure.
         Defined as PRINTER_INFO_3 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="POINTER32" name="pSecurityDescriptor" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_3 )
   _XBST_POINTER32 ( pSecurityDescriptor )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_4</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_4</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_4 structure.
         Defined as PRINTER_INFO_4 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-4</ref-url>
      <size>12</size>
      <members>
         <member type="LPSTR" name="pPrinterName" offset="0" size="4" />
         <member type="LPSTR" name="pServerName" offset="4" size="4" />
         <member type="DWORD" name="Attributes" offset="8" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cPrinterName" target="pPrinterName" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cServerName" target="pServerName" offset="4" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_4 )
   _XBST_LPSTR_DYNSZ ( pPrinterName , cPrinterName)
   _XBST_LPSTR_DYNSZ ( pServerName  , cServerName )
   _XBST_DWORD ( Attributes   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_5</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_5</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_5 structure.
         Defined as PRINTER_INFO_5 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-5</ref-url>
      <size>20</size>
      <members>
         <member type="LPSTR" name="pPrinterName" offset="0" size="4" />
         <member type="LPSTR" name="pPortName" offset="4" size="4" />
         <member type="DWORD" name="Attributes" offset="8" size="4" />
         <member type="DWORD" name="DeviceNotSelectedTimeout" offset="12" size="4" />
         <member type="DWORD" name="TransmissionRetryTimeout" offset="16" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cPrinterName" target="pPrinterName" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cPortName" target="pPortName" offset="4" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_5 )
   _XBST_LPSTR_DYNSZ ( pPrinterName  , cPrinterName )
   _XBST_LPSTR_DYNSZ ( pPortName     , cPortName    )
   _XBST_DWORD ( Attributes               )
   _XBST_DWORD ( DeviceNotSelectedTimeout )
   _XBST_DWORD ( TransmissionRetryTimeout )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_6</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_6</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_6 structure.
         Defined as PRINTER_INFO_6 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-6</ref-url>
      <size>4</size>
      <members>
         <member type="DWORD" name="dwStatus" offset="0" size="4" />
      </members>
      <properties>
         <property type="logical" name="lPaused" member="dwStatus" mask="0x00000001" readonly="true" />
         <property type="logical" name="lError" member="dwStatus" mask="0x00000002" readonly="true" />
         <property type="logical" name="lPendingDeletion" member="dwStatus" mask="0x00000004" readonly="true" />
         <property type="logical" name="lPaperJam" member="dwStatus" mask="0x00000008" readonly="true" />
         <property type="logical" name="lPaperOut" member="dwStatus" mask="0x00000010" readonly="true" />
         <property type="logical" name="lManualFeed" member="dwStatus" mask="0x00000020" readonly="true" />
         <property type="logical" name="lPaperProblem" member="dwStatus" mask="0x00000040" readonly="true" />
         <property type="logical" name="lOffline" member="dwStatus" mask="0x00000080" readonly="true" />
         <property type="logical" name="lIoActive" member="dwStatus" mask="0x00000100" readonly="true" />
         <property type="logical" name="lBusy" member="dwStatus" mask="0x00000200" readonly="true" />
         <property type="logical" name="lPrinting" member="dwStatus" mask="0x00000400" readonly="true" />
         <property type="logical" name="lOutputBinFull" member="dwStatus" mask="0x00000800" readonly="true" />
         <property type="logical" name="lNotAvailable" member="dwStatus" mask="0x00001000" readonly="true" />
         <property type="logical" name="lWaiting" member="dwStatus" mask="0x00002000" readonly="true" />
         <property type="logical" name="lProcessing" member="dwStatus" mask="0x00004000" readonly="true" />
         <property type="logical" name="lInitializing" member="dwStatus" mask="0x00008000" readonly="true" />
         <property type="logical" name="lWarmingUp" member="dwStatus" mask="0x00010000" readonly="true" />
         <property type="logical" name="lTonerLow" member="dwStatus" mask="0x00020000" readonly="true" />
         <property type="logical" name="lNoToner" member="dwStatus" mask="0x00040000" readonly="true" />
         <property type="logical" name="lPagePunt" member="dwStatus" mask="0x00080000" readonly="true" />
         <property type="logical" name="lUserIntervention" member="dwStatus" mask="0x00100000" readonly="true" />
         <property type="logical" name="lOutOfMemory" member="dwStatus" mask="0x00200000" readonly="true" />
         <property type="logical" name="lDoorOpen" member="dwStatus" mask="0x00400000" readonly="true" />
         <property type="logical" name="lServerUnknown" member="dwStatus" mask="0x00800000" readonly="true" />
         <property type="logical" name="lPowerSave" member="dwStatus" mask="0x01000000" readonly="true" />
         <property type="logical" name="lServerOffline" member="dwStatus" mask="0x02000000" readonly="true" />
         <property type="logical" name="lDriverUpdateNeeded" member="dwStatus" mask="0x04000000" readonly="true" />
      </properties>
      <remarks>
         OT4XB exposes additional readonly logical properties for all status flags declared in this source block.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_6 )
   _XBST_DWORD ( dwStatus )
   // ---------- ot4xb extension
   pc->ROPropertyCB("lPaused"               , "{|s| lAnd( s:dwStatus , 0x00000001)}");
   pc->ROPropertyCB("lError"                , "{|s| lAnd( s:dwStatus , 0x00000002)}");
   pc->ROPropertyCB("lPendingDeletion"      , "{|s| lAnd( s:dwStatus , 0x00000004)}");
   pc->ROPropertyCB("lPaperJam"             , "{|s| lAnd( s:dwStatus , 0x00000008)}");
   pc->ROPropertyCB("lPaperOut"             , "{|s| lAnd( s:dwStatus , 0x00000010)}");
   pc->ROPropertyCB("lManualFeed"           , "{|s| lAnd( s:dwStatus , 0x00000020)}");
   pc->ROPropertyCB("lPaperProblem"         , "{|s| lAnd( s:dwStatus , 0x00000040)}");
   pc->ROPropertyCB("lOffline"              , "{|s| lAnd( s:dwStatus , 0x00000080)}");
   pc->ROPropertyCB("lIoActive"             , "{|s| lAnd( s:dwStatus , 0x00000100)}");
   pc->ROPropertyCB("lBusy"                 , "{|s| lAnd( s:dwStatus , 0x00000200)}");
   pc->ROPropertyCB("lPrinting"             , "{|s| lAnd( s:dwStatus , 0x00000400)}");
   pc->ROPropertyCB("lOutputBinFull"        , "{|s| lAnd( s:dwStatus , 0x00000800)}");
   pc->ROPropertyCB("lNotAvailable"         , "{|s| lAnd( s:dwStatus , 0x00001000)}");
   pc->ROPropertyCB("lWaiting"              , "{|s| lAnd( s:dwStatus , 0x00002000)}");
   pc->ROPropertyCB("lProcessing"           , "{|s| lAnd( s:dwStatus , 0x00004000)}");
   pc->ROPropertyCB("lInitializing"         , "{|s| lAnd( s:dwStatus , 0x00008000)}");
   pc->ROPropertyCB("lWarmingUp"            , "{|s| lAnd( s:dwStatus , 0x00010000)}");
   pc->ROPropertyCB("lTonerLow"             , "{|s| lAnd( s:dwStatus , 0x00020000)}");
   pc->ROPropertyCB("lNoToner"              , "{|s| lAnd( s:dwStatus , 0x00040000)}");
   pc->ROPropertyCB("lPagePunt"             , "{|s| lAnd( s:dwStatus , 0x00080000)}");
   pc->ROPropertyCB("lUserIntervention"     , "{|s| lAnd( s:dwStatus , 0x00100000)}");
   pc->ROPropertyCB("lOutOfMemory"          , "{|s| lAnd( s:dwStatus , 0x00200000)}");
   pc->ROPropertyCB("lDoorOpen"             , "{|s| lAnd( s:dwStatus , 0x00400000)}");
   pc->ROPropertyCB("lServerUnknown"        , "{|s| lAnd( s:dwStatus , 0x00800000)}");
   pc->ROPropertyCB("lPowerSave"            , "{|s| lAnd( s:dwStatus , 0x01000000)}");
   pc->ROPropertyCB("lServerOffline"        , "{|s| lAnd( s:dwStatus , 0x02000000)}");
   pc->ROPropertyCB("lDriverUpdateNeeded"   , "{|s| lAnd( s:dwStatus , 0x04000000)}");
   // ----------
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_7</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_7</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_7 structure.
         Defined as PRINTER_INFO_7 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-7</ref-url>
      <size>8</size>
      <members>
         <member type="LPSTR" name="pszObjectGUID" offset="0" size="4" />
         <member type="DWORD" name="dwAction" offset="4" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cObjectGUID" target="pszObjectGUID" offset="0" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_7 )
   _XBST_LPSTR_DYNSZ ( pszObjectGUID , cObjectGUID)
   _XBST_DWORD  ( dwAction      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_8</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_8</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_8 structure.
         Defined as PRINTER_INFO_8 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="POINTER32" name="pDevMode" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_8 )
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_INFO_9</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_INFO_9</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_INFO_9 structure.
         Defined as PRINTER_INFO_9 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="POINTER32" name="pDevMode" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_INFO_9 )
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_NOTIFY_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_NOTIFY_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_NOTIFY_INFO structure.
         Defined as PRINTER_NOTIFY_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="DWORD" name="Version" offset="0" size="4" />
         <member type="DWORD" name="Flags" offset="4" size="4" />
         <member type="DWORD" name="Count" offset="8" size="4" />
         <member type="WAPIST_PRINTER_NOTIFY_INFO_DATA" name="aData0" offset="12" size="12" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO )
   _XBST_DWORD                     ( Version )
   _XBST_DWORD                     ( Flags   )
   _XBST_DWORD                     ( Count   )
   _XBST_PRINTER_NOTIFY_INFO_DATA  ( aData0  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi _PRINTER_NOTIFY_INFO_DATA___DATA structure.
         Defined as _PRINTER_NOTIFY_INFO_DATA___DATA in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="cbBuf" offset="0" size="4" />
         <member type="POINTER32" name="pBuf" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( _PRINTER_NOTIFY_INFO_DATA___DATA )
   _XBST_DWORD     ( cbBuf )
   _XBST_POINTER32 ( pBuf  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA</source>
      <category>winapi/structures</category>
      <description>Auxiliary wrapper for the PRINTER_NOTIFY_INFO_DATA NotifyData union.</description>
      <size>8</size>
      <members>
         <union name="NotifyData" offset="0" size="8">
            <member type="DWORD" name="adwData0" offset="0" size="4" />
            <member type="DWORD" name="adwData1" offset="4" size="4" />
            <member type="WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA" name="Data" offset="0" size="8" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( _PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA )
  {
     UINT nP1 = pc->GwstGetOffset();
     UINT nMax;
     {
        _XBST_DWORD( adwData0 )
        _XBST_DWORD( adwData1 )
     }
     nMax = pc->GwstGetOffset();
     pc->GwstSetOffset(nP1);
     _XBST__PRINTER_NOTIFY_INFO_DATA___DATA( Data )
     if( pc->GwstGetOffset() < nMax ) pc->GwstSetOffset(nMax);

  }
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_NOTIFY_INFO_DATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_NOTIFY_INFO_DATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_NOTIFY_INFO_DATA structure.
         Defined as PRINTER_NOTIFY_INFO_DATA in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-notify-info-data</ref-url>
      <size>20</size>
      <members>
         <member type="WORD" name="Type" offset="0" size="2" />
         <member type="WORD" name="Field" offset="2" size="2" />
         <member type="DWORD" name="Reserved" offset="4" size="4" />
         <member type="DWORD" name="Id" offset="8" size="4" />
         <member type="WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA" name="NotifyData" offset="12" size="8" child="true" />
         <union name="NotifyData" offset="12" size="8">
            <member type="DWORD[2]" name="adwData" offset="12" size="8" count="2" />
            <struct name="Data" offset="12" size="8" anonymous="true">
               <member type="DWORD" name="cbBuf" offset="12" size="4" />
               <member type="LPVOID" name="pBuf" offset="16" size="4" />
            </struct>
         </union>
      </members>
      <ot4xb-helpers>
         <helper type="WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA" member="NotifyData">
            Auxiliary OT4XB class used to expose the named NotifyData union.
         </helper>
         <helper type="WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA" member="NotifyData.Data">
            Auxiliary OT4XB class used to expose the anonymous Data structure inside NotifyData.
         </helper>
      </ot4xb-helpers>
      <remarks>
         NotifyData is a named C union. Its Data branch is an anonymous C structure in the WinApi
         declaration. OT4XB uses small auxiliary classes to expose those nested layouts from Xbase++.
         Read either NotifyData:adwData0 and NotifyData:adwData1, or NotifyData:Data:cbBuf and
         NotifyData:Data:pBuf, depending on the Type and Field values documented by the Windows spooler API.
      </remarks>
      <remarks>
         NotifyData:Data:pBuf is a pointer supplied by the Windows spooler notification API. The pointer is
         not owned by this structure object. Use NotifyData:Data:cbBuf as the byte length before reading from
         pBuf, and do not free pBuf from Xbase++ code.
      </remarks>
      <example><![CDATA[
local nd := oNotify:aData0

? nd:NotifyData:adwData0
? nd:NotifyData:adwData1

if nd:NotifyData:Data:pBuf != 0 .and. nd:NotifyData:Data:cbBuf > 0
   ? PeekStr( nd:NotifyData:Data:pBuf, 0, nd:NotifyData:Data:cbBuf )
endif
      ]]></example>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO_DATA )
   _XBST_WORD   (  Type      )
   _XBST_WORD   (  Field     )
   _XBST_DWORD  (  Reserved  )
   _XBST_DWORD  (  Id        )
   _XBST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA( NotifyData )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_NOTIFY_OPTIONS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_NOTIFY_OPTIONS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_NOTIFY_OPTIONS structure.
         Defined as PRINTER_NOTIFY_OPTIONS in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="Version" offset="0" size="4" />
         <member type="DWORD" name="Flags" offset="4" size="4" />
         <member type="DWORD" name="Count" offset="8" size="4" />
         <member type="POINTER32" name="pTypes" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS )
   _XBST_DWORD     ( Version )
   _XBST_DWORD     ( Flags   )
   _XBST_DWORD     ( Count   )
   _XBST_POINTER32 ( pTypes  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTER_NOTIFY_OPTIONS_TYPE structure.
         Defined as PRINTER_NOTIFY_OPTIONS_TYPE in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WORD" name="Type" offset="0" size="2" />
         <member type="WORD" name="Reserved0" offset="2" size="2" />
         <member type="DWORD" name="Reserved1" offset="4" size="4" />
         <member type="DWORD" name="Reserved2" offset="8" size="4" />
         <member type="DWORD" name="Count" offset="12" size="4" />
         <member type="POINTER32" name="pFields" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS_TYPE )
   _XBST_WORD       ( Type      )
   _XBST_WORD       ( Reserved0 )
   _XBST_DWORD      ( Reserved1 )
   _XBST_DWORD      ( Reserved2 )
   _XBST_DWORD      ( Count     )
   _XBST_POINTER32  ( pFields   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTPROCESSOR_CAPS_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTPROCESSOR_CAPS_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTPROCESSOR_CAPS_1 structure.
         Defined as PRINTPROCESSOR_CAPS_1 in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwLevel" offset="0" size="4" />
         <member type="DWORD" name="dwNupOptions" offset="4" size="4" />
         <member type="DWORD" name="dwPageOrderFlags" offset="8" size="4" />
         <member type="DWORD" name="dwNumberOfCopies" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_CAPS_1 )
   _XBST_DWORD ( dwLevel          )
   _XBST_DWORD ( dwNupOptions     )
   _XBST_DWORD ( dwPageOrderFlags )
   _XBST_DWORD ( dwNumberOfCopies )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PRINTPROCESSOR_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PRINTPROCESSOR_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PRINTPROCESSOR_INFO_1 structure.
         Defined as PRINTPROCESSOR_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_INFO_1 )
   _XBST_LPSTR ( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PROVIDOR_INFO_1</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PROVIDOR_INFO_1</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PROVIDOR_INFO_1 structure.
         Defined as PROVIDOR_INFO_1 in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="LPSTR" name="pName" offset="0" size="4" />
         <member type="LPSTR" name="pEnvironment" offset="4" size="4" />
         <member type="LPSTR" name="pDLLName" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_1 )
   _XBST_LPSTR( pName        )
   _XBST_LPSTR( pEnvironment )
   _XBST_LPSTR( pDLLName     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PROVIDOR_INFO_2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PROVIDOR_INFO_2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PROVIDOR_INFO_2 structure.
         Defined as PROVIDOR_INFO_2 in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LPSTR" name="pOrder" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_2 )
   _XBST_LPSTR( pOrder )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PSFEATURE_CUSTPAPER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PSFEATURE_CUSTPAPER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PSFEATURE_CUSTPAPER structure.
         Defined as PSFEATURE_CUSTPAPER in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="LONG" name="lOrientation" offset="0" size="4" />
         <member type="LONG" name="lWidth" offset="4" size="4" />
         <member type="LONG" name="lHeight" offset="8" size="4" />
         <member type="LONG" name="lWidthOffset" offset="12" size="4" />
         <member type="LONG" name="lHeightOffset" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PSFEATURE_CUSTPAPER )
   _XBST_LONG ( lOrientation  )
   _XBST_LONG ( lWidth        )
   _XBST_LONG ( lHeight       )
   _XBST_LONG ( lWidthOffset  )
   _XBST_LONG ( lHeightOffset )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PSFEATURE_OUTPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PSFEATURE_OUTPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PSFEATURE_OUTPUT structure.
         Defined as PSFEATURE_OUTPUT in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="BOOL" name="bPageIndependent" offset="0" size="4" />
         <member type="BOOL" name="bSetPageDevice" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PSFEATURE_OUTPUT )
   _XBST_BOOL ( bPageIndependent )
   _XBST_BOOL ( bSetPageDevice   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PSINJECTDATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PSINJECTDATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PSINJECTDATA structure.
         Defined as PSINJECTDATA in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="DataBytes" offset="0" size="4" />
         <member type="WORD" name="InjectionPoint" offset="4" size="2" />
         <member type="WORD" name="PageNumber" offset="6" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PSINJECTDATA )
   _XBST_DWORD ( DataBytes      )
   _XBST_WORD  ( InjectionPoint )
   _XBST_WORD  ( PageNumber     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RGNDATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RGNDATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RGNDATA structure.
         Defined as RGNDATA in ot4xb_wapist_map.ch.
      </description>
      <size>33</size>
      <members>
         <member type="WAPIST_RGNDATAHEADER" name="rdh" offset="0" size="32" child="true" />
         <member type="BYTE" name="Buffer0" offset="32" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RGNDATA )
   _XBST_RGNDATAHEADER ( rdh )
   _XBST_CHAR          ( Buffer0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RGNDATAHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RGNDATAHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RGNDATAHEADER structure.
         Defined as RGNDATAHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="DWORD" name="iType" offset="4" size="4" />
         <member type="DWORD" name="nCount" offset="8" size="4" />
         <member type="DWORD" name="nRgnSize" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rcBound" offset="16" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RGNDATAHEADER )
   _XBST_DWORD ( dwSize    )
   _XBST_DWORD ( iType     )
   _XBST_DWORD ( nCount    )
   _XBST_DWORD ( nRgnSize  )
   _XBST_RECT  ( rcBound   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
///*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DISPLAY_DEVICE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DISPLAY_DEVICE</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi DISPLAY_DEVICE layout declared in this source block.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-display_devicea</ref-url>
      <members>
         <member type="DWORD" name="cb" />
         <member type="SZWSTR" name="DeviceName" chars="32" access="string" />
         <member type="SZWSTR" name="DeviceString" chars="128" access="string" />
         <member type="DWORD" name="StateFlags" />
         <member type="SZWSTR" name="DeviceID" chars="128" access="string" />
         <member type="SZWSTR" name="DeviceKey" chars="128" access="string" />
      </members>
      <remarks>The current source block keeps this layout commented out and does not declare active GWST members.</remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DISPLAY_DEVICE )
//  DWORD cb;
//  WCHAR DeviceName[32];
//  WCHAR DeviceString[128];
//  DWORD StateFlags;
//  WCHAR DeviceID[128];
//  WCHAR DeviceKey[128];
//XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ALTTABINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ALTTABINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ALTTABINFO structure.
         Defined as ALTTABINFO in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="INT" name="cItems" offset="4" size="4" />
         <member type="INT" name="cColumns" offset="8" size="4" />
         <member type="INT" name="cRows" offset="12" size="4" />
         <member type="INT" name="iColFocus" offset="16" size="4" />
         <member type="INT" name="iRowFocus" offset="20" size="4" />
         <member type="INT" name="cxItem" offset="24" size="4" />
         <member type="INT" name="cyItem" offset="28" size="4" />
         <member type="WAPIST_POINT" name="ptStart" offset="32" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ALTTABINFO )
   _XBST_DWORD  ( cbSize    )
   _XBST_int    ( cItems    )
   _XBST_int    ( cColumns  )
   _XBST_int    ( cRows     )
   _XBST_int    ( iColFocus )
   _XBST_int    ( iRowFocus )
   _XBST_int    ( cxItem    )
   _XBST_int    ( cyItem    )
   _XBST_POINT  ( ptStart   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TITLEBARINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TITLEBARINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TITLEBARINFO structure.
         Defined as TITLEBARINFO in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcTitleBar" offset="4" size="16" child="true" />
         <member type="DWORD" name="rgstate_TitleBar" offset="20" size="4" />
         <member type="DWORD" name="rgstate_Reserved" offset="24" size="4" />
         <member type="DWORD" name="rgstate_Min" offset="28" size="4" />
         <member type="DWORD" name="rgstate_Max" offset="32" size="4" />
         <member type="DWORD" name="rgstate_Help" offset="36" size="4" />
         <member type="DWORD" name="rgstate_Close" offset="40" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TITLEBARINFO )
   _XBST_DWORD  ( cbSize            )
   _XBST_RECT   ( rcTitleBar        )
   _XBST_DWORD  ( rgstate_TitleBar  )   //0
   _XBST_DWORD  ( rgstate_Reserved  )   //1
   _XBST_DWORD  ( rgstate_Min       )   //2
   _XBST_DWORD  ( rgstate_Max       )   //3
   _XBST_DWORD  ( rgstate_Help      )   //4
   _XBST_DWORD  ( rgstate_Close     )   //5

XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WINDOWINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WINDOWINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WINDOWINFO structure.
         Defined as WINDOWINFO in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-windowinfo</ref-url>
      <size>60</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcWindow" offset="4" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcClient" offset="20" size="16" child="true" />
         <member type="DWORD" name="dwStyle" offset="36" size="4" />
         <member type="DWORD" name="dwExStyle" offset="40" size="4" />
         <member type="DWORD" name="dwWindowStatus" offset="44" size="4" />
         <member type="UINT" name="cxWindowBorders" offset="48" size="4" />
         <member type="UINT" name="cyWindowBorders" offset="52" size="4" />
         <member type="ATOM" name="atomWindowType" offset="56" size="2" />
         <member type="WORD" name="wCreatorVersion" offset="58" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WINDOWINFO )
   _XBST_DWORD ( cbSize           )
   _XBST_RECT  ( rcWindow         )
   _XBST_RECT  ( rcClient         )
   _XBST_DWORD ( dwStyle          )
   _XBST_DWORD ( dwExStyle        )
   _XBST_DWORD ( dwWindowStatus   )
   _XBST_UINT  ( cxWindowBorders  )
   _XBST_UINT  ( cyWindowBorders  )
   _XBST_ATOM  ( atomWindowType   )
   _XBST_WORD  ( wCreatorVersion  )
   pc->GwstAdjustSize(sizeof(WINDOWINFO));
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WINDOWPLACEMENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WINDOWPLACEMENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WINDOWPLACEMENT structure.
         Defined as WINDOWPLACEMENT in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="UINT" name="length" offset="0" size="4" />
         <member type="UINT" name="flags" offset="4" size="4" />
         <member type="UINT" name="showCmd" offset="8" size="4" />
         <member type="WAPIST_POINT" name="ptMinPosition" offset="12" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptMaxPosition" offset="20" size="8" child="true" />
         <member type="WAPIST_RECT" name="rcNormalPosition" offset="28" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WINDOWPLACEMENT )
   _XBST_UINT   ( length           )
   _XBST_UINT   ( flags            )
   _XBST_UINT   ( showCmd          )
   _XBST_POINT  ( ptMinPosition    )
   _XBST_POINT  ( ptMaxPosition    )
   _XBST_RECT   ( rcNormalPosition )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GUITHREADINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GUITHREADINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GUITHREADINFO structure.
         Defined as GUITHREADINFO in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="flags" offset="4" size="4" />
         <member type="HWND" name="hwndActive" offset="8" size="4" />
         <member type="HWND" name="hwndFocus" offset="12" size="4" />
         <member type="HWND" name="hwndCapture" offset="16" size="4" />
         <member type="HWND" name="hwndMenuOwner" offset="20" size="4" />
         <member type="HWND" name="hwndMoveSize" offset="24" size="4" />
         <member type="HWND" name="hwndCaret" offset="28" size="4" />
         <member type="WAPIST_RECT" name="rcCaret" offset="32" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( GUITHREADINFO )
   _XBST_DWORD  ( cbSize          )
   _XBST_DWORD  ( flags           )
   _XBST_HWND   ( hwndActive      )
   _XBST_HWND   ( hwndFocus       )
   _XBST_HWND   ( hwndCapture     )
   _XBST_HWND   ( hwndMenuOwner   )
   _XBST_HWND   ( hwndMoveSize    )
   _XBST_HWND   ( hwndCaret       )
   _XBST_RECT   ( rcCaret         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CURSORINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CURSORINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CURSORINFO structure.
         Defined as CURSORINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="flags" offset="4" size="4" />
         <member type="HCURSOR" name="hCursor" offset="8" size="4" />
         <member type="WAPIST_POINT" name="ptScreenPos" offset="12" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CURSORINFO  )
   _XBST_DWORD   ( cbSize        )
   _XBST_DWORD   ( flags         )
   _XBST_HCURSOR ( hCursor       )
   _XBST_POINT   ( ptScreenPos   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ICONINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ICONINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ICONINFO structure.
         Defined as ICONINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="BOOL" name="fIcon" offset="0" size="4" />
         <member type="DWORD" name="xHotspot" offset="4" size="4" />
         <member type="DWORD" name="yHotspot" offset="8" size="4" />
         <member type="HBITMAP" name="hbmMask" offset="12" size="4" />
         <member type="HBITMAP" name="hbmColor" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ICONINFO  )
   _XBST_BOOL    ( fIcon     )
   _XBST_DWORD   ( xHotspot  )
   _XBST_DWORD   ( yHotspot  )
   _XBST_HBITMAP ( hbmMask   )
   _XBST_HBITMAP ( hbmColor  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ICONMETRICS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ICONMETRICS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ICONMETRICS structure.
         Defined as ICONMETRICS in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="INT" name="iHorzSpacing" offset="4" size="4" />
         <member type="INT" name="iVertSpacing" offset="8" size="4" />
         <member type="INT" name="iTitleWrap" offset="12" size="4" />
         <member type="WAPIST_LOGFONT" name="lfFont" offset="16" size="28" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ICONMETRICS  )
   _XBST_UINT    ( cbSize         )
   _XBST_int     ( iHorzSpacing   )
   _XBST_int     ( iVertSpacing   )
   _XBST_int     ( iTitleWrap     )
   _XBST_LOGFONT ( lfFont         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_METAFILEPICT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_METAFILEPICT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi METAFILEPICT structure.
         Defined as METAFILEPICT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="LONG" name="mm" offset="0" size="4" />
         <member type="LONG" name="xExt" offset="4" size="4" />
         <member type="LONG" name="yExt" offset="8" size="4" />
         <member type="HMETAFILE" name="hMF" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( METAFILEPICT  )
   _XBST_LONG      ( mm    )
   _XBST_LONG      ( xExt  )
   _XBST_LONG      ( yExt  )
   _XBST_HMETAFILE ( hMF   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MDINEXTMENU</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MDINEXTMENU</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MDINEXTMENU structure.
         Defined as MDINEXTMENU in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HMENU" name="hmenuIn" offset="0" size="4" />
         <member type="HMENU" name="hmenuNext" offset="4" size="4" />
         <member type="HWND" name="hwndNext" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MDINEXTMENU              )
   _XBST_HMENU  ( hmenuIn     )
   _XBST_HMENU  ( hmenuNext   )
   _XBST_HWND   ( hwndNext    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUBARINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUBARINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUBARINFO structure.
         Defined as MENUBARINFO in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menubarinfo</ref-url>
      <size>32</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcBar" offset="4" size="16" child="true" />
         <member type="HMENU" name="hMenu" offset="20" size="4" />
         <member type="HWND" name="hwndMenu" offset="24" size="4" />
      </members>
      <bitfields storage-type="DWORD" storage-name="_fflags_" offset="28" size="4">
         <bitfield type="BOOL" name="fBarFocused" bit-offset="0" width="1" property="fBarFocused" />
         <bitfield type="BOOL" name="fFocused" bit-offset="1" width="1" property="fFocused" />
         <bitfield type="BOOL" name="fUnused" bit-offset="2" width="30" />
      </bitfields>
      <properties>
         <property type="logical" name="fBarFocused" member="_fflags_" bit="1" />
         <property type="logical" name="fFocused" member="_fflags_" bit="2" />
      </properties>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUBARINFO              )
   _XBST_DWORD ( cbSize     )
   _XBST_RECT  ( rcBar      )
   _XBST_HMENU ( hMenu      )
   _XBST_HWND  ( hwndMenu   )
   _XBST_DWORD ( _fflags_   )
   pc->PropertyCB( "fBarFocused" , "{|s,v| lDwBitOnOff( @s:_fflags_,1,v) }");
   pc->PropertyCB( "fFocused"    , "{|s,v| lDwBitOnOff( @s:_fflags_,2,v) }");
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUEX_TEMPLATE_HEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUEX_TEMPLATE_HEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUEX_TEMPLATE_HEADER structure.
         Defined as MENUEX_TEMPLATE_HEADER in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="WORD" name="wVersion" offset="0" size="2" />
         <member type="WORD" name="wOffset" offset="2" size="2" />
         <member type="DWORD" name="dwHelpId" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_HEADER   )
   _XBST_WORD  ( wVersion )
   _XBST_WORD  ( wOffset  )
   _XBST_DWORD ( dwHelpId )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUEX_TEMPLATE_ITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUEX_TEMPLATE_ITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUEX_TEMPLATE_ITEM structure.
         Defined as MENUEX_TEMPLATE_ITEM in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="DWORD" name="dwHelpId" offset="0" size="4" />
         <member type="DWORD" name="dwType" offset="4" size="4" />
         <member type="DWORD" name="dwState" offset="8" size="4" />
         <member type="DWORD" name="menuId" offset="12" size="4" />
         <member type="WORD" name="bResInfo" offset="16" size="2" />
         <member type="SHORT" name="_wszText_" offset="18" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_ITEM  )
   _XBST_DWORD ( dwHelpId  )
   _XBST_DWORD ( dwType    )
   _XBST_DWORD ( dwState   )
   _XBST_DWORD ( menuId    )
   _XBST_WORD  ( bResInfo  )
   _XBST_short ( _wszText_ ) // WCHAR szText
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUGETOBJECTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUGETOBJECTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUGETOBJECTINFO structure.
         Defined as MENUGETOBJECTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="DWORD" name="dwFlags" offset="0" size="4" />
         <member type="UINT" name="uPos" offset="4" size="4" />
         <member type="HMENU" name="hmenu" offset="8" size="4" />
         <member type="POINTER32" name="riid" offset="12" size="4" />
         <member type="POINTER32" name="pvObj" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUGETOBJECTINFO        )
   _XBST_DWORD      ( dwFlags   )
   _XBST_UINT       ( uPos      )
   _XBST_HMENU      ( hmenu     )
   _XBST_POINTER32  ( riid      )
   _XBST_POINTER32  ( pvObj     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUINFO structure.
         Defined as MENUINFO in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="fMask" offset="4" size="4" />
         <member type="DWORD" name="dwStyle" offset="8" size="4" />
         <member type="UINT" name="cyMax" offset="12" size="4" />
         <member type="HBRUSH" name="hbrBack" offset="16" size="4" />
         <member type="DWORD" name="dwContextHelpID" offset="20" size="4" />
         <member type="POINTER32" name="dwMenuData" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUINFO                 )
   _XBST_DWORD     ( cbSize            )
   _XBST_DWORD     ( fMask             )
   _XBST_DWORD     ( dwStyle           )
   _XBST_UINT      ( cyMax             )
   _XBST_HBRUSH    ( hbrBack           )
   _XBST_DWORD     ( dwContextHelpID   )
   _XBST_POINTER32 ( dwMenuData        )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUITEMINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUITEMINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUITEMINFOA structure.
         Defined as MENUITEMINFO in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfoa</ref-url>
      <size>48</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="fMask" offset="4" size="4" />
         <member type="UINT" name="fType" offset="8" size="4" />
         <member type="UINT" name="fState" offset="12" size="4" />
         <member type="UINT" name="wID" offset="16" size="4" />
         <member type="HMENU" name="hSubMenu" offset="20" size="4" />
         <member type="HBITMAP" name="hbmpChecked" offset="24" size="4" />
         <member type="HBITMAP" name="hbmpUnchecked" offset="28" size="4" />
         <member type="ULONG_PTR" name="dwItemData" offset="32" size="4" />
         <member type="LPSTR" name="dwTypeData" offset="36" size="4" />
         <member type="UINT" name="cch" offset="40" size="4" />
         <member type="HBITMAP" name="hbmpItem" offset="44" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="_cTypeData" target="dwTypeData" offset="36" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUITEMINFO             )
   _XBST_UINT       ( cbSize            )
   _XBST_UINT       ( fMask             )
   _XBST_UINT       ( fType             )
   _XBST_UINT       ( fState            )
   _XBST_UINT       ( wID               )
   _XBST_HMENU      ( hSubMenu          )
   _XBST_HBITMAP    ( hbmpChecked       )
   _XBST_HBITMAP    ( hbmpUnchecked     )
   _XBST_ULONG_PTR  ( dwItemData        )
  pc->GwstBeginUnion();
      _XBST_LPSTR      ( dwTypeData        )
      _XBST_DYNSZ ( _cTypeData        )
  pc->GwstEndUnion();
   _XBST_UINT       ( cch               )
   _XBST_HBITMAP    ( hbmpItem          )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUITEMTEMPLATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUITEMTEMPLATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUITEMTEMPLATE structure.
         Defined as MENUITEMTEMPLATE in ot4xb_wapist_map.ch.
      </description>
      <size>6</size>
      <members>
         <member type="WORD" name="mtOption" offset="0" size="2" />
         <member type="WORD" name="mtID" offset="2" size="2" />
         <member type="SHORT" name="mtString_1" offset="4" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATE         )
   _XBST_WORD  ( mtOption   )
   _XBST_WORD  ( mtID       )
   _XBST_short ( mtString_1 ) // WCHAR mtString[1]
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MENUITEMTEMPLATEHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MENUITEMTEMPLATEHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MENUITEMTEMPLATEHEADER structure.
         Defined as MENUITEMTEMPLATEHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="WORD" name="versionNumber" offset="0" size="2" />
         <member type="WORD" name="offset" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATEHEADER   )
   _XBST_WORD ( versionNumber  )
   _XBST_WORD ( offset         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TPMPARAMS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TPMPARAMS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TPMPARAMS structure.
         Defined as TPMPARAMS in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcExclude" offset="4" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TPMPARAMS                )
   _XBST_UINT ( cbSize    )
   _XBST_RECT ( rcExclude )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ACCEL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ACCEL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ACCEL structure.
         Defined as ACCEL in ot4xb_wapist_map.ch.
      </description>
      <size>5</size>
      <members>
         <member type="BYTE" name="fVirt" offset="0" size="1" />
         <member type="WORD" name="key" offset="1" size="2" />
         <member type="WORD" name="cmd" offset="3" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ACCEL )
   _XBST_BYTE( fVirt )
   _XBST_WORD( key )
   _XBST_WORD( cmd )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MINMAXINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MINMAXINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MINMAXINFO structure.
         Defined as MINMAXINFO in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="WAPIST_POINT" name="ptReserved" offset="0" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptMaxSize" offset="8" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptMaxPosition" offset="16" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptMinTrackSize" offset="24" size="8" child="true" />
         <member type="WAPIST_POINT" name="ptMaxTrackSize" offset="32" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MINMAXINFO )
   _XBST_POINT( ptReserved      )
   _XBST_POINT( ptMaxSize       )
   _XBST_POINT( ptMaxPosition   )
   _XBST_POINT( ptMinTrackSize  )
   _XBST_POINT( ptMaxTrackSize  )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMHDR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMHDR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMHDR structure.
         Defined as NMHDR in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HWND" name="hwndFrom" offset="0" size="4" />
         <member type="UINT" name="idFrom" offset="4" size="4" />
         <member type="UINT" name="code" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMHDR )
   _XBST_HWND (hwndFrom )
   _XBST_UINT (idFrom   )
   _XBST_UINT (code     )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMRBAUTOSIZE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMRBAUTOSIZE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMRBAUTOSIZE structure.
         Defined as NMRBAUTOSIZE in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="BOOL" name="fChanged" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rcTarget" offset="16" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcActual" offset="32" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMRBAUTOSIZE      )
   _XBST_NMHDR ( hdr      )
   _XBST_BOOL  ( fChanged )
   _XBST_RECT  ( rcTarget )
   _XBST_RECT  ( rcActual )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMREBAR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMREBAR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMREBAR structure.
         Defined as NMREBAR in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwMask" offset="12" size="4" />
         <member type="UINT" name="uBand" offset="16" size="4" />
         <member type="UINT" name="fStyle" offset="20" size="4" />
         <member type="UINT" name="wID" offset="24" size="4" />
         <member type="LPARAM" name="lParam" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMREBAR           )
   _XBST_NMHDR   ( hdr    )
   _XBST_DWORD   ( dwMask )
   _XBST_UINT    ( uBand  )
   _XBST_UINT    ( fStyle )
   _XBST_UINT    ( wID    )
   _XBST_LPARAM  ( lParam )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMREBARAUTOBREAK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMREBARAUTOBREAK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMREBARAUTOBREAK structure.
         Defined as NMREBARAUTOBREAK in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="uBand" offset="12" size="4" />
         <member type="UINT" name="wID" offset="16" size="4" />
         <member type="UINT" name="uMsg" offset="20" size="4" />
         <member type="UINT" name="fStyleCurrent" offset="24" size="4" />
         <member type="BOOL" name="fAutoBreak" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMREBARAUTOBREAK  )
   _XBST_NMHDR  ( hdr           )
   _XBST_UINT   ( uBand         )
   _XBST_UINT   ( wID           )
   _XBST_UINT   ( uMsg          )
   _XBST_UINT   ( fStyleCurrent )
   _XBST_BOOL   ( fAutoBreak    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMREBARCHEVRON</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMREBARCHEVRON</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMREBARCHEVRON structure.
         Defined as NMREBARCHEVRON in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="uBand" offset="12" size="4" />
         <member type="UINT" name="wID" offset="16" size="4" />
         <member type="LPARAM" name="lParam" offset="20" size="4" />
         <member type="WAPIST_RECT" name="rc" offset="24" size="16" child="true" />
         <member type="LPARAM" name="lParamNM" offset="40" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMREBARCHEVRON    )
   _XBST_NMHDR     ( hdr      )
   _XBST_UINT      ( uBand    )
   _XBST_UINT      ( wID      )
   _XBST_LPARAM    ( lParam   )
   _XBST_RECT      ( rc       )
   _XBST_LPARAM    ( lParamNM )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMREBARCHILDSIZE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMREBARCHILDSIZE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMREBARCHILDSIZE structure.
         Defined as NMREBARCHILDSIZE in ot4xb_wapist_map.ch.
      </description>
      <size>52</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="uBand" offset="12" size="4" />
         <member type="UINT" name="wID" offset="16" size="4" />
         <member type="WAPIST_RECT" name="rcChild" offset="20" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcBand" offset="36" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMREBARCHILDSIZE  )
   _XBST_NMHDR  ( hdr     )
   _XBST_UINT   ( uBand   )
   _XBST_UINT   ( wID     )
   _XBST_RECT   ( rcChild )
   _XBST_RECT   ( rcBand  )

XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RBHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RBHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RBHITTESTINFO structure.
         Defined as RBHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="UINT" name="flags" offset="8" size="4" />
         <member type="INT" name="iBand" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RBHITTESTINFO     )
   _XBST_POINT  ( pt    )
   _XBST_UINT   ( flags )
   _XBST_int    ( iBand )

XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_REBARBANDINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_REBARBANDINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi REBARBANDINFO structure.
         Defined as REBARBANDINFO in ot4xb_wapist_map.ch.
      </description>
      <size>80</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="fMask" offset="4" size="4" />
         <member type="UINT" name="fStyle" offset="8" size="4" />
         <member type="COLORREF" name="clrFore" offset="12" size="4" />
         <member type="COLORREF" name="clrBack" offset="16" size="4" />
         <member type="LPSTR" name="lpText" offset="20" size="4" />
         <member type="UINT" name="cch" offset="24" size="4" />
         <member type="INT" name="iImage" offset="28" size="4" />
         <member type="HWND" name="hwndChild" offset="32" size="4" />
         <member type="UINT" name="cxMinChild" offset="36" size="4" />
         <member type="UINT" name="cyMinChild" offset="40" size="4" />
         <member type="UINT" name="cx" offset="44" size="4" />
         <member type="HBITMAP" name="hbmBack" offset="48" size="4" />
         <member type="UINT" name="wID" offset="52" size="4" />
         <member type="UINT" name="cyChild" offset="56" size="4" />
         <member type="UINT" name="cyMaxChild" offset="60" size="4" />
         <member type="UINT" name="cyIntegral" offset="64" size="4" />
         <member type="UINT" name="cxIdeal" offset="68" size="4" />
         <member type="LPARAM" name="lParam" offset="72" size="4" />
         <member type="UINT" name="cxHeader" offset="76" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( REBARBANDINFO     )
   _XBST_UINT           (  cbSize      )
   _XBST_UINT           (  fMask       )
   _XBST_UINT           (  fStyle      )
   _XBST_COLORREF       (  clrFore     )
   _XBST_COLORREF       (  clrBack     )
   _XBST_LPSTR          (  lpText      )
   _XBST_UINT           (  cch         )
   _XBST_int            (  iImage      )
   _XBST_HWND           (  hwndChild   )
   _XBST_UINT           (  cxMinChild  )
   _XBST_UINT           (  cyMinChild  )
   _XBST_UINT           (  cx          )
   _XBST_HBITMAP        (  hbmBack     )
   _XBST_UINT           (  wID         )
   _XBST_UINT           (  cyChild     )
   _XBST_UINT           (  cyMaxChild  )
   _XBST_UINT           (  cyIntegral  )
   _XBST_UINT           (  cxIdeal     )
   _XBST_LPARAM         (  lParam      )
   _XBST_UINT           (  cxHeader    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_REBARINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_REBARINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi REBARINFO structure.
         Defined as REBARINFO in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="fMask" offset="4" size="4" />
         <member type="HANDLE" name="himl" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( REBARINFO         )
   _XBST_UINT        ( cbSize  )
   _XBST_UINT        ( fMask   )
   _XBST_HANDLE      ( himl    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBBUTTON</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBBUTTON</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBBUTTON structure.
         Defined as TBBUTTON in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="INT" name="iBitmap" offset="0" size="4" />
         <member type="INT" name="idCommand" offset="4" size="4" />
         <member type="BYTE" name="fsState" offset="8" size="1" />
         <member type="BYTE" name="fsStyle" offset="9" size="1" />
         <member type="WORD" name="wReserved" offset="10" size="2" />
         <member type="DWORD" name="dwData" offset="12" size="4" />
         <member type="LONG" name="iString" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBBUTTON )
  _XBST_int   (  iBitmap    )
  _XBST_int   (  idCommand  )
  _XBST_BYTE  (  fsState    )
  _XBST_BYTE  (  fsStyle    )
  _XBST_WORD  (  wReserved  )
  _XBST_DWORD (  dwData     )
  _XBST_LONG  (  iString    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WNDCLASS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WNDCLASS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WNDCLASSA structure.
         Defined as WNDCLASS in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa</ref-url>
      <size>40</size>
      <members>
         <member type="UINT" name="style" offset="0" size="4" />
         <member type="WNDPROC" name="lpfnWndProc" offset="4" size="4" />
         <member type="INT" name="cbClsExtra" offset="8" size="4" />
         <member type="INT" name="cbWndExtra" offset="12" size="4" />
         <member type="HINSTANCE" name="hInstance" offset="16" size="4" />
         <member type="HICON" name="hIcon" offset="20" size="4" />
         <member type="HCURSOR" name="hCursor" offset="24" size="4" />
         <member type="HBRUSH" name="hbrBackground" offset="28" size="4" />
         <member type="LPSTR" name="lpszMenuName" offset="32" size="4" />
         <member type="LPSTR" name="lpszClassName" offset="36" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cMenuName" target="lpszMenuName" offset="32" size="4" access="string" />
         <helper type="DYNSZ" name="cClassName" target="lpszClassName" offset="36" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(WNDCLASS)
  _XBST_UINT       ( style          )
  _XBST_WNDPROC    ( lpfnWndProc    )
  _XBST_int        ( cbClsExtra     )
  _XBST_int        ( cbWndExtra     )
  _XBST_HINSTANCE  ( hInstance      )
  _XBST_HICON      ( hIcon          )
  _XBST_HCURSOR    ( hCursor        )
  _XBST_HBRUSH     ( hbrBackground  )
  _XBST_LPSTR      ( lpszMenuName   ) pc->GwstBack() ; _XBST_DYNSZ ( cMenuName  )
  _XBST_LPSTR      ( lpszClassName  ) pc->GwstBack() ; _XBST_DYNSZ ( cClassName )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WNDCLASSEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WNDCLASSEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WNDCLASSEX structure.
         Defined as WNDCLASSEX in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa</ref-url>
      <size>48</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="style" offset="4" size="4" />
         <member type="WNDPROC" name="lpfnWndProc" offset="8" size="4" />
         <member type="INT" name="cbClsExtra" offset="12" size="4" />
         <member type="INT" name="cbWndExtra" offset="16" size="4" />
         <member type="HINSTANCE" name="hInstance" offset="20" size="4" />
         <member type="HICON" name="hIcon" offset="24" size="4" />
         <member type="HCURSOR" name="hCursor" offset="28" size="4" />
         <member type="HBRUSH" name="hbrBackground" offset="32" size="4" />
         <member type="LPSTR" name="lpszMenuName" offset="36" size="4" />
         <member type="LPSTR" name="lpszClassName" offset="40" size="4" />
         <member type="HICON" name="hIconSm" offset="44" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cMenuName" target="lpszMenuName" offset="36" size="4" access="string" />
         <helper type="DYNSZ" name="cClassName" target="lpszClassName" offset="40" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(WNDCLASSEX)
  _XBST_UINT       ( cbSize         )
  _XBST_UINT       ( style          )
  _XBST_WNDPROC    ( lpfnWndProc    )
  _XBST_int        ( cbClsExtra     )
  _XBST_int        ( cbWndExtra     )
  _XBST_HINSTANCE  ( hInstance      )
  _XBST_HICON      ( hIcon          )
  _XBST_HCURSOR    ( hCursor        )
  _XBST_HBRUSH     ( hbrBackground  )
  _XBST_LPSTR      ( lpszMenuName   ) ; pc->GwstBack() ; _XBST_DYNSZ ( cMenuName  )
  _XBST_LPSTR      ( lpszClassName  ) ; pc->GwstBack() ; _XBST_DYNSZ ( cClassName )
  _XBST_HICON      ( hIconSm        )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MDICREATESTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MDICREATESTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MDICREATESTRUCT structure.
         Defined as MDICREATESTRUCT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mdicreatestructa</ref-url>
      <size>36</size>
      <members>
         <member type="LPSTR" name="szClass" offset="0" size="4" />
         <member type="LPSTR" name="szTitle" offset="4" size="4" />
         <member type="HANDLE" name="hOwner" offset="8" size="4" />
         <member type="INT" name="x" offset="12" size="4" />
         <member type="INT" name="y" offset="16" size="4" />
         <member type="INT" name="cx" offset="20" size="4" />
         <member type="INT" name="cy" offset="24" size="4" />
         <member type="DWORD" name="style" offset="28" size="4" />
         <member type="LPARAM" name="lParam" offset="32" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cClass" target="szClass" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cTitle" target="szTitle" offset="4" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MDICREATESTRUCT )
  _XBST_LPSTR   ( szClass  ) ; pc->GwstBack() ; _XBST_DYNSZ( cClass )
  _XBST_LPSTR   ( szTitle  ) ; pc->GwstBack() ; _XBST_DYNSZ( cTitle )
  _XBST_HANDLE  ( hOwner   )
  _XBST_int     ( x        )
  _XBST_int     ( y        )
  _XBST_int     ( cx       )
  _XBST_int     ( cy       )
  _XBST_DWORD   ( style    )
  _XBST_LPARAM  ( lParam   )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HARDWAREINPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HARDWAREINPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HARDWAREINPUT structure.
         Defined as HARDWAREINPUT in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="uMsg" offset="0" size="4" />
         <member type="WORD" name="wParamL" offset="4" size="2" />
         <member type="WORD" name="wParamH" offset="6" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HARDWAREINPUT )
  _XBST_DWORD ( uMsg    )
  _XBST_WORD  ( wParamL )
  _XBST_WORD  ( wParamH )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INPUT structure.
         Defined as INPUT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input</ref-url>
      <size>28</size>
      <members>
         <member type="DWORD" name="type" offset="0" size="4" />
         <union offset="4" size="24">
            <member type="WAPIST_MOUSEINPUT" name="mi" offset="4" size="24" child="true" />
            <member type="WAPIST_KEYBDINPUT" name="ki" offset="4" size="16" child="true" />
            <member type="WAPIST_HARDWAREINPUT" name="hi" offset="4" size="8" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INPUT )
  _XBST_DWORD             ( type )
  pc->GwstBeginUnion();
    _XBST_MOUSEINPUT      ( mi )
    _XBST_KEYBDINPUT      ( ki )
    _XBST_HARDWAREINPUT   ( hi )
  pc->GwstEndUnion();
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_KEYBDINPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_KEYBDINPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi KEYBDINPUT structure.
         Defined as KEYBDINPUT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WORD" name="wVk" offset="0" size="2" />
         <member type="WORD" name="wScan" offset="2" size="2" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
         <member type="DWORD" name="time" offset="8" size="4" />
         <member type="ULONG_PTR" name="dwExtraInfo" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( KEYBDINPUT )
    _XBST_WORD       ( wVk         )
    _XBST_WORD       ( wScan       )
    _XBST_DWORD      ( dwFlags     )
    _XBST_DWORD      ( time        )
    _XBST_ULONG_PTR  ( dwExtraInfo )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LASTINPUTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LASTINPUTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LASTINPUTINFO structure.
         Defined as LASTINPUTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwTime" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LASTINPUTINFO )
    _XBST_UINT  ( cbSize )
    _XBST_DWORD ( dwTime )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MOUSEINPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MOUSEINPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MOUSEINPUT structure.
         Defined as MOUSEINPUT in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="LONG" name="dx" offset="0" size="4" />
         <member type="LONG" name="dy" offset="4" size="4" />
         <member type="DWORD" name="mouseData" offset="8" size="4" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
         <member type="DWORD" name="time" offset="16" size="4" />
         <member type="ULONG_PTR" name="dwExtraInfo" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MOUSEINPUT )
    _XBST_LONG      ( dx          )
    _XBST_LONG      ( dy          )
    _XBST_DWORD     ( mouseData   )
    _XBST_DWORD     ( dwFlags     )
    _XBST_DWORD     ( time        )
    _XBST_ULONG_PTR ( dwExtraInfo )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IMAGEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IMAGEINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IMAGEINFO structure.
         Defined as IMAGEINFO in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="HBITMAP" name="hbmImage" offset="0" size="4" />
         <member type="HBITMAP" name="hbmMask" offset="4" size="4" />
         <member type="INT" name="Unused1" offset="8" size="4" />
         <member type="INT" name="Unused2" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rcImage" offset="16" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IMAGEINFO )
    _XBST_HBITMAP   ( hbmImage )
    _XBST_HBITMAP   ( hbmMask  )
    _XBST_int       ( Unused1  )
    _XBST_int       ( Unused2  )
    _XBST_RECT      ( rcImage  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IMAGELISTDRAWPARAMS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IMAGELISTDRAWPARAMS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IMAGELISTDRAWPARAMS structure.
         Defined as IMAGELISTDRAWPARAMS in ot4xb_wapist_map.ch.
      </description>
      <size>68</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="HIMAGELIST" name="himl" offset="4" size="4" />
         <member type="INT" name="i" offset="8" size="4" />
         <member type="HDC" name="hdcDst" offset="12" size="4" />
         <member type="INT" name="x" offset="16" size="4" />
         <member type="INT" name="y" offset="20" size="4" />
         <member type="INT" name="cx" offset="24" size="4" />
         <member type="INT" name="cy" offset="28" size="4" />
         <member type="INT" name="xBitmap" offset="32" size="4" />
         <member type="INT" name="yBitmap" offset="36" size="4" />
         <member type="COLORREF" name="rgbBk" offset="40" size="4" />
         <member type="COLORREF" name="rgbFg" offset="44" size="4" />
         <member type="UINT" name="fStyle" offset="48" size="4" />
         <member type="DWORD" name="dwRop" offset="52" size="4" />
         <member type="DWORD" name="fState" offset="56" size="4" />
         <member type="DWORD" name="Frame" offset="60" size="4" />
         <member type="DWORD" name="crEffect" offset="64" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IMAGELISTDRAWPARAMS )
    _XBST_DWORD         ( cbSize   )
    _XBST_HIMAGELIST    ( himl     )
    _XBST_int           ( i        )
    _XBST_HDC           ( hdcDst   )
    _XBST_int           ( x        )
    _XBST_int           ( y        )
    _XBST_int           ( cx       )
    _XBST_int           ( cy       )
    _XBST_int           ( xBitmap  )
    _XBST_int           ( yBitmap  )
    _XBST_COLORREF      ( rgbBk    )
    _XBST_COLORREF      ( rgbFg    )
    _XBST_UINT          ( fStyle   )
    _XBST_DWORD         ( dwRop    )
    _XBST_DWORD         ( fState   )
    _XBST_DWORD         ( Frame    )
    _XBST_DWORD         ( crEffect )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MSGBOXPARAMS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MSGBOXPARAMS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MSGBOXPARAMS structure.
         Defined as MSGBOXPARAMS in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="HWND" name="hwndOwner" offset="4" size="4" />
         <member type="HINSTANCE" name="hInstance" offset="8" size="4" />
         <member type="LPSTR" name="lpszText" offset="12" size="4" />
         <member type="LPSTR" name="lpszCaption" offset="16" size="4" />
         <member type="DWORD" name="dwStyle" offset="20" size="4" />
         <member type="LPSTR" name="lpszIcon" offset="24" size="4" />
         <member type="DWORD" name="dwContextHelpId" offset="28" size="4" />
         <member type="POINTER32" name="lpfnMsgBoxCallback" offset="32" size="4" />
         <member type="DWORD" name="dwLanguageId" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MSGBOXPARAMS )
    _XBST_UINT             ( cbSize             )
    _XBST_HWND             ( hwndOwner          )
    _XBST_HINSTANCE        ( hInstance          )
    _XBST_LPSTR            ( lpszText           )
    _XBST_LPSTR            ( lpszCaption        )
    _XBST_DWORD            ( dwStyle            )
    _XBST_LPSTR            ( lpszIcon           )
    _XBST_DWORD            ( dwContextHelpId    )
    _XBST_POINTER32        ( lpfnMsgBoxCallback )
    _XBST_DWORD            ( dwLanguageId       )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DLGTEMPLATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DLGTEMPLATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DLGTEMPLATE structure.
         Defined as DLGTEMPLATE in ot4xb_wapist_map.ch.
      </description>
      <size>18</size>
      <members>
         <member type="DWORD" name="style" offset="0" size="4" />
         <member type="DWORD" name="dwExtendedStyle" offset="4" size="4" />
         <member type="WORD" name="cdit" offset="8" size="2" />
         <member type="SHORT" name="x" offset="10" size="2" />
         <member type="SHORT" name="y" offset="12" size="2" />
         <member type="SHORT" name="cx" offset="14" size="2" />
         <member type="SHORT" name="cy" offset="16" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DLGTEMPLATE )
    _XBST_DWORD ( style              )
    _XBST_DWORD ( dwExtendedStyle    )
    _XBST_WORD  ( cdit               )
    _XBST_short ( x                  )
    _XBST_short ( y                  )
    _XBST_short ( cx                 )
    _XBST_short ( cy                 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DLGITEMTEMPLATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DLGITEMTEMPLATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DLGITEMTEMPLATE structure.
         Defined as DLGITEMTEMPLATE in ot4xb_wapist_map.ch.
      </description>
      <size>18</size>
      <members>
         <member type="DWORD" name="style" offset="0" size="4" />
         <member type="DWORD" name="dwExtendedStyle" offset="4" size="4" />
         <member type="SHORT" name="x" offset="8" size="2" />
         <member type="SHORT" name="y" offset="10" size="2" />
         <member type="SHORT" name="cx" offset="12" size="2" />
         <member type="SHORT" name="cy" offset="14" size="2" />
         <member type="WORD" name="id" offset="16" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DLGITEMTEMPLATE  )
    _XBST_DWORD ( style              )
    _XBST_DWORD ( dwExtendedStyle    )
    _XBST_short ( x                  )
    _XBST_short ( y                  )
    _XBST_short ( cx                 )
    _XBST_short ( cy                 )
    _XBST_WORD  ( id                 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FLASHWINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FLASHWINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FLASHWINFO structure.
         Defined as FLASHWINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="HWND" name="hwnd" offset="4" size="4" />
         <member type="DWORD" name="dwFlags" offset="8" size="4" />
         <member type="UINT" name="uCount" offset="12" size="4" />
         <member type="DWORD" name="dwTimeout" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FLASHWINFO )
    _XBST_UINT   ( cbSize    )
    _XBST_HWND   ( hwnd      )
    _XBST_DWORD  ( dwFlags   )
    _XBST_UINT   ( uCount    )
    _XBST_DWORD  ( dwTimeout )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// RTF structures
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BIDIOPTIONS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BIDIOPTIONS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BIDIOPTIONS structure.
         Defined as BIDIOPTIONS in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="WORD" name="wMask" offset="4" size="2" />
         <member type="WORD" name="wEffects" offset="6" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( BIDIOPTIONS )
    _XBST_UINT ( cbSize    )
    _XBST_WORD ( wMask     )
    _XBST_WORD ( wEffects  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CHARFORMAT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CHARFORMAT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CHARFORMAT structure.
         Defined as CHARFORMAT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-charformata</ref-url>
      <size>60</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="DWORD" name="dwEffects" offset="8" size="4" />
         <member type="LONG" name="yHeight" offset="12" size="4" />
         <member type="LONG" name="yOffset" offset="16" size="4" />
         <member type="COLORREF" name="crTextColor" offset="20" size="4" />
         <member type="BYTE" name="bCharSet" offset="24" size="1" />
         <member type="BYTE" name="bPitchAndFamily" offset="25" size="1" />
         <padding offset="26" size="2" />
         <member type="SZSTR" name="szFaceName" offset="28" size="32" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CHARFORMAT )
    _XBST_UINT        ( cbSize          )
    _XBST_DWORD       ( dwMask          )
    _XBST_DWORD       ( dwEffects       )
    _XBST_LONG        ( yHeight         )
    _XBST_LONG        ( yOffset         )
    _XBST_COLORREF    ( crTextColor     )
    _XBST_BYTE        ( bCharSet        )
    _XBST_BYTE        ( bPitchAndFamily )
    pc->GwstAlignNextMember(4);
    _XBST_SZSTR       ( szFaceName , LF_FACESIZE )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CHARFORMAT2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CHARFORMAT2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CHARFORMAT2 structure.
         Defined as CHARFORMAT2 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-charformat2a</ref-url>
      <size>84</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="DWORD" name="dwEffects" offset="8" size="4" />
         <member type="LONG" name="yHeight" offset="12" size="4" />
         <member type="LONG" name="yOffset" offset="16" size="4" />
         <member type="COLORREF" name="crTextColor" offset="20" size="4" />
         <member type="BYTE" name="bCharSet" offset="24" size="1" />
         <member type="BYTE" name="bPitchAndFamily" offset="25" size="1" />
         <padding offset="26" size="2" />
         <member type="SZSTR" name="szFaceName" offset="28" size="32" access="string" />
         <member type="WORD" name="wWeight" offset="60" size="2" />
         <member type="SHORT" name="sSpacing" offset="62" size="2" />
         <member type="COLORREF" name="crBackColor" offset="64" size="4" />
         <member type="LCID" name="lcid" offset="68" size="4" />
         <member type="DWORD" name="dwReserved" offset="72" size="4" />
         <member type="SHORT" name="sStyle" offset="76" size="2" />
         <member type="WORD" name="wKerning" offset="78" size="2" />
         <member type="BYTE" name="bUnderlineType" offset="80" size="1" />
         <member type="BYTE" name="bAnimation" offset="81" size="1" />
         <member type="BYTE" name="bRevAuthor" offset="82" size="1" />
         <member type="BYTE" name="bReserved1" offset="83" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CHARFORMAT2 )
    _XBST_UINT         ( cbSize          )
    _XBST_DWORD        ( dwMask          )
    _XBST_DWORD        ( dwEffects       )
    _XBST_LONG         ( yHeight         )
    _XBST_LONG         ( yOffset         )
    _XBST_COLORREF     ( crTextColor     )
    _XBST_BYTE         ( bCharSet        )
    _XBST_BYTE         ( bPitchAndFamily )
    pc->GwstAlignNextMember(4);
    _XBST_SZSTR        ( szFaceName , LF_FACESIZE )
    _XBST_WORD         ( wWeight         )
    _XBST_SHORT        ( sSpacing        )
    _XBST_COLORREF     ( crBackColor     )
    _XBST_LCID         ( lcid            )
    _XBST_DWORD        ( dwReserved      )
    _XBST_SHORT        ( sStyle          )
    _XBST_WORD         ( wKerning        )
    _XBST_BYTE         ( bUnderlineType  )
    _XBST_BYTE         ( bAnimation      )
    _XBST_BYTE         ( bRevAuthor      )
    _XBST_BYTE         ( bReserved1      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CHARRANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CHARRANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CHARRANGE structure.
         Defined as CHARRANGE in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LONG" name="cpMin" offset="0" size="4" />
         <member type="LONG" name="cpMax" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CHARRANGE )
    _XBST_LONG        ( cpMin )
    _XBST_LONG        ( cpMax )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COMPCOLOR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COMPCOLOR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COMPCOLOR structure.
         Defined as COMPCOLOR in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="COLORREF" name="crText" offset="0" size="4" />
         <member type="COLORREF" name="crBackground" offset="4" size="4" />
         <member type="DWORD" name="dwEffects" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COMPCOLOR )
    _XBST_COLORREF ( crText        )
    _XBST_COLORREF ( crBackground  )
    _XBST_DWORD    ( dwEffects     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_EDITSTREAM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_EDITSTREAM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi EDITSTREAM structure.
         Defined as EDITSTREAM in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="DWORD" name="dwCookie" offset="0" size="4" />
         <member type="DWORD" name="dwError" offset="4" size="4" />
         <member type="DWORD" name="pfnCallback" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( EDITSTREAM )
    _XBST_DWORD ( dwCookie    )
    _XBST_DWORD ( dwError     )
    _XBST_DWORD ( pfnCallback )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENCORRECTTEXT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENCORRECTTEXT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENCORRECTTEXT structure.
         Defined as ENCORRECTTEXT in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="WAPIST_CHARRANGE" name="chrg" offset="12" size="8" child="true" />
         <member type="WORD" name="seltyp" offset="20" size="2" />
         <padding offset="22" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENCORRECTTEXT )
   _XBST_NMHDR     ( nmhdr  )
   _XBST_CHARRANGE ( chrg   )
   _XBST_WORD      ( seltyp )
   pc->GwstSetOffset(sizeof(ENCORRECTTEXT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENDROPFILES</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENDROPFILES</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENDROPFILES structure.
         Defined as ENDROPFILES in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="HANDLE" name="hDrop" offset="12" size="4" />
         <member type="LONG" name="cp" offset="16" size="4" />
         <member type="BOOL" name="fProtected" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENDROPFILES )
   _XBST_NMHDR  ( nmhdr      )
   _XBST_HANDLE ( hDrop      )
   _XBST_LONG   ( cp         )
   _XBST_BOOL   ( fProtected )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENLINK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENLINK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENLINK structure.
         Defined as ENLINK in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="UINT" name="msg" offset="12" size="4" />
         <member type="WPARAM" name="wParam" offset="16" size="4" />
         <member type="LPARAM" name="lParam" offset="20" size="4" />
         <member type="WAPIST_CHARRANGE" name="chrg" offset="24" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENLINK )
   _XBST_NMHDR     ( nmhdr   )
   _XBST_UINT      ( msg     )
   _XBST_WPARAM    ( wParam  )
   _XBST_LPARAM    ( lParam  )
   _XBST_CHARRANGE ( chrg    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENLOWFIRTF</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENLOWFIRTF</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENLOWFIRTF structure.
         Defined as ENLOWFIRTF in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="szControl" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENLOWFIRTF )
   _XBST_NMHDR ( nmhdr     )
   _XBST_LPSTR ( szControl )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENOLEOPFAILED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENOLEOPFAILED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENOLEOPFAILED structure.
         Defined as ENOLEOPFAILED in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LONG" name="iob" offset="12" size="4" />
         <member type="LONG" name="lOper" offset="16" size="4" />
         <member type="HRESULT" name="hr" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENOLEOPFAILED )
   _XBST_NMHDR   ( nmhdr )
   _XBST_LONG    ( iob   )
   _XBST_LONG    ( lOper )
   _XBST_HRESULT ( hr    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENPROTECTED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENPROTECTED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENPROTECTED structure.
         Defined as ENPROTECTED in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="UINT" name="msg" offset="12" size="4" />
         <member type="WPARAM" name="wParam" offset="16" size="4" />
         <member type="LPARAM" name="lParam" offset="20" size="4" />
         <member type="WAPIST_CHARRANGE" name="chrg" offset="24" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENPROTECTED )
   _XBST_NMHDR     ( nmhdr  )
   _XBST_UINT      ( msg    )
   _XBST_WPARAM    ( wParam )
   _XBST_LPARAM    ( lParam )
   _XBST_CHARRANGE ( chrg   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ENSAVECLIPBOARD</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ENSAVECLIPBOARD</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi ENSAVECLIPBOARD structure.
         Defined as ENSAVECLIPBOARD in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LONG" name="cObjectCount" offset="12" size="4" />
         <member type="LONG" name="cch" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ENSAVECLIPBOARD )
   _XBST_NMHDR ( nmhdr        )
   _XBST_LONG  ( cObjectCount )
   _XBST_LONG  ( cch          )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FINDTEXT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FINDTEXT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FINDTEXT structure.
         Defined as FINDTEXT in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_CHARRANGE" name="chrg" offset="0" size="8" child="true" />
         <member type="LPSTR" name="lpstrText" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FINDTEXT ) // Ojo resolver colisión con la función FindText() de comdlg32.dll
   _XBST_CHARRANGE  ( chrg      )
   _XBST_LPSTR      ( lpstrText )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FINDTEXTEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FINDTEXTEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FINDTEXTEX structure.
         Defined as FINDTEXTEX in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_CHARRANGE" name="chrg" offset="0" size="8" child="true" />
         <member type="LPSTR" name="lpstrText" offset="8" size="4" />
         <member type="WAPIST_CHARRANGE" name="chrgText" offset="12" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FINDTEXTEX )
   _XBST_CHARRANGE  ( chrg      )
   _XBST_LPSTR      ( lpstrText )
   _XBST_CHARRANGE  ( chrgText      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FORMATRANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FORMATRANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FORMATRANGE structure.
         Defined as FORMATRANGE in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="HDC" name="hdc" offset="0" size="4" />
         <member type="HDC" name="hdcTarget" offset="4" size="4" />
         <member type="WAPIST_RECT" name="rc" offset="8" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcPage" offset="24" size="16" child="true" />
         <member type="WAPIST_CHARRANGE" name="chrg" offset="40" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FORMATRANGE )
   _XBST_HDC       ( hdc       )
   _XBST_HDC       ( hdcTarget )
   _XBST_RECT      ( rc        )
   _XBST_RECT      ( rcPage    )
   _XBST_CHARRANGE ( chrg      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GETTEXTEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GETTEXTEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GETTEXTEX structure.
         Defined as GETTEXTEX in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="DWORD" name="cb" offset="0" size="4" />
         <member type="DWORD" name="flags" offset="4" size="4" />
         <member type="UINT" name="codepage" offset="8" size="4" />
         <member type="LPSTR" name="lpDefaultChar" offset="12" size="4" />
         <member type="POINTER32" name="lpUsedDefChar" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( GETTEXTEX )
   _XBST_DWORD      ( cb            )
   _XBST_DWORD      ( flags         )
   _XBST_UINT       ( codepage      )
   _XBST_LPSTR      ( lpDefaultChar )
   _XBST_POINTER32  ( lpUsedDefChar )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GETTEXTLENGTHEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GETTEXTLENGTHEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GETTEXTLENGTHEX structure.
         Defined as GETTEXTLENGTHEX in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="flags" offset="0" size="4" />
         <member type="UINT" name="codepage" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( GETTEXTLENGTHEX )
   _XBST_DWORD  ( flags    )
   _XBST_UINT   ( codepage )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HYPHENATEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HYPHENATEINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HYPHENATEINFO structure.
         Defined as HYPHENATEINFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="SHORT" name="cbSize" offset="0" size="2" />
         <member type="SHORT" name="dxHyphenateZone" offset="2" size="2" />
         <member type="DWORD" name="pfnHyphenate" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HYPHENATEINFO )
   _XBST_SHORT  ( cbSize          )
   _XBST_SHORT  ( dxHyphenateZone )
   _XBST_DWORD  ( pfnHyphenate    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HYPHRESULT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HYPHRESULT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HYPHRESULT structure.
         Defined as HYPHRESULT in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="INT" name="khyph" offset="0" size="4" />
         <member type="LONG" name="ichHyph" offset="4" size="4" />
         <member type="SHORT" name="chHyph" offset="8" size="2" />
         <padding offset="10" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HYPHRESULT )
   _XBST_int   ( khyph   )
   _XBST_LONG  ( ichHyph )
   _XBST_SHORT ( chHyph  )
   pc->GwstSetOffset(sizeof(HYPHRESULT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IMECOMPTEXT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IMECOMPTEXT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IMECOMPTEXT structure.
         Defined as IMECOMPTEXT in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LONG" name="cb" offset="0" size="4" />
         <member type="DWORD" name="flags" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IMECOMPTEXT )
   _XBST_LONG  ( cb     )
   _XBST_DWORD ( flags  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MSGFILTER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MSGFILTER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MSGFILTER structure.
         Defined as MSGFILTER in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="UINT" name="msg" offset="12" size="4" />
         <member type="WPARAM" name="wParam" offset="16" size="4" />
         <member type="LPARAM" name="lParam" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MSGFILTER )
   _XBST_NMHDR  ( nmhdr  )
   _XBST_UINT   ( msg    )
   _XBST_WPARAM ( wParam )
   _XBST_LPARAM ( lParam )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OBJECTPOSITIONS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OBJECTPOSITIONS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi OBJECTPOSITIONS structure.
         Defined as OBJECTPOSITIONS in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LONG" name="cObjectCount" offset="12" size="4" />
         <member type="POINTER32" name="pcpPositions" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( OBJECTPOSITIONS )
   _XBST_NMHDR     ( nmhdr        )
   _XBST_LONG      ( cObjectCount )
   _XBST_POINTER32 ( pcpPositions )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PARAFORMAT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PARAFORMAT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PARAFORMAT structure.
         Defined as PARAFORMAT in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="WORD" name="wNumbering" offset="8" size="2" />
         <member type="WORD" name="wReserved" offset="10" size="2" />
         <member type="LONG" name="dxStartIndent" offset="12" size="4" />
         <member type="LONG" name="dxRightIndent" offset="16" size="4" />
         <member type="LONG" name="dxOffset" offset="20" size="4" />
         <member type="WORD" name="wAlignment" offset="24" size="2" />
         <member type="SHORT" name="cTabCount" offset="26" size="2" />
         <member type="BINSTR" name="rgxTabs" offset="28" size="128" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PARAFORMAT )
   _XBST_UINT  ( cbSize        )
   _XBST_DWORD ( dwMask        )
   _XBST_WORD  ( wNumbering    )
   _XBST_WORD  ( wReserved     )
   _XBST_LONG  ( dxStartIndent )
   _XBST_LONG  ( dxRightIndent )
   _XBST_LONG  ( dxOffset      )
   _XBST_WORD  ( wAlignment    )
   _XBST_SHORT ( cTabCount     )
   _XBST_BINSTR( rgxTabs, (MAX_TAB_STOPS * sizeof(LONG)) )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PARAFORMAT2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PARAFORMAT2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PARAFORMAT2 structure.
         Defined as PARAFORMAT2 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-paraformat2</ref-url>
      <size>188</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="WORD" name="wNumbering" offset="8" size="2" />
         <member type="WORD" name="wReserved" offset="10" size="2" />
         <member type="LONG" name="dxStartIndent" offset="12" size="4" />
         <member type="LONG" name="dxRightIndent" offset="16" size="4" />
         <member type="LONG" name="dxOffset" offset="20" size="4" />
         <member type="WORD" name="wAlignment" offset="24" size="2" />
         <member type="SHORT" name="cTabCount" offset="26" size="2" />
         <member type="BINSTR" name="rgxTabs" offset="28" size="128" />
         <member type="LONG" name="dySpaceBefore" offset="156" size="4" />
         <member type="LONG" name="dySpaceAfter" offset="160" size="4" />
         <member type="LONG" name="dyLineSpacing" offset="164" size="4" />
         <member type="SHORT" name="sStyle" offset="168" size="2" />
         <member type="BYTE" name="bLineSpacingRule" offset="170" size="1" />
         <member type="BYTE" name="bOutlineLevel" offset="171" size="1" />
         <member type="WORD" name="wShadingWeight" offset="172" size="2" />
         <member type="WORD" name="wShadingStyle" offset="174" size="2" />
         <member type="WORD" name="wNumberingStart" offset="176" size="2" />
         <member type="WORD" name="wNumberingStyle" offset="178" size="2" />
         <member type="WORD" name="wNumberingTab" offset="180" size="2" />
         <member type="WORD" name="wBorderSpace" offset="182" size="2" />
         <member type="WORD" name="wBorderWidth" offset="184" size="2" />
         <member type="WORD" name="wBorders" offset="186" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PARAFORMAT2 )
   _XBST_UINT  ( cbSize        )
   _XBST_DWORD ( dwMask        )
   _XBST_WORD  ( wNumbering    )
   _XBST_WORD  ( wReserved     )
   _XBST_LONG  ( dxStartIndent )
   _XBST_LONG  ( dxRightIndent )
   _XBST_LONG  ( dxOffset      )
   _XBST_WORD  ( wAlignment    )
   _XBST_SHORT ( cTabCount     )
   _XBST_BINSTR( rgxTabs, (MAX_TAB_STOPS * sizeof(LONG)) )
   _XBST_LONG  ( dySpaceBefore    )
   _XBST_LONG  ( dySpaceAfter     )
   _XBST_LONG  ( dyLineSpacing    )
   _XBST_SHORT ( sStyle           )
   _XBST_BYTE  ( bLineSpacingRule )
   _XBST_BYTE  ( bOutlineLevel    )
   _XBST_WORD  ( wShadingWeight   )
   _XBST_WORD  ( wShadingStyle    )
   _XBST_WORD  ( wNumberingStart  )
   _XBST_WORD  ( wNumberingStyle  )
   _XBST_WORD  ( wNumberingTab    )
   _XBST_WORD  ( wBorderSpace     )
   _XBST_WORD  ( wBorderWidth     )
   _XBST_WORD  ( wBorders         )
   pc->GwstSetOffset(sizeof(PARAFORMAT2) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PUNCTUATION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PUNCTUATION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PUNCTUATION structure.
         Defined as PUNCTUATION in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="UINT" name="iSize" offset="0" size="4" />
         <member type="LPSTR" name="szPunctuation" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PUNCTUATION )
   _XBST_UINT   ( iSize         )
   _XBST_LPSTR  ( szPunctuation )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_REOBJECT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_REOBJECT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi REOBJECT structure.
         Defined as REOBJECT in ot4xb_wapist_map.ch.
      </description>
      <size>56</size>
      <members>
         <member type="DWORD" name="cbStruct" offset="0" size="4" />
         <member type="LONG" name="cp" offset="4" size="4" />
         <member type="WAPIST_CLSID" name="clsid" offset="8" size="16" child="true" />
         <member type="DWORD" name="poleobj" offset="24" size="4" />
         <member type="DWORD" name="pstg" offset="28" size="4" />
         <member type="DWORD" name="polesite" offset="32" size="4" />
         <member type="WAPIST_SIZEL" name="sizel" offset="36" size="8" child="true" />
         <member type="DWORD" name="dvaspect" offset="44" size="4" />
         <member type="DWORD" name="dwFlags" offset="48" size="4" />
         <member type="DWORD" name="dwUser" offset="52" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( REOBJECT )
   _XBST_DWORD  ( cbStruct )
   _XBST_LONG   ( cp       )
   _XBST_CLSID  ( clsid    )
   _XBST_DWORD  ( poleobj  )
   _XBST_DWORD  ( pstg     )
   _XBST_DWORD  ( polesite )
   _XBST_SIZEL  ( sizel    )
   _XBST_DWORD  ( dvaspect )
   _XBST_DWORD  ( dwFlags  )
   _XBST_DWORD  ( dwUser   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_REPASTESPECIAL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_REPASTESPECIAL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi REPASTESPECIAL structure.
         Defined as REPASTESPECIAL in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwAspect" offset="0" size="4" />
         <member type="DWORD" name="dwParam" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( REPASTESPECIAL )
   _XBST_DWORD ( dwAspect )
   _XBST_DWORD ( dwParam  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_REQRESIZE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_REQRESIZE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi REQRESIZE structure.
         Defined as REQRESIZE in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="WAPIST_RECT" name="rc" offset="12" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( REQRESIZE )
   _XBST_NMHDR ( nmhdr )
   _XBST_RECT  ( rc    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SELCHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SELCHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SELCHANGE structure.
         Defined as SELCHANGE in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-selchange</ref-url>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="WAPIST_CHARRANGE" name="chrg" offset="12" size="8" child="true" />
         <member type="WORD" name="seltyp" offset="20" size="2" />
         <padding offset="22" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SELCHANGE )
   _XBST_NMHDR      ( nmhdr  )
   _XBST_CHARRANGE  ( chrg   )
   _XBST_WORD       ( seltyp )
   pc->GwstSetOffset(sizeof(SELCHANGE) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SETTEXTEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SETTEXTEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SETTEXTEX structure.
         Defined as SETTEXTEX in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="flags" offset="0" size="4" />
         <member type="UINT" name="codepage" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SETTEXTEX )
   _XBST_DWORD ( flags    )
   _XBST_UINT  ( codepage )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TEXTRANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TEXTRANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TEXTRANGE structure.
         Defined as TEXTRANGE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_CHARRANGE" name="chrg" offset="0" size="8" child="true" />
         <member type="LPSTR" name="lpstrText" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TEXTRANGE )
   _XBST_CHARRANGE ( chrg      )
   _XBST_LPSTR     ( lpstrText )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_GUID</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_GUID</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi GUID structure.
         Defined as GUID in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="ULONG" name="Data1" offset="0" size="4" />
         <member type="WORD" name="Data2" offset="4" size="2" />
         <member type="WORD" name="Data3" offset="6" size="2" />
         <member type="BINSTR" name="Data4" offset="8" size="8" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( GUID )
   _XBST_ULONG   ( Data1 )
   _XBST_WORD    ( Data2 )
   _XBST_WORD    ( Data3 )
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CLSID</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CLSID</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CLSID structure.
         Defined as CLSID in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="ULONG" name="Data1" offset="0" size="4" />
         <member type="WORD" name="Data2" offset="4" size="2" />
         <member type="WORD" name="Data3" offset="6" size="2" />
         <member type="BINSTR" name="Data4" offset="8" size="8" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CLSID )
   _XBST_ULONG   ( Data1 )
   _XBST_WORD    ( Data2 )
   _XBST_WORD    ( Data3 )
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// winsock structures
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IN_ADDR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IN_ADDR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IN_ADDR structure.
         Defined as IN_ADDR in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock2/ns-winsock2-in_addr</ref-url>
      <size>4</size>
      <members>
         <union name="S_un" offset="0" size="4">
            <struct name="S_un_b" offset="0" size="4">
               <member type="BYTE" name="s_b1" offset="0" size="1" />
               <member type="BYTE" name="s_b2" offset="1" size="1" />
               <member type="BYTE" name="s_b3" offset="2" size="1" />
               <member type="BYTE" name="s_b4" offset="3" size="1" />
            </struct>
            <struct name="S_un_w" offset="0" size="4">
               <member type="WORD" name="s_w1" offset="0" size="2" />
               <member type="WORD" name="s_w2" offset="2" size="2" />
            </struct>
            <member type="DWORD" name="S_addr" offset="0" size="4" />
         </union>
      </members>
      <ot4xb-helpers>
         <helper name="s_net" target="s_b1" />
         <helper name="s_host" target="s_b2" />
         <helper name="s_lh" target="s_b3" />
         <helper name="s_impno" target="s_b4" />
         <helper name="s_imp" target="s_w2" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IN_ADDR )
   _XBST_BYTE    ( s_b1 ) ; pc->GwstBack() ; _XBST_BYTE( s_net   )
   _XBST_BYTE    ( s_b2 ) ; pc->GwstBack() ; _XBST_BYTE( s_host  )
   _XBST_BYTE    ( s_b3 ) ; pc->GwstBack() ; _XBST_BYTE( s_lh    )
   _XBST_BYTE    ( s_b4 ) ; pc->GwstBack() ; _XBST_BYTE( s_impno )
   pc->GwstSetOffset(0);
   _XBST_WORD    ( s_w1 )
   _XBST_WORD    ( s_w2 ) ; pc->GwstBack() ; _XBST_WORD( s_imp )
   pc->GwstSetOffset(0);
   _XBST_DWORD   ( S_addr )
   pc->PropertyCB("S_un_b" , "{|s| s }");
   pc->PropertyCB("S_un_w" , "{|s| s }");
   pc->PropertyCB("S_un"   , "{|s| s }");
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKADDR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKADDR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKADDR structure.
         Defined as SOCKADDR in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WORD" name="sa_family" offset="0" size="2" />
         <member type="BINSTR" name="sa_data" offset="2" size="14" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKADDR )
   _XBST_WORD    ( sa_family )
   _XBST_BINSTR  ( sa_data , 14 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKET_ADDRESS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKET_ADDRESS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKET_ADDRESS structure.
         Defined as SOCKET_ADDRESS in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="POINTER32" name="lpSockaddr" offset="0" size="4" />
         <member type="INT" name="iSockaddrLength" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKET_ADDRESS )
   _XBST_POINTER( lpSockaddr )
   _XBST_INT(     iSockaddrLength )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKET_ADDRESS_LIST</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKET_ADDRESS_LIST</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKET_ADDRESS_LIST structure.
         Defined as SOCKET_ADDRESS_LIST in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-socket_address_list</ref-url>
      <size>12</size>
      <members>
         <member type="INT" name="iAddressCount" offset="0" size="4" />
         <member type="WAPIST_SOCKET_ADDRESS" name="_Address_" offset="4" size="8" child="true" />
      </members>
      <ot4xb-helpers>
         <helper type="embedded-array" name="Address" element-type="WAPIST_SOCKET_ADDRESS" count-member="iAddressCount" first-member="_Address_" />
      </ot4xb-helpers>
      <methods>
         <method name="ReqSize" returns="numeric">Returns the byte size required for the requested address count.</method>
      </methods>   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKET_ADDRESS_LIST )
   _XBST_INT( iAddressCount )
   _XBST_SOCKET_ADDRESS(  _Address_ )
   pc->Var( "_aa_" );
   pc->GwstBack();
   pc->Member_EmbededStructArray( "Address","WAPIST_SOCKET_ADDRESS","_Address_","iAddressCount",
                                  pc->GwstGetOffset(),sizeof(SOCKET_ADDRESS) );
   pc->MethodCB( "ReqSize" , pc->cbbs("{|s,n| iif(n == NIL,n := s:iAddressCount,),n := iif(n < 1, 0, n-1),"
                                              "s:_sizeof_() + ( n * %i)  }", sizeof(SOCKET_ADDRESS) ));
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_CSADDR_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_CSADDR_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi CSADDR_INFO structure.
         Defined as CSADDR_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_SOCKET_ADDRESS" name="LocalAddr" offset="0" size="8" child="true" />
         <member type="WAPIST_SOCKET_ADDRESS" name="RemoteAddr" offset="8" size="8" child="true" />
         <member type="INT" name="iSocketType" offset="16" size="4" />
         <member type="INT" name="iProtocol" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( CSADDR_INFO )
   _XBST_SOCKET_ADDRESS(  LocalAddr )
   _XBST_SOCKET_ADDRESS(  RemoteAddr )
   _XBST_INT( iSocketType )
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKADDR_STORAGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKADDR_STORAGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKADDR_STORAGE structure.
         Defined as SOCKADDR_STORAGE in ot4xb_wapist_map.ch.
      </description>
      <size>128</size>
      <members>
         <member type="SHORT" name="ss_family" offset="0" size="2" />
         <member type="BINSTR" name="__ss_pad1" offset="2" size="6" />
         <member type="INT64" name="__ss_align" offset="8" size="8" />
         <member type="BINSTR" name="__ss_pad2" offset="16" size="112" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKADDR_STORAGE )
   _XBST_SHORT( ss_family )
   _XBST_BINSTR( __ss_pad1 , 6 )
   _XBST_INT64(__ss_align )
   _XBST_BINSTR( __ss_pad2 , 112 )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SCOPE_ID</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SCOPE_ID</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SCOPE_ID structure.
         Defined as SCOPE_ID in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/ws2ipdef/ns-ws2ipdef-scope_id</ref-url>
      <size>4</size>
      <members>
         <member type="DWORD" name="Value" offset="0" size="4" />
      </members>
      <bitfields storage-type="DWORD" storage-name="Value" offset="0" size="4">
         <bitfield type="DWORD" name="Zone" bit-offset="0" width="28" />
         <bitfield type="DWORD" name="Level" bit-offset="28" width="4" />
      </bitfields>   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SCOPE_ID )
   _XBST_DWORD( Value )
   pc->Member_BitField("Zone","Value",0,28,32);
   pc->Member_BitField("Level","Value",28,4,32);
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKADDR_IN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKADDR_IN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKADDR_IN structure.
         Defined as SOCKADDR_IN in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WORD" name="sin_family" offset="0" size="2" />
         <member type="WORD" name="sin_port" offset="2" size="2" />
         <member type="WAPIST_IN_ADDR" name="sin_addr" offset="4" size="?" child="true" />
         <member type="BINSTR" name="sin_zero" offset="4" size="8" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKADDR_IN )
   _XBST_WORD( sin_family  )
   _XBST_WORD( sin_port    )
   _XBST_IN_ADDR( sin_addr )
   _XBST_BINSTR( sin_zero , 8)
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSABUF</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSABUF</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSABUF structure.
         Defined as WSABUF in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="ULONG" name="len" offset="0" size="4" />
         <member type="LPSTR" name="buf" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSABUF )
   _XBST_ULONG( len )
   _XBST_LPSTR( buf )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( common_structures_ns )
static WSACMSGHDR* wsamsg_CMSG_FIRSTHDR( WSAMSG* p ){ return WSA_CMSG_FIRSTHDR(p); }
static WSACMSGHDR* wsamsg_CMSG_NXTHDR( WSAMSG* p1 , WSACMSGHDR* p2 ){ return WSA_CMSG_NXTHDR(p1,p2); }
static DWORD  wsamsg_CMSGHDR_ALIGN(DWORD n ){ return WSA_CMSGHDR_ALIGN(n); }
static DWORD  wsamsg_CMSGDATA_ALIGN(DWORD n ){ return WSA_CMSGDATA_ALIGN(n); }
static LPBYTE wsamsg_CMSG_DATA(WSACMSGHDR* p){ return WSA_CMSG_DATA(p);}
static SIZE_T wsamsg_CMSG_SPACE(SIZE_T n){ return WSA_CMSG_SPACE(n);}
static SIZE_T wsamsg_CMSG_LEN(SIZE_T n){ return WSA_CMSG_LEN(n);}
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAMSG</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAMSG</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinSock WSAMSG structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-wsamsg</ref-url>
      <members>
         <member type="POINTER32" name="name" />
         <member type="INT" name="namelen" />
         <member type="POINTER32" name="lpBuffers" />
         <member type="ULONG" name="dwBufferCount" />
         <member type="WAPIST_WSABUF" name="Control" child="true" />
         <member type="ULONG" name="dwFlags" />
      </members>
      <methods>
         <method name="CMSGHDR_ALIGN" scope="class" />
         <method name="CMSGDATA_ALIGN" scope="class" />
         <method name="CMSG_FIRSTHDR" scope="class" />
         <method name="CMSG_NXTHDR" scope="class" />
         <method name="CMSG_DATA" scope="class" />
         <method name="CMSG_SPACE" scope="class" />
         <method name="CMSG_LEN" scope="class" />
      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAMSG )
   _XBST_POINTER32( name )
   _XBST_INT(       namelen )
   _XBST_POINTER32( lpBuffers )
   _XBST_ULONG(     dwBufferCount)
   _XBST_WSABUF(    Control )
   _XBST_ULONG(     dwFlags )

   pc->ClassMethodCB( "CMSGHDR_ALIGN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSGHDR_ALIGN ));
   pc->ClassMethodCB( "CMSGDATA_ALIGN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSGDATA_ALIGN ));

   pc->ClassMethodCB( "CMSG_FIRSTHDR" ,pc->cbbs("{|s,p| FpQCall(%i,\"__pt__pt\",p)}",
                      common_structures_ns::wsamsg_CMSG_FIRSTHDR ));
   pc->ClassMethodCB( "CMSG_NXTHDR" ,pc->cbbs("{|s,p1,p2| FpQCall(%i,\"__pt__pt__pt\",p1,p2)}",
                      common_structures_ns::wsamsg_CMSG_NXTHDR ));

   pc->ClassMethodCB( "CMSG_DATA" ,pc->cbbs("{|s,p| FpQCall(%i,\"__pt__pt\",p)}",
                      common_structures_ns::wsamsg_CMSG_DATA ));

   pc->ClassMethodCB( "CMSG_SPACE" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSG_SPACE ));
   pc->ClassMethodCB( "CMSG_LEN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSG_LEN ));

XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACMSGHDR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACMSGHDR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACMSGHDR structure.
         Defined as WSACMSGHDR in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="SIZE_T" name="cmsg_len" offset="0" size="4" />
         <member type="INT" name="cmsg_level" offset="4" size="4" />
         <member type="INT" name="cmsg_type" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACMSGHDR )
   _XBST_SIZE_T(  cmsg_len   )
   _XBST_INT(     cmsg_level )
   _XBST_INT(     cmsg_type  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( common_structures_ns )
#pragma warning( push )
#pragma warning( disable : 4127 )
static void fd_set_FD_CLR(SOCKET fd , fd_set* set){ FD_CLR(fd,set);}
static void fd_set_FD_SET(SOCKET fd , fd_set* set,SIZE_T cs )
{
   do
   {
      u_int __i;
      for(__i = 0; __i < ((fd_set FAR *)(set))->fd_count; __i++)
      {
         if (((fd_set FAR *)(set))->fd_array[__i] == (fd)){break;}
      }
      if(__i == ((fd_set FAR *)(set))->fd_count)
      {
         if(((fd_set FAR *)(set))->fd_count < cs )
         {
            ((fd_set FAR *)(set))->fd_array[__i] = (fd);
            ((fd_set FAR *)(set))->fd_count++;
         }
      }
   } while(0);
}
static void fd_set_FD_ZERO(fd_set* set){ FD_ZERO(set);}
static void fd_set_FD_ISSET(SOCKET fd , fd_set* set){ FD_ISSET(fd,set);}
#pragma warning( pop )
END_NAMESPACE()
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FD_SET</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FD_SET</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FD_SET structure.
         Defined as FD_SET in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-fd_set</ref-url>
      <size>260</size>
      <members>
         <member type="UINT" name="fd_count" offset="0" size="4" />
         <member type="BINSTR" name="fd_array" offset="4" size="256" />
      </members>
      <methods>
         <method name="FD_CLR" scope="class" />
         <method name="FD_SET" scope="class" />
         <method name="FD_ZERO" scope="class" />
         <method name="FD_ISSET" scope="class" />      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FD_SET )
   _XBST_UINT( fd_count )
   _XBST_BINSTR( fd_array , 64 * sizeof(SOCKET) )
   pc->ClassMethodCB( "FD_CLR" ,pc->cbbs("{|s,n,p|FpQCall(%i,\"__sl__sl__pt__sl\",n,@p)}",
                      common_structures_ns::fd_set_FD_CLR ));
   pc->ClassMethodCB( "FD_SET" ,pc->cbbs("{|s,n,p,cs|iif(cs == NIL,cs := 64,),"
                                          " FpQCall(%i,\"__sl__sl__pt__sl\",n,@p,cs)}",
                      common_structures_ns::fd_set_FD_SET ));
   pc->ClassMethodCB( "FD_ZERO" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__pt\",@p)}",
                      common_structures_ns::fd_set_FD_ZERO ));
   pc->ClassMethodCB( "FD_ISSET" ,pc->cbbs("{|s,n,p| FpQCall(%i,\"__sl__sl__pt\",n,@p)}",
                      common_structures_ns::fd_set_FD_ISSET ));

XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TIMEVAL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TIMEVAL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TIMEVAL structure.
         Defined as TIMEVAL in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-timeval</ref-url>
      <size>8</size>
      <members>
         <member type="LONG" name="tv_sec" offset="0" size="4" />
         <member type="LONG" name="tv_usec" offset="4" size="4" />
      </members>
      <methods>
         <method name="IsSet" returns="logical" />
         <method name="Clear" returns="Self" />
         <method name="cmp" scope="class" />      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TIMEVAL )
   _XBST_LONG(  tv_sec  )
   _XBST_LONG(  tv_usec )
   pc->MethodCB("IsSet","{|s| nOr(s:tv_sec,s:tv_usec) != 0 }");
   pc->MethodCB("Clear","{|s| s:tv_sec := 0 , s:tv_usec := 0 , s}");
   pc->ClassMethodCB("cmp","{|s,a,b|i64cmp({a:tv_usec,a:tv_sec},{b:tv_usec,b:tv_sec})}");
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HOSTENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HOSTENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HOSTENT structure.
         Defined as HOSTENT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-hostent</ref-url>
      <size>16</size>
      <members>
         <member type="LPSTR" name="h_name" offset="0" size="4" />
         <member type="POINTER32" name="h_aliases" offset="4" size="4" />
         <member type="SHORT" name="h_addrtype" offset="8" size="2" />
         <member type="SHORT" name="h_length" offset="10" size="2" />
         <member type="POINTER32" name="h_addr_list" offset="12" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cName" target="h_name" offset="0" size="4" access="string" />
         <helper type="POINTER32" name="h_addr" target="h_addr_list" offset="12" size="4" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HOSTENT )
   _XBST_LPSTR(     h_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( h_aliases  )
   _XBST_short(     h_addrtype )
   _XBST_short(     h_length   )
   _XBST_POINTER32( h_addr_list) ; pc->GwstBack() ; _XBST_POINTER32( h_addr)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NETENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NETENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NETENT structure.
         Defined as NETENT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-netent</ref-url>
      <size>16</size>
      <members>
         <member type="LPSTR" name="n_name" offset="0" size="4" />
         <member type="POINTER32" name="n_aliases" offset="4" size="4" />
         <member type="SHORT" name="n_addrtype" offset="8" size="2" />
         <member type="DWORD" name="n_net" offset="12" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cName" target="n_name" offset="0" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NETENT )
   _XBST_LPSTR(     n_name     ) ; pc->GwstBack();  pc->Member_DynSz("cName");
   _XBST_POINTER32( n_aliases  )
   _XBST_short(     n_addrtype )
   pc->GwstSetOffset( FIELD_OFFSET( netent , n_net     ) );
   _XBST_DWORD(     n_net      )
   pc->GwstAdjustSize( sizeof(netent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SERVENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SERVENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SERVENT structure.
         Defined as SERVENT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-servent</ref-url>
      <size>16</size>
      <members>
         <member type="LPSTR" name="s_name" offset="0" size="4" />
         <member type="POINTER32" name="s_aliases" offset="4" size="4" />
         <member type="SHORT" name="s_port" offset="8" size="2" />
         <member type="LPSTR" name="s_proto" offset="12" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cName" target="s_name" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cProto" target="s_proto" offset="12" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SERVENT )
   _XBST_LPSTR(     s_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( s_aliases  )
   _XBST_short(     s_port )
   pc->GwstSetOffset( FIELD_OFFSET( servent , s_proto ) );
   _XBST_LPSTR(     s_proto     ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(servent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PROTOENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PROTOENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PROTOENT structure.
         Defined as PROTOENT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-protoent</ref-url>
      <size>12</size>
      <members>
         <member type="LPSTR" name="p_name" offset="0" size="4" />
         <member type="POINTER32" name="p_aliases" offset="4" size="4" />
         <member type="SHORT" name="p_proto" offset="8" size="2" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cName" target="p_name" offset="0" size="4" access="string" />
         <helper type="DYNSZ" name="cProto" target="p_proto" offset="8" size="2" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PROTOENT )
   _XBST_LPSTR(     p_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( p_aliases  )
   _XBST_short(     p_proto    ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(protoent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSADATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSADATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSADATA structure.
         Defined as WSADATA in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata</ref-url>
      <size>400</size>
      <members>
         <member type="WORD" name="wVersion" offset="0" size="2" />
         <member type="WORD" name="wHighVersion" offset="2" size="2" />
         <member type="SZSTR" name="szDescription" offset="4" size="257" access="string" />
         <member type="SZSTR" name="szSystemStatus" offset="261" size="129" access="string" />
         <member type="WORD" name="iMaxSockets" offset="390" size="2" />
         <member type="WORD" name="iMaxUdpDg" offset="392" size="2" />
         <member type="LPSTR" name="lpVendorInfo" offset="396" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSADATA )
   _XBST_WORD(     wVersion )
   _XBST_WORD(     wHighVersion )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , szDescription ) );
   _XBST_SZSTR(    szDescription  , (WSADESCRIPTION_LEN+1) )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , szSystemStatus ) );
   _XBST_SZSTR(    szSystemStatus , (WSASYS_STATUS_LEN+1 ) )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , iMaxSockets ) );
   _XBST_WORD(     iMaxSockets  )
   _XBST_WORD(     iMaxUdpDg    )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , lpVendorInfo ) );
   _XBST_LPSTR(    lpVendorInfo )
   pc->GwstAdjustSize( sizeof(WSADATA) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SOCKPROTO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SOCKPROTO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SOCKPROTO structure.
         Defined as SOCKPROTO in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="WORD" name="sp_family" offset="0" size="2" />
         <member type="WORD" name="sp_protocol" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SOCKPROTO )
   _XBST_WORD(     sp_family   )
   _XBST_WORD(     sp_protocol )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LINGER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LINGER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LINGER structure.
         Defined as LINGER in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="WORD" name="l_onoff" offset="0" size="2" />
         <member type="WORD" name="l_linger" offset="2" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LINGER )
   _XBST_WORD(     l_onoff  )
   _XBST_WORD(     l_linger )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_FLOWSPEC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_FLOWSPEC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi FLOWSPEC structure.
         Defined as FLOWSPEC in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="ULONG" name="TokenRate" offset="0" size="4" />
         <member type="ULONG" name="TokenBucketSize" offset="4" size="4" />
         <member type="ULONG" name="PeakBandwidth" offset="8" size="4" />
         <member type="ULONG" name="Latency" offset="12" size="4" />
         <member type="ULONG" name="DelayVariation" offset="16" size="4" />
         <member type="ULONG" name="ServiceType" offset="20" size="4" />
         <member type="ULONG" name="MaxSduSize" offset="24" size="4" />
         <member type="ULONG" name="MinimumPolicedSize" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( FLOWSPEC )
   _XBST_ULONG( TokenRate          )
   _XBST_ULONG( TokenBucketSize    )
   _XBST_ULONG( PeakBandwidth      )
   _XBST_ULONG( Latency            )
   _XBST_ULONG( DelayVariation     )
   _XBST_ULONG( ServiceType        )
   _XBST_ULONG( MaxSduSize         )
   _XBST_ULONG( MinimumPolicedSize )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_QOS_OBJECT_HDR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_QOS_OBJECT_HDR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi QOS_OBJECT_HDR structure.
         Defined as QOS_OBJECT_HDR in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="ULONG" name="ObjectType" offset="0" size="4" />
         <member type="ULONG" name="ObjectLength" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( QOS_OBJECT_HDR )
   _XBST_ULONG( ObjectType    )
   _XBST_ULONG( ObjectLength  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_QOS_SD_MODE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_QOS_SD_MODE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi QOS_SD_MODE structure.
         Defined as QOS_SD_MODE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_QOS_OBJECT_HDR" name="ObjectHdr" offset="0" size="8" child="true" />
         <member type="ULONG" name="ShapeDiscardMode" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( QOS_SD_MODE )
   _XBST_QOS_OBJECT_HDR( ObjectHdr          )
   _XBST_ULONG(          ShapeDiscardMode   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_QOS_SHAPING_RATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_QOS_SHAPING_RATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi QOS_SHAPING_RATE structure.
         Defined as QOS_SHAPING_RATE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_QOS_OBJECT_HDR" name="ObjectHdr" offset="0" size="8" child="true" />
         <member type="ULONG" name="ShapingRate" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( QOS_SHAPING_RATE )
   _XBST_QOS_OBJECT_HDR  ( ObjectHdr   )
   _XBST_ULONG           ( ShapingRate )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_QOS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_QOS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi QOS structure.
         Defined as QOS in ot4xb_wapist_map.ch.
      </description>
      <size>72</size>
      <members>
         <member type="WAPIST_FLOWSPEC" name="SendingFlowspec" offset="0" size="32" child="true" />
         <member type="WAPIST_FLOWSPEC" name="ReceivingFlowspec" offset="32" size="32" child="true" />
         <member type="WAPIST_WSABUF" name="ProviderSpecific" offset="64" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( QOS )
   _XBST_FLOWSPEC ( SendingFlowspec   )
   _XBST_FLOWSPEC ( ReceivingFlowspec )
   _XBST_WSABUF   ( ProviderSpecific  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSANETWORKEVENTS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSANETWORKEVENTS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSANETWORKEVENTS structure.
         Defined as WSANETWORKEVENTS in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LONG" name="lNetworkEvents" offset="0" size="4" />
         <member type="BINSTR" name="iErrorCode" offset="4" size="40" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSANETWORKEVENTS )
   _XBST_LONG(   lNetworkEvents )
   _XBST_BINSTR( iErrorCode, (FD_MAX_EVENTS * sizeof(int)) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAPROTOCOLCHAIN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAPROTOCOLCHAIN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAPROTOCOLCHAIN structure.
         Defined as WSAPROTOCOLCHAIN in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="INT" name="ChainLen" offset="0" size="4" />
         <member type="BINSTR" name="ChainEntries" offset="4" size="28" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAPROTOCOLCHAIN )
   _XBST_int(    ChainLen )
   _XBST_BINSTR( ChainEntries , (MAX_PROTOCOL_CHAIN * sizeof(DWORD) ) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAPROTOCOL_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAPROTOCOL_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAPROTOCOL_INFO structure.
         Defined as WSAPROTOCOL_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>88</size>
      <members>
         <member type="DWORD" name="dwServiceFlags1" offset="0" size="4" />
         <member type="DWORD" name="dwServiceFlags2" offset="4" size="4" />
         <member type="DWORD" name="dwServiceFlags3" offset="8" size="4" />
         <member type="DWORD" name="dwServiceFlags4" offset="12" size="4" />
         <member type="DWORD" name="dwProviderFlags" offset="16" size="4" />
         <member type="WAPIST_GUID" name="ProviderId" offset="20" size="16" child="true" />
         <member type="DWORD" name="dwCatalogEntryId" offset="36" size="4" />
         <member type="WAPIST_WSAPROTOCOLCHAIN" name="ProtocolChain" offset="40" size="4" child="true" />
         <member type="INT" name="iVersion" offset="44" size="4" />
         <member type="INT" name="iAddressFamily" offset="48" size="4" />
         <member type="INT" name="iMaxSockAddr" offset="52" size="4" />
         <member type="INT" name="iMinSockAddr" offset="56" size="4" />
         <member type="INT" name="iSocketType" offset="60" size="4" />
         <member type="INT" name="iProtocol" offset="64" size="4" />
         <member type="INT" name="iProtocolMaxOffset" offset="68" size="4" />
         <member type="INT" name="iNetworkByteOrder" offset="72" size="4" />
         <member type="INT" name="iSecurityScheme" offset="76" size="4" />
         <member type="DWORD" name="dwMessageSize" offset="80" size="4" />
         <member type="DWORD" name="dwProviderReserved" offset="84" size="4" />
         <member type="BINSTR" name="szProtocol" offset="324" size="256" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAPROTOCOL_INFO )
   _XBST_DWORD            ( dwServiceFlags1                  )
   _XBST_DWORD            ( dwServiceFlags2                  )
   _XBST_DWORD            ( dwServiceFlags3                  )
   _XBST_DWORD            ( dwServiceFlags4                  )
   _XBST_DWORD            ( dwProviderFlags                  )
   _XBST_GUID             ( ProviderId                       )
   _XBST_DWORD            ( dwCatalogEntryId                 )
   _XBST_WSAPROTOCOLCHAIN ( ProtocolChain                    )
   _XBST_int              ( iVersion                         )
   _XBST_int              ( iAddressFamily                   )
   _XBST_int              ( iMaxSockAddr                     )
   _XBST_int              ( iMinSockAddr                     )
   _XBST_int              ( iSocketType                      )
   _XBST_int              ( iProtocol                        )
   _XBST_int              ( iProtocolMaxOffset               )
   _XBST_int              ( iNetworkByteOrder                )
   _XBST_int              ( iSecurityScheme                  )
   _XBST_DWORD            ( dwMessageSize                    )
   _XBST_DWORD            ( dwProviderReserved               )
   _XBST_BINSTR           ( szProtocol , (WSAPROTOCOL_LEN+1) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACOMPLETION_NS_WINDOWMESSAGE structure.
         Defined as WSACOMPLETION_NS_WINDOWMESSAGE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HWND" name="hWnd" offset="0" size="4" />
         <member type="UINT" name="uMsg" offset="4" size="4" />
         <member type="WPARAM" name="context" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_WINDOWMESSAGE )
   _XBST_HWND   ( hWnd    )
   _XBST_UINT   ( uMsg    )
   _XBST_WPARAM ( context )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION_NS_EVENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION_NS_EVENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACOMPLETION_NS_EVENT structure.
         Defined as WSACOMPLETION_NS_EVENT in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="POINTER32" name="lpOverlapped" offset="0" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_EVENT )
   _XBST_POINTER32 ( lpOverlapped )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION_NS_APC</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION_NS_APC</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACOMPLETION_NS_APC structure.
         Defined as WSACOMPLETION_NS_APC in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="POINTER32" name="lpOverlapped" offset="0" size="4" />
         <member type="POINTER32" name="lpfnCompletionProc" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_APC )
   _XBST_POINTER32 ( lpOverlapped          )
   _XBST_POINTER32 ( lpfnCompletionProc    )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION_NS_PORT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION_NS_PORT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACOMPLETION_NS_PORT structure.
         Defined as WSACOMPLETION_NS_PORT in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="POINTER32" name="lpOverlapped" offset="0" size="4" />
         <member type="HANDLE" name="hPort" offset="4" size="4" />
         <member type="POINTER32" name="Key" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PORT )
   _XBST_POINTER32 ( lpOverlapped )
   _XBST_HANDLE    ( hPort        )
   _XBST_POINTER32 ( Key          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION_NS_PARAMETERS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION_NS_PARAMETERS</source>
      <category>winapi/structures</category>
      <description>Auxiliary wrapper for the WSACOMPLETION namespace-provider parameter union.</description>
      <members>
         <union name="Parameters">
            <member type="WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE" name="WindowMessage" child="true" />
            <member type="WAPIST_WSACOMPLETION_NS_EVENT" name="Event" child="true" />
            <member type="WAPIST_WSACOMPLETION_NS_APC" name="Apc" child="true" />
            <member type="WAPIST_WSACOMPLETION_NS_PORT" name="Port" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PARAMETERS )
  pc->GwstBeginUnion();
   _XBST_WSACOMPLETION_NS_WINDOWMESSAGE( WindowMessage )
   _XBST_WSACOMPLETION_NS_EVENT(         Event         )
   _XBST_WSACOMPLETION_NS_APC(           Apc           )
   _XBST_WSACOMPLETION_NS_PORT(          Port          )
  pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSACOMPLETION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSACOMPLETION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSACOMPLETION structure.
         Defined as WSACOMPLETION in ot4xb_wapist_map.ch.
      </description>
      <size>4</size>
      <members>
         <member type="LONG" name="Type" offset="0" size="4" />
         <member type="WAPIST_WSACOMPLETION_NS_PARAMETERS" name="Parameters" offset="4" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSACOMPLETION )
   _XBST_LONG( Type )
   _XBST_WSACOMPLETION_NS_PARAMETERS( Parameters )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BLOB</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BLOB</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BLOB structure.
         Defined as BLOB in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="ULONG" name="cbSize" offset="0" size="4" />
         <member type="LPBYTE" name="pBlobData" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( BLOB )
   _XBST_ULONG(  cbSize )
   _XBST_LPBYTE( pBlobData )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_AFPROTOCOLS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_AFPROTOCOLS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi AFPROTOCOLS structure.
         Defined as AFPROTOCOLS in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="INT" name="iAddressFamily" offset="0" size="4" />
         <member type="INT" name="iProtocol" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( AFPROTOCOLS )
   _XBST_INT( iAddressFamily )
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAVERSION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAVERSION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAVERSION structure.
         Defined as WSAVERSION in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwVersion" offset="0" size="4" />
         <member type="LONG" name="ecHow" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAVERSION )
   _XBST_DWORD  ( dwVersion )
   _XBST_LONG   ( ecHow     )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAQUERYSET</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAQUERYSET</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAQUERYSET structure.
         Defined as WSAQUERYSET in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="LPSTR" name="lpszServiceInstanceName" offset="4" size="4" />
         <member type="POINTER32" name="lpServiceClassId" offset="8" size="4" />
         <member type="POINTER32" name="lpVersion" offset="12" size="4" />
         <member type="LPSTR" name="lpszComment" offset="16" size="4" />
         <member type="DWORD" name="dwNameSpace" offset="20" size="4" />
         <member type="POINTER32" name="lpNSProviderId" offset="24" size="4" />
         <member type="LPSTR" name="lpszContext" offset="28" size="4" />
         <member type="DWORD" name="dwNumberOfProtocols" offset="32" size="4" />
         <member type="POINTER32" name="lpafpProtocols" offset="36" size="4" />
         <member type="LPSTR" name="lpszQueryString" offset="40" size="4" />
         <member type="DWORD" name="dwNumberOfCsAddrs" offset="44" size="4" />
         <member type="POINTER32" name="lpcsaBuffer" offset="48" size="4" />
         <member type="DWORD" name="dwOutputFlags" offset="52" size="4" />
         <member type="POINTER32" name="lpBlob" offset="56" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAQUERYSET )
   _XBST_DWORD     ( dwSize                     )
   _XBST_LPSTR     ( lpszServiceInstanceName    )
   _XBST_POINTER32 ( lpServiceClassId           )
   _XBST_POINTER32 ( lpVersion                  )
   _XBST_LPSTR     ( lpszComment                )
   _XBST_DWORD     ( dwNameSpace                )
   _XBST_POINTER32 ( lpNSProviderId             )
   _XBST_LPSTR     ( lpszContext                )
   _XBST_DWORD     ( dwNumberOfProtocols        )
   _XBST_POINTER32 ( lpafpProtocols             )
   _XBST_LPSTR     ( lpszQueryString            )
   _XBST_DWORD     ( dwNumberOfCsAddrs          )
   _XBST_POINTER32 ( lpcsaBuffer                )
   _XBST_DWORD     ( dwOutputFlags              )
   _XBST_POINTER32 ( lpBlob                     )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAQUERYSET2</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAQUERYSET2</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAQUERYSET2 structure.
         Defined as WSAQUERYSET2 in ot4xb_wapist_map.ch.
      </description>
      <size>56</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="LPSTR" name="lpszServiceInstanceName" offset="4" size="4" />
         <member type="POINTER32" name="lpVersion" offset="8" size="4" />
         <member type="LPSTR" name="lpszComment" offset="12" size="4" />
         <member type="DWORD" name="dwNameSpace" offset="16" size="4" />
         <member type="POINTER32" name="lpNSProviderId" offset="20" size="4" />
         <member type="LPSTR" name="lpszContext" offset="24" size="4" />
         <member type="DWORD" name="dwNumberOfProtocols" offset="28" size="4" />
         <member type="POINTER32" name="lpafpProtocols" offset="32" size="4" />
         <member type="LPSTR" name="lpszQueryString" offset="36" size="4" />
         <member type="DWORD" name="dwNumberOfCsAddrs" offset="40" size="4" />
         <member type="POINTER32" name="lpcsaBuffer" offset="44" size="4" />
         <member type="DWORD" name="dwOutputFlags" offset="48" size="4" />
         <member type="POINTER32" name="lpBlob" offset="52" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAQUERYSET2 )
   _XBST_DWORD        ( dwSize                   )
   _XBST_LPSTR        ( lpszServiceInstanceName  )
   _XBST_POINTER32    ( lpVersion                )
   _XBST_LPSTR        ( lpszComment              )
   _XBST_DWORD        ( dwNameSpace              )
   _XBST_POINTER32    ( lpNSProviderId           )
   _XBST_LPSTR        ( lpszContext              )
   _XBST_DWORD        ( dwNumberOfProtocols      )
   _XBST_POINTER32    ( lpafpProtocols           )
   _XBST_LPSTR        ( lpszQueryString          )
   _XBST_DWORD        ( dwNumberOfCsAddrs        )
   _XBST_POINTER32    ( lpcsaBuffer              )
   _XBST_DWORD        ( dwOutputFlags            )
   _XBST_POINTER32    ( lpBlob                   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSANSCLASSINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSANSCLASSINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSANSCLASSINFO structure.
         Defined as WSANSCLASSINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="LPSTR" name="lpszName" offset="0" size="4" />
         <member type="DWORD" name="dwNameSpace" offset="4" size="4" />
         <member type="DWORD" name="dwValueType" offset="8" size="4" />
         <member type="DWORD" name="dwValueSize" offset="12" size="4" />
         <member type="POINTER32" name="lpValue" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSANSCLASSINFO )
   _XBST_LPSTR     ( lpszName     )
   _XBST_DWORD     ( dwNameSpace  )
   _XBST_DWORD     ( dwValueType  )
   _XBST_DWORD     ( dwValueSize  )
   _XBST_POINTER32 ( lpValue      )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSASERVICECLASSINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSASERVICECLASSINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSASERVICECLASSINFO structure.
         Defined as WSASERVICECLASSINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="POINTER32" name="lpServiceClassId" offset="0" size="4" />
         <member type="LPSTR" name="lpszServiceClassName" offset="4" size="4" />
         <member type="DWORD" name="dwCount" offset="8" size="4" />
         <member type="POINTER32" name="lpClassInfos" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSASERVICECLASSINFO )
   _XBST_POINTER32   ( lpServiceClassId      )
   _XBST_LPSTR       ( lpszServiceClassName  )
   _XBST_DWORD       ( dwCount               )
    _XBST_POINTER32  ( lpClassInfos          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSANAMESPACE_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSANAMESPACE_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSANAMESPACE_INFO structure.
         Defined as WSANAMESPACE_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_GUID" name="NSProviderId" offset="0" size="16" child="true" />
         <member type="DWORD" name="dwNameSpace" offset="16" size="4" />
         <member type="BOOL" name="fActive" offset="20" size="4" />
         <member type="DWORD" name="dwVersion" offset="24" size="4" />
         <member type="LPSTR" name="lpszIdentifier" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFO )
   _XBST_GUID      ( NSProviderId     )
   _XBST_DWORD     ( dwNameSpace      )
   _XBST_BOOL      ( fActive          )
   _XBST_DWORD     ( dwVersion        )
   _XBST_LPSTR     ( lpszIdentifier   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSANAMESPACE_INFOEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSANAMESPACE_INFOEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSANAMESPACE_INFOEX structure.
         Defined as WSANAMESPACE_INFOEX in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="WAPIST_GUID" name="NSProviderId" offset="0" size="16" child="true" />
         <member type="DWORD" name="dwNameSpace" offset="16" size="4" />
         <member type="BOOL" name="fActive" offset="20" size="4" />
         <member type="DWORD" name="dwVersion" offset="24" size="4" />
         <member type="LPSTR" name="lpszIdentifier" offset="28" size="4" />
         <member type="WAPIST_BLOB" name="ProviderSpecific" offset="32" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFOEX )
   _XBST_GUID   (  NSProviderId     )
   _XBST_DWORD  (  dwNameSpace      )
   _XBST_BOOL   (  fActive          )
   _XBST_DWORD  (  dwVersion        )
   _XBST_LPSTR  (  lpszIdentifier   )
   _XBST_BLOB   (  ProviderSpecific )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WSAPOLLFD</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WSAPOLLFD</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WSAPOLLFD structure.
         Defined as WSAPOLLFD in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="SOCKET" name="fd" offset="0" size="4" />
         <member type="SHORT" name="events" offset="4" size="2" />
         <member type="SHORT" name="revents" offset="6" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WSAPOLLFD )
   _XBST_SOCKET ( fd      )
   _XBST_SHORT  ( events  )
   _XBST_SHORT  ( revents )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_ADDRINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_ADDRINFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinSock ADDRINFOA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa</ref-url>
      <size>32</size>
      <members>
         <member type="INT" name="ai_flags" offset="0" size="4" />
         <member type="INT" name="ai_family" offset="4" size="4" />
         <member type="INT" name="ai_socktype" offset="8" size="4" />
         <member type="INT" name="ai_protocol" offset="12" size="4" />
         <member type="INT" name="ai_addrlen" offset="16" size="4" />
         <member type="LPSTR" name="ai_canonname" offset="20" size="4" />
         <member type="POINTER32" name="ai_addr" offset="24" size="4" />
         <member type="POINTER32" name="ai_next" offset="28" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cCanonName" target="ai_canonname" offset="20" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( ADDRINFO )
   _XBST_int   ( ai_flags       )
   _XBST_int   ( ai_family      )
   _XBST_int   ( ai_socktype    )
   _XBST_int   ( ai_protocol    )
   _XBST_int   ( ai_addrlen     )
   _XBST_LPSTR(  ai_canonname   )   pc->GwstBack() ; _XBST_DYNSZ ( cCanonName  )
   _XBST_POINTER32( ai_addr     )
   _XBST_POINTER32( ai_next     )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OPENFILENAME</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OPENFILENAME</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi OPENFILENAMEA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea</ref-url>
      <members>
         <member type="DWORD" name="lStructSize" />
         <member type="HWND" name="hwndOwner" />
         <member type="HINSTANCE" name="hInstance" />
         <member type="LPSTR" name="lpstrFilter" />
         <member type="LPSTR" name="lpstrCustomFilter" />
         <member type="DWORD" name="nMaxCustFilter" />
         <member type="DWORD" name="nFilterIndex" />
         <member type="LPSTR" name="lpstrFile" />
         <member type="DWORD" name="nMaxFile" />
         <member type="LPSTR" name="lpstrFileTitle" />
         <member type="DWORD" name="nMaxFileTitle" />
         <member type="LPSTR" name="lpstrInitialDir" />
         <member type="LPSTR" name="lpstrTitle" />
         <member type="DWORD" name="Flags" />
         <member type="WORD" name="nFileOffset" />
         <member type="WORD" name="nFileExtension" />
         <member type="LPSTR" name="lpstrDefExt" />
         <member type="LPARAM" name="lCustData" />
         <member type="POINTER32" name="lpfnHook" />
         <member type="LPSTR" name="lpTemplateName" />
         <member type="POINTER32" name="pvReserved" />
         <member type="DWORD" name="dwReserved" />
         <member type="DWORD" name="FlagsEx" />
      </members>
      <properties>
         <property type="numeric" name="_size_400_" scope="class" readonly="true" />
         <property type="numeric" name="_size_500_" scope="class" readonly="true" />
      </properties>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( OPENFILENAME )
   _XBST_DWORD       (   lStructSize       )
   _XBST_HWND        (   hwndOwner         )
   _XBST_HINSTANCE   (   hInstance         )
   _XBST_LPSTR       (   lpstrFilter       )
   _XBST_LPSTR       (   lpstrCustomFilter )
   _XBST_DWORD       (   nMaxCustFilter    )
   _XBST_DWORD       (   nFilterIndex      )
   _XBST_LPSTR       (   lpstrFile         )
   _XBST_DWORD       (   nMaxFile          )
   _XBST_LPSTR       (   lpstrFileTitle    )
   _XBST_DWORD       (   nMaxFileTitle     )
   _XBST_LPSTR       (   lpstrInitialDir   )
   _XBST_LPSTR       (   lpstrTitle        )
   _XBST_DWORD       (   Flags             )
   _XBST_WORD        (   nFileOffset       )
   _XBST_WORD        (   nFileExtension    )
   _XBST_LPSTR       (   lpstrDefExt       )
   _XBST_LPARAM      (   lCustData         )
   _XBST_POINTER32   (   lpfnHook          )
   _XBST_LPSTR       (   lpTemplateName    )
   _XBST_POINTER32   (   pvReserved        )
   _XBST_DWORD       (   dwReserved        )
   _XBST_DWORD       (   FlagsEx           )
   wsprintf(pc->m_szPrintfBuffer,"{|s| %i }",OPENFILENAME_SIZE_VERSION_400 );
   pc->ROClassPropertyCB("_size_400_",pc->m_szPrintfBuffer);
   wsprintf(pc->m_szPrintfBuffer,"{|s| %i }",sizeof( OPENFILENAME) );
   pc->ROClassPropertyCB("_size_500_", pc->m_szPrintfBuffer );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// HID
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWHID</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWHID</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWHID structure.
         Defined as RAWHID in ot4xb_wapist_map.ch.
      </description>
      <size>9</size>
      <members>
         <member type="DWORD" name="dwSizeHid" offset="0" size="4" />
         <member type="DWORD" name="dwCount" offset="4" size="4" />
         <member type="BYTE" name="bRawData" offset="8" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWHID )
   _XBST_DWORD ( dwSizeHid  )
   _XBST_DWORD ( dwCount    )
   _XBST_BYTE  ( bRawData   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWINPUT_DATA_UNION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWINPUT_DATA_UNION</source>
      <category>winapi/structures</category>
      <description>Auxiliary wrapper for the RAWINPUT data union.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinput</ref-url>
      <members>
         <union name="data">
            <member type="WAPIST_RAWMOUSE" name="mouse" child="true" />
            <member type="WAPIST_RAWKEYBOARD" name="keyboard" child="true" />
            <member type="WAPIST_RAWHID" name="hid" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWINPUT_DATA_UNION )
  pc->GwstBeginUnion();
   _XBST_RAWMOUSE    ( mouse     )
   _XBST_RAWKEYBOARD ( keyboard  )
   _XBST_RAWHID      ( hid       )
  pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWINPUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWINPUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWINPUT structure.
         Defined as RAWINPUT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_RAWINPUTHEADER" name="header" offset="0" size="16" child="true" />
         <member type="WAPIST_RAWINPUT_DATA_UNION" name="data" offset="16" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWINPUT )
   _XBST_RAWINPUTHEADER( header )
   _XBST_RAWINPUT_DATA_UNION( data )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWINPUTDEVICE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWINPUTDEVICE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWINPUTDEVICE structure.
         Defined as RAWINPUTDEVICE in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="USHORT" name="usUsagePage" offset="0" size="2" />
         <member type="USHORT" name="usUsage" offset="2" size="2" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
         <member type="HWND" name="hwndTarget" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWINPUTDEVICE)
   _XBST_USHORT ( usUsagePage  )
   _XBST_USHORT ( usUsage      )
   _XBST_DWORD  ( dwFlags      )
   _XBST_HWND   ( hwndTarget   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWINPUTDEVICELIST</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWINPUTDEVICELIST</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWINPUTDEVICELIST structure.
         Defined as RAWINPUTDEVICELIST in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="HANDLE" name="hDevice" offset="0" size="4" />
         <member type="DWORD" name="dwType" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWINPUTDEVICELIST )
   _XBST_HANDLE ( hDevice )
   _XBST_DWORD  ( dwType  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWINPUTHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWINPUTHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWINPUTHEADER structure.
         Defined as RAWINPUTHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwType" offset="0" size="4" />
         <member type="DWORD" name="dwSize" offset="4" size="4" />
         <member type="HANDLE" name="hDevice" offset="8" size="4" />
         <member type="WPARAM" name="wParam" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWINPUTHEADER )
   _XBST_DWORD  ( dwType  )
   _XBST_DWORD  ( dwSize  )
   _XBST_HANDLE ( hDevice )
   _XBST_WPARAM ( wParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWKEYBOARD</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWKEYBOARD</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RAWKEYBOARD structure.
         Defined as RAWKEYBOARD in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="USHORT" name="MakeCode" offset="0" size="2" />
         <member type="USHORT" name="Flags" offset="2" size="2" />
         <member type="USHORT" name="Reserved" offset="4" size="2" />
         <member type="USHORT" name="VKey" offset="6" size="2" />
         <member type="UINT" name="Message" offset="8" size="4" />
         <member type="ULONG" name="ExtraInformation" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWKEYBOARD )
   _XBST_USHORT ( MakeCode         )
   _XBST_USHORT ( Flags            )
   _XBST_USHORT ( Reserved         )
   _XBST_USHORT ( VKey             )
   _XBST_UINT   ( Message          )
   _XBST_ULONG  ( ExtraInformation )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RAWMOUSE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RAWMOUSE</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi RAWMOUSE structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse</ref-url>
      <members>
         <member type="USHORT" name="usFlags" />
         <union name="buttons">
            <member type="ULONG" name="ulButtons" />
            <struct>
               <member type="USHORT" name="usButtonFlags" />
               <member type="USHORT" name="usButtonData" />
            </struct>
         </union>
         <member type="ULONG" name="ulRawButtons" />
         <member type="LONG" name="lLastX" />
         <member type="LONG" name="lLastY" />
         <member type="ULONG" name="ulExtraInformation" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RAWMOUSE )
   _XBST_USHORT    ( usFlags )
   // union
   _XBST_ULONG    ( ulButtons )
   pc->GwstSetOffset(2);
   _XBST_USHORT ( usButtonFlags )
   _XBST_USHORT ( usButtonData  )
   // ---
   _XBST_ULONG  ( ulRawButtons       )
   _XBST_LONG   ( lLastX             )
   _XBST_LONG   ( lLastY             )
   _XBST_ULONG  ( ulExtraInformation )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RID_DEVICE_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RID_DEVICE_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi RID_DEVICE_INFO structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rid_device_info</ref-url>
      <members>
         <member type="DWORD" name="cbSize" />
         <member type="DWORD" name="dwType" />
         <union name="device">
            <member type="WAPIST_RID_DEVICE_INFO_MOUSE" name="mouse" child="true" />
            <member type="WAPIST_RID_DEVICE_INFO_KEYBOARD" name="keyboard" child="true" />
            <member type="WAPIST_RID_DEVICE_INFO_HID" name="hid" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO )
   _XBST_DWORD    ( cbSize  )
   _XBST_DWORD    ( dwType  )
  pc->GwstBeginUnion();
   _XBST_RID_DEVICE_INFO_MOUSE     ( mouse     )
   _XBST_RID_DEVICE_INFO_KEYBOARD  ( keyboard  )
   _XBST_RID_DEVICE_INFO_HID       ( hid       )
  pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RID_DEVICE_INFO_HID</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RID_DEVICE_INFO_HID</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RID_DEVICE_INFO_HID structure.
         Defined as RID_DEVICE_INFO_HID in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwVendorId" offset="0" size="4" />
         <member type="DWORD" name="dwProductId" offset="4" size="4" />
         <member type="DWORD" name="dwVersionNumber" offset="8" size="4" />
         <member type="USHORT" name="usUsagePage" offset="12" size="2" />
         <member type="USHORT" name="usUsage" offset="14" size="2" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_HID )
   _XBST_DWORD   ( dwVendorId       )
   _XBST_DWORD   ( dwProductId      )
   _XBST_DWORD   ( dwVersionNumber  )
   _XBST_USHORT  ( usUsagePage      )
   _XBST_USHORT  ( usUsage          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RID_DEVICE_INFO_KEYBOARD</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RID_DEVICE_INFO_KEYBOARD</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RID_DEVICE_INFO_KEYBOARD structure.
         Defined as RID_DEVICE_INFO_KEYBOARD in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="DWORD" name="dwType" offset="0" size="4" />
         <member type="DWORD" name="dwSubType" offset="4" size="4" />
         <member type="DWORD" name="dwKeyboardMode" offset="8" size="4" />
         <member type="DWORD" name="dwNumberOfFunctionKeys" offset="12" size="4" />
         <member type="DWORD" name="dwNumberOfIndicators" offset="16" size="4" />
         <member type="DWORD" name="dwNumberOfKeysTotal" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_KEYBOARD )
   _XBST_DWORD ( dwType                 )
   _XBST_DWORD ( dwSubType              )
   _XBST_DWORD ( dwKeyboardMode         )
   _XBST_DWORD ( dwNumberOfFunctionKeys )
   _XBST_DWORD ( dwNumberOfIndicators   )
   _XBST_DWORD ( dwNumberOfKeysTotal    )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_RID_DEVICE_INFO_MOUSE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_RID_DEVICE_INFO_MOUSE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi RID_DEVICE_INFO_MOUSE structure.
         Defined as RID_DEVICE_INFO_MOUSE in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwId" offset="0" size="4" />
         <member type="DWORD" name="dwNumberOfButtons" offset="4" size="4" />
         <member type="DWORD" name="dwSampleRate" offset="8" size="4" />
         <member type="BOOL" name="fHasHorizontalWheel" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_MOUSE )
   _XBST_DWORD ( dwId                )
   _XBST_DWORD ( dwNumberOfButtons   )
   _XBST_DWORD ( dwSampleRate        )
   _XBST_BOOL  ( fHasHorizontalWheel )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// IPHLPR
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IP_ADDR_STRING</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IP_ADDR_STRING</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IP_ADDR_STRING structure.
         Defined as IP_ADDR_STRING in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="POINTER32" name="_Next" offset="0" size="4" />
         <member type="BINSTR" name="IpAddress" offset="4" size="16" />
         <member type="BINSTR" name="IpMask" offset="20" size="16" />
         <member type="DWORD" name="Context" offset="36" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IP_ADDR_STRING )
   _XBST_POINTER32    ( _Next )
   _XBST_BINSTR       ( IpAddress , 16 )
   _XBST_BINSTR       ( IpMask    , 16 )
   _XBST_DWORD        ( Context )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IP_ADAPTER_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IP_ADAPTER_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IP_ADAPTER_INFO structure.
         Defined as IP_ADAPTER_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>640</size>
      <members>
         <member type="POINTER32" name="_Next" offset="0" size="4" />
         <member type="DWORD" name="ComboIndex" offset="4" size="4" />
         <member type="SZSTR" name="AdapterName" offset="8" size="260" access="string" />
         <member type="SZSTR" name="Description" offset="268" size="132" access="string" />
         <member type="UINT" name="AddressLength" offset="400" size="4" />
         <member type="BINSTR" name="Address" offset="404" size="8" />
         <member type="DWORD" name="Index" offset="412" size="4" />
         <member type="UINT" name="Type" offset="416" size="4" />
         <member type="BOOL" name="DhcpEnabled" offset="420" size="4" />
         <member type="POINTER32" name="CurrentIpAddress" offset="424" size="4" />
         <member type="WAPIST_IP_ADDR_STRING" name="IpAddressList" offset="428" size="40" child="true" />
         <member type="WAPIST_IP_ADDR_STRING" name="GatewayList" offset="468" size="40" child="true" />
         <member type="WAPIST_IP_ADDR_STRING" name="DhcpServer" offset="508" size="40" child="true" />
         <member type="BOOL" name="HaveWins" offset="548" size="4" />
         <member type="WAPIST_IP_ADDR_STRING" name="PrimaryWinsServer" offset="552" size="40" child="true" />
         <member type="WAPIST_IP_ADDR_STRING" name="SecondaryWinsServer" offset="592" size="40" child="true" />
         <member type="DWORD" name="LeaseObtained" offset="632" size="4" />
         <member type="DWORD" name="LeaseExpires" offset="636" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IP_ADAPTER_INFO )
   _XBST_POINTER32           ( _Next                 )
   _XBST_DWORD               ( ComboIndex            )
   _XBST_SZSTR               ( AdapterName , 260     )
   _XBST_SZSTR               ( Description , 132     )
   _XBST_UINT                ( AddressLength         )
   _XBST_BINSTR              ( Address ,  8          )
   _XBST_DWORD               ( Index                 )
   _XBST_UINT                ( Type                  )
   _XBST_BOOL                ( DhcpEnabled           )
   _XBST_POINTER32           ( CurrentIpAddress      )
   _XBST_IP_ADDR_STRING      ( IpAddressList         )
   _XBST_IP_ADDR_STRING      ( GatewayList           )
   _XBST_IP_ADDR_STRING      ( DhcpServer            )
   _XBST_BOOL                ( HaveWins              )
   _XBST_IP_ADDR_STRING      ( PrimaryWinsServer     )
   _XBST_IP_ADDR_STRING      ( SecondaryWinsServer   )
   _XBST_DWORD               ( LeaseObtained         )
   _XBST_DWORD               ( LeaseExpires          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_IP_PER_ADAPTER_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_IP_PER_ADAPTER_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi IP_PER_ADAPTER_INFO structure.
         Defined as IP_PER_ADAPTER_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>52</size>
      <members>
         <member type="UINT" name="AutoconfigEnabled" offset="0" size="4" />
         <member type="UINT" name="AutoconfigActive" offset="4" size="4" />
         <member type="POINTER32" name="CurrentDnsServer" offset="8" size="4" />
         <member type="WAPIST_IP_ADDR_STRING" name="DnsServerList" offset="12" size="40" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( IP_PER_ADAPTER_INFO )
   _XBST_UINT             ( AutoconfigEnabled  )
   _XBST_UINT             ( AutoconfigActive   )
   _XBST_POINTER32        ( CurrentDnsServer   )
   _XBST_IP_ADDR_STRING   ( DnsServerList      )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OVERLAPPED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OVERLAPPED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi OVERLAPPED structure.
         Defined as OVERLAPPED in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-overlapped</ref-url>
      <size>20</size>
      <members>
         <member type="ULONG_PTR" name="Internal" offset="0" size="4" />
         <member type="ULONG_PTR" name="InternalHigh" offset="4" size="4" />
         <union offset="8" size="8">
            <struct offset="8" size="8" anonymous="true">
               <member type="DWORD" name="Offset" offset="8" size="4" />
               <member type="DWORD" name="OffsetHigh" offset="12" size="4" />
            </struct>
            <member type="PVOID" name="Pointer" offset="8" size="4" />
         </union>
         <member type="HANDLE" name="hEvent" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( OVERLAPPED )
   _XBST_ULONG_PTR ( Internal      )
   _XBST_ULONG_PTR ( InternalHigh  )
   _XBST_DWORD     ( Offset        )
   _XBST_DWORD     ( OffsetHigh    )
   pc->GwstSetOffset( 8  );
   _XBST_PVOID( Pointer       )
   pc->GwstSetOffset(16  );
   _XBST_HANDLE    ( hEvent        )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SYSTEM_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SYSTEM_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SYSTEM_INFO structure.
         Defined as SYSTEM_INFO in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info</ref-url>
      <size>36</size>
      <members>
         <union name="DUMMYUNIONNAME" offset="0" size="4">
            <member type="DWORD" name="dwOemId" offset="0" size="4" />
            <struct name="DUMMYSTRUCTNAME" offset="0" size="4" anonymous="true">
               <member type="WORD" name="wProcessorArchitecture" offset="0" size="2" />
               <member type="WORD" name="wReserved" offset="2" size="2" />
            </struct>
         </union>
         <member type="DWORD" name="dwPageSize" offset="4" size="4" />
         <member type="LPVOID" name="lpMinimumApplicationAddress" offset="8" size="4" />
         <member type="LPVOID" name="lpMaximumApplicationAddress" offset="12" size="4" />
         <member type="DWORD" name="dwActiveProcessorMask" offset="16" size="4" />
         <member type="DWORD" name="dwNumberOfProcessors" offset="20" size="4" />
         <member type="DWORD" name="dwProcessorType" offset="24" size="4" />
         <member type="DWORD" name="dwAllocationGranularity" offset="28" size="4" />
         <member type="WORD" name="wProcessorLevel" offset="32" size="2" />
         <member type="WORD" name="wProcessorRevision" offset="34" size="2" />
      </members>
      <remarks>
         The structure is automatically initialized with the current system information when instantiated.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SYSTEM_INFO )
   _XBST_DWORD( dwOemId )
   pc->GwstSetOffset( 0 );
   _XBST_WORD    ( wProcessorArchitecture      )
   _XBST_WORD    ( wReserved                   )
   _XBST_DWORD   ( dwPageSize                  )
   _XBST_LPVOID  ( lpMinimumApplicationAddress )
   _XBST_LPVOID  ( lpMaximumApplicationAddress )
   _XBST_DWORD   ( dwActiveProcessorMask       )
   _XBST_DWORD   ( dwNumberOfProcessors        )
   _XBST_DWORD   ( dwProcessorType             )
   _XBST_DWORD   ( dwAllocationGranularity     )
   _XBST_WORD    ( wProcessorLevel             )
   _XBST_WORD    ( wProcessorRevision          )
   pc->GwstSetOffset(sizeof( SYSTEM_INFO)  );
   DWORD dwfp = (DWORD) GetProcAddress(GetModuleHandle("kernel32"), "GetNativeSystemInfo" );
   if(! dwfp) {dwfp = (DWORD) GetProcAddress(GetModuleHandle("kernel32"), "GetSystemInfo" );}
   pc->Method_cbbs( "init", "{|s,p1,p2| s:_gwst_(p1,p2),nFpCall(%i,s),s }" , dwfp );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// WINNT STRUCTRURES
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OSVERSIONINFOEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OSVERSIONINFOEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi OSVERSIONINFOEXA structure.
         Defined as OSVERSIONINFOEX in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoexa</ref-url>
      <size>156</size>
      <members>
         <member type="DWORD" name="dwOSVersionInfoSize" offset="0" size="4" />
         <member type="DWORD" name="dwMajorVersion" offset="4" size="4" />
         <member type="DWORD" name="dwMinorVersion" offset="8" size="4" />
         <member type="DWORD" name="dwBuildNumber" offset="12" size="4" />
         <member type="DWORD" name="dwPlatformId" offset="16" size="4" />
         <member type="SZSTR" name="szCSDVersion" offset="20" size="128" access="string" />
         <member type="WORD" name="wServicePackMajor" offset="148" size="2" />
         <member type="WORD" name="wServicePackMinor" offset="150" size="2" />
         <member type="WORD" name="wSuiteMask" offset="152" size="2" />
         <member type="BYTE" name="wProductType" offset="154" size="1" />
         <member type="BYTE" name="wReserved" offset="155" size="1" />
      </members>
      <remarks>
         The structure is automatically initialized with the current operating system version information when instantiated.
      </remarks>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( OSVERSIONINFOEX )
   _XBST_DWORD ( dwOSVersionInfoSize )
   _XBST_DWORD ( dwMajorVersion )
   _XBST_DWORD ( dwMinorVersion )
   _XBST_DWORD ( dwBuildNumber )
   _XBST_DWORD ( dwPlatformId )
   _XBST_SZSTR ( szCSDVersion,128)
   _XBST_WORD  ( wServicePackMajor )
   _XBST_WORD  ( wServicePackMinor )
   _XBST_WORD  ( wSuiteMask )
   _XBST_BYTE  ( wProductType )
   _XBST_BYTE  ( wReserved )
   pc->Method_cbbs( "init", "{|s,p1,p2| s:_gwst_(p1,p2),nFpCall(%i,s),s }" , ot4xb_fill_OSVERSIONINFOEX );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// TOOLHELP STRUCTURES
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MODULEENTRY32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MODULEENTRY32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MODULEENTRY32 structure.
         Defined as MODULEENTRY32 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-moduleentry32</ref-url>
      <size>548</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="DWORD" name="th32ModuleID" offset="4" size="4" />
         <member type="DWORD" name="th32ProcessID" offset="8" size="4" />
         <member type="DWORD" name="GlblcntUsage" offset="12" size="4" />
         <member type="DWORD" name="ProccntUsage" offset="16" size="4" />
         <member type="POINTER32" name="modBaseAddr" offset="20" size="4" />
         <member type="DWORD" name="modBaseSize" offset="24" size="4" />
         <member type="HANDLE" name="hModule" offset="28" size="4" />
         <member type="SZSTR" name="szModule" offset="32" size="256" access="string" />
         <member type="SZSTR" name="szExePath" offset="288" size="260" access="string" />
      </members>
      <methods>
         <method name="_reset_" returns="Self">
            Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
         </method>      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MODULEENTRY32 )
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   _XBST_DWORD ( dwSize           )
   _XBST_DWORD ( th32ModuleID     )
   _XBST_DWORD ( th32ProcessID    )
   _XBST_DWORD ( GlblcntUsage     )
   _XBST_DWORD ( ProccntUsage     )
   _XBST_POINTER32 ( modBaseAddr  )
   _XBST_DWORD ( modBaseSize      )
   _XBST_HANDLE( hModule          )
   _XBST_SZSTR ( szModule  , 256  )
   _XBST_SZSTR ( szExePath , 260  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PROCESSENTRY32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PROCESSENTRY32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PROCESSENTRY32 structure.
         Defined as PROCESSENTRY32 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32</ref-url>
      <size>296</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="DWORD" name="cntUsage" offset="4" size="4" />
         <member type="DWORD" name="th32ProcessID" offset="8" size="4" />
         <member type="DWORD" name="th32DefaultHeapID" offset="12" size="4" />
         <member type="DWORD" name="th32ModuleID" offset="16" size="4" />
         <member type="DWORD" name="cntThreads" offset="20" size="4" />
         <member type="DWORD" name="th32ParentProcessID" offset="24" size="4" />
         <member type="LONG" name="pcPriClassBase" offset="28" size="4" />
         <member type="DWORD" name="dwFlags" offset="32" size="4" />
         <member type="SZSTR" name="szExeFile" offset="36" size="260" access="string" />
      </members>
      <methods>
         <method name="_reset_" returns="Self">
            Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
         </method>      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PROCESSENTRY32 )
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   _XBST_DWORD ( dwSize                )
   _XBST_DWORD ( cntUsage              )
   _XBST_DWORD ( th32ProcessID         )
   _XBST_DWORD ( th32DefaultHeapID     )
   _XBST_DWORD ( th32ModuleID          )
   _XBST_DWORD ( cntThreads            )
   _XBST_DWORD ( th32ParentProcessID   )
   _XBST_LONG  ( pcPriClassBase        )
   _XBST_DWORD ( dwFlags               )
   _XBST_SZSTR ( szExeFile , 260       )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_THREADENTRY32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_THREADENTRY32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi THREADENTRY32 structure.
         Defined as THREADENTRY32 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-threadentry32</ref-url>
      <size>28</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="DWORD" name="cntUsage" offset="4" size="4" />
         <member type="DWORD" name="th32ThreadID" offset="8" size="4" />
         <member type="DWORD" name="th32OwnerProcessID" offset="12" size="4" />
         <member type="LONG" name="tpBasePri" offset="16" size="4" />
         <member type="LONG" name="tpDeltaPri" offset="20" size="4" />
         <member type="DWORD" name="dwFlags" offset="24" size="4" />
      </members>
      <methods>
         <method name="_reset_" returns="Self">
            Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
         </method>      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( THREADENTRY32 )
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   _XBST_DWORD ( dwSize               )
   _XBST_DWORD ( cntUsage             )
   _XBST_DWORD ( th32ThreadID         )
   _XBST_DWORD ( th32OwnerProcessID   )
   _XBST_LONG  ( tpBasePri            )
   _XBST_LONG  ( tpDeltaPri           )
   _XBST_DWORD ( dwFlags              )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HEAPENTRY32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HEAPENTRY32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HEAPENTRY32 structure.
         Defined as HEAPENTRY32 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-heapentry32</ref-url>
      <size>36</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="HANDLE" name="hHandle" offset="4" size="4" />
         <member type="DWORD" name="dwAddress" offset="8" size="4" />
         <member type="DWORD" name="dwBlockSize" offset="12" size="4" />
         <member type="DWORD" name="dwFlags" offset="16" size="4" />
         <member type="DWORD" name="dwLockCount" offset="20" size="4" />
         <member type="DWORD" name="dwResvd" offset="24" size="4" />
         <member type="DWORD" name="th32ProcessID" offset="28" size="4" />
         <member type="DWORD" name="th32HeapID" offset="32" size="4" />
      </members>
      <methods>
         <method name="_reset_" returns="Self">
            Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
         </method>      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HEAPENTRY32 )
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   _XBST_DWORD ( dwSize           )
   _XBST_HANDLE( hHandle          )
   _XBST_DWORD ( dwAddress        )
   _XBST_DWORD ( dwBlockSize      )
   _XBST_DWORD ( dwFlags          )
   _XBST_DWORD ( dwLockCount      )
   _XBST_DWORD ( dwResvd          )
   _XBST_DWORD ( th32ProcessID    )
   _XBST_DWORD ( th32HeapID       )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HEAPLIST32</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HEAPLIST32</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HEAPLIST32 structure.
         Defined as HEAPLIST32 in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-heaplist32</ref-url>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="DWORD" name="th32ProcessID" offset="4" size="4" />
         <member type="DWORD" name="th32HeapID" offset="8" size="4" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
      </members>
      <methods>
         <method name="_reset_" returns="Self">
            Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
         </method>      </methods>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HEAPLIST32 )
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   _XBST_DWORD ( dwSize        )
   _XBST_DWORD ( th32ProcessID )
   _XBST_DWORD ( th32HeapID    )
   _XBST_DWORD ( dwFlags       )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVBKIMAGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVBKIMAGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVBKIMAGE structure.
         Defined as LVBKIMAGE in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvbkimagea</ref-url>
      <size>24</size>
      <members>
         <member type="ULONG" name="ulFlags" offset="0" size="4" />
         <member type="HBITMAP" name="hbm" offset="4" size="4" />
         <member type="LPSTR" name="pszImage" offset="8" size="4" />
         <member type="UINT" name="cchImageMax" offset="12" size="4" />
         <member type="INT" name="xOffsetPercent" offset="16" size="4" />
         <member type="INT" name="yOffsetPercent" offset="20" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cImage" target="pszImage" offset="8" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVBKIMAGE )
   _XBST_ULONG( ulFlags )
   _XBST_HBITMAP( hbm )
   _XBST_LPSTR_DYNSZ( pszImage , cImage )
   _XBST_UINT( cchImageMax )
   _XBST_int( xOffsetPercent )
   _XBST_int( yOffsetPercent )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVCOLUMN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVCOLUMN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVCOLUMN structure.
         Defined as LVCOLUMN in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvcolumna</ref-url>
      <size>44</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="INT" name="fmt" offset="4" size="4" />
         <member type="INT" name="cx" offset="8" size="4" />
         <member type="LPSTR" name="pszText" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="INT" name="iSubItem" offset="20" size="4" />
         <member type="INT" name="iImage" offset="24" size="4" />
         <member type="INT" name="iOrder" offset="28" size="4" />
         <member type="INT" name="cxMin" offset="32" size="4" />
         <member type="INT" name="cxDefault" offset="36" size="4" />
         <member type="INT" name="cxIdeal" offset="40" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cText" target="pszText" offset="12" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVCOLUMN )
   _XBST_UINT( mask )
   _XBST_int( fmt )
   _XBST_int( cx )
_XBST_LPSTR_DYNSZ( pszText , cText )
   _XBST_int( cchTextMax )
   _XBST_int( iSubItem )
   _XBST_int( iImage )
   _XBST_int( iOrder )
   _XBST_int( cxMin )
   _XBST_int( cxDefault )
   _XBST_int( cxIdeal )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVFINDINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVFINDINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVFINDINFO structure.
         Defined as LVFINDINFO in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvfindinfoa</ref-url>
      <size>24</size>
      <members>
         <member type="UINT" name="flags" offset="0" size="4" />
         <member type="LPSTR" name="psz" offset="4" size="4" />
         <member type="LPARAM" name="lParam" offset="8" size="4" />
         <member type="WAPIST_POINT" name="pt" offset="12" size="8" child="true" />
         <member type="UINT" name="vkDirection" offset="20" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cStr" target="psz" offset="4" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVFINDINFO )
   _XBST_UINT( flags )
_XBST_LPSTR_DYNSZ( psz , cStr )
   _XBST_LPARAM( lParam )
   _XBST_POINT( pt )
   _XBST_UINT( vkDirection )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVFOOTERINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVFOOTERINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVFOOTERINFO structure.
         Defined as LVFOOTERINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="POINTER32" name="pszText" offset="4" size="4" />
         <member type="INT" name="cchTextMax" offset="8" size="4" />
         <member type="UINT" name="cItems" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(LVFOOTERINFO )
   _XBST_UINT( mask )
   _XBST_POINTER32( pszText )  // LPWSTR
   _XBST_int( cchTextMax )
   _XBST_UINT( cItems )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVFOOTERITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVFOOTERITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVFOOTERITEM structure.
         Defined as LVFOOTERITEM in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="INT" name="iItem" offset="4" size="4" />
         <member type="POINTER32" name="pszText" offset="8" size="4" />
         <member type="INT" name="cchTextMax" offset="12" size="4" />
         <member type="UINT" name="state" offset="16" size="4" />
         <member type="UINT" name="stateMask" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(LVFOOTERITEM )
   _XBST_UINT( mask )
   _XBST_int( iItem )
   _XBST_POINTER32( pszText ) // LPWSTR
   _XBST_int( cchTextMax )
   _XBST_UINT( state )
   _XBST_UINT( stateMask )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVGROUP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVGROUP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVGROUP structure.
         Defined as LVGROUP in ot4xb_wapist_map.ch.
      </description>
      <size>96</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="mask" offset="4" size="4" />
         <member type="POINTER32" name="pszHeader" offset="8" size="4" />
         <member type="INT" name="cchHeader" offset="12" size="4" />
         <member type="POINTER32" name="pszFooter" offset="16" size="4" />
         <member type="INT" name="cchFooter" offset="20" size="4" />
         <member type="INT" name="iGroupId" offset="24" size="4" />
         <member type="UINT" name="stateMask" offset="28" size="4" />
         <member type="UINT" name="state" offset="32" size="4" />
         <member type="UINT" name="uAlign" offset="36" size="4" />
         <member type="POINTER32" name="pszSubtitle" offset="40" size="4" />
         <member type="UINT" name="cchSubtitle" offset="44" size="4" />
         <member type="POINTER32" name="pszTask" offset="48" size="4" />
         <member type="UINT" name="cchTask" offset="52" size="4" />
         <member type="POINTER32" name="pszDescriptionTop" offset="56" size="4" />
         <member type="UINT" name="cchDescriptionTop" offset="60" size="4" />
         <member type="POINTER32" name="pszDescriptionBottom" offset="64" size="4" />
         <member type="UINT" name="cchDescriptionBottom" offset="68" size="4" />
         <member type="INT" name="iTitleImage" offset="72" size="4" />
         <member type="INT" name="iExtendedImage" offset="76" size="4" />
         <member type="INT" name="iFirstItem" offset="80" size="4" />
         <member type="UINT" name="cItems" offset="84" size="4" />
         <member type="POINTER32" name="pszSubsetTitle" offset="88" size="4" />
         <member type="UINT" name="cchSubsetTitle" offset="92" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVGROUP )
   _XBST_UINT   ( cbSize )
   _XBST_UINT   ( mask )
   _XBST_POINTER32 ( pszHeader ) // LPWSTR
   _XBST_int    ( cchHeader )
   _XBST_POINTER32( pszFooter ) // LPWSTR
   _XBST_int    ( cchFooter )
   _XBST_int    ( iGroupId )
   _XBST_UINT   ( stateMask )
   _XBST_UINT   ( state )
   _XBST_UINT   ( uAlign )
   _XBST_POINTER32 ( pszSubtitle ) // LPWSTR
   _XBST_UINT   ( cchSubtitle )
   _XBST_POINTER32 ( pszTask )  // LPWSTR
   _XBST_UINT   ( cchTask )
   _XBST_POINTER32 ( pszDescriptionTop )  // LPWSTR
   _XBST_UINT   ( cchDescriptionTop )
   _XBST_POINTER32 ( pszDescriptionBottom ) // LPWSTR
   _XBST_UINT   ( cchDescriptionBottom )
   _XBST_int    ( iTitleImage )
   _XBST_int    ( iExtendedImage )
   _XBST_int    ( iFirstItem )
   _XBST_UINT   ( cItems )
   _XBST_POINTER32 ( pszSubsetTitle ) // LPWSTR
   _XBST_UINT   ( cchSubsetTitle )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVGROUPMETRICS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVGROUPMETRICS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVGROUPMETRICS structure.
         Defined as LVGROUPMETRICS in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="mask" offset="4" size="4" />
         <member type="UINT" name="Left" offset="8" size="4" />
         <member type="UINT" name="Top" offset="12" size="4" />
         <member type="UINT" name="Right" offset="16" size="4" />
         <member type="UINT" name="Bottom" offset="20" size="4" />
         <member type="COLORREF" name="crLeft" offset="24" size="4" />
         <member type="COLORREF" name="crTop" offset="28" size="4" />
         <member type="COLORREF" name="crRight" offset="32" size="4" />
         <member type="COLORREF" name="crBottom" offset="36" size="4" />
         <member type="COLORREF" name="crHeader" offset="40" size="4" />
         <member type="COLORREF" name="crFooter" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(LVGROUPMETRICS )
   _XBST_UINT( cbSize )
   _XBST_UINT( mask )
   _XBST_UINT( Left )
   _XBST_UINT( Top )
   _XBST_UINT( Right )
   _XBST_UINT( Bottom )
   _XBST_COLORREF( crLeft )
   _XBST_COLORREF( crTop )
   _XBST_COLORREF( crRight )
   _XBST_COLORREF( crBottom )
   _XBST_COLORREF( crHeader )
   _XBST_COLORREF( crFooter )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVHITTESTINFO structure.
         Defined as LVHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="UINT" name="flags" offset="8" size="4" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="INT" name="iSubItem" offset="16" size="4" />
         <member type="INT" name="iGroup" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVHITTESTINFO )
   _XBST_POINT( pt )
   _XBST_UINT( flags )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_int( iGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVINSERTGROUPSORTED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVINSERTGROUPSORTED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVINSERTGROUPSORTED structure.
         Defined as LVINSERTGROUPSORTED in ot4xb_wapist_map.ch.
      </description>
      <size>104</size>
      <members>
         <member type="POINTER32" name="pfnGroupCompare" offset="0" size="4" />
         <member type="POINTER32" name="pvData" offset="4" size="4" />
         <member type="WAPIST_LVGROUP" name="lvGroup" offset="8" size="96" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVINSERTGROUPSORTED )
   _XBST_POINTER32( pfnGroupCompare )
   _XBST_POINTER32( pvData )
   _XBST_LVGROUP( lvGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVINSERTMARK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVINSERTMARK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVINSERTMARK structure.
         Defined as LVINSERTMARK in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
         <member type="INT" name="iItem" offset="8" size="4" />
         <member type="DWORD" name="dwReserved" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVINSERTMARK )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwFlags )
   _XBST_int( iItem )
   _XBST_DWORD( dwReserved )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVITEM</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi LVITEMA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvitema</ref-url>
      <size>60</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="INT" name="iItem" offset="4" size="4" />
         <member type="INT" name="iSubItem" offset="8" size="4" />
         <member type="UINT" name="state" offset="12" size="4" />
         <member type="UINT" name="stateMask" offset="16" size="4" />
         <member type="LPSTR" name="pszText" offset="20" size="4" />
         <member type="INT" name="cchTextMax" offset="24" size="4" />
         <member type="INT" name="iImage" offset="28" size="4" />
         <member type="LPARAM" name="lParam" offset="32" size="4" />
         <member type="INT" name="iIndent" offset="36" size="4" />
         <member type="INT" name="iGroupId" offset="40" size="4" />
         <member type="UINT" name="cColumns" offset="44" size="4" />
         <member type="POINTER32" name="puColumns" offset="48" size="4" />
         <member type="POINTER32" name="piColFmt" offset="52" size="4" />
         <member type="INT" name="iGroup" offset="56" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cText" target="pszText" offset="20" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVITEM )
   _XBST_UINT( mask )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_UINT( state )
   _XBST_UINT( stateMask )
_XBST_LPSTR_DYNSZ( pszText , cText)
   _XBST_int( cchTextMax )
   _XBST_int( iImage )
   _XBST_LPARAM( lParam )
   _XBST_int( iIndent )
   _XBST_int( iGroupId )
   _XBST_UINT( cColumns )
   _XBST_POINTER32( puColumns )
   _XBST_POINTER32( piColFmt )
   _XBST_int( iGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVITEMINDEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVITEMINDEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVITEMINDEX structure.
         Defined as LVITEMINDEX in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="INT" name="iItem" offset="0" size="4" />
         <member type="INT" name="iGroup" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/`r`nXB_BEGIN_STRUCTURE( LVITEMINDEX )
   _XBST_int( iItem )
   _XBST_int( iGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVSETINFOTIP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVSETINFOTIP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVSETINFOTIP structure.
         Defined as LVSETINFOTIP in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
         <member type="POINTER32" name="pszText" offset="8" size="4" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="INT" name="iSubItem" offset="16" size="4" />
         <member type="HBITMAP" name="hbmp" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVSETINFOTIP )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwFlags )
   _XBST_POINTER32( pszText ) // LPWSTR
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_HBITMAP( hbmp )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVTILEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVTILEINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVTILEINFO structure.
         Defined as LVTILEINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="INT" name="iItem" offset="4" size="4" />
         <member type="UINT" name="cColumns" offset="8" size="4" />
         <member type="POINTER32" name="puColumns" offset="12" size="4" />
         <member type="POINTER32" name="piColFmt" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVTILEINFO )
   _XBST_UINT   ( cbSize )
   _XBST_int    ( iItem )
   _XBST_UINT   ( cColumns )
   _XBST_POINTER32( puColumns )
   _XBST_POINTER32   ( piColFmt )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LVTILEVIEWINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LVTILEVIEWINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LVTILEVIEWINFO structure.
         Defined as LVTILEVIEWINFO in ot4xb_wapist_map.ch.
      </description>
      <size>40</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="DWORD" name="dwFlags" offset="8" size="4" />
         <member type="WAPIST_SIZE" name="sizeTile" offset="12" size="8" child="true" />
         <member type="INT" name="cLines" offset="20" size="4" />
         <member type="WAPIST_RECT" name="rcLabelMargin" offset="24" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LVTILEVIEWINFO )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwMask )
   _XBST_DWORD( dwFlags )
   _XBST_SIZE( sizeTile )
   _XBST_int( cLines )
   _XBST_RECT( rcLabelMargin )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMITEMACTIVATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMITEMACTIVATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMITEMACTIVATE structure.
         Defined as NMITEMACTIVATE in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="INT" name="iSubItem" offset="16" size="4" />
         <member type="UINT" name="uNewState" offset="20" size="4" />
         <member type="UINT" name="uOldState" offset="24" size="4" />
         <member type="UINT" name="uChanged" offset="28" size="4" />
         <member type="WAPIST_POINT" name="ptAction" offset="32" size="8" child="true" />
         <member type="LPARAM" name="lParam" offset="40" size="4" />
         <member type="UINT" name="uKeyFlags" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMITEMACTIVATE )
   _XBST_NMHDR( hdr )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_UINT( uNewState )
   _XBST_UINT( uOldState )
   _XBST_UINT( uChanged )
   _XBST_POINT( ptAction )
   _XBST_LPARAM( lParam )
   _XBST_UINT( uKeyFlags )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLISTVIEW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLISTVIEW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLISTVIEW structure.
         Defined as NMLISTVIEW in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="INT" name="iSubItem" offset="16" size="4" />
         <member type="UINT" name="uNewState" offset="20" size="4" />
         <member type="UINT" name="uOldState" offset="24" size="4" />
         <member type="UINT" name="uChanged" offset="28" size="4" />
         <member type="WAPIST_POINT" name="ptAction" offset="32" size="8" child="true" />
         <member type="LPARAM" name="lParam" offset="40" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLISTVIEW )
   _XBST_NMHDR( hdr )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_UINT( uNewState )
   _XBST_UINT( uOldState )
   _XBST_UINT( uChanged )
   _XBST_POINT( ptAction )
   _XBST_LPARAM( lParam )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVCACHEHINT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVCACHEHINT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVCACHEHINT structure.
         Defined as NMLVCACHEHINT in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iFrom" offset="12" size="4" />
         <member type="INT" name="iTo" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVCACHEHINT )
   _XBST_NMHDR( hdr )
   _XBST_int( iFrom )
   _XBST_int( iTo )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVCUSTOMDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVCUSTOMDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVCUSTOMDRAW structure.
         Defined as NMLVCUSTOMDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>104</size>
      <members>
         <member type="WAPIST_NMCUSTOMDRAW" name="nmcd" offset="0" size="48" child="true" />
         <member type="COLORREF" name="clrText" offset="48" size="4" />
         <member type="COLORREF" name="clrTextBk" offset="52" size="4" />
         <member type="INT" name="iSubItem" offset="56" size="4" />
         <member type="DWORD" name="dwItemType" offset="60" size="4" />
         <member type="COLORREF" name="clrFace" offset="64" size="4" />
         <member type="INT" name="iIconEffect" offset="68" size="4" />
         <member type="INT" name="iIconPhase" offset="72" size="4" />
         <member type="INT" name="iPartId" offset="76" size="4" />
         <member type="INT" name="iStateId" offset="80" size="4" />
         <member type="WAPIST_RECT" name="rcText" offset="84" size="16" child="true" />
         <member type="UINT" name="uAlign" offset="100" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW( nmcd )
   _XBST_COLORREF( clrText )
   _XBST_COLORREF( clrTextBk )
   _XBST_int( iSubItem )
   _XBST_DWORD( dwItemType )
   _XBST_COLORREF( clrFace )
   _XBST_INT( iIconEffect )
   _XBST_INT( iIconPhase )
   _XBST_INT( iPartId )
   _XBST_INT( iStateId )
   _XBST_RECT( rcText )
   _XBST_UINT( uAlign )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVDISPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVDISPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVDISPINFO structure.
         Defined as NMLVDISPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_LVITEM" name="item" offset="12" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVDISPINFO )
   _XBST_NMHDR( hdr )
   _XBST_LVITEM( item )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVEMPTYMARKUP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVEMPTYMARKUP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVEMPTYMARKUP structure.
         Defined as NMLVEMPTYMARKUP in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
         <member type="SZWSTR" name="szMarkup" size="2084" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVEMPTYMARKUP )
   _XBST_NMHDR( hdr )
   _XBST_DWORD( dwFlags )
   _XBST_SZWSTR( szMarkup , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVFINDITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVFINDITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVFINDITEM structure.
         Defined as NMLVFINDITEM in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iStart" offset="12" size="4" />
         <member type="WAPIST_LVFINDINFO" name="lvfi" offset="16" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVFINDITEM )
   _XBST_NMHDR( hdr )
   _XBST_int( iStart )
   _XBST_LVFINDINFO( lvfi )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVGETINFOTIP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVGETINFOTIP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVGETINFOTIP structure.
         Defined as NMLVGETINFOTIP in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-nmlvgetinfotipa</ref-url>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
         <member type="LPSTR" name="pszText" offset="16" size="4" />
         <member type="INT" name="cchTextMax" offset="20" size="4" />
         <member type="INT" name="iItem" offset="24" size="4" />
         <member type="INT" name="iSubItem" offset="28" size="4" />
         <member type="LPARAM" name="lParam" offset="32" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cText" target="pszText" offset="16" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVGETINFOTIP )
   _XBST_NMHDR( hdr )
   _XBST_DWORD( dwFlags )
_XBST_LPSTR_DYNSZ( pszText , cText)
   _XBST_int( cchTextMax )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_LPARAM( lParam )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVKEYDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVKEYDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVKEYDOWN structure.
         Defined as NMLVKEYDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>18</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WORD" name="wVKey" offset="12" size="2" />
         <member type="UINT" name="flags" offset="14" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVKEYDOWN )
   _XBST_NMHDR( hdr )
   _XBST_WORD( wVKey )
   _XBST_UINT( flags )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVLINK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVLINK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVLINK structure.
         Defined as NMLVLINK in ot4xb_wapist_map.ch.
      </description>
      <size>132</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_LITEM" name="link" offset="12" size="112" child="true" />
         <member type="INT" name="iItem" offset="124" size="4" />
         <member type="INT" name="iSubItem" offset="128" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVLINK )
   _XBST_NMHDR( hdr )
   _XBST_LITEM( link )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVODSTATECHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVODSTATECHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVODSTATECHANGE structure.
         Defined as NMLVODSTATECHANGE in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iFrom" offset="12" size="4" />
         <member type="INT" name="iTo" offset="16" size="4" />
         <member type="UINT" name="uNewState" offset="20" size="4" />
         <member type="UINT" name="uOldState" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVODSTATECHANGE )
   _XBST_NMHDR( hdr )
   _XBST_int( iFrom )
   _XBST_int( iTo )
   _XBST_UINT( uNewState )
   _XBST_UINT( uOldState )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLVSCROLL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLVSCROLL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLVSCROLL structure.
         Defined as NMLVSCROLL in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="dx" offset="12" size="4" />
         <member type="INT" name="dy" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLVSCROLL )
   _XBST_NMHDR( hdr )
   _XBST_int( dx )
   _XBST_int( dy )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LITEM structure.
         Defined as LITEM in ot4xb_wapist_map.ch.
      </description>
      <size>112</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="INT" name="iLink" offset="4" size="4" />
         <member type="UINT" name="state" offset="8" size="4" />
         <member type="UINT" name="stateMask" offset="12" size="4" />
         <member type="SZWSTR" name="szID" offset="16" size="96" access="string" chars="48" />
         <member type="SZWSTR" name="szUrl" size="2084" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LITEM )
   _XBST_UINT( mask )
   _XBST_int( iLink )
   _XBST_UINT( state )
   _XBST_UINT( stateMask )
   _XBST_SZWSTR( szID  , 48 )
   _XBST_SZWSTR( szUrl , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCUSTOMDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCUSTOMDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCUSTOMDRAW structure.
         Defined as NMCUSTOMDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwDrawStage" offset="12" size="4" />
         <member type="HDC" name="hdc" offset="16" size="4" />
         <member type="WAPIST_RECT" name="rc" offset="20" size="16" child="true" />
         <member type="DWORD" name="dwItemSpec" offset="36" size="4" />
         <member type="UINT" name="uItemState" offset="40" size="4" />
         <member type="LPARAM" name="lItemlParam" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCUSTOMDRAW )
   _XBST_NMHDR( hdr )
   _XBST_DWORD( dwDrawStage )
   _XBST_HDC( hdc )
   _XBST_RECT( rc )
   _XBST_DWORD( dwItemSpec )
   _XBST_UINT( uItemState )
   _XBST_LPARAM( lItemlParam )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_WINDOWPOS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_WINDOWPOS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi WINDOWPOS structure.
         Defined as WINDOWPOS in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="HWND" name="hwnd" offset="0" size="4" />
         <member type="HWND" name="hwndInsertAfter" offset="4" size="4" />
         <member type="INT" name="x" offset="8" size="4" />
         <member type="INT" name="y" offset="12" size="4" />
         <member type="INT" name="cx" offset="16" size="4" />
         <member type="INT" name="cy" offset="20" size="4" />
         <member type="UINT" name="flags" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( WINDOWPOS )
   _XBST_HWND ( hwnd  )
   _XBST_HWND ( hwndInsertAfter  )
   _XBST_int ( x  )
   _XBST_int ( y  )
   _XBST_int ( cx  )
   _XBST_int ( cy  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COLORSCHEME</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COLORSCHEME</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COLORSCHEME structure.
         Defined as COLORSCHEME in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="COLORREF" name="clrBtnHighlight" offset="4" size="4" />
         <member type="COLORREF" name="clrBtnShadow" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COLORSCHEME )
   _XBST_DWORD ( dwSize  )
   _XBST_COLORREF ( clrBtnHighlight  )
   _XBST_COLORREF ( clrBtnShadow  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DPASTREAMINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DPASTREAMINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DPASTREAMINFO structure.
         Defined as DPASTREAMINFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="INT" name="iPos" offset="0" size="4" />
         <member type="LPVOID" name="pvItem" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DPASTREAMINFO )
   _XBST_int ( iPos  )
   _XBST_LPVOID ( pvItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCHAR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCHAR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCHAR structure.
         Defined as NMCHAR in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="ch" offset="12" size="4" />
         <member type="DWORD" name="dwItemPrev" offset="16" size="4" />
         <member type="DWORD" name="dwItemNext" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCHAR )
   _XBST_NMHDR ( hdr         )
   _XBST_UINT  ( ch          )
   _XBST_DWORD ( dwItemPrev  )
   _XBST_DWORD ( dwItemNext  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCUSTOMSPLITRECTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCUSTOMSPLITRECTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCUSTOMSPLITRECTINFO structure.
         Defined as NMCUSTOMSPLITRECTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_RECT" name="rcClient" offset="12" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcButton" offset="28" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcSplit" offset="44" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCUSTOMSPLITRECTINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcClient  )
   _XBST_RECT ( rcButton  )
   _XBST_RECT ( rcSplit  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCUSTOMTEXT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCUSTOMTEXT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCUSTOMTEXT structure.
         Defined as NMCUSTOMTEXT in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="HDC" name="hDC" offset="12" size="4" />
         <member type="POINTER32" name="lpString" offset="16" size="4" />
         <member type="INT" name="nCount" offset="20" size="4" />
         <member type="POINTER32" name="lpRect" offset="24" size="4" />
         <member type="UINT" name="uFormat" offset="28" size="4" />
         <member type="BOOL" name="fLink" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCUSTOMTEXT )
   _XBST_NMHDR ( hdr  )
   _XBST_HDC ( hDC  )
   _XBST_POINTER32 ( lpString  )
   _XBST_int ( nCount  )
   _XBST_POINTER32( lpRect  )
   _XBST_UINT ( uFormat  )
   _XBST_BOOL ( fLink  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMKEY</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMKEY</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMKEY structure.
         Defined as NMKEY in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="nVKey" offset="12" size="4" />
         <member type="UINT" name="uFlags" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMKEY )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( nVKey  )
   _XBST_UINT ( uFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMMOUSE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMMOUSE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMMOUSE structure.
         Defined as NMMOUSE in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="POINTER32" name="dwItemSpec" offset="12" size="4" />
         <member type="POINTER32" name="dwItemData" offset="16" size="4" />
         <member type="WAPIST_POINT" name="pt" offset="20" size="8" child="true" />
         <member type="LPARAM" name="dwHitInfo" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMMOUSE )
   _XBST_NMHDR ( hdr  )
   _XBST_POINTER32 ( dwItemSpec  )
   _XBST_POINTER32 ( dwItemData  )
   _XBST_POINT ( pt  )
   _XBST_LPARAM ( dwHitInfo  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMOBJECTNOTIFY</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMOBJECTNOTIFY</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMOBJECTNOTIFY structure.
         Defined as NMOBJECTNOTIFY in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="POINTER32" name="piid" offset="16" size="4" />
         <member type="POINTER32" name="pObject" offset="20" size="4" />
         <member type="HRESULT" name="hResult" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMOBJECTNOTIFY )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_POINTER32 ( piid  )
   _XBST_POINTER32 ( pObject  )
   _XBST_HRESULT ( hResult  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTOOLTIPSCREATED</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTOOLTIPSCREATED</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTOOLTIPSCREATED structure.
         Defined as NMTOOLTIPSCREATED in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="HWND" name="hwndToolTips" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTOOLTIPSCREATED )
   _XBST_NMHDR ( hdr  )
   _XBST_HWND ( hwndToolTips  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_READERMODEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_READERMODEINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi READERMODEINFO structure.
         Defined as READERMODEINFO in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="HWND" name="hwnd" offset="4" size="4" />
         <member type="DWORD" name="fFlags" offset="8" size="4" />
         <member type="POINTER32" name="prc" offset="12" size="4" />
         <member type="DWORD" name="pfnScroll" offset="16" size="4" />
         <member type="DWORD" name="fFlags" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( READERMODEINFO )
   _XBST_UINT ( cbSize  )
   _XBST_HWND ( hwnd  )
   _XBST_DWORD ( fFlags  )
   _XBST_POINTER32( prc  )
   _XBST_DWORD  ( pfnScroll  )
   _XBST_DWORD  ( fFlags  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BUTTON_IMAGELIST</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BUTTON_IMAGELIST</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BUTTON_IMAGELIST structure.
         Defined as BUTTON_IMAGELIST in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="HIMAGELIST" name="himl" offset="0" size="4" />
         <member type="WAPIST_RECT" name="margin" offset="4" size="16" child="true" />
         <member type="UINT" name="uAlign" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( BUTTON_IMAGELIST )
   _XBST_HIMAGELIST ( himl  )
   _XBST_RECT ( margin  )
   _XBST_UINT ( uAlign  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_BUTTON_SPLITINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_BUTTON_SPLITINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi BUTTON_SPLITINFO structure.
         Defined as BUTTON_SPLITINFO in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="HIMAGELIST" name="himlGlyph" offset="4" size="4" />
         <member type="UINT" name="uSplitStyle" offset="8" size="4" />
         <member type="WAPIST_SIZE" name="size" offset="12" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( BUTTON_SPLITINFO )
   _XBST_UINT ( mask  )
   _XBST_HIMAGELIST ( himlGlyph  )
   _XBST_UINT ( uSplitStyle  )
   _XBST_SIZE ( size  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMBCDROPDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMBCDROPDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMBCDROPDOWN structure.
         Defined as NMBCDROPDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_RECT" name="rcButton" offset="12" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMBCDROPDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMBCHOTITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMBCHOTITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMBCHOTITEM structure.
         Defined as NMBCHOTITEM in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMBCHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COMBOBOXINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COMBOBOXINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COMBOBOXINFO structure.
         Defined as COMBOBOXINFO in ot4xb_wapist_map.ch.
      </description>
      <size>52</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcItem" offset="4" size="16" child="true" />
         <member type="WAPIST_RECT" name="rcButton" offset="20" size="16" child="true" />
         <member type="DWORD" name="stateButton" offset="36" size="4" />
         <member type="HWND" name="hwndCombo" offset="40" size="4" />
         <member type="HWND" name="hwndItem" offset="44" size="4" />
         <member type="HWND" name="hwndList" offset="48" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COMBOBOXINFO )
   _XBST_DWORD ( cbSize  )
   _XBST_RECT ( rcItem  )
   _XBST_RECT ( rcButton  )
   _XBST_DWORD ( stateButton  )
   _XBST_HWND ( hwndCombo  )
   _XBST_HWND ( hwndItem  )
   _XBST_HWND ( hwndList  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COMPAREITEMSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COMPAREITEMSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COMPAREITEMSTRUCT structure.
         Defined as COMPAREITEMSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="UINT" name="CtlType" offset="0" size="4" />
         <member type="UINT" name="CtlID" offset="4" size="4" />
         <member type="HWND" name="hwndItem" offset="8" size="4" />
         <member type="UINT" name="itemID1" offset="12" size="4" />
         <member type="POINTER32" name="itemData1" offset="16" size="4" />
         <member type="UINT" name="itemID2" offset="20" size="4" />
         <member type="POINTER32" name="itemData2" offset="24" size="4" />
         <member type="DWORD" name="dwLocaleId" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COMPAREITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_HWND ( hwndItem  )
   _XBST_UINT ( itemID1  )
   _XBST_POINTER32 ( itemData1  )
   _XBST_UINT ( itemID2  )
   _XBST_POINTER32 ( itemData2  )
   _XBST_DWORD ( dwLocaleId  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRAWITEMSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRAWITEMSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRAWITEMSTRUCT structure.
         Defined as DRAWITEMSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="UINT" name="CtlType" offset="0" size="4" />
         <member type="UINT" name="CtlID" offset="4" size="4" />
         <member type="UINT" name="itemID" offset="8" size="4" />
         <member type="UINT" name="itemAction" offset="12" size="4" />
         <member type="UINT" name="itemState" offset="16" size="4" />
         <member type="HWND" name="hwndItem" offset="20" size="4" />
         <member type="HDC" name="hDC" offset="24" size="4" />
         <member type="WAPIST_RECT" name="rcItem" offset="28" size="16" child="true" />
         <member type="POINTER32" name="itemData" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRAWITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_UINT ( itemID  )
   _XBST_UINT ( itemAction  )
   _XBST_UINT ( itemState  )
   _XBST_HWND ( hwndItem  )
   _XBST_HDC ( hDC  )
   _XBST_RECT ( rcItem  )
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MEASUREITEMSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MEASUREITEMSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MEASUREITEMSTRUCT structure.
         Defined as MEASUREITEMSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="UINT" name="CtlType" offset="0" size="4" />
         <member type="UINT" name="CtlID" offset="4" size="4" />
         <member type="UINT" name="itemID" offset="8" size="4" />
         <member type="UINT" name="itemWidth" offset="12" size="4" />
         <member type="UINT" name="itemHeight" offset="16" size="4" />
         <member type="POINTER32" name="itemData" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MEASUREITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_UINT ( itemID  )
   _XBST_UINT ( itemWidth  )
   _XBST_UINT ( itemHeight  )
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COMBOBOXEXITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COMBOBOXEXITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COMBOBOXEXITEM structure.
         Defined as COMBOBOXEXITEM in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="POINTER32" name="iItem" offset="4" size="4" />
         <member type="LPSTR" name="pszText" offset="8" size="4" />
         <member type="INT" name="cchTextMax" offset="12" size="4" />
         <member type="INT" name="iImage" offset="16" size="4" />
         <member type="INT" name="iSelectedImage" offset="20" size="4" />
         <member type="INT" name="iOverlay" offset="24" size="4" />
         <member type="INT" name="iIndent" offset="28" size="4" />
         <member type="LPARAM" name="lParam" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COMBOBOXEXITEM )
   _XBST_UINT ( mask  )
   _XBST_POINTER32 ( iItem  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
   _XBST_int ( iSelectedImage  )
   _XBST_int ( iOverlay  )
   _XBST_int ( iIndent  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCBEDRAGBEGIN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCBEDRAGBEGIN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCBEDRAGBEGIN structure.
         Defined as NMCBEDRAGBEGIN in ot4xb_wapist_map.ch.
      </description>
      <size>17</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItemid" offset="12" size="4" />
         <member type="BYTE" name="szText" offset="16" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCBEDRAGBEGIN )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItemid  )
   _XBST_CHAR ( szText  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCBEENDEDIT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCBEENDEDIT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCBEENDEDIT structure.
         Defined as NMCBEENDEDIT in ot4xb_wapist_map.ch.
      </description>
      <size>25</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="BOOL" name="fChanged" offset="12" size="4" />
         <member type="INT" name="iNewSelection" offset="16" size="4" />
         <member type="BYTE" name="szText" offset="20" size="1" />
         <member type="INT" name="iWhy" offset="21" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCBEENDEDIT )
   _XBST_NMHDR ( hdr  )
   _XBST_BOOL ( fChanged  )
   _XBST_int ( iNewSelection  )
   _XBST_TCHAR ( szText  )
   _XBST_int ( iWhy  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMCOMBOBOXEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMCOMBOBOXEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMCOMBOBOXEX structure.
         Defined as NMCOMBOBOXEX in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_COMBOBOXEXITEM" name="ceItem" offset="12" size="36" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMCOMBOBOXEX )
   _XBST_NMHDR ( hdr  )
   _XBST_COMBOBOXEXITEM ( ceItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DATETIMEPICKERINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DATETIMEPICKERINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DATETIMEPICKERINFO structure.
         Defined as DATETIMEPICKERINFO in ot4xb_wapist_map.ch.
      </description>
      <size>56</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcCheck" offset="4" size="16" child="true" />
         <member type="DWORD" name="stateCheck" offset="20" size="4" />
         <member type="WAPIST_RECT" name="rcButton" offset="24" size="16" child="true" />
         <member type="DWORD" name="stateButton" offset="40" size="4" />
         <member type="HWND" name="hwndEdit" offset="44" size="4" />
         <member type="HWND" name="hwndUD" offset="48" size="4" />
         <member type="HWND" name="hwndDropDown" offset="52" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DATETIMEPICKERINFO )
   _XBST_DWORD ( cbSize  )
   _XBST_RECT ( rcCheck  )
   _XBST_DWORD ( stateCheck  )
   _XBST_RECT ( rcButton  )
   _XBST_DWORD ( stateButton  )
   _XBST_HWND ( hwndEdit  )
   _XBST_HWND ( hwndUD  )
   _XBST_HWND ( hwndDropDown  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDATETIMECHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDATETIMECHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDATETIMECHANGE structure.
         Defined as NMDATETIMECHANGE in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwFlags" offset="12" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="st" offset="16" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDATETIMECHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_DWORD ( dwFlags  )
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDATETIMEFORMAT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDATETIMEFORMAT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDATETIMEFORMAT structure.
         Defined as NMDATETIMEFORMAT in ot4xb_wapist_map.ch.
      </description>
      <size>37</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="pszFormat" offset="12" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="st" offset="16" size="16" child="true" />
         <member type="LPSTR" name="pszDisplay" offset="32" size="4" />
         <member type="BYTE" name="szDisplay" offset="36" size="1" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDATETIMEFORMAT )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SYSTEMTIME ( st  )
   _XBST_LPSTR ( pszDisplay  )
   _XBST_TCHAR ( szDisplay  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDATETIMEFORMATQUERY</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDATETIMEFORMATQUERY</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDATETIMEFORMATQUERY structure.
         Defined as NMDATETIMEFORMATQUERY in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="pszFormat" offset="12" size="4" />
         <member type="WAPIST_SIZE" name="szMax" offset="16" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDATETIMEFORMATQUERY )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SIZE ( szMax  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDATETIMESTRING</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDATETIMESTRING</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDATETIMESTRING structure.
         Defined as NMDATETIMESTRING in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="pszUserString" offset="12" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="st" offset="16" size="16" child="true" />
         <member type="DWORD" name="dwFlags" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDATETIMESTRING )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszUserString  )
   _XBST_SYSTEMTIME ( st  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDATETIMEWMKEYDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDATETIMEWMKEYDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDATETIMEWMKEYDOWN structure.
         Defined as NMDATETIMEWMKEYDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="INT" name="nVirtKey" offset="12" size="4" />
         <member type="LPSTR" name="pszFormat" offset="16" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="st" offset="20" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDATETIMEWMKEYDOWN )
   _XBST_NMHDR ( nmhdr  )
   _XBST_int ( nVirtKey  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DRAGLISTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DRAGLISTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DRAGLISTINFO structure.
         Defined as DRAGLISTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="UINT" name="uNotification" offset="0" size="4" />
         <member type="HWND" name="hWnd" offset="4" size="4" />
         <member type="WAPIST_POINT" name="ptCursor" offset="8" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DRAGLISTINFO )
   _XBST_UINT ( uNotification  )
   _XBST_HWND ( hWnd  )
   _XBST_POINT ( ptCursor  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_EDITBALLOONTIP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_EDITBALLOONTIP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi EDITBALLOONTIP structure.
         Defined as EDITBALLOONTIP in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="cbStruct" offset="0" size="4" />
         <member type="POINTER32" name="pszTitle" offset="4" size="4" />
         <member type="POINTER32" name="pszText" offset="8" size="4" />
         <member type="INT" name="ttiIcon" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( EDITBALLOONTIP )
   _XBST_DWORD ( cbStruct  )
   _XBST_POINTER32 ( pszTitle  )
   _XBST_POINTER32 ( pszText  )
   _XBST_INT ( ttiIcon  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HDHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HDHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HDHITTESTINFO structure.
         Defined as HDHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="UINT" name="flags" offset="8" size="4" />
         <member type="INT" name="iItem" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HDHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
   _XBST_int ( iItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HDITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HDITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HDITEM structure.
         Defined as HDITEM in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="INT" name="cxy" offset="4" size="4" />
         <member type="LPSTR" name="pszText" offset="8" size="4" />
         <member type="HBITMAP" name="hbm" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="INT" name="fmt" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
         <member type="INT" name="iImage" offset="28" size="4" />
         <member type="INT" name="iOrder" offset="32" size="4" />
         <member type="UINT" name="type" offset="36" size="4" />
         <member type="LPVOID" name="pvFilter" offset="40" size="4" />
         <member type="UINT" name="state" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HDITEM )
   _XBST_UINT    ( mask  )
   _XBST_int     ( cxy  )
   _XBST_LPSTR  ( pszText  )
   _XBST_HBITMAP ( hbm  )
   _XBST_int     ( cchTextMax  )
   _XBST_int     ( fmt  )
   _XBST_LPARAM  ( lParam  )
   _XBST_int     ( iImage  )
   _XBST_int     ( iOrder  )
   _XBST_UINT    ( type  )
   _XBST_LPVOID  ( pvFilter  )
   _XBST_UINT   ( state  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HDLAYOUT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HDLAYOUT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HDLAYOUT structure.
         Defined as HDLAYOUT in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="POINTER32" name="prc" offset="0" size="4" />
         <member type="POINTER32" name="pwpos" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HDLAYOUT )
   _XBST_POINTER32  ( prc  )
   _XBST_POINTER32  ( pwpos  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HDTEXTFILTER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HDTEXTFILTER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HDTEXTFILTER structure.
         Defined as HDTEXTFILTER in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="LPSTR" name="pszText" offset="0" size="4" />
         <member type="INT" name="cchTextMax" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HDTEXTFILTER )
   _XBST_LPSTR ( pszText  )
   _XBST_INT ( cchTextMax  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMHDDISPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMHDDISPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMHDDISPINFO structure.
         Defined as NMHDDISPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="UINT" name="mask" offset="16" size="4" />
         <member type="LPSTR" name="pszText" offset="20" size="4" />
         <member type="INT" name="cchTextMax" offset="24" size="4" />
         <member type="INT" name="iImage" offset="28" size="4" />
         <member type="LPARAM" name="lParam" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMHDDISPINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_UINT ( mask  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMHDFILTERBTNCLICK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMHDFILTERBTNCLICK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMHDFILTERBTNCLICK structure.
         Defined as NMHDFILTERBTNCLICK in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rc" offset="16" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMHDFILTERBTNCLICK )
   _XBST_NMHDR ( hdr  )
   _XBST_INT ( iItem  )
   _XBST_RECT ( rc  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMHEADER structure.
         Defined as NMHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="INT" name="iButton" offset="16" size="4" />
         <member type="POINTER32" name="pitem" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMHEADER )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_int ( iButton  )
   _XBST_POINTER32 ( pitem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMIPADDRESS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMIPADDRESS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMIPADDRESS structure.
         Defined as NMIPADDRESS in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iField" offset="12" size="4" />
         <member type="INT" name="iValue" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMIPADDRESS )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iField  )
   _XBST_int ( iValue  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_DELETEITEMSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_DELETEITEMSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi DELETEITEMSTRUCT structure.
         Defined as DELETEITEMSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="UINT" name="CtlType" offset="0" size="4" />
         <member type="UINT" name="CtlID" offset="4" size="4" />
         <member type="UINT" name="itemID" offset="8" size="4" />
         <member type="HWND" name="hwndItem" offset="12" size="4" />
         <member type="POINTER32" name="itemData" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( DELETEITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_UINT ( itemID  )
   _XBST_HWND ( hwndItem  )
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MCGRIDINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MCGRIDINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MCGRIDINFO structure.
         Defined as MCGRIDINFO in ot4xb_wapist_map.ch.
      </description>
      <size>84</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwPart" offset="4" size="4" />
         <member type="DWORD" name="dwFlags" offset="8" size="4" />
         <member type="INT" name="iCalendar" offset="12" size="4" />
         <member type="INT" name="iRow" offset="16" size="4" />
         <member type="INT" name="iCol" offset="20" size="4" />
         <member type="BOOL" name="bSelected" offset="24" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="stStart" offset="28" size="16" child="true" />
         <member type="WAPIST_SYSTEMTIME" name="stEnd" offset="44" size="16" child="true" />
         <member type="WAPIST_RECT" name="rc" offset="60" size="16" child="true" />
         <member type="POINTER32" name="pszName" offset="76" size="4" />
         <member type="DWORD" name="cchName" offset="80" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MCGRIDINFO )
   _XBST_UINT ( cbSize  )
   _XBST_DWORD ( dwPart  )
   _XBST_DWORD ( dwFlags  )
   _XBST_int ( iCalendar  )
   _XBST_int ( iRow  )
   _XBST_int ( iCol  )
   _XBST_BOOL ( bSelected  )
   _XBST_SYSTEMTIME ( stStart  )
   _XBST_SYSTEMTIME ( stEnd  )
   _XBST_RECT ( rc  )
   _XBST_POINTER32( pszName  )
   _XBST_DWORD( cchName  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MCHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MCHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MCHITTESTINFO structure.
         Defined as MCHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_POINT" name="pt" offset="4" size="8" child="true" />
         <member type="UINT" name="uHit" offset="12" size="4" />
         <member type="WAPIST_SYSTEMTIME" name="st" offset="16" size="16" child="true" />
         <member type="WAPIST_RECT" name="rc" offset="32" size="16" child="true" />
         <member type="INT" name="iOffset" offset="48" size="4" />
         <member type="INT" name="iRow" offset="52" size="4" />
         <member type="INT" name="iCol" offset="56" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MCHITTESTINFO )
   _XBST_UINT ( cbSize  )
   _XBST_POINT ( pt  )
   _XBST_UINT ( uHit  ) // out param
   _XBST_SYSTEMTIME ( st  )
   _XBST_RECT ( rc  )
   _XBST_int ( iOffset  )
   _XBST_int ( iRow  )
   _XBST_int ( iCol  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMDAYSTATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMDAYSTATE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMDAYSTATE structure.
         Defined as NMDAYSTATE in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="WAPIST_SYSTEMTIME" name="stStart" offset="12" size="16" child="true" />
         <member type="INT" name="cDayState" offset="28" size="4" />
         <member type="POINTER32" name="prgDayState" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMDAYSTATE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_SYSTEMTIME ( stStart  )
   _XBST_int ( cDayState  )
   _XBST_POINTER32( prgDayState  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMSELCHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMSELCHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMSELCHANGE structure.
         Defined as NMSELCHANGE in ot4xb_wapist_map.ch.
      </description>
      <size>44</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="WAPIST_SYSTEMTIME" name="stSelStart" offset="12" size="16" child="true" />
         <member type="WAPIST_SYSTEMTIME" name="stSelEnd" offset="28" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMSELCHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_SYSTEMTIME ( stSelStart  )
   _XBST_SYSTEMTIME ( stSelEnd  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMVIEWCHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMVIEWCHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMVIEWCHANGE structure.
         Defined as NMVIEWCHANGE in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwOldView" offset="12" size="4" />
         <member type="DWORD" name="dwNewView" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMVIEWCHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_DWORD ( dwOldView  )
   _XBST_DWORD ( dwNewView  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMPGCALCSIZE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMPGCALCSIZE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMPGCALCSIZE structure.
         Defined as NMPGCALCSIZE in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwFlag" offset="12" size="4" />
         <member type="INT" name="iWidth" offset="16" size="4" />
         <member type="INT" name="iHeight" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMPGCALCSIZE )
   _XBST_NMHDR ( hdr  )
   _XBST_DWORD ( dwFlag  )
   _XBST_int ( iWidth  )
   _XBST_int ( iHeight  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMPGHOTITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMPGHOTITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMPGHOTITEM structure.
         Defined as NMPGHOTITEM in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="idOld" offset="12" size="4" />
         <member type="INT" name="idNew" offset="16" size="4" />
         <member type="DWORD" name="dwFlags" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMPGHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( idOld  )
   _XBST_int ( idNew  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMPGSCROLL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMPGSCROLL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMPGSCROLL structure.
         Defined as NMPGSCROLL in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="BOOL" name="fwKeys" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rcParent" offset="16" size="16" child="true" />
         <member type="INT" name="iDir" offset="32" size="4" />
         <member type="INT" name="iXpos" offset="36" size="4" />
         <member type="INT" name="iYpos" offset="40" size="4" />
         <member type="INT" name="iScroll" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMPGSCROLL )
   _XBST_NMHDR ( hdr  )
   _XBST_BOOL ( fwKeys  )
   _XBST_RECT ( rcParent  )
   _XBST_int ( iDir  )
   _XBST_int ( iXpos  )
   _XBST_int ( iYpos  )
   _XBST_int ( iScroll  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PBRANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PBRANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi PBRANGE structure.
         Defined as PBRANGE in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="INT" name="iLow" offset="0" size="4" />
         <member type="INT" name="iHigh" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PBRANGE )
   _XBST_int ( iLow  )
   _XBST_int ( iHigh  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMREBARSPLITTER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMREBARSPLITTER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMREBARSPLITTER structure.
         Defined as NMREBARSPLITTER in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_RECT" name="rcSizing" offset="12" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMREBARSPLITTER )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcSizing  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SCROLLBARINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SCROLLBARINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SCROLLBARINFO structure.
         Defined as SCROLLBARINFO in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="WAPIST_RECT" name="rcScrollBar" offset="4" size="16" child="true" />
         <member type="INT" name="dxyLineButton" offset="20" size="4" />
         <member type="INT" name="xyThumbTop" offset="24" size="4" />
         <member type="INT" name="xyThumbBottom" offset="28" size="4" />
         <member type="INT" name="reserved" offset="32" size="4" />
         <member type="BINSTR" name="rgstate" size="24" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SCROLLBARINFO )
   _XBST_DWORD ( cbSize  )
   _XBST_RECT ( rcScrollBar  )
   _XBST_int ( dxyLineButton  )
   _XBST_int ( xyThumbTop  )
   _XBST_int ( xyThumbBottom  )
   _XBST_int ( reserved  )
   _XBST_BINSTR( rgstate , (sizeof(DWORD) * (CCHILDREN_SCROLLBAR+1) )  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SCROLLINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SCROLLINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi SCROLLINFO structure.
         Defined as SCROLLINFO in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="fMask" offset="4" size="4" />
         <member type="INT" name="nMin" offset="8" size="4" />
         <member type="INT" name="nMax" offset="12" size="4" />
         <member type="UINT" name="nPage" offset="16" size="4" />
         <member type="INT" name="nPos" offset="20" size="4" />
         <member type="INT" name="nTrackPos" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( SCROLLINFO )
   _XBST_UINT ( cbSize  )
   _XBST_UINT ( fMask  )
   _XBST_int  ( nMin  )
   _XBST_int  ( nMax  )
   _XBST_UINT ( nPage  )
   _XBST_int  ( nPos  )
   _XBST_int  ( nTrackPos  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_LHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_LHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi LHITTESTINFO structure.
         Defined as LHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>120</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="WAPIST_LITEM" name="item" offset="8" size="112" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( LHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMLINK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMLINK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMLINK structure.
         Defined as NMLINK in ot4xb_wapist_map.ch.
      </description>
      <size>124</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_LITEM" name="item" offset="12" size="112" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMLINK )
   _XBST_NMHDR ( hdr  )
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTCKEYDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTCKEYDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTCKEYDOWN structure.
         Defined as NMTCKEYDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>18</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WORD" name="wVKey" offset="12" size="2" />
         <member type="UINT" name="flags" offset="14" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTCKEYDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_WORD ( wVKey  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TCHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TCHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TCHITTESTINFO structure.
         Defined as TCHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="UINT" name="flags" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TCHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TCITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TCITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TCITEM structure.
         Defined as TCITEM in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="DWORD" name="dwState" offset="4" size="4" />
         <member type="DWORD" name="dwStateMask" offset="8" size="4" />
         <member type="LPSTR" name="pszText" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="INT" name="iImage" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TCITEM )
   _XBST_UINT ( mask  )
   _XBST_DWORD ( dwState  )
   _XBST_DWORD ( dwStateMask  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TCITEMHEADER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TCITEMHEADER</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TCITEMHEADER structure.
         Defined as TCITEMHEADER in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="UINT" name="lpReserved1" offset="4" size="4" />
         <member type="UINT" name="lpReserved2" offset="8" size="4" />
         <member type="LPSTR" name="pszText" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="INT" name="iImage" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TCITEMHEADER )
   _XBST_UINT ( mask  )
   _XBST_UINT ( lpReserved1  )
   _XBST_UINT ( lpReserved2  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COLORMAP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COLORMAP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COLORMAP structure.
         Defined as COLORMAP in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="COLORREF" name="from" offset="0" size="4" />
         <member type="COLORREF" name="to" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COLORMAP )
   _XBST_COLORREF ( from  )
   _XBST_COLORREF ( to  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBCUSTOMDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBCUSTOMDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBCUSTOMDRAW structure.
         Defined as NMTBCUSTOMDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>112</size>
      <members>
         <member type="WAPIST_NMCUSTOMDRAW" name="nmcd" offset="0" size="48" child="true" />
         <member type="HBRUSH" name="hbrMonoDither" offset="48" size="4" />
         <member type="HBRUSH" name="hbrLines" offset="52" size="4" />
         <member type="HPEN" name="hpenLines" offset="56" size="4" />
         <member type="COLORREF" name="clrText" offset="60" size="4" />
         <member type="COLORREF" name="clrMark" offset="64" size="4" />
         <member type="COLORREF" name="clrTextHighlight" offset="68" size="4" />
         <member type="COLORREF" name="clrBtnFace" offset="72" size="4" />
         <member type="COLORREF" name="clrBtnHighlight" offset="76" size="4" />
         <member type="COLORREF" name="clrHighlightHotTrack" offset="80" size="4" />
         <member type="WAPIST_RECT" name="rcText" offset="84" size="16" child="true" />
         <member type="INT" name="nStringBkMode" offset="100" size="4" />
         <member type="INT" name="nHLStringBkMode" offset="104" size="4" />
         <member type="INT" name="iListGap" offset="108" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW ( nmcd  )
   _XBST_HBRUSH ( hbrMonoDither  )
   _XBST_HBRUSH ( hbrLines  )
   _XBST_HPEN ( hpenLines  )
   _XBST_COLORREF ( clrText  )
   _XBST_COLORREF ( clrMark  )
   _XBST_COLORREF ( clrTextHighlight  )
   _XBST_COLORREF ( clrBtnFace  )
   _XBST_COLORREF ( clrBtnHighlight  )
   _XBST_COLORREF ( clrHighlightHotTrack  )
   _XBST_RECT ( rcText  )
   _XBST_int ( nStringBkMode  )
   _XBST_int ( nHLStringBkMode  )
   _XBST_int ( iListGap  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBDISPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBDISPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBDISPINFO structure.
         Defined as NMTBDISPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="DWORD" name="dwMask" offset="12" size="4" />
         <member type="INT" name="idCommand" offset="16" size="4" />
         <member type="POINTER32" name="lParam" offset="20" size="4" />
         <member type="INT" name="iImage" offset="24" size="4" />
         <member type="LPSTR" name="pszText" offset="28" size="4" />
         <member type="INT" name="cchText" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBDISPINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_DWORD ( dwMask  )
   _XBST_int ( idCommand  )
   _XBST_POINTER32 ( lParam  )
   _XBST_int ( iImage  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchText  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBGETINFOTIP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBGETINFOTIP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBGETINFOTIP structure.
         Defined as NMTBGETINFOTIP in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="pszText" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="INT" name="iItem" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBGETINFOTIP )
   _XBST_NMHDR ( hdr  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iItem  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBHOTITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBHOTITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBHOTITEM structure.
         Defined as NMTBHOTITEM in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="idOld" offset="12" size="4" />
         <member type="INT" name="idNew" offset="16" size="4" />
         <member type="DWORD" name="dwFlags" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( idOld  )
   _XBST_int ( idNew  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBRESTORE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBRESTORE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBRESTORE structure.
         Defined as NMTBRESTORE in ot4xb_wapist_map.ch.
      </description>
      <size>56</size>
      <members>
         <member type="WAPIST_NMHDR" name="nmhdr" offset="0" size="12" child="true" />
         <member type="POINTER32" name="pData" offset="12" size="4" />
         <member type="POINTER32" name="pCurrent" offset="16" size="4" />
         <member type="UINT" name="cbData" offset="20" size="4" />
         <member type="INT" name="iItem" offset="24" size="4" />
         <member type="INT" name="cButtons" offset="28" size="4" />
         <member type="INT" name="cbBytesPerRecord" offset="32" size="4" />
         <member type="WAPIST_TBBUTTON" name="tbButton" offset="36" size="20" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBRESTORE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_POINTER32 ( pData  )
   _XBST_POINTER32 ( pCurrent  )
   _XBST_UINT ( cbData  )
   _XBST_int ( iItem  )
   _XBST_int ( cButtons  )
   _XBST_int ( cbBytesPerRecord  )
   _XBST_TBBUTTON ( tbButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTBSAVE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTBSAVE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTBSAVE structure.
         Defined as NMTBSAVE in ot4xb_wapist_map.ch.
      </description>
      <size>52</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="POINTER32" name="pData" offset="12" size="4" />
         <member type="POINTER32" name="pCurrent" offset="16" size="4" />
         <member type="UINT" name="cbData" offset="20" size="4" />
         <member type="INT" name="iItem" offset="24" size="4" />
         <member type="INT" name="cButtons" offset="28" size="4" />
         <member type="WAPIST_TBBUTTON" name="tbButton" offset="32" size="20" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTBSAVE )
   _XBST_NMHDR ( hdr  )
   _XBST_POINTER32 ( pData  )
   _XBST_POINTER32 ( pCurrent  )
   _XBST_UINT ( cbData  )
   _XBST_int ( iItem  )
   _XBST_int ( cButtons  )
   _XBST_TBBUTTON ( tbButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTOOLBAR</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTOOLBAR</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTOOLBAR structure.
         Defined as NMTOOLBAR in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iItem" offset="12" size="4" />
         <member type="WAPIST_TBBUTTON" name="tbButton" offset="16" size="20" child="true" />
         <member type="INT" name="cchText" offset="36" size="4" />
         <member type="LPSTR" name="pszText" offset="40" size="4" />
         <member type="WAPIST_RECT" name="rcButton" offset="44" size="16" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTOOLBAR )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_TBBUTTON ( tbButton  )
   _XBST_int ( cchText  )
   _XBST_LPSTR ( pszText  )
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBADDBITMAP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBADDBITMAP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBADDBITMAP structure.
         Defined as TBADDBITMAP in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="HINSTANCE" name="hInst" offset="0" size="4" />
         <member type="POINTER32" name="nID" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBADDBITMAP )
   _XBST_HINSTANCE ( hInst  )
   _XBST_POINTER32 ( nID  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBBUTTONINFOA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBBUTTONINFOA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBBUTTONINFOA structure.
         Defined as TBBUTTONINFOA in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="INT" name="idCommand" offset="8" size="4" />
         <member type="INT" name="iImage" offset="12" size="4" />
         <member type="BYTE" name="fsState" offset="16" size="1" />
         <member type="BYTE" name="fsStyle" offset="17" size="1" />
         <member type="WORD" name="cx" offset="18" size="2" />
         <member type="POINTER32" name="lParam" offset="20" size="4" />
         <member type="LPSTR" name="pszText" offset="24" size="4" />
         <member type="INT" name="cchText" offset="28" size="4" />
         <member type="INT" name="iImageLabel" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBBUTTONINFOA )
   _XBST_UINT  ( cbSize  )
   _XBST_DWORD  ( dwMask  )
   _XBST_int  ( idCommand  )
   _XBST_int  ( iImage  )
   _XBST_BYTE  ( fsState  )
   _XBST_BYTE  ( fsStyle  )
   _XBST_WORD  ( cx  )
   _XBST_POINTER32  ( lParam  )
   _XBST_LPSTR  ( pszText  )
   _XBST_int  ( cchText  )
   _XBST_int  ( iImageLabel  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBINSERTMARK</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBINSERTMARK</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBINSERTMARK structure.
         Defined as TBINSERTMARK in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="INT" name="iButton" offset="0" size="4" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBINSERTMARK )
   _XBST_int ( iButton  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBMETRICS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBMETRICS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBMETRICS structure.
         Defined as TBMETRICS in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwMask" offset="4" size="4" />
         <member type="INT" name="cxPad" offset="8" size="4" />
         <member type="INT" name="cyPad" offset="12" size="4" />
         <member type="INT" name="cxBarPad" offset="16" size="4" />
         <member type="INT" name="cyBarPad" offset="20" size="4" />
         <member type="INT" name="cxButtonSpacing" offset="24" size="4" />
         <member type="INT" name="cyButtonSpacing" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBMETRICS )
   _XBST_UINT ( cbSize  )
   _XBST_DWORD ( dwMask  )
   _XBST_int ( cxPad  )
   _XBST_int ( cyPad  )
   _XBST_int ( cxBarPad  )
   _XBST_int ( cyBarPad  )
   _XBST_int ( cxButtonSpacing  )
   _XBST_int ( cyButtonSpacing  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBREPLACEBITMAP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBREPLACEBITMAP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBREPLACEBITMAP structure.
         Defined as TBREPLACEBITMAP in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="HINSTANCE" name="hInstOld" offset="0" size="4" />
         <member type="POINTER32" name="nIDOld" offset="4" size="4" />
         <member type="HINSTANCE" name="hInstNew" offset="8" size="4" />
         <member type="POINTER32" name="nIDNew" offset="12" size="4" />
         <member type="INT" name="nButtons" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBREPLACEBITMAP )
   _XBST_HINSTANCE ( hInstOld  )
   _XBST_POINTER32 ( nIDOld  )
   _XBST_HINSTANCE ( hInstNew  )
   _XBST_POINTER32 ( nIDNew  )
   _XBST_int ( nButtons  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TBSAVEPARAMS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TBSAVEPARAMS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TBSAVEPARAMS structure.
         Defined as TBSAVEPARAMS in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HANDLE" name="hkr" offset="0" size="4" />
         <member type="LPSTR" name="pszSubKey" offset="4" size="4" />
         <member type="LPSTR" name="pszValueName" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TBSAVEPARAMS )
   _XBST_HANDLE ( hkr  )
   _XBST_LPSTR ( pszSubKey  )
   _XBST_LPSTR ( pszValueName  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTTCUSTOMDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTTCUSTOMDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTTCUSTOMDRAW structure.
         Defined as NMTTCUSTOMDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>52</size>
      <members>
         <member type="WAPIST_NMCUSTOMDRAW" name="nmcd" offset="0" size="48" child="true" />
         <member type="UINT" name="uDrawFlags" offset="48" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTTCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW ( nmcd  )
   _XBST_UINT ( uDrawFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTTDISPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTTDISPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTTDISPINFO structure.
         Defined as NMTTDISPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="lpszText" offset="12" size="4" />
         <member type="HINSTANCE" name="hinst" offset="16" size="4" />
         <member type="UINT" name="uFlags" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
         <member type="HBITMAP" name="hbmp" offset="28" size="4" />
         <member type="BYTE" name="szText" size="80" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTTDISPINFO )
   _XBST_NMHDR      ( hdr  )
   _XBST_LPSTR     ( lpszText  )
   _XBST_TCHAR       ( szText[80]  )
   _XBST_HINSTANCE  ( hinst  )
   _XBST_UINT       ( uFlags  )
   _XBST_LPARAM     ( lParam  )
   _XBST_HBITMAP ( hbmp  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TOOLINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TOOLINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TOOLINFO structure.
         Defined as TOOLINFO in ot4xb_wapist_map.ch.
      </description>
      <size>48</size>
      <members>
         <member type="UINT" name="cbSize" offset="0" size="4" />
         <member type="UINT" name="uFlags" offset="4" size="4" />
         <member type="HWND" name="hwnd" offset="8" size="4" />
         <member type="POINTER32" name="uId" offset="12" size="4" />
         <member type="WAPIST_RECT" name="rect" offset="16" size="16" child="true" />
         <member type="HINSTANCE" name="hinst" offset="32" size="4" />
         <member type="LPSTR" name="lpszText" offset="36" size="4" />
         <member type="LPARAM" name="lParam" offset="40" size="4" />
         <member type="POINTER32" name="lpReserved" offset="44" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TOOLINFO )
   _XBST_UINT      ( cbSize  )
   _XBST_UINT      ( uFlags  )
   _XBST_HWND      ( hwnd  )
   _XBST_POINTER32  ( uId  )
   _XBST_RECT      ( rect  )
   _XBST_HINSTANCE ( hinst  )
   _XBST_LPSTR    ( lpszText  )
   _XBST_LPARAM ( lParam  )
   _XBST_POINTER32 ( lpReserved  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TTGETTITLE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TTGETTITLE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TTGETTITLE structure.
         Defined as TTGETTITLE in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="dwSize" offset="0" size="4" />
         <member type="UINT" name="uTitleBitmap" offset="4" size="4" />
         <member type="UINT" name="cch" offset="8" size="4" />
         <member type="POINTER32" name="pszTitle" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TTGETTITLE )
   _XBST_DWORD ( dwSize  )
   _XBST_UINT ( uTitleBitmap  )
   _XBST_UINT ( cch  )
   _XBST_POINTER32 ( pszTitle  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TTHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TTHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TTHITTESTINFO structure.
         Defined as TTHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="HWND" name="hwnd" offset="0" size="4" />
         <member type="WAPIST_POINT" name="pt" offset="4" size="8" child="true" />
         <member type="WAPIST_TOOLINFO" name="ti" offset="12" size="48" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TTHITTESTINFO )
   _XBST_HWND ( hwnd  )
   _XBST_POINT ( pt  )
   _XBST_TOOLINFO ( ti  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTREEVIEW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTREEVIEW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTREEVIEW structure.
         Defined as NMTREEVIEW in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="action" offset="12" size="4" />
         <member type="WAPIST_TVITEM" name="itemOld" offset="16" size="?" child="true" />
         <member type="WAPIST_TVITEM" name="itemNew" offset="16" size="?" child="true" />
         <member type="WAPIST_POINT" name="ptDrag" offset="16" size="8" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTREEVIEW )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( action  )
   _XBST_TVITEM ( itemOld  )
   _XBST_TVITEM ( itemNew  )
   _XBST_POINT ( ptDrag  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVASYNCDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVASYNCDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVASYNCDRAW structure.
         Defined as NMTVASYNCDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>36</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="POINTER32" name="pimldp" offset="12" size="4" />
         <member type="HRESULT" name="hr" offset="16" size="4" />
         <member type="HANDLE" name="hItem" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
         <member type="DWORD" name="dwRetFlags" offset="28" size="4" />
         <member type="INT" name="iRetImageIndex" offset="32" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVASYNCDRAW )
   _XBST_NMHDR ( hdr  )
   _XBST_POINTER32 ( pimldp  )
   _XBST_HRESULT ( hr  )
   _XBST_HANDLE ( hItem  )
   _XBST_LPARAM ( lParam  )
   _XBST_DWORD ( dwRetFlags  )
   _XBST_int ( iRetImageIndex  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVCUSTOMDRAW</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVCUSTOMDRAW</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVCUSTOMDRAW structure.
         Defined as NMTVCUSTOMDRAW in ot4xb_wapist_map.ch.
      </description>
      <size>60</size>
      <members>
         <member type="WAPIST_NMCUSTOMDRAW" name="nmcd" offset="0" size="48" child="true" />
         <member type="COLORREF" name="clrText" offset="48" size="4" />
         <member type="COLORREF" name="clrTextBk" offset="52" size="4" />
         <member type="INT" name="iLevel" offset="56" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW ( nmcd  )
   _XBST_COLORREF ( clrText  )
   _XBST_COLORREF ( clrTextBk  )
   _XBST_int ( iLevel  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVDISPINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVDISPINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVDISPINFO structure.
         Defined as NMTVDISPINFO in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_TVITEM" name="item" offset="12" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVDISPINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_TVITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVDISPINFOEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVDISPINFOEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVDISPINFOEX structure.
         Defined as NMTVDISPINFOEX in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WAPIST_TVITEMEX" name="item" offset="12" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVDISPINFOEX )
   _XBST_NMHDR ( hdr  )
   _XBST_TVITEMEX ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVGETINFOTIP</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVGETINFOTIP</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVGETINFOTIP structure.
         Defined as NMTVGETINFOTIP in ot4xb_wapist_map.ch.
      </description>
      <size>28</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="LPSTR" name="pszText" offset="12" size="4" />
         <member type="INT" name="cchTextMax" offset="16" size="4" />
         <member type="HANDLE" name="hItem" offset="20" size="4" />
         <member type="LPARAM" name="lParam" offset="24" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVGETINFOTIP )
   _XBST_NMHDR ( hdr  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_HANDLE ( hItem  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVITEMCHANGE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVITEMCHANGE</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVITEMCHANGE structure.
         Defined as NMTVITEMCHANGE in ot4xb_wapist_map.ch.
      </description>
      <size>32</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="UINT" name="uChanged" offset="12" size="4" />
         <member type="HANDLE" name="hItem" offset="16" size="4" />
         <member type="UINT" name="uStateNew" offset="20" size="4" />
         <member type="UINT" name="uStateOld" offset="24" size="4" />
         <member type="LPARAM" name="lParam" offset="28" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVITEMCHANGE )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( uChanged  )
   _XBST_HANDLE ( hItem  )
   _XBST_UINT ( uStateNew  )
   _XBST_UINT ( uStateOld  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVKEYDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVKEYDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVKEYDOWN structure.
         Defined as NMTVKEYDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>18</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="WORD" name="wVKey" offset="12" size="2" />
         <member type="UINT" name="flags" offset="14" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVKEYDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_WORD ( wVKey  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMTVSTATEIMAGECHANGING</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMTVSTATEIMAGECHANGING</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMTVSTATEIMAGECHANGING structure.
         Defined as NMTVSTATEIMAGECHANGING in ot4xb_wapist_map.ch.
      </description>
      <size>24</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="HANDLE" name="hti" offset="12" size="4" />
         <member type="INT" name="iOldStateImageIndex" offset="16" size="4" />
         <member type="INT" name="iNewStateImageIndex" offset="20" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMTVSTATEIMAGECHANGING )
   _XBST_NMHDR ( hdr  )
   _XBST_HANDLE ( hti  )
   _XBST_int ( iOldStateImageIndex  )
   _XBST_int ( iNewStateImageIndex  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVGETITEMPARTRECTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVGETITEMPARTRECTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVGETITEMPARTRECTINFO structure.
         Defined as TVGETITEMPARTRECTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HANDLE" name="hti" offset="0" size="4" />
         <member type="POINTER32" name="prc" offset="4" size="4" />
         <member type="INT" name="partID" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TVGETITEMPARTRECTINFO )
   _XBST_HANDLE ( hti  )
   _XBST_POINTER32 ( prc  )
   _XBST_int ( partID  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVHITTESTINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVHITTESTINFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVHITTESTINFO structure.
         Defined as TVHITTESTINFO in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="WAPIST_POINT" name="pt" offset="0" size="8" child="true" />
         <member type="UINT" name="flags" offset="8" size="4" />
         <member type="HANDLE" name="hItem" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TVHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
   _XBST_HANDLE ( hItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVINSERTSTRUCT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVINSERTSTRUCT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVINSERTSTRUCTA structure.
         Defined as TVINSERTSTRUCT in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvinsertstructa</ref-url>
      <size>64</size>
      <members>
         <member type="HANDLE" name="hParent" offset="0" size="4" />
         <member type="HANDLE" name="hInsertAfter" offset="4" size="4" />
         <union offset="8" size="56">
            <member type="WAPIST_TVITEMEX" name="itemex" offset="8" size="56" child="true" />
            <member type="WAPIST_TVITEM" name="item" offset="8" size="40" child="true" />
         </union>
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TVINSERTSTRUCT )
   _XBST_HANDLE ( hParent  )
   _XBST_HANDLE ( hInsertAfter  )
pc->GwstBeginUnion();
   _XBST_TVITEMEX ( itemex  )
   _XBST_TVITEM ( item  )
pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVITEM</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVITEM</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVITEM structure.
         Defined as TVITEM in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvitema</ref-url>
      <size>40</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="HANDLE" name="hItem" offset="4" size="4" />
         <member type="UINT" name="state" offset="8" size="4" />
         <member type="UINT" name="stateMask" offset="12" size="4" />
         <member type="LPSTR" name="pszText" offset="16" size="4" />
         <member type="INT" name="cchTextMax" offset="20" size="4" />
         <member type="INT" name="iImage" offset="24" size="4" />
         <member type="INT" name="iSelectedImage" offset="28" size="4" />
         <member type="INT" name="cChildren" offset="32" size="4" />
         <member type="LPARAM" name="lParam" offset="36" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cText" target="pszText" offset="16" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TVITEM )
   _XBST_UINT ( mask  )
   _XBST_HANDLE ( hItem  )
   _XBST_UINT ( state  )
   _XBST_UINT ( stateMask  )
   _XBST_LPSTR_DYNSZ ( pszText  , cText )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
   _XBST_int ( iSelectedImage  )
   _XBST_int ( cChildren  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVITEMEX</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVITEMEX</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVITEMEX structure.
         Defined as TVITEMEX in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvitemexa</ref-url>
      <size>56</size>
      <members>
         <member type="UINT" name="mask" offset="0" size="4" />
         <member type="HANDLE" name="hItem" offset="4" size="4" />
         <member type="UINT" name="state" offset="8" size="4" />
         <member type="UINT" name="stateMask" offset="12" size="4" />
         <member type="LPSTR" name="pszText" offset="16" size="4" />
         <member type="INT" name="cchTextMax" offset="20" size="4" />
         <member type="INT" name="iImage" offset="24" size="4" />
         <member type="INT" name="iSelectedImage" offset="28" size="4" />
         <member type="INT" name="cChildren" offset="32" size="4" />
         <member type="LPARAM" name="lParam" offset="36" size="4" />
         <member type="INT" name="iIntegral" offset="40" size="4" />
         <member type="UINT" name="uStateEx" offset="44" size="4" />
         <member type="HWND" name="hwnd" offset="48" size="4" />
         <member type="INT" name="iExpandedImage" offset="52" size="4" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cText" target="pszText" offset="16" size="4" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/`r`nXB_BEGIN_STRUCTURE( TVITEMEX )
   _XBST_UINT      ( mask  )
   _XBST_HANDLE ( hItem  )
   _XBST_UINT      ( state  )
   _XBST_UINT      ( stateMask  )
   _XBST_LPSTR_DYNSZ ( pszText  , cText )
   _XBST_int       ( cchTextMax  )
   _XBST_int       ( iImage  )
   _XBST_int       ( iSelectedImage  )
   _XBST_int       ( cChildren  )
   _XBST_LPARAM    ( lParam  )
   _XBST_int       ( iIntegral  )
   _XBST_UINT      ( uStateEx  )
   _XBST_HWND      ( hwnd  )
   _XBST_int       ( iExpandedImage  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TVSORTCB</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TVSORTCB</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TVSORTCB structure.
         Defined as TVSORTCB in ot4xb_wapist_map.ch.
      </description>
      <size>12</size>
      <members>
         <member type="HANDLE" name="hParent" offset="0" size="4" />
         <member type="POINTER32" name="lpfnCompare" offset="4" size="4" />
         <member type="LPARAM" name="lParam" offset="8" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( TVSORTCB )
   _XBST_HANDLE ( hParent  )
   _XBST_POINTER32 ( lpfnCompare  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_NMUPDOWN</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_NMUPDOWN</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi NMUPDOWN structure.
         Defined as NMUPDOWN in ot4xb_wapist_map.ch.
      </description>
      <size>20</size>
      <members>
         <member type="WAPIST_NMHDR" name="hdr" offset="0" size="12" child="true" />
         <member type="INT" name="iPos" offset="12" size="4" />
         <member type="INT" name="iDelta" offset="16" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( NMUPDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iPos  )
   _XBST_int ( iDelta  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_UDACCEL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_UDACCEL</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi UDACCEL structure.
         Defined as UDACCEL in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="UINT" name="nSec" offset="0" size="4" />
         <member type="UINT" name="nInc" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( UDACCEL )
   _XBST_UINT ( nSec  )
   _XBST_UINT ( nInc  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_URL_COMPONENTS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_URL_COMPONENTS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi URL_COMPONENTSA structure.
         Defined as URL_COMPONENTS in ot4xb_wapist_map.ch.
      </description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-url_componentsa</ref-url>
      <size>60</size>
      <members>
         <member type="DWORD" name="dwStructSize" offset="0" size="4" />
         <member type="LPSTR" name="lpszScheme" offset="4" size="4" />
         <member type="DWORD" name="dwSchemeLength" offset="8" size="4" />
         <member type="INT" name="nScheme" offset="12" size="4" />
         <member type="LPSTR" name="lpszHostName" offset="16" size="4" />
         <member type="DWORD" name="dwHostNameLength" offset="20" size="4" />
         <member type="WORD" name="nPort" offset="24" size="2" />
         <member type="LPSTR" name="lpszUserName" offset="28" size="4" />
         <member type="DWORD" name="dwUserNameLength" offset="32" size="4" />
         <member type="LPSTR" name="lpszPassword" offset="36" size="4" />
         <member type="DWORD" name="dwPasswordLength" offset="40" size="4" />
         <member type="LPSTR" name="lpszUrlPath" offset="44" size="4" />
         <member type="DWORD" name="dwUrlPathLength" offset="48" size="4" />
         <member type="LPSTR" name="lpszExtraInfo" offset="52" size="4" />
         <member type="DWORD" name="dwExtraInfoLength" offset="56" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( URL_COMPONENTS )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwStructSize      ));  _XBST_DWORD( dwStructSize       )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszScheme        ));  _XBST_LPSTR( lpszScheme         )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwSchemeLength    ));  _XBST_DWORD( dwSchemeLength     )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , nScheme           ));  _XBST_int  ( nScheme            )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszHostName      ));  _XBST_LPSTR( lpszHostName       )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwHostNameLength  ));  _XBST_DWORD( dwHostNameLength   )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , nPort             ));  _XBST_WORD ( nPort              )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszUserName      ));  _XBST_LPSTR( lpszUserName       )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwUserNameLength  ));  _XBST_DWORD( dwUserNameLength   )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszPassword      ));  _XBST_LPSTR( lpszPassword       )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwPasswordLength  ));  _XBST_DWORD( dwPasswordLength   )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszUrlPath       ));  _XBST_LPSTR( lpszUrlPath        )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwUrlPathLength   ));  _XBST_DWORD( dwUrlPathLength    )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszExtraInfo     ));  _XBST_LPSTR( lpszExtraInfo      )
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwExtraInfoLength ));  _XBST_DWORD( dwExtraInfoLength  )
pc->GwstSetOffset(sizeof( URL_COMPONENTS) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_ASYNC_RESULT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_ASYNC_RESULT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNET_ASYNC_RESULT structure.
         Defined as INTERNET_ASYNC_RESULT in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwResult" offset="0" size="4" />
         <member type="DWORD" name="dwError" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_ASYNC_RESULT )
   _XBST_DWORD( dwResult );
   _XBST_DWORD( dwError  );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_DIAGNOSTIC_SOCKET_INFO structure.</description>
      <members>
         <member type="DWORD" name="Socket" />
         <member type="DWORD" name="SourcePort" />
         <member type="DWORD" name="DestPort" />
         <member type="DWORD" name="Flags" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_DIAGNOSTIC_SOCKET_INFO )
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Socket    )); _XBST_DWORD( Socket      );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,SourcePort)); _XBST_DWORD( SourcePort  );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,DestPort  )); _XBST_DWORD( DestPort    );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Flags     )); _XBST_DWORD( Flags       );
   pc->GwstSetOffset(sizeof(INTERNET_DIAGNOSTIC_SOCKET_INFO));
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_PROXY_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_PROXY_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_PROXY_INFO structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_proxy_info</ref-url>
      <members>
         <member type="DWORD" name="dwAccessType" />
         <member type="LPSTR" name="lpszProxy" />
         <member type="LPSTR" name="lpszProxyBypass" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cProxy" target="lpszProxy" access="string" />
         <helper type="DYNSZ" name="cProxyBypass" target="lpszProxyBypass" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_PROXY_INFO )
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,dwAccessType   )); _XBST_DWORD      ( dwAccessType                 );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxy      )); _XBST_LPSTR_DYNSZ( lpszProxy      , cProxy      );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxyBypass)); _XBST_LPSTR_DYNSZ( lpszProxyBypass, cProxyBypass);
   pc->GwstSetOffset(sizeof(INTERNET_PROXY_INFO));
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_PER_CONN_OPTION___VALUE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_PER_CONN_OPTION___VALUE</source>
      <category>winapi/structures</category>
      <description>Auxiliary wrapper for the INTERNET_PER_CONN_OPTION Value union.</description>
      <members>
         <union name="Value">
            <member type="DWORD" name="dwValue" />
            <member type="LPSTR" name="pszValue" />
            <member type="WAPIST_FILETIME" name="ftValue" child="true" />
         </union>
      </members>
      <ot4xb-helpers><helper type="DYNSZ" name="cValue" target="pszValue" access="string" /></ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION___VALUE )
   _XBST_DWORD        ( dwValue   );
   _XBST_LPSTR_DYNSZ  ( pszValue  , cValue );
   _XBST_FILETIME     ( ftValue   );
   pc->GwstSetOffset( RTL_FIELD_SIZE(INTERNET_PER_CONN_OPTION, Value) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_PER_CONN_OPTION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_PER_CONN_OPTION</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_PER_CONN_OPTIONA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_per_conn_optiona</ref-url>
      <members>
         <member type="DWORD" name="dwOption" />
         <member type="WAPIST_INTERNET_PER_CONN_OPTION___VALUE" name="Value" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION )
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,dwOption));   _XBST_DWORD(                            dwOption            );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,Value   ));   _XBST_INTERNET_PER_CONN_OPTION___VALUE( Value               );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_PER_CONN_OPTION_LIST</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_PER_CONN_OPTION_LIST</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_PER_CONN_OPTION_LISTA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_per_conn_option_lista</ref-url>
      <members>
         <member type="DWORD" name="dwSize" />
         <member type="LPSTR" name="pszConnection" />
         <member type="DWORD" name="dwOptionCount" />
         <member type="DWORD" name="dwOptionError" />
         <member type="POINTER32" name="pOptions" />
      </members>
      <ot4xb-helpers><helper type="DYNSZ" name="cConnection" target="pszConnection" access="string" /></ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION_LIST )
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwSize        )); _XBST_DWORD     ( dwSize        );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pszConnection )); _XBST_LPSTR_DYNSZ( pszConnection , cConnection);
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionCount )); _XBST_DWORD     ( dwOptionCount );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionError )); _XBST_DWORD     ( dwOptionError );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pOptions      )); _XBST_POINTER32 ( pOptions      );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION_LIST) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_VERSION_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_VERSION_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNET_VERSION_INFO structure.
         Defined as INTERNET_VERSION_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwMajorVersion" offset="0" size="4" />
         <member type="DWORD" name="dwMinorVersion" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_VERSION_INFO )
   _XBST_DWORD ( dwMajorVersion  )
   _XBST_DWORD ( dwMinorVersion  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_HTTP_VERSION_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_HTTP_VERSION_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi HTTP_VERSION_INFO structure.
         Defined as HTTP_VERSION_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwMajorVersion" offset="0" size="4" />
         <member type="DWORD" name="dwMinorVersion" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( HTTP_VERSION_INFO )
   _XBST_DWORD( dwMajorVersion )
   _XBST_DWORD( dwMinorVersion )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_CONNECTED_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_CONNECTED_INFO</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNET_CONNECTED_INFO structure.
         Defined as INTERNET_CONNECTED_INFO in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwConnectedState" offset="0" size="4" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_CONNECTED_INFO )
   _XBST_DWORD( dwConnectedState )
   _XBST_DWORD( dwFlags          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_CERTIFICATE_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_CERTIFICATE_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_CERTIFICATE_INFO structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_certificate_info</ref-url>
      <members>
         <member type="WAPIST_FILETIME" name="ftExpiry" child="true" />
         <member type="WAPIST_FILETIME" name="ftStart" child="true" />
         <member type="LPSTR" name="lpszSubjectInfo" />
         <member type="LPSTR" name="lpszIssuerInfo" />
         <member type="LPSTR" name="lpszProtocolName" />
         <member type="LPSTR" name="lpszSignatureAlgName" />
         <member type="LPSTR" name="lpszEncryptionAlgName" />
         <member type="DWORD" name="dwKeySize" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_CERTIFICATE_INFO )
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , ftExpiry               ));_XBST_FILETIME ( ftExpiry               );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , ftStart                ));_XBST_FILETIME ( ftStart                );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszSubjectInfo        ));_XBST_LPSTR   ( lpszSubjectInfo        );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszIssuerInfo         ));_XBST_LPSTR   ( lpszIssuerInfo         );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszProtocolName       ));_XBST_LPSTR   ( lpszProtocolName       );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszSignatureAlgName   ));_XBST_LPSTR   ( lpszSignatureAlgName   );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszEncryptionAlgName  ));_XBST_LPSTR   ( lpszEncryptionAlgName  );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , dwKeySize              ));_XBST_DWORD    ( dwKeySize              );
   pc->GwstSetOffset( sizeof( INTERNET_CERTIFICATE_INFO) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_BUFFERS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_BUFFERS</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_BUFFERSA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_buffersa</ref-url>
      <members>
         <member type="DWORD" name="dwStructSize" />
         <member type="POINTER32" name="pNext" />
         <member type="LPSTR" name="lpcszHeader" />
         <member type="DWORD" name="dwHeadersLength" />
         <member type="DWORD" name="dwHeadersTotal" />
         <member type="LPVOID" name="lpvBuffer" />
         <member type="DWORD" name="dwBufferLength" />
         <member type="DWORD" name="dwBufferTotal" />
         <member type="DWORD" name="dwOffsetLow" />
         <member type="DWORD" name="dwOffsetHigh" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_BUFFERS )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwStructSize      ));   _XBST_DWORD      ( dwStructSize      );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , Next              ));   _XBST_POINTER32  ( pNext             );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , lpcszHeader       ));   _XBST_LPSTR     ( lpcszHeader       );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwHeadersLength   ));   _XBST_DWORD      ( dwHeadersLength   );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwHeadersTotal    ));   _XBST_DWORD      ( dwHeadersTotal    );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , lpvBuffer         ));   _XBST_LPVOID     ( lpvBuffer         );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwBufferLength    ));   _XBST_DWORD      ( dwBufferLength    );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwBufferTotal     ));   _XBST_DWORD      ( dwBufferTotal     );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwOffsetLow       ));   _XBST_DWORD      ( dwOffsetLow       );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwOffsetHigh      ));   _XBST_DWORD      ( dwOffsetHigh      );
   pc->GwstSetOffset( sizeof( INTERNET_BUFFERS) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INCOMINGCOOKIESTATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INCOMINGCOOKIESTATE</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet IncomingCookieState structure.</description>
      <members>
         <member type="INT" name="cSession" />
         <member type="INT" name="cPersistent" />
         <member type="INT" name="cAccepted" />
         <member type="INT" name="cLeashed" />
         <member type="INT" name="cDowngraded" />
         <member type="INT" name="cBlocked" />
         <member type="LPSTR" name="pszLocation" />
      </members>
      <ot4xb-helpers><helper type="DYNSZ" name="cLocation" target="pszLocation" access="string" /></ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INCOMINGCOOKIESTATE )
    _XBST_int( cSession      );
   _XBST_int   ( cPersistent   );
   _XBST_int   ( cAccepted     );
   _XBST_int   ( cLeashed      );
   _XBST_int   ( cDowngraded   );
   _XBST_int   ( cBlocked      );
   _XBST_LPSTR_DYNSZ ( pszLocation   , cLocation);
   pc->GwstSetOffset( sizeof( IncomingCookieState) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_OUTGOINGCOOKIESTATE</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_OUTGOINGCOOKIESTATE</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet OutgoingCookieState structure.</description>
      <members>
         <member type="INT" name="cSent" />
         <member type="INT" name="cSuppressed" />
         <member type="LPSTR" name="pszLocation" />
      </members>
      <ot4xb-helpers><helper type="DYNSZ" name="cLocation" target="pszLocation" access="string" /></ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( OUTGOINGCOOKIESTATE  )
   _XBST_int   ( cSent         )
   _XBST_int   ( cSuppressed   )
   _XBST_LPSTR_DYNSZ ( pszLocation  , cLocation )
   pc->GwstSetOffset( sizeof( OutgoingCookieState) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNETCOOKIEHISTORY</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNETCOOKIEHISTORY</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNETCOOKIEHISTORY structure.
         Defined as INTERNETCOOKIEHISTORY in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="BOOL" name="fAccepted" offset="0" size="4" />
         <member type="BOOL" name="fLeashed" offset="4" size="4" />
         <member type="BOOL" name="fDowngraded" offset="8" size="4" />
         <member type="BOOL" name="fRejected" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNETCOOKIEHISTORY )
   _XBST_BOOL ( fAccepted    );
   _XBST_BOOL ( fLeashed     );
   _XBST_BOOL ( fDowngraded  );
   _XBST_BOOL ( fRejected    );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_COOKIEDECISION</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_COOKIEDECISION</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi COOKIEDECISION structure.
         Defined as COOKIEDECISION in ot4xb_wapist_map.ch.
      </description>
      <size>8</size>
      <members>
         <member type="DWORD" name="dwCookieState" offset="0" size="4" />
         <member type="BOOL" name="fAllowSession" offset="4" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( COOKIEDECISION         )
   _XBST_DWORD ( dwCookieState  )
   _XBST_BOOL  ( fAllowSession  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_AUTH_NOTIFY_DATA</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_AUTH_NOTIFY_DATA</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNET_AUTH_NOTIFY_DATA structure.
         Defined as INTERNET_AUTH_NOTIFY_DATA in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="cbStruct" offset="0" size="4" />
         <member type="DWORD" name="dwOptions" offset="4" size="4" />
         <member type="DWORD" name="pfnNotify" offset="8" size="4" />
         <member type="DWORD" name="dwContext" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_AUTH_NOTIFY_DATA   )
   _XBST_DWORD ( cbStruct    )
   _XBST_DWORD ( dwOptions   )
   _XBST_DWORD ( pfnNotify   )
   _XBST_DWORD ( dwContext   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_CACHE_ENTRY_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_CACHE_ENTRY_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_CACHE_ENTRY_INFOA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_cache_entry_infoa</ref-url>
      <members>
         <member type="DWORD" name="dwStructSize" />
         <member type="LPSTR" name="lpszSourceUrlName" />
         <member type="LPSTR" name="lpszLocalFileName" />
         <member type="DWORD" name="CacheEntryType" />
         <member type="DWORD" name="dwUseCount" />
         <member type="DWORD" name="dwHitRate" />
         <member type="DWORD" name="dwSizeLow" />
         <member type="DWORD" name="dwSizeHigh" />
         <member type="WAPIST_FILETIME" name="LastModifiedTime" child="true" />
         <member type="WAPIST_FILETIME" name="ExpireTime" child="true" />
         <member type="WAPIST_FILETIME" name="LastAccessTime" child="true" />
         <member type="WAPIST_FILETIME" name="LastSyncTime" child="true" />
         <member type="LPSTR" name="lpHeaderInfo" />
         <member type="DWORD" name="dwHeaderInfoSize" />
         <member type="LPSTR" name="lpszFileExtension" />
         <union>
            <member type="DWORD" name="dwReserved" />
            <member type="DWORD" name="dwExemptDelta" />
         </union>
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cSourceUrlName" target="lpszSourceUrlName" access="string" />
         <helper type="DYNSZ" name="cLocalFileName" target="lpszLocalFileName" access="string" />
         <helper type="DYNSZ" name="cHeaderInfo" target="lpHeaderInfo" access="string" />
         <helper type="DYNSZ" name="cFileExtension" target="lpszFileExtension" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_ENTRY_INFO )

   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwStructSize      ));_XBST_DWORD    ( dwStructSize      );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_CACHE_ENTRY_INFO, lpszSourceUrlName));
   pc->Member_lpStr("lpszSourceUrlName");
   pc->GwstBack();
   pc->Member_DynSz("cSourceUrlName");
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpszLocalFileName ));_XBST_LPSTR_DYNSZ    ( lpszLocalFileName , cLocalFileName);
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , CacheEntryType    ));_XBST_DWORD    ( CacheEntryType    );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwUseCount        ));_XBST_DWORD    ( dwUseCount        );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwHitRate         ));_XBST_DWORD    ( dwHitRate         );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwSizeLow         ));_XBST_DWORD    ( dwSizeLow         );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwSizeHigh        ));_XBST_DWORD    ( dwSizeHigh        );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastModifiedTime  ));_XBST_FILETIME ( LastModifiedTime  );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , ExpireTime        ));_XBST_FILETIME ( ExpireTime        );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastAccessTime    ));_XBST_FILETIME ( LastAccessTime    );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastSyncTime      ));_XBST_FILETIME ( LastSyncTime      );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpHeaderInfo      ));_XBST_LPSTR_DYNSZ ( lpHeaderInfo  , cHeaderInfo );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwHeaderInfoSize  ));_XBST_DWORD    ( dwHeaderInfoSize  );
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpszFileExtension ));_XBST_LPSTR_DYNSZ  ( lpszFileExtension , cFileExtension);
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwReserved        ));_XBST_DWORD( dwReserved    );// Anonymous UNION
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwExemptDelta     ));_XBST_DWORD( dwExemptDelta );// Anonymous UNION
   pc->GwstSetOffset( sizeof( INTERNET_CACHE_ENTRY_INFO) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_CACHE_TIMESTAMPS</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_CACHE_TIMESTAMPS</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi INTERNET_CACHE_TIMESTAMPS structure.
         Defined as INTERNET_CACHE_TIMESTAMPS in ot4xb_wapist_map.ch.
      </description>
      <size>0</size>
      <members>
         <member type="WAPIST_FILETIME" name="ftExpires" offset="0" size="?" child="true" />
         <member type="WAPIST_FILETIME" name="ftLastModified" offset="0" size="?" child="true" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_TIMESTAMPS  )
   _XBST_FILETIME(  ftExpires      );
   _XBST_FILETIME(  ftLastModified );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_INTERNET_CACHE_GROUP_INFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_INTERNET_CACHE_GROUP_INFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet INTERNET_CACHE_GROUP_INFOA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_cache_group_infoa</ref-url>
      <members>
         <member type="DWORD" name="dwGroupSize" />
         <member type="DWORD" name="dwGroupFlags" />
         <member type="DWORD" name="dwGroupType" />
         <member type="DWORD" name="dwDiskUsage" />
         <member type="DWORD" name="dwDiskQuota" />
         <member type="BINSTR" name="dwOwnerStorage_bytes" size="16" />
         <member type="DWORD" name="dwOwnerStorage_0" />
         <member type="DWORD" name="dwOwnerStorage_1" />
         <member type="DWORD" name="dwOwnerStorage_2" />
         <member type="DWORD" name="dwOwnerStorage_3" />
         <member type="SZSTR" name="szGroupName" size="120" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_GROUP_INFO   )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupSize  ));  _XBST_DWORD(  dwGroupSize  )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupFlags ));  _XBST_DWORD(  dwGroupFlags )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupType  ));  _XBST_DWORD(  dwGroupType  )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwDiskUsage  ));  _XBST_DWORD(  dwDiskUsage  )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwDiskQuota  ));  _XBST_DWORD(  dwDiskQuota  )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwOwnerStorage)); _XBST_BINSTR(dwOwnerStorage_bytes, 16);
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwOwnerStorage));
   _XBST_DWORD(  dwOwnerStorage_0 )
   _XBST_DWORD(  dwOwnerStorage_1 )
   _XBST_DWORD(  dwOwnerStorage_2 )
   _XBST_DWORD(  dwOwnerStorage_3 )
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , szGroupName)); _XBST_SZSTR(szGroupName,120 )
   pc->GwstSetOffset( sizeof( INTERNET_CACHE_GROUP_INFO) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_AUTO_PROXY_SCRIPT_BUFFER</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_AUTO_PROXY_SCRIPT_BUFFER</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinInet AUTO_PROXY_SCRIPT_BUFFER structure.</description>
      <members>
         <member type="DWORD" name="dwStructSize" />
         <member type="LPSTR" name="lpszScriptBuffer" />
         <member type="DWORD" name="dwScriptBufferSize" />
      </members>
      <ot4xb-helpers><helper type="DYNSZ" name="cScriptBuffer" target="lpszScriptBuffer" access="string" /></ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( AUTO_PROXY_SCRIPT_BUFFER )

   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwStructSize        ));_XBST_DWORD( dwStructSize        )
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,lpszScriptBuffer    ));_XBST_LPSTR_DYNSZ( lpszScriptBuffer , cScriptBuffer )
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwScriptBufferSize  ));_XBST_DWORD( dwScriptBufferSize  )
   pc->GwstSetOffset( sizeof( AUTO_PROXY_SCRIPT_BUFFER) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_TRACKMOUSEEVENT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_TRACKMOUSEEVENT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi TRACKMOUSEEVENT structure.
         Defined as TRACKMOUSEEVENT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="DWORD" name="cbSize" offset="0" size="4" />
         <member type="DWORD" name="dwFlags" offset="4" size="4" />
         <member type="HWND" name="hwndTrack" offset="8" size="4" />
         <member type="DWORD" name="dwHoverTime" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(TRACKMOUSEEVENT )
   _XBST_DWORD( cbSize)
   _XBST_DWORD( dwFlags)
   _XBST_HWND  (hwndTrack)
   _XBST_DWORD( dwHoverTime)
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_MOUSEMOVEPOINT</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_MOUSEMOVEPOINT</source>
      <category>winapi/structures</category>
      <description>
         Wrapper over the WinApi MOUSEMOVEPOINT structure.
         Defined as MOUSEMOVEPOINT in ot4xb_wapist_map.ch.
      </description>
      <size>16</size>
      <members>
         <member type="INT" name="x" offset="0" size="4" />
         <member type="INT" name="y" offset="4" size="4" />
         <member type="DWORD" name="time" offset="8" size="4" />
         <member type="ULONG_PTR" name="dwExtraInfo" offset="12" size="4" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( MOUSEMOVEPOINT )
	_XBST_int(x)
	_XBST_int(y)
	_XBST_DWORD(time)
	_XBST_ULONG_PTR(dwExtraInfo )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_PREVENT_MEDIA_REMOVAL</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_PREVENT_MEDIA_REMOVAL</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi PREVENT_MEDIA_REMOVAL structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddstor/ns-ntddstor-_prevent_media_removal</ref-url>
      <members><member type="BYTE" name="PreventMediaRemoval" /></members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE( PREVENT_MEDIA_REMOVAL )
_XBST_BYTE( PreventMediaRemoval	)
pc->GwstSetOffset(sizeof(PREVENT_MEDIA_REMOVAL));
XB_END_STRUCTURE
// ---------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SHFILEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SHFILEINFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi SHFILEINFOA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileinfoa</ref-url>
      <members>
         <member type="HICON" name="hIcon" />
         <member type="INT" name="iIcon" />
         <member type="DWORD" name="dwAttributes" />
         <member type="SZSTR" name="szDisplayName" size="MAX_PATH" access="string" />
         <member type="SZSTR" name="szTypeName" size="80" access="string" />
      </members>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(SHFILEINFO)
_XBST_HICON(hIcon)
_XBST_int(iIcon)
_XBST_DWORD(dwAttributes)
_XBST_SZSTR(szDisplayName, MAX_PATH)
_XBST_SZSTR(szTypeName, 80);
pc->GwstSetOffset(sizeof(SHFILEINFOA));
XB_END_STRUCTURE
// ---------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <class>
      <name>WAPIST_SHELLEXECUTEINFO</name>
      <parent>GWST</parent>
      <source>winapi_CommonStructures.cpp:WAPIST_SHELLEXECUTEINFO</source>
      <category>winapi/structures</category>
      <description>Wrapper over the WinApi SHELLEXECUTEINFOA structure.</description>
      <ref-url>https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shellexecuteinfoa</ref-url>
      <members>
         <member type="DWORD" name="cbSize" />
         <member type="ULONG" name="fMask" />
         <member type="HWND" name="hwnd" />
         <member type="LPSTR" name="lpVerb" />
         <member type="LPSTR" name="lpFile" />
         <member type="LPSTR" name="lpParameters" />
         <member type="LPSTR" name="lpDirectory" />
         <member type="INT" name="nShow" />
         <member type="HINSTANCE" name="hInstApp" />
         <member type="LPVOID" name="lpIDList" />
         <member type="LPSTR" name="lpClass" />
         <member type="HANDLE" name="hkeyClass" />
         <member type="DWORD" name="dwHotKey" />
         <union>
            <member type="HANDLE" name="hIcon" />
            <member type="HANDLE" name="hMonitor" />
         </union>
         <member type="HANDLE" name="hProcess" />
      </members>
      <ot4xb-helpers>
         <helper type="DYNSZ" name="cVerb" target="lpVerb" access="string" />
         <helper type="DYNSZ" name="cFile" target="lpFile" access="string" />
         <helper type="DYNSZ" name="cParameters" target="lpParameters" access="string" />
         <helper type="DYNSZ" name="cDirectory" target="lpDirectory" access="string" />
         <helper type="DYNSZ" name="cClass" target="lpClass" access="string" />
      </ot4xb-helpers>
   </class>
</xbdoc>
*******************************************************************************************************************/
XB_BEGIN_STRUCTURE(SHELLEXECUTEINFO)
	_XBST_DWORD(cbSize)
	_XBST_ULONG(fMask)
	_XBST_HWND(hwnd)
	_XBST_LPSTR_DYNSZ(lpVerb, cVerb)
	_XBST_LPSTR_DYNSZ(lpFile, cFile)
	_XBST_LPSTR_DYNSZ(lpParameters, cParameters)
	_XBST_LPSTR_DYNSZ(lpDirectory, cDirectory)
	_XBST_int(nShow)
	_XBST_HINSTANCE(hInstApp)
	_XBST_LPVOID(lpIDList)
	_XBST_LPSTR_DYNSZ(lpClass , cClass )
	_XBST_HANDLE( hkeyClass )
	_XBST_DWORD(dwHotKey)
	_XBST_HANDLE(hIcon)
	pc->GwstBack(); // inline union
	_XBST_HANDLE( hMonitor )
	_XBST_HANDLE( hProcess )
	// ----------
	// ----------
XB_END_STRUCTURE
// ---------------------------------------------------------------------------------------------------------------------
