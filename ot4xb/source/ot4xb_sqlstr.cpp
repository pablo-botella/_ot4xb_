//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include  <math.h>
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __sqlstr_money
            | syntax_: `__sqlstr_money( xValue [, aFormat] )`
            | category: sql/string
            | _kw_: __sqlstr_money, Function
   }}*/
/*{{|desc: Converts a numeric or character value to a SQL-style money string with two decimal places.
    | params:
    - `xValue` Numeric/Character - Value to format. Numeric values are converted to cents internally.
      Character values are parsed as money text and may use "." or "," as decimal separators.
    - `aFormat` Array - Optional { nFlags, nPad } format array.

    Returns Character - Formatted money string. nPad left-pads the result with spaces up to the requested
      width.

    |note: With nFlags == 0, negative values are formatted with a leading minus sign. With nonzero flags,
      negative values are formatted as an absolute amount; a marker is appended only when flag 0x00000002 is
      present.

    |flags: For negative values, append a credit marker instead of using a leading minus sign.For non-negative
      values, append a debit marker.Use H/Hb instead of C/Cr for negative values.Use the long marker form: Cr,
      Hb or Db. }}*/
_XPP_REG_FUN_(__SQLSTR_MONEY)
{
   TXppParamList xpp(pl, 2);
   LONGLONG qn = xpp[1]->GetSqlStrMoney();
   DWORD flags = 0;
   DWORD pad = 0;
   ULONG np = xpp.PCount();
   TXbCPItem* xxb;
   if (np > 0)
   {
      xxb = xpp._get_(np);
      if (xxb->CheckType(XPP_ARRAY))
      {
         DWORD dwc = xxb->con_size();
         np--;
         if (dwc > 0) { flags = _conArrayGetNL(xxb->con(), 1, 0); }
         if (dwc > 1) { pad = _conArrayGetNL(xxb->con(), 2, 0); }
      }
   }

   xpp[0]->PutSqlStrMoney(qn, flags, pad);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: __sqlstr_str2money
            | syntax_: `BOOL __sqlstr_str2money( LPSTR buffer, DWORD buffer_cb, LONGLONG & qn )`
            | category: sql/string
            | header: ot4xb_c_exported.h
            | mangled-name: __sqlstr_str2money
            | _kw_: __sqlstr_str2money, Function
   }}*/
/*{{|desc: Parses money text into a 64-bit integer amount with two implied decimals, i.e. the value in
      hundredths. This is the character-value parser behind the __sqlstr_money() family.
    | params:
    - `buffer` LPSTR - Money text to parse. Digits with optional "." or "," separators; a separator
      followed by a second separator, or by more than two digits, is reclassified as a thousands separator.
      Spaces and tabs are skipped. A "-" negates the amount parsed so far; "c" or "C" (credit marker)
      negates it and ends the parse; any other character ends the parse.
    - `buffer_cb` DWORD - Length of buffer in bytes.
    - `qn` LONGLONG & - Receives the amount scaled by 100 (two implied decimals); zeroed before parsing.

    Returns BOOL - FALSE when buffer is NULL or buffer_cb is 0; TRUE otherwise, even when the parse stops
      early. }}*/
OT4XB_API BOOL __sqlstr_str2money(LPSTR buffer, DWORD buffer_cb, LONGLONG& qn)
{


   DWORD dw_bp;
   DWORD decimal_places = 0;
   char  dc_sep = 0;
   char  th_sep = 0;
   qn = 0LL;
   if (!buffer) { return FALSE; }
   if (!buffer_cb) { return FALSE; }


   for (dw_bp = 0; dw_bp < buffer_cb; dw_bp++)
   {
      char ch = buffer[dw_bp];
      switch (ch)
      {
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      {
         qn = qn * 10LL;
         qn += (LONGLONG)(ch - '0');
         if (dc_sep)
         {
            decimal_places++;
            if (decimal_places > 2) { th_sep = dc_sep; dc_sep = 0; decimal_places = 0; }
         }
         break;
      }
      case '.': case ',':
      {
         if (dc_sep) { th_sep = dc_sep; dc_sep = 0; decimal_places = 0; break; }
         if (th_sep == ch) { break; }
         dc_sep = ch;
         break;
      }
      case ' ': case '\t':
      {
         break;
      }
      case '-':
      {
         qn = qn * -1LL;
         break;
      }
      case 'c': case 'C':
      {
         qn = qn * -1LL;
         dw_bp = buffer_cb + 1;
         break;
      }
      default:
      {
         dw_bp = buffer_cb + 1;
         break;
      }
      }

   }
   while (decimal_places < 2)
   {
      qn = qn * 10LL;
      decimal_places++;
   }
   return TRUE;
}
/*{{end-c-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void money_sum_internal(XppParamList pl, BOOL bSubstract)
{
   TXppParamList xpp(pl, 0);
   ULONG np = xpp.PCount();
   ULONG n;
   DWORD flags = 0;
   DWORD pad = 0;
   TXbCPItem* xxb;


   LONGLONG qt = 0LL;
   if (np > 0)
   {
      xxb = xpp._get_(np);
      if (xxb->CheckType(XPP_ARRAY))
      {
         DWORD dwc = xxb->con_size();
         np--;
         if (dwc > 0) { flags = _conArrayGetNL(xxb->con(), 1, 0); }
         if (dwc > 1) { pad = _conArrayGetNL(xxb->con(), 2, 0); }
      }
   }


   for (n = 1; n <= np; n++)
   {
      LONGLONG qn = xpp._get_(n)->GetSqlStrMoney();
      if (flags && 1)
      {
         if (qn < 0) { qn = qn * -1LL; }
      }
      if (n > 1 && bSubstract)
      {
         qt -= qn;
      }
      else
      {
         qt += qn;
      }
   }
   xpp[0]->PutSqlStrMoney(qt, flags, pad);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __sqlstr_money_sum
            | syntax_: `__sqlstr_money_sum( xValue1 [, xValueN] [, aFormat] )`
            | category: sql/string
            | _kw_: __sqlstr_money_sum, Function
   }}*/
/*{{|desc: Sums one or more money values and returns the result formatted as a SQL-style money string.
    | params:
    - `xValue1...xValueN` Numeric/Character - Money values to add. Each value is converted using the same
      parser as __sqlstr_money().
    - `aFormat` Array - Optional final { nFlags, nPad } format array.

    Returns Character - Formatted sum.

    |note: When aFormat is supplied with any nonzero nFlags value, each input value is converted to its
      absolute value before being added. The same nFlags and nPad values are then used to format the final
      result. }}*/
