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
_XPP_REG_FUN_(_RGX_NEW)// _rgx_new( [@hrgx ,]  cRegExpStr [, cFlags ] ) -> hrgxe
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_SET_PATTERN)// _rgx_set_pattern( hrgx , cRegExpStr ) -> hrgxe
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_SET_FLAGS)// _rgx_set_flags( hrgx , cFlags ) -> hrgxe
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
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_DESTROY) // _rgx_destroy(@hrgx) -> 0
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_TEST) //  _rgx_test(hrgx,cStr) -> lMatch
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_REPLACE) // _rgx_replace(hrgx,cStr,cRepStr) -> cNewStr
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
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(_RGX_EXEC) // _rgx_exec(hrgx,cStr[,lSub]) -> { {pos,cb[,aSub]},...,{pos,cb[,aSub]} }
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
// -----------------------------------------------------------------------------------------------------------------
static void create_class_rgx(XppParamList pl)
{
   ContainerHandle conco = _conClsObj("_RGX");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("_RGX");
      // -----
      pc->EXPORTED();
      // -----
      pc->Var("m_hrgx");
      // -----
      pc->MethodCB("init", "{|s,pat,flg| s:m_hrgx := _rgx_new(__vdef(s:m_hrgx,0),pat,flg) , s }");
      pc->MethodCB("SetPattern", "{|s,pat| _rgx_set_pattern(s:m_hrgx,pat)}");
      pc->MethodCB("SetFlags", "{|s,fl| _rgx_set_flags(s:m_hrgx,fl)}");
      pc->MethodCB("Destroy", "{|s| s:m_hrgx:=_rgx_destroy(s:m_hrgx)}");
      pc->MethodCB("Test", "{|s,cc| _rgx_test(s:m_hrgx,cc)}");
      pc->MethodCB("Replace", "{|s,cc,cRep| _rgx_replace(s:m_hrgx,cc,cRep)}");
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

   _mk_ptr_(LPSTR, dw, 0)[0] = ((dw & 0x01000000) ? 'g' : 0x20);
   _mk_ptr_(LPSTR, dw, 0)[1] = ((dw & 0x02000000) ? 'i' : 0x20);
   _mk_ptr_(LPSTR, dw, 0)[2] = ((dw & 0x04000000) ? 'm' : 0x20);
   _mk_ptr_(LPSTR, dw, 0)[3] = 0;

   ContainerHandle pcon[4]; ZeroMemory(pcon, sizeof(pcon));
   pcon[0] = _conPutNL(0, 0);
   pcon[1] = conx; conx = 0;
   pcon[2] = _conPutCL(0, _mk_ptr_(LPSTR, dw, 0), 3);
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
//----------------------------------------------------------------------------------------------------------------------



