//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//----------------------------------------------------------------------------------------------------------------------
static BOOL bCompareLongLongAndDouble( LONGLONG ll , double nd);
static BOOL bCompareULongLongAndDouble( ULONGLONG ll , double nd);
//-----------------------------------------------------------------------------------------------------------------------

/*{{begin-function}}*/
/*{{function_: LongLong2Double
            | syntax_: `LongLong2Double( cLongLong [, @lDataLost] )`
            | category: numeric/64-bit
            | _kw_: int64 to double, 8-byte string, QWORD, convert
   }}*/
/*{{|desc: Converts a signed 64-bit integer stored as an 8-byte binary string to a Numeric (double) value.
    | params:
    - `cLongLong` Character - String holding the value in its first 8 bytes, little-endian.
    - `@lDataLost` Logical - Optional, by reference. Receives .T. when the double cannot represent the
      exact 64-bit value, .F. when the conversion is exact.

    Returns Numeric - The converted value, or NIL when cLongLong is not a Character value of at least 8
      bytes. }}*/
XPPRET XPPENTRY LONGLONG2DOUBLE( XppParamList pl) // LongLong2Double( cLongLong [, @lDataLost ] ) nDouble
{
   union{ char sz[9]; LONGLONG ll; } uu;
   double nd;
   if( _parc( uu.sz , 9 , pl , 1) < 8 ) { _ret(pl); return;}
   nd = (double) uu.ll;
   _storl(!bCompareLongLongAndDouble(uu.ll,nd) ,pl,2,0);
   _retnd(pl,nd);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Double2LongLong
            | syntax_: `Double2LongLong( nDouble )`
            | category: numeric/64-bit
            | _kw_: double to int64, 8-byte string, QWORD, convert
   }}*/
/*{{|desc: Converts a Numeric value to a signed 64-bit integer returned as an 8-byte binary string in
      little-endian order. The decimal part of nDouble is discarded.
    | params:
    - `nDouble` Numeric - Value to convert.

    Returns Character - 8-byte string with the signed 64-bit value. }}*/
XPPRET XPPENTRY DOUBLE2LONGLONG( XppParamList pl)
{
   union{
   char sz[9];
   LONGLONG ll;
   } uu;
   uu.ll = (LONGLONG) _parnd(pl,1);
   _retclen(pl,uu.sz,8);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
static BOOL bCompareLongLongAndDouble( LONGLONG ll , double nd)
{
  return ( ( (LONGLONG) nd ) == ll );
}
//----------------------------------------------------------------------------------------------------------------------
static BOOL bCompareULongLongAndDouble( ULONGLONG ll , double nd)
{
  return ( ( (ULONGLONG) nd ) == ll );
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ULongLong2Double
            | syntax_: `ULongLong2Double( cULongLong [, @lDataLost] )`
            | category: numeric/64-bit
            | _kw_: uint64 to double, 8-byte string, QWORD, convert
   }}*/
/*{{|desc: Converts an unsigned 64-bit integer stored as an 8-byte binary string to a Numeric (double) value.
    | params:
    - `cULongLong` Character - String holding the value in its first 8 bytes, little-endian.
    - `@lDataLost` Logical - Optional, by reference. Receives .T. when the double cannot represent the
      exact 64-bit value, .F. when the conversion is exact.

    Returns Numeric - The converted value, or NIL when cULongLong is not a Character value of at least 8
      bytes. }}*/
XPPRET XPPENTRY ULONGLONG2DOUBLE( XppParamList pl)
{
   union{ char sz[9]; ULARGE_INTEGER li; } uu;
   double nd;
   if( _parc( uu.sz , 9 , pl , 1) < 8 ) { _ret(pl); return;}
   nd  = (double) ((DWORD) uu.li.HighPart);
   nd  = (nd *  4294967296.00 ) + ((double) uu.li.LowPart);
   _storl(!bCompareULongLongAndDouble(uu.li.QuadPart,nd) ,pl,2,0);
   _retnd(pl,nd);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Double2ULongLong
            | syntax_: `Double2ULongLong( nDouble )`
            | category: numeric/64-bit
            | _kw_: double to uint64, 8-byte string, QWORD, convert
   }}*/
/*{{|desc: Converts a Numeric value to an unsigned 64-bit integer returned as an 8-byte binary string in
      little-endian order. The decimal part of nDouble is discarded.
    | params:
    - `nDouble` Numeric - Value to convert.

    Returns Character - 8-byte string with the unsigned 64-bit value. }}*/
XPPRET XPPENTRY DOUBLE2ULONGLONG( XppParamList pl)
{
   union{
   char sz[9];
   ULONGLONG ll;
   } uu;
   uu.ll = (ULONGLONG) _parnd(pl,1);
   _retclen(pl,uu.sz,8);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: GetNumFormat
            | syntax_: `GetNumFormat( @nNum, @nInt, @nDec )`
            | category: numeric/64-bit
            | _kw_: numeric format, width, decimals, internal format
   }}*/
/*{{|desc: Returns nNum and stores its internal format metadata - the width and decimals Xbase++ uses when
      the number is converted to text - into @nInt and @nDec.
    | params:
    - `@nNum` Numeric - Value to query.
    - `@nInt` Numeric - By reference. Receives the internal width.
    - `@nDec` Numeric - By reference. Receives the internal decimal count.

    Returns Numeric - nNum itself, or NIL when nNum is not a Numeric. }}*/