_XPP_REG_FUN_(__SQLSTR_MONEY_SUM)
{
   money_sum_internal(pl, 0);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: __sqlstr_money_substract
            | syntax_: `__sqlstr_money_substract( xValue1, xValue2 [, xValueN] [, aFormat] )`
            | category: sql/string
            | _kw_: __sqlstr_money_substract, Function
   }}*/
/*{{|desc: Subtracts money values from the first value and returns the result formatted as a SQL-style money
      string.
    | params:
    - `xValue1` Numeric/Character - Initial money value.
    - `xValue2...xValueN` Numeric/Character - Money values subtracted from the first value.
    - `aFormat` Array - Optional final { nFlags, nPad } format array.

    Returns Character - Formatted result.

    |note: The exported name keeps the historical spelling "substract". When aFormat is supplied with any
      nonzero nFlags value, each input value is converted to its absolute value before the subtraction sequence
      is applied. }}*/
_XPP_REG_FUN_(__SQLSTR_MONEY_SUBSTRACT)
{
   money_sum_internal(pl, 1);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DWORD escape_to_sql_required_size(LPBYTE p, DWORD cb)
{
   DWORD cbo = 0;
   if (p && cb)
   {
      if (((LONG)cb) < 0)
      {
         cb = _xstrlen((LPSTR)p);
         cbo++;
      }

      DWORD n;
      for (n = 0; n < cb; n++)
      {
         switch (p[n])
         {
         case 0: case 8: case '\t': case 26: case '\n': case '\r': case '\"': case '\'': case '\\': case '%': case '_':
         {
            cbo += 2;
            break;
         }
         default:
         {
            cbo++;
         }
         }
      }
      return cbo;
   }
   return cbo; // not including terminator \0 in cb == -1
}
// -------------------------------------------------------------------------------------------------
// escape_to_sql_buffer_flags
DWORD escape_to_sql_buffer(LPBYTE p, DWORD cb, LPBYTE po, DWORD cbo, DWORD flags)
{
   DWORD dw = 0;
   if (((LONG)cb) < 0)
   {
      flags |= (DWORD)escape_to_sql_buffer_flags::zero_terminated_string;
   }


   if (p && cb && po && cbo)
   {
      DWORD n;
      if (flags & (DWORD)escape_to_sql_buffer_flags::zero_terminated_string)
      {
         cbo--;
         po[cbo] = 0;
      }
      for (n = 0; (n < cb) && (dw < cbo); n++)
      {
         BYTE  b0 = 0;
         BYTE  b1 = 0;
         switch (p[n])
         {
         case 0x00:
         {
            if (flags & (DWORD)escape_to_sql_buffer_flags::zero_terminated_string)
            {
               po[dw] = 0;
               return dw;
            }
            else
            {
               b0 = '\\'; b1 = '0';
            }
            break;
         }
         case '\b':
         {
            b0 = '\\'; b1 = 'b'; break;
         }
         case '\t':
         {
            b0 = '\\'; b1 = 't'; break;
         }
         case 26:
         {
            b0 = '\\'; b1 = 'Z'; break;
         }
         case '\n':
         {
            b0 = '\\'; b1 = 'n'; break;
         }
         case '\r':
         {
            b0 = '\\'; b1 = 'r'; break;
         }
         case '\"':
         {
            b0 = '\\'; b1 = '\"'; break;
         }
         case '\'':
         {
            b0 = '\\'; b1 = '\''; break;
         }
         case '\\':
         {
            b0 = '\\'; b1 = '\\'; break;
         }
         case '%':
         {
            if (flags & (DWORD)escape_to_sql_buffer_flags::wildcard_escape)
            {
               b0 = '\\'; b1 = '%';
            }
            else
            {
               b0 = '%';
            }

            break;
         }
         case '_':
         {
            if (flags & (DWORD)escape_to_sql_buffer_flags::wildcard_escape)
            {
               b0 = '\\'; b1 = '_';
            }
            else
            {
               b0 = '_';
            }
            break;
         }
         default:
         {
            b0 = p[n]; b1 = 0; break;
         }
         }
         po[dw] = b0; dw++;
         if (b1)
         {
            if (dw < cbo)
            {
               po[dw] = b1; dw++;
            }
            else
            {
               dw--;
               po[dw] = 0;
               return dw;
            }
         }
      }
   }
   return dw;
}
// -------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: escape_to_sql
            | syntax_: `LPSTR escape_to_sql( LPSTR pIn, UINT * pcbOut, DWORD flags )`
            | category: sql/string
            | header: ot4xb_c_exported.h
            | mangled-name: escape_to_sql
            | _kw_: escape_to_sql, Function
   }}*/
/*{{|desc: Escapes a zero-terminated string for use inside a SQL string literal, returning the result as a
      newly allocated buffer. Backspace, tab, Ctrl+Z, LF, CR, double quote, single quote and backslash are
      escaped with a backslash sequence; the SQL wildcards "%" and "_" are escaped only when the
      wildcard_escape flag (0x0008) is set.
    | params:
    - `pIn` LPSTR - Zero-terminated string to escape.
    - `pcbOut` UINT * - Optional; when not NULL, receives the length in bytes of the escaped string,
      not counting the terminating zero.
    - `flags` DWORD - escape_to_sql_buffer_flags combination. Only wildcard_escape (0x0008) is relevant
      here; the input is always processed as zero-terminated.

    Returns LPSTR - Allocated buffer with the escaped, zero-terminated copy; free it with _xfree. }}*/
