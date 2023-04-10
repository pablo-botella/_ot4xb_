//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
using namespace Gdiplus;
//----------------------------------------------------------------------------------------------------------------------
typedef GpStatus(WINGDIPAPI GdipGetImageEncodersSize_ft)(UINT*, UINT*);
typedef GpStatus(WINGDIPAPI GdipGetImageEncoders_ft)(UINT, UINT size, ImageCodecInfo*);
static GdipGetImageEncodersSize_ft* fpGetImageEncodersSize = (GdipGetImageEncodersSize_ft*)0;
static GdipGetImageEncoders_ft* fpGetImageEncoders = (GdipGetImageEncoders_ft*)0;
static HMODULE hGdiplusDll = (HMODULE)0;
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE(gdiplus_helper_ns)

BOOL  load_gdiplus_table()
{
   if (!hGdiplusDll)
   {
      hGdiplusDll = LoadLibrary("gdiplus.dll");
      if (hGdiplusDll)
      {
         fpGetImageEncodersSize = (GdipGetImageEncodersSize_ft*)GetProcAddress(hGdiplusDll, "GdipGetImageEncodersSize");
         fpGetImageEncoders = (GdipGetImageEncoders_ft*)GetProcAddress(hGdiplusDll, "GdipGetImageEncoders");
      }
   }
   if (fpGetImageEncodersSize && fpGetImageEncoders)
   {
      return TRUE;
   }
   return FALSE;
}
// ----------------------------------------------------------------------------------------------------------------------
static void method_get_encoder_clsid(TXbClsParams* px)
{
   if (load_gdiplus_table())
   {
      if (px->CheckParamType(1, XPP_CHARACTER))
      {
         ULONG p1_cb = 0;
         LPSTR p1 = px->ParamLockStr(1, &p1_cb);
         LPWSTR format = mb2w(p1, (int)p1_cb, 0, 0);
         UINT  num = 0;          // number of image encoders
         UINT  size = 0;         // size of the image encoder array in bytes

         ImageCodecInfo* pImageCodecInfo = NULL;
         fpGetImageEncodersSize(&num, &size);

         if (size > 0)
         {
            pImageCodecInfo = (ImageCodecInfo*)(_xgrab(size));
            if (pImageCodecInfo)
            {
               if (fpGetImageEncoders(num, size, pImageCodecInfo) == 0)
               {
                  for (UINT j = 0; j < num; ++j)
                  {
                     const WCHAR* mt = pImageCodecInfo[j].MimeType;
                     if (mt)
                     {
                        if (wcscmp(mt, format) == 0)
                        {
                           px->PutReturnStrLen((LPSTR)&pImageCodecInfo[j].Clsid, sizeof(CLSID));
                           j = num + 1;
                        }
                     }
                  }
               }
               _xfree((void*)pImageCodecInfo);
               pImageCodecInfo = NULL;
            }
         }
      }
   }
}
// -----------------------------------------------------------------------------------------------------------------
static void method_font_spec(TXbClsParams* px)
{
   if (px->CheckParamType(1, XPP_CHARACTER) && px->CheckParamType(2, XPP_NUMERIC))
   {
      ULONG cb = 0;
      LPSTR pfa = px->ParamLockStr(1, &cb);
      int   cc = MultiByteToWideChar(CP_ACP, 0, pfa, (int)cb, 0, 0);
      int   cbs = ((32 + (cc << 1) + 2) | 0x0F) + 1;
      font_spec_t* p = (font_spec_t*)_xgrab(cbs);
      p->cb = cbs;
      p->font_size = px->GetParamFloat(2);
      p->font_style = px->GetParamLong(3);
      p->font_name_length = cc;
      MultiByteToWideChar(CP_ACP, 0, pfa, cb, p->font_name, cc + 1);
      p->dw_crc_32 = dwCrc32(0, _mk_ptr_(LPBYTE, p, 8), (ULONG)cbs - 8);
      px->PutReturnStrLen((LPSTR)p, cbs);
      _xfree((void*)p);
   }
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
void AddXbMethods(TXbClass* pc)
{
   pc->ClassMethod("font_spec_t", method_font_spec, 3);
   pc->ClassMethod("get_encoder_clsid", method_get_encoder_clsid, 1 );
}
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE()
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
BEGIN_XBASE_CLASS(GDIPLUS_HELPER)
{
   gdiplus_helper_ns::AddXbMethods(pc);
}
END_XBASE_CLASS
// -----------------------------------------------------------------------------------------------------------------
