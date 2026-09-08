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
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-note-id}}*/
/*{{note-id: wapist-map
            | title_: The wapist structure classes and ot4xb_wapist_map.ch}}*/
/*{{|:
   Every WinAPI structure class in this file is registered and exported under its real WAPIST_-prefixed name:
   the class function of the POINT wrapper is WAPIST_POINT() and the registered class name is "WAPIST_POINT".
   ot4xb_wapist_map.ch maps the plain WinAPI structure names to those class functions with #pragma Map, so
   Xbase++ code can simply write POINT():new(). The map is not loaded by default: ot4xb.ch includes it only
   when _OT4XB_MAP_WAPIST_FUNC_ is defined before including ot4xb.ch. Each mapped class names its alias in a
   "Defined as X in ot4xb_wapist_map.ch." sentence; a class documented without such a sentence has no map
   entry and must be used through its WAPIST_* class function. }}*/
/*{{end-note-id}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_POINT
            | _slug_: wapist_point
            | class-function: WAPIST_POINT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi POINT structure. Defined as POINT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/windef/ns-windef-point
            | _kw_: WAPIST_POINT, POINT, WINAPI, Structures
   }}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{|:**BEGIN STRUCTURE  POINT** }}*/
XB_BEGIN_STRUCTURE ( POINT )
   /*{{|member_: - MEMBER LONG x |desc_: x coordinate. }}*/
   _XBST_LONG ( x )
   /*{{|member_: - MEMBER LONG y |desc_: y coordinate. }}*/
   _XBST_LONG ( y )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_POINTS
            | _slug_: wapist_points
            | class-function: WAPIST_POINTS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi POINTS structure. Defined as POINTS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_POINTS, POINTS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  POINTS** }}*/
XB_BEGIN_STRUCTURE ( POINTS )
   /*{{|member_: - MEMBER SHORT x }}*/
   _XBST_SHORT ( x )
   /*{{|member_: - MEMBER SHORT y }}*/
   _XBST_SHORT ( y )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_POINTL
            | _slug_: wapist_pointl
            | class-function: WAPIST_POINTL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi POINTL structure. Defined as POINTL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_POINTL, POINTL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  POINTL** }}*/
XB_BEGIN_STRUCTURE ( POINTL )
   /*{{|member_: - MEMBER LONG x }}*/
   _XBST_LONG ( x )
   /*{{|member_: - MEMBER LONG y }}*/
   _XBST_LONG ( y )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MSG
            | _slug_: wapist_msg
            | class-function: WAPIST_MSG
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MSG structure. Defined as MSG in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MSG, MSG, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MSG** }}*/
XB_BEGIN_STRUCTURE ( MSG )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND   ( hwnd    )
   /*{{|member_: - MEMBER UINT message }}*/
   _XBST_UINT   ( message )
   /*{{|member_: - MEMBER WPARAM wParam }}*/
   _XBST_WPARAM ( wParam  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
   /*{{|member_: - MEMBER DWORD time }}*/
   _XBST_DWORD  ( time    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT  ( pt      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BITMAP
            | _slug_: wapist_bitmap
            | class-function: WAPIST_BITMAP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BITMAP structure. Defined as BITMAP in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_BITMAP, BITMAP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BITMAP** }}*/
XB_BEGIN_STRUCTURE ( BITMAP       )
   /*{{|member_: - MEMBER LONG bmType }}*/
   _XBST_LONG      ( bmType       )
   /*{{|member_: - MEMBER LONG bmWidth }}*/
   _XBST_LONG      ( bmWidth      )
   /*{{|member_: - MEMBER LONG bmHeight }}*/
   _XBST_LONG      ( bmHeight     )
   /*{{|member_: - MEMBER LONG bmWidthBytes }}*/
   _XBST_LONG      ( bmWidthBytes )
   /*{{|member_: - MEMBER WORD bmPlanes }}*/
   _XBST_WORD      ( bmPlanes     )
   /*{{|member_: - MEMBER WORD bmBitsPixel }}*/
   _XBST_WORD      ( bmBitsPixel  )
   /*{{|member_: - MEMBER POINTER32 bmBits }}*/
   _XBST_POINTER32 ( bmBits       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BITMAPINFOHEADER
            | _slug_: wapist_bitmapinfoheader
            | class-function: WAPIST_BITMAPINFOHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BITMAPINFOHEADER structure. Defined as BITMAPINFOHEADER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_BITMAPINFOHEADER, BITMAPINFOHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BITMAPINFOHEADER** }}*/
XB_BEGIN_STRUCTURE ( BITMAPINFOHEADER )
   /*{{|member_: - MEMBER DWORD biSize }}*/
   _XBST_DWORD ( biSize          )
   /*{{|member_: - MEMBER LONG biWidth }}*/
   _XBST_LONG  ( biWidth         )
   /*{{|member_: - MEMBER LONG biHeight }}*/
   _XBST_LONG  ( biHeight        )
   /*{{|member_: - MEMBER WORD biPlanes }}*/
   _XBST_WORD  ( biPlanes        )
   /*{{|member_: - MEMBER WORD biBitCount }}*/
   _XBST_WORD  ( biBitCount      )
   /*{{|member_: - MEMBER DWORD biCompression }}*/
   _XBST_DWORD ( biCompression   )
   /*{{|member_: - MEMBER DWORD biSizeImage }}*/
   _XBST_DWORD ( biSizeImage     )
   /*{{|member_: - MEMBER LONG biXPelsPerMeter }}*/
   _XBST_LONG  ( biXPelsPerMeter )
   /*{{|member_: - MEMBER LONG biYPelsPerMeter }}*/
   _XBST_LONG  ( biYPelsPerMeter )
   /*{{|member_: - MEMBER DWORD biClrUsed }}*/
   _XBST_DWORD ( biClrUsed       )
   /*{{|member_: - MEMBER DWORD biClrImportant }}*/
   _XBST_DWORD ( biClrImportant  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DIBSECTION
            | _slug_: wapist_dibsection
            | class-function: WAPIST_DIBSECTION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DIBSECTION structure. Defined as DIBSECTION in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DIBSECTION, DIBSECTION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DIBSECTION** }}*/
XB_BEGIN_STRUCTURE ( DIBSECTION )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_bitmap> wapist_BITMAP}} dsBm }}*/
   _XBST_BITMAP           ( dsBm          )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_bitmapinfoheader> wapist_BITMAPINFOHEADER}} dsBmih }}*/
   _XBST_BITMAPINFOHEADER ( dsBmih        )
   /*{{|member_: - MEMBER DWORD dsBitfield_R }}*/
   _XBST_DWORD            ( dsBitfield_R  )
   /*{{|member_: - MEMBER DWORD dsBitfield_G }}*/
   _XBST_DWORD            ( dsBitfield_G  )
   /*{{|member_: - MEMBER DWORD dsBitfield_B }}*/
   _XBST_DWORD            ( dsBitfield_B  )
   /*{{|member_: - MEMBER HANDLE dshSection }}*/
   _XBST_HANDLE           ( dshSection    )
   /*{{|member_: - MEMBER DWORD dsOffset }}*/
   _XBST_DWORD            ( dsOffset      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_EXTLOGPEN
            | _slug_: wapist_extlogpen
            | class-function: WAPIST_EXTLOGPEN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi EXTLOGPEN structure. Defined as EXTLOGPEN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_EXTLOGPEN, EXTLOGPEN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  EXTLOGPEN** }}*/
XB_BEGIN_STRUCTURE ( EXTLOGPEN )
   /*{{|member_: - MEMBER DWORD elpPenStyle }}*/
   _XBST_DWORD      ( elpPenStyle      )
   /*{{|member_: - MEMBER DWORD elpWidth }}*/
   _XBST_DWORD      ( elpWidth         )
   /*{{|member_: - MEMBER UINT elpBrushStyle }}*/
   _XBST_UINT       ( elpBrushStyle    )
   /*{{|member_: - MEMBER ULONG elpColor }}*/
   _XBST_ULONG      ( elpColor         )
   /*{{|member_: - MEMBER POINTER32 elpHatch }}*/
   _XBST_POINTER32  ( elpHatch         )
   /*{{|member_: - MEMBER DWORD elpNumEntries }}*/
   _XBST_DWORD      ( elpNumEntries    )
   /*{{|member_: - MEMBER DWORD elpStyleEntry0 }}*/
   _XBST_DWORD      ( elpStyleEntry0   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LOGPEN
            | _slug_: wapist_logpen
            | class-function: WAPIST_LOGPEN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LOGPEN structure. Defined as LOGPEN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LOGPEN, LOGPEN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LOGPEN** }}*/
XB_BEGIN_STRUCTURE ( LOGPEN )
   /*{{|member_: - MEMBER DWORD lopnPenStyle }}*/
   _XBST_DWORD ( lopnPenStyle )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} lopnWidth }}*/
   _XBST_POINT ( lopnWidth    )
   /*{{|member_: - MEMBER ULONG lopnColor }}*/
   _XBST_ULONG ( lopnColor    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LOGBRUSH
            | _slug_: wapist_logbrush
            | class-function: WAPIST_LOGBRUSH
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LOGBRUSH structure. Defined as LOGBRUSH in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LOGBRUSH, LOGBRUSH, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LOGBRUSH** }}*/
XB_BEGIN_STRUCTURE ( LOGBRUSH )
   /*{{|member_: - MEMBER UINT lbStyle }}*/
   _XBST_UINT  ( lbStyle )
   /*{{|member_: - MEMBER ULONG lbColor }}*/
   _XBST_ULONG ( lbColor )
   /*{{|member_: - MEMBER LONG lbHatch }}*/
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LOGBRUSH32
            | _slug_: wapist_logbrush32
            | class-function: WAPIST_LOGBRUSH32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LOGBRUSH32 structure. Defined as LOGBRUSH32 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LOGBRUSH32, LOGBRUSH32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LOGBRUSH32** }}*/
XB_BEGIN_STRUCTURE ( LOGBRUSH32 )
   /*{{|member_: - MEMBER UINT lbStyle }}*/
   _XBST_UINT  ( lbStyle )
   /*{{|member_: - MEMBER ULONG lbColor }}*/
   _XBST_ULONG ( lbColor )
   /*{{|member_: - MEMBER LONG lbHatch }}*/
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LOGFONT
            | _slug_: wapist_logfont
            | class-function: WAPIST_LOGFONT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LOGFONT structure. Defined as LOGFONT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LOGFONT, LOGFONT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LOGFONT** }}*/
XB_BEGIN_STRUCTURE ( LOGFONT )
   /*{{|member_: - MEMBER LONG lfHeight }}*/
   _XBST_LONG   ( lfHeight                 )
   /*{{|member_: - MEMBER LONG lfWidth }}*/
   _XBST_LONG   ( lfWidth                  )
   /*{{|member_: - MEMBER LONG lfEscapement }}*/
   _XBST_LONG   ( lfEscapement             )
   /*{{|member_: - MEMBER LONG lfOrientation }}*/
   _XBST_LONG   ( lfOrientation            )
   /*{{|member_: - MEMBER LONG lfWeight }}*/
   _XBST_LONG   ( lfWeight                 )
   /*{{|member_: - MEMBER BYTE lfItalic }}*/
   _XBST_BYTE   ( lfItalic                 )
   /*{{|member_: - MEMBER BYTE lfUnderline }}*/
   _XBST_BYTE   ( lfUnderline              )
   /*{{|member_: - MEMBER BYTE lfStrikeOut }}*/
   _XBST_BYTE   ( lfStrikeOut              )
   /*{{|member_: - MEMBER BYTE lfCharSet }}*/
   _XBST_BYTE   ( lfCharSet                )
   /*{{|member_: - MEMBER BYTE lfOutPrecision }}*/
   _XBST_BYTE   ( lfOutPrecision           )
   /*{{|member_: - MEMBER BYTE lfClipPrecision }}*/
   _XBST_BYTE   ( lfClipPrecision          )
   /*{{|member_: - MEMBER BYTE lfQuality }}*/
   _XBST_BYTE   ( lfQuality                )
   /*{{|member_: - MEMBER BYTE lfPitchAndFamily }}*/
   _XBST_BYTE   ( lfPitchAndFamily         )
   /*{{|member_: - MEMBER SZSTR lfFaceName }}*/
   _XBST_SZSTR  ( lfFaceName , LF_FACESIZE )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BLENDFUNCTION
            | _slug_: wapist_blendfunction
            | class-function: WAPIST_BLENDFUNCTION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BLENDFUNCTION structure. Defined as BLENDFUNCTION in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_BLENDFUNCTION, BLENDFUNCTION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BLENDFUNCTION** }}*/
XB_BEGIN_STRUCTURE ( BLENDFUNCTION )
   /*{{|member_: - MEMBER BYTE BlendOp }}*/
   _XBST_BYTE ( BlendOp             )
   /*{{|member_: - MEMBER BYTE BlendFlags }}*/
   _XBST_BYTE ( BlendFlags          )
   /*{{|member_: - MEMBER BYTE SourceConstantAlpha }}*/
   _XBST_BYTE ( SourceConstantAlpha )
   /*{{|member_: - MEMBER BYTE AlphaFormat }}*/
   _XBST_BYTE ( AlphaFormat         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RGBQUAD
            | _slug_: wapist_rgbquad
            | class-function: WAPIST_RGBQUAD
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RGBQUAD structure. Defined as RGBQUAD in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RGBQUAD, RGBQUAD, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RGBQUAD** }}*/
XB_BEGIN_STRUCTURE ( RGBQUAD )
   /*{{|member_: - MEMBER BYTE rgbBlue }}*/
   _XBST_BYTE ( rgbBlue     )
   /*{{|member_: - MEMBER BYTE rgbGreen }}*/
   _XBST_BYTE ( rgbGreen    )
   /*{{|member_: - MEMBER BYTE rgbRed }}*/
   _XBST_BYTE ( rgbRed      )
   /*{{|member_: - MEMBER BYTE rgbReserved }}*/
   _XBST_BYTE ( rgbReserved )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BITMAPINFO
            | _slug_: wapist_bitmapinfo
            | class-function: WAPIST_BITMAPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BITMAPINFO structure. Defined as BITMAPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_BITMAPINFO, BITMAPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BITMAPINFO** }}*/
XB_BEGIN_STRUCTURE ( BITMAPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_bitmapinfoheader> wapist_BITMAPINFOHEADER}} bmiHeader }}*/
   _XBST_BITMAPINFOHEADER ( bmiHeader )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rgbquad> wapist_RGBQUAD}} bmiColors }}*/
   _XBST_RGBQUAD          ( bmiColors )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SIZE
            | _slug_: wapist_size
            | class-function: WAPIST_SIZE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SIZE structure. Defined as SIZE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SIZE, SIZE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SIZE** }}*/
XB_BEGIN_STRUCTURE ( SIZE )
   /*{{|member_: - MEMBER LONG cx }}*/
   _XBST_LONG ( cx )
   /*{{|member_: - MEMBER LONG cy }}*/
   _XBST_LONG ( cy )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SIZEL
            | _slug_: wapist_sizel
            | class-function: WAPIST_SIZEL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SIZEL structure. Defined as SIZEL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SIZEL, SIZEL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SIZEL** }}*/
XB_BEGIN_STRUCTURE ( SIZEL )
   /*{{|member_: - MEMBER LONG cx }}*/
   _XBST_LONG ( cx )
   /*{{|member_: - MEMBER LONG cy }}*/
   _XBST_LONG ( cy )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TRIVERTEX
            | _slug_: wapist_trivertex
            | class-function: WAPIST_TRIVERTEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TRIVERTEX structure. Defined as TRIVERTEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TRIVERTEX, TRIVERTEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TRIVERTEX** }}*/
XB_BEGIN_STRUCTURE ( TRIVERTEX )
   /*{{|member_: - MEMBER LONG x }}*/
   _XBST_LONG ( x     )
   /*{{|member_: - MEMBER LONG y }}*/
   _XBST_LONG ( y     )
   /*{{|member_: - MEMBER WORD Red }}*/
   _XBST_WORD ( Red   )
   /*{{|member_: - MEMBER WORD Green }}*/
   _XBST_WORD ( Green )
   /*{{|member_: - MEMBER WORD Blue }}*/
   _XBST_WORD ( Blue  )
   /*{{|member_: - MEMBER WORD Alpha }}*/
   _XBST_WORD ( Alpha )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PALETTEENTRY
            | _slug_: wapist_paletteentry
            | class-function: WAPIST_PALETTEENTRY
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PALETTEENTRY structure. Defined as PALETTEENTRY in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PALETTEENTRY, PALETTEENTRY, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PALETTEENTRY** }}*/
XB_BEGIN_STRUCTURE ( PALETTEENTRY )
   /*{{|member_: - MEMBER BYTE peRed }}*/
   _XBST_BYTE ( peRed   )
   /*{{|member_: - MEMBER BYTE peGreen }}*/
   _XBST_BYTE ( peGreen )
   /*{{|member_: - MEMBER BYTE peBlue }}*/
   _XBST_BYTE ( peBlue  )
   /*{{|member_: - MEMBER BYTE peFlags }}*/
   _XBST_BYTE ( peFlags )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LOGPALETTE
            | _slug_: wapist_logpalette
            | class-function: WAPIST_LOGPALETTE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LOGPALETTE structure. Defined as LOGPALETTE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LOGPALETTE, LOGPALETTE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LOGPALETTE** }}*/
XB_BEGIN_STRUCTURE ( LOGPALETTE )
   /*{{|member_: - MEMBER WORD palVersion }}*/
   _XBST_WORD         ( palVersion    )
   /*{{|member_: - MEMBER WORD palNumEntries }}*/
   _XBST_WORD         ( palNumEntries )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_paletteentry> wapist_PALETTEENTRY}} palPalEntry0 }}*/
   _XBST_PALETTEENTRY ( palPalEntry0  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_XFORM
            | _slug_: wapist_xform
            | class-function: WAPIST_XFORM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi XFORM structure. Defined as XFORM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_XFORM, XFORM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  XFORM** }}*/
XB_BEGIN_STRUCTURE ( XFORM )
   /*{{|member_: - MEMBER FLOAT eM11 }}*/
   _XBST_FLOAT ( eM11 )
   /*{{|member_: - MEMBER FLOAT eM12 }}*/
   _XBST_FLOAT ( eM12 )
   /*{{|member_: - MEMBER FLOAT eM21 }}*/
   _XBST_FLOAT ( eM21 )
   /*{{|member_: - MEMBER FLOAT eM22 }}*/
   _XBST_FLOAT ( eM22 )
   /*{{|member_: - MEMBER FLOAT eDx }}*/
   _XBST_FLOAT ( eDx  )
   /*{{|member_: - MEMBER FLOAT eDy }}*/
   _XBST_FLOAT ( eDy  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RECT
            | _slug_: wapist_rect
            | class-function: WAPIST_RECT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RECT structure. Defined as RECT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RECT, RECT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RECT** }}*/
XB_BEGIN_STRUCTURE ( RECT )
   /*{{|member_: - MEMBER LONG left }}*/
   _XBST_LONG ( left   )
   /*{{|member_: - MEMBER LONG top }}*/
   _XBST_LONG ( top    )
   /*{{|member_: - MEMBER LONG right }}*/
   _XBST_LONG ( right  )
   /*{{|member_: - MEMBER LONG bottom }}*/
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RECTL
            | _slug_: wapist_rectl
            | class-function: WAPIST_RECTL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RECTL structure. Defined as RECTL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RECTL, RECTL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RECTL** }}*/
XB_BEGIN_STRUCTURE ( RECTL )
   /*{{|member_: - MEMBER LONG left }}*/
   _XBST_LONG ( left   )
   /*{{|member_: - MEMBER LONG top }}*/
   _XBST_LONG ( top    )
   /*{{|member_: - MEMBER LONG right }}*/
   _XBST_LONG ( right  )
   /*{{|member_: - MEMBER LONG bottom }}*/
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ABC
            | _slug_: wapist_abc
            | class-function: WAPIST_ABC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ABC structure. Defined as ABC in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ABC, ABC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ABC** }}*/
XB_BEGIN_STRUCTURE ( ABC )
   /*{{|member_: - MEMBER INT abcA }}*/
   _XBST_INT  ( abcA )
   /*{{|member_: - MEMBER UINT abcB }}*/
   _XBST_UINT ( abcB )
   /*{{|member_: - MEMBER INT abcC }}*/
   _XBST_INT  ( abcC )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ABCFLOAT
            | _slug_: wapist_abcfloat
            | class-function: WAPIST_ABCFLOAT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ABCFLOAT structure. Defined as ABCFLOAT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ABCFLOAT, ABCFLOAT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ABCFLOAT** }}*/
XB_BEGIN_STRUCTURE ( ABCFLOAT )
   /*{{|member_: - MEMBER FLOAT abcfA }}*/
   _XBST_FLOAT ( abcfA )
   /*{{|member_: - MEMBER FLOAT abcfB }}*/
   _XBST_FLOAT ( abcfB )
   /*{{|member_: - MEMBER FLOAT abcfC }}*/
   _XBST_FLOAT ( abcfC )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRAWTEXTPARAMS
            | _slug_: wapist_drawtextparams
            | class-function: WAPIST_DRAWTEXTPARAMS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRAWTEXTPARAMS structure. Defined as DRAWTEXTPARAMS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DRAWTEXTPARAMS, DRAWTEXTPARAMS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRAWTEXTPARAMS** }}*/
XB_BEGIN_STRUCTURE ( DRAWTEXTPARAMS )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize        )
   /*{{|member_: - MEMBER INT iTabLength }}*/
   _XBST_int  ( iTabLength    )
   /*{{|member_: - MEMBER INT iLeftMargin }}*/
   _XBST_int  ( iLeftMargin   )
   /*{{|member_: - MEMBER INT iRightMargin }}*/
   _XBST_int  ( iRightMargin  )
   /*{{|member_: - MEMBER UINT uiLengthDrawn }}*/
   _XBST_UINT ( uiLengthDrawn )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENUMLOGFONT
            | _slug_: wapist_enumlogfont
            | class-function: WAPIST_ENUMLOGFONT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENUMLOGFONT structure. Defined as ENUMLOGFONT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENUMLOGFONT, ENUMLOGFONT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENUMLOGFONT** }}*/
XB_BEGIN_STRUCTURE ( ENUMLOGFONT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_logfont> wapist_LOGFONT}} elfLogFont }}*/
   _XBST_LOGFONT ( elfLogFont                    )
   /*{{|member_: - MEMBER SZSTR elfFullName }}*/
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   /*{{|member_: - MEMBER SZSTR elfStyle }}*/
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENUMLOGFONTEX
            | _slug_: wapist_enumlogfontex
            | class-function: WAPIST_ENUMLOGFONTEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENUMLOGFONTEX structure. Defined as ENUMLOGFONTEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENUMLOGFONTEX, ENUMLOGFONTEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENUMLOGFONTEX** }}*/
XB_BEGIN_STRUCTURE ( ENUMLOGFONTEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_logfont> wapist_LOGFONT}} elfLogFont }}*/
   _XBST_LOGFONT ( elfLogFont                    )
   /*{{|member_: - MEMBER SZSTR elfFullName }}*/
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   /*{{|member_: - MEMBER SZSTR elfStyle }}*/
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
   /*{{|member_: - MEMBER SZSTR elfScript }}*/
   _XBST_SZSTR   ( elfScript   , LF_FACESIZE     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_EXTLOGFONT
            | _slug_: wapist_extlogfont
            | class-function: WAPIST_EXTLOGFONT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi EXTLOGFONT structure. Defined as EXTLOGFONT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_EXTLOGFONT, EXTLOGFONT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  EXTLOGFONT** }}*/
XB_BEGIN_STRUCTURE ( EXTLOGFONT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_logfont> wapist_LOGFONT}} elfLogFont }}*/
   _XBST_LOGFONT ( elfLogFont                     )
   /*{{|member_: - MEMBER SZSTR elfFullName }}*/
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE  )
   /*{{|member_: - MEMBER SZSTR elfStyle }}*/
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE      )
   /*{{|member_: - MEMBER DWORD elfVersion }}*/
   _XBST_DWORD   ( elfVersion                     )
   /*{{|member_: - MEMBER DWORD elfStyleSize }}*/
   _XBST_DWORD   ( elfStyleSize                   )
   /*{{|member_: - MEMBER DWORD elfMatch }}*/
   _XBST_DWORD   ( elfMatch                       )
   /*{{|member_: - MEMBER DWORD elfReserved }}*/
   _XBST_DWORD   ( elfReserved                    )
   /*{{|member_: - MEMBER BINSTR elfVendorId }}*/
   _XBST_BINSTR  ( elfVendorId , ELF_VENDOR_SIZE  )
   /*{{|member_: - MEMBER DWORD elfCulture }}*/
   _XBST_DWORD   ( elfCulture                     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_panose> wapist_PANOSE}} elfPanose }}*/
   _XBST_PANOSE  ( elfPanose                      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FIXED
            | _slug_: wapist_fixed
            | class-function: WAPIST_FIXED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FIXED structure. Defined as FIXED in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FIXED, FIXED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FIXED** }}*/
XB_BEGIN_STRUCTURE ( FIXED )
   /*{{|member_: - MEMBER WORD fract }}*/
   _XBST_WORD  ( fract )
   /*{{|member_: - MEMBER SHORT value }}*/
   _XBST_short ( value )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GCP_RESULTS
            | _slug_: wapist_gcp_results
            | class-function: WAPIST_GCP_RESULTS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GCP_RESULTS structure. Defined as GCP_RESULTS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GCP_RESULTS, GCP_RESULTS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GCP_RESULTS** }}*/
XB_BEGIN_STRUCTURE ( GCP_RESULTS )
   /*{{|member_: - MEMBER DWORD lStructSize }}*/
   _XBST_DWORD     ( lStructSize )
   /*{{|member_: - MEMBER LPSTR lpOutString }}*/
   _XBST_LPSTR     ( lpOutString )
   /*{{|member_: - MEMBER POINTER32 lpOrder }}*/
   _XBST_POINTER32 ( lpOrder )
   /*{{|member_: - MEMBER POINTER32 lpDx }}*/
   _XBST_POINTER32 ( lpDx )
   /*{{|member_: - MEMBER POINTER32 lpCaretPos }}*/
   _XBST_POINTER32 ( lpCaretPos )
   /*{{|member_: - MEMBER LPSTR lpClass }}*/
   _XBST_LPSTR     ( lpClass )
   /*{{|member_: - MEMBER POINTER32 lpGlyphs }}*/
   _XBST_POINTER32 ( lpGlyphs )
   /*{{|member_: - MEMBER UINT nGlyphs }}*/
   _XBST_UINT      ( nGlyphs )
   /*{{|member_: - MEMBER INT nMaxFit }}*/
   _XBST_int       ( nMaxFit )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GLYPHMETRICS
            | _slug_: wapist_glyphmetrics
            | class-function: WAPIST_GLYPHMETRICS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GLYPHMETRICS structure. Defined as GLYPHMETRICS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GLYPHMETRICS, GLYPHMETRICS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GLYPHMETRICS** }}*/
XB_BEGIN_STRUCTURE ( GLYPHMETRICS )
   /*{{|member_: - MEMBER UINT gmBlackBoxX }}*/
   _XBST_UINT      ( gmBlackBoxX )
   /*{{|member_: - MEMBER UINT gmBlackBoxY }}*/
   _XBST_UINT      ( gmBlackBoxY )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} gmptGlyphOrigin }}*/
   _XBST_POINT     ( gmptGlyphOrigin )
   /*{{|member_: - MEMBER SHORT gmCellIncX }}*/
   _XBST_short     ( gmCellIncX )
   /*{{|member_: - MEMBER SHORT gmCellIncY }}*/
   _XBST_short     ( gmCellIncY )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GLYPHSET
            | _slug_: wapist_glyphset
            | class-function: WAPIST_GLYPHSET
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GLYPHSET structure. Defined as GLYPHSET in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GLYPHSET, GLYPHSET, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GLYPHSET** }}*/
XB_BEGIN_STRUCTURE ( GLYPHSET )
   /*{{|member_: - MEMBER DWORD cbThis }}*/
   _XBST_DWORD   ( cbThis )
   /*{{|member_: - MEMBER DWORD flAccel }}*/
   _XBST_DWORD   ( flAccel )
   /*{{|member_: - MEMBER DWORD cGlyphsSupported }}*/
   _XBST_DWORD   ( cGlyphsSupported )
   /*{{|member_: - MEMBER DWORD cRanges }}*/
   _XBST_DWORD   ( cRanges )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wcrange> wapist_WCRANGE}} ranges0 }}*/
   _XBST_WCRANGE ( ranges0 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_KERNINGPAIR
            | _slug_: wapist_kerningpair
            | class-function: WAPIST_KERNINGPAIR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi KERNINGPAIR structure. Defined as KERNINGPAIR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_KERNINGPAIR, KERNINGPAIR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  KERNINGPAIR** }}*/
XB_BEGIN_STRUCTURE ( KERNINGPAIR )
   /*{{|member_: - MEMBER WORD wFirst }}*/
   _XBST_WORD ( wFirst )
   /*{{|member_: - MEMBER WORD wSecond }}*/
   _XBST_WORD ( wSecond )
   /*{{|member_: - MEMBER INT iKernAmount }}*/
   _XBST_int  ( iKernAmount )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MAT2
            | _slug_: wapist_mat2
            | class-function: WAPIST_MAT2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MAT2 structure. Defined as MAT2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MAT2, MAT2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MAT2** }}*/
XB_BEGIN_STRUCTURE ( MAT2 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} eM11 }}*/
   _XBST_FIXED ( eM11 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} eM12 }}*/
   _XBST_FIXED ( eM12 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} eM21 }}*/
   _XBST_FIXED ( eM21 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} eM22 }}*/
   _XBST_FIXED ( eM22 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NEWTEXTMETRIC
            | _slug_: wapist_newtextmetric
            | class-function: WAPIST_NEWTEXTMETRIC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NEWTEXTMETRIC structure. Defined as NEWTEXTMETRIC in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NEWTEXTMETRIC, NEWTEXTMETRIC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NEWTEXTMETRIC** }}*/
XB_BEGIN_STRUCTURE ( NEWTEXTMETRIC )
   /*{{|member_: - MEMBER LONG tmHeight }}*/
   _XBST_LONG  ( tmHeight           )
   /*{{|member_: - MEMBER LONG tmAscent }}*/
   _XBST_LONG  ( tmAscent           )
   /*{{|member_: - MEMBER LONG tmDescent }}*/
   _XBST_LONG  ( tmDescent          )
   /*{{|member_: - MEMBER LONG tmInternalLeading }}*/
   _XBST_LONG  ( tmInternalLeading  )
   /*{{|member_: - MEMBER LONG tmExternalLeading }}*/
   _XBST_LONG  ( tmExternalLeading  )
   /*{{|member_: - MEMBER LONG tmAveCharWidth }}*/
   _XBST_LONG  ( tmAveCharWidth     )
   /*{{|member_: - MEMBER LONG tmMaxCharWidth }}*/
   _XBST_LONG  ( tmMaxCharWidth     )
   /*{{|member_: - MEMBER LONG tmWeight }}*/
   _XBST_LONG  ( tmWeight           )
   /*{{|member_: - MEMBER LONG tmOverhang }}*/
   _XBST_LONG  ( tmOverhang         )
   /*{{|member_: - MEMBER LONG tmDigitizedAspectX }}*/
   _XBST_LONG  ( tmDigitizedAspectX )
   /*{{|member_: - MEMBER LONG tmDigitizedAspectY }}*/
   _XBST_LONG  ( tmDigitizedAspectY )
   /*{{|member_: - MEMBER BYTE tmFirstChar }}*/
   _XBST_TCHAR ( tmFirstChar        )
   /*{{|member_: - MEMBER BYTE tmLastChar }}*/
   _XBST_TCHAR ( tmLastChar         )
   /*{{|member_: - MEMBER BYTE tmDefaultChar }}*/
   _XBST_TCHAR ( tmDefaultChar      )
   /*{{|member_: - MEMBER BYTE tmBreakChar }}*/
   _XBST_TCHAR ( tmBreakChar        )
   /*{{|member_: - MEMBER BYTE tmItalic }}*/
   _XBST_BYTE  ( tmItalic           )
   /*{{|member_: - MEMBER BYTE tmUnderlined }}*/
   _XBST_BYTE  ( tmUnderlined       )
   /*{{|member_: - MEMBER BYTE tmStruckOut }}*/
   _XBST_BYTE  ( tmStruckOut        )
   /*{{|member_: - MEMBER BYTE tmPitchAndFamily }}*/
   _XBST_BYTE  ( tmPitchAndFamily   )
   /*{{|member_: - MEMBER BYTE tmCharSet }}*/
   _XBST_BYTE  ( tmCharSet          )
   /*{{|member_: - MEMBER DWORD ntmFlags }}*/
   _XBST_DWORD ( ntmFlags           )
   /*{{|member_: - MEMBER UINT ntmSizeEM }}*/
   _XBST_UINT  ( ntmSizeEM          )
   /*{{|member_: - MEMBER UINT ntmCellHeight }}*/
   _XBST_UINT  ( ntmCellHeight      )
   /*{{|member_: - MEMBER UINT ntmAvgWidth }}*/
   _XBST_UINT  ( ntmAvgWidth        )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NEWTEXTMETRICEX
            | _slug_: wapist_newtextmetricex
            | class-function: WAPIST_NEWTEXTMETRICEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NEWTEXTMETRICEX structure. Defined as NEWTEXTMETRICEX in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NEWTEXTMETRICEX, NEWTEXTMETRICEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NEWTEXTMETRICEX** }}*/
XB_BEGIN_STRUCTURE ( NEWTEXTMETRICEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_newtextmetric> wapist_NEWTEXTMETRIC}} ntmTm }}*/
   _XBST_NEWTEXTMETRIC ( ntmTm      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fontsignature> wapist_FONTSIGNATURE}} ntmFontSig }}*/
   _XBST_FONTSIGNATURE ( ntmFontSig )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OUTLINETEXTMETRIC
            | _slug_: wapist_outlinetextmetric
            | class-function: WAPIST_OUTLINETEXTMETRIC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi OUTLINETEXTMETRIC structure. Defined as OUTLINETEXTMETRIC in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_OUTLINETEXTMETRIC, OUTLINETEXTMETRIC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OUTLINETEXTMETRIC** }}*/
XB_BEGIN_STRUCTURE ( OUTLINETEXTMETRIC )
   /*{{|member_: - MEMBER UINT otmSize }}*/
   _XBST_UINT       ( otmSize                   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_textmetric> wapist_TEXTMETRIC}} otmTextMetrics }}*/
   _XBST_TEXTMETRIC ( otmTextMetrics            )
   /*{{|member_: - MEMBER BYTE otmFiller }}*/
   _XBST_BYTE       ( otmFiller                 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_panose> wapist_PANOSE}} otmPanoseNumber }}*/
   _XBST_PANOSE     ( otmPanoseNumber           )
   /*{{|member_: - MEMBER UINT otmfsSelection }}*/
   _XBST_UINT       ( otmfsSelection            )
   /*{{|member_: - MEMBER UINT otmfsType }}*/
   _XBST_UINT       ( otmfsType                 )
   /*{{|member_: - MEMBER INT otmsCharSlopeRise }}*/
   _XBST_int        ( otmsCharSlopeRise         )
   /*{{|member_: - MEMBER INT otmsCharSlopeRun }}*/
   _XBST_int        ( otmsCharSlopeRun          )
   /*{{|member_: - MEMBER INT otmItalicAngle }}*/
   _XBST_int        ( otmItalicAngle            )
   /*{{|member_: - MEMBER UINT otmEMSquare }}*/
   _XBST_UINT       ( otmEMSquare               )
   /*{{|member_: - MEMBER INT otmAscent }}*/
   _XBST_int        ( otmAscent                 )
   /*{{|member_: - MEMBER INT otmDescent }}*/
   _XBST_int        ( otmDescent                )
   /*{{|member_: - MEMBER UINT otmLineGap }}*/
   _XBST_UINT       ( otmLineGap                )
   /*{{|member_: - MEMBER UINT otmsCapEmHeight }}*/
   _XBST_UINT       ( otmsCapEmHeight           )
   /*{{|member_: - MEMBER UINT otmsXHeight }}*/
   _XBST_UINT       ( otmsXHeight               )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} otmrcFontBox }}*/
   _XBST_RECT       ( otmrcFontBox              )
   /*{{|member_: - MEMBER INT otmMacAscent }}*/
   _XBST_int        ( otmMacAscent              )
   /*{{|member_: - MEMBER INT otmMacDescent }}*/
   _XBST_int        ( otmMacDescent             )
   /*{{|member_: - MEMBER UINT otmMacLineGap }}*/
   _XBST_UINT       ( otmMacLineGap             )
   /*{{|member_: - MEMBER UINT otmusMinimumPPEM }}*/
   _XBST_UINT       ( otmusMinimumPPEM          )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} otmptSubscriptSize }}*/
   _XBST_POINT      ( otmptSubscriptSize        )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} otmptSubscriptOffset }}*/
   _XBST_POINT      ( otmptSubscriptOffset      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} otmptSuperscriptSize }}*/
   _XBST_POINT      ( otmptSuperscriptSize      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} otmptSuperscriptOffset }}*/
   _XBST_POINT      ( otmptSuperscriptOffset    )
   /*{{|member_: - MEMBER UINT otmsStrikeoutSize }}*/
   _XBST_UINT       ( otmsStrikeoutSize         )
   /*{{|member_: - MEMBER INT otmsStrikeoutPosition }}*/
   _XBST_int        ( otmsStrikeoutPosition     )
   /*{{|member_: - MEMBER INT otmsUnderscoreSize }}*/
   _XBST_int        ( otmsUnderscoreSize        )
   /*{{|member_: - MEMBER INT otmsUnderscorePosition }}*/
   _XBST_int        ( otmsUnderscorePosition    )
   /*{{|member_: - MEMBER LPSTR otmpFamilyName }}*/
   _XBST_LPSTR      ( otmpFamilyName            )
   /*{{|member_: - MEMBER LPSTR otmpFaceName }}*/
   _XBST_LPSTR      ( otmpFaceName              )
   /*{{|member_: - MEMBER LPSTR otmpStyleName }}*/
   _XBST_LPSTR      ( otmpStyleName             )
   /*{{|member_: - MEMBER LPSTR otmpFullName }}*/
   _XBST_LPSTR      ( otmpFullName              )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PANOSE
            | _slug_: wapist_panose
            | class-function: WAPIST_PANOSE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PANOSE structure. Defined as PANOSE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PANOSE, PANOSE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PANOSE** }}*/
XB_BEGIN_STRUCTURE ( PANOSE )
   /*{{|member_: - MEMBER BYTE bFamilyType }}*/
   _XBST_BYTE ( bFamilyType      )
   /*{{|member_: - MEMBER BYTE bSerifStyle }}*/
   _XBST_BYTE ( bSerifStyle      )
   /*{{|member_: - MEMBER BYTE bWeight }}*/
   _XBST_BYTE ( bWeight          )
   /*{{|member_: - MEMBER BYTE bProportion }}*/
   _XBST_BYTE ( bProportion      )
   /*{{|member_: - MEMBER BYTE bContrast }}*/
   _XBST_BYTE ( bContrast        )
   /*{{|member_: - MEMBER BYTE bStrokeVariation }}*/
   _XBST_BYTE ( bStrokeVariation )
   /*{{|member_: - MEMBER BYTE bArmStyle }}*/
   _XBST_BYTE ( bArmStyle        )
   /*{{|member_: - MEMBER BYTE bLetterform }}*/
   _XBST_BYTE ( bLetterform      )
   /*{{|member_: - MEMBER BYTE bMidline }}*/
   _XBST_BYTE ( bMidline         )
   /*{{|member_: - MEMBER BYTE bXHeight }}*/
   _XBST_BYTE ( bXHeight         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_POINTFX
            | _slug_: wapist_pointfx
            | class-function: WAPIST_POINTFX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi POINTFX structure. Defined as POINTFX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_POINTFX, POINTFX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  POINTFX** }}*/
XB_BEGIN_STRUCTURE ( POINTFX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} x }}*/
   _XBST_FIXED ( x )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_fixed> wapist_FIXED}} y }}*/
   _XBST_FIXED ( y )

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_POLYTEXT
            | _slug_: wapist_polytext
            | class-function: WAPIST_POLYTEXT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi POLYTEXT structure. Defined as POLYTEXT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_POLYTEXT, POLYTEXT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  POLYTEXT** }}*/
XB_BEGIN_STRUCTURE ( POLYTEXT )
   /*{{|member_: - MEMBER INT x }}*/
   _XBST_int       ( x       )
   /*{{|member_: - MEMBER INT y }}*/
   _XBST_int       ( y       )
   /*{{|member_: - MEMBER UINT n }}*/
   _XBST_UINT      ( n       )
   /*{{|member_: - MEMBER LPSTR lpstr }}*/
   _XBST_LPSTR     ( lpstr   )
   /*{{|member_: - MEMBER UINT uiFlags }}*/
   _XBST_UINT      ( uiFlags )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcl }}*/
   _XBST_RECT      ( rcl     )
   /*{{|member_: - MEMBER POINTER32 pdx }}*/
   _XBST_POINTER32 ( pdx     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RASTERIZER_STATUS
            | _slug_: wapist_rasterizer_status
            | class-function: WAPIST_RASTERIZER_STATUS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RASTERIZER_STATUS structure. Defined as RASTERIZER_STATUS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RASTERIZER_STATUS, RASTERIZER_STATUS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RASTERIZER_STATUS** }}*/
XB_BEGIN_STRUCTURE( RASTERIZER_STATUS )
/*{{|member_: - MEMBER SHORT nSize }}*/
_XBST_short( nSize )
/*{{|member_: - MEMBER SHORT wFlags }}*/
_XBST_short( wFlags )
/*{{|member_: - MEMBER SHORT nLanguageID }}*/
_XBST_short( nLanguageID )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TEXTMETRIC
            | _slug_: wapist_textmetric
            | class-function: WAPIST_TEXTMETRIC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TEXTMETRIC structure. Defined as TEXTMETRIC in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TEXTMETRIC, TEXTMETRIC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TEXTMETRIC** }}*/
XB_BEGIN_STRUCTURE( TEXTMETRIC )
/*{{|member_: - MEMBER LONG tmHeight }}*/
_XBST_LONG( tmHeight )
/*{{|member_: - MEMBER LONG tmAscent }}*/
_XBST_LONG( tmAscent )
/*{{|member_: - MEMBER LONG tmDescent }}*/
_XBST_LONG( tmDescent )
/*{{|member_: - MEMBER LONG tmInternalLeading }}*/
_XBST_LONG( tmInternalLeading )
/*{{|member_: - MEMBER LONG tmExternalLeading }}*/
_XBST_LONG( tmExternalLeading )
/*{{|member_: - MEMBER LONG tmAveCharWidth }}*/
_XBST_LONG( tmAveCharWidth )
/*{{|member_: - MEMBER LONG tmMaxCharWidth }}*/
_XBST_LONG( tmMaxCharWidth )
/*{{|member_: - MEMBER LONG tmWeight }}*/
_XBST_LONG( tmWeight )
/*{{|member_: - MEMBER LONG tmOverhang }}*/
_XBST_LONG( tmOverhang )
/*{{|member_: - MEMBER LONG tmDigitizedAspectX }}*/
_XBST_LONG( tmDigitizedAspectX )
/*{{|member_: - MEMBER LONG tmDigitizedAspectY }}*/
_XBST_LONG( tmDigitizedAspectY )
/*{{|member_: - MEMBER BYTE tmFirstChar }}*/
_XBST_TCHAR( tmFirstChar )
/*{{|member_: - MEMBER BYTE tmLastChar }}*/
_XBST_TCHAR( tmLastChar )
/*{{|member_: - MEMBER BYTE tmDefaultChar }}*/
_XBST_TCHAR( tmDefaultChar )
/*{{|member_: - MEMBER BYTE tmBreakChar }}*/
_XBST_TCHAR( tmBreakChar )
/*{{|member_: - MEMBER BYTE tmItalic }}*/
_XBST_BYTE( tmItalic )
/*{{|member_: - MEMBER BYTE tmUnderlined }}*/
_XBST_BYTE( tmUnderlined )
/*{{|member_: - MEMBER BYTE tmStruckOut }}*/
_XBST_BYTE( tmStruckOut )
/*{{|member_: - MEMBER BYTE tmPitchAndFamily }}*/
_XBST_BYTE( tmPitchAndFamily )
/*{{|member_: - MEMBER BYTE tmCharSet }}*/
_XBST_BYTE( tmCharSet )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TTPOLYCURVE
            | _slug_: wapist_ttpolycurve
            | class-function: WAPIST_TTPOLYCURVE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TTPOLYCURVE structure. Defined as TTPOLYCURVE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TTPOLYCURVE, TTPOLYCURVE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TTPOLYCURVE** }}*/
XB_BEGIN_STRUCTURE( TTPOLYCURVE )
/*{{|member_: - MEMBER WORD wType }}*/
_XBST_WORD( wType )
/*{{|member_: - MEMBER WORD cpfx }}*/
_XBST_WORD( cpfx )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_pointfx> wapist_POINTFX}} apfx0 }}*/
_XBST_POINTFX( apfx0 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TTPOLYGONHEADER
            | _slug_: wapist_ttpolygonheader
            | class-function: WAPIST_TTPOLYGONHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TTPOLYGONHEADER structure. Defined as TTPOLYGONHEADER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_TTPOLYGONHEADER, TTPOLYGONHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TTPOLYGONHEADER** }}*/
XB_BEGIN_STRUCTURE( TTPOLYGONHEADER )
/*{{|member_: - MEMBER DWORD cb }}*/
_XBST_DWORD( cb )
/*{{|member_: - MEMBER DWORD dwType }}*/
_XBST_DWORD( dwType )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_pointfx> wapist_POINTFX}} pfxStart }}*/
_XBST_POINTFX( pfxStart )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WCRANGE
            | _slug_: wapist_wcrange
            | class-function: WAPIST_WCRANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WCRANGE structure. Defined as WCRANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WCRANGE, WCRANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WCRANGE** }}*/
XB_BEGIN_STRUCTURE( WCRANGE )
/*{{|member_: - MEMBER SHORT wcLow }}*/
_XBST_short( wcLow )
/*{{|member_: - MEMBER USHORT cGlyphs }}*/
_XBST_USHORT( cGlyphs )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FONTSIGNATURE
            | _slug_: wapist_fontsignature
            | class-function: WAPIST_FONTSIGNATURE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FONTSIGNATURE structure. Defined as FONTSIGNATURE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FONTSIGNATURE, FONTSIGNATURE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FONTSIGNATURE** }}*/
XB_BEGIN_STRUCTURE( FONTSIGNATURE )
/*{{|member_: - MEMBER DWORD fsUsb0 }}*/
_XBST_DWORD( fsUsb0 )
/*{{|member_: - MEMBER DWORD fsUsb1 }}*/
_XBST_DWORD( fsUsb1 )
/*{{|member_: - MEMBER DWORD fsUsb2 }}*/
_XBST_DWORD( fsUsb2 )
/*{{|member_: - MEMBER DWORD fsUsb3 }}*/
_XBST_DWORD( fsUsb3 )
/*{{|member_: - MEMBER DWORD fsCsb0 }}*/
_XBST_DWORD( fsCsb0 )
/*{{|member_: - MEMBER DWORD fsCsb1 }}*/
_XBST_DWORD( fsCsb1 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MONITORINFO
            | _slug_: wapist_monitorinfo
            | class-function: WAPIST_MONITORINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MONITORINFO structure. Defined as MONITORINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MONITORINFO, MONITORINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MONITORINFO** }}*/
XB_BEGIN_STRUCTURE( MONITORINFO )
/*{{|member_: - MEMBER DWORD cbSize }}*/
_XBST_DWORD( cbSize )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcMonitor }}*/
_XBST_RECT( rcMonitor )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcWork }}*/
_XBST_RECT( rcWork )
/*{{|member_: - MEMBER DWORD dwFlags }}*/
_XBST_DWORD( dwFlags )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MONITORINFOEX
            | _slug_: wapist_monitorinfoex
            | class-function: WAPIST_MONITORINFOEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MONITORINFOEX structure. Defined as MONITORINFOEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MONITORINFOEX, MONITORINFOEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MONITORINFOEX** }}*/
XB_BEGIN_STRUCTURE( MONITORINFOEX )
/*{{|member_: - MEMBER DWORD cbSize }}*/
_XBST_DWORD( cbSize )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcMonitor }}*/
_XBST_RECT( rcMonitor )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcWork }}*/
_XBST_RECT( rcWork )
/*{{|member_: - MEMBER DWORD dwFlags }}*/
_XBST_DWORD( dwFlags )
/*{{|member_: - MEMBER SZSTR szDevice }}*/
_XBST_SZSTR( szDevice, CCHDEVICENAME )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PAINTSTRUCT
            | _slug_: wapist_paintstruct
            | class-function: WAPIST_PAINTSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PAINTSTRUCT structure. Defined as PAINTSTRUCT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PAINTSTRUCT, PAINTSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PAINTSTRUCT** }}*/
XB_BEGIN_STRUCTURE( PAINTSTRUCT )
/*{{|member_: - MEMBER HDC hdc }}*/
_XBST_HDC( hdc )
/*{{|member_: - MEMBER BOOL fErase }}*/
_XBST_BOOL( fErase )
/*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcPaint }}*/
_XBST_RECT( rcPaint )
/*{{|member_: - MEMBER BOOL fRestore }}*/
_XBST_BOOL( fRestore )
/*{{|member_: - MEMBER BOOL fIncUpdate }}*/
_XBST_BOOL( fIncUpdate )
/*{{|member_: - MEMBER BINSTR rgbReserved }}*/
_XBST_BINSTR( rgbReserved, 32 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SYSTEMTIME
            | _slug_: wapist_systemtime
            | class-function: WAPIST_SYSTEMTIME
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SYSTEMTIME structure. Defined as SYSTEMTIME in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SYSTEMTIME, SYSTEMTIME, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SYSTEMTIME** }}*/
XB_BEGIN_STRUCTURE( SYSTEMTIME )
/*{{|member_: - MEMBER WORD wYear }}*/
_XBST_WORD( wYear )
/*{{|member_: - MEMBER WORD wMonth }}*/
_XBST_WORD( wMonth )
/*{{|member_: - MEMBER WORD wDayOfWeek }}*/
_XBST_WORD( wDayOfWeek )
/*{{|member_: - MEMBER WORD wDay }}*/
_XBST_WORD( wDay )
/*{{|member_: - MEMBER WORD wHour }}*/
_XBST_WORD( wHour )
/*{{|member_: - MEMBER WORD wMinute }}*/
_XBST_WORD( wMinute )
/*{{|member_: - MEMBER WORD wSecond }}*/
_XBST_WORD( wSecond )
/*{{|member_: - MEMBER WORD wMilliseconds }}*/
_XBST_WORD( wMilliseconds )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ADDJOB_INFO_1
            | _slug_: wapist_addjob_info_1
            | class-function: WAPIST_ADDJOB_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ADDJOB_INFO_1 structure. Defined as ADDJOB_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ADDJOB_INFO_1, ADDJOB_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ADDJOB_INFO_1** }}*/
XB_BEGIN_STRUCTURE( ADDJOB_INFO_1 )
/*{{|member_: - MEMBER LPSTR Path }}*/
_XBST_LPSTR( Path )
/*{{|member_: - MEMBER DWORD JobId }}*/
_XBST_DWORD( JobId )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DATATYPES_INFO_1
            | _slug_: wapist_datatypes_info_1
            | class-function: WAPIST_DATATYPES_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DATATYPES_INFO_1 structure. Defined as DATATYPES_INFO_1 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DATATYPES_INFO_1, DATATYPES_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DATATYPES_INFO_1** }}*/
XB_BEGIN_STRUCTURE( DATATYPES_INFO_1 )
/*{{|member_: - MEMBER LPSTR pName }}*/
_XBST_LPSTR( pName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DEVMODEW
            | _slug_: wapist_devmodew
            | class-function: WAPIST_DEVMODEW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DEVMODEW structure. Defined as DEVMODE in ot4xb_wapist_map.ch: the map
              names the neutral WAPIST_DEVMODE compatibility export, which returns this Unicode class object.
            | note: WAPIST_DEVMODE is the neutral compatibility export mapped to WAPIST_DEVMODEW. It is not a
              separate class; it returns the Unicode DEVMODEW class object.
            | note: Both DEVMODE classes are built by the shared devmode_structure() helper below; only dmDeviceName
              differs between the ANSI and Unicode variants, dmFormName stays an ANSI szStr member in both.
            | note: dmOrientation through dmPrintQuality, dmPosition, dmDisplayOrientation and dmDisplayFixedOutput
              overlay the same storage (a union in the WinApi declaration); dmDisplayFlags and dmNup overlay each
              other too.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-devmodew
            | _kw_: WAPIST_DEVMODEW, DEVMODEW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DEVMODEW** }}*/
   /*{{|member_: - MEMBER SZWSTR dmDeviceName }}*/
   /*{{|member_: - MEMBER WORD dmSpecVersion }}*/
   /*{{|member_: - MEMBER WORD dmDriverVersion }}*/
   /*{{|member_: - MEMBER WORD dmSize }}*/
   /*{{|member_: - MEMBER WORD dmDriverExtra }}*/
   /*{{|member_: - MEMBER DWORD dmFields }}*/
   /*{{|member_: - MEMBER SHORT dmOrientation }}*/
   /*{{|member_: - MEMBER SHORT dmPaperSize }}*/
   /*{{|member_: - MEMBER SHORT dmPaperLength }}*/
   /*{{|member_: - MEMBER SHORT dmPaperWidth }}*/
   /*{{|member_: - MEMBER SHORT dmScale }}*/
   /*{{|member_: - MEMBER SHORT dmCopies }}*/
   /*{{|member_: - MEMBER SHORT dmDefaultSource }}*/
   /*{{|member_: - MEMBER SHORT dmPrintQuality }}*/
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_pointl> wapist_POINTL}} dmPosition }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayOrientation }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFixedOutput }}*/
   /*{{|member_: - MEMBER SHORT dmColor }}*/
   /*{{|member_: - MEMBER SHORT dmDuplex }}*/
   /*{{|member_: - MEMBER SHORT dmYResolution }}*/
   /*{{|member_: - MEMBER SHORT dmTTOption }}*/
   /*{{|member_: - MEMBER SHORT dmCollate }}*/
   /*{{|member_: - MEMBER SZSTR dmFormName }}*/
   /*{{|member_: - MEMBER WORD dmLogPixels }}*/
   /*{{|member_: - MEMBER DWORD dmBitsPerPel }}*/
   /*{{|member_: - MEMBER DWORD dmPelsWidth }}*/
   /*{{|member_: - MEMBER DWORD dmPelsHeight }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFlags }}*/
   /*{{|member_: - MEMBER DWORD dmNup }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFrequency }}*/
   /*{{|member_: - MEMBER DWORD dmICMMethod }}*/
   /*{{|member_: - MEMBER DWORD dmICMIntent }}*/
   /*{{|member_: - MEMBER DWORD dmMediaType }}*/
   /*{{|member_: - MEMBER DWORD dmDitherType }}*/
   /*{{|member_: - MEMBER DWORD dmReserved1 }}*/
   /*{{|member_: - MEMBER DWORD dmReserved2 }}*/
   /*{{|member_: - MEMBER DWORD dmPanningWidth }}*/
   /*{{|member_: - MEMBER DWORD dmPanningHeight }}*/
/*{{|:**END STRUCTURE** }}*/
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
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DEVMODEA
            | _slug_: wapist_devmodea
            | class-function: WAPIST_DEVMODEA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DEVMODEA structure.
            | note: Built by the shared devmode_structure() helper below (the bUnicode = FALSE branch).
            | note: dmOrientation through dmPrintQuality, dmPosition, dmDisplayOrientation and dmDisplayFixedOutput
              overlay the same storage (a union in the WinApi declaration); dmDisplayFlags and dmNup overlay each
              other too.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-devmodea
            | _kw_: WAPIST_DEVMODEA, DEVMODEA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DEVMODEA** }}*/
   /*{{|member_: - MEMBER SZSTR dmDeviceName }}*/
   /*{{|member_: - MEMBER WORD dmSpecVersion }}*/
   /*{{|member_: - MEMBER WORD dmDriverVersion }}*/
   /*{{|member_: - MEMBER WORD dmSize }}*/
   /*{{|member_: - MEMBER WORD dmDriverExtra }}*/
   /*{{|member_: - MEMBER DWORD dmFields }}*/
   /*{{|member_: - MEMBER SHORT dmOrientation }}*/
   /*{{|member_: - MEMBER SHORT dmPaperSize }}*/
   /*{{|member_: - MEMBER SHORT dmPaperLength }}*/
   /*{{|member_: - MEMBER SHORT dmPaperWidth }}*/
   /*{{|member_: - MEMBER SHORT dmScale }}*/
   /*{{|member_: - MEMBER SHORT dmCopies }}*/
   /*{{|member_: - MEMBER SHORT dmDefaultSource }}*/
   /*{{|member_: - MEMBER SHORT dmPrintQuality }}*/
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_pointl> wapist_POINTL}} dmPosition }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayOrientation }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFixedOutput }}*/
   /*{{|member_: - MEMBER SHORT dmColor }}*/
   /*{{|member_: - MEMBER SHORT dmDuplex }}*/
   /*{{|member_: - MEMBER SHORT dmYResolution }}*/
   /*{{|member_: - MEMBER SHORT dmTTOption }}*/
   /*{{|member_: - MEMBER SHORT dmCollate }}*/
   /*{{|member_: - MEMBER SZSTR dmFormName }}*/
   /*{{|member_: - MEMBER WORD dmLogPixels }}*/
   /*{{|member_: - MEMBER DWORD dmBitsPerPel }}*/
   /*{{|member_: - MEMBER DWORD dmPelsWidth }}*/
   /*{{|member_: - MEMBER DWORD dmPelsHeight }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFlags }}*/
   /*{{|member_: - MEMBER DWORD dmNup }}*/
   /*{{|member_: - MEMBER DWORD dmDisplayFrequency }}*/
   /*{{|member_: - MEMBER DWORD dmICMMethod }}*/
   /*{{|member_: - MEMBER DWORD dmICMIntent }}*/
   /*{{|member_: - MEMBER DWORD dmMediaType }}*/
   /*{{|member_: - MEMBER DWORD dmDitherType }}*/
   /*{{|member_: - MEMBER DWORD dmReserved1 }}*/
   /*{{|member_: - MEMBER DWORD dmReserved2 }}*/
   /*{{|member_: - MEMBER DWORD dmPanningWidth }}*/
   /*{{|member_: - MEMBER DWORD dmPanningHeight }}*/
/*{{|:**END STRUCTURE** }}*/
void __cdecl WAPIST_DEVMODEA( XppParamList pl )
{
   devmode_structure( pl, FALSE );
}
/*{{end-class}}*/

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
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DOC_INFO_1
            | _slug_: wapist_doc_info_1
            | class-function: WAPIST_DOC_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DOC_INFO_1 structure. Defined as DOC_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DOC_INFO_1, DOC_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DOC_INFO_1** }}*/
XB_BEGIN_STRUCTURE( DOC_INFO_1 )
  /*{{|member_: - MEMBER LPSTR pDocName }}*/
  _XBST_LPSTR( pDocName     )
  /*{{|member_: - MEMBER LPSTR pOutputFile }}*/
  _XBST_LPSTR( pOutputFile  )
  /*{{|member_: - MEMBER LPSTR pDatatype }}*/
  _XBST_LPSTR( pDatatype    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DOC_INFO_2
            | _slug_: wapist_doc_info_2
            | class-function: WAPIST_DOC_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DOC_INFO_2 structure. Defined as DOC_INFO_2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DOC_INFO_2, DOC_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DOC_INFO_2** }}*/
XB_BEGIN_STRUCTURE( DOC_INFO_2 )
  /*{{|member_: - MEMBER LPSTR pDocName }}*/
  _XBST_LPSTR( pDocName    )
  /*{{|member_: - MEMBER LPSTR pOutputFile }}*/
  _XBST_LPSTR( pOutputFile )
  /*{{|member_: - MEMBER LPSTR pDatatype }}*/
  _XBST_LPSTR( pDatatype   )
  /*{{|member_: - MEMBER DWORD dwMode }}*/
  _XBST_DWORD( dwMode      )
  /*{{|member_: - MEMBER DWORD JobId }}*/
  _XBST_DWORD( JobId       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DOC_INFO_3
            | _slug_: wapist_doc_info_3
            | class-function: WAPIST_DOC_INFO_3
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DOC_INFO_3 structure. Defined as DOC_INFO_3 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DOC_INFO_3, DOC_INFO_3, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DOC_INFO_3** }}*/
XB_BEGIN_STRUCTURE( DOC_INFO_3 )
  /*{{|member_: - MEMBER LPSTR pDocName }}*/
  _XBST_LPSTR( pDocName    )
  /*{{|member_: - MEMBER LPSTR pOutputFile }}*/
  _XBST_LPSTR( pOutputFile )
  /*{{|member_: - MEMBER LPSTR pDatatype }}*/
  _XBST_LPSTR( pDatatype   )
  /*{{|member_: - MEMBER DWORD dwFlags }}*/
  _XBST_DWORD( dwFlags     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DOCINFO
            | _slug_: wapist_docinfo
            | class-function: WAPIST_DOCINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DOCINFO structure. Defined as DOCINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DOCINFO, DOCINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DOCINFO** }}*/
XB_BEGIN_STRUCTURE( DOCINFO )
  /*{{|member_: - MEMBER INT cbSize }}*/
  _XBST_int   (  cbSize         )
  /*{{|member_: - MEMBER LPSTR lpszDocName }}*/
  _XBST_LPSTR (  lpszDocName    )
  /*{{|member_: - MEMBER LPSTR lpszOutput }}*/
  _XBST_LPSTR (  lpszOutput     )
  /*{{|member_: - MEMBER LPSTR lpszDatatype }}*/
  _XBST_LPSTR (  lpszDatatype   )
  /*{{|member_: - MEMBER DWORD fwType }}*/
  _XBST_DWORD (  fwType         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRAWPATRECT
            | _slug_: wapist_drawpatrect
            | class-function: WAPIST_DRAWPATRECT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRAWPATRECT structure. Defined as DRAWPATRECT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRAWPATRECT, DRAWPATRECT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRAWPATRECT** }}*/
XB_BEGIN_STRUCTURE( DRAWPATRECT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptPosition }}*/
   _XBST_POINT ( ptPosition  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptSize }}*/
   _XBST_POINT ( ptSize      )
   /*{{|member_: - MEMBER WORD wStyle }}*/
   _XBST_WORD  ( wStyle      )
   /*{{|member_: - MEMBER WORD wPattern }}*/
   _XBST_WORD  ( wPattern    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_1
            | _slug_: wapist_driver_info_1
            | class-function: WAPIST_DRIVER_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_1 structure. Defined as DRIVER_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_1, DRIVER_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_1** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_1 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_2
            | _slug_: wapist_driver_info_2
            | class-function: WAPIST_DRIVER_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_2 structure. Defined as DRIVER_INFO_2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_2, DRIVER_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_2** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_2 )
   /*{{|member_: - MEMBER DWORD cVersion }}*/
   _XBST_DWORD ( cVersion      )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR ( pName         )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR ( pEnvironment  )
   /*{{|member_: - MEMBER LPSTR pDriverPath }}*/
   _XBST_LPSTR ( pDriverPath   )
   /*{{|member_: - MEMBER LPSTR pDataFile }}*/
   _XBST_LPSTR ( pDataFile     )
   /*{{|member_: - MEMBER LPSTR pConfigFile }}*/
   _XBST_LPSTR ( pConfigFile   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_3
            | _slug_: wapist_driver_info_3
            | class-function: WAPIST_DRIVER_INFO_3
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_3 structure. Defined as DRIVER_INFO_3 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_3, DRIVER_INFO_3, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_3** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_3 )
   /*{{|member_: - MEMBER DWORD cVersion }}*/
   _XBST_DWORD (  cVersion          )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR ( pName              )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR ( pEnvironment       )
   /*{{|member_: - MEMBER LPSTR pDriverPath }}*/
   _XBST_LPSTR ( pDriverPath        )
   /*{{|member_: - MEMBER LPSTR pDataFile }}*/
   _XBST_LPSTR ( pDataFile          )
   /*{{|member_: - MEMBER LPSTR pConfigFile }}*/
   _XBST_LPSTR ( pConfigFile        )
   /*{{|member_: - MEMBER LPSTR pHelpFile }}*/
   _XBST_LPSTR ( pHelpFile          )
   /*{{|member_: - MEMBER LPSTR pDependentFiles }}*/
   _XBST_LPSTR ( pDependentFiles    )
   /*{{|member_: - MEMBER LPSTR pMonitorName }}*/
   _XBST_LPSTR ( pMonitorName       )
   /*{{|member_: - MEMBER LPSTR pDefaultDataType }}*/
   _XBST_LPSTR ( pDefaultDataType   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_4
            | _slug_: wapist_driver_info_4
            | class-function: WAPIST_DRIVER_INFO_4
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_4 structure. Defined as DRIVER_INFO_4 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_4, DRIVER_INFO_4, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_4** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_4 )
   /*{{|member_: - MEMBER DWORD cVersion }}*/
   _XBST_DWORD (  cVersion          )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR (  pName             )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR (  pEnvironment      )
   /*{{|member_: - MEMBER LPSTR pDriverPath }}*/
   _XBST_LPSTR (  pDriverPath       )
   /*{{|member_: - MEMBER LPSTR pDataFile }}*/
   _XBST_LPSTR (  pDataFile         )
   /*{{|member_: - MEMBER LPSTR pConfigFile }}*/
   _XBST_LPSTR (  pConfigFile       )
   /*{{|member_: - MEMBER LPSTR pHelpFile }}*/
   _XBST_LPSTR (  pHelpFile         )
   /*{{|member_: - MEMBER LPSTR pDependentFiles }}*/
   _XBST_LPSTR (  pDependentFiles   )
   /*{{|member_: - MEMBER LPSTR pMonitorName }}*/
   _XBST_LPSTR (  pMonitorName      )
   /*{{|member_: - MEMBER LPSTR pDefaultDataType }}*/
   _XBST_LPSTR (  pDefaultDataType  )
   /*{{|member_: - MEMBER LPSTR pszzPreviousNames }}*/
   _XBST_LPSTR (  pszzPreviousNames )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_5
            | _slug_: wapist_driver_info_5
            | class-function: WAPIST_DRIVER_INFO_5
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_5 structure. Defined as DRIVER_INFO_5 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_5, DRIVER_INFO_5, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_5** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_5 )
   /*{{|member_: - MEMBER DWORD cVersion }}*/
   _XBST_DWORD  (  cVersion             )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR  (  pName                )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR  (  pEnvironment         )
   /*{{|member_: - MEMBER LPSTR pDriverPath }}*/
   _XBST_LPSTR  (  pDriverPath          )
   /*{{|member_: - MEMBER LPSTR pDataFile }}*/
   _XBST_LPSTR  (  pDataFile            )
   /*{{|member_: - MEMBER LPSTR pConfigFile }}*/
   _XBST_LPSTR  (  pConfigFile          )
   /*{{|member_: - MEMBER DWORD dwDriverAttributes }}*/
   _XBST_DWORD  (  dwDriverAttributes   )
   /*{{|member_: - MEMBER DWORD dwConfigVersion }}*/
   _XBST_DWORD  (  dwConfigVersion      )
   /*{{|member_: - MEMBER DWORD dwDriverVersion }}*/
   _XBST_DWORD  (  dwDriverVersion      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRIVER_INFO_6
            | _slug_: wapist_driver_info_6
            | class-function: WAPIST_DRIVER_INFO_6
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRIVER_INFO_6 structure. Defined as DRIVER_INFO_6 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRIVER_INFO_6, DRIVER_INFO_6, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRIVER_INFO_6** }}*/
XB_BEGIN_STRUCTURE( DRIVER_INFO_6 )
   /*{{|member_: - MEMBER DWORD cVersion }}*/
   _XBST_DWORD       (  cVersion           )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR       (  pName              )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR       (  pEnvironment       )
   /*{{|member_: - MEMBER LPSTR pDriverPath }}*/
   _XBST_LPSTR       (  pDriverPath        )
   /*{{|member_: - MEMBER LPSTR pDataFile }}*/
   _XBST_LPSTR       (  pDataFile          )
   /*{{|member_: - MEMBER LPSTR pConfigFile }}*/
   _XBST_LPSTR       (  pConfigFile        )
   /*{{|member_: - MEMBER LPSTR pHelpFile }}*/
   _XBST_LPSTR       (  pHelpFile          )
   /*{{|member_: - MEMBER LPSTR pDependentFiles }}*/
   _XBST_LPSTR       (  pDependentFiles    )
   /*{{|member_: - MEMBER LPSTR pMonitorName }}*/
   _XBST_LPSTR       (  pMonitorName       )
   /*{{|member_: - MEMBER LPSTR pDefaultDataType }}*/
   _XBST_LPSTR       (  pDefaultDataType   )
   /*{{|member_: - MEMBER LPSTR pszzPreviousNames }}*/
   _XBST_LPSTR       (  pszzPreviousNames  )
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftDriverDate }}*/
   _XBST_FILETIME    (  ftDriverDate       )
   /*{{|member_: - MEMBER DWORD64 dwlDriverVersion }}*/
   _XBST_DWORDLONG   (  dwlDriverVersion   )
   /*{{|member_: - MEMBER LPSTR pszMfgName }}*/
   _XBST_LPSTR       (  pszMfgName         )
   /*{{|member_: - MEMBER LPSTR pszOEMUrl }}*/
   _XBST_LPSTR       (  pszOEMUrl          )
   /*{{|member_: - MEMBER LPSTR pszHardwareID }}*/
   _XBST_LPSTR       (  pszHardwareID      )
   /*{{|member_: - MEMBER LPSTR pszProvider }}*/
   _XBST_LPSTR       (  pszProvider        )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FORM_INFO_1
            | _slug_: wapist_form_info_1
            | class-function: WAPIST_FORM_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FORM_INFO_1 structure. Defined as FORM_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FORM_INFO_1, FORM_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FORM_INFO_1** }}*/
XB_BEGIN_STRUCTURE( FORM_INFO_1 )
   /*{{|member_: - MEMBER DWORD Flags }}*/
   _XBST_DWORD ( Flags         )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR ( pName         )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_sizel> wapist_SIZEL}} Size }}*/
   _XBST_SIZEL ( Size          )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rectl> wapist_RECTL}} ImageableArea }}*/
   _XBST_RECTL ( ImageableArea )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_JOB_INFO_1
            | _slug_: wapist_job_info_1
            | class-function: WAPIST_JOB_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi JOB_INFO_1 structure. Defined as JOB_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_JOB_INFO_1, JOB_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  JOB_INFO_1** }}*/
XB_BEGIN_STRUCTURE( JOB_INFO_1 )
   /*{{|member_: - MEMBER DWORD JobId }}*/
   _XBST_DWORD       ( JobId         )
   /*{{|member_: - MEMBER LPSTR pPrinterName }}*/
   _XBST_LPSTR       ( pPrinterName  )
   /*{{|member_: - MEMBER LPSTR pMachineName }}*/
   _XBST_LPSTR       ( pMachineName  )
   /*{{|member_: - MEMBER LPSTR pUserName }}*/
   _XBST_LPSTR       ( pUserName     )
   /*{{|member_: - MEMBER LPSTR pDocument }}*/
   _XBST_LPSTR       ( pDocument     )
   /*{{|member_: - MEMBER LPSTR pDatatype }}*/
   _XBST_LPSTR       ( pDatatype     )
   /*{{|member_: - MEMBER LPSTR pStatus }}*/
   _XBST_LPSTR       ( pStatus       )
   /*{{|member_: - MEMBER DWORD Status }}*/
   _XBST_DWORD       ( Status        )
   /*{{|member_: - MEMBER DWORD Priority }}*/
   _XBST_DWORD       ( Priority      )
   /*{{|member_: - MEMBER DWORD Position }}*/
   _XBST_DWORD       ( Position      )
   /*{{|member_: - MEMBER DWORD TotalPages }}*/
   _XBST_DWORD       ( TotalPages    )
   /*{{|member_: - MEMBER DWORD PagesPrinted }}*/
   _XBST_DWORD       ( PagesPrinted  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} Submitted }}*/
   _XBST_SYSTEMTIME  ( Submitted     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_JOB_INFO_2
            | _slug_: wapist_job_info_2
            | class-function: WAPIST_JOB_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi JOB_INFO_2 structure. Defined as JOB_INFO_2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_JOB_INFO_2, JOB_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  JOB_INFO_2** }}*/
XB_BEGIN_STRUCTURE( JOB_INFO_2 )
   /*{{|member_: - MEMBER DWORD JobId }}*/
   _XBST_DWORD      ( JobId                 )
   /*{{|member_: - MEMBER LPSTR pPrinterName }}*/
   _XBST_LPSTR      ( pPrinterName          )
   /*{{|member_: - MEMBER LPSTR pMachineName }}*/
   _XBST_LPSTR      ( pMachineName          )
   /*{{|member_: - MEMBER LPSTR pUserName }}*/
   _XBST_LPSTR      ( pUserName             )
   /*{{|member_: - MEMBER LPSTR pDocument }}*/
   _XBST_LPSTR      ( pDocument             )
   /*{{|member_: - MEMBER LPSTR pNotifyName }}*/
   _XBST_LPSTR      ( pNotifyName           )
   /*{{|member_: - MEMBER LPSTR pDatatype }}*/
   _XBST_LPSTR      ( pDatatype             )
   /*{{|member_: - MEMBER LPSTR pPrintProcessor }}*/
   _XBST_LPSTR      ( pPrintProcessor       )
   /*{{|member_: - MEMBER LPSTR pParameters }}*/
   _XBST_LPSTR      ( pParameters           )
   /*{{|member_: - MEMBER LPSTR pDriverName }}*/
   _XBST_LPSTR      ( pDriverName           )
   /*{{|member_: - MEMBER POINTER32 pDevMode }}*/
   _XBST_POINTER32  ( pDevMode              )
   /*{{|member_: - MEMBER LPSTR pStatus }}*/
   _XBST_LPSTR      ( pStatus               )
   /*{{|member_: - MEMBER POINTER32 pSecurityDescriptor }}*/
   _XBST_POINTER32  ( pSecurityDescriptor   )
   /*{{|member_: - MEMBER DWORD Status }}*/
   _XBST_DWORD      ( Status                )
   /*{{|member_: - MEMBER DWORD Priority }}*/
   _XBST_DWORD      ( Priority              )
   /*{{|member_: - MEMBER DWORD Position }}*/
   _XBST_DWORD      ( Position              )
   /*{{|member_: - MEMBER DWORD StartTime }}*/
   _XBST_DWORD      ( StartTime             )
   /*{{|member_: - MEMBER DWORD UntilTime }}*/
   _XBST_DWORD      ( UntilTime             )
   /*{{|member_: - MEMBER DWORD TotalPages }}*/
   _XBST_DWORD      ( TotalPages            )
   /*{{|member_: - MEMBER DWORD Size }}*/
   _XBST_DWORD      ( Size                  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} Submitted }}*/
   _XBST_SYSTEMTIME ( Submitted             )
   /*{{|member_: - MEMBER DWORD Time }}*/
   _XBST_DWORD      ( Time                  )
   /*{{|member_: - MEMBER DWORD PagesPrinted }}*/
   _XBST_DWORD      ( PagesPrinted          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_JOB_INFO_3
            | _slug_: wapist_job_info_3
            | class-function: WAPIST_JOB_INFO_3
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi JOB_INFO_3 structure. Defined as JOB_INFO_3 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_JOB_INFO_3, JOB_INFO_3, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  JOB_INFO_3** }}*/
XB_BEGIN_STRUCTURE( JOB_INFO_3 )
   /*{{|member_: - MEMBER DWORD JobId }}*/
   _XBST_DWORD  ( JobId     )
   /*{{|member_: - MEMBER DWORD NextJobId }}*/
   _XBST_DWORD  ( NextJobId )
   /*{{|member_: - MEMBER DWORD Reserved }}*/
   _XBST_DWORD  ( Reserved  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MONITOR_INFO_1
            | _slug_: wapist_monitor_info_1
            | class-function: WAPIST_MONITOR_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MONITOR_INFO_1 structure. Defined as MONITOR_INFO_1 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MONITOR_INFO_1, MONITOR_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MONITOR_INFO_1** }}*/
XB_BEGIN_STRUCTURE( MONITOR_INFO_1 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MONITOR_INFO_2
            | _slug_: wapist_monitor_info_2
            | class-function: WAPIST_MONITOR_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MONITOR_INFO_2 structure. Defined as MONITOR_INFO_2 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MONITOR_INFO_2, MONITOR_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MONITOR_INFO_2** }}*/
XB_BEGIN_STRUCTURE( MONITOR_INFO_2 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR ( pName        )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR ( pEnvironment )
   /*{{|member_: - MEMBER LPSTR pDLLName }}*/
   _XBST_LPSTR ( pDLLName     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PORT_INFO_1
            | _slug_: wapist_port_info_1
            | class-function: WAPIST_PORT_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PORT_INFO_1 structure. Defined as PORT_INFO_1 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PORT_INFO_1, PORT_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PORT_INFO_1** }}*/
XB_BEGIN_STRUCTURE( PORT_INFO_1 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PORT_INFO_2
            | _slug_: wapist_port_info_2
            | class-function: WAPIST_PORT_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PORT_INFO_2 structure. Defined as PORT_INFO_2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PORT_INFO_2, PORT_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PORT_INFO_2** }}*/
XB_BEGIN_STRUCTURE( PORT_INFO_2 )
   /*{{|member_: - MEMBER LPSTR pPortName }}*/
   _XBST_LPSTR ( pPortName    )
   /*{{|member_: - MEMBER LPSTR pMonitorName }}*/
   _XBST_LPSTR ( pMonitorName )
   /*{{|member_: - MEMBER LPSTR pDescription }}*/
   _XBST_LPSTR ( pDescription )
   /*{{|member_: - MEMBER DWORD fPortType }}*/
   _XBST_DWORD ( fPortType    )
   /*{{|member_: - MEMBER DWORD Reserved }}*/
   _XBST_DWORD ( Reserved     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PORT_INFO_3
            | _slug_: wapist_port_info_3
            | class-function: WAPIST_PORT_INFO_3
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PORT_INFO_3 structure. Defined as PORT_INFO_3 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PORT_INFO_3, PORT_INFO_3, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PORT_INFO_3** }}*/
XB_BEGIN_STRUCTURE( PORT_INFO_3 )
   /*{{|member_: - MEMBER DWORD dwStatus }}*/
   _XBST_DWORD( dwStatus   )
   /*{{|member_: - MEMBER LPSTR pszStatus }}*/
   _XBST_LPSTR( pszStatus  )
   /*{{|member_: - MEMBER DWORD dwSeverity }}*/
   _XBST_DWORD( dwSeverity )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_DEFAULTS
            | _slug_: wapist_printer_defaults
            | class-function: WAPIST_PRINTER_DEFAULTS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_DEFAULTS structure. Defined as PRINTER_DEFAULTS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_DEFAULTS, PRINTER_DEFAULTS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_DEFAULTS** }}*/
XB_BEGIN_STRUCTURE( PRINTER_DEFAULTS )
   /*{{|member_: - MEMBER LPSTR pDatatype }}*/
   _XBST_LPSTR       ( pDatatype     )
   /*{{|member_: - MEMBER POINTER32 pDevMode }}*/
   _XBST_POINTER32   ( pDevMode      )
   /*{{|member_: - MEMBER ACCESS_MASK DesiredAccess }}*/
   _XBST_ACCESS_MASK ( DesiredAccess )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_ENUM_VALUES
            | _slug_: wapist_printer_enum_values
            | class-function: WAPIST_PRINTER_ENUM_VALUES
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_ENUM_VALUES structure. Defined as PRINTER_ENUM_VALUES in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_ENUM_VALUES, PRINTER_ENUM_VALUES, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_ENUM_VALUES** }}*/
XB_BEGIN_STRUCTURE( PRINTER_ENUM_VALUES )
   /*{{|member_: - MEMBER LPSTR pValueName }}*/
   _XBST_LPSTR   ( pValueName  )
   /*{{|member_: - MEMBER DWORD cbValueName }}*/
   _XBST_DWORD   ( cbValueName )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD   ( dwType      )
   /*{{|member_: - MEMBER LPBYTE pData }}*/
   _XBST_LPBYTE  ( pData       )
   /*{{|member_: - MEMBER DWORD cbData }}*/
   _XBST_DWORD   ( cbData      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_1
            | _slug_: wapist_printer_info_1
            | class-function: WAPIST_PRINTER_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_1 structure. Defined as PRINTER_INFO_1 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-1
            | _kw_: WAPIST_PRINTER_INFO_1, PRINTER_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_1** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_1 )
   /*{{|member_: - MEMBER DWORD Flags }}*/
   _XBST_DWORD ( Flags        )
   /*{{|member_: - MEMBER LPSTR pDescription }}*/
   /*{{|member_: - MEMBER DYNSZ cDescription |desc_: Helper member mapped over ::pDescription. }}*/
   _XBST_LPSTR_DYNSZ ( pDescription , cDescription)
   /*{{|member_: - MEMBER LPSTR pName }}*/
   /*{{|member_: - MEMBER DYNSZ cName |desc_: Helper member mapped over ::pName. }}*/
   _XBST_LPSTR_DYNSZ ( pName        , cName       )
   /*{{|member_: - MEMBER LPSTR pComment }}*/
   /*{{|member_: - MEMBER DYNSZ cComment |desc_: Helper member mapped over ::pComment. }}*/
   _XBST_LPSTR_DYNSZ ( pComment     , cComment    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_2
            | _slug_: wapist_printer_info_2
            | class-function: WAPIST_PRINTER_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_2 structure. Defined as PRINTER_INFO_2 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-2
            | _kw_: WAPIST_PRINTER_INFO_2, PRINTER_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_2** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_2 )
   /*{{|member_: - MEMBER LPSTR pServerName }}*/
   /*{{|member_: - MEMBER DYNSZ cServerName |desc_: Helper member mapped over ::pServerName. }}*/
   _XBST_LPSTR_DYNSZ ( pServerName   , cServerName          )
   /*{{|member_: - MEMBER LPSTR pPrinterName }}*/
   /*{{|member_: - MEMBER DYNSZ cPrinterName |desc_: Helper member mapped over ::pPrinterName. }}*/
   _XBST_LPSTR_DYNSZ ( pPrinterName  , cPrinterName         )
   /*{{|member_: - MEMBER LPSTR pShareName }}*/
   /*{{|member_: - MEMBER DYNSZ cShareName |desc_: Helper member mapped over ::pShareName. }}*/
   _XBST_LPSTR_DYNSZ ( pShareName    , cShareName           )
   /*{{|member_: - MEMBER LPSTR pPortName }}*/
   /*{{|member_: - MEMBER DYNSZ cPortName |desc_: Helper member mapped over ::pPortName. }}*/
   _XBST_LPSTR_DYNSZ ( pPortName     , cPortName            )
   /*{{|member_: - MEMBER LPSTR pDriverName }}*/
   /*{{|member_: - MEMBER DYNSZ cDriverName |desc_: Helper member mapped over ::pDriverName. }}*/
   _XBST_LPSTR_DYNSZ ( pDriverName   , cDriverName          )
   /*{{|member_: - MEMBER LPSTR pComment }}*/
   /*{{|member_: - MEMBER DYNSZ cComment |desc_: Helper member mapped over ::pComment. }}*/
   _XBST_LPSTR_DYNSZ ( pComment      , cComment             )
   /*{{|member_: - MEMBER LPSTR pLocation }}*/
   /*{{|member_: - MEMBER DYNSZ cLocation |desc_: Helper member mapped over ::pLocation. }}*/
   _XBST_LPSTR_DYNSZ ( pLocation     , cLocation            )
   /*{{|member_: - MEMBER PDEVMODE pDevMode }}*/
   _XBST_POINTER32 ( pDevMode            )
   /*{{|member_: - MEMBER LPSTR pSepFile }}*/
   /*{{|member_: - MEMBER DYNSZ cSepFile |desc_: Helper member mapped over ::pSepFile. }}*/
   _XBST_LPSTR_DYNSZ ( pSepFile         , cSepFile           )
   /*{{|member_: - MEMBER LPSTR pPrintProcessor }}*/
   /*{{|member_: - MEMBER DYNSZ cPrintProcessor |desc_: Helper member mapped over ::pPrintProcessor. }}*/
   _XBST_LPSTR_DYNSZ ( pPrintProcessor  , cPrintProcessor    )
   /*{{|member_: - MEMBER LPSTR pDatatype }}*/
   /*{{|member_: - MEMBER DYNSZ cDatatype |desc_: Helper member mapped over ::pDatatype. }}*/
   _XBST_LPSTR_DYNSZ ( pDatatype        , cDatatype          )
   /*{{|member_: - MEMBER LPSTR pParameters }}*/
   /*{{|member_: - MEMBER DYNSZ cParameters |desc_: Helper member mapped over ::pParameters. }}*/
   _XBST_LPSTR_DYNSZ ( pParameters      , cParameters        )
   /*{{|member_: - MEMBER PSECURITY_DESCRIPTOR pSecurityDescriptor }}*/
   _XBST_POINTER32 ( pSecurityDescriptor )
   /*{{|member_: - MEMBER DWORD Attributes }}*/
   _XBST_DWORD     ( Attributes          )
   /*{{|member_: - MEMBER DWORD Priority }}*/
   _XBST_DWORD     ( Priority            )
   /*{{|member_: - MEMBER DWORD DefaultPriority }}*/
   _XBST_DWORD     ( DefaultPriority     )
   /*{{|member_: - MEMBER DWORD StartTime }}*/
   _XBST_DWORD     ( StartTime           )
   /*{{|member_: - MEMBER DWORD UntilTime }}*/
   _XBST_DWORD     ( UntilTime           )
   /*{{|member_: - MEMBER DWORD Status }}*/
   _XBST_DWORD     ( Status              )
   /*{{|member_: - MEMBER DWORD cJobs }}*/
   _XBST_DWORD     ( cJobs               )
   /*{{|member_: - MEMBER DWORD AveragePPM }}*/
   _XBST_DWORD     ( AveragePPM          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_3
            | _slug_: wapist_printer_info_3
            | class-function: WAPIST_PRINTER_INFO_3
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_3 structure. Defined as PRINTER_INFO_3 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_INFO_3, PRINTER_INFO_3, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_3** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_3 )
   /*{{|member_: - MEMBER POINTER32 pSecurityDescriptor }}*/
   _XBST_POINTER32 ( pSecurityDescriptor )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_4
            | _slug_: wapist_printer_info_4
            | class-function: WAPIST_PRINTER_INFO_4
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_4 structure. Defined as PRINTER_INFO_4 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-4
            | _kw_: WAPIST_PRINTER_INFO_4, PRINTER_INFO_4, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_4** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_4 )
   /*{{|member_: - MEMBER LPSTR pPrinterName }}*/
   /*{{|member_: - MEMBER DYNSZ cPrinterName |desc_: Helper member mapped over ::pPrinterName. }}*/
   _XBST_LPSTR_DYNSZ ( pPrinterName , cPrinterName)
   /*{{|member_: - MEMBER LPSTR pServerName }}*/
   /*{{|member_: - MEMBER DYNSZ cServerName |desc_: Helper member mapped over ::pServerName. }}*/
   _XBST_LPSTR_DYNSZ ( pServerName  , cServerName )
   /*{{|member_: - MEMBER DWORD Attributes }}*/
   _XBST_DWORD ( Attributes   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_5
            | _slug_: wapist_printer_info_5
            | class-function: WAPIST_PRINTER_INFO_5
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_5 structure. Defined as PRINTER_INFO_5 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-5
            | _kw_: WAPIST_PRINTER_INFO_5, PRINTER_INFO_5, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_5** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_5 )
   /*{{|member_: - MEMBER LPSTR pPrinterName }}*/
   /*{{|member_: - MEMBER DYNSZ cPrinterName |desc_: Helper member mapped over ::pPrinterName. }}*/
   _XBST_LPSTR_DYNSZ ( pPrinterName  , cPrinterName )
   /*{{|member_: - MEMBER LPSTR pPortName }}*/
   /*{{|member_: - MEMBER DYNSZ cPortName |desc_: Helper member mapped over ::pPortName. }}*/
   _XBST_LPSTR_DYNSZ ( pPortName     , cPortName    )
   /*{{|member_: - MEMBER DWORD Attributes }}*/
   _XBST_DWORD ( Attributes               )
   /*{{|member_: - MEMBER DWORD DeviceNotSelectedTimeout }}*/
   _XBST_DWORD ( DeviceNotSelectedTimeout )
   /*{{|member_: - MEMBER DWORD TransmissionRetryTimeout }}*/
   _XBST_DWORD ( TransmissionRetryTimeout )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_6
            | _slug_: wapist_printer_info_6
            | class-function: WAPIST_PRINTER_INFO_6
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_6 structure. Defined as PRINTER_INFO_6 in
              ot4xb_wapist_map.ch.
            | note: OT4XB exposes additional readonly logical properties for all status flags declared in this source
              block.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-6
            | _kw_: WAPIST_PRINTER_INFO_6, PRINTER_INFO_6, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_6** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_6 )
   /*{{|member_: - MEMBER DWORD dwStatus }}*/
   _XBST_DWORD ( dwStatus )
   // ---------- ot4xb extension
   /*{{|property_: - PROPERTY lPaused | desc_: LOGICAL READ-ONLY ( 0x00000001 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPaused"               , "{|s| lAnd( s:dwStatus , 0x00000001)}");
   /*{{|property_: - PROPERTY lError | desc_: LOGICAL READ-ONLY ( 0x00000002 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lError"                , "{|s| lAnd( s:dwStatus , 0x00000002)}");
   /*{{|property_: - PROPERTY lPendingDeletion | desc_: LOGICAL READ-ONLY ( 0x00000004 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPendingDeletion"      , "{|s| lAnd( s:dwStatus , 0x00000004)}");
   /*{{|property_: - PROPERTY lPaperJam | desc_: LOGICAL READ-ONLY ( 0x00000008 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPaperJam"             , "{|s| lAnd( s:dwStatus , 0x00000008)}");
   /*{{|property_: - PROPERTY lPaperOut | desc_: LOGICAL READ-ONLY ( 0x00000010 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPaperOut"             , "{|s| lAnd( s:dwStatus , 0x00000010)}");

   /*{{|property_: - PROPERTY lManualFeed | desc_: LOGICAL READ-ONLY ( 0x00000020 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lManualFeed"           , "{|s| lAnd( s:dwStatus , 0x00000020)}");
   /*{{|property_: - PROPERTY lPaperProblem | desc_: LOGICAL READ-ONLY ( 0x00000040 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPaperProblem"         , "{|s| lAnd( s:dwStatus , 0x00000040)}");
   /*{{|property_: - PROPERTY lOffline | desc_: LOGICAL READ-ONLY ( 0x00000080 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lOffline"              , "{|s| lAnd( s:dwStatus , 0x00000080)}");
   /*{{|property_: - PROPERTY lIoActive | desc_: LOGICAL READ-ONLY ( 0x00000100 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lIoActive"             , "{|s| lAnd( s:dwStatus , 0x00000100)}");
   /*{{|property_: - PROPERTY lBusy | desc_: LOGICAL READ-ONLY ( 0x00000200 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lBusy"                 , "{|s| lAnd( s:dwStatus , 0x00000200)}");
   /*{{|property_: - PROPERTY lPrinting | desc_: LOGICAL READ-ONLY ( 0x00000400 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPrinting"             , "{|s| lAnd( s:dwStatus , 0x00000400)}");
   /*{{|property_: - PROPERTY lOutputBinFull | desc_: LOGICAL READ-ONLY ( 0x00000800 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lOutputBinFull"        , "{|s| lAnd( s:dwStatus , 0x00000800)}");
   /*{{|property_: - PROPERTY lNotAvailable | desc_: LOGICAL READ-ONLY ( 0x00001000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lNotAvailable"         , "{|s| lAnd( s:dwStatus , 0x00001000)}");
   /*{{|property_: - PROPERTY lWaiting | desc_: LOGICAL READ-ONLY ( 0x00002000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lWaiting"              , "{|s| lAnd( s:dwStatus , 0x00002000)}");
   /*{{|property_: - PROPERTY lProcessing | desc_: LOGICAL READ-ONLY ( 0x00004000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lProcessing"           , "{|s| lAnd( s:dwStatus , 0x00004000)}");
   /*{{|property_: - PROPERTY lInitializing | desc_: LOGICAL READ-ONLY ( 0x00008000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lInitializing"         , "{|s| lAnd( s:dwStatus , 0x00008000)}");
   /*{{|property_: - PROPERTY lWarmingUp | desc_: LOGICAL READ-ONLY ( 0x00010000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lWarmingUp"            , "{|s| lAnd( s:dwStatus , 0x00010000)}");
   /*{{|property_: - PROPERTY lTonerLow | desc_: LOGICAL READ-ONLY ( 0x00020000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lTonerLow"             , "{|s| lAnd( s:dwStatus , 0x00020000)}");
   /*{{|property_: - PROPERTY lNoToner | desc_: LOGICAL READ-ONLY ( 0x00040000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lNoToner"              , "{|s| lAnd( s:dwStatus , 0x00040000)}");
   /*{{|property_: - PROPERTY lPagePunt | desc_: LOGICAL READ-ONLY ( 0x00080000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPagePunt"             , "{|s| lAnd( s:dwStatus , 0x00080000)}");
   /*{{|property_: - PROPERTY lUserIntervention | desc_: LOGICAL READ-ONLY ( 0x00100000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lUserIntervention"     , "{|s| lAnd( s:dwStatus , 0x00100000)}");
   /*{{|property_: - PROPERTY lOutOfMemory | desc_: LOGICAL READ-ONLY ( 0x00200000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lOutOfMemory"          , "{|s| lAnd( s:dwStatus , 0x00200000)}");
   /*{{|property_: - PROPERTY lDoorOpen | desc_: LOGICAL READ-ONLY ( 0x00400000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lDoorOpen"             , "{|s| lAnd( s:dwStatus , 0x00400000)}");
   /*{{|property_: - PROPERTY lServerUnknown | desc_: LOGICAL READ-ONLY ( 0x00800000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lServerUnknown"        , "{|s| lAnd( s:dwStatus , 0x00800000)}");
   /*{{|property_: - PROPERTY lPowerSave | desc_: LOGICAL READ-ONLY ( 0x01000000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lPowerSave"            , "{|s| lAnd( s:dwStatus , 0x01000000)}");
   /*{{|property_: - PROPERTY lServerOffline | desc_: LOGICAL READ-ONLY ( 0x02000000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lServerOffline"        , "{|s| lAnd( s:dwStatus , 0x02000000)}");
   /*{{|property_: - PROPERTY lDriverUpdateNeeded | desc_: LOGICAL READ-ONLY ( 0x04000000 & ::dwStatus ) }}*/
   pc->ROPropertyCB("lDriverUpdateNeeded"   , "{|s| lAnd( s:dwStatus , 0x04000000)}");
   // ----------
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_7
            | _slug_: wapist_printer_info_7
            | class-function: WAPIST_PRINTER_INFO_7
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_7 structure. Defined as PRINTER_INFO_7 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-info-7
            | _kw_: WAPIST_PRINTER_INFO_7, PRINTER_INFO_7, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_7** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_7 )
   /*{{|member_: - MEMBER LPSTR pszObjectGUID }}*/
   /*{{|member_: - MEMBER DYNSZ cObjectGUID |desc_: Helper member mapped over ::pszObjectGUID. }}*/
   _XBST_LPSTR_DYNSZ ( pszObjectGUID , cObjectGUID)
   /*{{|member_: - MEMBER DWORD dwAction }}*/
   _XBST_DWORD  ( dwAction      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_8
            | _slug_: wapist_printer_info_8
            | class-function: WAPIST_PRINTER_INFO_8
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_8 structure. Defined as PRINTER_INFO_8 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_INFO_8, PRINTER_INFO_8, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_8** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_8 )
   /*{{|member_: - MEMBER POINTER32 pDevMode }}*/
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_INFO_9
            | _slug_: wapist_printer_info_9
            | class-function: WAPIST_PRINTER_INFO_9
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_INFO_9 structure. Defined as PRINTER_INFO_9 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_INFO_9, PRINTER_INFO_9, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_INFO_9** }}*/
XB_BEGIN_STRUCTURE( PRINTER_INFO_9 )
   /*{{|member_: - MEMBER POINTER32 pDevMode }}*/
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_NOTIFY_INFO
            | _slug_: wapist_printer_notify_info
            | class-function: WAPIST_PRINTER_NOTIFY_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_NOTIFY_INFO structure. Defined as PRINTER_NOTIFY_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_NOTIFY_INFO, PRINTER_NOTIFY_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_NOTIFY_INFO** }}*/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO )
   /*{{|member_: - MEMBER DWORD Version }}*/
   _XBST_DWORD                     ( Version )
   /*{{|member_: - MEMBER DWORD Flags }}*/
   _XBST_DWORD                     ( Flags   )
   /*{{|member_: - MEMBER DWORD Count }}*/
   _XBST_DWORD                     ( Count   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_printer_notify_info_data> wapist_PRINTER_NOTIFY_INFO_DATA}} aData0 }}*/
   _XBST_PRINTER_NOTIFY_INFO_DATA  ( aData0  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA
            | _slug_: wapist__printer_notify_info_data___data
            | class-function: WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi _PRINTER_NOTIFY_INFO_DATA___DATA structure. Defined as
              _PRINTER_NOTIFY_INFO_DATA___DATA in ot4xb_wapist_map.ch.
   | _kw_: WAPIST__PRINTER_NOTIFY_INFO_DATA___DATA, _PRINTER_NOTIFY_INFO_DATA___DATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  _PRINTER_NOTIFY_INFO_DATA___DATA** }}*/
XB_BEGIN_STRUCTURE( _PRINTER_NOTIFY_INFO_DATA___DATA )
   /*{{|member_: - MEMBER DWORD cbBuf }}*/
   _XBST_DWORD     ( cbBuf )
   /*{{|member_: - MEMBER POINTER32 pBuf }}*/
   _XBST_POINTER32 ( pBuf  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA
            | _slug_: wapist__printer_notify_info_data___notifydata
            | class-function: WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Auxiliary wrapper for the PRINTER_NOTIFY_INFO_DATA NotifyData union. Defined as
              _PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA in ot4xb_wapist_map.ch.
   | _kw_: WAPIST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA, _PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  _PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA** }}*/
XB_BEGIN_STRUCTURE( _PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA )
  {
     UINT nP1 = pc->GwstGetOffset();
     UINT nMax;
     {
        /*{{|member_: - MEMBER DWORD adwData0 }}*/
        _XBST_DWORD( adwData0 )
        /*{{|member_: - MEMBER DWORD adwData1 }}*/
        _XBST_DWORD( adwData1 )
     }
     nMax = pc->GwstGetOffset();
     pc->GwstSetOffset(nP1);
     /*{{|member_: - MEMBER @ {{ilink: <slug wapist__printer_notify_info_data___data> wapist__PRINTER_NOTIFY_INFO_DATA___DATA}} Data }}*/
     _XBST__PRINTER_NOTIFY_INFO_DATA___DATA( Data )
     if( pc->GwstGetOffset() < nMax ) pc->GwstSetOffset(nMax);

  }
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_NOTIFY_INFO_DATA
            | _slug_: wapist_printer_notify_info_data
            | class-function: WAPIST_PRINTER_NOTIFY_INFO_DATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_NOTIFY_INFO_DATA structure. Defined as PRINTER_NOTIFY_INFO_DATA in
              ot4xb_wapist_map.ch.
            | note: NotifyData is a named C union. Its Data branch is an anonymous C structure in the WinApi
              declaration. OT4XB uses small auxiliary classes to expose those nested layouts from Xbase++. Read either
              NotifyData:adwData0 and NotifyData:adwData1, or NotifyData:Data:cbBuf and NotifyData:Data:pBuf,
              depending on the Type and Field values documented by the Windows spooler API.
            | note: NotifyData:Data:pBuf is a pointer supplied by the Windows spooler notification API. The pointer is
              not owned by this structure object. Use NotifyData:Data:cbBuf as the byte length before reading from
              pBuf, and do not free pBuf from Xbase++ code.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/printdocs/printer-notify-info-data
            | example: ```
              local nd := oNotify:aData0

              ? nd:NotifyData:adwData0
              ? nd:NotifyData:adwData1

              if nd:NotifyData:Data:pBuf != 0 .and. nd:NotifyData:Data:cbBuf > 0
                 ? PeekStr( nd:NotifyData:Data:pBuf, 0, nd:NotifyData:Data:cbBuf )
              endif
              ```
   | _kw_: WAPIST_PRINTER_NOTIFY_INFO_DATA, PRINTER_NOTIFY_INFO_DATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_NOTIFY_INFO_DATA** }}*/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO_DATA )
   /*{{|member_: - MEMBER WORD Type }}*/
   _XBST_WORD   (  Type      )
   /*{{|member_: - MEMBER WORD Field }}*/
   _XBST_WORD   (  Field     )
   /*{{|member_: - MEMBER DWORD Reserved }}*/
   _XBST_DWORD  (  Reserved  )
   /*{{|member_: - MEMBER DWORD Id }}*/
   _XBST_DWORD  (  Id        )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist__printer_notify_info_data___notifydata> wapist__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA}} NotifyData }}*/
   _XBST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA( NotifyData )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_NOTIFY_OPTIONS
            | _slug_: wapist_printer_notify_options
            | class-function: WAPIST_PRINTER_NOTIFY_OPTIONS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_NOTIFY_OPTIONS structure. Defined as PRINTER_NOTIFY_OPTIONS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_NOTIFY_OPTIONS, PRINTER_NOTIFY_OPTIONS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_NOTIFY_OPTIONS** }}*/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS )
   /*{{|member_: - MEMBER DWORD Version }}*/
   _XBST_DWORD     ( Version )
   /*{{|member_: - MEMBER DWORD Flags }}*/
   _XBST_DWORD     ( Flags   )
   /*{{|member_: - MEMBER DWORD Count }}*/
   _XBST_DWORD     ( Count   )
   /*{{|member_: - MEMBER POINTER32 pTypes }}*/
   _XBST_POINTER32 ( pTypes  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE
            | _slug_: wapist_printer_notify_options_type
            | class-function: WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTER_NOTIFY_OPTIONS_TYPE structure. Defined as
              PRINTER_NOTIFY_OPTIONS_TYPE in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTER_NOTIFY_OPTIONS_TYPE, PRINTER_NOTIFY_OPTIONS_TYPE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTER_NOTIFY_OPTIONS_TYPE** }}*/
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS_TYPE )
   /*{{|member_: - MEMBER WORD Type }}*/
   _XBST_WORD       ( Type      )
   /*{{|member_: - MEMBER WORD Reserved0 }}*/
   _XBST_WORD       ( Reserved0 )
   /*{{|member_: - MEMBER DWORD Reserved1 }}*/
   _XBST_DWORD      ( Reserved1 )
   /*{{|member_: - MEMBER DWORD Reserved2 }}*/
   _XBST_DWORD      ( Reserved2 )
   /*{{|member_: - MEMBER DWORD Count }}*/
   _XBST_DWORD      ( Count     )
   /*{{|member_: - MEMBER POINTER32 pFields }}*/
   _XBST_POINTER32  ( pFields   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTPROCESSOR_CAPS_1
            | _slug_: wapist_printprocessor_caps_1
            | class-function: WAPIST_PRINTPROCESSOR_CAPS_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTPROCESSOR_CAPS_1 structure. Defined as PRINTPROCESSOR_CAPS_1 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTPROCESSOR_CAPS_1, PRINTPROCESSOR_CAPS_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTPROCESSOR_CAPS_1** }}*/
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_CAPS_1 )
   /*{{|member_: - MEMBER DWORD dwLevel }}*/
   _XBST_DWORD ( dwLevel          )
   /*{{|member_: - MEMBER DWORD dwNupOptions }}*/
   _XBST_DWORD ( dwNupOptions     )
   /*{{|member_: - MEMBER DWORD dwPageOrderFlags }}*/
   _XBST_DWORD ( dwPageOrderFlags )
   /*{{|member_: - MEMBER DWORD dwNumberOfCopies }}*/
   _XBST_DWORD ( dwNumberOfCopies )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PRINTPROCESSOR_INFO_1
            | _slug_: wapist_printprocessor_info_1
            | class-function: WAPIST_PRINTPROCESSOR_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PRINTPROCESSOR_INFO_1 structure. Defined as PRINTPROCESSOR_INFO_1 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PRINTPROCESSOR_INFO_1, PRINTPROCESSOR_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PRINTPROCESSOR_INFO_1** }}*/
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_INFO_1 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR ( pName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PROVIDOR_INFO_1
            | _slug_: wapist_providor_info_1
            | class-function: WAPIST_PROVIDOR_INFO_1
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PROVIDOR_INFO_1 structure. Defined as PROVIDOR_INFO_1 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PROVIDOR_INFO_1, PROVIDOR_INFO_1, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PROVIDOR_INFO_1** }}*/
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_1 )
   /*{{|member_: - MEMBER LPSTR pName }}*/
   _XBST_LPSTR( pName        )
   /*{{|member_: - MEMBER LPSTR pEnvironment }}*/
   _XBST_LPSTR( pEnvironment )
   /*{{|member_: - MEMBER LPSTR pDLLName }}*/
   _XBST_LPSTR( pDLLName     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PROVIDOR_INFO_2
            | _slug_: wapist_providor_info_2
            | class-function: WAPIST_PROVIDOR_INFO_2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PROVIDOR_INFO_2 structure. Defined as PROVIDOR_INFO_2 in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PROVIDOR_INFO_2, PROVIDOR_INFO_2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PROVIDOR_INFO_2** }}*/
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_2 )
   /*{{|member_: - MEMBER LPSTR pOrder }}*/
   _XBST_LPSTR( pOrder )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PSFEATURE_CUSTPAPER
            | _slug_: wapist_psfeature_custpaper
            | class-function: WAPIST_PSFEATURE_CUSTPAPER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PSFEATURE_CUSTPAPER structure. Defined as PSFEATURE_CUSTPAPER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PSFEATURE_CUSTPAPER, PSFEATURE_CUSTPAPER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PSFEATURE_CUSTPAPER** }}*/
XB_BEGIN_STRUCTURE( PSFEATURE_CUSTPAPER )
   /*{{|member_: - MEMBER LONG lOrientation }}*/
   _XBST_LONG ( lOrientation  )
   /*{{|member_: - MEMBER LONG lWidth }}*/
   _XBST_LONG ( lWidth        )
   /*{{|member_: - MEMBER LONG lHeight }}*/
   _XBST_LONG ( lHeight       )
   /*{{|member_: - MEMBER LONG lWidthOffset }}*/
   _XBST_LONG ( lWidthOffset  )
   /*{{|member_: - MEMBER LONG lHeightOffset }}*/
   _XBST_LONG ( lHeightOffset )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PSFEATURE_OUTPUT
            | _slug_: wapist_psfeature_output
            | class-function: WAPIST_PSFEATURE_OUTPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PSFEATURE_OUTPUT structure. Defined as PSFEATURE_OUTPUT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_PSFEATURE_OUTPUT, PSFEATURE_OUTPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PSFEATURE_OUTPUT** }}*/
XB_BEGIN_STRUCTURE( PSFEATURE_OUTPUT )
   /*{{|member_: - MEMBER BOOL bPageIndependent }}*/
   _XBST_BOOL ( bPageIndependent )
   /*{{|member_: - MEMBER BOOL bSetPageDevice }}*/
   _XBST_BOOL ( bSetPageDevice   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PSINJECTDATA
            | _slug_: wapist_psinjectdata
            | class-function: WAPIST_PSINJECTDATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PSINJECTDATA structure. Defined as PSINJECTDATA in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PSINJECTDATA, PSINJECTDATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PSINJECTDATA** }}*/
XB_BEGIN_STRUCTURE( PSINJECTDATA )
   /*{{|member_: - MEMBER DWORD DataBytes }}*/
   _XBST_DWORD ( DataBytes      )
   /*{{|member_: - MEMBER WORD InjectionPoint }}*/
   _XBST_WORD  ( InjectionPoint )
   /*{{|member_: - MEMBER WORD PageNumber }}*/
   _XBST_WORD  ( PageNumber     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RGNDATA
            | _slug_: wapist_rgndata
            | class-function: WAPIST_RGNDATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RGNDATA structure. Defined as RGNDATA in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RGNDATA, RGNDATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RGNDATA** }}*/
XB_BEGIN_STRUCTURE( RGNDATA )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rgndataheader> wapist_RGNDATAHEADER}} rdh }}*/
   _XBST_RGNDATAHEADER ( rdh )
   /*{{|member_: - MEMBER BYTE Buffer0 }}*/
   _XBST_CHAR          ( Buffer0 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RGNDATAHEADER
            | _slug_: wapist_rgndataheader
            | class-function: WAPIST_RGNDATAHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RGNDATAHEADER structure. Defined as RGNDATAHEADER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RGNDATAHEADER, RGNDATAHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RGNDATAHEADER** }}*/
XB_BEGIN_STRUCTURE( RGNDATAHEADER )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize    )
   /*{{|member_: - MEMBER DWORD iType }}*/
   _XBST_DWORD ( iType     )
   /*{{|member_: - MEMBER DWORD nCount }}*/
   _XBST_DWORD ( nCount    )
   /*{{|member_: - MEMBER DWORD nRgnSize }}*/
   _XBST_DWORD ( nRgnSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcBound }}*/
   _XBST_RECT  ( rcBound   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DISPLAY_DEVICE
            | _slug_: wapist_display_device
            | class-function: WAPIST_DISPLAY_DEVICE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DISPLAY_DEVICE layout declared in this source block, with the ANSI
              fixed string members of DISPLAY_DEVICEA.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-display_devicea
            | _kw_: WAPIST_DISPLAY_DEVICE, DISPLAY_DEVICE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DISPLAY_DEVICE** }}*/
XB_BEGIN_STRUCTURE( DISPLAY_DEVICE )
/*{{|member_: - MEMBER DWORD cb }}*/
_XBST_DWORD( cb );
/*{{|member_: - MEMBER SZSTR DeviceName }}*/
_XBST_SZSTR( DeviceName , 32) 
/*{{|member_: - MEMBER SZSTR DeviceString }}*/
_XBST_SZSTR( DeviceString,128)
  /*{{|member_: - MEMBER DWORD StateFlags }}*/
  _XBST_DWORD( StateFlags)
  /*{{|member_: - MEMBER SZSTR DeviceID }}*/
  _XBST_SZSTR( DeviceID,128)
  /*{{|member_: - MEMBER SZSTR DeviceKey }}*/
  _XBST_SZSTR( DeviceKey,128)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ALTTABINFO
            | _slug_: wapist_alttabinfo
            | class-function: WAPIST_ALTTABINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ALTTABINFO structure. Defined as ALTTABINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ALTTABINFO, ALTTABINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ALTTABINFO** }}*/
XB_BEGIN_STRUCTURE( ALTTABINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD  ( cbSize    )
   /*{{|member_: - MEMBER INT cItems }}*/
   _XBST_int    ( cItems    )
   /*{{|member_: - MEMBER INT cColumns }}*/
   _XBST_int    ( cColumns  )
   /*{{|member_: - MEMBER INT cRows }}*/
   _XBST_int    ( cRows     )
   /*{{|member_: - MEMBER INT iColFocus }}*/
   _XBST_int    ( iColFocus )
   /*{{|member_: - MEMBER INT iRowFocus }}*/
   _XBST_int    ( iRowFocus )
   /*{{|member_: - MEMBER INT cxItem }}*/
   _XBST_int    ( cxItem    )
   /*{{|member_: - MEMBER INT cyItem }}*/
   _XBST_int    ( cyItem    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptStart }}*/
   _XBST_POINT  ( ptStart   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TITLEBARINFO
            | _slug_: wapist_titlebarinfo
            | class-function: WAPIST_TITLEBARINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TITLEBARINFO structure. Defined as TITLEBARINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TITLEBARINFO, TITLEBARINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TITLEBARINFO** }}*/
XB_BEGIN_STRUCTURE( TITLEBARINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD  ( cbSize            )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcTitleBar }}*/
   _XBST_RECT   ( rcTitleBar        )
   /*{{|member_: - MEMBER DWORD rgstate_TitleBar }}*/
   _XBST_DWORD  ( rgstate_TitleBar  )   //0
   /*{{|member_: - MEMBER DWORD rgstate_Reserved }}*/
   _XBST_DWORD  ( rgstate_Reserved  )   //1
   /*{{|member_: - MEMBER DWORD rgstate_Min }}*/
   _XBST_DWORD  ( rgstate_Min       )   //2
   /*{{|member_: - MEMBER DWORD rgstate_Max }}*/
   _XBST_DWORD  ( rgstate_Max       )   //3
   /*{{|member_: - MEMBER DWORD rgstate_Help }}*/
   _XBST_DWORD  ( rgstate_Help      )   //4
   /*{{|member_: - MEMBER DWORD rgstate_Close }}*/
   _XBST_DWORD  ( rgstate_Close     )   //5

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WINDOWINFO
            | _slug_: wapist_windowinfo
            | class-function: WAPIST_WINDOWINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WINDOWINFO structure. Defined as WINDOWINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-windowinfo
            | _kw_: WAPIST_WINDOWINFO, WINDOWINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WINDOWINFO** }}*/
XB_BEGIN_STRUCTURE( WINDOWINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD ( cbSize           )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcWindow }}*/
   _XBST_RECT  ( rcWindow         )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcClient }}*/
   _XBST_RECT  ( rcClient         )
   /*{{|member_: - MEMBER DWORD dwStyle }}*/
   _XBST_DWORD ( dwStyle          )
   /*{{|member_: - MEMBER DWORD dwExStyle }}*/
   _XBST_DWORD ( dwExStyle        )
   /*{{|member_: - MEMBER DWORD dwWindowStatus }}*/
   _XBST_DWORD ( dwWindowStatus   )
   /*{{|member_: - MEMBER UINT cxWindowBorders }}*/
   _XBST_UINT  ( cxWindowBorders  )
   /*{{|member_: - MEMBER UINT cyWindowBorders }}*/
   _XBST_UINT  ( cyWindowBorders  )
   /*{{|member_: - MEMBER ATOM atomWindowType }}*/
   _XBST_ATOM  ( atomWindowType   )
   /*{{|member_: - MEMBER WORD wCreatorVersion }}*/
   _XBST_WORD  ( wCreatorVersion  )
   pc->GwstAdjustSize(sizeof(WINDOWINFO));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WINDOWPLACEMENT
            | _slug_: wapist_windowplacement
            | class-function: WAPIST_WINDOWPLACEMENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WINDOWPLACEMENT structure. Defined as WINDOWPLACEMENT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WINDOWPLACEMENT, WINDOWPLACEMENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WINDOWPLACEMENT** }}*/
XB_BEGIN_STRUCTURE( WINDOWPLACEMENT )
   /*{{|member_: - MEMBER UINT length }}*/
   _XBST_UINT   ( length           )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT   ( flags            )
   /*{{|member_: - MEMBER UINT showCmd }}*/
   _XBST_UINT   ( showCmd          )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMinPosition }}*/
   _XBST_POINT  ( ptMinPosition    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMaxPosition }}*/
   _XBST_POINT  ( ptMaxPosition    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcNormalPosition }}*/
   _XBST_RECT   ( rcNormalPosition )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GUITHREADINFO
            | _slug_: wapist_guithreadinfo
            | class-function: WAPIST_GUITHREADINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GUITHREADINFO structure. Defined as GUITHREADINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GUITHREADINFO, GUITHREADINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GUITHREADINFO** }}*/
XB_BEGIN_STRUCTURE( GUITHREADINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD  ( cbSize          )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD  ( flags           )
   /*{{|member_: - MEMBER HWND hwndActive }}*/
   _XBST_HWND   ( hwndActive      )
   /*{{|member_: - MEMBER HWND hwndFocus }}*/
   _XBST_HWND   ( hwndFocus       )
   /*{{|member_: - MEMBER HWND hwndCapture }}*/
   _XBST_HWND   ( hwndCapture     )
   /*{{|member_: - MEMBER HWND hwndMenuOwner }}*/
   _XBST_HWND   ( hwndMenuOwner   )
   /*{{|member_: - MEMBER HWND hwndMoveSize }}*/
   _XBST_HWND   ( hwndMoveSize    )
   /*{{|member_: - MEMBER HWND hwndCaret }}*/
   _XBST_HWND   ( hwndCaret       )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcCaret }}*/
   _XBST_RECT   ( rcCaret         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CURSORINFO
            | _slug_: wapist_cursorinfo
            | class-function: WAPIST_CURSORINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CURSORINFO structure. Defined as CURSORINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_CURSORINFO, CURSORINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CURSORINFO** }}*/
XB_BEGIN_STRUCTURE( CURSORINFO  )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD   ( cbSize        )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD   ( flags         )
   /*{{|member_: - MEMBER HCURSOR hCursor }}*/
   _XBST_HCURSOR ( hCursor       )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptScreenPos }}*/
   _XBST_POINT   ( ptScreenPos   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ICONINFO
            | _slug_: wapist_iconinfo
            | class-function: WAPIST_ICONINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ICONINFO structure. Defined as ICONINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ICONINFO, ICONINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ICONINFO** }}*/
XB_BEGIN_STRUCTURE( ICONINFO  )
   /*{{|member_: - MEMBER BOOL fIcon }}*/
   _XBST_BOOL    ( fIcon     )
   /*{{|member_: - MEMBER DWORD xHotspot }}*/
   _XBST_DWORD   ( xHotspot  )
   /*{{|member_: - MEMBER DWORD yHotspot }}*/
   _XBST_DWORD   ( yHotspot  )
   /*{{|member_: - MEMBER HBITMAP hbmMask }}*/
   _XBST_HBITMAP ( hbmMask   )
   /*{{|member_: - MEMBER HBITMAP hbmColor }}*/
   _XBST_HBITMAP ( hbmColor  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ICONMETRICS
            | _slug_: wapist_iconmetrics
            | class-function: WAPIST_ICONMETRICS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ICONMETRICS structure. Defined as ICONMETRICS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ICONMETRICS, ICONMETRICS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ICONMETRICS** }}*/
XB_BEGIN_STRUCTURE( ICONMETRICS  )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT    ( cbSize         )
   /*{{|member_: - MEMBER INT iHorzSpacing }}*/
   _XBST_int     ( iHorzSpacing   )
   /*{{|member_: - MEMBER INT iVertSpacing }}*/
   _XBST_int     ( iVertSpacing   )
   /*{{|member_: - MEMBER INT iTitleWrap }}*/
   _XBST_int     ( iTitleWrap     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_logfont> wapist_LOGFONT}} lfFont }}*/
   _XBST_LOGFONT ( lfFont         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_METAFILEPICT
            | _slug_: wapist_metafilepict
            | class-function: WAPIST_METAFILEPICT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi METAFILEPICT structure. Defined as METAFILEPICT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_METAFILEPICT, METAFILEPICT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  METAFILEPICT** }}*/
XB_BEGIN_STRUCTURE( METAFILEPICT  )
   /*{{|member_: - MEMBER LONG mm }}*/
   _XBST_LONG      ( mm    )
   /*{{|member_: - MEMBER LONG xExt }}*/
   _XBST_LONG      ( xExt  )
   /*{{|member_: - MEMBER LONG yExt }}*/
   _XBST_LONG      ( yExt  )
   /*{{|member_: - MEMBER HMETAFILE hMF }}*/
   _XBST_HMETAFILE ( hMF   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MDINEXTMENU
            | _slug_: wapist_mdinextmenu
            | class-function: WAPIST_MDINEXTMENU
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MDINEXTMENU structure. Defined as MDINEXTMENU in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MDINEXTMENU, MDINEXTMENU, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MDINEXTMENU** }}*/
XB_BEGIN_STRUCTURE( MDINEXTMENU              )
   /*{{|member_: - MEMBER HMENU hmenuIn }}*/
   _XBST_HMENU  ( hmenuIn     )
   /*{{|member_: - MEMBER HMENU hmenuNext }}*/
   _XBST_HMENU  ( hmenuNext   )
   /*{{|member_: - MEMBER HWND hwndNext }}*/
   _XBST_HWND   ( hwndNext    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUBARINFO
            | _slug_: wapist_menubarinfo
            | class-function: WAPIST_MENUBARINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUBARINFO structure. Defined as MENUBARINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menubarinfo
            | _kw_: WAPIST_MENUBARINFO, MENUBARINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUBARINFO** }}*/
XB_BEGIN_STRUCTURE( MENUBARINFO              )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD ( cbSize     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcBar }}*/
   _XBST_RECT  ( rcBar      )
   /*{{|member_: - MEMBER HMENU hMenu }}*/
   _XBST_HMENU ( hMenu      )
   /*{{|member_: - MEMBER HWND hwndMenu }}*/
   _XBST_HWND  ( hwndMenu   )
   /*{{|member_: - MEMBER DWORD _fflags_ |desc_: Bit flags storage; see the flag properties below. }}*/
   _XBST_DWORD ( _fflags_   )
   /*{{|property_: - PROPERTY fBarFocused | desc_: LOGICAL READ-WRITE ( bit 1 of ::_fflags_ ) }}*/
   pc->PropertyCB( "fBarFocused" , "{|s,v| lDwBitOnOff( @s:_fflags_,1,v) }");
   /*{{|property_: - PROPERTY fFocused | desc_: LOGICAL READ-WRITE ( bit 2 of ::_fflags_ ) }}*/
   pc->PropertyCB( "fFocused"    , "{|s,v| lDwBitOnOff( @s:_fflags_,2,v) }");
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUEX_TEMPLATE_HEADER
            | _slug_: wapist_menuex_template_header
            | class-function: WAPIST_MENUEX_TEMPLATE_HEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUEX_TEMPLATE_HEADER structure. Defined as MENUEX_TEMPLATE_HEADER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MENUEX_TEMPLATE_HEADER, MENUEX_TEMPLATE_HEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUEX_TEMPLATE_HEADER** }}*/
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_HEADER   )
   /*{{|member_: - MEMBER WORD wVersion }}*/
   _XBST_WORD  ( wVersion )
   /*{{|member_: - MEMBER WORD wOffset }}*/
   _XBST_WORD  ( wOffset  )
   /*{{|member_: - MEMBER DWORD dwHelpId }}*/
   _XBST_DWORD ( dwHelpId )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUEX_TEMPLATE_ITEM
            | _slug_: wapist_menuex_template_item
            | class-function: WAPIST_MENUEX_TEMPLATE_ITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUEX_TEMPLATE_ITEM structure. Defined as MENUEX_TEMPLATE_ITEM in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MENUEX_TEMPLATE_ITEM, MENUEX_TEMPLATE_ITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUEX_TEMPLATE_ITEM** }}*/
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_ITEM  )
   /*{{|member_: - MEMBER DWORD dwHelpId }}*/
   _XBST_DWORD ( dwHelpId  )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD ( dwType    )
   /*{{|member_: - MEMBER DWORD dwState }}*/
   _XBST_DWORD ( dwState   )
   /*{{|member_: - MEMBER DWORD menuId }}*/
   _XBST_DWORD ( menuId    )
   /*{{|member_: - MEMBER WORD bResInfo }}*/
   _XBST_WORD  ( bResInfo  )
   /*{{|member_: - MEMBER SHORT _wszText_ }}*/
   _XBST_short ( _wszText_ ) // WCHAR szText
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUGETOBJECTINFO
            | _slug_: wapist_menugetobjectinfo
            | class-function: WAPIST_MENUGETOBJECTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUGETOBJECTINFO structure. Defined as MENUGETOBJECTINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MENUGETOBJECTINFO, MENUGETOBJECTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUGETOBJECTINFO** }}*/
XB_BEGIN_STRUCTURE( MENUGETOBJECTINFO        )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD      ( dwFlags   )
   /*{{|member_: - MEMBER UINT uPos }}*/
   _XBST_UINT       ( uPos      )
   /*{{|member_: - MEMBER HMENU hmenu }}*/
   _XBST_HMENU      ( hmenu     )
   /*{{|member_: - MEMBER POINTER32 riid }}*/
   _XBST_POINTER32  ( riid      )
   /*{{|member_: - MEMBER POINTER32 pvObj }}*/
   _XBST_POINTER32  ( pvObj     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUINFO
            | _slug_: wapist_menuinfo
            | class-function: WAPIST_MENUINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUINFO structure. Defined as MENUINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MENUINFO, MENUINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUINFO** }}*/
XB_BEGIN_STRUCTURE( MENUINFO                 )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD     ( cbSize            )
   /*{{|member_: - MEMBER DWORD fMask }}*/
   _XBST_DWORD     ( fMask             )
   /*{{|member_: - MEMBER DWORD dwStyle }}*/
   _XBST_DWORD     ( dwStyle           )
   /*{{|member_: - MEMBER UINT cyMax }}*/
   _XBST_UINT      ( cyMax             )
   /*{{|member_: - MEMBER HBRUSH hbrBack }}*/
   _XBST_HBRUSH    ( hbrBack           )
   /*{{|member_: - MEMBER DWORD dwContextHelpID }}*/
   _XBST_DWORD     ( dwContextHelpID   )
   /*{{|member_: - MEMBER POINTER32 dwMenuData }}*/
   _XBST_POINTER32 ( dwMenuData        )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUITEMINFO
            | _slug_: wapist_menuiteminfo
            | class-function: WAPIST_MENUITEMINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUITEMINFOA structure. Defined as MENUITEMINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfoa
            | _kw_: WAPIST_MENUITEMINFO, MENUITEMINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUITEMINFO** }}*/
XB_BEGIN_STRUCTURE( MENUITEMINFO             )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT       ( cbSize            )
   /*{{|member_: - MEMBER UINT fMask }}*/
   _XBST_UINT       ( fMask             )
   /*{{|member_: - MEMBER UINT fType }}*/
   _XBST_UINT       ( fType             )
   /*{{|member_: - MEMBER UINT fState }}*/
   _XBST_UINT       ( fState            )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT       ( wID               )
   /*{{|member_: - MEMBER HMENU hSubMenu }}*/
   _XBST_HMENU      ( hSubMenu          )
   /*{{|member_: - MEMBER HBITMAP hbmpChecked }}*/
   _XBST_HBITMAP    ( hbmpChecked       )
   /*{{|member_: - MEMBER HBITMAP hbmpUnchecked }}*/
   _XBST_HBITMAP    ( hbmpUnchecked     )
   /*{{|member_: - MEMBER ULONG_PTR dwItemData }}*/
   _XBST_ULONG_PTR  ( dwItemData        )
  pc->GwstBeginUnion();
      /*{{|member_: - MEMBER LPSTR dwTypeData }}*/
      _XBST_LPSTR      ( dwTypeData        )
      /*{{|member_: - MEMBER DYNSZ _cTypeData |desc_: Helper member mapped over ::dwTypeData. }}*/
      _XBST_DYNSZ ( _cTypeData        )
  pc->GwstEndUnion();
   /*{{|member_: - MEMBER UINT cch }}*/
   _XBST_UINT       ( cch               )
   /*{{|member_: - MEMBER HBITMAP hbmpItem }}*/
   _XBST_HBITMAP    ( hbmpItem          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUITEMTEMPLATE
            | _slug_: wapist_menuitemtemplate
            | class-function: WAPIST_MENUITEMTEMPLATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUITEMTEMPLATE structure. Defined as MENUITEMTEMPLATE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MENUITEMTEMPLATE, MENUITEMTEMPLATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUITEMTEMPLATE** }}*/
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATE         )
   /*{{|member_: - MEMBER WORD mtOption }}*/
   _XBST_WORD  ( mtOption   )
   /*{{|member_: - MEMBER WORD mtID }}*/
   _XBST_WORD  ( mtID       )
   /*{{|member_: - MEMBER SHORT mtString_1 }}*/
   _XBST_short ( mtString_1 ) // WCHAR mtString[1]
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MENUITEMTEMPLATEHEADER
            | _slug_: wapist_menuitemtemplateheader
            | class-function: WAPIST_MENUITEMTEMPLATEHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MENUITEMTEMPLATEHEADER structure. Defined as MENUITEMTEMPLATEHEADER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MENUITEMTEMPLATEHEADER, MENUITEMTEMPLATEHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MENUITEMTEMPLATEHEADER** }}*/
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATEHEADER   )
   /*{{|member_: - MEMBER WORD versionNumber }}*/
   _XBST_WORD ( versionNumber  )
   /*{{|member_: - MEMBER WORD offset }}*/
   _XBST_WORD ( offset         )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TPMPARAMS
            | _slug_: wapist_tpmparams
            | class-function: WAPIST_TPMPARAMS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TPMPARAMS structure. Defined as TPMPARAMS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TPMPARAMS, TPMPARAMS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TPMPARAMS** }}*/
XB_BEGIN_STRUCTURE( TPMPARAMS                )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcExclude }}*/
   _XBST_RECT ( rcExclude )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ACCEL
            | _slug_: wapist_accel
            | class-function: WAPIST_ACCEL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ACCEL structure. Defined as ACCEL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ACCEL, ACCEL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ACCEL** }}*/
XB_BEGIN_STRUCTURE( ACCEL )
   /*{{|member_: - MEMBER BYTE fVirt }}*/
   _XBST_BYTE( fVirt )
   /*{{|member_: - MEMBER WORD key }}*/
   _XBST_WORD( key )
   /*{{|member_: - MEMBER WORD cmd }}*/
   _XBST_WORD( cmd )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MINMAXINFO
            | _slug_: wapist_minmaxinfo
            | class-function: WAPIST_MINMAXINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MINMAXINFO structure. Defined as MINMAXINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MINMAXINFO, MINMAXINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MINMAXINFO** }}*/
XB_BEGIN_STRUCTURE( MINMAXINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptReserved }}*/
   _XBST_POINT( ptReserved      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMaxSize }}*/
   _XBST_POINT( ptMaxSize       )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMaxPosition }}*/
   _XBST_POINT( ptMaxPosition   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMinTrackSize }}*/
   _XBST_POINT( ptMinTrackSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptMaxTrackSize }}*/
   _XBST_POINT( ptMaxTrackSize  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMHDR
            | _slug_: wapist_nmhdr
            | class-function: WAPIST_NMHDR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMHDR structure. Defined as NMHDR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMHDR, NMHDR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMHDR** }}*/
XB_BEGIN_STRUCTURE( NMHDR )
   /*{{|member_: - MEMBER HWND hwndFrom }}*/
   _XBST_HWND (hwndFrom )
   /*{{|member_: - MEMBER UINT idFrom }}*/
   _XBST_UINT (idFrom   )
   /*{{|member_: - MEMBER UINT code }}*/
   _XBST_UINT (code     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMRBAUTOSIZE
            | _slug_: wapist_nmrbautosize
            | class-function: WAPIST_NMRBAUTOSIZE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMRBAUTOSIZE structure. Defined as NMRBAUTOSIZE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMRBAUTOSIZE, NMRBAUTOSIZE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMRBAUTOSIZE** }}*/
XB_BEGIN_STRUCTURE( NMRBAUTOSIZE      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr      )
   /*{{|member_: - MEMBER BOOL fChanged }}*/
   _XBST_BOOL  ( fChanged )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcTarget }}*/
   _XBST_RECT  ( rcTarget )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcActual }}*/
   _XBST_RECT  ( rcActual )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMREBAR
            | _slug_: wapist_nmrebar
            | class-function: WAPIST_NMREBAR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMREBAR structure. Defined as NMREBAR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMREBAR, NMREBAR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMREBAR** }}*/
XB_BEGIN_STRUCTURE( NMREBAR           )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR   ( hdr    )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD   ( dwMask )
   /*{{|member_: - MEMBER UINT uBand }}*/
   _XBST_UINT    ( uBand  )
   /*{{|member_: - MEMBER UINT fStyle }}*/
   _XBST_UINT    ( fStyle )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT    ( wID    )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM  ( lParam )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMREBARAUTOBREAK
            | _slug_: wapist_nmrebarautobreak
            | class-function: WAPIST_NMREBARAUTOBREAK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMREBARAUTOBREAK structure. Defined as NMREBARAUTOBREAK in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMREBARAUTOBREAK, NMREBARAUTOBREAK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMREBARAUTOBREAK** }}*/
XB_BEGIN_STRUCTURE( NMREBARAUTOBREAK  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR  ( hdr           )
   /*{{|member_: - MEMBER UINT uBand }}*/
   _XBST_UINT   ( uBand         )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT   ( wID           )
   /*{{|member_: - MEMBER UINT uMsg }}*/
   _XBST_UINT   ( uMsg          )
   /*{{|member_: - MEMBER UINT fStyleCurrent }}*/
   _XBST_UINT   ( fStyleCurrent )
   /*{{|member_: - MEMBER BOOL fAutoBreak }}*/
   _XBST_BOOL   ( fAutoBreak    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMREBARCHEVRON
            | _slug_: wapist_nmrebarchevron
            | class-function: WAPIST_NMREBARCHEVRON
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMREBARCHEVRON structure. Defined as NMREBARCHEVRON in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMREBARCHEVRON, NMREBARCHEVRON, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMREBARCHEVRON** }}*/
XB_BEGIN_STRUCTURE( NMREBARCHEVRON    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR     ( hdr      )
   /*{{|member_: - MEMBER UINT uBand }}*/
   _XBST_UINT      ( uBand    )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT      ( wID      )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM    ( lParam   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT      ( rc       )
   /*{{|member_: - MEMBER LPARAM lParamNM }}*/
   _XBST_LPARAM    ( lParamNM )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMREBARCHILDSIZE
            | _slug_: wapist_nmrebarchildsize
            | class-function: WAPIST_NMREBARCHILDSIZE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMREBARCHILDSIZE structure. Defined as NMREBARCHILDSIZE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMREBARCHILDSIZE, NMREBARCHILDSIZE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMREBARCHILDSIZE** }}*/
XB_BEGIN_STRUCTURE( NMREBARCHILDSIZE  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR  ( hdr     )
   /*{{|member_: - MEMBER UINT uBand }}*/
   _XBST_UINT   ( uBand   )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT   ( wID     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcChild }}*/
   _XBST_RECT   ( rcChild )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcBand }}*/
   _XBST_RECT   ( rcBand  )

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RBHITTESTINFO
            | _slug_: wapist_rbhittestinfo
            | class-function: WAPIST_RBHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RBHITTESTINFO structure. Defined as RBHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RBHITTESTINFO, RBHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RBHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( RBHITTESTINFO     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT  ( pt    )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT   ( flags )
   /*{{|member_: - MEMBER INT iBand }}*/
   _XBST_int    ( iBand )

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_REBARBANDINFO
            | _slug_: wapist_rebarbandinfo
            | class-function: WAPIST_REBARBANDINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi REBARBANDINFO structure. Defined as REBARBANDINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_REBARBANDINFO, REBARBANDINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  REBARBANDINFO** }}*/
XB_BEGIN_STRUCTURE( REBARBANDINFO     )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT           (  cbSize      )
   /*{{|member_: - MEMBER UINT fMask }}*/
   _XBST_UINT           (  fMask       )
   /*{{|member_: - MEMBER UINT fStyle }}*/
   _XBST_UINT           (  fStyle      )
   /*{{|member_: - MEMBER COLORREF clrFore }}*/
   _XBST_COLORREF       (  clrFore     )
   /*{{|member_: - MEMBER COLORREF clrBack }}*/
   _XBST_COLORREF       (  clrBack     )
   /*{{|member_: - MEMBER LPSTR lpText }}*/
   _XBST_LPSTR          (  lpText      )
   /*{{|member_: - MEMBER UINT cch }}*/
   _XBST_UINT           (  cch         )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int            (  iImage      )
   /*{{|member_: - MEMBER HWND hwndChild }}*/
   _XBST_HWND           (  hwndChild   )
   /*{{|member_: - MEMBER UINT cxMinChild }}*/
   _XBST_UINT           (  cxMinChild  )
   /*{{|member_: - MEMBER UINT cyMinChild }}*/
   _XBST_UINT           (  cyMinChild  )
   /*{{|member_: - MEMBER UINT cx }}*/
   _XBST_UINT           (  cx          )
   /*{{|member_: - MEMBER HBITMAP hbmBack }}*/
   _XBST_HBITMAP        (  hbmBack     )
   /*{{|member_: - MEMBER UINT wID }}*/
   _XBST_UINT           (  wID         )
   /*{{|member_: - MEMBER UINT cyChild }}*/
   _XBST_UINT           (  cyChild     )
   /*{{|member_: - MEMBER UINT cyMaxChild }}*/
   _XBST_UINT           (  cyMaxChild  )
   /*{{|member_: - MEMBER UINT cyIntegral }}*/
   _XBST_UINT           (  cyIntegral  )
   /*{{|member_: - MEMBER UINT cxIdeal }}*/
   _XBST_UINT           (  cxIdeal     )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM         (  lParam      )
   /*{{|member_: - MEMBER UINT cxHeader }}*/
   _XBST_UINT           (  cxHeader    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_REBARINFO
            | _slug_: wapist_rebarinfo
            | class-function: WAPIST_REBARINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi REBARINFO structure. Defined as REBARINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_REBARINFO, REBARINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  REBARINFO** }}*/
XB_BEGIN_STRUCTURE( REBARINFO         )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT        ( cbSize  )
   /*{{|member_: - MEMBER UINT fMask }}*/
   _XBST_UINT        ( fMask   )
   /*{{|member_: - MEMBER HANDLE himl }}*/
   _XBST_HANDLE      ( himl    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBBUTTON
            | _slug_: wapist_tbbutton
            | class-function: WAPIST_TBBUTTON
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBBUTTON structure. Defined as TBBUTTON in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBBUTTON, TBBUTTON, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBBUTTON** }}*/
XB_BEGIN_STRUCTURE( TBBUTTON )
  /*{{|member_: - MEMBER INT iBitmap }}*/
  _XBST_int   (  iBitmap    )
  /*{{|member_: - MEMBER INT idCommand }}*/
  _XBST_int   (  idCommand  )
  /*{{|member_: - MEMBER BYTE fsState }}*/
  _XBST_BYTE  (  fsState    )
  /*{{|member_: - MEMBER BYTE fsStyle }}*/
  _XBST_BYTE  (  fsStyle    )
  /*{{|member_: - MEMBER WORD wReserved }}*/
  _XBST_WORD  (  wReserved  )
  /*{{|member_: - MEMBER DWORD dwData }}*/
  _XBST_DWORD (  dwData     )
  /*{{|member_: - MEMBER LONG iString }}*/
  _XBST_LONG  (  iString    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WNDCLASS
            | _slug_: wapist_wndclass
            | class-function: WAPIST_WNDCLASS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WNDCLASSA structure. Defined as WNDCLASS in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
            | _kw_: WAPIST_WNDCLASS, WNDCLASS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WNDCLASS** }}*/
XB_BEGIN_STRUCTURE(WNDCLASS)
  /*{{|member_: - MEMBER UINT style }}*/
  _XBST_UINT       ( style          )
  /*{{|member_: - MEMBER WNDPROC lpfnWndProc }}*/
  _XBST_WNDPROC    ( lpfnWndProc    )
  /*{{|member_: - MEMBER INT cbClsExtra }}*/
  _XBST_int        ( cbClsExtra     )
  /*{{|member_: - MEMBER INT cbWndExtra }}*/
  _XBST_int        ( cbWndExtra     )
  /*{{|member_: - MEMBER HINSTANCE hInstance }}*/
  _XBST_HINSTANCE  ( hInstance      )
  /*{{|member_: - MEMBER HICON hIcon }}*/
  _XBST_HICON      ( hIcon          )
  /*{{|member_: - MEMBER HCURSOR hCursor }}*/
  _XBST_HCURSOR    ( hCursor        )
  /*{{|member_: - MEMBER HBRUSH hbrBackground }}*/
  _XBST_HBRUSH     ( hbrBackground  )
  /*{{|member_: - MEMBER LPSTR lpszMenuName }}*/
  /*{{|member_: - MEMBER DYNSZ cMenuName |desc_: Helper member mapped over ::lpszMenuName. }}*/
  _XBST_LPSTR      ( lpszMenuName   ) pc->GwstBack() ; _XBST_DYNSZ ( cMenuName  )
  /*{{|member_: - MEMBER LPSTR lpszClassName }}*/
  /*{{|member_: - MEMBER DYNSZ cClassName |desc_: Helper member mapped over ::lpszClassName. }}*/
  _XBST_LPSTR      ( lpszClassName  ) pc->GwstBack() ; _XBST_DYNSZ ( cClassName )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WNDCLASSEX
            | _slug_: wapist_wndclassex
            | class-function: WAPIST_WNDCLASSEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WNDCLASSEX structure. Defined as WNDCLASSEX in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
            | _kw_: WAPIST_WNDCLASSEX, WNDCLASSEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WNDCLASSEX** }}*/
XB_BEGIN_STRUCTURE(WNDCLASSEX)
  /*{{|member_: - MEMBER UINT cbSize }}*/
  _XBST_UINT       ( cbSize         )
  /*{{|member_: - MEMBER UINT style }}*/
  _XBST_UINT       ( style          )
  /*{{|member_: - MEMBER WNDPROC lpfnWndProc }}*/
  _XBST_WNDPROC    ( lpfnWndProc    )
  /*{{|member_: - MEMBER INT cbClsExtra }}*/
  _XBST_int        ( cbClsExtra     )
  /*{{|member_: - MEMBER INT cbWndExtra }}*/
  _XBST_int        ( cbWndExtra     )
  /*{{|member_: - MEMBER HINSTANCE hInstance }}*/
  _XBST_HINSTANCE  ( hInstance      )
  /*{{|member_: - MEMBER HICON hIcon }}*/
  _XBST_HICON      ( hIcon          )
  /*{{|member_: - MEMBER HCURSOR hCursor }}*/
  _XBST_HCURSOR    ( hCursor        )
  /*{{|member_: - MEMBER HBRUSH hbrBackground }}*/
  _XBST_HBRUSH     ( hbrBackground  )
  /*{{|member_: - MEMBER LPSTR lpszMenuName }}*/
  /*{{|member_: - MEMBER DYNSZ cMenuName |desc_: Helper member mapped over ::lpszMenuName. }}*/
  _XBST_LPSTR      ( lpszMenuName   ) ; pc->GwstBack() ; _XBST_DYNSZ ( cMenuName  )
  /*{{|member_: - MEMBER LPSTR lpszClassName }}*/
  /*{{|member_: - MEMBER DYNSZ cClassName |desc_: Helper member mapped over ::lpszClassName. }}*/
  _XBST_LPSTR      ( lpszClassName  ) ; pc->GwstBack() ; _XBST_DYNSZ ( cClassName )
  /*{{|member_: - MEMBER HICON hIconSm }}*/
  _XBST_HICON      ( hIconSm        )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MDICREATESTRUCT
            | _slug_: wapist_mdicreatestruct
            | class-function: WAPIST_MDICREATESTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MDICREATESTRUCT structure. Defined as MDICREATESTRUCT in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mdicreatestructa
            | _kw_: WAPIST_MDICREATESTRUCT, MDICREATESTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MDICREATESTRUCT** }}*/
XB_BEGIN_STRUCTURE( MDICREATESTRUCT )
  /*{{|member_: - MEMBER LPSTR szClass }}*/
  /*{{|member_: - MEMBER DYNSZ cClass |desc_: Helper member mapped over ::szClass. }}*/
  _XBST_LPSTR   ( szClass  ) ; pc->GwstBack() ; _XBST_DYNSZ( cClass )
  /*{{|member_: - MEMBER LPSTR szTitle }}*/
  /*{{|member_: - MEMBER DYNSZ cTitle |desc_: Helper member mapped over ::szTitle. }}*/
  _XBST_LPSTR   ( szTitle  ) ; pc->GwstBack() ; _XBST_DYNSZ( cTitle )
  /*{{|member_: - MEMBER HANDLE hOwner }}*/
  _XBST_HANDLE  ( hOwner   )
  /*{{|member_: - MEMBER INT x }}*/
  _XBST_int     ( x        )
  /*{{|member_: - MEMBER INT y }}*/
  _XBST_int     ( y        )
  /*{{|member_: - MEMBER INT cx }}*/
  _XBST_int     ( cx       )
  /*{{|member_: - MEMBER INT cy }}*/
  _XBST_int     ( cy       )
  /*{{|member_: - MEMBER DWORD style }}*/
  _XBST_DWORD   ( style    )
  /*{{|member_: - MEMBER LPARAM lParam }}*/
  _XBST_LPARAM  ( lParam   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HARDWAREINPUT
            | _slug_: wapist_hardwareinput
            | class-function: WAPIST_HARDWAREINPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HARDWAREINPUT structure. Defined as HARDWAREINPUT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HARDWAREINPUT, HARDWAREINPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HARDWAREINPUT** }}*/
XB_BEGIN_STRUCTURE( HARDWAREINPUT )
  /*{{|member_: - MEMBER DWORD uMsg }}*/
  _XBST_DWORD ( uMsg    )
  /*{{|member_: - MEMBER WORD wParamL }}*/
  _XBST_WORD  ( wParamL )
  /*{{|member_: - MEMBER WORD wParamH }}*/
  _XBST_WORD  ( wParamH )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INPUT
            | _slug_: wapist_input
            | class-function: WAPIST_INPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INPUT structure. Defined as INPUT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-input
            | _kw_: WAPIST_INPUT, INPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INPUT** }}*/
XB_BEGIN_STRUCTURE( INPUT )
  /*{{|member_: - MEMBER DWORD type }}*/
  _XBST_DWORD             ( type )
  pc->GwstBeginUnion();
    /*{{|member_: - MEMBER @ {{ilink: <slug wapist_mouseinput> wapist_MOUSEINPUT}} mi }}*/
    _XBST_MOUSEINPUT      ( mi )
    /*{{|member_: - MEMBER @ {{ilink: <slug wapist_keybdinput> wapist_KEYBDINPUT}} ki }}*/
    _XBST_KEYBDINPUT      ( ki )
    /*{{|member_: - MEMBER @ {{ilink: <slug wapist_hardwareinput> wapist_HARDWAREINPUT}} hi }}*/
    _XBST_HARDWAREINPUT   ( hi )
  pc->GwstEndUnion();
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_KEYBDINPUT
            | _slug_: wapist_keybdinput
            | class-function: WAPIST_KEYBDINPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi KEYBDINPUT structure. Defined as KEYBDINPUT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_KEYBDINPUT, KEYBDINPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  KEYBDINPUT** }}*/
XB_BEGIN_STRUCTURE( KEYBDINPUT )
    /*{{|member_: - MEMBER WORD wVk }}*/
    _XBST_WORD       ( wVk         )
    /*{{|member_: - MEMBER WORD wScan }}*/
    _XBST_WORD       ( wScan       )
    /*{{|member_: - MEMBER DWORD dwFlags }}*/
    _XBST_DWORD      ( dwFlags     )
    /*{{|member_: - MEMBER DWORD time }}*/
    _XBST_DWORD      ( time        )
    /*{{|member_: - MEMBER ULONG_PTR dwExtraInfo }}*/
    _XBST_ULONG_PTR  ( dwExtraInfo )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LASTINPUTINFO
            | _slug_: wapist_lastinputinfo
            | class-function: WAPIST_LASTINPUTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LASTINPUTINFO structure. Defined as LASTINPUTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LASTINPUTINFO, LASTINPUTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LASTINPUTINFO** }}*/
XB_BEGIN_STRUCTURE( LASTINPUTINFO )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT  ( cbSize )
    /*{{|member_: - MEMBER DWORD dwTime }}*/
    _XBST_DWORD ( dwTime )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MOUSEINPUT
            | _slug_: wapist_mouseinput
            | class-function: WAPIST_MOUSEINPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MOUSEINPUT structure. Defined as MOUSEINPUT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MOUSEINPUT, MOUSEINPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MOUSEINPUT** }}*/
XB_BEGIN_STRUCTURE( MOUSEINPUT )
    /*{{|member_: - MEMBER LONG dx }}*/
    _XBST_LONG      ( dx          )
    /*{{|member_: - MEMBER LONG dy }}*/
    _XBST_LONG      ( dy          )
    /*{{|member_: - MEMBER DWORD mouseData }}*/
    _XBST_DWORD     ( mouseData   )
    /*{{|member_: - MEMBER DWORD dwFlags }}*/
    _XBST_DWORD     ( dwFlags     )
    /*{{|member_: - MEMBER DWORD time }}*/
    _XBST_DWORD     ( time        )
    /*{{|member_: - MEMBER ULONG_PTR dwExtraInfo }}*/
    _XBST_ULONG_PTR ( dwExtraInfo )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IMAGEINFO
            | _slug_: wapist_imageinfo
            | class-function: WAPIST_IMAGEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IMAGEINFO structure. Defined as IMAGEINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_IMAGEINFO, IMAGEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IMAGEINFO** }}*/
XB_BEGIN_STRUCTURE( IMAGEINFO )
    /*{{|member_: - MEMBER HBITMAP hbmImage }}*/
    _XBST_HBITMAP   ( hbmImage )
    /*{{|member_: - MEMBER HBITMAP hbmMask }}*/
    _XBST_HBITMAP   ( hbmMask  )
    /*{{|member_: - MEMBER INT Unused1 }}*/
    _XBST_int       ( Unused1  )
    /*{{|member_: - MEMBER INT Unused2 }}*/
    _XBST_int       ( Unused2  )
    /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcImage }}*/
    _XBST_RECT      ( rcImage  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IMAGELISTDRAWPARAMS
            | _slug_: wapist_imagelistdrawparams
            | class-function: WAPIST_IMAGELISTDRAWPARAMS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IMAGELISTDRAWPARAMS structure. Defined as IMAGELISTDRAWPARAMS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_IMAGELISTDRAWPARAMS, IMAGELISTDRAWPARAMS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IMAGELISTDRAWPARAMS** }}*/
XB_BEGIN_STRUCTURE( IMAGELISTDRAWPARAMS )
    /*{{|member_: - MEMBER DWORD cbSize }}*/
    _XBST_DWORD         ( cbSize   )
    /*{{|member_: - MEMBER HIMAGELIST himl }}*/
    _XBST_HIMAGELIST    ( himl     )
    /*{{|member_: - MEMBER INT i }}*/
    _XBST_int           ( i        )
    /*{{|member_: - MEMBER HDC hdcDst }}*/
    _XBST_HDC           ( hdcDst   )
    /*{{|member_: - MEMBER INT x }}*/
    _XBST_int           ( x        )
    /*{{|member_: - MEMBER INT y }}*/
    _XBST_int           ( y        )
    /*{{|member_: - MEMBER INT cx }}*/
    _XBST_int           ( cx       )
    /*{{|member_: - MEMBER INT cy }}*/
    _XBST_int           ( cy       )
    /*{{|member_: - MEMBER INT xBitmap }}*/
    _XBST_int           ( xBitmap  )
    /*{{|member_: - MEMBER INT yBitmap }}*/
    _XBST_int           ( yBitmap  )
    /*{{|member_: - MEMBER COLORREF rgbBk }}*/
    _XBST_COLORREF      ( rgbBk    )
    /*{{|member_: - MEMBER COLORREF rgbFg }}*/
    _XBST_COLORREF      ( rgbFg    )
    /*{{|member_: - MEMBER UINT fStyle }}*/
    _XBST_UINT          ( fStyle   )
    /*{{|member_: - MEMBER DWORD dwRop }}*/
    _XBST_DWORD         ( dwRop    )
    /*{{|member_: - MEMBER DWORD fState }}*/
    _XBST_DWORD         ( fState   )
    /*{{|member_: - MEMBER DWORD Frame }}*/
    _XBST_DWORD         ( Frame    )
    /*{{|member_: - MEMBER DWORD crEffect }}*/
    _XBST_DWORD         ( crEffect )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MSGBOXPARAMS
            | _slug_: wapist_msgboxparams
            | class-function: WAPIST_MSGBOXPARAMS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MSGBOXPARAMS structure. Defined as MSGBOXPARAMS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MSGBOXPARAMS, MSGBOXPARAMS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MSGBOXPARAMS** }}*/
XB_BEGIN_STRUCTURE( MSGBOXPARAMS )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT             ( cbSize             )
    /*{{|member_: - MEMBER HWND hwndOwner }}*/
    _XBST_HWND             ( hwndOwner          )
    /*{{|member_: - MEMBER HINSTANCE hInstance }}*/
    _XBST_HINSTANCE        ( hInstance          )
    /*{{|member_: - MEMBER LPSTR lpszText }}*/
    _XBST_LPSTR            ( lpszText           )
    /*{{|member_: - MEMBER LPSTR lpszCaption }}*/
    _XBST_LPSTR            ( lpszCaption        )
    /*{{|member_: - MEMBER DWORD dwStyle }}*/
    _XBST_DWORD            ( dwStyle            )
    /*{{|member_: - MEMBER LPSTR lpszIcon }}*/
    _XBST_LPSTR            ( lpszIcon           )
    /*{{|member_: - MEMBER DWORD dwContextHelpId }}*/
    _XBST_DWORD            ( dwContextHelpId    )
    /*{{|member_: - MEMBER POINTER32 lpfnMsgBoxCallback }}*/
    _XBST_POINTER32        ( lpfnMsgBoxCallback )
    /*{{|member_: - MEMBER DWORD dwLanguageId }}*/
    _XBST_DWORD            ( dwLanguageId       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DLGTEMPLATE
            | _slug_: wapist_dlgtemplate
            | class-function: WAPIST_DLGTEMPLATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DLGTEMPLATE structure. Defined as DLGTEMPLATE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DLGTEMPLATE, DLGTEMPLATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DLGTEMPLATE** }}*/
XB_BEGIN_STRUCTURE( DLGTEMPLATE )
    /*{{|member_: - MEMBER DWORD style }}*/
    _XBST_DWORD ( style              )
    /*{{|member_: - MEMBER DWORD dwExtendedStyle }}*/
    _XBST_DWORD ( dwExtendedStyle    )
    /*{{|member_: - MEMBER WORD cdit }}*/
    _XBST_WORD  ( cdit               )
    /*{{|member_: - MEMBER SHORT x }}*/
    _XBST_short ( x                  )
    /*{{|member_: - MEMBER SHORT y }}*/
    _XBST_short ( y                  )
    /*{{|member_: - MEMBER SHORT cx }}*/
    _XBST_short ( cx                 )
    /*{{|member_: - MEMBER SHORT cy }}*/
    _XBST_short ( cy                 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DLGITEMTEMPLATE
            | _slug_: wapist_dlgitemtemplate
            | class-function: WAPIST_DLGITEMTEMPLATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DLGITEMTEMPLATE structure. Defined as DLGITEMTEMPLATE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DLGITEMTEMPLATE, DLGITEMTEMPLATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DLGITEMTEMPLATE** }}*/
XB_BEGIN_STRUCTURE( DLGITEMTEMPLATE  )
    /*{{|member_: - MEMBER DWORD style }}*/
    _XBST_DWORD ( style              )
    /*{{|member_: - MEMBER DWORD dwExtendedStyle }}*/
    _XBST_DWORD ( dwExtendedStyle    )
    /*{{|member_: - MEMBER SHORT x }}*/
    _XBST_short ( x                  )
    /*{{|member_: - MEMBER SHORT y }}*/
    _XBST_short ( y                  )
    /*{{|member_: - MEMBER SHORT cx }}*/
    _XBST_short ( cx                 )
    /*{{|member_: - MEMBER SHORT cy }}*/
    _XBST_short ( cy                 )
    /*{{|member_: - MEMBER WORD id }}*/
    _XBST_WORD  ( id                 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FLASHWINFO
            | _slug_: wapist_flashwinfo
            | class-function: WAPIST_FLASHWINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FLASHWINFO structure. Defined as FLASHWINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FLASHWINFO, FLASHWINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FLASHWINFO** }}*/
XB_BEGIN_STRUCTURE( FLASHWINFO )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT   ( cbSize    )
    /*{{|member_: - MEMBER HWND hwnd }}*/
    _XBST_HWND   ( hwnd      )
    /*{{|member_: - MEMBER DWORD dwFlags }}*/
    _XBST_DWORD  ( dwFlags   )
    /*{{|member_: - MEMBER UINT uCount }}*/
    _XBST_UINT   ( uCount    )
    /*{{|member_: - MEMBER DWORD dwTimeout }}*/
    _XBST_DWORD  ( dwTimeout )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
// RTF structures
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BIDIOPTIONS
            | _slug_: wapist_bidioptions
            | class-function: WAPIST_BIDIOPTIONS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BIDIOPTIONS structure. Defined as BIDIOPTIONS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_BIDIOPTIONS, BIDIOPTIONS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BIDIOPTIONS** }}*/
XB_BEGIN_STRUCTURE( BIDIOPTIONS )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT ( cbSize    )
    /*{{|member_: - MEMBER WORD wMask }}*/
    _XBST_WORD ( wMask     )
    /*{{|member_: - MEMBER WORD wEffects }}*/
    _XBST_WORD ( wEffects  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CHARFORMAT
            | _slug_: wapist_charformat
            | class-function: WAPIST_CHARFORMAT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CHARFORMAT structure. Defined as CHARFORMAT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-charformata
            | _kw_: WAPIST_CHARFORMAT, CHARFORMAT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CHARFORMAT** }}*/
XB_BEGIN_STRUCTURE( CHARFORMAT )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT        ( cbSize          )
    /*{{|member_: - MEMBER DWORD dwMask }}*/
    _XBST_DWORD       ( dwMask          )
    /*{{|member_: - MEMBER DWORD dwEffects }}*/
    _XBST_DWORD       ( dwEffects       )
    /*{{|member_: - MEMBER LONG yHeight }}*/
    _XBST_LONG        ( yHeight         )
    /*{{|member_: - MEMBER LONG yOffset }}*/
    _XBST_LONG        ( yOffset         )
    /*{{|member_: - MEMBER COLORREF crTextColor }}*/
    _XBST_COLORREF    ( crTextColor     )
    /*{{|member_: - MEMBER BYTE bCharSet }}*/
    _XBST_BYTE        ( bCharSet        )
    /*{{|member_: - MEMBER BYTE bPitchAndFamily }}*/
    _XBST_BYTE        ( bPitchAndFamily )
    pc->GwstAlignNextMember(4);
    /*{{|member_: - MEMBER SZSTR szFaceName }}*/
    _XBST_SZSTR       ( szFaceName , LF_FACESIZE )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CHARFORMAT2
            | _slug_: wapist_charformat2
            | class-function: WAPIST_CHARFORMAT2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CHARFORMAT2 structure. Defined as CHARFORMAT2 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-charformat2a
            | _kw_: WAPIST_CHARFORMAT2, CHARFORMAT2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CHARFORMAT2** }}*/
XB_BEGIN_STRUCTURE( CHARFORMAT2 )
    /*{{|member_: - MEMBER UINT cbSize }}*/
    _XBST_UINT         ( cbSize          )
    /*{{|member_: - MEMBER DWORD dwMask }}*/
    _XBST_DWORD        ( dwMask          )
    /*{{|member_: - MEMBER DWORD dwEffects }}*/
    _XBST_DWORD        ( dwEffects       )
    /*{{|member_: - MEMBER LONG yHeight }}*/
    _XBST_LONG         ( yHeight         )
    /*{{|member_: - MEMBER LONG yOffset }}*/
    _XBST_LONG         ( yOffset         )
    /*{{|member_: - MEMBER COLORREF crTextColor }}*/
    _XBST_COLORREF     ( crTextColor     )
    /*{{|member_: - MEMBER BYTE bCharSet }}*/
    _XBST_BYTE         ( bCharSet        )
    /*{{|member_: - MEMBER BYTE bPitchAndFamily }}*/
    _XBST_BYTE         ( bPitchAndFamily )
    pc->GwstAlignNextMember(4);
    /*{{|member_: - MEMBER SZSTR szFaceName }}*/
    _XBST_SZSTR        ( szFaceName , LF_FACESIZE )
    /*{{|member_: - MEMBER WORD wWeight }}*/
    _XBST_WORD         ( wWeight         )
    /*{{|member_: - MEMBER SHORT sSpacing }}*/
    _XBST_SHORT        ( sSpacing        )
    /*{{|member_: - MEMBER COLORREF crBackColor }}*/
    _XBST_COLORREF     ( crBackColor     )
    /*{{|member_: - MEMBER LCID lcid }}*/
    _XBST_LCID         ( lcid            )
    /*{{|member_: - MEMBER DWORD dwReserved }}*/
    _XBST_DWORD        ( dwReserved      )
    /*{{|member_: - MEMBER SHORT sStyle }}*/
    _XBST_SHORT        ( sStyle          )
    /*{{|member_: - MEMBER WORD wKerning }}*/
    _XBST_WORD         ( wKerning        )
    /*{{|member_: - MEMBER BYTE bUnderlineType }}*/
    _XBST_BYTE         ( bUnderlineType  )
    /*{{|member_: - MEMBER BYTE bAnimation }}*/
    _XBST_BYTE         ( bAnimation      )
    /*{{|member_: - MEMBER BYTE bRevAuthor }}*/
    _XBST_BYTE         ( bRevAuthor      )
    /*{{|member_: - MEMBER BYTE bReserved1 }}*/
    _XBST_BYTE         ( bReserved1      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CHARRANGE
            | _slug_: wapist_charrange
            | class-function: WAPIST_CHARRANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CHARRANGE structure. Defined as CHARRANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_CHARRANGE, CHARRANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CHARRANGE** }}*/
XB_BEGIN_STRUCTURE( CHARRANGE )
    /*{{|member_: - MEMBER LONG cpMin }}*/
    _XBST_LONG        ( cpMin )
    /*{{|member_: - MEMBER LONG cpMax }}*/
    _XBST_LONG        ( cpMax )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COMPCOLOR
            | _slug_: wapist_compcolor
            | class-function: WAPIST_COMPCOLOR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COMPCOLOR structure. Defined as COMPCOLOR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_COMPCOLOR, COMPCOLOR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COMPCOLOR** }}*/
XB_BEGIN_STRUCTURE( COMPCOLOR )
    /*{{|member_: - MEMBER COLORREF crText }}*/
    _XBST_COLORREF ( crText        )
    /*{{|member_: - MEMBER COLORREF crBackground }}*/
    _XBST_COLORREF ( crBackground  )
    /*{{|member_: - MEMBER DWORD dwEffects }}*/
    _XBST_DWORD    ( dwEffects     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_EDITSTREAM
            | _slug_: wapist_editstream
            | class-function: WAPIST_EDITSTREAM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi EDITSTREAM structure. Defined as EDITSTREAM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_EDITSTREAM, EDITSTREAM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  EDITSTREAM** }}*/
XB_BEGIN_STRUCTURE( EDITSTREAM )
    /*{{|member_: - MEMBER DWORD dwCookie }}*/
    _XBST_DWORD ( dwCookie    )
    /*{{|member_: - MEMBER DWORD dwError }}*/
    _XBST_DWORD ( dwError     )
    /*{{|member_: - MEMBER DWORD pfnCallback }}*/
    _XBST_DWORD ( pfnCallback )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENCORRECTTEXT
            | _slug_: wapist_encorrecttext
            | class-function: WAPIST_ENCORRECTTEXT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENCORRECTTEXT structure. Defined as ENCORRECTTEXT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENCORRECTTEXT, ENCORRECTTEXT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENCORRECTTEXT** }}*/
XB_BEGIN_STRUCTURE( ENCORRECTTEXT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR     ( nmhdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE ( chrg   )
   /*{{|member_: - MEMBER WORD seltyp }}*/
   _XBST_WORD      ( seltyp )
   pc->GwstSetOffset(sizeof(ENCORRECTTEXT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENDROPFILES
            | _slug_: wapist_endropfiles
            | class-function: WAPIST_ENDROPFILES
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENDROPFILES structure. Defined as ENDROPFILES in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENDROPFILES, ENDROPFILES, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENDROPFILES** }}*/
XB_BEGIN_STRUCTURE( ENDROPFILES )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR  ( nmhdr      )
   /*{{|member_: - MEMBER HANDLE hDrop }}*/
   _XBST_HANDLE ( hDrop      )
   /*{{|member_: - MEMBER LONG cp }}*/
   _XBST_LONG   ( cp         )
   /*{{|member_: - MEMBER BOOL fProtected }}*/
   _XBST_BOOL   ( fProtected )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENLINK
            | _slug_: wapist_enlink
            | class-function: WAPIST_ENLINK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENLINK structure. Defined as ENLINK in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENLINK, ENLINK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENLINK** }}*/
XB_BEGIN_STRUCTURE( ENLINK )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR     ( nmhdr   )
   /*{{|member_: - MEMBER UINT msg }}*/
   _XBST_UINT      ( msg     )
   /*{{|member_: - MEMBER WPARAM wParam }}*/
   _XBST_WPARAM    ( wParam  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM    ( lParam  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE ( chrg    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENLOWFIRTF
            | _slug_: wapist_enlowfirtf
            | class-function: WAPIST_ENLOWFIRTF
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENLOWFIRTF structure. Defined as ENLOWFIRTF in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENLOWFIRTF, ENLOWFIRTF, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENLOWFIRTF** }}*/
XB_BEGIN_STRUCTURE( ENLOWFIRTF )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr     )
   /*{{|member_: - MEMBER LPSTR szControl }}*/
   _XBST_LPSTR ( szControl )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENOLEOPFAILED
            | _slug_: wapist_enoleopfailed
            | class-function: WAPIST_ENOLEOPFAILED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENOLEOPFAILED structure. Defined as ENOLEOPFAILED in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENOLEOPFAILED, ENOLEOPFAILED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENOLEOPFAILED** }}*/
XB_BEGIN_STRUCTURE( ENOLEOPFAILED )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR   ( nmhdr )
   /*{{|member_: - MEMBER LONG iob }}*/
   _XBST_LONG    ( iob   )
   /*{{|member_: - MEMBER LONG lOper }}*/
   _XBST_LONG    ( lOper )
   /*{{|member_: - MEMBER HRESULT hr }}*/
   _XBST_HRESULT ( hr    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENPROTECTED
            | _slug_: wapist_enprotected
            | class-function: WAPIST_ENPROTECTED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENPROTECTED structure. Defined as ENPROTECTED in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_ENPROTECTED, ENPROTECTED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENPROTECTED** }}*/
XB_BEGIN_STRUCTURE( ENPROTECTED )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR     ( nmhdr  )
   /*{{|member_: - MEMBER UINT msg }}*/
   _XBST_UINT      ( msg    )
   /*{{|member_: - MEMBER WPARAM wParam }}*/
   _XBST_WPARAM    ( wParam )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM    ( lParam )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE ( chrg   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ENSAVECLIPBOARD
            | _slug_: wapist_ensaveclipboard
            | class-function: WAPIST_ENSAVECLIPBOARD
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi ENSAVECLIPBOARD structure. Defined as ENSAVECLIPBOARD in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_ENSAVECLIPBOARD, ENSAVECLIPBOARD, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ENSAVECLIPBOARD** }}*/
XB_BEGIN_STRUCTURE( ENSAVECLIPBOARD )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr        )
   /*{{|member_: - MEMBER LONG cObjectCount }}*/
   _XBST_LONG  ( cObjectCount )
   /*{{|member_: - MEMBER LONG cch }}*/
   _XBST_LONG  ( cch          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FINDTEXT
            | _slug_: wapist_findtext
            | class-function: WAPIST_FINDTEXT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FINDTEXT structure. Defined as FINDTEXT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FINDTEXT, FINDTEXT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FINDTEXT** }}*/
XB_BEGIN_STRUCTURE( FINDTEXT ) // Ojo resolver colisión con la función FindText() de comdlg32.dll
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE  ( chrg      )
   /*{{|member_: - MEMBER LPSTR lpstrText }}*/
   _XBST_LPSTR      ( lpstrText )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FINDTEXTEX
            | _slug_: wapist_findtextex
            | class-function: WAPIST_FINDTEXTEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FINDTEXTEX structure. Defined as FINDTEXTEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FINDTEXTEX, FINDTEXTEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FINDTEXTEX** }}*/
XB_BEGIN_STRUCTURE( FINDTEXTEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE  ( chrg      )
   /*{{|member_: - MEMBER LPSTR lpstrText }}*/
   _XBST_LPSTR      ( lpstrText )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrgText }}*/
   _XBST_CHARRANGE  ( chrgText      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FORMATRANGE
            | _slug_: wapist_formatrange
            | class-function: WAPIST_FORMATRANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FORMATRANGE structure. Defined as FORMATRANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FORMATRANGE, FORMATRANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FORMATRANGE** }}*/
XB_BEGIN_STRUCTURE( FORMATRANGE )
   /*{{|member_: - MEMBER HDC hdc }}*/
   _XBST_HDC       ( hdc       )
   /*{{|member_: - MEMBER HDC hdcTarget }}*/
   _XBST_HDC       ( hdcTarget )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT      ( rc        )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcPage }}*/
   _XBST_RECT      ( rcPage    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE ( chrg      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GETTEXTEX
            | _slug_: wapist_gettextex
            | class-function: WAPIST_GETTEXTEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GETTEXTEX structure. Defined as GETTEXTEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GETTEXTEX, GETTEXTEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GETTEXTEX** }}*/
XB_BEGIN_STRUCTURE( GETTEXTEX )
   /*{{|member_: - MEMBER DWORD cb }}*/
   _XBST_DWORD      ( cb            )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD      ( flags         )
   /*{{|member_: - MEMBER UINT codepage }}*/
   _XBST_UINT       ( codepage      )
   /*{{|member_: - MEMBER LPSTR lpDefaultChar }}*/
   _XBST_LPSTR      ( lpDefaultChar )
   /*{{|member_: - MEMBER POINTER32 lpUsedDefChar }}*/
   _XBST_POINTER32  ( lpUsedDefChar )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GETTEXTLENGTHEX
            | _slug_: wapist_gettextlengthex
            | class-function: WAPIST_GETTEXTLENGTHEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GETTEXTLENGTHEX structure. Defined as GETTEXTLENGTHEX in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_GETTEXTLENGTHEX, GETTEXTLENGTHEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GETTEXTLENGTHEX** }}*/
XB_BEGIN_STRUCTURE( GETTEXTLENGTHEX )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD  ( flags    )
   /*{{|member_: - MEMBER UINT codepage }}*/
   _XBST_UINT   ( codepage )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HYPHENATEINFO
            | _slug_: wapist_hyphenateinfo
            | class-function: WAPIST_HYPHENATEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HYPHENATEINFO structure. Defined as HYPHENATEINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HYPHENATEINFO, HYPHENATEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HYPHENATEINFO** }}*/
XB_BEGIN_STRUCTURE( HYPHENATEINFO )
   /*{{|member_: - MEMBER SHORT cbSize }}*/
   _XBST_SHORT  ( cbSize          )
   /*{{|member_: - MEMBER SHORT dxHyphenateZone }}*/
   _XBST_SHORT  ( dxHyphenateZone )
   /*{{|member_: - MEMBER DWORD pfnHyphenate }}*/
   _XBST_DWORD  ( pfnHyphenate    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HYPHRESULT
            | _slug_: wapist_hyphresult
            | class-function: WAPIST_HYPHRESULT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HYPHRESULT structure. Defined as HYPHRESULT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HYPHRESULT, HYPHRESULT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HYPHRESULT** }}*/
XB_BEGIN_STRUCTURE( HYPHRESULT )
   /*{{|member_: - MEMBER INT khyph }}*/
   _XBST_int   ( khyph   )
   /*{{|member_: - MEMBER LONG ichHyph }}*/
   _XBST_LONG  ( ichHyph )
   /*{{|member_: - MEMBER SHORT chHyph }}*/
   _XBST_SHORT ( chHyph  )
   pc->GwstSetOffset(sizeof(HYPHRESULT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IMECOMPTEXT
            | _slug_: wapist_imecomptext
            | class-function: WAPIST_IMECOMPTEXT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IMECOMPTEXT structure. Defined as IMECOMPTEXT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_IMECOMPTEXT, IMECOMPTEXT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IMECOMPTEXT** }}*/
XB_BEGIN_STRUCTURE( IMECOMPTEXT )
   /*{{|member_: - MEMBER LONG cb }}*/
   _XBST_LONG  ( cb     )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD ( flags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MSGFILTER
            | _slug_: wapist_msgfilter
            | class-function: WAPIST_MSGFILTER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MSGFILTER structure. Defined as MSGFILTER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MSGFILTER, MSGFILTER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MSGFILTER** }}*/
XB_BEGIN_STRUCTURE( MSGFILTER )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR  ( nmhdr  )
   /*{{|member_: - MEMBER UINT msg }}*/
   _XBST_UINT   ( msg    )
   /*{{|member_: - MEMBER WPARAM wParam }}*/
   _XBST_WPARAM ( wParam )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OBJECTPOSITIONS
            | _slug_: wapist_objectpositions
            | class-function: WAPIST_OBJECTPOSITIONS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi OBJECTPOSITIONS structure. Defined as OBJECTPOSITIONS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_OBJECTPOSITIONS, OBJECTPOSITIONS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OBJECTPOSITIONS** }}*/
XB_BEGIN_STRUCTURE( OBJECTPOSITIONS )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR     ( nmhdr        )
   /*{{|member_: - MEMBER LONG cObjectCount }}*/
   _XBST_LONG      ( cObjectCount )
   /*{{|member_: - MEMBER POINTER32 pcpPositions }}*/
   _XBST_POINTER32 ( pcpPositions )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PARAFORMAT
            | _slug_: wapist_paraformat
            | class-function: WAPIST_PARAFORMAT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PARAFORMAT structure. Defined as PARAFORMAT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PARAFORMAT, PARAFORMAT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PARAFORMAT** }}*/
XB_BEGIN_STRUCTURE( PARAFORMAT )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT  ( cbSize        )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD ( dwMask        )
   /*{{|member_: - MEMBER WORD wNumbering }}*/
   _XBST_WORD  ( wNumbering    )
   /*{{|member_: - MEMBER WORD wReserved }}*/
   _XBST_WORD  ( wReserved     )
   /*{{|member_: - MEMBER LONG dxStartIndent }}*/
   _XBST_LONG  ( dxStartIndent )
   /*{{|member_: - MEMBER LONG dxRightIndent }}*/
   _XBST_LONG  ( dxRightIndent )
   /*{{|member_: - MEMBER LONG dxOffset }}*/
   _XBST_LONG  ( dxOffset      )
   /*{{|member_: - MEMBER WORD wAlignment }}*/
   _XBST_WORD  ( wAlignment    )
   /*{{|member_: - MEMBER SHORT cTabCount }}*/
   _XBST_SHORT ( cTabCount     )
   /*{{|member_: - MEMBER BINSTR rgxTabs }}*/
   _XBST_BINSTR( rgxTabs, (MAX_TAB_STOPS * sizeof(LONG)) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PARAFORMAT2
            | _slug_: wapist_paraformat2
            | class-function: WAPIST_PARAFORMAT2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PARAFORMAT2 structure. Defined as PARAFORMAT2 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-paraformat2
            | _kw_: WAPIST_PARAFORMAT2, PARAFORMAT2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PARAFORMAT2** }}*/
XB_BEGIN_STRUCTURE( PARAFORMAT2 )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT  ( cbSize        )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD ( dwMask        )
   /*{{|member_: - MEMBER WORD wNumbering }}*/
   _XBST_WORD  ( wNumbering    )
   /*{{|member_: - MEMBER WORD wReserved }}*/
   _XBST_WORD  ( wReserved     )
   /*{{|member_: - MEMBER LONG dxStartIndent }}*/
   _XBST_LONG  ( dxStartIndent )
   /*{{|member_: - MEMBER LONG dxRightIndent }}*/
   _XBST_LONG  ( dxRightIndent )
   /*{{|member_: - MEMBER LONG dxOffset }}*/
   _XBST_LONG  ( dxOffset      )
   /*{{|member_: - MEMBER WORD wAlignment }}*/
   _XBST_WORD  ( wAlignment    )
   /*{{|member_: - MEMBER SHORT cTabCount }}*/
   _XBST_SHORT ( cTabCount     )
   /*{{|member_: - MEMBER BINSTR rgxTabs }}*/
   _XBST_BINSTR( rgxTabs, (MAX_TAB_STOPS * sizeof(LONG)) )
   /*{{|member_: - MEMBER LONG dySpaceBefore }}*/
   _XBST_LONG  ( dySpaceBefore    )
   /*{{|member_: - MEMBER LONG dySpaceAfter }}*/
   _XBST_LONG  ( dySpaceAfter     )
   /*{{|member_: - MEMBER LONG dyLineSpacing }}*/
   _XBST_LONG  ( dyLineSpacing    )
   /*{{|member_: - MEMBER SHORT sStyle }}*/
   _XBST_SHORT ( sStyle           )
   /*{{|member_: - MEMBER BYTE bLineSpacingRule }}*/
   _XBST_BYTE  ( bLineSpacingRule )
   /*{{|member_: - MEMBER BYTE bOutlineLevel }}*/
   _XBST_BYTE  ( bOutlineLevel    )
   /*{{|member_: - MEMBER WORD wShadingWeight }}*/
   _XBST_WORD  ( wShadingWeight   )
   /*{{|member_: - MEMBER WORD wShadingStyle }}*/
   _XBST_WORD  ( wShadingStyle    )
   /*{{|member_: - MEMBER WORD wNumberingStart }}*/
   _XBST_WORD  ( wNumberingStart  )
   /*{{|member_: - MEMBER WORD wNumberingStyle }}*/
   _XBST_WORD  ( wNumberingStyle  )
   /*{{|member_: - MEMBER WORD wNumberingTab }}*/
   _XBST_WORD  ( wNumberingTab    )
   /*{{|member_: - MEMBER WORD wBorderSpace }}*/
   _XBST_WORD  ( wBorderSpace     )
   /*{{|member_: - MEMBER WORD wBorderWidth }}*/
   _XBST_WORD  ( wBorderWidth     )
   /*{{|member_: - MEMBER WORD wBorders }}*/
   _XBST_WORD  ( wBorders         )
   pc->GwstSetOffset(sizeof(PARAFORMAT2) ); // align to 4 bytes boundary
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PUNCTUATION
            | _slug_: wapist_punctuation
            | class-function: WAPIST_PUNCTUATION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PUNCTUATION structure. Defined as PUNCTUATION in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PUNCTUATION, PUNCTUATION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PUNCTUATION** }}*/
XB_BEGIN_STRUCTURE( PUNCTUATION )
   /*{{|member_: - MEMBER UINT iSize }}*/
   _XBST_UINT   ( iSize         )
   /*{{|member_: - MEMBER LPSTR szPunctuation }}*/
   _XBST_LPSTR  ( szPunctuation )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_REOBJECT
            | _slug_: wapist_reobject
            | class-function: WAPIST_REOBJECT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi REOBJECT structure. Defined as REOBJECT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_REOBJECT, REOBJECT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  REOBJECT** }}*/
XB_BEGIN_STRUCTURE( REOBJECT )
   /*{{|member_: - MEMBER DWORD cbStruct }}*/
   _XBST_DWORD  ( cbStruct )
   /*{{|member_: - MEMBER LONG cp }}*/
   _XBST_LONG   ( cp       )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_clsid> wapist_CLSID}} clsid }}*/
   _XBST_CLSID  ( clsid    )
   /*{{|member_: - MEMBER DWORD poleobj }}*/
   _XBST_DWORD  ( poleobj  )
   /*{{|member_: - MEMBER DWORD pstg }}*/
   _XBST_DWORD  ( pstg     )
   /*{{|member_: - MEMBER DWORD polesite }}*/
   _XBST_DWORD  ( polesite )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_sizel> wapist_SIZEL}} sizel }}*/
   _XBST_SIZEL  ( sizel    )
   /*{{|member_: - MEMBER DWORD dvaspect }}*/
   _XBST_DWORD  ( dvaspect )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD  ( dwFlags  )
   /*{{|member_: - MEMBER DWORD dwUser }}*/
   _XBST_DWORD  ( dwUser   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_REPASTESPECIAL
            | _slug_: wapist_repastespecial
            | class-function: WAPIST_REPASTESPECIAL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi REPASTESPECIAL structure. Defined as REPASTESPECIAL in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_REPASTESPECIAL, REPASTESPECIAL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  REPASTESPECIAL** }}*/
XB_BEGIN_STRUCTURE( REPASTESPECIAL )
   /*{{|member_: - MEMBER DWORD dwAspect }}*/
   _XBST_DWORD ( dwAspect )
   /*{{|member_: - MEMBER DWORD dwParam }}*/
   _XBST_DWORD ( dwParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_REQRESIZE
            | _slug_: wapist_reqresize
            | class-function: WAPIST_REQRESIZE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi REQRESIZE structure. Defined as REQRESIZE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_REQRESIZE, REQRESIZE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  REQRESIZE** }}*/
XB_BEGIN_STRUCTURE( REQRESIZE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT  ( rc    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SELCHANGE
            | _slug_: wapist_selchange
            | class-function: WAPIST_SELCHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SELCHANGE structure. Defined as SELCHANGE in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/richedit/ns-richedit-selchange
            | _kw_: WAPIST_SELCHANGE, SELCHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SELCHANGE** }}*/
XB_BEGIN_STRUCTURE( SELCHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR      ( nmhdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE  ( chrg   )
   /*{{|member_: - MEMBER WORD seltyp }}*/
   _XBST_WORD       ( seltyp )
   pc->GwstSetOffset(sizeof(SELCHANGE) ); // align to 4 bytes boundary
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SETTEXTEX
            | _slug_: wapist_settextex
            | class-function: WAPIST_SETTEXTEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SETTEXTEX structure. Defined as SETTEXTEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SETTEXTEX, SETTEXTEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SETTEXTEX** }}*/
XB_BEGIN_STRUCTURE( SETTEXTEX )
   /*{{|member_: - MEMBER DWORD flags }}*/
   _XBST_DWORD ( flags    )
   /*{{|member_: - MEMBER UINT codepage }}*/
   _XBST_UINT  ( codepage )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TEXTRANGE
            | _slug_: wapist_textrange
            | class-function: WAPIST_TEXTRANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TEXTRANGE structure. Defined as TEXTRANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TEXTRANGE, TEXTRANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TEXTRANGE** }}*/
XB_BEGIN_STRUCTURE( TEXTRANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_charrange> wapist_CHARRANGE}} chrg }}*/
   _XBST_CHARRANGE ( chrg      )
   /*{{|member_: - MEMBER LPSTR lpstrText }}*/
   _XBST_LPSTR     ( lpstrText )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_GUID
            | _slug_: wapist_guid
            | class-function: WAPIST_GUID
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi GUID structure. Defined as GUID in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_GUID, GUID, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  GUID** }}*/
XB_BEGIN_STRUCTURE( GUID )
   /*{{|member_: - MEMBER ULONG Data1 }}*/
   _XBST_ULONG   ( Data1 )
   /*{{|member_: - MEMBER WORD Data2 }}*/
   _XBST_WORD    ( Data2 )
   /*{{|member_: - MEMBER WORD Data3 }}*/
   _XBST_WORD    ( Data3 )
   /*{{|member_: - MEMBER BINSTR Data4 }}*/
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CLSID
            | _slug_: wapist_clsid
            | class-function: WAPIST_CLSID
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CLSID structure. Defined as CLSID in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_CLSID, CLSID, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CLSID** }}*/
XB_BEGIN_STRUCTURE( CLSID )
   /*{{|member_: - MEMBER ULONG Data1 }}*/
   _XBST_ULONG   ( Data1 )
   /*{{|member_: - MEMBER WORD Data2 }}*/
   _XBST_WORD    ( Data2 )
   /*{{|member_: - MEMBER WORD Data3 }}*/
   _XBST_WORD    ( Data3 )
   /*{{|member_: - MEMBER BINSTR Data4 }}*/
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
// winsock structures
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IN_ADDR
            | _slug_: wapist_in_addr
            | class-function: WAPIST_IN_ADDR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IN_ADDR structure. Defined as IN_ADDR in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock2/ns-winsock2-in_addr
            | _kw_: WAPIST_IN_ADDR, IN_ADDR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IN_ADDR** }}*/
XB_BEGIN_STRUCTURE( IN_ADDR )
   /*{{|member_: - MEMBER BYTE s_b1 }}*/
   /*{{|member_: - MEMBER BYTE s_net |desc_: Helper member mapped over ::s_b1. }}*/
   _XBST_BYTE    ( s_b1 ) ; pc->GwstBack() ; _XBST_BYTE( s_net   )
   /*{{|member_: - MEMBER BYTE s_b2 }}*/
   /*{{|member_: - MEMBER BYTE s_host |desc_: Helper member mapped over ::s_b2. }}*/
   _XBST_BYTE    ( s_b2 ) ; pc->GwstBack() ; _XBST_BYTE( s_host  )
   /*{{|member_: - MEMBER BYTE s_b3 }}*/
   /*{{|member_: - MEMBER BYTE s_lh |desc_: Helper member mapped over ::s_b3. }}*/
   _XBST_BYTE    ( s_b3 ) ; pc->GwstBack() ; _XBST_BYTE( s_lh    )
   /*{{|member_: - MEMBER BYTE s_b4 }}*/
   /*{{|member_: - MEMBER BYTE s_impno |desc_: Helper member mapped over ::s_b4. }}*/
   _XBST_BYTE    ( s_b4 ) ; pc->GwstBack() ; _XBST_BYTE( s_impno )
   pc->GwstSetOffset(0);
   /*{{|member_: - MEMBER WORD s_w1 }}*/
   _XBST_WORD    ( s_w1 )
   /*{{|member_: - MEMBER WORD s_w2 }}*/
   /*{{|member_: - MEMBER WORD s_imp |desc_: Helper member mapped over ::s_w2. }}*/
   _XBST_WORD    ( s_w2 ) ; pc->GwstBack() ; _XBST_WORD( s_imp )
   pc->GwstSetOffset(0);
   /*{{|member_: - MEMBER DWORD S_addr }}*/
   _XBST_DWORD   ( S_addr )
   /*{{|property_: - PROPERTY S_un_b |desc_: Returns Self: the struct members are mapped directly on this object. }}*/
   pc->PropertyCB("S_un_b" , "{|s| s }");
   /*{{|property_: - PROPERTY S_un_w |desc_: Returns Self: the struct members are mapped directly on this object. }}*/
   pc->PropertyCB("S_un_w" , "{|s| s }");
   /*{{|property_: - PROPERTY S_un |desc_: Returns Self: the union members are mapped directly on this object. }}*/
   pc->PropertyCB("S_un"   , "{|s| s }");
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKADDR
            | _slug_: wapist_sockaddr
            | class-function: WAPIST_SOCKADDR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKADDR structure. Defined as SOCKADDR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SOCKADDR, SOCKADDR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKADDR** }}*/
XB_BEGIN_STRUCTURE( SOCKADDR )
   /*{{|member_: - MEMBER WORD sa_family }}*/
   _XBST_WORD    ( sa_family )
   /*{{|member_: - MEMBER BINSTR sa_data }}*/
   _XBST_BINSTR  ( sa_data , 14 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKET_ADDRESS
            | _slug_: wapist_socket_address
            | class-function: WAPIST_SOCKET_ADDRESS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKET_ADDRESS structure. Defined as SOCKET_ADDRESS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_SOCKET_ADDRESS, SOCKET_ADDRESS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKET_ADDRESS** }}*/
XB_BEGIN_STRUCTURE( SOCKET_ADDRESS )
   /*{{|member_: - MEMBER POINTER32 lpSockaddr }}*/
   _XBST_POINTER( lpSockaddr )
   /*{{|member_: - MEMBER INT iSockaddrLength }}*/
   _XBST_INT(     iSockaddrLength )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKET_ADDRESS_LIST
            | _slug_: wapist_socket_address_list
            | class-function: WAPIST_SOCKET_ADDRESS_LIST
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKET_ADDRESS_LIST structure. Defined as SOCKET_ADDRESS_LIST in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-socket_address_list
            | _kw_: WAPIST_SOCKET_ADDRESS_LIST, SOCKET_ADDRESS_LIST, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKET_ADDRESS_LIST** }}*/
XB_BEGIN_STRUCTURE( SOCKET_ADDRESS_LIST )
   /*{{|member_: - MEMBER INT iAddressCount }}*/
   _XBST_INT( iAddressCount )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_socket_address> wapist_SOCKET_ADDRESS}} _Address_ }}*/
   _XBST_SOCKET_ADDRESS(  _Address_ )
   pc->Var( "_aa_" );
   pc->GwstBack();
   /*{{|member_: - MEMBER embedded array of @ {{ilink: <slug wapist_socket_address> wapist_SOCKET_ADDRESS}} Address
            | desc_: Embedded structure array of WAPIST_SOCKET_ADDRESS elements mapped over ::_Address_; the element
              count is read from ::iAddressCount.
   }}*/
   pc->Member_EmbededStructArray( "Address","WAPIST_SOCKET_ADDRESS","_Address_","iAddressCount",
                                  pc->GwstGetOffset(),sizeof(SOCKET_ADDRESS) );
   /*{{|method_: - `METHOD ReqSize( n )`
            | return: Numeric
            | desc_: Returns the byte size required for the requested address count.
   }}*/
   pc->MethodCB( "ReqSize" , pc->cbbs("{|s,n| iif(n == NIL,n := s:iAddressCount,),n := iif(n < 1, 0, n-1),"
                                              "s:_sizeof_() + ( n * %i)  }", sizeof(SOCKET_ADDRESS) ));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_CSADDR_INFO
            | _slug_: wapist_csaddr_info
            | class-function: WAPIST_CSADDR_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi CSADDR_INFO structure. Defined as CSADDR_INFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_CSADDR_INFO, CSADDR_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  CSADDR_INFO** }}*/
XB_BEGIN_STRUCTURE( CSADDR_INFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_socket_address> wapist_SOCKET_ADDRESS}} LocalAddr }}*/
   _XBST_SOCKET_ADDRESS(  LocalAddr )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_socket_address> wapist_SOCKET_ADDRESS}} RemoteAddr }}*/
   _XBST_SOCKET_ADDRESS(  RemoteAddr )
   /*{{|member_: - MEMBER INT iSocketType }}*/
   _XBST_INT( iSocketType )
   /*{{|member_: - MEMBER INT iProtocol }}*/
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKADDR_STORAGE
            | _slug_: wapist_sockaddr_storage
            | class-function: WAPIST_SOCKADDR_STORAGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKADDR_STORAGE structure. Defined as SOCKADDR_STORAGE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_SOCKADDR_STORAGE, SOCKADDR_STORAGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKADDR_STORAGE** }}*/
XB_BEGIN_STRUCTURE( SOCKADDR_STORAGE )
   /*{{|member_: - MEMBER SHORT ss_family }}*/
   _XBST_SHORT( ss_family )
   /*{{|member_: - MEMBER BINSTR __ss_pad1 }}*/
   _XBST_BINSTR( __ss_pad1 , 6 )
   /*{{|member_: - MEMBER INT64 __ss_align }}*/
   _XBST_INT64(__ss_align )
   /*{{|member_: - MEMBER BINSTR __ss_pad2 }}*/
   _XBST_BINSTR( __ss_pad2 , 112 )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SCOPE_ID
            | _slug_: wapist_scope_id
            | class-function: WAPIST_SCOPE_ID
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SCOPE_ID structure. Defined as SCOPE_ID in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/ws2ipdef/ns-ws2ipdef-scope_id
            | _kw_: WAPIST_SCOPE_ID, SCOPE_ID, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SCOPE_ID** }}*/
XB_BEGIN_STRUCTURE( SCOPE_ID )
   /*{{|member_: - MEMBER DWORD Value }}*/
   _XBST_DWORD( Value )
   /*{{|member_: - MEMBER DWORD Zone |desc_: Bit field mapped over ::Value: bit offset 0, width 28 bits. }}*/
   pc->Member_BitField("Zone","Value",0,28,32);
   /*{{|member_: - MEMBER DWORD Level |desc_: Bit field mapped over ::Value: bit offset 28, width 4 bits. }}*/
   pc->Member_BitField("Level","Value",28,4,32);
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKADDR_IN
            | _slug_: wapist_sockaddr_in
            | class-function: WAPIST_SOCKADDR_IN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKADDR_IN structure. Defined as SOCKADDR_IN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SOCKADDR_IN, SOCKADDR_IN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKADDR_IN** }}*/
XB_BEGIN_STRUCTURE( SOCKADDR_IN )
   /*{{|member_: - MEMBER WORD sin_family }}*/
   _XBST_WORD( sin_family  )
   /*{{|member_: - MEMBER WORD sin_port }}*/
   _XBST_WORD( sin_port    )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_in_addr> wapist_IN_ADDR}} sin_addr }}*/
   _XBST_IN_ADDR( sin_addr )
   /*{{|member_: - MEMBER BINSTR sin_zero }}*/
   _XBST_BINSTR( sin_zero , 8)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSABUF
            | _slug_: wapist_wsabuf
            | class-function: WAPIST_WSABUF
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSABUF structure. Defined as WSABUF in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSABUF, WSABUF, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSABUF** }}*/
XB_BEGIN_STRUCTURE( WSABUF )
   /*{{|member_: - MEMBER ULONG len }}*/
   _XBST_ULONG( len )
   /*{{|member_: - MEMBER LPSTR buf }}*/
   _XBST_LPSTR( buf )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
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
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAMSG
            | _slug_: wapist_wsamsg
            | class-function: WAPIST_WSAMSG
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinSock WSAMSG structure. Defined as WSAMSG in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-wsamsg
            | _kw_: WAPIST_WSAMSG, WSAMSG, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAMSG** }}*/
XB_BEGIN_STRUCTURE( WSAMSG )
   /*{{|member_: - MEMBER POINTER32 name }}*/
   _XBST_POINTER32( name )
   /*{{|member_: - MEMBER INT namelen }}*/
   _XBST_INT(       namelen )
   /*{{|member_: - MEMBER POINTER32 lpBuffers }}*/
   _XBST_POINTER32( lpBuffers )
   /*{{|member_: - MEMBER ULONG dwBufferCount }}*/
   _XBST_ULONG(     dwBufferCount)
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsabuf> wapist_WSABUF}} Control }}*/
   _XBST_WSABUF(    Control )
   /*{{|member_: - MEMBER ULONG dwFlags }}*/
   _XBST_ULONG(     dwFlags )

   /*{{|class-method_: - CLASS METHOD CMSGHDR_ALIGN( p ) }}*/
   pc->ClassMethodCB( "CMSGHDR_ALIGN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSGHDR_ALIGN ));
   /*{{|class-method_: - CLASS METHOD CMSGDATA_ALIGN( p ) }}*/
   pc->ClassMethodCB( "CMSGDATA_ALIGN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSGDATA_ALIGN ));

   /*{{|class-method_: - CLASS METHOD CMSG_FIRSTHDR( p ) }}*/
   pc->ClassMethodCB( "CMSG_FIRSTHDR" ,pc->cbbs("{|s,p| FpQCall(%i,\"__pt__pt\",p)}",
                      common_structures_ns::wsamsg_CMSG_FIRSTHDR ));
   /*{{|class-method_: - CLASS METHOD CMSG_NXTHDR( p1 , p2 ) }}*/
   pc->ClassMethodCB( "CMSG_NXTHDR" ,pc->cbbs("{|s,p1,p2| FpQCall(%i,\"__pt__pt__pt\",p1,p2)}",
                      common_structures_ns::wsamsg_CMSG_NXTHDR ));

   /*{{|class-method_: - CLASS METHOD CMSG_DATA( p ) }}*/
   pc->ClassMethodCB( "CMSG_DATA" ,pc->cbbs("{|s,p| FpQCall(%i,\"__pt__pt\",p)}",
                      common_structures_ns::wsamsg_CMSG_DATA ));

   /*{{|class-method_: - CLASS METHOD CMSG_SPACE( p ) }}*/
   pc->ClassMethodCB( "CMSG_SPACE" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSG_SPACE ));
   /*{{|class-method_: - CLASS METHOD CMSG_LEN( p ) }}*/
   pc->ClassMethodCB( "CMSG_LEN" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__sl\",p)}",
                      common_structures_ns::wsamsg_CMSG_LEN ));

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACMSGHDR
            | _slug_: wapist_wsacmsghdr
            | class-function: WAPIST_WSACMSGHDR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACMSGHDR structure. Defined as WSACMSGHDR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSACMSGHDR, WSACMSGHDR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACMSGHDR** }}*/
XB_BEGIN_STRUCTURE( WSACMSGHDR )
   /*{{|member_: - MEMBER SIZE_T cmsg_len }}*/
   _XBST_SIZE_T(  cmsg_len   )
   /*{{|member_: - MEMBER INT cmsg_level }}*/
   _XBST_INT(     cmsg_level )
   /*{{|member_: - MEMBER INT cmsg_type }}*/
   _XBST_INT(     cmsg_type  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
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
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FD_SET
            | _slug_: wapist_fd_set
            | class-function: WAPIST_FD_SET
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FD_SET structure. Defined as FD_SET in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-fd_set
            | _kw_: WAPIST_FD_SET, FD_SET, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FD_SET** }}*/
XB_BEGIN_STRUCTURE( FD_SET )
   /*{{|member_: - MEMBER UINT fd_count }}*/
   _XBST_UINT( fd_count )
   /*{{|member_: - MEMBER BINSTR fd_array }}*/
   _XBST_BINSTR( fd_array , 64 * sizeof(SOCKET) )
   /*{{|class-method_: - CLASS METHOD FD_CLR( n , p ) }}*/
   pc->ClassMethodCB( "FD_CLR" ,pc->cbbs("{|s,n,p|FpQCall(%i,\"__sl__sl__pt__sl\",n,@p)}",
                      common_structures_ns::fd_set_FD_CLR ));
   /*{{|class-method_: - CLASS METHOD FD_SET( n , p , cs ) }}*/
   pc->ClassMethodCB( "FD_SET" ,pc->cbbs("{|s,n,p,cs|iif(cs == NIL,cs := 64,),"
                                          " FpQCall(%i,\"__sl__sl__pt__sl\",n,@p,cs)}",
                      common_structures_ns::fd_set_FD_SET ));
   /*{{|class-method_: - CLASS METHOD FD_ZERO( p ) }}*/
   pc->ClassMethodCB( "FD_ZERO" ,pc->cbbs("{|s,p| FpQCall(%i,\"__sl__pt\",@p)}",
                      common_structures_ns::fd_set_FD_ZERO ));
   /*{{|class-method_: - CLASS METHOD FD_ISSET( n , p ) }}*/
   pc->ClassMethodCB( "FD_ISSET" ,pc->cbbs("{|s,n,p| FpQCall(%i,\"__sl__sl__pt\",n,@p)}",
                      common_structures_ns::fd_set_FD_ISSET ));

XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TIMEVAL
            | _slug_: wapist_timeval
            | class-function: WAPIST_TIMEVAL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TIMEVAL structure. Defined as TIMEVAL in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-timeval
            | _kw_: WAPIST_TIMEVAL, TIMEVAL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TIMEVAL** }}*/
XB_BEGIN_STRUCTURE( TIMEVAL )
   /*{{|member_: - MEMBER LONG tv_sec }}*/
   _XBST_LONG(  tv_sec  )
   /*{{|member_: - MEMBER LONG tv_usec }}*/
   _XBST_LONG(  tv_usec )
   /*{{|method_: - `METHOD IsSet()` |return: Logical }}*/
   pc->MethodCB("IsSet","{|s| nOr(s:tv_sec,s:tv_usec) != 0 }");
   /*{{|method_: - `METHOD Clear()` |return: Self }}*/
   pc->MethodCB("Clear","{|s| s:tv_sec := 0 , s:tv_usec := 0 , s}");
   /*{{|class-method_: - CLASS METHOD cmp( a , b ) }}*/
   pc->ClassMethodCB("cmp","{|s,a,b|i64cmp({a:tv_usec,a:tv_sec},{b:tv_usec,b:tv_sec})}");
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HOSTENT
            | _slug_: wapist_hostent
            | class-function: WAPIST_HOSTENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HOSTENT structure. Defined as HOSTENT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-hostent
            | _kw_: WAPIST_HOSTENT, HOSTENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HOSTENT** }}*/
XB_BEGIN_STRUCTURE( HOSTENT )
   /*{{|member_: - MEMBER LPSTR h_name }}*/
   /*{{|member_: - MEMBER DYNSZ cName |desc_: Helper member mapped over ::h_name. }}*/
   _XBST_LPSTR(     h_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   /*{{|member_: - MEMBER POINTER32 h_aliases }}*/
   _XBST_POINTER32( h_aliases  )
   /*{{|member_: - MEMBER SHORT h_addrtype }}*/
   _XBST_short(     h_addrtype )
   /*{{|member_: - MEMBER SHORT h_length }}*/
   _XBST_short(     h_length   )
   /*{{|member_: - MEMBER POINTER32 h_addr_list }}*/
   /*{{|member_: - MEMBER POINTER32 h_addr |desc_: Helper member mapped over ::h_addr_list. }}*/
   _XBST_POINTER32( h_addr_list) ; pc->GwstBack() ; _XBST_POINTER32( h_addr)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NETENT
            | _slug_: wapist_netent
            | class-function: WAPIST_NETENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NETENT structure. Defined as NETENT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-netent
            | _kw_: WAPIST_NETENT, NETENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NETENT** }}*/
XB_BEGIN_STRUCTURE( NETENT )
   /*{{|member_: - MEMBER LPSTR n_name }}*/
   /*{{|member_: - MEMBER DYNSZ cName |desc_: Helper member mapped over ::n_name. }}*/
   _XBST_LPSTR(     n_name     ) ; pc->GwstBack();  pc->Member_DynSz("cName");
   /*{{|member_: - MEMBER POINTER32 n_aliases }}*/
   _XBST_POINTER32( n_aliases  )
   /*{{|member_: - MEMBER SHORT n_addrtype }}*/
   _XBST_short(     n_addrtype )
   pc->GwstSetOffset( FIELD_OFFSET( netent , n_net     ) );
   /*{{|member_: - MEMBER DWORD n_net }}*/
   _XBST_DWORD(     n_net      )
   pc->GwstAdjustSize( sizeof(netent) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SERVENT
            | _slug_: wapist_servent
            | class-function: WAPIST_SERVENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SERVENT structure. Defined as SERVENT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-servent
            | _kw_: WAPIST_SERVENT, SERVENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SERVENT** }}*/
XB_BEGIN_STRUCTURE( SERVENT )
   /*{{|member_: - MEMBER LPSTR s_name }}*/
   /*{{|member_: - MEMBER DYNSZ cName |desc_: Helper member mapped over ::s_name. }}*/
   _XBST_LPSTR(     s_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   /*{{|member_: - MEMBER POINTER32 s_aliases }}*/
   _XBST_POINTER32( s_aliases  )
   /*{{|member_: - MEMBER SHORT s_port }}*/
   _XBST_short(     s_port )
   pc->GwstSetOffset( FIELD_OFFSET( servent , s_proto ) );
   /*{{|member_: - MEMBER LPSTR s_proto }}*/
   /*{{|member_: - MEMBER DYNSZ cProto |desc_: Helper member mapped over ::s_proto. }}*/
   _XBST_LPSTR(     s_proto     ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(servent) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PROTOENT
            | _slug_: wapist_protoent
            | class-function: WAPIST_PROTOENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PROTOENT structure. Defined as PROTOENT in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-protoent
            | _kw_: WAPIST_PROTOENT, PROTOENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PROTOENT** }}*/
XB_BEGIN_STRUCTURE( PROTOENT )
   /*{{|member_: - MEMBER LPSTR p_name }}*/
   /*{{|member_: - MEMBER DYNSZ cName |desc_: Helper member mapped over ::p_name. }}*/
   _XBST_LPSTR(     p_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   /*{{|member_: - MEMBER POINTER32 p_aliases }}*/
   _XBST_POINTER32( p_aliases  )
   /*{{|member_: - MEMBER SHORT p_proto }}*/
   /*{{|member_: - MEMBER DYNSZ cProto |desc_: Helper member mapped over ::p_proto. }}*/
   _XBST_short(     p_proto    ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(protoent) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSADATA
            | _slug_: wapist_wsadata
            | class-function: WAPIST_WSADATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSADATA structure. Defined as WSADATA in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata
            | _kw_: WAPIST_WSADATA, WSADATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSADATA** }}*/
XB_BEGIN_STRUCTURE( WSADATA )
   /*{{|member_: - MEMBER WORD wVersion }}*/
   _XBST_WORD(     wVersion )
   /*{{|member_: - MEMBER WORD wHighVersion }}*/
   _XBST_WORD(     wHighVersion )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , szDescription ) );
   /*{{|member_: - MEMBER SZSTR szDescription }}*/
   _XBST_SZSTR(    szDescription  , (WSADESCRIPTION_LEN+1) )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , szSystemStatus ) );
   /*{{|member_: - MEMBER SZSTR szSystemStatus }}*/
   _XBST_SZSTR(    szSystemStatus , (WSASYS_STATUS_LEN+1 ) )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , iMaxSockets ) );
   /*{{|member_: - MEMBER WORD iMaxSockets }}*/
   _XBST_WORD(     iMaxSockets  )
   /*{{|member_: - MEMBER WORD iMaxUdpDg }}*/
   _XBST_WORD(     iMaxUdpDg    )
   pc->GwstSetOffset( FIELD_OFFSET( WSADATA , lpVendorInfo ) );
   /*{{|member_: - MEMBER LPSTR lpVendorInfo }}*/
   _XBST_LPSTR(    lpVendorInfo )
   pc->GwstAdjustSize( sizeof(WSADATA) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SOCKPROTO
            | _slug_: wapist_sockproto
            | class-function: WAPIST_SOCKPROTO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SOCKPROTO structure. Defined as SOCKPROTO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SOCKPROTO, SOCKPROTO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SOCKPROTO** }}*/
XB_BEGIN_STRUCTURE( SOCKPROTO )
   /*{{|member_: - MEMBER WORD sp_family }}*/
   _XBST_WORD(     sp_family   )
   /*{{|member_: - MEMBER WORD sp_protocol }}*/
   _XBST_WORD(     sp_protocol )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LINGER
            | _slug_: wapist_linger
            | class-function: WAPIST_LINGER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LINGER structure. Defined as LINGER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LINGER, LINGER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LINGER** }}*/
XB_BEGIN_STRUCTURE( LINGER )
   /*{{|member_: - MEMBER WORD l_onoff }}*/
   _XBST_WORD(     l_onoff  )
   /*{{|member_: - MEMBER WORD l_linger }}*/
   _XBST_WORD(     l_linger )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_FLOWSPEC
            | _slug_: wapist_flowspec
            | class-function: WAPIST_FLOWSPEC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi FLOWSPEC structure. Defined as FLOWSPEC in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_FLOWSPEC, FLOWSPEC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  FLOWSPEC** }}*/
XB_BEGIN_STRUCTURE( FLOWSPEC )
   /*{{|member_: - MEMBER ULONG TokenRate }}*/
   _XBST_ULONG( TokenRate          )
   /*{{|member_: - MEMBER ULONG TokenBucketSize }}*/
   _XBST_ULONG( TokenBucketSize    )
   /*{{|member_: - MEMBER ULONG PeakBandwidth }}*/
   _XBST_ULONG( PeakBandwidth      )
   /*{{|member_: - MEMBER ULONG Latency }}*/
   _XBST_ULONG( Latency            )
   /*{{|member_: - MEMBER ULONG DelayVariation }}*/
   _XBST_ULONG( DelayVariation     )
   /*{{|member_: - MEMBER ULONG ServiceType }}*/
   _XBST_ULONG( ServiceType        )
   /*{{|member_: - MEMBER ULONG MaxSduSize }}*/
   _XBST_ULONG( MaxSduSize         )
   /*{{|member_: - MEMBER ULONG MinimumPolicedSize }}*/
   _XBST_ULONG( MinimumPolicedSize )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_QOS_OBJECT_HDR
            | _slug_: wapist_qos_object_hdr
            | class-function: WAPIST_QOS_OBJECT_HDR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi QOS_OBJECT_HDR structure. Defined as QOS_OBJECT_HDR in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_QOS_OBJECT_HDR, QOS_OBJECT_HDR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  QOS_OBJECT_HDR** }}*/
XB_BEGIN_STRUCTURE( QOS_OBJECT_HDR )
   /*{{|member_: - MEMBER ULONG ObjectType }}*/
   _XBST_ULONG( ObjectType    )
   /*{{|member_: - MEMBER ULONG ObjectLength }}*/
   _XBST_ULONG( ObjectLength  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_QOS_SD_MODE
            | _slug_: wapist_qos_sd_mode
            | class-function: WAPIST_QOS_SD_MODE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi QOS_SD_MODE structure. Defined as QOS_SD_MODE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_QOS_SD_MODE, QOS_SD_MODE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  QOS_SD_MODE** }}*/
XB_BEGIN_STRUCTURE( QOS_SD_MODE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_qos_object_hdr> wapist_QOS_OBJECT_HDR}} ObjectHdr }}*/
   _XBST_QOS_OBJECT_HDR( ObjectHdr          )
   /*{{|member_: - MEMBER ULONG ShapeDiscardMode }}*/
   _XBST_ULONG(          ShapeDiscardMode   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_QOS_SHAPING_RATE
            | _slug_: wapist_qos_shaping_rate
            | class-function: WAPIST_QOS_SHAPING_RATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi QOS_SHAPING_RATE structure. Defined as QOS_SHAPING_RATE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_QOS_SHAPING_RATE, QOS_SHAPING_RATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  QOS_SHAPING_RATE** }}*/
XB_BEGIN_STRUCTURE( QOS_SHAPING_RATE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_qos_object_hdr> wapist_QOS_OBJECT_HDR}} ObjectHdr }}*/
   _XBST_QOS_OBJECT_HDR  ( ObjectHdr   )
   /*{{|member_: - MEMBER ULONG ShapingRate }}*/
   _XBST_ULONG           ( ShapingRate )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_QOS
            | _slug_: wapist_qos
            | class-function: WAPIST_QOS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi QOS structure. Defined as QOS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_QOS, QOS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  QOS** }}*/
XB_BEGIN_STRUCTURE( QOS )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_flowspec> wapist_FLOWSPEC}} SendingFlowspec }}*/
   _XBST_FLOWSPEC ( SendingFlowspec   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_flowspec> wapist_FLOWSPEC}} ReceivingFlowspec }}*/
   _XBST_FLOWSPEC ( ReceivingFlowspec )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsabuf> wapist_WSABUF}} ProviderSpecific }}*/
   _XBST_WSABUF   ( ProviderSpecific  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSANETWORKEVENTS
            | _slug_: wapist_wsanetworkevents
            | class-function: WAPIST_WSANETWORKEVENTS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSANETWORKEVENTS structure. Defined as WSANETWORKEVENTS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSANETWORKEVENTS, WSANETWORKEVENTS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSANETWORKEVENTS** }}*/
XB_BEGIN_STRUCTURE( WSANETWORKEVENTS )
   /*{{|member_: - MEMBER LONG lNetworkEvents }}*/
   _XBST_LONG(   lNetworkEvents )
   /*{{|member_: - MEMBER BINSTR iErrorCode }}*/
   _XBST_BINSTR( iErrorCode, (FD_MAX_EVENTS * sizeof(int)) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAPROTOCOLCHAIN
            | _slug_: wapist_wsaprotocolchain
            | class-function: WAPIST_WSAPROTOCOLCHAIN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAPROTOCOLCHAIN structure. Defined as WSAPROTOCOLCHAIN in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSAPROTOCOLCHAIN, WSAPROTOCOLCHAIN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAPROTOCOLCHAIN** }}*/
XB_BEGIN_STRUCTURE( WSAPROTOCOLCHAIN )
   /*{{|member_: - MEMBER INT ChainLen }}*/
   _XBST_int(    ChainLen )
   /*{{|member_: - MEMBER BINSTR ChainEntries }}*/
   _XBST_BINSTR( ChainEntries , (MAX_PROTOCOL_CHAIN * sizeof(DWORD) ) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAPROTOCOL_INFO
            | _slug_: wapist_wsaprotocol_info
            | class-function: WAPIST_WSAPROTOCOL_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAPROTOCOL_INFO structure. Defined as WSAPROTOCOL_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSAPROTOCOL_INFO, WSAPROTOCOL_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAPROTOCOL_INFO** }}*/
XB_BEGIN_STRUCTURE( WSAPROTOCOL_INFO )
   /*{{|member_: - MEMBER DWORD dwServiceFlags1 }}*/
   _XBST_DWORD            ( dwServiceFlags1                  )
   /*{{|member_: - MEMBER DWORD dwServiceFlags2 }}*/
   _XBST_DWORD            ( dwServiceFlags2                  )
   /*{{|member_: - MEMBER DWORD dwServiceFlags3 }}*/
   _XBST_DWORD            ( dwServiceFlags3                  )
   /*{{|member_: - MEMBER DWORD dwServiceFlags4 }}*/
   _XBST_DWORD            ( dwServiceFlags4                  )
   /*{{|member_: - MEMBER DWORD dwProviderFlags }}*/
   _XBST_DWORD            ( dwProviderFlags                  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_guid> wapist_GUID}} ProviderId }}*/
   _XBST_GUID             ( ProviderId                       )
   /*{{|member_: - MEMBER DWORD dwCatalogEntryId }}*/
   _XBST_DWORD            ( dwCatalogEntryId                 )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsaprotocolchain> wapist_WSAPROTOCOLCHAIN}} ProtocolChain }}*/
   _XBST_WSAPROTOCOLCHAIN ( ProtocolChain                    )
   /*{{|member_: - MEMBER INT iVersion }}*/
   _XBST_int              ( iVersion                         )
   /*{{|member_: - MEMBER INT iAddressFamily }}*/
   _XBST_int              ( iAddressFamily                   )
   /*{{|member_: - MEMBER INT iMaxSockAddr }}*/
   _XBST_int              ( iMaxSockAddr                     )
   /*{{|member_: - MEMBER INT iMinSockAddr }}*/
   _XBST_int              ( iMinSockAddr                     )
   /*{{|member_: - MEMBER INT iSocketType }}*/
   _XBST_int              ( iSocketType                      )
   /*{{|member_: - MEMBER INT iProtocol }}*/
   _XBST_int              ( iProtocol                        )
   /*{{|member_: - MEMBER INT iProtocolMaxOffset }}*/
   _XBST_int              ( iProtocolMaxOffset               )
   /*{{|member_: - MEMBER INT iNetworkByteOrder }}*/
   _XBST_int              ( iNetworkByteOrder                )
   /*{{|member_: - MEMBER INT iSecurityScheme }}*/
   _XBST_int              ( iSecurityScheme                  )
   /*{{|member_: - MEMBER DWORD dwMessageSize }}*/
   _XBST_DWORD            ( dwMessageSize                    )
   /*{{|member_: - MEMBER DWORD dwProviderReserved }}*/
   _XBST_DWORD            ( dwProviderReserved               )
   /*{{|member_: - MEMBER BINSTR szProtocol }}*/
   _XBST_BINSTR           ( szProtocol , (WSAPROTOCOL_LEN+1) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE
            | _slug_: wapist_wsacompletion_ns_windowmessage
            | class-function: WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACOMPLETION_NS_WINDOWMESSAGE structure. Defined as
              WSACOMPLETION_NS_WINDOWMESSAGE in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSACOMPLETION_NS_WINDOWMESSAGE, WSACOMPLETION_NS_WINDOWMESSAGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION_NS_WINDOWMESSAGE** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_WINDOWMESSAGE )
   /*{{|member_: - MEMBER HWND hWnd }}*/
   _XBST_HWND   ( hWnd    )
   /*{{|member_: - MEMBER UINT uMsg }}*/
   _XBST_UINT   ( uMsg    )
   /*{{|member_: - MEMBER WPARAM context }}*/
   _XBST_WPARAM ( context )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION_NS_EVENT
            | _slug_: wapist_wsacompletion_ns_event
            | class-function: WAPIST_WSACOMPLETION_NS_EVENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACOMPLETION_NS_EVENT structure. Defined as WSACOMPLETION_NS_EVENT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSACOMPLETION_NS_EVENT, WSACOMPLETION_NS_EVENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION_NS_EVENT** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_EVENT )
   /*{{|member_: - MEMBER POINTER32 lpOverlapped }}*/
   _XBST_POINTER32 ( lpOverlapped )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION_NS_APC
            | _slug_: wapist_wsacompletion_ns_apc
            | class-function: WAPIST_WSACOMPLETION_NS_APC
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACOMPLETION_NS_APC structure. Defined as WSACOMPLETION_NS_APC in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSACOMPLETION_NS_APC, WSACOMPLETION_NS_APC, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION_NS_APC** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_APC )
   /*{{|member_: - MEMBER POINTER32 lpOverlapped }}*/
   _XBST_POINTER32 ( lpOverlapped          )
   /*{{|member_: - MEMBER POINTER32 lpfnCompletionProc }}*/
   _XBST_POINTER32 ( lpfnCompletionProc    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION_NS_PORT
            | _slug_: wapist_wsacompletion_ns_port
            | class-function: WAPIST_WSACOMPLETION_NS_PORT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACOMPLETION_NS_PORT structure. Defined as WSACOMPLETION_NS_PORT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSACOMPLETION_NS_PORT, WSACOMPLETION_NS_PORT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION_NS_PORT** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PORT )
   /*{{|member_: - MEMBER POINTER32 lpOverlapped }}*/
   _XBST_POINTER32 ( lpOverlapped )
   /*{{|member_: - MEMBER HANDLE hPort }}*/
   _XBST_HANDLE    ( hPort        )
   /*{{|member_: - MEMBER POINTER32 Key }}*/
   _XBST_POINTER32 ( Key          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION_NS_PARAMETERS
            | _slug_: wapist_wsacompletion_ns_parameters
            | class-function: WAPIST_WSACOMPLETION_NS_PARAMETERS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Auxiliary wrapper for the WSACOMPLETION namespace-provider parameter union. Defined as
              WSACOMPLETION_NS_PARAMETERS in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSACOMPLETION_NS_PARAMETERS, WSACOMPLETION_NS_PARAMETERS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION_NS_PARAMETERS** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PARAMETERS )
  pc->GwstBeginUnion();
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsacompletion_ns_windowmessage> wapist_WSACOMPLETION_NS_WINDOWMESSAGE}} WindowMessage }}*/
   _XBST_WSACOMPLETION_NS_WINDOWMESSAGE( WindowMessage )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsacompletion_ns_event> wapist_WSACOMPLETION_NS_EVENT}} Event }}*/
   _XBST_WSACOMPLETION_NS_EVENT(         Event         )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsacompletion_ns_apc> wapist_WSACOMPLETION_NS_APC}} Apc }}*/
   _XBST_WSACOMPLETION_NS_APC(           Apc           )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsacompletion_ns_port> wapist_WSACOMPLETION_NS_PORT}} Port }}*/
   _XBST_WSACOMPLETION_NS_PORT(          Port          )
  pc->GwstEndUnion();
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSACOMPLETION
            | _slug_: wapist_wsacompletion
            | class-function: WAPIST_WSACOMPLETION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSACOMPLETION structure. Defined as WSACOMPLETION in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSACOMPLETION, WSACOMPLETION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSACOMPLETION** }}*/
XB_BEGIN_STRUCTURE( WSACOMPLETION )
   /*{{|member_: - MEMBER LONG Type }}*/
   _XBST_LONG( Type )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_wsacompletion_ns_parameters> wapist_WSACOMPLETION_NS_PARAMETERS}} Parameters }}*/
   _XBST_WSACOMPLETION_NS_PARAMETERS( Parameters )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BLOB
            | _slug_: wapist_blob
            | class-function: WAPIST_BLOB
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BLOB structure. Defined as BLOB in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_BLOB, BLOB, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BLOB** }}*/
XB_BEGIN_STRUCTURE( BLOB )
   /*{{|member_: - MEMBER ULONG cbSize }}*/
   _XBST_ULONG(  cbSize )
   /*{{|member_: - MEMBER LPBYTE pBlobData }}*/
   _XBST_LPBYTE( pBlobData )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_AFPROTOCOLS
            | _slug_: wapist_afprotocols
            | class-function: WAPIST_AFPROTOCOLS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi AFPROTOCOLS structure. Defined as AFPROTOCOLS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_AFPROTOCOLS, AFPROTOCOLS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  AFPROTOCOLS** }}*/
XB_BEGIN_STRUCTURE( AFPROTOCOLS )
   /*{{|member_: - MEMBER INT iAddressFamily }}*/
   _XBST_INT( iAddressFamily )
   /*{{|member_: - MEMBER INT iProtocol }}*/
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAVERSION
            | _slug_: wapist_wsaversion
            | class-function: WAPIST_WSAVERSION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAVERSION structure. Defined as WSAVERSION in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSAVERSION, WSAVERSION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAVERSION** }}*/
XB_BEGIN_STRUCTURE( WSAVERSION )
   /*{{|member_: - MEMBER DWORD dwVersion }}*/
   _XBST_DWORD  ( dwVersion )
   /*{{|member_: - MEMBER LONG ecHow }}*/
   _XBST_LONG   ( ecHow     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAQUERYSET
            | _slug_: wapist_wsaqueryset
            | class-function: WAPIST_WSAQUERYSET
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAQUERYSET structure. Defined as WSAQUERYSET in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSAQUERYSET, WSAQUERYSET, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAQUERYSET** }}*/
XB_BEGIN_STRUCTURE( WSAQUERYSET )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD     ( dwSize                     )
   /*{{|member_: - MEMBER LPSTR lpszServiceInstanceName }}*/
   _XBST_LPSTR     ( lpszServiceInstanceName    )
   /*{{|member_: - MEMBER POINTER32 lpServiceClassId }}*/
   _XBST_POINTER32 ( lpServiceClassId           )
   /*{{|member_: - MEMBER POINTER32 lpVersion }}*/
   _XBST_POINTER32 ( lpVersion                  )
   /*{{|member_: - MEMBER LPSTR lpszComment }}*/
   _XBST_LPSTR     ( lpszComment                )
   /*{{|member_: - MEMBER DWORD dwNameSpace }}*/
   _XBST_DWORD     ( dwNameSpace                )
   /*{{|member_: - MEMBER POINTER32 lpNSProviderId }}*/
   _XBST_POINTER32 ( lpNSProviderId             )
   /*{{|member_: - MEMBER LPSTR lpszContext }}*/
   _XBST_LPSTR     ( lpszContext                )
   /*{{|member_: - MEMBER DWORD dwNumberOfProtocols }}*/
   _XBST_DWORD     ( dwNumberOfProtocols        )
   /*{{|member_: - MEMBER POINTER32 lpafpProtocols }}*/
   _XBST_POINTER32 ( lpafpProtocols             )
   /*{{|member_: - MEMBER LPSTR lpszQueryString }}*/
   _XBST_LPSTR     ( lpszQueryString            )
   /*{{|member_: - MEMBER DWORD dwNumberOfCsAddrs }}*/
   _XBST_DWORD     ( dwNumberOfCsAddrs          )
   /*{{|member_: - MEMBER POINTER32 lpcsaBuffer }}*/
   _XBST_POINTER32 ( lpcsaBuffer                )
   /*{{|member_: - MEMBER DWORD dwOutputFlags }}*/
   _XBST_DWORD     ( dwOutputFlags              )
   /*{{|member_: - MEMBER POINTER32 lpBlob }}*/
   _XBST_POINTER32 ( lpBlob                     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAQUERYSET2
            | _slug_: wapist_wsaqueryset2
            | class-function: WAPIST_WSAQUERYSET2
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAQUERYSET2 structure. Defined as WSAQUERYSET2 in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSAQUERYSET2, WSAQUERYSET2, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAQUERYSET2** }}*/
XB_BEGIN_STRUCTURE( WSAQUERYSET2 )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD        ( dwSize                   )
   /*{{|member_: - MEMBER LPSTR lpszServiceInstanceName }}*/
   _XBST_LPSTR        ( lpszServiceInstanceName  )
   /*{{|member_: - MEMBER POINTER32 lpVersion }}*/
   _XBST_POINTER32    ( lpVersion                )
   /*{{|member_: - MEMBER LPSTR lpszComment }}*/
   _XBST_LPSTR        ( lpszComment              )
   /*{{|member_: - MEMBER DWORD dwNameSpace }}*/
   _XBST_DWORD        ( dwNameSpace              )
   /*{{|member_: - MEMBER POINTER32 lpNSProviderId }}*/
   _XBST_POINTER32    ( lpNSProviderId           )
   /*{{|member_: - MEMBER LPSTR lpszContext }}*/
   _XBST_LPSTR        ( lpszContext              )
   /*{{|member_: - MEMBER DWORD dwNumberOfProtocols }}*/
   _XBST_DWORD        ( dwNumberOfProtocols      )
   /*{{|member_: - MEMBER POINTER32 lpafpProtocols }}*/
   _XBST_POINTER32    ( lpafpProtocols           )
   /*{{|member_: - MEMBER LPSTR lpszQueryString }}*/
   _XBST_LPSTR        ( lpszQueryString          )
   /*{{|member_: - MEMBER DWORD dwNumberOfCsAddrs }}*/
   _XBST_DWORD        ( dwNumberOfCsAddrs        )
   /*{{|member_: - MEMBER POINTER32 lpcsaBuffer }}*/
   _XBST_POINTER32    ( lpcsaBuffer              )
   /*{{|member_: - MEMBER DWORD dwOutputFlags }}*/
   _XBST_DWORD        ( dwOutputFlags            )
   /*{{|member_: - MEMBER POINTER32 lpBlob }}*/
   _XBST_POINTER32    ( lpBlob                   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSANSCLASSINFO
            | _slug_: wapist_wsansclassinfo
            | class-function: WAPIST_WSANSCLASSINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSANSCLASSINFO structure. Defined as WSANSCLASSINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSANSCLASSINFO, WSANSCLASSINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSANSCLASSINFO** }}*/
XB_BEGIN_STRUCTURE( WSANSCLASSINFO )
   /*{{|member_: - MEMBER LPSTR lpszName }}*/
   _XBST_LPSTR     ( lpszName     )
   /*{{|member_: - MEMBER DWORD dwNameSpace }}*/
   _XBST_DWORD     ( dwNameSpace  )
   /*{{|member_: - MEMBER DWORD dwValueType }}*/
   _XBST_DWORD     ( dwValueType  )
   /*{{|member_: - MEMBER DWORD dwValueSize }}*/
   _XBST_DWORD     ( dwValueSize  )
   /*{{|member_: - MEMBER POINTER32 lpValue }}*/
   _XBST_POINTER32 ( lpValue      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSASERVICECLASSINFO
            | _slug_: wapist_wsaserviceclassinfo
            | class-function: WAPIST_WSASERVICECLASSINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSASERVICECLASSINFO structure. Defined as WSASERVICECLASSINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSASERVICECLASSINFO, WSASERVICECLASSINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSASERVICECLASSINFO** }}*/
XB_BEGIN_STRUCTURE( WSASERVICECLASSINFO )
   /*{{|member_: - MEMBER POINTER32 lpServiceClassId }}*/
   _XBST_POINTER32   ( lpServiceClassId      )
   /*{{|member_: - MEMBER LPSTR lpszServiceClassName }}*/
   _XBST_LPSTR       ( lpszServiceClassName  )
   /*{{|member_: - MEMBER DWORD dwCount }}*/
   _XBST_DWORD       ( dwCount               )
    /*{{|member_: - MEMBER POINTER32 lpClassInfos }}*/
    _XBST_POINTER32  ( lpClassInfos          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSANAMESPACE_INFO
            | _slug_: wapist_wsanamespace_info
            | class-function: WAPIST_WSANAMESPACE_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSANAMESPACE_INFO structure. Defined as WSANAMESPACE_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSANAMESPACE_INFO, WSANAMESPACE_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSANAMESPACE_INFO** }}*/
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_guid> wapist_GUID}} NSProviderId }}*/
   _XBST_GUID      ( NSProviderId     )
   /*{{|member_: - MEMBER DWORD dwNameSpace }}*/
   _XBST_DWORD     ( dwNameSpace      )
   /*{{|member_: - MEMBER BOOL fActive }}*/
   _XBST_BOOL      ( fActive          )
   /*{{|member_: - MEMBER DWORD dwVersion }}*/
   _XBST_DWORD     ( dwVersion        )
   /*{{|member_: - MEMBER LPSTR lpszIdentifier }}*/
   _XBST_LPSTR     ( lpszIdentifier   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSANAMESPACE_INFOEX
            | _slug_: wapist_wsanamespace_infoex
            | class-function: WAPIST_WSANAMESPACE_INFOEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSANAMESPACE_INFOEX structure. Defined as WSANAMESPACE_INFOEX in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_WSANAMESPACE_INFOEX, WSANAMESPACE_INFOEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSANAMESPACE_INFOEX** }}*/
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFOEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_guid> wapist_GUID}} NSProviderId }}*/
   _XBST_GUID   (  NSProviderId     )
   /*{{|member_: - MEMBER DWORD dwNameSpace }}*/
   _XBST_DWORD  (  dwNameSpace      )
   /*{{|member_: - MEMBER BOOL fActive }}*/
   _XBST_BOOL   (  fActive          )
   /*{{|member_: - MEMBER DWORD dwVersion }}*/
   _XBST_DWORD  (  dwVersion        )
   /*{{|member_: - MEMBER LPSTR lpszIdentifier }}*/
   _XBST_LPSTR  (  lpszIdentifier   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_blob> wapist_BLOB}} ProviderSpecific }}*/
   _XBST_BLOB   (  ProviderSpecific )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WSAPOLLFD
            | _slug_: wapist_wsapollfd
            | class-function: WAPIST_WSAPOLLFD
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WSAPOLLFD structure. Defined as WSAPOLLFD in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WSAPOLLFD, WSAPOLLFD, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WSAPOLLFD** }}*/
XB_BEGIN_STRUCTURE( WSAPOLLFD )
   /*{{|member_: - MEMBER SOCKET fd }}*/
   _XBST_SOCKET ( fd      )
   /*{{|member_: - MEMBER SHORT events }}*/
   _XBST_SHORT  ( events  )
   /*{{|member_: - MEMBER SHORT revents }}*/
   _XBST_SHORT  ( revents )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_ADDRINFO
            | _slug_: wapist_addrinfo
            | class-function: WAPIST_ADDRINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinSock ADDRINFOA structure. Defined as ADDRINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
            | _kw_: WAPIST_ADDRINFO, ADDRINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  ADDRINFO** }}*/
XB_BEGIN_STRUCTURE( ADDRINFO )
   /*{{|member_: - MEMBER INT ai_flags }}*/
   _XBST_int   ( ai_flags       )
   /*{{|member_: - MEMBER INT ai_family }}*/
   _XBST_int   ( ai_family      )
   /*{{|member_: - MEMBER INT ai_socktype }}*/
   _XBST_int   ( ai_socktype    )
   /*{{|member_: - MEMBER INT ai_protocol }}*/
   _XBST_int   ( ai_protocol    )
   /*{{|member_: - MEMBER INT ai_addrlen }}*/
   _XBST_int   ( ai_addrlen     )
   /*{{|member_: - MEMBER LPSTR ai_canonname }}*/
   /*{{|member_: - MEMBER DYNSZ cCanonName |desc_: Helper member mapped over ::ai_canonname. }}*/
   _XBST_LPSTR(  ai_canonname   )   pc->GwstBack() ; _XBST_DYNSZ ( cCanonName  )
   /*{{|member_: - MEMBER POINTER32 ai_addr }}*/
   _XBST_POINTER32( ai_addr     )
   /*{{|member_: - MEMBER POINTER32 ai_next }}*/
   _XBST_POINTER32( ai_next     )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OPENFILENAME
            | _slug_: wapist_openfilename
            | class-function: WAPIST_OPENFILENAME
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi OPENFILENAMEA structure. Defined as OPENFILENAME in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
            | _kw_: WAPIST_OPENFILENAME, OPENFILENAME, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OPENFILENAME** }}*/
XB_BEGIN_STRUCTURE( OPENFILENAME )
   /*{{|member_: - MEMBER DWORD lStructSize }}*/
   _XBST_DWORD       (   lStructSize       )
   /*{{|member_: - MEMBER HWND hwndOwner }}*/
   _XBST_HWND        (   hwndOwner         )
   /*{{|member_: - MEMBER HINSTANCE hInstance }}*/
   _XBST_HINSTANCE   (   hInstance         )
   /*{{|member_: - MEMBER LPSTR lpstrFilter }}*/
   _XBST_LPSTR       (   lpstrFilter       )
   /*{{|member_: - MEMBER LPSTR lpstrCustomFilter }}*/
   _XBST_LPSTR       (   lpstrCustomFilter )
   /*{{|member_: - MEMBER DWORD nMaxCustFilter }}*/
   _XBST_DWORD       (   nMaxCustFilter    )
   /*{{|member_: - MEMBER DWORD nFilterIndex }}*/
   _XBST_DWORD       (   nFilterIndex      )
   /*{{|member_: - MEMBER LPSTR lpstrFile }}*/
   _XBST_LPSTR       (   lpstrFile         )
   /*{{|member_: - MEMBER DWORD nMaxFile }}*/
   _XBST_DWORD       (   nMaxFile          )
   /*{{|member_: - MEMBER LPSTR lpstrFileTitle }}*/
   _XBST_LPSTR       (   lpstrFileTitle    )
   /*{{|member_: - MEMBER DWORD nMaxFileTitle }}*/
   _XBST_DWORD       (   nMaxFileTitle     )
   /*{{|member_: - MEMBER LPSTR lpstrInitialDir }}*/
   _XBST_LPSTR       (   lpstrInitialDir   )
   /*{{|member_: - MEMBER LPSTR lpstrTitle }}*/
   _XBST_LPSTR       (   lpstrTitle        )
   /*{{|member_: - MEMBER DWORD Flags }}*/
   _XBST_DWORD       (   Flags             )
   /*{{|member_: - MEMBER WORD nFileOffset }}*/
   _XBST_WORD        (   nFileOffset       )
   /*{{|member_: - MEMBER WORD nFileExtension }}*/
   _XBST_WORD        (   nFileExtension    )
   /*{{|member_: - MEMBER LPSTR lpstrDefExt }}*/
   _XBST_LPSTR       (   lpstrDefExt       )
   /*{{|member_: - MEMBER LPARAM lCustData }}*/
   _XBST_LPARAM      (   lCustData         )
   /*{{|member_: - MEMBER POINTER32 lpfnHook }}*/
   _XBST_POINTER32   (   lpfnHook          )
   /*{{|member_: - MEMBER LPSTR lpTemplateName }}*/
   _XBST_LPSTR       (   lpTemplateName    )
   /*{{|member_: - MEMBER POINTER32 pvReserved }}*/
   _XBST_POINTER32   (   pvReserved        )
   /*{{|member_: - MEMBER DWORD dwReserved }}*/
   _XBST_DWORD       (   dwReserved        )
   /*{{|member_: - MEMBER DWORD FlagsEx }}*/
   _XBST_DWORD       (   FlagsEx           )
   wsprintf(pc->m_szPrintfBuffer,"{|s| %i }",OPENFILENAME_SIZE_VERSION_400 );
   /*{{|class-property_: - CLASS PROPERTY _size_400_
            | type: Numeric
            | desc_: Read-only. The OPENFILENAME_SIZE_VERSION_400 byte size, for dialogs with the pre-Windows
              2000 layout.
   }}*/
   pc->ROClassPropertyCB("_size_400_",pc->m_szPrintfBuffer);
   wsprintf(pc->m_szPrintfBuffer,"{|s| %i }",sizeof( OPENFILENAME) );
   /*{{|class-property_: - CLASS PROPERTY _size_500_
            | type: Numeric
            | desc_: Read-only. sizeof(OPENFILENAME) as compiled into ot4xb: the full structure size with the
              FlagsEx extension.
   }}*/
   pc->ROClassPropertyCB("_size_500_", pc->m_szPrintfBuffer );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
// HID
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWHID
            | _slug_: wapist_rawhid
            | class-function: WAPIST_RAWHID
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWHID structure. Defined as RAWHID in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RAWHID, RAWHID, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWHID** }}*/
XB_BEGIN_STRUCTURE( RAWHID )
   /*{{|member_: - MEMBER DWORD dwSizeHid }}*/
   _XBST_DWORD ( dwSizeHid  )
   /*{{|member_: - MEMBER DWORD dwCount }}*/
   _XBST_DWORD ( dwCount    )
   /*{{|member_: - MEMBER BYTE bRawData }}*/
   _XBST_BYTE  ( bRawData   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWINPUT_DATA_UNION
            | _slug_: wapist_rawinput_data_union
            | class-function: WAPIST_RAWINPUT_DATA_UNION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Auxiliary wrapper for the RAWINPUT data union.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawinput
            | _kw_: WAPIST_RAWINPUT_DATA_UNION, RAWINPUT_DATA_UNION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWINPUT_DATA_UNION** }}*/
XB_BEGIN_STRUCTURE( RAWINPUT_DATA_UNION )
  pc->GwstBeginUnion();
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rawmouse> wapist_RAWMOUSE}} mouse }}*/
   _XBST_RAWMOUSE    ( mouse     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rawkeyboard> wapist_RAWKEYBOARD}} keyboard }}*/
   _XBST_RAWKEYBOARD ( keyboard  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rawhid> wapist_RAWHID}} hid }}*/
   _XBST_RAWHID      ( hid       )
  pc->GwstEndUnion();
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWINPUT
            | _slug_: wapist_rawinput
            | class-function: WAPIST_RAWINPUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWINPUT structure. Defined as RAWINPUT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RAWINPUT, RAWINPUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWINPUT** }}*/
XB_BEGIN_STRUCTURE( RAWINPUT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rawinputheader> wapist_RAWINPUTHEADER}} header }}*/
   _XBST_RAWINPUTHEADER( header )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rawinput_data_union> wapist_RAWINPUT_DATA_UNION}} data }}*/
   _XBST_RAWINPUT_DATA_UNION( data )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWINPUTDEVICE
            | _slug_: wapist_rawinputdevice
            | class-function: WAPIST_RAWINPUTDEVICE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWINPUTDEVICE structure. Defined as RAWINPUTDEVICE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RAWINPUTDEVICE, RAWINPUTDEVICE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWINPUTDEVICE** }}*/
XB_BEGIN_STRUCTURE( RAWINPUTDEVICE)
   /*{{|member_: - MEMBER USHORT usUsagePage }}*/
   _XBST_USHORT ( usUsagePage  )
   /*{{|member_: - MEMBER USHORT usUsage }}*/
   _XBST_USHORT ( usUsage      )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD  ( dwFlags      )
   /*{{|member_: - MEMBER HWND hwndTarget }}*/
   _XBST_HWND   ( hwndTarget   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWINPUTDEVICELIST
            | _slug_: wapist_rawinputdevicelist
            | class-function: WAPIST_RAWINPUTDEVICELIST
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWINPUTDEVICELIST structure. Defined as RAWINPUTDEVICELIST in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RAWINPUTDEVICELIST, RAWINPUTDEVICELIST, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWINPUTDEVICELIST** }}*/
XB_BEGIN_STRUCTURE( RAWINPUTDEVICELIST )
   /*{{|member_: - MEMBER HANDLE hDevice }}*/
   _XBST_HANDLE ( hDevice )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD  ( dwType  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWINPUTHEADER
            | _slug_: wapist_rawinputheader
            | class-function: WAPIST_RAWINPUTHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWINPUTHEADER structure. Defined as RAWINPUTHEADER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RAWINPUTHEADER, RAWINPUTHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWINPUTHEADER** }}*/
XB_BEGIN_STRUCTURE( RAWINPUTHEADER )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD  ( dwType  )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD  ( dwSize  )
   /*{{|member_: - MEMBER HANDLE hDevice }}*/
   _XBST_HANDLE ( hDevice )
   /*{{|member_: - MEMBER WPARAM wParam }}*/
   _XBST_WPARAM ( wParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWKEYBOARD
            | _slug_: wapist_rawkeyboard
            | class-function: WAPIST_RAWKEYBOARD
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWKEYBOARD structure. Defined as RAWKEYBOARD in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_RAWKEYBOARD, RAWKEYBOARD, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWKEYBOARD** }}*/
XB_BEGIN_STRUCTURE( RAWKEYBOARD )
   /*{{|member_: - MEMBER USHORT MakeCode }}*/
   _XBST_USHORT ( MakeCode         )
   /*{{|member_: - MEMBER USHORT Flags }}*/
   _XBST_USHORT ( Flags            )
   /*{{|member_: - MEMBER USHORT Reserved }}*/
   _XBST_USHORT ( Reserved         )
   /*{{|member_: - MEMBER USHORT VKey }}*/
   _XBST_USHORT ( VKey             )
   /*{{|member_: - MEMBER UINT Message }}*/
   _XBST_UINT   ( Message          )
   /*{{|member_: - MEMBER ULONG ExtraInformation }}*/
   _XBST_ULONG  ( ExtraInformation )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RAWMOUSE
            | _slug_: wapist_rawmouse
            | class-function: WAPIST_RAWMOUSE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RAWMOUSE structure. Defined as RAWMOUSE in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
            | _kw_: WAPIST_RAWMOUSE, RAWMOUSE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RAWMOUSE** }}*/
XB_BEGIN_STRUCTURE( RAWMOUSE )
   /*{{|member_: - MEMBER USHORT usFlags }}*/
   _XBST_USHORT    ( usFlags )
   // union
   /*{{|member_: - MEMBER ULONG ulButtons }}*/
   _XBST_ULONG    ( ulButtons )
   pc->GwstSetOffset(2);
   /*{{|member_: - MEMBER USHORT usButtonFlags }}*/
   _XBST_USHORT ( usButtonFlags )
   /*{{|member_: - MEMBER USHORT usButtonData }}*/
   _XBST_USHORT ( usButtonData  )
   // ---
   /*{{|member_: - MEMBER ULONG ulRawButtons }}*/
   _XBST_ULONG  ( ulRawButtons       )
   /*{{|member_: - MEMBER LONG lLastX }}*/
   _XBST_LONG   ( lLastX             )
   /*{{|member_: - MEMBER LONG lLastY }}*/
   _XBST_LONG   ( lLastY             )
   /*{{|member_: - MEMBER ULONG ulExtraInformation }}*/
   _XBST_ULONG  ( ulExtraInformation )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RID_DEVICE_INFO
            | _slug_: wapist_rid_device_info
            | class-function: WAPIST_RID_DEVICE_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RID_DEVICE_INFO structure. Defined as RID_DEVICE_INFO in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rid_device_info
            | _kw_: WAPIST_RID_DEVICE_INFO, RID_DEVICE_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RID_DEVICE_INFO** }}*/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD    ( cbSize  )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD    ( dwType  )
  pc->GwstBeginUnion();
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rid_device_info_mouse> wapist_RID_DEVICE_INFO_MOUSE}} mouse }}*/
   _XBST_RID_DEVICE_INFO_MOUSE     ( mouse     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rid_device_info_keyboard> wapist_RID_DEVICE_INFO_KEYBOARD}} keyboard }}*/
   _XBST_RID_DEVICE_INFO_KEYBOARD  ( keyboard  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rid_device_info_hid> wapist_RID_DEVICE_INFO_HID}} hid }}*/
   _XBST_RID_DEVICE_INFO_HID       ( hid       )
  pc->GwstEndUnion();
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RID_DEVICE_INFO_HID
            | _slug_: wapist_rid_device_info_hid
            | class-function: WAPIST_RID_DEVICE_INFO_HID
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RID_DEVICE_INFO_HID structure. Defined as RID_DEVICE_INFO_HID in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RID_DEVICE_INFO_HID, RID_DEVICE_INFO_HID, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RID_DEVICE_INFO_HID** }}*/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_HID )
   /*{{|member_: - MEMBER DWORD dwVendorId }}*/
   _XBST_DWORD   ( dwVendorId       )
   /*{{|member_: - MEMBER DWORD dwProductId }}*/
   _XBST_DWORD   ( dwProductId      )
   /*{{|member_: - MEMBER DWORD dwVersionNumber }}*/
   _XBST_DWORD   ( dwVersionNumber  )
   /*{{|member_: - MEMBER USHORT usUsagePage }}*/
   _XBST_USHORT  ( usUsagePage      )
   /*{{|member_: - MEMBER USHORT usUsage }}*/
   _XBST_USHORT  ( usUsage          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RID_DEVICE_INFO_KEYBOARD
            | _slug_: wapist_rid_device_info_keyboard
            | class-function: WAPIST_RID_DEVICE_INFO_KEYBOARD
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RID_DEVICE_INFO_KEYBOARD structure. Defined as RID_DEVICE_INFO_KEYBOARD in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RID_DEVICE_INFO_KEYBOARD, RID_DEVICE_INFO_KEYBOARD, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RID_DEVICE_INFO_KEYBOARD** }}*/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_KEYBOARD )
   /*{{|member_: - MEMBER DWORD dwType }}*/
   _XBST_DWORD ( dwType                 )
   /*{{|member_: - MEMBER DWORD dwSubType }}*/
   _XBST_DWORD ( dwSubType              )
   /*{{|member_: - MEMBER DWORD dwKeyboardMode }}*/
   _XBST_DWORD ( dwKeyboardMode         )
   /*{{|member_: - MEMBER DWORD dwNumberOfFunctionKeys }}*/
   _XBST_DWORD ( dwNumberOfFunctionKeys )
   /*{{|member_: - MEMBER DWORD dwNumberOfIndicators }}*/
   _XBST_DWORD ( dwNumberOfIndicators   )
   /*{{|member_: - MEMBER DWORD dwNumberOfKeysTotal }}*/
   _XBST_DWORD ( dwNumberOfKeysTotal    )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_RID_DEVICE_INFO_MOUSE
            | _slug_: wapist_rid_device_info_mouse
            | class-function: WAPIST_RID_DEVICE_INFO_MOUSE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi RID_DEVICE_INFO_MOUSE structure. Defined as RID_DEVICE_INFO_MOUSE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_RID_DEVICE_INFO_MOUSE, RID_DEVICE_INFO_MOUSE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  RID_DEVICE_INFO_MOUSE** }}*/
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_MOUSE )
   /*{{|member_: - MEMBER DWORD dwId }}*/
   _XBST_DWORD ( dwId                )
   /*{{|member_: - MEMBER DWORD dwNumberOfButtons }}*/
   _XBST_DWORD ( dwNumberOfButtons   )
   /*{{|member_: - MEMBER DWORD dwSampleRate }}*/
   _XBST_DWORD ( dwSampleRate        )
   /*{{|member_: - MEMBER BOOL fHasHorizontalWheel }}*/
   _XBST_BOOL  ( fHasHorizontalWheel )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
// IPHLPR
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IP_ADDR_STRING
            | _slug_: wapist_ip_addr_string
            | class-function: WAPIST_IP_ADDR_STRING
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IP_ADDR_STRING structure. Defined as IP_ADDR_STRING in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_IP_ADDR_STRING, IP_ADDR_STRING, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IP_ADDR_STRING** }}*/
XB_BEGIN_STRUCTURE( IP_ADDR_STRING )
   /*{{|member_: - MEMBER POINTER32 _Next }}*/
   _XBST_POINTER32    ( _Next )
   /*{{|member_: - MEMBER BINSTR IpAddress }}*/
   _XBST_BINSTR       ( IpAddress , 16 )
   /*{{|member_: - MEMBER BINSTR IpMask }}*/
   _XBST_BINSTR       ( IpMask    , 16 )
   /*{{|member_: - MEMBER DWORD Context }}*/
   _XBST_DWORD        ( Context )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IP_ADAPTER_INFO
            | _slug_: wapist_ip_adapter_info
            | class-function: WAPIST_IP_ADAPTER_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IP_ADAPTER_INFO structure. Defined as IP_ADAPTER_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_IP_ADAPTER_INFO, IP_ADAPTER_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IP_ADAPTER_INFO** }}*/
XB_BEGIN_STRUCTURE( IP_ADAPTER_INFO )
   /*{{|member_: - MEMBER POINTER32 _Next }}*/
   _XBST_POINTER32           ( _Next                 )
   /*{{|member_: - MEMBER DWORD ComboIndex }}*/
   _XBST_DWORD               ( ComboIndex            )
   /*{{|member_: - MEMBER SZSTR AdapterName }}*/
   _XBST_SZSTR               ( AdapterName , 260     )
   /*{{|member_: - MEMBER SZSTR Description }}*/
   _XBST_SZSTR               ( Description , 132     )
   /*{{|member_: - MEMBER UINT AddressLength }}*/
   _XBST_UINT                ( AddressLength         )
   /*{{|member_: - MEMBER BINSTR Address }}*/
   _XBST_BINSTR              ( Address ,  8          )
   /*{{|member_: - MEMBER DWORD Index }}*/
   _XBST_DWORD               ( Index                 )
   /*{{|member_: - MEMBER UINT Type }}*/
   _XBST_UINT                ( Type                  )
   /*{{|member_: - MEMBER BOOL DhcpEnabled }}*/
   _XBST_BOOL                ( DhcpEnabled           )
   /*{{|member_: - MEMBER POINTER32 CurrentIpAddress }}*/
   _XBST_POINTER32           ( CurrentIpAddress      )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} IpAddressList }}*/
   _XBST_IP_ADDR_STRING      ( IpAddressList         )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} GatewayList }}*/
   _XBST_IP_ADDR_STRING      ( GatewayList           )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} DhcpServer }}*/
   _XBST_IP_ADDR_STRING      ( DhcpServer            )
   /*{{|member_: - MEMBER BOOL HaveWins }}*/
   _XBST_BOOL                ( HaveWins              )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} PrimaryWinsServer }}*/
   _XBST_IP_ADDR_STRING      ( PrimaryWinsServer     )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} SecondaryWinsServer }}*/
   _XBST_IP_ADDR_STRING      ( SecondaryWinsServer   )
   /*{{|member_: - MEMBER DWORD LeaseObtained }}*/
   _XBST_DWORD               ( LeaseObtained         )
   /*{{|member_: - MEMBER DWORD LeaseExpires }}*/
   _XBST_DWORD               ( LeaseExpires          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_IP_PER_ADAPTER_INFO
            | _slug_: wapist_ip_per_adapter_info
            | class-function: WAPIST_IP_PER_ADAPTER_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi IP_PER_ADAPTER_INFO structure. Defined as IP_PER_ADAPTER_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_IP_PER_ADAPTER_INFO, IP_PER_ADAPTER_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  IP_PER_ADAPTER_INFO** }}*/
XB_BEGIN_STRUCTURE( IP_PER_ADAPTER_INFO )
   /*{{|member_: - MEMBER UINT AutoconfigEnabled }}*/
   _XBST_UINT             ( AutoconfigEnabled  )
   /*{{|member_: - MEMBER UINT AutoconfigActive }}*/
   _XBST_UINT             ( AutoconfigActive   )
   /*{{|member_: - MEMBER POINTER32 CurrentDnsServer }}*/
   _XBST_POINTER32        ( CurrentDnsServer   )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_ip_addr_string> wapist_IP_ADDR_STRING}} DnsServerList }}*/
   _XBST_IP_ADDR_STRING   ( DnsServerList      )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OVERLAPPED
            | _slug_: wapist_overlapped
            | class-function: WAPIST_OVERLAPPED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi OVERLAPPED structure. Defined as OVERLAPPED in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-overlapped
            | _kw_: WAPIST_OVERLAPPED, OVERLAPPED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OVERLAPPED** }}*/
XB_BEGIN_STRUCTURE( OVERLAPPED )
   /*{{|member_: - MEMBER ULONG_PTR Internal }}*/
   _XBST_ULONG_PTR ( Internal      )
   /*{{|member_: - MEMBER ULONG_PTR InternalHigh }}*/
   _XBST_ULONG_PTR ( InternalHigh  )
   /*{{|member_: - MEMBER DWORD Offset }}*/
   _XBST_DWORD     ( Offset        )
   /*{{|member_: - MEMBER DWORD OffsetHigh }}*/
   _XBST_DWORD     ( OffsetHigh    )
   pc->GwstSetOffset( 8  );
   /*{{|member_: - MEMBER PVOID Pointer }}*/
   _XBST_PVOID( Pointer       )
   pc->GwstSetOffset(16  );
   /*{{|member_: - MEMBER HANDLE hEvent }}*/
   _XBST_HANDLE    ( hEvent        )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SYSTEM_INFO
            | _slug_: wapist_system_info
            | class-function: WAPIST_SYSTEM_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SYSTEM_INFO structure. Defined as SYSTEM_INFO in ot4xb_wapist_map.ch.
            | note: The structure is automatically initialized with the current system information when instantiated.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info
            | _kw_: WAPIST_SYSTEM_INFO, SYSTEM_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SYSTEM_INFO** }}*/
XB_BEGIN_STRUCTURE( SYSTEM_INFO )
   /*{{|member_: - MEMBER DWORD dwOemId }}*/
   _XBST_DWORD( dwOemId )
   pc->GwstSetOffset( 0 );
   /*{{|member_: - MEMBER WORD wProcessorArchitecture }}*/
   _XBST_WORD    ( wProcessorArchitecture      )
   /*{{|member_: - MEMBER WORD wReserved }}*/
   _XBST_WORD    ( wReserved                   )
   /*{{|member_: - MEMBER DWORD dwPageSize }}*/
   _XBST_DWORD   ( dwPageSize                  )
   /*{{|member_: - MEMBER LPVOID lpMinimumApplicationAddress }}*/
   _XBST_LPVOID  ( lpMinimumApplicationAddress )
   /*{{|member_: - MEMBER LPVOID lpMaximumApplicationAddress }}*/
   _XBST_LPVOID  ( lpMaximumApplicationAddress )
   /*{{|member_: - MEMBER DWORD dwActiveProcessorMask }}*/
   _XBST_DWORD   ( dwActiveProcessorMask       )
   /*{{|member_: - MEMBER DWORD dwNumberOfProcessors }}*/
   _XBST_DWORD   ( dwNumberOfProcessors        )
   /*{{|member_: - MEMBER DWORD dwProcessorType }}*/
   _XBST_DWORD   ( dwProcessorType             )
   /*{{|member_: - MEMBER DWORD dwAllocationGranularity }}*/
   _XBST_DWORD   ( dwAllocationGranularity     )
   /*{{|member_: - MEMBER WORD wProcessorLevel }}*/
   _XBST_WORD    ( wProcessorLevel             )
   /*{{|member_: - MEMBER WORD wProcessorRevision }}*/
   _XBST_WORD    ( wProcessorRevision          )
   pc->GwstSetOffset(sizeof( SYSTEM_INFO)  );
   DWORD dwfp = (DWORD) GetProcAddress(GetModuleHandle("kernel32"), "GetNativeSystemInfo" );
   if(! dwfp) {dwfp = (DWORD) GetProcAddress(GetModuleHandle("kernel32"), "GetSystemInfo" );}
   pc->Method_cbbs( "init", "{|s,p1,p2| s:_gwst_(p1,p2),nFpCall(%i,s),s }" , dwfp );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// WINNT STRUCTRURES
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OSVERSIONINFOEX
            | _slug_: wapist_osversioninfoex
            | class-function: WAPIST_OSVERSIONINFOEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi OSVERSIONINFOEXA structure.
            | note: The structure is automatically initialized with the current operating system version information
              when instantiated.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoexa
            | _kw_: WAPIST_OSVERSIONINFOEX, OSVERSIONINFOEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OSVERSIONINFOEX** }}*/
XB_BEGIN_STRUCTURE( OSVERSIONINFOEX )
   /*{{|member_: - MEMBER DWORD dwOSVersionInfoSize }}*/
   _XBST_DWORD ( dwOSVersionInfoSize )
   /*{{|member_: - MEMBER DWORD dwMajorVersion }}*/
   _XBST_DWORD ( dwMajorVersion )
   /*{{|member_: - MEMBER DWORD dwMinorVersion }}*/
   _XBST_DWORD ( dwMinorVersion )
   /*{{|member_: - MEMBER DWORD dwBuildNumber }}*/
   _XBST_DWORD ( dwBuildNumber )
   /*{{|member_: - MEMBER DWORD dwPlatformId }}*/
   _XBST_DWORD ( dwPlatformId )
   /*{{|member_: - MEMBER SZSTR szCSDVersion }}*/
   _XBST_SZSTR ( szCSDVersion,128)
   /*{{|member_: - MEMBER WORD wServicePackMajor }}*/
   _XBST_WORD  ( wServicePackMajor )
   /*{{|member_: - MEMBER WORD wServicePackMinor }}*/
   _XBST_WORD  ( wServicePackMinor )
   /*{{|member_: - MEMBER WORD wSuiteMask }}*/
   _XBST_WORD  ( wSuiteMask )
   /*{{|member_: - MEMBER BYTE wProductType }}*/
   _XBST_BYTE  ( wProductType )
   /*{{|member_: - MEMBER BYTE wReserved }}*/
   _XBST_BYTE  ( wReserved )
   pc->Method_cbbs( "init", "{|s,p1,p2| s:_gwst_(p1,p2),nFpCall(%i,s),s }" , ot4xb_fill_OSVERSIONINFOEX );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// TOOLHELP STRUCTURES
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MODULEENTRY32
            | _slug_: wapist_moduleentry32
            | class-function: WAPIST_MODULEENTRY32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MODULEENTRY32 structure. Defined as MODULEENTRY32 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-moduleentry32
            | _kw_: WAPIST_MODULEENTRY32, MODULEENTRY32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MODULEENTRY32** }}*/
XB_BEGIN_STRUCTURE( MODULEENTRY32 )
   /*{{|method_: - `METHOD _reset_()`
            | return: Self
            | desc_: Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
   }}*/
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize           )
   /*{{|member_: - MEMBER DWORD th32ModuleID }}*/
   _XBST_DWORD ( th32ModuleID     )
   /*{{|member_: - MEMBER DWORD th32ProcessID }}*/
   _XBST_DWORD ( th32ProcessID    )
   /*{{|member_: - MEMBER DWORD GlblcntUsage }}*/
   _XBST_DWORD ( GlblcntUsage     )
   /*{{|member_: - MEMBER DWORD ProccntUsage }}*/
   _XBST_DWORD ( ProccntUsage     )
   /*{{|member_: - MEMBER POINTER32 modBaseAddr }}*/
   _XBST_POINTER32 ( modBaseAddr  )
   /*{{|member_: - MEMBER DWORD modBaseSize }}*/
   _XBST_DWORD ( modBaseSize      )
   /*{{|member_: - MEMBER HANDLE hModule }}*/
   _XBST_HANDLE( hModule          )
   /*{{|member_: - MEMBER SZSTR szModule }}*/
   _XBST_SZSTR ( szModule  , 256  )
   /*{{|member_: - MEMBER SZSTR szExePath }}*/
   _XBST_SZSTR ( szExePath , 260  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PROCESSENTRY32
            | _slug_: wapist_processentry32
            | class-function: WAPIST_PROCESSENTRY32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PROCESSENTRY32 structure. Defined as PROCESSENTRY32 in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32
            | _kw_: WAPIST_PROCESSENTRY32, PROCESSENTRY32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PROCESSENTRY32** }}*/
XB_BEGIN_STRUCTURE( PROCESSENTRY32 )
   /*{{|method_: - `METHOD _reset_()`
            | return: Self
            | desc_: Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
   }}*/
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize                )
   /*{{|member_: - MEMBER DWORD cntUsage }}*/
   _XBST_DWORD ( cntUsage              )
   /*{{|member_: - MEMBER DWORD th32ProcessID }}*/
   _XBST_DWORD ( th32ProcessID         )
   /*{{|member_: - MEMBER DWORD th32DefaultHeapID }}*/
   _XBST_DWORD ( th32DefaultHeapID     )
   /*{{|member_: - MEMBER DWORD th32ModuleID }}*/
   _XBST_DWORD ( th32ModuleID          )
   /*{{|member_: - MEMBER DWORD cntThreads }}*/
   _XBST_DWORD ( cntThreads            )
   /*{{|member_: - MEMBER DWORD th32ParentProcessID }}*/
   _XBST_DWORD ( th32ParentProcessID   )
   /*{{|member_: - MEMBER LONG pcPriClassBase }}*/
   _XBST_LONG  ( pcPriClassBase        )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags               )
   /*{{|member_: - MEMBER SZSTR szExeFile }}*/
   _XBST_SZSTR ( szExeFile , 260       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_THREADENTRY32
            | _slug_: wapist_threadentry32
            | class-function: WAPIST_THREADENTRY32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi THREADENTRY32 structure. Defined as THREADENTRY32 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-threadentry32
            | _kw_: WAPIST_THREADENTRY32, THREADENTRY32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  THREADENTRY32** }}*/
XB_BEGIN_STRUCTURE( THREADENTRY32 )
   /*{{|method_: - `METHOD _reset_()`
            | return: Self
            | desc_: Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
   }}*/
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize               )
   /*{{|member_: - MEMBER DWORD cntUsage }}*/
   _XBST_DWORD ( cntUsage             )
   /*{{|member_: - MEMBER DWORD th32ThreadID }}*/
   _XBST_DWORD ( th32ThreadID         )
   /*{{|member_: - MEMBER DWORD th32OwnerProcessID }}*/
   _XBST_DWORD ( th32OwnerProcessID   )
   /*{{|member_: - MEMBER LONG tpBasePri }}*/
   _XBST_LONG  ( tpBasePri            )
   /*{{|member_: - MEMBER LONG tpDeltaPri }}*/
   _XBST_LONG  ( tpDeltaPri           )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags              )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HEAPENTRY32
            | _slug_: wapist_heapentry32
            | class-function: WAPIST_HEAPENTRY32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HEAPENTRY32 structure. Defined as HEAPENTRY32 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-heapentry32
            | _kw_: WAPIST_HEAPENTRY32, HEAPENTRY32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HEAPENTRY32** }}*/
XB_BEGIN_STRUCTURE( HEAPENTRY32 )
   /*{{|method_: - `METHOD _reset_()`
            | return: Self
            | desc_: Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
   }}*/
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize           )
   /*{{|member_: - MEMBER HANDLE hHandle }}*/
   _XBST_HANDLE( hHandle          )
   /*{{|member_: - MEMBER DWORD dwAddress }}*/
   _XBST_DWORD ( dwAddress        )
   /*{{|member_: - MEMBER DWORD dwBlockSize }}*/
   _XBST_DWORD ( dwBlockSize      )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags          )
   /*{{|member_: - MEMBER DWORD dwLockCount }}*/
   _XBST_DWORD ( dwLockCount      )
   /*{{|member_: - MEMBER DWORD dwResvd }}*/
   _XBST_DWORD ( dwResvd          )
   /*{{|member_: - MEMBER DWORD th32ProcessID }}*/
   _XBST_DWORD ( th32ProcessID    )
   /*{{|member_: - MEMBER DWORD th32HeapID }}*/
   _XBST_DWORD ( th32HeapID       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HEAPLIST32
            | _slug_: wapist_heaplist32
            | class-function: WAPIST_HEAPLIST32
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HEAPLIST32 structure. Defined as HEAPLIST32 in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/ns-tlhelp32-heaplist32
            | _kw_: WAPIST_HEAPLIST32, HEAPLIST32, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HEAPLIST32** }}*/
XB_BEGIN_STRUCTURE( HEAPLIST32 )
   /*{{|method_: - `METHOD _reset_()`
            | return: Self
            | desc_: Clears the structure, sets dwSize to ::_sizeof_(), and returns Self.
   }}*/
   pc->MethodCB("_reset_" , "{|s| s:_zeromemory_() , s:dwSize := s:_sizeof_() , s }");
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize        )
   /*{{|member_: - MEMBER DWORD th32ProcessID }}*/
   _XBST_DWORD ( th32ProcessID )
   /*{{|member_: - MEMBER DWORD th32HeapID }}*/
   _XBST_DWORD ( th32HeapID    )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags       )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVBKIMAGE
            | _slug_: wapist_lvbkimage
            | class-function: WAPIST_LVBKIMAGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVBKIMAGE structure. Defined as LVBKIMAGE in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvbkimagea
            | _kw_: WAPIST_LVBKIMAGE, LVBKIMAGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVBKIMAGE** }}*/
XB_BEGIN_STRUCTURE( LVBKIMAGE )
   /*{{|member_: - MEMBER ULONG ulFlags }}*/
   _XBST_ULONG( ulFlags )
   /*{{|member_: - MEMBER HBITMAP hbm }}*/
   _XBST_HBITMAP( hbm )
   /*{{|member_: - MEMBER LPSTR pszImage }}*/
   /*{{|member_: - MEMBER DYNSZ cImage |desc_: Helper member mapped over ::pszImage. }}*/
   _XBST_LPSTR_DYNSZ( pszImage , cImage )
   /*{{|member_: - MEMBER UINT cchImageMax }}*/
   _XBST_UINT( cchImageMax )
   /*{{|member_: - MEMBER INT xOffsetPercent }}*/
   _XBST_int( xOffsetPercent )
   /*{{|member_: - MEMBER INT yOffsetPercent }}*/
   _XBST_int( yOffsetPercent )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVCOLUMN
            | _slug_: wapist_lvcolumn
            | class-function: WAPIST_LVCOLUMN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVCOLUMN structure. Defined as LVCOLUMN in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvcolumna
            | _kw_: WAPIST_LVCOLUMN, LVCOLUMN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVCOLUMN** }}*/
XB_BEGIN_STRUCTURE( LVCOLUMN )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER INT fmt }}*/
   _XBST_int( fmt )
   /*{{|member_: - MEMBER INT cx }}*/
   _XBST_int( cx )
/*{{|member_: - MEMBER LPSTR pszText }}*/
/*{{|member_: - MEMBER DYNSZ cText |desc_: Helper member mapped over ::pszText. }}*/
_XBST_LPSTR_DYNSZ( pszText , cText )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int( cchTextMax )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int( iImage )
   /*{{|member_: - MEMBER INT iOrder }}*/
   _XBST_int( iOrder )
   /*{{|member_: - MEMBER INT cxMin }}*/
   _XBST_int( cxMin )
   /*{{|member_: - MEMBER INT cxDefault }}*/
   _XBST_int( cxDefault )
   /*{{|member_: - MEMBER INT cxIdeal }}*/
   _XBST_int( cxIdeal )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVFINDINFO
            | _slug_: wapist_lvfindinfo
            | class-function: WAPIST_LVFINDINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVFINDINFO structure. Defined as LVFINDINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvfindinfoa
            | _kw_: WAPIST_LVFINDINFO, LVFINDINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVFINDINFO** }}*/
XB_BEGIN_STRUCTURE( LVFINDINFO )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT( flags )
/*{{|member_: - MEMBER LPSTR psz }}*/
/*{{|member_: - MEMBER DYNSZ cStr |desc_: Helper member mapped over ::psz. }}*/
_XBST_LPSTR_DYNSZ( psz , cStr )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM( lParam )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT( pt )
   /*{{|member_: - MEMBER UINT vkDirection }}*/
   _XBST_UINT( vkDirection )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVFOOTERINFO
            | _slug_: wapist_lvfooterinfo
            | class-function: WAPIST_LVFOOTERINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVFOOTERINFO structure. Defined as LVFOOTERINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVFOOTERINFO, LVFOOTERINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVFOOTERINFO** }}*/
XB_BEGIN_STRUCTURE(LVFOOTERINFO )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER POINTER32 pszText }}*/
   _XBST_POINTER32( pszText )  // LPWSTR
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int( cchTextMax )
   /*{{|member_: - MEMBER UINT cItems }}*/
   _XBST_UINT( cItems )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVFOOTERITEM
            | _slug_: wapist_lvfooteritem
            | class-function: WAPIST_LVFOOTERITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVFOOTERITEM structure. Defined as LVFOOTERITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVFOOTERITEM, LVFOOTERITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVFOOTERITEM** }}*/
XB_BEGIN_STRUCTURE(LVFOOTERITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER POINTER32 pszText }}*/
   _XBST_POINTER32( pszText ) // LPWSTR
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int( cchTextMax )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT( state )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT( stateMask )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVGROUP
            | _slug_: wapist_lvgroup
            | class-function: WAPIST_LVGROUP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVGROUP structure. Defined as LVGROUP in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVGROUP, LVGROUP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVGROUP** }}*/
XB_BEGIN_STRUCTURE( LVGROUP )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT   ( cbSize )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT   ( mask )
   /*{{|member_: - MEMBER POINTER32 pszHeader }}*/
   _XBST_POINTER32 ( pszHeader ) // LPWSTR
   /*{{|member_: - MEMBER INT cchHeader }}*/
   _XBST_int    ( cchHeader )
   /*{{|member_: - MEMBER POINTER32 pszFooter }}*/
   _XBST_POINTER32( pszFooter ) // LPWSTR
   /*{{|member_: - MEMBER INT cchFooter }}*/
   _XBST_int    ( cchFooter )
   /*{{|member_: - MEMBER INT iGroupId }}*/
   _XBST_int    ( iGroupId )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT   ( stateMask )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT   ( state )
   /*{{|member_: - MEMBER UINT uAlign }}*/
   _XBST_UINT   ( uAlign )
   /*{{|member_: - MEMBER POINTER32 pszSubtitle }}*/
   _XBST_POINTER32 ( pszSubtitle ) // LPWSTR
   /*{{|member_: - MEMBER UINT cchSubtitle }}*/
   _XBST_UINT   ( cchSubtitle )
   /*{{|member_: - MEMBER POINTER32 pszTask }}*/
   _XBST_POINTER32 ( pszTask )  // LPWSTR
   /*{{|member_: - MEMBER UINT cchTask }}*/
   _XBST_UINT   ( cchTask )
   /*{{|member_: - MEMBER POINTER32 pszDescriptionTop }}*/
   _XBST_POINTER32 ( pszDescriptionTop )  // LPWSTR
   /*{{|member_: - MEMBER UINT cchDescriptionTop }}*/
   _XBST_UINT   ( cchDescriptionTop )
   /*{{|member_: - MEMBER POINTER32 pszDescriptionBottom }}*/
   _XBST_POINTER32 ( pszDescriptionBottom ) // LPWSTR
   /*{{|member_: - MEMBER UINT cchDescriptionBottom }}*/
   _XBST_UINT   ( cchDescriptionBottom )
   /*{{|member_: - MEMBER INT iTitleImage }}*/
   _XBST_int    ( iTitleImage )
   /*{{|member_: - MEMBER INT iExtendedImage }}*/
   _XBST_int    ( iExtendedImage )
   /*{{|member_: - MEMBER INT iFirstItem }}*/
   _XBST_int    ( iFirstItem )
   /*{{|member_: - MEMBER UINT cItems }}*/
   _XBST_UINT   ( cItems )
   /*{{|member_: - MEMBER POINTER32 pszSubsetTitle }}*/
   _XBST_POINTER32 ( pszSubsetTitle ) // LPWSTR
   /*{{|member_: - MEMBER UINT cchSubsetTitle }}*/
   _XBST_UINT   ( cchSubsetTitle )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVGROUPMETRICS
            | _slug_: wapist_lvgroupmetrics
            | class-function: WAPIST_LVGROUPMETRICS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVGROUPMETRICS structure. Defined as LVGROUPMETRICS in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_LVGROUPMETRICS, LVGROUPMETRICS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVGROUPMETRICS** }}*/
XB_BEGIN_STRUCTURE(LVGROUPMETRICS )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT( cbSize )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER UINT Left }}*/
   _XBST_UINT( Left )
   /*{{|member_: - MEMBER UINT Top }}*/
   _XBST_UINT( Top )
   /*{{|member_: - MEMBER UINT Right }}*/
   _XBST_UINT( Right )
   /*{{|member_: - MEMBER UINT Bottom }}*/
   _XBST_UINT( Bottom )
   /*{{|member_: - MEMBER COLORREF crLeft }}*/
   _XBST_COLORREF( crLeft )
   /*{{|member_: - MEMBER COLORREF crTop }}*/
   _XBST_COLORREF( crTop )
   /*{{|member_: - MEMBER COLORREF crRight }}*/
   _XBST_COLORREF( crRight )
   /*{{|member_: - MEMBER COLORREF crBottom }}*/
   _XBST_COLORREF( crBottom )
   /*{{|member_: - MEMBER COLORREF crHeader }}*/
   _XBST_COLORREF( crHeader )
   /*{{|member_: - MEMBER COLORREF crFooter }}*/
   _XBST_COLORREF( crFooter )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVHITTESTINFO
            | _slug_: wapist_lvhittestinfo
            | class-function: WAPIST_LVHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVHITTESTINFO structure. Defined as LVHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVHITTESTINFO, LVHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( LVHITTESTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT( pt )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT( flags )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER INT iGroup }}*/
   _XBST_int( iGroup )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVINSERTGROUPSORTED
            | _slug_: wapist_lvinsertgroupsorted
            | class-function: WAPIST_LVINSERTGROUPSORTED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVINSERTGROUPSORTED structure. Defined as LVINSERTGROUPSORTED in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_LVINSERTGROUPSORTED, LVINSERTGROUPSORTED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVINSERTGROUPSORTED** }}*/
XB_BEGIN_STRUCTURE( LVINSERTGROUPSORTED )
   /*{{|member_: - MEMBER POINTER32 pfnGroupCompare }}*/
   _XBST_POINTER32( pfnGroupCompare )
   /*{{|member_: - MEMBER POINTER32 pvData }}*/
   _XBST_POINTER32( pvData )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_lvgroup> wapist_LVGROUP}} lvGroup }}*/
   _XBST_LVGROUP( lvGroup )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVINSERTMARK
            | _slug_: wapist_lvinsertmark
            | class-function: WAPIST_LVINSERTMARK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVINSERTMARK structure. Defined as LVINSERTMARK in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVINSERTMARK, LVINSERTMARK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVINSERTMARK** }}*/
XB_BEGIN_STRUCTURE( LVINSERTMARK )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT( cbSize )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER DWORD dwReserved }}*/
   _XBST_DWORD( dwReserved )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVITEM
            | _slug_: wapist_lvitem
            | class-function: WAPIST_LVITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVITEMA structure. Defined as LVITEM in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvitema
            | _kw_: WAPIST_LVITEM, LVITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVITEM** }}*/
XB_BEGIN_STRUCTURE( LVITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT( state )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT( stateMask )
/*{{|member_: - MEMBER LPSTR pszText }}*/
/*{{|member_: - MEMBER DYNSZ cText |desc_: Helper member mapped over ::pszText. }}*/
_XBST_LPSTR_DYNSZ( pszText , cText)
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int( cchTextMax )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int( iImage )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM( lParam )
   /*{{|member_: - MEMBER INT iIndent }}*/
   _XBST_int( iIndent )
   /*{{|member_: - MEMBER INT iGroupId }}*/
   _XBST_int( iGroupId )
   /*{{|member_: - MEMBER UINT cColumns }}*/
   _XBST_UINT( cColumns )
   /*{{|member_: - MEMBER POINTER32 puColumns }}*/
   _XBST_POINTER32( puColumns )
   /*{{|member_: - MEMBER POINTER32 piColFmt }}*/
   _XBST_POINTER32( piColFmt )
   /*{{|member_: - MEMBER INT iGroup }}*/
   _XBST_int( iGroup )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVITEMINDEX
            | _slug_: wapist_lvitemindex
            | class-function: WAPIST_LVITEMINDEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVITEMINDEX structure. Defined as LVITEMINDEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVITEMINDEX, LVITEMINDEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVITEMINDEX** }}*/
XB_BEGIN_STRUCTURE( LVITEMINDEX )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iGroup }}*/
   _XBST_int( iGroup )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVSETINFOTIP
            | _slug_: wapist_lvsetinfotip
            | class-function: WAPIST_LVSETINFOTIP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVSETINFOTIP structure. Defined as LVSETINFOTIP in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVSETINFOTIP, LVSETINFOTIP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVSETINFOTIP** }}*/
XB_BEGIN_STRUCTURE( LVSETINFOTIP )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT( cbSize )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags )
   /*{{|member_: - MEMBER POINTER32 pszText }}*/
   _XBST_POINTER32( pszText ) // LPWSTR
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER HBITMAP hbmp }}*/
   _XBST_HBITMAP( hbmp )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVTILEINFO
            | _slug_: wapist_lvtileinfo
            | class-function: WAPIST_LVTILEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVTILEINFO structure. Defined as LVTILEINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LVTILEINFO, LVTILEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVTILEINFO** }}*/
XB_BEGIN_STRUCTURE( LVTILEINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT   ( cbSize )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int    ( iItem )
   /*{{|member_: - MEMBER UINT cColumns }}*/
   _XBST_UINT   ( cColumns )
   /*{{|member_: - MEMBER POINTER32 puColumns }}*/
   _XBST_POINTER32( puColumns )
   /*{{|member_: - MEMBER POINTER32 piColFmt }}*/
   _XBST_POINTER32   ( piColFmt )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LVTILEVIEWINFO
            | _slug_: wapist_lvtileviewinfo
            | class-function: WAPIST_LVTILEVIEWINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LVTILEVIEWINFO structure. Defined as LVTILEVIEWINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_LVTILEVIEWINFO, LVTILEVIEWINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LVTILEVIEWINFO** }}*/
XB_BEGIN_STRUCTURE( LVTILEVIEWINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT( cbSize )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD( dwMask )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_size> wapist_SIZE}} sizeTile }}*/
   _XBST_SIZE( sizeTile )
   /*{{|member_: - MEMBER INT cLines }}*/
   _XBST_int( cLines )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcLabelMargin }}*/
   _XBST_RECT( rcLabelMargin )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMITEMACTIVATE
            | _slug_: wapist_nmitemactivate
            | class-function: WAPIST_NMITEMACTIVATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMITEMACTIVATE structure. Defined as NMITEMACTIVATE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMITEMACTIVATE, NMITEMACTIVATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMITEMACTIVATE** }}*/
XB_BEGIN_STRUCTURE( NMITEMACTIVATE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER UINT uNewState }}*/
   _XBST_UINT( uNewState )
   /*{{|member_: - MEMBER UINT uOldState }}*/
   _XBST_UINT( uOldState )
   /*{{|member_: - MEMBER UINT uChanged }}*/
   _XBST_UINT( uChanged )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptAction }}*/
   _XBST_POINT( ptAction )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM( lParam )
   /*{{|member_: - MEMBER UINT uKeyFlags }}*/
   _XBST_UINT( uKeyFlags )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLISTVIEW
            | _slug_: wapist_nmlistview
            | class-function: WAPIST_NMLISTVIEW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLISTVIEW structure. Defined as NMLISTVIEW in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLISTVIEW, NMLISTVIEW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLISTVIEW** }}*/
XB_BEGIN_STRUCTURE( NMLISTVIEW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER UINT uNewState }}*/
   _XBST_UINT( uNewState )
   /*{{|member_: - MEMBER UINT uOldState }}*/
   _XBST_UINT( uOldState )
   /*{{|member_: - MEMBER UINT uChanged }}*/
   _XBST_UINT( uChanged )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptAction }}*/
   _XBST_POINT( ptAction )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM( lParam )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVCACHEHINT
            | _slug_: wapist_nmlvcachehint
            | class-function: WAPIST_NMLVCACHEHINT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVCACHEHINT structure. Defined as NMLVCACHEHINT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVCACHEHINT, NMLVCACHEHINT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVCACHEHINT** }}*/
XB_BEGIN_STRUCTURE( NMLVCACHEHINT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT iFrom }}*/
   _XBST_int( iFrom )
   /*{{|member_: - MEMBER INT iTo }}*/
   _XBST_int( iTo )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVCUSTOMDRAW
            | _slug_: wapist_nmlvcustomdraw
            | class-function: WAPIST_NMLVCUSTOMDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVCUSTOMDRAW structure. Defined as NMLVCUSTOMDRAW in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMLVCUSTOMDRAW, NMLVCUSTOMDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVCUSTOMDRAW** }}*/
XB_BEGIN_STRUCTURE( NMLVCUSTOMDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmcustomdraw> wapist_NMCUSTOMDRAW}} nmcd }}*/
   _XBST_NMCUSTOMDRAW( nmcd )
   /*{{|member_: - MEMBER COLORREF clrText }}*/
   _XBST_COLORREF( clrText )
   /*{{|member_: - MEMBER COLORREF clrTextBk }}*/
   _XBST_COLORREF( clrTextBk )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER DWORD dwItemType }}*/
   _XBST_DWORD( dwItemType )
   /*{{|member_: - MEMBER COLORREF clrFace }}*/
   _XBST_COLORREF( clrFace )
   /*{{|member_: - MEMBER INT iIconEffect }}*/
   _XBST_INT( iIconEffect )
   /*{{|member_: - MEMBER INT iIconPhase }}*/
   _XBST_INT( iIconPhase )
   /*{{|member_: - MEMBER INT iPartId }}*/
   _XBST_INT( iPartId )
   /*{{|member_: - MEMBER INT iStateId }}*/
   _XBST_INT( iStateId )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcText }}*/
   _XBST_RECT( rcText )
   /*{{|member_: - MEMBER UINT uAlign }}*/
   _XBST_UINT( uAlign )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVDISPINFO
            | _slug_: wapist_nmlvdispinfo
            | class-function: WAPIST_NMLVDISPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVDISPINFO structure. Defined as NMLVDISPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVDISPINFO, NMLVDISPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVDISPINFO** }}*/
XB_BEGIN_STRUCTURE( NMLVDISPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_lvitem> wapist_LVITEM}} item }}*/
   _XBST_LVITEM( item )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVEMPTYMARKUP
            | _slug_: wapist_nmlvemptymarkup
            | class-function: WAPIST_NMLVEMPTYMARKUP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVEMPTYMARKUP structure. Defined as NMLVEMPTYMARKUP in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMLVEMPTYMARKUP, NMLVEMPTYMARKUP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVEMPTYMARKUP** }}*/
XB_BEGIN_STRUCTURE( NMLVEMPTYMARKUP )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags )
   /*{{|member_: - MEMBER SZWSTR szMarkup }}*/
   _XBST_SZWSTR( szMarkup , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVFINDITEM
            | _slug_: wapist_nmlvfinditem
            | class-function: WAPIST_NMLVFINDITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVFINDITEM structure. Defined as NMLVFINDITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVFINDITEM, NMLVFINDITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVFINDITEM** }}*/
XB_BEGIN_STRUCTURE( NMLVFINDITEM )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT iStart }}*/
   _XBST_int( iStart )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_lvfindinfo> wapist_LVFINDINFO}} lvfi }}*/
   _XBST_LVFINDINFO( lvfi )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVGETINFOTIP
            | _slug_: wapist_nmlvgetinfotip
            | class-function: WAPIST_NMLVGETINFOTIP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVGETINFOTIP structure. Defined as NMLVGETINFOTIP in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-nmlvgetinfotipa
            | _kw_: WAPIST_NMLVGETINFOTIP, NMLVGETINFOTIP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVGETINFOTIP** }}*/
XB_BEGIN_STRUCTURE( NMLVGETINFOTIP )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags )
/*{{|member_: - MEMBER LPSTR pszText }}*/
/*{{|member_: - MEMBER DYNSZ cText |desc_: Helper member mapped over ::pszText. }}*/
_XBST_LPSTR_DYNSZ( pszText , cText)
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int( cchTextMax )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM( lParam )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVKEYDOWN
            | _slug_: wapist_nmlvkeydown
            | class-function: WAPIST_NMLVKEYDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVKEYDOWN structure. Defined as NMLVKEYDOWN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVKEYDOWN, NMLVKEYDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVKEYDOWN** }}*/
XB_BEGIN_STRUCTURE( NMLVKEYDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER WORD wVKey }}*/
   _XBST_WORD( wVKey )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT( flags )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVLINK
            | _slug_: wapist_nmlvlink
            | class-function: WAPIST_NMLVLINK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVLINK structure. Defined as NMLVLINK in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVLINK, NMLVLINK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVLINK** }}*/
XB_BEGIN_STRUCTURE( NMLVLINK )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_litem> wapist_LITEM}} link }}*/
   _XBST_LITEM( link )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int( iItem )
   /*{{|member_: - MEMBER INT iSubItem }}*/
   _XBST_int( iSubItem )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVODSTATECHANGE
            | _slug_: wapist_nmlvodstatechange
            | class-function: WAPIST_NMLVODSTATECHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVODSTATECHANGE structure. Defined as NMLVODSTATECHANGE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMLVODSTATECHANGE, NMLVODSTATECHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVODSTATECHANGE** }}*/
XB_BEGIN_STRUCTURE( NMLVODSTATECHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT iFrom }}*/
   _XBST_int( iFrom )
   /*{{|member_: - MEMBER INT iTo }}*/
   _XBST_int( iTo )
   /*{{|member_: - MEMBER UINT uNewState }}*/
   _XBST_UINT( uNewState )
   /*{{|member_: - MEMBER UINT uOldState }}*/
   _XBST_UINT( uOldState )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLVSCROLL
            | _slug_: wapist_nmlvscroll
            | class-function: WAPIST_NMLVSCROLL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLVSCROLL structure. Defined as NMLVSCROLL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLVSCROLL, NMLVSCROLL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLVSCROLL** }}*/
XB_BEGIN_STRUCTURE( NMLVSCROLL )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER INT dx }}*/
   _XBST_int( dx )
   /*{{|member_: - MEMBER INT dy }}*/
   _XBST_int( dy )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LITEM
            | _slug_: wapist_litem
            | class-function: WAPIST_LITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LITEM structure. Defined as LITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LITEM, LITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LITEM** }}*/
XB_BEGIN_STRUCTURE( LITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT( mask )
   /*{{|member_: - MEMBER INT iLink }}*/
   _XBST_int( iLink )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT( state )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT( stateMask )
   /*{{|member_: - MEMBER SZWSTR szID }}*/
   _XBST_SZWSTR( szID  , 48 )
   /*{{|member_: - MEMBER SZWSTR szUrl }}*/
   _XBST_SZWSTR( szUrl , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCUSTOMDRAW
            | _slug_: wapist_nmcustomdraw
            | class-function: WAPIST_NMCUSTOMDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCUSTOMDRAW structure. Defined as NMCUSTOMDRAW in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMCUSTOMDRAW, NMCUSTOMDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCUSTOMDRAW** }}*/
XB_BEGIN_STRUCTURE( NMCUSTOMDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR( hdr )
   /*{{|member_: - MEMBER DWORD dwDrawStage }}*/
   _XBST_DWORD( dwDrawStage )
   /*{{|member_: - MEMBER HDC hdc }}*/
   _XBST_HDC( hdc )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT( rc )
   /*{{|member_: - MEMBER DWORD dwItemSpec }}*/
   _XBST_DWORD( dwItemSpec )
   /*{{|member_: - MEMBER UINT uItemState }}*/
   _XBST_UINT( uItemState )
   /*{{|member_: - MEMBER LPARAM lItemlParam }}*/
   _XBST_LPARAM( lItemlParam )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_WINDOWPOS
            | _slug_: wapist_windowpos
            | class-function: WAPIST_WINDOWPOS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi WINDOWPOS structure. Defined as WINDOWPOS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_WINDOWPOS, WINDOWPOS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  WINDOWPOS** }}*/
XB_BEGIN_STRUCTURE( WINDOWPOS )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND ( hwnd  )
   /*{{|member_: - MEMBER HWND hwndInsertAfter }}*/
   _XBST_HWND ( hwndInsertAfter  )
   /*{{|member_: - MEMBER INT x }}*/
   _XBST_int ( x  )
   /*{{|member_: - MEMBER INT y }}*/
   _XBST_int ( y  )
   /*{{|member_: - MEMBER INT cx }}*/
   _XBST_int ( cx  )
   /*{{|member_: - MEMBER INT cy }}*/
   _XBST_int ( cy  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COLORSCHEME
            | _slug_: wapist_colorscheme
            | class-function: WAPIST_COLORSCHEME
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COLORSCHEME structure. Defined as COLORSCHEME in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_COLORSCHEME, COLORSCHEME, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COLORSCHEME** }}*/
XB_BEGIN_STRUCTURE( COLORSCHEME )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize  )
   /*{{|member_: - MEMBER COLORREF clrBtnHighlight }}*/
   _XBST_COLORREF ( clrBtnHighlight  )
   /*{{|member_: - MEMBER COLORREF clrBtnShadow }}*/
   _XBST_COLORREF ( clrBtnShadow  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DPASTREAMINFO
            | _slug_: wapist_dpastreaminfo
            | class-function: WAPIST_DPASTREAMINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DPASTREAMINFO structure. Defined as DPASTREAMINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DPASTREAMINFO, DPASTREAMINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DPASTREAMINFO** }}*/
XB_BEGIN_STRUCTURE( DPASTREAMINFO )
   /*{{|member_: - MEMBER INT iPos }}*/
   _XBST_int ( iPos  )
   /*{{|member_: - MEMBER LPVOID pvItem }}*/
   _XBST_LPVOID ( pvItem  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCHAR
            | _slug_: wapist_nmchar
            | class-function: WAPIST_NMCHAR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCHAR structure. Defined as NMCHAR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMCHAR, NMCHAR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCHAR** }}*/
XB_BEGIN_STRUCTURE( NMCHAR )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr         )
   /*{{|member_: - MEMBER UINT ch }}*/
   _XBST_UINT  ( ch          )
   /*{{|member_: - MEMBER DWORD dwItemPrev }}*/
   _XBST_DWORD ( dwItemPrev  )
   /*{{|member_: - MEMBER DWORD dwItemNext }}*/
   _XBST_DWORD ( dwItemNext  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCUSTOMSPLITRECTINFO
            | _slug_: wapist_nmcustomsplitrectinfo
            | class-function: WAPIST_NMCUSTOMSPLITRECTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCUSTOMSPLITRECTINFO structure. Defined as NMCUSTOMSPLITRECTINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMCUSTOMSPLITRECTINFO, NMCUSTOMSPLITRECTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCUSTOMSPLITRECTINFO** }}*/
XB_BEGIN_STRUCTURE( NMCUSTOMSPLITRECTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcClient }}*/
   _XBST_RECT ( rcClient  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcButton }}*/
   _XBST_RECT ( rcButton  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcSplit }}*/
   _XBST_RECT ( rcSplit  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCUSTOMTEXT
            | _slug_: wapist_nmcustomtext
            | class-function: WAPIST_NMCUSTOMTEXT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCUSTOMTEXT structure. Defined as NMCUSTOMTEXT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMCUSTOMTEXT, NMCUSTOMTEXT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCUSTOMTEXT** }}*/
XB_BEGIN_STRUCTURE( NMCUSTOMTEXT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER HDC hDC }}*/
   _XBST_HDC ( hDC  )
   /*{{|member_: - MEMBER POINTER32 lpString }}*/
   _XBST_POINTER32 ( lpString  )
   /*{{|member_: - MEMBER INT nCount }}*/
   _XBST_int ( nCount  )
   /*{{|member_: - MEMBER POINTER32 lpRect }}*/
   _XBST_POINTER32( lpRect  )
   /*{{|member_: - MEMBER UINT uFormat }}*/
   _XBST_UINT ( uFormat  )
   /*{{|member_: - MEMBER BOOL fLink }}*/
   _XBST_BOOL ( fLink  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMKEY
            | _slug_: wapist_nmkey
            | class-function: WAPIST_NMKEY
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMKEY structure. Defined as NMKEY in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMKEY, NMKEY, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMKEY** }}*/
XB_BEGIN_STRUCTURE( NMKEY )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER UINT nVKey }}*/
   _XBST_UINT ( nVKey  )
   /*{{|member_: - MEMBER UINT uFlags }}*/
   _XBST_UINT ( uFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMMOUSE
            | _slug_: wapist_nmmouse
            | class-function: WAPIST_NMMOUSE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMMOUSE structure. Defined as NMMOUSE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMMOUSE, NMMOUSE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMMOUSE** }}*/
XB_BEGIN_STRUCTURE( NMMOUSE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER POINTER32 dwItemSpec }}*/
   _XBST_POINTER32 ( dwItemSpec  )
   /*{{|member_: - MEMBER POINTER32 dwItemData }}*/
   _XBST_POINTER32 ( dwItemData  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER LPARAM dwHitInfo }}*/
   _XBST_LPARAM ( dwHitInfo  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMOBJECTNOTIFY
            | _slug_: wapist_nmobjectnotify
            | class-function: WAPIST_NMOBJECTNOTIFY
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMOBJECTNOTIFY structure. Defined as NMOBJECTNOTIFY in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMOBJECTNOTIFY, NMOBJECTNOTIFY, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMOBJECTNOTIFY** }}*/
XB_BEGIN_STRUCTURE( NMOBJECTNOTIFY )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER POINTER32 piid }}*/
   _XBST_POINTER32 ( piid  )
   /*{{|member_: - MEMBER POINTER32 pObject }}*/
   _XBST_POINTER32 ( pObject  )
   /*{{|member_: - MEMBER HRESULT hResult }}*/
   _XBST_HRESULT ( hResult  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTOOLTIPSCREATED
            | _slug_: wapist_nmtooltipscreated
            | class-function: WAPIST_NMTOOLTIPSCREATED
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTOOLTIPSCREATED structure. Defined as NMTOOLTIPSCREATED in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTOOLTIPSCREATED, NMTOOLTIPSCREATED, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTOOLTIPSCREATED** }}*/
XB_BEGIN_STRUCTURE( NMTOOLTIPSCREATED )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER HWND hwndToolTips }}*/
   _XBST_HWND ( hwndToolTips  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_READERMODEINFO
            | _slug_: wapist_readermodeinfo
            | class-function: WAPIST_READERMODEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi READERMODEINFO structure. Defined as READERMODEINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_READERMODEINFO, READERMODEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  READERMODEINFO** }}*/
XB_BEGIN_STRUCTURE( READERMODEINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize  )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND ( hwnd  )
   /*{{|member_: - MEMBER DWORD fFlags }}*/
   _XBST_DWORD ( fFlags  )
   /*{{|member_: - MEMBER POINTER32 prc }}*/
   _XBST_POINTER32( prc  )
   /*{{|member_: - MEMBER DWORD pfnScroll }}*/
   _XBST_DWORD  ( pfnScroll  )
   /*{{|member_: - MEMBER DWORD pfnTranslateDispatch }}*/
   _XBST_DWORD  ( pfnTranslateDispatch )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BUTTON_IMAGELIST
            | _slug_: wapist_button_imagelist
            | class-function: WAPIST_BUTTON_IMAGELIST
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BUTTON_IMAGELIST structure. Defined as BUTTON_IMAGELIST in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_BUTTON_IMAGELIST, BUTTON_IMAGELIST, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BUTTON_IMAGELIST** }}*/
XB_BEGIN_STRUCTURE( BUTTON_IMAGELIST )
   /*{{|member_: - MEMBER HIMAGELIST himl }}*/
   _XBST_HIMAGELIST ( himl  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} margin }}*/
   _XBST_RECT ( margin  )
   /*{{|member_: - MEMBER UINT uAlign }}*/
   _XBST_UINT ( uAlign  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_BUTTON_SPLITINFO
            | _slug_: wapist_button_splitinfo
            | class-function: WAPIST_BUTTON_SPLITINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi BUTTON_SPLITINFO structure. Defined as BUTTON_SPLITINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_BUTTON_SPLITINFO, BUTTON_SPLITINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  BUTTON_SPLITINFO** }}*/
XB_BEGIN_STRUCTURE( BUTTON_SPLITINFO )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER HIMAGELIST himlGlyph }}*/
   _XBST_HIMAGELIST ( himlGlyph  )
   /*{{|member_: - MEMBER UINT uSplitStyle }}*/
   _XBST_UINT ( uSplitStyle  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_size> wapist_SIZE}} size }}*/
   _XBST_SIZE ( size  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMBCDROPDOWN
            | _slug_: wapist_nmbcdropdown
            | class-function: WAPIST_NMBCDROPDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMBCDROPDOWN structure. Defined as NMBCDROPDOWN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMBCDROPDOWN, NMBCDROPDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMBCDROPDOWN** }}*/
XB_BEGIN_STRUCTURE( NMBCDROPDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcButton }}*/
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMBCHOTITEM
            | _slug_: wapist_nmbchotitem
            | class-function: WAPIST_NMBCHOTITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMBCHOTITEM structure. Defined as NMBCHOTITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMBCHOTITEM, NMBCHOTITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMBCHOTITEM** }}*/
XB_BEGIN_STRUCTURE( NMBCHOTITEM )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COMBOBOXINFO
            | _slug_: wapist_comboboxinfo
            | class-function: WAPIST_COMBOBOXINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COMBOBOXINFO structure. Defined as COMBOBOXINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_COMBOBOXINFO, COMBOBOXINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COMBOBOXINFO** }}*/
XB_BEGIN_STRUCTURE( COMBOBOXINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD ( cbSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcItem }}*/
   _XBST_RECT ( rcItem  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcButton }}*/
   _XBST_RECT ( rcButton  )
   /*{{|member_: - MEMBER DWORD stateButton }}*/
   _XBST_DWORD ( stateButton  )
   /*{{|member_: - MEMBER HWND hwndCombo }}*/
   _XBST_HWND ( hwndCombo  )
   /*{{|member_: - MEMBER HWND hwndItem }}*/
   _XBST_HWND ( hwndItem  )
   /*{{|member_: - MEMBER HWND hwndList }}*/
   _XBST_HWND ( hwndList  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COMPAREITEMSTRUCT
            | _slug_: wapist_compareitemstruct
            | class-function: WAPIST_COMPAREITEMSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COMPAREITEMSTRUCT structure. Defined as COMPAREITEMSTRUCT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_COMPAREITEMSTRUCT, COMPAREITEMSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COMPAREITEMSTRUCT** }}*/
XB_BEGIN_STRUCTURE( COMPAREITEMSTRUCT )
   /*{{|member_: - MEMBER UINT CtlType }}*/
   _XBST_UINT ( CtlType  )
   /*{{|member_: - MEMBER UINT CtlID }}*/
   _XBST_UINT ( CtlID  )
   /*{{|member_: - MEMBER HWND hwndItem }}*/
   _XBST_HWND ( hwndItem  )
   /*{{|member_: - MEMBER UINT itemID1 }}*/
   _XBST_UINT ( itemID1  )
   /*{{|member_: - MEMBER POINTER32 itemData1 }}*/
   _XBST_POINTER32 ( itemData1  )
   /*{{|member_: - MEMBER UINT itemID2 }}*/
   _XBST_UINT ( itemID2  )
   /*{{|member_: - MEMBER POINTER32 itemData2 }}*/
   _XBST_POINTER32 ( itemData2  )
   /*{{|member_: - MEMBER DWORD dwLocaleId }}*/
   _XBST_DWORD ( dwLocaleId  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRAWITEMSTRUCT
            | _slug_: wapist_drawitemstruct
            | class-function: WAPIST_DRAWITEMSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRAWITEMSTRUCT structure. Defined as DRAWITEMSTRUCT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DRAWITEMSTRUCT, DRAWITEMSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRAWITEMSTRUCT** }}*/
XB_BEGIN_STRUCTURE( DRAWITEMSTRUCT )
   /*{{|member_: - MEMBER UINT CtlType }}*/
   _XBST_UINT ( CtlType  )
   /*{{|member_: - MEMBER UINT CtlID }}*/
   _XBST_UINT ( CtlID  )
   /*{{|member_: - MEMBER UINT itemID }}*/
   _XBST_UINT ( itemID  )
   /*{{|member_: - MEMBER UINT itemAction }}*/
   _XBST_UINT ( itemAction  )
   /*{{|member_: - MEMBER UINT itemState }}*/
   _XBST_UINT ( itemState  )
   /*{{|member_: - MEMBER HWND hwndItem }}*/
   _XBST_HWND ( hwndItem  )
   /*{{|member_: - MEMBER HDC hDC }}*/
   _XBST_HDC ( hDC  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcItem }}*/
   _XBST_RECT ( rcItem  )
   /*{{|member_: - MEMBER POINTER32 itemData }}*/
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MEASUREITEMSTRUCT
            | _slug_: wapist_measureitemstruct
            | class-function: WAPIST_MEASUREITEMSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MEASUREITEMSTRUCT structure. Defined as MEASUREITEMSTRUCT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MEASUREITEMSTRUCT, MEASUREITEMSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MEASUREITEMSTRUCT** }}*/
XB_BEGIN_STRUCTURE( MEASUREITEMSTRUCT )
   /*{{|member_: - MEMBER UINT CtlType }}*/
   _XBST_UINT ( CtlType  )
   /*{{|member_: - MEMBER UINT CtlID }}*/
   _XBST_UINT ( CtlID  )
   /*{{|member_: - MEMBER UINT itemID }}*/
   _XBST_UINT ( itemID  )
   /*{{|member_: - MEMBER UINT itemWidth }}*/
   _XBST_UINT ( itemWidth  )
   /*{{|member_: - MEMBER UINT itemHeight }}*/
   _XBST_UINT ( itemHeight  )
   /*{{|member_: - MEMBER POINTER32 itemData }}*/
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COMBOBOXEXITEM
            | _slug_: wapist_comboboxexitem
            | class-function: WAPIST_COMBOBOXEXITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COMBOBOXEXITEM structure. Defined as COMBOBOXEXITEM in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_COMBOBOXEXITEM, COMBOBOXEXITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COMBOBOXEXITEM** }}*/
XB_BEGIN_STRUCTURE( COMBOBOXEXITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER POINTER32 iItem }}*/
   _XBST_POINTER32 ( iItem  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
   /*{{|member_: - MEMBER INT iSelectedImage }}*/
   _XBST_int ( iSelectedImage  )
   /*{{|member_: - MEMBER INT iOverlay }}*/
   _XBST_int ( iOverlay  )
   /*{{|member_: - MEMBER INT iIndent }}*/
   _XBST_int ( iIndent  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCBEDRAGBEGIN
            | _slug_: wapist_nmcbedragbegin
            | class-function: WAPIST_NMCBEDRAGBEGIN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCBEDRAGBEGIN structure. Defined as NMCBEDRAGBEGIN in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMCBEDRAGBEGIN, NMCBEDRAGBEGIN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCBEDRAGBEGIN** }}*/
XB_BEGIN_STRUCTURE( NMCBEDRAGBEGIN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItemid }}*/
   _XBST_int ( iItemid  )
   /*{{|member_: - MEMBER BYTE szText }}*/
   _XBST_CHAR ( szText  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCBEENDEDIT
            | _slug_: wapist_nmcbeendedit
            | class-function: WAPIST_NMCBEENDEDIT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCBEENDEDIT structure. Defined as NMCBEENDEDIT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMCBEENDEDIT, NMCBEENDEDIT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCBEENDEDIT** }}*/
XB_BEGIN_STRUCTURE( NMCBEENDEDIT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER BOOL fChanged }}*/
   _XBST_BOOL ( fChanged  )
   /*{{|member_: - MEMBER INT iNewSelection }}*/
   _XBST_int ( iNewSelection  )
   /*{{|member_: - MEMBER BYTE szText }}*/
   _XBST_TCHAR ( szText  )
   /*{{|member_: - MEMBER INT iWhy }}*/
   _XBST_int ( iWhy  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMCOMBOBOXEX
            | _slug_: wapist_nmcomboboxex
            | class-function: WAPIST_NMCOMBOBOXEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMCOMBOBOXEX structure. Defined as NMCOMBOBOXEX in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMCOMBOBOXEX, NMCOMBOBOXEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMCOMBOBOXEX** }}*/
XB_BEGIN_STRUCTURE( NMCOMBOBOXEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_comboboxexitem> wapist_COMBOBOXEXITEM}} ceItem }}*/
   _XBST_COMBOBOXEXITEM ( ceItem  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DATETIMEPICKERINFO
            | _slug_: wapist_datetimepickerinfo
            | class-function: WAPIST_DATETIMEPICKERINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DATETIMEPICKERINFO structure. Defined as DATETIMEPICKERINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DATETIMEPICKERINFO, DATETIMEPICKERINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DATETIMEPICKERINFO** }}*/
XB_BEGIN_STRUCTURE( DATETIMEPICKERINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD ( cbSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcCheck }}*/
   _XBST_RECT ( rcCheck  )
   /*{{|member_: - MEMBER DWORD stateCheck }}*/
   _XBST_DWORD ( stateCheck  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcButton }}*/
   _XBST_RECT ( rcButton  )
   /*{{|member_: - MEMBER DWORD stateButton }}*/
   _XBST_DWORD ( stateButton  )
   /*{{|member_: - MEMBER HWND hwndEdit }}*/
   _XBST_HWND ( hwndEdit  )
   /*{{|member_: - MEMBER HWND hwndUD }}*/
   _XBST_HWND ( hwndUD  )
   /*{{|member_: - MEMBER HWND hwndDropDown }}*/
   _XBST_HWND ( hwndDropDown  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDATETIMECHANGE
            | _slug_: wapist_nmdatetimechange
            | class-function: WAPIST_NMDATETIMECHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDATETIMECHANGE structure. Defined as NMDATETIMECHANGE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMDATETIMECHANGE, NMDATETIMECHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDATETIMECHANGE** }}*/
XB_BEGIN_STRUCTURE( NMDATETIMECHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} st }}*/
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDATETIMEFORMAT
            | _slug_: wapist_nmdatetimeformat
            | class-function: WAPIST_NMDATETIMEFORMAT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDATETIMEFORMAT structure. Defined as NMDATETIMEFORMAT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMDATETIMEFORMAT, NMDATETIMEFORMAT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDATETIMEFORMAT** }}*/
XB_BEGIN_STRUCTURE( NMDATETIMEFORMAT )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER LPSTR pszFormat }}*/
   _XBST_LPSTR ( pszFormat  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} st }}*/
   _XBST_SYSTEMTIME ( st  )
   /*{{|member_: - MEMBER LPSTR pszDisplay }}*/
   _XBST_LPSTR ( pszDisplay  )
   /*{{|member_: - MEMBER BYTE szDisplay }}*/
   _XBST_TCHAR ( szDisplay  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDATETIMEFORMATQUERY
            | _slug_: wapist_nmdatetimeformatquery
            | class-function: WAPIST_NMDATETIMEFORMATQUERY
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDATETIMEFORMATQUERY structure. Defined as NMDATETIMEFORMATQUERY in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMDATETIMEFORMATQUERY, NMDATETIMEFORMATQUERY, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDATETIMEFORMATQUERY** }}*/
XB_BEGIN_STRUCTURE( NMDATETIMEFORMATQUERY )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr |desc_: NHDR structure }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER LPSTR pszFormat |desc_: string pointer }}*/
   _XBST_LPSTR ( pszFormat  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_size> wapist_SIZE}} szMax |desc_: SIZE structure }}*/
   _XBST_SIZE ( szMax  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDATETIMESTRING
            | _slug_: wapist_nmdatetimestring
            | class-function: WAPIST_NMDATETIMESTRING
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDATETIMESTRING structure. Defined as NMDATETIMESTRING in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMDATETIMESTRING, NMDATETIMESTRING, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDATETIMESTRING** }}*/
XB_BEGIN_STRUCTURE( NMDATETIMESTRING )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER LPSTR pszUserString }}*/
   _XBST_LPSTR ( pszUserString  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} st }}*/
   _XBST_SYSTEMTIME ( st  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDATETIMEWMKEYDOWN
            | _slug_: wapist_nmdatetimewmkeydown
            | class-function: WAPIST_NMDATETIMEWMKEYDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDATETIMEWMKEYDOWN structure. Defined as NMDATETIMEWMKEYDOWN in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMDATETIMEWMKEYDOWN, NMDATETIMEWMKEYDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDATETIMEWMKEYDOWN** }}*/
XB_BEGIN_STRUCTURE( NMDATETIMEWMKEYDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER INT nVirtKey }}*/
   _XBST_int ( nVirtKey  )
   /*{{|member_: - MEMBER LPSTR pszFormat }}*/
   _XBST_LPSTR ( pszFormat  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} st }}*/
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DRAGLISTINFO
            | _slug_: wapist_draglistinfo
            | class-function: WAPIST_DRAGLISTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DRAGLISTINFO structure. Defined as DRAGLISTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_DRAGLISTINFO, DRAGLISTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DRAGLISTINFO** }}*/
XB_BEGIN_STRUCTURE( DRAGLISTINFO )
   /*{{|member_: - MEMBER UINT uNotification }}*/
   _XBST_UINT ( uNotification  )
   /*{{|member_: - MEMBER HWND hWnd }}*/
   _XBST_HWND ( hWnd  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptCursor }}*/
   _XBST_POINT ( ptCursor  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_EDITBALLOONTIP
            | _slug_: wapist_editballoontip
            | class-function: WAPIST_EDITBALLOONTIP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi EDITBALLOONTIP structure. Defined as EDITBALLOONTIP in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_EDITBALLOONTIP, EDITBALLOONTIP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  EDITBALLOONTIP** }}*/
XB_BEGIN_STRUCTURE( EDITBALLOONTIP )
   /*{{|member_: - MEMBER DWORD cbStruct }}*/
   _XBST_DWORD ( cbStruct  )
   /*{{|member_: - MEMBER POINTER32 pszTitle }}*/
   _XBST_POINTER32 ( pszTitle  )
   /*{{|member_: - MEMBER POINTER32 pszText }}*/
   _XBST_POINTER32 ( pszText  )
   /*{{|member_: - MEMBER INT ttiIcon }}*/
   _XBST_INT ( ttiIcon  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HDHITTESTINFO
            | _slug_: wapist_hdhittestinfo
            | class-function: WAPIST_HDHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HDHITTESTINFO structure. Defined as HDHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HDHITTESTINFO, HDHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HDHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( HDHITTESTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HDITEM
            | _slug_: wapist_hditem
            | class-function: WAPIST_HDITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HDITEM structure. Defined as HDITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HDITEM, HDITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HDITEM** }}*/
XB_BEGIN_STRUCTURE( HDITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT    ( mask  )
   /*{{|member_: - MEMBER INT cxy }}*/
   _XBST_int     ( cxy  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR  ( pszText  )
   /*{{|member_: - MEMBER HBITMAP hbm }}*/
   _XBST_HBITMAP ( hbm  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int     ( cchTextMax  )
   /*{{|member_: - MEMBER INT fmt }}*/
   _XBST_int     ( fmt  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM  ( lParam  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int     ( iImage  )
   /*{{|member_: - MEMBER INT iOrder }}*/
   _XBST_int     ( iOrder  )
   /*{{|member_: - MEMBER UINT type }}*/
   _XBST_UINT    ( type  )
   /*{{|member_: - MEMBER LPVOID pvFilter }}*/
   _XBST_LPVOID  ( pvFilter  )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT   ( state  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HDLAYOUT
            | _slug_: wapist_hdlayout
            | class-function: WAPIST_HDLAYOUT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HDLAYOUT structure. Defined as HDLAYOUT in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HDLAYOUT, HDLAYOUT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HDLAYOUT** }}*/
XB_BEGIN_STRUCTURE( HDLAYOUT )
   /*{{|member_: - MEMBER POINTER32 prc }}*/
   _XBST_POINTER32  ( prc  )
   /*{{|member_: - MEMBER POINTER32 pwpos }}*/
   _XBST_POINTER32  ( pwpos  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HDTEXTFILTER
            | _slug_: wapist_hdtextfilter
            | class-function: WAPIST_HDTEXTFILTER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HDTEXTFILTER structure. Defined as HDTEXTFILTER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_HDTEXTFILTER, HDTEXTFILTER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HDTEXTFILTER** }}*/
XB_BEGIN_STRUCTURE( HDTEXTFILTER )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_INT ( cchTextMax  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMHDDISPINFO
            | _slug_: wapist_nmhddispinfo
            | class-function: WAPIST_NMHDDISPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMHDDISPINFO structure. Defined as NMHDDISPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMHDDISPINFO, NMHDDISPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMHDDISPINFO** }}*/
XB_BEGIN_STRUCTURE( NMHDDISPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMHDFILTERBTNCLICK
            | _slug_: wapist_nmhdfilterbtnclick
            | class-function: WAPIST_NMHDFILTERBTNCLICK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMHDFILTERBTNCLICK structure. Defined as NMHDFILTERBTNCLICK in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMHDFILTERBTNCLICK, NMHDFILTERBTNCLICK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMHDFILTERBTNCLICK** }}*/
XB_BEGIN_STRUCTURE( NMHDFILTERBTNCLICK )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_INT ( iItem  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT ( rc  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMHEADER
            | _slug_: wapist_nmheader
            | class-function: WAPIST_NMHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMHEADER structure. Defined as NMHEADER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMHEADER, NMHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMHEADER** }}*/
XB_BEGIN_STRUCTURE( NMHEADER )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER INT iButton }}*/
   _XBST_int ( iButton  )
   /*{{|member_: - MEMBER POINTER32 pitem }}*/
   _XBST_POINTER32 ( pitem  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMIPADDRESS
            | _slug_: wapist_nmipaddress
            | class-function: WAPIST_NMIPADDRESS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMIPADDRESS structure. Defined as NMIPADDRESS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMIPADDRESS, NMIPADDRESS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMIPADDRESS** }}*/
XB_BEGIN_STRUCTURE( NMIPADDRESS )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iField }}*/
   _XBST_int ( iField  )
   /*{{|member_: - MEMBER INT iValue }}*/
   _XBST_int ( iValue  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_DELETEITEMSTRUCT
            | _slug_: wapist_deleteitemstruct
            | class-function: WAPIST_DELETEITEMSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi DELETEITEMSTRUCT structure. Defined as DELETEITEMSTRUCT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_DELETEITEMSTRUCT, DELETEITEMSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  DELETEITEMSTRUCT** }}*/
XB_BEGIN_STRUCTURE( DELETEITEMSTRUCT )
   /*{{|member_: - MEMBER UINT CtlType }}*/
   _XBST_UINT ( CtlType  )
   /*{{|member_: - MEMBER UINT CtlID }}*/
   _XBST_UINT ( CtlID  )
   /*{{|member_: - MEMBER UINT itemID }}*/
   _XBST_UINT ( itemID  )
   /*{{|member_: - MEMBER HWND hwndItem }}*/
   _XBST_HWND ( hwndItem  )
   /*{{|member_: - MEMBER POINTER32 itemData }}*/
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MCGRIDINFO
            | _slug_: wapist_mcgridinfo
            | class-function: WAPIST_MCGRIDINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MCGRIDINFO structure. Defined as MCGRIDINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MCGRIDINFO, MCGRIDINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MCGRIDINFO** }}*/
XB_BEGIN_STRUCTURE( MCGRIDINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize  )
   /*{{|member_: - MEMBER DWORD dwPart }}*/
   _XBST_DWORD ( dwPart  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
   /*{{|member_: - MEMBER INT iCalendar }}*/
   _XBST_int ( iCalendar  )
   /*{{|member_: - MEMBER INT iRow }}*/
   _XBST_int ( iRow  )
   /*{{|member_: - MEMBER INT iCol }}*/
   _XBST_int ( iCol  )
   /*{{|member_: - MEMBER BOOL bSelected }}*/
   _XBST_BOOL ( bSelected  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} stStart }}*/
   _XBST_SYSTEMTIME ( stStart  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} stEnd }}*/
   _XBST_SYSTEMTIME ( stEnd  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT ( rc  )
   /*{{|member_: - MEMBER POINTER32 pszName }}*/
   _XBST_POINTER32( pszName  )
   /*{{|member_: - MEMBER DWORD cchName }}*/
   _XBST_DWORD( cchName  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MCHITTESTINFO
            | _slug_: wapist_mchittestinfo
            | class-function: WAPIST_MCHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MCHITTESTINFO structure. Defined as MCHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_MCHITTESTINFO, MCHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MCHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( MCHITTESTINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER UINT uHit }}*/
   _XBST_UINT ( uHit  ) // out param
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} st }}*/
   _XBST_SYSTEMTIME ( st  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rc }}*/
   _XBST_RECT ( rc  )
   /*{{|member_: - MEMBER INT iOffset }}*/
   _XBST_int ( iOffset  )
   /*{{|member_: - MEMBER INT iRow }}*/
   _XBST_int ( iRow  )
   /*{{|member_: - MEMBER INT iCol }}*/
   _XBST_int ( iCol  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMDAYSTATE
            | _slug_: wapist_nmdaystate
            | class-function: WAPIST_NMDAYSTATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMDAYSTATE structure. Defined as NMDAYSTATE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMDAYSTATE, NMDAYSTATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMDAYSTATE** }}*/
XB_BEGIN_STRUCTURE( NMDAYSTATE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} stStart }}*/
   _XBST_SYSTEMTIME ( stStart  )
   /*{{|member_: - MEMBER INT cDayState }}*/
   _XBST_int ( cDayState  )
   /*{{|member_: - MEMBER POINTER32 prgDayState }}*/
   _XBST_POINTER32( prgDayState  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMSELCHANGE
            | _slug_: wapist_nmselchange
            | class-function: WAPIST_NMSELCHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMSELCHANGE structure. Defined as NMSELCHANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMSELCHANGE, NMSELCHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMSELCHANGE** }}*/
XB_BEGIN_STRUCTURE( NMSELCHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} stSelStart }}*/
   _XBST_SYSTEMTIME ( stSelStart  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_systemtime> wapist_SYSTEMTIME}} stSelEnd }}*/
   _XBST_SYSTEMTIME ( stSelEnd  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMVIEWCHANGE
            | _slug_: wapist_nmviewchange
            | class-function: WAPIST_NMVIEWCHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMVIEWCHANGE structure. Defined as NMVIEWCHANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMVIEWCHANGE, NMVIEWCHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMVIEWCHANGE** }}*/
XB_BEGIN_STRUCTURE( NMVIEWCHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER DWORD dwOldView }}*/
   _XBST_DWORD ( dwOldView  )
   /*{{|member_: - MEMBER DWORD dwNewView }}*/
   _XBST_DWORD ( dwNewView  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMPGCALCSIZE
            | _slug_: wapist_nmpgcalcsize
            | class-function: WAPIST_NMPGCALCSIZE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMPGCALCSIZE structure. Defined as NMPGCALCSIZE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMPGCALCSIZE, NMPGCALCSIZE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMPGCALCSIZE** }}*/
XB_BEGIN_STRUCTURE( NMPGCALCSIZE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER DWORD dwFlag }}*/
   _XBST_DWORD ( dwFlag  )
   /*{{|member_: - MEMBER INT iWidth }}*/
   _XBST_int ( iWidth  )
   /*{{|member_: - MEMBER INT iHeight }}*/
   _XBST_int ( iHeight  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMPGHOTITEM
            | _slug_: wapist_nmpghotitem
            | class-function: WAPIST_NMPGHOTITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMPGHOTITEM structure. Defined as NMPGHOTITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMPGHOTITEM, NMPGHOTITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMPGHOTITEM** }}*/
XB_BEGIN_STRUCTURE( NMPGHOTITEM )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT idOld }}*/
   _XBST_int ( idOld  )
   /*{{|member_: - MEMBER INT idNew }}*/
   _XBST_int ( idNew  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMPGSCROLL
            | _slug_: wapist_nmpgscroll
            | class-function: WAPIST_NMPGSCROLL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMPGSCROLL structure. Defined as NMPGSCROLL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMPGSCROLL, NMPGSCROLL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMPGSCROLL** }}*/
XB_BEGIN_STRUCTURE( NMPGSCROLL )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER BOOL fwKeys }}*/
   _XBST_BOOL ( fwKeys  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcParent }}*/
   _XBST_RECT ( rcParent  )
   /*{{|member_: - MEMBER INT iDir }}*/
   _XBST_int ( iDir  )
   /*{{|member_: - MEMBER INT iXpos }}*/
   _XBST_int ( iXpos  )
   /*{{|member_: - MEMBER INT iYpos }}*/
   _XBST_int ( iYpos  )
   /*{{|member_: - MEMBER INT iScroll }}*/
   _XBST_int ( iScroll  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PBRANGE
            | _slug_: wapist_pbrange
            | class-function: WAPIST_PBRANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PBRANGE structure. Defined as PBRANGE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_PBRANGE, PBRANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PBRANGE** }}*/
XB_BEGIN_STRUCTURE( PBRANGE )
   /*{{|member_: - MEMBER INT iLow }}*/
   _XBST_int ( iLow  )
   /*{{|member_: - MEMBER INT iHigh }}*/
   _XBST_int ( iHigh  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMREBARSPLITTER
            | _slug_: wapist_nmrebarsplitter
            | class-function: WAPIST_NMREBARSPLITTER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMREBARSPLITTER structure. Defined as NMREBARSPLITTER in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMREBARSPLITTER, NMREBARSPLITTER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMREBARSPLITTER** }}*/
XB_BEGIN_STRUCTURE( NMREBARSPLITTER )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcSizing }}*/
   _XBST_RECT ( rcSizing  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SCROLLBARINFO
            | _slug_: wapist_scrollbarinfo
            | class-function: WAPIST_SCROLLBARINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SCROLLBARINFO structure. Defined as SCROLLBARINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SCROLLBARINFO, SCROLLBARINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SCROLLBARINFO** }}*/
XB_BEGIN_STRUCTURE( SCROLLBARINFO )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD ( cbSize  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcScrollBar }}*/
   _XBST_RECT ( rcScrollBar  )
   /*{{|member_: - MEMBER INT dxyLineButton }}*/
   _XBST_int ( dxyLineButton  )
   /*{{|member_: - MEMBER INT xyThumbTop }}*/
   _XBST_int ( xyThumbTop  )
   /*{{|member_: - MEMBER INT xyThumbBottom }}*/
   _XBST_int ( xyThumbBottom  )
   /*{{|member_: - MEMBER INT reserved }}*/
   _XBST_int ( reserved  )
   /*{{|member_: - MEMBER BINSTR rgstate }}*/
   _XBST_BINSTR( rgstate , (sizeof(DWORD) * (CCHILDREN_SCROLLBAR+1) )  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SCROLLINFO
            | _slug_: wapist_scrollinfo
            | class-function: WAPIST_SCROLLINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SCROLLINFO structure. Defined as SCROLLINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_SCROLLINFO, SCROLLINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SCROLLINFO** }}*/
XB_BEGIN_STRUCTURE( SCROLLINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize  )
   /*{{|member_: - MEMBER UINT fMask }}*/
   _XBST_UINT ( fMask  )
   /*{{|member_: - MEMBER INT nMin }}*/
   _XBST_int  ( nMin  )
   /*{{|member_: - MEMBER INT nMax }}*/
   _XBST_int  ( nMax  )
   /*{{|member_: - MEMBER UINT nPage }}*/
   _XBST_UINT ( nPage  )
   /*{{|member_: - MEMBER INT nPos }}*/
   _XBST_int  ( nPos  )
   /*{{|member_: - MEMBER INT nTrackPos }}*/
   _XBST_int  ( nTrackPos  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_LHITTESTINFO
            | _slug_: wapist_lhittestinfo
            | class-function: WAPIST_LHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi LHITTESTINFO structure. Defined as LHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_LHITTESTINFO, LHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  LHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( LHITTESTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_litem> wapist_LITEM}} item }}*/
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMLINK
            | _slug_: wapist_nmlink
            | class-function: WAPIST_NMLINK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMLINK structure. Defined as NMLINK in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMLINK, NMLINK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMLINK** }}*/
XB_BEGIN_STRUCTURE( NMLINK )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_litem> wapist_LITEM}} item }}*/
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTCKEYDOWN
            | _slug_: wapist_nmtckeydown
            | class-function: WAPIST_NMTCKEYDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTCKEYDOWN structure. Defined as NMTCKEYDOWN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTCKEYDOWN, NMTCKEYDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTCKEYDOWN** }}*/
XB_BEGIN_STRUCTURE( NMTCKEYDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER WORD wVKey }}*/
   _XBST_WORD ( wVKey  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TCHITTESTINFO
            | _slug_: wapist_tchittestinfo
            | class-function: WAPIST_TCHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TCHITTESTINFO structure. Defined as TCHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TCHITTESTINFO, TCHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TCHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( TCHITTESTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TCITEM
            | _slug_: wapist_tcitem
            | class-function: WAPIST_TCITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TCITEM structure. Defined as TCITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TCITEM, TCITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TCITEM** }}*/
XB_BEGIN_STRUCTURE( TCITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER DWORD dwState }}*/
   _XBST_DWORD ( dwState  )
   /*{{|member_: - MEMBER DWORD dwStateMask }}*/
   _XBST_DWORD ( dwStateMask  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TCITEMHEADER
            | _slug_: wapist_tcitemheader
            | class-function: WAPIST_TCITEMHEADER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TCITEMHEADER structure. Defined as TCITEMHEADER in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TCITEMHEADER, TCITEMHEADER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TCITEMHEADER** }}*/
XB_BEGIN_STRUCTURE( TCITEMHEADER )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER UINT lpReserved1 }}*/
   _XBST_UINT ( lpReserved1  )
   /*{{|member_: - MEMBER UINT lpReserved2 }}*/
   _XBST_UINT ( lpReserved2  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COLORMAP
            | _slug_: wapist_colormap
            | class-function: WAPIST_COLORMAP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COLORMAP structure. Defined as COLORMAP in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_COLORMAP, COLORMAP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COLORMAP** }}*/
XB_BEGIN_STRUCTURE( COLORMAP )
   /*{{|member_: - MEMBER COLORREF from }}*/
   _XBST_COLORREF ( from  )
   /*{{|member_: - MEMBER COLORREF to }}*/
   _XBST_COLORREF ( to  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBCUSTOMDRAW
            | _slug_: wapist_nmtbcustomdraw
            | class-function: WAPIST_NMTBCUSTOMDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBCUSTOMDRAW structure. Defined as NMTBCUSTOMDRAW in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTBCUSTOMDRAW, NMTBCUSTOMDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBCUSTOMDRAW** }}*/
XB_BEGIN_STRUCTURE( NMTBCUSTOMDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmcustomdraw> wapist_NMCUSTOMDRAW}} nmcd }}*/
   _XBST_NMCUSTOMDRAW ( nmcd  )
   /*{{|member_: - MEMBER HBRUSH hbrMonoDither }}*/
   _XBST_HBRUSH ( hbrMonoDither  )
   /*{{|member_: - MEMBER HBRUSH hbrLines }}*/
   _XBST_HBRUSH ( hbrLines  )
   /*{{|member_: - MEMBER HPEN hpenLines }}*/
   _XBST_HPEN ( hpenLines  )
   /*{{|member_: - MEMBER COLORREF clrText }}*/
   _XBST_COLORREF ( clrText  )
   /*{{|member_: - MEMBER COLORREF clrMark }}*/
   _XBST_COLORREF ( clrMark  )
   /*{{|member_: - MEMBER COLORREF clrTextHighlight }}*/
   _XBST_COLORREF ( clrTextHighlight  )
   /*{{|member_: - MEMBER COLORREF clrBtnFace }}*/
   _XBST_COLORREF ( clrBtnFace  )
   /*{{|member_: - MEMBER COLORREF clrBtnHighlight }}*/
   _XBST_COLORREF ( clrBtnHighlight  )
   /*{{|member_: - MEMBER COLORREF clrHighlightHotTrack }}*/
   _XBST_COLORREF ( clrHighlightHotTrack  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcText }}*/
   _XBST_RECT ( rcText  )
   /*{{|member_: - MEMBER INT nStringBkMode }}*/
   _XBST_int ( nStringBkMode  )
   /*{{|member_: - MEMBER INT nHLStringBkMode }}*/
   _XBST_int ( nHLStringBkMode  )
   /*{{|member_: - MEMBER INT iListGap }}*/
   _XBST_int ( iListGap  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBDISPINFO
            | _slug_: wapist_nmtbdispinfo
            | class-function: WAPIST_NMTBDISPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBDISPINFO structure. Defined as NMTBDISPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTBDISPINFO, NMTBDISPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBDISPINFO** }}*/
XB_BEGIN_STRUCTURE( NMTBDISPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD ( dwMask  )
   /*{{|member_: - MEMBER INT idCommand }}*/
   _XBST_int ( idCommand  )
   /*{{|member_: - MEMBER POINTER32 lParam }}*/
   _XBST_POINTER32 ( lParam  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchText }}*/
   _XBST_int ( cchText  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBGETINFOTIP
            | _slug_: wapist_nmtbgetinfotip
            | class-function: WAPIST_NMTBGETINFOTIP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBGETINFOTIP structure. Defined as NMTBGETINFOTIP in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTBGETINFOTIP, NMTBGETINFOTIP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBGETINFOTIP** }}*/
XB_BEGIN_STRUCTURE( NMTBGETINFOTIP )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBHOTITEM
            | _slug_: wapist_nmtbhotitem
            | class-function: WAPIST_NMTBHOTITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBHOTITEM structure. Defined as NMTBHOTITEM in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTBHOTITEM, NMTBHOTITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBHOTITEM** }}*/
XB_BEGIN_STRUCTURE( NMTBHOTITEM )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT idOld }}*/
   _XBST_int ( idOld  )
   /*{{|member_: - MEMBER INT idNew }}*/
   _XBST_int ( idNew  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBRESTORE
            | _slug_: wapist_nmtbrestore
            | class-function: WAPIST_NMTBRESTORE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBRESTORE structure. Defined as NMTBRESTORE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTBRESTORE, NMTBRESTORE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBRESTORE** }}*/
XB_BEGIN_STRUCTURE( NMTBRESTORE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} nmhdr }}*/
   _XBST_NMHDR ( nmhdr  )
   /*{{|member_: - MEMBER POINTER32 pData }}*/
   _XBST_POINTER32 ( pData  )
   /*{{|member_: - MEMBER POINTER32 pCurrent }}*/
   _XBST_POINTER32 ( pCurrent  )
   /*{{|member_: - MEMBER UINT cbData }}*/
   _XBST_UINT ( cbData  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER INT cButtons }}*/
   _XBST_int ( cButtons  )
   /*{{|member_: - MEMBER INT cbBytesPerRecord }}*/
   _XBST_int ( cbBytesPerRecord  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tbbutton> wapist_TBBUTTON}} tbButton }}*/
   _XBST_TBBUTTON ( tbButton  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTBSAVE
            | _slug_: wapist_nmtbsave
            | class-function: WAPIST_NMTBSAVE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTBSAVE structure. Defined as NMTBSAVE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTBSAVE, NMTBSAVE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTBSAVE** }}*/
XB_BEGIN_STRUCTURE( NMTBSAVE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER POINTER32 pData }}*/
   _XBST_POINTER32 ( pData  )
   /*{{|member_: - MEMBER POINTER32 pCurrent }}*/
   _XBST_POINTER32 ( pCurrent  )
   /*{{|member_: - MEMBER UINT cbData }}*/
   _XBST_UINT ( cbData  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER INT cButtons }}*/
   _XBST_int ( cButtons  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tbbutton> wapist_TBBUTTON}} tbButton }}*/
   _XBST_TBBUTTON ( tbButton  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTOOLBAR
            | _slug_: wapist_nmtoolbar
            | class-function: WAPIST_NMTOOLBAR
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTOOLBAR structure. Defined as NMTOOLBAR in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTOOLBAR, NMTOOLBAR, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTOOLBAR** }}*/
XB_BEGIN_STRUCTURE( NMTOOLBAR )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iItem }}*/
   _XBST_int ( iItem  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tbbutton> wapist_TBBUTTON}} tbButton }}*/
   _XBST_TBBUTTON ( tbButton  )
   /*{{|member_: - MEMBER INT cchText }}*/
   _XBST_int ( cchText  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rcButton }}*/
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBADDBITMAP
            | _slug_: wapist_tbaddbitmap
            | class-function: WAPIST_TBADDBITMAP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBADDBITMAP structure. Defined as TBADDBITMAP in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBADDBITMAP, TBADDBITMAP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBADDBITMAP** }}*/
XB_BEGIN_STRUCTURE( TBADDBITMAP )
   /*{{|member_: - MEMBER HINSTANCE hInst }}*/
   _XBST_HINSTANCE ( hInst  )
   /*{{|member_: - MEMBER POINTER32 nID }}*/
   _XBST_POINTER32 ( nID  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBBUTTONINFOA
            | _slug_: wapist_tbbuttoninfoa
            | class-function: WAPIST_TBBUTTONINFOA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBBUTTONINFOA structure. Defined as TBBUTTONINFOA in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBBUTTONINFOA, TBBUTTONINFOA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBBUTTONINFOA** }}*/
XB_BEGIN_STRUCTURE( TBBUTTONINFOA )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT  ( cbSize  )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD  ( dwMask  )
   /*{{|member_: - MEMBER INT idCommand }}*/
   _XBST_int  ( idCommand  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int  ( iImage  )
   /*{{|member_: - MEMBER BYTE fsState }}*/
   _XBST_BYTE  ( fsState  )
   /*{{|member_: - MEMBER BYTE fsStyle }}*/
   _XBST_BYTE  ( fsStyle  )
   /*{{|member_: - MEMBER WORD cx }}*/
   _XBST_WORD  ( cx  )
   /*{{|member_: - MEMBER POINTER32 lParam }}*/
   _XBST_POINTER32  ( lParam  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR  ( pszText  )
   /*{{|member_: - MEMBER INT cchText }}*/
   _XBST_int  ( cchText  )
   /*{{|member_: - MEMBER INT iImageLabel }}*/
   _XBST_int  ( iImageLabel  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBINSERTMARK
            | _slug_: wapist_tbinsertmark
            | class-function: WAPIST_TBINSERTMARK
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBINSERTMARK structure. Defined as TBINSERTMARK in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBINSERTMARK, TBINSERTMARK, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBINSERTMARK** }}*/
XB_BEGIN_STRUCTURE( TBINSERTMARK )
   /*{{|member_: - MEMBER INT iButton }}*/
   _XBST_int ( iButton  )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBMETRICS
            | _slug_: wapist_tbmetrics
            | class-function: WAPIST_TBMETRICS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBMETRICS structure. Defined as TBMETRICS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBMETRICS, TBMETRICS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBMETRICS** }}*/
XB_BEGIN_STRUCTURE( TBMETRICS )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT ( cbSize  )
   /*{{|member_: - MEMBER DWORD dwMask }}*/
   _XBST_DWORD ( dwMask  )
   /*{{|member_: - MEMBER INT cxPad }}*/
   _XBST_int ( cxPad  )
   /*{{|member_: - MEMBER INT cyPad }}*/
   _XBST_int ( cyPad  )
   /*{{|member_: - MEMBER INT cxBarPad }}*/
   _XBST_int ( cxBarPad  )
   /*{{|member_: - MEMBER INT cyBarPad }}*/
   _XBST_int ( cyBarPad  )
   /*{{|member_: - MEMBER INT cxButtonSpacing }}*/
   _XBST_int ( cxButtonSpacing  )
   /*{{|member_: - MEMBER INT cyButtonSpacing }}*/
   _XBST_int ( cyButtonSpacing  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBREPLACEBITMAP
            | _slug_: wapist_tbreplacebitmap
            | class-function: WAPIST_TBREPLACEBITMAP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBREPLACEBITMAP structure. Defined as TBREPLACEBITMAP in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_TBREPLACEBITMAP, TBREPLACEBITMAP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBREPLACEBITMAP** }}*/
XB_BEGIN_STRUCTURE( TBREPLACEBITMAP )
   /*{{|member_: - MEMBER HINSTANCE hInstOld }}*/
   _XBST_HINSTANCE ( hInstOld  )
   /*{{|member_: - MEMBER POINTER32 nIDOld }}*/
   _XBST_POINTER32 ( nIDOld  )
   /*{{|member_: - MEMBER HINSTANCE hInstNew }}*/
   _XBST_HINSTANCE ( hInstNew  )
   /*{{|member_: - MEMBER POINTER32 nIDNew }}*/
   _XBST_POINTER32 ( nIDNew  )
   /*{{|member_: - MEMBER INT nButtons }}*/
   _XBST_int ( nButtons  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TBSAVEPARAMS
            | _slug_: wapist_tbsaveparams
            | class-function: WAPIST_TBSAVEPARAMS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TBSAVEPARAMS structure. Defined as TBSAVEPARAMS in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TBSAVEPARAMS, TBSAVEPARAMS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TBSAVEPARAMS** }}*/
XB_BEGIN_STRUCTURE( TBSAVEPARAMS )
   /*{{|member_: - MEMBER HANDLE hkr }}*/
   _XBST_HANDLE ( hkr  )
   /*{{|member_: - MEMBER LPSTR pszSubKey }}*/
   _XBST_LPSTR ( pszSubKey  )
   /*{{|member_: - MEMBER LPSTR pszValueName }}*/
   _XBST_LPSTR ( pszValueName  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTTCUSTOMDRAW
            | _slug_: wapist_nmttcustomdraw
            | class-function: WAPIST_NMTTCUSTOMDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTTCUSTOMDRAW structure. Defined as NMTTCUSTOMDRAW in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTTCUSTOMDRAW, NMTTCUSTOMDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTTCUSTOMDRAW** }}*/
XB_BEGIN_STRUCTURE( NMTTCUSTOMDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmcustomdraw> wapist_NMCUSTOMDRAW}} nmcd }}*/
   _XBST_NMCUSTOMDRAW ( nmcd  )
   /*{{|member_: - MEMBER UINT uDrawFlags }}*/
   _XBST_UINT ( uDrawFlags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTTDISPINFO
            | _slug_: wapist_nmttdispinfo
            | class-function: WAPIST_NMTTDISPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTTDISPINFO structure. Defined as NMTTDISPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTTDISPINFO, NMTTDISPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTTDISPINFO** }}*/
XB_BEGIN_STRUCTURE( NMTTDISPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR      ( hdr  )
   /*{{|member_: - MEMBER LPSTR lpszText }}*/
   _XBST_LPSTR     ( lpszText  )
   /*{{|member_: - MEMBER BYTE szText }}*/
   _XBST_TCHAR       ( szText[80]  )
   /*{{|member_: - MEMBER HINSTANCE hinst }}*/
   _XBST_HINSTANCE  ( hinst  )
   /*{{|member_: - MEMBER UINT uFlags }}*/
   _XBST_UINT       ( uFlags  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM     ( lParam  )
   /*{{|member_: - MEMBER HBITMAP hbmp }}*/
   _XBST_HBITMAP ( hbmp  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TOOLINFO
            | _slug_: wapist_toolinfo
            | class-function: WAPIST_TOOLINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TOOLINFO structure. Defined as TOOLINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TOOLINFO, TOOLINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TOOLINFO** }}*/
XB_BEGIN_STRUCTURE( TOOLINFO )
   /*{{|member_: - MEMBER UINT cbSize }}*/
   _XBST_UINT      ( cbSize  )
   /*{{|member_: - MEMBER UINT uFlags }}*/
   _XBST_UINT      ( uFlags  )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND      ( hwnd  )
   /*{{|member_: - MEMBER POINTER32 uId }}*/
   _XBST_POINTER32  ( uId  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_rect> wapist_RECT}} rect }}*/
   _XBST_RECT      ( rect  )
   /*{{|member_: - MEMBER HINSTANCE hinst }}*/
   _XBST_HINSTANCE ( hinst  )
   /*{{|member_: - MEMBER LPSTR lpszText }}*/
   _XBST_LPSTR    ( lpszText  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
   /*{{|member_: - MEMBER POINTER32 lpReserved }}*/
   _XBST_POINTER32 ( lpReserved  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TTGETTITLE
            | _slug_: wapist_ttgettitle
            | class-function: WAPIST_TTGETTITLE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TTGETTITLE structure. Defined as TTGETTITLE in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TTGETTITLE, TTGETTITLE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TTGETTITLE** }}*/
XB_BEGIN_STRUCTURE( TTGETTITLE )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   _XBST_DWORD ( dwSize  )
   /*{{|member_: - MEMBER UINT uTitleBitmap }}*/
   _XBST_UINT ( uTitleBitmap  )
   /*{{|member_: - MEMBER UINT cch }}*/
   _XBST_UINT ( cch  )
   /*{{|member_: - MEMBER POINTER32 pszTitle }}*/
   _XBST_POINTER32 ( pszTitle  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TTHITTESTINFO
            | _slug_: wapist_tthittestinfo
            | class-function: WAPIST_TTHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TTHITTESTINFO structure. Defined as TTHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TTHITTESTINFO, TTHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TTHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( TTHITTESTINFO )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND ( hwnd  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_toolinfo> wapist_TOOLINFO}} ti }}*/
   _XBST_TOOLINFO ( ti  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTREEVIEW
            | _slug_: wapist_nmtreeview
            | class-function: WAPIST_NMTREEVIEW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTREEVIEW structure. Defined as NMTREEVIEW in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTREEVIEW, NMTREEVIEW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTREEVIEW** }}*/
XB_BEGIN_STRUCTURE( NMTREEVIEW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER UINT action }}*/
   _XBST_UINT ( action  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitem> wapist_TVITEM}} itemOld }}*/
   _XBST_TVITEM ( itemOld  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitem> wapist_TVITEM}} itemNew }}*/
   _XBST_TVITEM ( itemNew  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} ptDrag }}*/
   _XBST_POINT ( ptDrag  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVASYNCDRAW
            | _slug_: wapist_nmtvasyncdraw
            | class-function: WAPIST_NMTVASYNCDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVASYNCDRAW structure. Defined as NMTVASYNCDRAW in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTVASYNCDRAW, NMTVASYNCDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVASYNCDRAW** }}*/
XB_BEGIN_STRUCTURE( NMTVASYNCDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER POINTER32 pimldp }}*/
   _XBST_POINTER32 ( pimldp  )
   /*{{|member_: - MEMBER HRESULT hr }}*/
   _XBST_HRESULT ( hr  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
   /*{{|member_: - MEMBER DWORD dwRetFlags }}*/
   _XBST_DWORD ( dwRetFlags  )
   /*{{|member_: - MEMBER INT iRetImageIndex }}*/
   _XBST_int ( iRetImageIndex  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVCUSTOMDRAW
            | _slug_: wapist_nmtvcustomdraw
            | class-function: WAPIST_NMTVCUSTOMDRAW
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVCUSTOMDRAW structure. Defined as NMTVCUSTOMDRAW in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTVCUSTOMDRAW, NMTVCUSTOMDRAW, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVCUSTOMDRAW** }}*/
XB_BEGIN_STRUCTURE( NMTVCUSTOMDRAW )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmcustomdraw> wapist_NMCUSTOMDRAW}} nmcd }}*/
   _XBST_NMCUSTOMDRAW ( nmcd  )
   /*{{|member_: - MEMBER COLORREF clrText }}*/
   _XBST_COLORREF ( clrText  )
   /*{{|member_: - MEMBER COLORREF clrTextBk }}*/
   _XBST_COLORREF ( clrTextBk  )
   /*{{|member_: - MEMBER INT iLevel }}*/
   _XBST_int ( iLevel  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVDISPINFO
            | _slug_: wapist_nmtvdispinfo
            | class-function: WAPIST_NMTVDISPINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVDISPINFO structure. Defined as NMTVDISPINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTVDISPINFO, NMTVDISPINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVDISPINFO** }}*/
XB_BEGIN_STRUCTURE( NMTVDISPINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitem> wapist_TVITEM}} item }}*/
   _XBST_TVITEM ( item  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVDISPINFOEX
            | _slug_: wapist_nmtvdispinfoex
            | class-function: WAPIST_NMTVDISPINFOEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVDISPINFOEX structure. Defined as NMTVDISPINFOEX in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTVDISPINFOEX, NMTVDISPINFOEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVDISPINFOEX** }}*/
XB_BEGIN_STRUCTURE( NMTVDISPINFOEX )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitemex> wapist_TVITEMEX}} item }}*/
   _XBST_TVITEMEX ( item  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVGETINFOTIP
            | _slug_: wapist_nmtvgetinfotip
            | class-function: WAPIST_NMTVGETINFOTIP
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVGETINFOTIP structure. Defined as NMTVGETINFOTIP in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTVGETINFOTIP, NMTVGETINFOTIP, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVGETINFOTIP** }}*/
XB_BEGIN_STRUCTURE( NMTVGETINFOTIP )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   _XBST_LPSTR ( pszText  )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVITEMCHANGE
            | _slug_: wapist_nmtvitemchange
            | class-function: WAPIST_NMTVITEMCHANGE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVITEMCHANGE structure. Defined as NMTVITEMCHANGE in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTVITEMCHANGE, NMTVITEMCHANGE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVITEMCHANGE** }}*/
XB_BEGIN_STRUCTURE( NMTVITEMCHANGE )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER UINT uChanged }}*/
   _XBST_UINT ( uChanged  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
   /*{{|member_: - MEMBER UINT uStateNew }}*/
   _XBST_UINT ( uStateNew  )
   /*{{|member_: - MEMBER UINT uStateOld }}*/
   _XBST_UINT ( uStateOld  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVKEYDOWN
            | _slug_: wapist_nmtvkeydown
            | class-function: WAPIST_NMTVKEYDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVKEYDOWN structure. Defined as NMTVKEYDOWN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMTVKEYDOWN, NMTVKEYDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVKEYDOWN** }}*/
XB_BEGIN_STRUCTURE( NMTVKEYDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER WORD wVKey }}*/
   _XBST_WORD ( wVKey  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMTVSTATEIMAGECHANGING
            | _slug_: wapist_nmtvstateimagechanging
            | class-function: WAPIST_NMTVSTATEIMAGECHANGING
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMTVSTATEIMAGECHANGING structure. Defined as NMTVSTATEIMAGECHANGING in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_NMTVSTATEIMAGECHANGING, NMTVSTATEIMAGECHANGING, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMTVSTATEIMAGECHANGING** }}*/
XB_BEGIN_STRUCTURE( NMTVSTATEIMAGECHANGING )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER HANDLE hti }}*/
   _XBST_HANDLE ( hti  )
   /*{{|member_: - MEMBER INT iOldStateImageIndex }}*/
   _XBST_int ( iOldStateImageIndex  )
   /*{{|member_: - MEMBER INT iNewStateImageIndex }}*/
   _XBST_int ( iNewStateImageIndex  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVGETITEMPARTRECTINFO
            | _slug_: wapist_tvgetitempartrectinfo
            | class-function: WAPIST_TVGETITEMPARTRECTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVGETITEMPARTRECTINFO structure. Defined as TVGETITEMPARTRECTINFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_TVGETITEMPARTRECTINFO, TVGETITEMPARTRECTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVGETITEMPARTRECTINFO** }}*/
XB_BEGIN_STRUCTURE( TVGETITEMPARTRECTINFO )
   /*{{|member_: - MEMBER HANDLE hti }}*/
   _XBST_HANDLE ( hti  )
   /*{{|member_: - MEMBER POINTER32 prc }}*/
   _XBST_POINTER32 ( prc  )
   /*{{|member_: - MEMBER INT partID }}*/
   _XBST_int ( partID  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVHITTESTINFO
            | _slug_: wapist_tvhittestinfo
            | class-function: WAPIST_TVHITTESTINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVHITTESTINFO structure. Defined as TVHITTESTINFO in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TVHITTESTINFO, TVHITTESTINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVHITTESTINFO** }}*/
XB_BEGIN_STRUCTURE( TVHITTESTINFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_point> wapist_POINT}} pt }}*/
   _XBST_POINT ( pt  )
   /*{{|member_: - MEMBER UINT flags }}*/
   _XBST_UINT ( flags  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVINSERTSTRUCT
            | _slug_: wapist_tvinsertstruct
            | class-function: WAPIST_TVINSERTSTRUCT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVINSERTSTRUCTA structure. Defined as TVINSERTSTRUCT in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvinsertstructa
            | _kw_: WAPIST_TVINSERTSTRUCT, TVINSERTSTRUCT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVINSERTSTRUCT** }}*/
XB_BEGIN_STRUCTURE( TVINSERTSTRUCT )
   /*{{|member_: - MEMBER HANDLE hParent }}*/
   _XBST_HANDLE ( hParent  )
   /*{{|member_: - MEMBER HANDLE hInsertAfter }}*/
   _XBST_HANDLE ( hInsertAfter  )
pc->GwstBeginUnion();
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitemex> wapist_TVITEMEX}} itemex }}*/
   _XBST_TVITEMEX ( itemex  )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_tvitem> wapist_TVITEM}} item }}*/
   _XBST_TVITEM ( item  )
pc->GwstEndUnion();
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVITEM
            | _slug_: wapist_tvitem
            | class-function: WAPIST_TVITEM
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVITEM structure. Defined as TVITEM in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvitema
            | _kw_: WAPIST_TVITEM, TVITEM, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVITEM** }}*/
XB_BEGIN_STRUCTURE( TVITEM )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT ( mask  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT ( state  )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT ( stateMask  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   /*{{|member_: - MEMBER DYNSZ cText |desc_: Helper member mapped over ::pszText. }}*/
   _XBST_LPSTR_DYNSZ ( pszText  , cText )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int ( iImage  )
   /*{{|member_: - MEMBER INT iSelectedImage }}*/
   _XBST_int ( iSelectedImage  )
   /*{{|member_: - MEMBER INT cChildren }}*/
   _XBST_int ( cChildren  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVITEMEX
            | _slug_: wapist_tvitemex
            | class-function: WAPIST_TVITEMEX
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVITEMEX structure. Defined as TVITEMEX in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-tvitemexa
            | _kw_: WAPIST_TVITEMEX, TVITEMEX, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVITEMEX** }}*/
XB_BEGIN_STRUCTURE( TVITEMEX )
   /*{{|member_: - MEMBER UINT mask }}*/
   _XBST_UINT      ( mask  )
   /*{{|member_: - MEMBER HANDLE hItem }}*/
   _XBST_HANDLE ( hItem  )
   /*{{|member_: - MEMBER UINT state }}*/
   _XBST_UINT      ( state  )
   /*{{|member_: - MEMBER UINT stateMask }}*/
   _XBST_UINT      ( stateMask  )
   /*{{|member_: - MEMBER LPSTR pszText }}*/
   /*{{|member_: - MEMBER DYNSZ cText |desc_: Helper member mapped over ::pszText. }}*/
   _XBST_LPSTR_DYNSZ ( pszText  , cText )
   /*{{|member_: - MEMBER INT cchTextMax }}*/
   _XBST_int       ( cchTextMax  )
   /*{{|member_: - MEMBER INT iImage }}*/
   _XBST_int       ( iImage  )
   /*{{|member_: - MEMBER INT iSelectedImage }}*/
   _XBST_int       ( iSelectedImage  )
   /*{{|member_: - MEMBER INT cChildren }}*/
   _XBST_int       ( cChildren  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM    ( lParam  )
   /*{{|member_: - MEMBER INT iIntegral }}*/
   _XBST_int       ( iIntegral  )
   /*{{|member_: - MEMBER UINT uStateEx }}*/
   _XBST_UINT      ( uStateEx  )
   /*{{|member_: - MEMBER HWND hwnd }}*/
   _XBST_HWND      ( hwnd  )
   /*{{|member_: - MEMBER INT iExpandedImage }}*/
   _XBST_int       ( iExpandedImage  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TVSORTCB
            | _slug_: wapist_tvsortcb
            | class-function: WAPIST_TVSORTCB
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TVSORTCB structure. Defined as TVSORTCB in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_TVSORTCB, TVSORTCB, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TVSORTCB** }}*/
XB_BEGIN_STRUCTURE( TVSORTCB )
   /*{{|member_: - MEMBER HANDLE hParent }}*/
   _XBST_HANDLE ( hParent  )
   /*{{|member_: - MEMBER POINTER32 lpfnCompare }}*/
   _XBST_POINTER32 ( lpfnCompare  )
   /*{{|member_: - MEMBER LPARAM lParam }}*/
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_NMUPDOWN
            | _slug_: wapist_nmupdown
            | class-function: WAPIST_NMUPDOWN
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi NMUPDOWN structure. Defined as NMUPDOWN in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_NMUPDOWN, NMUPDOWN, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  NMUPDOWN** }}*/
XB_BEGIN_STRUCTURE( NMUPDOWN )
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_nmhdr> wapist_NMHDR}} hdr }}*/
   _XBST_NMHDR ( hdr  )
   /*{{|member_: - MEMBER INT iPos }}*/
   _XBST_int ( iPos  )
   /*{{|member_: - MEMBER INT iDelta }}*/
   _XBST_int ( iDelta  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_UDACCEL
            | _slug_: wapist_udaccel
            | class-function: WAPIST_UDACCEL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi UDACCEL structure. Defined as UDACCEL in ot4xb_wapist_map.ch.
            | _kw_: WAPIST_UDACCEL, UDACCEL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  UDACCEL** }}*/
XB_BEGIN_STRUCTURE( UDACCEL )
   /*{{|member_: - MEMBER UINT nSec }}*/
   _XBST_UINT ( nSec  )
   /*{{|member_: - MEMBER UINT nInc }}*/
   _XBST_UINT ( nInc  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_URL_COMPONENTS
            | _slug_: wapist_url_components
            | class-function: WAPIST_URL_COMPONENTS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi URL_COMPONENTSA structure. Defined as URL_COMPONENTS in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-url_componentsa
            | _kw_: WAPIST_URL_COMPONENTS, URL_COMPONENTS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  URL_COMPONENTS** }}*/
XB_BEGIN_STRUCTURE( URL_COMPONENTS )
/*{{|member_: - MEMBER DWORD dwStructSize }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwStructSize      ));  _XBST_DWORD( dwStructSize       )
/*{{|member_: - MEMBER LPSTR lpszScheme }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszScheme        ));  _XBST_LPSTR( lpszScheme         )
/*{{|member_: - MEMBER DWORD dwSchemeLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwSchemeLength    ));  _XBST_DWORD( dwSchemeLength     )
/*{{|member_: - MEMBER INT nScheme }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , nScheme           ));  _XBST_int  ( nScheme            )
/*{{|member_: - MEMBER LPSTR lpszHostName }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszHostName      ));  _XBST_LPSTR( lpszHostName       )
/*{{|member_: - MEMBER DWORD dwHostNameLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwHostNameLength  ));  _XBST_DWORD( dwHostNameLength   )
/*{{|member_: - MEMBER WORD nPort }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , nPort             ));  _XBST_WORD ( nPort              )
/*{{|member_: - MEMBER LPSTR lpszUserName }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszUserName      ));  _XBST_LPSTR( lpszUserName       )
/*{{|member_: - MEMBER DWORD dwUserNameLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwUserNameLength  ));  _XBST_DWORD( dwUserNameLength   )
/*{{|member_: - MEMBER LPSTR lpszPassword }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszPassword      ));  _XBST_LPSTR( lpszPassword       )
/*{{|member_: - MEMBER DWORD dwPasswordLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwPasswordLength  ));  _XBST_DWORD( dwPasswordLength   )
/*{{|member_: - MEMBER LPSTR lpszUrlPath }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszUrlPath       ));  _XBST_LPSTR( lpszUrlPath        )
/*{{|member_: - MEMBER DWORD dwUrlPathLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwUrlPathLength   ));  _XBST_DWORD( dwUrlPathLength    )
/*{{|member_: - MEMBER LPSTR lpszExtraInfo }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , lpszExtraInfo     ));  _XBST_LPSTR( lpszExtraInfo      )
/*{{|member_: - MEMBER DWORD dwExtraInfoLength }}*/
pc->GwstSetOffset(FIELD_OFFSET( URL_COMPONENTS , dwExtraInfoLength ));  _XBST_DWORD( dwExtraInfoLength  )
pc->GwstSetOffset(sizeof( URL_COMPONENTS) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_ASYNC_RESULT
            | _slug_: wapist_internet_async_result
            | class-function: WAPIST_INTERNET_ASYNC_RESULT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNET_ASYNC_RESULT structure. Defined as INTERNET_ASYNC_RESULT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_ASYNC_RESULT, INTERNET_ASYNC_RESULT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_ASYNC_RESULT** }}*/
XB_BEGIN_STRUCTURE( INTERNET_ASYNC_RESULT )
   /*{{|member_: - MEMBER DWORD dwResult }}*/
   _XBST_DWORD( dwResult );
   /*{{|member_: - MEMBER DWORD dwError }}*/
   _XBST_DWORD( dwError  );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO
            | _slug_: wapist_internet_diagnostic_socket_info
            | class-function: WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_DIAGNOSTIC_SOCKET_INFO structure. Defined as
              INTERNET_DIAGNOSTIC_SOCKET_INFO in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_DIAGNOSTIC_SOCKET_INFO, INTERNET_DIAGNOSTIC_SOCKET_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_DIAGNOSTIC_SOCKET_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_DIAGNOSTIC_SOCKET_INFO )
   /*{{|member_: - MEMBER DWORD Socket }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Socket    )); _XBST_DWORD( Socket      );
   /*{{|member_: - MEMBER DWORD SourcePort }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,SourcePort)); _XBST_DWORD( SourcePort  );
   /*{{|member_: - MEMBER DWORD DestPort }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,DestPort  )); _XBST_DWORD( DestPort    );
   /*{{|member_: - MEMBER DWORD Flags }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Flags     )); _XBST_DWORD( Flags       );
   pc->GwstSetOffset(sizeof(INTERNET_DIAGNOSTIC_SOCKET_INFO));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_PROXY_INFO
            | _slug_: wapist_internet_proxy_info
            | class-function: WAPIST_INTERNET_PROXY_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_PROXY_INFO structure. Defined as INTERNET_PROXY_INFO in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_proxy_info
            | _kw_: WAPIST_INTERNET_PROXY_INFO, INTERNET_PROXY_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_PROXY_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_PROXY_INFO )
   /*{{|member_: - MEMBER DWORD dwAccessType }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,dwAccessType   )); _XBST_DWORD      ( dwAccessType                 );
   /*{{|member_: - MEMBER LPSTR lpszProxy }}*/
   /*{{|member_: - MEMBER DYNSZ cProxy |desc_: Helper member mapped over ::lpszProxy. }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxy      )); _XBST_LPSTR_DYNSZ( lpszProxy      , cProxy      );
   /*{{|member_: - MEMBER LPSTR lpszProxyBypass }}*/
   /*{{|member_: - MEMBER DYNSZ cProxyBypass |desc_: Helper member mapped over ::lpszProxyBypass. }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxyBypass)); _XBST_LPSTR_DYNSZ( lpszProxyBypass, cProxyBypass);
   pc->GwstSetOffset(sizeof(INTERNET_PROXY_INFO));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_PER_CONN_OPTION___VALUE
            | _slug_: wapist_internet_per_conn_option___value
            | class-function: WAPIST_INTERNET_PER_CONN_OPTION___VALUE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Auxiliary wrapper for the INTERNET_PER_CONN_OPTION Value union.
            | _kw_: WAPIST_INTERNET_PER_CONN_OPTION___VALUE, INTERNET_PER_CONN_OPTION___VALUE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_PER_CONN_OPTION___VALUE** }}*/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION___VALUE )
   /*{{|member_: - MEMBER DWORD dwValue }}*/
   _XBST_DWORD        ( dwValue   );
   /*{{|member_: - MEMBER LPSTR pszValue }}*/
   /*{{|member_: - MEMBER DYNSZ cValue |desc_: Helper member mapped over ::pszValue. }}*/
   _XBST_LPSTR_DYNSZ  ( pszValue  , cValue );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftValue }}*/
   _XBST_FILETIME     ( ftValue   );
   pc->GwstSetOffset( RTL_FIELD_SIZE(INTERNET_PER_CONN_OPTION, Value) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_PER_CONN_OPTION
            | _slug_: wapist_internet_per_conn_option
            | class-function: WAPIST_INTERNET_PER_CONN_OPTION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_PER_CONN_OPTIONA structure. Defined as INTERNET_PER_CONN_OPTION
              in ot4xb_wapist_map.ch.
           | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_per_conn_optiona
           | _kw_: WAPIST_INTERNET_PER_CONN_OPTION, INTERNET_PER_CONN_OPTION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_PER_CONN_OPTION** }}*/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION )
   /*{{|member_: - MEMBER DWORD dwOption }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,dwOption));   _XBST_DWORD(                            dwOption            );
   /*{{|member_: - MEMBER @ {{ilink: <slug wapist_internet_per_conn_option___value> wapist_INTERNET_PER_CONN_OPTION___VALUE}} Value }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,Value   ));   _XBST_INTERNET_PER_CONN_OPTION___VALUE( Value               );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------

/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_PER_CONN_OPTION_LIST
            | _slug_: wapist_internet_per_conn_option_list
            | class-function: WAPIST_INTERNET_PER_CONN_OPTION_LIST
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_PER_CONN_OPTION_LISTA structure. Defined as
              INTERNET_PER_CONN_OPTION_LIST in ot4xb_wapist_map.ch.
      | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_per_conn_option_lista
      | _kw_: WAPIST_INTERNET_PER_CONN_OPTION_LIST, INTERNET_PER_CONN_OPTION_LIST, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_PER_CONN_OPTION_LIST** }}*/
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION_LIST )
   /*{{|member_: - MEMBER DWORD dwSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwSize        )); _XBST_DWORD     ( dwSize        );
   /*{{|member_: - MEMBER LPSTR pszConnection }}*/
   /*{{|member_: - MEMBER DYNSZ cConnection |desc_: Helper member mapped over ::pszConnection. }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pszConnection )); _XBST_LPSTR_DYNSZ( pszConnection , cConnection);
   /*{{|member_: - MEMBER DWORD dwOptionCount }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionCount )); _XBST_DWORD     ( dwOptionCount );
   /*{{|member_: - MEMBER DWORD dwOptionError }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionError )); _XBST_DWORD     ( dwOptionError );
   /*{{|member_: - MEMBER POINTER32 pOptions }}*/
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pOptions      )); _XBST_POINTER32 ( pOptions      );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION_LIST) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_VERSION_INFO
            | _slug_: wapist_internet_version_info
            | class-function: WAPIST_INTERNET_VERSION_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNET_VERSION_INFO structure. Defined as INTERNET_VERSION_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_VERSION_INFO, INTERNET_VERSION_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_VERSION_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_VERSION_INFO )
   /*{{|member_: - MEMBER DWORD dwMajorVersion }}*/
   _XBST_DWORD ( dwMajorVersion  )
   /*{{|member_: - MEMBER DWORD dwMinorVersion }}*/
   _XBST_DWORD ( dwMinorVersion  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_HTTP_VERSION_INFO
            | _slug_: wapist_http_version_info
            | class-function: WAPIST_HTTP_VERSION_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi HTTP_VERSION_INFO structure. Defined as HTTP_VERSION_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_HTTP_VERSION_INFO, HTTP_VERSION_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  HTTP_VERSION_INFO** }}*/
XB_BEGIN_STRUCTURE( HTTP_VERSION_INFO )
   /*{{|member_: - MEMBER DWORD dwMajorVersion }}*/
   _XBST_DWORD( dwMajorVersion )
   /*{{|member_: - MEMBER DWORD dwMinorVersion }}*/
   _XBST_DWORD( dwMinorVersion )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_CONNECTED_INFO
            | _slug_: wapist_internet_connected_info
            | class-function: WAPIST_INTERNET_CONNECTED_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNET_CONNECTED_INFO structure. Defined as INTERNET_CONNECTED_INFO in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_CONNECTED_INFO, INTERNET_CONNECTED_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_CONNECTED_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_CONNECTED_INFO )
   /*{{|member_: - MEMBER DWORD dwConnectedState }}*/
   _XBST_DWORD( dwConnectedState )
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags          )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_CERTIFICATE_INFO
            | _slug_: wapist_internet_certificate_info
            | class-function: WAPIST_INTERNET_CERTIFICATE_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_CERTIFICATE_INFO structure. Defined as INTERNET_CERTIFICATE_INFO
              in ot4xb_wapist_map.ch.
           | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_certificate_info
           | _kw_: WAPIST_INTERNET_CERTIFICATE_INFO, INTERNET_CERTIFICATE_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_CERTIFICATE_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_CERTIFICATE_INFO )
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftExpiry }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , ftExpiry               ));_XBST_FILETIME ( ftExpiry               );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftStart }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , ftStart                ));_XBST_FILETIME ( ftStart                );
   /*{{|member_: - MEMBER LPSTR lpszSubjectInfo }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszSubjectInfo        ));_XBST_LPSTR   ( lpszSubjectInfo        );
   /*{{|member_: - MEMBER LPSTR lpszIssuerInfo }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszIssuerInfo         ));_XBST_LPSTR   ( lpszIssuerInfo         );
   /*{{|member_: - MEMBER LPSTR lpszProtocolName }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszProtocolName       ));_XBST_LPSTR   ( lpszProtocolName       );
   /*{{|member_: - MEMBER LPSTR lpszSignatureAlgName }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszSignatureAlgName   ));_XBST_LPSTR   ( lpszSignatureAlgName   );
   /*{{|member_: - MEMBER LPSTR lpszEncryptionAlgName }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , lpszEncryptionAlgName  ));_XBST_LPSTR   ( lpszEncryptionAlgName  );
   /*{{|member_: - MEMBER DWORD dwKeySize }}*/
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_CERTIFICATE_INFO , dwKeySize              ));_XBST_DWORD    ( dwKeySize              );
   pc->GwstSetOffset( sizeof( INTERNET_CERTIFICATE_INFO) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_BUFFERS
            | _slug_: wapist_internet_buffers
            | class-function: WAPIST_INTERNET_BUFFERS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_BUFFERSA structure.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_buffersa
            | _kw_: WAPIST_INTERNET_BUFFERS, INTERNET_BUFFERS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_BUFFERS** }}*/
XB_BEGIN_STRUCTURE( INTERNET_BUFFERS )
   /*{{|member_: - MEMBER DWORD dwStructSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwStructSize      ));   _XBST_DWORD      ( dwStructSize      );
   /*{{|member_: - MEMBER POINTER32 pNext }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , Next              ));   _XBST_POINTER32  ( pNext             );
   /*{{|member_: - MEMBER LPSTR lpcszHeader }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , lpcszHeader       ));   _XBST_LPSTR     ( lpcszHeader       );
   /*{{|member_: - MEMBER DWORD dwHeadersLength }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwHeadersLength   ));   _XBST_DWORD      ( dwHeadersLength   );
   /*{{|member_: - MEMBER DWORD dwHeadersTotal }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwHeadersTotal    ));   _XBST_DWORD      ( dwHeadersTotal    );
   /*{{|member_: - MEMBER LPVOID lpvBuffer }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , lpvBuffer         ));   _XBST_LPVOID     ( lpvBuffer         );
   /*{{|member_: - MEMBER DWORD dwBufferLength }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwBufferLength    ));   _XBST_DWORD      ( dwBufferLength    );
   /*{{|member_: - MEMBER DWORD dwBufferTotal }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwBufferTotal     ));   _XBST_DWORD      ( dwBufferTotal     );
   /*{{|member_: - MEMBER DWORD dwOffsetLow }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwOffsetLow       ));   _XBST_DWORD      ( dwOffsetLow       );
   /*{{|member_: - MEMBER DWORD dwOffsetHigh }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_BUFFERS , dwOffsetHigh      ));   _XBST_DWORD      ( dwOffsetHigh      );
   pc->GwstSetOffset( sizeof( INTERNET_BUFFERS) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INCOMINGCOOKIESTATE
            | _slug_: wapist_incomingcookiestate
            | class-function: WAPIST_INCOMINGCOOKIESTATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet IncomingCookieState structure. Defined as IncomingCookieState in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INCOMINGCOOKIESTATE, INCOMINGCOOKIESTATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INCOMINGCOOKIESTATE** }}*/
XB_BEGIN_STRUCTURE( INCOMINGCOOKIESTATE )
    /*{{|member_: - MEMBER INT cSession }}*/
    _XBST_int( cSession      );
   /*{{|member_: - MEMBER INT cPersistent }}*/
   _XBST_int   ( cPersistent   );
   /*{{|member_: - MEMBER INT cAccepted }}*/
   _XBST_int   ( cAccepted     );
   /*{{|member_: - MEMBER INT cLeashed }}*/
   _XBST_int   ( cLeashed      );
   /*{{|member_: - MEMBER INT cDowngraded }}*/
   _XBST_int   ( cDowngraded   );
   /*{{|member_: - MEMBER INT cBlocked }}*/
   _XBST_int   ( cBlocked      );
   /*{{|member_: - MEMBER LPSTR pszLocation }}*/
   /*{{|member_: - MEMBER DYNSZ cLocation |desc_: Helper member mapped over ::pszLocation. }}*/
   _XBST_LPSTR_DYNSZ ( pszLocation   , cLocation);
   pc->GwstSetOffset( sizeof( IncomingCookieState) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_OUTGOINGCOOKIESTATE
            | _slug_: wapist_outgoingcookiestate
            | class-function: WAPIST_OUTGOINGCOOKIESTATE
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet OutgoingCookieState structure. Defined as OutgoingCookieState in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_OUTGOINGCOOKIESTATE, OUTGOINGCOOKIESTATE, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  OUTGOINGCOOKIESTATE** }}*/
XB_BEGIN_STRUCTURE( OUTGOINGCOOKIESTATE  )
   /*{{|member_: - MEMBER INT cSent }}*/
   _XBST_int   ( cSent         )
   /*{{|member_: - MEMBER INT cSuppressed }}*/
   _XBST_int   ( cSuppressed   )
   /*{{|member_: - MEMBER LPSTR pszLocation }}*/
   /*{{|member_: - MEMBER DYNSZ cLocation |desc_: Helper member mapped over ::pszLocation. }}*/
   _XBST_LPSTR_DYNSZ ( pszLocation  , cLocation )
   pc->GwstSetOffset( sizeof( OutgoingCookieState) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNETCOOKIEHISTORY
            | _slug_: wapist_internetcookiehistory
            | class-function: WAPIST_INTERNETCOOKIEHISTORY
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNETCOOKIEHISTORY structure. Defined as InternetCookieHistory in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNETCOOKIEHISTORY, INTERNETCOOKIEHISTORY, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNETCOOKIEHISTORY** }}*/
XB_BEGIN_STRUCTURE( INTERNETCOOKIEHISTORY )
   /*{{|member_: - MEMBER BOOL fAccepted }}*/
   _XBST_BOOL ( fAccepted    );
   /*{{|member_: - MEMBER BOOL fLeashed }}*/
   _XBST_BOOL ( fLeashed     );
   /*{{|member_: - MEMBER BOOL fDowngraded }}*/
   _XBST_BOOL ( fDowngraded  );
   /*{{|member_: - MEMBER BOOL fRejected }}*/
   _XBST_BOOL ( fRejected    );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_COOKIEDECISION
            | _slug_: wapist_cookiedecision
            | class-function: WAPIST_COOKIEDECISION
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi COOKIEDECISION structure. Defined as CookieDecision in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_COOKIEDECISION, COOKIEDECISION, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  COOKIEDECISION** }}*/
XB_BEGIN_STRUCTURE( COOKIEDECISION         )
   /*{{|member_: - MEMBER DWORD dwCookieState }}*/
   _XBST_DWORD ( dwCookieState  )
   /*{{|member_: - MEMBER BOOL fAllowSession }}*/
   _XBST_BOOL  ( fAllowSession  )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_AUTH_NOTIFY_DATA
            | _slug_: wapist_internet_auth_notify_data
            | class-function: WAPIST_INTERNET_AUTH_NOTIFY_DATA
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNET_AUTH_NOTIFY_DATA structure. Defined as INTERNET_AUTH_NOTIFY_DATA
              in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_AUTH_NOTIFY_DATA, INTERNET_AUTH_NOTIFY_DATA, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_AUTH_NOTIFY_DATA** }}*/
XB_BEGIN_STRUCTURE( INTERNET_AUTH_NOTIFY_DATA   )
   /*{{|member_: - MEMBER DWORD cbStruct }}*/
   _XBST_DWORD ( cbStruct    )
   /*{{|member_: - MEMBER DWORD dwOptions }}*/
   _XBST_DWORD ( dwOptions   )
   /*{{|member_: - MEMBER DWORD pfnNotify }}*/
   _XBST_DWORD ( pfnNotify   )
   /*{{|member_: - MEMBER DWORD dwContext }}*/
   _XBST_DWORD ( dwContext   )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_CACHE_ENTRY_INFO
            | _slug_: wapist_internet_cache_entry_info
            | class-function: WAPIST_INTERNET_CACHE_ENTRY_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_CACHE_ENTRY_INFOA structure. Defined as
              INTERNET_CACHE_ENTRY_INFO in ot4xb_wapist_map.ch.
          | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_cache_entry_infoa
          | _kw_: WAPIST_INTERNET_CACHE_ENTRY_INFO, INTERNET_CACHE_ENTRY_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_CACHE_ENTRY_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_ENTRY_INFO )

   /*{{|member_: - MEMBER DWORD dwStructSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwStructSize      ));_XBST_DWORD    ( dwStructSize      );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_CACHE_ENTRY_INFO, lpszSourceUrlName));
   /*{{|member_: - MEMBER LPSTR lpszSourceUrlName }}*/
   pc->Member_lpStr("lpszSourceUrlName");
   pc->GwstBack();
   /*{{|member_: - MEMBER DYNSZ cSourceUrlName |desc_: Helper member mapped over ::lpszSourceUrlName. }}*/
   pc->Member_DynSz("cSourceUrlName");
   /*{{|member_: - MEMBER LPSTR lpszLocalFileName }}*/
   /*{{|member_: - MEMBER DYNSZ cLocalFileName |desc_: Helper member mapped over ::lpszLocalFileName. }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpszLocalFileName ));_XBST_LPSTR_DYNSZ    ( lpszLocalFileName , cLocalFileName);
   /*{{|member_: - MEMBER DWORD CacheEntryType }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , CacheEntryType    ));_XBST_DWORD    ( CacheEntryType    );
   /*{{|member_: - MEMBER DWORD dwUseCount }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwUseCount        ));_XBST_DWORD    ( dwUseCount        );
   /*{{|member_: - MEMBER DWORD dwHitRate }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwHitRate         ));_XBST_DWORD    ( dwHitRate         );
   /*{{|member_: - MEMBER DWORD dwSizeLow }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwSizeLow         ));_XBST_DWORD    ( dwSizeLow         );
   /*{{|member_: - MEMBER DWORD dwSizeHigh }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwSizeHigh        ));_XBST_DWORD    ( dwSizeHigh        );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} LastModifiedTime }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastModifiedTime  ));_XBST_FILETIME ( LastModifiedTime  );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ExpireTime }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , ExpireTime        ));_XBST_FILETIME ( ExpireTime        );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} LastAccessTime }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastAccessTime    ));_XBST_FILETIME ( LastAccessTime    );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} LastSyncTime }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , LastSyncTime      ));_XBST_FILETIME ( LastSyncTime      );
   /*{{|member_: - MEMBER LPSTR lpHeaderInfo }}*/
   /*{{|member_: - MEMBER DYNSZ cHeaderInfo |desc_: Helper member mapped over ::lpHeaderInfo. }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpHeaderInfo      ));_XBST_LPSTR_DYNSZ ( lpHeaderInfo  , cHeaderInfo );
   /*{{|member_: - MEMBER DWORD dwHeaderInfoSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwHeaderInfoSize  ));_XBST_DWORD    ( dwHeaderInfoSize  );
   /*{{|member_: - MEMBER LPSTR lpszFileExtension }}*/
   /*{{|member_: - MEMBER DYNSZ cFileExtension |desc_: Helper member mapped over ::lpszFileExtension. }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , lpszFileExtension ));_XBST_LPSTR_DYNSZ  ( lpszFileExtension , cFileExtension);
   /*{{|member_: - MEMBER DWORD dwReserved }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwReserved        ));_XBST_DWORD( dwReserved    );// Anonymous UNION
   /*{{|member_: - MEMBER DWORD dwExemptDelta }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_ENTRY_INFO , dwExemptDelta     ));_XBST_DWORD( dwExemptDelta );// Anonymous UNION
   pc->GwstSetOffset( sizeof( INTERNET_CACHE_ENTRY_INFO) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_CACHE_TIMESTAMPS
            | _slug_: wapist_internet_cache_timestamps
            | class-function: WAPIST_INTERNET_CACHE_TIMESTAMPS
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi INTERNET_CACHE_TIMESTAMPS structure. Defined as INTERNET_CACHE_TIMESTAMPS
              in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_INTERNET_CACHE_TIMESTAMPS, INTERNET_CACHE_TIMESTAMPS, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_CACHE_TIMESTAMPS** }}*/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_TIMESTAMPS  )
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftExpires }}*/
   _XBST_FILETIME(  ftExpires      );
   /*{{|member_: - MEMBER @ {{ilink: <slug filetime64> FILETIME64}} ftLastModified }}*/
   _XBST_FILETIME(  ftLastModified );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_INTERNET_CACHE_GROUP_INFO
            | _slug_: wapist_internet_cache_group_info
            | class-function: WAPIST_INTERNET_CACHE_GROUP_INFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet INTERNET_CACHE_GROUP_INFOA structure. Defined as
              INTERNET_CACHE_GROUP_INFO in ot4xb_wapist_map.ch.
          | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/wininet/ns-wininet-internet_cache_group_infoa
          | _kw_: WAPIST_INTERNET_CACHE_GROUP_INFO, INTERNET_CACHE_GROUP_INFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  INTERNET_CACHE_GROUP_INFO** }}*/
XB_BEGIN_STRUCTURE( INTERNET_CACHE_GROUP_INFO   )
   /*{{|member_: - MEMBER DWORD dwGroupSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupSize  ));  _XBST_DWORD(  dwGroupSize  )
   /*{{|member_: - MEMBER DWORD dwGroupFlags }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupFlags ));  _XBST_DWORD(  dwGroupFlags )
   /*{{|member_: - MEMBER DWORD dwGroupType }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwGroupType  ));  _XBST_DWORD(  dwGroupType  )
   /*{{|member_: - MEMBER DWORD dwDiskUsage }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwDiskUsage  ));  _XBST_DWORD(  dwDiskUsage  )
   /*{{|member_: - MEMBER DWORD dwDiskQuota }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwDiskQuota  ));  _XBST_DWORD(  dwDiskQuota  )
   /*{{|member_: - MEMBER BINSTR dwOwnerStorage_bytes }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwOwnerStorage)); _XBST_BINSTR(dwOwnerStorage_bytes, 16);
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , dwOwnerStorage));
   /*{{|member_: - MEMBER DWORD dwOwnerStorage_0 }}*/
   _XBST_DWORD(  dwOwnerStorage_0 )
   /*{{|member_: - MEMBER DWORD dwOwnerStorage_1 }}*/
   _XBST_DWORD(  dwOwnerStorage_1 )
   /*{{|member_: - MEMBER DWORD dwOwnerStorage_2 }}*/
   _XBST_DWORD(  dwOwnerStorage_2 )
   /*{{|member_: - MEMBER DWORD dwOwnerStorage_3 }}*/
   _XBST_DWORD(  dwOwnerStorage_3 )
   /*{{|member_: - MEMBER SZSTR szGroupName }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  INTERNET_CACHE_GROUP_INFO , szGroupName)); _XBST_SZSTR(szGroupName,120 )
   pc->GwstSetOffset( sizeof( INTERNET_CACHE_GROUP_INFO) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_AUTO_PROXY_SCRIPT_BUFFER
            | _slug_: wapist_auto_proxy_script_buffer
            | class-function: WAPIST_AUTO_PROXY_SCRIPT_BUFFER
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinInet AUTO_PROXY_SCRIPT_BUFFER structure. Defined as AUTO_PROXY_SCRIPT_BUFFER
              in ot4xb_wapist_map.ch.
   | _kw_: WAPIST_AUTO_PROXY_SCRIPT_BUFFER, AUTO_PROXY_SCRIPT_BUFFER, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  AUTO_PROXY_SCRIPT_BUFFER** }}*/
XB_BEGIN_STRUCTURE( AUTO_PROXY_SCRIPT_BUFFER )

   /*{{|member_: - MEMBER DWORD dwStructSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwStructSize        ));_XBST_DWORD( dwStructSize        )
   /*{{|member_: - MEMBER LPSTR lpszScriptBuffer }}*/
   /*{{|member_: - MEMBER DYNSZ cScriptBuffer |desc_: Helper member mapped over ::lpszScriptBuffer. }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,lpszScriptBuffer    ));_XBST_LPSTR_DYNSZ( lpszScriptBuffer , cScriptBuffer )
   /*{{|member_: - MEMBER DWORD dwScriptBufferSize }}*/
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwScriptBufferSize  ));_XBST_DWORD( dwScriptBufferSize  )
   pc->GwstSetOffset( sizeof( AUTO_PROXY_SCRIPT_BUFFER) );
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_TRACKMOUSEEVENT
            | _slug_: wapist_trackmouseevent
            | class-function: WAPIST_TRACKMOUSEEVENT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi TRACKMOUSEEVENT structure. Defined as TRACKMOUSEEVENT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_TRACKMOUSEEVENT, TRACKMOUSEEVENT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  TRACKMOUSEEVENT** }}*/
XB_BEGIN_STRUCTURE(TRACKMOUSEEVENT )
   /*{{|member_: - MEMBER DWORD cbSize }}*/
   _XBST_DWORD( cbSize)
   /*{{|member_: - MEMBER DWORD dwFlags }}*/
   _XBST_DWORD( dwFlags)
   /*{{|member_: - MEMBER HWND hwndTrack }}*/
   _XBST_HWND  (hwndTrack)
   /*{{|member_: - MEMBER DWORD dwHoverTime }}*/
   _XBST_DWORD( dwHoverTime)
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_MOUSEMOVEPOINT
            | _slug_: wapist_mousemovepoint
            | class-function: WAPIST_MOUSEMOVEPOINT
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi MOUSEMOVEPOINT structure. Defined as MOUSEMOVEPOINT in
              ot4xb_wapist_map.ch.
   | _kw_: WAPIST_MOUSEMOVEPOINT, MOUSEMOVEPOINT, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  MOUSEMOVEPOINT** }}*/
XB_BEGIN_STRUCTURE( MOUSEMOVEPOINT )
	/*{{|member_: - MEMBER INT x }}*/
	_XBST_int(x)
	/*{{|member_: - MEMBER INT y }}*/
	_XBST_int(y)
	/*{{|member_: - MEMBER DWORD time }}*/
	_XBST_DWORD(time)
	/*{{|member_: - MEMBER ULONG_PTR dwExtraInfo }}*/
	_XBST_ULONG_PTR(dwExtraInfo )
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_PREVENT_MEDIA_REMOVAL
            | _slug_: wapist_prevent_media_removal
            | class-function: WAPIST_PREVENT_MEDIA_REMOVAL
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi PREVENT_MEDIA_REMOVAL structure. Defined as PREVENT_MEDIA_REMOVAL in
              ot4xb_wapist_map.ch.
 | ref-url: https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddstor/ns-ntddstor-_prevent_media_removal
 | _kw_: WAPIST_PREVENT_MEDIA_REMOVAL, PREVENT_MEDIA_REMOVAL, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  PREVENT_MEDIA_REMOVAL** }}*/
XB_BEGIN_STRUCTURE( PREVENT_MEDIA_REMOVAL )
/*{{|member_: - MEMBER BYTE PreventMediaRemoval }}*/
_XBST_BYTE( PreventMediaRemoval	)
pc->GwstSetOffset(sizeof(PREVENT_MEDIA_REMOVAL));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// ---------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SHFILEINFO
            | _slug_: wapist_shfileinfo
            | class-function: WAPIST_SHFILEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SHFILEINFOA structure. Defined as SHFILEINFO in ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shfileinfoa
            | _kw_: WAPIST_SHFILEINFO, SHFILEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SHFILEINFO** }}*/
XB_BEGIN_STRUCTURE(SHFILEINFO)
/*{{|member_: - MEMBER HICON hIcon }}*/
_XBST_HICON(hIcon)
/*{{|member_: - MEMBER INT iIcon }}*/
_XBST_int(iIcon)
/*{{|member_: - MEMBER DWORD dwAttributes }}*/
_XBST_DWORD(dwAttributes)
/*{{|member_: - MEMBER SZSTR szDisplayName }}*/
_XBST_SZSTR(szDisplayName, MAX_PATH)
/*{{|member_: - MEMBER SZSTR szTypeName }}*/
_XBST_SZSTR(szTypeName, 80);
pc->GwstSetOffset(sizeof(SHFILEINFOA));
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// ---------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: WAPIST_SHELLEXECUTEINFO
            | _slug_: wapist_shellexecuteinfo
            | class-function: WAPIST_SHELLEXECUTEINFO
            | parent: {{ilink: <class gwst> gwst}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi SHELLEXECUTEINFOA structure. Defined as SHELLEXECUTEINFO in
              ot4xb_wapist_map.ch.
            | ref-url: https://learn.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shellexecuteinfoa
            | _kw_: WAPIST_SHELLEXECUTEINFO, SHELLEXECUTEINFO, WINAPI, Structures
   }}*/
/*{{|:**BEGIN STRUCTURE  SHELLEXECUTEINFO** }}*/
XB_BEGIN_STRUCTURE(SHELLEXECUTEINFO)
	/*{{|member_: - MEMBER DWORD cbSize }}*/
	_XBST_DWORD(cbSize)
	/*{{|member_: - MEMBER ULONG fMask }}*/
	_XBST_ULONG(fMask)
	/*{{|member_: - MEMBER HWND hwnd }}*/
	_XBST_HWND(hwnd)
	/*{{|member_: - MEMBER LPSTR lpVerb }}*/
	/*{{|member_: - MEMBER DYNSZ cVerb |desc_: Helper member mapped over ::lpVerb. }}*/
	_XBST_LPSTR_DYNSZ(lpVerb, cVerb)
	/*{{|member_: - MEMBER LPSTR lpFile }}*/
	/*{{|member_: - MEMBER DYNSZ cFile |desc_: Helper member mapped over ::lpFile. }}*/
	_XBST_LPSTR_DYNSZ(lpFile, cFile)
	/*{{|member_: - MEMBER LPSTR lpParameters }}*/
	/*{{|member_: - MEMBER DYNSZ cParameters |desc_: Helper member mapped over ::lpParameters. }}*/
	_XBST_LPSTR_DYNSZ(lpParameters, cParameters)
	/*{{|member_: - MEMBER LPSTR lpDirectory }}*/
	/*{{|member_: - MEMBER DYNSZ cDirectory |desc_: Helper member mapped over ::lpDirectory. }}*/
	_XBST_LPSTR_DYNSZ(lpDirectory, cDirectory)
	/*{{|member_: - MEMBER INT nShow }}*/
	_XBST_int(nShow)
	/*{{|member_: - MEMBER HINSTANCE hInstApp }}*/
	_XBST_HINSTANCE(hInstApp)
	/*{{|member_: - MEMBER LPVOID lpIDList }}*/
	_XBST_LPVOID(lpIDList)
	/*{{|member_: - MEMBER LPSTR lpClass }}*/
	/*{{|member_: - MEMBER DYNSZ cClass |desc_: Helper member mapped over ::lpClass. }}*/
	_XBST_LPSTR_DYNSZ(lpClass , cClass )
	/*{{|member_: - MEMBER HANDLE hkeyClass }}*/
	_XBST_HANDLE( hkeyClass )
	/*{{|member_: - MEMBER DWORD dwHotKey }}*/
	_XBST_DWORD(dwHotKey)
	/*{{|member_: - MEMBER HANDLE hIcon }}*/
	_XBST_HANDLE(hIcon)
	pc->GwstBack(); // inline union
	/*{{|member_: - MEMBER HANDLE hMonitor }}*/
	_XBST_HANDLE( hMonitor )
	/*{{|member_: - MEMBER HANDLE hProcess }}*/
	_XBST_HANDLE( hProcess )
	// ----------
	// ----------
XB_END_STRUCTURE
/*{{|:**END STRUCTURE** }}*/
/*{{include-note-id: wapist-map}}*/
/*{{end-class}}*/
// ---------------------------------------------------------------------------------------------------------------------
