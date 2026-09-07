#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
#define HLSMAX                    240    /* H,L, and S vary over 0-HLSMAX */
#define RGBMAX                    255    /* R,G, and B vary over 0-RGBMAX */
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_RGB
            | syntax_: `DWORD ot4xb_RGB( int r, int g, int b )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_RGB( nRed, nGreen, nBlue )`
            | mangled-name: ot4xb_RGB
            | _kw_: RGB, COLORREF, color, colour, red green blue
   }}*/
/*{{|desc: Builds a COLORREF from its red, green and blue components (the RGB macro of the Windows API).
    | params:
    - `r` int - Red component, 0-255.
    - `g` int - Green component, 0-255.
    - `b` int - Blue component, 0-255.

    Returns DWORD - The COLORREF value, 0x00BBGGRR. }}*/
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB( int r, int g, int b)
{
   return RGB(r,g,b);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_RGB2R
            | syntax_: `DWORD ot4xb_RGB2R( COLORREF rgb )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_RGB2R( nRGB )`
            | mangled-name: ot4xb_RGB2R
            | _kw_: GetRValue, red, COLORREF, color component
   }}*/
/*{{|desc: Red component of a COLORREF (the GetRValue macro).
    | params:
    - `rgb` COLORREF - Colour value, 0x00BBGGRR.

    Returns DWORD - Red component, 0-255. }}*/
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2R(COLORREF rgb){ return (DWORD) GetRValue(rgb); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_RGB2G
            | syntax_: `DWORD ot4xb_RGB2G( COLORREF rgb )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_RGB2G( nRGB )`
            | mangled-name: ot4xb_RGB2G
            | _kw_: GetGValue, green, COLORREF, color component
   }}*/
/*{{|desc: Green component of a COLORREF (the GetGValue macro).
    | params:
    - `rgb` COLORREF - Colour value, 0x00BBGGRR.

    Returns DWORD - Green component, 0-255. }}*/
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2G(COLORREF rgb){ return (DWORD) GetGValue(rgb); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_RGB2B
            | syntax_: `DWORD ot4xb_RGB2B( COLORREF rgb )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_RGB2B( nRGB )`
            | mangled-name: ot4xb_RGB2B
            | _kw_: GetBValue, blue, COLORREF, color component
   }}*/
/*{{|desc: Blue component of a COLORREF (the GetBValue macro).
    | params:
    - `rgb` COLORREF - Colour value, 0x00BBGGRR.

    Returns DWORD - Blue component, 0-255. }}*/
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2B(COLORREF rgb){ return (DWORD) GetBValue(rgb); }
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_ARGB2RGB
            | syntax_: `COLORREF ot4xb_ARGB2RGB( DWORD argb )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_ARGB2RGB( nARGB )`
            | mangled-name: ot4xb_ARGB2RGB
            | _kw_: ARGB, COLORREF, GDI+, .NET color, alpha, convert color
   }}*/
/*{{|desc: Converts an ARGB value (0xAARRGGBB, the layout of GDI+ and .NET colours) into a COLORREF
      (0x00BBGGRR): the alpha byte is dropped and the red and blue bytes change places.
    | params:
    - `argb` DWORD - Colour as 0xAARRGGBB.

    Returns COLORREF - The same colour as 0x00BBGGRR, without alpha. }}*/
