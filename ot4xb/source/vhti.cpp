//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <shlwapi.h>
/*{{begin-note-id}}*/
/*{{note-id: vhti-deprecated }}*/
/*{{|:
   Every function in this module is deprecated: they were born to keep ot4xb working on Windows
   versions older than XP and no longer make sense today. They remain only for compatibility
   with existing projects. }}*/
/*{{end-note-id}}*/
// -----------------------------------------------------------------------------------------------------------------
typedef HRESULT (__stdcall *ft_DLLGETVERSION)(DLLVERSIONINFO*);
//----------------------------------------------------------------------------------------------------------------------
typedef HTHEME   ( __stdcall * ft_OpenThemeData)(HWND,LPCWSTR);
typedef HTHEME   ( __stdcall * ft_OpenThemeDataEx)(HWND,LPCWSTR,DWORD);
typedef HRESULT  ( __stdcall * ft_CloseThemeData)(HTHEME);
typedef HRESULT  ( __stdcall * ft_DrawThemeBackground)(HTHEME,HDC,int,int,RECT*,RECT*);
typedef HRESULT  ( __stdcall * ft_DrawThemeText)(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,DWORD,RECT*);
typedef HRESULT  ( __stdcall * ft_GetThemeBackgroundContentRect)(HTHEME,HDC,int,int,RECT*,LPRECT);
typedef HRESULT  ( __stdcall * ft_GetThemeBackgroundExtent)(HTHEME,HDC,int,int,RECT*,LPRECT);
typedef HRESULT  ( __stdcall * ft_GetThemeBackgroundRegion)(HTHEME,HDC,int,int,RECT*,HRGN*);
typedef HRESULT  ( __stdcall * ft_GetThemePartSize)(HTHEME,HDC,int,int,RECT*,THEMESIZE,SIZE*);
typedef HRESULT  ( __stdcall * ft_GetThemeTextExtent)(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,RECT*,LPRECT);
typedef HRESULT  ( __stdcall * ft_GetThemeTextMetrics)(HTHEME,HDC,int,int,TEXTMETRICW*);
typedef HRESULT  ( __stdcall * ft_HitTestThemeBackground)(HTHEME,HDC,int,int,DWORD,RECT*,HRGN,POINT,WORD*);
typedef HRESULT  ( __stdcall * ft_DrawThemeEdge)(HTHEME,HDC,int,int,RECT*,UINT,UINT,LPRECT);
typedef HRESULT  ( __stdcall * ft_DrawThemeIcon)(HTHEME,HDC,int,int,RECT*,HIMAGELIST,int);
typedef BOOL     ( __stdcall * ft_IsThemePartDefined)(HTHEME,int,int);
typedef BOOL     ( __stdcall * ft_IsThemeBackgroundPartiallyTransparent)(HTHEME,int,int);
typedef HRESULT  ( __stdcall * ft_GetThemeColor)(HTHEME,int,int,int,COLORREF*);
typedef HRESULT  ( __stdcall * ft_GetThemeMetric)(HTHEME,HDC,int,int,int,int*);
typedef HRESULT  ( __stdcall * ft_GetThemeString)(HTHEME,int,int,int,LPWSTR,int);
typedef HRESULT  ( __stdcall * ft_GetThemeBool)(HTHEME,int,int,int,BOOL*);
typedef HRESULT  ( __stdcall * ft_GetThemeInt)(HTHEME,int,int,int,int*);
typedef HRESULT  ( __stdcall * ft_GetThemeEnumValue)(HTHEME,int,int,int,int*);
typedef HRESULT  ( __stdcall * ft_GetThemePosition)(HTHEME,int,int,int,POINT*);
typedef HRESULT  ( __stdcall * ft_GetThemeFont)(HTHEME,HDC,int,int,int,LOGFONTW*);
typedef HRESULT  ( __stdcall * ft_GetThemeRect)(HTHEME,int,int,int,LPRECT);
typedef HRESULT  ( __stdcall * ft_GetThemeMargins)(HTHEME,HDC,int,int,int,RECT*,MARGINS*);
typedef HRESULT  ( __stdcall * ft_GetThemeIntList)(HTHEME,int,int,int,INTLIST*);
typedef HRESULT  ( __stdcall * ft_GetThemePropertyOrigin)(HTHEME,int,int,int,PROPERTYORIGIN*);
typedef HRESULT  ( __stdcall * ft_SetWindowTheme)(HWND,LPCWSTR,LPCWSTR);
typedef HRESULT  ( __stdcall * ft_GetThemeFilename)(HTHEME,int,int,int,LPWSTR,int);
typedef COLORREF ( __stdcall * ft_GetThemeSysColor)(HTHEME,int);
typedef HBRUSH   ( __stdcall * ft_GetThemeSysColorBrush)(HTHEME,int);
typedef BOOL     ( __stdcall * ft_GetThemeSysBool)(HTHEME,int);
typedef int      ( __stdcall * ft_GetThemeSysSize)(HTHEME,int);
typedef HRESULT  ( __stdcall * ft_GetThemeSysFont)(HTHEME,int,LOGFONTW*);
typedef HRESULT  ( __stdcall * ft_GetThemeSysString)(HTHEME,int,LPWSTR,int);
typedef HRESULT  ( __stdcall * ft_GetThemeSysInt)(HTHEME,int,int*);
typedef BOOL     ( __stdcall * ft_IsThemeActive)(void);
typedef BOOL     ( __stdcall * ft_IsAppThemed)(void);
typedef HTHEME   ( __stdcall * ft_GetWindowTheme)(HWND);
typedef HRESULT  ( __stdcall * ft_EnableThemeDialogTexture)(HWND,DWORD);
typedef BOOL     ( __stdcall * ft_IsThemeDialogTextureEnabled)(HWND);
typedef DWORD    ( __stdcall * ft_GetThemeAppProperties)(void);
typedef void     ( __stdcall * ft_SetThemeAppProperties)(DWORD);
typedef HRESULT  ( __stdcall * ft_GetCurrentThemeName)(LPWSTR,int,LPWSTR,int,LPWSTR,int);
typedef HRESULT  ( __stdcall * ft_GetThemeDocumentationProperty)(LPCWSTR,LPCWSTR,LPWSTR,int);
typedef HRESULT  ( __stdcall * ft_DrawThemeParentBackground)(HWND,HDC,RECT*);
typedef HRESULT  ( __stdcall * ft_EnableTheming)(BOOL);
typedef HRESULT  ( __stdcall * ft_DrawThemeBackgroundEx)(HTHEME,HDC,int,int,RECT*,DTBGOPTS*);
typedef HRESULT  ( __stdcall * ft_BufferedPaintInit)(void);
typedef HRESULT  ( __stdcall * ft_BufferedPaintUnInit)(void);
typedef HANDLE   ( __stdcall * ft_BeginBufferedPaint)(HDC,RECT*,BP_BUFFERFORMAT,BP_PAINTPARAMS*,HDC*);
typedef HRESULT  ( __stdcall * ft_EndBufferedPaint)(HANDLE,BOOL);
typedef HRESULT  ( __stdcall * ft_GetBufferedPaintTargetRect)(HANDLE,RECT*);
typedef HDC      ( __stdcall * ft_GetBufferedPaintTargetDC)(HANDLE);
typedef HDC      ( __stdcall * ft_GetBufferedPaintDC)(HANDLE);
typedef HRESULT  ( __stdcall * ft_GetBufferedPaintBits)(HANDLE,RGBQUAD**,int*);
typedef HRESULT  ( __stdcall * ft_BufferedPaintClear)(HANDLE,RECT*);
typedef HRESULT  ( __stdcall * ft_BufferedPaintSetAlpha)(HANDLE,RECT*,BYTE);
typedef HRESULT  ( __stdcall * ft_BufferedPaintStopAllAnimations)(HWND);
typedef HANDLE   ( __stdcall * ft_BeginBufferedAnimation)(HWND,HDC,RECT*,BP_BUFFERFORMAT,BP_PAINTPARAMS*,BP_ANIMATIONPARAMS*,HDC*,HDC*);
typedef HRESULT  ( __stdcall * ft_EndBufferedAnimation)(HANDLE,BOOL);
typedef BOOL     ( __stdcall * ft_BufferedPaintRenderAnimation)(HWND,HDC);
typedef HRESULT  ( __stdcall * ft_DrawThemeParentBackgroundEx)(HWND,HDC,DWORD,RECT*);
typedef HRESULT  ( __stdcall * ft_GetThemeBitmap)(HTHEME,int,int,int,ULONG,HBITMAP*);
typedef HRESULT  ( __stdcall * ft_GetThemeStream)(HTHEME,int,int,int,void**,DWORD*,HINSTANCE);
typedef HRESULT  ( __stdcall * ft_GetThemeTransitionDuration)(HTHEME,int,int,int,int,DWORD*);
typedef BOOL     ( __stdcall * ft_IsCompositionActive)(void);
typedef HRESULT  ( __stdcall * ft_SetWindowThemeAttribute)(HWND,WINDOWTHEMEATTRIBUTETYPE,PVOID,DWORD);
typedef HRESULT  ( __stdcall * ft_DrawThemeTextEx)(HTHEME,HDC,int,int,LPCWSTR,int,DWORD,LPRECT,DTTOPTS*);
typedef HRESULT  ( __stdcall * ft__BufferedPaintMakeOpaque)(HPAINTBUFFER ,RECT*);
typedef HRESULT  ( __stdcall * ft__SetWindowThemeNonClientAttributes)(HWND,DWORD,DWORD);
// -----------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( vhti_ns )   
      // ---------------------------------------------------------------------------------
      static BOOL    _bIsManifiest_ = 0;
      static BOOL    _bInit_ = 0;      
      static HMODULE _hdll_  = 0;
      // ---------------------------------------------------------------------------------
      static ft_OpenThemeData OpenThemeData = 0;
      static ft_OpenThemeDataEx OpenThemeDataEx = 0;
      static ft_CloseThemeData CloseThemeData = 0;
      static ft_DrawThemeBackground DrawThemeBackground = 0;
      static ft_DrawThemeText DrawThemeText = 0;
      static ft_GetThemeBackgroundContentRect GetThemeBackgroundContentRect = 0;
      static ft_GetThemeBackgroundExtent GetThemeBackgroundExtent = 0;
      static ft_GetThemeBackgroundRegion GetThemeBackgroundRegion = 0;
      static ft_GetThemePartSize GetThemePartSize = 0;
      static ft_GetThemeTextExtent GetThemeTextExtent = 0;
      static ft_GetThemeTextMetrics GetThemeTextMetrics = 0;
      static ft_HitTestThemeBackground HitTestThemeBackground = 0;
      static ft_DrawThemeEdge DrawThemeEdge = 0;
      static ft_DrawThemeIcon DrawThemeIcon = 0;
      static ft_IsThemePartDefined IsThemePartDefined = 0;
      static ft_IsThemeBackgroundPartiallyTransparent IsThemeBackgroundPartiallyTransparent = 0;
      static ft_GetThemeColor GetThemeColor = 0;
      static ft_GetThemeMetric GetThemeMetric = 0;
      static ft_GetThemeString GetThemeString = 0;
      static ft_GetThemeBool GetThemeBool = 0;
      static ft_GetThemeInt GetThemeInt = 0;
      static ft_GetThemeEnumValue GetThemeEnumValue = 0;
      static ft_GetThemePosition GetThemePosition = 0;
      static ft_GetThemeFont GetThemeFont = 0;
      static ft_GetThemeRect GetThemeRect = 0;
      static ft_GetThemeMargins GetThemeMargins = 0;
      static ft_GetThemeIntList GetThemeIntList = 0;
      static ft_GetThemePropertyOrigin GetThemePropertyOrigin = 0;
      static ft_SetWindowTheme SetWindowTheme = 0;
      static ft_GetThemeFilename GetThemeFilename = 0;
      static ft_GetThemeSysColor GetThemeSysColor = 0;
      static ft_GetThemeSysColorBrush GetThemeSysColorBrush = 0;
      static ft_GetThemeSysBool GetThemeSysBool = 0;
      static ft_GetThemeSysSize GetThemeSysSize = 0;
      static ft_GetThemeSysFont GetThemeSysFont = 0;
      static ft_GetThemeSysString GetThemeSysString = 0;
      static ft_GetThemeSysInt GetThemeSysInt = 0;
      static ft_IsThemeActive IsThemeActive = 0;
      static ft_IsAppThemed IsAppThemed = 0;
      static ft_GetWindowTheme GetWindowTheme = 0;
      static ft_EnableThemeDialogTexture EnableThemeDialogTexture = 0;
      static ft_IsThemeDialogTextureEnabled IsThemeDialogTextureEnabled = 0;
      static ft_GetThemeAppProperties GetThemeAppProperties = 0;
      static ft_SetThemeAppProperties SetThemeAppProperties = 0;
      static ft_GetCurrentThemeName GetCurrentThemeName = 0;
      static ft_GetThemeDocumentationProperty GetThemeDocumentationProperty = 0;
      static ft_DrawThemeParentBackground DrawThemeParentBackground = 0;
      static ft_EnableTheming EnableTheming = 0;
      static ft_DrawThemeBackgroundEx DrawThemeBackgroundEx = 0;
      static ft_BufferedPaintInit BufferedPaintInit = 0;
      static ft_BufferedPaintUnInit BufferedPaintUnInit = 0;
      static ft_BeginBufferedPaint BeginBufferedPaint = 0;
      static ft_EndBufferedPaint EndBufferedPaint = 0;
      static ft_GetBufferedPaintTargetRect GetBufferedPaintTargetRect = 0;
      static ft_GetBufferedPaintTargetDC GetBufferedPaintTargetDC = 0;
      static ft_GetBufferedPaintDC GetBufferedPaintDC = 0;
      static ft_GetBufferedPaintBits GetBufferedPaintBits = 0;
      static ft_BufferedPaintClear BufferedPaintClear = 0;
      static ft_BufferedPaintSetAlpha BufferedPaintSetAlpha = 0;
      static ft_BufferedPaintStopAllAnimations BufferedPaintStopAllAnimations = 0;
      static ft_BeginBufferedAnimation BeginBufferedAnimation = 0;
      static ft_EndBufferedAnimation EndBufferedAnimation = 0;
      static ft_BufferedPaintRenderAnimation BufferedPaintRenderAnimation = 0;
      static ft_DrawThemeParentBackgroundEx DrawThemeParentBackgroundEx = 0;
      static ft_GetThemeBitmap GetThemeBitmap = 0;
      static ft_GetThemeStream GetThemeStream = 0;
      static ft_GetThemeTransitionDuration GetThemeTransitionDuration = 0;
      static ft_IsCompositionActive IsCompositionActive = 0;
      static ft_SetWindowThemeAttribute SetWindowThemeAttribute = 0;
      static ft_DrawThemeTextEx DrawThemeTextEx = 0;
      // ---------------------------------------------------------------------------------
      static void init( void )
      {
         if( _bInit_ ){ return;}
         _bInit_ = TRUE;
         _hdll_ = LoadLibrary("uxtheme");
         if(! _hdll_ ){ return;}  
         CRITICAL_SECTION* pcs = _drtool_get_pcs_();
         EnterCriticalSection( pcs );
         __try
         {
            // ---------
            {
               HMODULE hComCtl = LoadLibrary("comctl32.dll");
               if(hComCtl)
               {
                  ft_DLLGETVERSION fp = (ft_DLLGETVERSION) GetProcAddress(hComCtl,"DllGetVersion");
                  if( fp )
                  {
                     DLLVERSIONINFO dvi;
                     ZeroMemory( &dvi, sizeof( dvi));
                     dvi.cbSize = sizeof dvi;
                     if( (*fp)(&dvi) == NOERROR ){ _bIsManifiest_ = (BOOL) (dvi.dwMajorVersion >= 6); }
                  }
                  FreeLibrary( hComCtl );
               }
            }
            // ---------            
            OpenThemeData = (ft_OpenThemeData) GetProcAddress(_hdll_,"OpenThemeData");
            OpenThemeDataEx = (ft_OpenThemeDataEx) GetProcAddress(_hdll_,"OpenThemeDataEx");
            CloseThemeData = (ft_CloseThemeData) GetProcAddress(_hdll_,"CloseThemeData");
            DrawThemeBackground = (ft_DrawThemeBackground) GetProcAddress(_hdll_,"DrawThemeBackground");
            DrawThemeText = (ft_DrawThemeText) GetProcAddress(_hdll_,"DrawThemeText");
            GetThemeBackgroundContentRect = (ft_GetThemeBackgroundContentRect) GetProcAddress(_hdll_,"GetThemeBackgroundContentRect");
            GetThemeBackgroundExtent = (ft_GetThemeBackgroundExtent) GetProcAddress(_hdll_,"GetThemeBackgroundExtent");
            GetThemeBackgroundRegion = (ft_GetThemeBackgroundRegion) GetProcAddress(_hdll_,"GetThemeBackgroundRegion");
            GetThemePartSize = (ft_GetThemePartSize) GetProcAddress(_hdll_,"GetThemePartSize");
            GetThemeTextExtent = (ft_GetThemeTextExtent) GetProcAddress(_hdll_,"GetThemeTextExtent");
            GetThemeTextMetrics = (ft_GetThemeTextMetrics) GetProcAddress(_hdll_,"GetThemeTextMetrics");
            HitTestThemeBackground = (ft_HitTestThemeBackground) GetProcAddress(_hdll_,"HitTestThemeBackground");
            DrawThemeEdge = (ft_DrawThemeEdge) GetProcAddress(_hdll_,"DrawThemeEdge");
            DrawThemeIcon = (ft_DrawThemeIcon) GetProcAddress(_hdll_,"DrawThemeIcon");
            IsThemePartDefined = (ft_IsThemePartDefined) GetProcAddress(_hdll_,"IsThemePartDefined");
            IsThemeBackgroundPartiallyTransparent = (ft_IsThemeBackgroundPartiallyTransparent) GetProcAddress(_hdll_,"IsThemeBackgroundPartiallyTransparent");
            GetThemeColor = (ft_GetThemeColor) GetProcAddress(_hdll_,"GetThemeColor");
            GetThemeMetric = (ft_GetThemeMetric) GetProcAddress(_hdll_,"GetThemeMetric");
            GetThemeString = (ft_GetThemeString) GetProcAddress(_hdll_,"GetThemeString");
            GetThemeBool = (ft_GetThemeBool) GetProcAddress(_hdll_,"GetThemeBool");
            GetThemeInt = (ft_GetThemeInt) GetProcAddress(_hdll_,"GetThemeInt");
            GetThemeEnumValue = (ft_GetThemeEnumValue) GetProcAddress(_hdll_,"GetThemeEnumValue");
            GetThemePosition = (ft_GetThemePosition) GetProcAddress(_hdll_,"GetThemePosition");
            GetThemeFont = (ft_GetThemeFont) GetProcAddress(_hdll_,"GetThemeFont");
            GetThemeRect = (ft_GetThemeRect) GetProcAddress(_hdll_,"GetThemeRect");
            GetThemeMargins = (ft_GetThemeMargins) GetProcAddress(_hdll_,"GetThemeMargins");
            GetThemeIntList = (ft_GetThemeIntList) GetProcAddress(_hdll_,"GetThemeIntList");
            GetThemePropertyOrigin = (ft_GetThemePropertyOrigin) GetProcAddress(_hdll_,"GetThemePropertyOrigin");
            SetWindowTheme = (ft_SetWindowTheme) GetProcAddress(_hdll_,"SetWindowTheme");
            GetThemeFilename = (ft_GetThemeFilename) GetProcAddress(_hdll_,"GetThemeFilename");
            GetThemeSysColor = (ft_GetThemeSysColor) GetProcAddress(_hdll_,"GetThemeSysColor");
            GetThemeSysColorBrush = (ft_GetThemeSysColorBrush) GetProcAddress(_hdll_,"GetThemeSysColorBrush");
            GetThemeSysBool = (ft_GetThemeSysBool) GetProcAddress(_hdll_,"GetThemeSysBool");
            GetThemeSysSize = (ft_GetThemeSysSize) GetProcAddress(_hdll_,"GetThemeSysSize");
            GetThemeSysFont = (ft_GetThemeSysFont) GetProcAddress(_hdll_,"GetThemeSysFont");
            GetThemeSysString = (ft_GetThemeSysString) GetProcAddress(_hdll_,"GetThemeSysString");
            GetThemeSysInt = (ft_GetThemeSysInt) GetProcAddress(_hdll_,"GetThemeSysInt");
            IsThemeActive = (ft_IsThemeActive) GetProcAddress(_hdll_,"IsThemeActive");
            IsAppThemed = (ft_IsAppThemed) GetProcAddress(_hdll_,"IsAppThemed");
            GetWindowTheme = (ft_GetWindowTheme) GetProcAddress(_hdll_,"GetWindowTheme");
            EnableThemeDialogTexture = (ft_EnableThemeDialogTexture) GetProcAddress(_hdll_,"EnableThemeDialogTexture");
            IsThemeDialogTextureEnabled = (ft_IsThemeDialogTextureEnabled) GetProcAddress(_hdll_,"IsThemeDialogTextureEnabled");
            GetThemeAppProperties = (ft_GetThemeAppProperties) GetProcAddress(_hdll_,"GetThemeAppProperties");
            SetThemeAppProperties = (ft_SetThemeAppProperties) GetProcAddress(_hdll_,"SetThemeAppProperties");
            GetCurrentThemeName = (ft_GetCurrentThemeName) GetProcAddress(_hdll_,"GetCurrentThemeName");
            GetThemeDocumentationProperty = (ft_GetThemeDocumentationProperty) GetProcAddress(_hdll_,"GetThemeDocumentationProperty");
            DrawThemeParentBackground = (ft_DrawThemeParentBackground) GetProcAddress(_hdll_,"DrawThemeParentBackground");
            EnableTheming = (ft_EnableTheming) GetProcAddress(_hdll_,"EnableTheming");
            DrawThemeBackgroundEx = (ft_DrawThemeBackgroundEx) GetProcAddress(_hdll_,"DrawThemeBackgroundEx");
            BufferedPaintInit = (ft_BufferedPaintInit) GetProcAddress(_hdll_,"BufferedPaintInit");
            BufferedPaintUnInit = (ft_BufferedPaintUnInit) GetProcAddress(_hdll_,"BufferedPaintUnInit");
            BeginBufferedPaint = (ft_BeginBufferedPaint) GetProcAddress(_hdll_,"BeginBufferedPaint");
            EndBufferedPaint = (ft_EndBufferedPaint) GetProcAddress(_hdll_,"EndBufferedPaint");
            GetBufferedPaintTargetRect = (ft_GetBufferedPaintTargetRect) GetProcAddress(_hdll_,"GetBufferedPaintTargetRect");
            GetBufferedPaintTargetDC = (ft_GetBufferedPaintTargetDC) GetProcAddress(_hdll_,"GetBufferedPaintTargetDC");
            GetBufferedPaintDC = (ft_GetBufferedPaintDC) GetProcAddress(_hdll_,"GetBufferedPaintDC");
            GetBufferedPaintBits = (ft_GetBufferedPaintBits) GetProcAddress(_hdll_,"GetBufferedPaintBits");
            BufferedPaintClear = (ft_BufferedPaintClear) GetProcAddress(_hdll_,"BufferedPaintClear");
            BufferedPaintSetAlpha = (ft_BufferedPaintSetAlpha) GetProcAddress(_hdll_,"BufferedPaintSetAlpha");
            BufferedPaintStopAllAnimations = (ft_BufferedPaintStopAllAnimations) GetProcAddress(_hdll_,"BufferedPaintStopAllAnimations");
            BeginBufferedAnimation = (ft_BeginBufferedAnimation) GetProcAddress(_hdll_,"BeginBufferedAnimation");
            EndBufferedAnimation = (ft_EndBufferedAnimation) GetProcAddress(_hdll_,"EndBufferedAnimation");
            BufferedPaintRenderAnimation = (ft_BufferedPaintRenderAnimation) GetProcAddress(_hdll_,"BufferedPaintRenderAnimation");
            DrawThemeParentBackgroundEx = (ft_DrawThemeParentBackgroundEx) GetProcAddress(_hdll_,"DrawThemeParentBackgroundEx");
            GetThemeBitmap = (ft_GetThemeBitmap) GetProcAddress(_hdll_,"GetThemeBitmap");
            GetThemeStream = (ft_GetThemeStream) GetProcAddress(_hdll_,"GetThemeStream");
            GetThemeTransitionDuration = (ft_GetThemeTransitionDuration) GetProcAddress(_hdll_,"GetThemeTransitionDuration");
            IsCompositionActive = (ft_IsCompositionActive) GetProcAddress(_hdll_,"IsCompositionActive");
            SetWindowThemeAttribute = (ft_SetWindowThemeAttribute) GetProcAddress(_hdll_,"SetWindowThemeAttribute");
            DrawThemeTextEx = (ft_DrawThemeTextEx) GetProcAddress(_hdll_,"DrawThemeTextEx");
         }
         __finally
         {
            LeaveCriticalSection(pcs );
         }
      }
      // ---------------------------------------------------------------------------------
