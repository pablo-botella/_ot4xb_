//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( gdiplus_helper_ns )
// -----------------------------------------------------------------------------------------------------------------
typedef struct tag_font_spec_t
{
   DWORD  cb;
   DWORD  dw_crc_32; // starting at pos 8 with size cb - 8
   float  font_size;
   int    font_style;
   LONG   reserved_4;   
   LONG   reserved_5;   
   LONG   reserved_6;   
   int    font_name_length;
   WCHAR  font_name[1];
} font_spec_t;
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------
