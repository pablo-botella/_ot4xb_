//------------------------------------------------------------
//  Project: Open Tools for Xbase++                          -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#include <ot4xb_api.h>
//-----------------------------------------------------------------------------------------------------------------------
/*******************************************************************************************************************
<xbdoc>
   <function-family>
      <name>GWST member accessors</name>
      <source>gwst_xb_setget.cpp</source>
      <category>structures/internal</category>
      <description>
         Internal read/write helpers used by OT4XB GWST structure classes to expose binary structure members as
         Xbase++ properties. They are exported implementation details and are not intended to be called directly
         from application code.
      </description>
      <status>Internal GWST support API; not intended for direct application calls.</status>
      <remarks>
         These functions are generated into GWST member accessors by the structure/class machinery. Application
         code normally uses the structure member directly, for example oRect:left or oFindData:cFileName, and
         does not call _gwst_xbsetget_*() functions by hand.

         The common calling shape is _gwst_xbsetget_type_( @xValue, nPCount, @pStorage, nShift, nOffset,
         nStorageSize, pGhost, nMemberSize ). When nPCount is greater than 1 the helper writes xValue into the
         structure storage. Otherwise it reads the member and returns the converted Xbase++ value.

         Storage can be the default Xbase++ character buffer used by GWST, a linked/allocated memory pointer, or
         a direct ghost pointer supplied by the structure runtime. Character-buffer storage is locked while the
         member is read or written and unlocked before returning.
      </remarks>
      <functions>
         <function name="_gwst_xbsetget_bool_"        c-type="BOOL"       xbase-type="logical" description="Reads or writes a Win32 BOOL value." />
         <function name="_gwst_xbsetget_bytebool_"    c-type="BYTE"       xbase-type="logical" description="Reads or writes a byte-sized boolean value." />
         <function name="_gwst_xbsetget_byte_"        c-type="BYTE"       xbase-type="numeric" description="Reads or writes an unsigned 8-bit value." />
         <function name="_gwst_xbsetget_sint8_"       c-type="INT8"       xbase-type="numeric" description="Reads or writes a signed 8-bit value with sign extension on read." />
         <function name="_gwst_xbsetget_word_"        c-type="WORD"       xbase-type="numeric" description="Reads or writes an unsigned 16-bit value." />
         <function name="_gwst_xbsetget_sint16_"      c-type="INT16"      xbase-type="numeric" description="Reads or writes a signed 16-bit value with sign extension on read." />
         <function name="_gwst_xbsetget_dword_"       c-type="DWORD"      xbase-type="numeric" description="Reads or writes a 32-bit value using Xbase++ LONG representation." />
         <function name="_gwst_xbsetget_uint32_"      c-type="UINT32"     xbase-type="numeric" description="Reads an unsigned 32-bit value as LONG or double when the high bit is set." />
         <function name="_gwst_xbsetget_dword64_"     c-type="QWORD"      xbase-type="character" description="Reads or writes an unsigned 64-bit value as an 8-byte string." />
         <function name="_gwst_xbsetget_nint64_"      c-type="INT64"      xbase-type="character" description="Reads or writes a signed 64-bit value as an 8-byte string." />
         <function name="_gwst_xbsetget_pclipvar_"    c-type="PXBASEVAR"  xbase-type="any" description="Stores a retained Xbase++ container handle in the structure member." />
         <function name="_gwst_xbsetget_xppguiwnd_"   c-type="pointer"    xbase-type="numeric" description="Stores a GUI window C++ pointer, resolving Xbase++ objects through ::GetTwWinBaseCppPointer()." />
         <function name="_gwst_xbsetget_float_"       c-type="FLOAT"      xbase-type="numeric" description="Reads or writes a 32-bit floating point value." />
         <function name="_gwst_xbsetget_double_"      c-type="DOUBLE"     xbase-type="numeric" description="Reads or writes a 64-bit floating point value." />
         <function name="_gwst_xbsetget_lpstr_"       c-type="LPSTR"      xbase-type="numeric" description="Alias of the DWORD accessor for pointer-sized string pointers in 32-bit builds." />
         <function name="_gwst_xbsetget_binstr_"      c-type="BYTE[]"     xbase-type="character" description="Reads or writes a fixed-size binary buffer." />
         <function name="_gwst_xbsetget_szstr_"       c-type="SZSTR"      xbase-type="character" description="Reads or writes a fixed-size zero-terminated ANSI character buffer." />
         <function name="_gwst_xbsetget_szwstr_"      c-type="SZWSTR"     xbase-type="character" description="Reads or writes a fixed-size Unicode buffer, converting to or from ANSI at the Xbase++ boundary." />
         <function name="_gwst_xbsetget_dynsz_"       c-type="DYNSZ"      xbase-type="character" description="Reads or writes an owned dynamic ANSI string pointer allocated with _xgrab() and released with _xfree()." />
         <function name="_gwst_xbsetget_wordnet_"     c-type="WORD"       xbase-type="numeric" description="Reads or writes a network-byte-order 16-bit value." />
         <function name="_gwst_xbsetget_dwordnet_"    c-type="DWORD"      xbase-type="numeric" description="Reads or writes a network-byte-order 32-bit value." />
         <function name="_gwst_xbsetget_xdate_"       c-type="CHAR[8]"    xbase-type="date" description="Reads or writes an 8-byte Xbase++ date representation." />
         <function name="_gwst_xbsetget_pointer32_"   c-type="POINTER32"  xbase-type="numeric" description="Alias of the DWORD accessor for 32-bit pointers." />
         <function name="_gwst_xbsetget_handle_"      c-type="HANDLE"     xbase-type="numeric" description="Alias of the DWORD accessor for Win32 handles." />
      </functions>
   </function-family>
</xbdoc>
*******************************************************************************************************************/
//-----------------------------------------------------------------------------------------------------------------------
typedef struct GWSTSG_strcut
{                  
   XppParamList     pl;
   ContainerHandle  conpt;
   BOOL             bWrite;
   ContainerHandle  conVal;
   DWORD            dwType;
   void *           pt;
   BOOL             bLock;  
   DWORD            dwPtSize;
} GWSTSG;
//-----------------------------------------------------------------------------------------------------------------------
// 1@v,2PCount(),3pt,4pshift,5offset,6psize,7ghost,8size
static BOOL _gwst_sg_init_( GWSTSG * psg , XppParamList pl )
{  
   DWORD tp = 0;    
   void** ppGhost = ( void**) _parnl(pl,7);
   _bset( (BYTE*) psg,0,sizeof( GWSTSG ) );
   psg->pl      = pl;
   psg->bWrite  = (BOOL) (_parnl(pl,2) > 1 );    
   psg->conVal  = ( psg->bWrite ? _conTpParamByRef(pl,1,&(psg->dwType)) : _conNew(NULLCONTAINER));
   if( ppGhost ) 
   {
      psg->pt = ppGhost[0];
      if( psg->pt ) psg->pt = (void*) ( ((DWORD) psg->pt ) + ((DWORD) _parnl(pl,5) ) );
   }
   else
   {
      psg->conpt   = _conTpParamByRef(pl,3,&tp);
      if( psg->conpt )
      {
         if( tp & XPP_UNDEF )
         {           
            DWORD dw = (DWORD) _parnl(pl,6);
            LPSTR p  = (LPSTR) _xgrab( dw );
            _conPutCL( psg->conpt , p ,dw);
            _xfree( (void*) p);
            tp = XPP_CHARACTER;
         }
         if( tp & XPP_CHARACTER)
         {
            if( ot4xb_conWLockC( psg->conpt , reinterpret_cast<LPSTR*>( &(psg->pt) ) , &(psg->dwPtSize) ) ) // 0 == OK
            {
               psg->pt = 0;
            }
            else psg->bLock = TRUE;
         }
         else _conGetNL( psg->conpt , (LONG*) ( &(psg->pt) ) );
         
      }
      if( psg->pt ) psg->pt = (void*) ( ((DWORD) psg->pt ) + ((DWORD) _parnl(pl,4) ) + ((DWORD) _parnl(pl,5) ) );
   }
   return TRUE;
} 
// -----------------------------------------------------------------------------------------------------------------
static void _gwst_sg_exit_( GWSTSG * psg )
{
   if( psg->conpt || psg->pt )
   {
      if( psg->bLock ) ot4xb_conUnlockC( psg->conpt );
      if(psg->bWrite) _ret(psg->pl);
      else
      {
         _conReturn( psg->pl , psg->conVal );
         _conRelease( psg->conVal );
      }
      return;
   }
   else _ret(psg->pl);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_BOOL_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{                  
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
      
         if( sg.dwType & XPP_LOGICAL ) _conGetL(sg.conVal, reinterpret_cast<BOOL*>(sg.pt) );
         else _conGetLong(sg.conVal, reinterpret_cast<LONG*>(sg.pt) );
         if( reinterpret_cast<BOOL*>(sg.pt)[0] ) reinterpret_cast<BOOL*>(sg.pt)[0] = TRUE;
         else reinterpret_cast<BOOL*>(sg.pt)[0] = FALSE;
      }
      else if( sg.pt ) _conPutL(sg.conVal,reinterpret_cast<BOOL*>(sg.pt)[0]);
      else _conPutL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_BYTEBOOL_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         BOOL b = FALSE;
         if( sg.dwType & XPP_LOGICAL ) _conGetL(sg.conVal, &b );
         else _conGetLong(sg.conVal, reinterpret_cast<LONG*>(&b) );
         if( b ) reinterpret_cast<BYTE*>(sg.pt)[0] = 1;
         else reinterpret_cast<BYTE*>(sg.pt)[0] = 0;
      }
      else if( sg.pt )
      {
         BOOL b = ( reinterpret_cast<BYTE*>(sg.pt)[0] ? TRUE : FALSE);
         _conPutL(sg.conVal,b);
      }
      else _conPutL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_BYTE_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<BYTE*>(sg.pt)[0] = LOBYTE( LOWORD(n) );
      }
      else if( sg.pt )
      {                      
         BYTE b = reinterpret_cast<BYTE*>(sg.pt)[0];
         _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0),0) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_SINT8_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<BYTE*>(sg.pt)[0] = LOBYTE( LOWORD(n) );
      }
      else if( sg.pt )
      {                      
         BYTE b = reinterpret_cast<BYTE*>(sg.pt)[0];
         if( b & 0x80 ) _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0xFF),0xFFFF) );
         else _conPutNL(sg.conVal,(LONG) MAKELONG( MAKEWORD(b,0),0) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_WORD_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = LOWORD(n);
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) MAKELONG(reinterpret_cast<WORD*>(sg.pt)[0],0));
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_SINT16_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = LOWORD(n);
      }
      else if( sg.pt )
      {  
         WORD w = reinterpret_cast<WORD*>(sg.pt)[0];
         _conPutNL(sg.conVal,(LONG) MAKELONG(w,((w & 0x8000) ? 0xFFFF : 0 ) ) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_DWORD_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_UINT32_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
      }
      else if( sg.pt )
      {  
         DWORD dw = reinterpret_cast<DWORD*>(sg.pt)[0];
         if( dw & 0x80000000 ) _conPutNDF(sg.conVal,(double)dw,-1,0);
         else _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_DWORD64_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         reinterpret_cast<ULONGLONG*>(sg.pt)[0] = 0;
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb, reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG) );
         }
         else if( (sg.dwType & XPP_NUMERIC) && (sg.dwType & _xpp_DOUBLE) )         
         {
            double nd = 0.00F;
            _conGetND(sg.conVal,&nd);
            reinterpret_cast<ULONGLONG*>(sg.pt)[0] = (ULONGLONG) nd;
         }
         else if( sg.dwType & XPP_NUMERIC)
         {                                                  
            LONG n = 0;
            _conGetNL(sg.conVal,&n);
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->LowPart = (DWORD) n;
         }                
         else if( sg.dwType & XPP_ARRAY)
         {                                                  
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->LowPart  = (DWORD) _conArrayGetNL(sg.conVal,1,0);
            reinterpret_cast<ULARGE_INTEGER*>(sg.pt)->HighPart = (DWORD) _conArrayGetNL(sg.conVal,2,0);
         }                
         else if( sg.dwType & XPP_OBJECT)
         {                                                  
            _conGetCLMember(sg.conVal,"Q",reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG));
         }                
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(sg.pt), sizeof(ULONGLONG));
      }
      else
      {
         ULONGLONG qw = 0;
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(&qw), sizeof(ULONGLONG));
      }
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_NINT64_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         reinterpret_cast<LONGLONG*>(sg.pt)[0] = 0;
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb, reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG) );
         }
         else if( (sg.dwType & XPP_NUMERIC) && (sg.dwType & _xpp_DOUBLE) )                  
         {
            double nd = 0.00F;
            _conGetND(sg.conVal,&nd);
            reinterpret_cast<LONGLONG*>(sg.pt)[0] = (LONGLONG) nd;
         }
         else if( sg.dwType & XPP_NUMERIC)
         {                                                  
            LONG n = 0;
            _conGetNL(sg.conVal,&n);
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->LowPart = (DWORD) n;
            if( n < 0 ) reinterpret_cast<LARGE_INTEGER*>(sg.pt)->HighPart = -1;
         }                
         else if( sg.dwType & XPP_ARRAY)
         {                                                  
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->LowPart  = (DWORD) _conArrayGetNL(sg.conVal,1,0);
            reinterpret_cast<LARGE_INTEGER*>(sg.pt)->HighPart = _conArrayGetNL(sg.conVal,2,0);
         }                
         else if( sg.dwType & XPP_OBJECT)
         {                                                  
            _conGetCLMember(sg.conVal,"Q",reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG));
         }                
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(sg.pt), sizeof(LONGLONG));
      }
      else
      {
         LONGLONG qw = 0;
         _conPutCL(sg.conVal,reinterpret_cast<CHAR*>(&qw), sizeof(LONGLONG));
      }
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_PCLIPVAR_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
        if( reinterpret_cast<ContainerHandle*>(sg.pt)[0] )
        {
           _conRelease( reinterpret_cast<ContainerHandle*>(sg.pt)[0] );
           reinterpret_cast<ContainerHandle*>(sg.pt)[0] = NULLCONTAINER;
        }
        if( !(sg.dwType & XPP_UNDEF) )
        {
           reinterpret_cast<ContainerHandle*>(sg.pt)[0] = _conPut(NULLCONTAINER,sg.conVal);
        }
      }
      else if( sg.pt )
      {  
         _conPut(sg.conVal,reinterpret_cast<ContainerHandle*>(sg.pt)[0]);
      }
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_XPPGUIWND_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
        if( sg.dwType & XPP_NUMERIC ) _conGetLong(sg.conVal,reinterpret_cast<LONG*>(sg.pt));
        else if( sg.dwType & XPP_OBJECT )
        {
           reinterpret_cast<LONG*>(sg.pt)[0] = _conMCallLong(sg.conVal,"GetTwWinBaseCppPointer");
        }
        else reinterpret_cast<LONG*>(sg.pt)[0] = 0;
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,reinterpret_cast<LONG*>(sg.pt)[0]);
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_FLOAT_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {    
         _conGetFloat(sg.conVal,reinterpret_cast<FLOAT*>(sg.pt) );
      }
      else if( sg.pt )
      {  
         _conPutFloat(sg.conVal,reinterpret_cast<FLOAT*>(sg.pt)[0]);
      }
      else _conPutND(sg.conVal,0.00F );
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_DOUBLE_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {    
         _conGetND(sg.conVal,reinterpret_cast<double*>(sg.pt) );
      }
      else if( sg.pt )
      {  
         _conPutND(sg.conVal,reinterpret_cast<double*>(sg.pt)[0]);
      }
      else _conPutND(sg.conVal,0.00F );
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_LPSTR_(XppParamList pl){ _GWST_XBSETGET_DWORD_(pl); }
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_BINSTR_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         DWORD dw = 0;
         if( sg.dwType & XPP_CHARACTER ) _conGetCL(sg.conVal,&dw,reinterpret_cast<LPSTR>(sg.pt),dws);
         if(dw < dws) _bset(reinterpret_cast<LPBYTE>(sg.pt) + dw , 0 , dws - dw );
      }
      else if( sg.pt )
      {  
         _conPutCL(sg.conVal,reinterpret_cast<LPSTR>(sg.pt),dws);
      }
      else
      {    
         void * p = _xgrab(dws);
         _conPutCL(sg.conVal,reinterpret_cast<LPSTR>(p),dws);
         _xfree(p);
      }
   }
   _gwst_sg_exit_(&sg);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_SZSTR_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         DWORD dw = 0;
         if( sg.dwType & XPP_CHARACTER ) _conGetCL(sg.conVal,&dw,reinterpret_cast<LPSTR>(sg.pt),dws);
         if(dw < dws) _bset(reinterpret_cast<LPBYTE>(sg.pt) + dw , 0 , dws - dw );
      }
      else if( sg.pt ) _conPutC(sg.conVal,reinterpret_cast<LPSTR>(sg.pt));
      else _conPutC(sg.conVal,"");
   }
   _gwst_sg_exit_(&sg);
}
// -----------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_SZWSTR_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   DWORD dws = (DWORD) _parnl(pl,8);
   GWSTSG sg;        
   
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {                                 
         _bset(reinterpret_cast<LPBYTE>(sg.pt),0,dws);
         if( sg.dwType & XPP_CHARACTER )
         {                                                                                     
            ULONG nMax  = ((dws -1) >> 1);
            ULONG nLen  = 0;
            LPSTR pAnsi = 0;
            ot4xb_conRLockC(sg.conVal,&pAnsi,&nLen); 
            if( nLen > 0 )
            {
               if( nLen > nMax ) nLen = nMax;
               MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,pAnsi,nLen,reinterpret_cast<LPWSTR>(sg.pt),nLen);
            }
            ot4xb_conUnlockC(sg.conVal); 
         }
      }
      else if( sg.pt )
      {  
         ULONG nLen  = ( dws >> 1 );
         LPSTR pAnsi = (LPSTR) _xgrab(nLen + 1);
         WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,reinterpret_cast<LPWSTR>(sg.pt),nLen,pAnsi,nLen,0,0);
         _conPutC(sg.conVal,pAnsi);
         _xfree( (void*) pAnsi);
      }
      else _conPutC(sg.conVal,"");
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_DYNSZ_(XppParamList pl) // (1@v,2np,3@pt,4ns) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         if( reinterpret_cast<LPSTR*>(sg.pt)[0] )
         {
            _xfree(reinterpret_cast<void**>(sg.pt)[0]);
            reinterpret_cast<void**>(sg.pt)[0] = 0;
         }
         if( sg.dwType & XPP_CHARACTER )
         {         
            reinterpret_cast<LPSTR*>(sg.pt)[0] = _conXStrDup(sg.conVal);
         }
      }
      else if( sg.pt )
      {  
         if( reinterpret_cast<LPSTR*>(sg.pt)[0] )
         {
            _conPutC( sg.conVal , reinterpret_cast<LPSTR*>(sg.pt)[0] );
         }
      }
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_WORDNET_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<WORD*>(sg.pt)[0] = htons(LOWORD(n));
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) MAKELONG(ntohs(reinterpret_cast<WORD*>(sg.pt)[0]),0));
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_DWORDNET_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         LONG n = 0;
         _conGetLong(sg.conVal,&n);
         reinterpret_cast<DWORD*>(sg.pt)[0] = htonl(n);
      }
      else if( sg.pt )
      {  
         _conPutNL(sg.conVal,(LONG) ntohl(reinterpret_cast<DWORD*>(sg.pt)[0]) );
      }
      else _conPutNL(sg.conVal,0);
   }
   _gwst_sg_exit_(&sg);
}
//-----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_XDATE_(XppParamList pl) // (1@v,2np,3@pt,4ns,5npsize) 
{
   GWSTSG sg;
   if( _gwst_sg_init_(&sg,pl) )
   {
      if( sg.bWrite && sg.pt ) 
      {
         _bset(reinterpret_cast<LPBYTE>(sg.pt) , 0 , 8);
         if( sg.dwType & XPP_CHARACTER )
         {
            DWORD cb = 0;
            _conGetCL(sg.conVal,&cb,reinterpret_cast<CHAR*>(sg.pt), 8 );
         }
         else if( sg.dwType & XPP_DATE )
         {
            _conGetDS(sg.conVal, reinterpret_cast<CHAR*>(sg.pt));
         }
      }
      else if( sg.pt )
      {  
         _conPutDS(sg.conVal,reinterpret_cast<CHAR*>(sg.pt));
      }
      else
      {
         char sz[16];
         _bset((LPBYTE)sz,0,16); _bset((LPBYTE)sz,32,8);
         _conPutDS(sg.conVal,sz);
      }
   }
   _gwst_sg_exit_(&sg);
}
//----------------------------------------------------------------------------------------------------------------------
XPPRET XPPENTRY _GWST_XBSETGET_POINTER32_(XppParamList pl) { _GWST_XBSETGET_DWORD_(pl); }
XPPRET XPPENTRY _GWST_XBSETGET_HANDLE_(XppParamList pl) { _GWST_XBSETGET_DWORD_(pl); }
// -----------------------------------------------------------------------------------------------------------------