END_NAMESPACE()
// -----------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_OpenThemeData
            | syntax_: `HTHEME vhti_OpenThemeData( HWND p1, LPCWSTR p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_OpenThemeData@8
            | _kw_: uxtheme, OpenThemeData, visual style, theme handle, HTHEME
   }}*/
/*{{|desc: Opens a theme handle giving access to the visual style data of a window class. Forwards to
      OpenThemeData in uxtheme.dll, bound on first use; when the export is missing it does nothing and returns
      NULL.
    | params:
    - `p1` HWND - Window the theme data is associated with; can be NULL.
    - `p2` LPCWSTR - Semicolon separated class name list; the first class with theme data is used.

    Returns HTHEME - Theme handle for the other vhti calls, or NULL on failure. }}*/
OT4XB_API HTHEME __stdcall vhti_OpenThemeData(HWND p1,LPCWSTR p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::OpenThemeData == 0 ){ return 0; }
   return ( *vhti_ns::OpenThemeData)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_OpenThemeDataEx
            | syntax_: `HTHEME vhti_OpenThemeDataEx( HWND p1, LPCWSTR p2, DWORD p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_OpenThemeDataEx@12
            | _kw_: uxtheme, OpenThemeDataEx, visual style, theme handle, flags
   }}*/
/*{{|desc: Opens a theme handle giving access to the visual style data of a window class, with extra option
      flags. Forwards to OpenThemeDataEx in uxtheme.dll, bound on first use; when the export is missing it
      does nothing and returns NULL.
    | params:
    - `p1` HWND - Window the theme data is associated with; can be NULL.
    - `p2` LPCWSTR - Semicolon separated class name list; the first class with theme data is used.
    - `p3` DWORD - OTD_* option flags (OTD_FORCE_RECT_SIZING, OTD_NONCLIENT).

    Returns HTHEME - Theme handle for the other vhti calls, or NULL on failure. }}*/
