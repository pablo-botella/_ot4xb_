//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#define _CRT_SECURE_NO_DEPRECATE
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
static DWORD _fp_parclen_jmp_ = (DWORD) GetProcAddress( GetModuleHandle( "xpprt1.dll" ), "__parclen" );
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetLen
            | syntax_: `DWORD _conArrayGetLen( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetLen
            | _kw_: array element, length, size, indices, container
   }}*/
/*{{|desc: Gets the length of an array element at the specified indices. Wrapper for _conSizeA with variable
      arguments.
    | params:
    - `cona` ContainerHandle - Container handle of the array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns DWORD - Length of the array element, or 0 if invalid. }}*/
OT4XB_API DWORD _conArrayGetLen( ContainerHandle cona, ... )
{
   DWORD ul = 0;
   DWORD sp1 = 0;
   if( !cona ){
      return 0;
   }
   _asm
   {
      push edx
      mov sp1, esp
      mov edx, 0
      lea ecx, cona
      label_1 :
      inc edx
         add ecx, 4
         mov eax, [ecx]
         and eax, eax
         jz  label_2
         jmp label_1
         label_2 :
      push 0
         label_3 :
         push[ecx]
         pop eax
         push eax
         dec  edx
         sub  ecx, 4
         mov eax, edx
         and eax, eax
         jnz  label_3
         lea eax, ul
         push eax
         mov eax, cona
         push eax
         call _conSizeA
         mov esp, sp1
         pop edx
   }
   return ul;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetType
            | syntax_: `DWORD _conArrayGetType( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetType
            | _kw_: array element, type, XPP type, indices, container
   }}*/
/*{{|desc: Gets the type of an array element at the specified indices. Wrapper for _conTypeA with variable
      arguments.
    | params:
    - `cona` ContainerHandle - Container handle of the array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns DWORD - XPP type flags of the element, or 0 if invalid. }}*/
OT4XB_API DWORD _conArrayGetType( ContainerHandle cona, ... )
{
   DWORD ul = 0;
   DWORD sp1 = 0;
   if( !cona ){
      return 0;
   }
   _asm
   {
      push edx
      mov sp1, esp
      mov edx, 0
      lea ecx, cona
      label_1 :
      inc edx
         add ecx, 4
         mov eax, [ecx]
         and eax, eax
         jz  label_2
         jmp label_1
         label_2 :
      push 0
         label_3 :
         push[ecx]
         pop eax
         push eax
         dec  edx
         sub  ecx, 4
         mov eax, edx
         and eax, eax
         jnz  label_3
         lea eax, ul
         push eax
         mov eax, cona
         push eax
         call _conTypeA
         mov esp, sp1
         pop edx
   }
   return ul;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayCheckType
            | syntax_: `BOOL _conArrayCheckType( ContainerHandle cona, ULONG nType, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayCheckType
            | _kw_: array element, check type, type flags, indices
   }}*/
/*{{|desc: Checks if an array element at the specified indices matches the given type flags.
    | params:
    - `cona` ContainerHandle - Container handle of the array.
    - `nType` ULONG - XPP type flags to check against.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns BOOL - TRUE if the element matches the type flags, FALSE otherwise. }}*/
OT4XB_API BOOL _conArrayCheckType( ContainerHandle cona, ULONG nType, ... )
{
   DWORD ul = 0;
   DWORD sp1 = 0;
   if( !cona ){
      return FALSE;
   }
   _asm
   {
      push edx
      mov sp1, esp
      mov edx, 0
      lea ecx, nType
      label_1 :
      inc edx
         add ecx, 4
         mov eax, [ecx]
         and eax, eax
         jz  label_2
         jmp label_1
         label_2 :
      push 0
         label_3 :
         push[ecx]
         pop eax
         push eax
         dec  edx
         sub  ecx, 4
         mov eax, edx
         and eax, eax
         jnz  label_3
         lea eax, ul
         push eax
         mov eax, cona
         push eax
         call _conTypeA
         mov esp, sp1
         pop edx
   }
   return (BOOL) ( ul & nType );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conCheckType
            | syntax_: `BOOL _conCheckType( ContainerHandle con, ULONG nType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conCheckType
            | _kw_: container type, check type, XPP flags, valtype
   }}*/
/*{{|desc: Checks if a container matches the given type flags.
    | params:
    - `con` ContainerHandle - Container to check.
    - `nType` ULONG - XPP type flags to check against.

    Returns BOOL - TRUE if the container matches the type flags, FALSE otherwise. }}*/
OT4XB_API BOOL _conCheckType( ContainerHandle con, ULONG nType )
{
   ULONG ul = 0;
   if( con == NULLCONTAINER ) return (BOOL) nType == 0;
   _conType( con, &ul );
   return (BOOL) ( ul & nType );
}
/*{{end-c-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetArrayLen
            | syntax_: `ULONG _conGetArrayLen( ContainerHandle cona )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetArrayLen
            | _kw_: array length, Len, first dimension, container
   }}*/
/*{{|desc: Returns the number of elements in the first dimension of an array container.
    | params:
    - `cona` ContainerHandle - Container handle of the array.

    Returns ULONG - Number of elements, or 0 if invalid. }}*/
OT4XB_API ULONG _conGetArrayLen( ContainerHandle cona )
{
   ULONG ul = 0;
   _conSizeA( cona, &ul, 0 );
   return ul;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetLong
            | syntax_: `XPPAPIRET _conGetLong( ContainerHandle con, LONG * pnVal )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetLong
            | _kw_: container to LONG, numeric, read value
   }}*/
/*{{|desc: Extracts a LONG value from a numeric container.
    | params:
    - `con` ContainerHandle - Container to extract the value from.
    - `pnVal` LONG* - Pointer to receive the LONG value.

    Returns XPPAPIRET - Non 0 if error.

    |note: Retrieving LONG values with _conGetNL() can result in data lost if the container have stored a
      double value. _conGetLong() detect the internal numeric type and convert it to LONG properly. }}*/
OT4XB_API XPPAPIRET _conGetLong( ContainerHandle con, LONG * pnVal )
{
   ULONG ulType = 0;
   XPPAPIRET nResult = 0;
   LONG nValue = 0;
   if( con )
   {
      _conType( con, &ulType );
      if( ulType & XPP_NUMERIC )
      {
         if( ulType & _xpp_DOUBLE )
         {
            double nd = 0.00F;
            LARGE_INTEGER li;
            nResult = _conGetND( con, &nd );
            li.QuadPart = (LONGLONG) nd;
            nValue = (LONG) li.LowPart;
         }
         else nResult = _conGetNL( con, &nValue );
      }
   }
   if( pnVal ) pnVal[0] = nValue;
   return nResult;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetLongOrBool
            | syntax_: `XPPAPIRET _conGetLongOrBool( ContainerHandle con, LONG * pnVal )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetLongOrBool
            | _kw_: container to LONG, logical as 1 0, read value
   }}*/
/*{{|desc: Extracts a LONG value from a numeric or logical container. Logical containers are converted to 1
      (.T.) or 0 (.F.).
    | params:
    - `con` ContainerHandle - Container to extract the value from. Must be numeric or logical.
    - `pnVal` LONG* - Pointer to receive the LONG value.

    Returns XPPAPIRET - Non 0 if error.

    |note: Retrieving LONG values with _conGetNL() can result in data lost if the container have stored a
      double value. _conGetLongOrBool() detect the internal numeric type and convert it to LONG properly. }}*/
OT4XB_API XPPAPIRET _conGetLongOrBool( ContainerHandle con, LONG * pnVal )
{
   ULONG ulType = 0;
   XPPAPIRET nResult = 0;
   LONG nValue = 0;
   if( con )
   {
      _conType( con, &ulType );
      if( ulType & XPP_NUMERIC )
      {
         if( ulType & _xpp_DOUBLE )
         {
            double nd = 0.00F;
            LARGE_INTEGER li;
            nResult = _conGetND( con, &nd );
            li.QuadPart = (LONGLONG) nd;
            nValue = (LONG) li.LowPart;
         }
         else nResult = _conGetNL( con, &nValue );
      }
      else if( ulType & XPP_LOGICAL )
      {
         BOOL nnn = 0;
         nResult = _conGetL( con, &nnn );
         nValue = ( nnn ? 1 : 0 );
      }
   }
   if( pnVal ) pnVal[0] = nValue;
   return nResult;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetLong64
            | syntax_: `XPPAPIRET _conGetLong64( ContainerHandle con, LONGLONG * pnVal )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetLong64
            | _kw_: container to int64, LONGLONG, numeric, read value
   }}*/
/*{{|desc: Extracts a LONGLONG (64-bit integer) value from a numeric container. Detects the internal numeric
      type to avoid data loss.
    | params:
    - `con` ContainerHandle - Numeric container to extract the value from.
    - `pnVal` LONGLONG* - Pointer to receive the 64-bit value.

    Returns XPPAPIRET - Non 0 if error.

    |seealso: See also: {{ilink: <c-function _conGetLongEx> _conGetLongEx}} }}*/
OT4XB_API XPPAPIRET _conGetLong64( ContainerHandle con, LONGLONG * pnVal )
{
   ULONG ulType = 0;
   XPPAPIRET nResult = 0;
   LONGLONG q = 0LL;
   if( con )
   {
      _conType( con, &ulType );
      if( ulType & XPP_NUMERIC )
      {
         if( ulType & _xpp_DOUBLE )
         {
            double nd = 0.00F;
            nResult = _conGetND( con, &nd );
            q = (LONGLONG) nd;
         }
         else
         {
            LONG nl = 0;
            nResult = _conGetNL( con, &nl );
            q = (LONGLONG) nl;
         }
      }
   }
   if( pnVal ) pnVal[0] = q;
   return nResult;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: con-get-long-ex |:  Extracts a LONG (a 32-bit integer) from a container holding any of the
    supported Xbase++ types. It is the "extended" reader: the caller gets an integer whatever it
    passed, the conversion being chosen from the container's own type:

    - Numeric: an integer value is used as-is; a floating value is truncated to a 64-bit integer and
      only its low 32 bits are kept, so a magnitude beyond 32 bits wraps around.
    - Logical: .T. gives 1, .F. gives 0.
    - Character: the string is read as the raw 4 bytes of a LONG - a binary int32, not its decimal
      text - so it should be exactly 4 bytes long.
    - Object: the object is expected to follow the ot4xb structure convention and expose _lock_() /
      _unlock_(). _lock_() is called to get a pointer, the first LONG there is read, and _unlock_()
      is always called afterwards; an object with no _lock_ method yields 0.

    - Any other container type yields 0.
    }}*/
   // ----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetLongEx
            | syntax_: `XPPAPIRET _conGetLongEx( ContainerHandle con, LONG * pnVal )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetLongEx
            | _kw_: container to LONG, any type, error return
   }}*/
/*{{|desc: The function return non 0 on error
    | params:
    - `con` ContainerHandle - Container to extract the value from.
    - `pnVal` LONG* - Pointer to receive the LONG value.

    Returns XPPAPIRET - Non 0 if error.

    |include-note-id: con-get-long-ex }}*/
OT4XB_API XPPAPIRET _conGetLongEx( ContainerHandle con, LONG * pnVal )
{
   ULONG ul = 0;
   XPPAPIRET nResult = 0;
   LONG nValue = 0;
   if( con )
   {
      _conType( con, &ul );
      if( ( ul & XPP_NUMERIC ) && ( ul & _xpp_DOUBLE ) )
      {
         double nd = 0.00F;
         LARGE_INTEGER li;
         nResult = _conGetND( con, &nd );
         li.QuadPart = (LONGLONG) nd;
         nValue = (LONG) li.LowPart;
      }
      else switch( ul & 0xFF )
      {
         case XPP_NUMERIC:
         {
            nResult = _conGetLong( con, &nValue ); break;
         }
         case XPP_LOGICAL:
         {
            BOOL nn = 0; nResult = _conGetL( con, (BOOL *) &nn ); nValue = ( nn ? 1 : 0 ); break;
         }
         case XPP_CHARACTER:
         {
            _conGetCL( con, &ul, (LPSTR) ( (void *) &nValue ), sizeof( LONG ) ); break;
         }
         case XPP_OBJECT:
         {
            DWORD * p = (DWORD *) _conMCallLong( con, "_lock_" );
            __try{
               if( p ) nValue = (LONG) p[0];
            }
            __finally {
               _conMCallLong( con, "_unlock_" );
            }
            break;
         }
      }
   }
   if( pnVal ) pnVal[0] = nValue;
   return nResult;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _parLong
            | syntax_: `LONG _parLong( XppParamList pl, ULONG nIndex, ... )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _parLong
            | _kw_: parameter to LONG, numeric parameter, XppParamList
   }}*/
/*{{|desc: Extracts a LONG value from a numeric parameter in an XppParamList. If the parameter is an array,
      accepts indices to select the element.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nIndex` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Optional array indices if the parameter is an array. MUST end with 0.

    Returns LONG - Extracted value, or 0 if not numeric.

    |note: Retrieving LONG values with _parnl() can result in data lost if the Xbase++ param contains a double
      value. _parLong() detect the internal numeric type and convert it to LONG properly.

    |seealso: See also: {{ilink: <c-function _parLongOrBool> _parLongOrBool}}, {{ilink: <c-function _parLongEx> _parLongEx}} }}*/
OT4XB_API LONG _parLong( XppParamList pl, ULONG nIndex, ... )
{
   ULONG ulType = _partype( pl, nIndex );
   LONG  nResult = 0;
   if( ulType & XPP_ARRAY )
   {
      va_list pMarker;
      int pnn[64];
      ULONG n = 0;
      ULONG nn = 0;
      for( n = 0; n < 64; n++ ) pnn[n] = 0;
      n = 0;
      va_start( pMarker, nIndex );
      while( n < 63 && ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
      if( n > 0 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle cona = _conParam( pl, nIndex, &bByRef );
         ContainerHandle con = _conArrayGetA( cona, NULLCONTAINER, pnn );
         if( !bByRef ) _conRelease( cona );
         cona = NULLCONTAINER;
         if( con != NULLCONTAINER )
         {
            _conGetLong( con, &nResult );
            _conRelease( con );
         }
      }
   }
   else if( ( ulType & XPP_NUMERIC ) && ( ulType & _xpp_DOUBLE ) )
   {
      double nd = _parnd( pl, nIndex, 0 );
      LARGE_INTEGER li;
      li.QuadPart = (LONGLONG) nd;
      nResult = (LONG) li.LowPart;
   }
   else if( ulType & XPP_NUMERIC ) nResult = _parnl( pl, nIndex, 0 );
   return nResult;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _parLongOrBool
            | syntax_: `LONG _parLongOrBool( XppParamList pl, ULONG nIndex, ... )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _parLongOrBool
            | _kw_: parameter to LONG, logical parameter, XppParamList
   }}*/
/*{{|desc: Extracts a LONG value from a numeric or logical parameter in an XppParamList. Logical parameters are
      converted to 1 (.T.) or 0 (.F.). If the parameter is an array, accepts indices to select the element.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nIndex` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Optional array indices if the parameter is an array. MUST end with 0.

    Returns LONG - Extracted value, or 0 if not numeric or logical.

    |seealso: See also: {{ilink: <c-function _parLong> _parLong}}, {{ilink: <c-function _parLongEx> _parLongEx}} }}*/
OT4XB_API LONG _parLongOrBool( XppParamList pl, ULONG nIndex, ... )
{
   ULONG ulType = _partype( pl, nIndex );
   LONG  nResult = 0;
   if( ulType & XPP_ARRAY )
   {
      va_list pMarker;
      int pnn[64];
      ULONG n = 0;
      ULONG nn = 0;
      for( n = 0; n < 64; n++ ) pnn[n] = 0;
      n = 0;
      va_start( pMarker, nIndex );
      while( n < 63 && ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
      if( n > 0 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle cona = _conParam( pl, nIndex, &bByRef );
         ContainerHandle con = _conArrayGetA( cona, NULLCONTAINER, pnn );
         if( !bByRef ) _conRelease( cona );
         cona = NULLCONTAINER;
         if( con != NULLCONTAINER )
         {
            _conGetLongOrBool( con, &nResult );
            _conRelease( con );
         }
      }
   }
   else if( ( ulType & XPP_NUMERIC ) && ( ulType & _xpp_DOUBLE ) )
   {
      double nd = _parnd( pl, nIndex, 0 );
      LARGE_INTEGER li;
      li.QuadPart = (LONGLONG) nd;
      nResult = (LONG) li.LowPart;
   }
   else if( ulType & XPP_NUMERIC ){
      nResult = _parnl( pl, nIndex, 0 );
   }
   else if( ulType & XPP_LOGICAL )
   {
      nResult = ( _parl( pl, nIndex, 0 ) ? 1 : 0 );
   }
   return nResult;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _parLongEx
            | syntax_: `LONG _parLongEx( XppParamList pl, ULONG nIndex, ... )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _parLongEx
            | _kw_: parameter to LONG, any type, XppParamList
   }}*/
/*{{|desc: Extracts a LONG value from a parameter of any supported type in an XppParamList: - Numeric: detects
      internal type (double or integer) and converts properly. - Logical: returns 1 for .T., 0 for .F. -
      Character: treats the string buffer as containing the raw 4 bytes of a LONG. - Object: assumes the object
      implements the :_lock_() and :_unlock_() methods (ot4xb structure convention), calls :_lock_() to obtain a
      pointer and reads the first LONG from it. If the parameter is an array, accepts indices to select the
      element.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nIndex` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Optional array indices if the parameter is an array. MUST end with 0.

    Returns LONG - Extracted value, or 0 if type not supported.

    |seealso: See also: {{ilink: <c-function _parLong> _parLong}}, {{ilink: <c-function _parLongOrBool> _parLongOrBool}}, {{ilink: <c-function _conGetLongEx> _conGetLongEx}} }}*/
OT4XB_API LONG _parLongEx( XppParamList pl, ULONG nIndex, ... )
{
   ULONG ulType = _partype( pl, nIndex );
   LONG  nResult = 0;
   if( ulType & XPP_ARRAY )
   {
      va_list pMarker;
      int pnn[64];
      ULONG n = 0;
      ULONG nn = 0;
      for( n = 0; n < 64; n++ ) pnn[n] = 0;
      n = 0;
      va_start( pMarker, nIndex );
      while( n < 63 && ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
      if( n > 0 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle cona = _conParam( pl, nIndex, &bByRef );
         ContainerHandle con = _conArrayGetA( cona, NULLCONTAINER, pnn );
         if( !bByRef ) _conRelease( cona );
         cona = NULLCONTAINER;
         if( con != NULLCONTAINER )
         {
            _conGetLongEx( con, &nResult );
            _conRelease( con );
         }
      }
   }
   else if( ( ulType & XPP_NUMERIC ) && ( ulType & _xpp_DOUBLE ) )
   {
      double nd = _parnd( pl, nIndex, 0 );
      LARGE_INTEGER li;
      li.QuadPart = (LONGLONG) nd;
      nResult = (LONG) li.LowPart;
   }
   else if( ulType & XPP_NUMERIC ){
      nResult = _parnl( pl, nIndex, 0 );
   }
   else if( ulType & XPP_LOGICAL ){
      nResult = ( _parl( pl, nIndex, 0 ) ? 1 : 0 );
   }
   else if( ulType & XPP_CHARACTER )
   {
      LARGE_INTEGER li; li.QuadPart = 0;
      _parc( _mk_ptr_( LPSTR, &li, 0 ), sizeof( li ), pl, nIndex, 0 );
      nResult = li.LowPart;
   }
   else if( ulType & XPP_OBJECT )
   {
      BOOL bByRef = FALSE;
      ContainerHandle con = _conParam( pl, nIndex, &bByRef );
      if( con != NULLCONTAINER )
      {
         _conGetLongEx( con, &nResult );
         if( !bByRef ) _conRelease( con );
      }
   }
   return nResult;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _parLong64
            | syntax_: `LONGLONG _parLong64( XppParamList pl, ULONG nIndex, ... )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _parLong64
            | _kw_: parameter to int64, LONGLONG, XppParamList
   }}*/
/*{{|desc: Extracts a LONGLONG (64-bit integer) value from a numeric parameter in an XppParamList. Detects the
      internal numeric type to avoid data loss. If the parameter is an array, accepts indices to select the
      element.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nIndex` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Optional array indices if the parameter is an array. MUST end with 0.

    Returns LONGLONG - Extracted 64-bit value, or 0 if not numeric.

    |seealso: See also: {{ilink: <c-function _parLong> _parLong}}, {{ilink: <c-function _conGetLong64> _conGetLong64}} }}*/
OT4XB_API LONGLONG _parLong64( XppParamList pl, ULONG nIndex, ... )
{
   ULONG ulType = _partype( pl, nIndex );
   LONGLONG q = 0LL;
   if( ulType & XPP_ARRAY )
   {
      va_list pMarker;
      int pnn[64];
      ULONG n = 0;
      ULONG nn = 0;
      for( n = 0; n < 64; n++ ) pnn[n] = 0;
      n = 0;
      va_start( pMarker, nIndex );
      while( n < 63 && ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
      if( n > 0 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle cona = _conParam( pl, nIndex, &bByRef );
         ContainerHandle con = _conArrayGetA( cona, NULLCONTAINER, pnn );
         if( !bByRef ) _conRelease( cona );
         cona = NULLCONTAINER;
         if( con != NULLCONTAINER )
         {
            _conGetLong64( con, &q );
            _conRelease( con );
         }
      }
   }
   else if( ulType & XPP_NUMERIC )
   {
      if( ulType & _xpp_DOUBLE )
      {
         double nd = _parnd( pl, nIndex, 0 );
         q = (LONGLONG) nd;
      }
      else
      {
         q = (LONGLONG) _parnl( pl, nIndex, 0 );
      }
   }
   return q;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: PSzz2Array
            | syntax_: `PSzz2Array( pStr )`
            | category: container
            | _kw_: pszz, double zero list, string list to array, multi string
   }}*/
/*{{|desc: Converts a pszz buffer to a Xbase++ array. A pszz buffer is a sequence of substrings each terminated
      by Chr(0), where a double Chr(0)+Chr(0) marks the end of the list. Each substring becomes one element of
      the returned array.
    | params:
    - `pStr` Character/Numeric pointer/Object - pszz buffer resolved through OT4XB extended pointer
      handling. The buffer contains substrings each ending in Chr(0), terminated by Chr(0)+Chr(0).

    Returns Array - Array of strings, one element per substring.

    |note: This is the reverse operation for Array2pszz(). The current parser preserves empty elements found in
      the buffer, including a final empty item when the supplied buffer represents one.

    |seealso: See also: {{ilink: <function Array2pszz> Array2pszz}} }}*/
