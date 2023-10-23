//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------

#pragma once

enum class   escape_to_sql_buffer_flags : DWORD
{

   zero_terminated_string = 0x0001,
   binary_string = 0x0002,
   wildcard_escape = 0x0008,
   add_quotes = 0x1000 // only for OT4XB_SQL_ESCAPE_STRING_ANSI() 

};




// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
enum class ot4xb_sql_type_flag : DWORD
{
   none = 0,
   LTrim = 0x000001,
   RTrim = 0x000002,
   AllTrim = 0x000003,
   wildcard_escape = (DWORD) escape_to_sql_buffer_flags::wildcard_escape,
   LeftAlign = 0x000010,
   RightAlign = 0x000020,
   Truncate = 0x000100,
   ToUtf8 = 0x001000,
   NotNull = 0x010000,
   OvNull = 0x100000,
   OvMin = 0x200000,
   OvMax = 0x400000,
   OvZero = 0x800000
};

// ------------------------------------------------------------------------------------------------------------------


namespace sql_dump_value
{
   static void to_integer_value(TXppParamList& xpp, LONGLONG min, LONGLONG max, DWORD flags);
   static void put_decimal_max_value(TXppParamList& xpp, int len, int dec, BOOL negative);
   static void to_decimal_value(TXppParamList& xpp, int len, int dec, DWORD flags);
   static void to_double_value(TXppParamList& xpp);
   static void to_bit_value(TXppParamList& xpp, int len);
   static void to_date_value(TXppParamList& xpp, DWORD flags);
   static void to_char_value(TXppParamList& xpp, int len, DWORD flags);
   static LPSTR  grip_string(TXppParamList& xpp, char alt_buffer[256], DWORD* pcb);

}