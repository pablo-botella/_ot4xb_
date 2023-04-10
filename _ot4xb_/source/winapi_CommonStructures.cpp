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
#define _XBST_DEVMODE( name )                          pc->Child( #name , "WAPIST_DEVMODE" );
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
XB_BEGIN_STRUCTURE ( POINT )
   _XBST_LONG ( x )
   _XBST_LONG ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( POINTS )
   _XBST_SHORT ( x )
   _XBST_SHORT ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( POINTL )
   _XBST_LONG ( x )
   _XBST_LONG ( y )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( MSG )
   _XBST_HWND   ( hwnd    )
   _XBST_UINT   ( message )
   _XBST_WPARAM ( wParam  )
   _XBST_LPARAM ( lParam  )
   _XBST_DWORD  ( time    )
   _XBST_POINT  ( pt      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( LOGPEN )
   _XBST_DWORD ( lopnPenStyle )
   _XBST_POINT ( lopnWidth    )
   _XBST_ULONG ( lopnColor    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( LOGBRUSH )
   _XBST_UINT  ( lbStyle )
   _XBST_ULONG ( lbColor )
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( LOGBRUSH32 )
   _XBST_UINT  ( lbStyle )
   _XBST_ULONG ( lbColor )
   _XBST_LONG  ( lbHatch )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( BLENDFUNCTION )
   _XBST_BYTE ( BlendOp             )
   _XBST_BYTE ( BlendFlags          )
   _XBST_BYTE ( SourceConstantAlpha )
   _XBST_BYTE ( AlphaFormat         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( RGBQUAD )
   _XBST_BYTE ( rgbBlue     )
   _XBST_BYTE ( rgbGreen    )
   _XBST_BYTE ( rgbRed      )
   _XBST_BYTE ( rgbReserved )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( BITMAPINFO )
   _XBST_BITMAPINFOHEADER ( bmiHeader )
   _XBST_RGBQUAD          ( bmiColors )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( SIZE )
   _XBST_LONG ( cx )
   _XBST_LONG ( cy )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( SIZEL )
   _XBST_LONG ( cx )
   _XBST_LONG ( cy )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( TRIVERTEX )
   _XBST_LONG ( x     )
   _XBST_LONG ( y     )
   _XBST_WORD ( Red   )
   _XBST_WORD ( Green )
   _XBST_WORD ( Blue  )
   _XBST_WORD ( Alpha )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( PALETTEENTRY )
   _XBST_BYTE ( peRed   )
   _XBST_BYTE ( peGreen )
   _XBST_BYTE ( peBlue  )
   _XBST_BYTE ( peFlags )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( LOGPALETTE )
   _XBST_WORD         ( palVersion    )
   _XBST_WORD         ( palNumEntries )
   _XBST_PALETTEENTRY ( palPalEntry0  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( XFORM )
   _XBST_FLOAT ( eM11 )
   _XBST_FLOAT ( eM12 )
   _XBST_FLOAT ( eM21 )
   _XBST_FLOAT ( eM22 )
   _XBST_FLOAT ( eDx  )
   _XBST_FLOAT ( eDy  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( RECT )
   _XBST_LONG ( left   )
   _XBST_LONG ( top    )
   _XBST_LONG ( right  )
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( RECTL )
   _XBST_LONG ( left   )
   _XBST_LONG ( top    )
   _XBST_LONG ( right  )
   _XBST_LONG ( bottom )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( ABC )
   _XBST_INT  ( abcA )
   _XBST_UINT ( abcB )
   _XBST_INT  ( abcC )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( ABCFLOAT )
   _XBST_FLOAT ( abcfA )
   _XBST_FLOAT ( abcfB )
   _XBST_FLOAT ( abcfC )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( DRAWTEXTPARAMS )
   _XBST_UINT ( cbSize        )
   _XBST_int  ( iTabLength    )
   _XBST_int  ( iLeftMargin   )
   _XBST_int  ( iRightMargin  )
   _XBST_UINT ( uiLengthDrawn )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( ENUMLOGFONT )
   _XBST_LOGFONT ( elfLogFont                    )
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( ENUMLOGFONTEX )
   _XBST_LOGFONT ( elfLogFont                    )
   _XBST_SZSTR   ( elfFullName , LF_FULLFACESIZE )
   _XBST_SZSTR   ( elfStyle    , LF_FACESIZE     )
   _XBST_SZSTR   ( elfScript   , LF_FACESIZE     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( FIXED )
   _XBST_WORD  ( fract )
   _XBST_short ( value )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( GLYPHMETRICS )
   _XBST_UINT      ( gmBlackBoxX )
   _XBST_UINT      ( gmBlackBoxY )
   _XBST_POINT     ( gmptGlyphOrigin )
   _XBST_short     ( gmCellIncX )
   _XBST_short     ( gmCellIncY )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( GLYPHSET )
   _XBST_DWORD   ( cbThis )
   _XBST_DWORD   ( flAccel )
   _XBST_DWORD   ( cGlyphsSupported )
   _XBST_DWORD   ( cRanges )
   _XBST_WCRANGE ( ranges0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( KERNINGPAIR )
   _XBST_WORD ( wFirst )
   _XBST_WORD ( wSecond )
   _XBST_int  ( iKernAmount )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( MAT2 )
   _XBST_FIXED ( eM11 )
   _XBST_FIXED ( eM12 )
   _XBST_FIXED ( eM21 )
   _XBST_FIXED ( eM22 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( NEWTEXTMETRICEX )
   _XBST_NEWTEXTMETRIC ( ntmTm      )
   _XBST_FONTSIGNATURE ( ntmFontSig )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( POINTFX )
   _XBST_FIXED ( x )
   _XBST_FIXED ( y )

XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE ( RASTERIZER_STATUS )
   _XBST_short ( nSize       )
   _XBST_short ( wFlags      )
   _XBST_short ( nLanguageID )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( TEXTMETRIC )
   _XBST_LONG  ( tmHeight               )
   _XBST_LONG  ( tmAscent               )
   _XBST_LONG  ( tmDescent              )
   _XBST_LONG  ( tmInternalLeading      )
   _XBST_LONG  ( tmExternalLeading      )
   _XBST_LONG  ( tmAveCharWidth         )
   _XBST_LONG  ( tmMaxCharWidth         )
   _XBST_LONG  ( tmWeight               )
   _XBST_LONG  ( tmOverhang             )
   _XBST_LONG  ( tmDigitizedAspectX     )
   _XBST_LONG  ( tmDigitizedAspectY     )
   _XBST_TCHAR ( tmFirstChar            )
   _XBST_TCHAR ( tmLastChar             )
   _XBST_TCHAR ( tmDefaultChar          )
   _XBST_TCHAR ( tmBreakChar            )
   _XBST_BYTE  ( tmItalic               )
   _XBST_BYTE  ( tmUnderlined           )
   _XBST_BYTE  ( tmStruckOut            )
   _XBST_BYTE  ( tmPitchAndFamily       )
   _XBST_BYTE  ( tmCharSet              )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( TTPOLYCURVE )
   _XBST_WORD    ( wType )
   _XBST_WORD    ( cpfx  )
   _XBST_POINTFX ( apfx0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( TTPOLYGONHEADER )
   _XBST_DWORD   ( cb       )
   _XBST_DWORD   ( dwType   )
   _XBST_POINTFX ( pfxStart )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( WCRANGE )
   _XBST_short  ( wcLow   )
   _XBST_USHORT ( cGlyphs )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( FONTSIGNATURE )
   _XBST_DWORD ( fsUsb0 )
   _XBST_DWORD ( fsUsb1 )
   _XBST_DWORD ( fsUsb2 )
   _XBST_DWORD ( fsUsb3 )
   _XBST_DWORD ( fsCsb0 )
   _XBST_DWORD ( fsCsb1 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( MONITORINFO )
   _XBST_DWORD ( cbSize    )
   _XBST_RECT  ( rcMonitor )
   _XBST_RECT  ( rcWork    )
   _XBST_DWORD ( dwFlags   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( MONITORINFOEX )
   _XBST_DWORD ( cbSize                   )
   _XBST_RECT  ( rcMonitor                )
   _XBST_RECT  ( rcWork                   )
   _XBST_DWORD ( dwFlags                  )
   _XBST_SZSTR ( szDevice , CCHDEVICENAME )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( PAINTSTRUCT )
   _XBST_HDC    ( hdc              )
   _XBST_BOOL   ( fErase           )
   _XBST_RECT   ( rcPaint          )
   _XBST_BOOL   ( fRestore         )
   _XBST_BOOL   ( fIncUpdate       )
   _XBST_BINSTR ( rgbReserved , 32 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE ( SYSTEMTIME )
   _XBST_WORD( wYear         )
   _XBST_WORD( wMonth        )
   _XBST_WORD( wDayOfWeek    )
   _XBST_WORD( wDay          )
   _XBST_WORD( wHour         )
   _XBST_WORD( wMinute       )
   _XBST_WORD( wSecond       )
   _XBST_WORD( wMilliseconds )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ADDJOB_INFO_1 )
  _XBST_LPSTR( Path  )
  _XBST_DWORD( JobId )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DATATYPES_INFO_1 )
  _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DEVMODE )
  _XBST_SZWSTR  ( dmDeviceName  ,  CCHDEVICENAME )
  _XBST_WORD    ( dmSpecVersion                  )
  _XBST_WORD    ( dmDriverVersion                )
  _XBST_WORD    ( dmSize                         )
  _XBST_WORD    ( dmDriverExtra                  )
  _XBST_DWORD   ( dmFields                       )
  {
     UINT nP1 = pc->GwstGetOffset();
     UINT nMax;
     {
        _XBST_short( dmOrientation   )
        _XBST_short( dmPaperSize     )
        _XBST_short( dmPaperLength   )
        _XBST_short( dmPaperWidth    )
        _XBST_short( dmScale         )
        _XBST_short( dmCopies        )
        _XBST_short( dmDefaultSource )
        _XBST_short( dmPrintQuality  )
     }
     nMax = pc->GwstGetOffset(); pc->GwstSetOffset(nP1);
     _XBST_POINTL( dmPosition )
     if( pc->GwstGetOffset() > nMax ){nMax = pc->GwstGetOffset();} pc->GwstSetOffset(nP1);
    _XBST_DWORD( dmDisplayOrientation )
     if( pc->GwstGetOffset() > nMax ){nMax = pc->GwstGetOffset();} pc->GwstSetOffset(nP1);
    _XBST_DWORD( dmDisplayFixedOutput )
     if( pc->GwstGetOffset() < nMax ) pc->GwstSetOffset(nMax);
  }
  _XBST_short(  dmColor                  )
  _XBST_short(  dmDuplex                 )
  _XBST_short(  dmYResolution            )
  _XBST_short(  dmTTOption               )
  _XBST_short(  dmCollate                )
  _XBST_SZSTR(  dmFormName  , CCHFORMNAME)
  _XBST_WORD (  dmLogPixels              )
  _XBST_DWORD(  dmBitsPerPel             )
  _XBST_DWORD(  dmPelsWidth              )
  _XBST_DWORD(  dmPelsHeight             )
  pc->GwstBeginUnion();
      _XBST_DWORD(    dmDisplayFlags )
      _XBST_DWORD(    dmNup          )
  pc->GwstEndUnion();
  _XBST_DWORD(  dmDisplayFrequency  )
  _XBST_DWORD(  dmICMMethod         )
  _XBST_DWORD(  dmICMIntent         )
  _XBST_DWORD(  dmMediaType         )
  _XBST_DWORD(  dmDitherType        )
  _XBST_DWORD(  dmReserved1         )
  _XBST_DWORD(  dmReserved2         )
  _XBST_DWORD(  dmPanningWidth      )
  _XBST_DWORD(  dmPanningHeight     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DOC_INFO_1 )
  _XBST_LPSTR( pDocName     )
  _XBST_LPSTR( pOutputFile  )
  _XBST_LPSTR( pDatatype    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DOC_INFO_2 )
  _XBST_LPSTR( pDocName    )
  _XBST_LPSTR( pOutputFile )
  _XBST_LPSTR( pDatatype   )
  _XBST_DWORD( dwMode      )
  _XBST_DWORD( JobId       )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DOC_INFO_3 )
  _XBST_LPSTR( pDocName    )
  _XBST_LPSTR( pOutputFile )
  _XBST_LPSTR( pDatatype   )
  _XBST_DWORD( dwFlags     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DOCINFO )
  _XBST_int   (  cbSize         )
  _XBST_LPSTR (  lpszDocName    )
  _XBST_LPSTR (  lpszOutput     )
  _XBST_LPSTR (  lpszDatatype   )
  _XBST_DWORD (  fwType         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DRAWPATRECT )
   _XBST_POINT ( ptPosition  )
   _XBST_POINT ( ptSize      )
   _XBST_WORD  ( wStyle      )
   _XBST_WORD  ( wPattern    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DRIVER_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DRIVER_INFO_2 )
   _XBST_DWORD ( cVersion      )
   _XBST_LPSTR ( pName         )
   _XBST_LPSTR ( pEnvironment  )
   _XBST_LPSTR ( pDriverPath   )
   _XBST_LPSTR ( pDataFile     )
   _XBST_LPSTR ( pConfigFile   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( FORM_INFO_1 )
   _XBST_DWORD ( Flags         )
   _XBST_LPSTR ( pName         )
   _XBST_SIZEL ( Size          )
   _XBST_RECTL ( ImageableArea )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( JOB_INFO_3 )
   _XBST_DWORD  ( JobId     )
   _XBST_DWORD  ( NextJobId )
   _XBST_DWORD  ( Reserved  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MONITOR_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MONITOR_INFO_2 )
   _XBST_LPSTR ( pName        )
   _XBST_LPSTR ( pEnvironment )
   _XBST_LPSTR ( pDLLName     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PORT_INFO_1 )
   _XBST_LPSTR( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PORT_INFO_2 )
   _XBST_LPSTR ( pPortName    )
   _XBST_LPSTR ( pMonitorName )
   _XBST_LPSTR ( pDescription )
   _XBST_DWORD ( fPortType    )
   _XBST_DWORD ( Reserved     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PORT_INFO_3 )
   _XBST_DWORD( dwStatus   )
   _XBST_LPSTR( pszStatus  )
   _XBST_DWORD( dwSeverity )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_DEFAULTS )
   _XBST_LPSTR       ( pDatatype     )
   _XBST_POINTER32   ( pDevMode      )
   _XBST_ACCESS_MASK ( DesiredAccess )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_ENUM_VALUES )
   _XBST_LPSTR   ( pValueName  )
   _XBST_DWORD   ( cbValueName )
   _XBST_DWORD   ( dwType      )
   _XBST_LPBYTE  ( pData       )
   _XBST_DWORD   ( cbData      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_INFO_1 )
   _XBST_DWORD ( Flags        )
   _XBST_LPSTR_DYNSZ ( pDescription , cDescription)
   _XBST_LPSTR_DYNSZ ( pName        , cName       )
   _XBST_LPSTR_DYNSZ ( pComment     , cComment    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( PRINTER_INFO_3 )
   _XBST_POINTER32 ( pSecurityDescriptor )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_INFO_4 )
   _XBST_LPSTR_DYNSZ ( pPrinterName , cPrinterName)
   _XBST_LPSTR_DYNSZ ( pServerName  , cServerName )
   _XBST_DWORD ( Attributes   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_INFO_5 )
   _XBST_LPSTR_DYNSZ ( pPrinterName  , cPrinterName )
   _XBST_LPSTR_DYNSZ ( pPortName     , cPortName    )
   _XBST_DWORD ( Attributes               )
   _XBST_DWORD ( DeviceNotSelectedTimeout )
   _XBST_DWORD ( TransmissionRetryTimeout )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( PRINTER_INFO_7 )
   _XBST_LPSTR_DYNSZ ( pszObjectGUID , cObjectGUID)
   _XBST_DWORD  ( dwAction      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_INFO_8 )
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_INFO_9 )
   _XBST_POINTER32 ( pDevMode )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO )
   _XBST_DWORD                     ( Version )
   _XBST_DWORD                     ( Flags   )
   _XBST_DWORD                     ( Count   )
   _XBST_PRINTER_NOTIFY_INFO_DATA  ( aData0  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( _PRINTER_NOTIFY_INFO_DATA___DATA )
   _XBST_DWORD     ( cbBuf )
   _XBST_POINTER32 ( pBuf  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_INFO_DATA )
   _XBST_WORD   (  Type      )
   _XBST_WORD   (  Field     )
   _XBST_DWORD  (  Reserved  )
   _XBST_DWORD  (  Id        )
   _XBST__PRINTER_NOTIFY_INFO_DATA___NOTIFYDATA( NotifyData )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS )
   _XBST_DWORD     ( Version )
   _XBST_DWORD     ( Flags   )
   _XBST_DWORD     ( Count   )
   _XBST_POINTER32 ( pTypes  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTER_NOTIFY_OPTIONS_TYPE )
   _XBST_WORD       ( Type      )
   _XBST_WORD       ( Reserved0 )
   _XBST_DWORD      ( Reserved1 )
   _XBST_DWORD      ( Reserved2 )
   _XBST_DWORD      ( Count     )
   _XBST_POINTER32  ( pFields   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_CAPS_1 )
   _XBST_DWORD ( dwLevel          )
   _XBST_DWORD ( dwNupOptions     )
   _XBST_DWORD ( dwPageOrderFlags )
   _XBST_DWORD ( dwNumberOfCopies )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PRINTPROCESSOR_INFO_1 )
   _XBST_LPSTR ( pName )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_1 )
   _XBST_LPSTR( pName        )
   _XBST_LPSTR( pEnvironment )
   _XBST_LPSTR( pDLLName     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PROVIDOR_INFO_2 )
   _XBST_LPSTR( pOrder )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PSFEATURE_CUSTPAPER )
   _XBST_LONG ( lOrientation  )
   _XBST_LONG ( lWidth        )
   _XBST_LONG ( lHeight       )
   _XBST_LONG ( lWidthOffset  )
   _XBST_LONG ( lHeightOffset )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PSFEATURE_OUTPUT )
   _XBST_BOOL ( bPageIndependent )
   _XBST_BOOL ( bSetPageDevice   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PSINJECTDATA )
   _XBST_DWORD ( DataBytes      )
   _XBST_WORD  ( InjectionPoint )
   _XBST_WORD  ( PageNumber     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RGNDATA )
   _XBST_RGNDATAHEADER ( rdh )
   _XBST_CHAR          ( Buffer0 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RGNDATAHEADER )
   _XBST_DWORD ( dwSize    )
   _XBST_DWORD ( iType     )
   _XBST_DWORD ( nCount    )
   _XBST_DWORD ( nRgnSize  )
   _XBST_RECT  ( rcBound   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
//XB_BEGIN_STRUCTURE( DISPLAY_DEVICE )
//  DWORD cb;
//  WCHAR DeviceName[32];
//  WCHAR DeviceString[128];
//  DWORD StateFlags;
//  WCHAR DeviceID[128];
//  WCHAR DeviceKey[128];
//XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( WINDOWPLACEMENT )
   _XBST_UINT   ( length           )
   _XBST_UINT   ( flags            )
   _XBST_UINT   ( showCmd          )
   _XBST_POINT  ( ptMinPosition    )
   _XBST_POINT  ( ptMaxPosition    )
   _XBST_RECT   ( rcNormalPosition )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( CURSORINFO  )
   _XBST_DWORD   ( cbSize        )
   _XBST_DWORD   ( flags         )
   _XBST_HCURSOR ( hCursor       )
   _XBST_POINT   ( ptScreenPos   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ICONINFO  )
   _XBST_BOOL    ( fIcon     )
   _XBST_DWORD   ( xHotspot  )
   _XBST_DWORD   ( yHotspot  )
   _XBST_HBITMAP ( hbmMask   )
   _XBST_HBITMAP ( hbmColor  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ICONMETRICS  )
   _XBST_UINT    ( cbSize         )
   _XBST_int     ( iHorzSpacing   )
   _XBST_int     ( iVertSpacing   )
   _XBST_int     ( iTitleWrap     )
   _XBST_LOGFONT ( lfFont         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( METAFILEPICT  )
   _XBST_LONG      ( mm    )
   _XBST_LONG      ( xExt  )
   _XBST_LONG      ( yExt  )
   _XBST_HMETAFILE ( hMF   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MDINEXTMENU              )
   _XBST_HMENU  ( hmenuIn     )
   _XBST_HMENU  ( hmenuNext   )
   _XBST_HWND   ( hwndNext    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_HEADER   )
   _XBST_WORD  ( wVersion )
   _XBST_WORD  ( wOffset  )
   _XBST_DWORD ( dwHelpId )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MENUEX_TEMPLATE_ITEM  )
   _XBST_DWORD ( dwHelpId  )
   _XBST_DWORD ( dwType    )
   _XBST_DWORD ( dwState   )
   _XBST_DWORD ( menuId    )
   _XBST_WORD  ( bResInfo  )
   _XBST_short ( _wszText_ ) // WCHAR szText
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MENUGETOBJECTINFO        )
   _XBST_DWORD      ( dwFlags   )
   _XBST_UINT       ( uPos      )
   _XBST_HMENU      ( hmenu     )
   _XBST_POINTER32  ( riid      )
   _XBST_POINTER32  ( pvObj     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATE         )
   _XBST_WORD  ( mtOption   )
   _XBST_WORD  ( mtID       )
   _XBST_short ( mtString_1 ) // WCHAR mtString[1]
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MENUITEMTEMPLATEHEADER   )
   _XBST_WORD ( versionNumber  )
   _XBST_WORD ( offset         )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TPMPARAMS                )
   _XBST_UINT ( cbSize    )
   _XBST_RECT ( rcExclude )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ACCEL )
   _XBST_BYTE( fVirt )
   _XBST_WORD( key )
   _XBST_WORD( cmd )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MINMAXINFO )
   _XBST_POINT( ptReserved      )
   _XBST_POINT( ptMaxSize       )
   _XBST_POINT( ptMaxPosition   )
   _XBST_POINT( ptMinTrackSize  )
   _XBST_POINT( ptMaxTrackSize  )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMHDR )
   _XBST_HWND (hwndFrom )
   _XBST_UINT (idFrom   )
   _XBST_UINT (code     )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMRBAUTOSIZE      )
   _XBST_NMHDR ( hdr      )
   _XBST_BOOL  ( fChanged )
   _XBST_RECT  ( rcTarget )
   _XBST_RECT  ( rcActual )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMREBAR           )
   _XBST_NMHDR   ( hdr    )
   _XBST_DWORD   ( dwMask )
   _XBST_UINT    ( uBand  )
   _XBST_UINT    ( fStyle )
   _XBST_UINT    ( wID    )
   _XBST_LPARAM  ( lParam )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMREBARAUTOBREAK  )
   _XBST_NMHDR  ( hdr           )
   _XBST_UINT   ( uBand         )
   _XBST_UINT   ( wID           )
   _XBST_UINT   ( uMsg          )
   _XBST_UINT   ( fStyleCurrent )
   _XBST_BOOL   ( fAutoBreak    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMREBARCHEVRON    )
   _XBST_NMHDR     ( hdr      )
   _XBST_UINT      ( uBand    )
   _XBST_UINT      ( wID      )
   _XBST_LPARAM    ( lParam   )
   _XBST_RECT      ( rc       )
   _XBST_LPARAM    ( lParamNM )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMREBARCHILDSIZE  )
   _XBST_NMHDR  ( hdr     )
   _XBST_UINT   ( uBand   )
   _XBST_UINT   ( wID     )
   _XBST_RECT   ( rcChild )
   _XBST_RECT   ( rcBand  )

XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RBHITTESTINFO     )
   _XBST_POINT  ( pt    )
   _XBST_UINT   ( flags )
   _XBST_int    ( iBand )

XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( REBARINFO         )
   _XBST_UINT        ( cbSize  )
   _XBST_UINT        ( fMask   )
   _XBST_HANDLE      ( himl    )
XB_END_STRUCTURE
//-----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( HARDWAREINPUT )
  _XBST_DWORD ( uMsg    )
  _XBST_WORD  ( wParamL )
  _XBST_WORD  ( wParamH )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INPUT )
  _XBST_DWORD             ( type )
  pc->GwstBeginUnion();
    _XBST_MOUSEINPUT      ( mi )
    _XBST_KEYBDINPUT      ( ki )
    _XBST_HARDWAREINPUT   ( hi )
  pc->GwstEndUnion();
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( KEYBDINPUT )
    _XBST_WORD       ( wVk         )
    _XBST_WORD       ( wScan       )
    _XBST_DWORD      ( dwFlags     )
    _XBST_DWORD      ( time        )
    _XBST_ULONG_PTR  ( dwExtraInfo )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LASTINPUTINFO )
    _XBST_UINT  ( cbSize )
    _XBST_DWORD ( dwTime )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MOUSEINPUT )
    _XBST_LONG      ( dx          )
    _XBST_LONG      ( dy          )
    _XBST_DWORD     ( mouseData   )
    _XBST_DWORD     ( dwFlags     )
    _XBST_DWORD     ( time        )
    _XBST_ULONG_PTR ( dwExtraInfo )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( IMAGEINFO )
    _XBST_HBITMAP   ( hbmImage )
    _XBST_HBITMAP   ( hbmMask  )
    _XBST_int       ( Unused1  )
    _XBST_int       ( Unused2  )
    _XBST_RECT      ( rcImage  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( BIDIOPTIONS )
    _XBST_UINT ( cbSize    )
    _XBST_WORD ( wMask     )
    _XBST_WORD ( wEffects  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( CHARRANGE )
    _XBST_LONG        ( cpMin )
    _XBST_LONG        ( cpMax )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( COMPCOLOR )
    _XBST_COLORREF ( crText        )
    _XBST_COLORREF ( crBackground  )
    _XBST_DWORD    ( dwEffects     )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( EDITSTREAM )
    _XBST_DWORD ( dwCookie    )
    _XBST_DWORD ( dwError     )
    _XBST_DWORD ( pfnCallback )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENCORRECTTEXT )
   _XBST_NMHDR     ( nmhdr  )
   _XBST_CHARRANGE ( chrg   )
   _XBST_WORD      ( seltyp )
   pc->GwstSetOffset(sizeof(ENCORRECTTEXT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENDROPFILES )
   _XBST_NMHDR  ( nmhdr      )
   _XBST_HANDLE ( hDrop      )
   _XBST_LONG   ( cp         )
   _XBST_BOOL   ( fProtected )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENLINK )
   _XBST_NMHDR     ( nmhdr   )
   _XBST_UINT      ( msg     )
   _XBST_WPARAM    ( wParam  )
   _XBST_LPARAM    ( lParam  )
   _XBST_CHARRANGE ( chrg    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENLOWFIRTF )
   _XBST_NMHDR ( nmhdr     )
   _XBST_LPSTR ( szControl )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENOLEOPFAILED )
   _XBST_NMHDR   ( nmhdr )
   _XBST_LONG    ( iob   )
   _XBST_LONG    ( lOper )
   _XBST_HRESULT ( hr    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENPROTECTED )
   _XBST_NMHDR     ( nmhdr  )
   _XBST_UINT      ( msg    )
   _XBST_WPARAM    ( wParam )
   _XBST_LPARAM    ( lParam )
   _XBST_CHARRANGE ( chrg   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( ENSAVECLIPBOARD )
   _XBST_NMHDR ( nmhdr        )
   _XBST_LONG  ( cObjectCount )
   _XBST_LONG  ( cch          )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( FINDTEXT ) // Ojo resolver colisión con la función FindText() de comdlg32.dll
   _XBST_CHARRANGE  ( chrg      )
   _XBST_LPSTR      ( lpstrText )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( FINDTEXTEX )
   _XBST_CHARRANGE  ( chrg      )
   _XBST_LPSTR      ( lpstrText )
   _XBST_CHARRANGE  ( chrgText      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( FORMATRANGE )
   _XBST_HDC       ( hdc       )
   _XBST_HDC       ( hdcTarget )
   _XBST_RECT      ( rc        )
   _XBST_RECT      ( rcPage    )
   _XBST_CHARRANGE ( chrg      )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( GETTEXTEX )
   _XBST_DWORD      ( cb            )
   _XBST_DWORD      ( flags         )
   _XBST_UINT       ( codepage      )
   _XBST_LPSTR      ( lpDefaultChar )
   _XBST_POINTER32  ( lpUsedDefChar )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( GETTEXTLENGTHEX )
   _XBST_DWORD  ( flags    )
   _XBST_UINT   ( codepage )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HYPHENATEINFO )
   _XBST_SHORT  ( cbSize          )
   _XBST_SHORT  ( dxHyphenateZone )
   _XBST_DWORD  ( pfnHyphenate    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HYPHRESULT )
   _XBST_int   ( khyph   )
   _XBST_LONG  ( ichHyph )
   _XBST_SHORT ( chHyph  )
   pc->GwstSetOffset(sizeof(HYPHRESULT) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( IMECOMPTEXT )
   _XBST_LONG  ( cb     )
   _XBST_DWORD ( flags  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MSGFILTER )
   _XBST_NMHDR  ( nmhdr  )
   _XBST_UINT   ( msg    )
   _XBST_WPARAM ( wParam )
   _XBST_LPARAM ( lParam )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( OBJECTPOSITIONS )
   _XBST_NMHDR     ( nmhdr        )
   _XBST_LONG      ( cObjectCount )
   _XBST_POINTER32 ( pcpPositions )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( PUNCTUATION )
   _XBST_UINT   ( iSize         )
   _XBST_LPSTR  ( szPunctuation )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( REPASTESPECIAL )
   _XBST_DWORD ( dwAspect )
   _XBST_DWORD ( dwParam  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( REQRESIZE )
   _XBST_NMHDR ( nmhdr )
   _XBST_RECT  ( rc    )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SELCHANGE )
   _XBST_NMHDR      ( nmhdr  )
   _XBST_CHARRANGE  ( chrg   )
   _XBST_WORD       ( seltyp )
   pc->GwstSetOffset(sizeof(SELCHANGE) ); // align to 4 bytes boundary
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SETTEXTEX )
   _XBST_DWORD ( flags    )
   _XBST_UINT  ( codepage )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TEXTRANGE )
   _XBST_CHARRANGE ( chrg      )
   _XBST_LPSTR     ( lpstrText )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( GUID )
   _XBST_ULONG   ( Data1 )
   _XBST_WORD    ( Data2 )
   _XBST_WORD    ( Data3 )
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( CLSID )
   _XBST_ULONG   ( Data1 )
   _XBST_WORD    ( Data2 )
   _XBST_WORD    ( Data3 )
   _XBST_BINSTR  ( Data4  , 8)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
