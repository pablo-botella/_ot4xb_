//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma optimize( "t", on )
#include <ot4xb_api.h>
#include <regex>
#include <string>
#include <malloc.h> // _resetstkoflw

// regex_match_seh() is the full-protection engine (try/catch for invalid patterns + __try/__except SEH for a
// stack overflow from heavy backtracking); it is defined further down. Forward-declared here so the C export
// ot4xb_regex_match() can run its whole mechanism through it. Returns 1 = match, 0 = no match, -1 = error.
static int regex_match_seh( LPSTR pattern, LPSTR string_to_test, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags );

// regex_replace_seh() is the equivalent full-protection engine for replace (try/catch + SEH), defined further
// down. Forward-declared here so the ot4xb_regex_replace() C export can run its whole mechanism through it too.
static BOOL regex_replace_seh( std::string & text, LPSTR pattern, LPSTR replacement, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags, std::string & output_str );

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_regex_match
            | syntax_: `int ot4xb_regex_match( LPSTR pattern, LPSTR string_to_test, int flags, int match_flags )`
            | category: string/regex
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_regex_match
            | _kw_: ot4xb_regex_match, Function
   }}*/
/*{{|desc: Tests whether a whole string matches a C++ std::regex pattern using std::regex_match(). C-level
      entry to the same protected engine as the Xbase-level ot4xb_regex_match(); lStrWildCmpEx() uses it for
      its regex mode. An invalid pattern and a stack overflow from heavy backtracking (the MSVC engine is a
      recursive backtracker) are trapped internally and reported as -1 instead of crashing the process.
    | params:
    - `pattern` LPSTR - Regular expression pattern passed to std::regex.
    - `string_to_test` LPSTR - String to test.
    - `flags` int - std::regex syntax option flags (cast to std::regex::flag_type); 0 for the defaults.
    - `match_flags` int - std::regex_constants match flags (cast to
      std::regex_constants::match_flag_type); 0 for the defaults.

    Returns int - 1 = match, 0 = no match, -1 = error (invalid pattern / engine failure) }}*/
int   OT4XB_API __cdecl ot4xb_regex_match(LPSTR pattern, LPSTR string_to_test, int flags, int match_flags)
{
   // run the whole mechanism (try/catch + SEH) through regex_match_seh so C-level callers like
   // lStrWildCmpEx() are protected against BOTH an invalid pattern and a stack overflow from heavy
   // backtracking. Returns 1 = match, 0 = no match, -1 = error.
   return regex_match_seh( pattern, string_to_test, (std::regex::flag_type)flags, (std::regex_constants::match_flag_type)match_flags );
}
/*{{end-c-function}}*/
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-c-function}}*/
/*{{c-function_: ot4xb_regex_replace
            | syntax_: ```
                 LPSTR ot4xb_regex_replace( LPSTR pattern, LPSTR input_string, LPSTR replacement, DWORD * pcb_out, int flags, int match_flags )
              ```
            | category: string/regex
            | header: ot4xb_c_exported.h
            | mangled-name: ot4xb_regex_replace
            | _kw_: ot4xb_regex_replace, Function
   }}*/
/*{{|desc: Replaces text using a C++ std::regex pattern and std::regex_replace(), returning the result as a
      newly allocated string. C-level entry to the same protected engine as the Xbase-level
      ot4xb_regex_replace(). An invalid pattern and a stack overflow from heavy backtracking (the MSVC
      engine is a recursive backtracker) are trapped internally and reported as a NULL result instead of
      crashing the process.
    | params:
    - `pattern` LPSTR - Regular expression pattern passed to std::regex.
    - `input_string` LPSTR - Input string.
    - `replacement` LPSTR - Replacement string passed to std::regex_replace().
    - `pcb_out` DWORD * - Optional output: receives the length in bytes of the returned string, 0 when
      NULL is returned. May be NULL when the length is not needed.
    - `flags` int - std::regex syntax option flags (cast to std::regex::flag_type); 0 for the defaults.
    - `match_flags` int - std::regex_constants match/format flags (cast to
      std::regex_constants::match_flag_type); 0 for the defaults.

    Returns LPSTR - Result string allocated with _xgrab() (zero-terminated); the caller releases it with
      _xfree(). NULL when the engine fails, and also when the result is an empty string; *pcb_out is 0 in
      both cases. }}*/