OT4XB_API LPSTR escape_to_sql(LPSTR pIn, UINT* pcbOut, DWORD flags)
{
   DWORD cb = escape_to_sql_required_size((LPBYTE)pIn, (DWORD)-1) + 4;
   LPSTR buffer = (LPSTR)_xgrab(cb);
   cb = escape_to_sql_buffer((LPBYTE)pIn, (DWORD)-1, (LPBYTE)buffer, cb, flags);
   if (pcbOut) {
      pcbOut[0] = cb;
   }
   return buffer;
}
/*{{end-c-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ot4xb_sql_type_flag ot4xb_str_to_sql_type_flag(LPSTR p)
{
   DWORD flags = 0;
   BOOL go_next = 0;
   if (p)
   {
      for (; *p; p++)
      {
         if (go_next)
         {
            if (*p == ',')
            {
               go_next = FALSE;
            }
         }
         else
         {
            go_next = TRUE;
            switch (_lower_ansi_char_table_[(BYTE)*p])
            {
            case 'w': { flags |= (DWORD)ot4xb_sql_type_flag::wildcard_escape; break; } // "wildcard_escape" for queries
            case 'a':  // AllTrim
            {
               switch (_lower_ansi_char_table_[(BYTE)p[1]])
               {
               case 'l': case 't': { flags |= (DWORD)ot4xb_sql_type_flag::AllTrim; break; } // AllTrim | AT
               default: { break; }
               }
               break;
            }
            case 'l':  // LTrim , LeftAlign
            {
               switch (_lower_ansi_char_table_[(BYTE)p[1]])
               {
               case 'e': case 'a': { flags |= (DWORD)ot4xb_sql_type_flag::LeftAlign; break; }   // LeftAlign | LA
               case 't': { flags |= (DWORD)ot4xb_sql_type_flag::LTrim; break; }    // LTrim
               default: { break; }
               }
               break;
            }
            case 'r':  // RTrim , RightAlign
            {
               switch (_lower_ansi_char_table_[(BYTE)p[1]])
               {
               case 'i': case 'a': { flags |= (DWORD)ot4xb_sql_type_flag::RightAlign; break; } // RightAlign | RA 
               case 't': { flags |= (DWORD)ot4xb_sql_type_flag::RTrim; break; }    // RTrim
               default: { break; }
               }
               break;
            }
            case 't':  // Truncate
            {
               switch (_lower_ansi_char_table_[(BYTE)p[1]])
               {
               case 'r': { flags |= (DWORD)ot4xb_sql_type_flag::Truncate; break; } // Truncate
               case 'u': { flags |= (DWORD)ot4xb_sql_type_flag::ToUtf8; break; } // TU -> ToUtf8
               case 'o':
               {
                  if (_lower_ansi_char_table_[(BYTE)p[2]] == 'u')
                  {
                     flags |= (DWORD)ot4xb_sql_type_flag::ToUtf8;// ToUtf8

                  }
                  break;
               }
               default: { break; }
               }
               break;
            }
            case 'n': // NotNull = 0x010000
            {
               if (_lower_ansi_char_table_[(BYTE)p[1]] == 'o')
               {
                  if (_lower_ansi_char_table_[(BYTE)p[2]] == 't')
                  {
                     if (_lower_ansi_char_table_[(BYTE)p[3]] == 'n')
                     {
                        flags |= (DWORD)ot4xb_sql_type_flag::NotNull;
                     }
                  }
               }
            }
            case 'o': // Ov????
            {
               if (_lower_ansi_char_table_[(BYTE)p[1]] == 'v')
               {
                  switch (_lower_ansi_char_table_[(BYTE)p[2]])
                  {
                  case 'n': { flags |= (DWORD)ot4xb_sql_type_flag::OvNull; break; } // OvNull
                  case 'm':
                  {
                     switch (_lower_ansi_char_table_[(BYTE)p[3]])
                     {
                     case 'a': { flags |= (DWORD)ot4xb_sql_type_flag::OvMax; break; } // OvMax
                     case 'i': { flags |= (DWORD)ot4xb_sql_type_flag::OvMin; break; } // OvMin
                     default: { break; }
                     }
                     break;
                  }
                  case 'z': { flags |= (DWORD)ot4xb_sql_type_flag::OvZero; break; } // OvZero
                  default: { break; }
                  }
               }
               break;
            }
            default:
            {
               break;
            }
            }
         }
      }
   }
   return (ot4xb_sql_type_flag)flags;

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ot4xb_sql_type ot4xb_str_to_sql_type_enum(LPSTR p)
{
   if (p)
   {
      if (!_xstrcmpi(p, "Tinyint")) { return ot4xb_sql_type::TinyInt; }
      if (!_xstrcmpi(p, "Smallint")) { return ot4xb_sql_type::SmallInt; }
      if (!_xstrcmpi(p, "MediumInt")) { return ot4xb_sql_type::MediumInt; }
      if (!_xstrcmpi(p, "Int")) { return ot4xb_sql_type::Int; }
      if (!_xstrcmpi(p, "BigInt")) { return ot4xb_sql_type::BigInt; }
      if (!_xstrcmpi(p, "Decimal")) { return ot4xb_sql_type::Decimal; }
      if (!_xstrcmpi(p, "Float")) { return ot4xb_sql_type::Float; }
      if (!_xstrcmpi(p, "Double")) { return ot4xb_sql_type::Double; }
      if (!_xstrcmpi(p, "Bit")) { return ot4xb_sql_type::Bit; }
      if (!_xstrcmpi(p, "Date")) { return ot4xb_sql_type::Date; }
      if (!_xstrcmpi(p, "Time")) { return ot4xb_sql_type::Time; }
      if (!_xstrcmpi(p, "DateTime")) { return ot4xb_sql_type::DateTime; }
      if (!_xstrcmpi(p, "TimeStamp")) { return ot4xb_sql_type::TimeStamp; }
      if (!_xstrcmpi(p, "Year")) { return ot4xb_sql_type::Year; }
      if (!_xstrcmpi(p, "Char")) { return ot4xb_sql_type::Char; }
      if (!_xstrcmpi(p, "VarChar")) { return ot4xb_sql_type::VarChar; }
      if (!_xstrcmpi(p, "Binary")) { return ot4xb_sql_type::Binary; }
      if (!_xstrcmpi(p, "VarBinary")) { return ot4xb_sql_type::VarBinary; }
      if (!_xstrcmpi(p, "TinyBlob")) { return ot4xb_sql_type::TinyBlob; }
      if (!_xstrcmpi(p, "Blob")) { return ot4xb_sql_type::Blob; }
      if (!_xstrcmpi(p, "MediumBlob")) { return ot4xb_sql_type::MediumBlob; }
      if (!_xstrcmpi(p, "LongBlob")) { return ot4xb_sql_type::LongBlob; }
      if (!_xstrcmpi(p, "TinyText")) { return ot4xb_sql_type::TinyText; }
      if (!_xstrcmpi(p, "Text")) { return ot4xb_sql_type::Text; }
      if (!_xstrcmpi(p, "MediumText")) { return ot4xb_sql_type::MediumText; }
      if (!_xstrcmpi(p, "LongText")) { return ot4xb_sql_type::LongText; }
      if (!_xstrcmpi(p, "Enum")) { return ot4xb_sql_type::Enum; }
      if (!_xstrcmpi(p, "Set")) { return ot4xb_sql_type::Set; }
      if( !_xstrcmpi( p, "Json" ) ) { return ot4xb_sql_type::Json; }
   }
   return ot4xb_sql_type::Invalid;
}
// --------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_sql_escape_string_ansi
            | syntax_: `ot4xb_sql_escape_string_ansi( cString, [nFlags] )`
            | category: sql/string
            | _kw_: ot4xb_sql_escape_string_ansi, Function
   }}*/
