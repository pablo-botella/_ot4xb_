//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#ifndef _APIcpp_XbSettings_h_
#define _APIcpp_XbSettings_h_
#ifdef __cplusplus
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-cpp-class}}*/
/*{{cpp-class_: XbSet
   | category: c-api/classes , ot4xb-api
   | desc: The Xbase++ Set() function from C++: static methods only, each one calling Set() through the
     container API with the _SET_* index of the setting. The generic forms take the index and a value of the
     right C type; the named forms (Exact, Decimals, DateFormat, Epoch, Path, Century, Collation, ...) cover
     every setting of set.ch, one overload to read the current value and one to change it, which returns
     the previous value as Set() does. A string comes back as a copy in the ot4xb heap: free it with _xfree.
   | note: Set() is executed by the calling thread, so the value read or written is the one of the current
     Xbase++ thread.
   | _kw_: XbSet, Class }}*/
class OT4XB_API XbSet
{
   public:
   /*{{|method_: `static BOOL SetBool( LONG idx, BOOL value )` | desc_: Set( idx, value ) for a Logical
      setting; returns the previous value. }}*/
   static BOOL   SetBool(LONG,BOOL);
   /*{{|method_: `static BOOL SetBool( LONG idx )` | desc_: Set( idx ) for a Logical setting. }}*/
   static BOOL   SetBool(LONG);
   /*{{|method_: `static LONG SetLong( LONG idx, LONG value )` | desc_: Set( idx, value ) for a Numeric
      setting; returns the previous value. }}*/
   static LONG   SetLong(LONG,LONG);
   /*{{|method_: `static LONG SetLong( LONG idx )` | desc_: Set( idx ) for a Numeric setting. }}*/
   static LONG   SetLong(LONG);
   /*{{|method_: `static double SetDouble( LONG idx, double value )` | desc_: Set( idx, value ) for a Numeric
      setting with decimals; returns the previous value. }}*/
   static double SetDouble(LONG,double);
   /*{{|method_: `static double SetDouble( LONG idx )` | desc_: Set( idx ) for such a setting. }}*/
   static double SetDouble(LONG);
   /*{{|method_: `static LPSTR SetPsz( LONG idx, LPSTR value )` | desc_: Set( idx, value ) for a Character
      setting; returns a copy of the previous value (free it with _xfree). }}*/
   static LPSTR  SetPsz(LONG,LPSTR);
   /*{{|method_: `static LPSTR SetPsz( LONG idx )` | desc_: Set( idx ) for a Character setting, as a copy. }}*/
   static LPSTR  SetPsz(LONG);
   /*{{|method_: `static LPSTR SetPszAdditive( LONG idx, LPSTR value, BOOL bAdditive )` | desc_: Set( idx,
      value, bAdditive ) for the file settings that take the ADDITIVE flag (alternate and print files). }}*/
   static LPSTR  SetPszAdditive(LONG,LPSTR, BOOL);
   // --------------------------------------------------------------------
   /*{{|method_: `static <type> <Setting>( <type> value )` | desc_: One pair of overloads per setting of
      set.ch, from Exact() to SmartFilter(): with the value, changes the setting and returns the previous
      value; without it, reads it. The C type follows the setting (BOOL, LONG, double or LPSTR); AltFile() and
      PrintFile() take the ADDITIVE flag as second argument. }}*/
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
/*{{end-cpp-class}}*/
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