XPPRET XPPENTRY GETNUMFORMAT( XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl,1,&bByRef , XPP_NUMERIC );
   double nd = 0.00F;
   LONG  ii  = 0;
   LONG  dd  = 0;
   if( con != NULLCONTAINER )
   {
      _conGetNDF( con,&nd,&ii,&dd );
      _stornl(ii,pl,2,0); _stornl(dd,pl,3,0);
      _conReturn( pl,con);
      if( !bByRef) _conRelease(con);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: lIsNumF64
            | syntax_: `lIsNumF64( nValue )`
            | category: numeric/64-bit
            | _kw_: numeric type, double, LONG, 64-bit float, internal representation
   }}*/
/*{{|desc: Tells whether a value is an Xbase++ Numeric stored internally as a 64-bit double instead of a
      32-bit LONG.
    | params:
    - `nValue` Numeric - Value to test. Any non Numeric value simply returns .F.

    Returns Logical - .T. when nValue is a Numeric held as double, .F. otherwise. }}*/
XPPRET XPPENTRY LISNUMF64( XppParamList pl)
{
   ULONG n = _partype(pl,1);

   _retl(pl, (BOOL)( (n & XPP_NUMERIC) && (n &_xpp_DOUBLE ) ) );
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: SetNumFormat
            | syntax_: `SetNumFormat( @nNum [, nInt] [, nDec] )`
            | category: numeric/64-bit
            | _kw_: numeric format, width, decimals, set format
   }}*/
/*{{|desc: Changes the internal width and decimals metadata of nNum without changing its value. Pass nNum by
      reference so the new format is stored back into the variable.
    | params:
    - `@nNum` Numeric - Value to update.
    - `nInt` Numeric - Optional. New width; when omitted the current width is kept.
    - `nDec` Numeric - Optional. New decimal count; when omitted the current count is kept.

    Returns Numeric - The value with the updated format, or NIL when nNum is not a Numeric. }}*/
XPPRET XPPENTRY SETNUMFORMAT( XppParamList pl)
{
   BOOL bByRef = FALSE;
   ContainerHandle con = _conTParam( pl,1,&bByRef , XPP_NUMERIC );
   double nd = 0.00F;
   LONG  ii  = 0;
   LONG  dd  = 0;
   if( con != NULLCONTAINER )
   {
      ULONG nParams = _partype(pl,0);
      _conGetNDF( con,&nd,&ii,&dd );
      if( nParams > 1 ) ii = _parLong(pl,2);
      if( nParams > 2 ) dd = _parLong(pl,3);
      _conPutNDF( con,nd,ii,dd );
      _conReturn( pl,con);
      if( !bByRef) _conRelease(con);
      return;
   }
   _ret(pl);
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: _LARGE_INTEGER_
            | _slug_: _large_integer_
            | class-function: _LARGE_INTEGER_
            | parent: {{ilink: <class gwst> gwst}}
            | category: numeric/64-bit
            | desc: Base GWST structure class holding 8 bytes readable as two DWORD halves (::LowPart/::HighPart,
              also aliased ::l/::h) or as a single 64-bit value (::QuadPart, aliased ::q), all mapped over the same
              memory like a C union. Parent of LARGE_INTEGER and ULARGE_INTEGER.
   | _kw_: LARGE_INTEGER, 64-bit, LowPart, HighPart, QuadPart, structure
   }}*/
