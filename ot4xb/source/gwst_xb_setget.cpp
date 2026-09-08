//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
typedef struct GWSTSG_strcut
{                  
   XppParamList     pl;
   ContainerHandle  conpt;
   BOOL             bWrite;
   ContainerHandle  conVal;
   DWORD            dwType;
   void *           pt;
   BOOL             bLock;  
   DWORD            dwPtSize;
} GWSTSG;
//-----------------------------------------------------------------------------------------------------------------------
// 1@v,2PCount(),3pt,4pshift,5offset,6psize,7ghost,8size
static BOOL _gwst_sg_init_( GWSTSG * psg , XppParamList pl )
{  
   DWORD tp = 0;    
   void** ppGhost = ( void**) _parnl(pl,7);
   _bset( (BYTE*) psg,0,sizeof( GWSTSG ) );
   psg->pl      = pl;
   psg->bWrite  = (BOOL) (_parnl(pl,2) > 1 );    
   psg->conVal  = ( psg->bWrite ? _conTpParamByRef(pl,1,&(psg->dwType)) : _conNew(NULLCONTAINER));
   if( ppGhost ) 
   {
      psg->pt = ppGhost[0];
      if( psg->pt ) psg->pt = (void*) ( ((DWORD) psg->pt ) + ((DWORD) _parnl(pl,5) ) );
   }
   else
   {
      psg->conpt   = _conTpParamByRef(pl,3,&tp);
      if( psg->conpt )
      {
         if( tp & XPP_UNDEF )
         {           
            DWORD dw = (DWORD) _parnl(pl,6);
            LPSTR p  = (LPSTR) _xgrab( dw );
            _conPutCL( psg->conpt , p ,dw);
            _xfree( (void*) p);
            tp = XPP_CHARACTER;
         }
         if( tp & XPP_CHARACTER)
         {
            if( ot4xb_conWLockC( psg->conpt , reinterpret_cast<LPSTR*>( &(psg->pt) ) , &(psg->dwPtSize) ) ) // 0 == OK
            {
               psg->pt = 0;
            }
            else psg->bLock = TRUE;
         }
         else _conGetNL( psg->conpt , (LONG*) ( &(psg->pt) ) );
         
      }
      if( psg->pt ) psg->pt = (void*) ( ((DWORD) psg->pt ) + ((DWORD) _parnl(pl,4) ) + ((DWORD) _parnl(pl,5) ) );
   }
   return TRUE;
} 
// -----------------------------------------------------------------------------------------------------------------
static void _gwst_sg_exit_( GWSTSG * psg )
{
   if( psg->conpt || psg->pt )
   {
      if( psg->bLock )
      {
         ot4xb_conUnlockC( psg->conpt );
      }
      if( psg->bWrite )
      {
         _ret( psg->pl );
      }
      else
      {
         _conReturn( psg->pl , psg->conVal );
         _conReleaseM( psg->conVal , NULLCONTAINER );
      }
      return;
   }
   else 
   {
      if( !psg->bWrite )
      {
         _conReleaseM( psg->conVal, NULLCONTAINER );
      }
      _ret( psg->pl ); 
   }
}
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_bool_
            | syntax_: `_gwst_xbsetget_bool_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_bool_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a Win32 BOOL member (32 bit). A
      written value that is not zero is stored as 1, zero as 0; reading returns the member as a Logical.
    | params:
    - `@xValue` Logical/Numeric - New member value; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other value selects read
      mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure image or a Numeric
      memory address. A NIL is replaced with a new Character buffer of nStorageSize bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached through the
      pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Logical - Member value in read mode (.F. when the member cannot be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_BOOL_(XppParamList pl)
{                  
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
      
         if( sg.dwType & XPP_LOGICAL ) _conGetL(sg.conVal, reinterpret_cast<BOOL*>(sg.pt) );
         else _conGetLong(sg.conVal, reinterpret_cast<LONG*>(sg.pt) );
         if( reinterpret_cast<BOOL*>(sg.pt)[0] ) reinterpret_cast<BOOL*>(sg.pt)[0] = TRUE;
         else reinterpret_cast<BOOL*>(sg.pt)[0] = FALSE;
      }
      else if( sg.pt ) _conPutL(sg.conVal,reinterpret_cast<BOOL*>(sg.pt)[0]);
      else _conPutL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_bytebool_
            | syntax_: `_gwst_xbsetget_bytebool_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_bytebool_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a boolean member
      stored in a single byte. A written value that is not zero is stored as 1, zero as 0; reading returns
      the member as a Logical.
    | params:
    - `@xValue` Logical/Numeric - New member value; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Logical - Member value in read mode (.F. when the member cannot be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_BYTEBOOL_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         BOOL b = FALSE;
         if( sg.dwType & XPP_LOGICAL ) _conGetL(sg.conVal, &b );
         else _conGetLong(sg.conVal, reinterpret_cast<LONG*>(&b) );
         if( b ) reinterpret_cast<BYTE*>(sg.pt)[0] = 1;
         else reinterpret_cast<BYTE*>(sg.pt)[0] = 0;
      }
      else if( sg.pt )
      {
         BOOL b = ( reinterpret_cast<BYTE*>(sg.pt)[0] ? TRUE : FALSE);
         _conPutL(sg.conVal,b);
      }
      else _conPutL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_byte_
            | syntax_: `_gwst_xbsetget_byte_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_byte_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write an unsigned
      8 bit member. Reading returns 0 to 255.
    | params:
    - `@xValue` Numeric - New member value; only the low 8 bits are stored. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value 0 to 255 in read mode (0 when the member cannot be reached); NIL in
      write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_BYTE_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<BYTE*>(sg.pt)[0] = LOBYTE( LOWORD(n) );
      }
      else if( sg.pt )
      {                      
         BYTE b = reinterpret_cast<BYTE*>(sg.pt)[0];
         _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0),0) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_sint8_
            | syntax_: `_gwst_xbsetget_sint8_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_sint8_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a signed 8 bit
      member. Reading sign extends the byte and returns -128 to 127.
    | params:
    - `@xValue` Numeric - New member value; only the low 8 bits are stored. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value -128 to 127 in read mode (0 when the member cannot be reached); NIL in
      write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_SINT8_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<BYTE*>(sg.pt)[0] = LOBYTE( LOWORD(n) );
      }
      else if( sg.pt )
      {                      
         BYTE b = reinterpret_cast<BYTE*>(sg.pt)[0];
         if( b & 0x80 ) _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0xFF),0xFFFF) );
         else _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0),0) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_word_
            | syntax_: `_gwst_xbsetget_word_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_word_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write an unsigned
      16 bit member. Reading returns 0 to 65535.
    | params:
    - `@xValue` Numeric - New member value; only the low 16 bits are stored. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value 0 to 65535 in read mode (0 when the member cannot be reached); NIL in
      write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_WORD_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = LOWORD(n);
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) MAKELONG(reinterpret_cast<WORD*>(sg.pt)[0],0));
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_sint16_
            | syntax_: `_gwst_xbsetget_sint16_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_sint16_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a signed 16 bit
      member. Reading sign extends the value and returns -32768 to 32767.
    | params:
    - `@xValue` Numeric - New member value; only the low 16 bits are stored. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value -32768 to 32767 in read mode (0 when the member cannot be reached); NIL
      in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_SINT16_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = LOWORD(n);
      }
      else if( sg.pt )
      {  
         WORD w = reinterpret_cast<WORD*>(sg.pt)[0];
         _conPutNL(sg.conVal,(LONG) MAKELONG(w,((w & 0x8000) ? 0xFFFF : 0 ) ) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_dword_
            | syntax_: `_gwst_xbsetget_dword_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_dword_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a 32 bit member.
      The member is read back with signed semantics, so values above 0x7FFFFFFF appear negative.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member as a signed 32 bit value in read mode (0 when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_DWORD_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_uint32_
            | syntax_: `_gwst_xbsetget_uint32_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_uint32_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write an unsigned
      32 bit member. Reading never returns a negative value: above 0x7FFFFFFF the member comes back as a
      floating point Numeric.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value 0 to 4294967295 in read mode (0 when the member cannot be reached); NIL
      in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_UINT32_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
      }
      else if( sg.pt )
      {  
         DWORD dw = reinterpret_cast<DWORD*>(sg.pt)[0];
         if( dw & 0x80000000 ) _conPutNDF(sg.conVal,(double)dw,-1,0);
         else _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_dword64_
            | syntax_: `_gwst_xbsetget_dword64_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_dword64_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write an unsigned
      64 bit member (QWORD). Reading returns the raw member as an 8 byte Character string. Writing clears
      the member first and then stores xValue according to its type; unlisted types leave the member
      cleared.
    | params:
    - `@xValue` Character/Numeric/Array/Object - New member value; only used in write mode. A Character
      supplies the first 8 bytes; an integer Numeric sets the low 32 bits; a floating point Numeric is
      converted to a 64 bit integer; an Array supplies { nLow, nHigh }; an Object supplies its Q member as
      an 8 byte string.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Character - The member as an 8 byte string in read mode (8 zero bytes when the member cannot
      be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_DWORD64_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         reinterpret_cast<ULONGLONG*>(sg.pt)[0] = 0;
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb, reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG) );
         }
         else if( (sg.dwType & XPP_NUMERIC) && (sg.dwType & _xpp_DOUBLE) )         
         {
            double nd = 0.00F;
            _conGetND(sg.conVal,&nd);
            reinterpret_cast<ULONGLONG*>(sg.pt)[0] = (ULONGLONG) nd;
         }
         else if( sg.dwType & XPP_NUMERIC)
         {                                                  
            LONG n = 0;
            _conGetNL(sg.conVal,&n);
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->LowPart = (DWORD) n;
         }                
         else if( sg.dwType & XPP_ARRAY)
         {                                                  
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->LowPart  = (DWORD) _conArrayGetNL(sg.conVal,1,0);
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->HighPart = (DWORD) _conArrayGetNL(sg.conVal,2,0);
         }                
         else if( sg.dwType & XPP_OBJECT)
         {                                                  
            _conGetCLMember(sg.conVal,"Q",reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG));
         }                
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG));
      }
      else
      {
         ULONGLONG qw = 0;
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(&qw), sizeof(ULONGLONG));
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_nint64_
            | syntax_: `_gwst_xbsetget_nint64_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_nint64_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a signed 64 bit
      member. Reading returns the raw member as an 8 byte Character string. Writing clears the member first
      and then stores xValue according to its type; unlisted types leave the member cleared.
    | params:
    - `@xValue` Character/Numeric/Array/Object - New member value; only used in write mode. A Character
      supplies the first 8 bytes; an integer Numeric sets the low 32 bits and sign extends when negative; a
      floating point Numeric is converted to a 64 bit integer; an Array supplies { nLow, nHigh }; an Object
      supplies its Q member as an 8 byte string.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Character - The member as an 8 byte string in read mode (8 zero bytes when the member cannot
      be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_NINT64_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         reinterpret_cast<LONGLONG*>(sg.pt)[0] = 0;
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb, reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG) );
         }
         else if( (sg.dwType & XPP_NUMERIC) && (sg.dwType & _xpp_DOUBLE) )                  
         {
            double nd = 0.00F;
            _conGetND(sg.conVal,&nd);
            reinterpret_cast<LONGLONG*>(sg.pt)[0] = (LONGLONG) nd;
         }
         else if( sg.dwType & XPP_NUMERIC)
         {                                                  
            LONG n = 0;
            _conGetNL(sg.conVal,&n);
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->LowPart = (DWORD) n;
            if( n < 0 ) reinterpret_cast<LARGE_INTEGER*>(sg.pt)->HighPart = -1;
         }                
         else if( sg.dwType & XPP_ARRAY)
         {                                                  
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->LowPart  = (DWORD) _conArrayGetNL(sg.conVal,1,0);
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->HighPart = _conArrayGetNL(sg.conVal,2,0);
         }                
         else if( sg.dwType & XPP_OBJECT)
         {                                                  
            _conGetCLMember(sg.conVal,"Q",reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG));
         }                
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG));
      }
      else
      {
         LONGLONG qw = 0;
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(&qw), sizeof(LONGLONG));
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_pclipvar_
            | syntax_: `_gwst_xbsetget_pclipvar_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_pclipvar_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code for members that hold a complete
      Xbase++ value of any type. Every write releases the previously stored value; assigning NIL just
      leaves the member empty. Reading returns the stored value.
    | params:
    - `@xValue` AnyType - New member value; NIL clears the member. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns AnyType - The stored value in read mode, NIL when the member is empty; NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_PCLIPVAR_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
        if( reinterpret_cast<ContainerHandle*>(sg.pt)[0] )
        {
           _conRelease( reinterpret_cast<ContainerHandle*>(sg.pt)[0] );
           reinterpret_cast<ContainerHandle*>(sg.pt)[0] = NULLCONTAINER;
        }
        if( !(sg.dwType & XPP_UNDEF) )
        {
           reinterpret_cast<ContainerHandle*>(sg.pt)[0] = _conPut(NULLCONTAINER,sg.conVal);
        }
      }
      else if( sg.pt )
      {  
         _conPut(sg.conVal,reinterpret_cast<ContainerHandle*>(sg.pt)[0]);
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_xppguiwnd_
            | syntax_: `_gwst_xbsetget_xppguiwnd_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_xppguiwnd_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code for members that hold the C++
      window pointer of an Xbase++ GUI object. A Numeric is stored as is; an Object is asked for the
      pointer through its GetTwWinBaseCppPointer() method; any other type stores 0. Reading returns the
      pointer as a Numeric.
    | params:
    - `@xValue` Numeric/Object - New member value; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - The stored pointer in read mode (0 when the member cannot be reached); NIL in write
      mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_XPPGUIWND_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
        if( sg.dwType & XPP_NUMERIC ) _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
        else if( sg.dwType & XPP_OBJECT )
        {
           reinterpret_cast<LONG*>(sg.pt)[0] = _conMCallLong(sg.conVal,"GetTwWinBaseCppPointer");
        }
        else reinterpret_cast<LONG*>(sg.pt)[0] = 0;
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_float_
            | syntax_: `_gwst_xbsetget_float_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_float_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a 32 bit
      floating point member.
    | params:
    - `@xValue` Numeric - New member value; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value in read mode (0.0 when the member cannot be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_FLOAT_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {    
         _conGetFloat(sg.conVal,reinterpret_cast<FLOAT*>(sg.pt) );
      }
      else if( sg.pt )
      {  
         _conPutFloat(sg.conVal,reinterpret_cast<FLOAT*>(sg.pt)[0]);
      }
      else _conPutND(sg.conVal,0.00F );
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_double_
            | syntax_: `_gwst_xbsetget_double_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_double_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a 64 bit
      floating point member.
    | params:
    - `@xValue` Numeric - New member value; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value in read mode (0.0 when the member cannot be reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_DOUBLE_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {    
         _conGetND(sg.conVal,reinterpret_cast<double*>(sg.pt) );
      }
      else if( sg.pt )
      {  
         _conPutND(sg.conVal,reinterpret_cast<double*>(sg.pt)[0]);
      }
      else _conPutND(sg.conVal,0.00F );
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_lpstr_
            | syntax_: `_gwst_xbsetget_lpstr_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_lpstr_, Function
   }}*/
/*{{|desc: Internal GWST member accessor for LPSTR members. Alias of the DWORD accessor: the member is
      handled as a 32 bit pointer value, a Numeric address, not the text it points to.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member as a signed 32 bit value in read mode (0 when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_LPSTR_(XppParamList pl){ _GWST_XBSETGET_DWORD_(pl); }
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_binstr_
            | syntax_: `_gwst_xbsetget_binstr_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost, nMemberSize )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_binstr_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a fixed size
      binary member of nMemberSize bytes. Writing copies a Character value into the member and zero fills
      the rest of it; a non Character value zero fills the whole member. Reading returns the complete
      member, embedded zero bytes included.
    | params:
    - `@xValue` Character - Bytes to store; anything beyond nMemberSize bytes is discarded. Only used
      in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.
    - `nMemberSize` Numeric - Byte size of the member buffer.

    Returns Character - The whole member, nMemberSize bytes, in read mode; NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_BINSTR_(XppParamList pl)
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         DWORD dw = 0;
         if( sg.dwType & XPP_CHARACTER ) _conGetCL(sg.conVal,&dw,reinterpret_cast<LPSTR>(sg.pt),dws);
         if(dw < dws) _bset(reinterpret_cast<LPBYTE>(sg.pt) + dw , 0 , dws - dw );
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<LPSTR>(sg.pt),dws);
      }
      else
      {    
         void * p = _xgrab(dws);
         _conPutCL(sg.conVal,reinterpret_cast<LPSTR>(p),dws);
         _xfree(p);
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_szstr_
            | syntax_: `_gwst_xbsetget_szstr_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost, nMemberSize )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_szstr_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a fixed size
      zero terminated ANSI member of nMemberSize bytes. Writing copies a Character value and zero fills the
      rest of the member; a value of the full member size leaves no zero terminator. Reading returns the
      member text up to the first zero byte.
    | params:
    - `@xValue` Character - Text to store; truncated to nMemberSize bytes. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.
    - `nMemberSize` Numeric - Byte size of the member buffer.

    Returns Character - Member text up to the first zero byte in read mode ("" when the member cannot be
      reached); NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_SZSTR_(XppParamList pl)
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         DWORD dw = 0;
         if( sg.dwType & XPP_CHARACTER ) _conGetCL(sg.conVal,&dw,reinterpret_cast<LPSTR>(sg.pt),dws);
         if(dw < dws) _bset(reinterpret_cast<LPBYTE>(sg.pt) + dw , 0 , dws - dw );
      }
      else if( sg.pt ) _conPutC(sg.conVal,reinterpret_cast<LPSTR>(sg.pt));
      else _conPutC(sg.conVal,"");
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_szwstr_
            | syntax_: `_gwst_xbsetget_szwstr_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost, nMemberSize )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_szwstr_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a fixed size
      Unicode member of nMemberSize bytes. Writing zero fills the member and converts the ANSI Character
      value to Unicode into it, truncated to the member capacity minus one character. Reading converts the
      member back to ANSI.
    | params:
    - `@xValue` Character - ANSI text to store; only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.
    - `nMemberSize` Numeric - Byte size of the member buffer.

    Returns Character - Member text converted to ANSI in read mode ("" when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_SZWSTR_(XppParamList pl)
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         _bset(reinterpret_cast<LPBYTE>(sg.pt),0,dws);
         if( sg.dwType & XPP_CHARACTER )
         {                                                                                     
            ULONG nMax  = ((dws -1) >> 1);
            ULONG nLen  = 0;
            LPSTR pAnsi = 0;
            ot4xb_conRLockC(sg.conVal,&pAnsi,&nLen); 
            if( nLen > 0 )
            {
               if( nLen > nMax ) nLen = nMax;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,nLen,reinterpret_cast<LPWSTR>(sg.pt),nLen);
            }
            ot4xb_conUnlockC(sg.conVal); 
         }
      }
      else if( sg.pt )
      {  
         ULONG nLen  = ( dws >> 1 );
         LPSTR pAnsi = (LPSTR) _xgrab(nLen + 1);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,reinterpret_cast<LPWSTR>(sg.pt),nLen,pAnsi,nLen,0,0);
         _conPutC(sg.conVal,pAnsi);
         _xfree( (void*) pAnsi);
      }
      else _conPutC(sg.conVal,"");
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_dynsz_
            | syntax_: `_gwst_xbsetget_dynsz_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost, nMemberSize )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_dynsz_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code for members that point to a
      dynamically allocated zero terminated ANSI string owned by the structure. Writing always releases the
      current string first; a Character value is then duplicated and the member points to the copy, any
      other value leaves the member cleared. Reading returns the text, or NIL when the member is cleared.
    | params:
    - `@xValue` Character - New text; any other type just clears the member. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.
    - `nMemberSize` Numeric - Not used by this accessor; the string is sized dynamically.

    Returns Character - Member text in read mode, NIL when the member holds no string; NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_DYNSZ_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         if( reinterpret_cast<LPSTR*>(sg.pt)[0] )
         {
            _xfree(reinterpret_cast<void**>(sg.pt)[0]);
            reinterpret_cast<void**>(sg.pt)[0] = 0;
         }
         if( sg.dwType & XPP_CHARACTER )
         {         
            reinterpret_cast<LPSTR*>(sg.pt)[0] = _conXStrDup(sg.conVal);
         }
      }
      else if( sg.pt )
      {  
         if( reinterpret_cast<LPSTR*>(sg.pt)[0] )
         {
            _conPutC( sg.conVal , reinterpret_cast<LPSTR*>(sg.pt)[0] );
         }
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_wordnet_
            | syntax_: `_gwst_xbsetget_wordnet_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_wordnet_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write an unsigned
      16 bit member kept in network byte order (big endian). Bytes are swapped on write and on read, so
      the Xbase++ side always sees a plain Numeric.
    | params:
    - `@xValue` Numeric - New member value; only the low 16 bits are stored. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member value 0 to 65535 in read mode (0 when the member cannot be reached); NIL in
      write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_WORDNET_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = htons(LOWORD(n));
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) MAKELONG(ntohs(reinterpret_cast<WORD*>(sg.pt)[0]),0));
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_dwordnet_
            | syntax_: `_gwst_xbsetget_dwordnet_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_dwordnet_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a 32 bit member
      kept in network byte order (big endian). Bytes are swapped on write and on read; the member is read
      back with signed semantics, so values above 0x7FFFFFFF appear negative.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member as a signed 32 bit value in read mode (0 when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_DWORDNET_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<DWORD*>(sg.pt)[0] = htonl(n);
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) ntohl(reinterpret_cast<DWORD*>(sg.pt)[0]) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_xdate_
            | syntax_: `_gwst_xbsetget_xdate_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_xdate_, Function
   }}*/