OT4XB_API HTHEME __stdcall vhti_OpenThemeDataEx(HWND p1,LPCWSTR p2,DWORD p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::OpenThemeDataEx == 0 ){ return 0; }
   return ( *vhti_ns::OpenThemeDataEx)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_CloseThemeData
            | syntax_: `HRESULT vhti_CloseThemeData( HTHEME p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_CloseThemeData@4
            | _kw_: uxtheme, CloseThemeData, theme handle, release
   }}*/
/*{{|desc: Closes a theme handle opened with vhti_OpenThemeData or vhti_OpenThemeDataEx. Forwards to
      CloseThemeData in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle to close.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_CloseThemeData(HTHEME p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::CloseThemeData == 0 ){ return 0; }
   return ( *vhti_ns::CloseThemeData)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeBackground
            | syntax_: `HRESULT vhti_DrawThemeBackground( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, RECT * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeBackground@24
            | _kw_: uxtheme, DrawThemeBackground, draw part, visual style, owner draw
   }}*/
/*{{|desc: Draws the border and fill of a theme part in a given state. Forwards to DrawThemeBackground in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Rectangle to draw the background in.
    - `p6` RECT * - Optional clipping rectangle; NULL to draw unclipped.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackground(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,RECT* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeBackground == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeBackground)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeText
            | syntax_: ```
                 HRESULT vhti_DrawThemeText( HTHEME p1, HDC p2, int p3, int p4, LPCWSTR p5, int p6, DWORD p7, DWORD p8, RECT * p9 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeText@36
            | _kw_: uxtheme, DrawThemeText, themed text, draw text
   }}*/
