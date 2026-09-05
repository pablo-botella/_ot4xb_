#define VCMP_LTRIM                      0x00000010
#define VCMP_RTRIM                      0x00000020   
// #define VCMP_MISSING_LEFT               0x00000040 // internal ignored if user provide it
// #define VCMP_MISSING_RIGHT              0x00000080 // internal ignored if user provide it


// #define VCMP_COMPARE_MAP                0x00000100   // when object is expando  or array is k->v pair list  // NOT IMPLEMENTED YET !!!!!!!!
#define VCMP_STRINGIFY_CHANGES          0x00000200  
// #define VCMP_JUST_DUMP_VALUES           0x00000400   // internal ignored if user provide it

#define VCMP_USE_PRECISSION_BYTE        0x00001000   
#define VCMP_USE_MINIMAL_REPRESENTATION 0x00002000   
#define VCMP_DOUBLE_PRECISSION_BYTE     0x000F0000   
#xtranslate VCMP_GET_PRECISSION( <f> ) => iif( lAnd( <f> , VCMP_USE_PRECISSION_BYTE ) , nRShift( nAnd( <f> , VCMP_DOUBLE_PRECISSION_BYTE ) , 16 ) , 0x04 )
#xtranslate VCMP_SET_PRECISSION( <flags> , <n> ) => ( <flags> := nOr( nAndNot( <flags> , VCMP_DOUBLE_PRECISSION_BYTE ) , VCMP_USE_PRECISSION_BYTE , nLShift( nAnd( <n> , 0x0F ) , 16 ) ) )

#define VCMP_CAST_BYTE_MASK             0x00F00000   
#define VCMP_CAST_TO_LEFT               0x00100000   
#define VCMP_CAST_TO_RIGHT              0x00200000   
#define VCMP_CAST_TO_STRING             0x00300000   
#define VCMP_CAST_TO_STRING_UPPER       0x00400000   
#define VCMP_CAST_TO_STRING_LOWER       0x00500000   
#define VCMP_CAST_TO_STRING_DATE8       0x00600000   
#define VCMP_CAST_TO_STRING_DATE10      0x00700000   
#define VCMP_CAST_TO_STRING_YES_NO      0x00800000   
#define VCMP_CAST_TO_STRING_TRUE_FALSE  0x00900000   
#define VCMP_CAST_TO_INTEGER            0x00A00000   
#define VCMP_CAST_TO_DOUBLE             0x00B00000   
#define VCMP_CAST_TO_DATE               0x00C00000   
#define VCMP_CAST_TO_LOGICAL            0x00D00000   
