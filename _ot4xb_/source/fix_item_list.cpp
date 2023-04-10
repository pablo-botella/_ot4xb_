//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <stdlib.h>
extern BYTE _lower_ansi_char_table_[256];
// --------------------------------------------------------------------------------------
OT4XB_API int ot4xb_qsort_ui32_compare_ascending( const void * a, const void * b )
{
   return ( *(DWORD *) a - *(DWORD *) b );
}
// --------------------------------------------------------------------------------------
OT4XB_API int ot4xb_qsort_ui32_compare_descending( const void * a, const void * b )
{
   return ( *(DWORD *) b - *(DWORD *) a );
}
// -------------------------------------------------------------------------------------
OT4XB_API void ot4xb_qsort_ui32( DWORD * list, DWORD count, BOOL descending )
{
   qsort( list , count, sizeof( DWORD ), ( descending ? ot4xb_qsort_ui32_compare_descending : ot4xb_qsort_ui32_compare_ascending));
}

// --------------------------------------------------------------------------------------