/*{{|desc: Draws text using the font and color the theme defines for a part and state. Forwards to
      DrawThemeText in uxtheme.dll, bound on first use; when the export is missing it does nothing and returns
      0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` LPCWSTR - Unicode text to draw.
    - `p6` int - Number of characters to draw, or -1 for the whole null terminated string.
    - `p7` DWORD - DT_* text format flags.
    - `p8` DWORD - Reserved; must be 0.
    - `p9` RECT * - Rectangle to draw the text in.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeText(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,DWORD p8,RECT* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeText == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeText)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeBackgroundContentRect
            | syntax_: ```
                 HRESULT vhti_GetThemeBackgroundContentRect( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, LPRECT p6 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeBackgroundContentRect@24
            | _kw_: uxtheme, content rect, background, borders
   }}*/
/*{{|desc: Computes the content area of a theme background: the part of the bounding rectangle left inside
      the borders. Forwards to GetThemeBackgroundContentRect in uxtheme.dll, bound on first use; when the
      export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Bounding rectangle of the background.
    - `p6` LPRECT - Receives the content rectangle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundContentRect(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,LPRECT p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundContentRect == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundContentRect)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeBackgroundExtent
            | syntax_: `HRESULT vhti_GetThemeBackgroundExtent( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, LPRECT p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeBackgroundExtent@24
            | _kw_: uxtheme, background extent, borders, rectangle
   }}*/
/*{{|desc: Computes the full background rectangle needed to wrap a given content rectangle with the part
      borders. Forwards to GetThemeBackgroundExtent in uxtheme.dll, bound on first use; when the export is
      missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Content rectangle.
    - `p6` LPRECT - Receives the background rectangle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundExtent(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,LPRECT p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundExtent == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundExtent)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeBackgroundRegion
            | syntax_: `HRESULT vhti_GetThemeBackgroundRegion( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, HRGN * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeBackgroundRegion@24
            | _kw_: uxtheme, background region, HRGN, transparent
   }}*/
/*{{|desc: Computes the region covered by a theme background, honoring transparent and rounded areas.
      Forwards to GetThemeBackgroundRegion in uxtheme.dll, bound on first use; when the export is missing it
      does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Background rectangle.
    - `p6` HRGN * - Receives the region handle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundRegion(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,HRGN* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundRegion == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundRegion)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemePartSize
            | syntax_: ```
                 HRESULT vhti_GetThemePartSize( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, THEMESIZE p6, SIZE * p7 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemePartSize@28
            | _kw_: uxtheme, part size, GetThemePartSize, themed control size
   }}*/
/*{{|desc: Retrieves the size of a theme part. Forwards to GetThemePartSize in uxtheme.dll, bound on first
      use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Optional rectangle of the drawing destination; NULL for none.
    - `p6` THEMESIZE - Which size to get: TS_MIN, TS_TRUE or TS_DRAW.
    - `p7` SIZE * - Receives the size.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemePartSize(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,THEMESIZE p6,SIZE* p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePartSize == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePartSize)(p1,p2,p3,p4,p5,p6,p7);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeTextExtent
            | syntax_: ```
                 HRESULT vhti_GetThemeTextExtent( HTHEME p1, HDC p2, int p3, int p4, LPCWSTR p5, int p6, DWORD p7, RECT * p8, LPRECT p9 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeTextExtent@36
            | _kw_: uxtheme, text extent, measure text, theme font
   }}*/
/*{{|desc: Calculates the rectangle required to draw a text with the theme font of a part and state. Forwards
      to GetThemeTextExtent in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Device context used to measure the text.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` LPCWSTR - Unicode text to measure.
    - `p6` int - Number of characters, or -1 for the whole null terminated string.
    - `p7` DWORD - DT_* text format flags.
    - `p8` RECT * - Optional rectangle controlling the layout; NULL for none.
    - `p9` LPRECT - Receives the required rectangle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeTextExtent(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,RECT* p8,LPRECT p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTextExtent == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTextExtent)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeTextMetrics
            | syntax_: `HRESULT vhti_GetThemeTextMetrics( HTHEME p1, HDC p2, int p3, int p4, TEXTMETRICW * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeTextMetrics@20
            | _kw_: uxtheme, text metrics, TEXTMETRIC, theme font
   }}*/
/*{{|desc: Retrieves the text metrics of the font the theme uses for a part and state. Forwards to
      GetThemeTextMetrics in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` TEXTMETRICW * - Receives the TEXTMETRICW data.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeTextMetrics(HTHEME p1,HDC p2,int p3,int p4,TEXTMETRICW* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTextMetrics == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTextMetrics)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_HitTestThemeBackground
            | syntax_: ```
                 HRESULT vhti_HitTestThemeBackground( HTHEME p1, HDC p2, int p3, int p4, DWORD p5, RECT * p6, HRGN p7, POINT p8, WORD * p9 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_HitTestThemeBackground@40
            | _kw_: uxtheme, hit test, background, point
   }}*/
/*{{|desc: Hit tests a point against the background of a theme part. Forwards to HitTestThemeBackground in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` DWORD - HTTB_* hit test options.
    - `p6` RECT * - Background rectangle.
    - `p7` HRGN - Optional region for partially transparent backgrounds; NULL for none.
    - `p8` POINT - Point to test.
    - `p9` WORD * - Receives the resulting hit test code.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_HitTestThemeBackground(HTHEME p1,HDC p2,int p3,int p4,DWORD p5,RECT* p6,HRGN p7,POINT p8,WORD* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::HitTestThemeBackground == 0 ){ return 0; }
   return ( *vhti_ns::HitTestThemeBackground)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeEdge
            | syntax_: ```
                 HRESULT vhti_DrawThemeEdge( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, UINT p6, UINT p7, LPRECT p8 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeEdge@32
            | _kw_: uxtheme, DrawThemeEdge, draw edge, border
   }}*/
/*{{|desc: Draws one or more edges of a rectangle with the theme colors of a part and state. Forwards to
      DrawThemeEdge in uxtheme.dll, bound on first use; when the export is missing it does nothing and returns
      0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Rectangle whose edges are drawn.
    - `p6` UINT - Type of edge: BDR_* or EDGE_* value.
    - `p7` UINT - BF_* flags selecting the borders to draw.
    - `p8` LPRECT - Optional output: receives the interior rectangle when BF_ADJUST is included; NULL if
      not wanted.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeEdge(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,UINT p6,UINT p7,LPRECT p8)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeEdge == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeEdge)(p1,p2,p3,p4,p5,p6,p7,p8);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeIcon
            | syntax_: ```
                 HRESULT vhti_DrawThemeIcon( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, HIMAGELIST p6, int p7 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeIcon@28
            | _kw_: uxtheme, DrawThemeIcon, image list, draw icon
   }}*/
/*{{|desc: Draws an image from an image list applying the effects the theme defines for a part and state.
      Forwards to DrawThemeIcon in uxtheme.dll, bound on first use; when the export is missing it does nothing
      and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Rectangle to draw the image in.
    - `p6` HIMAGELIST - Image list holding the image.
    - `p7` int - Index of the image to draw.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeIcon(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,HIMAGELIST p6,int p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeIcon == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeIcon)(p1,p2,p3,p4,p5,p6,p7);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsThemePartDefined
            | syntax_: `BOOL vhti_IsThemePartDefined( HTHEME p1, int p2, int p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsThemePartDefined@12
            | _kw_: uxtheme, part defined, state defined, query
   }}*/
/*{{|desc: Tells whether the theme defines the given part and state. Forwards to IsThemePartDefined in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns FALSE.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier, or 0 to check the part only.

    Returns BOOL - TRUE when the part and state are defined by the theme. }}*/
OT4XB_API BOOL __stdcall vhti_IsThemePartDefined(HTHEME p1,int p2,int p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemePartDefined == 0 ){ return 0; }
   return ( *vhti_ns::IsThemePartDefined)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsThemeBackgroundPartiallyTransparent
            | syntax_: `BOOL vhti_IsThemeBackgroundPartiallyTransparent( HTHEME p1, int p2, int p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsThemeBackgroundPartiallyTransparent@12
            | _kw_: uxtheme, transparent background, alpha, query
   }}*/
/*{{|desc: Tells whether the background of a part and state contains transparent or alpha blended pixels.
      Forwards to IsThemeBackgroundPartiallyTransparent in uxtheme.dll, bound on first use; when the export is
      missing it does nothing and returns FALSE.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.

    Returns BOOL - TRUE when the background is partially transparent. }}*/
OT4XB_API BOOL __stdcall vhti_IsThemeBackgroundPartiallyTransparent(HTHEME p1,int p2,int p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeBackgroundPartiallyTransparent == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeBackgroundPartiallyTransparent)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeColor
            | syntax_: `HRESULT vhti_GetThemeColor( HTHEME p1, int p2, int p3, int p4, COLORREF * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeColor@20
            | _kw_: uxtheme, theme color, COLORREF, property
   }}*/
/*{{|desc: Retrieves a color property of a theme part and state. Forwards to GetThemeColor in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* color property).
    - `p5` COLORREF * - Receives the color value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeColor(HTHEME p1,int p2,int p3,int p4,COLORREF* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeColor == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeColor)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeMetric
            | syntax_: `HRESULT vhti_GetThemeMetric( HTHEME p1, HDC p2, int p3, int p4, int p5, int * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeMetric@24
            | _kw_: uxtheme, theme metric, integer property
   }}*/