LPSTR OT4XB_API __cdecl ot4xb_regex_replace(LPSTR pattern, LPSTR input_string, LPSTR replacement, DWORD* pcb_out, int flags, int match_flags)
{
   LPSTR p = 0;
   size_t cb = 0;
   // run the whole mechanism (try/catch + SEH) through regex_replace_seh so C-level callers are protected
   // against both an invalid pattern and a stack overflow from heavy backtracking
   std::string text(input_string);
   std::string output_str;
   if( regex_replace_seh( text, pattern, replacement, (std::regex::flag_type)flags, (std::regex_constants::match_flag_type)match_flags, output_str ) )
   {
      cb = output_str.length();
      if (cb > 0)
      {
         p = (LPSTR)_xgrab(cb + 1);
         _bcopy((LPBYTE)p, (LPBYTE)output_str.c_str(), cb);
      }
   }
   if (pcb_out)
   {
      *pcb_out = cb;
   }
   return p;
}
/*{{end-c-function}}*/
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// MSVC std::regex is a recursive backtracker: heavy patterns can overflow the thread stack, and a stack
// overflow is a SEH event, not a C++ exception. Every engine call is fenced behind __try/__except so it
// is reported as a plain failure instead of killing the process. The SEH wrappers must not create C++
// objects (C2712), so the C++ bodies live in separate engine functions.
static int regex_seh_filter( DWORD dwCode )
{
   return ( dwCode == EXCEPTION_STACK_OVERFLOW ) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static int regex_match_engine(LPSTR pattern, LPSTR string_to_test, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags)
{
   try
   {
      std::regex rgx(pattern, flags);
      return std::regex_match(string_to_test, rgx, match_flags); // 1 = match, 0 = no match
   }
   catch (...)
   {
      return -1; // invalid pattern or engine failure
   }
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static int regex_match_seh(LPSTR pattern, LPSTR string_to_test, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags)
{
   __try
   {
      return regex_match_engine(pattern, string_to_test, flags, match_flags);
   }
   __except( regex_seh_filter( GetExceptionCode() ) )
   {
      _resetstkoflw(); // restore the stack guard page after the overflow
   }
   return -1; // stack overflow (heavy backtracking): signal error
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_regex_match
            | syntax_: `ot4xb_regex_match( cPattern, cString, [nFlags], [nMatchFlags] )`
            | category: string/regex
            | _kw_: ot4xb_regex_match, Function
   }}*/
/*{{|desc: Tests a string against a C++ std::regex pattern using std::regex_match().
    | params:
    - `cPattern` Character - Regular expression pattern passed to std::regex.
    - `cString` Character - String to test.
    - `nFlags` Numeric - Optional std::regex syntax option flags. Constants are exposed in ot4xb.ch as
      ot4xb_regex_option.* and can be combined with nOr().
    - `nMatchFlags` Numeric - Optional std::regex_constants match flags. Constants are exposed in ot4xb.ch
      as ot4xb_regex_option.match_*.

    Returns Logical/NIL - .T. when the whole string matches the pattern, .F. when it does not, and NIL when
      the pattern could not be evaluated (invalid pattern, or a stack overflow from heavy backtracking). A NIL
      result therefore means "could not evaluate", not "no match"; using it raises an Xbase-level error.

    |note: This wrapper uses the C++ regular expression engine. It is the regex helper normally used by
      lStrWildCmpEx(). Because std::regex_match() tests the complete string, use an appropriate pattern when
      looking for a substring. Engine failures (e.g. an invalid pattern) are caught internally and the function
      returns NIL. A stack overflow from heavy backtracking (the MSVC engine is a recursive backtracker) is
      trapped with SEH and reported as NIL as well, instead of crashing the process; the VBScript RegExp
      wrapper is still the stronger engine for such patterns.

    |include-note-id: regex-options }}*/
_XPP_REG_FUN_(OT4XB_REGEX_MATCH)
{
   int result = -1;
   TXppParamList xpp(pl, 4);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR string_to_test = xpp[2]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[3]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[4]->GetLong();
   if (pattern && string_to_test)
   {
      result = regex_match_seh(pattern, string_to_test, flags, match_flags);
   }
   if (result < 0)
   {
      // invalid pattern / engine failure (or a non-character param): leave the return value NIL so the
      // failure surfaces as an Xbase-level error instead of a misleading .F.
   }
   else
   {
      xpp[0]->PutBool(result);
   }
}
/*{{end-function}}*/
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static BOOL regex_replace_engine(std::string & text, LPSTR pattern, LPSTR replacement, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags, std::string & output_str)
{
   try
   {
      std::regex rgx(pattern, flags);
      output_str = std::regex_replace(text, rgx, replacement, match_flags);
      return TRUE;
   }
   catch (...)
   {
      // invalid pattern or engine failure
   }
   return FALSE;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static BOOL regex_replace_seh(std::string & text, LPSTR pattern, LPSTR replacement, std::regex::flag_type flags, std::regex_constants::match_flag_type match_flags, std::string & output_str)
{
   __try
   {
      return regex_replace_engine(text, pattern, replacement, flags, match_flags, output_str);
   }
   __except( regex_seh_filter( GetExceptionCode() ) )
   {
      _resetstkoflw();
   }
   return FALSE;
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_regex_replace
            | syntax_: `ot4xb_regex_replace( cPattern, cInput, cReplacement, [nFlags], [nMatchFlags] )`
            | category: string/regex
            | _kw_: ot4xb_regex_replace, Function
   }}*/
/*{{|desc: Replaces text using a C++ std::regex pattern and std::regex_replace().
    | params:
    - `cPattern` Character - Regular expression pattern passed to std::regex.
    - `cInput` Character - Input string.
    - `cReplacement` Character - Replacement string passed to std::regex_replace().
    - `nFlags` Numeric - Optional std::regex syntax option flags.
    - `nMatchFlags` Numeric - Optional std::regex_constants match/format flags. Replacement format flags
      such as ot4xb_regex_option.format_sed and ot4xb_regex_option.format_first_only can be used here.

    Returns Character/NIL - Resulting string after applying the replacement, or NIL if the C++ regex engine
      reports an exception.

    |note: This wrapper uses the C++ regular expression engine. Failures on very complex or invalid
      expressions are caught internally and make the function return NIL instead of propagating the exception.
      A stack overflow from heavy backtracking (the MSVC engine is a recursive backtracker) is trapped with
      SEH and reported as NIL as well, instead of crashing the process; the VBScript RegExp wrapper is still
      the stronger engine for such patterns.

    |include-note-id: regex-options }}*/
_XPP_REG_FUN_(OT4XB_REGEX_REPLACE)
{
   TXppParamList xpp(pl, 5);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR input_string = xpp[2]->LockStr();
   LPSTR replacement = xpp[3]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[4]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[5]->GetLong();

   if( pattern && input_string && replacement )
   {
      std::string text(input_string);
      std::string output_str;
      if( regex_replace_seh(text, pattern, replacement, flags, match_flags, output_str) )
      {
         xpp[0]->PutStrLen((LPSTR)output_str.c_str(), output_str.length());
      }
   }
   // on failure, or a non-character param (LockStr returns NULL), the return value stays NIL
}
/*{{end-function}}*/
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
static BOOL ot4xb_regex_search_seh(LPCSTR ps, std::cmatch & cm, std::regex & rgx, std::regex_constants::match_flag_type match_flags, BOOL & bOk)
{
   __try
   {
      return ot4xb_regex_search(ps, cm, rgx, match_flags, bOk);
   }
   __except( regex_seh_filter( GetExceptionCode() ) )
   {
      _resetstkoflw();
      bOk = FALSE;
   }
   return FALSE;
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: ot4xb_regex_search
            | syntax_: `ot4xb_regex_search( cPattern, cInput, [nFlags], [nMatchFlags], [lSubMatches] )`
            | category: string/regex
            | _kw_: ot4xb_regex_search, Function
   }}*/