XPPRET XPPENTRY PSZZ2ARRAY( XppParamList pl )
{
   CON_PLKSTREX plk;
   LPSTR p = (LPSTR) _conParamRLockStrEx( pl, 1, &plk );
   TList * pList = new TList;
   ContainerHandle cona;
   ULONG n, nMax;
   if( p )
   {
      LPSTR  pStr = p;
      WORD * pw = (WORD *) p;
      for( ; pw[0] != 0; p++, pw = (WORD *) p )
      {
         if( *p == 0 )
         {
            pList->Add( (void *) pStr );
            pStr = p + 1;
         }
      }
      if( pStr != 0 ) pList->Add( (void *) pStr );
   }
   nMax = pList->Count();
   cona = _conNewArray( 1, nMax );
   for( n = 0; n < nMax; n++ ) _conArrayPutC( cona, (LPSTR) pList->Get( n ), n + 1, 0 );
   delete pList;
   _conUnLockStrEx_( &plk );
   _conReturn( pl, cona );
   _conRelease( cona );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conXStrDup
            | syntax_: `LPSTR _conXStrDup( ContainerHandle con, ULONG * pnLen )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conXStrDup
            | _kw_: container to string, copy string, zero terminated, xgrab
   }}*/
/*{{|desc: Retrieves a zero-terminated string copy from a CHARACTER Xbase++ container.
    | params:
    - `con` ContainerHandle - Opaque handle to a CHARACTER Xbase++ value.
    - `pnLen` ULONG* - Optional pointer to receive the string length. May be NULL.

    Returns LPSTR - Pointer to a newly allocated zero-terminated string, or NULL if the container is not a
      string.

    |note: The returned string must be released with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR _conXStrDup( ContainerHandle con, ULONG * pnLen )
{
   ULONG nLen = 0;
   LPSTR pRet = (LPSTR) 0;
   if( _conSizeC( con, &nLen ) == 0 )
   {
      ULONG nWritten = 0;
      pRet = (LPSTR) _xgrab( nLen + 1 );
      _conGetCL( con, &nWritten, pRet, nLen + 1 );
   }
   if( pnLen ) pnLen[0] = nLen;
   return (LPSTR) pRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszGetClassName
            | syntax_: `LPSTR _pszGetClassName( ContainerHandle conClassObject )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszGetClassName
            | _kw_: class name, object, className, container
   }}*/
/*{{|desc: Returns the class name of a Xbase++ object container. Calls the object's className() method
      internally.
    | params:
    - `conClassObject` ContainerHandle - Opaque handle to a Xbase++ object.

    Returns LPSTR - Pointer to a newly allocated zero-terminated string with the class name, or NULL if not an
      object.

    |note: The returned string must be released with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR _pszGetClassName( ContainerHandle conClassObject )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   LPSTR           p = (LPSTR) 0;
   ULONG           ulLen = 0;
   ULONG           ulCopy = 0;

   if( conClassObject == NULLCONTAINER ) return p;
   _conCallMethodPa( con, "className", 1, &conClassObject );
   _conSizeC( con, &ulLen );
   if( ulLen > 0 )
   {
      p = (LPSTR) _xgrab( ulLen + 1 );
      _conGetCL( con, &ulCopy, p, ulLen );
   }
   _conRelease( con );
   return p;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetSuperClass
            | syntax_: `ContainerHandle _conGetSuperClass( ContainerHandle conClassObject )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetSuperClass
            | _kw_: super class, parent class name, object
   }}*/
/*{{|desc: Returns a container holding the parent class name of a Xbase++ object container.
    | params:
    - `conClassObject` ContainerHandle - Opaque handle to a Xbase++ object.

    Returns ContainerHandle - Opaque handle to a Xbase++ value containing the parent class name, or
      NULLCONTAINER if not an object.

    |note: The returned ContainerHandle must be released with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conGetSuperClass( ContainerHandle conClassObject )
{

   ContainerHandle conRet = NULLCONTAINER;
   ContainerHandle * pcon;
   ULONG           ulType = 0;
   ULONG           ulLen = 0;

   if( conClassObject == NULLCONTAINER ) return NULLCONTAINER;
   _conType( conClassObject, &ulType );
   if( !( ulType & XPP_OBJECT ) ) return NULLCONTAINER;

   pcon = (ContainerHandle *) _xgrab( 3 * sizeof( ContainerHandle ) );
   pcon[0] = conClassObject;
   pcon[1] = _conPutNL( NULLCONTAINER, 2 );
   pcon[2] = _conNew( NULLCONTAINER );
   _conCallMethodPa( pcon[2], "classDescribe", 2, pcon ); // #define CLASS_DESCR_SUPERCLASSES 2
   pcon[0] = NULLCONTAINER;
   if( _conSizeA( pcon[2], &ulLen, 0 ) == 0 )
   {
      if( ulLen > 0 )
      {
         pcon[0] = _conArrayGet( pcon[2], pcon[0], 1, 0 );
         if( pcon[0] != NULLCONTAINER )
         {
            ulType = 0;
            _conType( pcon[0], &ulType );
            if( ulType & XPP_OBJECT ) conRet = pcon[0];
            pcon[0] = NULLCONTAINER;
         }
      }

   }
   if( pcon[0] != NULLCONTAINER ) _conRelease( pcon[0] );
   if( pcon[1] != NULLCONTAINER ) _conRelease( pcon[1] );
   if( pcon[2] != NULLCONTAINER ) _conRelease( pcon[2] );

   _xfree( (void *) pcon );
   return conRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _dwANFlagsParam
            | syntax_: `DWORD _dwANFlagsParam( XppParamList pl, ULONG nParam )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _dwANFlagsParam
            | _kw_: flags parameter, array or numeric, DWORD flags, combine
   }}*/
/*{{|desc: Returns a Xbase++ parameter as DWORD flags. If the parameter is a single numeric value, returns it
      as DWORD. If the parameter is an array of numeric values, combines all elements with bitwise OR and
      returns the result. Useful for accepting flags either as a single value or as an array.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).

    Returns DWORD - Combined flags value, or 0 if not numeric. }}*/
OT4XB_API DWORD _dwANFlagsParam( XppParamList pl, ULONG nParam )
{
   ULONG ulType = _partype( pl, nParam );
   if( ulType & XPP_NUMERIC )
   {
      return (DWORD) _parLong( pl, nParam );
   }
   else if( ulType & XPP_ARRAY )
   {
      ULONG nElements = _paralen( pl, nParam, 0 );
      ULONG n;
      DWORD dw = 0;
      for( n = 1; n <= nElements; n++ ) dw |= _parLong( pl, nParam, n, 0 );
      return dw;
   }
   return (DWORD) 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszzACParam
            | syntax_: `LPSTR _pszzACParam( XppParamList pl, ULONG nParam )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszzACParam
            | _kw_: pszz parameter, string or array, double zero list
   }}*/
/*{{|desc: Returns a pszz buffer from a Xbase++ character parameter. If the parameter is a single string,
      returns it as a pszz buffer (string + Chr(0)+Chr(0)). If the parameter is an array of strings,
      concatenates all elements separated by Chr(0), ending with Chr(0)+Chr(0).
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).

    Returns LPSTR - Newly allocated pszz buffer. Must be released with _xfree().

    |note: The returned string must be released with _xfree() when no longer needed. }}*/
OT4XB_API LPSTR _pszzACParam( XppParamList pl, ULONG nParam )
{
   ULONG ulType = _partype( pl, nParam );
   if( ulType & XPP_CHARACTER )
   {
      ULONG nLen = _parclen( pl, nParam );
      LPSTR p = (LPSTR) _xgrab( nLen + 2 );
      _parc( p, nLen + 1, pl, nParam );
      return p;
   }
   else if( ulType & XPP_ARRAY )
   {
      ULONG nElements = _paralen( pl, nParam, 0 );
      ULONG n;
      ULONG nSize = 2;
      LPSTR pOut, p;
      for( n = 1; n <= nElements; n++ ) nSize += _parclen( pl, nParam, n, 0 ) + 1;
      pOut = (LPSTR) _xgrab( (UINT) nSize );
      p = pOut;
      for( n = 1; n <= nElements; n++ )
      {
         if( _paratype( pl, nParam, n, 0 ) & XPP_CHARACTER )
         {
            ULONG nn = _parc( p, nSize, pl, nParam, n, 0 ) + 1;
            nSize -= nn; p += nn;
         }
      }
      return pOut;
   }
   return (LPSTR) _xgrab( 2 );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszParam
            | syntax_: `LPSTR _pszParam( XppParamList pl, ULONG n )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszParam
            | _kw_: string parameter, copy, zero terminated, xgrab, XppParamList
   }}*/
/*{{|desc: Returns a copy of a Xbase++ character parameter as a zero-terminated string, allocated with
      _xgrab(). Must be released with _xfree() when no longer needed.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).

    Returns LPSTR - Pointer to a newly allocated zero-terminated string copy, or NULL if not a string.

    |seealso: See also: {{ilink: <c-function _pszParam_cb> _pszParam_cb}} }}*/
OT4XB_API LPSTR _pszParam( XppParamList pl, ULONG n )
{
   return _pszParam_cb( pl, n, 0 );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszParam_cb
            | syntax_: `LPSTR _pszParam_cb( XppParamList pl, ULONG n, DWORD * pcb )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszParam_cb
            | _kw_: string parameter, copy, length, zero terminated, xgrab
   }}*/
/*{{|desc: Returns a copy of a Xbase++ character parameter as a zero-terminated string, allocated with
      _xgrab(). Must be released with _xfree() when no longer needed. Also returns the length of the string (not
      including the terminating zero) via pcb.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).
    - `pcb` DWORD* - Pointer to receive the string length, not including the terminating zero. May be NULL.

    Returns LPSTR - Pointer to a newly allocated zero-terminated string copy, or NULL if not a string.

    |seealso: See also: {{ilink: <c-function _pszParam> _pszParam}} }}*/
OT4XB_API LPSTR _pszParam_cb( XppParamList pl, ULONG n, DWORD * pcb )
{
   LPSTR p = 0;
   DWORD cb = 0;
   if( _partype( pl, n ) & XPP_CHARACTER )
   {
      cb = _parclen( pl, n );
      if( cb )
      {
         p = (LPSTR) _xgrab( cb + 1 );
         _parc( p, cb + 1, pl, n );
      }
   }
   if( pcb ){
      *pcb = cb;
   }
   return p;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetNLMember
            | syntax_: `LONG _conGetNLMember( ContainerHandle conObj, LPSTR pMName )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetNLMember
            | _kw_: object member, get LONG, ivar, read member
   }}*/
/*{{|desc: Returns the value of a Xbase++ object member as LONG.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).

    Returns LONG - Member value as LONG, or 0 if not found. }}*/
OT4XB_API LONG _conGetNLMember( ContainerHandle conObj, LPSTR pMName )
{
   LONG n = 0;
   ContainerHandle con = _conPutNL( NULLCONTAINER, 0 );
   _conGetMember( conObj, pMName, con );
   _conGetLong( con, &n );
   _conRelease( con );
   return n;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conSetNLMember
            | syntax_: `void _conSetNLMember( ContainerHandle conObj, LPSTR pMName, LONG n )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conSetNLMember
            | _kw_: object member, set LONG, ivar, write member
   }}*/
/*{{|desc: Sets the value of a Xbase++ object member from a LONG.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `n` LONG - Value to store in the member.

    Returns void }}*/
OT4XB_API void _conSetNLMember( ContainerHandle conObj, LPSTR pMName, LONG n )
{
   ContainerHandle con = _conPutNL( NULLCONTAINER, n );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetLMember
            | syntax_: `BOOL _conGetLMember( ContainerHandle conObj, LPSTR pMName )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetLMember
            | _kw_: object member, get BOOL, logical, read member
   }}*/
/*{{|desc: Returns the value of a Xbase++ object member as BOOL.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).

    Returns BOOL - Member value as BOOL, or FALSE if not found. }}*/
OT4XB_API BOOL _conGetLMember( ContainerHandle conObj, LPSTR pMName )
{
   BOOL n = FALSE;
   ContainerHandle con = _conPutL( NULLCONTAINER, 0 );
   _conGetMember( conObj, pMName, con );
   _conGetL( con, &n );
   _conRelease( con );
   return n;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conSetLMember
            | syntax_: `void _conSetLMember( ContainerHandle conObj, LPSTR pMName, BOOL n )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conSetLMember
            | _kw_: object member, set BOOL, logical, write member
   }}*/
/*{{|desc: Sets the value of a Xbase++ object member from a BOOL.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `n` BOOL - Value to store in the member.

    Returns void }}*/
OT4XB_API void _conSetLMember( ContainerHandle conObj, LPSTR pMName, BOOL n )
{
   ContainerHandle con = _conPutL( NULLCONTAINER, n );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
// Return a string from a Xbase++ object member
// the string is guaranteed to be zero terminated, but also can contain zeros inside
// the length of the string ( not counting the terminating zero) is stored inside pnLen if is provided
// The string must be released with _xfree() when no longer needed.
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszMember
            | syntax_: `LPSTR _pszMember( ContainerHandle cono, LPSTR pMName, PULONG pnLen )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszMember
            | _kw_: object member, get string, copy, xgrab
   }}*/
/*{{|desc: Returns a copy of a Xbase++ object string member as a zero-terminated string, allocated with
      _xgrab(). Must be released with _xfree() when no longer needed. Also returns the string length (not
      including the terminating zero) via pnLen.
    | params:
    - `cono` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `pnLen` PULONG - Pointer to receive the string length, not including the terminating zero. May be
      NULL.

    Returns LPSTR - Pointer to a newly allocated zero-terminated string copy, or NULL if not a string. }}*/
OT4XB_API LPSTR _pszMember( ContainerHandle cono, LPSTR pMName, PULONG pnLen )
{
   LPSTR pRet = (LPSTR) 0;
   ULONG nLen = 0;
   ContainerHandle con = _conNew( NULLCONTAINER );
   _conGetMember( cono, pMName, con );
   if( _conSizeC( con, &nLen ) == 0 )
   {
      ULONG nWritten = 0;
      pRet = (LPSTR) _xgrab( nLen + 1 );
      _conGetCL( con, &nWritten, pRet, nLen + 1 );
      if( pnLen != 0 ) pnLen[0] = nWritten;
   }
   _conRelease( con );
   return pRet;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszMember2W
            | syntax_: `LPWSTR _pszMember2W( ContainerHandle cono, LPSTR pMName, PULONG pcc )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _pszMember2W
            | _kw_: object member, get string, wide, UTF-16, xgrab
   }}*/
/*{{|desc: Returns a copy of a Xbase++ object string member converted to Unicode (UCS2), allocated with
      _xgrab(). Must be released with _xfree() when no longer needed. Also returns the number of Unicode
      characters (not bytes) via pcc.
    | params:
    - `cono` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `pcc` PULONG - Pointer to receive the number of Unicode characters, not bytes. May be NULL.

    Returns LPWSTR - Pointer to a newly allocated Unicode string copy, or NULL if not a string.

    |seealso: See also: {{ilink: <c-function _pszMember> _pszMember}} }}*/
OT4XB_API LPWSTR _pszMember2W( ContainerHandle cono, LPSTR pMName, PULONG pcc )
{
   ULONG  cb = 0;
   LPSTR  p = _pszMember( cono, pMName, &cb );
   LPWSTR pw = 0;
   int cc = 0;
   if( p ){
      pw = ansi2w( p, (int) cb, &cc ); _xfree( (void *) p );
   }
   if( pcc ){
      pcc[0] = (ULONG) cc;
   }
   return pw;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conSetCLMember
            | syntax_: `void _conSetCLMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue, ULONG nLen )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conSetCLMember
            | _kw_: object member, set string, counted, write member
   }}*/
/*{{|desc: Sets a Xbase++ object member from a sized string (length specified explicitly).
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `pValue` LPSTR - String value to store.
    - `nLen` ULONG - Length of the string in bytes.

    Returns void

    |seealso: See also: {{ilink: <c-function _conSetCMember> _conSetCMember}} }}*/
OT4XB_API void _conSetCLMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue, ULONG nLen )
{
   ContainerHandle con = _conPutCL( NULLCONTAINER, pValue, nLen );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conSetCMember
            | syntax_: `void _conSetCMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conSetCMember
            | _kw_: object member, set string, zero terminated, write member
   }}*/
/*{{|desc: Sets a Xbase++ object member from a zero-terminated string.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `pValue` LPSTR - Zero-terminated string value to store.

    Returns void

    |seealso: See also: {{ilink: <c-function _conSetCLMember> _conSetCLMember}} }}*/
OT4XB_API void  _conSetCMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue )
{
   ContainerHandle con = _conPutC( NULLCONTAINER, pValue );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Fill a character buffer with the content of a Xbase++ object member
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetCLMember
            | syntax_: `void _conGetCLMember( ContainerHandle conObj, LPSTR pMName, LPSTR pBuffer, ULONG nBuffSize )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conGetCLMember
            | _kw_: object member, get string, buffer, read member
   }}*/
/*{{|desc: Copies the value of a Xbase++ object string member into a caller-provided buffer.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).
    - `pBuffer` LPSTR - Caller-provided buffer to receive the string.
    - `nBuffSize` ULONG - Size of the buffer in bytes.

    Returns void

    |seealso: See also: {{ilink: <c-function _conSetCLMember> _conSetCLMember}}, {{ilink: <c-function _pszMember> _pszMember}} }}*/
OT4XB_API void _conGetCLMember( ContainerHandle conObj, LPSTR pMName, LPSTR pBuffer, ULONG nBuffSize )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   if( _conGetMember( conObj, pMName, con ) == 0 )
   {
      ULONG nWritten = 0;
      _conGetCL( con, &nWritten, pBuffer, nBuffSize );
   }
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// Put a NIL value into a Xbase++ object member
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conSetNILMember
            | syntax_: `void _conSetNILMember( ContainerHandle conObj, LPSTR pMName )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conSetNILMember
            | _kw_: object member, set NIL, clear member
   }}*/
/*{{|desc: Sets a Xbase++ object member to NIL.
    | params:
    - `conObj` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pMName` LPSTR - Member name (case insensitive).

    Returns void }}*/
OT4XB_API void _conSetNILMember( ContainerHandle conObj, LPSTR pMName )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// retrieve a ContainerHandle from the Xbase++ paramlist if the param type match <nType>
// values in <nType> can be combined with the bitwise OR operator.
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conTParam
            | syntax_: `ContainerHandle _conTParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG nType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conTParam
            | _kw_: typed parameter, type check, XppParamList, container
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter if its type is one of the types specified in the
      nType mask. If not, releases the container (only if not passed by reference) and returns NULLCONTAINER.
      Also informs whether the parameter was passed by reference via pbByRef.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).
    - `pbByRef` BOOL* - Pointer to receive whether the parameter was passed by reference. May be NULL.
    - `nType` ULONG - XPP type mask of accepted types (e.g. `XPP_CHARACTER | XPP_ARRAY`).

    Returns ContainerHandle - Opaque handle to the parameter value, or NULLCONTAINER if type does not match.

    |seealso: See also: {{ilink: <c-function _conTpParam> _conTpParam}}, {{ilink: <c-function _conCopyParam> _conCopyParam}} }}*/
OT4XB_API ContainerHandle _conTParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG nType )
{
   ContainerHandle con = _conParam( pl, n, pbByRef );
   ULONG lType;
   if( con == NULLCONTAINER )return NULLCONTAINER;
   if( _conType( con, &lType ) == 0 )  if( lType & nType ) return con;
   if( pbByRef != 0 ){
      if( !pbByRef[0] ) _conRelease( con );
   }
   else _conRelease( con );
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conCopyParam
            | syntax_: `ContainerHandle _conCopyParam( XppParamList pl, ULONG n )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conCopyParam
            | _kw_: copy parameter, independent copy, XppParamList, container
   }}*/
/*{{|desc: Returns an independent copy of a Xbase++ parameter as a new ContainerHandle, regardless of whether
      it was passed by reference or by value. The caller must release the returned handle with _conRelease().
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).

    Returns ContainerHandle - Opaque handle to a new independent copy of the parameter value.

    |seealso: See also: {{ilink: <c-function _conTParam> _conTParam}}, {{ilink: <c-function _conTpParam> _conTpParam}} }}*/
OT4XB_API ContainerHandle _conCopyParam( XppParamList pl, ULONG n )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam( pl, n, &bByRef );
   ContainerHandle conr = _conNew( con );
   if( con && ( !bByRef ) ) _conRelease( con );
   return conr;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conTpParam
            | syntax_: `ContainerHandle _conTpParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG * pType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conTpParam
            | _kw_: typed parameter, type string, XppParamList, container
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter if its type is one of the types specified in the
      pType mask. If not, releases the container (only if not passed by reference) and returns NULLCONTAINER.
      Also returns the actual type of the parameter via pType. If pType[0] is 0 on entry, accepts any type.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).
    - `pbByRef` BOOL* - Pointer to receive whether the parameter was passed by reference. May be NULL.
    - `pType` ULONG* - On entry: XPP type mask of accepted types, or 0 to accept any type. On exit: actual
      type of the parameter.

    Returns ContainerHandle - Opaque handle to the parameter value, or NULLCONTAINER if type does not match.

    |seealso: See also: {{ilink: <c-function _conTParam> _conTParam}}, {{ilink: <c-function _conCopyParam> _conCopyParam}} }}*/
OT4XB_API ContainerHandle _conTpParam( XppParamList pl, ULONG n, BOOL * pbByRef, ULONG * pType )
{
   ContainerHandle con;
   ULONG lType;
   if( pType == 0 ) return NULLCONTAINER;
   con = _conParam( pl, n, pbByRef );
   if( con == NULLCONTAINER ){
      pType[0] = 0; return NULLCONTAINER;
   }
   if( _conType( con, &lType ) == 0 )
   {
      if( pType[0] == 0 ) pType[0] = lType;
      if( lType & pType[0] ){
         pType[0] = lType; return con;
      }
   }
   if( pbByRef != 0 ){
      if( !pbByRef[0] ) _conRelease( con );
   }
   else _conRelease( con );
   pType[0] = 0;
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from a Xbase++ object member if match <nType>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conTMember
            | syntax_: `ContainerHandle _conTMember( ContainerHandle Self, LPSTR pszMemberName, ULONG nType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conTMember
            | _kw_: typed member, object member, type check, container
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ object member if its type is one of the types specified in
      the nType mask. If not, releases the container and returns NULLCONTAINER.
    | params:
    - `Self` ContainerHandle - Opaque handle to the Xbase++ object.
    - `pszMemberName` LPSTR - Member name (case insensitive).
    - `nType` ULONG - XPP type mask of accepted types (e.g. `XPP_CHARACTER | XPP_ARRAY`).

    Returns ContainerHandle - Opaque handle to the member value, or NULLCONTAINER if type does not match.

    |seealso: See also: {{ilink: <c-function _conTParam> _conTParam}} }}*/