/*{{|desc: Retrieves a metric property (an integer measure) of a theme part and state. Forwards to
      GetThemeMetric in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` int - Property identifier (TMT_* metric property).
    - `p6` int * - Receives the value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeMetric(HTHEME p1,HDC p2,int p3,int p4,int p5,int* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeMetric == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeMetric)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeString
            | syntax_: `HRESULT vhti_GetThemeString( HTHEME p1, int p2, int p3, int p4, LPWSTR p5, int p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeString@24
            | _kw_: uxtheme, theme string, property
   }}*/
/*{{|desc: Retrieves a string property of a theme part and state. Forwards to GetThemeString in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* string property).
    - `p5` LPWSTR - Buffer that receives the string.
    - `p6` int - Size of the buffer in characters.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeString(HTHEME p1,int p2,int p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeString == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeString)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeBool
            | syntax_: `HRESULT vhti_GetThemeBool( HTHEME p1, int p2, int p3, int p4, BOOL * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeBool@20
            | _kw_: uxtheme, theme bool, property
   }}*/
/*{{|desc: Retrieves a boolean property of a theme part and state. Forwards to GetThemeBool in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* boolean property).
    - `p5` BOOL * - Receives the value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeBool(HTHEME p1,int p2,int p3,int p4,BOOL* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBool == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBool)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeInt
            | syntax_: `HRESULT vhti_GetThemeInt( HTHEME p1, int p2, int p3, int p4, int * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeInt@20
            | _kw_: uxtheme, theme int, property
   }}*/
/*{{|desc: Retrieves an integer property of a theme part and state. Forwards to GetThemeInt in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* integer property).
    - `p5` int * - Receives the value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeInt(HTHEME p1,int p2,int p3,int p4,int* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeInt == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeInt)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeEnumValue
            | syntax_: `HRESULT vhti_GetThemeEnumValue( HTHEME p1, int p2, int p3, int p4, int * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeEnumValue@20
            | _kw_: uxtheme, theme enum, property
   }}*/
/*{{|desc: Retrieves an enumerated property of a theme part and state. Forwards to GetThemeEnumValue in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* enum property).
    - `p5` int * - Receives the value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeEnumValue(HTHEME p1,int p2,int p3,int p4,int* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeEnumValue == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeEnumValue)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemePosition
            | syntax_: `HRESULT vhti_GetThemePosition( HTHEME p1, int p2, int p3, int p4, POINT * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemePosition@20
            | _kw_: uxtheme, theme position, POINT property
   }}*/
/*{{|desc: Retrieves a position property of a theme part and state. Forwards to GetThemePosition in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* position property).
    - `p5` POINT * - Receives the position.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemePosition(HTHEME p1,int p2,int p3,int p4,POINT* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePosition == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePosition)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeFont
            | syntax_: `HRESULT vhti_GetThemeFont( HTHEME p1, HDC p2, int p3, int p4, int p5, LOGFONTW * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeFont@24
            | _kw_: uxtheme, theme font, LOGFONT, property
   }}*/
/*{{|desc: Retrieves a font property of a theme part and state. Forwards to GetThemeFont in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` int - Property identifier (TMT_* font property).
    - `p6` LOGFONTW * - Receives the font data.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeFont(HTHEME p1,HDC p2,int p3,int p4,int p5,LOGFONTW* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeFont == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeFont)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeRect
            | syntax_: `HRESULT vhti_GetThemeRect( HTHEME p1, int p2, int p3, int p4, LPRECT p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeRect@20
            | _kw_: uxtheme, theme rect, RECT property
   }}*/
/*{{|desc: Retrieves a rectangle property of a theme part and state. Forwards to GetThemeRect in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* rectangle property).
    - `p5` LPRECT - Receives the rectangle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeRect(HTHEME p1,int p2,int p3,int p4,LPRECT p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeRect == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeRect)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeMargins
            | syntax_: ```
                 HRESULT vhti_GetThemeMargins( HTHEME p1, HDC p2, int p3, int p4, int p5, RECT * p6, MARGINS * p7 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeMargins@28
            | _kw_: uxtheme, theme margins, MARGINS property
   }}*/
/*{{|desc: Retrieves a margins property of a theme part and state. Forwards to GetThemeMargins in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Optional device context; NULL allowed.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` int - Property identifier (TMT_* margins property).
    - `p6` RECT * - Optional rectangle the margins apply to; NULL allowed.
    - `p7` MARGINS * - Receives the margins.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeMargins(HTHEME p1,HDC p2,int p3,int p4,int p5,RECT* p6,MARGINS* p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeMargins == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeMargins)(p1,p2,p3,p4,p5,p6,p7);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeIntList
            | syntax_: `HRESULT vhti_GetThemeIntList( HTHEME p1, int p2, int p3, int p4, INTLIST * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeIntList@20
            | _kw_: uxtheme, int list, INTLIST property
   }}*/
/*{{|desc: Retrieves an integer list property of a theme part and state. Forwards to GetThemeIntList in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* integer list property).
    - `p5` INTLIST * - Receives the list of integers.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeIntList(HTHEME p1,int p2,int p3,int p4,INTLIST* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeIntList == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeIntList)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemePropertyOrigin
            | syntax_: `HRESULT vhti_GetThemePropertyOrigin( HTHEME p1, int p2, int p3, int p4, PROPERTYORIGIN * p5 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemePropertyOrigin@20
            | _kw_: uxtheme, property origin, where defined
   }}*/
/*{{|desc: Tells at which level a property of a part and state is defined: state, part, class, global or not
      found. Forwards to GetThemePropertyOrigin in uxtheme.dll, bound on first use; when the export is missing
      it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* value).
    - `p5` PROPERTYORIGIN * - Receives the PROPERTYORIGIN value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemePropertyOrigin(HTHEME p1,int p2,int p3,int p4,PROPERTYORIGIN* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePropertyOrigin == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePropertyOrigin)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_SetWindowTheme
            | syntax_: `HRESULT vhti_SetWindowTheme( HWND p1, LPCWSTR p2, LPCWSTR p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_SetWindowTheme@12
            | _kw_: uxtheme, SetWindowTheme, disable theming, explorer theme, window
   }}*/
/*{{|desc: Changes the way the visual style applies to a window. Passing empty strings in p2 and p3 removes
      theming from the window. Forwards to SetWindowTheme in uxtheme.dll, bound on first use; when the export
      is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HWND - Window to change.
    - `p2` LPCWSTR - Application name used to match the style instead of the real one, or NULL.
    - `p3` LPCWSTR - Semicolon separated list of class id names used instead of the real one, or NULL.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_SetWindowTheme(HWND p1,LPCWSTR p2,LPCWSTR p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetWindowTheme == 0 ){ return 0; }
   return ( *vhti_ns::SetWindowTheme)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeFilename
            | syntax_: `HRESULT vhti_GetThemeFilename( HTHEME p1, int p2, int p3, int p4, LPWSTR p5, int p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeFilename@24
            | _kw_: uxtheme, theme filename, property
   }}*/
/*{{|desc: Retrieves a filename property of a theme part and state. Forwards to GetThemeFilename in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* filename property).
    - `p5` LPWSTR - Buffer that receives the file name.
    - `p6` int - Size of the buffer in characters.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeFilename(HTHEME p1,int p2,int p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeFilename == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeFilename)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysColor
            | syntax_: `COLORREF vhti_GetThemeSysColor( HTHEME p1, int p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysColor@8
            | _kw_: uxtheme, system color, theme, COLORREF
   }}*/
/*{{|desc: Retrieves a system color as defined by the current theme. Forwards to GetThemeSysColor in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - COLOR_* system color index.

    Returns COLORREF - The color value (0x00BBGGRR). }}*/
OT4XB_API COLORREF __stdcall vhti_GetThemeSysColor(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysColor == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysColor)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysColorBrush
            | syntax_: `HBRUSH vhti_GetThemeSysColorBrush( HTHEME p1, int p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysColorBrush@8
            | _kw_: uxtheme, system color brush, HBRUSH
   }}*/
/*{{|desc: Retrieves a brush of a system color as defined by the current theme. Forwards to
      GetThemeSysColorBrush in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns NULL.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - COLOR_* system color index.

    Returns HBRUSH - Brush handle the caller must delete with DeleteObject, or NULL. }}*/
OT4XB_API HBRUSH __stdcall vhti_GetThemeSysColorBrush(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysColorBrush == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysColorBrush)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysBool
            | syntax_: `BOOL vhti_GetThemeSysBool( HTHEME p1, int p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysBool@8
            | _kw_: uxtheme, system bool, metric
   }}*/
/*{{|desc: Retrieves a boolean system metric of the current theme. Forwards to GetThemeSysBool in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns FALSE.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - TMT_* boolean id (e.g. TMT_FLATMENUS).

    Returns BOOL - The value of the metric. }}*/
OT4XB_API BOOL __stdcall vhti_GetThemeSysBool(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysBool == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysBool)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysSize
            | syntax_: `int vhti_GetThemeSysSize( HTHEME p1, int p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysSize@8
            | _kw_: uxtheme, system size, metric
   }}*/
/*{{|desc: Retrieves a system size metric of the current theme. Forwards to GetThemeSysSize in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0.
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Size index (SM_* value from the subset supported by themes).

    Returns int - Size in pixels. }}*/
OT4XB_API int __stdcall vhti_GetThemeSysSize(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysSize == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysSize)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysFont
            | syntax_: `HRESULT vhti_GetThemeSysFont( HTHEME p1, int p2, LOGFONTW * p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysFont@12
            | _kw_: uxtheme, system font, LOGFONT
   }}*/