/*{{|desc: Escapes an ANSI string so it can be used inside a SQL string literal.
    | params:
    - `cString` Character - String to escape.
    - `nFlags` Numeric - Escape flags. Combine flags with nOr().

    Returns Character - Escaped string. The function escapes NUL, backspace, tab, Ctrl+Z, LF, CR, double
      quote, single quote and backslash; wildcards are escaped only when flag 0x0008 is set.

    |note: Without 0x0002, the function behaves as zero-terminated input and stops at the first NUL byte. With
      0x0002, NUL bytes are escaped as "\0" and the full Xbase++ string length is used.

    |flags: Treat input as zero-terminated. This is the default when 0x0002 is not set.Treat input as a binary
      Xbase++ string and process its full length.Also escape SQL wildcard characters "%" and "_".Wrap the
      escaped result in single quotes.

    |include-note-id: sql-type-flags }}*/
_XPP_REG_FUN_(OT4XB_SQL_ESCAPE_STRING_ANSI)
{
   TXppParamList xpp(pl, 2);
   DWORD flags = xpp[2]->GetDWord();
   DWORD cb = 0;
   LPBYTE p = (LPBYTE)xpp[1]->LockStr(&cb, FALSE);
   DWORD buffer_cb = escape_to_sql_required_size((LPBYTE)p, cb) + 4;
   LPSTR buffer = (LPSTR)_xgrab(buffer_cb);
   DWORD cbo = 0;
   LPSTR po = buffer;

   if (flags & (DWORD)escape_to_sql_buffer_flags::binary_string)
   {
      flags &= ~(DWORD)escape_to_sql_buffer_flags::zero_terminated_string;
   }
   else
   {
      flags &= ~(DWORD)escape_to_sql_buffer_flags::binary_string;
      flags |= (DWORD)escape_to_sql_buffer_flags::zero_terminated_string;   // default here
   }


   if (flags & (DWORD)escape_to_sql_buffer_flags::add_quotes) // quotes '
   {
      *po = '\''; po++;  cbo++; buffer_cb -= 2;
   }
   cbo += escape_to_sql_buffer((LPBYTE)p, cb, (LPBYTE)po, buffer_cb, flags);
   if (flags & (DWORD)escape_to_sql_buffer_flags::add_quotes) // quotes '
   {
      buffer[cbo] = '\''; cbo++;
   }
   xpp[0]->PutStrLen(buffer, cbo);
   _xfree((void*)buffer);
   buffer = 0;
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------
static void sql_dump_value::to_integer_value(TXppParamList& xpp, LONGLONG min, LONGLONG max, DWORD flags)
{
   LONGLONG value = 0;
   BOOL init = FALSE;
   DWORD t = xpp[1]->GetType();

   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      value = atoll(xpp[1]->LockStr());
      init = TRUE;
      break;
   }
   case XPP_NUMERIC:
   {
      if (t & _xpp_DOUBLE)
      {
         value = (LONGLONG)xpp[1]->GetDouble();
      }
      else
      {
         value = (LONGLONG)(xpp[1]->GetLong() & 0xFFFFFFFFll);
      }
      init = TRUE;
      break;
   }
   case XPP_DATE:
   {
      value = (LONGLONG)xpp[1]->GetJulianDate();
      init = TRUE;
      break;
   }
   case XPP_LOGICAL:
   {
      value = xpp[1]->GetBool() ? 1ll : 0ll;
      init = TRUE;
      break;
   }
   default:
   {
      break;
   }
   }
   if (!init)
   {
      if (flags & (DWORD)ot4xb_sql_type_flag::NotNull)
      {
         xpp[0]->PutStr("null");
      }
      else
      {
         xpp[0]->PutStr("0");
      }
      return;
   }
   if (value < min || value > max)
   {
      if (flags & (DWORD)ot4xb_sql_type_flag::OvNull)
      {
         xpp[0]->PutStr("null");
         return;
      }
      if (flags & (DWORD)ot4xb_sql_type_flag::OvZero)
      {
         value = 0ll;
      }
      else
      {
         if (value < min && (flags & (DWORD)ot4xb_sql_type_flag::OvMin))
         {
            value = min;
         }
         if (value > max && (flags & (DWORD)ot4xb_sql_type_flag::OvMax))
         {
            value = max;
         }
      }
   }
   char sz[64] = { 0 };
   snprintf(sz, sizeof(sz), "%lli", value);
   xpp[0]->PutStr(sz);
}
// ---------------------------------------------------------------------------------------------------------
void sql_dump_value::put_decimal_max_value(TXppParamList& xpp, int len, int dec, BOOL negative)
{
   char buffer[128] = { 0 };
   int n = 0;
   LPSTR p = buffer;
   if (negative)
   {
      *p = '-'; p++;
   }

   for (n = len - dec; n > 0; *p = '9', p++, n--);
   if (dec)
   {
      *p = '.'; p++;
      for (n = dec; n > 0; *p = '9', p++, n--);
   }
   xpp[0]->PutStr(buffer);
}
// ------------------------------------------------------------------------------------------------------------------------------
void sql_dump_value::to_decimal_value(TXppParamList& xpp, int len, int dec, DWORD flags)
{
   DWORD t = xpp[1]->GetType();
   char buffer[512] = { 0 };
   if (len < 0 || len > 65) { len = 65; }
   if (dec >= len) { dec = len - 1; }
   if (dec < 0) { dec = 0; }


   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      LPSTR p = xpp[1]->LockStr();
      if (p)
      {
         char sz_int[72] = { 0 };
         DWORD int_count = 0;
         char sz_dec[72] = { 0 };
         DWORD dec_count = 0;
         LPSTR dst = sz_int;
         BOOL  decimal_reached = FALSE;
         BOOL  negative = FALSE;
         DWORD cb = 0;
         for (; *p && cb < 67; p++)
         {
            switch (*p)
            {
            case 7: case 32:
            {
               if (int_count || dec_count || decimal_reached) { cb = 0xFF; }
               break;
            }
            case '-':
            {
               if (cb) { cb = 0xFF; }
               else { negative = TRUE; }
               break;
            }
            case '.':
            {
               if (decimal_reached) { cb = 0xFF; }
               else { decimal_reached = TRUE; dst = sz_dec; }
               break;
            }
            default:
            {
               if (*p >= '0' && *p <= '9')
               {
                  *dst = *p; cb++;
                  if (decimal_reached) { dec_count++; }
                  else { int_count++; }
               }
               else { cb = 0xFF; }
               break;
            }
            }
         }

         if (int_count > (DWORD)(len - dec))
         {

            if (flags & (DWORD)ot4xb_sql_type_flag::OvNull)
            {
               xpp[0]->PutStr("null");
               return;
            }
            if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero | (DWORD)ot4xb_sql_type_flag::OvMin))
            {
               xpp[0]->PutStr("0");
               return;
            }
            if (flags & (DWORD)ot4xb_sql_type_flag::OvMax)
            {
               sql_dump_value::put_decimal_max_value(xpp, len, dec, negative);
               return;
            }
         }
         if (!int_count)
         {
            *sz_int = '0';
            int_count = 1;
         }
         if (dec_count > (DWORD)dec)
         {
            dec_count = (DWORD)dec;
            sz_dec[(DWORD)dec] = '\0';
         }

         sprintf_s(buffer, sizeof(buffer), "%s%s%s%s", (negative ? "-" : ""), sz_int, (dec_count ? "." : ""), sz_dec);
         xpp[0]->PutStr(buffer);
         return;
      }
      break;
   }
   case XPP_NUMERIC:
   {
      int cb = 0;
      BOOL negative = FALSE;
      if (t & _xpp_DOUBLE)
      {
         double nd = xpp[1]->GetDouble();
         negative = !(nd >= fabs(nd));   // nd < 0.0

         cb = _scprintf("%.*f", dec, nd);   // measure first: _scprintf only counts, never writes or kills
         if (cb < (int) sizeof(buffer)) { sprintf_s(buffer, sizeof(buffer), "%.*f", dec, nd); }
      }
      else
      {
         long nl = xpp[1]->GetLong();
         negative = nl < 0;
         cb = sprintf_s(buffer, sizeof(buffer), "%i", nl);
      }
      if (cb > (len - dec))
      {
         if (flags & (DWORD)ot4xb_sql_type_flag::OvNull)
         {
            xpp[0]->PutStr("null");
            return;
         }
         if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero | (DWORD)ot4xb_sql_type_flag::OvMin))
         {
            xpp[0]->PutStr("0");
            return;
         }
         if (flags & (DWORD)ot4xb_sql_type_flag::OvMax)
         {
            sql_dump_value::put_decimal_max_value(xpp, len, dec, negative);
            return;
         }
      }
      xpp[0]->PutStr(buffer);
      return;
   }
   case XPP_DATE:
   {
      int cb = 0;
      long nl = xpp[1]->GetJulianDate();
      cb = sprintf_s(buffer, sizeof(buffer), "%i", nl);
      if (cb > (len - dec))
      {
         if (flags & (DWORD)ot4xb_sql_type_flag::OvNull)
         {
            xpp[0]->PutStr("null");
            return;
         }
         if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero | (DWORD)ot4xb_sql_type_flag::OvMin))
         {
            xpp[0]->PutStr("0");
            return;
         }
         if (flags & (DWORD)ot4xb_sql_type_flag::OvMax)
         {
            sql_dump_value::put_decimal_max_value(xpp, len, dec, 0);
            return;
         }
      }
      xpp[0]->PutStr(buffer);
      return;
   }
   case XPP_LOGICAL:
   {
      xpp[0]->PutStr(xpp[1]->GetBool() ? "1" : "0");
      return;
   }
   default:
   {
      break;
   }
   }
   xpp[0]->PutStr((flags & (DWORD)ot4xb_sql_type_flag::OvNull) ? "null" : "0");
}
// -----------------------------------------------------------------------------------------------------------------------------
void sql_dump_value::to_double_value(TXppParamList& xpp)
{

   DWORD t = xpp[1]->GetType();
   char buffer[255] = { 0 };
   double nd = 0.00;

   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      LPSTR p = xpp[1]->LockStr();
      if (p)
      {
         nd = atof(p);
      }
      break;
   }
   case XPP_NUMERIC:
   {
      nd = xpp[1]->GetDouble();
      break;
   }
   case XPP_DATE:
   {
      nd = (double)xpp[1]->GetJulianDate();
      break;
   }
   case XPP_LOGICAL:
   {
      nd = xpp[1]->GetBool() ? 1.00 : 0.00;
      break;
   }
   default:
   {
      break;
   }
   }
   sprintf_s(buffer, sizeof(buffer), "%.15g", nd);
   xpp[0]->PutStr(buffer);
}
// ------------------------------------------------------------------------------------------------------------------------------
void sql_dump_value::to_bit_value(TXppParamList& xpp, int len)
{
   DWORD t = xpp[1]->GetType();
   char buffer[128] = { 0 };
   if (len < 1 || len > 64) { len = 64; }

   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      LPSTR ps = xpp[1]->LockStr();
      if (ps)
      {
         LPSTR pd = buffer;
         *pd = 'b'; pd++; *pd = '\''; pd++;
         for (; *ps && len > 0; ps++)
         {
            if (*ps == '0' || *ps == '1') { *pd = *ps; pd++; len--; }
         }
         *pd = '\''; pd++;
         xpp[0]->PutStr(buffer);
         return;
      }
      break;
   }
   case XPP_NUMERIC:
   {
      sprintf_s(buffer, sizeof(buffer), "%i", xpp[1]->GetLong());
      xpp[0]->PutStr(buffer);
      return;
   }
   default:
   {
      break;
   }
   }
   xpp[0]->PutStr("b''");
}
// ------------------------------------------------------------------------------------------------------------------------------
void sql_dump_value::to_date_value(TXppParamList& xpp, DWORD flags)
{
   DWORD t = xpp[1]->GetType();
   char buffer[16] = { 0 };
   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      LPSTR ps = xpp[1]->LockStr();
      if (ps)
      {
         LPSTR pd = buffer;
         DWORD cb = 0;
         *pd = '\''; pd++;
         for (; *ps && cb < 8; ps++)
         {
            if (*ps >= '0' && *ps <= '9') { *pd = *ps; pd++; cb++; }
         }
         *pd = '\''; pd++;
         if (buffer[1] < '0' || buffer[1] > '9')
         {
            if (flags & (DWORD)ot4xb_sql_type_flag::NotNull)
            {
               xpp[0]->PutStr("'0000-00-00'");
            }
            else
            {
               xpp[0]->PutStr("null");
            }
            return;
         }
         xpp[0]->PutStr(buffer);
         return;
      }
      break;

   }
   case XPP_DATE:
   {

      LPSTR ps = (LPSTR)xpp[1]->GetDateString();
      if (ps[0] < '0' || ps[0] > '9')
      {
         if (flags & (DWORD)ot4xb_sql_type_flag::NotNull)
         {
            xpp[0]->PutStr("'0000-00-00'");
         }
         else
         {
            xpp[0]->PutStr("null");
         }
         return;
      }
      sprintf_s(buffer, sizeof(buffer), "'%s'", ps);
      xpp[0]->PutStr(buffer);
      return;
   }
   default:
   {
      break;
   }
   }
   if (flags & (DWORD)ot4xb_sql_type_flag::NotNull)
   {
      xpp[0]->PutStr("'0000-00-00'");
   }
   else
   {
      xpp[0]->PutStr("null");
   }
}
// ------------------------------------------------------------------------------------------------------------------------------
void sql_dump_value::to_char_value(TXppParamList& xpp, int len, DWORD flags)
{
   char buffer[256] = { 0 };
   DWORD cb = 0;
   LPSTR ps = sql_dump_value::grip_string(xpp, buffer, &cb);
   DWORD max_cb = (len < 1 ? cb : (DWORD)len);
   if (!ps)
   {
      if (flags & (DWORD)ot4xb_sql_type_flag::NotNull)
      {
         xpp[0]->PutStr("''");
      }
      else
      {
         xpp[0]->PutStr("null");
      }
      return;
   }
   if (!cb)
   {
      xpp[0]->PutStr("''");
      return;
   }

   if (flags & (DWORD)ot4xb_sql_type_flag::LTrim)
   {
      while (*ps == ' ' || *ps == '\t')
      {
         ps++; cb--;
      }
   }
   if (flags & (DWORD)ot4xb_sql_type_flag::RTrim)
   {
      while (cb && (ps[cb - 1] == ' ' || ps[cb - 1] == '\t'))
      {
         cb--;
      }
   }
   DWORD pd_size = escape_to_sql_required_size((LPBYTE)ps, ((flags & (DWORD)ot4xb_sql_type_flag::RightAlign) ? max(max_cb, cb) : cb)) + 16;
   LPSTR pd = (LPSTR)_xgrab(pd_size);
   DWORD dwo = 0;
   DWORD pad = 0;
   LPSTR p = pd;

   *p = '\''; p++; dwo++;
   if (flags & (DWORD)ot4xb_sql_type_flag::Truncate)
   {
      if (cb > (DWORD)max_cb)
      {
         cb = (DWORD)max_cb;
      }
   }
   if (flags & (DWORD)ot4xb_sql_type_flag::RightAlign)
   {
      while ((pad + cb) < (DWORD)max_cb)
      {
         *p = ' '; p++; pad++; dwo++;
      }
   }
   dwo += escape_to_sql_buffer((LPBYTE)ps, cb, (LPBYTE)p, pd_size - dwo, (DWORD)escape_to_sql_buffer_flags::binary_string);
   p = _mk_ptr_(LPSTR, pd, dwo);
   if (flags & (DWORD)ot4xb_sql_type_flag::LeftAlign)
   {
      while ((pad + cb) < (DWORD)max_cb)
      {
         *p = ' '; p++; pad++; dwo++;
      }
   }
   *p = '\''; p++; dwo++;
   if (flags & (DWORD)ot4xb_sql_type_flag::ToUtf8)
   {
      int cbo = 0;
      LPSTR tmp = mb2mb(pd, (int)dwo, &cbo, CP_ACP, CP_UTF8);
      xpp[0]->PutStrLen(tmp, cbo);
      _xfree((void*)tmp); tmp = 0;
   }
   else
   {
      xpp[0]->PutStrLen(pd, dwo);
   }
   _xfree((void*)pd); pd = 0;
}
// ------------------------------------------------------------------------------------------------------------------------------
LPSTR  sql_dump_value::grip_string(TXppParamList& xpp, LPSTR alt_buffer, DWORD* pcb)
{
   DWORD t = xpp[1]->GetType();
   switch (t & 0xFF)
   {
   case XPP_CHARACTER:
   {
      LPSTR p = xpp[1]->LockStr(pcb);
      return p;
   }

   case XPP_NUMERIC:
   {
      LPSTR p = (LPSTR)alt_buffer;

      if (t & _xpp_DOUBLE)
      {
         double nd = xpp[1]->GetDouble();
         *pcb = sprintf_s(p, 256, "%.15g", nd); // alt_buffer is 256 bytes by contract
      }
      else
      {
         long nl = xpp[1]->GetLong();
         *pcb = sprintf_s(p, 256, "%i", nl); // alt_buffer is 256 bytes by contract
      }
      return p;
   }
   case XPP_DATE:
   {
      LPSTR p = (LPSTR)xpp[1]->GetDateString();
      *pcb = 8;
      return p;
   }
   case XPP_LOGICAL:
   {
      LPSTR p = (LPSTR) alt_buffer;
      *pcb = 1;
      *p = xpp[1]->GetBool() ? '1' : '0';
      p[1] = 0;
      return p;
   }
   default:
   {
      break;
   }
   }
   *pcb = 0;
   return 0;

}
// ------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_get_sql_type_len
            | syntax_: `ot4xb_get_sql_type_len( cType | nLen )`
            | category: sql/string
            | _kw_: ot4xb_get_sql_type_len, Function
   }}*/