// winsock structures
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( SOCKADDR )
   _XBST_WORD    ( sa_family )
   _XBST_BINSTR  ( sa_data , 14 )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SOCKET_ADDRESS )
   _XBST_POINTER( lpSockaddr )
   _XBST_INT(     iSockaddrLength )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( CSADDR_INFO )
   _XBST_SOCKET_ADDRESS(  LocalAddr )
   _XBST_SOCKET_ADDRESS(  RemoteAddr )
   _XBST_INT( iSocketType )
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SOCKADDR_STORAGE )
   _XBST_SHORT( ss_family )
   _XBST_BINSTR( __ss_pad1 , 6 )
   _XBST_INT64(__ss_align )
   _XBST_BINSTR( __ss_pad2 , 112 )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SCOPE_ID )
   _XBST_DWORD( Value )
   pc->Member_BitField("Zone","Value",0,28,32);
   pc->Member_BitField("Level","Value",28,4,32);
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SOCKADDR_IN )
   _XBST_WORD( sin_family  )
   _XBST_WORD( sin_port    )
   _XBST_IN_ADDR( sin_addr )
   _XBST_BINSTR( sin_zero , 8)
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TIMEVAL )
   _XBST_LONG(  tv_sec  )
   _XBST_LONG(  tv_usec )
   pc->MethodCB("IsSet","{|s| nOr(s:tv_sec,s:tv_usec) != 0 }");
   pc->MethodCB("Clear","{|s| s:tv_sec := 0 , s:tv_usec := 0 , s}");
   pc->ClassMethodCB("cmp","{|s,a,b|i64cmp({a:tv_usec,a:tv_sec},{b:tv_usec,b:tv_sec})}");
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HOSTENT )
   _XBST_LPSTR(     h_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( h_aliases  )
   _XBST_short(     h_addrtype )
   _XBST_short(     h_length   )
   _XBST_POINTER32( h_addr_list) ; pc->GwstBack() ; _XBST_POINTER32( h_addr)
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NETENT )
   _XBST_LPSTR(     n_name     ) ; pc->GwstBack();  pc->Member_DynSz("cName");
   _XBST_POINTER32( n_aliases  )
   _XBST_short(     n_addrtype )
   pc->GwstSetOffset( FIELD_OFFSET( netent , n_net     ) );
   _XBST_DWORD(     n_net      )
   pc->GwstAdjustSize( sizeof(netent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( SERVENT )
   _XBST_LPSTR(     s_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( s_aliases  )
   _XBST_short(     s_port )
   pc->GwstSetOffset( FIELD_OFFSET( servent , s_proto ) );
   _XBST_LPSTR(     s_proto     ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(servent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PROTOENT )
   _XBST_LPSTR(     p_name     ) ; pc->GwstBack() ; pc->Member_DynSz("cName");
   _XBST_POINTER32( p_aliases  )
   _XBST_short(     p_proto    ) ; pc->GwstBack() ; pc->Member_DynSz("cProto");
   pc->GwstAdjustSize( sizeof(protoent) );
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( SOCKPROTO )
   _XBST_WORD(     sp_family   )
   _XBST_WORD(     sp_protocol )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LINGER )
   _XBST_WORD(     l_onoff  )
   _XBST_WORD(     l_linger )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( QOS_OBJECT_HDR )
   _XBST_ULONG( ObjectType    )
   _XBST_ULONG( ObjectLength  )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( QOS_SD_MODE )
   _XBST_QOS_OBJECT_HDR( ObjectHdr          )
   _XBST_ULONG(          ShapeDiscardMode   )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( QOS_SHAPING_RATE )
   _XBST_QOS_OBJECT_HDR  ( ObjectHdr   )
   _XBST_ULONG           ( ShapingRate )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( QOS )
   _XBST_FLOWSPEC ( SendingFlowspec   )
   _XBST_FLOWSPEC ( ReceivingFlowspec )
   _XBST_WSABUF   ( ProviderSpecific  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSANETWORKEVENTS )
   _XBST_LONG(   lNetworkEvents )
   _XBST_BINSTR( iErrorCode, (FD_MAX_EVENTS * sizeof(int)) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSAPROTOCOLCHAIN )
   _XBST_int(    ChainLen )
   _XBST_BINSTR( ChainEntries , (MAX_PROTOCOL_CHAIN * sizeof(DWORD) ) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_WINDOWMESSAGE )
   _XBST_HWND   ( hWnd    )
   _XBST_UINT   ( uMsg    )
   _XBST_WPARAM ( context )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_EVENT )
   _XBST_POINTER32 ( lpOverlapped )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_APC )
   _XBST_POINTER32 ( lpOverlapped          )
   _XBST_POINTER32 ( lpfnCompletionProc    )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PORT )
   _XBST_POINTER32 ( lpOverlapped )
   _XBST_HANDLE    ( hPort        )
   _XBST_POINTER32 ( Key          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSACOMPLETION_NS_PARAMETERS )
  pc->GwstBeginUnion();
   _XBST_WSACOMPLETION_NS_WINDOWMESSAGE( WindowMessage )
   _XBST_WSACOMPLETION_NS_EVENT(         Event         )
   _XBST_WSACOMPLETION_NS_APC(           Apc           )
   _XBST_WSACOMPLETION_NS_PORT(          Port          )
  pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSACOMPLETION )
   _XBST_LONG( Type )
   _XBST_WSACOMPLETION_NS_PARAMETERS( Parameters )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( BLOB )
   _XBST_ULONG(  cbSize )
   _XBST_LPBYTE( pBlobData )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( AFPROTOCOLS )
   _XBST_INT( iAddressFamily )
   _XBST_INT( iProtocol )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSAVERSION )
   _XBST_DWORD  ( dwVersion )
   _XBST_LONG   ( ecHow     )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( WSANSCLASSINFO )
   _XBST_LPSTR     ( lpszName     )
   _XBST_DWORD     ( dwNameSpace  )
   _XBST_DWORD     ( dwValueType  )
   _XBST_DWORD     ( dwValueSize  )
   _XBST_POINTER32 ( lpValue      )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSASERVICECLASSINFO )
   _XBST_POINTER32   ( lpServiceClassId      )
   _XBST_LPSTR       ( lpszServiceClassName  )
   _XBST_DWORD       ( dwCount               )
    _XBST_POINTER32  ( lpClassInfos          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFO )
   _XBST_GUID      ( NSProviderId     )
   _XBST_DWORD     ( dwNameSpace      )
   _XBST_BOOL      ( fActive          )
   _XBST_DWORD     ( dwVersion        )
   _XBST_LPSTR     ( lpszIdentifier   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSANAMESPACE_INFOEX )
   _XBST_GUID   (  NSProviderId     )
   _XBST_DWORD  (  dwNameSpace      )
   _XBST_BOOL   (  fActive          )
   _XBST_DWORD  (  dwVersion        )
   _XBST_LPSTR  (  lpszIdentifier   )
   _XBST_BLOB   (  ProviderSpecific )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( WSAPOLLFD )
   _XBST_SOCKET ( fd      )
   _XBST_SHORT  ( events  )
   _XBST_SHORT  ( revents )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( RAWHID )
   _XBST_DWORD ( dwSizeHid  )
   _XBST_DWORD ( dwCount    )
   _XBST_BYTE  ( bRawData   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWINPUT_DATA_UNION )
  pc->GwstBeginUnion();
   _XBST_RAWMOUSE    ( mouse     )
   _XBST_RAWKEYBOARD ( keyboard  )
   _XBST_RAWHID      ( hid       )
  pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWINPUT )
   _XBST_RAWINPUTHEADER( header )
   _XBST_RAWINPUT_DATA_UNION( data )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWINPUTDEVICE)
   _XBST_USHORT ( usUsagePage  )
   _XBST_USHORT ( usUsage      )
   _XBST_DWORD  ( dwFlags      )
   _XBST_HWND   ( hwndTarget   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWINPUTDEVICELIST )
   _XBST_HANDLE ( hDevice )
   _XBST_DWORD  ( dwType  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWINPUTHEADER )
   _XBST_DWORD  ( dwType  )
   _XBST_DWORD  ( dwSize  )
   _XBST_HANDLE ( hDevice )
   _XBST_WPARAM ( wParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RAWKEYBOARD )
   _XBST_USHORT ( MakeCode         )
   _XBST_USHORT ( Flags            )
   _XBST_USHORT ( Reserved         )
   _XBST_USHORT ( VKey             )
   _XBST_UINT   ( Message          )
   _XBST_ULONG  ( ExtraInformation )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_HID )
   _XBST_DWORD   ( dwVendorId       )
   _XBST_DWORD   ( dwProductId      )
   _XBST_DWORD   ( dwVersionNumber  )
   _XBST_USHORT  ( usUsagePage      )
   _XBST_USHORT  ( usUsage          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( RID_DEVICE_INFO_KEYBOARD )
   _XBST_DWORD ( dwType                 )
   _XBST_DWORD ( dwSubType              )
   _XBST_DWORD ( dwKeyboardMode         )
   _XBST_DWORD ( dwNumberOfFunctionKeys )
   _XBST_DWORD ( dwNumberOfIndicators   )
   _XBST_DWORD ( dwNumberOfKeysTotal    )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( IP_ADDR_STRING )
   _XBST_POINTER32    ( _Next )
   _XBST_BINSTR       ( IpAddress , 16 )
   _XBST_BINSTR       ( IpMask    , 16 )
   _XBST_DWORD        ( Context )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( IP_PER_ADAPTER_INFO )
   _XBST_UINT             ( AutoconfigEnabled  )
   _XBST_UINT             ( AutoconfigActive   )
   _XBST_POINTER32        ( CurrentDnsServer   )
   _XBST_IP_ADDR_STRING   ( DnsServerList      )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
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

XB_BEGIN_STRUCTURE( LVBKIMAGE )
   _XBST_ULONG( ulFlags )
   _XBST_HBITMAP( hbm )
   _XBST_LPSTR_DYNSZ( pszImage , cImage )
   _XBST_UINT( cchImageMax )
   _XBST_int( xOffsetPercent )
   _XBST_int( yOffsetPercent )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( LVFINDINFO )
   _XBST_UINT( flags )
_XBST_LPSTR_DYNSZ( psz , cStr )
   _XBST_LPARAM( lParam )
   _XBST_POINT( pt )
   _XBST_UINT( vkDirection )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE(LVFOOTERINFO )
   _XBST_UINT( mask )
   _XBST_POINTER32( pszText )  // LPWSTR
   _XBST_int( cchTextMax )
   _XBST_UINT( cItems )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE(LVFOOTERITEM )
   _XBST_UINT( mask )
   _XBST_int( iItem )
   _XBST_POINTER32( pszText ) // LPWSTR
   _XBST_int( cchTextMax )
   _XBST_UINT( state )
   _XBST_UINT( stateMask )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( LVHITTESTINFO )
   _XBST_POINT( pt )
   _XBST_UINT( flags )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_int( iGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LVINSERTGROUPSORTED )
   _XBST_POINTER32( pfnGroupCompare )
   _XBST_POINTER32( pvData )
   _XBST_LVGROUP( lvGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LVINSERTMARK )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwFlags )
   _XBST_int( iItem )
   _XBST_DWORD( dwReserved )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( LVITEMINDEX )
   _XBST_int( iItem )
   _XBST_int( iGroup )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LVSETINFOTIP )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwFlags )
   _XBST_POINTER32( pszText ) // LPWSTR
   _XBST_int( iItem )
   _XBST_int( iSubItem )
   _XBST_HBITMAP( hbmp )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LVTILEINFO )
   _XBST_UINT   ( cbSize )
   _XBST_int    ( iItem )
   _XBST_UINT   ( cColumns )
   _XBST_POINTER32( puColumns )
   _XBST_POINTER32   ( piColFmt )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LVTILEVIEWINFO )
   _XBST_UINT( cbSize )
   _XBST_DWORD( dwMask )
   _XBST_DWORD( dwFlags )
   _XBST_SIZE( sizeTile )
   _XBST_int( cLines )
   _XBST_RECT( rcLabelMargin )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMLVCACHEHINT )
   _XBST_NMHDR( hdr )
   _XBST_int( iFrom )
   _XBST_int( iTo )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMLVDISPINFO )
   _XBST_NMHDR( hdr )
   _XBST_LVITEM( item )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLVEMPTYMARKUP )
   _XBST_NMHDR( hdr )
   _XBST_DWORD( dwFlags )
   _XBST_SZWSTR( szMarkup , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLVFINDITEM )
   _XBST_NMHDR( hdr )
   _XBST_int( iStart )
   _XBST_LVFINDINFO( lvfi )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMLVKEYDOWN )
   _XBST_NMHDR( hdr )
   _XBST_WORD( wVKey )
   _XBST_UINT( flags )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLVLINK )
   _XBST_NMHDR( hdr )
   _XBST_LITEM( link )
   _XBST_int( iItem )
   _XBST_int( iSubItem )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLVODSTATECHANGE )
   _XBST_NMHDR( hdr )
   _XBST_int( iFrom )
   _XBST_int( iTo )
   _XBST_UINT( uNewState )
   _XBST_UINT( uOldState )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLVSCROLL )
   _XBST_NMHDR( hdr )
   _XBST_int( dx )
   _XBST_int( dy )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( LITEM )
   _XBST_UINT( mask )
   _XBST_int( iLink )
   _XBST_UINT( state )
   _XBST_UINT( stateMask )
   _XBST_SZWSTR( szID  , 48 )
   _XBST_SZWSTR( szUrl , (2048 + 32 + sizeof("://")) )