OT4XB_API ContainerHandle _conTMember( ContainerHandle Self, LPSTR pszMemberName, ULONG nType )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   if( _conGetMember( Self, pszMemberName, con ) == 0 )
   {
      ULONG lType;
      if( _conType( con, &lType ) == 0 )
      {
         if( lType & nType ){
            return con;
         }
      }
   }
   _conRelease( con );
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lCallFuncPA
            | syntax_: `lCallFuncPA( cFuncName, aParams, @uResult )`
            | category: container
            | _kw_: call function, parameters array, by name, dynamic call
   }}*/
/*{{|desc: Calls a Xbase++ function by name passing the elements of an array as individual parameters. Returns
      .F. without raising an error if the function does not exist.
    | params:
    - `cFuncName` String - Name of the function to call.
    - `aParams` Array - Array of values to pass individually to the function.
    - `@uResult` AnyType - Param passed by reference to receive the return value of the called function.

    Returns Logical - .T. if the call succeeded, .F. if the function does not exist.

    |note: If aParams is passed by reference, the parameter array is written back after the call so
      by-reference changes made by the called function are preserved. }}*/
XPPRET XPPENTRY LCALLFUNCPA( XppParamList pl )
{
   BOOL pbRef[3];
   ContainerHandle pcon[3];
   BOOL       bRet = FALSE;

   if( ( pcon[0] = _conTParam( pl, 1, &( pbRef[0] ), XPP_CHARACTER ) ) != NULLCONTAINER )
   {
      LPSTR psz;
      ULONG cb;
      if( ot4xb_conRLockC( pcon[0], &psz, &cb ) == 0 )
      {
         ULONG nParams = 0;
         ContainerHandle * _tos;
         ULONG n;
         pcon[1] = _conTParam( pl, 2, &( pbRef[1] ), XPP_ARRAY );
         if( pcon[1] != NULLCONTAINER ) _conSizeA( pcon[1], &nParams, 0 );
         _tos = (ContainerHandle *) _xgrab( (UINT) ( sizeof( ContainerHandle ) * nParams ) );
         for( n = 1; n <= nParams; n++ ) _tos[( n - 1 )] = _conArrayGet( pcon[1], NULLCONTAINER, n, 0 );
         if( ( pcon[2] = _conParam( pl, 3, &( pbRef[2] ) ) ) == NULLCONTAINER )
         {
            pcon[2] = _conNew( NULLCONTAINER );
            pbRef[2] = FALSE;
         }
         bRet = (BOOL) ( _conCallPa( pcon[2], psz, nParams, _tos ) == 0 );
         if( pbRef[1] ) for( n = 1; n <= nParams; n++ ) _conArrayPut( pcon[1], _tos[( n - 1 )], n, 0 );
         for( n = 1; n <= nParams; n++ ) _conRelease( _tos[( n - 1 )] );
         _xfree( (void *) _tos );
         if( !pbRef[1] ) _conRelease( pcon[1] );
         if( !pbRef[2] ) _conRelease( pcon[2] );
         ot4xb_conUnlockC( pcon[0] );
      }
      if( !pbRef[0] ) _conRelease( pcon[0] );
   }
   _retl( pl, bRet );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lCallMethodPA
            | syntax_: `lCallMethodPA( oSelf, cMethod, aParams, @uResult )`
            | category: container
            | _kw_: call method, parameters array, by name, dynamic call, object
   }}*/
/*{{|desc: Calls a method of a Xbase++ object passing the elements of an array as individual parameters.
      Returns .F. without raising an error if the object is not valid or the method does not exist.
    | params:
    - `oSelf` Object - Object on which to call the method.
    - `cMethod` String - Name of the method to call.
    - `aParams` Array - Array of values to pass individually to the method.
    - `@uResult` AnyType - Param passed by reference to receive the return value of the called method.

    Returns Logical - .T. if the call succeeded, .F. if the object is not valid or the method does not exist.

    |note: If aParams is passed by reference, the parameter array is written back after the call so
      by-reference changes made by the called method are preserved.

    |seealso: See also: {{ilink: <function lCallFuncPA> lCallFuncPA}} }}*/
XPPRET XPPENTRY LCALLMETHODPA( XppParamList pl )
{
   BOOL pbRef[4];
   ContainerHandle pcon[4];
   BOOL       bRet = FALSE;

   if( ( pcon[0] = _conTParam( pl, 1, &( pbRef[0] ), XPP_OBJECT ) ) != NULLCONTAINER )
   {
      if( ( pcon[1] = _conTParam( pl, 2, &( pbRef[1] ), XPP_CHARACTER ) ) != NULLCONTAINER )
      {
         LPSTR psz;
         ULONG cb;
         if( ot4xb_conRLockC( pcon[1], &psz, &cb ) == 0 )
         {
            ULONG nParams = 0;
            ContainerHandle * _tos;
            ULONG n;
            pcon[2] = _conTParam( pl, 3, &( pbRef[2] ), XPP_ARRAY );
            if( pcon[2] != NULLCONTAINER ) _conSizeA( pcon[2], &nParams, 0 );
            _tos = (ContainerHandle *) _xgrab( (UINT) ( sizeof( ContainerHandle ) * ( nParams + 1 ) ) );
            _tos[0] = pcon[0];
            for( n = 1; n <= nParams; n++ ) _tos[n] = _conArrayGet( pcon[2], NULLCONTAINER, n, 0 );
            if( ( pcon[3] = _conParam( pl, 4, &( pbRef[3] ) ) ) == NULLCONTAINER )
            {
               pcon[3] = _conNew( NULLCONTAINER );
               pbRef[3] = FALSE;
            }
            bRet = (BOOL) ( _conCallMethodPa( pcon[3], psz, nParams + 1, _tos ) == 0 );
            if( pbRef[2] ) for( n = 1; n <= nParams; n++ ) _conArrayPut( pcon[2], _tos[n], n, 0 );
            for( n = 1; n <= nParams; n++ ) _conRelease( _tos[n] );
            _xfree( (void *) _tos );
            if( !pbRef[2] ) _conRelease( pcon[2] );
            if( !pbRef[3] ) _conRelease( pcon[3] );
            ot4xb_conUnlockC( pcon[1] );
         }
         if( !pbRef[1] ) _conRelease( pcon[1] );
      }
      if( !pbRef[0] ) _conRelease( pcon[0] );
   }
   _retl( pl, bRet );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: CallFunction
            | syntax_: `CallFunction( cFuncName, params... )`
            | category: container
            | _kw_: call function, by name, dynamic call, variable parameters
   }}*/
/*{{|desc: Calls a Xbase++ function by name. The function name is the first parameter, followed by any number
      of parameters to pass to the function. Returns NIL if the function cannot be called.
    | params:
    - `cFuncName` String - Name of the function to call.
    - `params...` AnyType - Any number of values to pass to the function.

    Returns AnyType - Return value of the called function, or NIL if the function cannot be called.

    |seealso: See also: {{ilink: <function lCallFuncPA> lCallFuncPA}} }}*/
XPPRET XPPENTRY CALLFUNCTION( XppParamList pl )
{
   BOOL * _ref;
   ContainerHandle * _tos;
   ULONG       nParams = _partype( pl, 0 );
   ContainerHandle  _eval = NULLCONTAINER;
   ULONG n;
   LPSTR pfName;

   if( !( _partype( pl, 1 ) & XPP_CHARACTER ) ){
      _ret( pl ); return;
   }
   _ref = (BOOL *) _xgrab( (UINT) ( sizeof( BOOL ) * nParams ) );
   _tos = (ContainerHandle *) _xgrab( (UINT) ( sizeof( ContainerHandle ) * nParams ) );
   for( n = 0; n < nParams; n++ ) _tos[n] = _conParam( pl, n + 1, &_ref[n] );
   _eval = _conNew( NULLCONTAINER );
   if ( ot4xb_conRLockC( _tos[0], &pfName, &n ) == 0 )
   {
      _conCallPa( _eval, pfName, nParams - 1, &( _tos[ 1 ] ) );
      ot4xb_conUnlockC( _tos[ 0 ] );
   }
   for( n = 0; n < nParams; n++ ) if( !_ref[n] ) _conRelease( _tos[n] );
   _xfree( (void *) _ref );
   _xfree( (void *) _tos );
   _conReturn( pl, _eval );
   _conRelease( _eval );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lObjGetMember
            | syntax_: `lObjGetMember( oSelf, cMemberName, @uVal )`
            | category: container
            | _kw_: object member, get, by name, ivar, reflection
   }}*/
/*{{|desc: Gets the value of a member of a Xbase++ object.
    | params:
    - `oSelf` Object - Object from which to get the member value.
    - `cMemberName` String - Name of the member (case insensitive).
    - `@uVal` AnyType - Param passed by reference to receive the member value.

    Returns Logical - .T. if the member was retrieved successfully, .F. otherwise.

    |seealso: See also: {{ilink: <function lObjSetMember> lObjSetMember}} }}*/
XPPRET XPPENTRY LOBJGETMEMBER( XppParamList pl )
{

   BOOL bRet = FALSE;
   BOOL bSelfByRef, bNameByRef, bValByRef;
   ContainerHandle Self, conName, conVal;

   if( ( Self = _conTParam( pl, 1, &bSelfByRef, XPP_OBJECT ) ) != NULLCONTAINER )
   {
      if( ( conName = _conTParam( pl, 2, &bNameByRef, XPP_CHARACTER ) ) != NULLCONTAINER )
      {
         LPSTR psz;
         ULONG cb;
         if( ot4xb_conRLockC( conName, &psz, &cb ) == 0 )
         {
            if( ( conVal = _conParam( pl, 3, &bValByRef ) ) == NULLCONTAINER )
            {
               conVal = _conNew( NULLCONTAINER );
               bValByRef = FALSE;
            }
            bRet = (BOOL) ( _conGetMember( Self, psz, conVal ) == 0 );

            if( !bValByRef ) _conRelease( conVal );
            ot4xb_conUnlockC( conName );
         }
         if( !bNameByRef ) _conRelease( conName );
      }
      if( !bSelfByRef ) _conRelease( Self );
   }
   _retl( pl, bRet );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lObjSetMember
            | syntax_: `lObjSetMember( oSelf, cMemberName, uVal )`
            | category: container
            | _kw_: object member, set, by name, ivar, reflection
   }}*/
/*{{|desc: Sets the value of a member of a Xbase++ object.
    | params:
    - `oSelf` Object - Object on which to set the member value.
    - `cMemberName` String - Name of the member (case insensitive).
    - `uVal` AnyType - Value to assign to the member.

    Returns Logical - .T. if the member was set successfully, .F. otherwise.

    |seealso: See also: {{ilink: <function lObjGetMember> lObjGetMember}} }}*/
XPPRET XPPENTRY LOBJSETMEMBER( XppParamList pl )
{

   BOOL bRet = FALSE;
   BOOL bSelfByRef, bNameByRef, bValByRef;
   ContainerHandle Self, conName, conVal;

   if( ( Self = _conTParam( pl, 1, &bSelfByRef, XPP_OBJECT ) ) != NULLCONTAINER )
   {
      if( ( conName = _conTParam( pl, 2, &bNameByRef, XPP_CHARACTER ) ) != NULLCONTAINER )
      {
         LPSTR psz;
         ULONG cb;
         if( ot4xb_conRLockC( conName, &psz, &cb ) == 0 )
         {
            if( ( conVal = _conParam( pl, 3, &bValByRef ) ) != NULLCONTAINER )
            {
               bRet = (BOOL) ( _conSetMember( Self, psz, conVal ) == 0 );
            }
            if( !bValByRef ) _conRelease( conVal );
            ot4xb_conUnlockC( conName );
         }
         if( !bNameByRef ) _conRelease( conName );
      }
      if( !bSelfByRef ) _conRelease( Self );
   }
   _retl( pl, bRet );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from the param list if was passed by reference and the type is object
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conParamSelfByRef
            | syntax_: `ContainerHandle _conParamSelfByRef( XppParamList pl, ULONG nParam )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conParamSelfByRef
            | _kw_: parameter by reference, object, Self, XppParamList
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter if it is an object and was passed by reference.
      Returns NULLCONTAINER otherwise.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).

    Returns ContainerHandle - Opaque handle to the object, or NULLCONTAINER if not an object or not passed by
      reference.

    |seealso: See also: {{ilink: <c-function _conParamByRef> _conParamByRef}}, {{ilink: <c-function _conTParamByRef> _conTParamByRef}} }}*/
OT4XB_API ContainerHandle _conParamSelfByRef( XppParamList pl, ULONG nParam )
{
   return _conTParamByRef( pl, nParam, XPP_OBJECT );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conParamByRef
            | syntax_: `ContainerHandle _conParamByRef( XppParamList pl, ULONG nParam )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conParamByRef
            | _kw_: parameter by reference, @, XppParamList, container
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter only if it was passed by reference. Returns
      NULLCONTAINER if the parameter was not passed by reference.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).

    Returns ContainerHandle - Opaque handle to the parameter, or NULLCONTAINER if not passed by reference.

    |seealso: See also: {{ilink: <c-function _conTParamByRef> _conTParamByRef}}, {{ilink: <c-function _conParamSelfByRef> _conParamSelfByRef}} }}*/
OT4XB_API ContainerHandle _conParamByRef( XppParamList pl, ULONG nParam )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam( pl, nParam, &bByRef );
   if( con == NULLCONTAINER ) return NULLCONTAINER;
   if( !bByRef ){
      _conRelease( con ); return NULLCONTAINER;
   }
   return con;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conTParamByRef
            | syntax_: `ContainerHandle _conTParamByRef( XppParamList pl, ULONG nParam, ULONG ulType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conTParamByRef
            | _kw_: parameter by reference, typed, type flags, XppParamList
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter only if it was passed by reference and its type
      is one of the types specified in the ulType mask. Returns NULLCONTAINER otherwise.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `ulType` ULONG - XPP type mask of accepted types.

    Returns ContainerHandle - Opaque handle to the parameter, or NULLCONTAINER if not passed by reference or
      type does not match.

    |seealso: See also: {{ilink: <c-function _conParamByRef> _conParamByRef}}, {{ilink: <c-function _conTParam> _conTParam}} }}*/
OT4XB_API ContainerHandle _conTParamByRef( XppParamList pl, ULONG nParam, ULONG ulType )
{
   ContainerHandle con = _conParamByRef( pl, nParam );
   ULONG nParamType = 0;
   if( con == NULLCONTAINER ) return NULLCONTAINER;
   _conType( con, &nParamType );
   if( nParamType & ulType ) return con;
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conTpParamByRef
            | syntax_: `ContainerHandle _conTpParamByRef( XppParamList pl, ULONG nParam, ULONG * pType )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conTpParamByRef
            | _kw_: parameter by reference, typed, type string, XppParamList
   }}*/
/*{{|desc: Returns the ContainerHandle of a Xbase++ parameter only if it was passed by reference and its type
      is one of the types specified in the pType mask. Also returns the actual type of the parameter via pType.
      If pType[0] is 0 on entry, accepts any type. Returns NULLCONTAINER if not passed by reference or type does
      not match.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nParam` ULONG - Position of the parameter (1-based).
    - `pType` ULONG* - On entry: XPP type mask of accepted types, or 0 to accept any type. On exit: actual
      type of the parameter.

    Returns ContainerHandle - Opaque handle to the parameter, or NULLCONTAINER if not passed by reference or
      type does not match.

    |seealso: See also: {{ilink: <c-function _conTpParam> _conTpParam}}, {{ilink: <c-function _conTParamByRef> _conTParamByRef}} }}*/
OT4XB_API ContainerHandle _conTpParamByRef( XppParamList pl, ULONG nParam, ULONG * pType )
{
   BOOL            bByRef = FALSE;
   ContainerHandle con = _conTpParam( pl, nParam, &bByRef, pType );
   if( con == NULLCONTAINER ) return NULLCONTAINER;
   if( !bByRef ){
      _conRelease( con );  return NULLCONTAINER;
   }
   return con;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conReleaseM
            | syntax_: `void _conReleaseM( ContainerHandle con, ..., NULLCONTAINER )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conReleaseM
            | _kw_: release containers, multiple, NULLCONTAINER terminated
   }}*/
/*{{|desc: Releases multiple ContainerHandles in a single call. The argument list must end with NULLCONTAINER.
    | params:
    - `con, ...` ContainerHandle - One or more ContainerHandles to release. MUST end with NULLCONTAINER.

    Returns void }}*/
OT4XB_API void _conReleaseM( ContainerHandle con, ... )
{
   va_list pMarker;
   ContainerHandle conx = NULLCONTAINER;
   if( con ){
      _conRelease( con );
   }
   va_start( pMarker, con );
   while( ( conx = va_arg( pMarker, ContainerHandle ) ) != 0 ){
      _conRelease( conx );
   }
   va_end( pMarker );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conReleasePa
            | syntax_: `void _conReleasePa( ContainerHandle * pcon, ULONG np )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conReleasePa
            | _kw_: release containers, array of handles
   }}*/
/*{{|desc: Releases an array of ContainerHandles.
    | params:
    - `pcon` ContainerHandle* - Pointer to an array of ContainerHandles to release.
    - `np` ULONG - Number of ContainerHandles in the array.

    Returns void

    |seealso: See also: {{ilink: <c-function _conReleaseM> _conReleaseM}} }}*/
OT4XB_API void _conReleasePa( ContainerHandle * pcon, ULONG np )
{
   if( pcon )
   {
      ULONG n = 0;
      for( n = 0; n < np; n++ )
      {
         if( pcon[n] ){
            _conRelease( pcon[n] );
         }
         pcon[n] = 0;
      }
   }
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
// if pcon point to a NIL Xbase++ container, release the container and store a NULLCONTAINER at the provided pointer
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conNil2NullContainer
            | syntax_: `void _conNil2NullContainer( ContainerHandle * pcon )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conNil2NullContainer
            | _kw_: release NIL container, NULLCONTAINER, cleanup
   }}*/
/*{{|desc: Releases a ContainerHandle if it contains NIL and sets the pointer to NULLCONTAINER.
    | params:
    - `pcon` ContainerHandle* - Pointer to a ContainerHandle. Set to NULLCONTAINER if the container holds
      NIL.

    Returns void }}*/
OT4XB_API void _conNil2NullContainer( ContainerHandle * pcon )
{
   if( pcon )
   {
      ULONG ulType = 0;
      _conType( pcon[0], &ulType );
      if( ulType & XPP_UNDEF ){
         _conRelease( pcon[0] ); pcon[0] = NULLCONTAINER;
      }
   }
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetSizeC
            | syntax_: `LONG _conArrayGetSizeC( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetSizeC
            | _kw_: array element, string length, indices
   }}*/
/*{{|desc: Returns the length of a string stored inside a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns LONG - Length of the string, or 0 if the element is not a string. }}*/
OT4XB_API LONG _conArrayGetSizeC( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   LONG nRet = 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conSizeC( con, (ULONG *) &nRet ) != 0 ) nRet = 0;
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetXStrDup
            | syntax_: `LPSTR _conArrayGetXStrDup( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetXStrDup
            | _kw_: array element, get string, copy, xgrab, indices
   }}*/
/*{{|desc: Returns a copy of a string stored inside a Xbase++ array element at the specified indices, allocated
      with _xgrab(). Must be released with _xfree() when no longer needed.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns LPSTR - Pointer to a newly allocated zero-terminated string copy, or NULL if the element is not a
      string. }}*/
OT4XB_API LPSTR _conArrayGetXStrDup( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   ULONG nLen;
   LPSTR pRet = (LPSTR) 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conSizeC( con, &nLen ) == 0 )
   {
      ULONG nWritten = 0;
      pRet = (LPSTR) _xgrab( nLen + 1 );
      _conGetCL( con, &nWritten, pRet, nLen + 1 );
   }
   _conRelease( con );
   return (LPSTR) pRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetCL
            | syntax_: `LONG _conArrayGetCL( ContainerHandle cona, LPSTR pStr, ULONG nLen, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetCL
            | _kw_: array element, get string, buffer, indices
   }}*/
/*{{|desc: Fills a caller-provided buffer with the content of a string stored inside a Xbase++ array element at
      the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pStr` LPSTR - Caller-provided buffer to receive the string.
    - `nLen` ULONG - Size of the buffer in bytes.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns LONG - Number of characters written to the buffer. }}*/
OT4XB_API LONG _conArrayGetCL( ContainerHandle cona, LPSTR pStr, ULONG nLen, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   ULONG nWritten = 0;

   va_start( pMarker, nLen );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, nLen );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   _conGetCL( con, &nWritten, pStr, nLen );
   _conRelease( con );
   return nWritten;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetNL
            | syntax_: `LONG _conArrayGetNL( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetNL
            | _kw_: array element, get LONG, indices
   }}*/
/*{{|desc: Returns a LONG value stored inside a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns LONG - Numeric value of the element, or 0 if not numeric. }}*/
OT4XB_API LONG _conArrayGetNL( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   LONG nRet = 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conGetLong( con, &nRet ) != 0 ) nRet = 0;
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetL
            | syntax_: `BOOL _conArrayGetL( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetL
            | _kw_: array element, get BOOL, logical, indices
   }}*/