/*{{|desc: Internal GWST member accessor used by generated property code to read or write a Date member
      stored as 8 characters in YYYYMMDD form. Writing clears the member and stores a Date as its YYYYMMDD
      text, or copies a Character value as raw bytes. Reading builds a Date from the member.
    | params:
    - `@xValue` Date/Character - New value; a Date is stored as YYYYMMDD text, a Character is copied
      as raw bytes (first 8). Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Date - Member date in read mode (an empty Date when the member cannot be reached); NIL in
      write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_XDATE_(XppParamList pl)
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _bset(reinterpret_cast<LPBYTE>(sg.pt) , 0 , 8);
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb,reinterpret_cast<CHAR*>(sg.pt), 8 );
         }
         else if( sg.dwType & XPP_DATE )
         {
            _conGetDS(sg.conVal, reinterpret_cast<CHAR*>(sg.pt));
         }
      }
      else if( sg.pt )
      {  
         _conPutDS(sg.conVal,reinterpret_cast<CHAR*>(sg.pt));
      }
      else
      {
         char sz[16];
         _bset((LPBYTE)sz,0,16); _bset((LPBYTE)sz,32,8);
         _conPutDS(sg.conVal,sz);
      }
   }
   _gwst_sg_exit_(&sg);
}
/*{{end-internal-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_pointer32_
            | syntax_: `_gwst_xbsetget_pointer32_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_pointer32_, Function
   }}*/