XB_END_STRUCTURE
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( COLORSCHEME )
   _XBST_DWORD ( dwSize  )
   _XBST_COLORREF ( clrBtnHighlight  )
   _XBST_COLORREF ( clrBtnShadow  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DPASTREAMINFO )
   _XBST_int ( iPos  )
   _XBST_LPVOID ( pvItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMCHAR )
   _XBST_NMHDR ( hdr         )
   _XBST_UINT  ( ch          )
   _XBST_DWORD ( dwItemPrev  )
   _XBST_DWORD ( dwItemNext  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMCUSTOMSPLITRECTINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcClient  )
   _XBST_RECT ( rcButton  )
   _XBST_RECT ( rcSplit  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMKEY )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( nVKey  )
   _XBST_UINT ( uFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMMOUSE )
   _XBST_NMHDR ( hdr  )
   _XBST_POINTER32 ( dwItemSpec  )
   _XBST_POINTER32 ( dwItemData  )
   _XBST_POINT ( pt  )
   _XBST_LPARAM ( dwHitInfo  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMOBJECTNOTIFY )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_POINTER32 ( piid  )
   _XBST_POINTER32 ( pObject  )
   _XBST_HRESULT ( hResult  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTOOLTIPSCREATED )
   _XBST_NMHDR ( hdr  )
   _XBST_HWND ( hwndToolTips  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( BUTTON_IMAGELIST )
   _XBST_HIMAGELIST ( himl  )
   _XBST_RECT ( margin  )
   _XBST_UINT ( uAlign  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( BUTTON_SPLITINFO )
   _XBST_UINT ( mask  )
   _XBST_HIMAGELIST ( himlGlyph  )
   _XBST_UINT ( uSplitStyle  )
   _XBST_SIZE ( size  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMBCDROPDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMBCHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( MEASUREITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_UINT ( itemID  )
   _XBST_UINT ( itemWidth  )
   _XBST_UINT ( itemHeight  )
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMCBEDRAGBEGIN )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItemid  )
   _XBST_CHAR ( szText  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMCBEENDEDIT )
   _XBST_NMHDR ( hdr  )
   _XBST_BOOL ( fChanged  )
   _XBST_int ( iNewSelection  )
   _XBST_TCHAR ( szText  )
   _XBST_int ( iWhy  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMCOMBOBOXEX )
   _XBST_NMHDR ( hdr  )
   _XBST_COMBOBOXEXITEM ( ceItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMDATETIMECHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_DWORD ( dwFlags  )
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMDATETIMEFORMAT )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SYSTEMTIME ( st  )
   _XBST_LPSTR ( pszDisplay  )
   _XBST_TCHAR ( szDisplay  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMDATETIMEFORMATQUERY )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SIZE ( szMax  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMDATETIMESTRING )
   _XBST_NMHDR ( nmhdr  )
   _XBST_LPSTR ( pszUserString  )
   _XBST_SYSTEMTIME ( st  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMDATETIMEWMKEYDOWN )
   _XBST_NMHDR ( nmhdr  )
   _XBST_int ( nVirtKey  )
   _XBST_LPSTR ( pszFormat  )
   _XBST_SYSTEMTIME ( st  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DRAGLISTINFO )
   _XBST_UINT ( uNotification  )
   _XBST_HWND ( hWnd  )
   _XBST_POINT ( ptCursor  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( EDITBALLOONTIP )
   _XBST_DWORD ( cbStruct  )
   _XBST_POINTER32 ( pszTitle  )
   _XBST_POINTER32 ( pszText  )
   _XBST_INT ( ttiIcon  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HDHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
   _XBST_int ( iItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( HDLAYOUT )
   _XBST_POINTER32  ( prc  )
   _XBST_POINTER32  ( pwpos  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HDTEXTFILTER )
   _XBST_LPSTR ( pszText  )
   _XBST_INT ( cchTextMax  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMHDFILTERBTNCLICK )
   _XBST_NMHDR ( hdr  )
   _XBST_INT ( iItem  )
   _XBST_RECT ( rc  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMHEADER )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_int ( iButton  )
   _XBST_POINTER32 ( pitem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMIPADDRESS )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iField  )
   _XBST_int ( iValue  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( DELETEITEMSTRUCT )
   _XBST_UINT ( CtlType  )
   _XBST_UINT ( CtlID  )
   _XBST_UINT ( itemID  )
   _XBST_HWND ( hwndItem  )
   _XBST_POINTER32 ( itemData  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMDAYSTATE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_SYSTEMTIME ( stStart  )
   _XBST_int ( cDayState  )
   _XBST_POINTER32( prgDayState  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMSELCHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_SYSTEMTIME ( stSelStart  )
   _XBST_SYSTEMTIME ( stSelEnd  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMVIEWCHANGE )
   _XBST_NMHDR ( nmhdr  )
   _XBST_DWORD ( dwOldView  )
   _XBST_DWORD ( dwNewView  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMPGCALCSIZE )
   _XBST_NMHDR ( hdr  )
   _XBST_DWORD ( dwFlag  )
   _XBST_int ( iWidth  )
   _XBST_int ( iHeight  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMPGHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( idOld  )
   _XBST_int ( idNew  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( PBRANGE )
   _XBST_int ( iLow  )
   _XBST_int ( iHigh  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMREBARSPLITTER )
   _XBST_NMHDR ( hdr  )
   _XBST_RECT ( rcSizing  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( LHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMLINK )
   _XBST_NMHDR ( hdr  )
   _XBST_LITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTCKEYDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_WORD ( wVKey  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TCHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TCITEMHEADER )
   _XBST_UINT ( mask  )
   _XBST_UINT ( lpReserved1  )
   _XBST_UINT ( lpReserved2  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iImage  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( COLORMAP )
   _XBST_COLORREF ( from  )
   _XBST_COLORREF ( to  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMTBGETINFOTIP )
   _XBST_NMHDR ( hdr  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_int ( iItem  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTBHOTITEM )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( idOld  )
   _XBST_int ( idNew  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMTOOLBAR )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iItem  )
   _XBST_TBBUTTON ( tbButton  )
   _XBST_int ( cchText  )
   _XBST_LPSTR ( pszText  )
   _XBST_RECT ( rcButton  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TBADDBITMAP )
   _XBST_HINSTANCE ( hInst  )
   _XBST_POINTER32 ( nID  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TBINSERTMARK )
   _XBST_int ( iButton  )
   _XBST_DWORD ( dwFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TBREPLACEBITMAP )
   _XBST_HINSTANCE ( hInstOld  )
   _XBST_POINTER32 ( nIDOld  )
   _XBST_HINSTANCE ( hInstNew  )
   _XBST_POINTER32 ( nIDNew  )
   _XBST_int ( nButtons  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TBSAVEPARAMS )
   _XBST_HANDLE ( hkr  )
   _XBST_LPSTR ( pszSubKey  )
   _XBST_LPSTR ( pszValueName  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTTCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW ( nmcd  )
   _XBST_UINT ( uDrawFlags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TTGETTITLE )
   _XBST_DWORD ( dwSize  )
   _XBST_UINT ( uTitleBitmap  )
   _XBST_UINT ( cch  )
   _XBST_POINTER32 ( pszTitle  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TTHITTESTINFO )
   _XBST_HWND ( hwnd  )
   _XBST_POINT ( pt  )
   _XBST_TOOLINFO ( ti  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTREEVIEW )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( action  )
   _XBST_TVITEM ( itemOld  )
   _XBST_TVITEM ( itemNew  )
   _XBST_POINT ( ptDrag  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( NMTVCUSTOMDRAW )
   _XBST_NMCUSTOMDRAW ( nmcd  )
   _XBST_COLORREF ( clrText  )
   _XBST_COLORREF ( clrTextBk  )
   _XBST_int ( iLevel  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVDISPINFO )
   _XBST_NMHDR ( hdr  )
   _XBST_TVITEM ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVDISPINFOEX )
   _XBST_NMHDR ( hdr  )
   _XBST_TVITEMEX ( item  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVGETINFOTIP )
   _XBST_NMHDR ( hdr  )
   _XBST_LPSTR ( pszText  )
   _XBST_int ( cchTextMax  )
   _XBST_HANDLE ( hItem  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVITEMCHANGE )
   _XBST_NMHDR ( hdr  )
   _XBST_UINT ( uChanged  )
   _XBST_HANDLE ( hItem  )
   _XBST_UINT ( uStateNew  )
   _XBST_UINT ( uStateOld  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVKEYDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_WORD ( wVKey  )
   _XBST_UINT ( flags  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMTVSTATEIMAGECHANGING )
   _XBST_NMHDR ( hdr  )
   _XBST_HANDLE ( hti  )
   _XBST_int ( iOldStateImageIndex  )
   _XBST_int ( iNewStateImageIndex  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TVGETITEMPARTRECTINFO )
   _XBST_HANDLE ( hti  )
   _XBST_POINTER32 ( prc  )
   _XBST_int ( partID  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TVHITTESTINFO )
   _XBST_POINT ( pt  )
   _XBST_UINT ( flags  )
   _XBST_HANDLE ( hItem  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( TVINSERTSTRUCT )
   _XBST_HANDLE ( hParent  )
   _XBST_HANDLE ( hInsertAfter  )
pc->GwstBeginUnion();
   _XBST_TVITEMEX ( itemex  )
   _XBST_TVITEM ( item  )
pc->GwstEndUnion();
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( TVITEMEX )
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
XB_BEGIN_STRUCTURE( TVSORTCB )
   _XBST_HANDLE ( hParent  )
   _XBST_POINTER32 ( lpfnCompare  )
   _XBST_LPARAM ( lParam  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( NMUPDOWN )
   _XBST_NMHDR ( hdr  )
   _XBST_int ( iPos  )
   _XBST_int ( iDelta  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( UDACCEL )
   _XBST_UINT ( nSec  )
   _XBST_UINT ( nInc  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( INTERNET_ASYNC_RESULT )
   _XBST_DWORD( dwResult );
   _XBST_DWORD( dwError  );
XB_END_STRUCTURE   
// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_DIAGNOSTIC_SOCKET_INFO )
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Socket    )); _XBST_DWORD( Socket      );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,SourcePort)); _XBST_DWORD( SourcePort  );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,DestPort  )); _XBST_DWORD( DestPort    );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_DIAGNOSTIC_SOCKET_INFO ,Flags     )); _XBST_DWORD( Flags       );
   pc->GwstSetOffset(sizeof(INTERNET_DIAGNOSTIC_SOCKET_INFO));
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_PROXY_INFO )
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,dwAccessType   )); _XBST_DWORD      ( dwAccessType                 );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxy      )); _XBST_LPSTR_DYNSZ( lpszProxy      , cProxy      );
   pc->GwstSetOffset(FIELD_OFFSET( INTERNET_PROXY_INFO,lpszProxyBypass)); _XBST_LPSTR_DYNSZ( lpszProxyBypass, cProxyBypass);
   pc->GwstSetOffset(sizeof(INTERNET_PROXY_INFO));
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION___VALUE )
   _XBST_DWORD        ( dwValue   );
   _XBST_LPSTR_DYNSZ  ( pszValue  , cValue );
   _XBST_FILETIME     ( ftValue   );
   pc->GwstSetOffset( RTL_FIELD_SIZE(INTERNET_PER_CONN_OPTION, Value) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION )
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,dwOption));   _XBST_DWORD(                            dwOption            );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION ,Value   ));   _XBST_INTERNET_PER_CONN_OPTION___VALUE( Value               );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