/*{{|desc: Returns a BOOL value stored inside a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns BOOL - Logical value of the element, or FALSE if not logical. }}*/
OT4XB_API BOOL _conArrayGetL( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   BOOL nRet = 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conGetL( con, &nRet ) != 0 ) nRet = 0;
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetNLEx
            | syntax_: `LONG _conArrayGetNLEx( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetNLEx
            | _kw_: array element, get LONG, any type, indices
   }}*/
/*{{|desc: Returns a LONG value from a Xbase++ array element at the specified indices, supporting any type
      accepted by _conGetLongEx: - Numeric: detects internal type (double or integer) and converts properly. -
      Logical: returns 1 for .T., 0 for .F. - Character: treats the string buffer as containing the raw 4 bytes
      of a LONG. - Object: assumes the object implements the :_lock_() and :_unlock_() methods (ot4xb structure
      convention), calls :_lock_() to obtain a pointer and reads the first LONG from it.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns LONG - Value of the element as LONG, or 0 if type not supported.

    |seealso: See also: {{ilink: <c-function _conGetLongEx> _conGetLongEx}}, {{ilink: <c-function _conArrayGetNL> _conArrayGetNL}} }}*/
OT4XB_API LONG _conArrayGetNLEx( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   LONG nRet = 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conGetLongEx( con, &nRet ) != 0 ) nRet = 0;
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayGetND
            | syntax_: `double _conArrayGetND( ContainerHandle cona, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayGetND
            | _kw_: array element, get double, indices
   }}*/
/*{{|desc: Returns a double value stored inside a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns double - Numeric value of the element, or 0.0 if not numeric. }}*/
OT4XB_API double _conArrayGetND( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   double nRet = (double) 0;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   if( _conGetND( con, &nRet ) != 0 ) nRet = 0;
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutC_MacroStr
            | syntax_: `XPPAPIRET _conArrayPutC_MacroStr( ContainerHandle cona, LPSTR pStr, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayPutC_MacroStr
            | _kw_: array element, put codeblock, macro compile, indices
   }}*/
/*{{|desc: Compiles a string as a codeblock and stores it into a Xbase++ array element at the specified
      indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pStr` LPSTR - String to compile as a codeblock.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutC_MacroStr( ContainerHandle cona, LPSTR pStr, ... )
{

   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = _conNew( NULLCONTAINER );
   XPPAPIRET nRet;

   va_start( pMarker, pStr );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, pStr );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   // TODO: si no tiene  la forma de un codeblock {|.... |    .... } hay que ponerlo dentro de un codeblock
   // porque no queremos evaluar el codigo sino crear un codeblock
   _conEvalMacroStr( con, pStr );

   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutEmptyData
            | syntax_: ```
                 XPPAPIRET _conArrayPutEmptyData( ContainerHandle cona, ULONG nType, LONG nLength, LONG nDecs, ULONG n1, ..., 0 )
              ```
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayPutEmptyData
            | _kw_: array element, empty value, type, initialize, indices
   }}*/
/*{{|desc: Initializes a Xbase++ array element with the empty value corresponding to the specified type.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `nType` ULONG - XPP type of the element to initialize.
    - `nLength` LONG - Length of the value (used for strings).
    - `nDecs` LONG - Number of decimals (used for numeric values).
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutEmptyData( ContainerHandle cona, ULONG nType, LONG nLength, LONG nDecs, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, nDecs );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, nDecs );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutEmptyData( con, nType, nLength, nDecs );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutNL
            | syntax_: `XPPAPIRET _conArrayPutNL( ContainerHandle cona, LONG nVal, ULONG n1, ..., 0 )`
            | category: container
            | header: ot4xb_cpp_exported.h
            | mangled-name: _conArrayPutNL
            | _kw_: array element, put LONG, indices
   }}*/
/*{{|desc: Stores a LONG value into a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `nVal` LONG - Value to store.
    - `n1...nN, 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutNL( ContainerHandle cona, LONG nVal, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, nVal );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, nVal );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutNL( con, nVal );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutNDF
            | syntax_: ```
                 XPPAPIRET _conArrayPutNDF( ContainerHandle cona, double nd, LONG nDigits, LONG nDec, ULONG nn, ..., 0 )
              ```
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutNDF
            | _kw_: array element, put double, digits decimals, format, indices
   }}*/
/*{{|desc: Stores a double value with explicit digit and decimal format into a Xbase++ array element at the
      specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `nd` double - Double value to store.
    - `nDigits` LONG - Total number of digits.
    - `nDec` LONG - Number of decimal places.
    - `nn, ..., 0` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutNDF( ContainerHandle cona, double nd, LONG nDigits, LONG nDec, ULONG nn, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, nn );
   for( i = 2; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   pi[0] = nn;
   va_start( pMarker, nn );
   for( i = 1; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutNDF( con, nd, nDigits, nDec );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutND
            | syntax_: `XPPAPIRET _conArrayPutND( ContainerHandle cona, double nd, ULONG nn, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutND
            | _kw_: array element, put double, indices
   }}*/
/*{{|desc: Stores a double value into a Xbase++ array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `nd` double - Value to store.
    - `nn` ULONG - First index (1-based).
    - `...` ULONG - Remaining indices, one per dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutND( ContainerHandle cona, double nd, ULONG nn, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, nn );
   for( i = 2; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   pi[0] = nn;
   va_start( pMarker, nn );
   for( i = 1; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutND( con, nd );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutL
            | syntax_: `XPPAPIRET _conArrayPutL( ContainerHandle cona, BOOL bVal, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutL
            | _kw_: array element, put BOOL, logical, indices
   }}*/
/*{{|desc: Stores a BOOL as a Xbase++ logical value into an array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `bVal` BOOL - Value to store (.T. when not 0).
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutL( ContainerHandle cona, BOOL bVal, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, bVal );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, bVal );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutL( con, bVal );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutDS
            | syntax_: `XPPAPIRET _conArrayPutDS( ContainerHandle cona, LPSTR pStr, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutDS
            | _kw_: array element, put date, date string, indices
   }}*/
/*{{|desc: Stores a date string as a Xbase++ Date value into an array element at the specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pStr` LPSTR - Date string in YYYYMMDD format. Eight spaces store an empty date.
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutDS( ContainerHandle cona, LPSTR pStr, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, pStr );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, pStr );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutDS( con, pStr );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutCL
            | syntax_: `XPPAPIRET _conArrayPutCL( ContainerHandle cona, LPSTR pStr, ULONG nLen, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutCL
            | _kw_: array element, put string, counted, indices
   }}*/
/*{{|desc: Stores a byte counted string as a Xbase++ character value into an array element at the specified
      indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pStr` LPSTR - Pointer to the string data to store.
    - `nLen` ULONG - Number of bytes to store.
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutCL( ContainerHandle cona, LPSTR pStr, ULONG nLen, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, nLen );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, nLen );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutCL( con, pStr, nLen );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutBSTR2a
            | syntax_: `XPPAPIRET _conArrayPutBSTR2a( ContainerHandle cona, BSTR bs, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutBSTR2a
            | _kw_: array element, put BSTR, ANSI, indices
   }}*/
/*{{|desc: Converts a BSTR to ANSI and stores it as a Xbase++ character value into an array element at the
      specified indices. A NULL BSTR, or one that cannot be converted, is stored as an empty string.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `bs` BSTR - Wide string to convert and store. May be NULL.
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutBSTR2a( ContainerHandle cona, BSTR bs, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, bs );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, bs );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   if( bs )
   {
      int   cb = 0;
      LPSTR p = w2ansi( (LPWSTR) bs, (int) SysStringLen( bs ), &cb );
      if( p )
      {
         con = _conPutCL( con, p, (ULONG) cb );
         _xfree( (void *) p );
      }
   }
   if( !con ){
      con = _conPutC( con, "" );
   }
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArrayPutC
            | syntax_: `XPPAPIRET _conArrayPutC( ContainerHandle cona, LPSTR pStr, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArrayPutC
            | _kw_: array element, put string, zero terminated, indices
   }}*/
/*{{|desc: Stores a zero terminated string as a Xbase++ character value into an array element at the
      specified indices.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pStr` LPSTR - Zero terminated string to store.
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns XPPAPIRET - Non 0 if error. }}*/
OT4XB_API XPPAPIRET _conArrayPutC( ContainerHandle cona, LPSTR pStr, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   ContainerHandle con = NULLCONTAINER;
   XPPAPIRET nRet;

   va_start( pMarker, pStr );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, pStr );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conPutC( con, pStr );
   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _retcFmt
            | syntax_: `void _retcFmt( XppParamList pl, LPSTR pFmt, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _retcFmt
            | _kw_: return formatted string, wvsprintf, return value
   }}*/
/*{{|desc: Formats a string with wvsprintf() and places it as the character return value of the current
      Xbase++ function. The formatted result is limited to 1023 characters.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `pFmt` LPSTR - wsprintf() style format string.
    - `...` Values required by the format string.

    Returns void }}*/
OT4XB_API void  _retcFmt( XppParamList pl, LPSTR pFmt, ... )
{
   LPSTR pOut = (LPSTR) _xgrab( 1024 );
   va_list          pMarker;

   pOut[0] = pOut[1023] = 0;
   va_start( pMarker, pFmt );
   wvsprintf( pOut, pFmt, pMarker );
   _retc( pl, pOut );
   _xfree( (void *) pOut );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conClassDestroyCon
            | syntax_: `BOOL _conClassDestroyCon( ContainerHandle conco )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conClassDestroyCon
            | _kw_: ClassDestroy, dynamic class, destroy class
   }}*/
/*{{|desc: Tries to destroy a Xbase++ dynamic class by calling the ClassDestroy() function with the supplied
      class object.
    | params:
    - `conco` ContainerHandle - Container holding the class object of the class to destroy.

    Returns BOOL - TRUE when the class was destroyed. }}*/
OT4XB_API BOOL _conClassDestroyCon( ContainerHandle conco )
{
   BOOL bOk = FALSE;
   if( conco != NULLCONTAINER )
   {
      ContainerHandle con = _conPutL( NULLCONTAINER, FALSE );
      if( _conCall( con, "CLASSDESTROY", 1, conco ) == 0 ) _conGetL( con, &bOk );
      _conRelease( con );
   }
   return bOk;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conClsObj
            | syntax_: `ContainerHandle _conClsObj( LPSTR pClassName )`
            | category: container
            | header: ot4xb_api.h
            | mangled-name: _conClsObj
            | _kw_: ClassObject, class object, by name
   }}*/
/*{{|desc: Returns the class object of a class from its name, using the Xbase++ ClassObject() function. The
      class must already be known to the running application.
    | params:
    - `pClassName` LPSTR - Zero terminated class name.

    Returns ContainerHandle - New container holding the class object, or NULLCONTAINER when the class is not
      found. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conClsObj( LPSTR pClassName )
{
   ContainerHandle conco, concn;
   BOOL bOk;

   if( pClassName == 0 ) return NULLCONTAINER;
   conco = _conNew( NULLCONTAINER );
   concn = _conPutC( NULLCONTAINER, pClassName );
   bOk = (BOOL) ( _conCall( conco, "CLASSOBJECT", 1, concn ) == 0 );
   _conRelease( concn );
   if( bOk )
   {
      ULONG ulType = 0;
      _conType( conco, &ulType );
      if( ulType & XPP_OBJECT ) return conco;
   }
   _conRelease( conco );
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conClsObjNew
            | syntax_: `ContainerHandle _conClsObjNew( LPSTR pClassName )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conClsObjNew
            | _kw_: ClassObject, class object, by name, class function fallback
   }}*/
/*{{|desc: Returns the class object of a class from its name. When ClassObject() does not know the class, the
      function with the class name is called to obtain it, so the class is created on first use.
    | params:
    - `pClassName` LPSTR - Zero terminated class name.

    Returns ContainerHandle - New container holding the class object, or NULLCONTAINER when no class object
      can be obtained. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conClsObjNew( LPSTR pClassName )
{
   ContainerHandle conco = _conClsObj( pClassName );
   if( conco != NULLCONTAINER ) return conco;
   else
   {
      BOOL bOk;
      if( pClassName == 0 ) return NULLCONTAINER;
      conco = _conNew( NULLCONTAINER );
      bOk = (BOOL) ( _conCall( conco, pClassName, 0 ) == 0 );
      if( bOk )
      {
         ULONG ulType = 0;
         _conType( conco, &ulType );
         if( ulType & XPP_OBJECT ) return conco;
      }
      _conRelease( conco );
   }
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutNewObj
            | syntax_: `ContainerHandle _conPutNewObj( ContainerHandle conr, LPSTR pClassName, ContainerHandle p1, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutNewObj
            | _kw_: new object, instantiate, class object, New()
   }}*/
/*{{|desc: Creates a new instance of a class and stores it in a container. The class object is obtained with
      _conClsObjNew() and its New() method is called with the supplied parameters. The parameter containers
      are not released.
    | params:
    - `conr` ContainerHandle - Container that receives the new object, or NULLCONTAINER to create one.
    - `pClassName` LPSTR - Zero terminated class name.
    - `p1` ContainerHandle - First parameter for the New() method, or NULLCONTAINER when there are none.
    - `...` ContainerHandle - More parameters for the New() method. MUST end with NULLCONTAINER.

    Returns ContainerHandle - The receiving container. When the class object cannot be obtained it keeps its
      previous value. }}*/
OT4XB_API ContainerHandle _conPutNewObj( ContainerHandle conr, LPSTR pClassName, ContainerHandle p1, ... )
{
   va_list          pMarker;
   ContainerHandle  con;
   TContainerHandleList * pList;

   if( pClassName == 0 ) return NULLCONTAINER;
   if( !conr ){
      conr = _conNew( NULLCONTAINER );
   }
   con = _conClsObjNew( pClassName );
   if( con == NULLCONTAINER ) return conr;
   pList = new TContainerHandleList;
   pList->Add( con ); // Add the class object
   for( con = p1, va_start( pMarker, p1 );
      con != NULLCONTAINER;
      con = (ContainerHandle) va_arg( pMarker, ContainerHandle )
      ) pList->Add( con );
   va_end( pMarker );
   _conCallMethodPa( conr, "NEW", pList->m_nCount, pList->m_pItems );
   pList->Release( 0 ); // Free ClassObject
   delete pList;
   return conr;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conNewObj
            | syntax_: `ContainerHandle _conNewObj( LPSTR pClassName, ContainerHandle p1, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conNewObj
            | _kw_: new object, instantiate, class name, New() parameters
   }}*/
/*{{|desc: Creates a new instance of a class from its class name, calling the New() method with the supplied
      parameters. The parameter containers are not released.
    | params:
    - `pClassName` LPSTR - Zero terminated class name.
    - `p1` ContainerHandle - First parameter for the New() method, or NULLCONTAINER when there are none.
    - `...` ContainerHandle - More parameters for the New() method. MUST end with NULLCONTAINER.

    Returns ContainerHandle - New container holding the object, or NULLCONTAINER when the New() call does
      not produce an object. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conNewObj( LPSTR pClassName, ContainerHandle p1, ... )
{
   va_list          pMarker;
   ContainerHandle  con;
   TContainerHandleList * pList;
   ULONG           ulType = 0;

   if( pClassName == 0 ) return NULLCONTAINER;
   con = _conClsObjNew( pClassName );
   if( con == NULLCONTAINER ) return con;
   pList = new TContainerHandleList;
   pList->Add( con ); // Add the class object
   for( con = p1, va_start( pMarker, p1 );
      con != NULLCONTAINER;
      con = (ContainerHandle) va_arg( pMarker, ContainerHandle )
      ) pList->Add( con );
   va_end( pMarker );
   con = _conNew( NULLCONTAINER );
   _conCallMethodPa( con, "NEW", pList->m_nCount, pList->m_pItems );
   pList->Release( 0 ); // Free ClassObject
   delete pList;
   if( _conType( con, &ulType ) == 0 ){
      if( ulType & XPP_OBJECT ){
         return con;
      }
   }
   _conRelease( con );
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conNewObjR
            | syntax_: `ContainerHandle _conNewObjR( LPSTR pClassName, ContainerHandle p1, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conNewObjR
            | _kw_: new object, instantiate, release parameters
   }}*/
/*{{|desc: Like _conNewObj() but releases every supplied parameter container after the New() call.
    | params:
    - `pClassName` LPSTR - Zero terminated class name.
    - `p1` ContainerHandle - First parameter for the New() method, or NULLCONTAINER when there are none.
    - `...` ContainerHandle - More parameters for the New() method. MUST end with NULLCONTAINER.

    Returns ContainerHandle - New container holding the object, or NULLCONTAINER when the New() call does
      not produce an object. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conNewObjR( LPSTR pClassName, ContainerHandle p1, ... )
{
   va_list          pMarker;
   ContainerHandle  con;
   TContainerHandleList * pList;
   ULONG           ulType = 0;

   if( pClassName == 0 ) return NULLCONTAINER;
   con = _conClsObjNew( pClassName );
   if( con == NULLCONTAINER ) return con;
   pList = new TContainerHandleList;
   pList->Add( con ); // Add the class object
   for( con = p1, va_start( pMarker, p1 );
      con != NULLCONTAINER;
      con = (ContainerHandle) va_arg( pMarker, ContainerHandle )
      ) pList->Add( con );
   va_end( pMarker );
   con = _conNew( NULLCONTAINER );
   _conCallMethodPa( con, "NEW", pList->m_nCount, pList->m_pItems );
   pList->ReleaseAll(); // Free All containers
   delete pList;
   if( _conType( con, &ulType ) == 0 ){
      if( ulType & XPP_OBJECT ){
         return con;
      }
   }
   _conRelease( con );
   return NULLCONTAINER;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetFloat
            | syntax_: `DWORD _conGetFloat( ContainerHandle con, FLOAT * pnf )`
            | category: c-api/container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetFloat
            | _kw_: container to float, numeric, read value
   }}*/
/*{{|desc: Reads a Xbase++ numeric container and stores it as a C FLOAT.
    | params:
    - `con` ContainerHandle - Container holding the numeric value.
    - `pnf` FLOAT * - Receives the value converted to FLOAT.

    Returns DWORD - Non 0 if error.

    |note: These are exported C helpers, not Xbase++ callable functions. }}*/
OT4XB_API DWORD _conGetFloat( ContainerHandle con, FLOAT * pnf )
{
   double nd = 0.00F;
   DWORD result = (DWORD) _conGetND( con, &nd );
   pnf[0] = (FLOAT) nd;
   return result;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutFloat
            | syntax_: `ContainerHandle _conPutFloat( ContainerHandle con, FLOAT nf )`
            | category: c-api/container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutFloat
            | _kw_: float to container, numeric, write value
   }}*/
/*{{|desc: Stores a C FLOAT in a Xbase++ numeric container.
    | params:
    - `con` ContainerHandle - Container to receive the value, or NULLCONTAINER to create a new one.
    - `nf` FLOAT - Value to store.

    Returns ContainerHandle - The container holding the numeric value.

    |note: These are exported C helpers, not Xbase++ callable functions. }}*/
OT4XB_API ContainerHandle _conPutFloat( ContainerHandle con, FLOAT nf )
{
   double nd = (double) nf;
   return _conPutND( con, nd );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetQWord
            | syntax_: `DWORD _conGetQWord( ContainerHandle con, ULONGLONG * pqw )`
            | category: c-api/container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetQWord
            | _kw_: container to QWORD, 8-byte string, ULONGLONG
   }}*/
/*{{|desc: Reads eight binary bytes from a character container into a ULONGLONG.
    | params:
    - `con` ContainerHandle - Container holding the character value with the raw bytes.
    - `pqw` ULONGLONG * - Receives the bytes read from the string.

    Returns DWORD - Non 0 if error.

    |note: These are exported C helpers, not Xbase++ callable functions. }}*/
OT4XB_API DWORD _conGetQWord( ContainerHandle con, ULONGLONG * pqw )
{
   ULONG nBytes;
   return (DWORD) _conGetCL( con, &nBytes, (LPSTR) ( (void *) pqw ), sizeof( ULONGLONG ) );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutQWord
            | syntax_: `ContainerHandle _conPutQWord( ContainerHandle con, ULONGLONG qw )`
            | category: c-api/container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutQWord
            | _kw_: QWORD to container, 8-byte string, ULONGLONG
   }}*/
/*{{|desc: Stores a ULONGLONG as an eight-byte Xbase++ character value.
    | params:
    - `con` ContainerHandle - Container to receive the value, or NULLCONTAINER to create a new one.
    - `qw` ULONGLONG - Value to store as eight raw bytes.

    Returns ContainerHandle - The container holding the eight byte string.

    |note: These are exported C helpers, not Xbase++ callable functions. }}*/
OT4XB_API ContainerHandle _conPutQWord( ContainerHandle con, ULONGLONG qw )
{
   return _conPutCL( con, (LPSTR) ( (void *) &qw ), sizeof( ULONGLONG ) );
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _var2con
            | syntax_: `_var2con( xValue )`
            | category: container/low-level
            | _kw_: value to container, ContainerHandle, copy value, C interop
   }}*/
/*{{|desc: Creates a new Xbase++ container handle containing a copy of a value.
    | params:
    - `xValue` Any - Value to copy into a new container handle.

    Returns Numeric pointer - ContainerHandle value represented as a numeric pointer.

    |note: This is a low-level container helper. The returned handle must be released with _conrelease() when
      it is no longer needed.

    |seealso: See also: {{ilink: <function _con2var> _con2var}}

    |seealso: See also: {{ilink: <function _conrelease> _conrelease}} }}*/
XPPRET XPPENTRY _VAR2CON( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam( pl, 1, &bByRef );
   ContainerHandle conr = _conNew( con );
   if( !bByRef ) _conRelease( con );
   _retnl( pl, (LONG) ( (void *) conr ) );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _con2var
            | syntax_: `_con2var( hContainer )`
            | category: container/low-level
            | _kw_: container to value, ContainerHandle, read value, C interop
   }}*/
/*{{|desc: Returns the Xbase++ value stored in a container handle without releasing the handle.
    | params:
    - `hContainer` Numeric pointer - ContainerHandle value previously obtained from low-level container
      code.

    Returns Any - Value stored in the container, or NIL when hContainer is 0.

    |note: The handle remains owned by the caller. Use _conrelease() when the handle must be released.

    |seealso: See also: {{ilink: <function _var2con> _var2con}}

    |seealso: See also: {{ilink: <function _conrelease> _conrelease}} }}*/
XPPRET XPPENTRY _CON2VAR( XppParamList pl )
{
   ContainerHandle con = (ContainerHandle) ( (void *) _parLong( pl, 1 ) );
   if( con == NULLCONTAINER ) _ret( pl );
   else _conReturn( pl, con );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _conrelease
            | syntax_: `_conrelease( hContainer )`
            | category: container/low-level
            | _kw_: container to value, release handle, ContainerHandle
   }}*/
