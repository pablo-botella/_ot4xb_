//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
#include <ot4xb_api.h>
#import <vbscript.dll> tlbid(3) no_namespace

// -----------------------------------------------------------------------------------------------------------------
BEGIN_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
HRESULT dhInitializeImp(BOOL bInitializeCOM, BOOL bUnicode);
void dhUninitialize(BOOL bUninitializeCOM);
HRESULT dhToggleExceptions(BOOL bShow);
// -----------------------------------------------------------------------------------------------------------------
END_EXTERN_C
// -----------------------------------------------------------------------------------------------------------------
static IRegExp2* _rgx_init_interface(LONG npi)
{

   if (GetTlsHeapManager()->m_disphelper_refcount < 1)
   {
      dhInitializeImp(TRUE, TRUE);
      dhToggleExceptions(FALSE);
      GetTlsHeapManager()->m_disphelper_refcount = 1;
   }


   if (npi)
   {
      return (IRegExp2*)npi;
   }
   IRegExp2Ptr rgx(__uuidof(RegExp));
   IRegExp2* hrgx = (IRegExp2*)rgx.Detach();
   return hrgx;
}
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_new
            | syntax_: `_rgx_new( [@hRgx,] [cPattern], [cFlags] )`
            | category: string/regex
            | _kw_: regexp, VBScript RegExp, ActiveX, regular expression engine, create
   }}*/
/*{{|desc: Creates or reuses a regular expression engine based on the system VBScript/IE RegExp ActiveX
      component.
    | params:
    - `hRgx` Numeric by reference - Optional existing RegExp engine handle. When supplied, the same engine
      is reused and the parameter is updated with the resulting handle.
    - `cPattern` Character - Optional regular expression pattern.
    - `cFlags` Character - Optional flag string. The supported letters are "g" for Global, "i" for
      IgnoreCase, and "m" for Multiline.

    Returns Numeric - Handle to the underlying IRegExp2 ActiveX object.

    |note: This is the low-level handle function used by the _RGX class. Call _rgx_destroy() when the handle is
      no longer needed. }}*/