/*{{|desc: Extracts the length part from a SQL type declaration or returns a positive numeric value unchanged.
    | params:
    - `cType` Character - SQL type text such as "varchar(64)" or "decimal(12,2)".
    - `nLen` Numeric - Length value to pass through.

    Returns Numeric - Parsed positive length, or 0 when no positive length can be found. }}*/
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_LEN)
{
   TXppParamList xpp(pl, 1);
   DWORD len = 0;
   if (xpp[1]->CheckType(XPP_CHARACTER))
   {

      LPSTR p = xpp[1]->LockStr();
      for (; *p && *p != '('; p++);
      if (*p == '(')
      {
         p++;
         LONG n = atoi(p);
         if (n > 0)
         {
            len = (DWORD)n;
         }
      }
   }
   else
   {
      if (xpp[1]->CheckType(XPP_NUMERIC))
      {
         LONG n = xpp[1]->GetLong();
         if (n > 0)
         {
            len = (DWORD)n;
         }
      }
   }
   xpp[0]->PutDWord(len);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_get_sql_type_dec
            | syntax_: `ot4xb_get_sql_type_dec( cType | nDec )`
            | category: sql/string
            | _kw_: ot4xb_get_sql_type_dec, Function
   }}*/
/*{{|desc: Extracts the decimal-scale part from a SQL type declaration or returns a positive numeric value
      unchanged.
    | params:
    - `cType` Character - SQL type text such as "decimal(12,2)".
    - `nDec` Numeric - Decimal-scale value to pass through.

    Returns Numeric - Parsed positive decimal-scale value, or 0 when no positive value can be found. }}*/
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_DEC)
{
   TXppParamList xpp(pl, 1);
   DWORD len = 0;
   if (xpp[1]->CheckType(XPP_CHARACTER))
   {

      LPSTR p = xpp[1]->LockStr();
      for (; *p && *p != '('; p++);
      if (*p == '(')
      {
         p++;
         for (; *p && *p != ',' && *p != ')'; p++);
         if (*p == ',')
         {
            p++;
            LONG n = atoi(p);
            if (n > 0)
            {
               len = (DWORD)n;
            }
         }
      }
   }
   else
   {
      if (xpp[1]->CheckType(XPP_NUMERIC))
      {
         LONG n = xpp[1]->GetLong();
         if (n > 0)
         {
            len = (DWORD)n;
         }
      }
   }
   xpp[0]->PutDWord(len);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_get_sql_type_flag_enum
            | syntax_: `ot4xb_get_sql_type_flag_enum( cFlags | nFlags )`
            | category: sql/string
            | _kw_: ot4xb_get_sql_type_flag_enum, Function
   }}*/
