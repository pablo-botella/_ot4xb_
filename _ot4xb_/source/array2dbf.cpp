//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------        
#include <ot4xb_api.h>
#include <stdio.h>
#include <shlwapi.h>
#include <comutil.h>
//----------------------------------------------------------------------------------------------------------------------
BEGIN_NAMESPACE( a2dbf_ns )
// -----------------------------------------------------------------------------------------------------------------
#pragma pack(push,1)
class TDbfField : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      char   m_szName[11];      // 0,1,2,3,4,5,6,7,8,9,10
      char   m_chType;          // 11
      DWORD  m_dwOffset;        // 12,13,14,15
      BYTE   m_nLen;            // 16
      BYTE   m_nDec;            // 17
      BYTE   m_nFlags;          // 18
      DWORD  m_dwNextVal;       // 19,20,21,22  // next value for autoincrement fields
      BYTE   m_nStep;           // 23  // AutoIncrement Step Value
      DWORD  m_reserved1;       // 24,25,26,27
      DWORD  m_reserved2;       // 28,29,30,31 
      // ---------------------------------------------------------------------------------
      TDbfField(ContainerHandle conaSt , ULONG nPos , ULONG* psh , LPSTR pFmt )
      {
         m_nFlags     = 0;
         m_dwNextVal  = 0;
         m_nStep      = 0;
         m_reserved1  = 0;
         m_reserved2  = 0;
         ZeroMemory( m_szName   , 11 );
         _conArrayGetCL(conaSt,m_szName,10,nPos,1,0);
         _conArrayGetCL(conaSt,(LPSTR) &m_chType,1,nPos,2,0);

         switch( m_chType )
         {
            case 'C': 
            {
               m_nDec  = 0;
               m_nLen  = LOBYTE(LOWORD( _conArrayGetNL(conaSt,nPos,3,0)));
               if( m_nLen < 1 ) m_nLen = 10;
               break;
            }
            case 'N': 
            {
               m_nLen  = LOBYTE(LOWORD( _conArrayGetNL(conaSt,nPos,3,0)));
               if( m_nLen < 1 ) m_nLen = 10;
               m_nDec  = LOBYTE(LOWORD( _conArrayGetNL(conaSt,nPos,4,0)));
               if( m_nDec ){wsprintf(pFmt,"%%%i.%if",m_nLen,m_nDec);}
               else {wsprintf(pFmt,"%%%ii",m_nLen);}
               break;
            }
            case 'L': 
            {
               m_nLen  = 1;
               m_nDec  = 0;
               break;
            }
            case 'D': 
            {
               m_nLen  = 8;
               m_nDec  = 0;
               break;
            }
            default : // MEMO and extended types unsuported
            {
               m_chType = 'C';
               m_nLen   = 10;
               m_nDec   = 0;
               break;
            }
         }
         m_dwOffset   = psh[0];
         psh[0] = ( m_dwOffset + MAKELONG(MAKEWORD(m_nLen,0),0) );
      };
      // ---------------------------------------------------------------------------------
};
#pragma pack(pop,1)
// -----------------------------------------------------------------------------------------------------------------
#pragma pack(push,1)
class TDbfHeader : public T_ot4xb_base
{
   public:
      // ---------------------------------------------------------------------------------
      BYTE   m_nFileType;          // 0
      BYTE   m_sLUpdate[3];        // 1,2,3
      DWORD  m_nLastRec;           // 4,5,6,7
      WORD   m_wHeaderSize;        // 8,9
      WORD   m_wRecordSize;        // 10,11
      DWORD  m_reserved1;          // 12,13,14,15
      DWORD  m_reserved2;          // 16,17,18,19
      DWORD  m_reserved3;          // 20,21,22,23
      DWORD  m_reserved4;          // 24,25,26,27
      BYTE   m_nTableFlags;        // 28
      BYTE   m_nCodePage;          // 29
      WORD   m_reserved5;          // 30,31
      // ---------------------------------------------------------------------------------
      TDbfHeader(void)
      {
         SYSTEMTIME st;
         GetSystemTime(&st);
         m_nFileType = 0x30; // FoxBASE+/Dbase III plus, no memo
         m_sLUpdate[0] = LOBYTE( st.wYear );
         m_sLUpdate[1] = LOBYTE( st.wMonth);
         m_sLUpdate[2] = LOBYTE( st.wDay  );
         m_nLastRec    = 0;
         m_wHeaderSize = 0;
         m_wRecordSize = 0;
         m_reserved1   = m_reserved2 = m_reserved3 = m_reserved4 = 0;
         m_nTableFlags = 0;
         m_nCodePage   = 3;
         m_reserved5   = 0;
      };
      // ---------------------------------------------------------------------------------
};
#pragma pack(pop,1)
// -----------------------------------------------------------------------------------------------------------------
#pragma pack(push,1)
class TArray2Dbf : public T_ot4xb_base
{
   public:
      LPSTR*           m_ppFmt;
      TDbfField**      m_pFields;
      TDbfHeader*      m_pHeader;
      DWORD            m_nFields;
      DWORD            m_nLastRec;
      BOOL             m_bOverFlow;
      LPSTR            m_pBuffer;
      // ---------------------------------------------------------------------------------
      TArray2Dbf(ContainerHandle conaSt) 
      {
         ULONG n;
         ULONG sh = 1;
         m_bOverFlow = FALSE;
         m_pFields   = 0;
         m_pHeader   = new TDbfHeader;
         m_nLastRec  = 0;
         m_nFields = _conaGetLen(conaSt);
         m_ppFmt = 0;
         if( m_nFields )
         {
            m_ppFmt   = (LPSTR*) _xgrab( (64 + 4) * m_nFields );
            m_pFields = (TDbfField**) _xgrab(sizeof(TDbfField*) * m_nFields);
            m_pHeader->m_wHeaderSize = (sizeof(TDbfHeader) + 264);
            m_pHeader->m_wRecordSize = 1; // delete mark
            for( n = 0; n < m_nFields; n++ )
            {
               m_ppFmt[n] = _mk_ptr_(LPSTR,m_ppFmt, ((4 * m_nFields) + (n * 64)) );
               m_pFields[n] = new TDbfField(conaSt,n+1,&sh,m_ppFmt[n]);
               m_pHeader->m_wHeaderSize += sizeof(TDbfField);
               m_pHeader->m_wRecordSize = (m_pHeader->m_wRecordSize + MAKEWORD(m_pFields[n]->m_nLen,0));
            }
         }
         m_pBuffer = (LPSTR) _xgrab(1024);

      };
      // ---------------------------------------------------------------------------------
      ~TArray2Dbf( void )
      {
         if( m_ppFmt )  { _xfree( (void*) m_ppFmt ); m_ppFmt = 0; } 
         if( m_pFields) 
         {
            ULONG n;
            for( n=0; n < m_nFields; n++ )
            {
               if( m_pFields[n] ){ delete m_pFields[n]; m_pFields[n] = 0; }
            }
            _xfree( (void*) m_pFields );
            m_pFields = 0; m_nFields = 0;
         }
         if( m_pHeader ){ delete m_pHeader; m_pHeader = 0; }
         if( m_pBuffer ){ _xfree( (void*) m_pBuffer ); m_pBuffer = 0; }
      };
      // ---------------------------------------------------------------------------------
      LPSTR InitBuffer( ULONG cb , char ch = 32 )
      {
         if( cb > 1023 ) return 0;
         _bset((BYTE*) m_pBuffer,ch,cb);
         m_pBuffer[cb] = 0;
         return m_pBuffer;
      };
      // ---------------------------------------------------------------------------------
      void WriteArray(IStream* pOut , ContainerHandle cona)
      {
         ULONG n;
         m_nLastRec = 0;
         _conSizeA(cona,&m_nLastRec,0);
         WriteHeader(pOut);
         for( n= 1; n <= m_nLastRec; n++ ){ WriteRecord(pOut,cona,n);}
      };
      // ---------------------------------------------------------------------------------
      void WriteHeader( IStream* pOut )
      {
         ULONG cbr = 0;
         ULONG n;
         m_pHeader->m_nLastRec    = m_nLastRec;
         pOut->Write( (void*) m_pHeader , sizeof(TDbfHeader),&cbr);
         for( n = 0; n < m_nFields ; n++ ){ pOut->Write((void*) m_pFields[n],sizeof(TDbfField),&cbr); }
         pOut->Write( (void*) InitBuffer(1,0x0D),1,&cbr);
         pOut->Write( (void*) InitBuffer(263,0),263,&cbr);
      };
      // ---------------------------------------------------------------------------------
      void WriteRecord(IStream* pOut , ContainerHandle cona , ULONG nRec )
      {
         ULONG cbr = 0;
         ULONG n;
         pOut->Write((void*) InitBuffer(1),1 ,&cbr); // write Deleted field
         for( n = 0; n < m_nFields ; n++ ){WriteField(pOut,cona,n,nRec,m_ppFmt[n]);}
      }
      // ---------------------------------------------------------------------------------
      void WriteField(IStream* pOut , ContainerHandle cona , ULONG nn , ULONG nRec , LPSTR pFmt)
      {
         if( nn < m_nFields )
         {
            TDbfField* pField = m_pFields[nn];
            ContainerHandle con = _conNew(NULLCONTAINER);
            _conArrayGet(cona,con,nRec,nn+1,0); 
            
            switch( pField->m_chType )
            {
               case 'C':
               {
                  ULONG cb = MAKELONG(MAKEWORD(pField->m_nLen,0),0);
                  LPSTR p   = InitBuffer(cb);
                  ULONG cbr = 0;
                  if( _conCheckType(con,XPP_CHARACTER) ){_conGetCL(con,&cbr,p,cb);}
                  pOut->Write((void*) p,cb,&cbr);
                  break;
               }
               case 'L':
               {
                  ULONG cbr = 0;
                  BOOL  b = 0;
                  LPSTR p;
                  _conGetL(con,&b);
                  p = InitBuffer( 1 , (b ? 'T' : 'F') );
                  pOut->Write((void*)p,1,&cbr);
                  break;
               }
               case 'D':
               {
                  ULONG cbr = 0;
                  LPSTR p = InitBuffer(8);
                  _conGetDS(con,p);
                  pOut->Write((void*)p,8,&cbr);
                  break;
               }
               case 'N':
               {
                  ULONG cbr = 0;
                  ULONG cb  = MAKELONG(MAKEWORD(pField->m_nLen,0),0);
                  LPSTR p   = InitBuffer(cb);
                  if( pField->m_nDec )
                  {
                     double nd = 0.00F;
                     _conGetND(con,&nd);
                     if( sprintf_s(p,cb+1,pFmt,nd) < 0 )
                     {
                        InitBuffer(cb);
                        sprintf_s(p,cb+1,pFmt,0.0F);
                        m_bOverFlow = TRUE;
                     }
                  }
                  else
                  {
                     LONG n = 0;
                     _conGetLong(con,&n);
                     if( sprintf_s(p,cb+1,pFmt,n) < 0 )
                     {
                        InitBuffer(cb);
                        sprintf_s(p,cb+1,pFmt,0);
                        m_bOverFlow = TRUE;
                     }
                  }
                  pOut->Write((void*)p,cb,&cbr);
                  break;
               }
               default:  // empty sp string
               {
                  ULONG cb = MAKELONG(MAKEWORD(pField->m_nLen,0),0);
                  ULONG cbr = 0;
                  LPSTR p   = InitBuffer(cb);
                  pOut->Write((void*) p,cb,&cbr);
                  break;
               }
            }
         }
      };
      // ---------------------------------------------------------------------------------
};
#pragma pack(pop,1)
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
END_NAMESPACE() // a2dbf_ns
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
==> /docs/xb/functions/xb_function__A2DBF_.md ==>
### function `_a2dbf_()`