_XPP_REG_FUN_(_RGX_NEW)
{


   TXppParamList xpp(pl, 3);
   IRegExp2* hrgx = 0;
   UINT shp = 0; // shift params if first is numeric

   if (xpp[1]->CheckType(XPP_NUMERIC))
   {
      hrgx = _rgx_init_interface(xpp[1]->GetLong());
      xpp[1]->PutLong((LONG)hrgx);
      shp = 1;
   }
   else
   {
      hrgx = _rgx_init_interface(0);
   }
   xpp[0]->PutLong((LONG)hrgx);
   if (hrgx)
   {
      IRegExp2Ptr rgx(hrgx, true);

      if (xpp[(shp + 1)]->CheckType(XPP_CHARACTER))
      {
         _bstr_t bs = _bstr_t(xpp[(shp + 1)]->LockStr());
         rgx->Pattern = bs;
         xpp[(shp + 1)]->UnlockStr();

      }
      if (xpp[(shp + 2)]->CheckType(XPP_CHARACTER))
      {
         ULONG cb = 0;
         LPSTR p = xpp[(shp + 2)]->LockStr(&cb);
         ULONG n;
         for (n = 0; n < cb; n++)
         {
            switch (p[n])
            {
            case 'g': case 'G':
            {
               rgx->Global = VARIANT_TRUE;
               break;
            }
            case 'm': case 'M':
            {
               rgx->Multiline = VARIANT_TRUE;
               break;
            }
            case 'i': case 'I':
            {
               rgx->IgnoreCase = VARIANT_TRUE;
               break;
            }
            }
         }
         xpp[(shp + 2)]->UnlockStr();
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_set_pattern
            | syntax_: `_rgx_set_pattern( hRgx, cPattern )`
            | category: string/regex
            | _kw_: regexp, pattern, VBScript RegExp, set pattern
   }}*/
/*{{|desc: Sets the pattern on an existing _RGX ActiveX regular expression engine.
    | params:
    - `hRgx` Numeric - RegExp engine handle returned by _rgx_new().
    - `cPattern` Character - Regular expression pattern.

    Returns NIL }}*/
_XPP_REG_FUN_(_RGX_SET_PATTERN)
{
   TXppParamList xpp(pl, 2);
   if (xpp[1]->CheckType(XPP_NUMERIC) && xpp[2]->CheckType(XPP_CHARACTER))
   {
      IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
      if (hrgx)
      {
         IRegExp2Ptr rgx(hrgx, true);
         BSTR bs = xpp[2]->StrDupBSTR();
         rgx->put_Pattern(bs);
         SysFreeString(bs);
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_set_flags
            | syntax_: `_rgx_set_flags( hRgx, cFlags )`
            | category: string/regex
            | _kw_: regexp, Global, IgnoreCase, Multiline, flags
   }}*/
/*{{|desc: Sets the Global, IgnoreCase and Multiline flags on an existing _RGX engine.
    | params:
    - `hRgx` Numeric - RegExp engine handle returned by _rgx_new().
    - `cFlags` Character - Flag string. "g" enables Global, "i" enables IgnoreCase, and "m" enables
      Multiline.

    Returns NIL

    |note: Calling this function resets all three flags to false before applying the letters present in cFlags. }}*/
_XPP_REG_FUN_(_RGX_SET_FLAGS)
{
   TXppParamList xpp(pl, 2);
   if (xpp[1]->CheckType(XPP_NUMERIC) && xpp[2]->CheckType(XPP_CHARACTER))
   {
      IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
      if (hrgx)
      {
         IRegExp2Ptr rgx(hrgx, true);
         ULONG cb = 0;
         LPSTR p = xpp[2]->LockStr(&cb);
         ULONG n;
         rgx->Global = VARIANT_FALSE;
         rgx->Multiline = VARIANT_FALSE;
         rgx->IgnoreCase = VARIANT_FALSE;
         for (n = 0; n < cb; n++)
         {
            switch (p[n])
            {
            case 'g': case 'G':
            {
               rgx->Global = VARIANT_TRUE;
               break;
            }
            case 'm': case 'M':
            {
               rgx->Multiline = VARIANT_TRUE;
               break;
            }
            case 'i': case 'I':
            {
               rgx->IgnoreCase = VARIANT_TRUE;
               break;
            }
            }
         }
         xpp[2]->UnlockStr();
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_destroy
            | syntax_: `_rgx_destroy( @hRgx )`
            | category: string/regex
            | _kw_: regexp, release engine, destroy
   }}*/
/*{{|desc: Releases an _RGX ActiveX regular expression engine handle.
    | params:
    - `hRgx` Numeric by reference - RegExp engine handle to release. The parameter is set to 0.

    Returns Numeric - Always returns 0. }}*/
_XPP_REG_FUN_(_RGX_DESTROY)
{
   TXppParamList xpp(pl, 1);
   if (xpp[1]->CheckType(XPP_NUMERIC))
   {
      IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
      if (hrgx)
      {
         hrgx->Release();
      }
      hrgx = 0;
      xpp[1]->PutLong(0);
   }
   xpp[0]->PutLong(0);

}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_test
            | syntax_: `_rgx_test( hRgx, cString )`
            | category: string/regex
            | _kw_: regexp, test, match, VBScript RegExp
   }}*/
/*{{|desc: Tests a string with an _RGX ActiveX regular expression engine.
    | params:
    - `hRgx` Numeric - RegExp engine handle returned by _rgx_new().
    - `cString` Character - String to test.

    Returns Logical/NIL - .T. when the pattern matches, .F. when it does not match, or NIL on engine errors. }}*/
_XPP_REG_FUN_(_RGX_TEST)
{
   TXppParamList xpp(pl, 2);
   try
   {
      if (xpp[1]->CheckType(XPP_NUMERIC) && xpp[2]->CheckType(XPP_CHARACTER))
      {
         IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
         if (hrgx)
         {
            IRegExp2Ptr rgx(hrgx, true);
            _bstr_t bs(xpp[2]->StrDupBSTR(), FALSE);
            xpp[0]->PutBool((rgx->Test(bs) == VARIANT_TRUE ? 1 : 0));
            SysFreeString(bs.Detach());
         }
      }
   }
   catch (...)
   {
      xpp[0]->Put();
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_replace
            | syntax_: `_rgx_replace( hRgx, cString, cReplacement )`
            | category: string/regex
            | _kw_: regexp, replace, substitution, VBScript RegExp
   }}*/
/*{{|desc: Replaces text using an _RGX ActiveX regular expression engine.
    | params:
    - `hRgx` Numeric - RegExp engine handle returned by _rgx_new().
    - `cString` Character - Input string.
    - `cReplacement` Character - Replacement string understood by the VBScript RegExp engine.

    Returns Character/NIL - Resulting string, or NIL if the operation fails. }}*/
_XPP_REG_FUN_(_RGX_REPLACE)
{
   TXppParamList xpp(pl, 3);
   if (xpp[1]->CheckType(XPP_NUMERIC) && xpp[2]->CheckType(XPP_CHARACTER) && xpp[3]->CheckType(XPP_CHARACTER))
   {
      IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
      if (hrgx)
      {
         IRegExp2Ptr rgx(hrgx, true);
         BSTR bs_str = xpp[2]->StrDupBSTR();
         _variant_t v_pat;
         BSTR bs = 0;
         _variant_t_SetString(&v_pat, xpp[3]->LockStr());
         xpp[3]->UnlockStr();
         try
         {
            if (SUCCEEDED(rgx->raw_Replace(bs_str, v_pat, &bs)))
            {
               xpp[0]->PutBSTR2a(bs);
            }
         }
         catch (...) { ; }
         _variant_t_Clear(&v_pat);
         if (bs_str) { SysFreeString(bs_str); }
         if (bs) { SysFreeString(bs); }
      }
   }
}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx_exec
            | syntax_: `_rgx_exec( hRgx, cString, [lSubMatches] )`
            | category: string/regex
            | _kw_: regexp, exec, match positions, submatches, VBScript RegExp
   }}*/
