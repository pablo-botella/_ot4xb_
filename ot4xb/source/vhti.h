//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall ot4xb_IsAppThemed(void);
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API HTHEME __stdcall vhti_OpenThemeData(HWND,LPCWSTR);
OT4XB_API HTHEME __stdcall vhti_OpenThemeDataEx(HWND,LPCWSTR,DWORD);
OT4XB_API HRESULT __stdcall vhti_CloseThemeData(HTHEME);
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackground(HTHEME,HDC,int,int,RECT*,RECT*);
OT4XB_API HRESULT __stdcall vhti_DrawThemeText(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,DWORD,RECT*);
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundContentRect(HTHEME,HDC,int,int,RECT*,LPRECT);
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundExtent(HTHEME,HDC,int,int,RECT*,LPRECT);
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundRegion(HTHEME,HDC,int,int,RECT*,HRGN*);
OT4XB_API HRESULT __stdcall vhti_GetThemePartSize(HTHEME,HDC,int,int,RECT*,THEMESIZE,SIZE*);
OT4XB_API HRESULT __stdcall vhti_GetThemeTextExtent(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,RECT*,LPRECT);
OT4XB_API HRESULT __stdcall vhti_GetThemeTextMetrics(HTHEME,HDC,int,int,TEXTMETRICW*);
OT4XB_API HRESULT __stdcall vhti_HitTestThemeBackground(HTHEME,HDC,int,int,DWORD,RECT*,HRGN,POINT,WORD*);
OT4XB_API HRESULT __stdcall vhti_DrawThemeEdge(HTHEME,HDC,int,int,RECT*,UINT,UINT,LPRECT);
OT4XB_API HRESULT __stdcall vhti_DrawThemeIcon(HTHEME,HDC,int,int,RECT*,HIMAGELIST,int);
OT4XB_API BOOL __stdcall vhti_IsThemePartDefined(HTHEME,int,int);
OT4XB_API BOOL __stdcall vhti_IsThemeBackgroundPartiallyTransparent(HTHEME,int,int);
OT4XB_API HRESULT __stdcall vhti_GetThemeColor(HTHEME,int,int,int,COLORREF*);
OT4XB_API HRESULT __stdcall vhti_GetThemeMetric(HTHEME,HDC,int,int,int,int*);
OT4XB_API HRESULT __stdcall vhti_GetThemeString(HTHEME,int,int,int,LPWSTR,int);
OT4XB_API HRESULT __stdcall vhti_GetThemeBool(HTHEME,int,int,int,BOOL*);
OT4XB_API HRESULT __stdcall vhti_GetThemeInt(HTHEME,int,int,int,int*);
OT4XB_API HRESULT __stdcall vhti_GetThemeEnumValue(HTHEME,int,int,int,int*);
OT4XB_API HRESULT __stdcall vhti_GetThemePosition(HTHEME,int,int,int,POINT*);
OT4XB_API HRESULT __stdcall vhti_GetThemeFont(HTHEME,HDC,int,int,int,LOGFONTW*);
OT4XB_API HRESULT __stdcall vhti_GetThemeRect(HTHEME,int,int,int,LPRECT);
OT4XB_API HRESULT __stdcall vhti_GetThemeMargins(HTHEME,HDC,int,int,int,RECT*,MARGINS*);
OT4XB_API HRESULT __stdcall vhti_GetThemeIntList(HTHEME,int,int,int,INTLIST*);
OT4XB_API HRESULT __stdcall vhti_GetThemePropertyOrigin(HTHEME,int,int,int,PROPERTYORIGIN*);
OT4XB_API HRESULT __stdcall vhti_SetWindowTheme(HWND,LPCWSTR,LPCWSTR);
OT4XB_API HRESULT __stdcall vhti_GetThemeFilename(HTHEME,int,int,int,LPWSTR,int);
OT4XB_API COLORREF __stdcall vhti_GetThemeSysColor(HTHEME,int);
OT4XB_API HBRUSH __stdcall vhti_GetThemeSysColorBrush(HTHEME,int);
OT4XB_API BOOL __stdcall vhti_GetThemeSysBool(HTHEME,int);
OT4XB_API int __stdcall vhti_GetThemeSysSize(HTHEME,int);
OT4XB_API HRESULT __stdcall vhti_GetThemeSysFont(HTHEME,int,LOGFONTW*);
OT4XB_API HRESULT __stdcall vhti_GetThemeSysString(HTHEME,int,LPWSTR,int);
OT4XB_API HRESULT __stdcall vhti_GetThemeSysInt(HTHEME,int,int*);
OT4XB_API BOOL __stdcall vhti_IsThemeActive(void);
OT4XB_API BOOL __stdcall vhti_IsAppThemed(void);
OT4XB_API HTHEME __stdcall vhti_GetWindowTheme(HWND);
OT4XB_API HRESULT __stdcall vhti_EnableThemeDialogTexture(HWND,DWORD);
OT4XB_API BOOL __stdcall vhti_IsThemeDialogTextureEnabled(HWND);
OT4XB_API DWORD __stdcall vhti_GetThemeAppProperties(void);
OT4XB_API void __stdcall vhti_SetThemeAppProperties(DWORD);
OT4XB_API HRESULT __stdcall vhti_GetCurrentThemeName(LPWSTR,int,LPWSTR,int,LPWSTR,int);
OT4XB_API HRESULT __stdcall vhti_GetThemeDocumentationProperty(LPCWSTR,LPCWSTR,LPWSTR,int);
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackground(HWND,HDC,RECT*);
OT4XB_API HRESULT __stdcall vhti_EnableTheming(BOOL);
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackgroundEx(HTHEME,HDC,int,int,RECT*,DTBGOPTS*);
OT4XB_API HRESULT __stdcall vhti_BufferedPaintInit(void);
OT4XB_API HRESULT __stdcall vhti_BufferedPaintUnInit(void);
OT4XB_API HANDLE __stdcall vhti_BeginBufferedPaint(HDC,RECT*,BP_BUFFERFORMAT,BP_PAINTPARAMS*,HDC*);
OT4XB_API HRESULT __stdcall vhti_EndBufferedPaint(HANDLE,BOOL);
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintTargetRect(HANDLE,RECT*);
OT4XB_API HDC __stdcall vhti_GetBufferedPaintTargetDC(HANDLE);
OT4XB_API HDC __stdcall vhti_GetBufferedPaintDC(HANDLE);
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintBits(HANDLE,RGBQUAD**,int*);
OT4XB_API HRESULT __stdcall vhti_BufferedPaintClear(HANDLE,RECT*);
OT4XB_API HRESULT __stdcall vhti_BufferedPaintSetAlpha(HANDLE,RECT*,BYTE);
OT4XB_API HRESULT __stdcall vhti_BufferedPaintStopAllAnimations(HWND);
OT4XB_API HANDLE __stdcall vhti_BeginBufferedAnimation(HWND,HDC,RECT*,BP_BUFFERFORMAT,BP_PAINTPARAMS*,BP_ANIMATIONPARAMS*,HDC*,HDC*);
OT4XB_API HRESULT __stdcall vhti_EndBufferedAnimation(HANDLE,BOOL);
OT4XB_API BOOL __stdcall vhti_BufferedPaintRenderAnimation(HWND,HDC);
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackgroundEx(HWND,HDC,DWORD,RECT*);
OT4XB_API HRESULT __stdcall vhti_GetThemeBitmap(HTHEME,int,int,int,ULONG,HBITMAP*);
OT4XB_API HRESULT __stdcall vhti_GetThemeStream(HTHEME,int,int,int,void**,DWORD*,HINSTANCE);
OT4XB_API HRESULT __stdcall vhti_GetThemeTransitionDuration(HTHEME,int,int,int,int,DWORD*);
OT4XB_API BOOL __stdcall vhti_IsCompositionActive(void);
OT4XB_API HRESULT __stdcall vhti_SetWindowThemeAttribute(HWND,WINDOWTHEMEATTRIBUTETYPE,PVOID,DWORD);
OT4XB_API HRESULT __stdcall vhti_DrawThemeTextEx(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,LPRECT,DTTOPTS*);
//-------------------------------------------------------------------------------------------------------------------------
END_EXTERN_C
