//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
#include <shlwapi.h>
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
OT4XB_API HTHEME __stdcall vhti_OpenThemeData(HWND p1,LPCWSTR p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::OpenThemeData == 0 ){ return 0; }
   return ( *vhti_ns::OpenThemeData)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HTHEME __stdcall vhti_OpenThemeDataEx(HWND p1,LPCWSTR p2,DWORD p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::OpenThemeDataEx == 0 ){ return 0; }
   return ( *vhti_ns::OpenThemeDataEx)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_CloseThemeData(HTHEME p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::CloseThemeData == 0 ){ return 0; }
   return ( *vhti_ns::CloseThemeData)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackground(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,RECT* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeBackground == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeBackground)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeText(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,DWORD p8,RECT* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeText == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeText)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundContentRect(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,LPRECT p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundContentRect == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundContentRect)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundExtent(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,LPRECT p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundExtent == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundExtent)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeBackgroundRegion(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,HRGN* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBackgroundRegion == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBackgroundRegion)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemePartSize(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,THEMESIZE p6,SIZE* p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePartSize == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePartSize)(p1,p2,p3,p4,p5,p6,p7);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeTextExtent(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,RECT* p8,LPRECT p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTextExtent == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTextExtent)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeTextMetrics(HTHEME p1,HDC p2,int p3,int p4,TEXTMETRICW* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTextMetrics == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTextMetrics)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_HitTestThemeBackground(HTHEME p1,HDC p2,int p3,int p4,DWORD p5,RECT* p6,HRGN p7,POINT p8,WORD* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::HitTestThemeBackground == 0 ){ return 0; }
   return ( *vhti_ns::HitTestThemeBackground)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeEdge(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,UINT p6,UINT p7,LPRECT p8)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeEdge == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeEdge)(p1,p2,p3,p4,p5,p6,p7,p8);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeIcon(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,HIMAGELIST p6,int p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeIcon == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeIcon)(p1,p2,p3,p4,p5,p6,p7);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsThemePartDefined(HTHEME p1,int p2,int p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemePartDefined == 0 ){ return 0; }
   return ( *vhti_ns::IsThemePartDefined)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsThemeBackgroundPartiallyTransparent(HTHEME p1,int p2,int p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeBackgroundPartiallyTransparent == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeBackgroundPartiallyTransparent)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeColor(HTHEME p1,int p2,int p3,int p4,COLORREF* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeColor == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeColor)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeMetric(HTHEME p1,HDC p2,int p3,int p4,int p5,int* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeMetric == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeMetric)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeString(HTHEME p1,int p2,int p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeString == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeString)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeBool(HTHEME p1,int p2,int p3,int p4,BOOL* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBool == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBool)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeInt(HTHEME p1,int p2,int p3,int p4,int* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeInt == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeInt)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeEnumValue(HTHEME p1,int p2,int p3,int p4,int* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeEnumValue == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeEnumValue)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemePosition(HTHEME p1,int p2,int p3,int p4,POINT* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePosition == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePosition)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeFont(HTHEME p1,HDC p2,int p3,int p4,int p5,LOGFONTW* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeFont == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeFont)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeRect(HTHEME p1,int p2,int p3,int p4,LPRECT p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeRect == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeRect)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeMargins(HTHEME p1,HDC p2,int p3,int p4,int p5,RECT* p6,MARGINS* p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeMargins == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeMargins)(p1,p2,p3,p4,p5,p6,p7);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeIntList(HTHEME p1,int p2,int p3,int p4,INTLIST* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeIntList == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeIntList)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemePropertyOrigin(HTHEME p1,int p2,int p3,int p4,PROPERTYORIGIN* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemePropertyOrigin == 0 ){ return 0; }
   return ( *vhti_ns::GetThemePropertyOrigin)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_SetWindowTheme(HWND p1,LPCWSTR p2,LPCWSTR p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetWindowTheme == 0 ){ return 0; }
   return ( *vhti_ns::SetWindowTheme)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeFilename(HTHEME p1,int p2,int p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeFilename == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeFilename)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API COLORREF __stdcall vhti_GetThemeSysColor(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysColor == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysColor)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HBRUSH __stdcall vhti_GetThemeSysColorBrush(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysColorBrush == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysColorBrush)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_GetThemeSysBool(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysBool == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysBool)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API int __stdcall vhti_GetThemeSysSize(HTHEME p1,int p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysSize == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysSize)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeSysFont(HTHEME p1,int p2,LOGFONTW* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysFont == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysFont)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeSysString(HTHEME p1,int p2,LPWSTR p3,int p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysString == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysString)(p1,p2,p3,p4);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeSysInt(HTHEME p1,int p2,int* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeSysInt == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeSysInt)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsThemeActive(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeActive == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeActive)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsAppThemed(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsAppThemed == 0 ){ return 0; }
   return ( *vhti_ns::IsAppThemed)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HTHEME __stdcall vhti_GetWindowTheme(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetWindowTheme == 0 ){ return 0; }
   return ( *vhti_ns::GetWindowTheme)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_EnableThemeDialogTexture(HWND p1,DWORD p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EnableThemeDialogTexture == 0 ){ return 0; }
   return ( *vhti_ns::EnableThemeDialogTexture)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsThemeDialogTextureEnabled(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsThemeDialogTextureEnabled == 0 ){ return 0; }
   return ( *vhti_ns::IsThemeDialogTextureEnabled)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API DWORD __stdcall vhti_GetThemeAppProperties(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeAppProperties == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeAppProperties)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API void __stdcall vhti_SetThemeAppProperties(DWORD p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetThemeAppProperties == 0 ){ return; }
   ( *vhti_ns::SetThemeAppProperties)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetCurrentThemeName(LPWSTR p1,int p2,LPWSTR p3,int p4,LPWSTR p5,int p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetCurrentThemeName == 0 ){ return 0; }
   return ( *vhti_ns::GetCurrentThemeName)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeDocumentationProperty(LPCWSTR p1,LPCWSTR p2,LPWSTR p3,int p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeDocumentationProperty == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeDocumentationProperty)(p1,p2,p3,p4);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackground(HWND p1,HDC p2,RECT* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeParentBackground == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeParentBackground)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_EnableTheming(BOOL p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EnableTheming == 0 ){ return 0; }
   return ( *vhti_ns::EnableTheming)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeBackgroundEx(HTHEME p1,HDC p2,int p3,int p4,RECT* p5,DTBGOPTS* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeBackgroundEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeBackgroundEx)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_BufferedPaintInit(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintInit == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintInit)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_BufferedPaintUnInit(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintUnInit == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintUnInit)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HANDLE __stdcall vhti_BeginBufferedPaint(HDC p1,RECT* p2,BP_BUFFERFORMAT p3,BP_PAINTPARAMS* p4,HDC* p5)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BeginBufferedPaint == 0 ){ return 0; }
   return ( *vhti_ns::BeginBufferedPaint)(p1,p2,p3,p4,p5);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_EndBufferedPaint(HANDLE p1,BOOL p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EndBufferedPaint == 0 ){ return 0; }
   return ( *vhti_ns::EndBufferedPaint)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintTargetRect(HANDLE p1,RECT* p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintTargetRect == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintTargetRect)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HDC __stdcall vhti_GetBufferedPaintTargetDC(HANDLE p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintTargetDC == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintTargetDC)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HDC __stdcall vhti_GetBufferedPaintDC(HANDLE p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintDC == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintDC)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetBufferedPaintBits(HANDLE p1,RGBQUAD** p2,int* p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetBufferedPaintBits == 0 ){ return 0; }
   return ( *vhti_ns::GetBufferedPaintBits)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_BufferedPaintClear(HANDLE p1,RECT* p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintClear == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintClear)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_BufferedPaintSetAlpha(HANDLE p1,RECT* p2,BYTE p3)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintSetAlpha == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintSetAlpha)(p1,p2,p3);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_BufferedPaintStopAllAnimations(HWND p1)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintStopAllAnimations == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintStopAllAnimations)(p1);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HANDLE __stdcall vhti_BeginBufferedAnimation(HWND p1,HDC p2,RECT* p3,BP_BUFFERFORMAT p4,BP_PAINTPARAMS* p5,BP_ANIMATIONPARAMS* p6,HDC* p7,HDC* p8)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BeginBufferedAnimation == 0 ){ return 0; }
   return ( *vhti_ns::BeginBufferedAnimation)(p1,p2,p3,p4,p5,p6,p7,p8);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_EndBufferedAnimation(HANDLE p1,BOOL p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::EndBufferedAnimation == 0 ){ return 0; }
   return ( *vhti_ns::EndBufferedAnimation)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_BufferedPaintRenderAnimation(HWND p1,HDC p2)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::BufferedPaintRenderAnimation == 0 ){ return 0; }
   return ( *vhti_ns::BufferedPaintRenderAnimation)(p1,p2);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeParentBackgroundEx(HWND p1,HDC p2,DWORD p3,RECT* p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeParentBackgroundEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeParentBackgroundEx)(p1,p2,p3,p4);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeBitmap(HTHEME p1,int p2,int p3,int p4,ULONG p5,HBITMAP* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeBitmap == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeBitmap)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeStream(HTHEME p1,int p2,int p3,int p4,void** p5,DWORD* p6,HINSTANCE p7)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeStream == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeStream)(p1,p2,p3,p4,p5,p6,p7);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_GetThemeTransitionDuration(HTHEME p1,int p2,int p3,int p4,int p5,DWORD* p6)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::GetThemeTransitionDuration == 0 ){ return 0; }
   return ( *vhti_ns::GetThemeTransitionDuration)(p1,p2,p3,p4,p5,p6);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall vhti_IsCompositionActive(void)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::IsCompositionActive == 0 ){ return 0; }
   return ( *vhti_ns::IsCompositionActive)();
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_SetWindowThemeAttribute(HWND p1,WINDOWTHEMEATTRIBUTETYPE p2,PVOID p3,DWORD p4)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::SetWindowThemeAttribute == 0 ){ return 0; }
   return ( *vhti_ns::SetWindowThemeAttribute)(p1,p2,p3,p4);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API HRESULT __stdcall vhti_DrawThemeTextEx(HTHEME p1,HDC p2,int p3,int p4,LPCWSTR p5,int p6,DWORD p7,LPRECT p8,DTTOPTS* p9)
{
   if( !vhti_ns::_bInit_ ){ vhti_ns::init(); }
   if( vhti_ns::DrawThemeTextEx == 0 ){ return 0; }
   return ( *vhti_ns::DrawThemeTextEx)(p1,p2,p3,p4,p5,p6,p7,p8,p9);
}
//--------------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL __stdcall ot4xb_IsAppThemed(void )
{
   if( vhti_IsAppThemed() && vhti_IsThemeActive() ){ return vhti_ns::_bIsManifiest_; }
   return FALSE;
}

