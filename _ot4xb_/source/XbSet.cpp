//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
BOOL   XbSet::SetBool(LONG idx ,BOOL val)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   ContainerHandle conv = _conPutL( NULLCONTAINER  , val  );
   BOOL            res  = FALSE;
   _conCall(conr,"SET",2,coni,conv); 
   _conGetL(conr,&res);
   _conReleaseM(conr,coni,conv,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL   XbSet::SetBool(LONG idx)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   BOOL            res  = FALSE;
   _conCall(conr,"SET",1,coni); 
   _conGetL(conr,&res);
   _conReleaseM(conr,coni,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
LONG   XbSet::SetLong(LONG idx ,LONG val)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   ContainerHandle conv = _conPutNL( NULLCONTAINER  , val  );
   LONG            res  = 0;
   _conCall(conr,"SET",2,coni,conv); 
   _conGetLong(conr,&res);
   _conReleaseM(conr,coni,conv,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
LONG   XbSet::SetLong(LONG idx)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   LONG            res  = 0;
   _conCall(conr,"SET",1,coni); 
   _conGetLong(conr,&res);
   _conReleaseM(conr,coni,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
double XbSet::SetDouble(LONG idx ,double val)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   ContainerHandle conv = _conPutND( NULLCONTAINER  , val  );
   double          res  = 0;
   _conCall(conr,"SET",2,coni,conv); 
   _conGetND(conr,&res);
   _conReleaseM(conr,coni,conv,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
double XbSet::SetDouble(LONG idx)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   double          res  = 0;
   _conCall(conr,"SET",1,coni); 
   _conGetND(conr,&res);
   _conReleaseM(conr,coni,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR  XbSet::SetPsz(LONG idx,LPSTR val)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   ContainerHandle conv = _conPutC( NULLCONTAINER  , val  );
   LPSTR           res;
   _conCall(conr,"SET",2,coni,conv); 
   res = _conXStrDup(conr);
   _conReleaseM(conr,coni,conv,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR  XbSet::SetPsz(LONG idx)
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   LPSTR           res;
   _conCall(conr,"SET",1,coni); 
   res = _conXStrDup(conr);
   _conReleaseM(conr,coni,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR  XbSet::SetPszAdditive(LONG idx,LPSTR val, BOOL add )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   ContainerHandle coni = _conPutNL( NULLCONTAINER , idx  );
   ContainerHandle conv = _conPutC( NULLCONTAINER  , val  );
   ContainerHandle conl = _conPutL( NULLCONTAINER  , add  );
   LPSTR           res;
   _conCall(conr,"SET",3,coni,conv,conl); 
   res = _conXStrDup(conr);
   _conReleaseM(conr,coni,conv,conl,0);
   return res;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL   XbSet::Exact(BOOL value){return XbSet::SetBool(1,value);}
BOOL   XbSet::Exact(void){return XbSet::SetBool(1);}
BOOL   XbSet::Fixed(BOOL value){return XbSet::SetBool(2,value);}
BOOL   XbSet::Fixed(void){return XbSet::SetBool(2);}
LONG   XbSet::Decimals(LONG value){return XbSet::SetLong(3,value);}
LONG   XbSet::Decimals(void){return XbSet::SetLong(3);}
LPSTR  XbSet::DateFormat(LPSTR value){return XbSet::SetPsz(4,value);}
LPSTR  XbSet::DateFormat(void){return XbSet::SetPsz(4);}
LONG   XbSet::Epoch(LONG value){return XbSet::SetLong(5,value);}
LONG   XbSet::Epoch(void){return XbSet::SetLong(5);}
LPSTR  XbSet::Path(LPSTR value){return XbSet::SetPsz(6,value);}
LPSTR  XbSet::Path(void){return XbSet::SetPsz(6);}
LPSTR  XbSet::Default(LPSTR value){return XbSet::SetPsz(7,value);}
LPSTR  XbSet::Default(void){return XbSet::SetPsz(7);}
BOOL   XbSet::Exclusive(BOOL value){return XbSet::SetBool(8,value);}
BOOL   XbSet::Exclusive(void){return XbSet::SetBool(8);}
BOOL   XbSet::SoftSeek(BOOL value){return XbSet::SetBool(9,value);}
BOOL   XbSet::SoftSeek(void){return XbSet::SetBool(9);}
BOOL   XbSet::Unique(BOOL value){return XbSet::SetBool(10,value);}
BOOL   XbSet::Unique(void){return XbSet::SetBool(10);}
BOOL   XbSet::Deleted(BOOL value){return XbSet::SetBool(11,value);}
BOOL   XbSet::Deleted(void){return XbSet::SetBool(11);}
BOOL   XbSet::Cancel(BOOL value){return XbSet::SetBool(12,value);}
BOOL   XbSet::Cancel(void){return XbSet::SetBool(12);}
LONG   XbSet::TypeAhead(LONG value){return XbSet::SetLong(14,value);}
LONG   XbSet::TypeAhead(void){return XbSet::SetLong(14);}
LPSTR  XbSet::Color(LPSTR value){return XbSet::SetPsz(15,value);}
LPSTR  XbSet::Color(void){return XbSet::SetPsz(15);}
BOOL   XbSet::Cursor(BOOL value){return XbSet::SetBool(16,value);}
BOOL   XbSet::Cursor(void){return XbSet::SetBool(16);}
BOOL   XbSet::Console(BOOL value){return XbSet::SetBool(17,value);}
BOOL   XbSet::Console(void){return XbSet::SetBool(17);}
BOOL   XbSet::Alternate(BOOL value){return XbSet::SetBool(18,value);}
BOOL   XbSet::Alternate(void){return XbSet::SetBool(18);}
LPSTR  XbSet::AltFile(LPSTR value , BOOL bAdditive){return XbSet::SetPszAdditive(19,value,bAdditive);}
LPSTR  XbSet::AltFile(void){return XbSet::SetPsz(19);}
LPSTR  XbSet::Device(LPSTR value){return XbSet::SetPsz(20,value);}
LPSTR  XbSet::Device(void){return XbSet::SetPsz(20);}
BOOL   XbSet::Extra(BOOL value){return XbSet::SetBool(21,value);}
BOOL   XbSet::Extra(void){return XbSet::SetBool(21);}
LPSTR  XbSet::ExtraFile(LPSTR value){return XbSet::SetPsz(22,value);}
LPSTR  XbSet::ExtraFile(void){return XbSet::SetPsz(22);}
BOOL   XbSet::Printer(BOOL value){return XbSet::SetBool(23,value);}
BOOL   XbSet::Printer(void){return XbSet::SetBool(23);}
LPSTR  XbSet::PrintFile(LPSTR value, BOOL bAdditive){return XbSet::SetPszAdditive(24,value,bAdditive);}
LPSTR  XbSet::PrintFile(void){return XbSet::SetPsz(24);}
LONG   XbSet::Margin(LONG value){return XbSet::SetLong(25,value);}
LONG   XbSet::Margin(void){return XbSet::SetLong(25);}
BOOL   XbSet::Bell(BOOL value){return XbSet::SetBool(26,value);}
BOOL   XbSet::Bell(void){return XbSet::SetBool(26);}
BOOL   XbSet::Confirm(BOOL value){return XbSet::SetBool(27,value);}
BOOL   XbSet::Confirm(void){return XbSet::SetBool(27);}
BOOL   XbSet::Escape(BOOL value){return XbSet::SetBool(28,value);}
BOOL   XbSet::Escape(void){return XbSet::SetBool(28);}
BOOL   XbSet::Insert(BOOL value){return XbSet::SetBool(29,value);}
BOOL   XbSet::Insert(void){return XbSet::SetBool(29);}
BOOL   XbSet::Exit(BOOL value){return XbSet::SetBool(30,value);}
BOOL   XbSet::Exit(void){return XbSet::SetBool(30);}
BOOL   XbSet::Intensity(BOOL value){return XbSet::SetBool(31,value);}
BOOL   XbSet::Intensity(void){return XbSet::SetBool(31);}
BOOL   XbSet::ScoreBoard(BOOL value){return XbSet::SetBool(32,value);}
BOOL   XbSet::ScoreBoard(void){return XbSet::SetBool(32);}
BOOL   XbSet::Delimiters(BOOL value){return XbSet::SetBool(33,value);}
BOOL   XbSet::Delimiters(void){return XbSet::SetBool(33);}
LPSTR  XbSet::DelimChars(LPSTR value){return XbSet::SetPsz(34,value);}
LPSTR  XbSet::DelimChars(void){return XbSet::SetPsz(34);}
BOOL   XbSet::Wrap(BOOL value){return XbSet::SetBool(35,value);}
BOOL   XbSet::Wrap(void){return XbSet::SetBool(35);}
LONG   XbSet::Message(LONG value){return XbSet::SetLong(36,value);}
LONG   XbSet::Message(void){return XbSet::SetLong(36);}
BOOL   XbSet::MCenter(BOOL value){return XbSet::SetBool(37,value);}
BOOL   XbSet::MCenter(void){return XbSet::SetBool(37);}
BOOL   XbSet::Lexical(BOOL value){return XbSet::SetBool(39,value);}
BOOL   XbSet::Lexical(void){return XbSet::SetBool(39);}
BOOL   XbSet::Century(BOOL value){return XbSet::SetBool(40,value);}
BOOL   XbSet::Century(void){return XbSet::SetBool(40);}
LONG   XbSet::Collation(LONG value){return XbSet::SetLong(41,value);}
LONG   XbSet::Collation(void){return XbSet::SetLong(41);}
LPSTR  XbSet::Time(LPSTR value){return XbSet::SetPsz(42,value);}
LPSTR  XbSet::Time(void){return XbSet::SetPsz(42);}
LONG   XbSet::CharSet(LONG value){return XbSet::SetLong(43,value);}
LONG   XbSet::CharSet(void){return XbSet::SetLong(43);}
BOOL   XbSet::HandleEvent(BOOL value){return XbSet::SetBool(44,value);}
BOOL   XbSet::HandleEvent(void){return XbSet::SetBool(44);}
double XbSet::DevTimeOut(double value){return XbSet::SetDouble(45,value);}
double XbSet::DevTimeOut(void){return XbSet::SetDouble(45);}
BOOL   XbSet::Accelerators(BOOL value){return XbSet::SetBool(46,value);}
BOOL   XbSet::Accelerators(void){return XbSet::SetBool(46);}
LONG   XbSet::ColorMode(LONG value){return XbSet::SetLong(47,value);}
LONG   XbSet::ColorMode(void){return XbSet::SetLong(47);}
BOOL   XbSet::Optimize(BOOL value){return XbSet::SetBool(48,value);}
BOOL   XbSet::Optimize(void){return XbSet::SetBool(48);}
BOOL   XbSet::Rushmore(BOOL value){return XbSet::SetBool(49,value);}
BOOL   XbSet::Rushmore(void){return XbSet::SetBool(49);}
BOOL   XbSet::SmartFilter(BOOL value){return XbSet::SetBool(50,value);}
BOOL   XbSet::SmartFilter(void){return XbSet::SetBool(50);}
//----------------------------------------------------------------------------------------------------------------------