/*{{|desc: Returns the Xbase++ value stored in a container handle and releases that handle.
    | params:
    - `hContainer` Numeric pointer - ContainerHandle value to return and release.

    Returns Any - Value stored in the container, or NIL when hContainer is 0.

    |note: This helper is intended for handles produced by low-level OT4XB container routines such as
      _var2con().

    |seealso: See also: {{ilink: <function _var2con> _var2con}}

    |seealso: See also: {{ilink: <function _con2var> _con2var}} }}*/
XPPRET XPPENTRY _CONRELEASE( XppParamList pl )
{
   ContainerHandle con = (ContainerHandle) ( (void *) _parLong( pl, 1 ) );
   if( con == NULLCONTAINER ) _ret( pl );
   else {
      _conReturn( pl, con ); _conRelease( con );
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Array2pszz
            | syntax_: `Array2pszz( aStrings | cText, @nBuffSize )`
            | category: container/marshalling
            | _kw_: pszz, double zero list, array to string list, multi string, allocate
   }}*/
/*{{|desc: Allocates a double-zero-terminated string list buffer from a string or array of strings.
    | params:
    - `aStrings` Array - Array of strings to write as item1 + Chr(0) + ... + itemN + Chr(0) + Chr(0).
    - `cText` Character - String to copy into a newly allocated buffer with two trailing zero bytes.
    - `nBuffSize` Numeric by reference - Receives the allocated buffer size in bytes.

    Returns Numeric pointer - Pointer to the allocated pszz buffer, or 0 when the first parameter is not
      supported.

    |note: The returned memory is allocated with _xgrab(). The application owns that buffer and must release it
      with _xfree() when it is no longer required.

    |seealso: See also: {{ilink: <function PSzz2Array> PSzz2Array}} }}*/
XPPRET XPPENTRY ARRAY2PSZZ( XppParamList pl )
{
   ULONG ul = _partype( pl, 1 );
   LPSTR pStr = NULL;
   if( ul & XPP_CHARACTER )
   {
      ULONG nSize = _parclen( pl, 1, 0 ) + 2;
      pStr = (LPSTR) _xgrab( nSize );
      _stornl( (LONG) nSize, pl, 2, 0 );
      _parc( pStr, nSize, pl, 1, 0 );
      _retnl( pl, (LONG) pStr );
   }
   else if( ul & XPP_ARRAY )
   {
      ULONG nSize = 0;
      ULONG nItems = _paralen( pl, 1, 0 );
      ULONG n;
      for( n = 0; n < nItems; n++ ) nSize += ( _parclen( pl, 1, n + 1, 0 ) + 1 );
      if( nSize > 0 )
      {
         LPSTR p = pStr = (LPSTR) _xgrab( nSize + 2 );
         _stornl( (LONG) nSize + 2, pl, 2, 0 );
         for( n = 0; n < nItems; n++ ) p += ( _parc( p, ( nSize - ( p - pStr ) ), pl, 1, n + 1, 0 ) + 1 );
      }
   }
   _retnl( pl, (LONG) pStr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conArray2Pszz
            | syntax_: `LPSTR _conArray2Pszz( ContainerHandle cona, DWORD * pcb )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conArray2Pszz
            | _kw_: pszz, double zero list, array to string list
   }}*/
/*{{|desc: Builds a double zero terminated string list (pszz) from a Xbase++ array of strings. Elements that
      are not strings, or are empty, produce no entry.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array of character values.
    - `pcb` DWORD * - Receives the size in bytes of the allocated buffer. May be NULL.

    Returns LPSTR - Buffer allocated with _xgrab(), holding every string followed by a zero byte plus a
      final extra zero byte, or NULL when the array yields no data. Release it with _xfree(). }}*/
OT4XB_API LPSTR _conArray2Pszz( ContainerHandle cona, DWORD * pcb )
{
   LPSTR pStr = 0;
   ULONG nSize = 0;
   ULONG nItems = _conGetArrayLen( cona );
   ULONG n;
   if( pcb ) pcb[0] = 0;
   for( n = 0; n < nItems; n++ ) nSize += ( _conArrayGetSizeC( cona, n + 1, 0 ) + 1 );
   if( nSize > 0 )
   {
      LPSTR p = pStr = (LPSTR) _xgrab( nSize + 2 );
      if( pcb ) pcb[0] = nSize + 2;
      for( n = 0; n < nItems; n++ )
      {
         DWORD cb = _conArrayGetCL( cona, p, nSize, n + 1, 0 );
         if( cb ){
            cb++; nSize -= cb; p += cb;
         }
      }
   }
   return pStr;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPszz2Array
            | syntax_: `ContainerHandle _conPszz2Array( LPSTR p )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPszz2Array
            | _kw_: pszz, double zero list, string list to array
   }}*/
/*{{|desc: Builds a Xbase++ array of character values from a double zero terminated string list (pszz).
    | params:
    - `p` LPSTR - Pointer to the pszz list. May be NULL.

    Returns ContainerHandle - New container holding the array, one element per substring. A NULL pointer or
      a list with no content gives an empty array. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conPszz2Array( LPSTR p )
{
   TList * pList = new TList;
   ContainerHandle cona;
   ULONG n, nMax;
   BOOL bEmpty = TRUE;
   if( p )
   {
      LPSTR  pStr = p;
      WORD * pw = (WORD *) p;
      for( ; pw[0] != 0; p++, pw = (WORD *) p )
      {
         if( *p == 0 )
         {
            pList->Add( (void *) pStr );
            pStr = p + 1;
         }
         else {
            bEmpty = FALSE;
         }
      }
      if( pStr != 0 ) pList->Add( (void *) pStr );
   }
   nMax = ( bEmpty ? 0 : pList->Count() );
   cona = _conNewArray( 1, nMax );
   for( n = 0; n < nMax; n++ ) _conArrayPutC( cona, (LPSTR) pList->Get( n ), n + 1, 0 );
   delete pList;
   return cona;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ppMarshall2Array
            | syntax_: `ppMarshall2Array( pArrayOfStringPointers )`
            | category: container/marshalling
            | _kw_: argv, LPSTR array, C string array to Xbase++ array
   }}*/
/*{{|desc: Builds an Xbase++ array from a NULL-terminated C array of LPSTR pointers.
    | params:
    - `pArrayOfStringPointers` Numeric pointer - Pointer to a C array of LPSTR values terminated with a
      NULL pointer.

    Returns Array/NIL - An array with one Xbase++ character value for each C string, or NIL when no pointer is
      supplied.

    |note: The function copies the pointed strings into Xbase++ containers. It does not release
      pArrayOfStringPointers and it does not release any string referenced by that array. The pointed C string
      array does not need to have been created by Array2ppMarshall(). The only required layout is a sequence of
      LPSTR pointers ending with a NULL pointer.

    |seealso: See also: {{ilink: <function Array2ppMarshall> Array2ppMarshall}} }}*/
XPPRET XPPENTRY PPMARSHALL2ARRAY( XppParamList pl )
{
   ContainerHandle cona = NULLCONTAINER;
   LPSTR * pp = (LPSTR *) _parLong( pl, 1, 0 );
   if( pp )
   {
      ULONG n;
      ULONG nItems = 0;
      while( pp[nItems] ) nItems++;
      cona = _conNewArray( 1, nItems );
      for( n = 0; n < nItems; n++ ) _conArrayPutC( cona, pp[n], n + 1, 0 );
   }
   if( cona ){
      _conReturn( pl, cona );   _conRelease( cona );
   }
   else _ret( pl );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Array2ppMarshall
            | syntax_: `Array2ppMarshall( aStrings [, @aSizes] )`
            | category: container/marshalling
            | _kw_: argv, LPSTR array, Xbase++ array to C string array, marshal
   }}*/
/*{{|desc: Allocates a buffer containing a NULL-terminated C array of LPSTR pointers and the string data
      referenced by those pointers.
    | params:
    - `aStrings` Array - Array with the character strings to marshal.
    - `aSizes` Array by reference - Optional output array receiving the byte length of each source string,
      not including the trailing zero terminator.

    Returns Numeric pointer - Pointer to the allocated marshalled buffer, or 0 when aStrings is not a
      non-empty array.

    |note: The returned memory is allocated with _xgrab(). The application owns that buffer and must release it
      with _xfree() when it is no longer required. The buffer layout is: LPSTR pStr1 ... LPSTR pStrN DWORD 0
      String1 + Chr(0) ... StringN + Chr(0) This layout is suitable for C APIs that expect a `char**` or LPSTR*
      list terminated with a NULL pointer.

    |seealso: See also: {{ilink: <function ppMarshall2Array> ppMarshall2Array}}

    |example: ```
      BEGIN STRUCTURE pqPrintOpt MEMBER POINTER32 fieldName DYNAMIC METHOD SetFieldNames BLOCK {|s,a|
        _xfree(s:fieldName), ; s:fieldName := iif(a == NIL,0,Array2ppMarshall(a)) } DYNAMIC METHOD GetFieldNames
        BLOCK {|s| ppMarshall2Array(s:fieldName) } END STRUCTURE
      ``` }}*/
XPPRET XPPENTRY ARRAY2PPMARSHALL( XppParamList pl )
{
   ULONG ul = _partype( pl, 1 );
   void * pMem = NULL;
   if( ul & XPP_ARRAY )
   {
      ULONG nItems = _paralen( pl, 1, 0 );
      if( nItems > 0 )
      {
         ULONG * pnSizes = (ULONG *) _xgrab( sizeof( ULONG ) * nItems );
         ULONG nSize = ( 5 * nItems ) + 5;
         LPSTR * ppStr;
         ULONG n;
         LPSTR p;
         for( n = 0; n < nItems; n++ ) nSize += pnSizes[n] = _parclen( pl, 1, n + 1, 0 );
         pMem = _xgrab( nSize );
         ppStr = (LPSTR *) pMem;
         p = (LPSTR) ( (void *) &( ppStr[nItems + 1] ) ); // One NULL item at the end of the array
         for( n = 0; n < nItems; n++ )
         {
            ppStr[n] = p;
            p += _parc( p, pnSizes[n] + 1, pl, 1, n + 1, 0 ) + 1;
         }
         if( _partype( pl, 2 ) & _xpp_REFERENCE )
         {
            BOOL bP2ByRef = TRUE;
            ContainerHandle conP2 = _conParam( pl, 2, &bP2ByRef );
            if( conP2 != NULLCONTAINER )
            {
               if( bP2ByRef )
               {
                  ContainerHandle cona = _conNewArray( 1, nItems );
                  for( n = 0; n < nItems; n++ ) _conArrayPutNL( cona, pnSizes[n], n + 1, 0 );
                  _conPut( conP2, cona );
                  _conRelease( cona );
               }
               else _conRelease( conP2 );
            }
         }
         _xfree( (void *) pnSizes );
         pnSizes = NULL;
      }
   }
   _retnl( pl, (LONG) pMem );
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutZeroString
            | syntax_: `ContainerHandle _conPutZeroString( ContainerHandle con, ULONG nLen )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutZeroString
            | _kw_: zero string, blank buffer, Replicate chr(0), container
   }}*/
/*{{|desc: Creates a Xbase++ character value of the requested length with every byte set to binary zero.
    | params:
    - `con` ContainerHandle - Container to receive the value, or NULLCONTAINER to create a new one.
    - `nLen` ULONG - Length of the string in bytes.

    Returns ContainerHandle - The container holding the zero filled string. }}*/
OT4XB_API ContainerHandle _conPutZeroString( ContainerHandle con, ULONG nLen )
{
   LPSTR p = 0;
   ULONG ul = 0;
   con = _conPutEmptyData( con, XPP_CHARACTER, nLen, 0 );
   ot4xb_conWLockC( con, &p, &ul );
   _bset( (LPBYTE) p, 0, ul );
   ot4xb_conUnlockC( con );
   return con;
}
/*{{end-c-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Type2EmptyValue
            | syntax_: `Type2EmptyValue( cType [, nLen [, nDec]] )`
            | category: container/value
            | _kw_: empty value, by type, default value, blank
   }}*/
/*{{|desc: Creates an empty Xbase++ value for the requested type.
    | params:
    - `cType` Character - One-letter type selector. Supported values are "C" character, "M" memo, "N"
      numeric, "L" logical and "D" date.
    - `nXppType` Numeric - Xbase++ internal type mask such as XPP_CHARACTER, XPP_NUMERIC or XPP_DATE.
    - `nLen` Numeric - Optional length passed to the Xbase++ empty-data constructor.
    - `nDec` Numeric - Optional decimal count passed to the Xbase++ empty-data constructor.

    Returns Any - Empty value for the requested type. Unknown or zero type values return NIL.

    |note: Also Type2EmptyValue( nXppType [, nLen [, nDec]] ) -> xValue

    |note: This is a small wrapper around the Xbase++ empty-data constructor used internally by OT4XB. It is
      useful when code has a field or XPP type descriptor and needs the corresponding empty value. }}*/
XPPRET XPPENTRY TYPE2EMPTYVALUE( XppParamList pl )
{
   ULONG ulType = 0;
   ContainerHandle conr = NULLCONTAINER;
   if( _partype( pl, 1 ) & XPP_CHARACTER )
   {
      char sz[2];
      sz[1] = sz[0] = 0; _parc( sz, 2, pl, 1 );
      switch( sz[0] )
      {
         case 'c':; case 'C':
         {
            ulType = XPP_CHARACTER; break;
         }
         case 'm':; case 'M':
         {
            ulType = XPP_CHARACTER | XPP_MEMO; break;
         }
         case 'n':; case 'N':
         {
            ulType = XPP_NUMERIC;   break;
         }
         case 'l':; case 'L':
         {
            ulType = XPP_LOGICAL;   break;
         }
         case 'd':; case 'D':
         {
            ulType = XPP_DATE;      break;
         }
      }
   }
   else ulType = _parLong( pl, 1 );
   if( ulType ) conr = _conPutEmptyData( conr, ulType, _parLong( pl, 2 ), _parLong( pl, 3 ) );
   else conr = _conNew( conr );
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _parHWND
            | syntax_: `HWND _parHWND( XppParamList pl, ULONG nIndex, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _parHWND
            | _kw_: window handle parameter, HWND, GetHWND, XppParamList
   }}*/
/*{{|desc: Reads a window handle from a Xbase++ parameter. The parameter may be a numeric handle, an object
      implementing a GetHWND() method, or an array holding one of those when element indices are supplied.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `nIndex` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Indices (1-based) selecting the array element when the parameter is an array. MUST
      end with 0.

    Returns HWND - The window handle, or NULL when it cannot be obtained. }}*/
OT4XB_API HWND _parHWND( XppParamList pl, ULONG nIndex, ... )
{
   ULONG ulType = _partype( pl, nIndex );
   LONG  nResult = 0;
   if( ulType & XPP_ARRAY )
   {
      va_list pMarker;
      int pnn[64];
      ULONG n = 0;
      ULONG nn = 0;
      for( n = 0; n < 64; n++ ) pnn[n] = 0;
      n = 0;
      va_start( pMarker, nIndex );
      while( n < 63 && ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
      if( n > 0 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle cona = _conParam( pl, nIndex, &bByRef );
         ContainerHandle con = _conArrayGetA( cona, NULLCONTAINER, pnn );
         if( !bByRef ) _conRelease( cona );
         cona = NULLCONTAINER;
         if( con != NULLCONTAINER )
         {
            ulType = 0; _conType( con, &ulType );
            if( ulType & _xpp_DOUBLE )
            {
               double nd = 0.00F;
               _conGetND( con, &nd );
               nResult = (LONG) nd;
            }
            else if( ulType & XPP_NUMERIC ) _conGetLong( con, &nResult );
            else if( ulType & XPP_OBJECT ) nResult = _conMCallLong( con, "GetHWND" );

            _conRelease( con );
         }
      }
   }
   else if( ulType & XPP_NUMERIC ) nResult = _parLong( pl, nIndex, 0 );
   else if( ulType & XPP_OBJECT )
   {
      BOOL bByRef = FALSE;
      ContainerHandle con = _conParam( pl, nIndex, &bByRef );
      nResult = _conMCallLong( con, "GetHWND" );
      if( !bByRef ) _conRelease( con );
   }
   return (HWND) nResult;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetDateAsFileTime
            | syntax_: `XPPAPIRET _conGetDateAsFileTime( ContainerHandle con, FILETIME * pft )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetDateAsFileTime
            | _kw_: date to FILETIME, Xbase++ date, convert
   }}*/
/*{{|desc: Converts a Xbase++ Date value into a FILETIME set to 00:00:00 of that day. When the date is empty
      the FILETIME is left untouched.
    | params:
    - `con` ContainerHandle - Container holding the Date value.
    - `pft` FILETIME * - Receives the converted value.

    Returns XPPAPIRET - Always 0. }}*/
OT4XB_API XPPAPIRET _conGetDateAsFileTime( ContainerHandle con, FILETIME * pft )
{
   char sz[8];
   LONG n;

   _bset( (LPBYTE) sz, 32, 8 );
   if( con && pft ) _conGetDS( con, sz );
   if( sz[0] >= '0' )
   {
      SYSTEMTIME st;
      _bset( (LPBYTE) &st, 0, sizeof( SYSTEMTIME ) );
      for( n = 0; n < 8; n++ ) sz[n] -= 48;
      st.wDay = (WORD) ( sz[7] + ( sz[6] * 10 ) );
      st.wMonth = (WORD) ( sz[5] + ( sz[4] * 10 ) );
      st.wYear = (WORD) ( ( (WORD) sz[3] ) + ( (WORD) sz[2] * 10 ) + ( (WORD) sz[1] * 100 ) + ( (WORD) sz[0] * 1000 ) );
      if (pft)
      {
         SystemTimeToFileTime(&st, pft);
      }
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetDateAsSystemTime
            | syntax_: `XPPAPIRET _conGetDateAsSystemTime( ContainerHandle con, SYSTEMTIME * pst )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetDateAsSystemTime
            | _kw_: date to SYSTEMTIME, Xbase++ date, convert
   }}*/
/*{{|desc: Fills the date fields of a SYSTEMTIME from a Xbase++ Date value. A character value is also
      accepted; the first eight digits found in it are used as YYYYMMDD. Only wYear, wMonth and wDay are
      written, set to 0 when the date is empty or invalid; the time fields are never modified.
    | params:
    - `con` ContainerHandle - Container holding the Date or character value.
    - `pst` SYSTEMTIME * - Receives the date fields.

    Returns XPPAPIRET - Always 0. }}*/
OT4XB_API XPPAPIRET _conGetDateAsSystemTime( ContainerHandle con, SYSTEMTIME * pst )
{
   char sz[ 16 ] = { 0 };
   LONG n;

   if( con && pst )
   {
      ULONG ul = 0;
      _conType( con, &ul );
      if( (ul & 0xFF) == XPP_CHARACTER )
      {
         char buffer[ 256 ] = { 0 };
         ULONG cb = 0;
         ULONG pos = 0;
         _conGetCL( con, &cb, buffer, sizeof( buffer ) - 1 );
         for( ULONG i = 0; i < cb && pos <  8 ; i++ )
         {
            if( isdigit( buffer[ i ] ) )
            {
               sz[pos] = buffer[ i ]; pos++;
            }
         }
         if( pos < 8 )
         {
            ZeroMemory( sz, sizeof( sz ) );
         }
      }
      else
      {
         _conGetDS( con, sz );
      }
   }
   if( sz[0] >= '0' )
   {
      for( n = 0; n < 8; n++ ) sz[n] -= 48;
      if( pst )
      {
         pst->wDay = (WORD) ( sz[ 7 ] + ( sz[ 6 ] * 10 ) );
         pst->wMonth = (WORD) ( sz[ 5 ] + ( sz[ 4 ] * 10 ) );
         pst->wYear = (WORD) ( ( (WORD) sz[ 3 ] ) + ( (WORD) sz[ 2 ] * 10 ) + ( (WORD) sz[ 1 ] * 100 ) + ( (WORD) sz[ 0 ] * 1000 ) );
      }
   }
   else
   {
      if( pst )
      {
         pst->wDay = 0;
         pst->wMonth = 0;
         pst->wYear = 0;
      }
   }
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetDateTimeAsSystemTime
            | syntax_: ```
                 XPPAPIRET _conGetDateTimeAsSystemTime( ContainerHandle cond, ContainerHandle cont, SYSTEMTIME * pst )
              ```
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetDateTimeAsSystemTime
            | _kw_: date time to SYSTEMTIME, Xbase++ date, time string
   }}*/
/*{{|desc: Fills a SYSTEMTIME from a date container and a time container. The date part follows the
      _conGetDateAsSystemTime() rules; when the date is empty the time part is not read. The time may be a
      character value like HH:MM:SS or HH:MM:SS.mmm, or a numeric count of seconds since midnight as returned
      by Seconds(), where fractions become milliseconds.
    | params:
    - `cond` ContainerHandle - Container holding the date part.
    - `cont` ContainerHandle - Container holding the time part.
    - `pst` SYSTEMTIME * - Receives the result.

    Returns XPPAPIRET - Always 0. }}*/