/*{{|desc: Converts a SQL dump flag string to the numeric ot4xb_sql_type_flag bit mask.
    | params:
    - `cFlags` Character - Comma-separated flag names. Accepted names include LTrim, RTrim, AllTrim,
      wildcard_escape, LeftAlign, RightAlign, Truncate, ToUtf8, NotNull, OvNull, OvMin, OvMax and OvZero.
    - `nFlags` Numeric - Numeric flag mask to pass through.

    Returns Numeric - Numeric flag mask. Constants are declared in ot4xb.ch as ot4xb_sql_type_flag.*. }}*/
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_FLAG_ENUM)
{
   TXppParamList xpp(pl, 1);
   DWORD  flags = (DWORD)(xpp[1]->CheckType(XPP_CHARACTER) ? (DWORD)ot4xb_str_to_sql_type_flag(xpp[1]->LockStr()) : xpp[1]->GetDWord());
   xpp[0]->PutDWord(flags);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_get_sql_type_enum
            | syntax_: `ot4xb_get_sql_type_enum( cType | nType )`
            | category: sql/string
            | _kw_: ot4xb_get_sql_type_enum, Function
   }}*/
/*{{|desc: Converts a SQL type name to the numeric ot4xb_sql_type enumeration value.
    | params:
    - `cType` Character - SQL type name. Matching is case-insensitive and supports TinyInt, SmallInt,
      MediumInt, Int, BigInt, Decimal, Float, Double, Bit, Date, Time, DateTime, TimeStamp, Year, Char, VarChar,
      Binary, VarBinary, TinyBlob, Blob, MediumBlob, LongBlob, TinyText, Text, MediumText, LongText, Enum, Set
      and Json.
    - `nType` Numeric - Numeric type value to pass through.

    Returns Numeric - Numeric SQL type value. Constants are declared in ot4xb.ch as ot4xb_sql_type.*. Unknown
      character type names return ot4xb_sql_type.Invalid. }}*/
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_ENUM)
{
   TXppParamList xpp(pl, 1);
   ot4xb_sql_type q = (xpp[1]->CheckType(XPP_CHARACTER) ? ot4xb_str_to_sql_type_enum(xpp[1]->LockStr()) : (ot4xb_sql_type)xpp[1]->GetLong());
   xpp[0]->PutLong((LONG)q);
}
/*{{end-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_sql_dump_value_ansi
            | syntax_: `ot4xb_sql_dump_value_ansi( xValue, cType | nType, nLen, nDec, cFlags | nFlags )`
            | category: sql/string
            | _kw_: ot4xb_sql_dump_value_ansi, Function
   }}*/
