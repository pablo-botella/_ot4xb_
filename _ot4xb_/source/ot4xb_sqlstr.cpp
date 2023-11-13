//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__SQLSTR_MONEY) // __sqlstr_money(v, {flags,pad})
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
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
_XPP_REG_FUN_(__SQLSTR_MONEY_SUM)  // __sqlstr_money_sum(...)
{
   money_sum_internal(pl, 0);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(__SQLSTR_MONEY_SUBSTRACT) // __sqlstr_money_sum(...)
{
   money_sum_internal(pl, 1);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DWORD escape_to_sql_required_size(LPBYTE p, DWORD cb)
{
   DWORD cbo = 0;
   if (p && cb)
   {
      if (((LONG)cb) < 0)
      {
         for (; *p; p++)
         {
            switch (*p)
            {
               case 8: case '\t': case 26: case '\n': case '\r': case '\"': case '\'': case '\\': case '%': case '_':
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
      }
      else
      {
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
// escape_to_sql_buffer_flags
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
   }
   return ot4xb_sql_type::Invalid;
}
// --------------------------------------------------------------------------------------------------------------

// flags 0x1000 =quote ; 1 sz ,  2 bin  , 8  escape percent and underscore

_XPP_REG_FUN_(OT4XB_SQL_ESCAPE_STRING_ANSI)     //  ot4xb_sql_escape_string_ansi( cStr , flags ) -> Escaped Str 
{
   TXppParamList xpp(pl, 2);
   DWORD flags = xpp[2]->GetDWord();
   DWORD cb = 0;
   LPBYTE p = (LPBYTE)xpp[1]->LockStr(&cb, FALSE);
   DWORD buffer_cb = escape_to_sql_required_size((LPBYTE)p, cb) + 4;
   LPSTR buffer = (LPSTR)_xgrab(buffer_cb);
   DWORD cbo = 0;
   LPSTR po = buffer;

   if ((DWORD)escape_to_sql_buffer_flags::binary_string)
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
         value = xpp[1]->GetBool() ? 0ll : 1ll;
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
   char buffer[255] = { 0 };
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
               if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero || (DWORD)ot4xb_sql_type_flag::OvMin))
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
            negative = !(nd == abs(nd));
            cb = sprintf_s(buffer, sizeof(buffer), "%.*f", dec, nd);
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
            if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero || (DWORD)ot4xb_sql_type_flag::OvMin))
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
            if (flags & ((DWORD)ot4xb_sql_type_flag::OvZero || (DWORD)ot4xb_sql_type_flag::OvMin))
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
   sprintf_s(buffer, sizeof(buffer), "%.f", nd);
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
            if (buffer[1] < '0' || buffer[1] < '9')
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
   int max = (len < 1 ? (int)cb : len);
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
   DWORD pd_size = escape_to_sql_required_size((LPBYTE)ps, cb) + (max - cb) + 16;
   LPSTR pd = (LPSTR)_xgrab(pd_size);
   DWORD dwo = 0;
   DWORD pad = 0;
   LPSTR p = pd;

   *p = '\''; p++; dwo++;
   if (flags & (DWORD)ot4xb_sql_type_flag::Truncate)
   {
      if (cb > (DWORD)max)
      {
         cb = (DWORD)max;
      }
   }
   if (flags & (DWORD)ot4xb_sql_type_flag::RightAlign)
   {
      while ((pad + cb) < (DWORD)max)
      {
         *p = ' '; p++; pad++; dwo++;
      }
   }
   dwo += escape_to_sql_buffer((LPBYTE)ps, cb, (LPBYTE)p, pd_size - dwo, (DWORD)escape_to_sql_buffer_flags::binary_string);
   p = _mk_ptr_(LPSTR, pd, dwo);
   if (flags & (DWORD)ot4xb_sql_type_flag::LeftAlign)
   {
      while ((pad + cb) < (DWORD)max)
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
LPSTR  sql_dump_value::grip_string(TXppParamList& xpp, char alt_buffer[256], DWORD* pcb)
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
            *pcb = sprintf_s(p, sizeof(alt_buffer), "%.f", nd);
         }
         else
         {
            long nl = xpp[1]->GetLong();
            *pcb = sprintf_s(p, sizeof(alt_buffer), "%i", nl);
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
         LPSTR p = (LPSTR)alt_buffer;
         *pcb = 1;
         *p = xpp[1]->GetBool() ? '1' : '0';
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
// ------------------------------------------------------------------------------------------------------------------------------
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


// ------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_FLAG_ENUM)
{
   TXppParamList xpp(pl, 1);
   DWORD  flags = (DWORD)(xpp[1]->CheckType(XPP_CHARACTER) ? (DWORD)ot4xb_str_to_sql_type_flag(xpp[1]->LockStr()) : xpp[1]->GetDWord());
   xpp[0]->PutDWord(flags);
}
// ------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(OT4XB_GET_SQL_TYPE_ENUM)
{
   TXppParamList xpp(pl, 1);
   ot4xb_sql_type q = (xpp[1]->CheckType(XPP_CHARACTER) ? ot4xb_str_to_sql_type_enum(xpp[1]->LockStr()) : (ot4xb_sql_type)xpp[1]->GetLong());
   xpp[0]->PutLong((LONG)q);
}
// ------------------------------------------------------------------------------------------------------------------------------


_XPP_REG_FUN_(OT4XB_SQL_DUMP_VALUE_ANSI)    // ot4xb_sql_dump_value_ansi( value , 2sql_type , 3len , 4dec, 5 flags )
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