/*{{|desc: Executes an _RGX ActiveX regular expression engine and returns match positions.
    | params:
    - `hRgx` Numeric - RegExp engine handle returned by _rgx_new().
    - `cString` Character - Input string.
    - `lSubMatches` Logical - When .T., each match row includes an array with captured submatches.

    Returns Array/NIL - Array of rows { nPos, nLen } or { nPos, nLen, aSubMatches }. nPos is the zero-based
      FirstIndex value returned by the ActiveX engine. }}*/
_XPP_REG_FUN_(_RGX_EXEC)
{
   TXppParamList xpp(pl, 3);
   try
   {
      BOOL bSub = xpp[3]->GetBool();

      if (xpp[1]->CheckType(XPP_NUMERIC) && xpp[2]->CheckType(XPP_CHARACTER))
      {
         IRegExp2* hrgx = (IRegExp2*)xpp[1]->GetLong();
         if (hrgx)
         {
            IRegExp2Ptr rgx(hrgx, true);
            _bstr_t bs(xpp[2]->StrDupBSTR(), FALSE);
            IMatchCollection2Ptr mc;
            mc = rgx->Execute(bs);
            SysFreeString(bs.Detach());
            ULONG nMatches = (ULONG)(mc->Count);

            if (((int)nMatches) < 0) { nMatches = 0; }
            xpp[0]->PutNewArray(2, nMatches, (bSub ? 3 : 2), 0);
            ContainerHandle cona = xpp[0]->con();
            ULONG nMatch;
            for (nMatch = 0; nMatch < nMatches; nMatch++)
            {
               IMatch2Ptr mm = mc->Item[nMatch];
               _conArrayPutNL(cona, mm->FirstIndex, nMatch + 1, 1, 0);
               _conArrayPutNL(cona, mm->Length, nMatch + 1, 2, 0);
               if (bSub)
               {
                  ISubMatchesPtr smc = mm->SubMatches;
                  ULONG nSubMatches = (ULONG)(smc->Count);
                  if (((int)nSubMatches) < 0) { nSubMatches = 0; }
                  ULONG nn;
                  ContainerHandle cona_tmp = _conNewArray(1, nSubMatches);
                  for (nn = 0; nn < nSubMatches; nn++)
                  {
                     _variant_t v = smc->Item[nn];
                     _conArrayPutBSTR2a(cona_tmp, _bstr_t(v), nn + 1, 0);
                  }
                  _conArrayPut(cona, cona_tmp, nMatch + 1, 3, 0);
                  _conRelease(cona_tmp);
                  cona_tmp = NULLCONTAINER;
               }
            }
            xpp[2]->UnlockStr();
         }
      }
   }
   catch (...)
   {
      xpp[0]->Put();
   }

}
/*{{end-function}}*/
// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: _rgx
            | _slug_: _rgx
            | class-function: _rgx
            | category: string/regex
            | desc: Xbase++ class wrapper over the system VBScript/IE RegExp ActiveX engine. Calling _rgx() with no
              parameters returns this class object; calling _rgx( cCommand, cString [, cReplacement] ) executes a
              one-shot command as a plain function instead. The methods delegate to the low-level _rgx_* functions
              through the engine handle kept in :m_hrgx.
            | note: _rgx is the legacy regular expression class. It uses the VBScript RegExp syntax exposed by the
              ActiveX component installed with Windows/Internet Explorer scripting support.
            | note: cFlags is a character string. The supported letters are "g" for Global, "i" for IgnoreCase, and
              "m" for Multiline.
            | example: ```
              local rx := _RGX():New( "^[a-z]+$", "i" )
              ? rx:Test( "PATATA" )
              rx:Destroy()
              ```
   | _kw_: regexp, VBScript RegExp, ActiveX, regular expression, class
   }}*/