* Create a FOX database from the provided bidimensional array directly without use the DBE engine.
  * Only supported types are C,N,L,D

* Syntax:
  `_a2dbf_( aData , aStruct , cFName)  ->lOk `
<== <== 
*******************************************************************************************************************/
// -----------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_( _A2DBF_ ) // _a2dbf_( aData , aStruct , cFName)  ->lOk
{ 
   BOOL bOk = FALSE;
   BOOL bStructByRef = FALSE;
   ContainerHandle conaStruct = _conTParam( pl,2,&bStructByRef,XPP_ARRAY );
   if( conaStruct )
   {
      LPSTR pFName = _pszParam(pl,3);
      if( pFName )
      {
         IStream* pOut = 0;
         if(SUCCEEDED(SHCreateStreamOnFile(pFName,STGM_READWRITE|STGM_CREATE|STGM_SHARE_EXCLUSIVE,&pOut)))
         {
            a2dbf_ns::TArray2Dbf pa(conaStruct);
            BOOL bDataByRef = FALSE;
            ContainerHandle conaData = _conTParam( pl,1,&bDataByRef,XPP_ARRAY );
            if( conaData )
            {
               pa.WriteArray(pOut,conaData);
               bOk = TRUE;
               if( !bDataByRef ){ _conRelease(conaData); }
               conaData = NULLCONTAINER;
            }
            pOut->Release();
         }
         _xfree( (void*) pFName);
         pFName = 0;
      }
      if( !bStructByRef ){ _conRelease(conaStruct); }
      conaStruct = NULLCONTAINER;
   }
   _retl(pl,bOk);
}
// -----------------------------------------------------------------------------------------------------------------



