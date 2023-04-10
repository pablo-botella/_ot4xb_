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
static void LARGE_INTEGER_Plus(   TXbClsParams * px );
static void LARGE_INTEGER_Minus(  TXbClsParams * px );
static void LARGE_INTEGER_Mult(   TXbClsParams * px );
static void LARGE_INTEGER_Div(    TXbClsParams * px );
static void LARGE_INTEGER_Mod(  TXbClsParams * px );
static void ULARGE_INTEGER_Plus(   TXbClsParams * px );
static void ULARGE_INTEGER_Minus(  TXbClsParams * px );
static void ULARGE_INTEGER_Mult(   TXbClsParams * px );
static void ULARGE_INTEGER_Div(    TXbClsParams * px );
static void ULARGE_INTEGER_Mod(  TXbClsParams * px );
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LONGLONG2DOUBLE( XppParamList pl) // LongLong2Double( cLongLong [, @lDataLost ] ) nDouble
{
   union{ char sz[9]; LONGLONG ll; } uu;
   double nd;
   if( _parc( uu.sz , 9 , pl , 1) < 8 ) { _ret(pl); return;}
   nd = (double) uu.ll;
   _storl(!bCompareLongLongAndDouble(uu.ll,nd) ,pl,2,0);
   _retnd(pl,nd);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DOUBLE2LONGLONG( XppParamList pl) // Double2LongLong(nDouble) ->  cLongLong
{
   union{
   char sz[9];
   LONGLONG ll;
   } uu;
   uu.ll = (LONGLONG) _parnd(pl,1);
   _retclen(pl,uu.sz,8);
}
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
XPPRET XPPENTRY ULONGLONG2DOUBLE( XppParamList pl) // ULongLong2Double( cULongLong [, @lDataLost ] ) nDouble
{
   union{ char sz[9]; ULARGE_INTEGER li; } uu;
   double nd;
   if( _parc( uu.sz , 9 , pl , 1) < 8 ) { _ret(pl); return;}
   nd  = (double) ((DWORD) uu.li.HighPart);
   nd  = (nd *  4294967296.00 ) + ((double) uu.li.LowPart);
   _storl(!bCompareULongLongAndDouble(uu.li.QuadPart,nd) ,pl,2,0);
   _retnd(pl,nd);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY DOUBLE2ULONGLONG( XppParamList pl) // Double2ULongLong(nDouble) ->  cULongLong
{
   union{
   char sz[9];
   ULONGLONG ll;
   } uu;
   uu.ll = (ULONGLONG) _parnd(pl,1);
   _retclen(pl,uu.sz,8);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY GETNUMFORMAT( XppParamList pl) // GetNumFormat( @nNum ,  @nInt , @nDec ) -> nNum
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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LISNUMF64( XppParamList pl)
{
   ULONG n = _partype(pl,1);

   _retl(pl, (BOOL)( (n & XPP_NUMERIC) && (n &_xpp_DOUBLE ) ) );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY SETNUMFORMAT( XppParamList pl) // SetNumFormat( @nNum ,  nInt , nDec ) -> nNum
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
      if( nParams > 1 ) dd = _parLong(pl,2);
      if( nParams > 2 ) dd = _parLong(pl,3);
      _conPutNDF( con,nd,ii,dd );
      _conReturn( pl,con);
      if( !bByRef) _conRelease(con);
      return;
   }
   _ret(pl);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _LARGE_INTEGER_( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("_LARGE_INTEGER_");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("_LARGE_INTEGER_");
      pc->GwstParent();
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Member_DWord("LowPart");
      pc->Member_DWord("HighPart");
      pc->GwstSetOffset(0);
      pc->Member_DWord("l");
      pc->Member_DWord("h");
      pc->GwstSetOffset(0);
      pc->Member_DWord64("QuadPart");
      pc->GwstSetOffset(0);
      pc->Member_DWord64("q");
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapist_LARGE_INTEGER( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("LARGE_INTEGER");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("LARGE_INTEGER");
      pc->GwstParent("_LARGE_INTEGER_");
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Var("lPLost");
      // ---------------------------
      pc->GwstSetOffset(0); // Another union
      pc->Child("u","_LARGE_INTEGER_");
      // ---------------------------
      // pc->Property("double",LARGE_INTEGER_double,1,",@s:q");
      pc->PropertyCB("double","{|s,v|s:lPLost := .F.,"
                                   "iif( PCount() > 1,s:q := Double2LongLong(v),"
                                   "LongLong2Double( s:q , @s:lPLost))}");
      // ---------------------------
      pc->MethodCB( "init"       , "{|s,p1,p2| s:_gwst_(p1,p2) , (s:lPLost := .F.) ,s}");
      // ---------------------------
      pc->ClassMethodCB("New64","{|s,vv,o| o := s:New() , o:q := vv, o}");
      // ---------------------------
      pc->Method("Plus" ,LARGE_INTEGER_Plus      ,2,",@s:q");// ::Plus( val   ,lStore = .F.)               -> cInt64Result
      pc->Method("Minus",LARGE_INTEGER_Minus     ,2,",@s:q");// ::Minus( val  ,lStore = .F.)               -> cInt64Result
      pc->Method("Mul"  ,LARGE_INTEGER_Mult      ,2,",@s:q");// ::Mul( val    ,lStore = .F.)               -> cInt64Result
      pc->Method("Div"  ,LARGE_INTEGER_Div       ,3,",@s:q");// ::Div( divisor,lStore = .F.[, @mod] )      -> cInt64Result
      pc->Method("Mod"  ,LARGE_INTEGER_Mod       ,3,",@s:q");// ::Mod( divisor,lStore = .F.[, @DivResult] )-> cInt64Result
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
//-----------------------------------------------------------------------------------------------------------------------
// static void LARGE_INTEGER_double( TXbClsParams * px ) // 1
// {
//    _conSetLMember( px->GetSelf() ,"lPLost",FALSE);
//    if( px->PCount() > 0 )px->PutExtraQWord( 1 ,  (LONGLONG) px->GetParamDouble(1) );
//    else
//    {
//       LONGLONG q = px->GetExtraQWord(1);
//       double nd = (double) q;
//       px->PutReturnDouble( nd );
//       if( !bCompareLongLongAndDouble(q,nd) ) _conSetLMember( px->GetSelf() ,"lPLost",TRUE);
//    }
// }
//-----------------------------------------------------------------------------------------------------------------------
static void LARGE_INTEGER_Plus(   TXbClsParams * px ) // ::Plus( val    , lStore = .F. )
{
      LONGLONG q = px->GetExtraQWord(1)  +  px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , q );
      px->PutReturnQWord( q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void LARGE_INTEGER_Minus(  TXbClsParams * px ) // ::Minus( val   , lStore = .F. )
{
      LONGLONG q = px->GetExtraQWord(1)  -  px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , q );
      px->PutReturnQWord( q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void LARGE_INTEGER_Mult(   TXbClsParams * px ) // ::Mul( val     , lStore = .F. )
{
      LONGLONG q = px->GetExtraQWord(1)  *  px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , q );
      px->PutReturnQWord( q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void LARGE_INTEGER_Div(    TXbClsParams * px ) // ::Div( divisor , lStore = .F. , @mod )
{
      LONGLONG q0 =  px->GetExtraQWord(1);
      LONGLONG q1 =  px->GetParamQWord(1);
      LONGLONG q  = (LONGLONG) (q0 /  q1 );
      LONGLONG m  = q0 % q1 ;
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , q );
      px->PutParamQWord( 3 , m );
      px->PutReturnQWord( q );
}
//-----------------------------------------------------------------------------------------------------------------------
static void LARGE_INTEGER_Mod(    TXbClsParams * px ) // ::Mod( divisor , lStore = .F. , @DivResult)
{
      LONGLONG q0 =  px->GetExtraQWord(1);
      LONGLONG q1 =  px->GetParamQWord(1);
      LONGLONG q  = (LONGLONG) (q0 /  q1 );
      LONGLONG m  = q0 % q1 ;
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , m );
      px->PutParamQWord( 3 , q );
      px->PutReturnQWord( m );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY wapist_ULARGE_INTEGER( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("ULARGE_INTEGER");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("ULARGE_INTEGER");
      pc->GwstParent("_LARGE_INTEGER_");
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Var("lPLost");
      // ---------------------------
      pc->GwstSetOffset(0); // Another union
      pc->Child("u","_LARGE_INTEGER_");
      // ---------------------------
      pc->PropertyCB("double","{|s,v|s:lPLost := .F.,"
                                   "iif( PCount() > 1,s:q := Double2ULongLong(v),"
                                   "ULongLong2Double( s:q , @s:lPLost))}");
      // ---------------------------
      pc->MethodCB( "init"       , "{|s,p1,p2| s:_gwst_(p1,p2) , (s:lPLost := .F.) ,s}");
      // ---------------------------
      pc->ClassMethodCB("New64","{|s,vv,o| o := s:New() , o:q := vv, o}");
      // ---------------------------
      pc->Method("Plus" ,ULARGE_INTEGER_Plus      ,2,",@s:q");// ::Plus( val   ,lStore = .F.)               -> cInt64Result
      pc->Method("Minus",ULARGE_INTEGER_Minus     ,2,",@s:q");// ::Minus( val  ,lStore = .F.)               -> cInt64Result
      pc->Method("Mul"  ,ULARGE_INTEGER_Mult      ,2,",@s:q");// ::Mul( val    ,lStore = .F.)               -> cInt64Result
      pc->Method("Div"  ,ULARGE_INTEGER_Div       ,3,",@s:q");// ::Div( divisor,lStore = .F.[, @mod] )      -> cInt64Result
      pc->Method("Mod"  ,ULARGE_INTEGER_Mod       ,3,",@s:q");// ::Mod( divisor,lStore = .F.[, @DivResult] )-> cInt64Result
      pc->MethodCB("Str" ,  "{|s| cPrintf('%I64u',s:l,s:h)}");
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//-----------------------------------------------------------------------------------------------------------------------
static void ULARGE_INTEGER_Plus(   TXbClsParams * px ) // ::Plus( val    , lStore = .F. )
{
      ULONGLONG q = (ULONGLONG) px->GetExtraQWord(1)  +  (ULONGLONG) px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , (LONGLONG) q );
      px->PutReturnQWord( (LONGLONG) q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void ULARGE_INTEGER_Minus(  TXbClsParams * px ) // ::Minus( val   , lStore = .F. )
{
      ULONGLONG q = (ULONGLONG) px->GetExtraQWord(1)  -  (ULONGLONG) px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , (LONGLONG) q );
      px->PutReturnQWord( (LONGLONG) q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void ULARGE_INTEGER_Mult(   TXbClsParams * px ) // ::Mul( val     , lStore = .F. )
{
      ULONGLONG q = (ULONGLONG) px->GetExtraQWord(1)  *  (ULONGLONG) px->GetParamQWord(1);
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , (LONGLONG) q );
      px->PutReturnQWord( (LONGLONG) q );

}
//-----------------------------------------------------------------------------------------------------------------------
static void ULARGE_INTEGER_Div(    TXbClsParams * px ) // ::Div( divisor , lStore = .F. , @mod )
{
      ULONGLONG q0 =  (ULONGLONG) px->GetExtraQWord(1);
      ULONGLONG q1 =  (ULONGLONG) px->GetParamQWord(1);
      ULONGLONG q  = (ULONGLONG) (q0 /  q1 );
      ULONGLONG m  = q0 % q1 ;
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , (LONGLONG) q );
      px->PutParamQWord( 3 , (LONGLONG) m );
      px->PutReturnQWord( (LONGLONG) q );
}
//-----------------------------------------------------------------------------------------------------------------------
static void ULARGE_INTEGER_Mod(    TXbClsParams * px ) // ::Mod( divisor , lStore = .F. , @DivResult)
{
      ULONGLONG q0 =  (ULONGLONG) px->GetExtraQWord(1);
      ULONGLONG q1 =  (ULONGLONG) px->GetParamQWord(1);
      ULONGLONG q  = (ULONGLONG) (q0 /  q1 );
      ULONGLONG m  = q0 % q1 ;
      if( px->GetParamBool(2) ) px->PutExtraQWord( 1 , (LONGLONG) m );
      px->PutParamQWord( 3 , (LONGLONG) q );
      px->PutReturnQWord( (LONGLONG) m );
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY MAKE_QWORD( XppParamList pl )  // MAKE_QWORD( nLo32,nHi32,[@nDouble],[@lDoubleDataLost] ) -> cQWord
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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY MAKE_INT64( XppParamList pl ) // MAKE_INT64( nLo32,nHi32,[@nDouble],[@lDoubleDataLost] ) -> cQWord
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
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY LO_DWORD( XppParamList pl ) // LO_DWORD(uNum64) -> dw
{      
   union{ char sz[9]; LARGE_INTEGER li; } uu;
   ULONG np = _partype(pl,1);
   _bset( (LPBYTE) &uu , 0 , sizeof(uu) );
   if( (np & XPP_NUMERIC) && (np & _xpp_DOUBLE) )  uu.li.QuadPart = (LONGLONG) _parnd(pl,1,0);
   else if(np & XPP_NUMERIC) uu.li.LowPart = (DWORD) _parnl(pl,1,0);
   else if(np & XPP_CHARACTER) _parc( uu.sz , 9 , pl , 1);
   _retnl(pl, (LONG) uu.li.LowPart );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY HI_DWORD( XppParamList pl ) // HI_DWORD(uNum64) -> dw
{      
   union{ char sz[9]; LARGE_INTEGER li; } uu;
   ULONG np = _partype(pl,1);
   _bset( (LPBYTE) &uu , 0 , sizeof(uu) );
   if( (np & XPP_NUMERIC) && (np & _xpp_DOUBLE) )  uu.li.QuadPart = (LONGLONG) _parnd(pl,1,0);
   else if(np & XPP_NUMERIC) uu.li.LowPart = (DWORD) _parnl(pl,1,0);
   else if(np & XPP_CHARACTER) _parc( uu.sz , 9 , pl , 1);
   _retnl(pl, (LONG) uu.li.HighPart );
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY I64CMP( XppParamList pl )
{
   TXppParamList xpp(pl,2);
   LONGLONG n = xpp[1]->GetQWord() - xpp[2]->GetQWord();
   xpp[0]->PutLong( ( n == 0 ? 0 : (n > 0 ? 1 : -1) ) );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(I64SUM) // TODO: add multiple params and cast the result to the first type
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() + xpp[2]->GetQWord() );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(I64REST) // TODO: add multiple params and cast the result to the first type
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() - xpp[2]->GetQWord() );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(I64MULT) // TODO: add multiple params and cast the result to the first type
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() *  xpp[2]->GetQWord() );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(I64DIV) // TODO: add multiple params and cast the result to the first type
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() / xpp[2]->GetQWord() );
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(I64MOD) // TODO: add multiple params and cast the result to the first type
{
   TXppParamList xpp(pl,2);
   xpp[0]->PutQWord(xpp[1]->GetQWord() %  xpp[2]->GetQWord() );
}
// -----------------------------------------------------------------------------------------------------------------