static void create_class_rgx(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("_RGX");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("_RGX");
      /*{{|:**BEGIN CLASS  _rgx** }}*/
      // -----
      pc->EXPORTED();
      // -----
      /*{{|ivar_: - VAR m_hrgx
               | desc_: Internal IRegExp2 engine handle, created through _rgx_new() and released by ::Destroy().
      }}*/
      pc->Var("m_hrgx");
      // -----
      /*{{|method_: - METHOD init( [cPattern], [cFlags] )
               | return: Self
               | desc_: Creates or reuses the internal ActiveX RegExp engine; invoked through _rgx():New( [cPattern],
                 [cFlags] ) -> oRgx.
      }}*/
      pc->MethodCB("init", "{|s,pat,flg| s:m_hrgx := _rgx_new(__vdef(s:m_hrgx,0),pat,flg) , s }");
      /*{{|method_: - METHOD SetPattern( cPattern ) | return: NIL | desc_: Sets the regular expression pattern. }}*/
      pc->MethodCB("SetPattern", "{|s,pat| _rgx_set_pattern(s:m_hrgx,pat)}");
      /*{{|method_: - METHOD SetFlags( cFlags )
               | return: NIL
               | desc_: Sets the "g", "i" and "m" ActiveX RegExp flags. All three flags are reset before the letters
                 present in cFlags are applied.
      }}*/
      pc->MethodCB("SetFlags", "{|s,fl| _rgx_set_flags(s:m_hrgx,fl)}");
      /*{{|method_: - METHOD Destroy()
               | return: 0
               | desc_: Releases the internal ActiveX RegExp engine and clears the handle.
      }}*/
      pc->MethodCB("Destroy", "{|s| s:m_hrgx:=_rgx_destroy(s:m_hrgx)}");
      /*{{|method_: - METHOD Test( cString )
               | return: lMatch / NIL
               | desc_: Tests cString with the current pattern: .T. on match, .F. on no match, NIL on engine errors.
      }}*/
      pc->MethodCB("Test", "{|s,cc| _rgx_test(s:m_hrgx,cc)}");
      /*{{|method_: - METHOD Replace( cString, cReplacement )
               | return: cResult / NIL
               | desc_: Replaces text with the current pattern.
      }}*/
      pc->MethodCB("Replace", "{|s,cc,cRep| _rgx_replace(s:m_hrgx,cc,cRep)}");
      /*{{|method_: - METHOD Exec( cString, [lSubMatches] )
               | return: aMatches / NIL
               | desc_: Returns match positions and optionally captured submatches, as rows { nPos, nLen } or
                 { nPos, nLen, aSubMatches }.
      }}*/
      /*{{|:**END CLASS** }}*/
      pc->MethodCB("Exec", "{|s,cc,lSub| _rgx_exec(s:m_hrgx,cc,lSub)}");
      // -----
      conco = pc->Create();
      delete pc;
      if (conco == NULLCONTAINER)
      {
         _ret(pl);
         return;
      }
   }
   _conReturn(pl, conco);
   _conRelease(conco);
}
/*{{end-class}}*/
// -----------------------------------------------------------------------------------------------------------------
static void rgx_utility(XppParamList pl, DWORD np) // "operation.flags:expression" , string , replace  // test,replace,exec
{
   LPSTR buffer = 0;
   DWORD  op = 0;
   DWORD  dw = 0;
   ContainerHandle conx = 0;
   DWORD engine = 0;
   ContainerHandle conr = 0;
   BOOL bSubMatches = 0;
   ContainerHandle pcon[4] = { 0 };   // declared up here so every early "goto cleanup" lands on a zeroed array

   if (np < 2) { goto cleanup; }
   if (!(_partype(pl, 1) & XPP_CHARACTER)) { goto cleanup; }
   if (!(_partype(pl, 2) & XPP_CHARACTER)) { goto cleanup; }





   buffer = _pszParam(pl, 1);

   if (buffer)
   {
      switch (buffer[0])
      {
      case 't': case 'T': op = 1; break;
      case 'r': case 'R': op = 2; break;
      case 'e': case 'E': op = 3; break;
      }
      if (op == 2) { if (np < 3) { goto cleanup; } }
      if (op == 2) { if (!(_partype(pl, 3) & XPP_CHARACTER)) { goto cleanup; } }
      if (op)
      {
         LPSTR p;
         for (p = buffer; *p && (!conx); p++)
         {
            switch (*p)
            {
            case ':': conx = _conPutC(conx, _mk_ptr_(LPSTR, p, 1)); break;
            case '.': dw |= 0x10; break;
            case 'g': case 'G': dw |= (dw & 0x10 ? 0x01000000 : 0); break;
            case 'i': case 'I': dw |= (dw & 0x10 ? 0x02000000 : 0); break;
            case 'm': case 'M': dw |= (dw & 0x10 ? 0x04000000 : 0); break;
            case 's': case 'S': if (dw & 0x10) { bSubMatches = 1; } break;
            }
         }
      }
      _xfree(buffer); buffer = 0;
   }
   if (buffer) { goto cleanup; } // must be unreacheable
   if (!conx) { goto cleanup; }
   if ((op > 3) || (op < 1)) { goto cleanup; }

   _mk_ptr_(LPSTR, &dw, 0)[0] = ((dw & 0x01000000) ? 'g' : 0x20);
   _mk_ptr_(LPSTR, &dw, 0)[1] = ((dw & 0x02000000) ? 'i' : 0x20);
   _mk_ptr_(LPSTR, &dw, 0)[2] = ((dw & 0x04000000) ? 'm' : 0x20);
   _mk_ptr_(LPSTR, &dw, 0)[3] = 0;

   pcon[0] = _conPutNL(0, 0);
   pcon[1] = conx; conx = 0;
   pcon[2] = _conPutCL(0, _mk_ptr_(LPSTR, &dw, 0), 3);
   pcon[3] = _conPutNL(0, 0);
   if (_conCallPa(pcon[3], "_RGX_NEW", 3, pcon) == 0)
   {
      _conGetLong(pcon[3], _mk_ptr_(LPLONG, &engine, 0));
   }
   for (dw = 0; dw < 4; dw++) { if (pcon[dw]) { _conRelease(pcon[dw]); } pcon[dw] = 0; }
   if (!engine) { goto cleanup; }

   conr = _conPut(conr, 0);

   switch (op)
   {
   case 1: // test
   {
      pcon[0] = _conPutNL(0, engine);
      pcon[1] = _conParam(pl, 2, 0);
      _conCallPa(conr, "_RGX_TEST", 2, pcon);
      goto cleanup;
   }
   case 2:  // replace
   {
      pcon[0] = _conPutNL(0, engine);
      pcon[1] = _conParam(pl, 2, 0);
      pcon[2] = _conParam(pl, 3, 0);
      _conCallPa(conr, "_RGX_REPLACE", 3, pcon);
      goto cleanup;
   }
   case 3:  // exec
   {
      pcon[0] = _conPutNL(0, engine);
      pcon[1] = _conParam(pl, 2, 0);
      pcon[2] = _conPutL(0, bSubMatches);
      _conCallPa(conr, "_RGX_EXEC", 3, pcon);
      goto cleanup;
   }
   }
cleanup:;
   for (dw = 0; dw < 4; dw++) { if (pcon[dw]) { _conRelease(pcon[dw]); } pcon[dw] = 0; }
   if (engine) { _conCallVoid("_RGX_DESTROY", engine); engine = 0; }
   if (conx) { _conRelease(conx); conx = 0; }
   if (buffer) { _xfree(buffer); buffer = 0; }
   if (conr) { _conReturn(pl, conr); _conRelease(conr); conr = 0; }
   else { _ret(pl); }

}
//----------------------------------------------------------------------------------------------------------------------
/*{{begin-function}}*/
/*{{function_: _rgx
            | syntax_: `_rgx( cCommand, cString [, cReplacement] ) -> xResult`
            | category: string/regex
            | _kw_: regexp, one shot, VBScript RegExp, regular expression command
   }}*/