/*{{|desc: Converts an Xbase++ value to an ANSI SQL literal according to a SQL type, length, decimals and
      flags.
    | params:
    - `xValue` Any - Value to dump as SQL text.
    - `cType` Character - SQL type name accepted by ot4xb_get_sql_type_enum().
    - `nType` Numeric - Numeric ot4xb_sql_type value.
    - `nLen` Numeric - SQL length or precision. For text/blob families, 0 means no explicit limit.
    - `nDec` Numeric - Decimal scale for Decimal values.
    - `cFlags` Character - Comma-separated SQL dump flag names accepted by ot4xb_get_sql_type_flag_enum().
    - `nFlags` Numeric - Numeric ot4xb_sql_type_flag mask.

    Returns Character - SQL literal text: numeric text for numeric types, quoted escaped text for
      character/blob/text/json types, b'...' for Bit character input, or "null" where the current type and flags
      request a SQL NULL.

    |note: Implemented specific type handling covers integer types, Decimal, Float/Double, Bit, Date,
      Char/VarChar, Binary/VarBinary, Blob/Text families and Json. Time, DateTime, TimeStamp, Year, Enum and Set
      currently fall through to the default conversion path.

    |note: Character flags control trimming, alignment, truncation, UTF-8 conversion and NotNull behavior.
      Overflow flags control numeric/decimal out-of-range handling: return null, clamp to min/max, or force zero
      depending on the selected flag.

    |include-note-id: sql-types }}*/