/*{{|desc: Internal GWST member accessor for 32 bit pointer members. Alias of the DWORD accessor: the
      member is handled as a plain 32 bit value.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member as a signed 32 bit value in read mode (0 when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_POINTER32_(XppParamList pl) { _GWST_XBSETGET_DWORD_(pl); }
/*{{end-internal-function}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-internal-function}}*/
/*{{internal-function_: _gwst_xbsetget_handle_
            | syntax_: `_gwst_xbsetget_handle_( @xValue, nPCount, @pStorage, nShift, nOffset, nStorageSize, pGhost )`
            | category: structures/internal
            | _kw_: _gwst_xbsetget_handle_, Function
   }}*/
/*{{|desc: Internal GWST member accessor for Win32 handle members (HANDLE, HWND and the like). Alias of
      the DWORD accessor: the member is handled as a plain 32 bit value.
    | params:
    - `@xValue` Numeric - New member value, stored as its 32 bit value. Only used in write mode.
    - `nPCount` Numeric - Caller's PCount(); a value greater than 1 selects write mode, any other
      value selects read mode.
    - `@pStorage` Character/Numeric - Structure storage: a Character buffer holding the structure
      image or a Numeric memory address. A NIL is replaced with a new Character buffer of nStorageSize
      bytes.
    - `nShift` Numeric - Byte displacement of the structure start inside the storage.
    - `nOffset` Numeric - Byte offset of the member inside the structure.
    - `nStorageSize` Numeric - Byte size of the Character buffer created when pStorage contains NIL.
    - `pGhost` Numeric - Address of a C pointer variable; when it is not zero the member is reached
      through the pointer stored there, plus nOffset, and both pStorage and nShift are ignored.

    Returns Numeric - Member as a signed 32 bit value in read mode (0 when the member cannot be reached);
      NIL in write mode. }}*/
XPPRET XPPENTRY _GWST_XBSETGET_HANDLE_(XppParamList pl) { _GWST_XBSETGET_DWORD_(pl); }
/*{{end-internal-function}}*/
// -----------------------------------------------------------------------------------------------------------------




