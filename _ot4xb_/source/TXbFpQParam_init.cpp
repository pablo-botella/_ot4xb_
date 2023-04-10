//------------------------------------------------------------
//  Project : Open Tools for Xbase++                          -
//  Repository : http ://www.xbwin.com                        -
//  Author : Pablo Botella Navarro( http ://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPXBASE(BOOL bOut){if(!bOut ) m_pdwStack[0] = (DWORD) _conNew( m_con );}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_BOOL(BOOL bOut ){ if( !bOut ){ IO_QT_DWORD(bOut); m_dw0 = (m_dw0 ? 1 : 0);} }
void TXbFpQParam::IO_QT_BYTEBOOL(BOOL bOut ){ if( !bOut ){ IO_QT_DWORD(bOut); m_dw0 = ( (m_dw0 & 0xFF) ? 1 : 0);} }
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_INT8(BOOL bOut )
{
   if( ! bOut )
   {
      switch( m_nType & 0xFF )
      {
         case XPP_NUMERIC   : { _conGetLong(m_con, (LONG*) &m_dw0 ); break;}
         case XPP_LOGICAL   : { _conGetL(m_con, (BOOL*) &m_dw0 ); break;}
         case XPP_CHARACTER : { ULONG ul; _conGetCL(m_con, &ul,(LPSTR ) ((void*) &m_dw0 ) , sizeof(BYTE) ); break;}
         case XPP_OBJECT    :
         {
            LPSTR p = (LPSTR) _conMCallLong( m_con , "_lock_");
            __try{ if(p) m_dw0 = MAKELONG(MAKEWORD(p[0],0),0);}
            __finally { _conMCallLong( m_con , "_unlock_"); }
            break;
         }
      }
      m_dw0 &= 0xFF;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_BYTE(BOOL bOut ){ IO_QT_INT8(bOut);}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_INT16(BOOL bOut)
{
   if( !bOut )
   {
      switch( m_nType & 0xFF )
      {
         case XPP_NUMERIC   : { _conGetLong(m_con, (LONG*) &m_dw0 ); break;}
         case XPP_LOGICAL   : { _conGetL(m_con, (BOOL*) &m_dw0 ); break;}
         case XPP_CHARACTER : { ULONG ul; _conGetCL(m_con, &ul,(LPSTR ) &m_dw0 , sizeof(WORD) ); break;}
         case XPP_OBJECT    :
         {
            WORD* p = (WORD*) _conMCallLong( m_con , "_lock_");
            __try{ if(p) m_dw0 = MAKELONG(p[0],0);}
            __finally { _conMCallLong( m_con , "_unlock_"); }
            break;
         }
      }
      m_dw0 &= 0xFFFF;
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_WORD(BOOL bOut){ IO_QT_INT16(bOut);}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_INT32(BOOL bOut){ if(!bOut ) _conGetLongEx(m_con,(LONG *) m_pdwStack );}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_DWORD(BOOL bOut){ IO_QT_INT32(bOut);}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_INT64(BOOL bOut)
{
   if( !bOut )
   {
      m_nStackSize = 2;  // size of stack in DWORDs
      switch ( m_nType & 0xFF )
      {
         case XPP_NUMERIC:
         {
            if( m_nType & _xpp_DOUBLE )
            {
               LONGLONG  qw;
               double    nd = 0.00F;
               DWORD   * p  = ( DWORD*) &qw;
               _conGetND( m_con , &nd);
               qw = (LONGLONG) nd;
               m_dw0 = p[0];
               m_dw1 = p[1];
            }
            else IO_QT_INT32(bOut); 
            return;
         }
         case XPP_CHARACTER:
         {
            ULONG n = 0;
            _conGetCL( m_con ,&n,(LPSTR) &m_dw0 , sizeof(LONGLONG));
            return;
         }
         case XPP_DATE:
         {
            _conGetDateAsFileTime(m_con,(FILETIME*) ((void*) &m_dw0) );
            return;
         }
         case XPP_OBJECT:
         {
            DWORD * p = (DWORD*) _conMCallLong( m_con , "_lock_");
            __try{ if(p){ m_dw0 = p[0];  m_dw1 = p[1];} }
            __finally { _conMCallLong( m_con , "_unlock_"); }
            return;
         }
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_QWORD(BOOL bOut){ IO_QT_INT64(bOut); }
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_FLOAT(BOOL bOut)
{
   if( !bOut )
   {
      FLOAT * psf = (FLOAT*) ((void*) &m_dw0);
      switch ( m_nType & 0xFF )
      {
         case XPP_NUMERIC:
         {
            double    nd = 0.00F;
            _conGetND( m_con , &nd);
            psf[0] = (FLOAT) nd;
            return;
         }
         case XPP_CHARACTER:
         {
            ULONG n = 0;
            _conGetCL( m_con ,&n,(LPSTR) ((void*) &m_dw0) ,sizeof(FLOAT));
            return;
         }
         case XPP_OBJECT:
         {
            DWORD * p = (DWORD*) _conMCallLong( m_con , "_lock_");
            __try{ if(p) m_dw0 = p[0]; }
            __finally { _conMCallLong( m_con , "_unlock_"); }
            return;
         }
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_DOUBLE(BOOL bOut)
{
   if( !bOut )
   {
      double * psf = (double*) ((void*) &m_dw0);
      m_nStackSize = 2;  // size of stack in DWORDs
      switch ( m_nType & 0xFF )
      {
         case XPP_NUMERIC: {  _conGetND( m_con , psf);  return; }
         case XPP_CHARACTER:
         {
            ULONG n = 0;
            _conGetCL( m_con ,&n,(LPSTR) ((void*) &m_dw0) ,sizeof(double));
            return;
         }
         case XPP_OBJECT:
         {
            DWORD * p = (DWORD*) _conMCallLong( m_con , "_lock_");
            __try{ if(p) {m_dw0 = p[0]; m_dw1 = p[1];}}
            __finally { _conMCallLong( m_con , "_unlock_"); }
            return;
         }
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_POINTER(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:
      {                             
         if( bOut )  _conPutL(m_con,(BOOL) (m_dw1 & m_dwIntMask));
         else
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetL( m_con , (BOOL*) &m_dw1 );
         }
         return;
      }
      case XPP_NUMERIC:
      {
         if(!bOut) _conGetLong( m_con , (LONG*) ((void*) &m_dw0) );
         return;
      }
      case XPP_CHARACTER:
      {
         if( bOut)
         {
           if( m_bConLock )
           {
              ot4xb_conUnlockC( m_con );
              m_bConLock = FALSE;
              m_pStr = 0;
           }
         }
         else
         {
            if( m_bByRef )
            {
               if( ot4xb_conWLockC( m_con, &m_pStr , &m_nLen) == 0 )
               {
                  m_pdwStack[0] = (DWORD) m_pStr;
                  m_bConLock = TRUE;
               }
            }
            else
            {
               if( ot4xb_conRLockC( m_con, &m_pStr , &m_nLen) == 0 )
               {
                  m_pdwStack[0] = (DWORD) m_pStr;
                  m_bConLock = TRUE;
               }
            }            
         }
         return;
      }
      case XPP_DATE:
      {
         if( bOut ) 
         {        
            _conPutDateFromFileTime( m_con, (FILETIME*) ((void*) &m_dw1) );
         }
         else
         {
            _conGetDateAsFileTime( m_con, (FILETIME*) ((void*) &m_dw1) );
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
         }
         return;
      }
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         LONG*  p;
         if( bOut )
         {
            p = (LONG*) m_pStr;
            if( m_pStr )
            {
               for( n = 0; n < nItems; n++ ) _conArrayPutNL(m_con,p[n],n+1,0);
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(DWORD) * (nItems+1) );
               p = (LONG*) m_pStr;
               m_pdwStack[0] = (DWORD) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = _conArrayGetNLEx(m_con,n+1,0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT:
      {                                
         if( bOut )
         {
            _conMCallLong( m_con , "_unlock_");
            m_bObjLock    = FALSE;
         }
         else
         {
            m_pdwStack[0] = (DWORD) _conMCallLong( m_con , "_lock_");
            m_bObjLock    = TRUE;
         }
         return;
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPBOOL(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:  { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )  _conPutL(m_con,(BOOL) (m_dw1 & m_dwIntMask) );
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
            m_dw1 = ( (m_dw1 & m_dwIntMask) ? 1 : 0 );
         }
         return;
      }
      case XPP_CHARACTER:{ IO_QT_POINTER(bOut); return; }
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         BOOL*  p;

         if( bOut )
         {
            if( m_pStr )
            {
               p = (BOOL*) m_pStr;
               for( n = 0; n < nItems; n++ ) _conArrayPutL(m_con,p[n],n+1,0);
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(DWORD) * (nItems+1) );
               p = (BOOL*) m_pStr;
               m_pdwStack[0] = (DWORD) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (BOOL) ( _conArrayGetNLEx(m_con,n+1,0) ? 1 : 0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT:{ IO_QT_POINTER(bOut); return; }
   }
}
// -----------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPBYTEBOOL(BOOL bOut)
{
   m_dwIntMask = 0xFF;
   IO_QT_LPBOOL(bOut);
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPINT8(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:  { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            m_dw1 = ( (m_dw1 & 0xFF) | ( (m_dw1 & 0x80) ? 0xFFFFFF00 : 0) );
             _conPutNL(m_con,(LONG) m_dw1);
         }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         LPSTR  p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
            
               p = m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  LONG nVal = (LONG) MAKELONG( MAKEWORD( p[n],0),0);
                  nVal = ( (nVal & 0xFF) | ( (nVal & 0x80) ? 0xFFFFFF00 : 0) );
                  _conArrayPutNL(m_con,nVal,n+1,0);
               }
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(char) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (char) ( _conArrayGetNLEx(m_con,n+1,0) & 0xFF );
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPBYTE(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:  { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            m_dw1 = (m_dw1 & 0xFF);
             _conPutNL(m_con,(LONG) m_dw1);
         }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         LPBYTE p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
               p = (LPBYTE) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  LONG nVal = (LONG) MAKELONG( MAKEWORD( p[n],0),0);
                  _conArrayPutNL(m_con,nVal,n+1,0);
               }
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(BYTE) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (LPBYTE) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (BYTE) ( _conArrayGetNLEx(m_con,n+1,0) & 0xFF );
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPINT16(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:  { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            m_dw1 = ( (m_dw1 & 0xFFFF) | ( (m_dw1 & 0x8000) ? 0xFFFF0000 : 0) );
             _conPutNL(m_con,(LONG) m_dw1);
         }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         SHORT * p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
            
               p = (SHORT*) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  LONG nVal = (LONG) MAKELONG( p[n],0);
                  nVal = ( (nVal & 0xFFFF) | ( (nVal & 0x8000) ? 0xFFFF0000 : 0) );
                  _conArrayPutNL(m_con,nVal,n+1,0);
               }
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(WORD) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (SHORT*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (SHORT) ( _conArrayGetNLEx(m_con,n+1,0) & 0xFFFF );
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPWORD(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:{ IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            m_dw1 = (m_dw1 & 0xFFFF);
             _conPutNL(m_con,(LONG) m_dw1);
         }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         WORD*   p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
            
               p = (WORD*) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  LONG nVal = (LONG) MAKELONG( p[n],0);
                  nVal = (nVal & 0xFFFF);
                  _conArrayPutNL(m_con,nVal,n+1,0);
               }
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(WORD) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (WORD*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (WORD) ( _conArrayGetNLEx(m_con,n+1,0) & 0xFFFF );
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}

//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPINT32(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL:  { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut ) { _conPutNL(m_con,(LONG) m_dw1); }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         LONG*   p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
            
               p = (LONG*) m_pStr;
               for( n = 0; n < nItems; n++ ) _conArrayPutNL(m_con,p[n],n+1,0);
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(LONG) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (LONG*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = _conArrayGetNLEx(m_con,n+1,0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPDWORD(BOOL bOut)
{
   switch ( m_nType & 0xFF )
   {
      case XPP_LOGICAL: { IO_QT_POINTER(bOut); return; }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            if( m_dw1 & 0x80000000 ) _conPutND( m_con , (double) m_dw1 );
            else _conPutNL(m_con,(LONG) m_dw1);
         }
         else    
         {
            m_pdwStack[0] = (DWORD) ((void*)&m_dw1);
            _conGetLong( m_con , (LONG*) &m_dw1);
         }
         return;
      }
      
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         DWORD* p;
         
         if( bOut )
         {
            if( m_pStr )
            {     
            
               p = (DWORD*) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  if( p[n] & 0x80000000 ) _conArrayPutND(m_con,(double) (p[n]),n+1,0);
                  else _conArrayPutNL(m_con,p[n],n+1,0);
               }
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(LONG) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (DWORD*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = _conArrayGetNLEx(m_con,n+1,0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPINT64(BOOL bOut)
{
   LONGLONG * p;
   switch ( m_nType & 0xFF )
   {
      case XPP_ARRAY :
      {
         if( bOut )
         {
            if( m_pStr )
            {
               ULONG nItems = _conGetArrayLen(m_con);  
               ULONG  n;
               p = (LONGLONG *) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  _conArrayPutCL(m_con,(LPSTR) ((void*) &(p[n])), sizeof(LONGLONG),n+1,0);
               }
               _xfree( (void*) m_pStr ); m_pStr = 0;
            }
         }
         else 
         {
            m_pStr = (LPSTR) _cona2i64a(m_con,NULL);
            m_pdwStack[0] = (DWORD) m_pStr;
            if( m_pStr ) m_bxgrab = TRUE; 
         }
         return;
      }
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            p = (LONGLONG*) ((void*)(&m_dw1));
            _conPutND(m_con,(double) p[0]);
         }
         else
         {
            double nd;
            _conGetND( m_con , &nd);
            p = (LONGLONG*) ((void*)(&m_dw1));
            p[0] = (LONGLONG) nd;
            m_pdwStack[0] = (DWORD) p;
         }
         return;
      }
      case XPP_DATE:
      {
         p = (LONGLONG*) ((void*)(&m_dw1));
         if( bOut )
         {
            _conPutDateFromFileTime(m_con,(FILETIME*) p );
            _conPutND(m_con,(double) p[0]);
         }
         else
         {
            m_pdwStack[0] = (DWORD) p;
            _conGetDateAsFileTime(m_con,(FILETIME*) p );
         }
         return;
      
      
      }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPQWORD(BOOL bOut){ if( !(m_nType & XPP_NUMERIC) ) IO_QT_LPINT64(bOut); }
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPFLOAT(BOOL bOut)
{
   FLOAT * psf = (FLOAT*) ((void*) &m_dw1);
   switch ( m_nType & 0xFF )
   {
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            _conPutND(m_con,(double) psf[0] );
         }
         else    
         {                                       
            double nd = 0.00F;
            m_pdwStack[0] = (DWORD) psf;
            _conGetND( m_con , &nd);
            psf[0] = (FLOAT) nd;
         }
         return;
      }
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         FLOAT*   p;
         if( bOut )
         {
            if( m_pStr )
            {     
               p = (FLOAT*) m_pStr;
               for( n = 0; n < nItems; n++ ) _conArrayPutND(m_con,(double) p[n],n+1,0);
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(FLOAT) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (FLOAT*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = (FLOAT) _conArrayGetND(m_con,n+1,0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_LPDOUBLE(BOOL bOut)
{
   double * psf = (double *) ((void*) &m_dw1);
   switch ( m_nType & 0xFF )
   {
      case XPP_NUMERIC:
      {
         if( bOut )
         {
            _conPutND(m_con, psf[0] );
         }
         else    
         {                                       
            m_pdwStack[0] = (DWORD) psf;
            _conGetND( m_con , &psf[0]);
         }
         return;
      }
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen(m_con);                 
         ULONG  n;
         double*   p;
         if( bOut )
         {
            if( m_pStr )
            {     
               p = (double*) m_pStr;
               for( n = 0; n < nItems; n++ ) _conArrayPutND(m_con, p[n],n+1,0);
               _xfree( m_pStr ); m_pStr = 0; m_bxgrab      = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( sizeof(double) * (nItems+1) );
               m_pdwStack[0] = (DWORD) m_pStr;
               p = (double*) m_pStr;
               for( n = 0; n < nItems; n++ ) p[n] = _conArrayGetND(m_con,n+1,0);
               m_bxgrab      = TRUE;
            }
         }
         return;
      }
      case XPP_CHARACTER: { IO_QT_POINTER(bOut); return; }
      case XPP_OBJECT: { IO_QT_POINTER(bOut); return; }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_STR2WIDE(BOOL bOut)
{
   LPWSTR pw   = 0;
   LPSTR pAnsi = 0;
   switch( m_nType & 0xFF )
   {
      case XPP_CHARACTER:
      {
         if( bOut)
         {
            if( m_pStr ) _xfree( (void*) m_pStr);
         }
         else
         {
            if( ot4xb_conRLockC( m_con , &pAnsi , &m_nLen) == 0)
            {
               m_pStr = (LPSTR) _xgrab( (m_nLen + 1) * 2 );
               pw = (LPWSTR) ( (void*) m_pStr );
               m_pdwStack[0] = (DWORD) pw;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,m_nLen,pw,m_nLen);
               m_bxgrab   = TRUE;
               ot4xb_conUnlockC(m_con);
            }
         }
         return;
      }
      case XPP_OBJECT:
      {
         if( bOut)
         {
            if( m_pStr ) _xfree( (void*) m_pStr);
         }
         else
         {
            pAnsi = (LPSTR) _conMCallLong( m_con , "_lock_" , &m_nLen );
            if( pAnsi)
            {
               m_pStr = (LPSTR) _xgrab( (m_nLen + 1) * 2 );
               pw = (LPWSTR) ( (void*) m_pStr );
               m_pdwStack[0] = (DWORD) pw;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,m_nLen,pw,m_nLen);
               m_bxgrab   = TRUE;
            }
            _conMCallLong( m_con , "_unlock_");
         }
         return;
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_STR2WIDE_W(BOOL bOut)
{
   LPWSTR pw   = 0;
   LPSTR pAnsi = 0;
   switch( m_nType & 0xFF )
   {
      case XPP_CHARACTER:
      {
         if( bOut)
         {
            if( m_pStr )
            {
               if( ot4xb_conWLockC( m_con , &pAnsi , &m_nLen) == 0)
               {
                  pw = (LPWSTR) ( (void*) m_pStr );
                  WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pw,m_nLen,pAnsi,m_nLen,0,0);
                  ot4xb_conUnlockC(m_con);
               }  
               _xfree( (void*) m_pStr);
            }
         }
         else
         {
            if( ot4xb_conRLockC( m_con , &pAnsi , &m_nLen) == 0)
            {
               m_pStr = (LPSTR) _xgrab( (m_nLen + 1) * 2 );
               pw = (LPWSTR) ( (void*) m_pStr );
               m_pdwStack[0] = (DWORD) pw;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,m_nLen,pw,m_nLen);
               m_bxgrab   = TRUE;
               ot4xb_conUnlockC(m_con);
            }
         }
         return;
      }
      case XPP_OBJECT:
      {
         if( bOut)
         {
            if( m_pStr )
            {
               pAnsi = (LPSTR) _conMCallLong( m_con , "_lock_" , &m_nLen );
               if( pAnsi )
               {
                  pw = (LPWSTR) ( (void*) m_pStr );
                  WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,pw,m_nLen,pAnsi,m_nLen,0,0);
               }  
               _conMCallLong( m_con , "_unlock_");
               _xfree( (void*) m_pStr);
            }
         }
         else
         {
            pAnsi = (LPSTR) _conMCallLong( m_con , "_lock_" , &m_nLen );
            if( pAnsi)
            {
               m_pStr = (LPSTR) _xgrab( (m_nLen + 1) * 2 );
               pw = (LPWSTR) ( (void*) m_pStr );
               m_pdwStack[0] = (DWORD) pw;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,m_nLen,pw,m_nLen);
               m_bxgrab   = TRUE;
            }
            _conMCallLong( m_con , "_unlock_");
         }
         return;
      }
   }
}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_HWND(BOOL bOut){ if(! bOut ) m_dw0 = (DWORD) _conGetHWND(m_con);}
//----------------------------------------------------------------------------------------------------------------------
void TXbFpQParam::IO_QT_VARIANT(BOOL bOut)
{
   if( !bOut )
   {
      ULONG cb = 0;
      m_nStackSize = 4;  // size of stack in DWORDs
      if( m_nType & XPP_CHARACTER){  _conSizeC(m_con,&cb); }
      if( cb == 16 )
      {
         ULONG n = 0;
         _conGetCL( m_con ,&n,(LPSTR) &m_dw0 ,16);
      }
      else { m_dw0 = 0x0A;m_dw1 = 0;m_dw2 = 0x80020004;m_dw3 = 0;} // DEFAULT vtMissing
      return;
   }
}
// -----------------------------------------------------------------------------------------------------------------