_XPP_REG_FUN_(OT4XB_SQL_DUMP_VALUE_ANSI)
{
   TXppParamList xpp(pl, 5);
   ot4xb_sql_type q = (xpp[2]->CheckType(XPP_CHARACTER) ? ot4xb_str_to_sql_type_enum(xpp[2]->LockStr()) : (ot4xb_sql_type)xpp[2]->GetLong());
   DWORD  flags = (DWORD)(xpp[5]->CheckType(XPP_CHARACTER) ? (DWORD)ot4xb_str_to_sql_type_flag(xpp[5]->LockStr()) : xpp[5]->GetDWord());

   int len = xpp[3]->GetLong();
   int dec = xpp[4]->GetLong();
   switch (q)
   {

   case ot4xb_sql_type::TinyInt: { sql_dump_value::to_integer_value(xpp, 0xFFFFFFFFFFFFFF80ll, 0x000000000000007Fll, flags); break; }
   case ot4xb_sql_type::SmallInt: { sql_dump_value::to_integer_value(xpp, 0xFFFFFFFFFFFF8000ll, 0x0000000000007FFFll, flags); break; }
   case ot4xb_sql_type::MediumInt: { sql_dump_value::to_integer_value(xpp, 0xFFFFFFFFFF800000ll, 0x00000000007FFFFFll, flags); break; }
   case ot4xb_sql_type::Int: { sql_dump_value::to_integer_value(xpp, 0xFFFFFFFF80000000ll, 0x000000007FFFFFFFll, flags); break; }
   case ot4xb_sql_type::BigInt: { sql_dump_value::to_integer_value(xpp, 0x8000000000000000ll, 0x7FFFFFFFFFFFFFFFll, flags); break; }
   case ot4xb_sql_type::Decimal: { sql_dump_value::to_decimal_value(xpp, len, dec, flags); break; }
   case ot4xb_sql_type::Float: case ot4xb_sql_type::Double: { sql_dump_value::to_double_value(xpp); break; }
   case ot4xb_sql_type::Bit: { sql_dump_value::to_bit_value(xpp, len); break; }
   case ot4xb_sql_type::Date: { sql_dump_value::to_date_value(xpp, flags); break; }
                            // case ot4xb_sql_type::Time: {; break; } // to-do
                            // case ot4xb_sql_type::DateTime: {; break; }
                            // case ot4xb_sql_type::TimeStamp: {; break; }
                            // case ot4xb_sql_type::Year: {; break; }
   case ot4xb_sql_type::Char: { sql_dump_value::to_char_value(xpp, len, flags); break; }
   case ot4xb_sql_type::VarChar:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::LTrim |
         (DWORD)ot4xb_sql_type_flag::RTrim |
         (DWORD)ot4xb_sql_type_flag::Truncate |
         (DWORD)ot4xb_sql_type_flag::ToUtf8 |
         (DWORD)ot4xb_sql_type_flag::NotNull);
      flags = flags | (DWORD)ot4xb_sql_type_flag::RTrim;
      sql_dump_value::to_char_value(xpp, len, flags);
      break;
   }
   case ot4xb_sql_type::Binary:
   {

      flags = flags & ((DWORD)ot4xb_sql_type_flag::LTrim |
         (DWORD)ot4xb_sql_type_flag::RTrim |
         (DWORD)ot4xb_sql_type_flag::AllTrim |
         (DWORD)ot4xb_sql_type_flag::LeftAlign |
         (DWORD)ot4xb_sql_type_flag::RightAlign |
         (DWORD)ot4xb_sql_type_flag::Truncate |
         (DWORD)ot4xb_sql_type_flag::NotNull);
      sql_dump_value::to_char_value(xpp, len, flags);
      break;
   }
   case ot4xb_sql_type::VarBinary:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::LTrim |
         (DWORD)ot4xb_sql_type_flag::RTrim |
         (DWORD)ot4xb_sql_type_flag::Truncate |
         (DWORD)ot4xb_sql_type_flag::NotNull);
      flags = flags | (DWORD)ot4xb_sql_type_flag::RTrim;
      sql_dump_value::to_char_value(xpp, len, flags);
      break;
   }
   case ot4xb_sql_type::TinyBlob:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull);
      sql_dump_value::to_char_value(xpp, 0xFF, flags);
      break;
   }
   case ot4xb_sql_type::Blob:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull);
      sql_dump_value::to_char_value(xpp, 0xFFFF, flags);
      break;
   }
   case ot4xb_sql_type::MediumBlob:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull);
      sql_dump_value::to_char_value(xpp, 0xFFFFFF, flags);
      break;
   }
   case ot4xb_sql_type::LongBlob:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull);
      sql_dump_value::to_char_value(xpp, 0, flags);
      break;
   }
   case ot4xb_sql_type::TinyText:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull | (DWORD)ot4xb_sql_type_flag::ToUtf8);
      sql_dump_value::to_char_value(xpp, 0xFF, flags);
      break;
   }
   case ot4xb_sql_type::Text:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull | (DWORD)ot4xb_sql_type_flag::ToUtf8);
      sql_dump_value::to_char_value(xpp, 0xFFFF, flags);
      break;
   }
   case ot4xb_sql_type::MediumText:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull | (DWORD)ot4xb_sql_type_flag::ToUtf8);
      sql_dump_value::to_char_value(xpp, 0xFFFFFF, flags);
      break;
   }
   case ot4xb_sql_type::LongText:
   {
      flags = flags & ((DWORD)ot4xb_sql_type_flag::NotNull | (DWORD)ot4xb_sql_type_flag::ToUtf8);
      sql_dump_value::to_char_value(xpp, 0, flags);
      break;
   }
   case ot4xb_sql_type::Json:
   {
      if( xpp[ 1 ]->CheckType( XPP_OBJECT | XPP_ARRAY ) )
      {
         TZString z( 4096 );
         json_ns::serialize_value( z, xpp[ 1 ]->con(), 0,0x00200000, 0 );
         xpp[ 1 ]->PutStrLen( z._pt_(), z.len() );
      }
      flags = flags & ( (DWORD) ot4xb_sql_type_flag::NotNull | (DWORD) ot4xb_sql_type_flag::ToUtf8 );
      sql_dump_value::to_char_value( xpp, 0xFFFF, flags );
      
      break;
  
   }
   // case ot4xb_sql_type::Enum: {; break; }
   // case ot4xb_sql_type::Set: {; break; }
   
   default:
   {

      DWORD t = xpp[1]->GetType();
      switch (t)
      {
      case XPP_LOGICAL:
      {
         sql_dump_value::to_integer_value(xpp, 0xFFFFFFFFFFFFFF80ll, 0x000000000000007Fll, flags);
         break;
      }

      case XPP_NUMERIC:
      {
         if (t & _xpp_DOUBLE)
         {
            sql_dump_value::to_double_value(xpp);
         }
         else
         {

            sql_dump_value::to_integer_value(xpp, 0x8000000000000000ll, 0x7FFFFFFFFFFFFFFFll, flags);
         }
         break;
      }
      case XPP_DATE:
      {
         sql_dump_value::to_date_value(xpp, flags);
         break;
      }
      default: // XPP_CHARACTER:
      {
         sql_dump_value::to_char_value(xpp, len, flags);
         break;
      }
      }
      break;
   }
   }
}
/*{{end-function}}*/