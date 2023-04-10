#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
#define HLSMAX                    240    /* H,L, and S vary over 0-HLSMAX */
#define RGBMAX                    255    /* R,G, and B vary over 0-RGBMAX */
// -----------------------------------------------------------------------------------------------------------------
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB( int r, int g, int b)
{
   return RGB(r,g,b);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2R(COLORREF rgb){ return (DWORD) GetRValue(rgb); }
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2G(COLORREF rgb){ return (DWORD) GetGValue(rgb); }
extern "C" DWORD OT4XB_API __cdecl ot4xb_RGB2B(COLORREF rgb){ return (DWORD) GetBValue(rgb); }
// -----------------------------------------------------------------------------------------------------------------
extern "C" COLORREF OT4XB_API __cdecl ot4xb_ARGB2RGB(DWORD argb)
{
   return RGB( ((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF) , (argb & 0xFF) );
}
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
extern "C" COLORREF OT4XB_API __cdecl ot4xb_HSL2RGB( int h , int s , int l )
{  
   int r = 0;
   int g = 0;
   int b = 0;
   hsl2rgb(h,s,l,r,g,b);
   return RGB( r,g,b);
}
// -----------------------------------------------------------------------------------------------------------------
extern "C" void OT4XB_API __cdecl ot4xb_RGB2HSL( COLORREF rgb , int* ph , int* ps , int* pl )
{                                                              
   rgb2hsl(GetRValue(rgb),GetGValue(rgb),GetBValue(rgb),*ph,*ps,*pl);
}
// -----------------------------------------------------------------------------------------------------------------