/*{{|desc: Retrieves a system font of the current theme. Forwards to GetThemeSysFont in uxtheme.dll, bound on
      first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - TMT_* font id (e.g. TMT_CAPTIONFONT).
    - `p3` LOGFONTW * - Receives the font data.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeSysFont(HTHEME p1,int p2,LOGFONTW* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysFont == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysFont)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysString
            | syntax_: `HRESULT vhti_GetThemeSysString( HTHEME p1, int p2, LPWSTR p3, int p4 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysString@16
            | _kw_: uxtheme, system string
   }}*/
/*{{|desc: Retrieves a system string of the current theme. Forwards to GetThemeSysString in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - TMT_* string id (e.g. TMT_CSSNAME, TMT_XMLNAME).
    - `p3` LPWSTR - Buffer that receives the string.
    - `p4` int - Size of the buffer in characters.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeSysString(HTHEME p1,int p2,LPWSTR p3,int p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysString == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysString)(p1,p2,p3,p4);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeSysInt
            | syntax_: `HRESULT vhti_GetThemeSysInt( HTHEME p1, int p2, int * p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeSysInt@12
            | _kw_: uxtheme, system int
   }}*/
/*{{|desc: Retrieves a system integer of the current theme. Forwards to GetThemeSysInt in uxtheme.dll, bound
      on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - TMT_* integer id (e.g. TMT_MINCOLORDEPTH).
    - `p3` int * - Receives the value.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeSysInt(HTHEME p1,int p2,int* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysInt == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysInt)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsThemeActive
            | syntax_: `BOOL vhti_IsThemeActive( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsThemeActive@0
            | _kw_: uxtheme, IsThemeActive, visual styles enabled
   }}*/
/*{{|desc: Tells whether a visual style is active for the current user session. Forwards to IsThemeActive in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns FALSE.

    Returns BOOL - TRUE when a visual style is active. }}*/
OT4XB_API BOOL __stdcall vhti_IsThemeActive(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeActive == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeActive)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsAppThemed
            | syntax_: `BOOL vhti_IsAppThemed( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsAppThemed@0
            | _kw_: uxtheme, IsAppThemed, visual styles, application
   }}*/
/*{{|desc: Tells whether visual styles are applied to the current application. Forwards to IsAppThemed in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns FALSE.

    Returns BOOL - TRUE when the application is themed. }}*/
OT4XB_API BOOL __stdcall vhti_IsAppThemed(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsAppThemed == 0 ){ return 0; }
   return ( *vhti_ns::IsAppThemed)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetWindowTheme
            | syntax_: `HTHEME vhti_GetWindowTheme( HWND p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetWindowTheme@4
            | _kw_: uxtheme, GetWindowTheme, theme handle, window
   }}*/
/*{{|desc: Retrieves the theme handle associated with a window. Forwards to GetWindowTheme in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns NULL.
    | params:
    - `p1` HWND - Window to query.

    Returns HTHEME - Theme handle of the window, or NULL when it has none. }}*/
OT4XB_API HTHEME __stdcall vhti_GetWindowTheme(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetWindowTheme == 0 ){ return 0; }
   return ( *vhti_ns::GetWindowTheme)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_EnableThemeDialogTexture
            | syntax_: `HRESULT vhti_EnableThemeDialogTexture( HWND p1, DWORD p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_EnableThemeDialogTexture@8
            | _kw_: uxtheme, dialog texture, tab page background, ETDT
   }}*/
/*{{|desc: Enables or disables the tab page background texture of a dialog window. Forwards to
      EnableThemeDialogTexture in uxtheme.dll, bound on first use; when the export is missing it does nothing
      and returns 0 (reads as S_OK).
    | params:
    - `p1` HWND - Dialog window.
    - `p2` DWORD - ETDT_* flags (e.g. ETDT_ENABLETAB, ETDT_DISABLE).

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_EnableThemeDialogTexture(HWND p1,DWORD p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EnableThemeDialogTexture == 0 ){ return 0; }
   return ( *vhti_ns::EnableThemeDialogTexture)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsThemeDialogTextureEnabled
            | syntax_: `BOOL vhti_IsThemeDialogTextureEnabled( HWND p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsThemeDialogTextureEnabled@4
            | _kw_: uxtheme, dialog texture, query
   }}*/
/*{{|desc: Tells whether the tab page background texture is enabled for a dialog window. Forwards to
      IsThemeDialogTextureEnabled in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns FALSE.
    | params:
    - `p1` HWND - Dialog window.

    Returns BOOL - TRUE when the texture is enabled. }}*/
OT4XB_API BOOL __stdcall vhti_IsThemeDialogTextureEnabled(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeDialogTextureEnabled == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeDialogTextureEnabled)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeAppProperties
            | syntax_: `DWORD vhti_GetThemeAppProperties( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeAppProperties@0
            | _kw_: uxtheme, app properties, STAP flags
   }}*/
/*{{|desc: Retrieves the flags that tell which parts of the current application can be themed. Forwards to
      GetThemeAppProperties in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0.

    Returns DWORD - Combination of STAP_* flags. }}*/
OT4XB_API DWORD __stdcall vhti_GetThemeAppProperties(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeAppProperties == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeAppProperties)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_SetThemeAppProperties
            | syntax_: `void vhti_SetThemeAppProperties( DWORD p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_SetThemeAppProperties@4
            | _kw_: uxtheme, app properties, STAP flags, set
   }}*/
/*{{|desc: Sets the flags that tell which parts of the current application can be themed. Forwards to
      SetThemeAppProperties in uxtheme.dll, bound on first use; when the export is missing it does nothing.
    | params:
    - `p1` DWORD - Combination of STAP_* flags.

    Returns void }}*/
OT4XB_API void __stdcall vhti_SetThemeAppProperties(DWORD p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetThemeAppProperties == 0 ){ return; }
   ( *vhti_ns::SetThemeAppProperties)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetCurrentThemeName
            | syntax_: `HRESULT vhti_GetCurrentThemeName( LPWSTR p1, int p2, LPWSTR p3, int p4, LPWSTR p5, int p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetCurrentThemeName@24
            | _kw_: uxtheme, current theme, msstyles, color scheme, size name
   }}*/
/*{{|desc: Retrieves the file path of the current visual style and its active color scheme and size names.
      Forwards to GetCurrentThemeName in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` LPWSTR - Buffer that receives the theme file path.
    - `p2` int - Size of p1 in characters.
    - `p3` LPWSTR - Buffer that receives the color scheme name; NULL if not wanted.
    - `p4` int - Size of p3 in characters.
    - `p5` LPWSTR - Buffer that receives the size name; NULL if not wanted.
    - `p6` int - Size of p5 in characters.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetCurrentThemeName(LPWSTR p1,int p2,LPWSTR p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetCurrentThemeName == 0 ){ return 0; }
   return ( *vhti_ns::GetCurrentThemeName)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeDocumentationProperty
            | syntax_: `HRESULT vhti_GetThemeDocumentationProperty( LPCWSTR p1, LPCWSTR p2, LPWSTR p3, int p4 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeDocumentationProperty@16
            | _kw_: uxtheme, documentation property, theme file
   }}*/
/*{{|desc: Retrieves a property from the documentation section of a theme file. Forwards to
      GetThemeDocumentationProperty in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` LPCWSTR - Path of the theme file.
    - `p2` LPCWSTR - Property name (a SZ_THDOCPROP_* string).
    - `p3` LPWSTR - Buffer that receives the value.
    - `p4` int - Size of the buffer in characters.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeDocumentationProperty(LPCWSTR p1,LPCWSTR p2,LPWSTR p3,int p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeDocumentationProperty == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeDocumentationProperty)(p1,p2,p3,p4);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeParentBackground
            | syntax_: `HRESULT vhti_DrawThemeParentBackground( HWND p1, HDC p2, RECT * p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeParentBackground@12
            | _kw_: uxtheme, parent background, transparent control, paint
   }}*/
/*{{|desc: Asks the parent of a window to paint its background into the given device context, to fill
      transparent child areas. Forwards to DrawThemeParentBackground in uxtheme.dll, bound on first use; when
      the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HWND - Child window whose parent does the painting.
    - `p2` HDC - Device context to paint into, normally one of the child.
    - `p3` RECT * - Optional area to paint, in child coordinates; NULL for the whole window.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackground(HWND p1,HDC p2,RECT* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeParentBackground == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeParentBackground)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_EnableTheming
            | syntax_: `HRESULT vhti_EnableTheming( BOOL p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_EnableTheming@4
            | _kw_: uxtheme, EnableTheming, deprecated
   }}*/
/*{{|desc: Enables or disables visual styles for the current user session. Deprecated; modern Windows
      versions ignore it. Forwards to EnableTheming in uxtheme.dll, bound on first use; when the export is
      missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` BOOL - TRUE to enable, FALSE to disable.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_EnableTheming(BOOL p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EnableTheming == 0 ){ return 0; }
   return ( *vhti_ns::EnableTheming)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeBackgroundEx
            | syntax_: ```
                 HRESULT vhti_DrawThemeBackgroundEx( HTHEME p1, HDC p2, int p3, int p4, RECT * p5, DTBGOPTS * p6 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeBackgroundEx@24
            | _kw_: uxtheme, DrawThemeBackgroundEx, DTBGOPTS, draw part
   }}*/