OT4XB_API XPPAPIRET _conGetDateTimeAsSystemTime( ContainerHandle cond, ContainerHandle cont, SYSTEMTIME * pst )
{
   _conGetDateAsSystemTime( cond, pst );
   if( pst->wDay == 0 ) return 0;
   if( _conCheckType( cont, XPP_CHARACTER ) )
   {
      char sz[32];
      ULONG n = 0;
      ZeroMemory( sz, 32 );
      _conGetCL( cont, &n, sz, 31 );
      sz[2] = sz[5] = sz[8] = sz[12] = 0;
      sz[11] = ( sz[11] ? sz[11] : '0' ); sz[10] = ( sz[10] ? sz[10] : '0' ); sz[9] = ( sz[9] ? sz[9] : '0' );
      pst->wHour = (WORD) ( atoi( sz ) & 0x00FF );
      pst->wMinute = (WORD) ( atoi( sz + 3 ) & 0x00FF );
      pst->wSecond = (WORD) ( atoi( sz + 6 ) & 0x00FF );
      pst->wMilliseconds = (WORD) ( atoi( sz + 9 ) & 0x0FFF );
      return 0;
   }
   if( _conCheckType( cont, XPP_NUMERIC ) )
   {
      LONG nl;
      double nd = 0.00F;
      _conGetND( cont, &nd );
      nl = (LONG) ( nd * 1000.00F );
      if( nl < 0 ) nl = 86400000 + nl;
      pst->wHour = (WORD) ( nl / 3600000 ); nl = ( nl % 3600000 );
      pst->wMinute = (WORD) ( nl / 60000 ); nl = ( nl % 60000 );
      pst->wSecond = (WORD) ( nl / 1000 ); nl = ( nl % 1000 );
      pst->wMilliseconds = (WORD) nl;
      return 0;
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutDateFromFileTime
            | syntax_: `XPPAPIRET _conPutDateFromFileTime( ContainerHandle con, FILETIME * pft )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutDateFromFileTime
            | _kw_: FILETIME to date, Xbase++ date, convert
   }}*/
/*{{|desc: Stores the date part of a FILETIME into a container as a Xbase++ Date value. A NULL FILETIME
      pointer, or one that cannot be converted, stores an empty date.
    | params:
    - `con` ContainerHandle - Container to receive the Date value. Nothing is done when it is
      NULLCONTAINER.
    - `pft` FILETIME * - Value to convert. May be NULL.

    Returns XPPAPIRET - Always 0. }}*/
OT4XB_API XPPAPIRET _conPutDateFromFileTime( ContainerHandle con, FILETIME * pft )
{
   if( con )
   {
      char sz[9];
      _bset( (LPBYTE) sz, 32, 8 );
      if( pft )
      {
         SYSTEMTIME st;
         _bset( (LPBYTE) &st, 0, sizeof( SYSTEMTIME ) );
         if( FileTimeToSystemTime( pft, &st ) )
         {
            wsprintf( sz, "%04.4hu%02.2hu%02.2hu", st.wYear, st.wMonth, st.wDay );
         }
      }
      _conPutDS( con, sz );
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conPutDateFromSystemTime
            | syntax_: `XPPAPIRET _conPutDateFromSystemTime( ContainerHandle con, SYSTEMTIME * pst )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conPutDateFromSystemTime
            | _kw_: SYSTEMTIME to date, Xbase++ date, convert
   }}*/
/*{{|desc: Stores the date fields of a SYSTEMTIME into a container as a Xbase++ Date value. A NULL SYSTEMTIME
      pointer stores an empty date.
    | params:
    - `con` ContainerHandle - Container to receive the Date value. Nothing is done when it is
      NULLCONTAINER.
    - `pst` SYSTEMTIME * - Value to convert. May be NULL.

    Returns XPPAPIRET - Always 0. }}*/
OT4XB_API XPPAPIRET _conPutDateFromSystemTime( ContainerHandle con, SYSTEMTIME * pst )
{
   if( con )
   {
      char sz[9];
      _bset( (LPBYTE) sz, 32, 8 );
      if( pst )
      {
         wsprintf( sz, "%04.4hu%02.2hu%02.2hu", pst->wYear, pst->wMonth, pst->wDay );
      }
      _conPutDS( con, sz );
   }
   return 0;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _cona2i64a
            | syntax_: `LONGLONG * _cona2i64a( ContainerHandle cona, ULONG * pnItems )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _cona2i64a
            | _kw_: array to int64 array, LONGLONG, convert array
   }}*/
/*{{|desc: Converts a Xbase++ array into a C array of LONGLONG values. Character elements are read as up to
      eight raw bytes, numeric elements are converted to integer, Date elements are stored as FILETIME, and
      object elements are read through their :_lock_() and :_unlock_() methods (ot4xb structure convention,
      first eight bytes). Any other type gives 0.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `pnItems` ULONG * - Receives the number of array elements. May be NULL.

    Returns LONGLONG * - Buffer allocated with _xgrab(), one entry per element plus a final entry set to 0,
      or NULL when the array is empty. Release it with _xfree(). }}*/
OT4XB_API LONGLONG * _cona2i64a( ContainerHandle cona, ULONG * pnItems )
{
   ULONG n;
   ULONG nItems = _conGetArrayLen( cona );
   LONGLONG * p = 0;
   if( pnItems ) pnItems[0] = nItems;

   if( nItems )
   {
      p = (LONGLONG *) _xgrab( sizeof( LONGLONG ) * ( nItems + 1 ) );
      for( n = 0; n < nItems; n++ )
      {
         ContainerHandle con = _conNew( NULLCONTAINER );
         ULONG nType = 0;
         _conArrayGet( cona, con, n + 1, 0 );
         _conType( con, &nType );
         switch( nType & 0xFF )
         {
            case XPP_CHARACTER:
            {
               ULONG ul = 0;
               _conGetCL( con, &ul, (LPSTR) ( (void *) &( p[n] ) ), sizeof( LONGLONG ) );
               break;
            }
            case XPP_NUMERIC:
            {
               double nd = 0;
               _conGetND( con, &nd );
               p[n] = (LONGLONG) nd;
               break;
            }
            case XPP_OBJECT:
            {
               LONGLONG * po = (LONGLONG *) _conMCallLong( con, "_lock_" );
               __try{
                  if( po ) p[n] = po[0];
               }
               __finally {
                  _conMCallLong( con, "_unlock_" );
               }
               break;
            }
            case XPP_DATE:
            {
               _conGetDateAsFileTime( con, (FILETIME *) ( (void *) ( &p[n] ) ) );
               break;
            }
         }
         _conRelease( con ); con = NULLCONTAINER;
      }
   }
   return p;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _BSTRParam
            | syntax_: `BSTR _BSTRParam( XppParamList pl, ULONG n )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _BSTRParam
            | _kw_: BSTR parameter, string to BSTR, COM, XppParamList
   }}*/
/*{{|desc: Reads a Xbase++ character parameter and returns it converted to a newly allocated BSTR. The ANSI
      code page is used for the wide conversion.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).

    Returns BSTR - New wide string, or NULL when the parameter is not a non-empty string. Release it with
      SysFreeString(). }}*/
OT4XB_API BSTR _BSTRParam( XppParamList pl, ULONG n )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, n, &bByRef, XPP_CHARACTER );
   BSTR  pb = _conGetBSTR( con );
   if( con && ( !bByRef ) ) _conRelease( con );
   return pb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetBSTRMember
            | syntax_: `BSTR _conGetBSTRMember( ContainerHandle conObj, LPSTR pMName )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetBSTRMember
            | _kw_: object member, BSTR, COM string
   }}*/
/*{{|desc: Reads a member variable of a Xbase++ object and returns its character content as a newly allocated
      BSTR.
    | params:
    - `conObj` ContainerHandle - Container holding the object.
    - `pMName` LPSTR - Zero terminated member name.

    Returns BSTR - New wide string, or NULL when the member is not a non-empty string. Release it with
      SysFreeString(). }}*/
OT4XB_API BSTR _conGetBSTRMember( ContainerHandle conObj, LPSTR pMName )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   BSTR  pb = NULL;
   if( _conGetMember( conObj, pMName, con ) == 0 ) pb = _conGetBSTR( con );
   _conRelease( con );
   return pb;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetBSTR
            | syntax_: `BSTR _conGetBSTR( ContainerHandle con )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetBSTR
            | _kw_: container to BSTR, COM string, SysAllocString
   }}*/
/*{{|desc: Converts the character content of a container into a newly allocated BSTR. The ANSI code page is
      used for the wide conversion.
    | params:
    - `con` ContainerHandle - Container holding the character value.

    Returns BSTR - New wide string, or NULL when the container does not hold a non-empty string. Release it
      with SysFreeString(). }}*/
OT4XB_API BSTR _conGetBSTR( ContainerHandle con )
{
   BSTR  pbStr = (BSTR) 0;
   if( con )
   {
      ULONG nLen = 0;
      LPSTR pStr = (LPSTR) 0;
      if( ot4xb_conRLockC( con, &pStr, &nLen ) == 0 )
      {
         if( nLen > 0 )
         {
            pbStr = SysAllocStringByteLen( 0, (UINT) ( nLen * 2 ) );
            if( pbStr != 0 )
            {
               MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, pStr, nLen, (LPWSTR) pbStr, nLen );

            }
         }
         ot4xb_conUnlockC( con );
      }
   }
   return pbStr;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: _conArrayGetBSTR(ContainerHandle,...)
            | _tg_: _conArrayGetBSTR
            | syntax_: `BSTR _conArrayGetBSTR( ContainerHandle cona, ... )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: ?_conArrayGetBSTR@@YAPA_WPAUMomHandleEntry@@ZZ
            | _kw_: array element, BSTR, COM string, indices
   }}*/
/*{{|desc: Returns the character content of a Xbase++ array element converted to a newly allocated BSTR.
    | params:
    - `cona` ContainerHandle - Opaque handle to the Xbase++ array.
    - `...` ULONG - Indices (1-based) for each dimension. MUST end with 0.

    Returns BSTR - New wide string, or NULL when the element is not a non-empty string. Release it with
      SysFreeString(). }}*/
OT4XB_API BSTR _conArrayGetBSTR( ContainerHandle cona, ... )
{
   int * pi;
   int   i;
   va_list pMarker;
   BSTR  pbStr = (BSTR) 0;
   ContainerHandle con = NULLCONTAINER;

   va_start( pMarker, cona );
   for( i = 1; ( va_arg( pMarker, ULONG ) != 0 ); i++ );
   va_end( pMarker );
   pi = (int *) _xgrab( (UINT) ( ( i + 1 ) * sizeof( int ) ) );

   va_start( pMarker, cona );
   for( i = 0; ( ( pi[i] = va_arg( pMarker, ULONG ) ) != 0 ); i++ );
   va_end( pMarker );

   con = _conArrayGetA( cona, con, pi );
   _xfree( (void *) pi );
   pbStr = _conGetBSTR( con );
   _conRelease( con );
   return pbStr;
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGetHWND
            | syntax_: `HWND _conGetHWND( ContainerHandle con )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGetHWND
            | _kw_: container to HWND, window handle, GetHWND
   }}*/
/*{{|desc: Reads a window handle from a container. Accepts a numeric value or an object implementing a
      GetHWND() method.
    | params:
    - `con` ContainerHandle - Container holding the numeric handle or the object.

    Returns HWND - The window handle, or NULL when it cannot be obtained. }}*/
OT4XB_API HWND _conGetHWND( ContainerHandle con )
{
   HWND hWnd = 0;
   if( con )
   {
      ULONG ulType = 0;
      _conType( con, &ulType );
      if( ulType & XPP_NUMERIC ) _conGetLong( con, (LONG *) &hWnd );
      else if( ulType & XPP_OBJECT ) hWnd = (HWND) _conMCallLong( con, "GetHWND" );
   }
   return (HWND) hWnd;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_memvar_setget
            | syntax_: `ot4xb_memvar_setget( cName )`
            | category: container/memvar
            | _kw_: memvar, public private variable, by name, get set
   }}*/
/*{{|desc: Gets or sets an Xbase++ memvar by name.
    | params:
    - `cName` Character - Name of the memvar.
    - `xValue` Any - Optional value to assign to the memvar.

    Returns Any - With one parameter, returns the memvar value. With two parameters, sets the memvar and
      returns NIL.

    |note: Also ot4xb_memvar_setget( cName, xValue ) -> NIL }}*/
XPPRET XPPENTRY OT4XB_MEMVAR_SETGET( XppParamList pl )
{
   ContainerHandle  conr = _conNew( NULLCONTAINER );
   BOOL             bNameByRef = FALSE;
   ContainerHandle  conName = _conTParam( pl, 1, &bNameByRef, XPP_CHARACTER );
   if( conName )
   {
      LPSTR pName = 0;
      ULONG cb = 0;
      if( ot4xb_conRLockC( conName, &pName, &cb ) == 0 )
      {
         if( _partype( pl, 0 ) == 2 )
         {
            BOOL bByRef = FALSE;
            ContainerHandle con = _conParam( pl, 2, &bByRef );
            if( con ){
               _conSetMemvar( pName, con ); if( !bByRef ){
                  _conRelease( con );
               }
            }
         }
         else {
            _conGetMemvar( pName, conr );
         }
         ot4xb_conUnlockC( conName );
      }
      if( !bNameByRef ) _conRelease( conName );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _pszCaptionParam
            | syntax_: `void _pszCaptionParam( XppParamList pl, ULONG n )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _pszCaptionParam
            | _kw_: caption parameter, tilde to ampersand, mnemonic, window caption
   }}*/
/*{{|desc: Reads a Xbase++ character parameter and returns a copy prepared for Windows captions: each '~' is
      replaced with '&' and each ';' with a tab character. The copy is allocated with _xgrab() and must be
      released with _xfree(). Returns NULL when the parameter is not a non-empty string.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).

    Returns void }}*/
LPSTR OT4XB_API _pszCaptionParam( XppParamList pl, ULONG n )
{
   ULONG nLen = _parclen( pl, n );
   if( nLen != 0 )
   {
      LPSTR p = (LPSTR) _xgrab( nLen + 1 );
      ULONG i;
      _parc( p, nLen + 1, pl, n );
      for( i = 0; i < nLen; i++ )
      {
         if( p[i] == '~' ) p[i] = '&';
         else if( p[i] == ';' ) p[i] = 9;
      }
      return p;
   }
   return NULL;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#pragma warning(disable: 4740 )
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-function}}*/
/*{{cpp-function_: ot4xb_parclen(XppParamList,ULONG,...)
            | _tg_: ot4xb_parclen
            | syntax_: `ULONG ot4xb_parclen( XppParamList pl, ULONG n, ... )`
            | category: container
            | header: ot4xb_api.h
            | mangled-name: ?ot4xb_parclen@@YAKPAXKZZ
            | _kw_: _parclen, parameter length, guarded, string parameter
   }}*/
/*{{|desc: Guarded version of the Xbase++ runtime _parclen(). When the requested position is greater than the
      actual parameter count it returns 0; otherwise execution continues in the original runtime routine.
    | params:
    - `pl` XppParamList - Opaque handle to the Xbase++ parameter list.
    - `n` ULONG - Position of the parameter (1-based).
    - `...` ULONG - Optional array element indices, as accepted by the runtime _parclen().

    Returns ULONG - Length of the character value, or 0 when the parameter is not present. }}*/
OT4XB_API __declspec( naked ) ULONG __cdecl ot4xb_parclen( XppParamList pl, ULONG n, ... )
{
   __asm push  ebp;
   __asm mov   ebp, esp;
   if( _partype( pl, 0 ) < n )
   {
      __asm mov eax, 0;
      __asm pop ebp;
      __asm retn;
   }
   __asm mov esp, ebp;
   __asm pop ebp;
   __asm jmp _fp_parclen_jmp_;
}
/*{{end-cpp-function}}*/
// -----------------------------------------------------------------------------------------------------------------
void _hook_parclen( void )
{
   DWORD   dw = 0;
   DWORD   dwOld = (DWORD) GetProcAddress( GetModuleHandle( "xpprt1.dll" ), "__parclen" );
   DWORD   dwNew = (DWORD) HeapAlloc( GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, 10 );
   DWORD   dwJmp = (DWORD) ot4xb_parclen;
   _fp_parclen_jmp_ = dwNew;
   VirtualProtect( (void *) dwOld, 5, 4, &dw );
   _bcopy( (LPBYTE) dwNew, (LPBYTE) dwOld, 5 );
   reinterpret_cast<LPBYTE>( dwNew )[5] = 0xE9;
   reinterpret_cast<LONG *>( dwNew + 6 )[0] = ( (LONG) dwOld + 5 ) - ( (LONG) ( dwNew + 10 ) );
   VirtualProtect( (void *) dwNew, 10, 64, &dw );
   reinterpret_cast<LPBYTE>( dwOld )[0] = 0xE9;
   reinterpret_cast<LONG *>( dwOld + 1 )[0] = ( (LONG) dwJmp ) - ( (LONG) ( dwOld + 5 ) );
   VirtualProtect( (void *) dwOld, 5, 64, &dw );
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conaadd
            | syntax_: `ContainerHandle _conaadd( ContainerHandle cona, ContainerHandle con )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conaadd
            | _kw_: AAdd, append element, array, container
   }}*/
/*{{|desc: Appends one element to a Xbase++ array, like the AAdd() function. When cona does not hold an array
      it is turned into a one element array, creating a new container when it is NULLCONTAINER.
    | params:
    - `cona` ContainerHandle - Container holding the array, or NULLCONTAINER.
    - `con` ContainerHandle - Container with the value for the new element, or NULLCONTAINER to leave it
      NIL.

    Returns ContainerHandle - The container holding the grown array. }}*/
OT4XB_API ContainerHandle _conaadd( ContainerHandle cona, ContainerHandle con )
{
   ULONG nSize = 0;
   if( _conCheckType( cona, XPP_ARRAY ) )
   {
      nSize = _conGetArrayLen( cona );
      nSize++;
      _conResizeA( cona, nSize );
   }
   else
   {
      ContainerHandle conTmp = _conNewArray( 1, 1 );
      nSize = 1;
      cona = _conPut( cona, conTmp );
      _conRelease( conTmp );
   }
   if( con ){
      _conArrayPut( cona, con, nSize, 0 );
   }
   return cona;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conNewCodeblock
            | syntax_: `ContainerHandle _conNewCodeblock( LPSTR pStr )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conNewCodeblock
            | _kw_: codeblock, macro compile, create block, string to block
   }}*/
/*{{|desc: Creates a codeblock by macro compiling a source string written in Xbase++ codeblock syntax.
    | params:
    - `pStr` LPSTR - Zero terminated string with the codeblock source.

    Returns ContainerHandle - New container holding the codeblock, or NULLCONTAINER when the string cannot
      be compiled. Release it with _conRelease() when no longer needed. }}*/
OT4XB_API ContainerHandle _conNewCodeblock( LPSTR pStr )
{
   ContainerHandle conb = _conNew( NULLCONTAINER );
   if( pStr )
   {
      if( _conEvalMacroStr( conb, pStr ) == 0 ){
         return conb;
      }
   }
   _conRelease( conb ); conb = 0;
   return 0;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: _conGenericBreakCB
            | syntax_: `ContainerHandle _conGenericBreakCB( BOOL bCopy )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: _conGenericBreakCB
            | _kw_: break codeblock, Break(), error handling, generic block
   }}*/
/*{{|desc: Returns the generic ot4xb break codeblock, which calls Break() with the value it receives. The
      codeblock is created on first use and cached for the rest of the process.
    | params:
    - `bCopy` BOOL - TRUE returns a new container copy owned by the caller. FALSE returns the shared
      cached container, which must NOT be released.

    Returns ContainerHandle - Container holding the codeblock. }}*/
OT4XB_API ContainerHandle _conGenericBreakCB( BOOL bCopy )
{
   static ContainerHandle con = NULLCONTAINER;
   if( con == NULLCONTAINER ){
      con = _conNewCodeblock( "{|e| Break(e) }" );
   }
   return ( bCopy ? _conNew( con ) : con );
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _congenericbreakcb
            | syntax_: `_congenericbreakcb()`
            | category: container/low-level
            | _kw_: break codeblock, Break(), error handling, generic block
   }}*/
/*{{|desc: Returns the generic OT4XB break codeblock.

    Returns Codeblock - Codeblock equivalent to `{|e| Break(e) }`.

    |note: This is a shared internal helper used when OT4XB needs a simple ErrorBlock-compatible break
      callback. }}*/
_XPP_REG_FUN_( _CONGENERICBREAKCB )
{
   _conReturn( pl, _conGenericBreakCB( 0 ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vdef
            | syntax_: `__vdef( xValue1 [, xValueN] )`
            | category: value
            | _kw_: default value, first non NIL, coalesce, parameters
   }}*/
/*{{|desc: Returns the first parameter that has a real Xbase++ value.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns First non-NIL value found, or NIL if all parameters are NIL or omitted. }}*/
_XPP_REG_FUN_( __VDEF )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & ( XPP_OBJECT | XPP_NUMERIC | XPP_LOGICAL | XPP_DATE | XPP_ARRAY | XPP_CHARACTER | XPP_BLOCK ) )
      {
         ContainerHandle con = _conParam( pl, n, 0 );
         _conReturn( pl, con );
         _conRelease( con );
         return;
      }
   }
   _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vblock
            | syntax_: `__vblock( xValue1 [, xValueN] )`
            | category: value
            | _kw_: first codeblock, variadic, find block
   }}*/
/*{{|desc: Returns the first codeblock found in a variable argument list.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns Codeblock/NIL - First codeblock parameter, or NIL if none is found. }}*/
_XPP_REG_FUN_( __VBLOCK )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & XPP_BLOCK )
      {
         ContainerHandle con = _conParam( pl, n, 0 );
         _conReturn( pl, con );
         _conRelease( con );
         return;
      }
   }
   _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vnum
            | syntax_: `__vnum( xValue1 [, xValueN] )`
            | category: value
            | _kw_: first numeric, variadic, find number
   }}*/
/*{{|desc: Returns the first numeric value found in a variable argument list.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns Numeric/NIL - First numeric parameter, or NIL if none is found. }}*/
_XPP_REG_FUN_( __VNUM )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & XPP_NUMERIC )
      {
         ContainerHandle con = _conParam( pl, n, 0 );
         _conReturn( pl, con );
         _conRelease( con );
         return;
      }
   }
   _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vlower
            | syntax_: `__vlower( xValue1 [, xValueN] )`
            | category: value/string
            | _kw_: first string, lowercase, variadic
   }}*/
/*{{|desc: Returns the first character value found in a variable argument list, converted to lowercase.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns Character/NIL - Lowercase copy of the first character parameter, or NIL if none is found. }}*/
_XPP_REG_FUN_( __VLOWER )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & XPP_CHARACTER )
      {
         DWORD cb = 0;
         LPSTR p = _pszParam_cb( pl, n, &cb );
         if( p )
         {
            CharLowerBuffA( p, cb );
            _retclen( pl, p, cb );
            _xfree( (void *) p );
            return;
         }
      }
   }
   _ret( pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vupper
            | syntax_: `__vupper( xValue1 [, xValueN] )`
            | category: value/string
            | _kw_: first string, uppercase, variadic
   }}*/
/*{{|desc: Returns the first character value found in a variable argument list, converted to uppercase.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns Character/NIL - Uppercase copy of the first character parameter, or NIL if none is found. }}*/
_XPP_REG_FUN_( __VUPPER )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & XPP_CHARACTER )
      {
         DWORD cb = 0;
         LPSTR p = _pszParam_cb( pl, n, &cb );
         if( p )
         {
            CharUpperBuffA( p, cb );
            _retclen( pl, p, cb );
            _xfree( (void *) p );
            return;
         }
      }
   }
   _ret( pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vstr
            | syntax_: `__vstr( xValue1 [, xValueN] )`
            | category: value/string
            | _kw_: first string, variadic, find character
   }}*/