extern "C" COLORREF OT4XB_API __cdecl ot4xb_ARGB2RGB(DWORD argb)
{
   return RGB( ((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF) , (argb & 0xFF) );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static SHORT hue2rgb(SHORT n1, SHORT n2, SHORT hue)
{
   if( hue < 0 ) hue += HLSMAX;
   if( hue > HLSMAX ) hue -= HLSMAX;
   if( hue < HLSMAX / 6 ) return n1 + (((n2 - n1) * hue + (HLSMAX / 12)) / (HLSMAX / 6));
   if( hue < HLSMAX / 2 ) return n2;
   if( hue < HLSMAX * 2 / 3 ) return n1 + (((n2 - n1) * ((HLSMAX * 2 / 3) - hue) +(HLSMAX / 12)) / (HLSMAX / 6));
   return n1;
}
// -----------------------------------------------------------------------------------------------------------------
static void hsl2rgb(int hue, int sat, int lum, int& red, int& green, int& blue)
{
   SHORT Magic1, Magic2;
   if( sat == 0 )
   {
      red = green = blue = (lum * RGBMAX) / HLSMAX;
   }
   else
   {
      if( lum <= HLSMAX / 2 ) Magic2 = (SHORT) ((lum * (HLSMAX + sat) + (HLSMAX / 2)) / HLSMAX);
      else Magic2 = (SHORT) ( lum + sat - ((lum * sat) + (HLSMAX / 2)) / HLSMAX);
      Magic1 = (SHORT) ( 2 * lum - Magic2 );
      red = (hue2rgb(Magic1, Magic2, (SHORT) hue + (HLSMAX / 3)) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
      green = (hue2rgb(Magic1, Magic2, (SHORT) hue) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
      blue = (hue2rgb(Magic1, Magic2, (SHORT) hue - (HLSMAX / 3)) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
   }
   if( red < 0  )  red += RGBMAX;
   if( blue < 0 )  blue += RGBMAX;
   if( green < 0 ) green += RGBMAX;
}
// -----------------------------------------------------------------------------------------------------------------
static void rgb2hsl(int red, int green, int blue, int& hue, int& sat, int& lum)
{
   BYTE  cMax, cMin;
   SHORT Rdelta, Gdelta, Bdelta;
   
   cMax = (BYTE) max(max(red, green), blue);
   cMin = (BYTE) min(min(red, green), blue);
   lum = (((cMax + cMin) * HLSMAX) + RGBMAX) / (2 * RGBMAX);
   if( cMax == cMin )
   {
      sat = 0;
      hue = HLSMAX * 2 / 3;    /* hue */
   }
   else
   {
      if( lum <= HLSMAX / 2 ) sat = (((cMax - cMin) * HLSMAX) + ((cMax + cMin) / 2)) / (cMax + cMin);
      else sat = (((cMax - cMin) * HLSMAX) + ((2 * RGBMAX - cMax - cMin) / 2)) / (2 * RGBMAX - cMax - cMin);
      Rdelta = (SHORT) (((cMax - red) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
      Gdelta = (SHORT) (((cMax - green) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
      Bdelta = (SHORT) (((cMax - blue) * (HLSMAX / 6)) + ((cMax - cMin) / 2)) / (cMax - cMin);
      if( red == cMax ) hue = Bdelta - Gdelta;
      else if( green == cMax ) hue = (HLSMAX / 3) + Rdelta - Bdelta;
      else hue = ((2 * HLSMAX) / 3) + Gdelta - Rdelta;
      if( hue < 0 ) hue += HLSMAX;
      if( hue > HLSMAX ) hue -= HLSMAX;
   }
   if( sat < 0 ) sat += HLSMAX;
   if( lum < 0 ) lum += HLSMAX;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_HSL2RGB
            | syntax_: `COLORREF ot4xb_HSL2RGB( int h, int s, int l )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_HSL2RGB( nHue, nSat, nLum )`
            | mangled-name: ot4xb_HSL2RGB
            | _kw_: HSL, HLS, hue, saturation, luminance, ColorHLSToRGB, color
   }}*/
/*{{|desc: Converts hue, saturation and luminance to a COLORREF. The three components use the Windows HLS
      scale, 0-240 (HLSMAX), the one of the colour dialog of the system.
    | params:
    - `h` int - Hue, 0-240 (0 red, 80 green, 160 blue).
    - `s` int - Saturation, 0-240. With 0 the result is a grey level and the hue is ignored.
    - `l` int - Luminance, 0-240 (0 black, 240 white).

    Returns COLORREF - The colour as 0x00BBGGRR.

    |seealso: See also: {{ilink: <c-function ot4xb_RGB2HSL> ot4xb_RGB2HSL}} }}*/
extern "C" COLORREF OT4XB_API __cdecl ot4xb_HSL2RGB( int h , int s , int l )
{  
   int r = 0;
   int g = 0;
   int b = 0;
   hsl2rgb(h,s,l,r,g,b);
   return RGB( r,g,b);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_RGB2HSL
            | syntax_: `void ot4xb_RGB2HSL( COLORREF rgb, int* ph, int* ps, int* pl )`
            | category: winapi/color
            | xbase-syntax: `@ot4xb:ot4xb_RGB2HSL( nRGB, @nHue, @nSat, @nLum )`
            | mangled-name: ot4xb_RGB2HSL
            | _kw_: HSL, HLS, hue, saturation, luminance, ColorRGBToHLS, color
   }}*/
/*{{|desc: Converts a COLORREF to hue, saturation and luminance in the Windows HLS scale, 0-240 (HLSMAX),
      stored through the three pointers.
    | params:
    - `rgb` COLORREF - Colour value, 0x00BBGGRR.
    - `ph` int* - Receives the hue, 0-240. A grey level (equal red, green and blue) gives 160.
    - `ps` int* - Receives the saturation, 0-240 (0 for a grey level).
    - `pl` int* - Receives the luminance, 0-240.

    Returns void

    |seealso: See also: {{ilink: <c-function ot4xb_HSL2RGB> ot4xb_HSL2RGB}} }}*/
extern "C" void OT4XB_API __cdecl ot4xb_RGB2HSL( COLORREF rgb , int* ph , int* ps , int* pl )
{                                                              
   rgb2hsl(GetRValue(rgb),GetGValue(rgb),GetBValue(rgb),*ph,*ps,*pl);
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
