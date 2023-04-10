//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_cStr( TXbClsParams * px );
static void UnicodeDynStr_wStr( TXbClsParams * px );
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API  LPWSTR mb2w( LPSTR pu ,int cb ,int* pcc , UINT nAcp , DWORD nFlags)
{
   int    cc = 0;
   LPWSTR  pw = 0;
   if( !pu ) return 0;
   if( cb == -1 ) cb = lstrlenA(pu);
   cc = MultiByteToWideChar(nAcp,nFlags,pu,(int)cb,0,0);
   pw = (LPWSTR) _xgrab( (cc * 2) +2 );
   cc = MultiByteToWideChar(nAcp,nFlags,pu,(int)cb,pw,cc+1);
   if( pcc ) pcc[0] = cc;
   return pw;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API BSTR pAnsi2BSTR( LPSTR pAnsi , int cb)
{
   int    cc = 0;
   LPWSTR  pw = 0;
   if( !pAnsi ) return 0;
   if( cb == -1 ) cb = lstrlenA(pAnsi);
   cc = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)cb,0,0);
   pw = (LPWSTR) SysAllocStringLen(0,cc);
   ZeroMemory(pw,(cc*2));
   cc = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)cb,pw,cc+1);
   return (BSTR) pw;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR w2mb(LPWSTR pw , int cc,int* pcb, UINT nAcp , DWORD nFlags)
{
   int   cb = 0;
   LPSTR  pu = 0;
   if( !pw ) return 0;
   if( cc == -1 ) cc = lstrlenW(pw);
   cb = WideCharToMultiByte(nAcp,nFlags,pw,cc,NULL,0,0,0);
   pu = (LPSTR) _xgrab( cb + 2);
   cb = WideCharToMultiByte(nAcp,nFlags,pw,cc,pu,cb+1,0,0);
   if( pcb ) pcb[0] = cb;
   return pu;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR mb2mb(LPSTR pa ,int cb,int* pcb,UINT nAcpFrom , UINT nAcpTo , DWORD nFlags1, DWORD nFlags2)
{
   LPSTR  pu = 0;
   if(pa)
   {
      int    cc = 0;
      LPWSTR pw = mb2w(pa,cb,&cc,nAcpFrom,nFlags1);
      if( pw ) 
      {
         pu = w2mb(pw,cc,pcb,nAcpTo,nFlags2);         
         _xfree((void*) pw);
         pw = 0;
      }
   }
   return pu;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR w2utf8(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_UTF8,0); }
OT4XB_API LPSTR w2ansi(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_ACP,0); }
OT4XB_API LPSTR w2oem(LPWSTR pw , int cc,int* pcb){ return w2mb(pw,cc,pcb,CP_OEMCP,0); }
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API  LPWSTR utf82w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_UTF8,0); }
OT4XB_API  LPWSTR ansi2w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_ACP,0); }
OT4XB_API  LPWSTR oem2w( LPSTR pu ,int cb ,int* pcc ){ return mb2w(pu,cb,pcc,CP_OEMCP,0); }
//----------------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR ansi2utf8( LPSTR pa ,int cb,int* pcb){ return mb2mb(pa,cb,pcb,CP_ACP,CP_UTF8,0,0);}
OT4XB_API LPSTR oem2utf8(  LPSTR po ,int cb,int* pcb){ return mb2mb(po,cb,pcb,CP_OEMCP,CP_UTF8,0,0);}
OT4XB_API LPSTR utf82ansi( LPSTR pu ,int cb,int* pcb){ return mb2mb(pu,cb,pcb,CP_UTF8,CP_ACP,0,0);}
OT4XB_API LPSTR utf82oem(  LPSTR pu ,int cb,int* pcb){ return mb2mb(pu,cb,pcb,CP_UTF8,CP_OEMCP,0,0);}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSZANSI2WIDE(XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1 , &bByRef , XPP_CHARACTER );
   ContainerHandle conr = NULLCONTAINER;
   if( conc != NULLCONTAINER )
   {
      LPSTR pAnsi = (LPSTR) 0;
      ULONG nLen  = 0;
      if(  ot4xb_conRLockC(conc, &pAnsi , &nLen ) == 0 )
      {
         if( nLen > 0 )
         {
            ULONG nWBytes = (nLen * 2) + (pAnsi[(nLen-1)] == 0 ? 0 : 2);
            LPWSTR pWide = (LPWSTR) _xgrab( nWBytes );
            MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,nLen,pWide,nLen);
            conr = _conPutCL(conr,(LPSTR)((void *) pWide),nWBytes);
            _xfree( (void*) pWide);
         }
         ot4xb_conUnlockC( conc ); pAnsi = (LPSTR) 0;
      } 
      if( !bByRef) _conRelease( conc);
   }
   if( conr == NULLCONTAINER ) _retclen( pl , "\0\0" , 2);
   else { _conReturn( pl, conr); _conRelease( conr); }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CSZWIDE2ANSI(XppParamList pl )
{
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1 , &bByRef , XPP_CHARACTER );
   ContainerHandle conr = NULLCONTAINER;
   if( conc != NULLCONTAINER )
   {
      LPWSTR pWide = (LPWSTR) 0;
      ULONG nWBytes  = 0;
      if(  ot4xb_conRLockC(conc,(LPSTR *)((void*) &pWide) , &nWBytes ) == 0 )
      {
         if( nWBytes > 1 )
         {
            ULONG nLen  = ( nWBytes >> 1 );
            LPSTR pAnsi = (LPSTR) _xgrab( nLen + 1);
            WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pWide,nLen,pAnsi,nLen,0,0);
            conr = _conPutC(conr,pAnsi);
            _xfree( (void*) pAnsi);
         }
         ot4xb_conUnlockC( conc ); pWide = (LPWSTR) 0;
      }
      if( !bByRef) _conRelease( conc);
   }
   if( conr == NULLCONTAINER ) _retc(pl,"");
   else { _conReturn( pl, conr); _conRelease( conr); }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY UNICODEDYNSTR( XppParamList pl )
{
   ContainerHandle conco = _conClsObj("UNICODEDYNSTR");
   if( conco == NULLCONTAINER )
   {
      TXbClass * pc = new TXbClass;
      pc->ClassName("UNICODEDYNSTR");
      pc->GwstParent();
      pc->EXPORTED();
      pc->GwstReadWrite();
      // ---------------------------
      pc->Var("_pp_");
      pc->Var("_nBytes_");
      pc->Member_Pointer32("p");
      pc->Property("cStr", UnicodeDynStr_cStr , 1 );
      pc->Property("wStr", UnicodeDynStr_wStr , 1 );
      // ---------------------------
      conco = pc->Create();
      delete pc;
      if( conco == NULLCONTAINER ){_ret(pl); return;}
   }
   _conReturn(pl,conco);
   _conRelease(conco);
}
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_cStr( TXbClsParams * px )
{
   ContainerHandle Self = px->GetSelf();
   void * p  = (void*) _conGetNLMember(Self,"p");
   void * pp = (void*) _conGetNLMember(Self,"_pp_");

   if( px->PCount() > 0 )
   {
      if( pp != NULL ){ _xfree( pp ); pp = NULL; }
      if( px->CheckParamType(1, XPP_CHARACTER ) )
      {
         ULONG   nLen   = 0;
         LPSTR   pStr   = px->ParamLockStr(1,&nLen);
         ULONG   nBytes = ((nLen * 2) + 2);
         LPWSTR  pWide  = ( LPWSTR ) _xgrab( nBytes );
         MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pStr,nLen,pWide,nLen);
         px->ParamUnlockStr(1); pStr = NULL;
         _conSetNLMember(Self,"p",(LONG) pWide);
         _conSetNLMember(Self,"_pp_",(LONG) pWide);
         _conSetNLMember(Self,"_nBytes_",(LONG) (nLen * 2) );
         px->PutReturn( px->GetParam(1) );
         return;
      }
      else
      {
         _conSetNLMember(Self,"p",0);
         _conSetNLMember(Self,"_pp_",0);
         _conSetNLMember(Self,"_nBytes_",0);
      }
   }
   else
   {
      if( p == pp ) // String was stored trought ::cStr or ::wStr methods
      {
         ULONG nBytes = (ULONG ) _conGetNLMember(Self,"_nBytes_");
         ULONG nLen   = (nBytes >> 1);
         LPSTR pStr   = (LPSTR) _xgrab(nLen);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,( LPWSTR )p,nLen,pStr,nLen,0,0);
         px->PutReturnStrLen(pStr,nLen);
         _xfree((void*) pStr);
      }
      else  // assuming string is Zero terminated
      {
         LPWSTR  pWide  = ( LPWSTR ) p;
         ULONG nLen     = 0;
         ULONG n;
         LPSTR pStr;
         for( n = 0; (pWide[n] != (WCHAR) 0); n++) nLen++;
         pStr   = (LPSTR) _xgrab(nLen);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pWide,nLen,pStr,nLen,0,0);
         px->PutReturnStrLen(pStr,nLen);
         _xfree((void*) pStr);
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
static void UnicodeDynStr_wStr( TXbClsParams * px )
{
   ContainerHandle Self = px->GetSelf();
   void * p  = (void*) _conGetNLMember(Self,"p");
   void * pp = (void*) _conGetNLMember(Self,"_pp_");
   if( px->PCount() > 0 )
   {
      if( pp != NULL ){ _xfree( pp ); pp = NULL; }
      if( px->CheckParamType(1, XPP_CHARACTER ) )
      {
         ULONG    nBytes = 0;
         LPWSTR   pWStr   = (LPWSTR) px->ParamLockStr(1,&nBytes);
         ULONG    nLen   = (nBytes >> 1);
         LPWSTR   pWide;
         ULONG    n;

         if( nLen > 0 )
         {
            if( pWStr[nLen-1] != (WCHAR) 0 ) nBytes += 2;
         }
         else nBytes = 2;
         pWide = (LPWSTR) _xgrab( nBytes );
         for( n = 0; n < nLen; n++ )  pWide[n] = pWStr[n];
         px->ParamUnlockStr(1); pWStr = NULL;
         _conSetNLMember(Self,"p",(LONG) pWide);
         _conSetNLMember(Self,"_pp_",(LONG) pWide);
         _conSetNLMember(Self,"_nBytes_",(LONG) (nLen * 2));
         px->PutReturn( px->GetParam(1) );
      }
      else
      {
         _conSetNLMember(Self,"p",0);
         _conSetNLMember(Self,"_pp_",0);
         _conSetNLMember(Self,"_nBytes_",0);
      }
   }
   else
   {
      if( p == pp ) // String was stored trought ::cStr or ::wStr methods
      {
         ULONG nBytes = (ULONG ) _conGetNLMember(Self,"_nBytes_");
         px->PutReturnStrLen((LPSTR)p,nBytes);
      }
      else  // assuming string is Zero terminated
      {
         LPWSTR  pWide  = ( LPWSTR ) p;
         ULONG nLen = 0;
         ULONG n;
         for( n = 0; (pWide[n] != (WCHAR) 0); n++) nLen++;
         px->PutReturnStrLen((LPSTR) p,(nLen* 2));
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CUTF8TOANSI(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nUtf8Len * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_UTF8,0,pUtf8,(int)nUtf8Len,pWide,(int)(nUtf8Len+1));
         int    nAnsiLen = WideCharToMultiByte(CP_ACP,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pAnsi    = (LPSTR) _xgrab((UINT) (nAnsiLen + 1));
         nAnsiLen = WideCharToMultiByte(CP_ACP,0,pWide,nWideLen,pAnsi,nAnsiLen+1,0,0);
         _conPutCL(conr,pAnsi,(ULONG)nAnsiLen);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pAnsi );         
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CANSITOUTF8(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nAnsiLen = 0;
      LPSTR pAnsi    = 0;
      if( ot4xb_conRLockC(conc,&pAnsi,&nAnsiLen) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nAnsiLen * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_ACP,0,pAnsi,(int)nAnsiLen,pWide,(int)(nAnsiLen+1));
         int    nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pUtf8    = (LPSTR) _xgrab((UINT) (nUtf8Len + 1));
         nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,pUtf8,nUtf8Len+1,0,0);
         _conPutCL(conr,pUtf8,(ULONG)nUtf8Len);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pUtf8 );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CUTF8TOOEM(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nUtf8Len * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_UTF8,0,pUtf8,(int)nUtf8Len,pWide,(int)(nUtf8Len+1));
         int    nOemLen = WideCharToMultiByte(CP_OEMCP,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pOem    = (LPSTR) _xgrab((UINT) (nOemLen + 1));
         nOemLen = WideCharToMultiByte(CP_OEMCP,0,pWide,nWideLen,pOem,nOemLen+1,0,0);
         _conPutCL(conr,pOem,(ULONG)nOemLen);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pOem );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY COEMTOUTF8(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nOemLen = 0;
      LPSTR pOem    = 0;
      if( ot4xb_conRLockC(conc,&pOem,&nOemLen) == 0 )
      {
         LPWSTR pWide    = (LPWSTR) _xgrab( (nOemLen * 2) + 2 );
         int    nWideLen = MultiByteToWideChar(CP_OEMCP,0,pOem,(int)nOemLen,pWide,(int)(nOemLen+1));
         int    nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,NULL,0,0,0);
         LPSTR  pUtf8    = (LPSTR) _xgrab((UINT) (nUtf8Len + 1));
         nUtf8Len = WideCharToMultiByte(CP_UTF8,0,pWide,nWideLen,pUtf8,nUtf8Len+1,0,0);
         _conPutCL(conr,pUtf8,(ULONG)nUtf8Len);
         ot4xb_conUnlockC(conc);
         _xfree( (void*) pWide ); _xfree( (void*) pUtf8 );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API WCHAR * pAnsi2WStr( LPSTR pAnsi , int cb , int* pcc )
{
   if( pAnsi )
   {
      if( (cb == -1 ) && pAnsi ) cb = (int) _xstrlen(pAnsi);
      if( pAnsi && cb )
      {
         LPWSTR pWide = (LPWSTR) _xgrab( (ULONG) ((cb + 1) * 2) );
         int    cc    = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,cb,pWide,cb);
         if( pcc ) pcc[0] = cc;
         return pWide;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
OT4XB_API LPSTR pWStr2Ansi( WCHAR* pWide  , int cc, int* pcc)
{
   if( pWide )
   {
      if( (cc == -1 ) && pWide ) cc = (int) _xstrlenW(pWide);
      if( pWide && cc )
      {
         LPSTR  pAnsi = (LPSTR) _xgrab( (ULONG) (cc + 1) );
         cc = WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pWide,cc,pAnsi,cc,0,0);
         if( pcc ) pcc[0] = cc;
         return pAnsi;
      }
   }
   return 0;
}
// -----------------------------------------------------------------------------------------------------------------
// Added behavior: PeekWStr(pMem,[@]nShift,-1) Assuming Zero terminated string
XPPRET XPPENTRY PEEKWSTR(XppParamList pl) // PeekWStr(pMem,[@]nShift,nSize) -> cStr || PeekWStr(pMem,[@]nShift,@cStr) -> nSize
{
    CON_PLKSTREX plk;
    LPSTR p      = (LPSTR) _conParamRLockStrEx(pl,1,&plk);
    LONG nShift  = _parLong(pl,2);
    ULONG ulType = _partype(pl,3);

    if( p == 0){_conUnLockStrEx_(&plk); _ret(pl); return;}

    if( ulType & XPP_CHARACTER )
    {
       BOOL bByRef = FALSE;
       ContainerHandle con = _conParam(pl,3,&bByRef);
       ULONG nSize = 0;
       p += nShift;
       if( con == NULLCONTAINER ){_conUnLockStrEx_(&plk); _ret(pl); return;}
       _conSizeC(con,&nSize);
       _conPutCL(con,p,nSize);
       if(!bByRef) _conRelease(con);
       _stornl(nShift+nSize,pl,2);
       _conUnLockStrEx_(&plk);
       _retnl(pl,nSize);
       return;
    }
    else if( ulType & XPP_NUMERIC)
    {
       ContainerHandle conr = NULLCONTAINER;
       LONG nSize = (_parLong(pl,3) * 2);
       p += nShift;
       if( nSize < 0 )
       {
          nSize = (lstrlenW( (LPWSTR) p ) * 2);
          _stornl(nShift+nSize+2,pl,2);
       }
       else
       {
          _stornl(nShift+nSize,pl,2);
       }
       conr = _conPutCL( conr , p,(ULONG) nSize);
       _conUnLockStrEx_(&plk);
       _conReturn( pl , conr );
       _conRelease(conr );
       return;
    }
    else if( ulType & XPP_ARRAY )
    {
       ContainerHandle cona = _conParam(pl,3,0);
       ULONG nItems = 0;
       ULONG nn;
       //LONG  nRead = 0;
       _conSizeA( cona, &nItems , 0 );
       for( nn = 1; nn <= nItems; nn++)
       {
          LONG nSize;
          ulType = 0;
          _conTypeA(cona,&ulType,nn,0);
          if( ulType & XPP_CHARACTER )
          {
             nSize = _conArrayGetSizeC(cona,nn,0);
             _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
             nShift += nSize;
          }
          else
          {
             nSize = ( _conArrayGetNL(cona,nn,0) * 2);
             if( nSize < 0 )
             {
                 nSize = (lstrlenW( reinterpret_cast<LPWSTR>(p + nShift) ) * 2);
                 _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
                 nShift += (nSize + 2);
             }
             else
             {
                _conArrayPutCL( cona , p + nShift , (ULONG) nSize , nn , 0);
                nShift += nSize;
             }
          }
          //nRead  += nSize;
       }
       _stornl(nShift,pl,2);
       _conUnLockStrEx_(&plk);
       _conReturn(pl,cona);
       _conRelease(cona);
       return;
    }
    _conUnLockStrEx_(&plk);
    _ret(pl);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY CUTF8TOWIDE(XppParamList pl )
{
   ContainerHandle conr = _conNew(NULLCONTAINER);
   BOOL bByRef = FALSE;
   ContainerHandle conc = _conTParam( pl,1,&bByRef,XPP_CHARACTER);
   if( conc )
   {
      ULONG nUtf8Len = 0;
      LPSTR pUtf8    = 0;
      if( ot4xb_conRLockC(conc,&pUtf8,&nUtf8Len) == 0 )
      {
         int    nWideLen = 0;
         LPWSTR pWide    = utf82w(pUtf8,nUtf8Len,&nWideLen);
         ot4xb_conUnlockC(conc);
         _conPutCL(conr,(LPSTR) pWide,nWideLen * 2);
         _xfree( (void*) pWide );
      }
      if(!bByRef ) _conRelease(conc);
      conc = 0;
   }
   _conReturn(pl,conr); _conRelease(conr);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _MB2W ) // _mb2w( str , nAcp , nFlags , lNoAddZero )
{
   TXppParamList xpp(pl,4);
   int   cb = 0;
   LPSTR pu = xpp[1]->LockStr((ULONG*) &cb); if( !pu ){ return; }      
   int cc = 0;
   LPWSTR pw = mb2w(pu,cb+(xpp[4]->GetBool() ? 0 : 1 ),&cc,xpp[2]->GetDWord(),xpp[3]->GetDWord());
   if( !pw ){ return; }
   xpp[0]->PutStrLen( (LPSTR) pw , (ULONG) cc * 2 );
   _xfree((void*) pw);
}
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _W2MB )  // _w2mb( wstr , nAcp , nFlags , lRemoveZero )
{
   TXppParamList xpp(pl,4);
   int cc = 0;
   LPWSTR pw = (LPWSTR ) xpp[1]->LockStr((ULONG*) &cc); if( !pw ){ return; }
   cc = cc >> 1;
   int   cb = 0;  
   LPSTR pu = w2mb(pw,cc,&cb,xpp[2]->GetDWord(),xpp[3]->GetDWord());
   if(!pu){ return; }   
   if(xpp[4]->GetBool()){if( cb > 0 ){ if( pu[(cb-1)] == 0 ){ cb--; }}}
   xpp[0]->PutStrLen(pu,(ULONG)cb);
   _xfree((void*) pu);   
}
// -----------------------------------------------------------------------------------------------------------------
//#define CP_ACP                    0           // default to ANSI code page
//#define CP_OEMCP                  1           // default to OEM  code page
//#define CP_THREAD_ACP             3           // current thread's ANSI code page
//#define CP_UTF8                   65001       // UTF-8 translation
//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _MB2MB) // _mb2mb( str , nAcpFrom , nAcpTo , nFlags1 , nFlags2 )
{
   TXppParamList xpp(pl,5);
   int   cb1 = 0;
   LPSTR p1  = xpp[1]->LockStr((ULONG*) &cb1); if( !p1 ){ return; }
   int   cb2 = 0;  
   LPSTR p2  = mb2mb(p1,cb1,&cb2,xpp[2]->GetDWord(),xpp[3]->GetDWord(),xpp[4]->GetDWord(),xpp[5]->GetDWord());
   if( !p2 ){ return; }   
   xpp[0]->PutStrLen(p2,(ULONG)cb2);
   _xfree((void*) p2);   
}