/*{{|desc: Searches an input string with a C++ std::regex pattern and returns all matches.
    | params:
    - `cPattern` Character - Regular expression pattern passed to std::regex.
    - `cInput` Character - Input string to search.
    - `nFlags` Numeric - Optional std::regex syntax option flags.
    - `nMatchFlags` Numeric - Optional std::regex_constants match flags.
    - `lSubMatches` Logical - When .T., each result entry is an array with the full match and captured
      submatches. When .F. or omitted, each result entry is the matched text.

    Returns Array/NIL - Array with the matches found, or NIL if the C++ regex engine reports an exception.

    |note: The pattern compilation and the search loop are protected with try/catch because invalid patterns
      and some complex expressions can fail inside the C++ regex engine. On such failures the function returns
      NIL instead of propagating the exception. A stack overflow from heavy backtracking (the MSVC engine is
      a recursive backtracker) is trapped with SEH and reported as NIL as well, instead of crashing the
      process; the VBScript RegExp wrapper is still the stronger engine for such patterns. }}*/
_XPP_REG_FUN_(OT4XB_REGEX_SEARCH )
{

   TXppParamList xpp(pl, 5);
   LPSTR pattern = xpp[1]->LockStr();
   LPSTR input_string = xpp[2]->LockStr();
   std::regex::flag_type flags = (std::regex::flag_type)xpp[3]->GetLong();
   std::regex_constants::match_flag_type match_flags = (std::regex_constants::match_flag_type)xpp[4]->GetLong();
   BOOL bSubMatches = xpp[5]->GetBool();
   std::regex rgx;
   std::cmatch cm;
   LPCSTR ps = (LPCSTR)input_string;
   DWORD result_size = 16;
   DWORD result_count = 0;
   ContainerHandle  cona_result = _conNewArray(1, result_size);
   BOOL bOk = ( pattern && input_string );   // a non-character param (LockStr returns NULL) yields NIL - nothing to evaluate
   if( bOk )
   {
      try
      {
         rgx.assign(pattern, flags); // the compile also throws on invalid patterns - keep the NIL contract
      }
      catch (...)
      {
         bOk = FALSE;
      }
   }
   while( bOk && ot4xb_regex_search_seh(ps, cm, rgx, match_flags,bOk) )
   {
      result_count++;
      if (result_count > result_size)
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
            _conArrayPut(cona, item, dw +1 , 0);
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
      if( cm[0].length() == 0 )
      {
         // empty match (e.g. "a*"): the cursor did not move - step over one char
         // or the same empty match would be found forever
         if( *ps == 0 ) break;
         ps++;
      }
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
/*{{end-function}}*/
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
