//------------------------------------------------------------
//  Project : Open Tools for Xbase++                          -
//  Repository : http ://www.xbwin.com                        -
//  Author : Pablo Botella Navarro( http ://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
// -----------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_LPXBASE
   |: Puts a ContainerHandle copy of the provided Xbase++ parameter in the call stack, not writing
      the out value on return.
}}*/
void TXbFpQParam::IO_QT_LPXBASE(BOOL bOut){if(!bOut ) m_pdwStack[0] = (DWORD) _conNew( m_con );}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_BOOL
   |: Takes the argument as an int32 and puts 1 in the stack if the value is non zero, 0 if it is zero,
      using the following rules:
   |include-note-id: con-get-long-ex
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_BOOL(BOOL bOut ){ if( !bOut ){ IO_QT_DWORD(bOut); m_dw0 = (m_dw0 ? 1 : 0);} }
// ----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_BYTEBOOL
   |: Takes the argument as an int32 and puts 1 in the stack if the first byte value is non zero, 0 if it is zero,
      using the following rules:
   |include-note-id: con-get-long-ex
   |note: The value is not written back to the parameter on return, so it is input only.
   |note: Only the first byte is used, so the value is truncated. eg. 0x1000 will be false because 0x1000 & 0xFF == 0 
}}*/
void TXbFpQParam::IO_QT_BYTEBOOL(BOOL bOut ){ if( !bOut ){ IO_QT_DWORD(bOut); m_dw0 = ( (m_dw0 & 0xFF) ? 1 : 0);} }
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_INT8
   |: Puts the low byte of the argument in the stack, to be read by the called function as a signed
      8-bit integer (-128 to 127). By xb type:
      - Numeric: the low byte of its integer value.
      - Logical: 1 for .T., 0 for .F.
      - Character: a binary string, read as raw bytes; its first byte is the value (so '0' gives 48, not 0).
      - Object: the first byte of its internal buffer is taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Only the low byte is kept, so larger values are truncated (e.g. 0x1234 gives 0x34).
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
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
/*{{note-id: IO_QT_BYTE
   |: Puts the low byte of the argument in the stack, to be read by the called function as an unsigned
      8-bit integer (0 to 255). By xb type:
      - Numeric: the low byte of its integer value.
      - Logical: 1 for .T., 0 for .F.
      - Character: a binary string, read as raw bytes; its first byte is the value (so '0' gives 48, not 0).
      - Object: the first byte of its internal buffer is taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Only the low byte is kept, so larger values are truncated (e.g. 0x1234 gives 0x34).
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_BYTE(BOOL bOut ){ IO_QT_INT8(bOut);}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_INT16
   |: Puts the low two bytes of the argument in the stack, to be read by the called function as a
      signed 16-bit integer (-32768 to 32767). By xb type:
      - Numeric: the low two bytes of its integer value.
      - Logical: 1 for .T., 0 for .F.
      - Character: a binary string, read as raw bytes; its first two bytes are the value (not the text).
      - Object: the first two bytes of its internal buffer are taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Only the low two bytes are kept, so larger values are truncated (e.g. 0x12345 gives 0x2345).
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
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
/*{{note-id: IO_QT_WORD
   |: Puts the low two bytes of the argument in the stack, to be read by the called function as an
      unsigned 16-bit integer (0 to 65535). By xb type:
      - Numeric: the low two bytes of its integer value.
      - Logical: 1 for .T., 0 for .F.
      - Character: a binary string, read as raw bytes; its first two bytes are the value (not the text).
      - Object: the first two bytes of its internal buffer are taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Only the low two bytes are kept, so larger values are truncated (e.g. 0x12345 gives 0x2345).
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_WORD(BOOL bOut){ IO_QT_INT16(bOut);}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_INT32
   |: Reads the argument as an int32, using the following rules:
   |include-note-id: con-get-long-ex
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_INT32(BOOL bOut){ if(!bOut ) _conGetLongEx(m_con,(LONG *) m_pdwStack );}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_DWORD
   |: Same as IO_QT_INT32 (an unsigned int32; the sign only matters for the LP output variant),
      read using the following rules:
   |include-note-id: con-get-long-ex
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_DWORD(BOOL bOut){ IO_QT_INT32(bOut);}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_INT64
   |: Puts an 8-byte value in the stack, to be read by the called function as a signed 64-bit
      integer. By xb type:
      - Numeric: the number converted to a 64-bit integer.
      - Character: a binary string, read as raw bytes; its first 8 bytes are the value (not the text).
      - Date: converted to an 8-byte FILETIME.
      - Object: the first 8 bytes of its internal buffer are taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
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
/*{{note-id: IO_QT_QWORD
   |: Puts an 8-byte value in the stack, to be read by the called function as an unsigned 64-bit
      integer. By xb type:
      - Numeric: the number converted to a 64-bit integer.
      - Character: a binary string, read as raw bytes; its first 8 bytes are the value (not the text).
      - Date: converted to an 8-byte FILETIME.
      - Object: the first 8 bytes of its internal buffer are taken (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
void TXbFpQParam::IO_QT_QWORD(BOOL bOut){ IO_QT_INT64(bOut); }
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_FLOAT
   |: Puts a 32-bit single-precision float (4 bytes) in the stack. By xb type:
      - Numeric: the number converted to a 32-bit single.
      - Character: a binary string that already holds a 32-bit single; its first 4 bytes are used.
      - Object: the first 4 bytes of its internal buffer are used (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Character and Object are taken as raw bytes and must already be a 32-bit single. A 64-bit
      double placed there keeps only its first 4 bytes, giving garbage - convert to single first.
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
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
/*{{note-id: IO_QT_DOUBLE
   |: Puts a 64-bit double-precision float (8 bytes) in the stack. By xb type:
      - Numeric: the number as a 64-bit double.
      - Character: a binary string that already holds a 64-bit double; its first 8 bytes are used.
      - Object: the first 8 bytes of its internal buffer are used (a GWST object or pt2gp(pointer));
        if the object cannot provide a buffer, the stack keeps its default 0.
   |note: Character and Object are taken as raw bytes and must already be a 64-bit double. A 32-bit
      single placed there is not widened, so the 8 bytes are misread - convert to double first.
   |note: The value is not written back to the parameter on return, so it is input only.
}}*/
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
/*{{note-id: IO_QT_POINTER
   |: Passes a pointer in the stack. By xb type:
      - Numeric: the number is used directly as the pointer (an address).
      - Character: a pointer to the string buffer is passed. If a value is to be received back, the
        parameter should be provided by reference.
      - Logical: the value is stored in a temporary buffer and its address is passed. If the
        parameter was provided by reference, the value in the buffer is written back to it.
      - Date: the value is stored in a temporary 8-byte buffer as a FILETIME with time 00:00. If the
        parameter was provided by reference, the date is extracted back from the buffer and stored
        in it. The time is discarded and there is no timezone information.
      - Array: passed as a buffer of 32-bit integers, filled from the elements; on return the values
        are written back to the elements, whether it was provided by value or by reference.
      - Object: the pointer to its internal buffer is passed (a GWST object or pt2gp(pointer)); if
        the object cannot provide it, the stack keeps its default 0 (a NULL pointer).
}}*/
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
/*{{note-id: IO_QT_LPBOOL
   |: Passes a pointer to a BOOL (or BOOL array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: passed as 1 for non-zero or 0 for zero. On return, if provided by reference, your
        variable is overwritten with .T. or .F. - now a logical, so a later comparison like .T. == 0
        fails with a type error in Xbase. To pass a pointer, do not use a Numeric: wrap it in
        pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is promoted to int32 and stored as 1 or 0 - a LOGICAL gives 1/0, a
        NUMERIC gives 1 for non-zero, a CHARACTER gives 1 unless its bytes are a binary 0. On return
        the whole array is promoted to logicals (.T./.F.), and here @ makes no difference at all: it
        is always rewritten, even elements the callee never touched, so {0,1,2} comes back
        {.F.,.T.,.T.}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPBYTEBOOL
   |: Passes a pointer to a BYTEBOOL (or BYTEBOOL array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: passed as 1 for a non-zero low byte or 0. On return, if provided by reference, your
        variable is overwritten with .T. or .F. - now a logical, so a later comparison like .T. == 0
        fails with a type error in Xbase. To pass a pointer, do not use a Numeric: wrap it in
        pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is promoted to int32 and stored as 1 or 0 - a LOGICAL gives 1/0, a
        NUMERIC gives 1 for non-zero, a CHARACTER gives 1 unless its bytes are a binary 0. On return
        the whole array is promoted to logicals (.T./.F.), and here @ makes no difference at all: it
        is always rewritten, even elements the callee never touched, so {0,1,2} comes back
        {.F.,.T.,.T.}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
void TXbFpQParam::IO_QT_LPBYTEBOOL(BOOL bOut)
{
   m_dwIntMask = 0xFF;
   
   switch( m_nType & 0xFF )
   {
      case XPP_ARRAY:
      {
         ULONG nItems = _conGetArrayLen( m_con );
         ULONG  n;
         LPBYTE p;

         if( bOut )
         {
            if( m_pStr )
            {
               p = (LPBYTE) m_pStr;
               for( n = 0; n < nItems; n++ ) 
               {
                  _conArrayPutL( m_con, p[ n ] & 0xFF, n + 1, 0 ); 
               }
               _xfree( m_pStr );
               m_pStr = 0;
               m_bxgrab = FALSE;
            }
         }
         else
         {
            if( nItems )
            {
               m_pStr = (LPSTR) _xgrab( nItems + 1  );
               p = (BYTE*) m_pStr;
               m_pdwStack[ 0 ] = (DWORD) m_pStr;
               for( n = 0; n < nItems; n++ )
               {
                  p[ n ] = (BYTE) ( _conArrayGetNLEx( m_con, n + 1, 0 ) ? 1 : 0 ) & 0xFF;
               }
               m_bxgrab = TRUE;
            }
         }
         return;
      }
      default: { IO_QT_LPBOOL( bOut ); return; }

   }
   
}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_LPINT8
   |: Passes a pointer to a signed 8-bit integer (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its low byte is passed, read as a signed value (-128..127). On return, if provided
        by reference, that signed byte is written back as a Numeric. To pass a pointer, do not use a
        Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element's low byte is passed. On return every element is written back as a signed
        Numeric (-128..127), always, even ones the callee never touched, so {200,256,300} comes back
        {-56,0,44}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPBYTE
   |: Passes a pointer to an unsigned 8-bit integer (BYTE) (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its low byte is passed, read as an unsigned value (0..255). On return, if provided
        by reference, that byte is written back as a Numeric. To pass a pointer, do not use a
        Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element's low byte is passed. On return every element is written back as a
        Numeric (0..255), always, even ones the callee never touched, so {200,256,300} comes back
        {200,0,44}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPINT16
   |: Passes a pointer to a signed 16-bit integer (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its low 16 bits are passed, read as a signed value (-32768..32767). On return, if
        provided by reference, that signed value is written back as a Numeric. To pass a pointer, do
        not use a Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element's low 16 bits are passed. On return every element is written back as a
        signed Numeric (-32768..32767), always, even ones the callee never touched, so {70000} comes
        back {4464}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPWORD
   |: Passes a pointer to an unsigned 16-bit integer (WORD) (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its low 16 bits are passed, read as an unsigned value (0..65535). On return, if
        provided by reference, that value is written back as a Numeric. To pass a pointer, do not use
        a Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element's low 16 bits are passed. On return every element is written back as a
        Numeric (0..65535), always, even ones the callee never touched, so {70000} comes back {4464}.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPINT32
   |: Passes a pointer to a signed 32-bit integer (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its 32-bit value is passed, signed. On return, if provided by reference, it is
        written back as a Numeric. To pass a pointer, do not use a Numeric: wrap it in
        pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is passed as a 32-bit signed integer. On return every element is written
        back as a Numeric, always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPDWORD
   |: Passes a pointer to an unsigned 32-bit integer (DWORD) (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its 32-bit value is passed, unsigned (0..4294967295). On return, if provided by
        reference, it is written back as a Numeric - as a double when bit 31 is set (>= 2147483648),
        since it no longer fits a signed 32-bit value. To pass a pointer, do not use a Numeric: wrap
        it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is passed as a 32-bit unsigned integer. On return every element is
        written back as a Numeric, always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPINT64
   |: Passes a pointer to a signed 64-bit integer (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: its 64-bit value is passed. On return, if provided by reference, it comes back as a
        double, so a value beyond 2^53 loses precision - there is no way around it. For an exact
        64-bit result use an object instead. To pass a pointer, do not use a Numeric: wrap it in
        pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is passed as a 64-bit integer. On return every element comes back as an
        8-byte character (exact), always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPQWORD
   |: Passes a pointer to an unsigned 64-bit integer (QWORD) (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: not passed - a Numeric cannot hold an unsigned 64-bit value. Use one of the other
        options instead (a character buffer or an object); there are plenty.
      - Character: passed as a memory buffer.
      - Array: each element is passed as a 64-bit integer. On return every element comes back as an
        8-byte character (exact), always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
void TXbFpQParam::IO_QT_LPQWORD(BOOL bOut){ if( !(m_nType & XPP_NUMERIC) ) IO_QT_LPINT64(bOut); }
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_LPFLOAT
   |: Passes a pointer to a single-precision float (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: narrowed to a 32-bit single on the way in. On return, if provided by reference, the
        single is widened back to a Numeric - only ~7 significant digits survive the round trip. To
        pass a pointer, do not use a Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is narrowed to a 32-bit single. On return every element is widened back
        to a Numeric, always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_LPDOUBLE
   |: Passes a pointer to a double-precision float (or array) in the stack.
      - Logical: written back as a logical when provided by reference.
      - Numeric: passed as a double, unchanged - the Xbase Numeric is already a double. On return,
        if provided by reference, it is written straight back with no loss. To pass a pointer, do not
        use a Numeric: wrap it in pt2gp(pointer).
      - Character: passed as a memory buffer.
      - Array: each element is passed as a double. On return every element is written back as a
        Numeric, always, even ones the callee never touched.
      - Object: the object's internal buffer pointer is passed (a GWST object or pt2gp(pointer)).
      - NIL: passed as 0 (a null pointer).
}}*/
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
/*{{note-id: IO_QT_STR2WIDE
   |: Passes a pointer to a wide (UTF-16) copy of the text, converted from ANSI. Read only: nothing
      is written back.
      - Character: its text is converted into a temporary wide buffer and that pointer is passed.
      - Object: the text in its internal buffer is converted the same way.
      - Any other type: nothing is passed.
}}*/
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
/*{{note-id: IO_QT_STR2WIDE_W
   |: Passes a pointer to a wide (UTF-16) copy of the text, converted from ANSI; on return the
      buffer is converted back to ANSI into the argument - the writable STR2WIDE.
      - Character: its text is converted into a temporary wide buffer and that pointer is passed. On
        return the buffer is converted back into the variable, keeping its original length.
      - Object: the same, back into its internal buffer.
      - Any other type: nothing is passed.
}}*/
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
/*{{note-id: IO_QT_HWND
   |: Puts a window handle (HWND) in the stack. Input only, nothing is written back.
      - Numeric: its value is the handle.
      - Object: its GetHWND() method provides the handle (any Xbp window object).
      - Any other type: a NULL handle (0).
}}*/
void TXbFpQParam::IO_QT_HWND(BOOL bOut){ if(! bOut ) m_dw0 = (DWORD) _conGetHWND(m_con);}
//----------------------------------------------------------------------------------------------------------------------
/*{{note-id: IO_QT_VARIANT
   |: Puts a 16-byte VARIANT by value in the stack. Input only, nothing is written back.
      - Character of exactly 16 bytes: its bytes are the VARIANT, copied verbatim.
      - Any other case: the default vtMissing.
}}*/
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
