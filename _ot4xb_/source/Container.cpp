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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BOOL _conCheckType( ContainerHandle con, ULONG nType )
{
   ULONG ul = 0;
   if( con == NULLCONTAINER ) return (BOOL) nType == 0;
   _conType( con, &ul );
   return (BOOL) ( ul & nType );
}
//-----------------------------------------------------------------------------------------------------------------------
OT4XB_API ULONG _conGetArrayLen( ContainerHandle cona )
{
   ULONG ul = 0;
   _conSizeA( cona, &ul, 0 );
   return ul;
}
//----------------------------------------------------------------------------------------------------------------------
// Description: Get a LONG value from a container
// Remarks: Retrieving LONG values with _conGetNL() can result in data lost if the container have stored a double
// value _conGetLong() detect the internal numeric type and convert it to LONG properly.
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
//----------------------------------------------------------------------------------------------------------------------
// Description: Get a LONG value from a container
// Remarks: Retrieving LONG values with _conGetNL() can result in data lost if the container have stored a double
// value _conGetLong() detect the internal numeric type and convert it to LONG properly.
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// Description: Get a LONG value from a Xbase++ parameter
// Params:
// <pl> Pointer to the Xbase++ parameter list
// <nIndex> Position of the parameter which contains the numeric value (first parameter is 1).
// <... > The remaining arguments must be of ULONG type and are only considered
// when the parameter <ulIndex> is an array. In this case, an index is specified for each array
// dimension to select the element which has the numeric value. Warning: The end of the
// list of array indexes must be indicated with a NULL index.
// Remarks: Retrieving LONG values with _parnl() can result in data lost if the Xbase++ param contains a double
// value _parLong() detect the internal numeric type and convert it to LONG properly.
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
      while( ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
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
// -----------------------------------------------------------------------------------------------------------------
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
      while( ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
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
// -----------------------------------------------------------------------------------------------------------------
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
      while( ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
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
// -----------------------------------------------------------------------------------------------------------------
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
      while( ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY PSZZ2ARRAY( XppParamList pl ) // PSzz2Array(pStr) -> aStr
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
//----------------------------------------------------------------------------------------------------------------------
// Retrieve a zero terminated string copy from a CHARACTER Xbase++ container
// The string must be released with _xfree() when no longer needed.
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
//----------------------------------------------------------------------------------------------------------------------
// Return a string containinig the class name of the provided Xbase++ container
// if this contains a object
// The string must be released with _xfree() when no longer needed.
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
//----------------------------------------------------------------------------------------------------------------------
// Return a string containing the parent class name of the provided Xbase++ container
// if this contains a object
// The string must be released with _xfree() when no longer needed.
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
//----------------------------------------------------------------------------------------------------------------------
// ..XB( { n,n,n,..} | n) -> n | n| ...
// return a numeric Xbase++ param as DWORD or combine with the OR bitwise operator the elements if the param is
// an Array of numeric values
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
//----------------------------------------------------------------------------------------------------------------------
// ..XB( { "blablabla","blablabla",..} | "blablabla") -> LPSTR blablabla\0blablabla\0blablabla\0\0
// Return a double zero terminated string from a character Xbase++ param
// or concatenate the items using Chr(0) as a separator if the param is an Xbase++ array
// The string must be released with _xfree() when no longer needed.
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
//----------------------------------------------------------------------------------------------------------------------
// Return a zero terminated string copy from a Xbase++ character param
// The string must be released with _xfree() when no longer needed.
OT4XB_API LPSTR _pszParam( XppParamList pl, ULONG n )
{
   return _pszParam_cb( pl, n, 0 );
}
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// Return the value of a Xbase++ member as LONG
OT4XB_API LONG _conGetNLMember( ContainerHandle conObj, LPSTR pMName )
{
   LONG n = 0;
   ContainerHandle con = _conPutNL( NULLCONTAINER, 0 );
   _conGetMember( conObj, pMName, con );
   _conGetLong( con, &n );
   _conRelease( con );
   return n;
}
//----------------------------------------------------------------------------------------------------------------------
// Store a LONG value into a Xbase++ object member
OT4XB_API void _conSetNLMember( ContainerHandle conObj, LPSTR pMName, LONG n )
{
   ContainerHandle con = _conPutNL( NULLCONTAINER, n );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
//----------------------------------------------------------------------------------------------------------------------
// Return the value of a Xbase++ member as BOOL
OT4XB_API BOOL _conGetLMember( ContainerHandle conObj, LPSTR pMName )
{
   BOOL n = FALSE;
   ContainerHandle con = _conPutL( NULLCONTAINER, 0 );
   _conGetMember( conObj, pMName, con );
   _conGetL( con, &n );
   _conRelease( con );
   return n;
}
//----------------------------------------------------------------------------------------------------------------------
// Store a BOOL value into a Xbase++ object member
OT4XB_API void _conSetLMember( ContainerHandle conObj, LPSTR pMName, BOOL n )
{
   ContainerHandle con = _conPutL( NULLCONTAINER, n );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
//----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
// Return a string from a Xbase++ object member
// the string is guaranteed to be zero terminated, but also can contain zeros inside
// the length of the string ( not counting the terminating zero) is stored inside pnLen if is provided
// The string must be released with _xfree() when no longer needed.

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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// Store a sized string into a Xbase++ object member
OT4XB_API void _conSetCLMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue, ULONG nLen )
{
   ContainerHandle con = _conPutCL( NULLCONTAINER, pValue, nLen );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
//----------------------------------------------------------------------------------------------------------------------
// Store a Zero terminated string into a Xbase++ object member
OT4XB_API void  _conSetCMember( ContainerHandle conObj, LPSTR pMName, LPSTR pValue )
{
   ContainerHandle con = _conPutC( NULLCONTAINER, pValue );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
//----------------------------------------------------------------------------------------------------------------------
// Fill a character buffer with the content of a Xbase++ object member
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
//----------------------------------------------------------------------------------------------------------------------
// Put a NIL value into a Xbase++ object member
OT4XB_API void _conSetNILMember( ContainerHandle conObj, LPSTR pMName )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   _conSetMember( conObj, pMName, con );
   _conRelease( con );
}
//----------------------------------------------------------------------------------------------------------------------
// retrieve a ContainerHandle from the Xbase++ paramlist if the param type match <nType>
// values in <nType> can be combined with the bitwise OR operator.
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conCopyParam( XppParamList pl, ULONG n )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam( pl, n, &bByRef );
   ContainerHandle conr = _conNew( con );
   if( con && ( !bByRef ) ) _conRelease( con );
   return conr;
}
//----------------------------------------------------------------------------------------------------------------------
// retrieve a ContainerHandle from the Xbase++ paramlist and it's type
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
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from a Xbase++ object member if match <nType>
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LCALLFUNCPA( XppParamList pl ) //lCallFuncPA(1func,2params,3@uResult)
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LCALLMETHODPA( XppParamList pl ) //lCallMethodPA(1Self,2method,3params,4@uResult)
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CALLFUNCTION( XppParamList pl ) // CallFunction(cFuncName,params..... )
{
   BOOL * _ref;
   ContainerHandle * _tos;
   ULONG       nParams = _partype( pl, 0 );
   ContainerHandle  _eval;
   ULONG n;
   LPSTR pfName;

   if( !( _partype( pl, 1 ) & XPP_CHARACTER ) ){
      _ret( pl ); return;
   }
   _ref = (BOOL *) _xgrab( (UINT) ( sizeof( BOOL ) * nParams ) );
   _tos = (ContainerHandle *) _xgrab( (UINT) ( sizeof( ContainerHandle ) * nParams ) );
   for( n = 0; n < nParams; n++ ) _tos[n] = _conParam( pl, n + 1, &_ref[n] );
   ot4xb_conRLockC( _tos[0], &pfName, &n );
   _eval = _conNew( NULLCONTAINER );
   _conCallPa( _eval, pfName, nParams - 1, &( _tos[1] ) );
   ot4xb_conUnlockC( _tos[0] );
   for( n = 0; n < nParams; n++ ) if( !_ref[n] ) _conRelease( _tos[n] );
   _xfree( (void *) _ref );
   _xfree( (void *) _tos );
   _conReturn( pl, _eval );
   _conRelease( _eval );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LOBJGETMEMBER( XppParamList pl ) //lObjGetMember(1Self,2name,3@val) -> lOk
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
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LOBJSETMEMBER( XppParamList pl ) //lObjSetMember(1Self,2name,3val) -> lOk
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from the param list if was passed by reference and the type is object
OT4XB_API ContainerHandle _conParamSelfByRef( XppParamList pl, ULONG nParam )
{
   return _conTParamByRef( pl, nParam, XPP_OBJECT );
}
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from the param list if was passed by reference
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
//----------------------------------------------------------------------------------------------------------------------
// retrieve a container from the param list if was passed by reference and match <ulType>
OT4XB_API ContainerHandle _conTParamByRef( XppParamList pl, ULONG nParam, ULONG ulType )
{
   ContainerHandle con = _conParamByRef( pl, nParam );
   ULONG nParamType = 0;
   if( con == NULLCONTAINER ) return NULLCONTAINER;
   _conType( con, &nParamType );
   if( nParamType & ulType ) return con;
   return NULLCONTAINER;
}
//-----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// Release multiple ContainerHandle params. The last param must be NULLCONTAINER
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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// if pcon point to a NIL Xbase++ container, release the container and store a NULLCONTAINER at the provided pointer
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
//----------------------------------------------------------------------------------------------------------------------
// return the length of a string stored inside a Xbase++ array element
// Syntax:
// _conArrayGetSizeC(ContainerHandle cona , n , ... )
// Params:
// <cona> Xbase++ Array container
// <n> Array index
// <... > an index must be specified for each array
// dimension to select the element which has the numeric value. Warning: The end of the
// list of array indexes must be indicated with a NULL index.
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
//----------------------------------------------------------------------------------------------------------------------
// return a copy a string stored inside a Xbase++ array element
// Syntax:
// _conArrayGetXStrDup(ContainerHandle cona , n , ... )
// Params:
// <cona> Xbase++ Array container
// <n> Array index
// <... > an index must be specified for each array
// dimension to select the element which has the numeric value. Warning: The end of the
// list of array indexes must be indicated with a NULL index.
// Remarks: The string must be released with _xfree()
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
//----------------------------------------------------------------------------------------------------------------------
// Fill a string buffer with the content of a string stored inside a Xbase++ array element
// Syntax:
// _conArrayGetXStrDup(ContainerHandle cona , n , ... )
// Params:
// <cona> Xbase++ Array container
// <n> Array index
// <... > an index must be specified for each array
// dimension to select the element which has the numeric value. Warning: The end of the
// list of array indexes must be indicated with a NULL index.
// Return the number of characters writted
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
//----------------------------------------------------------------------------------------------------------------------
// returns a long value stored into an Xbase++ array element
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
// -----------------------------------------------------------------------------------------------------------------
// returns a BOOL value stored into an Xbase++ array element
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
//----------------------------------------------------------------------------------------------------------------------
// returns a long value stored into an Xbase++ array element
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

//----------------------------------------------------------------------------------------------------------------------
// returns a double value stored into an Xbase++ array element
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
//----------------------------------------------------------------------------------------------------------------------
// Compile a string to generate a codeblock and store it into a Xbase++ array element
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

   _conEvalMacroStr( con, pStr );

   nRet = _conArrayPutA( cona, con, pi );
   _xfree( (void *) pi );
   _conRelease( con );
   return nRet;
}
//----------------------------------------------------------------------------------------------------------------------
// Init a Xbase++ array element with the emty value corresponding with the provided type
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
//----------------------------------------------------------------------------------------------------------------------
// store a LONG value into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// store a double value specifing its format into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// store a double value into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// store a logical value into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// store a date string value as a Xbase++ Date type into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// store a sized string into a Xbase++ array item
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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
// store a zero terminated string into a Xbase++ array item
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
//----------------------------------------------------------------------------------------------------------------------
// put a string at the Xbase++ return stack.
// the string is formated with wsprintf() so the remaining params
// will be acording the wsprintf() syntax.
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
//----------------------------------------------------------------------------------------------------------------------
// try to destroy a Xbase++ dynamic class
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
//----------------------------------------------------------------------------------------------------------------------
// return the class object if previously created from it's class Name
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
//----------------------------------------------------------------------------------------------------------------------
// return the class object if previously created or create it from it's class Name
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conPutNewObj( ContainerHandle conr, LPSTR pClassName, ContainerHandle p1, ... )
{
   va_list          pMarker;
   ContainerHandle  con;
   TContainerHandleList * pList;
   if( !conr ){
      conr = _conNew( NULLCONTAINER );
   }
   if( pClassName == 0 ) return NULLCONTAINER;
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
   _conRelease( con );
   pList->Release( 0 ); // Free ClassObject
   delete pList;
   return conr;
}
// -----------------------------------------------------------------------------------------------------------------

// return a instance object from it's class Name
// must specify the params to the New() method and a extra NULLCONTAINER
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
//----------------------------------------------------------------------------------------------------------------------

// like _conNewObj but automatically release all provided containers
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
//----------------------------------------------------------------------------------------------------------------------
// retrieve a 32 bit float value from a Xbase++ numeric container
OT4XB_API DWORD _conGetFloat( ContainerHandle con, FLOAT * pnf )
{
   double nd = 0.00F;
   DWORD result = (DWORD) _conGetND( con, &nd );
   pnf[0] = (FLOAT) nd;
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
// store a 32 bit float value inside a Xbase++ numeric container
OT4XB_API ContainerHandle _conPutFloat( ContainerHandle con, FLOAT nf )
{
   double nd = (double) nf;
   return _conPutND( con, nd );
}
//----------------------------------------------------------------------------------------------------------------------
// retrieve a 64 bit integer value from a Xbase++ character container
// Note: the container must contain the 8 Byte internal representation of the double value
OT4XB_API DWORD _conGetQWord( ContainerHandle con, ULONGLONG * pqw )
{
   ULONG nBytes;
   return (DWORD) _conGetCL( con, &nBytes, (LPSTR) ( (void *) pqw ), sizeof( ULONGLONG ) );
}
//----------------------------------------------------------------------------------------------------------------------
// Store the 8Byte representation of a __int64 value inside Xbase++ character container or produce a new one
OT4XB_API ContainerHandle _conPutQWord( ContainerHandle con, ULONGLONG qw )
{
   return _conPutCL( con, (LPSTR) ( (void *) &qw ), sizeof( ULONGLONG ) );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY _VAR2CON( XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conParam( pl, 1, &bByRef );
   ContainerHandle conr = _conNew( con );
   if( !bByRef ) _conRelease( con );
   _retnl( pl, (LONG) ( (void *) conr ) );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY _CON2VAR( XppParamList pl )
{
   ContainerHandle con = (ContainerHandle) ( (void *) _parLong( pl, 1 ) );
   if( con == NULLCONTAINER ) _ret( pl );
   else _conReturn( pl, con );
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY _CONRELEASE( XppParamList pl )
{
   ContainerHandle con = (ContainerHandle) ( (void *) _parLong( pl, 1 ) );
   if( con == NULLCONTAINER ) _ret( pl );
   else {
      _conReturn( pl, con ); _conRelease( con );
   }
}
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY ARRAY2PSZZ( XppParamList pl ) // Array2pszz(aStr|cStr,@nBuffSize) -> pStr
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
//-----------------------------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------------------------
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
      while( ( nn = va_arg( pMarker, ULONG ) ) != 0 ) pnn[n++] = nn;
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API XPPAPIRET _conGetDateAsSystemTime( ContainerHandle con, SYSTEMTIME * pst )
{
   char sz[8];
   LONG n;

   _bset( (LPBYTE) sz, 32, 8 );
   if( con && pst ) _conGetDS( con, sz );
   if( sz[0] >= '0' )
   {
      for( n = 0; n < 8; n++ ) sz[n] -= 48;
      pst->wDay = (WORD) ( sz[7] + ( sz[6] * 10 ) );
      pst->wMonth = (WORD) ( sz[5] + ( sz[4] * 10 ) );
      pst->wYear = (WORD) ( ( (WORD) sz[3] ) + ( (WORD) sz[2] * 10 ) + ( (WORD) sz[1] * 100 ) + ( (WORD) sz[0] * 1000 ) );
   }
   else
   {
      pst->wDay = 0;
      pst->wMonth = 0;
      pst->wYear = 0;
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API BSTR _BSTRParam( XppParamList pl, ULONG n )
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl, n, &bByRef, XPP_CHARACTER );
   BSTR  pb = _conGetBSTR( con );
   if( con && ( !bByRef ) ) _conRelease( con );
   return pb;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BSTR _conGetBSTRMember( ContainerHandle conObj, LPSTR pMName )
{
   ContainerHandle con = _conNew( NULLCONTAINER );
   BSTR  pb = NULL;
   if( _conGetMember( conObj, pMName, con ) == 0 ) pb = _conGetBSTR( con );
   _conRelease( con );
   return pb;
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
XPPRET XPPENTRY OT4XB_MEMVAR_SETGET( XppParamList pl ) //ot4xb_memvar_setget(var,val)
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#pragma warning(disable: 4740 )
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
      cona = _conPut( cona, conTmp );
      _conRelease( conTmp );
   }
   if( con ){
      _conArrayPut( cona, con, nSize, 0 );
   }
   return cona;
}
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API ContainerHandle _conGenericBreakCB( BOOL bCopy )
{
   static ContainerHandle con = NULLCONTAINER;
   if( con == NULLCONTAINER ){
      con = _conNewCodeblock( "{|e| Break(e) }" );
   }
   return ( bCopy ? _conNew( con ) : con );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( _CONGENERICBREAKCB )
{
   _conReturn( pl, _conGenericBreakCB( 0 ) );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
   _retc( pl, "" );
}
// -----------------------------------------------------------------------------------------------------------------
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
   _retc( pl, "" );
}
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------

_XPP_REG_FUN_( __V2FV )	 // __v2fv( 1 value , 2 type , 3 length , 4 dec ) -> value adjusted to field type and size
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

// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( __ANEW ) // __ANew( e1 , ... , eN ) -> { e1 , ... , eN }
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
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( __APEEK ) // __APeek( array , nIndex, ... , nSubIndex ) -> value | NIL
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
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( __VPEEK ) // __vpeek( vv , exp , def) -> value | def
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
// -----------------------------------------------------------------------------------------------------------------
// flags: 1 loop
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( __ANEXT ) // __ANext( array , @nIndex , flags) -> value | NIL
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
            sprintf( p, "%f", nd );
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
            _conReleaseM( con_key, con_value, 0 );
         }
         z += " ";
      }
      return;
   }
}

// -----------------------------------------------------------------------------------------------------------------
// flags = // 0x100 no scientific, 1 LTrim , 2 Rtrim , 0x200 do not convert 1252-to-utf8 
_XPP_REG_FUN_( __V2_CSV_CELL )  // 1 value , 2 flags , 3 decimal
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
         char s[128]; ZeroMemory( s, sizeof( s ) );
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
               if( dec > 0 && dec <= 0x0F )
               {
                  s[pos++] = '.';
                  for( ; dec; dec-- )
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
// -----------------------------------------------------------------------------------------------------------------
// flags:
// 2 - RTRIM
// 0x10000 -  naked value
_XPP_REG_FUN_( __XML_FV ) // __xml_fv(1 name , 2 value , 3 attributes , 4 cp_To = utf8 , 5 cp_from = default ansi , 6 flags )
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
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
static DWORD _watching_thread_ = 0;
static LONG  _watching_thread_count = 0;
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
// -----------------------------------------------------------------------------------------------------------------
extern "C" OT4XB_API LONG  __cdecl count_watch_thread_conc( void )
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      return _watching_thread_count;
   }
   return (DWORD) -1;
}
// -----------------------------------------------------------------------------------------------------------------

extern "C" OT4XB_API void  __cdecl on_watch_thread_conc( LONG n )
{
   if( _watching_thread_ == GetCurrentThreadId() )
   {
      _watching_thread_count += n;
   }
}
#endif
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------------------------------------------
#define OT4XB_QLOOP_COMPILE_BLOCKS  0x01000000
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function_+++.md ==>
### function `()`
* +++
* Syntax:
`+++`
<== <==
*******************************************************************************************************************/
_XPP_REG_FUN_( OT4XB_QLOOP ) // ot4xb_qloop( 1nFlags , 2@uCargo , [3bEval] , [4bCondition] , [5 bInit] ) -> nErrorCode ( >= 0 nLoops , < 0 Error Code )
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
// -----------------------------------------------------------------------------------------------------------------