/*{{|desc: Executes a one-shot legacy ActiveX regular expression command: a temporary engine is created for
      the command and destroyed before returning. Called without parameters, _rgx() acts instead as the class
      function of the _rgx class and returns its class object.
    | params:
    - `cCommand` Character - Command in the form "op[.flags]:pattern". op is "t" for test, "r" for
      replace, or "e" for exec. Flags after the dot are "g", "i" and "m"; for the "e" operation, "s" also
      requests captured submatches in the returned rows.
    - `cString` Character - Input string.
    - `cReplacement` Character - Replacement string, required only for the "r" operation.

    Returns Logical/Character/Array/NIL - The result of Test, Replace or Exec, or NIL if the command cannot
      be executed. With no parameters, the _rgx class object.

    |example: ```
      ? _rgx( "t.i:^[a-z]+$", "PATATA" )
      ? _rgx( "r.g:\d+", "a1 b2", "#" )
      ? _rgx( "e.gs:(\w+)=(\d+)", "a=1 b=2" )
      ```

    |seealso: See also: {{ilink: <function _rgx_new> _rgx_new}}, {{ilink: <function _rgx_test> _rgx_test}}, {{ilink: <function _rgx_replace> _rgx_replace}}, {{ilink: <function _rgx_exec> _rgx_exec}} }}*/
_XPP_REG_FUN_(_RGX)
{
   DWORD np = _partype(pl, 0);
   if (np)
   {
      rgx_utility(pl, np);
   }
   else
   {
      create_class_rgx(pl);
   }
}
/*{{end-function}}*/
//----------------------------------------------------------------------------------------------------------------------



