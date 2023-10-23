//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
#define __GWST_MEMBER_BOOL__         1
#define __GWST_MEMBER_BYTE__         2
#define __GWST_MEMBER_WORD__         3
#define __GWST_MEMBER_DWORD__        4
#define __GWST_MEMBER_SINT32__       4
#define __GWST_MEMBER_DWORD64__      5
#define __GWST_MEMBER_PCLIPVAR__     6
#define __GWST_MEMBER_FLOAT__        7
#define __GWST_MEMBER_DOUBLE__       8
#define __GWST_MEMBER_LPSTR__        9
#define __GWST_MEMBER_BINSTR__      10
#define __GWST_MEMBER_SZSTR__       11
#define __GWST_MEMBER_DYNSZ__       12
#define __GWST_MEMBER_SZWSTR__      13
#define __GWST_MEMBER_WORDNET__     14
#define __GWST_MEMBER_DWORDNET__    15
#define __GWST_MEMBER_XPPGUIWND__   16   

#define __GWST_MEMBER_SINT8__       17
#define __GWST_MEMBER_SINT16__      18
#define __GWST_MEMBER_UINT32__      19
#define __GWST_MEMBER_NINT64__      20

#define __GWST_MEMBER_BYTEBOOL__    21
#define __GWST_MEMBER_XDATE__       22
#define __GWST_MEMBER_POINTER32__   23
#define __GWST_MEMBER_HANDLE__      24

#define __GWST_MEMBER_MAX_DEF__     24
// ---------------------------------------------------------------------------
#define xppCLASS_HIDDEN         0x0001
#define xppCLASS_PROTECTED      0x0002
#define xppCLASS_EXPORTED       0x0003
#define xppVAR_ASSIGN_HIDDEN    0x0010
#define xppVAR_ASSIGN_PROTECTED 0x0020
#define xppVAR_ASSIGN_EXPORTED  0x0030
#define xppVAR_INSTANCE         0x0100
#define xppVAR_CLASS            0x0300
#define xppVAR_CLASS_SHARED     0x0B00
#define xppMETHOD_INSTANCE      0x0010
#define xppMETHOD_CLASS         0x0020
#define xppMETHOD_ACCESS        0x0400
#define xppMETHOD_ASSIGN        0x0800    
#define xppEXPORTED_CLASSVAR             ( xppCLASS_EXPORTED | xppVAR_CLASS )                                 // 0x0303
#define xppEXPORTED_SHARED_CLASSVAR      (xppEXPORTED_CLASSVAR | xppVAR_CLASS_SHARED )                        // 0x0B03
#define xppEXPORTED_CLASSMETHOD          (xppCLASS_EXPORTED | xppMETHOD_CLASS )                               // 0x0023
#define xppEXPORTED_METHOD               (xppCLASS_EXPORTED | xppMETHOD_INSTANCE )                            // 0x0013
#define xppEXPORTED_SETGET_METHOD        (xppEXPORTED_METHOD | xppMETHOD_ACCESS | xppMETHOD_ASSIGN )          // 0x0000
#define xppEXPORTED_SETGET_CLASSMETHOD   (xppEXPORTED_CLASSMETHOD | xppMETHOD_ACCESS | xppMETHOD_ASSIGN )     // 0x0000
#define xppEXPORTED_VAR                  ( xppCLASS_EXPORTED | xppVAR_INSTANCE)                               // 0x0000
//----------------------------------------------------------------------------------------------------------------------
#define OT4XB_LOG_WND_CLASS  "11CBDBE2_0AF0_4713_B463_269FA6E2654B"
//----------------------------------------------------------------------------------------------------------------------
#define QT_PSL_OR_PT               0x6C73403F   // "?@sl"
#define QT_VOID                    0x6F765F5F   // "__vo"
#define QT_BOOL                    0x6F625F5F   // "__bo"
#define QT_BYTEBOOL                0x62625F5F   // "__bb"
#define QT_INT8                    0x63735F5F   // "__sc"
#define QT_BYTE                    0x63755F5F   // "__uc"
#define QT_INT16                   0x73735F5F   // "__ss"
#define QT_WORD                    0x73755F5F   // "__us"
#define QT_INT32                   0x6C735F5F   // "__sl"
#define QT_DWORD                   0x6C755F5F   // "__ul"
#define QT_INT64                   0x71735F5F   // "__sq"
#define QT_QWORD                   0x71755F5F   // "__uq"
#define QT_FLOAT                   0x34665F5F   // "__f4"
#define QT_DOUBLE                  0x38665F5F   // "__f8"
#define QT_POINTER                 0x74705F5F   // "__pt"
#define QT_LPBOOL                  0x6F62405F   // "_@bo"
#define QT_LPBYTEBOOL              0x6262405F   // "_@bb"
#define QT_LPINT8                  0x6373405F   // "_@sc"
#define QT_LPBYTE                  0x6375405F   // "_@uc"
#define QT_LPINT16                 0x7373405F   // "_@ss"
#define QT_LPWORD                  0x7375405F   // "_@us"
#define QT_LPINT32                 0x6C73405F   // "_@sl"
#define QT_LPDWORD                 0x6C75405F   // "_@ul"
#define QT_LPINT64                 0x7173405F   // "_@sq"
#define QT_LPQWORD                 0x7175405F   // "_@uq"
#define QT_LPFLOAT                 0x3466405F   // "_@f4"
#define QT_LPDOUBLE                0x3866405F   // "_@f8"
#define QT_ZSTRING                 0x7A735F63   // "c_sz"   
#define QT_STR2WIDE                0x77735F63   // "c_sw"
#define QT_STR2WIDE_W              0x77734063   // "c@sw"
#define QT_HWND                    0x77685F5F   // "__hw"
#define QT_LPXBASE                 0x62785F5F   // "__xb"
#define QT_VARIANT                 0x74765F5F   // "__vt"
//----------------------------------------------------------------------------------------------------------------------
#define GWST_SORT_FLAG_DESCEND     1
//----------------------------------------------------------------------------------------------------------------------
#define _XPP_NOT_NIL_   0xFE      
//----------------------------------------------------------------------------------------------------------------------

enum class ot4xb_sql_type : LONG
{
   Invalid,
   TinyInt,
   SmallInt,
   MediumInt,
   Int,
   BigInt,
   Decimal,
   Float,
   Double,
   Bit,
   Date,
   Time,
   DateTime,
   TimeStamp,
   Year,
   Char,
   VarChar,
   Binary,
   VarBinary,
   TinyBlob,
   Blob,
   MediumBlob,
   LongBlob,
   TinyText,
   Text,
   MediumText,
   LongText,
   Enum,
   Set
};