XPPRET XPPENTRY _LARGE_INTEGER_( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("_LARGE_INTEGER_");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("_LARGE_INTEGER_");
      pc->GwstParent();
      /*{{|:**BEGIN STRUCTURE  _LARGE_INTEGER_** }}*/
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      /*{{|member_: - MEMBER DWORD LowPart | desc_: low 32 bits }}*/
      pc->Member_DWord("LowPart");
      /*{{|member_: - MEMBER DWORD HighPart | desc_: high 32 bits }}*/
      pc->Member_DWord("HighPart");
      pc->GwstSetOffset(0);
      /*{{|member_: - MEMBER DWORD l | desc_: alias of ::LowPart (same offset) }}*/
      pc->Member_DWord("l");
      /*{{|member_: - MEMBER DWORD h | desc_: alias of ::HighPart (same offset) }}*/
      pc->Member_DWord("h");
      pc->GwstSetOffset(0);
      /*{{|member_: - MEMBER DWORD64 QuadPart | desc_: the 8 bytes as one 64-bit value }}*/
      pc->Member_DWord64("QuadPart");
      pc->GwstSetOffset(0);
      /*{{|member_: - MEMBER DWORD64 q | desc_: alias of ::QuadPart (same offset) }}*/
      pc->Member_DWord64("q");
      /*{{|:**END STRUCTURE** }}*/
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
namespace large_integer_ns
   {
   static void Plus( XppParamList pl ) //::Plus( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesInt64Result
   {
      TXppParamList xpp( pl , 4);
      __int64 r = xpp[1]->GetQWord() + xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[ 4 ]->GetBool() )
      {
         xpp[ 1 ]->PutQWord( r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( r );                          // return the int64 result
   }
   static void Minus( XppParamList pl ) //::Minus( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesInt64Result
   {
      TXppParamList xpp( pl , 4);
      __int64 r = xpp[1]->GetQWord() - xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( r );                          // return the int64 result
   }
   static void Mult( XppParamList pl ) //::Mul( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesInt64Result
   {
      TXppParamList xpp( pl , 4);
      __int64 r = xpp[1]->GetQWord() * xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( r );                          // return the int64 result
   }
   static void Div( XppParamList pl ) //::Div( 1@s:q,2@s:nError,3v,4lStore,5@mod) -> quotient
   {
      TXppParamList xpp( pl , 5);
      __int64 q0 = xpp[1]->GetQWord();
      __int64 v  = xpp[3]->GetQWord();
      if( v == 0 )                                   // STATUS_INTEGER_DIVIDE_BY_ZERO
      {
         xpp[2]->PutLong( (LONG) 0xC0000094 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      if( v == -1 && q0 == _I64_MIN )                // STATUS_INTEGER_OVERFLOW ( MIN / -1 )
      {
         xpp[2]->PutLong( (LONG) 0xC0000095 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      __int64 q = q0 / v;
      __int64 m = q0 % v;
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( q ); // lStore -> write quotient back into @s:q
      }
      xpp[5]->PutQWord( m );                          // @mod = remainder
      xpp[0]->PutQWord( q );                          // return the quotient
   }
   static void Mod( XppParamList pl ) //::Mod( 1@s:q,2@s:nError,3v,4lStore,5@divresult) -> remainder
   {
      TXppParamList xpp( pl , 5);
      __int64 q0 = xpp[1]->GetQWord();
      __int64 v  = xpp[3]->GetQWord();
      if( v == 0 )                                   // STATUS_INTEGER_DIVIDE_BY_ZERO
      {
         xpp[2]->PutLong( (LONG) 0xC0000094 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      if( v == -1 && q0 == _I64_MIN )                // MIN % -1 uses the same IDIV -> also overflows
      {
         xpp[2]->PutLong( (LONG) 0xC0000095 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      __int64 q = q0 / v;
      __int64 m = q0 % v;
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( m ); // lStore -> write remainder back into @s:q
      }
      xpp[5]->PutQWord( q );                          // @divresult = quotient
      xpp[0]->PutQWord( m );                          // return the remainder
   }
}
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: LARGE_INTEGER
            | _slug_: large_integer
            | class-function: LARGE_INTEGER
            | parent: {{ilink: <slug _large_integer_> _LARGE_INTEGER_}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi signed LARGE_INTEGER structure. Inherits the _LARGE_INTEGER_ members and
              adds signed 64-bit arithmetic methods (::Plus, ::Minus, ::Mul, ::Div, ::Mod), a ::double property that
              converts ::q to and from Numeric, decimal text output with ::Str(), and the ::New64 class method. The
              ::nError var and the read-only flags ::lPLost, ::lDivByZero, ::lOverflow and ::lError report precision
              loss and arithmetic errors.
   | _kw_: LARGE_INTEGER, signed 64-bit, QuadPart, structure
   }}*/
XPPRET XPPENTRY wapist_LARGE_INTEGER( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("LARGE_INTEGER");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("LARGE_INTEGER");
      pc->GwstParent("_LARGE_INTEGER_");
      /*{{|:**BEGIN STRUCTURE  LARGE_INTEGER  FROM _LARGE_INTEGER_ ** }}*/
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      /*{{|ivar_: - VAR nError
               | desc_: Status code of the last arithmetic method or ::double access, kept as a plain instance
                 variable outside the 8-byte structure: 0 on success, 0xC000008F when a ::double read loses
                 precision, 0xC0000094 on division by zero and 0xC0000095 on overflow (see the ::lXxx flags).
      }}*/
      pc->Var("nError");
      // ---------------------------
      pc->GwstSetOffset(0); // Another union
      /*{{|member_: - MEMBER @ {{ilink: <slug _large_integer_> _LARGE_INTEGER_}} u
               | desc_: Child _LARGE_INTEGER_ view mapped over the same 8 bytes, like the u union member of the
                 WinApi structure.
      }}*/
      pc->Child("u","_LARGE_INTEGER_");
      // ---------------------------
      // pc->Property("double",LARGE_INTEGER_double,1,",@s:q");
      /*{{|property_: - PROPERTY double
               | type: Numeric
               | desc_: Read/write. Reading returns LongLong2Double( ::q ) and flags precision loss through
                 ::nError and ::lPLost; assigning stores Double2LongLong( value ) into ::q. Each access first
                 resets ::nError to 0.
      }}*/
      pc->PropertyCB("double","{|s,v,l,nd|s:nError := 0,"
                                "iif( v != NIL,"
                                      "s:q := Double2LongLong(v),"
                                      "( nd := LongLong2Double(s:q,@l), iif(l,,s:nError := 0xC000008F,0) ,nd)"
                                 ")}");




      // ---------------------------
      /*{{|method_: - METHOD new( [oParent] [, nShift] )
               | return: Self
               | desc_: Initializes the object through the GWST ::_gwst_() initializer, so the structure can stand
                 alone or map a parent structure's storage at byte offset nShift, and starts ::nError at 0.
      }}*/
      pc->MethodCB( "init"       , "{|s,p1,p2| s:_gwst_(p1,p2) , (s:nError := 0) ,s}");
      // ---------------------------
      /*{{|class-method_: - CLASS METHOD New64( vValue )
               | return: Object
               | desc_: Creates a new instance and stores vValue into ::q; vValue accepts the same forms as an
                 assignment to ::q: an 8-byte Character string, a Numeric, a { nLow, nHigh } array or an Object
                 exposing a Q member.
      }}*/
      pc->ClassMethodCB("New64","{|s,vv,o| o := s:New() , o:q := vv, o}");
      // ---------------------------
      /*{{|property_: - PROPERTY lPLost
               | type: Logical
               | desc_: Read-only. .T. when ::nError is 0xC000008F, the code left by a ::double read that lost
                 precision.
      }}*/
      pc->ROPropertyCB( "lPLost"    , "{|s,v|  !lAnd( nXor( s:nError , 0xC000008F))  }" );
      /*{{|property_: - PROPERTY lDivByZero
               | type: Logical
               | desc_: Read-only. .T. when ::nError is 0xC0000094, the code left by ::Div() or ::Mod() on a zero
                 divisor.
      }}*/
      pc->ROPropertyCB( "lDivByZero", "{|s| !lAnd( nXor( s:nError , 0xC0000094))  }" );
      /*{{|property_: - PROPERTY lOverflow
               | type: Logical
               | desc_: Read-only. .T. when ::nError is 0xC0000095, the code left by ::Div() or ::Mod() when the
                 most negative value is divided by -1.
      }}*/
      pc->ROPropertyCB( "lOverflow" , "{|s| !lAnd( nXor( s:nError , 0xC0000095))  }" );
      /*{{|property_: - PROPERTY lError
               | type: Logical
               | desc_: Read-only. .T. when ::nError holds any nonzero code.
      }}*/
      pc->ROPropertyCB( "lError"    , "{|s|  lAnd( s:nError )  }" );
      // pc->Method("Plus" ,LARGE_INTEGER_Plus      ,2,",@s:q");// ::Plus( val   ,lStore = .F.)               -> cInt64Result
      /*{{|method_: - METHOD Plus( vValue [, lStore] )
               | return: cInt64
               | desc_: Adds vValue to ::q with signed 64-bit arithmetic and returns the result as an 8-byte
                 binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Plus"  , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::large_integer_ns::Plus );
      /*{{|method_: - METHOD Minus( vValue [, lStore] )
               | return: cInt64
               | desc_: Subtracts vValue from ::q with signed 64-bit arithmetic and returns the result as an
                 8-byte binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Minus" , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::large_integer_ns::Minus );
      /*{{|method_: - METHOD Mul( vValue [, lStore] )
               | return: cInt64
               | desc_: Multiplies ::q by vValue with signed 64-bit arithmetic and returns the result as an
                 8-byte binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Mul"   , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::large_integer_ns::Mult );
      /*{{|method_: - METHOD Div( vValue [, lStore] [, @cMod] )
               | return: cInt64
               | desc_: Divides ::q by vValue with signed 64-bit arithmetic and returns the quotient as an 8-byte
                 binary string; @cMod receives the remainder. On a zero divisor ::nError becomes 0xC0000094, on
                 the most negative value divided by -1 it becomes 0xC0000095, and both results are 0; otherwise
                 ::nError is set to 0. With lStore .T. the quotient also replaces ::q.
      }}*/
      pc->Method_cbbs( "Div"   , "{|s,v,lStore,mod| XbFpCall(%i,@s:q ,@s:nError,v,lStore,@mod)}", ::large_integer_ns::Div);
      /*{{|method_: - METHOD Mod( vValue [, lStore] [, @cDiv] )
               | return: cInt64
               | desc_: Divides ::q by vValue with signed 64-bit arithmetic and returns the remainder as an
                 8-byte binary string; @cDiv receives the quotient. On a zero divisor ::nError becomes
                 0xC0000094, on the most negative value divided by -1 it becomes 0xC0000095, and both results
                 are 0; otherwise ::nError is set to 0. With lStore .T. the remainder also replaces ::q.
      }}*/
      pc->Method_cbbs( "Mod"   , "{|s,v,lStore,divresult| XbFpCall(%i,@s:q ,@s:nError,v,lStore,@divresult)}", ::large_integer_ns::Mod );
      /*{{|method_: - METHOD Str() | return: Character | desc_: Returns ::q as signed decimal text. }}*/
      /*{{|:**END STRUCTURE** }}*/
      pc->MethodCB("Str" ,  "{|s| cPrintf('%I64i',s:l,s:h)}");
      // pc->Method("SetDateTime"  ,LARGE_INTEGER_DateTime ,3,",@s:q");// ::SetDateTime(d,h,m,s,m divisor,lStore = .F.[, @DivResult] )-> cInt64Result
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
namespace ularge_integer_ns
   {
   static void Plus( XppParamList pl ) //::Plus( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesUInt64Result
   {
      TXppParamList xpp( pl , 4);
      ULONGLONG r = (ULONGLONG) xpp[1]->GetQWord() + (ULONGLONG) xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( (LONGLONG) r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( (LONGLONG) r );               // return the uint64 result
   }
   static void Minus( XppParamList pl ) //::Minus( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesUInt64Result
   {
      TXppParamList xpp( pl , 4);
      ULONGLONG r = (ULONGLONG) xpp[1]->GetQWord() - (ULONGLONG) xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( (LONGLONG) r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( (LONGLONG) r );               // return the uint64 result
   }
   static void Mult( XppParamList pl ) //::Mul( 1@s:q,2@s:nError,3v,4lStore) -> c8BytesUInt64Result
   {
      TXppParamList xpp( pl , 4);
      ULONGLONG r = (ULONGLONG) xpp[1]->GetQWord() * (ULONGLONG) xpp[3]->GetQWord();
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( (LONGLONG) r ); // lStore -> write result back into @s:q
      }
      xpp[0]->PutQWord( (LONGLONG) r );               // return the uint64 result
   }
   static void Div( XppParamList pl ) //::Div( 1@s:q,2@s:nError,3v,4lStore,5@mod) -> quotient
   {
      TXppParamList xpp( pl , 5);
      ULONGLONG q0 = (ULONGLONG) xpp[1]->GetQWord();
      ULONGLONG v  = (ULONGLONG) xpp[3]->GetQWord();
      if( v == 0 )                                   // STATUS_INTEGER_DIVIDE_BY_ZERO
      {
         xpp[2]->PutLong( (LONG) 0xC0000094 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      ULONGLONG q = q0 / v;
      ULONGLONG m = q0 % v;
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( (LONGLONG) q ); // lStore -> write quotient back into @s:q
      }
      xpp[5]->PutQWord( (LONGLONG) m );               // @mod = remainder
      xpp[0]->PutQWord( (LONGLONG) q );               // return the quotient
   }
   static void Mod( XppParamList pl ) //::Mod( 1@s:q,2@s:nError,3v,4lStore,5@divresult) -> remainder
   {
      TXppParamList xpp( pl , 5);
      ULONGLONG q0 = (ULONGLONG) xpp[1]->GetQWord();
      ULONGLONG v  = (ULONGLONG) xpp[3]->GetQWord();
      if( v == 0 )                                   // STATUS_INTEGER_DIVIDE_BY_ZERO
      {
         xpp[2]->PutLong( (LONG) 0xC0000094 );
         xpp[5]->PutQWord( 0 );
         xpp[0]->PutQWord( 0 );
         return;
      }
      ULONGLONG q = q0 / v;
      ULONGLONG m = q0 % v;
      xpp[2]->PutLong( 0 );                          // no error
      if( xpp[4]->GetBool() )
      {
         xpp[1]->PutQWord( (LONGLONG) m ); // lStore -> write remainder back into @s:q
      }
      xpp[5]->PutQWord( (LONGLONG) q );               // @divresult = quotient
      xpp[0]->PutQWord( (LONGLONG) m );               // return the remainder
   }
}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: ULARGE_INTEGER
            | _slug_: ularge_integer
            | class-function: ULARGE_INTEGER
            | parent: {{ilink: <slug _large_integer_> _LARGE_INTEGER_}}
            | category: winapi/structures
            | desc: Wrapper over the WinApi unsigned ULARGE_INTEGER structure. Same layout and interface as
              LARGE_INTEGER but the arithmetic methods, the ::double property and ::Str() treat the 8 bytes as an
              unsigned 64-bit value. There is no ::lOverflow flag; ::nError, ::lPLost, ::lDivByZero and ::lError are
              available.
   | _kw_: ULARGE_INTEGER, unsigned 64-bit, QuadPart, structure
   }}*/
XPPRET XPPENTRY wapist_ULARGE_INTEGER( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("ULARGE_INTEGER");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("ULARGE_INTEGER");
      pc->GwstParent("_LARGE_INTEGER_");
      /*{{|:**BEGIN STRUCTURE  ULARGE_INTEGER  FROM _LARGE_INTEGER_ ** }}*/
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      /*{{|ivar_: - VAR nError
               | desc_: Status code of the last arithmetic method or ::double access, kept as a plain instance
                 variable outside the 8-byte structure: 0 on success, 0xC000008F when a ::double read loses
                 precision and 0xC0000094 on division by zero (see the ::lXxx flags).
      }}*/
      pc->Var("nError");
      // ---------------------------
      pc->GwstSetOffset(0); // Another union
      /*{{|member_: - MEMBER @ {{ilink: <slug _large_integer_> _LARGE_INTEGER_}} u
               | desc_: Child _LARGE_INTEGER_ view mapped over the same 8 bytes, like the u union member of the
                 WinApi structure.
      }}*/
      pc->Child("u","_LARGE_INTEGER_");
      // ---------------------------
      /*{{|property_: - PROPERTY double
               | type: Numeric
               | desc_: Read/write. Reading returns ULongLong2Double( ::q ) and flags precision loss through
                 ::nError and ::lPLost; assigning stores Double2ULongLong( value ) into ::q. Each access first
                 resets ::nError to 0.
      }}*/
      pc->PropertyCB("double","{|s,v,l,nd|s:nError := 0,"
                                "iif( v != NIL,"
                                      "s:q := Double2ULongLong(v),"
                                      "( nd := ULongLong2Double(s:q,@l), iif(l,,s:nError := 0xC000008F,0) ,nd)"
                                 ")}");
      // ---------------------------
      /*{{|method_: - METHOD new( [oParent] [, nShift] )
               | return: Self
               | desc_: Initializes the object through the GWST ::_gwst_() initializer, so the structure can stand
                 alone or map a parent structure's storage at byte offset nShift, and starts ::nError at 0.
      }}*/
      pc->MethodCB( "init"       , "{|s,p1,p2| s:_gwst_(p1,p2) , (s:nError := 0) ,s}");
      // ---------------------------
      /*{{|class-method_: - CLASS METHOD New64( vValue )
               | return: Object
               | desc_: Creates a new instance and stores vValue into ::q; vValue accepts the same forms as an
                 assignment to ::q: an 8-byte Character string, a Numeric, a { nLow, nHigh } array or an Object
                 exposing a Q member.
      }}*/
      pc->ClassMethodCB("New64","{|s,vv,o| o := s:New() , o:q := vv, o}");
      // ---------------------------
      /*{{|property_: - PROPERTY lPLost
               | type: Logical
               | desc_: Read-only. .T. when ::nError is 0xC000008F, the code left by a ::double read that lost
                 precision.
      }}*/
      pc->ROPropertyCB( "lPLost"    , "{|s| !lAnd( nXor( s:nError , 0xC000008F))  }" );
      /*{{|property_: - PROPERTY lDivByZero
               | type: Logical
               | desc_: Read-only. .T. when ::nError is 0xC0000094, the code left by ::Div() or ::Mod() on a zero
                 divisor.
      }}*/
      pc->ROPropertyCB( "lDivByZero", "{|s| !lAnd( nXor( s:nError , 0xC0000094))  }" );
      /*{{|property_: - PROPERTY lError
               | type: Logical
               | desc_: Read-only. .T. when ::nError holds any nonzero code.
      }}*/
      pc->ROPropertyCB( "lError"    , "{|s|  lAnd( s:nError )  }" );
      /*{{|method_: - METHOD Plus( vValue [, lStore] )
               | return: cUInt64
               | desc_: Adds vValue to ::q with unsigned 64-bit arithmetic and returns the result as an 8-byte
                 binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Plus"  , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::ularge_integer_ns::Plus );
      /*{{|method_: - METHOD Minus( vValue [, lStore] )
               | return: cUInt64
               | desc_: Subtracts vValue from ::q with unsigned 64-bit arithmetic and returns the result as an
                 8-byte binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Minus" , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::ularge_integer_ns::Minus );
      /*{{|method_: - METHOD Mul( vValue [, lStore] )
               | return: cUInt64
               | desc_: Multiplies ::q by vValue with unsigned 64-bit arithmetic and returns the result as an
                 8-byte binary string; ::nError is set to 0. With lStore .T. the result also replaces ::q.
      }}*/
      pc->Method_cbbs( "Mul"   , "{|s,v,lStore| XbFpCall(%i,@s:q ,@s:nError,v,lStore)}", ::ularge_integer_ns::Mult );
      /*{{|method_: - METHOD Div( vValue [, lStore] [, @cMod] )
               | return: cUInt64
               | desc_: Divides ::q by vValue with unsigned 64-bit arithmetic and returns the quotient as an
                 8-byte binary string; @cMod receives the remainder. On a zero divisor ::nError becomes
                 0xC0000094 and both results are 0; otherwise ::nError is set to 0. With lStore .T. the quotient
                 also replaces ::q.
      }}*/
      pc->Method_cbbs( "Div"   , "{|s,v,lStore,mod| XbFpCall(%i,@s:q ,@s:nError,v,lStore,@mod)}", ::ularge_integer_ns::Div);
      /*{{|method_: - METHOD Mod( vValue [, lStore] [, @cDiv] )
               | return: cUInt64
               | desc_: Divides ::q by vValue with unsigned 64-bit arithmetic and returns the remainder as an
                 8-byte binary string; @cDiv receives the quotient. On a zero divisor ::nError becomes
                 0xC0000094 and both results are 0; otherwise ::nError is set to 0. With lStore .T. the
                 remainder also replaces ::q.
      }}*/
      pc->Method_cbbs( "Mod"   , "{|s,v,lStore,divresult| XbFpCall(%i,@s:q ,@s:nError,v,lStore,@divresult)}", ::ularge_integer_ns::Mod );
      /*{{|method_: - METHOD Str() | return: Character | desc_: Returns ::q as unsigned decimal text. }}*/
      /*{{|:**END STRUCTURE** }}*/
      pc->MethodCB("Str" ,  "{|s| cPrintf('%I64u',s:l,s:h)}");
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
/*{{end-class}}*/
//-----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Make_QWord
            | syntax_: `Make_QWord( nLo32, nHi32 [, @nDouble] [, @lDataLost] )`
            | category: numeric/64-bit
            | _kw_: make 64-bit, two DWORDs, QWORD, low high
   }}*/
/*{{|desc: Builds an unsigned 64-bit value from two 32-bit halves and returns it as an 8-byte binary string
      in little-endian order.
    | params:
    - `nLo32` Numeric - Low 32 bits.
    - `nHi32` Numeric - High 32 bits.
    - `@nDouble` Numeric - Optional, by reference. Receives the same value converted to double, reading
      the 8 bytes as unsigned.
    - `@lDataLost` Logical - Optional, by reference. Receives .T. when the double conversion loses
      precision, .F. when it is exact.

    Returns Character - 8-byte string with the unsigned 64-bit value. }}*/
XPPRET XPPENTRY MAKE_QWORD( XppParamList pl )
{      
   ULONG np = _partype(pl,0);
   union{ char sz[9]; ULARGE_INTEGER li; } uu;
   uu.li.LowPart   = (DWORD) _parLong(pl,1);
   uu.li.HighPart  = (DWORD) _parLong(pl,2);
   if( np > 2 )
   {
      double nd = (double) ((DWORD) uu.li.HighPart);
      nd  = (nd *  4294967296.00 ) + ((double) uu.li.LowPart);
      if( np  > 3 ) _storl(!bCompareULongLongAndDouble(uu.li.QuadPart,nd) ,pl,4,0);
      _stornd(nd,pl,3,0);
   }
   _retclen(pl,uu.sz,8);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Make_Int64
            | syntax_: `Make_Int64( nLo32, nHi32 [, @nDouble] [, @lDataLost] )`
            | category: numeric/64-bit
            | _kw_: make 64-bit, two DWORDs, int64, low high
   }}*/
/*{{|desc: Builds a signed 64-bit value from two 32-bit halves and returns it as an 8-byte binary string in
      little-endian order.
    | params:
    - `nLo32` Numeric - Low 32 bits.
    - `nHi32` Numeric - High 32 bits; its sign becomes the sign of the result.
    - `@nDouble` Numeric - Optional, by reference. Receives the same value converted to double, reading
      the 8 bytes as signed.
    - `@lDataLost` Logical - Optional, by reference. Receives .T. when the double conversion loses
      precision, .F. when it is exact.

    Returns Character - 8-byte string with the signed 64-bit value. }}*/
XPPRET XPPENTRY MAKE_INT64( XppParamList pl )
{      
   ULONG np = _partype(pl,0);
   union{ char sz[9]; LARGE_INTEGER li; } uu;
   uu.li.LowPart   = (DWORD) _parLong(pl,1);
   uu.li.HighPart  = _parLong(pl,2);
   if( np > 2 )
   {
      double nd = (double) uu.li.QuadPart;
      if( np  > 3 ) _storl(!bCompareLongLongAndDouble(uu.li.QuadPart,nd) ,pl,4,0);
      _stornd(nd,pl,3,0);
   }
   _retclen(pl,uu.sz,8);
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Lo_DWord
            | syntax_: `Lo_DWord( xInt64 )`
            | category: numeric/64-bit
            | _kw_: low DWORD, 64-bit, low 32 bits
   }}*/
/*{{|desc: Returns the low 32 bits of a 64-bit value.
    | params:
    - `xInt64` Character or Numeric - 8-byte binary string (shorter strings are padded with zero bytes),
      a Numeric double (converted to a signed 64-bit integer) or a 32-bit Numeric (taken as the low part).
      Any other type gives 0.

    Returns Numeric - The low DWORD as a signed 32-bit value; when bit 31 is set it appears negative. }}*/
XPPRET XPPENTRY LO_DWORD( XppParamList pl )
{      
   union{ char sz[9]; LARGE_INTEGER li; } uu;
   ULONG np = _partype(pl,1);
   _bset( (LPBYTE) &uu , 0 , sizeof(uu) );
   if( (np & XPP_NUMERIC) && (np & _xpp_DOUBLE) )  uu.li.QuadPart = (LONGLONG) _parnd(pl,1,0);
   else if(np & XPP_NUMERIC) uu.li.LowPart = (DWORD) _parnl(pl,1,0);
   else if(np & XPP_CHARACTER) _parc( uu.sz , 9 , pl , 1);
   _retnl(pl, (LONG) uu.li.LowPart );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: Hi_DWord
            | syntax_: `Hi_DWord( xInt64 )`
            | category: numeric/64-bit
            | _kw_: high DWORD, 64-bit, high 32 bits
   }}*/
/*{{|desc: Returns the high 32 bits of a 64-bit value.
    | params:
    - `xInt64` Character or Numeric - 8-byte binary string (shorter strings are padded with zero bytes),
      a Numeric double (converted to a signed 64-bit integer) or a 32-bit Numeric (whose high part is 0).
      Any other type gives 0.

    Returns Numeric - The high DWORD as a signed 32-bit value; when bit 31 is set it appears negative. }}*/
XPPRET XPPENTRY HI_DWORD( XppParamList pl )
{      
   union{ char sz[9]; LARGE_INTEGER li; } uu;
   ULONG np = _partype(pl,1);
   _bset( (LPBYTE) &uu , 0 , sizeof(uu) );
   if( (np & XPP_NUMERIC) && (np & _xpp_DOUBLE) )  uu.li.QuadPart = (LONGLONG) _parnd(pl,1,0);
   else if(np & XPP_NUMERIC) uu.li.LowPart = (DWORD) _parnl(pl,1,0);
   else if(np & XPP_CHARACTER) _parc( uu.sz , 9 , pl , 1);
   _retnl(pl, (LONG) uu.li.HighPart );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64cmp
            | syntax_: `i64cmp( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: compare int64, signed 64-bit, QWORD
   }}*/
/*{{|desc: Compares two OT4XB QWord-convertible values as SIGNED 64-bit integers.
    | params:
    - `xLeft` Character/Numeric/Array/Object - First value. A QWord-convertible value is an 8-byte
      binary string, a Numeric, a 2-element Array with {nLo32, nHi32} or an Object with a :q member (like
      LARGE_INTEGER); anything else counts as 0.
    - `xRight` Character/Numeric/Array/Object - Second value, same accepted types.

    Returns Numeric - -1 when xLeft is less than xRight, 0 when both are equal, 1 when xLeft is greater. }}*/
XPPRET XPPENTRY I64CMP( XppParamList pl )
{
   TXppParamList xpp(pl,2);
   LONGLONG a = xpp[1]->GetQWord();
   LONGLONG b = xpp[2]->GetQWord();
   xpp[0]->PutLong( a == b ? 0 : ( a > b ? 1 : -1 ) );   // direct compare (a - b could overflow)
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64sum
            | syntax_: `i64sum( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: add int64, signed 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Adds two OT4XB QWord-convertible values as 64-bit integers.
    | params:
    - `xLeft` Character/Numeric/Array/Object - First addend: an 8-byte binary string, a Numeric, a
      {nLo32, nHi32} Array or an Object with a :q member.
    - `xRight` Character/Numeric/Array/Object - Second addend, same accepted types.

    Returns Character - 8-byte binary string with the 64-bit sum. }}*/
_XPP_REG_FUN_(I64SUM)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() + xpp[2]->GetQWord() );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64minus
            | syntax_: `i64minus( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: subtract int64, signed 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Subtracts xRight from xLeft as 64-bit integers.
    | params:
    - `xLeft` Character/Numeric/Array/Object - Value to subtract from: an 8-byte binary string, a
      Numeric, a {nLo32, nHi32} Array or an Object with a :q member.
    - `xRight` Character/Numeric/Array/Object - Value to subtract, same accepted types.

    Returns Character - 8-byte binary string with the 64-bit difference. }}*/
_XPP_REG_FUN_(I64MINUS)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() - xpp[2]->GetQWord() );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64rest
            | syntax_: `i64rest()`
            | category: numeric/64-bit
            | _kw_: subtract int64, alias, QWORD arithmetic
   }}*/
/*{{|desc: Compatibility alias of i64minus(). Subtracts xRight from xLeft. }}*/
_XPP_REG_FUN_(I64REST)
{
   I64MINUS( pl );   // compat alias -> i64minus
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64mult
            | syntax_: `i64mult( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: multiply int64, signed 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Multiplies two OT4XB QWord-convertible values as 64-bit integers.
    | params:
    - `xLeft` Character/Numeric/Array/Object - First factor: an 8-byte binary string, a Numeric, a
      {nLo32, nHi32} Array or an Object with a :q member.
    - `xRight` Character/Numeric/Array/Object - Second factor, same accepted types.

    Returns Character - 8-byte binary string with the low 64 bits of the product. }}*/
_XPP_REG_FUN_(I64MULT)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() *  xpp[2]->GetQWord() );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64div
            | syntax_: `i64div( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: divide int64, signed 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Signed 64-bit integer division of xLeft by xRight.
    | params:
    - `xLeft` Character/Numeric/Array/Object - Dividend: an 8-byte binary string, a Numeric, a
      {nLo32, nHi32} Array or an Object with a :q member.
    - `xRight` Character/Numeric/Array/Object - Divisor, same accepted types.

    Returns Character - 8-byte binary string with the quotient, or NIL when the divisor is 0 and also for
      the overflow case (the minimum 64-bit value divided by -1). }}*/
_XPP_REG_FUN_(I64DIV)
{
   TXppParamList xpp(pl,2);
   LONGLONG a = xpp[1]->GetQWord();
   LONGLONG b = xpp[2]->GetQWord();
   if( b == 0 || ( b == -1 && a == _I64_MIN ) )
   {
      return;   // divide by zero / MIN/-1 overflow -> NIL
   }
   xpp[0]->PutQWord( a / b );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: i64mod
            | syntax_: `i64mod( xLeft, xRight )`
            | category: numeric/64-bit
            | _kw_: modulo int64, remainder, signed 64-bit
   }}*/
/*{{|desc: Signed 64-bit integer remainder of xLeft divided by xRight.
    | params:
    - `xLeft` Character/Numeric/Array/Object - Dividend: an 8-byte binary string, a Numeric, a
      {nLo32, nHi32} Array or an Object with a :q member.
    - `xRight` Character/Numeric/Array/Object - Divisor, same accepted types.

    Returns Character - 8-byte binary string with the remainder, or NIL when the divisor is 0 and also for
      the overflow case (the minimum 64-bit value divided by -1). }}*/
_XPP_REG_FUN_(I64MOD)
{
   TXppParamList xpp(pl,2);
   LONGLONG a = xpp[1]->GetQWord();
   LONGLONG b = xpp[2]->GetQWord();
   if( b == 0 || ( b == -1 && a == _I64_MIN ) )
   {
      return;   // divide by zero / MIN/-1 overflow -> NIL
   }
   xpp[0]->PutQWord( a % b );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64cmp
            | syntax_: `u64cmp()`
            | category: numeric/64-bit
            | _kw_: compare uint64, unsigned 64-bit, QWORD
   }}*/
/*{{|desc: Compares two OT4XB QWord-convertible values as UNSIGNED and returns -1, 0 or 1. }}*/
_XPP_REG_FUN_(U64CMP)
{
   TXppParamList xpp(pl,2);
   ULONGLONG a = (ULONGLONG) xpp[1]->GetQWord();
   ULONGLONG b = (ULONGLONG) xpp[2]->GetQWord();
   xpp[0]->PutLong( a == b ? 0 : ( a > b ? 1 : -1 ) );   // unsigned compare
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64sum
            | syntax_: `u64sum()`
            | category: numeric/64-bit
            | _kw_: add uint64, unsigned 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Adds two OT4XB QWord-convertible values (unsigned). }}*/
_XPP_REG_FUN_(U64SUM)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord( (LONGLONG) ( (ULONGLONG) xpp[1]->GetQWord() + (ULONGLONG) xpp[2]->GetQWord() ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64minus
            | syntax_: `u64minus()`
            | category: numeric/64-bit
            | _kw_: subtract uint64, unsigned 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Subtracts xRight from xLeft (unsigned). }}*/
_XPP_REG_FUN_(U64MINUS)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord( (LONGLONG) ( (ULONGLONG) xpp[1]->GetQWord() - (ULONGLONG) xpp[2]->GetQWord() ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64rest
            | syntax_: `u64rest()`
            | category: numeric/64-bit
            | _kw_: subtract uint64, alias, QWORD arithmetic
   }}*/
/*{{|desc: Compatibility alias of u64minus(). Subtracts xRight from xLeft (unsigned). }}*/
_XPP_REG_FUN_(U64REST)
{
   U64MINUS( pl );   // compat alias -> u64minus
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64mult
            | syntax_: `u64mult()`
            | category: numeric/64-bit
            | _kw_: multiply uint64, unsigned 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Multiplies two OT4XB QWord-convertible values (unsigned). }}*/
_XPP_REG_FUN_(U64MULT)
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord( (LONGLONG) ( (ULONGLONG) xpp[1]->GetQWord() * (ULONGLONG) xpp[2]->GetQWord() ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64div
            | syntax_: `u64div()`
            | category: numeric/64-bit
            | _kw_: divide uint64, unsigned 64-bit, QWORD arithmetic
   }}*/
/*{{|desc: Unsigned integer division of xLeft by xRight; returns NIL on a zero divisor. }}*/
_XPP_REG_FUN_(U64DIV)
{
   TXppParamList xpp(pl,2);
   ULONGLONG a = (ULONGLONG) xpp[1]->GetQWord();
   ULONGLONG b = (ULONGLONG) xpp[2]->GetQWord();
   if( b == 0 )
   {
      return;   // divide by zero -> NIL
   }
   xpp[0]->PutQWord( (LONGLONG) ( a / b ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: u64mod
            | syntax_: `u64mod()`
            | category: numeric/64-bit
            | _kw_: modulo uint64, remainder, unsigned 64-bit
   }}*/
/*{{|desc: Unsigned integer remainder of xLeft divided by xRight; returns NIL on a zero divisor. }}*/
_XPP_REG_FUN_(U64MOD)
{
   TXppParamList xpp(pl,2);
   ULONGLONG a = (ULONGLONG) xpp[1]->GetQWord();
   ULONGLONG b = (ULONGLONG) xpp[2]->GetQWord();
   if( b == 0 )
   {
      return;   // divide by zero -> NIL
   }
   xpp[0]->PutQWord( (LONGLONG) ( a % b ) );
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------



