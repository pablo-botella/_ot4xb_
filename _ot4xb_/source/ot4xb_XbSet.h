//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _APIcpp_XbSettings_h_
#define _APIcpp_XbSettings_h_
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
class OT4XB_API XbSet
{
   public:
   static BOOL   SetBool(LONG,BOOL);
   static BOOL   SetBool(LONG);
   static LONG   SetLong(LONG,LONG);
   static LONG   SetLong(LONG);
   static double SetDouble(LONG,double);
   static double SetDouble(LONG);
   static LPSTR  SetPsz(LONG,LPSTR);
   static LPSTR  SetPsz(LONG);
   static LPSTR  SetPszAdditive(LONG,LPSTR, BOOL);
   // --------------------------------------------------------------------
   static BOOL   Exact(BOOL value);
   static BOOL   Exact(void);
   static BOOL   Fixed(BOOL value);
   static BOOL   Fixed(void);
   static LONG   Decimals(LONG value);
   static LONG   Decimals(void);
   static LPSTR  DateFormat(LPSTR value);
   static LPSTR  DateFormat(void);
   static LONG   Epoch(LONG value);
   static LONG   Epoch(void);
   static LPSTR  Path(LPSTR value);
   static LPSTR  Path(void);
   static LPSTR  Default(LPSTR value);
   static LPSTR  Default(void);
   static BOOL   Exclusive(BOOL value);
   static BOOL   Exclusive(void);
   static BOOL   SoftSeek(BOOL value);
   static BOOL   SoftSeek(void);
   static BOOL   Unique(BOOL value);
   static BOOL   Unique(void);
   static BOOL   Deleted(BOOL value);
   static BOOL   Deleted(void);
   static BOOL   Cancel(BOOL value);
   static BOOL   Cancel(void);
   static LONG   TypeAhead(LONG value);
   static LONG   TypeAhead(void);
   static LPSTR  Color(LPSTR value);
   static LPSTR  Color(void);
   static BOOL   Cursor(BOOL value);
   static BOOL   Cursor(void);
   static BOOL   Console(BOOL value);
   static BOOL   Console(void);
   static BOOL   Alternate(BOOL value);
   static BOOL   Alternate(void);
   static LPSTR  AltFile(LPSTR value , BOOL bAdditive);
   static LPSTR  AltFile(void);
   static LPSTR  Device(LPSTR value);
   static LPSTR  Device(void);
   static BOOL   Extra(BOOL value);
   static BOOL   Extra(void);
   static LPSTR  ExtraFile(LPSTR value);
   static LPSTR  ExtraFile(void);
   static BOOL   Printer(BOOL value);
   static BOOL   Printer(void);
   static LPSTR  PrintFile(LPSTR value, BOOL bAdditive);
   static LPSTR  PrintFile(void);
   static LONG   Margin(LONG value);
   static LONG   Margin(void);
   static BOOL   Bell(BOOL value);
   static BOOL   Bell(void);
   static BOOL   Confirm(BOOL value);
   static BOOL   Confirm(void);
   static BOOL   Escape(BOOL value);
   static BOOL   Escape(void);
   static BOOL   Insert(BOOL value);
   static BOOL   Insert(void);
   static BOOL   Exit(BOOL value);
   static BOOL   Exit(void);
   static BOOL   Intensity(BOOL value);
   static BOOL   Intensity(void);
   static BOOL   ScoreBoard(BOOL value);
   static BOOL   ScoreBoard(void);
   static BOOL   Delimiters(BOOL value);
   static BOOL   Delimiters(void);
   static LPSTR  DelimChars(LPSTR value);
   static LPSTR  DelimChars(void);
   static BOOL   Wrap(BOOL value);
   static BOOL   Wrap(void);
   static LONG   Message(LONG value);
   static LONG   Message(void);
   static BOOL   MCenter(BOOL value);
   static BOOL   MCenter(void);
   static BOOL   Lexical(BOOL value);
   static BOOL   Lexical(void);
   static BOOL   Century(BOOL value);
   static BOOL   Century(void);
   static LONG   Collation(LONG value);
   static LONG   Collation(void);
   static LPSTR  Time(LPSTR value);
   static LPSTR  Time(void);
   static LONG   CharSet(LONG value);
   static LONG   CharSet(void);
   static BOOL   HandleEvent(BOOL value);
   static BOOL   HandleEvent(void);
   static double DevTimeOut(double value);
   static double DevTimeOut(void);
   static BOOL   Accelerators(BOOL value);
   static BOOL   Accelerators(void);
   static LONG   ColorMode(LONG value);
   static LONG   ColorMode(void);
   static BOOL   Optimize(BOOL value);
   static BOOL   Optimize(void);
   static BOOL   Rushmore(BOOL value);
   static BOOL   Rushmore(void);
   static BOOL   SmartFilter(BOOL value);
   static BOOL   SmartFilter(void);
};
//----------------------------------------------------------------------------------------------------------------------
extern "C" {
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif
//----------------------------------------------------------------------------------------------------------------------