/*{{|desc: Returns the first character value found in a variable argument list.
    | params:
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns Character/NIL - First character parameter, unchanged, or NIL if none is found. }}*/
_XPP_REG_FUN_( __VSTR )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   for( n = 1; n <= np; n++ )
   {
      if( _partype( pl, n ) & XPP_CHARACTER )
      {
         ContainerHandle con = _conParam( pl, n, 0 );
         _conReturn( pl, con );
         _conRelease( con );
         return;
      }
   }
   _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __v2fv
            | syntax_: `__v2fv( xValue, cFieldType, nLength, nDecimals )`
            | category: value
            | _kw_: field value, adjust type, length decimals, database field
   }}*/
/*{{|desc: Converts a value to a field value, adjusted to the requested field type, length, and decimals.
    | params:
    - `xValue` Any - Value to convert.
    - `cFieldType` Character - Field type. Supported values are C, M, L, D, and N.
    - `nLength` Numeric - Field length. Character results are truncated when needed.
    - `nDecimals` Numeric - Decimal count used for numeric field conversion.

    Returns Value converted to fit the requested field definition. Unsupported or incompatible values are
      converted to the corresponding empty field value where possible.

    |note: The function is meant for record/field work: it takes a general Xbase++ value and adapts it so it
      can be stored using the same type and size rules as a field value. }}*/
_XPP_REG_FUN_( __V2FV )
{
   TXppParamList xpp( pl, 4 );
   char   ft = 0;
   DWORD  fcb = ( xpp[3]->CheckType( XPP_NUMERIC ) ? xpp[3]->GetDWord() : 0 );
   DWORD  fdc = ( xpp[4]->CheckType( XPP_NUMERIC ) ? xpp[4]->GetDWord() : 0 );
   DWORD  vt = xpp[1]->GetType();
   DWORD vcb;
   char buffer[64];
   ZeroMemory( buffer, sizeof( buffer ) );
   xpp[0]->Put( xpp[1]->con() ); // same value by default
   xpp[2]->GetCL( &ft, 1 );
   switch( ft )
   {
      case 'M':
      {
         fcb = 0;
      }// continue to case 'C'
      case 'C':
      {
         switch( vt & 0xFF )
         {
            case XPP_CHARACTER:
            {
               vcb = xpp[1]->con_size();
               if( fcb && ( vcb > fcb ) )
               {
                  xpp[0]->resize( fcb );
               }
               return;
            }
            case XPP_NUMERIC:
            {
               vcb = 0;
               if( vt & _xpp_DOUBLE )
               {
                  vcb = sprintf_s( buffer, sizeof( buffer ), "%.16g", xpp[1]->GetDouble() );
               }
               else
               {
                  vcb = sprintf_s( buffer, sizeof( buffer ), "%i", xpp[1]->GetLong() );
               }
               if( fcb && ( vcb > fcb ) )
               {
                  vcb = fcb;
               }
               xpp[0]->PutStrLen( buffer, vcb );
               return;
            }
            case XPP_LOGICAL:
            {
               xpp[0]->PutStrLen( ( xpp[1]->GetBool() ? "Y" : "N" ), 1 );
               return;
            }
            case XPP_DATE:
            {
               xpp[1]->GetDateString( buffer );
               if( buffer[0] == 32 )
               {
                  xpp[0]->PutStr( "" );
               }
               else
               {
                  if( fcb && ( 8 > fcb ) )
                  {
                     if( fcb == 6 )
                     {
                        xpp[0]->PutStrLen( _mk_ptr_( LPSTR, buffer, 2 ), 6 ); // no century
                     }
                     else
                     {
                        xpp[0]->PutStr( "" );
                     }
                  }
                  else
                  {
                     xpp[0]->PutStrLen( buffer, 8 );
                  }
               }
               return;
            }
            default:
            {
               xpp[0]->PutStr( "" );
               break;
            }
         }
         return;
      }
      case 'L':
      {
         switch( vt & 0xFF )
         {
            case XPP_CHARACTER:
            {

               vcb = xpp[1]->GetCL( buffer, sizeof( buffer ) - 1 );
               if( vcb )
               {
                  switch( buffer[0] )
                  {
                     case 'y': case 'Y': case '1': case 'S': case 's': case 't': case 'T':
                     {
                        xpp[0]->PutBool( TRUE );
                        return;
                     }
                     default:
                     {
                        break;
                     }
                  }
               }
               xpp[0]->PutBool( FALSE );
               return;
            }
            case XPP_NUMERIC:
            {
               xpp[0]->PutBool( ( xpp[1]->GetLong() ? 1 : 0 ) );
               return;
            }
            case XPP_LOGICAL:
            {
               return;
            }
            case XPP_DATE:
            default:
            {
               xpp[0]->PutBool( 0 );
               break;
            }
         }
         return;
      }
      case 'D':
      {
         switch( vt & 0xFF )
         {
            case XPP_CHARACTER:
            {
               vcb = xpp[1]->GetCL( buffer, sizeof( buffer ) - 1 );
               xpp[0]->PutDateString( buffer );
               return;
            }
            case XPP_NUMERIC:
            {
               xpp[0]->PutJulianDate( xpp[1]->GetDWord() );
               return;
            }
            case XPP_DATE:
            {
               return;
            }
            case XPP_LOGICAL:
            default:
            {
               xpp[0]->PutDateString( "" );
               break;
            }
         }
         return;
      }
      case 'N':
      {
         switch( vt & 0xFF )
         {
            case XPP_CHARACTER:
            {
               vcb = xpp[1]->GetCL( buffer, sizeof( buffer ) - 1 );
               if( vcb )
               {
                  // fcb fdc 
                  if( fdc || bStrWildCmpI( "*.*", buffer ) )
                  {
                     xpp[0]->PutDoubleFormat( atof( buffer ), fcb, fdc );
                  }
                  else
                  {
                     __int64 q = _atoi64( buffer );
                     if( ( q & 0xFFFFFFFF ) == q )
                     {
                        xpp[0]->PutLong( (LONG) ( q & 0xFFFFFFFF ) );
                     }
                     else
                     {
                        xpp[0]->PutDoubleFormat( atof( buffer ), fcb, 0 );
                     }
                  }
               }
               else
               {
                  xpp[0]->PutLong( 0 );
               }
               return;
            }
            case XPP_NUMERIC:
            {
               return;
            }
            case XPP_LOGICAL:
            {
               xpp[0]->PutLong( ( xpp[1]->GetBool() ? 1 : 0 ) );
               return;
            }
            case XPP_DATE:
            {
               xpp[0]->PutLong( xpp[1]->GetJulianDate() );
               return;
            }
            default:
            {
               xpp[0]->PutLong( 0 );
               return;
            }
         }
         return;
      }
   }

}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vmask
            | syntax_: `__vmask( nTypeMask, xValue1 [, xValueN] )`
            | category: value
            | _kw_: first matching type, type mask, variadic
   }}*/
/*{{|desc: Returns the first parameter whose Xbase++ type matches a type mask.
    | params:
    - `nTypeMask` Numeric - Xbase++ type mask, using the type constants from types.ch. Combine several type
      flags with bitwise OR, for example with nOr( XPP_CHARACTER, XPP_NUMERIC ). Add 0x10000000 to require the
      selected value to be non-empty.
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right after nTypeMask.

    Returns First matching value, or NIL if no value matches the mask.

    |note: If the non-empty flag 0x10000000 is used with no explicit type bits, all ordinary Xbase++ value
      types are accepted, but empty values are skipped. }}*/
_XPP_REG_FUN_( __VMASK )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   ULONG nMask = (ULONG) _parLong( pl, 1, 0 );
   ULONG bNotEmpty = ( nMask & 0x10000000 );

   if( bNotEmpty )
   {
      nMask = ( nMask & ( ~0x10000000 ) );
      if( nMask == 0 )
      {
         nMask = 0xFFFF;
      }
   }

   for( n = 2; n <= np; n++ )
   {
      if( _partype( pl, n ) & nMask )
      {
         ContainerHandle con = _conParam( pl, n, 0 );
         if( bNotEmpty )
         {
            BOOL bEmpty = 0;
            _conIsEmpty( con, &bEmpty );
            if( bEmpty )
            {
               _conRelease( con );
               con = 0;
            }
         }
         if( con )
         {
            _conReturn( pl, con );
            _conRelease( con );
            return;
         }
      }
   }
   _ret( pl );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __xb_type
            | syntax_: `__xb_type( xValue )`
            | category: container/type
            | _kw_: internal type, XPP type, type mask, valtype
   }}*/
/*{{|desc: Returns the Xbase++ internal type of a value, or checks that type against a mask.
    | params:
    - `xValue` Any - Value whose internal Xbase++ type is inspected.
    - `nMask` Numeric - Type mask built from the Xbase++ type constants in types.ch.

    Returns Numeric/Logical - With one parameter, returns the numeric internal type of xValue. With two
      parameters, returns .T. when the type of xValue has any bit in common with nMask; otherwise .F.

    |note: Also __xb_type( xValue, nMask ) -> lMatch

    |note: The two-parameter form performs a bitwise AND check: __xb_type( xValue, nMask ) is true when nAnd(
      __xb_type( xValue ), nMask ) is not zero. }}*/
_XPP_REG_FUN_( __XB_TYPE )
{
   ULONG np = _partype( pl, 0 );
   ULONG nType = (ULONG) _partype( pl, 1 );
   ULONG nMask = (ULONG) _parLong( pl, 2, 0 );

   if( np == 1 )
   {
      _retnl( pl, (LONG) nType );
      return;
   }

   if( np == 2 )
   {
      _retl( pl, ( ( nType & nMask ) ? 1 : 0 ) );
      return;
   }
   _retl( pl, 0 );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vclsptr
            | syntax_: `__vclsptr( cClassName, xValue1 [, xValueN] )`
            | category: value
            | _kw_: pointer argument, first pointer, class filter, variadic
   }}*/
/*{{|desc: Returns the first value that can be used as a pointer argument, optionally filtering object values
      by class name.
    | params:
    - `cClassName` Character - Optional class-name mask. When the first parameter is a character string,
      object values are accepted only when ::ClassName() matches this mask. Matching uses case-insensitive
      WildCmp semantics, so '*' and '?' can be used as wildcards in the class name.
    - `xValue1...xValueN` Any - Variable argument list scanned from left to right.

    Returns First numeric pointer value, first object matching the optional class mask, or 0 if no suitable
      value is found.

    |note: Also __vclsptr( xValue1 [, xValueN] ) -> `xValue | 0`

    |note: Numeric values are assumed to already be pointers and are returned directly. Object values are
      accepted so OT4XB can use its normal pointer-object mechanism: the object is expected to provide
      _lock_/_unlock_ behavior so the pointer can be obtained for the duration of the call and released
      afterwards. The optional class-name parameter is only a filter to make sure the selected object is of the
      expected class; without it, the first object or numeric value is considered valid. If a numeric value is
      passed, __vclsptr() does not validate that it is a real pointer; passing an invalid pointer value will
      fail later when that pointer is used. }}*/
_XPP_REG_FUN_( __VCLSPTR )
{
   ULONG np = _partype( pl, 0 );
   ULONG n = 1;
   char sz[256]; ZeroMemory( sz, sizeof( sz ) );
   if( _partype( pl, 1 ) & XPP_CHARACTER )
   {
      _parc( sz, sizeof( sz ) - 1, pl, 1, 0 );
      n++;
   }
   for( ; n <= np; n++ )
   {
      ULONG nType = _partype( pl, n );
      if( nType & XPP_NUMERIC )
      {
         LONG  nValue = _parLong( pl, n, 0 );
         _retnl( pl, nValue );
         return;
      }
      else if( _partype( pl, n ) & XPP_OBJECT )
      {
         ContainerHandle cono = _conParam( pl, n, 0 );
         BOOL bOk = TRUE;
         if( sz[0] )
         {
            LPSTR pClsName = _conMCallLpstr( cono, "ClassName" );
            bOk = FALSE;
            if( pClsName )
            {
               bOk = bStrWildCmpI( sz, pClsName );
               _xfree( pClsName );
               pClsName = 0;
            }
         }
         if( bOk )
         {
            _conReturn( pl, cono );
            _conRelease( cono );
            return;
         }
         _conRelease( cono );
      }
   }
   _retnl( pl, 0 );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __anew
            | syntax_: `__anew( xValue1 [, xValueN] )`
            | category: container/array
            | _kw_: new array, from parameters, array literal
   }}*/
/*{{|desc: Creates a new array initialized with the values passed as parameters.
    | params:
    - `xValue1...xValueN` Any - Values copied into the returned array, in parameter order.

    Returns Array - A newly created array containing the supplied values.

    |note: __anew( 1, 2, 3 ) is equivalent in intent to { 1, 2, 3 }. The Xbase++ array literal should also
      create a new array every time it is evaluated. This helper was useful with old Xbase++ versions where
      array literals such as local aa := {1,2,3,4} could, in rare situations, unexpectedly share an array
      instance. The exact trigger was hard to reproduce. Newer Xbase++ versions are not expected to show that
      behavior, but __anew() is still harmless and is often used out of habit or as a defensive way to force a
      fresh array allocation on every call. }}*/
_XPP_REG_FUN_( __ANEW )
{
   ULONG np = _partype( pl, 0 );
   ULONG n;
   ContainerHandle cona = _conNewArray( 1, np, 0 );
   for( n = 1; n <= np; n++ )
   {
      ContainerHandle con = _conParam( pl, n, 0 );
      _conArrayPut( cona, con, n, 0 );
      _conRelease( con );
   }
   _conReturn( pl, cona );
   _conRelease( cona );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __apeek
            | syntax_: `__apeek( aArray, nIndex1 [, nIndexN] )`
            | category: container/array
            | _kw_: array peek, safe index, nested array, no error
   }}*/
/*{{|desc: Tries to read a value from an array using one or more indexes.
    | params:
    - `aArray` Array - Array to inspect.
    - `nIndex1...nIndexN` Numeric - One or more 1-based indexes. Multiple indexes are used to navigate
      nested or multidimensional arrays.

    Returns Any/NIL - The value found at the requested path, or NIL if the supplied value is not an array, an
      intermediate value is not an array, or any requested index is outside the available dimensions.

    |note: __apeek() is intended for defensive inspection of arrays whose shape may vary, such as parsed data
      or optional nested structures. It returns NIL instead of failing when the requested path does not exist.
      It is similar in purpose to __vpeek(), but is limited to arrays and numeric indexes. }}*/
