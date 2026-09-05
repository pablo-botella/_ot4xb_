//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
LONG resource_tool_base_t::GdiGetCharDimensions(HDC hDC, TEXTMETRIC * pTm , LONG * pHeight )
{
    static const CHAR _alphabet_[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    SIZE sz;
    if(pTm && !GetTextMetrics(hDC, pTm)) return 0;
    if(!GetTextExtentPoint32(hDC, _alphabet_ , 52, &sz)) return 0;
    if(pHeight) pHeight[0] = sz.cy;
    return (LONG) ( ((sz.cx / 26) + 1) / 2);
}
// -----------------------------------------------------------------------------------------------------------------
