//------------------------------------------------------------
//  Project : Open Tools for Xbase++                          -
//  Repository : http ://www.xbwin.com                        -
//  Author : Pablo Botella Navarro ( http ://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//----------------------------------------------------------------------------------------------------------------------
TXbFpQParam::TXbFpQParam()
{

   GetTlsHeapManager()->PopNextFpFlags(); // reset TLS flags. Not currently used here but reset anyway   
   m_pNext            = 0;
   m_pPrev            = 0;
   m_nType            = 0;
   m_nLen             = 0;
   m_bByRef           = 0;
   m_con              = 0;
   m_pStr             = 0;
   m_bxgrab           = 0;
   m_bConLock         = 0;
   m_bObjLock         = 0;
   m_nStackSize       = 0;
   m_dwq              = 0;
   m_dwIntMask        = (DWORD) -1;
   m_pdwStack         = 0;
   m_dw0              = 0;
   m_dw1              = 0;
   m_dw2              = 0;
   m_dw3              = 0;
   m_dw4              = 0;
   m_dw5              = 0;
   m_dw6              = 0;
   m_dw7              = 0;

}
// -----------------------------------------------------------------------------------------------------------------
TXbFpQParam::~TXbFpQParam()
{
   Release();
   m_pNext            ;
   m_pPrev            ;
   m_nType            ;
   m_nLen             ;
   m_bByRef           ;
   m_con              ;
   m_pStr             ;
   m_bxgrab           ;
   m_bConLock         ;
   m_bObjLock         ;
   m_nStackSize       ;
   m_dwq              ;
   m_dwIntMask        ;
   m_pdwStack         ;
   m_dw0              ;
   m_dw1              ;
   m_dw2              ;
   m_dw3              ;
   m_dw4              ;
   m_dw5              ;
   m_dw6              ;
   m_dw7              ;
}
// -----------------------------------------------------------------------------------------------------------------
TXbFpQParam * TXbFpQParam::InitList(XppParamList pl , DWORD* pdwq, ULONG nFirst,DWORD*pdwParams)
{
   TXbFpQParam *  pFirst = (TXbFpQParam *) NULL;
   DWORD nParams         = pdwParams[0];
   if(nParams )
   {
      ULONG n;
      TXbFpQParam * pItem = NULL;
      TXbFpQParam * pPrev = NULL;
      if( pdwq[1] == QT_VOID )
      {
         pdwParams[0] = 0;
         return 0;
      }
      for( n = 0 ; n < nParams; n++ )
      {
         pPrev = pItem;
         pItem = new TXbFpQParam;
         if(pPrev)
         {
            pPrev->m_pNext = pItem;
            pItem->m_pPrev = pPrev;
         }
         else pFirst = pItem;
         pItem ->InitParam(pl,n+nFirst,pdwq[(n+1)]);
      }
   }
   return pFirst;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::ReleaseAll(TXbFpQParam * pFirst )
{
   TXbFpQParam * pItem = pFirst;

   while(  pItem )
   {
      TXbFpQParam * pNext = pItem->m_pNext;
      delete pItem;
      pItem = pNext;
   }
}
//----------------------------------------------------------------------------------------------------------------------
DWORD * TXbFpQParam::PrepareStack( TXbFpQParam * pFirst , DWORD * pnStackSize )
{
   DWORD * pStack  = 0;
   DWORD n;
   TXbFpQParam * pItem;

   pnStackSize[0] = 0;

   for( pItem = pFirst; pItem; pItem = pItem->m_pNext ) pnStackSize[0]  += pItem->m_nStackSize;
   pStack = (DWORD*) _xgrab( sizeof(DWORD) * ( pnStackSize[0] + 1 ) );
   n = pnStackSize[0];
   for( pItem = pFirst; pItem; pItem = pItem->m_pNext ) pItem->PutStackValues(pStack,&n);
   return pStack;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::PutStackValues(DWORD * pStack , DWORD * pnPos)
{
   DWORD n;
   DWORD nPos = pnPos[0];
   for( n=0; n < m_nStackSize; n++)
   {
      nPos--; pStack[nPos] = m_pdwStack[n];
   }
   pnPos[0] = nPos;
}
//----------------------------------------------------------------------------------------------------------------------
BOOL TXbFpQParam::InitParam(XppParamList pl , ULONG nPos , DWORD dwq)
{
   m_con = _conParam(pl,nPos,&m_bByRef);
   _conType( m_con , &m_nType);
   m_dwq = dwq;
   m_nStackSize = 1;  // size of stack in DWORDs
   m_pdwStack   = (DWORD*) ((void*) &m_dw0);

   if( m_dwq == QT_PSL_OR_PT )
   {
      if( m_nType & XPP_NUMERIC ){ m_dwq = QT_LPINT32; }
      else { m_dwq = QT_POINTER; }
   }


   switch( m_dwq )
   {
      case QT_LPXBASE :        { IO_QT_LPXBASE(0)    ; return TRUE;}
      case QT_BOOL :           { IO_QT_BOOL(0)       ; return TRUE;}
      case QT_BYTEBOOL :       { IO_QT_BYTEBOOL(0)   ; return TRUE;}      
      case QT_INT8 :           { IO_QT_INT8(0)       ; return TRUE;}
      case QT_BYTE :           { IO_QT_BYTE(0)       ; return TRUE;}
      case QT_INT16 :          { IO_QT_INT16(0)      ; return TRUE;}
      case QT_WORD :           { IO_QT_WORD(0)       ; return TRUE;}
      case QT_INT32 :          { IO_QT_INT32(0)      ; return TRUE;}
      case QT_DWORD :          { IO_QT_DWORD(0)      ; return TRUE;}
      case QT_INT64 :          { IO_QT_INT64(0)      ; return TRUE;}
      case QT_QWORD :          { IO_QT_QWORD(0)      ; return TRUE;}
      case QT_FLOAT :          { IO_QT_FLOAT(0)      ; return TRUE;}
      case QT_DOUBLE :         { IO_QT_DOUBLE(0)     ; return TRUE;}
      case QT_POINTER :        { IO_QT_POINTER(0)    ; return TRUE;}
      case QT_LPBOOL :         { IO_QT_LPBOOL(0)     ; return TRUE;}
      case QT_LPBYTEBOOL :     { IO_QT_LPBYTEBOOL(0) ; return TRUE;}      
      case QT_LPINT8 :         { IO_QT_LPINT8(0)     ; return TRUE;}
      case QT_LPBYTE :         { IO_QT_LPBYTE(0)     ; return TRUE;}
      case QT_LPINT16 :        { IO_QT_LPINT16(0)    ; return TRUE;}
      case QT_LPWORD :         { IO_QT_LPWORD(0)     ; return TRUE;}
      case QT_LPINT32 :        { IO_QT_LPINT32(0)    ; return TRUE;}
      case QT_LPDWORD :        { IO_QT_LPDWORD(0)    ; return TRUE;}
      case QT_LPINT64 :        { IO_QT_LPINT64(0)    ; return TRUE;}
      case QT_LPQWORD :        { IO_QT_LPQWORD(0)    ; return TRUE;}
      case QT_LPFLOAT :        { IO_QT_LPFLOAT(0)    ; return TRUE;}
      case QT_LPDOUBLE :       { IO_QT_LPDOUBLE(0)   ; return TRUE;}
      case QT_STR2WIDE :       { IO_QT_STR2WIDE(0)   ; return TRUE;}
      case QT_STR2WIDE_W :     { IO_QT_STR2WIDE_W(0) ; return TRUE;}
      case QT_HWND :           { IO_QT_HWND(0)       ; return TRUE;}
      case QT_VARIANT :        { IO_QT_VARIANT(0)    ; return TRUE;}
   }
   m_nStackSize = 0;  // size of stack in DWORDs
   return FALSE;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::FCall(ContainerHandle conr,DWORD dwPtr,DWORD dwq,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr)
{
   GetTlsHeapManager()->PutLastPointer(0);
   switch( dwq )
   {
      case QT_VOID :
      {
         TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         return;
      }
      case QT_BOOL :
      {
         _conPutL( conr , (BOOL) TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr));
         return;
      }
      case QT_BYTEBOOL :
      {
         _conPutL( conr , (BOOL) (TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr) & 0xFF) );
         return;
      }      
      case QT_INT8 :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr) & 0xFF ;
         if( result & 0x80) result |= 0xFFFFFF00;
         _conPutNL( conr , result);
         return;
      }
      case QT_BYTE :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr) & 0xFF ;
         _conPutNL( conr , result);
         return;
      }
      case QT_INT16 :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr) & 0xFFFF ;
         if( result & 0x8000) result |= 0xFFFF0000;
         _conPutNL( conr , result);
         return;
      }
      case QT_WORD :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr) & 0xFFFF ;
         _conPutNL( conr , result);
         return;
      }
      case QT_DWORD :
      {
         DWORD result = (DWORD) TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         if( result & 0x80000000) _conPutND( conr , (double) result );
         else _conPutNL( conr , (LONG) result);
         return;
      }
      case QT_INT64 : ;
      case QT_QWORD :
      {
         LONGLONG result = TXbFpQParam::FCall64I(dwPtr,pdwStack,dwStackSize,pLErr);
         _conPutCL( conr , (LPSTR) &result,sizeof(LONGLONG));
         return;
      }
      case QT_FLOAT :
      {
         double result = TXbFpQParam::FCall32F(dwPtr,pdwStack,dwStackSize,pLErr);
         _conPutND( conr , result);
         return;
      }
      case QT_DOUBLE :
      {
         double result = TXbFpQParam::FCall64F(dwPtr,pdwStack,dwStackSize,pLErr);
         _conPutND( conr , result);
         return;
      }

      case QT_ZSTRING :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         GetTlsHeapManager()->PutLastPointer((DWORD) result);
         if( result ) _conPutC( conr , (LPSTR) result);
         else _conPutC( conr , "");
         return;
      }
      case QT_STR2WIDE :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         LPSTR pAnsi = 0;
         GetTlsHeapManager()->PutLastPointer((DWORD) result);
         pAnsi = w2ansi((LPWSTR)result,-1,0);
         if( pAnsi ){ _conPutC(conr,pAnsi); _xfree((void*) pAnsi);}
         else _conPutC( conr , "");
         return;
      }
      case QT_LPXBASE :
      {
         ContainerHandle result = (ContainerHandle) TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         _conPut( conr , result);
         if( result ) _conRelease(result);
         return;
      }
      default :
      {
         LONG result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
         _conPutNL( conr , result);
         return;
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
double   TXbFpQParam::FCall32F(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr)
{
   LONG    result = TXbFpQParam::FCall32I(dwPtr,pdwStack,dwStackSize,pLErr);
   FLOAT * p      = (FLOAT * ) ((void*) &result);
   return (double) p[0];
}
//----------------------------------------------------------------------------------------------------------------------
LONG     TXbFpQParam::FCall32I(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr)
{
   DWORD dw = 0;
   if( dwPtr )
   {
      LONG spt;
      DWORD n;
      _asm mov spt ,esp; // Save the stack before
      for( n = 0; n < dwStackSize ; n++)
      {
         dw = pdwStack[n];
         _asm mov eax , dw;
         _asm push eax;
      }
      _asm mov eax , dwPtr;
      _asm call eax;
      _asm mov dw  ,eax; // get the result
      _asm mov esp ,spt;  // restore the stack
      pLErr[0] = GetLastError();
   }
   return ( LONG ) dw;
}
//----------------------------------------------------------------------------------------------------------------------
LONGLONG TXbFpQParam::FCall64I(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr)
{
   DWORD dw = 0;
   char  sz[8];
   LONGLONG * p = (LONGLONG*) ((void*) sz);
   p[0] = 0;
   if( dwPtr )
   {
      LONG spt;
      DWORD n;

      _asm mov spt ,esp; // Save the stack before
      for( n = 0; n < dwStackSize ; n++)
      {
         dw = pdwStack[n];
         _asm mov eax , dw;
         _asm push eax;
      }
      _asm mov eax , dwPtr;
      _asm call eax;
      _asm mov dword ptr sz[0]   , eax; // Get the low   DWORD of the result
      _asm mov dword ptr sz[4]   , edx; // Get the hight DWORD of the result
      _asm mov esp ,spt;  // restore the stack
      pLErr[0] = GetLastError();
   }
   return p[0];
}
//----------------------------------------------------------------------------------------------------------------------
double   TXbFpQParam::FCall64F(DWORD dwPtr,DWORD* pdwStack,DWORD dwStackSize,DWORD* pLErr)
{
   DWORD dw = 0;
   double result = 0.00F;
   if( dwPtr )
   {
      LONG spt;
      DWORD n;

      _asm mov spt ,esp; // Save the stack before
      for( n = 0; n < dwStackSize ; n++)
      {
         dw = pdwStack[n];
         _asm mov eax , dw;
         _asm push eax;
      }
      _asm mov eax , dwPtr;
      _asm call eax;
      _asm fstp qword ptr result; // Get the result
      _asm mov esp ,spt;  // restore the stack
      pLErr[0] = GetLastError();
   }
   return result;
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::Release(void)
{
   switch( m_dwq )
   {
      case QT_LPXBASE :        { IO_QT_LPXBASE(1)    ; break;}
      case QT_BOOL :           { IO_QT_BOOL(1)       ; break;}
      case QT_BYTEBOOL :       { IO_QT_BYTEBOOL(1)   ; break;}      
      case QT_INT8 :           { IO_QT_INT8(1)       ; break;}
      case QT_BYTE :           { IO_QT_BYTE(1)       ; break;}
      case QT_INT16 :          { IO_QT_INT16(1)      ; break;}
      case QT_WORD :           { IO_QT_WORD(1)       ; break;}
      case QT_INT32 :          { IO_QT_INT32(1)      ; break;}
      case QT_DWORD :          { IO_QT_DWORD(1)      ; break;}
      case QT_INT64 :          { IO_QT_INT64(1)      ; break;}
      case QT_QWORD :          { IO_QT_QWORD(1)      ; break;}
      case QT_FLOAT :          { IO_QT_FLOAT(1)      ; break;}
      case QT_DOUBLE :         { IO_QT_DOUBLE(1)     ; break;}
      case QT_POINTER :        { IO_QT_POINTER(1)    ; break;}
      case QT_LPBOOL :         { IO_QT_LPBOOL(1)     ; break;}
      case QT_LPBYTEBOOL :     { IO_QT_LPBYTEBOOL(1) ; break;}      
      case QT_LPINT8 :         { IO_QT_LPINT8(1)     ; break;}
      case QT_LPBYTE :         { IO_QT_LPBYTE(1)     ; break;}
      case QT_LPINT16 :        { IO_QT_LPINT16(1)    ; break;}
      case QT_LPWORD :         { IO_QT_LPWORD(1)     ; break;}
      case QT_LPINT32 :        { IO_QT_LPINT32(1)    ; break;}
      case QT_LPDWORD :        { IO_QT_LPDWORD(1)    ; break;}
      case QT_LPINT64 :        { IO_QT_LPINT64(1)    ; break;}
      case QT_LPQWORD :        { IO_QT_LPQWORD(1)    ; break;}
      case QT_LPFLOAT :        { IO_QT_LPFLOAT(1)    ; break;}
      case QT_LPDOUBLE :       { IO_QT_LPDOUBLE(1)   ; break;}
      case QT_STR2WIDE :       { IO_QT_STR2WIDE(1)   ; break;}
      case QT_STR2WIDE_W :     { IO_QT_STR2WIDE_W(1) ; break;}
      case QT_HWND :           { IO_QT_HWND(1)       ; break;}
      case QT_VARIANT :        { IO_QT_VARIANT(1)    ; break;}

   }
   if( m_con )
   {
      if( !m_bByRef ) _conRelease(m_con);
      m_con = NULLCONTAINER;
   }
}
//----------------------------------------------------------------------------------------------------------------------