/*{{|desc: Draws the border and fill of a theme part with extended options. Forwards to DrawThemeBackgroundEx
      in uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` RECT * - Rectangle to draw the background in.
    - `p6` DTBGOPTS * - Drawing options: clip rectangle and DTBG_* flags.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackgroundEx(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,DTBGOPTS* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeBackgroundEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeBackgroundEx)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintInit
            | syntax_: `HRESULT vhti_BufferedPaintInit( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintInit@0
            | _kw_: buffered paint, BufferedPaintInit, double buffering, thread
   }}*/
/*{{|desc: Prepares buffered painting for the calling thread. Every call must be paired with
      vhti_BufferedPaintUnInit. Forwards to BufferedPaintInit in uxtheme.dll, bound on first use; when the
      export is missing it does nothing and returns 0 (reads as S_OK).

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_BufferedPaintInit(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintInit == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintInit)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintUnInit
            | syntax_: `HRESULT vhti_BufferedPaintUnInit( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintUnInit@0
            | _kw_: buffered paint, BufferedPaintUnInit, double buffering
   }}*/
/*{{|desc: Closes buffered painting for the calling thread, matching a previous vhti_BufferedPaintInit.
      Forwards to BufferedPaintUnInit in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns 0 (reads as S_OK).

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_BufferedPaintUnInit(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintUnInit == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintUnInit)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BeginBufferedPaint
            | syntax_: ```
                 HANDLE vhti_BeginBufferedPaint( HDC p1, RECT * p2, BP_BUFFERFORMAT p3, BP_PAINTPARAMS * p4, HDC * p5 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BeginBufferedPaint@20
            | _kw_: buffered paint, BeginBufferedPaint, double buffering, HPAINTBUFFER
   }}*/
/*{{|desc: Begins a double buffered paint operation over a target device context. Forwards to
      BeginBufferedPaint in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns NULL.
    | params:
    - `p1` HDC - Target device context.
    - `p2` RECT * - Area of the target to be painted through the buffer.
    - `p3` BP_BUFFERFORMAT - Format of the buffer (BPBF_* value).
    - `p4` BP_PAINTPARAMS * - Optional paint parameters; NULL for defaults.
    - `p5` HDC * - Receives the device context of the buffer; all drawing goes to this DC.

    Returns HANDLE - Paint buffer handle for the other buffered paint calls, or NULL on failure. }}*/
OT4XB_API HANDLE __stdcall vhti_BeginBufferedPaint(HDC p1,RECT* p2,BP_BUFFERFORMAT p3,BP_PAINTPARAMS* p4,HDC* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BeginBufferedPaint == 0 ){ return 0; }
   return ( *vhti_ns::BeginBufferedPaint)(p1,p2,p3,p4,p5);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_EndBufferedPaint
            | syntax_: `HRESULT vhti_EndBufferedPaint( HANDLE p1, BOOL p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_EndBufferedPaint@8
            | _kw_: buffered paint, EndBufferedPaint, double buffering
   }}*/
/*{{|desc: Ends a buffered paint operation and frees the buffer. Forwards to EndBufferedPaint in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HANDLE - Paint buffer handle.
    - `p2` BOOL - TRUE to copy the buffer to the target device context, FALSE to discard the drawing.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_EndBufferedPaint(HANDLE p1,BOOL p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EndBufferedPaint == 0 ){ return 0; }
   return ( *vhti_ns::EndBufferedPaint)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetBufferedPaintTargetRect
            | syntax_: `HRESULT vhti_GetBufferedPaintTargetRect( HANDLE p1, RECT * p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetBufferedPaintTargetRect@8
            | _kw_: buffered paint, target rect
   }}*/
/*{{|desc: Retrieves the target rectangle of a paint buffer. Forwards to GetBufferedPaintTargetRect in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HANDLE - Paint buffer handle.
    - `p2` RECT * - Receives the rectangle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintTargetRect(HANDLE p1,RECT* p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintTargetRect == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintTargetRect)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetBufferedPaintTargetDC
            | syntax_: `HDC vhti_GetBufferedPaintTargetDC( HANDLE p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetBufferedPaintTargetDC@4
            | _kw_: buffered paint, target DC
   }}*/
/*{{|desc: Retrieves the target device context of a paint buffer. Forwards to GetBufferedPaintTargetDC in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns NULL.
    | params:
    - `p1` HANDLE - Paint buffer handle.

    Returns HDC - Target device context, or NULL on failure. }}*/
OT4XB_API HDC __stdcall vhti_GetBufferedPaintTargetDC(HANDLE p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintTargetDC == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintTargetDC)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetBufferedPaintDC
            | syntax_: `HDC vhti_GetBufferedPaintDC( HANDLE p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetBufferedPaintDC@4
            | _kw_: buffered paint, paint DC
   }}*/
/*{{|desc: Retrieves the paint device context of a paint buffer, the same DC returned by
      vhti_BeginBufferedPaint. Forwards to GetBufferedPaintDC in uxtheme.dll, bound on first use; when the
      export is missing it does nothing and returns NULL.
    | params:
    - `p1` HANDLE - Paint buffer handle.

    Returns HDC - Buffer device context, or NULL on failure. }}*/
OT4XB_API HDC __stdcall vhti_GetBufferedPaintDC(HANDLE p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintDC == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintDC)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetBufferedPaintBits
            | syntax_: `HRESULT vhti_GetBufferedPaintBits( HANDLE p1, RGBQUAD * * p2, int * p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetBufferedPaintBits@12
            | _kw_: buffered paint, pixel bits, DIB, direct access
   }}*/
/*{{|desc: Gives direct access to the pixel bits of a paint buffer. Works only with the DIB based buffer
      formats. Forwards to GetBufferedPaintBits in uxtheme.dll, bound on first use; when the export is missing
      it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HANDLE - Paint buffer handle.
    - `p2` RGBQUAD * * - Receives the address of the first pixel (RGBQUAD array).
    - `p3` int * - Receives the width of a buffer row, in pixels.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintBits(HANDLE p1,RGBQUAD** p2,int* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintBits == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintBits)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintClear
            | syntax_: `HRESULT vhti_BufferedPaintClear( HANDLE p1, RECT * p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintClear@8
            | _kw_: buffered paint, clear, transparent, ARGB
   }}*/
/*{{|desc: Clears a rectangle of a paint buffer to transparent black (ARGB 0). Forwards to BufferedPaintClear
      in uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HANDLE - Paint buffer handle.
    - `p2` RECT * - Rectangle to clear; NULL for the whole buffer.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_BufferedPaintClear(HANDLE p1,RECT* p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintClear == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintClear)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintSetAlpha
            | syntax_: `HRESULT vhti_BufferedPaintSetAlpha( HANDLE p1, RECT * p2, BYTE p3 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintSetAlpha@12
            | _kw_: buffered paint, alpha channel, set alpha
   }}*/
/*{{|desc: Sets the alpha channel of the pixels in a rectangle of a paint buffer. Forwards to
      BufferedPaintSetAlpha in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HANDLE - Paint buffer handle.
    - `p2` RECT * - Rectangle to change; NULL for the whole buffer.
    - `p3` BYTE - Alpha value to apply: 0 transparent, 255 opaque.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_BufferedPaintSetAlpha(HANDLE p1,RECT* p2,BYTE p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintSetAlpha == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintSetAlpha)(p1,p2,p3);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintStopAllAnimations
            | syntax_: `HRESULT vhti_BufferedPaintStopAllAnimations( HWND p1 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintStopAllAnimations@4
            | _kw_: buffered animation, stop, window
   }}*/
/*{{|desc: Stops all buffered animations running on a window. Forwards to BufferedPaintStopAllAnimations in
      uxtheme.dll, bound on first use; when the export is missing it does nothing and returns 0 (reads as
      S_OK).
    | params:
    - `p1` HWND - Window whose animations are stopped.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_BufferedPaintStopAllAnimations(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintStopAllAnimations == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintStopAllAnimations)(p1);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BeginBufferedAnimation
            | syntax_: ```
                 HANDLE vhti_BeginBufferedAnimation( HWND p1, HDC p2, RECT * p3, BP_BUFFERFORMAT p4,
                    BP_PAINTPARAMS * p5, BP_ANIMATIONPARAMS * p6, HDC * p7, HDC * p8 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BeginBufferedAnimation@32
            | _kw_: buffered animation, BeginBufferedAnimation, transition, fade
   }}*/
/*{{|desc: Begins an animated transition of a window area: the caller paints the initial state into one DC
      and the final state into another, and the system renders the frames in between. Forwards to
      BeginBufferedAnimation in uxtheme.dll, bound on first use; when the export is missing it does nothing
      and returns NULL.
    | params:
    - `p1` HWND - Window to animate.
    - `p2` HDC - Target device context.
    - `p3` RECT * - Area of the target to animate.
    - `p4` BP_BUFFERFORMAT - Format of the buffers (BPBF_* value).
    - `p5` BP_PAINTPARAMS * - Optional paint parameters; NULL for defaults.
    - `p6` BP_ANIMATIONPARAMS * - Animation parameters: style and duration.
    - `p7` HDC * - Receives the DC where the initial state must be painted.
    - `p8` HDC * - Receives the DC where the final state must be painted.

    Returns HANDLE - Animation buffer handle, or NULL on failure. }}*/
