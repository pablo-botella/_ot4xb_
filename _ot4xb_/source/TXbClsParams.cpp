//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TXbClsParams::TXbClsParams( XppParamList pl )
{
   ULONG n;
   m_pl            = pl;
   m_bResult       = TRUE;
   m_realCount     = _partype(pl,0);
   m_real          = (TXbCPItem **) _xgrab( (UINT) (sizeof(TXbCPItem*) * m_realCount) );
   for( n = 0; n < m_realCount; n++){ m_real[n] = new TXbCPItem(pl,n+1);}
   m_Self    = m_real[0];
   m_return  = m_real[3];
   m_error   = m_real[4];
   m_paramsCount = (ULONG) m_real[5]->GetLong();
   m_params      = &m_real[7];
   m_formalCount = (ULONG) m_real[6]->GetLong();
   m_eparams       = 0; m_eparamsCount  = 0;
   if( (m_formalCount + 7) < m_realCount )
   {
      m_eparams =  &m_real[(m_formalCount + 7)];
      m_eparamsCount =  m_realCount  - (m_formalCount + 7);
   }
}
//----------------------------------------------------------------------------------------------------------------------
TXbClsParams::~TXbClsParams( void )
{
   if( m_real )
   {
      ULONG n;
      for( n = 0; n < m_realCount; n++) delete m_real[n];
      _xfree( (void *) m_real );
   }
   m_pl           = 0;
   m_bResult      = 0;
   m_return       = 0;
   m_error        = 0;
   m_Self         = 0;
   m_params       = 0;
   m_paramsCount  = 0;
   m_eparams      = 0;
   m_eparamsCount = 0;
   m_real         = 0;
   m_realCount    = 0;
   m_formalCount  = 0;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ShiftParams(LONG nParams)
{
   LONG  nParamCount     = m_real[5]->GetLong();
   LONG  nPCurrent       = (LONG) ((void*) m_params );
   ULONG nPBase          = (LONG) ((void*) (&m_real[7]) );
   LONG  nCurrentShift   = ((nPCurrent - nPBase) >> 2);
   LONG  nPlanedShift    = nCurrentShift + nParams;
   if( nPlanedShift < 0 ) nPlanedShift = 0;
   else if( nPlanedShift > nParamCount ) nPlanedShift = nParamCount;
   m_params      = (TXbCPItem **) (nPBase + (nPlanedShift << 2));
   m_paramsCount = (ULONG) ( nParamCount - nPlanedShift );
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ResetShiftParams(void)
{
   m_paramsCount = (ULONG) m_real[5]->GetLong();
   m_params      = &m_real[7];
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::PCount(void){ return m_paramsCount; }
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::GetParamType(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->GetType();
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::CheckParamType(ULONG np , ULONG ulType)
{
   if( (np == 0)|| (np > m_paramsCount)) return FALSE;
   return m_params[ ( np-1) ]->CheckType(ulType);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetTParam( ULONG np , ULONG ulType , BOOL * pbByRef )
{
   if( (np == 0)|| (np > m_paramsCount)) return NULLCONTAINER;
   return m_params[ ( np-1) ]->GetT( ulType , pbByRef);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetParam( ULONG np , BOOL * pbByRef)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULLCONTAINER;
   return m_params[ ( np-1) ]->Get(pbByRef);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParam( ULONG np , ContainerHandle con )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->Put(con);
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::GetParamBool(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return FALSE;
   return m_params[ ( np-1) ]->GetBool();
}
//----------------------------------------------------------------------------------------------------------------------
LONG TXbClsParams::GetParamLong(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->GetLong();
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetParamDWord(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->GetDWord();
}
//-----------------------------------------------------------------------------------------------------------------------
LONGLONG TXbClsParams::GetParamQWord(ULONG np)
{
   if (np == 0)
   {
      return 0LL;
   }
   if (np > m_paramsCount)
   {
      return 0LL;
   }
   return m_params[ ( np-1) ]->GetQWord();
}
//----------------------------------------------------------------------------------------------------------------------
WORD TXbClsParams::GetParamWord(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->GetWord();
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetParamLoHi2DWord(ULONG np)
{
   if( (np == 0)|| (np > (m_paramsCount -1) )) return 0;
   return (DWORD) MAKELONG( m_params[ ( np-1) ]->GetWord(),m_params[np]->GetWord());
}
//----------------------------------------------------------------------------------------------------------------------
double TXbClsParams::GetParamDouble(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return ( double) 0;
   return m_params[ ( np-1) ]->GetDouble();
}
//----------------------------------------------------------------------------------------------------------------------
FLOAT TXbClsParams::GetParamFloat(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return (FLOAT) 0;
   return m_params[ ( np-1) ]->GetFloat();
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamBool(ULONG np , BOOL value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutBool(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamLong(ULONG np , LONG value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutLong(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamDWord(ULONG np , DWORD value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutDWord(value);
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamQWord(ULONG np , LONGLONG value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutQWord(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamWord(ULONG np,WORD value)
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutWord(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamDWord2LoHi(ULONG np , DWORD value )
{
   if( (np == 0)|| (np > (m_paramsCount -1) )) return;
   m_params[ ( np-1) ]->PutWord(LOWORD(value));
   m_params[np]->PutWord(HIWORD(value));
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamDouble(ULONG np , double value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutDouble(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutParamFloat(ULONG np , FLOAT value )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutFloat(value);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamStrDup(ULONG np , ULONG * pnLen )
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->StrDup(pnLen);
}
//----------------------------------------------------------------------------------------------------------------------
LPWSTR TXbClsParams::ParamStrDupW(ULONG np , ULONG * pnBytes )
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->StrDupW(pnBytes);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::ParamGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->GetCL(pDst,nBuffSize);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamLockStr(ULONG np ,ULONG * pnSize, BOOL bWrite)
{
   if( (np == 0)|| (np > m_paramsCount)) return 0;
   return m_params[ ( np-1) ]->LockStr(pnSize,bWrite);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ParamUnlockStr(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->UnlockStr();
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ParamPutStrLen(ULONG np,LPSTR pStr , ULONG nLen)
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutStrLen(pStr,nLen);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ParamPutStr(ULONG np,LPSTR pStr)
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->PutStr(pStr);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::ECount(void){ return m_eparamsCount; }
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::GetExtraType(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetType();
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::CheckExtraType(ULONG np , ULONG ulType)
{
   if( (np == 0)|| (np > m_eparamsCount)) return FALSE;
   return m_eparams[ ( np-1) ]->CheckType(ulType);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetTExtra( ULONG np , ULONG ulType , BOOL * pbByRef )
{
   if( (np == 0)|| (np > m_eparamsCount)) return NULLCONTAINER;
   return m_eparams[ ( np-1) ]->GetT( ulType , pbByRef);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetExtra( ULONG np , BOOL * pbByRef)
{
   if( (np == 0)|| (np > m_eparamsCount)) return NULLCONTAINER;
   return m_eparams[ ( np-1) ]->Get(pbByRef);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtra( ULONG np , ContainerHandle con )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->Put(con);
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::GetExtraBool(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return FALSE;
   return m_eparams[ ( np-1) ]->GetBool();
}
//----------------------------------------------------------------------------------------------------------------------
LONG TXbClsParams::GetExtraLong(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetLong();
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetExtraDWord(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetDWord();
}
//-----------------------------------------------------------------------------------------------------------------------
LONGLONG TXbClsParams::GetExtraQWord(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetQWord();
}
//----------------------------------------------------------------------------------------------------------------------
WORD TXbClsParams::GetExtraWord(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetWord();
}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetExtraLoHi2DWord(ULONG np)
{
   if( (np == 0)|| (np > (m_eparamsCount -1) )) return 0;
   return (DWORD) MAKELONG( m_eparams[ ( np-1) ]->GetWord(),m_eparams[np]->GetWord());
}
//----------------------------------------------------------------------------------------------------------------------
double TXbClsParams::GetExtraDouble(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return ( double) 0;
   return m_eparams[ ( np-1) ]->GetDouble();
}
//----------------------------------------------------------------------------------------------------------------------
FLOAT TXbClsParams::GetExtraFloat(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return (FLOAT) 0;
   return m_eparams[ ( np-1) ]->GetFloat();
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraBool(ULONG np , BOOL value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutBool(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraLong(ULONG np , LONG value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutLong(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraDWord(ULONG np , DWORD value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutDWord(value);
}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraQWord(ULONG np , LONGLONG value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutQWord(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraWord(ULONG np,WORD value)
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutWord(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraDWord2LoHi(ULONG np , DWORD value )
{
   if( (np == 0)|| (np > (m_eparamsCount -1) )) return;
   m_eparams[ ( np-1) ]->PutWord(LOWORD(value));
   m_eparams[np]->PutWord(HIWORD(value));
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraDouble(ULONG np , double value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutDouble(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutExtraFloat(ULONG np , FLOAT value )
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutFloat(value);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ExtraPutStrLen(ULONG np,LPSTR pStr , ULONG nLen)
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutStrLen(pStr,nLen);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ExtraPutStr(ULONG np,LPSTR pStr)
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->PutStr(pStr);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ExtraLockStr(ULONG np ,ULONG * pnSize, BOOL bWrite)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->LockStr(pnSize,bWrite);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ExtraUnlockStr(ULONG np)
{
   if( (np == 0)|| (np > m_eparamsCount)) return;
   m_eparams[ ( np-1) ]->UnlockStr();
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::ExtraGetCL(ULONG np , LPSTR pDst , ULONG nBuffSize)
{
   if( (np == 0)|| (np > m_eparamsCount)) return 0;
   return m_eparams[ ( np-1) ]->GetCL(pDst,nBuffSize);
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetSelf(void){return m_Self->Get(0);}
//----------------------------------------------------------------------------------------------------------------------
void * TXbClsParams::GetSelfC(void)
{
   ContainerHandle Self =  GetSelf();
   if( Self == NULLCONTAINER) return NULL;
   return (void*) _conGetNLMember(Self,"_m__pt_");
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetSelfC(void * p)
{
   ContainerHandle Self =  GetSelf();
   if( Self != NULLCONTAINER) _conSetNLMember(Self,"_m__pt_",(LONG) p);
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::GetReturnType(void){return m_return->GetType();}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::CheckReturnType(ULONG ulType){return m_return->CheckType(ulType);}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetReturn(void){   return m_return->Get(0);}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::GetReturnBool(void){return m_return->GetBool();}
//----------------------------------------------------------------------------------------------------------------------
LONG TXbClsParams::GetReturnLong(void){return m_return->GetLong();}
//----------------------------------------------------------------------------------------------------------------------
DWORD TXbClsParams::GetReturnDWord(void){return m_return->GetDWord();}
//-----------------------------------------------------------------------------------------------------------------------
LONGLONG TXbClsParams::GetReturnQWord(void){return m_return->GetQWord();}
//----------------------------------------------------------------------------------------------------------------------
WORD TXbClsParams::GetReturnWord(void){return m_return->GetWord();}
//----------------------------------------------------------------------------------------------------------------------
double TXbClsParams::GetReturnDouble(void){return m_return->GetDouble();}
//----------------------------------------------------------------------------------------------------------------------
FLOAT TXbClsParams::GetReturnFloat(void){return m_return->GetFloat();}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnBool(BOOL value ){m_return->PutBool(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnLong(LONG value ){m_return->PutLong(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnDWord(DWORD value ){m_return->PutDWord(value);}
//-----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnQWord(LONGLONG value ){m_return->PutQWord(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnWord(WORD value){m_return->PutWord(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnDouble(double value ){m_return->PutDouble(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnFloat(FLOAT value ){m_return->PutFloat(value);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnStrLen(LPSTR pStr , ULONG nLen){m_return->PutStrLen(pStr,nLen);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnStr(LPSTR pStr){m_return->PutStr(pStr);}
// -----------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnWStr(LPWSTR pWStr)
{
   LPSTR p = w2ansi(pWStr);
   m_return->PutStr(p);
   _xfree((void*) p );
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::LockReturnStr(ULONG * pnSize, BOOL bWrite){return m_return->LockStr(pnSize,bWrite);}
//----------------------------------------------------------------------------------------------------------------------
void  TXbClsParams::UnlockReturnStr(){m_return->UnlockStr();}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturn(ContainerHandle con )
{
   m_return->Put(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturnSelf(void){m_return->Put(GetSelf());}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ReturnRLockStrEx(void){ return m_return->RLockStrEx();}
LPSTR TXbClsParams::ReturnWLockStrEx(void){ return m_return->WLockStrEx();}
LPSTR TXbClsParams::ReturnRLockStrExF(void){return m_return->RLockStrExF();}
LPSTR TXbClsParams::ReturnWLockStrExF(void){return m_return->WLockStrExF();}
LPSTR TXbClsParams::ReturnRLockStrExF8(void){return m_return->RLockStrExF8();}
LPSTR TXbClsParams::ReturnWLockStrExF8(void){return m_return->WLockStrExF8();}
void  TXbClsParams::ReturnUnLockStrEx(void){m_return->UnLockStrEx();}
ULONG TXbClsParams::ReturnExLen(void){return m_return->m_nLockLen;}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::ReturnNewObj(LPSTR pClassName, ContainerHandle p1 , ... )
{
   BOOL     bRet = FALSE;
   va_list  pMarker;
   PutReturn(0);
   if(pClassName)
   {
      ContainerHandle  con = _conClsObjNew(pClassName);
      if(con)
      {
         TContainerHandleList  * pList = new TContainerHandleList;
         pList->Add(con); // Add the class object
         va_start(pMarker,p1);
         for( con = p1;con;con = (ContainerHandle ) va_arg( pMarker, ContainerHandle))
         {
            pList->Add(con);
         }
         va_end( pMarker );
         con = 0;
         _conCallMethodPa( GetReturn() , "NEW",pList->m_nCount,pList->m_pItems);
         pList->Release(0); // Free ClassObject
         delete pList;
         if( !CheckReturnType(XPP_OBJECT) ) PutReturn(NULLCONTAINER);
         else bRet = TRUE;
      }
   }
   return bRet;
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::ReturnNewObjR(LPSTR pClassName, ContainerHandle p1 , ... )
{
   BOOL     bRet = FALSE;
   va_list  pMarker;
   PutReturn(0);
   if(pClassName)
   {
      ContainerHandle  con = _conClsObjNew(pClassName);
      if(con)
      {
         TContainerHandleList  * pList = new TContainerHandleList;
         pList->Add(con); // Add the class object
         va_start(pMarker,p1);
         for( con = p1;con;con = (ContainerHandle ) va_arg( pMarker, ContainerHandle))
         {
            pList->Add(con);
         }
         va_end( pMarker );
         con = 0;
         _conCallMethodPa( GetReturn() , "NEW",pList->m_nCount,pList->m_pItems);
         pList->ReleaseAll(); // Free All containers
         delete pList;
         if( !CheckReturnType(XPP_OBJECT) ) PutReturn(NULLCONTAINER);
         else bRet = TRUE;
      }
   }
   return bRet;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::ReturnNewArray(DWORD nDim, DWORD* pDim )
{
   LONG sp1;
   DWORD dw;
   DWORD dwDim = nDim;

   __asm mov sp1 ,esp;
   if( nDim && pDim )
   {
      while(dwDim)
      {
         dwDim--;
         dw = pDim[dwDim];
         __asm mov eax, dw;
         __asm push eax;
      }
      __asm mov eax, nDim;
      __asm push eax;
   }
   else // Create an empty array
   {
      __asm push 0;
      __asm push 1;
   }
   __asm
   {
      mov eax, _conNewArray;
      call eax;
      mov dw , eax;
      mov esp , sp1;
   }
   PutReturn( (ContainerHandle) dw );
   _conRelease( (ContainerHandle) dw );
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClsParams::GenError(void)
{
   _conEvalMacroStr( m_error->Get() , "ERROR():New()");
   m_bResult = FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
ContainerHandle TXbClsParams::GetError(void){ return m_error->Get();}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorArgs( ContainerHandle cona ){ _conSetMember(GetError(),"args",cona);}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorArgs(void)
{
 ContainerHandle cona = _conNewArray(1,m_paramsCount);
 ULONG n;
 for( n = 1; n <= m_paramsCount; n++) _conArrayPut(cona, GetParam(n),n,0);
 _conSetMember(GetError(),"args",cona);
 _conRelease(cona);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorDescription( LPSTR pStr)
{
  ContainerHandle con = _conPutC(NULLCONTAINER,pStr);
  _conSetMember(GetError(),"description",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorFilename( LPSTR pStr)
{
  ContainerHandle con = _conPutC(NULLCONTAINER,pStr);
  _conSetMember(GetError(),"filename",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorGenCode( LONG n )
{
  ContainerHandle con = _conPutNL(NULLCONTAINER,n);
  _conSetMember(GetError(),"genCode",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorOperation( LPSTR pStr )
{
  ContainerHandle con = _conPutC(NULLCONTAINER,pStr);
  _conSetMember(GetError(),"operation",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorOsCode( LONG n)
{
  ContainerHandle con = _conPutNL(NULLCONTAINER,n);
  _conSetMember(GetError(),"osCode",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorSeverity( LONG n)
{
  ContainerHandle con = _conPutNL(NULLCONTAINER,n);
  _conSetMember(GetError(),"severity",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorSubCode( LONG n)
{
  ContainerHandle con = _conPutNL(NULLCONTAINER,n);
  _conSetMember(GetError(),"subcode",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbClsParams::SetErrorSubSystem( LPSTR pStr)
{
  ContainerHandle con = _conPutC(NULLCONTAINER,pStr);
  _conSetMember(GetError(),"subsystem",con);
  _conRelease(con);
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamRLockStrEx(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->RLockStrEx();
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamWLockStrEx(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->WLockStrEx();
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamRLockStrExF(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->RLockStrExF();
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamWLockStrExF(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->WLockStrExF();
}
// -----------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamRLockStrExF8(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->RLockStrExF8();
}
//----------------------------------------------------------------------------------------------------------------------
LPSTR TXbClsParams::ParamWLockStrExF8(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->WLockStrExF8();
}
//----------------------------------------------------------------------------------------------------------------------
void  TXbClsParams::ParamUnLockStrEx(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->UnLockStrEx();
}
//----------------------------------------------------------------------------------------------------------------------
ULONG TXbClsParams::ParamExLen(ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->m_nLockLen;
}
//----------------------------------------------------------------------------------------------------------------------
HWND TXbClsParams::GetParamHWND( ULONG np)
{
   if( (np == 0)|| (np > m_paramsCount)) return NULL;
   return m_params[ ( np-1) ]->GetHWND();
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::ParamGetGuid(ULONG np, GUID* pDst)
{
   if( (np == 0)|| (np > m_paramsCount)) return FALSE;
   return m_params[ ( np-1) ]->GetGuid(pDst);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::ParamPutGuid(ULONG np, GUID* pSrc , BOOL bBraces)
{
   if( (np == 0)|| (np > m_paramsCount)) return FALSE;
   return m_params[ ( np-1) ]->PutGuid(pSrc,bBraces);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::GetReturnGuid(GUID* pDst)
{
   return m_return->GetGuid(pDst);
}
// -----------------------------------------------------------------------------------------------------------------
BOOL TXbClsParams::PutReturnGuid(GUID* pSrc , BOOL bBraces)
{
   return m_return->PutGuid(pSrc,bBraces);
}
// -----------------------------------------------------------------------------------------------------------------
void* TXbClsParams::Lock(ULONG* pdwSize)
{
   DWORD dw = 0;
   void* p  = (void*) _conMCallLong( GetSelf() ,"_lock_",&dw);
   if(pdwSize) pdwSize[0] = dw;
   return p;
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClsParams::Unlock(void){ _conMCallVoid( GetSelf() ,"_unlock_"); }
// -----------------------------------------------------------------------------------------------------------------
void TXbClsParams::Param_setprop_ansi2wide( ULONG np , LPWSTR* ppw )
{
   if( (np == 0)|| (np > m_paramsCount)) return;
   m_params[ ( np-1) ]->setprop_ansi2wide(ppw );
}
// -----------------------------------------------------------------------------------------------------------------
void TXbClsParams::PutReturn_getprop_wide2ansi( LPWSTR* ppw )
{
   return m_return->getprop_wide2ansi(ppw);
}
// -----------------------------------------------------------------------------------------------------------------




