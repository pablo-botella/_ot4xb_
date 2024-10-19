//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <regex>
#include <string>


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL  OT4XB_API __cdecl ot4xb_regex_match(LPSTR pattern, LPSTR string_to_test, int flags, int match_flags)
{

   BOOL result;
   std::regex rgx(pattern, (std::regex::flag_type)flags);
   result = std::regex_match(string_to_test, rgx, (std::regex_constants::match_flag_type)match_flags);
   return result;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LPSTR OT4XB_API __cdecl ot4xb_regex_replace(LPSTR pattern, LPSTR input_string, LPSTR replacement, DWORD* pcb_out, int flags, int match_flags)
{
   LPSTR p = 0;
   size_t cb = 0;
   std::string text(input_string);
   std::regex rgx(pattern, (std::regex::flag_type)flags);
   std::string output_str = std::regex_replace(text, rgx, replacement, (std::regex_constants::match_flag_type)match_flags);

   cb = output_str.length();
   if (cb > 0)
   {
      p = (LPSTR)_xgrab(cb + 1);
      _bcopy((LPBYTE)p, (LPBYTE)output_str.c_str(), cb);
   }
   if (pcb_out)
   {
      *pcb_out = cb;
   }
   return p;

}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_regex_match(1 pattern, 2 string_to_test, 3 flags, 4 match_flags) -> lMatch
_XPP_REG_FUN_(OT4XB_REGEX_MATCH)
{
   BOOL result = FALSE;
   TXppParamList xpp(pl, 4);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR string_to_test = xpp[2]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[3]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[4]->GetLong();
   if (pattern && string_to_test)
   {
      std::regex rgx(pattern, flags);
      result = std::regex_match(string_to_test, rgx, match_flags);
   }
   xpp[0]->PutBool(result);
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_regex_replace(1 pattern, 2 input_string, 3 replacement, 4flags, 5 match_flags)
_XPP_REG_FUN_(OT4XB_REGEX_REPLACE)
{
   TXppParamList xpp(pl, 5);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR input_string = xpp[2]->LockStr();
   LPSTR replacement = xpp[3]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[4]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[5]->GetLong();

   std::string text(input_string);
   std::regex rgx(pattern, flags);
   std::string output_str = std::regex_replace(text, rgx, replacement, match_flags);

   xpp[0]->PutStrLen((LPSTR)output_str.c_str(), output_str.length());

}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL ot4xb_regex_search(LPCSTR ps, std::cmatch & cm, std::regex & rgx, std::regex_constants::match_flag_type match_flags, BOOL & bOk)
{
   BOOL result = FALSE;
   bOk = TRUE;
   try
   {
      result = std::regex_search(ps, cm, rgx, match_flags);
   }
   catch (...)
   {
      bOk = FALSE;
      result = FALSE;
   }
   return result;

}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ot4xb_regex_extract(1 pattern, 2 input_string,3flags, 4 match_flags , 5 lSub)
_XPP_REG_FUN_(OT4XB_REGEX_SEARCH )
{

   TXppParamList xpp(pl, 5);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR input_string = xpp[2]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[3]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[4]->GetLong();
   BOOL bSubMatches = xpp[5]->GetBool();
   std::regex rgx(pattern, flags);
   std::cmatch cm;
   LPCSTR ps = (LPCSTR)input_string;
   DWORD result_size = 16;
   DWORD result_count = 0;
   ContainerHandle  cona_result = _conNewArray(1, result_size);
   BOOL bOk = TRUE;
   
   while( ot4xb_regex_search(ps, cm, rgx, match_flags,bOk) )
   {
      result_count++;
      if (result_count < result_size)
      {
         result_size += min( result_size , 1024 );
         _conResizeA(cona_result, result_size);
      }
      if (bSubMatches)
      {
         DWORD dw_max = cm.size();
         ContainerHandle cona = _conNewArray(1, dw_max );
         for (DWORD dw = 0; dw < dw_max; dw++)
         {
            ContainerHandle  item = _conPutCL(NULLCONTAINER, (LPSTR)cm[dw].first, cm[dw].length());
            _conArrayPut(cona_result, item, dw +1 , 0);
            _conRelease(item);
            item = NULLCONTAINER;
         }
         _conArrayPut(cona_result, cona, result_count, 0);
         _conRelease(cona);
         cona = NULLCONTAINER;
      }
      else
      {
         ContainerHandle  item = _conPutCL(NULLCONTAINER, (LPSTR)cm[0].first, cm[0].length());
         _conArrayPut(cona_result, item, result_count, 0);
         _conRelease(item);
         item = NULLCONTAINER;
      }
      
      
      ps = cm[0].second;
   }
   if (result_size > result_count)
   {
      _conResizeA(cona_result, result_count);
   }
   if (bOk) 
   {
      xpp[0]->Put(cona_result);
   }
   _conRelease(cona_result);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------