OT4XB_API HANDLE __stdcall vhti_BeginBufferedAnimation(HWND p1,HDC p2,RECT* p3,BP_BUFFERFORMAT p4,BP_PAINTPARAMS* p5,BP_ANIMATIONPARAMS* p6,HDC* p7,HDC* p8)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BeginBufferedAnimation == 0 ){ return 0; }
   return ( *vhti_ns::BeginBufferedAnimation)(p1,p2,p3,p4,p5,p6,p7,p8);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_EndBufferedAnimation
            | syntax_: `HRESULT vhti_EndBufferedAnimation( HANDLE p1, BOOL p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_EndBufferedAnimation@8
            | _kw_: buffered animation, EndBufferedAnimation, transition
   }}*/
/*{{|desc: Ends the setup phase of a buffered animation and starts rendering it. Forwards to
      EndBufferedAnimation in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HANDLE - Animation buffer handle.
    - `p2` BOOL - TRUE to run the animation onto the target, FALSE to discard it.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_EndBufferedAnimation(HANDLE p1,BOOL p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EndBufferedAnimation == 0 ){ return 0; }
   return ( *vhti_ns::EndBufferedAnimation)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_BufferedPaintRenderAnimation
            | syntax_: `BOOL vhti_BufferedPaintRenderAnimation( HWND p1, HDC p2 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_BufferedPaintRenderAnimation@8
            | _kw_: buffered animation, render frame, WM_PAINT
   }}*/
/*{{|desc: Paints the current frame of a buffered animation; call it first when handling WM_PAINT. Forwards
      to BufferedPaintRenderAnimation in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns FALSE.
    | params:
    - `p1` HWND - Window being animated.
    - `p2` HDC - Device context to paint into.

    Returns BOOL - TRUE when a frame was painted and the caller should skip its own painting. }}*/
OT4XB_API BOOL __stdcall vhti_BufferedPaintRenderAnimation(HWND p1,HDC p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintRenderAnimation == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintRenderAnimation)(p1,p2);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeParentBackgroundEx
            | syntax_: `HRESULT vhti_DrawThemeParentBackgroundEx( HWND p1, HDC p2, DWORD p3, RECT * p4 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeParentBackgroundEx@16
            | _kw_: uxtheme, parent background, DTPB flags, paint
   }}*/
/*{{|desc: Asks the parent of a window to paint its background into the given device context, with DTPB_*
      control flags. Forwards to DrawThemeParentBackgroundEx in uxtheme.dll, bound on first use; when the
      export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HWND - Child window whose parent does the painting.
    - `p2` HDC - Device context to paint into.
    - `p3` DWORD - DTPB_* option flags.
    - `p4` RECT * - Optional area to paint, in child coordinates; NULL for the whole window.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackgroundEx(HWND p1,HDC p2,DWORD p3,RECT* p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeParentBackgroundEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeParentBackgroundEx)(p1,p2,p3,p4);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeBitmap
            | syntax_: `HRESULT vhti_GetThemeBitmap( HTHEME p1, int p2, int p3, int p4, ULONG p5, HBITMAP * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeBitmap@24
            | _kw_: uxtheme, theme bitmap, HBITMAP property
   }}*/
/*{{|desc: Retrieves the bitmap behind a bitmap property of a theme part and state. Forwards to
      GetThemeBitmap in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* bitmap property).
    - `p5` ULONG - GBF_* flags selecting how the bitmap is returned.
    - `p6` HBITMAP * - Receives the bitmap handle.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeBitmap(HTHEME p1,int p2,int p3,int p4,ULONG p5,HBITMAP* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBitmap == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBitmap)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeStream
            | syntax_: ```
                 HRESULT vhti_GetThemeStream( HTHEME p1, int p2, int p3, int p4, void * * p5, DWORD * p6, HINSTANCE p7 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeStream@28
            | _kw_: uxtheme, theme stream, raw property data
   }}*/
/*{{|desc: Retrieves the raw data stream of a stream property of a theme part and state. Forwards to
      GetThemeStream in uxtheme.dll, bound on first use; when the export is missing it does nothing and
      returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State identifier of the part.
    - `p4` int - Property identifier (TMT_* stream property).
    - `p5` void * * - Receives the address of the stream data.
    - `p6` DWORD * - Receives the size of the stream in bytes.
    - `p7` HINSTANCE - Module of the style file for TMT_DISKSTREAM properties; NULL for TMT_STREAM.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeStream(HTHEME p1,int p2,int p3,int p4,void** p5,DWORD* p6,HINSTANCE p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeStream == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeStream)(p1,p2,p3,p4,p5,p6,p7);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_GetThemeTransitionDuration
            | syntax_: `HRESULT vhti_GetThemeTransitionDuration( HTHEME p1, int p2, int p3, int p4, int p5, DWORD * p6 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_GetThemeTransitionDuration@24
            | _kw_: uxtheme, transition duration, animation, states
   }}*/
/*{{|desc: Retrieves the duration of the animated transition between two states of a theme part. Forwards to
      GetThemeTransitionDuration in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` int - Part identifier.
    - `p3` int - State the transition starts from.
    - `p4` int - State the transition ends at.
    - `p5` int - Property identifier, normally TMT_TRANSITIONDURATIONS.
    - `p6` DWORD * - Receives the duration in milliseconds.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_GetThemeTransitionDuration(HTHEME p1,int p2,int p3,int p4,int p5,DWORD* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTransitionDuration == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTransitionDuration)(p1,p2,p3,p4,p5,p6);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_IsCompositionActive
            | syntax_: `BOOL vhti_IsCompositionActive( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_IsCompositionActive@0
            | _kw_: DWM, composition active, aero, uxtheme
   }}*/
/*{{|desc: Tells whether desktop composition (DWM) is active. Forwards to IsCompositionActive in uxtheme.dll,
      bound on first use; when the export is missing it does nothing and returns FALSE.

    Returns BOOL - TRUE when composition is active. }}*/
OT4XB_API BOOL __stdcall vhti_IsCompositionActive(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsCompositionActive == 0 ){ return 0; }
   return ( *vhti_ns::IsCompositionActive)();
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_SetWindowThemeAttribute
            | syntax_: `HRESULT vhti_SetWindowThemeAttribute( HWND p1, WINDOWTHEMEATTRIBUTETYPE p2, PVOID p3, DWORD p4 )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_SetWindowThemeAttribute@16
            | _kw_: uxtheme, SetWindowThemeAttribute, non client, WTA
   }}*/
/*{{|desc: Sets a theme attribute of a window; used to control the theming of the non client area. Forwards
      to SetWindowThemeAttribute in uxtheme.dll, bound on first use; when the export is missing it does
      nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HWND - Window to change.
    - `p2` WINDOWTHEMEATTRIBUTETYPE - Attribute type; WTA_NONCLIENT is the defined value.
    - `p3` PVOID - Address of the attribute data (a WTA_OPTIONS structure for WTA_NONCLIENT).
    - `p4` DWORD - Size of the attribute data in bytes.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_SetWindowThemeAttribute(HWND p1,WINDOWTHEMEATTRIBUTETYPE p2,PVOID p3,DWORD p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetWindowThemeAttribute == 0 ){ return 0; }
   return ( *vhti_ns::SetWindowThemeAttribute)(p1,p2,p3,p4);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: vhti_DrawThemeTextEx
            | syntax_: ```
                 HRESULT vhti_DrawThemeTextEx( HTHEME p1, HDC p2, int p3, int p4, LPCWSTR p5, int p6, DWORD p7, LPRECT p8, DTTOPTS * p9 )
              ```
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _vhti_DrawThemeTextEx@36
            | _kw_: uxtheme, DrawThemeTextEx, DTTOPTS, glow, shadow, text color
   }}*/
/*{{|desc: Draws text with the theme font of a part and state and extended DTTOPTS options (color, shadow,
      glow, composited drawing). Forwards to DrawThemeTextEx in uxtheme.dll, bound on first use; when the
      export is missing it does nothing and returns 0 (reads as S_OK).
    | params:
    - `p1` HTHEME - Theme handle.
    - `p2` HDC - Target device context.
    - `p3` int - Part identifier.
    - `p4` int - State identifier of the part.
    - `p5` LPCWSTR - Unicode text to draw.
    - `p6` int - Number of characters to draw, or -1 for the whole null terminated string.
    - `p7` DWORD - DT_* text format flags.
    - `p8` LPRECT - Rectangle to draw in; receives the computed rectangle when DT_CALCRECT is used.
    - `p9` DTTOPTS * - Extended options; its dwFlags member tells which fields are used.

    Returns HRESULT - S_OK on success or an error code. }}*/
OT4XB_API HRESULT __stdcall vhti_DrawThemeTextEx(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,LPRECT p8,DTTOPTS* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeTextEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeTextEx)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
//--------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_IsAppThemed
            | syntax_: `BOOL ot4xb_IsAppThemed( void )`
            | category: winapi/uxtheme
            | header: vhti.h
            | mangled-name: _ot4xb_IsAppThemed@0
            | _kw_: visual styles, themed, IsAppThemed, IsThemeActive, manifest
   }}*/
/*{{|desc: Tells whether the process is really running with visual styles: a visual style is active, the
      application is themed and the process loaded common controls version 6 or later (application manifest).
      The common controls version is read from comctl32.dll the first time any vhti function is used.

    Returns BOOL - TRUE only when the three conditions hold. }}*/
OT4XB_API BOOL __stdcall ot4xb_IsAppThemed(void )
{
   if( vhti_IsAppThemed() && vhti_IsThemeActive() ){ return vhti_ns::_bIsManifiest_; }
   return FALSE;
}
/*{{include-note-id: vhti-deprecated}}*/
/*{{end-c-function}}*/