XB_BEGIN_STRUCTURE( INTERNET_PER_CONN_OPTION_LIST )
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwSize        )); _XBST_DWORD     ( dwSize        );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pszConnection )); _XBST_LPSTR_DYNSZ( pszConnection , cConnection);
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionCount )); _XBST_DWORD     ( dwOptionCount );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , dwOptionError )); _XBST_DWORD     ( dwOptionError );
   pc->GwstSetOffset(FIELD_OFFSET(INTERNET_PER_CONN_OPTION_LIST , pOptions      )); _XBST_POINTER32 ( pOptions      );
   pc->GwstSetOffset( sizeof( INTERNET_PER_CONN_OPTION_LIST) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_VERSION_INFO )
   _XBST_DWORD ( dwMajorVersion  )
   _XBST_DWORD ( dwMinorVersion  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( HTTP_VERSION_INFO )
   _XBST_DWORD( dwMajorVersion )
   _XBST_DWORD( dwMinorVersion )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_CONNECTED_INFO )
   _XBST_DWORD( dwConnectedState )
   _XBST_DWORD( dwFlags          )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( OUTGOINGCOOKIESTATE  )
   _XBST_int   ( cSent         )
   _XBST_int   ( cSuppressed   )
   _XBST_LPSTR_DYNSZ ( pszLocation  , cLocation )
   pc->GwstSetOffset( sizeof( OutgoingCookieState) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNETCOOKIEHISTORY )
   _XBST_BOOL ( fAccepted    );
   _XBST_BOOL ( fLeashed     );
   _XBST_BOOL ( fDowngraded  );
   _XBST_BOOL ( fRejected    );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( COOKIEDECISION         )
   _XBST_DWORD ( dwCookieState  )
   _XBST_BOOL  ( fAllowSession  )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( INTERNET_AUTH_NOTIFY_DATA   )
   _XBST_DWORD ( cbStruct    )
   _XBST_DWORD ( dwOptions   )
   _XBST_DWORD ( pfnNotify   )
   _XBST_DWORD ( dwContext   )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( INTERNET_CACHE_TIMESTAMPS  )
   _XBST_FILETIME(  ftExpires      );
   _XBST_FILETIME(  ftLastModified );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
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
XB_BEGIN_STRUCTURE( AUTO_PROXY_SCRIPT_BUFFER )

   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwStructSize        ));_XBST_DWORD( dwStructSize        )
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,lpszScriptBuffer    ));_XBST_LPSTR_DYNSZ( lpszScriptBuffer , cScriptBuffer )
   pc->GwstSetOffset(FIELD_OFFSET(  AUTO_PROXY_SCRIPT_BUFFER,dwScriptBufferSize  ));_XBST_DWORD( dwScriptBufferSize  )
   pc->GwstSetOffset( sizeof( AUTO_PROXY_SCRIPT_BUFFER) );
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE(TRACKMOUSEEVENT )
   _XBST_DWORD( cbSize)
   _XBST_DWORD( dwFlags)
   _XBST_HWND  (hwndTrack)
   _XBST_DWORD( dwHoverTime)
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( MOUSEMOVEPOINT )
	_XBST_int(x)
	_XBST_int(y)
	_XBST_DWORD(time)
	_XBST_ULONG_PTR(dwExtraInfo )
XB_END_STRUCTURE
//----------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE( PREVENT_MEDIA_REMOVAL )
_XBST_BYTE( PreventMediaRemoval	)
pc->GwstSetOffset(sizeof(PREVENT_MEDIA_REMOVAL));
XB_END_STRUCTURE
// ---------------------------------------------------------------------------------------------------------------------
XB_BEGIN_STRUCTURE(SHFILEINFO)
_XBST_HICON(hIcon)
_XBST_int(iIcon)
_XBST_DWORD(dwAttributes)
_XBST_SZSTR(szDisplayName, MAX_PATH)
_XBST_SZSTR(szTypeName, 80);
pc->GwstSetOffset(sizeof(SHFILEINFOA));
XB_END_STRUCTURE
// ---------------------------------------------------------------------------------------------------------------------
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
