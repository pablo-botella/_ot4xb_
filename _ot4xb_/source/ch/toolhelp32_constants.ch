// -----------------------------------------------------------------------------------------------------------------
#ifndef _XB_TOOLHELP32_CONSTANTS_
#define _XB_TOOLHELP32_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------
#define TH32CS_SNAPHEAPLIST 0x00000001
#define TH32CS_SNAPPROCESS  0x00000002
#define TH32CS_SNAPTHREAD   0x00000004
#define TH32CS_SNAPMODULE   0x00000008
#define TH32CS_SNAPMODULE32 0x00000010
#define TH32CS_SNAPALL      nOr(TH32CS_SNAPHEAPLIST,TH32CS_SNAPPROCESS,TH32CS_SNAPTHREAD,TH32CS_SNAPMODULE)
#define TH32CS_INHERIT      dwfix(0x8000,0)
#define HF32_DEFAULT        1
#define HF32_SHARED         2
#define LF32_FIXED          0x00000001
#define LF32_FREE           0x00000002
#define LF32_MOVEABLE       0x00000004
#endif //_XB_TOOLHELP32_CONSTANTS_
// -----------------------------------------------------------------------------------------------------------------