_XPP_REG_FUN_( __APEEK )
{
   ULONG np = _partype( pl, 0 );
   ContainerHandle con = _conNew( NULLCONTAINER );

   if( _partype( pl, 1 ) & XPP_ARRAY )
   {
      ContainerHandle cona = _conParam( pl, 1, 0 );
      int * list = (int *) _xgrab( ( np * sizeof( int ) ) + 16 );
      ULONG n;
      for( n = 2; n <= np; n++ )
      {
         list[n - 2] = _parnl( pl, n, 0 );
      }
      _conArrayGetA( cona, con, list );
      _conRelease( cona );
      _xfree( (void *) list );
   }
   _conReturn( pl, con );
   _conRelease( con );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static BOOL __vpeek_from_array( ContainerHandle con, DWORD & cb, LPSTR & p )
{
   DWORD ccbb = 0;
   if( !_conCheckType( con, XPP_ARRAY ) )
   {
      return FALSE;
   }
   char buffer[128]; ZeroMemory( buffer, sizeof( buffer ) );
   for( p++, cb--; cb && *p && ( ( *p == 0x20 ) || ( *p == '\t' ) ); cb--, p++ ); // skip white spaces
   for( ; cb && ( *p >= '0' ) && ( *p <= '9' ); cb--, p++ )
   {
      buffer[ccbb] = *p;
      ccbb++; if( ccbb > 32 ){
         return FALSE;
      }
   }
   for( ; cb && *p && ( ( *p == 0x20 ) || ( *p == '\t' ) ); cb--, p++ ); // skip white spaces
   if( !( cb && ccbb && ( ( *p == ']' ) || ( *p == ',' ) ) ) )
   {
      return FALSE;
   }
   if( *p == ',' )
   {
      *p = '[';
   }
   else
   {
      p++;
      cb--;
   }
   buffer[ccbb] = 0;
   ULONG index = (DWORD) atol( buffer );
   if( index < 1 )
   {
      return FALSE;
   }
   if( _conGetArrayLen( con ) < index )
   {
      return FALSE;
   }
   ContainerHandle con_tmp = _conNew( NULLCONTAINER );
   BOOL bOk = (BOOL) ( _conArrayGet( con, con_tmp, index, 0 ) ? 1 : 0 );
   if( bOk )
   {
      _conPut( con, con_tmp );
   }
   _conRelease( con_tmp ); con_tmp = 0;
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
#define is_valid_ch_for_method(ch) ((( ch >= '0') && ( ch <= '9'))||(( ch >= 'a') && ( ch <= 'z'))||(( ch >= 'A') && ( ch <= 'Z'))||( ch == '_'))
// -----------------------------------------------------------------------------------------------------------------
static BOOL __vpeek_from_object( ContainerHandle con, DWORD & cb, LPSTR & p )
{
   DWORD ccbb = 0;
   if( !_conCheckType( con, XPP_OBJECT ) )
   {
      return FALSE;
   }
   char buffer[260]; ZeroMemory( buffer, sizeof( buffer ) );
   for( p++, cb--; cb && *p && ( ( *p == 0x20 ) || ( *p == '\t' ) ); cb--, p++ ); // skip white spaces
   for( ; cb && is_valid_ch_for_method( *p ); cb--, p++ )
   {
      buffer[ccbb] = *p;
      ccbb++;
      if( ccbb > 254 ){
         return FALSE;
      }
   }
   if( ( *buffer >= '0' ) && ( *buffer <= '9' ) )
   {
      return FALSE;
   }
   for( ; cb && *p && ( ( *p == 0x20 ) || ( *p == '\t' ) ); cb--, p++ ); // skip white spaces
   if( cb )
   {
      if( !( ( *p == ':' ) || ( *p == '[' ) ) )
      {
         return FALSE;
      }
   }
   if( !ccbb )
   {
      return FALSE;
   }
   buffer[ccbb] = 0;
   ContainerHandle con_tmp = _conNew( NULLCONTAINER );
   BOOL bOk = (BOOL) ( ( _conGetMember( con, buffer, con_tmp ) == 0 ) ? 1 : 0 );
   if( bOk )
   {
      _conPut( con, con_tmp );
   }
   _conRelease( con_tmp ); con_tmp = 0;
   return bOk;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __vpeek
            | syntax_: `__vpeek( xValue, cExpression [, xDefault] )`
            | category: value
            | _kw_: peek value, nested, array object path, safe access
   }}*/
/*{{|desc: Safely peeks/extracts a nested value from an array, object, or a combination of both.
    | params:
    - `xValue` Any - Root value to inspect, usually an array, object, or value parsed from structured data.
    - `cExpression` Character - Access expression. Use [n] to select an array element and :name to read an
      object member. Steps can be chained, for example "[1]:customer:name".
    - `xDefault` Any - Optional value returned when any step cannot be resolved.

    Returns Extracted value, xDefault when supplied and extraction fails, or NIL when extraction fails without
      a default.

    |note: This is useful when inspecting complex values whose shape is not guaranteed, such as parsed JSON. It
      allows probing deep values without first checking every intermediate array element or object member.

    |example: // Get a nested value from a parsed JSON-like structure. cName := __vpeek( xJson,
      ":data[1]:customer:name", "" ) }}*/
_XPP_REG_FUN_( __VPEEK )
{
   DWORD np = (DWORD) _partype( pl, 0 );
   ContainerHandle conr = _conNew( NULLCONTAINER );
   LPSTR pExpression = 0;
   BOOL bOk = TRUE;

   if( np )
   {
      BOOL bByRef = FALSE;
      ContainerHandle con_tmp = _conParam( pl, 1, &bByRef );
      _conPut( conr, con_tmp );
      if( con_tmp && ( !bByRef ) )
      {
         _conRelease( con_tmp );
      }
      con_tmp = 0;
   }
   DWORD cb = 0;
   pExpression = _pszParam_cb( pl, 2, &cb );
   if( pExpression )
   {
      LPSTR p = pExpression;
      while( bOk && cb )
      {
         for( ; cb && *p && ( ( *p == 0x20 ) || ( *p == '\t' ) ); cb--, p++ ); // skip white spaces
         switch( *p )
         {
            case '[':
            {
               bOk = __vpeek_from_array( conr, cb, p );
               break;
            }
            case ':':
            {
               bOk = __vpeek_from_object( conr, cb, p );
               break;
            }
            default:
            {
               bOk = ( cb ? 0 : 1 ); // only ok if empty
               break;
            }
         }
      }
      _xfree( pExpression ); pExpression = 0;
   }
   if( !bOk )
   {
      _conPut( conr, NULLCONTAINER );
      if( np > 2 )
      {
         BOOL bByRef = FALSE;
         ContainerHandle con_tmp = _conParam( pl, 3, &bByRef );
         _conPut( conr, con_tmp );
         if( con_tmp && ( !bByRef ) )
         {
            _conRelease( con_tmp );
         }
         con_tmp = 0;
      }

   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// flags: 1 loop
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __anext
            | syntax_: `__anext( aArray, @nIndex [, nFlags] )`
            | category: value/array
            | _kw_: array iterator, next element, index by reference
   }}*/
/*{{|desc: Returns the next element of an array and advances an index passed by reference.
    | params:
    - `aArray` Array - Array to iterate.
    - `nIndex` Numeric by reference - Current position. Values lower than 1 are treated as 0 before
      advancing. The parameter is updated with the position that was attempted or returned.
    - `nFlags` Numeric - Optional bit mask. Combine flags with bitwise OR, for example with nOr( flag1,
      ..., flagX ). 0x0001 - loop back to the first element after the end of the array.

    Returns Next array element, or NIL when there is no next element or the first parameter is not an array.

    |note: Without 0x0001, the array is traversed once and the function returns NIL after the last element.
      This is useful for round-robin iteration over a fixed array of resources, such as a list of mailboxes to
      check: each call returns the next item, and with 0x0001 the sequence starts again from the first item
      after the last. }}*/
_XPP_REG_FUN_( __ANEXT )
{
   DWORD flags = (DWORD) _parLong( pl, 3, 0 );
   ContainerHandle conr = _conNew( NULLCONTAINER );

   if( _partype( pl, 1 ) & XPP_ARRAY )
   {
      BOOL bByRef = FALSE;
      ContainerHandle cona = _conParam( pl, 1, &bByRef );
      LONG nn = _conGetArrayLen( cona );
      LONG n = _parnl( pl, 2, 0 );
      if( n < 1 ){
         n = 0;
      }
      n++;
      if( ( n > nn ) && ( flags & 1 ) )
      {
         n = 1;
      }
      if( ( n > 0 ) && ( n <= nn ) )
      {
         _conArrayGet( cona, conr, n, 0 );
      }
      if( !bByRef )
      {
         _conRelease( cona );
      }
      _stornl( n, pl, 2, 0 );
   }
   _conReturn( pl, conr );
   _conRelease( conr );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
static LPSTR __xml_fv__get_value( ContainerHandle  con_value )
{
   if( !con_value )
   {
      return 0;
   }

   DWORD dwType = 0;
   _conType( con_value, &dwType );
   switch( dwType & 0xFF )
   {
      case XPP_CHARACTER:
      {
         DWORD cb = 0;
         _conSizeC( con_value, &cb );
         LPSTR p = (LPSTR) _xgrab( cb + 4 );
         if( cb )
         {
            _conGetCL( con_value, &cb, p, cb + 1 );
         }
         return p;
      }
      case XPP_DATE:
      {
         char sz[16]; ZeroMemory( sz, sizeof( sz ) );
         _conGetDS( con_value, sz );
         if( ( sz[0] >= '0' ) && ( sz[0] <= '9' ) )
         {
            LPSTR p = (LPSTR) _xgrab( 16 );
            p[0] = sz[0]; p[1] = sz[1]; p[2] = sz[2]; p[3] = sz[3]; p[4] = '-'; p[5] = sz[4]; p[6] = sz[5]; p[7] = '-'; p[8] = sz[6]; p[9] = sz[7];
            return p;
         }
         return 0;
      }
      case XPP_NUMERIC:
      {
         LPSTR p = (LPSTR) _xgrab( 64 );
         if( dwType & _xpp_DOUBLE )
         {
            double nd = 0.0;
            _conGetND( con_value, &nd );
            sprintf( p, "%.15g", nd );
         }
         else
         {
            LONG nl = 0;
            _conGetNL( con_value, &nl );
            sprintf( p, "%i", nl );
         }
         return p;
      }
      case XPP_LOGICAL:
      {
         LPSTR p = (LPSTR) _xgrab( 64 );
         BOOL  b = 0;
         _conGetL( con_value, &b );
         if( b )
         {
            sprintf( p, "%s", "true" );
         }
         else
         {
            sprintf( p, "%s", "false" );
         }
         return p;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __xml_fv_get_value
            | syntax_: `__xml_fv_get_value( xValue )`
            | category: value/xml
            | _kw_: xml value, format value, text representation
   }}*/
/*{{|desc: Formats a Xbase++ value as the text representation used by __xml_fv().
    | params:
    - `xValue` Character/Date/Numeric/Logical - Value to format for XML value output.

    Returns Character - Character values are returned as-is, dates are formatted as yyyy-mm-dd, numeric values
      are formatted as text, and logical values are returned as true or false. Unsupported values return an
      empty string.

    |note: This function only formats the value text. It does not XML-escape the result and does not add XML
      element tags or attributes. }}*/
_XPP_REG_FUN_( __XML_FV_GET_VALUE )
{
   TXppParamList xpp( pl, 1 );
   {
      LPSTR p = __xml_fv__get_value( xpp[1]->con() );

      if( p )
      {
         xpp[0]->PutStr( p );
         _xfree( p );
      }
      else
      {
         xpp[0]->PutStr( "" );
      }

   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
static void __xml_fv__add_atributes( TZString & z, TXbCPItem & x )
{
   if( x.CheckType( XPP_CHARACTER ) )
   {
      z.AddChar( 0x20 );
      z.Add( x.str() );
      z.AddChar( 0x20 );
      return;
   }
   if( x.CheckType( XPP_ARRAY ) )
   {
      ContainerHandle cona = x.con();
      DWORD nCount = x.con_size();
      DWORD n;
      for( n = 1; n <= nCount; n++ )
      {
         ContainerHandle con_key = _conNew( NULLCONTAINER );
         ContainerHandle con_value = _conNew( NULLCONTAINER );
         _conArrayGet( cona, con_key, n, 1, 0 );
         _conArrayGet( cona, con_value, n, 2, 0 );
         DWORD cbKey = 0;
         LPSTR pKey = 0;
         if( _conRLockC( con_key, &pKey, &cbKey ) == 0 )
         {
            z.AddChar( 0x20 );
            z.printf( "%s=", pKey );
            LPSTR pValue = __xml_fv__get_value( con_value );
            z += "\"";
            if( pValue )
            {
               z.Add_to_xml( pValue );
               _xfree( (void *) pValue );
            }
            z += "\"";
            _conUnlockC( con_key ); pKey = 0;
           
         }
         _conReleaseM( con_key, con_value, 0 );
         z += " ";
      }
      return;
   }
}

// -----------------------------------------------------------------------------------------------------------------
// flags = // 0x100 no scientific, 1 LTrim , 2 Rtrim , 0x200 do not convert 1252-to-utf8 
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __v2_csv_cell
            | syntax_: `__v2_csv_cell( xValue [, nFlags] [, nDecimals] )`
            | category: value/csv
            | _kw_: csv cell, value to csv, quote, separator
   }}*/
/*{{|desc: Converts a Xbase++ value to one CSV cell.
    | params:
    - `xValue` Character/Date/Numeric/Logical - Value to format as a CSV cell.
    - `nFlags` Numeric - Optional bit mask. Combine flags with bitwise OR, for example with nOr( flag1,
      ..., flagX ). 0x0001 - left-trim spaces while building the cell. 0x0002 - right-trim spaces after building
      the cell. 0x0008 - prefix numeric-looking cells with an apostrophe. 0x0100 - quote numeric-looking cells
      to avoid scientific-notation interpretation by CSV consumers. 0x0200 - do not convert CP1252 characters to
      UTF-8. 0x0400 - convert CR, LF, and TAB to spaces. 0x0800 - convert double quotes to single quotes. 0x4000
      - limit input length to 400 characters. 0x8000 - limit input length to 800 characters. 0xC000 - limit
      input length to 1200 characters.
    - `nDecimals` Numeric - Optional decimal count for numeric values. When omitted, doubles use a compact
      representation and integer values are formatted without decimals.

    Returns Character - CSV cell text, quoted and escaped when needed.

    |note: Character and date values are passed through the CSV-cell formatter. Dates are written as
      yyyy-mm-dd, or ten spaces for an empty date. Logical values are written as 1 or 0. Embedded double quotes
      are escaped by doubling them unless the quote-to-single-quote flag is used. }}*/
_XPP_REG_FUN_( __V2_CSV_CELL )
{
   TXppParamList xpp( pl, 3 );
   TZString z;
   DWORD flags = xpp[2]->GetDWord();
   BYTE table[256]; _bset( table, 0, 32 ); _bset( table + 32, 1, 256 - 32 ); table[34] = 0;

   xpp[0]->PutStr( "" );
   switch( xpp[1]->GetType() & 0xFF )
   {

      case XPP_CHARACTER:
      {
         DWORD cb = 0;
         LPSTR p = xpp[1]->LockStr( &cb );
         z.str_1252_to_svc_utf8_cell( p, cb , flags);
         xpp[1]->UnlockStr();
         break;
      }
      case XPP_DATE:
      {
         char ds[32]; ZeroMemory( ds, sizeof( ds ) );
         _conGetDS( (ContainerHandle) xpp[1], ds );

         if( ds[0] < '0' )
         {
            _bset( (LPBYTE) ds, 32, 10 ); // empty yyyy-mm-dd
         }
         else
         {
            // yyyymmdd to  yyyy-mm-dd
            ds[9] = ds[7]; ds[8] = ds[6]; ds[7] = '-'; ds[6] = ds[5]; ds[5] = ds[4]; ds[4] = '-';
         }
         z.str_1252_to_svc_utf8_cell( ds, 10, flags );
         break;
      }
      case XPP_NUMERIC:
      {
         char s[256]; ZeroMemory( s, sizeof( s ) );
         DWORD dec = ( xpp[3]->CheckType( XPP_NUMERIC ) ? xpp[3]->GetDWord() & 0x0F : 0xFF );
         DWORD pos = 0;
         if( dec == 0 )
         {
            pos = (DWORD) _snprintf_c( s, sizeof( s ), "%u", xpp[1]->GetDWord() );
         }
         else
         {
            if( xpp[1]->CheckType( _xpp_DOUBLE ) )
            {
               if( dec > 0x0F )
               {
                  pos = (DWORD) _snprintf_c( s, sizeof( s ), "%.15g", xpp[1]->GetDouble() );
               }
               else
               {
                  char format[64];
                  _snprintf_c( format, sizeof( format ), "%%.%if", dec );
                  pos = (DWORD) _snprintf_c( s, sizeof( s ), format, xpp[1]->GetDouble() );
               }
            }
            else
            {
               pos = (DWORD) _snprintf_c( s, sizeof( s ), "%u", xpp[1]->GetDWord() );
               if( dec > 0 && dec <= 0x0F && pos < ( sizeof( s ) - 16 ) )
               {
                  s[pos++] = '.';
                  for( ; dec && pos < (sizeof(s)-2) ; dec-- )
                  {
                     s[pos++] = '0';
                  }
                  s[pos] = 0;
               }
            }
         }
         z.str_1252_to_svc_utf8_cell( s,pos, flags);
         break;
      }
      case XPP_LOGICAL:
      {
         z.AddChar( xpp[1]->GetBool() ? '1' : '0' );
         break;
      }

   }
   xpp[0]->PutStrLen( z.GetBuffer(), z.len() );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// flags:
// 2 - RTRIM
// 0x10000 -  naked value
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __xml_fv
            | syntax_: `__xml_fv( cName, xValue [, xAttributes] [, nCodePageTo] [, nCodePageFrom] [, nFlags] )`
            | category: value/xml
            | _kw_: xml fragment, element, attributes, format value
   }}*/
/*{{|desc: Formats a Xbase++ value as an XML value fragment, using an element name and optional attributes.
    | params:
    - `cName` Character - XML element name.
    - `xValue` Character/Date/Numeric/Logical - Value to serialize. Characters are used as text, dates are
      formatted as yyyy-mm-dd, numerics are formatted as text, and logical values are written as true or false.
    - `xAttributes` Character/Array - Optional attributes. Normally an array of { cName, xValue } pairs;
      each value is XML-escaped. A character value is also accepted and is inserted as raw attribute text.
    - `nCodePageTo` Numeric - Destination Windows code page. Defaults to CP_UTF8.
    - `nCodePageFrom` Numeric - Source Windows code page used for the generated text before conversion.
      Defaults to CP_ACP.
    - `nFlags` Numeric - Optional bit mask. Combine flags with bitwise OR, for example with nOr( flag1,
      ..., flagX ). 0x0002 - right-trim the escaped value text. 0x10000 - naked value: return only the
      XML-escaped value text, without opening or closing element tags.

    Returns Character - XML fragment. Unsupported values generate a self-closing element unless the
      naked-value flag is used.

    |note: Attribute names are not escaped. When xAttributes is a raw character string it is inserted as
      supplied, so the caller is responsible for making it valid XML attribute text. The self-closing form is
      not controlled by a flag; it is used automatically when xValue cannot be converted to XML text. }}*/
_XPP_REG_FUN_( __XML_FV )
{
   TXppParamList xpp( pl, 6 );
   TZString z;

   if( xpp[1]->LockStr() )
   {
      UINT cp_to = ( xpp[4]->CheckType( XPP_NUMERIC ) ? xpp[4]->GetDWord() : CP_UTF8 );
      UINT cp_from = ( xpp[5]->CheckType( XPP_NUMERIC ) ? xpp[5]->GetDWord() : CP_ACP );
      DWORD flags = xpp[6]->GetDWord();

      if( !( flags & 0x10000 ) )
      {
         z += "<";
         z += xpp[1]->str();
         __xml_fv__add_atributes( z, *xpp[3] );
      }
      LPSTR value = __xml_fv__get_value( xpp[2]->con() );
      if( value )
      {
         if( !( flags & 0x10000 ) )
         {
            z += ">";
         }
         z.Add_to_xml( value );
         if( flags & 2 )
         {
            z.RTrim();
         }
         if( !( flags & 0x10000 ) )
         {
            z += "</";
            z += xpp[1]->str();
            z += ">";
         }
         _xfree( (void *) value ); value = 0;
      }
      else
      {
         if( !( flags & 0x10000 ) )
         {
            z += " />";
         }
      }

      DWORD cb = 0;
      LPSTR p = z.Detach_mb2mb( cp_from, cp_to, &cb, 0, 0 );
      if( p )
      {
         xpp[0]->PutStrLen( p, cb );
         _xfree( (void *) p );
         p = 0;
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
static DWORD _watching_thread_ = 0;
static LONG  _watching_thread_count = 0;
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: begin_watch_thread_conc
            | syntax_: `BOOL begin_watch_thread_conc( void )`
            | category: container
            | _kw_: lock watch, container locks, debug, balance, thread
   }}*/
/*{{|desc: Starts counting the balance of container C locks and unlocks made from the calling thread. Only
      one watch can be active at a time. Debug builds of ot4xb only.

    Returns BOOL - TRUE when the watch started, FALSE when a watch is already active.

    }}*/
extern "C" OT4XB_API BOOL __cdecl begin_watch_thread_conc( void )
{
   if( _watching_thread_ )
   {
      return FALSE;
   }
   _watching_thread_ = GetCurrentThreadId();
   _watching_thread_count = 0;
   return TRUE;
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: end_watch_thread_conc
            | syntax_: `LONG end_watch_thread_conc( void )`
            | category: container
            | _kw_: lock watch, container locks, debug, final balance
   }}*/
/*{{|desc: Stops the container C lock watch and returns the final balance. Debug builds of ot4xb only.

    Returns LONG - Final lock balance, or -1 when the calling thread is not the watching thread.

    }}*/
extern "C" OT4XB_API LONG  __cdecl end_watch_thread_conc( void )
{
   DWORD n = (DWORD) -1;
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      n = (LONG) _watching_thread_count;
      _watching_thread_count = 0;
      _watching_thread_ = 0;
   }
   return n;
}
/*{{end-debug-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: count_watch_thread_conc
            | syntax_: `LONG count_watch_thread_conc( void )`
            | category: container
            | _kw_: lock watch, container locks, debug, balance
   }}*/
/*{{|desc: Returns the current balance of the container C lock watch. Debug builds of ot4xb only.

    Returns LONG - Current lock balance, or -1 when the calling thread is not the watching thread.

    }}*/
extern "C" OT4XB_API LONG  __cdecl count_watch_thread_conc( void )
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      return _watching_thread_count;
   }
   return (DWORD) -1;
}
/*{{end-debug-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-debug-c-function}}*/
/*{{debug-c-function_: on_watch_thread_conc
            | syntax_: `void on_watch_thread_conc( LONG n )`
            | category: container
            | _kw_: lock watch, container locks, debug, counter
   }}*/
/*{{|desc: Adds an amount to the container C lock watch balance when called from the watching thread. The
      ot4xb lock wrappers call it with 1 on each successful lock and -1 on each unlock. Debug builds of ot4xb
      only.
    | params:
    - `n` LONG - Amount to add to the balance.

    Returns void

    }}*/
extern "C" OT4XB_API void  __cdecl on_watch_thread_conc( LONG n )
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      _watching_thread_count += n;
   }
}
/*{{end-debug-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
#endif
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_conRLockC
            | syntax_: `ULONG ot4xb_conRLockC( ContainerHandle con, LPSTR * pp, ULONG * pcb )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_conRLockC
            | _kw_: lock string, read lock, container bytes, _conRLockC
   }}*/
/*{{|desc: Locks the character content of a container for read access and returns a pointer to its bytes. In
      debug builds the lock is counted by the watch thread instrumentation. Unlock with ot4xb_conUnlockC().
    | params:
    - `con` ContainerHandle - Container holding a character value.
    - `pp` LPSTR * - Receives the pointer to the string bytes.
    - `pcb` ULONG * - Receives the string length in bytes.

    Returns ULONG - 0 when the lock was obtained, non 0 on error. }}*/
OT4XB_API ULONG ot4xb_conRLockC( ContainerHandle con, LPSTR * pp, ULONG * pcb )
{
   ULONG result = _conRLockC( con, pp, pcb );
#ifdef _DEBUG
   if( result == 0 )
   {
      on_watch_thread_conc( 1 );
   }
#endif
   return result;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_conWLockC
            | syntax_: `ULONG ot4xb_conWLockC( ContainerHandle con, LPSTR * pp, ULONG * pcb )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_conWLockC
            | _kw_: lock string, write lock, modify in place, _conWLockC
   }}*/
/*{{|desc: Locks the character content of a container for write access, so the string bytes can be modified
      in place. In debug builds the lock is counted by the watch thread instrumentation. Unlock with
      ot4xb_conUnlockC().
    | params:
    - `con` ContainerHandle - Container holding a character value.
    - `pp` LPSTR * - Receives the pointer to the string bytes.
    - `pcb` ULONG * - Receives the string length in bytes.

    Returns ULONG - 0 when the lock was obtained, non 0 on error. }}*/
OT4XB_API ULONG ot4xb_conWLockC( ContainerHandle con, LPSTR * pp, ULONG * pcb )
{
   ULONG result = _conWLockC( con, pp, pcb );
#ifdef _DEBUG
   if( result == 0 )
   {
      on_watch_thread_conc( 1 );
   }
#endif
   return result;
}
/*{{end-c-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_conUnlockC
            | syntax_: `ULONG ot4xb_conUnlockC( ContainerHandle con )`
            | category: container
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_conUnlockC
            | _kw_: unlock string, release lock, _conUnlockC
   }}*/
/*{{|desc: Releases a character content lock previously obtained with ot4xb_conRLockC() or ot4xb_conWLockC().
      In debug builds the unlock is counted by the watch thread instrumentation.
    | params:
    - `con` ContainerHandle - Container whose lock is released.

    Returns ULONG - 0 when the lock was released, non 0 on error. }}*/
OT4XB_API ULONG ot4xb_conUnlockC( ContainerHandle con )
{
   ULONG result = _conUnlockC( con );
#ifdef _DEBUG
   if( result == 0 )
   {
      on_watch_thread_conc( -1 );
   }
#endif
   return result;
}
/*{{end-c-function}}*/
// -----------------------------------------------------------------------------------------------------------------
#define OT4XB_QLOOP_COMPILE_BLOCKS  0x01000000
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_qloop
            | syntax_: `ot4xb_qloop( nFlags, @uCargo, bEval [, bCondition] [, bInit] )`
            | category: value/control
            | _kw_: loop, codeblock loop, while, iterate, quick loop
   }}*/
/*{{|desc: Executes a small loop from Xbase++, evaluating a body codeblock while an optional condition
      codeblock is true.
    | params:
    - `nFlags` Numeric - Optional bit mask. Combine flags with bitwise OR, for example with nOr( flag1,
      ..., flagX ). 0x01000000 (OT4XB_QLOOP_COMPILE_BLOCKS in ot4xb.ch) - compile block parameters supplied as
      character macro strings before executing
      the loop.
    - `uCargo` Any by reference - Value passed as the only argument to bInit, bCondition, and bEval.
    - `bEval` Codeblock - Loop body. It is evaluated as Eval( bEval, uCargo ).
    - `bCondition` Codeblock - Optional condition block. While Eval( bCondition, uCargo ) is .T., the body
      is evaluated. When omitted, the body is evaluated once.
    - `bInit` Codeblock - Optional initialization block evaluated once before the loop body or condition.

    Returns Numeric - Non-negative values are the number of body evaluations. Negative values are error codes;
      currently -1 means bEval was not a codeblock after optional macro compilation.

    |note: This function is meant for running a small loop inside a codeblock without having to declare a
      separate function for the loop body. The OT4XB_QLOOP_COMPILE_BLOCKS flag allows the block parameters to be supplied as
      macro strings and compiled before the loop runs. The loop count is incremented before each body
      evaluation. When bCondition is omitted, the count is 1 after a successful single body evaluation. }}*/
_XPP_REG_FUN_( OT4XB_QLOOP )
{
   TXppParamList xpp( pl, 5 );

   DWORD dwFlags = xpp[1]->GetDWord();

   if( dwFlags & OT4XB_QLOOP_COMPILE_BLOCKS )
   {
      if( xpp[3]->CheckType( XPP_CHARACTER ) )
      {
         LPSTR pMacro = xpp[3]->StrDupA();
         xpp[3]->Put( NULLCONTAINER );
         if( pMacro )
         {
            _conEvalMacroStr( xpp[3]->con(), pMacro );
            _xfree( pMacro );
            pMacro = 0;
         }
      }
      if( xpp[4]->CheckType( XPP_CHARACTER ) )
      {
         LPSTR pMacro = xpp[4]->StrDupA();
         xpp[4]->Put( NULLCONTAINER );
         if( pMacro )
         {
            _conEvalMacroStr( xpp[4]->con(), pMacro );
            _xfree( pMacro );
            pMacro = 0;
         }
      }

      if( xpp[5]->CheckType( XPP_CHARACTER ) )
      {
         LPSTR pMacro = xpp[5]->StrDupA();
         xpp[5]->Put( NULLCONTAINER );
         if( pMacro )
         {
            _conEvalMacroStr( xpp[5]->con(), pMacro );
            _xfree( pMacro );
            pMacro = 0;
         }
      }
   }

   if( !xpp[3]->CheckType( XPP_BLOCK ) )
   {
      xpp[0]->PutLong( -1 );
      return;
   }
   ContainerHandle cargo = xpp[2]->con();
   LONG count = 0;

   if( xpp[5]->CheckType( XPP_BLOCK ) )
   {
      _conEvalVoid( xpp[5]->con(), cargo );
   }

   ContainerHandle codeblock = xpp[3]->con();

   if( xpp[4]->CheckType( XPP_BLOCK ) )
   {
      ContainerHandle condition = xpp[4]->con();
      while( _conEvalBool( condition, cargo ) )
      {
         count++;
         _conEvalVoid( codeblock, cargo );
      }
   }
   else
   {
      count++;
      _conEvalVoid( codeblock, cargo );
   }

   xpp[0]->PutLong( count );

}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
